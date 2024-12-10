#include "EndfUtils/MFxxMTyyyParser/MF02MT153Parser.hpp"

using namespace frendy;

//constructor
MF02MT153Parser::MF02MT153Parser(void)
{
  clear();

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MF02MT153Parser::~MF02MT153Parser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT153Parser::store_data() 
{
  MultiParser mp_obj;

  //Text file data check
  if( static_cast<Integer>(text.size()) < 2 )
  {
    string class_name = "MF02MT153Parser";
    string func_name  = "store_data()";

    ostringstream oss;
    oss << static_cast<Integer>(text.size());
    string str_data = "Text line number : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The text line number is not appropriate for  MF=02, MT=153.");
    err_com.push_back("The text line number should be larger than 1.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check MT and MF number
  if( mp_obj.check_mf_mt(text, mf_no, mt_no) != 0)
  {
    string class_name = "MF02MT153Parser";
    string func_name  = "store_data()";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "Text data at first line : " + text[0];
    string str_data02 = "File number (MF)        : " + oss01.str();
    string str_data03 = "Section number (MT)     : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The MF and MT numbers are different to MF=02, MT=153.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  mp_obj.get_mat(text, mat_no);

  int     line_no = 0;

  //Line No.01
  //ZA, AWR and INT
  mp_obj.read_head(text, line_no, ZAR, AWR, INEL, ABSO, INT, NBIN);

  vector<Real>    e_vec, r_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  //Line No.02
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3],
                   e_vec);
  TEMP  = r_vec[0];
  LSSF  = i_vec[0];
  ICOMP = i_vec[1];
  NUNR  = i_vec[3];

  if( i_vec[2] == (1+6*NBIN)*NUNR )
  {
    int ene_max = static_cast<int>(NUNR);
    int bin_max = static_cast<int>(NBIN);
    ENE.resize(ene_max);
    HEAT.resize(ene_max);
    P_COUNT.resize(ene_max);
    P_TABLE.resize(ene_max);

    int ele_no = 0;
    for(int i=0; i<ene_max; i++)
    {
      ENE[i] = e_vec[ele_no];
      ele_no++;

      HEAT[i].resize(bin_max);
      P_COUNT[i].resize(bin_max);
      P_TABLE[i].resize(xs_type_no);
      for(int j=0; j<bin_max; j++)
      {
        P_COUNT[i][j] = e_vec[ele_no];
        ele_no++;
      }

      for(int j=0; j<xs_type_no; j++)
      {
        P_TABLE[i][j].resize(bin_max);
        for(int k=0; k<bin_max; k++)
        {
          P_TABLE[i][j][k] = e_vec[ele_no];
          ele_no++;
        }
      }

      for(int j=0; j<bin_max; j++)
      {
        HEAT[i][j] = e_vec[ele_no];
        ele_no++;
      }

      //Check the order of total probability table
      for(int k=1; k<bin_max; k++)
      {
        if( P_TABLE[i][total_xs][k] - P_TABLE[i][total_xs][k-1] < 0.0 )
        {
          string class_name = "MF02MT153Parser";
          string func_name  = "store_data()";

          ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
          oss03.precision(8);
          oss06.precision(8);
          oss07.precision(8);
          oss03.setf(ios::showpoint);
          oss06.setf(ios::showpoint);
          oss07.setf(ios::showpoint);
          oss03.setf(ios::scientific);
          oss06.setf(ios::scientific);
          oss07.setf(ios::scientific);
          oss01 << i+1;
          oss02 << ene_max;
          oss03 << ENE[i];
          oss04 << k+1;
          oss05 << bin_max;
          oss06 << P_TABLE[i][total_xs][k-1];
          oss07 << P_TABLE[i][total_xs][k];
          string str_data01 = "Position of energy           : " + oss01.str() + " / " + oss02.str();
          string str_data02 = "Energy [eV]                  : " + oss03.str();
          string str_data03 = "Position of probability bin  : " + oss04.str() + " / " + oss05.str();
          string str_data04 = "Probability table (total)    : " + oss06.str() + " - " + oss07.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back(str_data04);
          err_com.push_back("The order of the total probability table (average total cross section)");
          err_com.push_back("must be ascending order.");
          err_com.push_back("However, this probability table is not ascending order.");
          err_com.push_back("This probability table may be incorrect.");
          err_com.push_back("");
          err_com.push_back("  Order of total probability table");
          for(int l=0; l<bin_max; l++)
          {
            ostringstream oss11;
            oss11.precision(8);
            oss11.setf(ios::showpoint);
            oss11.setf(ios::scientific);
            oss11 << P_TABLE[i][total_xs][l];
            string str_data11 = "    " + oss11.str();
            if( l == k )
            {
              str_data11 = str_data11 + " ***";
            }
            err_com.push_back(str_data11);
          }

          err_obj.output_caution(class_name, func_name, err_com);
        }
      }
    }
  }
  else
  {
    string class_name = "MF02MT153Parser";
    string func_name  = "store_data()";

    ostringstream oss01, oss02;
    oss01 << i_vec[2];
    oss02 << i_vec[3];
    string str_data01 = "Number of list data : " + oss01.str();
    string str_data02 = "NE                  : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The number of list data is not equal to RECONR mode (1+6*NE) nor");
    err_com.push_back("PURR mode (OPT2+NE*(1+5*OPT2)).");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  r_vec.clear();
  i_vec.clear();
  e_vec.clear();

  mp_obj.line_no_check(text, line_no, mf_no, mt_no);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT153Parser::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  mat_no = unassigned_mat_no;
  ZAR    = 0.0;
  AWR    = 0.0;
  TEMP   = 0.0;
  INT    = 0;
  NBIN   = 0;
  LSSF   = 0;
  ICOMP  = 0;
  NUNR   = 0;
  ENE.clear();
  clr_obj.clear_vec_array2_real8(HEAT);
  clr_obj.clear_vec_array2_real8(P_COUNT);
  clr_obj.clear_vec_array3_real8(P_TABLE);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT153Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF02MT153Parser::get_text()
{
  return text;
}

Integer MF02MT153Parser::get_mat_no()
{
  return mat_no;
}


Real         MF02MT153Parser::get_ZAR()
{
  return ZAR;
}

Real         MF02MT153Parser::get_AWR()
{
  return AWR;
}

Integer      MF02MT153Parser::get_INEL()
{
  return INEL;
}

Integer      MF02MT153Parser::get_ABSO()
{
  return ABSO;
}

Integer      MF02MT153Parser::get_INT()
{
  return INT;
}

Integer      MF02MT153Parser::get_NBIN()
{
  return NBIN;
}


Real         MF02MT153Parser::get_TEMP()
{
  return TEMP;
}

Integer      MF02MT153Parser::get_LSSF()
{
  return LSSF;
}

Integer      MF02MT153Parser::get_ICOMP()
{
  return ICOMP;
}

Integer      MF02MT153Parser::get_NUNR()
{
  return NUNR;
}

vector<Real> MF02MT153Parser::get_ENE()
{
  return ENE;
}

vector<vector<Real> > MF02MT153Parser::get_HEAT()
{
  return HEAT;
}

vector<vector<Real> > MF02MT153Parser::get_P_COUNT()
{
  return P_COUNT;
}

vector<vector<vector<Real> > > MF02MT153Parser::get_P_TABLE()
{
  return P_TABLE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT153Parser::set_mat_no(Integer& int_data)
{
  mat_no = int_data;
}

void MF02MT153Parser::set_ZAR(Real& real_data)
{
  ZAR = real_data;
}

void MF02MT153Parser::set_AWR(Real& real_data)
{
  AWR = real_data;
}

void MF02MT153Parser::set_INEL(Integer& int_data)
{
  INEL = int_data;
}

void MF02MT153Parser::set_ABSO(Integer& int_data)
{
  ABSO = int_data;
}

void MF02MT153Parser::set_INT(Integer& int_data)
{
  INT = int_data;
}

void MF02MT153Parser::set_NBIN(Integer& int_data)
{
  NBIN = int_data;
}


void MF02MT153Parser::set_TEMP(Real& real_data)
{
  TEMP = real_data;
}

void MF02MT153Parser::set_LSSF(Integer& int_data)
{
  LSSF = int_data;
}

void MF02MT153Parser::set_ICOMP(Integer& int_data)
{
  ICOMP = int_data;
}

void MF02MT153Parser::set_NUNR(Integer& int_data)
{
  NUNR = int_data;
}

void MF02MT153Parser::set_ENE(vector<Real>& real_vec)
{
  ENE = real_vec;
}

void MF02MT153Parser::set_HEAT(vector<vector<Real> >& real_vec)
{
  HEAT = real_vec;
}

void MF02MT153Parser::set_P_COUNT(vector<vector<Real> >& real_vec)
{
  P_COUNT = real_vec;
}

void MF02MT153Parser::set_P_TABLE(vector<vector<vector<Real> > >& real_vec)
{
  P_TABLE = real_vec;
}

