#include "catch.hpp"
#include "utilities.h"

#include "directories.h"
using namespace purify;
using namespace purify::notinstalled;

TEST_CASE("utilities [mod]", "[mod]") {
    Array<t_real> range;
    range.setLinSpaced(201, -100, 100);
    Array<t_real> output(range.size());
    for (t_int i = 0; i < range.size(); ++i)
    {
    	output(i) = utilities::mod(range(i), 20);
    }
    Array<t_real> expected(201);
    expected << 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
    			0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
    			0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
    			0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
    			0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
    			0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
    			0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
    			0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
    			0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
    			0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,
    			0;
    CHECK(expected.isApprox(output, 1e-13));
}

TEST_CASE("utilities [reshape]", "[reshape]"){
	//Testing if resize works the same as matlab's reshape
	Matrix<t_real> magic(4, 4);
	magic <<     16, 2, 3, 13,
     			5, 11, 10, 8,
     			9 ,7, 6, 12,
     			4, 14, 15, 1;
    std::cout << magic << '\n' << '\n'; 
    Vector<t_real> magic_vector(16);
    magic_vector << 16, 5, 9, 4, 2, 11, 7, 14, 3, 10, 6, 15, 13, 8, 12, 1;
    Matrix<t_real> magic_matrix(16, 1);
    magic_matrix <<  16, 5, 9, 4, 2, 11, 7, 14, 3, 10, 6, 15, 13, 8, 12, 1;
    magic_matrix.resize(4, 4);
    CHECK(magic.isApprox(magic_matrix, 1e-13));
    magic.resize(16, 1);
    std::cout << magic << '\n' << '\n';
    std::cout << magic_vector << '\n' << '\n';
    CHECK(magic.isApprox(magic_vector, 1e-13));
}
TEST_CASE("utilities [variance]", "[variance]"){
    //tests if mean and variance calculations are the same as done in matlab
    Vector<t_complex> real_data(1000);
    Vector<t_complex> imag_data(1000);
    real_data << -0.304871646251481,-4.62603736001300,2.89479789103017,-1.18412834471061,3.28740829917557,-3.25177986056312,6.57579107437387,-3.08481515653644,1.57914018226523,-1.82282396723939,5.20031406450509,-1.18729284264620,7.67616027792363,-4.24820904958422,7.77755399808376,2.32942694059886,2.83998885689594,-4.26994543471429,2.57392360377323,9.92319398185083,5.70640670486071,-0.978627190669815,4.59178984175619,-2.24374650603078,0.110632525875461,6.51703732237824,1.22358367337407,5.33698627176785,-0.981258708920104,-1.69563469512575,7.59108544689703,-1.59559348282270,0.963928199575646,3.38171581995345,-0.570952540661118,-3.60063138584332,-3.53523103623847,-6.64632040728694,0.0837879449510339,-1.36302372717401,-1.21288038883875,1.65833713095149,1.99398236056317,3.05348201592943,-11.0683187959990,-3.48157356917687,2.17025475448036,9.05336451242196,6.28641495102244,1.42947190873289,-3.30074633677492,6.05203787534855,2.27061040480860,6.46272806854716,0.861937243983027,-1.00245590670456,2.37485961736422,-0.437148497697265,11.7599243979369,-0.0153486683803967,-1.51234368881153,-4.99978359696340,1.42933631679275,-7.64687675426753,8.43231428976918,6.57482913865467,0.411755102751832,-3.96417648634455,7.38871735404052,-3.10611807497408,1.55510006887839,2.01761613757515,-2.00252313613308,-1.31141605255069,5.16911199615848,2.15651275810105,6.94829299713291,2.56224243349130,-8.19974395098838,-5.37793987955010,0.627293730266188,7.03457417505869,4.69989761309208,-3.85613983319366,0.859614966768149,-4.40354213136022,-3.78090038292121,2.95705895396639,-1.24385199200532,-2.89554588670256,-5.62976383681049,12.9266113638096,-0.807106516546915,4.75635742136928,3.09514288950858,8.81548751141640,5.83440703454209,1.48319033402307,-3.78514660831270,8.35289189463272,5.01686308784148,-6.68568099290313,-5.37016712751932,4.02258776130105,-0.268021237604272,-6.38789762378788,3.19767946495718,-3.10612417843103,-2.85573325895684,-1.18802482445593,-8.57127046282132,0.457551702989969,-4.39523221095666,3.49163883320307,2.23560008013935,1.71703888378303,1.83290006052668,0.429397370236555,0.0625895053908976,-2.25774840923025,9.33598054333443,7.45478760635764,7.83350797167199,3.17969240527688,-3.86662264970754,-1.78740354718113,0.524032190058226,1.82869292821448,2.73441381375104,-3.00402408212204,2.54762617761715,-2.15322864322887,-0.295710624989347,6.32162572352084,3.35190211814156,-0.266008569454657,-8.38323693808447,-1.28058841357944,-2.38164990987167,-1.25906538152318,3.46863370266427,5.23347113720382,-10.5625747430748,9.70712787052213,4.60833178509528,-7.35308616292756,3.42385834677800,6.00158052951119,6.62023362277060,1.92647963551794,2.03285471008095,5.26616769082545,16.4664267451528,-0.517695857966012,3.91797802788733,-9.94288706781086,5.56195418297089,3.38145787294056,-0.233183847610455,6.21519238994984,0.269743660488877,11.9043220834077,0.713565675490835,1.26292433654540,-5.91260369426215,-1.50721683619082,4.06671589609282,-5.91588691469489,-0.638317510551886,4.64272861722784,0.727550497893618,-6.72463272154224,2.92612610227580,-3.99298413158102,-2.72819175648628,-3.37894637916873,1.57345339423708,2.48376219156236,-7.62146111069280,-6.10370947462684,-0.684937774323206,-6.05655595202125,10.5354720771235,5.85608264034074,0.165143827300987,-3.72633919772992,1.09622271064418,6.39124212759812,2.25077874247647,3.93071452327201,0.641191772670900,3.37114489406308,-1.58246552799544,-12.0171582734810,0.968767548724441,-7.32627959217928,15.6006534658082,5.16509484656095,2.86411297249784,-0.969079346005554,7.74119247512036,1.51188826226407,8.85697430130889,-0.185512010903133,-0.799815177516084,4.27724773399404,5.80827122333193,-0.656408967233853,6.81456055390945,1.12377891482625,-0.166915062827608,-1.13567741259998,5.37172876369035,6.78637179194177,6.41838800372213,0.800773885955218,-0.261043095088481,6.49325819538115,-0.860965756354604,-2.56180102836019,-3.95942844613064,7.05242569998032,7.09855113386012,0.952615405821957,-0.461814574505765,3.99752618382877,-1.97909977957980,-0.853941179911548,0.347509358399474,-1.25281125928826,-2.52524170158662,7.79993485394360,8.85122066389378,-9.75993764825300,2.99561892787259,-0.766474823218961,-7.31631933924657,-0.114049401593624,-4.16921034774916,1.29515330874055,1.82470953345502,3.47602523505394,10.3850645256708,-5.08314680256437,2.48037985046054,11.9915598168670,10.4486266313344,-0.0329557721035410,-3.39875978306217,9.22231827502714,0.752164413974553,-0.318770429843339,-0.236971115317257,-2.49657441760545,1.05824590371991,-5.03398963394596,-4.43742433420020,-2.51568537005456,4.87628527585931,-1.12576923790285,1.02232722349752,3.84762703587408,-6.29857822308523,-1.04743313114510,3.78190698761212,4.26357624884139,-4.36144690578181,0.895821048190199,3.18169520061912,9.67741571037172,3.92330577263777,4.53046956048403,2.03970760267893,-12.2087464172536,-2.80025159428704,13.1546583319495,0.257407452338385,8.87604078090450,10.1913606897186,4.45625536337108,5.17525505954991,12.6995156944563,3.53298645014089,3.66797361111089,-0.920412180518470,-1.12544078650837,-3.39312902415609,-0.394096444531947,9.44590839752380,-2.29678934087303,7.72514064380050,-3.21327137410669,-3.00109555239550,0.800259582920075,8.04249709367907,-4.78090775912717,-11.2662859389425,-1.39112073489616,0.0578134368030262,-5.49232881581517,-1.55816989125497,-2.56870369097279,4.95117511486281,2.23668096237959,6.69521883184985,-3.41064341468595,1.24415067370110,-5.76942301227751,-0.478988827580625,0.558425568099049,-1.86660078592210,4.94755692811883,4.96875216274676,2.98640616013369,4.93473870668456,3.32928826211659,1.45252073202632,4.15847148150737,2.25062134243402,7.42510747020106,6.58647722913802,-1.93128657467670,-2.88706622831837,-0.238212768211347,-1.30463181392330,-4.78691959362851,-4.21369830861531,10.7065850211718,7.67089330653863,3.61795607787935,-4.26952956893565,2.51437866984996,-3.89434226485586,0.627065138919257,7.36761337399496,-3.98690978957778,3.07521927014135,4.14485802000430,2.16849131116939,-4.59098893232999,2.27038702570936,4.01472046275456,4.99638652718776,-2.76277205779229,-2.03995515075022,-0.830588491105003,8.15605840087383,-0.162660414629817,10.9832722204952,5.69826704493030,-1.56732571822185,-1.86645053763715,4.41749058754194,8.65456946963044,-6.54900503999606,5.26899910293145,-5.35680446591694,1.35946336986068,4.86563574737864,-3.36649410971853,-10.5871193712191,5.21088561317662,-9.18940773227009,4.96596216620697,-2.48149161431985,0.228960506150837,-3.24926765204553,6.35197742343566,-6.31527005726567,0.554522905287991,14.7400071024983,-1.39266757266294,-1.01310289777242,8.75603567487079,9.39262051264440,-5.12725413327830,1.45905893622463,3.66918561523921,-0.857020582747409,-1.81518070364695,-7.07286868131938,2.75256378532304,6.66344341819134,2.84053571078512,2.67088971694903,11.2182618619012,-1.70861632656683,-4.45309498611035,0.875238870365231,-6.17349967626331,-1.56822603376212,8.98731820700610,-2.79039196756435,-10.2070334506147,-4.68185028798843,-6.06280980010291,2.41331744496787,0.917756691494894,0.924732790324821,4.16328687386515,8.27311881401087,-3.21659068369282,6.23590246619682,3.68359319855757,-2.01118349914524,4.53403415303649,8.85950703668960,10.2250757062703,-4.05289160915994,-5.93781572446527,-1.49491847183201,-2.14026752589302,-2.70754821474371,-3.25470911834631,-1.71083815474188,11.0701976453593,2.95142294074158,-3.94365089698928,6.41331769350352,4.92361164995862,3.84560882088285,1.49424618510360,-1.21452890702989,-1.50124839770504,-3.63669661226995,-2.95580102658412,-10.0283988713485,4.25108572652464,-2.79861486254524,1.79576269113739,-2.46854057271204,1.43874747021213,4.71170927898291,2.65972847073781,0.0774399431087178,-8.18632132979020,0.306914271432588,2.07783218602005,-2.99779687204432,-5.28915822678984,1.55155838012907,10.4730524137230,-1.60797994985866,11.8404592488137,3.08733069813233,-0.149200149751186,-0.342774220023828,-0.788894604224912,1.50502361404252,-5.88522330032159,-3.24943698534991,-5.41273982679859,0.326285568387692,0.633894740999722,3.16890877036231,-0.399831958647647,-0.733759753685250,-8.69851827109190,7.78013489820438,-9.25607927819911,11.8424355106976,-2.29606632855045,-4.69706237766711,3.81515011658988,7.57750020293164,5.89577190280955,3.32586505238965,0.759554925803211,-2.77051289647204,0.539472751308121,0.826298322677624,1.30089431622670,5.27437907453959,-1.98563219023301,6.50661561945000,1.74926496387967,-5.76940622447260,4.16628593946908,5.72449297792307,-6.06258091123031,0.152539025832594,5.36135225305430,-2.59632046001016,0.917170250091547,-2.21035496836755,-4.89752611289268,0.312858555569878,-7.49518209466485,-1.11278938898732,0.891817615686645,0.277695816153466,2.68248926961839,-2.87691758111303,7.69831562263081,2.06370985838696,9.01636729125548,-9.71022405716541,-3.74191583394569,2.08306335754776,-4.47780148896520,5.22782141022555,-11.4928216700246,-3.20957220636306,6.44096388450743,-4.81423574982668,2.75977912412331,6.12808534325993,9.07443557909446,-0.818442295005394,12.3295588360187,-1.39227508995055,9.03662376677530,-7.66240984565544,-5.03085245075158,-6.73620525786908,-10.4644137479552,3.64504131799904,3.17250678136788,2.50683591341223,2.09725681931025,-8.78372379037181,7.02310889922868,-3.48240417181402,3.05126397695640,3.73344215795254,2.01710265315386,4.64034067178540,1.63001339825217,3.40986388477025,-3.01030642864604,-5.08244341243308,-1.31449055361912,-3.89202919475140,3.18616073438052,-0.706775083999013,2.01239057632623,3.20358355001171,3.94648152790166,1.58331128499275,0.133063309988423,-1.64134534485133,-7.22362871329933,0.654806927356218,-1.43746708794710,3.08511575937882,4.09230565172823,-1.61999600470000,-4.65602666679112,3.32645059215221,-0.159079796958906,7.84733410420804,5.67520962790926,0.478531987663319,-7.46950827666333,2.23257758058921,-2.40597626535361,-1.18573437072693,-1.85952612074340,-3.56578137888780,-5.52757352441546,0.857637646334361,-0.173308262564145,8.61495996612215,-2.07577562259519,-2.88830759307507,1.92107739208390,5.27146695434436,7.49015127946350,-1.55962786090150,-0.580385696989890,2.51717466829235,0.881788386135386,-1.83919909903432,4.32135749992859,1.61478619227291,5.04591172541219,-0.0430991122212729,4.74800937017269,4.60529042829142,-0.250035548067627,-5.55367250415187,3.23790726107020,0.648582812629880,6.94979191201439,-0.271409012387628,2.94220823559735,0.689323159851766,-1.89985695807300,0.878799425481135,3.29777435167177,-0.349082074711658,-1.61602276730829,4.25219178488917,-3.52474353715648,-5.89748006710824,1.55372710929945,-4.82197288794396,-6.63701805260267,1.52040223599521,3.77521483856861,-1.95115688486076,3.17604198728810,-5.77051739038793,1.00958582882813,-4.79948594683746,-3.71914173594001,-3.60303504765420,-10.4919277562959,4.62208693171367,-7.71803694238380,0.849731963841210,2.62637739297002,-3.58785291165739,0.819647176309389,11.8245661051223,6.07564079791273,-1.15948847790392,-2.61449021036601,-0.393838114711378,-3.79314877655343,3.54039000231522,-0.794617338766761,-11.3736557656149,7.81390969501663,1.92951364046261,5.28556803215442,-0.320962260538130,-1.63395033885826,-1.89927848282418,-10.9925206677374,3.79475503078504,12.9603003728663,1.47665077904018,3.86957361065098,6.89937225770666,2.53370838747424,6.33989500615187,7.79787198698353,-4.58970645930858,3.84995113720784,6.73291244623548,1.27622594007762,2.62803429828329,5.39513957139019,6.72445247192094,1.59129069184852,3.89874076278359,-7.26444238325722,3.99524891346277,-6.82568042091550,2.49314032882569,1.23725179239920,-1.87708259299877,2.70897681064533,5.57174262971643,2.02313625907951,-2.01782324507880,-4.86698586581035,2.92824094480277,-5.06302446478984,-3.52131439193377,1.16804648253090,-8.43749307518137,0.233256250832780,-8.43065228830794,9.88841442608929,1.81070123139502,2.17897532408756,1.40049945549523,7.96369219238187,1.21737806462432,6.93403677780472,5.20400245618654,-9.24583026725738,0.288562170257240,-2.21730540294912,9.42107839921778,-5.47330110822727,3.35473226955235,-1.23305466936994,-3.64435585899363,1.89767040200032,-6.12290928982579,-2.77817813513786,9.03093097309737,-1.54588301070869,-1.26500470672100,-1.77060887551992,7.66119928110060,11.3252222231009,-4.50164046724817,-1.72436834813889,12.5477975074134,-0.676914006742619,-8.08102226027525,2.79676403275100,-3.51785223611093,-9.51113927835644,1.65260218723022,3.64367555630810,-4.13971193959743,-7.77661154947703,-9.48385879630466,7.59940131961359,4.16565860850835,5.87121272382912,-4.33713448396085,4.70504592399210,-4.80846361942211,-4.21773189183657,-0.571735499434708,0.573122811174840,-4.29586564065037,3.24258456530442,1.17391781813773,1.20953888979682,9.75982479869557,-6.46015024860565,4.46453778182353,1.74729189251012,-2.68883025861726,-3.61679684153980,-8.10494075728425,-4.79186657567037,-9.31705140497529,-0.483866393904819,2.41320985398994,2.50712550561546,-2.47426548105751,-0.0246012168460918,-0.880595921310072,5.76140040434536,-0.0252716034832265,0.0700813120669455,2.30189042685091,2.76075892285585,-16.2203495952501,-8.18883786676409,1.01193731794856,5.76877278568406,-2.56987335423265,2.21336199530247,-6.40305357924542,-10.2418067454991,1.50094591522668,5.01150874819511,-2.41306785588914,-0.0535356883958651,-1.29682028778407,2.74094697576116,2.67271710498871,-4.09638167251074,15.1196772725298,0.0756239967442751,-1.51711553574781,-3.69979968479807,4.95205888300674,0.633682536429214,1.15672527940680,9.42081617794284,-0.691800198768938,-3.75166763665156,-1.92801680392049,-5.33845487262056,-7.58106150855294,5.02817599446681,7.31359946419604,2.74095374048281,10.2979100312990,-6.87822226301953,-5.72013049829560,5.48552451800657,10.7134068950197,1.73661771425818,1.85300498810294,6.80440489913772,3.39802119157946,-1.20698924453653,-2.11108830936905,3.11731756059177,-1.60697831705699,-6.08157386789615,1.88138717439771,3.51440237331965,3.92412213101022,7.54673429995519,-0.383230567100305,3.70205000986234,-4.17431802860574,14.3443780556058,3.41290302590971,-1.40673622671623,-1.69815309338568,4.44662751799979,-3.55089449675681,0.175905920008742,-2.16759663989078,0.383346895577652,5.52204614818013,0.356264726519447,3.01420991731377,-5.02697001880823,7.46994778757799,2.60793488311112,7.17409216043777,-1.03340836086745,5.85513389443422,1.19100175446739,7.31422975445867,3.36115113878701,4.25958668241305,8.14547466862683,0.141081196749173,3.25997732076374,-2.11885376539086,1.90609331621345,-14.5018831991699,-3.69261389871465,1.73056788265469,-5.20741790403998,-1.74322234760533,-4.36742426083223,2.47812316161614,1.79549371352784,2.55075378456809,0.583769651572968,-4.06222346716452,0.552348698464589,-7.49884452882456,-2.42635650630472,2.90936466936645,-6.92934985519854,0.215894963136942,10.4761652261157,6.68435231959022,1.44587177931717,0.0208867599884188,-4.26456060118204,0.747891036400417,1.69345826316541,-0.819070042373630,-0.293733389973047,-2.54292224419930,3.98572336808965,6.08771368964386,-8.36940270837905,2.34598964150070,4.20560623411918,-5.92417549932155,1.11058860059025,-1.51199824445307,1.15037653693476,8.42699906457299,5.97254608897704,11.6860810063801,5.80364500501798,0.0704344117275013,11.2832269235182,-1.49502960851693,-1.96173260650301,-2.79553251254815,10.8679372041617,0.566423136540294,-1.12975153535277,7.66415920964324,-6.42596601303098,4.15604498904345,0.650188179095152,-2.61304659103059,-3.36216842119820,1.38214973681451,6.00653252440517,-0.893049882403514,-3.45896201733265,6.44440396830157,1.47515390388127,8.60143664525990,3.64307575067413,3.10255616639315,1.19691909339811,-0.159792842692416,0.364855978009565,-7.45946398267937,-1.37112105993349,-10.3323435026339,3.64770848075161,-0.953191857282005,-14.5288634197350,-2.84159192640324,8.03297732554050,11.5380610320953,0.0242342721461294,5.71168129422183,0.764208760018126,6.52995755471509,-2.09062873152825,1.40727478421899,-1.07785699317413,4.90755928027094,1.56894059318796,-1.34689839607623,-3.78763867751540,-7.79686677362601,1.33316877494421,6.50123423889480,12.2511642417766,3.54230793894662,-2.97909816450795,1.12329442832884,3.61166715704603,-4.34953880198287,1.75739457456872,-1.85733426239985,-0.798113625163649,1.41747952101914,-0.173292359733162,-3.07788259145342,-4.87489631376816,-2.13211238341864,-3.46919660505687,4.17315209579482,-0.987121057221432,4.50958873371820,4.41354564906371,-0.674009587539918,-9.22482694280142,4.98430462743730,2.01412935902473,1.96045387923195,11.1686682686664,-5.52848396028967,9.27813179123906,-4.15404606021071,-5.53129575052918,-4.75692292237653,4.44837277043781,-3.38980445370567,4.73733370521530,1.51851130806232,-3.01878679070993,4.68753260220639,5.98241366130885,7.85459099959736,-8.04372102210121,-2.95157325534637,1.47114772520249,-5.07968274842957,7.30730532046769,0.579425442551930,-1.45759783319033,1.55981888645766,-2.26559406514121,4.52366738179315,-2.43775973288395,-0.493919116759299,3.77804490477091,-1.80267285992610,-3.76023230062060,-0.821696851064633,-1.47684878059274,-0.318470843337414,2.20681888141531,-2.75696082764366,4.66601156562901,4.50612414700332,-0.863602180525014,2.65213467784661,0.121780638319554,3.67790084228628,-0.812716817977069,2.92381550678327,2.14169850054183,3.47461797947730,-2.45772748781195,-6.43062333882092,1.80834402021409,2.22104253016101,-7.31727017051562,4.88391177582513,6.72146491415179,-1.64488212928209,-3.78564457404357,-1.81805622418963,-3.79139955772150,-1.55449432483884,2.02905769368022,0.641568789380687,7.25248270898054,-2.54943278610886,-5.42557922799508,-0.331900369174413,6.37637102980283,6.78171060095286,-5.81403692003900,-3.74832855841457,6.80797294461787,5.61637683646012,-6.99296555397079,-8.01258738801508,5.61712581205823;
    imag_data << -0.986882552409172,-6.07501583823682,1.04224390677593,6.12109689199267,8.08596035936394,-9.69204180447640,7.93936757662919,1.08724319346849,-3.30119724566667,2.43096732234842,3.31535480937915,-1.07482267418662,5.65346280046854,1.32128669472792,6.40493996896904,6.42736115611448,1.60828754663213,9.61688200194750,3.26413391942863,-2.23346626274541,3.10534938344038,-1.36026283148658,1.62477413237842,-0.662183832279980,1.81974754244311,7.96207145034602,8.17131543034288,5.69916554848738,2.58850491076691,-3.33905462066976,0.354659145294300,-0.116237327964654,2.82012119620926,-0.113989188965345,2.37304875703997,6.86980680499961,9.81665014154167,3.67333104489920,-4.48234952117331,-4.47979466248224,-0.138127498113111,3.90644513463164,3.60893046981311,2.87871322066868,-4.81258138912959,-5.02289987958370,6.96070560581372,1.08403339841240,0.511137979245540,-5.56681277467583,4.47126834448546,1.17330025093820,0.158836605742939,7.55236661419922,-1.84806176107197,-4.90624594167696,0.721630676819963,16.2086748167896,1.47464374254018,-3.36321999545958,-2.62454193712060,2.33318817512124,5.14657975758975,-5.06360051459087,3.91877645541654,-0.719360468727516,4.87793468192931,2.16339481260488,2.45870271065779,8.29364969247691,1.28801311285681,-6.51253685984997,9.72838484962368,2.82362450889971,3.20576457118370,3.94126038845295,1.37372333998935,-7.53633475016151,2.19313210642212,-3.51657846488918,6.60283189509381,-3.50881143948398,8.04141736388496,-0.296166719294966,-7.98215845047705,1.10758227924007,8.07457788328428,3.99260862248730,-3.21986584507869,3.92398669964722,-12.3316112645275,13.1509866086670,6.25658368145091,11.7820505795418,-6.29691322747959,3.61819381742987,5.53151435880995,-3.18957138974001,-1.67528502428909,-9.43190736580015,4.77521989480519,-6.09060069841387,7.90084623744846,2.39554866140079,-3.97297667998080,4.09391809621037,0.561272424347159,3.05728767698966,5.72935814683570,5.93605222789931,3.24417095803820,2.10443041755413,8.09055477148937,10.7601414005651,3.61667448970805,12.5345792477085,-5.11710933197295,-5.91499499688306,8.58418294496932,1.23483750755074,-4.82116927971952,0.161022596213568,-0.857127524323761,-0.722099000600333,3.10296344954057,1.75645779396265,-4.04751249036971,-2.49083364140783,3.89591025369235,10.7027260615579,6.44386903525731,-2.03533829723088,0.936125924625500,3.39982638132463,-4.51479036143136,-0.157713002060717,-1.13726629891304,2.76756861800344,2.60564650654058,4.66416003649834,-2.03641143668209,0.272194277124408,-1.59121684612026,2.90133122562933,2.99246001363313,-0.573933306466889,11.9340061295572,-6.99106930570533,-6.59196528454363,-6.73376131314796,1.56931920313704,-2.48419720882059,-4.88772319902451,2.46935437910237,-3.78323786173625,-3.00440577724486,1.00958253213171,1.62162977658495,-2.58251128672134,-5.98997958862717,-5.74820134898325,7.78689626528120,-2.48743781385432,1.07500149360069,-2.89058015717386,4.96041778938595,1.93712704721737,7.23823251055940,6.46370581692482,6.15901352433280,5.11654447829599,-6.58388020572824,-1.08557736207495,-1.43531434582236,5.61022505662070,0.224967447262691,-3.15231567034467,4.86682532411042,-4.01567881259723,-0.873782168028980,-5.38020529163479,4.78271075076051,-0.729977048082165,-2.17194023914146,-0.603723538777424,-1.76247179518188,0.379500021351323,0.250057030978731,10.5437580161177,7.33523326481621,0.443026295159096,0.628499446146050,-0.896799148025395,0.934395342842720,6.78488256099084,-2.96829648007854,1.46213009225261,-0.850814029617066,-1.44568746135580,6.40108470884209,6.55321108484059,4.56754950306138,-2.23068222119317,5.38149415616253,1.42648366199945,0.696837477982752,-0.975112032895530,-5.89861157986315,-1.58195166957996,-1.55353842785353,8.63445421401057,-12.3402855328585,-5.51722170556629,4.30919981688111,-8.74579941694927,9.67021202324538,1.70432390366129,5.79121013435273,1.16530687506628,10.6659001482549,-1.12829238647158,-0.344160011234123,2.35161782202347,5.26955355729738,7.81192344680305,6.38292147905661,-3.87777511625667,3.76717498668874,0.778974516059953,0.0703130209261342,5.82452924841787,1.07603706187380,3.28143875628925,5.33778790575850,2.85399966489577,-6.09820962386564,5.12321117430572,-1.59208186829361,-0.225623490253517,3.72328876867907,-4.44702240688788,-3.76199886658122,3.15888021870221,2.30207745843593,-4.23930734079429,6.60000123926857,2.66706875470665,5.32318016822180,2.54905929118813,3.27094294949230,1.33768186598140,-3.14014707645143,5.08488967762775,10.9145821025337,0.661581508171306,5.00334044665389,-5.04208151460842,0.865510453267145,4.42228796752399,0.829541144704558,0.824447933514115,-3.55447570321567,-5.90342085569324,4.45719151135090,-2.08733524644374,-8.49300385988535,-0.593731364256682,1.98470557439991,9.46578506388525,2.48984698584309,-4.39970997587592,-1.42246790465717,-10.3701996938858,0.655812254041061,6.16492570529570,7.14534661146800,-2.80570466882868,-1.24259066775821,6.50398210458207,5.13801651797644,2.66126307688656,5.95733073349218,3.12549577602600,2.42187593743890,8.12833527930142,-6.85061357353420,-9.42083100815139,4.34972416352229,2.24830850601482,-0.253885546160459,2.37828586877606,-6.52091062105098,4.48258292388305,-0.771831866285420,7.21768099710349,3.61894189051801,2.99286495651488,-3.54825814541023,-1.30963642507944,-7.22054831406348,-4.69333157491396,4.17503339040803,-4.67028438268390,5.20724744696141,7.86454410778232,5.62242544700396,-6.33230475582619,9.17512208822733,-2.38816356013604,-6.69651911883608,-3.15000490407582,2.48551078179961,3.51334310017455,4.30682042637398,-0.181198756521308,2.83809062231087,-0.0181293057999599,3.11517212564428,0.352078946751701,-1.60575781297549,0.507117784643479,2.94335024000936,9.71913072979386,2.74193351019856,-5.06690169092385,1.66684616651982,2.91127712801132,4.47333060286303,-2.36044945764708,-3.07909184827793,4.87877697269760,-4.46475006865800,0.232661929976468,2.38783687032430,5.65308101209784,2.82137298995595,-5.26371027935456,-4.90321366369642,3.83849996225386,-2.11812409496359,2.86376685673791,4.97435449731745,4.43467606349388,7.65902402167101,-5.42361850216190,9.31196278095671,-3.66720381653721,0.894758997459332,1.83251705567340,8.87445615077520,3.29939015966698,0.594920438527714,-6.95984814508380,-1.41460553461294,7.33181002367995,2.02423197001877,-6.66235943292937,3.64991576524498,4.19209353857050,3.49000371132840,-9.80497851290693,0.923643522502758,2.93118566168076,-4.24683629058804,-2.67825611671850,-3.05979135909611,-8.77702935546610,0.447826317061497,7.24601655766563,-1.19829746812750,-0.944881829376201,4.66105877495162,9.19010767946038,6.99061679379664,-6.10365233678619,-9.21074294400597,4.86736408488647,1.35258844344067,-4.21663325402031,6.31932332591761,3.05524430351311,-6.09658795127277,6.60597982290077,5.35754209904388,-0.617500371620895,10.6101318893993,-6.61910617782614,0.0110887915245631,1.59719561317632,2.21571334292340,-7.91553585033412,-9.16275232098563,-5.09738943448571,1.55031998211949,1.51215811498636,5.20780187945222,9.25247404384284,-5.22094284388054,0.766518216348770,6.89758659645465,-0.505720897462570,-2.98175309292614,-3.40320371244853,4.27586348190214,6.99855738110960,-7.23116698983684,2.08812256069761,2.84161667176779,4.20881538881222,-2.37483654741867,13.9614971133052,1.42066818987457,2.05040227570353,-5.08128338294286,1.08113305313764,6.47787028375142,2.69306789359374,-4.38061324196431,1.22422238716336,7.86459113818963,-9.17464193369374,-0.157998173354648,1.80604273204779,-2.12044794551996,5.40595352475210,0.423475231812566,8.71293124884174,1.22221051141450,7.03198862111346,-3.61675368902456,1.41223355126637,3.17042083170432,-4.99255783023385,-4.95140400904251,-6.91228682079639,21.1645515450835,0.829486134046995,-1.20151005063795,4.42014119619958,0.840072892157521,2.11829932702810,-5.02043891635651,-0.155399984278200,-3.60857259896142,1.78822594810217,-1.18493192906361,-2.63837213548273,-1.09029436968558,5.97261220157310,4.08136548356717,-1.46893966867006,3.12687979781864,-0.948383793888972,-0.142911827882221,-1.86041568981378,-0.232669574947332,-6.38412130132518,-3.15791051784639,-3.78195644573886,-5.22334200393784,5.05383137847619,0.954801564185527,-8.54342523892137,-3.01375332110441,-3.14110117649701,6.86322117712145,3.65570992911194,7.41334213282212,-4.28479430638137,0.427181176930605,-4.75092582864141,6.47612740157428,-1.07844614207232,4.30585507374058,4.43536756916936,-1.38484176042462,4.86301414002391,0.344565056670546,-0.104178790551851,-4.92145541943630,-7.40656124989472,5.45318038647618,-2.59347088666809,-12.2356105897654,-0.784783351445550,-2.41851764125001,-1.39623625892600,-0.654387408461129,0.110262129208840,-8.50556353763247,12.1760874383190,-7.73214480623816,1.37245469957565,1.53608966699421,-7.49021974378775,-4.58892687740286,-0.749527008614340,0.186130199184422,10.9984076657322,4.65335145424746,10.7569750345891,-6.04763675007119,0.106331552480367,-4.68562934087857,0.392572630270432,-2.73075658424148,0.187188304686837,-1.18607736311576,1.66347317045770,3.75967149588679,6.00226000582196,-0.752950443615949,6.63772353993054,-4.44661745581056,-0.603960022836337,3.14224809419236,8.20087850142755,-1.73972543440345,-3.11540969792144,6.50247048488843,4.03085919283022,2.72696499857233,4.65195987809385,8.86543696934307,-0.346446120598011,0.489571617199890,-1.60393502937096,0.955733152216114,-2.30793619993172,-2.86464721154484,-2.23828099761088,-3.21978440982702,10.0754011567072,4.30561125715357,-1.14379288651971,-3.48057982517669,-0.196670072916254,6.25068139658974,-4.79923541119682,-2.27560408113419,6.79466085786607,3.52481519775023,-8.15862670810459,-5.78704743733473,-0.326081548975567,-1.82027989102926,-5.82625163463799,0.942824181230358,0.866604331966646,2.09362188113883,4.99033941710665,-4.54549430864071,-3.76960090246520,5.86398789700878,1.14765048352229,-2.46918532691009,-4.44405921772957,4.18884834619406,-0.165496939931657,1.38402828293626,-3.52173404958265,9.46794751261090,6.08425667480225,1.64230103381105,2.65725440779167,4.38239350366259,6.96947860048063,-6.39958964082046,-6.55181557729448,-2.24682544878836,1.38991844656368,1.60823838431355,-3.07174500918336,-6.46623965475138,4.72307933094018,-0.937934226480919,1.27400470960735,2.83892650881148,8.05020557877595,-8.82985285382780,0.543071489120134,0.698623111385018,-0.640264638515364,0.881454600070123,7.15767327986840,-6.53251496191390,-8.75906181895835,2.95519715046581,-9.33135177210403,-0.421136369101183,-3.02179392342915,11.4400654937851,2.47403945980301,0.729594274513469,3.25892255244611,-4.81397123799874,-1.40304544046756,-3.03952785567130,3.94037263127342,-3.04628065348384,-0.487445857856294,-6.47014839202277,7.22061303096064,6.25085590009096,-7.07522625580136,-0.844393368497501,-1.50667543665378,2.10452053820230,2.82693500444263,-4.96278518871583,0.137237941923292,-1.98217920576248,5.78987499647710,-0.364294654355787,-0.353370952899440,-9.14803584780482,4.78432909500793,0.941707426429414,-1.94174679146287,3.22064682289296,5.68549417628417,9.06527931681103,6.29044230648945,-1.79409844397101,5.56231974317628,0.144539570174889,-7.75881332403430,-1.45864104784057,-5.84810175800871,11.2362997699358,14.5830372679809,4.37255981290586,-5.74800569772009,3.17349642949331,-4.66353828863095,5.69884148446714,3.97752667766667,-3.76549140543478,-4.67834109450307,-2.82692693907927,1.53912151019851,7.26955557386942,11.4944200412035,-0.824619241953505,-3.68813232173737,-1.91947014428269,2.92457541304859,0.551283328951362,-10.5108691773889,1.62459048607397,1.66375015829997,7.68422337149850,0.640513159705132,15.4341907748432,3.95989061481285,1.41917501153169,1.45414074329720,2.77248916546828,4.85902030647216,-3.35653984905517,0.432687159546608,1.39266393050589,14.7343116342150,-7.32484737457386,1.78372934366120,1.94685236167838,-6.33045914954616,1.21364083772689,-5.60691187579682,-1.52341334433832,5.71088434393449,-1.60108868882532,1.61989037216714,7.71426575311062,0.678068283932059,4.13433203226667,3.23397524615055,0.664769541045202,3.71878023122784,3.20976021258229,-0.684658818874277,0.424809920253365,-5.94396914143253,3.20453338027342,-11.5053228936908,3.06338562794649,-2.95367187891539,1.06072573629781,0.516030085335123,6.54395084314673,1.83273108091619,3.33970866525773,0.427781585352950,-1.38955847537381,1.95418484030877,9.69677816632740,9.71630821786320,1.86658454616778,1.33626459407945,2.00468807744370,-8.00471818357351,-5.31845960543191,2.10895250209211,1.54487885299222,4.19175595387769,-5.52337129394266,-7.84322429259330,3.55401160001513,-1.69213876223651,-0.0733439418849597,-6.59989638255240,-0.306063365810483,-3.52472523757195,10.8435346075484,4.21716314615900,0.623815828606714,-6.44782425333752,4.85014489598506,5.85185817619708,10.7415334814444,9.02701968922803,-7.45082047370225,-2.86854098587538,6.56148594845650,0.278155120144826,8.66679724306093,-2.87231669310446,-1.00600856609705,2.95439277616161,2.30112059259933,2.11153253734923,-2.80061722978199,-6.99996017274342,-1.69772176563245,8.10936871989553,2.75470266307292,2.62627087342995,-4.27252966772508,1.19426813055990,-2.72225634270171,-5.61415441322518,5.10711505090554,7.51470890272577,-5.80140049299760,2.27971638657577,-8.18040185270562,4.60830830127086,1.32653000076697,1.64849679081782,2.85548646445588,3.35029950310191,5.34610426879280,2.90180983252067,-10.1816642978045,-2.04420028768066,-2.59664882654486,1.35794231048884,7.97858980189901,1.71013532858463,3.70652865872418,-7.86985032069197,5.09129124484005,-4.72674365018913,4.48518949937298,5.95062974389335,0.648083271921177,11.7009728852424,1.35503706286296,-2.88172072263693,-1.91905115206039,-6.83567135798042,-1.25396052939937,6.73327869245207,-4.50431188720674,3.57082282385771,-6.46200051536869,-1.22028756045439,-1.51678609499573,2.70879530515641,1.59823635273195,1.21738722828193,-9.53124007310164,8.67060226701985,-6.02558934998295,4.19073447802412,10.2932376204781,-3.71295725349075,4.41321114351267,5.50472976295395,6.35241246486030,4.00855735696866,5.39730393913065,7.76457472145568,-0.379934583187310,-8.33083376132641,-1.50932707593569,1.39635326363802,7.94864164944964,1.52977119167950,10.3359109898236,-6.87679895205504,3.92586492576855,6.95811122299201,10.8367257933394,-6.56133500642218,-2.16825130851229,-4.28656917553870,8.35138355920101,-1.78260998400091,7.30161716252388,-4.98492182569983,3.71272715520582,-4.78244093372199,2.85654672562886,-2.06554403324862,-9.70377137672343,0.0735745928640066,-2.45394820530259,1.89893495003022,-2.80008253185270,3.34952868165566,-1.73376106316291,-6.03299902346308,7.82728533034367,-13.8429637950419,1.46187243520652,-8.33741108068210,-3.23637695272496,3.61816607030662,3.15963833141036,3.02833437875317,1.36917532663989,8.78925131660438,2.52539211094721,1.12628234552113,-0.282978500367258,1.68490866126717,0.824926248653402,1.67190666898627,7.89766351606675,5.16946437420129,-16.7810753742561,2.85944948101034,-5.31328233575751,2.46653207713667,3.19292984653047,6.00284478564091,1.79165908339327,-5.09594142716340,4.04099005457992,6.28664911155426,7.70831252313206,0.0513287213391592,1.05911946048251,3.10811246036954,5.72783923539077,6.36945417124024,7.12179319120286,-5.03508699250947,6.13584179977412,2.70797060361748,4.18738486823883,-11.5406068758087,3.82001846908337,2.24857891965163,-0.0811430618125326,-1.57056579818509,0.214091848314496,2.53085130823078,-3.29923488332421,-5.68306940190280,7.81804112022627,-2.82999571638126,-2.33257229346263,-4.93131507636266,1.03584307005498,-0.365347128213152,8.78010213976706,-1.03589260513752,-2.68894165805910,-8.45496735055799,0.283056201589255,4.23146054910738,4.28871634239212,0.611722776284721,-1.13159982811132,2.35822089406828,2.25789400402345,-3.70681877866625,-2.06028755208751,2.61926207414003,-2.14852552582905,-1.13063772505067,-0.592252059982873,1.76101339223434,3.68784713670645,1.84197987948484,8.13729926252090,6.63355401977785,8.27239273830919,-2.03159270046531,8.82485526221809,7.26529859014467,-4.03813289943850,-3.65699269552635,0.831942242560388,-5.31645665931098,5.59913439127307,-2.44355525850482,-7.52064959703091,-0.524988800312205,1.30449845232952,-7.80805852377796,1.62295151575897,3.01165945121642,-4.56532254748195,0.398478513364306,0.981061464261973,2.48667374655674,9.20891326484200,4.42405207540516,0.700958613858455,-4.42832962633434,-2.37644365500747,2.93013158564549,4.48071487377632,7.18590601608006,-0.945507670497849,1.93872470258590,5.75776935011454,6.27942672675524,4.93054421310186,6.07373218083889,-0.361201146335185,4.36246591883054,2.24406223549412,-2.98770580511706,-0.435701746662063,5.79676486377347,-6.78811682073627,-1.51965302427842,1.82513033758485,-3.58043507050087,-0.849371458888873,1.02739787568734,-2.74575423226436,5.03108198448302,2.72538291252305,-7.52761887604715,7.03028821409035,8.88609594724134,6.17083658978912,2.55041859103137,17.4696702856204,-1.51507351608471,4.14557500687493,3.51023732714305,5.83212209056215,5.08247254271830,3.87464726302389,-2.62708892640523,2.49882718954687,-2.01580083950028,5.82376594636942,-5.29170567684169,-1.31335902198100,-2.35766261191596,-0.994705835239736,-0.193593716239256,0.372554993658308,0.117310425233386,8.48928612443734,2.83349694544098,7.03679999092876,-1.58713773769063,2.32380181095208,0.238450012732315,5.55458129090712,4.69694604834804,4.13599806882244,-2.25847345666927,-7.75737500093263,-2.33590129169083,5.89434949339857,10.9710363166629,-4.01719004924447,4.32401584202611,10.9350936139585,-10.4314651301479,3.01521410137734,1.78040564606214,-6.33216437293564,4.91472280638023,2.80268137040425,0.153122217447969,-0.398120736703710,-3.24032060939536,-1.74287539247788,5.61699731102833,0.849242954635814;
    t_complex I(0, 1);
    Vector<t_complex> data = (real_data + I * imag_data);
    t_complex mu = utilities::mean(data);
    std::cout << mu << '\n';
    CHECK(std::abs(mu -(0.770634429899614 + 0.967954403523829 * I)) < 1e-13);
    t_real var = utilities::variance(data);
    std::cout << var << '\n';
    CHECK(std::abs(var - 50.1405284663126) < 1e-13);
}

TEST_CASE("utilities [read_write_vis]", "[read_write_vis]"){
    //tests the read and write function for a visibility data set
    std::string vis_file = vla_filename("at166B.3C129.c0.vis");
    std::string out_file = output_filename("test_output.vis");
    std::string out_w_file = output_filename("test_w_output.vis");
    auto uv_data = utilities::read_visibility(vis_file);
    utilities::write_visibility(uv_data, out_file);
    auto new_uv_data = utilities::read_visibility(out_file);
    CHECK(new_uv_data.u.isApprox(uv_data.u, 1e-13));
    CHECK(new_uv_data.v.isApprox(uv_data.v, 1e-13));
    CHECK(new_uv_data.vis.isApprox(uv_data.vis, 1e-13));
    CHECK(new_uv_data.weights.isApprox(uv_data.weights, 1e-13));
    t_int number_of_random_vis = 1e5;
    const bool w_term = true;
    auto random_uv_data = utilities::random_sample_density(number_of_random_vis, 0, purify_pi /3);
    utilities::write_visibility(random_uv_data, out_w_file, w_term);
    auto new_random_uv_data = utilities::read_visibility(out_w_file, w_term);
    CHECK(new_random_uv_data.u.isApprox(random_uv_data.u, 1e-8));
    CHECK(new_random_uv_data.v.isApprox(random_uv_data.v, 1e-8));
    CHECK(new_random_uv_data.w.isApprox(random_uv_data.w, 1e-8));
    CHECK(new_random_uv_data.vis.isApprox(random_uv_data.vis, 1e-8));
    CHECK(new_random_uv_data.weights.isApprox(random_uv_data.weights, 1e-8));
}
TEST_CASE("utilities [file exists]", "[file exists]"){
    std::string vis_file = vla_filename("at166B.3C129.c0.vis");
    //File should exist
    CHECK(utilities::file_exists(vis_file));
    //File should not exist
    CHECK(not utilities::file_exists("adfadsf"));

}