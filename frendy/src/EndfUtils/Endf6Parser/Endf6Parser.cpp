#include "EndfUtils/Endf6Parser/Endf6Parser.hpp"

using namespace frendy;

//constructor
Endf6Parser::Endf6Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
Endf6Parser::~Endf6Parser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::mod_list()
{
  parser_list.clear();
  clr_obj.clear_vec_array2_int(mt_list);

  parser_list = get_endf6_parser_no_cov().get_parser_list();
  mt_list     = get_endf6_parser_no_cov().get_mt_list();

  vector<Integer>          parser_list_cov = get_endf6_parser_cov().get_parser_list();
  vector<vector<Integer> > mt_list_cov     = get_endf6_parser_cov().get_mt_list();
  for(int i=0; i<static_cast<int>(parser_list_cov.size()); i++)
  {
    parser_list.push_back(parser_list_cov[i]);
    mt_list.push_back(mt_list_cov[i]);
  }
  parser_list_cov.clear();
  clr_obj.clear_vec_array2_int(mt_list_cov);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::read_endf()
{
  read_endf_no_cov();
  read_endf_cov();

  clr_obj.clear_vec_array2_real(time_each);
  time_each = time_each_no_cov;
  for(int i=0; i<static_cast<int>(time_each_cov.size()); i++)
  {
    time_each.push_back(time_each_cov[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::read_endf_no_cov()
{
  boost::timer::cpu_timer time;

  set_parser_list_no_cov();

  //Read ENDF data without covariance. 
  //cp_no_cov.set_file_name(name);
  cp_no_cov.set_endf_file_reader(efr_obj);
  time_total.push_back(cp_no_cov.get_time_total());

  //Calc total reading time.
  time_total.push_back(static_cast<Real>(time.elapsed().wall * 1.0E-9));

  //Get reading time at each MF and MT.
  time_each_no_cov = cp_no_cov.get_time_each();
  time_each        = time_each_no_cov;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::read_endf_cov()
{
  boost::timer::cpu_timer time;

  set_parser_list_cov();

  //Read ENDF covariance data.
  //cp_cov.set_file_name(name);
  cp_cov.set_endf_file_reader(efr_obj);
  time_total.push_back(cp_cov.get_time_total());

  //Calc total reading time.
  time_total.push_back(static_cast<Real>(time.elapsed().wall * 1.0E-9));

  //Get reading time at each MF and MT.
  time_each_cov = cp_cov.get_time_each();
  time_each     = time_each_cov;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::read_endf_xs_only()
{
  boost::timer::cpu_timer time;

  //Read MF03 data
  vector<Integer> mt_no_list =  efr_obj.get_mt_list(3);
  int mt_no = static_cast<int>(mt_no_list.size());

  vector<MF03Parser> mf03_obj;
  mf03_obj.resize(mt_no);
  for(int i=0; i<mt_no; i++)
  {
    mf03_obj[i].set_text(efr_obj.get_data(3,mt_no_list[i]));
  }
  efr_obj.clear();

  cp_no_cov.clear();
  cp_no_cov.set_mf03_data(mf03_obj);
  mf03_obj.clear();

  //Calc total reading time.
  time_total.clear();
  time_total.push_back(static_cast<Real>(time.elapsed().wall * 1.0E-9));
  time_total.push_back(0.0);
  time_total.push_back(time_total[0]);

  //Get reading time at each MF and MT.
  time_each_cov.clear();
  time_each.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::clear()
{
  name.clear();
  time_total.clear();

  clr_obj.clear_vec_array2_real(time_each);
  clr_obj.clear_vec_array2_real(time_each_no_cov);
  clr_obj.clear_vec_array2_real(time_each_cov);

  parser_list_no_cov.clear();
  parser_list_cov.clear();
  mt_list.clear();

  cp_no_cov.clear();
  cp_cov.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::set_file_name(string file_name)
{
  clear();
  name = file_name;
  file_name.clear();

  efr_obj.set_file_name(name);

  read_endf();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::set_endf_file_reader(EndfFileReader& obj)
{
  clear();

  efr_obj = obj;
  name = efr_obj.get_file_name();

  read_endf();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::set_text(vector<string>& text_data)
{
  clear();

  efr_obj.set_endf_data(text_data);

  read_endf();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::set_file_name_no_cov(string file_name)
{
  clear();
  name = file_name;
  file_name.clear();

  efr_obj.set_file_name(name);

  read_endf_no_cov();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::set_endf_file_reader_no_cov(EndfFileReader& obj)
{
  clear();

  efr_obj = obj;
  name = efr_obj.get_file_name();

  read_endf_no_cov();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::set_text_no_cov(vector<string>& text_data)
{
  clear();

  efr_obj.set_endf_data(text_data);

  read_endf_no_cov();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::set_file_name_cov(string file_name)
{
  clear();
  name = file_name;
  file_name.clear();

  efr_obj.set_file_name(name);

  read_endf_cov();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::set_endf_file_reader_cov(EndfFileReader& obj)
{
  clear();

  efr_obj = obj;
  name = efr_obj.get_file_name();

  read_endf_cov();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::set_file_name_xs_only(string file_name)
{
  clear();
  name = file_name;
  file_name.clear();

  efr_obj.set_file_name(name);

  read_endf_xs_only();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::set_endf_file_reader_xs_only(EndfFileReader& obj)
{
  clear();

  efr_obj = obj;
  name = efr_obj.get_file_name();

  read_endf_xs_only();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::set_text_xs_only(vector<string>& text_data)
{
  clear();

  efr_obj.set_endf_data(text_data);

  read_endf_xs_only();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::set_parser_list_no_cov()
{
  parser_list_no_cov.clear();
  parser_list_no_cov.push_back( 1);
  parser_list_no_cov.push_back( 2);
  parser_list_no_cov.push_back( 3);
  parser_list_no_cov.push_back( 4);
  parser_list_no_cov.push_back( 5);
  parser_list_no_cov.push_back( 6);
  parser_list_no_cov.push_back( 7);
  parser_list_no_cov.push_back( 8);
  parser_list_no_cov.push_back( 9);
  parser_list_no_cov.push_back(10);
  parser_list_no_cov.push_back(12);
  parser_list_no_cov.push_back(13);
  parser_list_no_cov.push_back(14);
  parser_list_no_cov.push_back(15);
  parser_list_no_cov.push_back(23);
  parser_list_no_cov.push_back(26);
  parser_list_no_cov.push_back(27);
  parser_list_no_cov.push_back(28);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Parser::set_parser_list_cov()
{
  parser_list_cov.clear();
  parser_list_cov.push_back(28);
  parser_list_cov.push_back(30);
  parser_list_cov.push_back(31);
  parser_list_cov.push_back(32);
  parser_list_cov.push_back(33);
  parser_list_cov.push_back(34);
  parser_list_cov.push_back(35);
  parser_list_cov.push_back(40);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

string                   Endf6Parser::get_file_name()
{
  return name;
}

vector<Integer>          Endf6Parser::get_parser_list()
{
  mod_list();
  return parser_list;
}

vector<vector<Integer> > Endf6Parser::get_mt_list()
{
  mod_list();
  return mt_list;
}

vector<Real>             Endf6Parser::get_time_total()
{
  return time_total;
}

vector<vector<Real> >    Endf6Parser::get_time_each()
{
  return time_each;
}


Endf6ParserCov     Endf6Parser::get_endf6_parser_cov()
{
  return cp_cov;
}

Endf6ParserNoCov   Endf6Parser::get_endf6_parser_no_cov()
{
  return cp_no_cov;
}


MF01MT451Parser    Endf6Parser::get_mf01_mt451_data()
{
  return cp_no_cov.get_mf01_mt451_data();
}

MF01MT452Parser    Endf6Parser::get_mf01_mt452_data()
{
  return cp_no_cov.get_mf01_mt452_data();
}

MF01MT455Parser    Endf6Parser::get_mf01_mt455_data()
{
  return cp_no_cov.get_mf01_mt455_data();
}

MF01MT456Parser    Endf6Parser::get_mf01_mt456_data()
{
  return cp_no_cov.get_mf01_mt456_data();
}

MF01MT458Parser    Endf6Parser::get_mf01_mt458_data()
{
  return cp_no_cov.get_mf01_mt458_data();
}

MF01MT460Parser    Endf6Parser::get_mf01_mt460_data()
{
  return cp_no_cov.get_mf01_mt460_data();
}

MF02MT151Parser    Endf6Parser::get_mf02_mt151_data()
{
  return cp_no_cov.get_mf02_mt151_data();
}

MF02MT152Parser    Endf6Parser::get_mf02_mt152_data()
{
  return cp_no_cov.get_mf02_mt152_data();
}

MF02MT153Parser    Endf6Parser::get_mf02_mt153_data()
{
  return cp_no_cov.get_mf02_mt153_data();
}

MF07MT002Parser    Endf6Parser::get_mf07_mt002_data()
{
  return cp_no_cov.get_mf07_mt002_data();
}

MF07MT004Parser    Endf6Parser::get_mf07_mt004_data()
{
  return cp_no_cov.get_mf07_mt004_data();
}

MF07MT451Parser    Endf6Parser::get_mf07_mt451_data()
{
  return cp_no_cov.get_mf07_mt451_data();
}

MF08MT454Parser    Endf6Parser::get_mf08_mt454_data()
{
  return cp_no_cov.get_mf08_mt454_data();
}

MF08MT457Parser    Endf6Parser::get_mf08_mt457_data()
{
  return cp_no_cov.get_mf08_mt457_data();
}

MF08MT459Parser    Endf6Parser::get_mf08_mt459_data()
{
  return cp_no_cov.get_mf08_mt459_data();
}

MF30MT001Parser    Endf6Parser::get_mf30_mt001_data()
{
  return cp_cov.get_mf30_mt001_data();
}

MF30MT002Parser    Endf6Parser::get_mf30_mt002_data()
{
  return cp_cov.get_mf30_mt002_data();
}

MF32MT151Parser    Endf6Parser::get_mf32_mt151_data()
{
  return cp_cov.get_mf32_mt151_data();
}


vector<MF03Parser> Endf6Parser::get_mf03_data()
{
  return cp_no_cov.get_mf03_data();
}

vector<MF04Parser> Endf6Parser::get_mf04_data()
{
  return cp_no_cov.get_mf04_data();
}

vector<MF05Parser> Endf6Parser::get_mf05_data()
{
  return cp_no_cov.get_mf05_data();
}

vector<MF06Parser> Endf6Parser::get_mf06_data()
{
  return cp_no_cov.get_mf06_data();
}

vector<MF08Parser> Endf6Parser::get_mf08_data()
{
  return cp_no_cov.get_mf08_data();
}

vector<MF09Parser> Endf6Parser::get_mf09_data()
{
  return cp_no_cov.get_mf09_data();
}

vector<MF10Parser> Endf6Parser::get_mf10_data()
{
  return cp_no_cov.get_mf10_data();
}

vector<MF12Parser> Endf6Parser::get_mf12_data()
{
  return cp_no_cov.get_mf12_data();
}

vector<MF13Parser> Endf6Parser::get_mf13_data()
{
  return cp_no_cov.get_mf13_data();
}

vector<MF14Parser> Endf6Parser::get_mf14_data()
{
  return cp_no_cov.get_mf14_data();
}

vector<MF15Parser> Endf6Parser::get_mf15_data()
{
  return cp_no_cov.get_mf15_data();
}

vector<MF23Parser> Endf6Parser::get_mf23_data()
{
  return cp_no_cov.get_mf23_data();
}

vector<MF26Parser> Endf6Parser::get_mf26_data()
{
  return cp_no_cov.get_mf26_data();
}

vector<MF27Parser> Endf6Parser::get_mf27_data()
{
  return cp_no_cov.get_mf27_data();
}

vector<MF28Parser> Endf6Parser::get_mf28_data()
{
  return cp_no_cov.get_mf28_data();
}

vector<MF31Parser> Endf6Parser::get_mf31_data()
{
  return cp_cov.get_mf31_data();
}

vector<MF33Parser> Endf6Parser::get_mf33_data()
{
  return cp_cov.get_mf33_data();
}

vector<MF34Parser> Endf6Parser::get_mf34_data()
{
  return cp_cov.get_mf34_data();
}

vector<MF35Parser> Endf6Parser::get_mf35_data()
{
  return cp_cov.get_mf35_data();
}

vector<MF40Parser> Endf6Parser::get_mf40_data()
{
  return cp_cov.get_mf40_data();
}


//Setter
void Endf6Parser::set_endf6_parser_cov(Endf6ParserCov parser_obj)
{
  cp_cov.clear();
  cp_cov = parser_obj;
}

void Endf6Parser::set_endf6_parser_no_cov(Endf6ParserNoCov parser_obj)
{
  cp_no_cov.clear();
  cp_no_cov = parser_obj;
}


void Endf6Parser::set_mf01_mt451_data(MF01MT451Parser parser_obj)
{
  cp_no_cov.set_mf01_mt451_data(parser_obj);
}

void Endf6Parser::set_mf01_mt452_data(MF01MT452Parser parser_obj)
{
  cp_no_cov.set_mf01_mt452_data(parser_obj);
}

void Endf6Parser::set_mf01_mt455_data(MF01MT455Parser parser_obj)
{
  cp_no_cov.set_mf01_mt455_data(parser_obj);
}

void Endf6Parser::set_mf01_mt456_data(MF01MT456Parser parser_obj)
{
  cp_no_cov.set_mf01_mt456_data(parser_obj);
}

void Endf6Parser::set_mf01_mt458_data(MF01MT458Parser parser_obj)
{
  cp_no_cov.set_mf01_mt458_data(parser_obj);
}

void Endf6Parser::set_mf01_mt460_data(MF01MT460Parser parser_obj)
{
  cp_no_cov.set_mf01_mt460_data(parser_obj);
}

void Endf6Parser::set_mf02_mt151_data(MF02MT151Parser parser_obj)
{
  cp_no_cov.set_mf02_mt151_data(parser_obj);
}

void Endf6Parser::set_mf02_mt152_data(MF02MT152Parser parser_obj)
{
  cp_no_cov.set_mf02_mt152_data(parser_obj);
}

void Endf6Parser::set_mf02_mt153_data(MF02MT153Parser parser_obj)
{
  cp_no_cov.set_mf02_mt153_data(parser_obj);
}

void Endf6Parser::set_mf07_mt002_data(MF07MT002Parser parser_obj)
{
  cp_no_cov.set_mf07_mt002_data(parser_obj);
}

void Endf6Parser::set_mf07_mt004_data(MF07MT004Parser parser_obj)
{
  cp_no_cov.set_mf07_mt004_data(parser_obj);
}

void Endf6Parser::set_mf07_mt451_data(MF07MT451Parser parser_obj)
{
  cp_no_cov.set_mf07_mt451_data(parser_obj);
}

void Endf6Parser::set_mf08_mt454_data(MF08MT454Parser parser_obj)
{
  cp_no_cov.set_mf08_mt454_data(parser_obj);
}

void Endf6Parser::set_mf08_mt457_data(MF08MT457Parser parser_obj)
{
  cp_no_cov.set_mf08_mt457_data(parser_obj);
}

void Endf6Parser::set_mf08_mt459_data(MF08MT459Parser parser_obj)
{
  cp_no_cov.set_mf08_mt459_data(parser_obj);
}

void Endf6Parser::set_mf30_mt001_data(MF30MT001Parser parser_obj)
{
  cp_cov.set_mf30_mt001_data(parser_obj);
}

void Endf6Parser::set_mf30_mt002_data(MF30MT002Parser parser_obj)
{
  cp_cov.set_mf30_mt002_data(parser_obj);
}

void Endf6Parser::set_mf32_mt151_data(MF32MT151Parser parser_obj)
{
  cp_cov.set_mf32_mt151_data(parser_obj);
}


void Endf6Parser::set_mf03_data(vector<MF03Parser> parser_obj)
{
  cp_no_cov.set_mf03_data(parser_obj);
}

void Endf6Parser::set_mf04_data(vector<MF04Parser> parser_obj)
{
  cp_no_cov.set_mf04_data(parser_obj);
}

void Endf6Parser::set_mf05_data(vector<MF05Parser> parser_obj)
{
  cp_no_cov.set_mf05_data(parser_obj);
}

void Endf6Parser::set_mf06_data(vector<MF06Parser> parser_obj)
{
  cp_no_cov.set_mf06_data(parser_obj);
}

void Endf6Parser::set_mf08_data(vector<MF08Parser> parser_obj)
{
  cp_no_cov.set_mf08_data(parser_obj);
}

void Endf6Parser::set_mf09_data(vector<MF09Parser> parser_obj)
{
  cp_no_cov.set_mf09_data(parser_obj);
}

void Endf6Parser::set_mf10_data(vector<MF10Parser> parser_obj)
{
  cp_no_cov.set_mf10_data(parser_obj);
}

void Endf6Parser::set_mf12_data(vector<MF12Parser> parser_obj)
{
  cp_no_cov.set_mf12_data(parser_obj);
}

void Endf6Parser::set_mf13_data(vector<MF13Parser> parser_obj)
{
  cp_no_cov.set_mf13_data(parser_obj);
}

void Endf6Parser::set_mf14_data(vector<MF14Parser> parser_obj)
{
  cp_no_cov.set_mf14_data(parser_obj);
}

void Endf6Parser::set_mf15_data(vector<MF15Parser> parser_obj)
{
  cp_no_cov.set_mf15_data(parser_obj);
}

void Endf6Parser::set_mf23_data(vector<MF23Parser> parser_obj)
{
  cp_no_cov.set_mf23_data(parser_obj);
}

void Endf6Parser::set_mf26_data(vector<MF26Parser> parser_obj)
{
  cp_no_cov.set_mf26_data(parser_obj);
}

void Endf6Parser::set_mf27_data(vector<MF27Parser> parser_obj)
{
  cp_no_cov.set_mf27_data(parser_obj);
}

void Endf6Parser::set_mf28_data(vector<MF28Parser> parser_obj)
{
  cp_no_cov.set_mf28_data(parser_obj);
}

void Endf6Parser::set_mf31_data(vector<MF31Parser> parser_obj)
{
  cp_cov.set_mf31_data(parser_obj);
}

void Endf6Parser::set_mf33_data(vector<MF33Parser> parser_obj)
{
  cp_cov.set_mf33_data(parser_obj);
}

void Endf6Parser::set_mf34_data(vector<MF34Parser> parser_obj)
{
  cp_cov.set_mf34_data(parser_obj);
}

void Endf6Parser::set_mf35_data(vector<MF35Parser> parser_obj)
{
  cp_cov.set_mf35_data(parser_obj);
}

void Endf6Parser::set_mf40_data(vector<MF40Parser> parser_obj)
{
  cp_cov.set_mf40_data(parser_obj);
}

