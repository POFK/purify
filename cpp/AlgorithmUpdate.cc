#include "purify/config.h"
#include "AlgorithmUpdate.h"

namespace purify {

  AlgorithmUpdate::AlgorithmUpdate(const purify::Params &params, const utilities::vis_params &uv_data,
      sopt::algorithm::ImagingProximalADMM<t_complex> &padmm,
      std::ostream &stream, const MeasurementOperator &measurements,
      const sopt::LinearTransform<sopt::Vector<sopt::t_complex>> &Psi, const t_uint channel_number, const bool use_weights)
    : params(params), stats(read_params_to_stats(params)), uv_data(uv_data), out_diagnostic(stream),
    padmm(padmm), c_start(std::clock()), Psi(Psi), measurements(measurements), channel_number(std::to_string(channel_number)), weights(std::make_shared<Vector<t_complex> >(Vector<t_complex>::Constant(uv_data.weights.size(), 1))){
      if (use_weights){
      weights = std::make_shared<Vector<t_complex> >(uv_data.weights);
      auto degrid = [&](const Vector<t_complex> & x) -> Vector<t_complex> {
        const Image<t_complex> image = Image<t_complex>::Map(x.data(), measurements.imsizey(), measurements.imsizex());
        return measurements.degrid(image).array() * weights->array();
      };
      auto grid = [&](const Vector<t_complex> & x) -> Vector<t_complex> {
        const Image<t_complex> image = measurements.grid(x.array() * weights->array());
        return Image<t_complex>::Map(image.data(), image.size(), 1);
      };
      std::function<Vector<t_complex>(Vector<t_complex>)> direct = degrid;
      std::function<Vector<t_complex>(Vector<t_complex>)> indirect = grid;
      dynamic_range_norm = std::sqrt(utilities::power_method(direct, indirect, measurements.imsizex() * measurements.imsizey(), 100));
      }
    };

  bool AlgorithmUpdate::operator()(const Vector<t_complex> &x) {
    if (params.adapt_gamma or params.run_diagnostic){
      std::clock_t c_end = std::clock();
      stats.total_time = (c_end - c_start) / CLOCKS_PER_SEC; // total time for solver to run in seconds
      // Getting things ready for l1 and l2 norm calculation
      Image<t_complex> const image = Image<t_complex>::Map(x.data(), params.height, params.width);
      Vector<t_complex> const y_residual
        = ((uv_data.vis - measurements.degrid(image)).array() * weights->array());
      stats.l2_norm = y_residual.stableNorm();
      Vector<t_complex> const alpha = Psi.adjoint() * x;
      // updating parameter
      AlgorithmUpdate::modify_gamma(alpha);
      auto new_l1_norm = alpha.lpNorm<1>();
      stats.l1_variation = std::abs(stats.l1_norm - new_l1_norm)/stats.l1_norm;
      stats.l1_norm = new_l1_norm;
      if(params.run_diagnostic) {
        std::string const outfile_fits = params.name + "_solution_" + params.weighting + "_update_" + channel_number;
        std::string const residual_fits
          = params.name + "_residual_" + params.weighting + "_update_" + channel_number;

        auto const residual = measurements.grid(y_residual.array() * weights->array());
        AlgorithmUpdate::save_figure(x, outfile_fits, "JY/PIXEL", 1);
        AlgorithmUpdate::save_figure(Image<t_complex>::Map(residual.data(), residual.size(), 1),
            residual_fits, "JY/PIXEL", 1);
        stats.rms
          = utilities::standard_deviation(Image<t_complex>::Map(residual.data(), residual.size(), 1));
        stats.dr = utilities::dynamic_range(image, residual, dynamic_range_norm);
        stats.max = residual.matrix().real().maxCoeff();
        stats.min = residual.matrix().real().minCoeff();
        // printing log information to stream
        AlgorithmUpdate::print_to_stream(out_diagnostic);
      }
      AlgorithmUpdate::print_to_stream(std::cout);
      stats.iter++;
    }
    return true;
  }

  void AlgorithmUpdate::modify_gamma(Vector<t_complex> const &alpha) {
    // modifies gamma value in padmm

    // setting information for updating parameters
    if(params.run_diagnostic or (params.adapt_gamma)) {
      stats.new_purify_gamma = alpha.cwiseAbs().maxCoeff() * params.beta;
      stats.relative_gamma = std::abs(stats.new_purify_gamma - padmm.gamma()) / padmm.gamma();
      std::cout << "Relative variation of step size = " << stats.relative_gamma << '\n';
      std::cout << "Old step size = " << padmm.gamma() << '\n';
      std::cout << "New step size = " << stats.new_purify_gamma << '\n';
    }
    if(stats.iter < params.adapt_iter and stats.relative_gamma > params.relative_gamma_adapt
        and stats.new_purify_gamma > 0 and params.adapt_gamma) {
      padmm.gamma(stats.new_purify_gamma);
    }

    // Information saved for diagnostics
    if(stats.iter == 0)
      stats.new_purify_gamma = padmm.gamma(); // so that first value on plot is not zero.

  }

  void AlgorithmUpdate::print_to_stream(std::ostream &stream) {
    if(stats.iter == 0)
      stream
        << "i Gamma RelativeGamma DynamicRange RMS(Res) Max(Res) Min(Res) l1_norm l2_norm l1_variation Time(sec)"
        << std::endl;
    stream << stats.iter << " ";
    stream << stats.new_purify_gamma << " ";
    stream << stats.relative_gamma << " ";
    stream << stats.dr << " ";
    stream << stats.rms << " ";
    stream << stats.max << " ";
    stream << stats.min << " ";
    stream << stats.l1_norm << " ";
    stream << stats.l2_norm << " ";
    stream << stats.l1_variation << " ";
    stream << stats.total_time << " ";
    stream << std::endl;
  }

  void AlgorithmUpdate::save_figure(const Vector<t_complex> &image,
      std::string const &output_file_name, std::string const &units,
      t_real const &upsample_ratio) {
    // Saves update images to fits files, with correct headers
    auto header = AlgorithmUpdate::create_header(uv_data, params);
    header.pix_units = units;
    header.cell_x /= upsample_ratio;
    header.cell_y /= upsample_ratio;
    Image<t_complex> temp_image = Image<t_complex>::Map(image.data(), params.height, params.width);
    if(upsample_ratio != 1) {
      temp_image = utilities::re_sample_image(temp_image, upsample_ratio);
    }
    header.fits_name = output_file_name + ".fits";
    std::printf("Saving %s \n", header.fits_name.c_str());
    pfitsio::write2d_header(temp_image.real(), header);
    if (params.stokes_val == purify::casa::MeasurementSet::ChannelWrapper::polarization::P){
      header.fits_name = output_file_name + "_imag.fits";
      std::printf("Saving %s \n", header.fits_name.c_str());
      pfitsio::write2d_header(temp_image.imag(), header);
    }
  }

  pfitsio::header_params AlgorithmUpdate::create_header(purify::utilities::vis_params const &uv_data,
      purify::Params const &params) {
    // header information
    pfitsio::header_params header;
    header.mean_frequency = uv_data.average_frequency;
    header.ra = uv_data.ra;
    header.dec = uv_data.dec;
    header.cell_x = params.cellsizex;
    header.cell_y = params.cellsizey;
    header.niters = stats.iter;
    header.hasconverged = false;
    header.residual_convergence = params.residual_convergence;
    header.relative_variation = params.relative_variation;
    header.epsilon = params.epsilon;
    return header;
  }
}
