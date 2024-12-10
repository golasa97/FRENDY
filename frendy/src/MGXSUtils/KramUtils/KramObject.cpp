#include "MGXSUtils/KramUtils/KramObject.hpp"

using namespace frendy;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

// ***** KramUtils ***** //

//constructor
KramUtils::KramUtils(void)
{
}

//destructor
KramUtils::~KramUtils(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real> > KramUtils::reverse_mg_array(vector<vector<Real> >& xs_vec)
{
  int mg = static_cast<int>(xs_vec.size());

  vector<vector<Real> > xs_new;
  xs_new.resize(mg);
  for(int i=0; i<mg; i++)
  {
    xs_new[i].resize(mg);
    for(int j=0; j<mg; j++)
    {
      xs_new[i][j] = xs_vec[mg-j-1][mg-i-1];
    }
  }

  return xs_new;
}

vector<Real> KramUtils::reverse_mg_vec(vector<Real>& xs_vec)
{
  int mg = static_cast<int>(xs_vec.size());

  vector<Real> xs_new;
  xs_new.resize(mg);
  for(int i=0; i<mg; i++)
  {
    xs_new[i] = xs_vec[mg-i-1];
  }

  return xs_new;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

// ***** KramXsnData ***** //

//constructor
KramXsnData::KramXsnData(void)
{
  clear();
}

//destructor
KramXsnData::~KramXsnData(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramXsnData::clear()
{
  ng     = 0;
  mat_no = unassigned_mat_no;

  clr_obj.clear_vec_array2_real(xs_sc);

  xs_prod.clear();
  xs_abs.clear();
  xs_fis.clear();
  xs_tot.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramXsnData::read_data(vector<string>& text_vec, int mg_no)
{
  int line_no = 0;
  read_data(text_vec, line_no, mg_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramXsnData::read_data(vector<string>& text_vec, int& line_no, int mg_no)
{
  clear();

  if( line_no >= static_cast<int>(text_vec.size()) )
  {
    return;
  }

  StringUtils str_obj;
  vector<string> str_vec;

  int str_no = 0;
  while( str_no == 0 )
  {
    str_vec = str_obj.read_data(text_vec, line_no, str_no);
  }

  transform(str_vec[0].begin(), str_vec[0].end(), str_vec[0].begin(), ::tolower);
  if( str_vec[0] != "xsn" || str_no == 1 )
  {
    if( str_vec[0] == "fsp" || str_vec[0] == "asc" )
    {
      line_no--;
      return;
    }

    string class_name = "KramXsnData";
    string func_name  = "read_data(vector<string>& text_vec, int& line_no)";

    ostringstream oss01, oss02;
    oss01 << line_no;
    oss02 << static_cast<int>(text_vec.size());

    string str_data01 = "Line number : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "Line data   : " + text_vec[line_no-1];

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);

    if( str_vec[0] != "xsn" )
    {
      err_com.push_back("XSN is not found in this text data.");
      err_com.push_back("Please check the KRAM file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    else //if( str_no == 1 )
    {
      err_com.push_back("There is not material number.");
      err_com.push_back("The material number is set as 1.");
      err_obj.output_caution(class_name, func_name, err_com);

      mat_no = 1;
    }
  }
  else
  {
    mat_no = numeric_string_cast<int>(str_vec[1]);
  }

  ng = mg_no;
  xs_sc.resize(ng);
  xs_prod.resize(ng);
  xs_abs.resize(ng);
  xs_fis.resize(ng);
  xs_tot.resize(ng);
  for(int i=0; i<ng; i++)
  {
    xs_prod[i] = 0.0;
    xs_abs[i]  = 0.0;
    xs_fis[i]  = 0.0;
    xs_tot[i]  = 0.0;
  }

  for(int i=0; i<ng+4; i++)
  {
    str_no = 0;
    while( str_no == 0 )
    {
      str_vec = str_obj.read_data(text_vec, line_no, str_no);
    }

    if( str_no != ng )
    {
      string class_name = "KramXsnData";
      string func_name  = "read_data(vector<string>& text_vec, int& line_no)";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << str_no;
      oss02 << ng;
      oss03 << line_no;
      oss04 << static_cast<int>(text_vec.size());

      string str_data01 = "Data section (reaction type) : ";
      string str_data02 = "Data number in this line     : " + oss01.str();
      string str_data03 = "Multi-group number           : " + oss02.str();
      string str_data04 = "Line number                  : " + oss03.str() + " / " + oss04.str();
      string str_data05 = "Line data                    : " + text_vec[line_no-1];

      if( i < ng )
      {
        ostringstream oss10, oss11;
        oss10 << i+1;
        str_data01 = str_data01 + "P0 scattering (" + oss10.str() + " / " + oss02.str() + ")";
      }
      else if( i == ng ) 
      {
        str_data01 = str_data01 + "Production";
      }
      else if( i == ng+1 ) 
      {
        str_data01 = str_data01 + "Absorption";
      }
      else if( i == ng+2 ) 
      {
        str_data01 = str_data01 + "Total";
      }
      else
      {
        str_data01 = str_data01 + "Fission";
      }

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("");

      if( str_vec[0] == "xsn" || str_vec[0] == "fsp" || str_vec[0] == "asc" )
      {
        err_com.push_back("XSN, FSP, or ASC was found.");
        err_com.push_back("The cross section data read process was interrupted.");
        err_com.push_back("The KRAM data may not correct.");
        err_com.push_back("Please check the KRAM file.");
        err_obj.output_caution(class_name, func_name, err_com);

        line_no--;
        return;
      }

      err_com.push_back("Data number must be equal to multi-group number.");
      err_com.push_back("Please check the KRAM file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }


    if( i < ng ) //P0 scattering
    {
      xs_sc[i].resize(ng);
      for(int j=0; j<ng; j++)
      {
        xs_sc[i][j] = numeric_string_cast<Real>(str_vec[j]);
      }
    }
    else if( i == ng ) //Production
    {
      for(int j=0; j<ng; j++)
      {
        xs_prod[j] = numeric_string_cast<Real>(str_vec[j]);
      }
    }
    else if( i == ng+1 ) //Absorption
    {
      for(int j=0; j<ng; j++)
      {
        xs_abs[j] = numeric_string_cast<Real>(str_vec[j]);
      }
    }
    else if( i == ng+2 ) //Total
    {
      for(int j=0; j<ng; j++)
      {
        xs_tot[j] = numeric_string_cast<Real>(str_vec[j]);
      }
    }
    else //Fission
    {
      for(int j=0; j<ng; j++)
      {
        xs_fis[j] = numeric_string_cast<Real>(str_vec[j]);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> KramXsnData::write_data()
{
  vector<string> text;
  text.clear();

  if( ng==0 )
  {
    return text;
  }

  ostringstream oss_mat;
  oss_mat << mat_no;
  string str_data = " XSN " + oss_mat.str();
  text.push_back(str_data);
  str_data.clear();

  //P0 scattering
  for(int i=0; i<ng; i++)
  {
    for(int j=0; j<static_cast<int>(xs_sc[i].size()); j++)
    {
      ostringstream oss_data;
      oss_data << scientific << setprecision(6) << setw(15) << xs_sc[i][j];
      str_data = str_data + oss_data.str();
    }
    text.push_back(str_data);
    str_data.clear();
  }

  //Production
  for(int i=0; i<ng; i++)
  {
    ostringstream oss_data;
    oss_data << scientific << setprecision(6) << setw(15) << xs_prod[i];
    str_data = str_data + oss_data.str();
  }
  text.push_back(str_data);
  str_data.clear();

  //Absorption
  for(int i=0; i<ng; i++)
  {
    ostringstream oss_data;
    oss_data << scientific << setprecision(6) << setw(15) << xs_abs[i];
    str_data = str_data + oss_data.str();
  }
  text.push_back(str_data);
  str_data.clear();

  //Total
  for(int i=0; i<ng; i++)
  {
    ostringstream oss_data;
    oss_data << scientific << setprecision(6) << setw(15) << xs_tot[i];
    str_data = str_data + oss_data.str();
  }
  text.push_back(str_data);
  str_data.clear();

  //Fission
  for(int i=0; i<ng; i++)
  {
    ostringstream oss_data;
    oss_data << scientific << setprecision(6) << setw(15) << xs_fis[i];
    str_data = str_data + oss_data.str();
  }
  text.push_back(str_data);
  str_data.clear();

  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool KramXsnData::isFissile()
{
  int fis_no = 0;
  for(int i=0; i<ng; i++)
  {
    if( fabs(xs_prod[i]) > min_value )
    {
      fis_no++;
    }

    if( fabs(xs_fis[i]) > min_value )
    {
      fis_no++;
    }

    if( fis_no > 0 )
    {
      break;
    }
  }

  if( fis_no > 0 )
  {
    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void KramXsnData::set_mat_no(int int_data)
{
  mat_no = int_data;
}

void KramXsnData::set_ng(int int_data)
{
  if( int_data > 0 )
  {
    ng = int_data;
  }

  if( static_cast<int>(xs_sc.size()) == 0 )
  {
    xs_sc.resize(ng);
    for(int i=0; i<ng; i++)
    {
      xs_sc[i].resize(ng);
      for(int j=0; j<ng; j++)
      {
        xs_sc[i][j] = 0.0;
      }
    }
  }

  if( static_cast<int>(xs_prod.size()) == 0 )
  {
    xs_prod.resize(ng);
    for(int i=0; i<ng; i++)
    {
      xs_prod[i] = 0.0;
    }
  }

  if( static_cast<int>(xs_abs.size()) == 0 )
  {
    xs_abs.resize(ng);
    for(int i=0; i<ng; i++)
    {
      xs_abs[i] = 0.0;
    }
  }

  if( static_cast<int>(xs_fis.size()) == 0 )
  {
    xs_fis.resize(ng);
    for(int i=0; i<ng; i++)
    {
      xs_fis[i] = 0.0;
    }
  }

  if( static_cast<int>(xs_tot.size()) == 0 )
  {
    xs_tot.resize(ng);
    for(int i=0; i<ng; i++)
    {
      xs_tot[i] = 0.0;
    }
  }

  if( static_cast<int>(xs_sc.size())   != ng ||
      static_cast<int>(xs_prod.size()) != ng ||
      static_cast<int>(xs_abs.size())  != ng ||
      static_cast<int>(xs_fis.size())  != ng ||
      static_cast<int>(xs_tot.size())  != ng )
  {
    string class_name = "KramXsnData";
    string func_name  = "set_ng(int int_data)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << ng;
    oss02 << static_cast<int>(xs_sc.size());
    oss03 << static_cast<int>(xs_prod.size());
    oss04 << static_cast<int>(xs_abs.size());
    oss05 << static_cast<int>(xs_fis.size());
    oss06 << static_cast<int>(xs_tot.size());

    string str_data01 = "ng                            : " + oss01.str();
    string str_data02 = "Energy grid number of xs_sc   : " + oss02.str();
    string str_data03 = "Energy grid number of xs_prod : " + oss03.str();
    string str_data04 = "Energy grid number of xs_abs  : " + oss04.str();
    string str_data05 = "Energy grid number of xs_fis  : " + oss05.str();
    string str_data06 = "Energy grid number of xs_tot  : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);

    err_com.push_back("ng is different to the energy grid of xs");
    err_com.push_back("Please check the KRAM file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramXsnData::set_xs_sc(vector<vector<Real> > xs_vec)
{
  xs_sc = xs_vec;

  if( static_cast<int>(xs_sc.size()) != ng )
  {
    set_ng(static_cast<int>(xs_sc.size()));
  }
}

void KramXsnData::set_xs_prod(vector<Real> xs_vec)
{
  xs_prod = xs_vec;

  if( static_cast<int>(xs_prod.size()) != ng )
  {
    set_ng(static_cast<int>(xs_prod.size()));
  }
}

void KramXsnData::set_xs_abs(vector<Real> xs_vec)
{
  xs_abs = xs_vec;

  if( static_cast<int>(xs_abs.size()) != ng )
  {
    set_ng(static_cast<int>(xs_abs.size()));
  }
}

void KramXsnData::set_xs_fis(vector<Real> xs_vec)
{
  xs_fis = xs_vec;

  if( static_cast<int>(xs_fis.size()) != ng )
  {
    set_ng(static_cast<int>(xs_fis.size()));
  }
}

void KramXsnData::set_xs_tot(vector<Real> xs_vec)
{
  xs_tot = xs_vec;

  if( static_cast<int>(xs_tot.size()) != ng )
  {
    set_ng(static_cast<int>(xs_tot.size()));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramXsnData::set_xs_sc_from_gendf(vector<vector<Real> > xs_vec)
{
  KramUtils kram_util_obj;
  xs_sc = kram_util_obj.reverse_mg_array(xs_vec);

  if( static_cast<int>(xs_sc.size()) != ng )
  {
    set_ng(static_cast<int>(xs_sc.size()));
  }
}

void KramXsnData::set_xs_prod_from_gendf(vector<Real> xs_vec)
{
  KramUtils kram_util_obj;
  xs_prod = kram_util_obj.reverse_mg_vec(xs_vec);

  if( static_cast<int>(xs_prod.size()) != ng )
  {
    set_ng(static_cast<int>(xs_prod.size()));
  }
}

void KramXsnData::set_xs_abs_from_gendf(vector<Real> xs_vec)
{
  KramUtils kram_util_obj;
  xs_abs = kram_util_obj.reverse_mg_vec(xs_vec);

  if( static_cast<int>(xs_abs.size()) != ng )
  {
    set_ng(static_cast<int>(xs_abs.size()));
  }
}

void KramXsnData::set_xs_fis_from_gendf(vector<Real> xs_vec)
{
  KramUtils kram_util_obj;
  xs_fis = kram_util_obj.reverse_mg_vec(xs_vec);

  if( static_cast<int>(xs_fis.size()) != ng )
  {
    set_ng(static_cast<int>(xs_fis.size()));
  }
}

void KramXsnData::set_xs_tot_from_gendf(vector<Real> xs_vec)
{
  KramUtils kram_util_obj;
  xs_tot = kram_util_obj.reverse_mg_vec(xs_vec);

  if( static_cast<int>(xs_tot.size()) != ng )
  {
    set_ng(static_cast<int>(xs_tot.size()));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter

int KramXsnData::get_mat_no()
{
  return mat_no;
}

int KramXsnData::get_ng()
{
  return ng;
}


vector<vector<Real> > KramXsnData::get_xs_sc()
{
  return xs_sc;
}

vector<Real> KramXsnData::get_xs_prod()
{
  return xs_prod;
}

vector<Real> KramXsnData::get_xs_abs()
{
  return xs_abs;
}

vector<Real> KramXsnData::get_xs_fis()
{
  return xs_fis;
}

vector<Real> KramXsnData::get_xs_tot()
{
  return xs_tot;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

// ***** KramFspData ***** //

//constructor
KramFspData::KramFspData(void)
{
  clear();
}

//destructor
KramFspData::~KramFspData(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramFspData::clear()
{
  ng     = 0;
  mat_no = unassigned_mat_no;

  fsp.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramFspData::read_data(vector<string>& text_vec, int mg_no)
{
  int line_no = 0;
  read_data(text_vec, line_no, mg_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramFspData::read_data(vector<string>& text_vec, int& line_no, int mg_no)
{
  clear();

  if( line_no >= static_cast<int>(text_vec.size()) )
  {
    return;
  }

  StringUtils str_obj;
  vector<string> str_vec;

  int str_no = 0;
  while( str_no == 0 )
  {
    str_vec = str_obj.read_data(text_vec, line_no, str_no);
  }

  transform(str_vec[0].begin(), str_vec[0].end(), str_vec[0].begin(), ::tolower);
  if( str_vec[0] != "fsp" || str_no == 1 )
  {
    if( str_vec[0] == "xsn" || str_vec[0] == "asc" )
    {
      line_no--;
      return;
    }

    string class_name = "KramFspData";
    string func_name  = "read_data(vector<string>& text_vec, int& line_no)";

    ostringstream oss01, oss02;
    oss01 << line_no;
    oss02 << static_cast<int>(text_vec.size());

    string str_data01 = "Line number : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "Line data   : " + text_vec[line_no-1];

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);

    if( str_vec[0] != "fsp" )
    {
      err_com.push_back("FSP is not found in this text data.");
      err_com.push_back("Please check the KRAM file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    else //if( str_no == 1 )
    {
      err_com.push_back("There is not material number.");
      err_com.push_back("The material number is set as 1.");
      err_obj.output_caution(class_name, func_name, err_com);

      mat_no = 1;
    }
  }
  else
  {
    mat_no = numeric_string_cast<int>(str_vec[1]);
  }

  ng = mg_no;
  fsp.resize(ng);
  for(int i=0; i<ng; i++)
  {
    fsp[i] = 0.0;
  }

  str_no = 0;
  while( str_no == 0 )
  {
    str_vec = str_obj.read_data(text_vec, line_no, str_no);
  }

  if( str_no != ng )
  {
    string class_name = "KramFspData";
    string func_name  = "read_data(vector<string>& text_vec, int& line_no)";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << str_no;
    oss02 << ng;
    oss03 << line_no;
    oss04 << static_cast<int>(text_vec.size());

    string str_data01 = "Data number in this line     : " + oss01.str();
    string str_data02 = "Multi-group number           : " + oss02.str();
    string str_data03 = "Line number                  : " + oss03.str() + " / " + oss04.str();
    string str_data04 = "Line data                    : " + text_vec[line_no-1];

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("");

    if( str_vec[0] == "xsn" || str_vec[0] == "fsp" || str_vec[0] == "asc" )
    {
      err_com.push_back("XSN, FSP, or ASC was found.");
      err_com.push_back("The fission spectrum data read process was interrupted.");
      err_com.push_back("The KRAM data may not correct.");
      err_com.push_back("Please check the KRAM file.");
      err_obj.output_caution(class_name, func_name, err_com);

      line_no--;
      return;
    }

    err_com.push_back("Data number must be equal to multi-group number.");
    err_com.push_back("Please check the KRAM file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }


  for(int i=0; i<ng; i++)
  {
    fsp[i] = numeric_string_cast<Real>(str_vec[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> KramFspData::write_data()
{
  vector<string> text;
  text.clear();

  if( ng==0 )
  {
    return text;
  }

  ostringstream oss_mat;
  oss_mat << mat_no;
  string str_data = " FSP " + oss_mat.str();
  text.push_back(str_data);
  str_data.clear();

  for(int i=0; i<ng; i++)
  {
    ostringstream oss_data;
    oss_data << scientific << setprecision(6) << setw(15) << fsp[i];
    str_data = str_data + oss_data.str();
  }
  text.push_back(str_data);
  str_data.clear();

  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool KramFspData::isFissile()
{
  int fis_no = 0;
  for(int i=0; i<ng; i++)
  {
    if( fabs(fsp[i]) > min_value )
    {
      fis_no++;
      break;
    }
  }

  if( fis_no > 0 )
  {
    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void KramFspData::set_mat_no(int int_data)
{
  mat_no = int_data;
}

void KramFspData::set_ng(int int_data)
{
  ng = int_data;

  if( static_cast<int>(fsp.size()) == 0 )
  {
    fsp.resize(ng);
    for(int i=0; i<ng; i++)
    {
      fsp[i] = 0.0;
    }
  }

  if( static_cast<int>(fsp.size()) != ng )
  {
    string class_name = "KramFspData";
    string func_name  = "set_ng(int int_data)";

    ostringstream oss01, oss02;
    oss01 << ng;
    oss02 << static_cast<int>(fsp.size());

    string str_data01 = "ng                        : " + oss01.str();
    string str_data02 = "Energy grid number of fsp : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);

    err_com.push_back("ng is different to the energy grid of fsp");
    err_com.push_back("Please check the KRAM file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

void KramFspData::set_fsp(vector<Real> fsp_vec)
{
  fsp = fsp_vec;

  if( static_cast<int>(fsp.size()) != ng )
  {
    set_ng(static_cast<int>(fsp.size()));
  }
}

void KramFspData::set_fsp_from_gendf(vector<Real> fsp_vec)
{
  KramUtils kram_util_obj;
  fsp = kram_util_obj.reverse_mg_vec(fsp_vec);

  if( static_cast<int>(fsp.size()) != ng )
  {
    set_ng(static_cast<int>(fsp.size()));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter

int KramFspData::get_mat_no()
{
  return mat_no;
}

int KramFspData::get_ng()
{
  return ng;
}

vector<Real> KramFspData::get_fsp()
{
  return fsp;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

// ***** KramAscData ***** //

//constructor
KramAscData::KramAscData(void)
{
  clear();
}

//destructor
KramAscData::~KramAscData(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramAscData::clear()
{
  ng     = 0;
  pl_no  = 0;
  mat_no = unassigned_mat_no;

  clr_obj.clear_vec_array3_real(asc);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramAscData::read_data(vector<string>& text_vec, int mg_no)
{
  int line_no = 0;
  read_data(text_vec, line_no, mg_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramAscData::read_data(vector<string>& text_vec, int& line_no, int mg_no)
{
  clear();

  if( line_no >= static_cast<int>(text_vec.size()) )
  {
    return;
  }

  StringUtils str_obj;
  vector<string> str_vec;

  int str_no = 0;
  while( str_no == 0 )
  {
    str_vec = str_obj.read_data(text_vec, line_no, str_no);
  }

  transform(str_vec[0].begin(), str_vec[0].end(), str_vec[0].begin(), ::tolower);
  if( str_vec[0] != "asc" || str_no == 1 )
  {
    if( str_vec[0] == "xsn" || str_vec[0] == "fsp" )
    {
      line_no--;
      return;
    }

    string class_name = "KramAscData";
    string func_name  = "read_data(vector<string>& text_vec, int& line_no)";

    ostringstream oss01, oss02;
    oss01 << line_no;
    oss02 << static_cast<int>(text_vec.size());

    string str_data01 = "Line number : " + oss01.str() + " / " + oss02.str();
    string str_data02 = "Line data   : " + text_vec[line_no-1];

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);

    if( str_vec[0] != "asc" )
    {
      err_com.push_back("ASC is not found in this text data.");
      err_com.push_back("Please check the KRAM file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    else //if( str_no == 1 )
    {
      err_com.push_back("There is not material number.");
      err_com.push_back("The material number is set as 1.");
      err_obj.output_caution(class_name, func_name, err_com);

      mat_no = 1;
    }
  }
  else
  {
    mat_no = numeric_string_cast<int>(str_vec[1]);
  }

  str_no = 0;
  while( str_no == 0 )
  {
    str_vec = str_obj.read_data(text_vec, line_no, str_no);
  }

  if( str_vec[0] == "xsn" || str_vec[0] == "fsp" || str_vec[0] == "asc" || str_no > 1 )
  {
    string class_name = "KramAscData";
    string func_name  = "read_data(vector<string>& text_vec, int& line_no)";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << str_no;
    oss02 << ng;
    oss03 << line_no;
    oss04 << static_cast<int>(text_vec.size());

    string str_data01 = "Data number in this line     : " + oss01.str();
    string str_data02 = "Multi-group number           : " + oss02.str();
    string str_data03 = "Line number                  : " + oss03.str() + " / " + oss04.str();
    string str_data04 = "Line data                    : " + text_vec[line_no-1];

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("");

    if( str_vec[0] == "xsn" || str_vec[0] == "fsp" || str_vec[0] == "asc" )
    {
      err_com.push_back("XSN, FSP, or ASC was found.");
      err_com.push_back("The angular scattering data read process was interrupted.");
      err_com.push_back("The KRAM data may not correct.");
      err_com.push_back("Please check the KRAM file.");
      err_obj.output_caution(class_name, func_name, err_com);

      line_no--;
      return;
    }
    else //if( str_no > 1 )
    {
      err_com.push_back("The only first data is used for pl_no (number of Lgendres).");
      err_com.push_back("The other data is invalid.");
      err_com.push_back("The KRAM data may not correct.");
      err_com.push_back("Please check the KRAM file.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  pl_no = numeric_string_cast<int>(str_vec[0]);
  asc.resize(pl_no);

  ng = mg_no;
  for(int i=0; i<pl_no; i++)
  {
    asc[i].resize(ng);
    for(int j=0; j<ng; j++)
    {
      str_no = 0;
      while( str_no == 0 )
      {
        str_vec = str_obj.read_data(text_vec, line_no, str_no);
      }

      if( str_no != ng )
      {
        string class_name = "KramAscData";
        string func_name  = "read_data(vector<string>& text_vec, int& line_no)";

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
        oss01 << i+1;
        oss02 << pl_no;
        oss03 << j+1;
        oss04 << ng;
        oss05 << str_no;
        oss06 << line_no;
        oss07 << static_cast<int>(text_vec.size());

        string str_data01 = "Pl number (Legendre number)  : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "Ein number                   : " + oss03.str() + " / " + oss04.str();
        string str_data03 = "Data number in this line     : " + oss05.str();
        string str_data04 = "Line number                  : " + oss06.str() + " / " + oss07.str();
        string str_data05 = "Line data                    : " + text_vec[line_no-1];

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back("");

        if( str_vec[0] == "xsn" || str_vec[0] == "fsp" || str_vec[0] == "asc" )
        {
          err_com.push_back("XSN, FSP, or ASC was found.");
          err_com.push_back("The angular scattering data read process was interrupted.");
          err_com.push_back("The KRAM data may not correct.");
          err_com.push_back("Please check the KRAM file.");
          err_obj.output_caution(class_name, func_name, err_com);

          line_no--;
          return;
        }

        err_com.push_back("Data number must be equal to multi-group number.");
        err_com.push_back("Please check the KRAM file.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      asc[i][j].resize(ng);
      for(int k=0; k<ng; k++)
      {
        asc[i][j][k] = numeric_string_cast<Real>(str_vec[k]);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> KramAscData::write_data()
{
  vector<string> text;
  text.clear();

  if( ng==0 )
  {
    return text;
  }

  ostringstream oss_mat, oss_pl;
  oss_mat << mat_no;
  string str_data = " ASC " + oss_mat.str();
  text.push_back(str_data);
  str_data.clear();

  oss_pl << setw(10) << pl_no;
  str_data = oss_pl.str();
  text.push_back(str_data);
  str_data.clear();
  

  for(int i=0; i<pl_no; i++)
  {
    for(int j=0; j<static_cast<int>(asc[i].size()); j++)
    {
      for(int k=0; k<static_cast<int>(asc[i][j].size()); k++)
      {
        ostringstream oss_data;
        oss_data << scientific << setprecision(6) << setw(15) << asc[i][j][k];
        str_data = str_data + oss_data.str();
      }
      text.push_back(str_data);
      str_data.clear();
    }
  }

  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void KramAscData::set_mat_no(int int_data)
{
  mat_no = int_data;
}

void KramAscData::set_ng(int int_data)
{
  ng = int_data;

  for(int i=0; i<static_cast<int>(asc.size()); i++)
  {
    if( static_cast<int>(asc[i].size()) == 0 )
    {
      for(int i=0; i<static_cast<int>(asc.size()); i++)
      {
        asc[i].resize(ng);
        for(int j=0; j<ng; j++)
        {
          asc[i][j].resize(ng);
          for(int k=0; k<ng; k++)
          {
            asc[i][j][k] = 0.0;
          }
        }
      }
    }

    if( static_cast<int>(asc[i].size()) != ng )
    {
      string class_name = "KramAscData";
      string func_name  = "set_ng(int int_data)";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << static_cast<int>(asc.size());
      oss03 << ng;
      oss04 << static_cast<int>(asc[i].size());

      string str_data01 = "Position (Pl number)         : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "ng                           : " + oss03.str();
      string str_data03 = "Energy grid number of asc[i] : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);

      err_com.push_back("ng is different to the energy grid of fsp");
      err_com.push_back("Please check the KRAM file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

void KramAscData::set_pl_no(int int_data)
{
  pl_no = int_data;

  asc.resize(pl_no);
  for(int i=0; i<pl_no; i++)
  {
    asc[i].resize(ng);
  }
}

void KramAscData::set_asc(vector<vector<vector<Real> > > xs_vec)
{
  asc = xs_vec;

  pl_no = static_cast<int>(asc.size());
  ng    = 0;
  for(int i=0; i<pl_no; i++)
  {
    if( static_cast<int>(asc[i].size()) > 0 )
    {
      ng = static_cast<int>(asc[i].size());
      break;
    }
  }
}

void KramAscData::set_asc_from_gendf(vector<vector<vector<Real> > > xs_vec)
{
  pl_no = static_cast<int>(xs_vec.size());
  asc.resize(pl_no);

  KramUtils kram_util_obj;
  for(int i=0; i<pl_no; i++)
  {
    asc[i] = kram_util_obj.reverse_mg_array(xs_vec[i]);
  }

  ng    = 0;
  for(int i=0; i<pl_no; i++)
  {
    if( static_cast<int>(asc[i].size()) > 0 )
    {
      ng = static_cast<int>(asc[i].size());
      break;
    }
  }
}

void KramAscData::set_asc(vector<vector<Real> > xs_vec, int pl_no_val)
{
  if( pl_no < pl_no_val )
  {
    pl_no = pl_no_val;
    asc.resize(pl_no_val);
  }

  int ng_new = static_cast<int>(xs_vec.size());
  if( ng != ng_new )
  {
    string class_name = "KramAscData";
    string func_name  = "set_asc(vector<vector<Real> > xs_vec, int pl_no_val)";

    ostringstream oss01, oss02, oss03;
    oss01 << pl_no_val;
    oss02 << ng;
    oss03 << ng_new;

    string str_data01 = "Pl number (Legendre number)  : " + oss01.str();
    string str_data02 = "Ein number (ng)              : " + oss02.str();
    string str_data03 = "Ein number (xs_vec.size())   : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("");
    err_com.push_back("The multi-group energy grid number is different.");
    err_com.push_back("Please check the KRAM file or cross section data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  asc[pl_no_val-1] = xs_vec;
}

void KramAscData::set_asc_from_gendf(vector<vector<Real> > xs_vec, int pl_no_val)
{
  KramUtils kram_util_obj;
  xs_vec = kram_util_obj.reverse_mg_array(xs_vec);

  set_asc(xs_vec, pl_no_val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter

int KramAscData::get_mat_no()
{
  return mat_no;
}

int KramAscData::get_ng()
{
  return ng;
}

int KramAscData::get_pl_no()
{
  return pl_no;
}


vector<vector<vector<Real> > > KramAscData::get_asc()
{
  return asc;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

// ***** KramCommonData ***** //

//constructor
KramCommonData::KramCommonData(void)
{
  clear();
}

//destructor
KramCommonData::~KramCommonData(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCommonData::clear()
{
  vector<KramXsnData>().swap(xsn_vec);
  vector<KramFspData>().swap(fsp_vec);
  vector<KramAscData>().swap(asc_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCommonData::read_xsn_data(vector<string>& text_vec, int& line_no, int mg_no)
{
  KramXsnData xsn_obj;

  int line_no_pre = line_no;
  xsn_obj.read_data(text_vec, line_no, mg_no);

  if( line_no == line_no_pre )
  {
    return;
  }

  xsn_vec.push_back(xsn_obj);

  if( xsn_obj.get_ng() != get_ng() && xsn_obj.get_ng() != 0 && get_ng() != 0 )
  {
    string class_name = "KramCommonData";
    string func_name  = "read_xsn_data(vector<string>& text_vec, int& line_no, int mg_no)";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << line_no_pre;
    oss02 << get_ng();
    oss03 << xsn_obj.get_ng();
    oss04 << xsn_obj.get_mat_no();

    string str_data01 = "Line number (top of this data)         : " + oss01.str();
    string str_data02 = "Mulgi-group grid number (ng)           : " + oss02.str();
    string str_data03 = "Mulgi-group grid number (new XSN file) : " + oss03.str();
    string str_data04 = "Mat number (new XSN file)              : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("");
    err_com.push_back("The multi-group grid number is different.");
    err_com.push_back("Please check the KRAM file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  xsn_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCommonData::read_fsp_data(vector<string>& text_vec, int& line_no, int mg_no)
{
  KramFspData fsp_obj;

  int line_no_pre = line_no;
  fsp_obj.read_data(text_vec, line_no, mg_no);

  if( line_no == line_no_pre )
  {
    return;
  }

  fsp_vec.push_back(fsp_obj);

  if( fsp_obj.get_ng() != get_ng() && fsp_obj.get_ng() != 0 && get_ng() != 0 )
  {
    string class_name = "KramCommonData";
    string func_name  = "read_fsp_data(vector<string>& text_vec, int& line_no, int mg_no)";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << line_no_pre;
    oss02 << get_ng();
    oss03 << fsp_obj.get_ng();
    oss04 << fsp_obj.get_mat_no();

    string str_data01 = "Line number (top of this data)         : " + oss01.str();
    string str_data02 = "Mulgi-group grid number (ng)           : " + oss02.str();
    string str_data03 = "Mulgi-group grid number (new FSP file) : " + oss03.str();
    string str_data04 = "Mat number (new FSP file)              : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("");
    err_com.push_back("The multi-group grid number is different.");
    err_com.push_back("Please check the KRAM file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  fsp_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCommonData::read_asc_data(vector<string>& text_vec, int& line_no, int mg_no)
{
  KramAscData asc_obj;

  int line_no_pre = line_no;
  asc_obj.read_data(text_vec, line_no, mg_no);

  if( line_no == line_no_pre )
  {
    return;
  }

  asc_vec.push_back(asc_obj);

  if( asc_obj.get_ng() != get_ng() && asc_obj.get_ng() != 0 && get_ng() != 0 )
  {
    string class_name = "KramCommonData";
    string func_name  = "read_asc_data(vector<string>& text_vec, int& line_no, int mg_no)";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << line_no_pre;
    oss02 << get_ng();
    oss03 << asc_obj.get_ng();
    oss04 << asc_obj.get_mat_no();

    string str_data01 = "Line number (top of this data)         : " + oss01.str();
    string str_data02 = "Mulgi-group grid number (ng)           : " + oss02.str();
    string str_data03 = "Mulgi-group grid number (new ASC file) : " + oss03.str();
    string str_data04 = "Mat number (new ASC file)              : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back("");
    err_com.push_back("The multi-group grid number is different.");
    err_com.push_back("Please check the KRAM file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  asc_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCommonData::read_data(vector<string>& text_vec, int mg_no)
{
  int line_no = 0;
  read_data(text_vec, line_no, mg_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCommonData::read_data(vector<string>& text_vec, int& line_no, int mg_no)
{
  clear();

  int line_no_pre = -1;
  while( line_no != line_no_pre )
  {
    line_no_pre = line_no;

    read_xsn_data(text_vec, line_no, mg_no);
    read_fsp_data(text_vec, line_no, mg_no);
    read_asc_data(text_vec, line_no, mg_no);

    if( line_no >= static_cast<int>(text_vec.size()) )
    {
      break;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> KramCommonData::write_data()
{
  vector<string> text_all;
  text_all.clear();

  vector<int> mat_list = get_mat_list();

  int i_max = static_cast<int>(mat_list.size());
  for(int i=0; i<i_max; i++)
  {
    //For XSN
    KramXsnData xsn_data = get_xsn(mat_list[i]);
    if( xsn_data.get_mat_no() != unassigned_mat_no && xsn_data.get_ng() != 0 )
    {
      vector<string> text_each = xsn_data.write_data();

      for(int j=0; j<static_cast<int>(text_each.size()); j++)
      {
        text_all.push_back(text_each[j]);
      }
      text_each.clear();
    }
    xsn_data.clear();

    //For FSP
    KramFspData fsp_data = get_fsp(mat_list[i]);
    if( fsp_data.get_mat_no() != unassigned_mat_no && fsp_data.get_ng() != 0 )
    {
      vector<string> text_each = fsp_data.write_data();

      for(int j=0; j<static_cast<int>(text_each.size()); j++)
      {
        text_all.push_back(text_each[j]);
      }
      text_each.clear();
    }
    fsp_data.clear();

    //For ASC
    KramAscData asc_data = get_asc(mat_list[i]);
    if( asc_data.get_mat_no() != unassigned_mat_no && asc_data.get_ng() != 0 )
    {
      vector<string> text_each = asc_data.write_data();

      for(int j=0; j<static_cast<int>(text_each.size()); j++)
      {
        text_all.push_back(text_each[j]);
      }
      text_each.clear();
    }
    asc_data.clear();
  }

  return text_all;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCommonData::set_xsn(KramXsnData xsn_data)
{
  int ng = get_ng();
  if( ng != 0 && ng != xsn_data.get_ng() )
  {
    string class_name = "KramCommonData";
    string func_name  = "set_xsn(KramXsnData xsn_data)";

    ostringstream oss01, oss02, oss03;
    oss01 << ng;
    oss02 << xsn_data.get_ng();
    oss03 << xsn_data.get_mat_no();

    string str_data01 = "Mulgi-group grid number (ng)           : " + oss01.str();
    string str_data02 = "Mulgi-group grid number (new XSN data) : " + oss02.str();
    string str_data03 = "Mat number (new XSN data)              : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);

    err_com.push_back("Multi-group grid number is different.");
    err_com.push_back("Please check new XSN data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int mod_flg = 0;
  int mat_new = xsn_data.get_mat_no();
  for(int i=0; i<static_cast<int>(xsn_vec.size()); i++)
  {
    if( xsn_vec[i].get_mat_no() == mat_new )
    {
      mod_flg    = 1;
      xsn_vec[i] = xsn_data;
      break;
    }
  }

  if( mod_flg == 0 )
  {
    xsn_vec.push_back(xsn_data);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCommonData::set_fsp(KramFspData fsp_data)
{
  int ng = get_ng();
  if( ng != 0 && ng != fsp_data.get_ng() )
  {
    string class_name = "KramCommonData";
    string func_name  = "set_fsp(KramFspData fsp_data)";

    ostringstream oss01, oss02, oss03;
    oss01 << ng;
    oss02 << fsp_data.get_ng();
    oss03 << fsp_data.get_mat_no();

    string str_data01 = "Mulgi-group grid number (ng)           : " + oss01.str();
    string str_data02 = "Mulgi-group grid number (new FSP data) : " + oss02.str();
    string str_data03 = "Mat number (new FSP data)              : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);

    if( fsp_data.get_ng() != 0 )
    {
      err_com.push_back("Multi-group grid number is different.");
      err_com.push_back("Please check new FSP data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    else
    {
      err_com.push_back("The all fsp data is set 0.0.");
      err_obj.output_caution(class_name, func_name, err_com);

      vector<Real> fsp_new;
      fsp_new.resize(ng);
      for(int i=0; i<ng; i++)
      {
        fsp_new[i] = 0.0;
      }
      fsp_data.set_fsp(fsp_new);
    }
  }

  int mod_flg = 0;
  int mat_new = fsp_data.get_mat_no();
  for(int i=0; i<static_cast<int>(fsp_vec.size()); i++)
  {
    if( fsp_vec[i].get_mat_no() == mat_new )
    {
      mod_flg    = 1;
      fsp_vec[i] = fsp_data;
      break;
    }
  }

  if( mod_flg == 0 )
  {
    fsp_vec.push_back(fsp_data);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCommonData::set_asc(KramAscData asc_data)
{
  int ng = get_ng();
  if( ng != 0 && ng != asc_data.get_ng() )
  {
    string class_name = "KramCommonData";
    string func_name  = "set_asc(KramAscData asc_data)";

    ostringstream oss01, oss02, oss03;
    oss01 << ng;
    oss02 << asc_data.get_ng();
    oss03 << asc_data.get_mat_no();

    string str_data01 = "Mulgi-group grid number (ng)           : " + oss01.str();
    string str_data02 = "Mulgi-group grid number (new ASC data) : " + oss02.str();
    string str_data03 = "Mat number (new ASC data)              : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);

    err_com.push_back("Multi-group grid number is different.");
    err_com.push_back("Please check new ASC data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int mod_flg = 0;
  int mat_new = asc_data.get_mat_no();
  for(int i=0; i<static_cast<int>(asc_vec.size()); i++)
  {
    if( asc_vec[i].get_mat_no() == mat_new )
    {
      mod_flg    = 1;
      asc_vec[i] = asc_data;
      break;
    }
  }

  if( mod_flg == 0 )
  {
    asc_vec.push_back(asc_data);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCommonData::set_xsn_vec(vector<KramXsnData> xsn_data)
{
  for(int i=0; i<static_cast<int>(xsn_data.size()); i++)
  {
    set_xsn(xsn_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCommonData::set_fsp_vec(vector<KramFspData> fsp_data)
{
  for(int i=0; i<static_cast<int>(fsp_data.size()); i++)
  {
    set_fsp(fsp_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCommonData::set_asc_vec(vector<KramAscData> asc_data)
{
  for(int i=0; i<static_cast<int>(asc_data.size()); i++)
  {
    set_asc(asc_data[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
int KramCommonData::get_ng()
{
  int ng = 0;
  for(int i=0; static_cast<int>(xsn_vec.size()); i++)
  {
    ng = xsn_vec[i].get_ng();
    if( ng > 0 )
    {
      return ng;
    }
  }

  for(int i=0; static_cast<int>(fsp_vec.size()); i++)
  {
    ng = fsp_vec[i].get_ng();
    if( ng > 0 )
    {
      return ng;
    }
  }

  for(int i=0; static_cast<int>(asc_vec.size()); i++)
  {
    ng = asc_vec[i].get_ng();
    if( ng > 0 )
    {
      return ng;
    }
  }

  return ng;
}

vector<int> KramCommonData::get_mat_list()
{
  vector<Real> mat_list_real;
  vector<int>  mat_list;
  mat_list = get_mat_list_xsn();
  for(int i=0; i<static_cast<int>(mat_list.size()); i++)
  {
    mat_list_real.push_back(static_cast<Real>(mat_list[i]));
  }

  mat_list = get_mat_list_fsp();
  for(int i=0; i<static_cast<int>(mat_list.size()); i++)
  {
    mat_list_real.push_back(static_cast<Real>(mat_list[i]));
  }

  mat_list = get_mat_list_asc();
  for(int i=0; i<static_cast<int>(mat_list.size()); i++)
  {
    mat_list_real.push_back(static_cast<Real>(mat_list[i]));
  }
  mat_list.clear();

  TabAdjuster ta_obj;
  ta_obj.delete_overlap_grid(mat_list_real);

  int i_max = static_cast<int>(mat_list_real.size());
  mat_list.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    mat_list[i] = static_cast<int>(round(mat_list_real[i]));
  }

  return mat_list;
}

vector<int> KramCommonData::get_mat_list_xsn()
{
  int i_max = xsn_vec.size();

  vector<int>  mat_list;
  mat_list.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    mat_list[i] = xsn_vec[i].get_mat_no();
  }

  return mat_list;
}

vector<int> KramCommonData::get_mat_list_fsp()
{
  int i_max = fsp_vec.size();

  vector<int>  mat_list;
  mat_list.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    mat_list[i] = fsp_vec[i].get_mat_no();
  }

  return mat_list;
}

vector<int> KramCommonData::get_mat_list_asc()
{
  int i_max = asc_vec.size();

  vector<int>  mat_list;
  mat_list.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    mat_list[i] = asc_vec[i].get_mat_no();
  }

  return mat_list;
}

vector<KramXsnData> KramCommonData::get_xsn_vec()
{
  return xsn_vec;
}

vector<KramFspData> KramCommonData::get_fsp_vec()
{
  return fsp_vec;
}

vector<KramAscData> KramCommonData::get_asc_vec()
{
  return asc_vec;
}

KramXsnData KramCommonData::get_xsn(int mat_no)
{
  KramXsnData xsn_data;
  xsn_data.clear();

  for(int i=0; i<static_cast<int>(xsn_vec.size()); i++)
  {
    if( xsn_vec[i].get_mat_no() == mat_no )
    {
      xsn_data = xsn_vec[i];
      break;
    }
  }

  return xsn_data;
}

KramFspData KramCommonData::get_fsp(int mat_no)
{
  KramFspData fsp_data;
  fsp_data.clear();

  for(int i=0; i<static_cast<int>(fsp_vec.size()); i++)
  {
    if( fsp_vec[i].get_mat_no() == mat_no )
    {
      fsp_data = fsp_vec[i];
      break;
    }
  }

  return fsp_data;
}

KramAscData KramCommonData::get_asc(int mat_no)
{
  KramAscData asc_data;
  asc_data.clear();

  for(int i=0; i<static_cast<int>(asc_vec.size()); i++)
  {
    if( asc_vec[i].get_mat_no() == mat_no )
    {
      asc_data = asc_vec[i];
      break;
    }
  }

  return asc_data;
}

