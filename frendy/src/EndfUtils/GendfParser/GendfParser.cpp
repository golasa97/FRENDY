#include "EndfUtils/GendfParser/GendfParser.hpp"

using namespace frendy;

//constructor
GendfParser::GendfParser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
GendfParser::~GendfParser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::mod_list()
{
  int i_max;

  vector<Integer> mt_list_tmp;
  mt_list_tmp.clear();
  parser_list.clear();
  clr_obj.clear_vec_array2_int(mt_list);

  //For MF=1
  if( mf01_mt451_data.get_mat_no() != 0 && fabs(mf01_mt451_data.get_ZA())  > min_value
                                        && fabs(mf01_mt451_data.get_AWR()) > min_value )
  {
    mt_list_tmp.push_back(451);
  }

  if( static_cast<int>(mt_list_tmp.size()) > 0 )
  {
    parser_list.push_back(1);
    mt_list.push_back(mt_list_tmp);
  }
  mt_list_tmp.clear();

  //For MF=3
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

  //For MF=5
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

  //For MF=6
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

  //For MF=16
  i_max = static_cast<int>(mf16_data.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf16_data[i].get_mt_no() != 0 )
      {
        mt_list_tmp.push_back(mf16_data[i].get_mt_no());
      }
    }

    if( static_cast<int>(mt_list_tmp.size()) > 0 )
    {
      parser_list.push_back(16);
      mt_list.push_back(mt_list_tmp);
    }
    mt_list_tmp.clear();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::read_gendf()
{
  boost::timer::cpu_timer time_tot;

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
  //cout << "Reading gendf data was finished." << endl;

  //Calc total reading time.
  time_total = static_cast<Real>(time_tot.elapsed().wall * 1.0E-9);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::parse_data(Integer mf_no, Integer mt_no, vector<Real>& time_each_mf)
{
  boost::timer::cpu_timer  time;

  if( mf_no==1 )
  {
    parse_mf01(mf_no, mt_no);
  }
  else if( mf_no==3 )
  {
    parse_mf03(mf_no, mt_no);
  }
  else if( mf_no==5 )
  {
    parse_mf05(mf_no, mt_no);
  }
  else if( mf_no==6 )
  {
    parse_mf06(mf_no, mt_no);
  }
  else if( mf_no==13 )
  {
    parse_mf13(mf_no, mt_no);
  }
  else if( mf_no==16 )
  {
    parse_mf16(mf_no, mt_no);
  }
  else
  {
    string class_name = "GendfParser";
    string func_name  = "parse_data(Integer mf_no, Integer mt_no, vector<Real>& time_each_mf)";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "File number (MF)    : " + oss01.str();
    string str_data02 = "Section number (MT) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This MF number is not available in this program.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  time_each_mf.push_back(static_cast<Real>(time.elapsed().wall * 1.0E-9));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::parse_mf01(Integer mf_no, Integer mt_no)
{
  if( mt_no==451 )
  {
    mf01_mt451_data.set_text(efr_obj.get_data(mf_no, mt_no));
  }
  else
  {
    string class_name = "GendfParser";
    string func_name  = "parse_mf01(Integer mf_no, Integer mt_no)";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "File number (MF)    : " + oss01.str();
    string str_data02 = "Section number (MT) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This MT number at MF=01 is not applicable in this program.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::parse_mf03(Integer mf_no, Integer mt_no)
{
  GMF03Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf03_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::parse_mf05(Integer mf_no, Integer mt_no)
{
  GMF05Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf05_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::parse_mf06(Integer mf_no, Integer mt_no)
{
  GMF06Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf06_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::parse_mf13(Integer mf_no, Integer mt_no)
{
  GMF13Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf13_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::parse_mf16(Integer mf_no, Integer mt_no)
{
  GMF16Parser parse_obj;
  parse_obj.set_text(efr_obj.get_data(mf_no, mt_no));

  mf16_data.push_back(parse_obj);

  parse_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::clear()
{
  name.clear();
  parser_list.clear();
  mt_list.clear();

  time_total = 0.0;
  clr_obj.clear_vec_array2_real(time_each);

  mf01_mt451_data.clear();
  vector<GMF03Parser>().swap(mf03_data);
  vector<GMF05Parser>().swap(mf05_data);
  vector<GMF06Parser>().swap(mf06_data);
  vector<GMF13Parser>().swap(mf13_data);
  vector<GMF16Parser>().swap(mf16_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::set_file_name(string file_name)
{
  clear();
  name = file_name;
  file_name.clear();

  efr_obj.set_file_name(name);

  read_gendf();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::set_endf_file_reader(EndfFileReader& obj)
{
  clear();

  efr_obj = obj;
  name = efr_obj.get_file_name();

  read_gendf();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::set_text(vector<string>& text_data)
{
  clear();

  efr_obj.set_endf_data(text_data);

  read_gendf();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::set_parser_list()
{
  parser_list.clear();

  parser_list.clear();
  parser_list.push_back( 1);
  parser_list.push_back( 3);
  parser_list.push_back( 5);
  parser_list.push_back( 6);
  parser_list.push_back(13);
  parser_list.push_back(16);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::mod_reaction_flg(NuclearDataObject& nucl_data_obj)
{
  int i_max = static_cast<int>(mf03_data.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no        = mf03_data[i].get_mt_no();
    Integer reaction_flg = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(mt_no).get_reaction_flg();

    mf03_data[i].set_LR(reaction_flg);
  }

  i_max = static_cast<int>(mf05_data.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no        = mf05_data[i].get_mt_no();
    Integer reaction_flg = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(mt_no).get_reaction_flg();

    mf05_data[i].set_LR(reaction_flg);
  }

  i_max = static_cast<int>(mf06_data.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no        = mf06_data[i].get_mt_no();
    Integer reaction_flg = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(mt_no).get_reaction_flg();

    mf06_data[i].set_LR(reaction_flg);
  }

  i_max = static_cast<int>(mf13_data.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no        = mf13_data[i].get_mt_no();
    Integer reaction_flg = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(mt_no).get_reaction_flg();

    mf13_data[i].set_LR(reaction_flg);
  }

  i_max = static_cast<int>(mf16_data.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no        = mf16_data[i].get_mt_no();
    Integer reaction_flg = nucl_data_obj.get_nucl_reaction_data_obj().get_xs_data_obj(mt_no).get_reaction_flg();

    mf16_data[i].set_LR(reaction_flg);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::mod_temp(Real temp_val)
{
  mf01_mt451_data.set_TEMP(temp_val);

  int i_max = static_cast<int>(mf03_data.size());
  for(int i=0; i<i_max; i++)
  {
    mf03_data[i].set_TEMP(temp_val);
  }

  i_max = static_cast<int>(mf05_data.size());
  for(int i=0; i<i_max; i++)
  {
    mf05_data[i].set_TEMP(temp_val);
  }

  i_max = static_cast<int>(mf06_data.size());
  for(int i=0; i<i_max; i++)
  {
    mf06_data[i].set_TEMP(temp_val);
  }

  i_max = static_cast<int>(mf13_data.size());
  for(int i=0; i<i_max; i++)
  {
    mf13_data[i].set_TEMP(temp_val);
  }

  i_max = static_cast<int>(mf16_data.size());
  for(int i=0; i<i_max; i++)
  {
    mf16_data[i].set_TEMP(temp_val);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::sort_all_mf_data()
{
  sort_mf03_data();
  sort_mf05_data();
  sort_mf06_data();
  sort_mf13_data();
  sort_mf16_data();
}

void GendfParser::sort_mf03_data()
{
  vector<Integer> mt_list_each = get_mt_list(3);

  sort(mt_list_each.begin(), mt_list_each.end());

  vector<GMF03Parser> mf03_new;
  int i_max = static_cast<int>(mt_list_each.size());
  mf03_new.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    Integer mt_val = mf03_data[i].get_mt_no();

    for(int j=0; j<i_max; j++)
    {
      if( mt_val == mt_list_each[j] )
      {
        mf03_new[j] = mf03_data[i];
        break;
      }
    }
  }

  mf03_data = mf03_new;
  vector<GMF03Parser>().swap(mf03_new);
  mod_list();
}


void GendfParser::sort_mf05_data()
{
  vector<Integer> mt_list_each = get_mt_list(5);

  sort(mt_list_each.begin(), mt_list_each.end());

  vector<GMF05Parser> mf05_new;
  int i_max = static_cast<int>(mt_list_each.size());
  mf05_new.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    Integer mt_val = mf05_data[i].get_mt_no();

    for(int j=0; j<i_max; j++)
    {
      if( mt_val == mt_list_each[j] )
      {
        mf05_new[j] = mf05_data[i];
        break;
      }
    }
  }

  mf05_data = mf05_new;
  vector<GMF05Parser>().swap(mf05_new);
  mod_list();
}


void GendfParser::sort_mf06_data()
{
  vector<Integer> mt_list_each = get_mt_list(6);

  sort(mt_list_each.begin(), mt_list_each.end());

  vector<GMF06Parser> mf06_new;
  int i_max = static_cast<int>(mt_list_each.size());
  mf06_new.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    Integer mt_val = mf06_data[i].get_mt_no();

    for(int j=0; j<i_max; j++)
    {
      if( mt_val == mt_list_each[j] )
      {
        mf06_new[j] = mf06_data[i];
        break;
      }
    }
  }

  mf06_data = mf06_new;
  vector<GMF06Parser>().swap(mf06_new);
  mod_list();
}


void GendfParser::sort_mf13_data()
{
  vector<Integer> mt_list_each = get_mt_list(13);

  sort(mt_list_each.begin(), mt_list_each.end());

  vector<GMF13Parser> mf13_new;
  int i_max = static_cast<int>(mt_list_each.size());
  mf13_new.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    Integer mt_val = mf13_data[i].get_mt_no();

    for(int j=0; j<i_max; j++)
    {
      if( mt_val == mt_list_each[j] )
      {
        mf13_new[j] = mf13_data[i];
        break;
      }
    }
  }

  mf13_data = mf13_new;
  vector<GMF13Parser>().swap(mf13_new);
  mod_list();
}


void GendfParser::sort_mf16_data()
{
  vector<Integer> mt_list_each = get_mt_list(16);

  sort(mt_list_each.begin(), mt_list_each.end());

  vector<GMF16Parser> mf16_new;
  int i_max = static_cast<int>(mt_list_each.size());
  mf16_new.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    Integer mt_val = mf16_data[i].get_mt_no();

    for(int j=0; j<i_max; j++)
    {
      if( mt_val == mt_list_each[j] )
      {
        mf16_new[j] = mf16_data[i];
        break;
      }
    }
  }

  mf16_data = mf16_new;
  vector<GMF16Parser>().swap(mf16_new);
  mod_list();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

string                   GendfParser::get_file_name()
{
  return name;
}

vector<Integer>          GendfParser::get_parser_list()
{
  mod_list();
  return parser_list;
}

vector<vector<Integer> > GendfParser::get_mt_list()
{
  mod_list();
  return mt_list;
}

vector<Integer>          GendfParser::get_mt_list(Integer mf_no)
{
  mod_list();

  vector<Integer> list_vec;
  list_vec.clear();

  int i_max = static_cast<int>(parser_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( parser_list[i] == mf_no )
    {
      list_vec = mt_list[i];
      break;
    }
  }

  return list_vec;
}

Real                     GendfParser::get_time_total()
{
  return time_total;
}

vector<vector<Real> >    GendfParser::get_time_each()
{
  return time_each;
}


Integer            GendfParser::get_mat_no()
{
  return mf01_mt451_data.get_mat_no();
}

GMF01MT451Parser   GendfParser::get_mf01_mt451_data()
{
  return mf01_mt451_data;
}

vector<GMF03Parser> GendfParser::get_mf03_data()
{
  return mf03_data;
}

vector<GMF05Parser> GendfParser::get_mf05_data()
{
  return mf05_data;
}

vector<GMF06Parser> GendfParser::get_mf06_data()
{
  return mf06_data;
}

vector<GMF13Parser> GendfParser::get_mf13_data()
{
  return mf13_data;
}

vector<GMF16Parser> GendfParser::get_mf16_data()
{
  return mf16_data;
}

GMF03Parser GendfParser::get_mf03_data(Integer mt_no)
{
  GMF03Parser mf03_obj;
  mf03_obj.clear();

  for(int i=0; i<static_cast<int>(mf03_data.size()); i++)
  {
    if( mf03_data[i].get_mt_no() == mt_no )
    {
      mf03_obj = mf03_data[i];
      break;
    }
  }

  return mf03_obj;
}

GMF05Parser GendfParser::get_mf05_data(Integer mt_no)
{
  GMF05Parser mf05_obj;
  mf05_obj.clear();

  for(int i=0; i<static_cast<int>(mf05_data.size()); i++)
  {
    if( mf05_data[i].get_mt_no() == mt_no )
    {
      mf05_obj = mf05_data[i];
      break;
    }
  }

  return mf05_obj;
}

GMF06Parser GendfParser::get_mf06_data(Integer mt_no)
{
  GMF06Parser mf06_obj;
  mf06_obj.clear();

  for(int i=0; i<static_cast<int>(mf06_data.size()); i++)
  {
    if( mf06_data[i].get_mt_no() == mt_no )
    {
      mf06_obj = mf06_data[i];
      break;
    }
  }

  return mf06_obj;
}

GMF13Parser GendfParser::get_mf13_data(Integer mt_no)
{
  GMF13Parser mf13_obj;
  mf13_obj.clear();

  for(int i=0; i<static_cast<int>(mf13_data.size()); i++)
  {
    if( mf13_data[i].get_mt_no() == mt_no )
    {
      mf13_obj = mf13_data[i];
      break;
    }
  }

  return mf13_obj;
}

GMF16Parser GendfParser::get_mf16_data(Integer mt_no)
{
  GMF16Parser mf16_obj;
  mf16_obj.clear();

  for(int i=0; i<static_cast<int>(mf16_data.size()); i++)
  {
    if( mf16_data[i].get_mt_no() == mt_no )
    {
      mf16_obj = mf16_data[i];
      break;
    }
  }

  return mf16_obj;
}


//Setter
void GendfParser::set_mat_no(Integer mat_no)
{
  if( mat_no < 0 || mat_no > 10000 )
  {
    string class_name = "GendfParser";
    string func_name  = "set_mat_no(Integer mat_no)";

    ostringstream oss01;
    oss01 << mat_no;
    string str_data01 = "Material number (MAT) : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This MAT number is not available in this program.");
    err_com.push_back("The available MAT number is 0 <= MAT < 10000.");

    err_obj.output_runtime_error(class_name, func_name, err_com);    
  }

  mf01_mt451_data.set_mat_no(mat_no);

  for(int i=0; i<static_cast<int>(mf03_data.size()); i++)
  {
    mf03_data[i].set_mat_no(mat_no);
  }

  for(int i=0; i<static_cast<int>(mf05_data.size()); i++)
  {
    mf05_data[i].set_mat_no(mat_no);
  }

  for(int i=0; i<static_cast<int>(mf06_data.size()); i++)
  {
    mf06_data[i].set_mat_no(mat_no);
  }

  for(int i=0; i<static_cast<int>(mf13_data.size()); i++)
  {
    mf13_data[i].set_mat_no(mat_no);
  }

  for(int i=0; i<static_cast<int>(mf16_data.size()); i++)
  {
    mf16_data[i].set_mat_no(mat_no);
  }
}

void GendfParser::set_mf01_mt451_data(GMF01MT451Parser parser_obj)
{
  mf01_mt451_data.clear();

  mf01_mt451_data = parser_obj;
}


void GendfParser::set_mf03_data(vector<GMF03Parser> parser_obj)
{
  vector<GMF03Parser>().swap(mf03_data);

  mf03_data = parser_obj;
}

void GendfParser::set_mf05_data(vector<GMF05Parser> parser_obj)
{
  vector<GMF05Parser>().swap(mf05_data);

  mf05_data = parser_obj;
}

void GendfParser::set_mf06_data(vector<GMF06Parser> parser_obj)
{
  vector<GMF06Parser>().swap(mf06_data);

  mf06_data = parser_obj;
}

void GendfParser::set_mf13_data(vector<GMF13Parser> parser_obj)
{
  vector<GMF13Parser>().swap(mf13_data);

  mf13_data = parser_obj;
}

void GendfParser::set_mf16_data(vector<GMF16Parser> parser_obj)
{
  vector<GMF16Parser>().swap(mf16_data);

  mf16_data = parser_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfParser::set_mf03_data(GMF03Parser parser_obj)
{
  Integer mt_no = parser_obj.get_mt_no();
  vector<Integer> mt_list_each = get_mt_list(3);

  int pos = -1;
  for(int i=0; i<static_cast<int>(mt_list_each.size()); i++)
  {
    if( mt_list_each[i] == mt_no )
    {
      pos = i;
      break;
    }
  }

  if( pos >= 0 )
  {
    mf03_data[pos] = parser_obj;
  }
  else
  {
    mf03_data.push_back(parser_obj);
    sort_mf03_data();
  }
}


void GendfParser::set_mf05_data(GMF05Parser parser_obj)
{
  Integer mt_no = parser_obj.get_mt_no();
  vector<Integer> mt_list_each = get_mt_list(5);

  int pos = -1;
  for(int i=0; i<static_cast<int>(mt_list_each.size()); i++)
  {
    if( mt_list_each[i] == mt_no )
    {
      pos = i;
      break;
    }
  }

  if( pos >= 0 )
  {
    mf05_data[pos] = parser_obj;
  }
  else
  {
    mf05_data.push_back(parser_obj);
    sort_mf05_data();
  }
}


void GendfParser::set_mf06_data(GMF06Parser parser_obj)
{
  Integer mt_no = parser_obj.get_mt_no();
  vector<Integer> mt_list_each = get_mt_list(6);

  int pos = -1;
  for(int i=0; i<static_cast<int>(mt_list_each.size()); i++)
  {
    if( mt_list_each[i] == mt_no )
    {
      pos = i;
      break;
    }
  }

  if( pos >= 0 )
  {
    mf06_data[pos] = parser_obj;
  }
  else
  {
    mf06_data.push_back(parser_obj);
    sort_mf06_data();
  }
}


void GendfParser::set_mf13_data(GMF13Parser parser_obj)
{
  Integer mt_no = parser_obj.get_mt_no();
  vector<Integer> mt_list_each = get_mt_list(13);

  int pos = -1;
  for(int i=0; i<static_cast<int>(mt_list_each.size()); i++)
  {
    if( mt_list_each[i] == mt_no )
    {
      pos = i;
      break;
    }
  }

  if( pos >= 0 )
  {
    mf13_data[pos] = parser_obj;
  }
  else
  {
    mf13_data.push_back(parser_obj);
    sort_mf13_data();
  }
}


void GendfParser::set_mf16_data(GMF16Parser parser_obj)
{
  Integer mt_no = parser_obj.get_mt_no();
  vector<Integer> mt_list_each = get_mt_list(16);

  int pos = -1;
  for(int i=0; i<static_cast<int>(mt_list_each.size()); i++)
  {
    if( mt_list_each[i] == mt_no )
    {
      pos = i;
      break;
    }
  }

  if( pos >= 0 )
  {
    mf16_data[pos] = parser_obj;
  }
  else
  {
    mf16_data.push_back(parser_obj);
    sort_mf16_data();
  }
}

