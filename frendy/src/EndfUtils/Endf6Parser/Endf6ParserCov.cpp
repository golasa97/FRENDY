#include "EndfUtils/Endf6Parser/Endf6ParserCov.hpp"

using namespace frendy;

//constructor
Endf6ParserCov::Endf6ParserCov(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
Endf6ParserCov::~Endf6ParserCov(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::mod_list()
{
  int i_max;

  vector<Integer> mt_list_tmp;
  mt_list_tmp.clear();
  parser_list.clear();
  clr_obj.clear_vec_array2_int(mt_list);

  //For MF=30
  if( mf30_mt001_data.get_mat_no() != 0 && fabs(mf30_mt001_data.get_ZA())  > min_value
                                        && fabs(mf30_mt001_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(1);
  }

  if( mf30_mt002_data.get_mat_no() != 0 && fabs(mf30_mt002_data.get_ZA())  > min_value
                                        && fabs(mf30_mt002_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(2);
  }

  if( static_cast<int>(mt_list_tmp.size()) > 0 )
  {
    parser_list.push_back(30);
    mt_list.push_back(mt_list_tmp);
  }
  mt_list_tmp.clear();

  //For MF=31
  i_max = static_cast<int>(mf31_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf31_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf31_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(31);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=32
  if( mf32_mt151_data.get_mat_no() != 0 && fabs(mf32_mt151_data.get_ZAR()) > min_value
                                        && fabs(mf32_mt151_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(151);
  }

  if( static_cast<int>(mt_list_tmp.size()) > 0 )
  {
    parser_list.push_back(32);
    mt_list.push_back(mt_list_tmp);
  }
  mt_list_tmp.clear();

  //For MF=33
  i_max = static_cast<int>(mf33_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf33_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf33_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(33);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=34
  i_max = static_cast<int>(mf34_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf34_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf34_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(34);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=35
  i_max = static_cast<int>(mf35_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf35_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf35_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(35);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=40
  i_max = static_cast<int>(mf40_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf40_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf40_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(40);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::read_endf()
{
  boost::timer::cpu_timer  time_tot;

  set_parser_list();

  vector<Real>    time_each_mf;
  time_each_mf.clear();
  clr_obj.clear_vec_array2_real(time_each);

  for(int i=0; i<static_cast<int>(parser_list.size()); i++)
  {
    Integer mf = parser_list[i];
    vector<Integer> mt_list_tmp = efr_obj.get_mt_list(mf);
    for(int j=0; j<static_cast<int>(mt_list_tmp.size()); j++)
    {
      //cout << "MF : " << mf << ", MT : " << mt_list_tmp[j] << endl;
      parse_data(mf, mt_list_tmp[j], time_each_mf);
    } 
    time_each.push_back(time_each_mf);
    time_each_mf.clear();
    mt_list_tmp.clear();
  }
  efr_obj.clear();
  //cout << "Reading covariance data was finished." << endl;

  time_total = static_cast<Real>(time_tot.elapsed().wall * 1.0E-9);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::parse_data(Integer mf_no, Integer mt_no, vector<Real>& time_each_mf)
{
  boost::timer::cpu_timer  time;

  if( mf_no==30 )
  {
    parse_mf30(mf_no, mt_no);
  }
  else if( mf_no==31 )
  {
    parse_mf31(mf_no, mt_no);
  }
  else if( mf_no==32 )
  {
    parse_mf32(mf_no, mt_no);
  }
  else if( mf_no==33 )
  {
    parse_mf33(mf_no, mt_no);
  }
  else if( mf_no==34 )
  {
    parse_mf34(mf_no, mt_no);
  }
  else if( mf_no==35 )
  {
    parse_mf35(mf_no, mt_no);
  }
  else if( mf_no==40 )
  {
    parse_mf40(mf_no, mt_no);
  }

  time_each_mf.push_back(static_cast<Real>(time.elapsed().wall * 1.0E-9));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::parse_mf30(Integer mf_no, Integer mt_no)
{
  if( mt_no==1 )
  {
    mf30_mt001_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else if( mt_no==2 )
  {
    mf30_mt002_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else
  {
    string class_name = "Endf6ParserCov";
    string func_name  = "parse_mf30(Integer mf_no, Integer mt_no)";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "File number (MF)    : " + oss01.str();
    string str_data02 = "Section number (MT) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This MT number at MF=30 is not applicable in this program.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::parse_mf31(Integer mf_no, Integer mt_no)
{
  MF31Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf31_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::parse_mf32(Integer mf_no, Integer mt_no)
{
  if( mt_no==151 )
  {
    mf32_mt151_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else
  {
    string class_name = "Endf6ParserCov";
    string func_name  = "parse_mf32(Integer mf_no, Integer mt_no)";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "File number (MF)    : " + oss01.str();
    string str_data02 = "Section number (MT) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This MT number at MF=32 is not applicable in this program.");
    err_com.push_back("Supported MT number is MT=151.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::parse_mf33(Integer mf_no, Integer mt_no)
{
  MF33Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf33_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::parse_mf34(Integer mf_no, Integer mt_no)
{
  MF34Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf34_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::parse_mf35(Integer mf_no, Integer mt_no)
{
  MF35Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf35_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::parse_mf40(Integer mf_no, Integer mt_no)
{
  MF40Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf40_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::clear()
{
  name.clear();
  time_total = 0.0;

  clr_obj.clear_vec_array2_real(time_each);

  parser_list.clear();
  mt_list.clear();

  mf30_mt001_data.clear();
  mf30_mt002_data.clear();
  mf32_mt151_data.clear();

  vector<MF31Parser>().swap(mf31_data);
  //for(int i=0; i<static_cast<int>(mf31_data.size()); i++)
  //{
  //  mf31_data[i].clear();
  //}
  //mf31_data.clear();

  vector<MF33Parser>().swap(mf33_data);
  //for(int i=0; i<static_cast<int>(mf33_data.size()); i++)
  //{
  //  mf33_data[i].clear();
  //}
  //mf33_data.clear();

  vector<MF34Parser>().swap(mf34_data);
  //for(int i=0; i<static_cast<int>(mf34_data.size()); i++)
  //{
  //  mf34_data[i].clear();
  //}
  //mf34_data.clear();

  vector<MF35Parser>().swap(mf35_data);
  //for(int i=0; i<static_cast<int>(mf35_data.size()); i++)
  //{
  //  mf35_data[i].clear();
  //}
  //mf35_data.clear();

  vector<MF40Parser>().swap(mf40_data);
  //for(int i=0; i<static_cast<int>(mf40_data.size()); i++)
  //{
  //  mf40_data[i].clear();
  //}
  //mf40_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::set_file_name(string file_name)
{
  clear();
  name = file_name;
  file_name.clear();

  efr_obj.set_file_name(name);

  read_endf();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::set_endf_file_reader(EndfFileReader& obj)
{
  clear();

  efr_obj = obj;
  name = efr_obj.get_file_name();

  read_endf();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::set_text(vector<string>& text_data)
{
  clear();

  efr_obj.set_endf_data(text_data);

  read_endf();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserCov::set_parser_list()
{
  parser_list.clear();

  parser_list.clear();
  parser_list.push_back(30);
  parser_list.push_back(31);
  parser_list.push_back(32);
  parser_list.push_back(33);
  parser_list.push_back(34);
  parser_list.push_back(35);
  parser_list.push_back(40);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

string                   Endf6ParserCov::get_file_name()
{
  return name;
}

vector<Integer>          Endf6ParserCov::get_parser_list()
{
  mod_list();
  return parser_list;
}

vector<vector<Integer> > Endf6ParserCov::get_mt_list()
{
  mod_list();
  return mt_list;
}

Real                     Endf6ParserCov::get_time_total()
{
  return time_total;
}

vector<vector<Real> >    Endf6ParserCov::get_time_each()
{
  return time_each;
}


MF30MT001Parser    Endf6ParserCov::get_mf30_mt001_data()
{
  return mf30_mt001_data;
}

MF30MT002Parser    Endf6ParserCov::get_mf30_mt002_data()
{
  return mf30_mt002_data;
}

MF32MT151Parser    Endf6ParserCov::get_mf32_mt151_data()
{
  return mf32_mt151_data;
}


vector<MF31Parser> Endf6ParserCov::get_mf31_data()
{
  return mf31_data;
}

vector<MF33Parser> Endf6ParserCov::get_mf33_data()
{
  return mf33_data;
}

vector<MF34Parser> Endf6ParserCov::get_mf34_data()
{
  return mf34_data;
}

vector<MF35Parser> Endf6ParserCov::get_mf35_data()
{
  return mf35_data;
}

vector<MF40Parser> Endf6ParserCov::get_mf40_data()
{
  return mf40_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void Endf6ParserCov::set_mf30_mt001_data(MF30MT001Parser parser_obj)
{
  mf30_mt001_data.clear();
  mf30_mt001_data = parser_obj;
}

void Endf6ParserCov::set_mf30_mt002_data(MF30MT002Parser parser_obj)
{
  mf30_mt002_data.clear();
  mf30_mt002_data = parser_obj;
}

void Endf6ParserCov::set_mf32_mt151_data(MF32MT151Parser parser_obj)
{
  mf32_mt151_data.clear();
  mf32_mt151_data = parser_obj;
}


void Endf6ParserCov::set_mf31_data(vector<MF31Parser> parser_obj)
{
  vector<MF31Parser>().swap(mf31_data);

  //for(int i=0; i<static_cast<int>(mf31_data.size()); i++)
  //{
  //  mf31_data[i].clear();
  //}
  //mf31_data.clear();

  mf31_data = parser_obj;
}

void Endf6ParserCov::set_mf33_data(vector<MF33Parser> parser_obj)
{
  vector<MF33Parser>().swap(mf33_data);

  //for(int i=0; i<static_cast<int>(mf33_data.size()); i++)
  //{
  //  mf33_data[i].clear();
  //}
  //mf33_data.clear();

  mf33_data = parser_obj;
}

void Endf6ParserCov::set_mf34_data(vector<MF34Parser> parser_obj)
{
  vector<MF34Parser>().swap(mf34_data);

  //for(int i=0; i<static_cast<int>(mf34_data.size()); i++)
  //{
  //  mf34_data[i].clear();
  //}
  //mf34_data.clear();

  mf34_data = parser_obj;
}

void Endf6ParserCov::set_mf35_data(vector<MF35Parser> parser_obj)
{
  vector<MF35Parser>().swap(mf35_data);

  //for(int i=0; i<static_cast<int>(mf35_data.size()); i++)
  //{
  //  mf35_data[i].clear();
  //}
  //mf35_data.clear();

  mf35_data = parser_obj;
}

void Endf6ParserCov::set_mf40_data(vector<MF40Parser> parser_obj)
{
  vector<MF40Parser>().swap(mf40_data);

  //for(int i=0; i<static_cast<int>(mf40_data.size()); i++)
  //{
  //  mf40_data[i].clear();
  //}
  //mf40_data.clear();

  mf40_data = parser_obj;
}

