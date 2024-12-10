#include "EndfUtils/EndfFileReader/MultiParser.hpp"

using namespace frendy;

//constructor
MultiParser::MultiParser(void)
{
  ndigit_pre = 0;
  char_no    = 0;
  data_no    = 0;
  int_size   = 0;

  err_obj.set_output_mode(err_obj.warning_off);
}

//destructor
MultiParser::~MultiParser(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

const int MultiParser::skip_linearize_tab_data;
const int MultiParser::linearize_tab_data;

int       MultiParser::linearize_tab_flg   = skip_linearize_tab_data;
Real      MultiParser::linearize_tolerance = -1.0;

//////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiParser::read_head(vector<string>& text, int& line_no, 
               Real& C1, Real& C2, Integer& L1, Integer& L2, Integer& N1, Integer& N2)
{
  //StringConverter str_conv;
  vector<Real>    nucl_data;
  nucl_data.clear();

  str_conv.read_line(text[line_no], nucl_data);
  line_no++;

  C1  = nucl_data[0];
  C2  = nucl_data[1];
  L1  = static_cast<Integer>(nucl_data[2]);
  L2  = static_cast<Integer>(nucl_data[3]);
  N1  = static_cast<Integer>(nucl_data[4]);
  N2  = static_cast<Integer>(nucl_data[5]);
  
  nucl_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiParser::read_text(vector<string>& text, int& line_no, string& HL)
{
  HL = text[line_no].substr(0,66);

  line_no++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiParser::read_cont(vector<string>& text, int& line_no,
               Real& C1, Real& C2, Integer& L1, Integer& L2, Integer& N1, Integer& N2)
{
  //StringConverter str_conv;
  vector<Real>    nucl_data;
  nucl_data.clear();

  str_conv.read_line(text[line_no], nucl_data);
  line_no++;

  C1  = nucl_data[0];
  C2  = nucl_data[1];
  L1  = static_cast<Integer>(nucl_data[2]);
  L2  = static_cast<Integer>(nucl_data[3]);
  N1  = static_cast<Integer>(nucl_data[4]);
  N2  = static_cast<Integer>(nucl_data[5]);

  nucl_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiParser::read_cont_real(vector<string>& text, int& line_no,
               Real& C1, Real& C2, Real& L1, Real& L2, Real& N1, Real& N2)
{
  //StringConverter str_conv;
  vector<Real>    nucl_data;
  nucl_data.clear();

  str_conv.read_line(text[line_no], nucl_data);
  line_no++;

  C1  = nucl_data[0];
  C2  = nucl_data[1];
  L1  = nucl_data[2];
  L2  = nucl_data[3];
  N1  = nucl_data[4];
  N2  = nucl_data[5];

  nucl_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiParser::read_list(vector<string>& text, int& line_no, 
               Real& C1, Real& C2, Integer& L1, Integer& L2,
	       Integer& NPL, Integer& N2, vector<Real>& B)
{
  //StringConverter str_conv;
  vector<Real>    nucl_data;

  nucl_data.clear();

  str_conv.read_line(text[line_no], nucl_data);
  line_no++;

  C1  = nucl_data[0];
  C2  = nucl_data[1];
  L1  = static_cast<Integer>(nucl_data[2]);
  L2  = static_cast<Integer>(nucl_data[3]);
  NPL = static_cast<Integer>(nucl_data[4]);
  N2  = static_cast<Integer>(nucl_data[5]);

  int npl = static_cast<int>(NPL);
  B.clear();
  B.resize(npl);
  int ele_no = 0;
  if( npl > 0 )
  {
    for(int i=0; i<npl; i+=6) 
    {
      str_conv.read_line(text[line_no], nucl_data);
      line_no++;

      for(int j=0; j<6; j++)
      {
        if( i+j < npl )
        {
          B[ele_no] = static_cast<Real>(nucl_data[j]);
          ele_no++;
        }
      }
    }
  }
  else
  {
    //Even if NPL = 0, the next line should be read.
    //(See ENDF-6 format Manual at Sec.2.2.1.6 "R-Matrix Limited Format (LRF=7),
    // on the case LBK = 0)
    // Note that this data format is only available for before ENDF/B-VIII.0.
    // ENDF/B-VIII.1 modified LBK data from LIST data to CONT data.
    line_no++; 
  }
  nucl_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiParser::read_tab1(vector<string>& text, int& line_no, 
               Real& C1, Real& C2, Integer& L1, Integer& L2,
	       Integer& NR, Integer& NP, vector<Integer>& NBT, vector<Integer>& INT,
	       vector<Real>& X, vector<Real>& Y)
{
  //StringConverter str_conv;
  vector<Real>    nucl_data;
  nucl_data.clear();

  int line_no_sta = line_no;

  str_conv.read_line(text[line_no], nucl_data);
  line_no++;

  C1  = nucl_data[0];
  C2  = nucl_data[1];
  L1  = static_cast<Integer>(nucl_data[2]);
  L2  = static_cast<Integer>(nucl_data[3]);
  NR  = static_cast<Integer>(nucl_data[4]);
  NP  = static_cast<Integer>(nucl_data[5]);

  //Read INT and NBT
  int nr = static_cast<int>(NR);
  NBT.clear();
  INT.clear();
  NBT.resize(nr);
  INT.resize(nr);
  int ele_no = 0;
  for(int i=0; i<nr; i+=3)
  {
    str_conv.read_line(text[line_no], nucl_data);
    line_no++;
    for(int j=0; j<3; j++)
    {
      if( i+j < nr )
      {
        NBT[ele_no] = static_cast<Integer>(nucl_data[j*2]);
        INT[ele_no] = static_cast<Integer>(nucl_data[j*2+1]);
        ele_no++;
      }
    }
  }

  //Read X and Y
  int np = static_cast<int>(NP);
  X.clear();
  Y.clear();
  X.resize(np);
  Y.resize(np);
  ele_no = 0;

  Real X_pre = 0.0;
  Real Y_pre = 0.0;
  vector<int> remove_element;
  remove_element.clear();
  for(int i=0; i<np; i+=3)
  {
    str_conv.read_line(text[line_no], nucl_data);
    line_no++;
    for(int j=0; j<3; j++)
    {
      if( i+j < np )
      {
        X[ele_no] = nucl_data[j*2];
        Y[ele_no] = nucl_data[j*2+1];

        if( ele_no == 0 )
        {
          X_pre = X[ele_no] * (1.0 - min_ene_dif);
          Y_pre = Y[ele_no];
        }
        else
        {
          if( (X[ele_no] < X_pre) || (Y[ele_no] < min_value || Y[ele_no-1] < min_value) )
          {
            Integer err_type = 0;
            Integer int_val  = ti_obj.search_interpolation_range(NBT, INT, ele_no);
            if( X[ele_no] >= X_pre )
            {
              err_type = 1;
              X_pre = X[ele_no] * (1.0 - min_ene_dif);
              Y_pre = Y[ele_no];
              if( int_val != int_lin_log && int_val != int_log_log )
              {
                ele_no++;
                continue;
              }
            }

            //Output warning message
            vector<Integer> mt_info;
            mt_info.clear();
            str_conv.read_line(text[line_no-1], nucl_data, mt_info);

            string class_name = "MultiParser";
            string func_name;
            func_name   = "read_tab1(vector<string>& text, int& line_no, Real& C1, Real& C2, ";
            func_name  += "Integer& L1, Integer& L2, Integer& NR, Integer& NP, ";
            func_name  += "vector<Integer>& NBT, vector<Integer>& INT, vector<Real>& X, vector<Real>& Y)";

            ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09;
            oss01 << mt_info[0]; //MAT
            oss02 << mt_info[1]; //MF
            oss03 << mt_info[2]; //MT
            oss04 << mt_info[3]; //Line No.
            oss05 << ele_no+1;
            oss06.precision(10);
            oss06.setf(ios::showpoint);
            oss06.setf(ios::scientific);
            oss06 << X_pre / (1.0 - min_ene_dif);
            oss07.precision(10);
            oss07.setf(ios::showpoint);
            oss07.setf(ios::scientific);
            oss07 << Y_pre;
            oss08.precision(10);
            oss08.setf(ios::showpoint);
            oss08.setf(ios::scientific);
            oss08 << X[ele_no];
            oss09.precision(10);
            oss09.setf(ios::showpoint);
            oss09.setf(ios::scientific);
            oss09 << Y[ele_no];
            string str_data01 = "MAT         : " + oss01.str();
            string str_data02 = "MF          : " + oss02.str();
            string str_data03 = "MT          : " + oss03.str();
            string str_data04 = "Line No.    : " + oss04.str();
            string str_data05 = "Element No. : " + oss05.str();
            string str_data06 = "X[i-1]      : " + oss06.str();
            string str_data07 = "Y[i-1]      : " + oss07.str();
            string str_data08 = "X[i]        : " + oss08.str();
            string str_data09 = "Y[i]        : " + oss09.str();

            vector<string> err_com;
            err_com.push_back(str_data01);
            err_com.push_back(str_data02);
            err_com.push_back(str_data03);
            err_com.push_back(str_data04);
            err_com.push_back(str_data05);
            err_com.push_back(str_data06);
            err_com.push_back(str_data07);
            err_com.push_back(str_data08);
            err_com.push_back(str_data09);
            err_com.push_back("");
            err_com.push_back("Error point of ENDF file :");
            err_com.push_back(text[line_no-1]);
            if( (ele_no+1)%3 == 1 )
            {
              err_com.push_back("^^^^^^^^^^^");
            }
            else if( (ele_no+1)%3 == 2 )
            {
              err_com.push_back("                      ^^^^^^^^^^^");
            }
            else if( (ele_no+1)%3 == 0 )
            {
              err_com.push_back("                                            ^^^^^^^^^^^");
            }
            err_com.push_back("");

            if( err_type == 0 )
            {
              err_com.push_back("The order of X data list in Tab1 record is not appropriate (X[i] < X[i-1]).");
              err_com.push_back("This energy grid is removed.");
              err_obj.output_caution(class_name, func_name, err_com);

              remove_element.push_back(ele_no);
            }
            else
            {
              if( int_val == int_lin_log ) 
              {
                err_com.push_back("Though the interpolation type is linear-log, the table data (y value)");
                err_com.push_back("is less than 0.0.");
              }
              else
              {
                err_com.push_back("Though the interpolation type is log-log, the table data (y value)");
                err_com.push_back("is less than 0.0.");
              }
              err_com.push_back("In this case, interpolation result is infinity.");
              err_com.push_back("Please check ENDF file.");
              err_com.push_back("");
              err_com.push_back("Note that FRENDY considers y value is 0 when such data is interpolated.");
              err_com.push_back("(The calculation result may not be appropriate.)");

              if( mt_info[1] != 7 && mt_info[2] != 4 ) //MF != 7 && MT != 4
              {
                err_obj.output_caution(class_name, func_name, err_com);
              }
            }
          }
          else
          {
            X_pre = X[ele_no] * (1.0 - min_ene_dif);
            Y_pre = Y[ele_no];
          }
        }
        ele_no++;
      }
    }
  }

  //Comparing the maximum value of NBT and size of X and Y
  if( NBT[nr-1] != np )
  {
    string class_name = "MultiParser";
    string func_name;
    func_name   = "read_tab1(vector<string>& text, int& line_no, Real& C1, Real& C2, ";
    func_name  += "Integer& L1, Integer& L2, Integer& NR, Integer& NP, ";
    func_name  += "vector<Integer>& NBT, vector<Integer>& INT, vector<Real>& X, vector<Real>& Y)";

    vector<Integer> mt_info;
    mt_info.clear();
    str_conv.read_line(text[line_no_sta], nucl_data, mt_info);

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09;
    oss01 << mt_info[0]; //MAT
    oss02 << mt_info[1]; //MF
    oss03 << mt_info[2]; //MT
    oss04 << mt_info[3]; //Line No.
    oss05 << np;
    oss06 << NBT[nr-1];
    string str_data01 = "MAT                            : " + oss01.str();
    string str_data02 = "MF                             : " + oss02.str();
    string str_data03 = "MT                             : " + oss03.str();
    string str_data04 = "Line No.                       : " + oss04.str();
    string str_data05 = "NP (size of X and Y)           : " + oss05.str();
    string str_data06 = "NBT(nr) (miximum value of NBT) : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back("");
    err_com.push_back("The mazimum value of NBT is not equal to NP.");
    err_com.push_back("This table data may not be appropriate.");
    err_obj.output_caution_format(class_name, func_name, err_com);
  }

  //Remove inappropriate data
  if( static_cast<int>(remove_element.size()) > 0 )
  {
    TabAdjuster ta_obj;
    ta_obj.remove_specified_grid(NBT, INT, X, Y, remove_element);
    NR = static_cast<Integer>(NBT.size());
    NP = static_cast<Integer>(X.size());
  }


  //Check all Y data is zero or not
  int zero_data_flg = 0;
  for(int i=0; i<np; i++)
  {
    if( fabs(Y[i]) > min_value )
    {
      zero_data_flg = 1;
      break;
    }
  }

  if( zero_data_flg == 0 )
  {
    string class_name = "MultiParser";
    string func_name;
    func_name   = "read_tab1(vector<string>& text, int& line_no, Real& C1, Real& C2, ";
    func_name  += "Integer& L1, Integer& L2, Integer& NR, Integer& NP, ";
    func_name  += "vector<Integer>& NBT, vector<Integer>& INT, vector<Real>& X, vector<Real>& Y)";

    vector<Integer> mt_info;
    mt_info.clear();
    str_conv.read_line(text[line_no_sta], nucl_data, mt_info);

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08, oss09;
    oss01 << mt_info[0]; //MAT
    oss02 << mt_info[1]; //MF
    oss03 << mt_info[2]; //MT
    oss04 << mt_info[3]; //Line No.
    oss05 << np;
    string str_data01 = "MAT            : " + oss01.str();
    string str_data02 = "MF             : " + oss02.str();
    string str_data03 = "MT             : " + oss03.str();
    string str_data04 = "Line No.       : " + oss04.str();
    string str_data05 = "Table Data No. : " + oss05.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back("");
    err_com.push_back("Initial line of TAB1 data");
    err_com.push_back(text[line_no_sta]);
    err_com.push_back("");
    err_com.push_back("All Y data is zero.");
    err_com.push_back("This table data may not be appropriate.");
    err_obj.output_caution_format(class_name, func_name, err_com);

    mt_info.clear();
  }
  else
  {
    //Linearization of tab1 data
    if( linearize_tab_flg == linearize_tab_data )
    {
      LinearizeTabData lin_tab_obj;

      if( linearize_tolerance > min_value )
      {
        lin_tab_obj.linearize_tab1_data(NBT, INT, X, Y, linearize_tolerance);
      }
      else
      {
        lin_tab_obj.linearize_tab1_data(NBT, INT, X, Y);
      }
      NR = static_cast<Integer>(NBT.size());
      NP = static_cast<Integer>(X.size());
    }
  }

  nucl_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiParser::read_tab2(vector<string>& text, int& line_no,
               Real& C1, Real& C2, Integer& L1, Integer& L2,
	       Integer& NR, Integer& NZ, vector<Integer>& NBT, vector<Integer>& INT)
{
  //StringConverter str_conv;
  vector<Real>    nucl_data;
  nucl_data.clear();

  str_conv.read_line(text[line_no], nucl_data);
  line_no++;

  C1  = nucl_data[0];
  C2  = nucl_data[1];
  L1  = static_cast<Integer>(nucl_data[2]);
  L2  = static_cast<Integer>(nucl_data[3]);
  NR  = static_cast<Integer>(nucl_data[4]);
  NZ  = static_cast<Integer>(nucl_data[5]);

  int nr = static_cast<int>(NR);
  NBT.clear();
  INT.clear();
  NBT.resize(nr);
  INT.resize(nr);
  int ele_no = 0;
  for(int i=0; i<nr; i+=3)
  {
    str_conv.read_line(text[line_no], nucl_data);
    line_no++;
    for(int j=0; j<3; j++)
    {
      if( i+j < nr )
      {
        NBT[ele_no] = static_cast<Integer>(nucl_data[j*2]);
        INT[ele_no] = static_cast<Integer>(nucl_data[j*2+1]);
        ele_no++;
      }
    }
  }
  nucl_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiParser::read_intg(vector<string>& text, int& line_no, Integer& NDIGIT,
                            Integer& II, Integer& JJ, vector<Integer>& KIJ)
{
  vector<string> buf;
  buf.clear();
  buf.resize(30);

  //Read II and JJ
  buf[0] = text[line_no].substr(0,5);
  buf[1] = text[line_no].substr(5,5);

  //Read KIJ
  check_ndigit(NDIGIT);

  Integer char_tmp = char_no;
  for(int i=2; i<data_no+2; i++)
  {
    buf[i] = text[line_no].substr(char_tmp,int_size);
    char_tmp += int_size;
  }

  //Convert string to numerical number
  //StringConverter str_conv;
  for(int i=0; i<data_no+2; i++)
  {
    str_conv.string_check(buf[i]);
  }

  II = numeric_string_cast<Integer>(buf[0]);
  JJ = numeric_string_cast<Integer>(buf[1]);

  KIJ.clear();
  KIJ.resize(data_no);
  for(int i=2; i<data_no+2; i++)
  {
    KIJ[i-2] = numeric_string_cast<Integer>(buf[i]);
  }
  buf.clear();
  line_no++;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void MultiParser::check_ndigit(Integer& NDIGIT)
{
  if( NDIGIT != ndigit_pre )
  {
    ndigit_pre = NDIGIT;

    switch(NDIGIT)
    {
      case 6:
        char_no  = 10; //5 + 5;
        data_no  =  8;
        int_size =  7;
        break;
      case 5:
        char_no  = 11; //5 + 5 + 1;
        data_no  =  9;
        int_size =  6;
        break;
      case 4:
        char_no  = 11; //5 + 5 + 1;
        data_no  = 11;
        int_size =  5;
        break;
      case 3:
        char_no  = 11; //5 + 5 + 1;
        data_no  = 13;
        int_size =  4;
        break;
      case 2:
        char_no  = 11; //5 + 5 + 1;
        data_no  = 18;
        int_size =  3;
        break;
      default:
        string class_name = "MultiParser";
        string func_name  = "check_ndigit(Integer& NDIGIT)";

        ostringstream oss;
        oss << NDIGIT;
        string str_data = "Digit number : " + oss.str();

        vector<string> err_com;
        err_com.push_back(str_data);
        err_com.push_back("The NDIGIT is only applicable 2-6.");
        err_com.push_back("Please check the intg data.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
        break;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiParser::get_mf_mt(vector<string>& text, Integer& MF, Integer& MT)
{
  string strMF  = text[0].substr(70, 2);
  string strMT  = text[0].substr(72, 3);

  MF  = numeric_string_cast<Integer>(strMF);
  MT  = numeric_string_cast<Integer>(strMT);

  strMF.clear();
  strMT.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiParser::get_mat(vector<string>& text, Integer& MAT) 
{
  string strMAT = text[0].substr(66, 4);
  
  MAT = numeric_string_cast<Integer>(strMAT);

  strMAT.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiParser::line_no_check(vector<string>& text, int line_no, Integer MF, Integer MT)
{
  int text_line_no = static_cast<int>(text.size());
  if( text_line_no != line_no )
  {
    string class_name = "MultiParser";
    string func_name  = "line_no_check(vector<string>& text, int& line_no, Integer MF, Integer MT)";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << MF;
    oss02 << MT;
    oss03 << text_line_no;
    oss04 << line_no;
    string str_data01 = "MF                 : " + oss01.str();
    string str_data02 = "MT                 : " + oss02.str();
    string str_data03 = "Text line number   : " + oss03.str();
    string str_data04 = "Parsed line number : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    if( text_line_no > line_no )
    {
      err_com.push_back("The line number of corresponding data in the ENDF file is larger");
    }
    else
    {
      err_com.push_back("The line number of corresponding data in the ENDF file is smaller");
    }
    err_com.push_back("than that in parsed data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MultiParser::check_mf_mt(vector<string>& text, Integer MF, Integer MT)
{
  Integer MF_chk, MT_chk;
  get_mf_mt(text, MF_chk, MT_chk);

  if( MF != MF_chk || MT != MT_chk )
  {
    return -1;
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MultiParser::check_mf(vector<string>& text, Integer MF)
{
  Integer MF_chk, MT_chk;
  get_mf_mt(text, MF_chk, MT_chk);

  if( MF != MF_chk )
  {
    return -1;
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiParser::set_linearize_tab_flg(int int_val)
{
  if( int_val != skip_linearize_tab_data &&
      int_val != linearize_tab_data )
  {
    string class_name = "MultiParser";
    string func_name  = "set_linearize_tab_flg(int int_val)";

    ostringstream oss01, oss02, oss03;
    oss01 << int_val;
    oss02 << skip_linearize_tab_data;
    oss03 << linearize_tab_data;
    string str_data01 = "linearize_tab_flg (input) : " + oss01.str();
    string str_data02 = "  skip linearization of TAB1 data  : " + oss02.str();
    string str_data03 = "  linearization of TAB1 data       : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This linearize_tab_flg value is not available in this program.");
    err_com.push_back("Available value is as follows:");
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  linearize_tab_flg = int_val;
}

void MultiParser::set_linearize_tolerance(Real real_val)
{
  if( real_val < min_value || real_val >= 1.0 )
  {
    string class_name = "MultiParser";
    string func_name  = "set_linearize_tolerance(Real real_val)";

    ostringstream oss01;
    oss01 << setw(8) << std::showpoint << std::scientific << real_val;
    string str_data01 = "linearize_tolerance : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);

    if( real_val < min_value )
    {
      err_com.push_back("linearize_tolerance is less than or equal to 0.0.");
    }
    else //if( real_val >= 1.0 )
    {
      err_com.push_back("linearize_tolerance must be less than 1.0.");
    }
    err_com.push_back("The default value is used for the linearization.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  linearize_tolerance = real_val;
}

void MultiParser::set_linearize_tolerance_def()
{
  linearize_tolerance = -1.0;
}

int  MultiParser::get_linearize_tab_flg()
{
  return linearize_tab_flg;
}

Real MultiParser::get_linearize_tolerance()
{
  return linearize_tolerance;
}

