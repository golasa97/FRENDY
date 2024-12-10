#include "EndfUtils/Endf6Parser/Endf6ParserNoCov.hpp"

using namespace frendy;

//constructor
Endf6ParserNoCov::Endf6ParserNoCov(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
Endf6ParserNoCov::~Endf6ParserNoCov(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::mod_list()
{
  int i_max;

  vector<Integer> mt_list_tmp;
  mt_list_tmp.clear();
  parser_list.clear();
  clr_obj.clear_vec_array2_int(mt_list);

  //For MF=01
  if( mf01_mt451_data.get_mat_no() != 0 && fabs(mf01_mt451_data.get_ZA())  > min_value 
                                        && fabs(mf01_mt451_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(451);
  }

  if( mf01_mt452_data.get_mat_no() != 0 && fabs(mf01_mt452_data.get_ZA())  > min_value 
                                        && fabs(mf01_mt452_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(452);
  }

  if( mf01_mt455_data.get_mat_no() != 0 && fabs(mf01_mt455_data.get_ZA())  > min_value
                                        && fabs(mf01_mt455_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(455);
  }

  if( mf01_mt456_data.get_mat_no() != 0 && fabs(mf01_mt456_data.get_ZA())  > min_value
                                        && fabs(mf01_mt456_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(456);
  }

  if( mf01_mt458_data.get_mat_no() != 0 && fabs(mf01_mt458_data.get_ZA())  > min_value
                                        && fabs(mf01_mt458_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(458);
  }

  if( mf01_mt460_data.get_mat_no() != 0 && fabs(mf01_mt460_data.get_ZA())  > min_value
                                        && fabs(mf01_mt460_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(460);
  }

  if( static_cast<int>(mt_list_tmp.size()) > 0 )
  {
    parser_list.push_back(1);
    mt_list.push_back(mt_list_tmp);
  }
  mt_list_tmp.clear();
  
  //For MF=02
  if( mf02_mt151_data.get_mat_no() != 0 && fabs(mf02_mt151_data.get_ZAR()) > min_value
                                        && fabs(mf02_mt151_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(151);
  }

  if( mf02_mt152_data.get_mat_no() != 0 && fabs(mf02_mt152_data.get_ZAR()) > min_value
                                        && fabs(mf02_mt152_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(152);
  }

  if( mf02_mt153_data.get_mat_no() != 0 && fabs(mf02_mt153_data.get_ZAR()) > min_value
                                        && fabs(mf02_mt153_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(153);
  }

  if( static_cast<int>(mt_list_tmp.size()) > 0 )
  {
    parser_list.push_back(2);
    mt_list.push_back(mt_list_tmp);
  }
  mt_list_tmp.clear();


  //For MF=03
  i_max = static_cast<int>(mf03_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf03_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf03_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(3);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=04
  i_max = static_cast<int>(mf04_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf04_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf04_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(4);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=05
  i_max = static_cast<int>(mf05_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf05_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf05_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(5);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=06
  i_max = static_cast<int>(mf06_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf06_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf06_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(6);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=07
  if( mf07_mt002_data.get_mat_no() != 0 && fabs(mf07_mt002_data.get_ZA())  > min_value
                                        && fabs(mf07_mt002_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(2);
  }

  if( mf07_mt004_data.get_mat_no() != 0 && fabs(mf07_mt004_data.get_ZA())  > min_value
                                        && fabs(mf07_mt004_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(4);
  }

  if( mf07_mt451_data.get_mat_no() != 0 && fabs(mf07_mt451_data.get_ZA())  > min_value
                                        && fabs(mf07_mt451_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(451);
  }

  if( static_cast<int>(mt_list_tmp.size()) > 0 )
  {
    parser_list.push_back(7);
    mt_list.push_back(mt_list_tmp);
  }
  mt_list_tmp.clear();

  //For MF=08
  if( mf08_mt454_data.get_mat_no() != 0 && fabs(mf08_mt454_data.get_ZA())  > min_value
                                        && fabs(mf08_mt454_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(454);
  }

  if( mf08_mt457_data.get_mat_no() != 0 && fabs(mf08_mt457_data.get_ZA())  > min_value
                                        && fabs(mf08_mt457_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(457);
  }

  if( mf08_mt459_data.get_mat_no() != 0 && fabs(mf08_mt459_data.get_ZA())  > min_value
                                        && fabs(mf08_mt459_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(459);
  }

  i_max = static_cast<int>(mf08_data.size());
  for(int i=0; i<i_max; i++)
  {
    if( mf08_data[i].get_mt_no() != 0 )
    {
      mt_list_tmp.push_back(mf08_data[i].get_mt_no());
    }
  }
  
  if( static_cast<int>(mt_list_tmp.size()) > 0 )
  {
    parser_list.push_back(8);
    mt_list.push_back(mt_list_tmp);
  }
  mt_list_tmp.clear();

  //For MF=09
  i_max = static_cast<int>(mf09_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf09_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf09_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(9);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=10
  i_max = static_cast<int>(mf10_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf10_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf10_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(10);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=12
  i_max = static_cast<int>(mf12_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf12_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf12_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(12);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=13
  i_max = static_cast<int>(mf13_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf13_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf13_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(13);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=14
  i_max = static_cast<int>(mf14_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf14_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf14_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(14);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=15
  i_max = static_cast<int>(mf15_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf15_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf15_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(15);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=23
  i_max = static_cast<int>(mf23_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf23_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf23_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(23);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=26
  i_max = static_cast<int>(mf26_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf26_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf26_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(26);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=27
  i_max = static_cast<int>(mf27_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf27_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf27_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(27);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }

  //For MF=28
  i_max = static_cast<int>(mf28_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf28_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf28_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(28);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::read_endf()
{
  boost::timer::cpu_timer time_tot;

  set_parser_list();

  vector<Real>    time_each_mf;
  time_each_mf.clear();
  clr_obj.clear_vec_array2_real(time_each);

  int tsl_data_flg = 0;
  for(int i=0; i<static_cast<int>(parser_list.size()); i++)
  {
    Integer mf = parser_list[i];
    if( mf == 7 )
    {
      tsl_data_flg = 1;
    }
  }

  for(int i=0; i<static_cast<int>(parser_list.size()); i++)
  {
    Integer mf = parser_list[i];
    vector<Integer> mt_list_tmp = efr_obj.get_mt_list(mf);
    if( mf == 3 )
    {
      Integer tot_data_check = 0;
      for(int j=0; j<static_cast<int>(mt_list_tmp.size()); j++)
      {
        if( mt_list_tmp[j] == 1 )
        {
          tot_data_check = 1;
          break;
        }
      }

      if( tot_data_check == 0 && tsl_data_flg == 0 )
      {
        string class_name = "Endf6ParserNoCov";
        string func_name  = "read_endf()";

        ostringstream oss01;
        oss01 << mf;
        string str_data01 = "File name        : " + name;
        string str_data02 = "File number (MF) : " + oss01.str();

        vector<string> err_com;
        if( static_cast<int>(name.size()) > 0 )
        {
          err_com.push_back(str_data01);
        }
        err_com.push_back(str_data02);
        err_com.push_back("There is no total cross section data (MT=1) in this ENDF file.");
        err_com.push_back("If this file is neutron induce data, this data may not be appropriate.");

        err_obj.output_caution(class_name, func_name, err_com);
      }
    }

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
  //cout << "Reading no covariance data was finished." << endl;
  
  time_total = static_cast<Real>(time_tot.elapsed().wall * 1.0E-9);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_data(Integer mf_no, Integer mt_no, vector<Real>& time_each_mf)
{
  boost::timer::cpu_timer time;

  if( mf_no== 1 )
  {
    parse_mf01(mf_no, mt_no);
  }
  else if( mf_no== 2 )
  {
    parse_mf02(mf_no, mt_no);
  }
  else if( mf_no== 3 )
  {
    parse_mf03(mf_no, mt_no);
  }
  else if( mf_no== 4 )
  {
    parse_mf04(mf_no, mt_no);
  }
  else if( mf_no== 5 )
  {
    parse_mf05(mf_no, mt_no);
  }
  else if( mf_no== 6 )
  {
    parse_mf06(mf_no, mt_no);
  }
  else if( mf_no== 7 )
  {
    parse_mf07(mf_no, mt_no);
  }
  else if( mf_no== 8 )
  {
    parse_mf08(mf_no, mt_no);
  }
  else if( mf_no== 9 )
  {
    parse_mf09(mf_no, mt_no);
  }
  else if( mf_no==10 )
  {
    parse_mf10(mf_no, mt_no);
  }
  else if( mf_no==12 )
  {
    parse_mf12(mf_no, mt_no);
  }
  else if( mf_no==13 )
  {
    parse_mf13(mf_no, mt_no);
  }
  else if( mf_no==14 )
  {
    parse_mf14(mf_no, mt_no);
  }
  else if( mf_no==15 )
  {
    parse_mf15(mf_no, mt_no);
  }
  else if( mf_no==23 )
  {
    parse_mf23(mf_no, mt_no);
  }
  else if( mf_no==26 )
  {
    parse_mf26(mf_no, mt_no);
  }
  else if( mf_no==27 )
  {
    parse_mf27(mf_no, mt_no);
  }
  else if( mf_no==28 )
  {
    parse_mf28(mf_no, mt_no);
  }

  time_each_mf.push_back(static_cast<Real>(time.elapsed().wall * 1.0E-9));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf01(Integer mf_no, Integer mt_no)
{
  if( mt_no==451 )
  {
    mf01_mt451_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else if( mt_no==452 )
  {
    mf01_mt452_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else if( mt_no==455 )
  {
    mf01_mt455_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else if( mt_no==456 )
  {
    mf01_mt456_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else if( mt_no==458 )
  {
    mf01_mt458_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else if( mt_no==460 )
  {
    mf01_mt460_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else
  {
    string class_name = "Endf6ParserNoCov";
    string func_name  = "parse_mf01(Integer mf_no, Integer mt_no)";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "File number (MF)    : " + oss01.str();
    string str_data02 = "Section number (MT) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This MT number at MF=1 is not applicable in this program.");
    err_com.push_back("Supported MT number is MT=451, 452, 455, 456, 458 and 460.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf02(Integer mf_no, Integer mt_no)
{
  if( mt_no==151 )
  {
    mf02_mt151_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else if( mt_no==152 )
  {
    mf02_mt152_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else if( mt_no==153 )
  {
    mf02_mt153_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else
  {
    string class_name = "Endf6ParserNoCov";
    string func_name  = "parse_mf02(Integer mf_no, Integer mt_no)";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "File number (MF)    : " + oss01.str();
    string str_data02 = "Section number (MT) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This MT number at MF=2 is not applicable in this program.");
    err_com.push_back("Supported MT number is MT=151, 152 and 153.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf03(Integer mf_no, Integer mt_no)
{
  MF03Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf03_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf04(Integer mf_no, Integer mt_no)
{
  MF04Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf04_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf05(Integer mf_no, Integer mt_no)
{
  MF05Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf05_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf06(Integer mf_no, Integer mt_no)
{
  MF06Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf06_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf07(Integer mf_no, Integer mt_no)
{
  if( mt_no==2 )
  {
    mf07_mt002_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else if( mt_no==4 )
  {
    mf07_mt004_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else if( mt_no==451 )
  {
    mf07_mt451_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else
  {
    string class_name = "Endf6ParserNoCov";
    string func_name  = "parse_mf07(Integer mf_no, Integer mt_no)";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "File number (MF)    : " + oss01.str();
    string str_data02 = "Section number (MT) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This MT number at MF=7 is not applicable in this program.");
    err_com.push_back("Supported MT number is MT=2 and 4.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf08(Integer mf_no, Integer mt_no)
{
  if( mt_no==454 )
  {
    mf08_mt454_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else if( mt_no==457 )
  {
    mf08_mt457_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else if( mt_no==459 )
  {
    mf08_mt459_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else
  {
    MF08Parser parse_obj;
    parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

    mf08_data.push_back(parse_obj);

    parse_obj.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf09(Integer mf_no, Integer mt_no)
{
  MF09Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf09_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf10(Integer mf_no, Integer mt_no)
{
  MF10Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf10_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf12(Integer mf_no, Integer mt_no)
{
  MF12Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf12_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf13(Integer mf_no, Integer mt_no)
{
  MF13Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf13_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf14(Integer mf_no, Integer mt_no)
{
  MF14Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf14_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf15(Integer mf_no, Integer mt_no)
{
  MF15Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf15_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf23(Integer mf_no, Integer mt_no)
{
  MF23Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf23_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf26(Integer mf_no, Integer mt_no)
{
  MF26Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf26_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf27(Integer mf_no, Integer mt_no)
{
  MF27Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf27_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::parse_mf28(Integer mf_no, Integer mt_no)
{
  MF28Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf28_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::clear()
{
  name.clear();
  time_total = 0.0;

  clr_obj.clear_vec_array2_real(time_each);

  parser_list.clear();
  mt_list.clear();

  mf01_mt451_data.clear();
  mf01_mt452_data.clear();
  mf01_mt455_data.clear();
  mf01_mt456_data.clear();
  mf01_mt458_data.clear();
  mf01_mt460_data.clear();
  mf02_mt151_data.clear();
  mf02_mt152_data.clear();
  mf02_mt153_data.clear();
  mf07_mt002_data.clear();
  mf07_mt004_data.clear();
  mf07_mt451_data.clear();
  mf08_mt454_data.clear();
  mf08_mt457_data.clear();
  mf08_mt459_data.clear();

  vector<MF03Parser>().swap(mf03_data);
  //for(int i=0; i<static_cast<int>(mf03_data.size()); i++)
  //{
  //  mf03_data[i].clear();
  //}
  //mf03_data.clear();

  vector<MF04Parser>().swap(mf04_data);
  //for(int i=0; i<static_cast<int>(mf04_data.size()); i++)
  //{
  //  mf04_data[i].clear();
  //}
  //mf04_data.clear();

  vector<MF05Parser>().swap(mf05_data);
  //for(int i=0; i<static_cast<int>(mf05_data.size()); i++)
  //{
  //  mf05_data[i].clear();
  //}
  //mf05_data.clear();

  vector<MF06Parser>().swap(mf06_data);
  //for(int i=0; i<static_cast<int>(mf06_data.size()); i++)
  //{
  //  mf06_data[i].clear();
  //}
  //mf06_data.clear();

  vector<MF08Parser>().swap(mf08_data);
  //for(int i=0; i<static_cast<int>(mf08_data.size()); i++)
  //{
  //  mf08_data[i].clear();
  //}
  //mf08_data.clear();

  vector<MF09Parser>().swap(mf09_data);
  //for(int i=0; i<static_cast<int>(mf09_data.size()); i++)
  //{
  //  mf09_data[i].clear();
  //}
  //mf09_data.clear();

  vector<MF10Parser>().swap(mf10_data);
  //for(int i=0; i<static_cast<int>(mf10_data.size()); i++)
  //{
  //  mf10_data[i].clear();
  //}
  //mf10_data.clear();

  vector<MF12Parser>().swap(mf12_data);
  //for(int i=0; i<static_cast<int>(mf12_data.size()); i++)
  //{
  //  mf12_data[i].clear();
  //}
  //mf12_data.clear();

  vector<MF13Parser>().swap(mf13_data);
  //for(int i=0; i<static_cast<int>(mf13_data.size()); i++)
  //{
  //  mf13_data[i].clear();
  //}
  //mf13_data.clear();

  vector<MF14Parser>().swap(mf14_data);
  //for(int i=0; i<static_cast<int>(mf14_data.size()); i++)
  //{
  //  mf14_data[i].clear();
  //}
  //mf14_data.clear();

  vector<MF15Parser>().swap(mf15_data);
  //for(int i=0; i<static_cast<int>(mf15_data.size()); i++)
  //{
  //  mf15_data[i].clear();
  //}
  //mf15_data.clear();

  vector<MF23Parser>().swap(mf23_data);
  //for(int i=0; i<static_cast<int>(mf23_data.size()); i++)
  //{
  //  mf23_data[i].clear();
  //}
  //mf23_data.clear();

  vector<MF26Parser>().swap(mf26_data);
  //for(int i=0; i<static_cast<int>(mf26_data.size()); i++)
  //{
  //  mf26_data[i].clear();
  //}
  //mf26_data.clear();

  vector<MF27Parser>().swap(mf27_data);
  //for(int i=0; i<static_cast<int>(mf27_data.size()); i++)
  //{
  //  mf27_data[i].clear();
  //}
  //mf27_data.clear();

  vector<MF28Parser>().swap(mf28_data);
  //for(int i=0; i<static_cast<int>(mf28_data.size()); i++)
  //{
  //  mf28_data[i].clear();
  //}
  //mf28_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::set_file_name(string file_name)
{
  clear();
  name = file_name;
  file_name.clear();

  efr_obj.set_file_name(name);

  read_endf();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::set_endf_file_reader(EndfFileReader& obj)
{
  clear();

  efr_obj = obj;
  name = efr_obj.get_file_name();

  read_endf();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::set_text(vector<string>& text_data)
{
  clear();

  efr_obj.set_endf_data(text_data);

  read_endf();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ParserNoCov::set_parser_list()
{
  parser_list.clear();

  parser_list.clear();
  parser_list.push_back( 1);
  parser_list.push_back( 2);
  parser_list.push_back( 3);
  parser_list.push_back( 4);
  parser_list.push_back( 5);
  parser_list.push_back( 6);
  parser_list.push_back( 7);
  parser_list.push_back( 8);
  parser_list.push_back( 9);
  parser_list.push_back(10);
  parser_list.push_back(12);
  parser_list.push_back(13);
  parser_list.push_back(14);
  parser_list.push_back(15);
  parser_list.push_back(23);
  parser_list.push_back(26);
  parser_list.push_back(27);
  parser_list.push_back(28);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

string                   Endf6ParserNoCov::get_file_name()
{
  return name;
}

vector<Integer>          Endf6ParserNoCov::get_parser_list()
{
  mod_list();
  return parser_list;
}

vector<vector<Integer> > Endf6ParserNoCov::get_mt_list()
{
  mod_list();
  return mt_list;
}

Real                     Endf6ParserNoCov::get_time_total()
{
  return time_total;
}

vector<vector<Real> >    Endf6ParserNoCov::get_time_each()
{
  return time_each;
}


MF01MT451Parser    Endf6ParserNoCov::get_mf01_mt451_data()
{
  return mf01_mt451_data;
}

MF01MT452Parser    Endf6ParserNoCov::get_mf01_mt452_data()
{
  return mf01_mt452_data;
}

MF01MT455Parser    Endf6ParserNoCov::get_mf01_mt455_data()
{
  return mf01_mt455_data;
}

MF01MT456Parser    Endf6ParserNoCov::get_mf01_mt456_data()
{
  return mf01_mt456_data;
}

MF01MT458Parser    Endf6ParserNoCov::get_mf01_mt458_data()
{
  return mf01_mt458_data;
}

MF01MT460Parser    Endf6ParserNoCov::get_mf01_mt460_data()
{
  return mf01_mt460_data;
}

MF02MT151Parser    Endf6ParserNoCov::get_mf02_mt151_data()
{
  return mf02_mt151_data;
}

MF02MT152Parser    Endf6ParserNoCov::get_mf02_mt152_data()
{
  return mf02_mt152_data;
}

MF02MT153Parser    Endf6ParserNoCov::get_mf02_mt153_data()
{
  return mf02_mt153_data;
}

MF07MT002Parser    Endf6ParserNoCov::get_mf07_mt002_data()
{
  return mf07_mt002_data;
}

MF07MT004Parser    Endf6ParserNoCov::get_mf07_mt004_data()
{
  return mf07_mt004_data;
}

MF07MT451Parser    Endf6ParserNoCov::get_mf07_mt451_data()
{
  return mf07_mt451_data;
}

MF08MT454Parser    Endf6ParserNoCov::get_mf08_mt454_data()
{
  return mf08_mt454_data;
}

MF08MT457Parser    Endf6ParserNoCov::get_mf08_mt457_data()
{
  return mf08_mt457_data;
}

MF08MT459Parser    Endf6ParserNoCov::get_mf08_mt459_data()
{
  return mf08_mt459_data;
}


vector<MF03Parser> Endf6ParserNoCov::get_mf03_data()
{
  return mf03_data;
}

vector<MF04Parser> Endf6ParserNoCov::get_mf04_data()
{
  return mf04_data;
}

vector<MF05Parser> Endf6ParserNoCov::get_mf05_data()
{
  return mf05_data;
}

vector<MF06Parser> Endf6ParserNoCov::get_mf06_data()
{
  return mf06_data;
}

vector<MF08Parser> Endf6ParserNoCov::get_mf08_data()
{
  return mf08_data;
}

vector<MF09Parser> Endf6ParserNoCov::get_mf09_data()
{
  return mf09_data;
}

vector<MF10Parser> Endf6ParserNoCov::get_mf10_data()
{
  return mf10_data;
}

vector<MF12Parser> Endf6ParserNoCov::get_mf12_data()
{
  return mf12_data;
}

vector<MF13Parser> Endf6ParserNoCov::get_mf13_data()
{
  return mf13_data;
}

vector<MF14Parser> Endf6ParserNoCov::get_mf14_data()
{
  return mf14_data;
}

vector<MF15Parser> Endf6ParserNoCov::get_mf15_data()
{
  return mf15_data;
}

vector<MF23Parser> Endf6ParserNoCov::get_mf23_data()
{
  return mf23_data;
}

vector<MF26Parser> Endf6ParserNoCov::get_mf26_data()
{
  return mf26_data;
}

vector<MF27Parser> Endf6ParserNoCov::get_mf27_data()
{
  return mf27_data;
}

vector<MF28Parser> Endf6ParserNoCov::get_mf28_data()
{
  return mf28_data;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void Endf6ParserNoCov::set_mf01_mt451_data(MF01MT451Parser parser_obj)
{
  mf01_mt451_data.clear();
  mf01_mt451_data = parser_obj;
}

void Endf6ParserNoCov::set_mf01_mt452_data(MF01MT452Parser parser_obj)
{
  mf01_mt452_data.clear();
  mf01_mt452_data = parser_obj;
}

void Endf6ParserNoCov::set_mf01_mt455_data(MF01MT455Parser parser_obj)
{
  mf01_mt455_data.clear();
  mf01_mt455_data = parser_obj;
}

void Endf6ParserNoCov::set_mf01_mt456_data(MF01MT456Parser parser_obj)
{
  mf01_mt456_data.clear();
  mf01_mt456_data = parser_obj;
}

void Endf6ParserNoCov::set_mf01_mt458_data(MF01MT458Parser parser_obj)
{
  mf01_mt458_data.clear();
  mf01_mt458_data = parser_obj;
}

void Endf6ParserNoCov::set_mf01_mt460_data(MF01MT460Parser parser_obj)
{
  mf01_mt460_data.clear();
  mf01_mt460_data = parser_obj;
}

void Endf6ParserNoCov::set_mf02_mt151_data(MF02MT151Parser parser_obj)
{
  mf02_mt151_data.clear();
  mf02_mt151_data = parser_obj;
}

void Endf6ParserNoCov::set_mf02_mt152_data(MF02MT152Parser parser_obj)
{
  mf02_mt152_data.clear();
  mf02_mt152_data = parser_obj;
}

void Endf6ParserNoCov::set_mf02_mt153_data(MF02MT153Parser parser_obj)
{
  mf02_mt153_data.clear();
  mf02_mt153_data = parser_obj;
}

void Endf6ParserNoCov::set_mf07_mt002_data(MF07MT002Parser parser_obj)
{
  mf07_mt002_data.clear();
  mf07_mt002_data = parser_obj;
}

void Endf6ParserNoCov::set_mf07_mt004_data(MF07MT004Parser parser_obj)
{
  mf07_mt004_data.clear();
  mf07_mt004_data = parser_obj;
}

void Endf6ParserNoCov::set_mf07_mt451_data(MF07MT451Parser parser_obj)
{
  mf07_mt451_data.clear();
  mf07_mt451_data = parser_obj;
}

void Endf6ParserNoCov::set_mf08_mt454_data(MF08MT454Parser parser_obj)
{
  mf08_mt454_data.clear();
  mf08_mt454_data = parser_obj;
}

void Endf6ParserNoCov::set_mf08_mt457_data(MF08MT457Parser parser_obj)
{
  mf08_mt457_data.clear();
  mf08_mt457_data = parser_obj;
}

void Endf6ParserNoCov::set_mf08_mt459_data(MF08MT459Parser parser_obj)
{
  mf08_mt459_data.clear();
  mf08_mt459_data = parser_obj;
}


void Endf6ParserNoCov::set_mf03_data(vector<MF03Parser> parser_obj)
{
  vector<MF03Parser>().swap(mf03_data);
  //for(int i=0; i<static_cast<int>(mf03_data.size()); i++)
  //{
  //  mf03_data[i].clear();
  //}
  //mf03_data.clear();

  mf03_data = parser_obj;
}

void Endf6ParserNoCov::set_mf04_data(vector<MF04Parser> parser_obj)
{
  vector<MF04Parser>().swap(mf04_data);
  //for(int i=0; i<static_cast<int>(mf04_data.size()); i++)
  //{
  //  mf04_data[i].clear();
  //}
  //mf04_data.clear();

  mf04_data = parser_obj;
}

void Endf6ParserNoCov::set_mf05_data(vector<MF05Parser> parser_obj)
{
  vector<MF05Parser>().swap(mf05_data);
  //for(int i=0; i<static_cast<int>(mf05_data.size()); i++)
  //{
  //  mf05_data[i].clear();
  //}
  //mf05_data.clear();

  mf05_data = parser_obj;
}

void Endf6ParserNoCov::set_mf06_data(vector<MF06Parser> parser_obj)
{
  vector<MF06Parser>().swap(mf06_data);
  //for(int i=0; i<static_cast<int>(mf06_data.size()); i++)
  //{
  //  mf06_data[i].clear();
  //}
  //mf06_data.clear();

  mf06_data = parser_obj;
}

void Endf6ParserNoCov::set_mf08_data(vector<MF08Parser> parser_obj)
{
  vector<MF08Parser>().swap(mf08_data);
  //for(int i=0; i<static_cast<int>(mf08_data.size()); i++)
  //{
  //  mf08_data[i].clear();
  //}
  //mf08_data.clear();

  mf08_data = parser_obj;
}

void Endf6ParserNoCov::set_mf09_data(vector<MF09Parser> parser_obj)
{
  vector<MF09Parser>().swap(mf09_data);
  //for(int i=0; i<static_cast<int>(mf09_data.size()); i++)
  //{
  //  mf09_data[i].clear();
  //}
  //mf09_data.clear();

  mf09_data = parser_obj;
}

void Endf6ParserNoCov::set_mf10_data(vector<MF10Parser> parser_obj)
{
  vector<MF10Parser>().swap(mf10_data);
  //for(int i=0; i<static_cast<int>(mf10_data.size()); i++)
  //{
  //  mf10_data[i].clear();
  //}
  //mf10_data.clear();

  mf10_data = parser_obj;
}

void Endf6ParserNoCov::set_mf12_data(vector<MF12Parser> parser_obj)
{
  vector<MF12Parser>().swap(mf12_data);
  //for(int i=0; i<static_cast<int>(mf12_data.size()); i++)
  //{
  //  mf12_data[i].clear();
  //}
  //mf12_data.clear();

  mf12_data = parser_obj;
}

void Endf6ParserNoCov::set_mf13_data(vector<MF13Parser> parser_obj)
{
  vector<MF13Parser>().swap(mf13_data);
  //for(int i=0; i<static_cast<int>(mf13_data.size()); i++)
  //{
  //  mf13_data[i].clear();
  //}
  //mf13_data.clear();

  mf13_data = parser_obj;
}

void Endf6ParserNoCov::set_mf14_data(vector<MF14Parser> parser_obj)
{
  vector<MF14Parser>().swap(mf14_data);
  //for(int i=0; i<static_cast<int>(mf14_data.size()); i++)
  //{
  //  mf14_data[i].clear();
  //}
  //mf14_data.clear();

  mf14_data = parser_obj;
}

void Endf6ParserNoCov::set_mf15_data(vector<MF15Parser> parser_obj)
{
  vector<MF15Parser>().swap(mf15_data);
  //for(int i=0; i<static_cast<int>(mf15_data.size()); i++)
  //{
  //  mf15_data[i].clear();
  //}
  //mf15_data.clear();

  mf15_data = parser_obj;
}

void Endf6ParserNoCov::set_mf23_data(vector<MF23Parser> parser_obj)
{
  vector<MF23Parser>().swap(mf23_data);
  //for(int i=0; i<static_cast<int>(mf23_data.size()); i++)
  //{
  //  mf23_data[i].clear();
  //}
  //mf23_data.clear();

  mf23_data = parser_obj;
}

void Endf6ParserNoCov::set_mf26_data(vector<MF26Parser> parser_obj)
{
  vector<MF26Parser>().swap(mf26_data);
  //for(int i=0; i<static_cast<int>(mf26_data.size()); i++)
  //{
  //  mf26_data[i].clear();
  //}
  //mf26_data.clear();

  mf26_data = parser_obj;
}

void Endf6ParserNoCov::set_mf27_data(vector<MF27Parser> parser_obj)
{
  vector<MF27Parser>().swap(mf27_data);
  //for(int i=0; i<static_cast<int>(mf27_data.size()); i++)
  //{
  //  mf27_data[i].clear();
  //}
  //mf27_data.clear();

  mf27_data = parser_obj;
}

void Endf6ParserNoCov::set_mf28_data(vector<MF28Parser> parser_obj)
{
  vector<MF28Parser>().swap(mf28_data);
  //for(int i=0; i<static_cast<int>(mf28_data.size()); i++)
  //{
  //  mf28_data[i].clear();
  //}
  //mf28_data.clear();

  mf28_data = parser_obj;
}

