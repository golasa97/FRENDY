#include "MGXSUtils/MatxsUtils/MatxsObject.hpp"

using namespace frendy;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

// ***** MatxsCommonData ***** //

//constructor
MatxsCommonData::MatxsCommonData(void)
{
  clear();
}

//destructor
MatxsCommonData::~MatxsCommonData(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCommonData::clear()
{
  //0v
  hname.clear();
  huse.clear();

  ivers = 0;

  //1d
  npart  = 0;
  ntype  = 0;
  nholl  = 0;
  nmat   = 0;
  matxw  = matxw_def;
  length = 0;

  //2d
  hsetid.clear();

  //3d
  hpart.clear();
  htype.clear();
  hmatn.clear();
  ngrp.clear();
  jinp.clear();
  joutp.clear();
  nsubm.clear();
  locm.clear();

  //4d
  vector<MatxsGroupStructureData>().swap(grp_obj);

  //5-10d
  vector<MatxsMaterialData>().swap(mat_obj);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCommonData::read_data(vector<string>& text_vec)
{
  int line_no = 0;
  read_data(text_vec, line_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCommonData::read_data(vector<string>& text_vec, int& line_no)
{
  search_0v_data(text_vec, line_no);

  StringUtils str_obj;
  string class_name = "MatxsCommonData";
  string func_name  = "read_data(vector<string>& text_vec, int& line_no)";
  str_obj.check_string_vector_data_end(text_vec, line_no+5, class_name, func_name);

  read_0v_data(text_vec, line_no);
  read_1d_data(text_vec, line_no);
  read_2d_data(text_vec, line_no);
  read_3d_data(text_vec, line_no);

  //Read 4d data
  grp_obj.resize(npart);
  for(int i=0; i<npart; i++)
  {
    grp_obj[i].set_ngrp(ngrp[i]);
    grp_obj[i].read_data(text_vec, line_no);
  }

  //Read 5d - 10d data
  mat_obj.resize(nmat);
  for(int i=0; i<nmat; i++)
  {
    mat_obj[i].set_ngrp(ngrp);
    mat_obj[i].set_joutp(joutp);
    mat_obj[i].set_nsubm(nsubm[i]);
    mat_obj[i].read_data(text_vec, line_no);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCommonData::search_0v_data(vector<string>& text_vec, int& line_no)
{
  if( line_no < 0 )
  {
    line_no = 0;
  }

  int find_flg = -1;
  for(int i=line_no; i<static_cast<int>(text_vec.size()); i++)
  {
    if( text_vec[i].find("0v") != string::npos )
    {
      find_flg = i;
      break;
    }
  }

  if( find_flg < 0 )
  {
    string class_name = "MatxsCommonData";
    string func_name  = "search_0v_data";

    vector<string> err_com;
    err_com.push_back("The 0v data is not found in the text data.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  line_no = find_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCommonData::read_0v_data(vector<string>& text_vec, int& line_no)
{
  StringUtils str_obj;
  vector<string> str_vec;

  if( static_cast<int>(text_vec[line_no].length()) <= 30 )
  {
    string class_name = "MatxsCommonData";
    string func_name  = "read_0v_data";

    string str_data = "line data : " + text_vec[line_no];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The number of characters in 0v data must be larger than 31.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  str_vec.resize(6);
  str_vec[0] = text_vec[line_no].substr( 0, 4); // 0v
  str_vec[1] = text_vec[line_no].substr( 4, 8); //hname
  str_vec[2] = text_vec[line_no].substr(12, 1); // *
  str_vec[3] = text_vec[line_no].substr(13,16); //huse
  str_vec[4] = text_vec[line_no].substr(29, 1);
  str_vec[5] = text_vec[line_no].substr(30);
  str_vec[5] = str_obj.get_formatted_string_data(str_vec[5], 6);

  if( str_vec[0].find("0v") == string::npos )
  {
    string class_name = "MatxsCommonData";
    string func_name  = "read_0v_data";

    string str_data = "line data : " + text_vec[line_no];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This data is not 0v data in MATXS format.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  line_no++;
  str_obj.skip_no_space_string_data(text_vec, line_no);

  hname = str_vec[1];
  huse  = str_vec[3];
  ivers = numeric_string_cast<Integer>(str_vec[5]);
  str_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCommonData::read_1d_data(vector<string>& text_vec, int& line_no)
{
  StringUtils str_obj;
  vector<string> str_vec;

  str_vec = str_obj.divide_string_data(text_vec[line_no], 6, 42);

  if( str_vec[0].find("1d") == string::npos )
  {
    string class_name = "MatxsCommonData";
    string func_name  = "read_1d_data";

    string str_data = "line data : " + text_vec[line_no];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This data is not 1d data in MATXS format.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  line_no++;
  str_obj.skip_no_space_string_data(text_vec, line_no);

  npart  = numeric_string_cast<Integer>(str_vec[1]);
  ntype  = numeric_string_cast<Integer>(str_vec[2]);
  nholl  = numeric_string_cast<Integer>(str_vec[3]);
  nmat   = numeric_string_cast<Integer>(str_vec[4]);
  matxw  = numeric_string_cast<Integer>(str_vec[5]);
  length = numeric_string_cast<Integer>(str_vec[6]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCommonData::read_2d_data(vector<string>& text_vec, int& line_no)
{
  StringUtils str_obj;
  string class_name = "MatxsCommonData";
  string func_name  = "read_2d_data";

  if( text_vec[line_no].find("2d") == string::npos )
  {
    string str_data = "line data : " + text_vec[line_no];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This data is not 2d data in MATXS format.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  line_no++;
  str_obj.skip_no_space_string_data(text_vec, line_no);

  int line_no_hsetid = nholl / 9;
  hsetid.resize(static_cast<int>(line_no_hsetid));
  for(int i=0; i<static_cast<int>(line_no_hsetid); i++)
  {
    str_obj.check_string_vector_data_end(text_vec, line_no, class_name, func_name);

    hsetid[i] = str_obj.get_formatted_string_data(text_vec[line_no], 72);
    line_no++;
  }
  str_obj.skip_no_space_string_data(text_vec, line_no);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCommonData::read_3d_data(vector<string>& text_vec, int& line_no)
{
  StringUtils str_obj;
  string class_name = "MatxsCommonData";
  string func_name  = "read_3d_data";
  vector<string> str_vec;

  int line_no_ori = line_no;
  int data_no     = npart + ntype + nmat + 1;
  while( static_cast<int>(str_vec.size()) < data_no )
  {
    str_obj.check_string_vector_data_end(text_vec, line_no, class_name, func_name);

    str_obj.add_string_vector_data(str_vec, str_obj.divide_string_data(text_vec[line_no], 8, 72));
    line_no++;
  }
  str_obj.skip_no_space_string_data(text_vec, line_no);

  if( str_vec[0].find("3d") == string::npos )
  {
    string str_data = "line data : " + text_vec[line_no_ori];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This data is not 3d data in MATXS format.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int ele_no = 1;
  hpart.resize(npart);
  htype.resize(ntype);
  hmatn.resize(nmat);
  for(int i=0; i<npart; i++)
  {
    hpart[i] = str_vec[ele_no];
    ele_no++;
  }
  for(int i=0; i<ntype; i++)
  {
    htype[i] = str_vec[ele_no];
    ele_no++;
  }
  for(int i=0; i<nmat; i++)
  {
    hmatn[i] = str_vec[ele_no];
    ele_no++;
  }
  str_vec.clear();

  data_no = npart + ntype*2 + nmat*2;
  while( static_cast<int>(str_vec.size()) < data_no )
  {
    str_obj.check_string_vector_data_end(text_vec, line_no, class_name, func_name);

    str_obj.add_string_vector_data(str_vec, str_obj.divide_string_data(text_vec[line_no], 6, 72));
    line_no++;
  }
  str_obj.skip_no_space_string_data(text_vec, line_no);

  ele_no = 0;
  ngrp.resize(npart);
  jinp.resize(ntype);
  joutp.resize(ntype);
  nsubm.resize(nmat);
  locm.resize(nmat);
  for(int i=0; i<npart; i++)
  {
    ngrp[i] = numeric_string_cast<Integer>(str_vec[ele_no]);
    ele_no++;
  }
  for(int i=0; i<ntype; i++)
  {
    jinp[i] = numeric_string_cast<Integer>(str_vec[ele_no]);
    ele_no++;
  }
  for(int i=0; i<ntype; i++)
  {
    joutp[i] = numeric_string_cast<Integer>(str_vec[ele_no]);
    ele_no++;
  }
  for(int i=0; i<nmat; i++)
  {
    nsubm[i] = numeric_string_cast<Integer>(str_vec[ele_no]);
    ele_no++;
  }
  for(int i=0; i<nmat; i++)
  {
    locm[i] = numeric_string_cast<Integer>(str_vec[ele_no]);
    ele_no++;
  }
  str_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MatxsCommonData::write_data()
{
  StringUtils str_obj;

  vector<string> text;
  text.clear();

  //0v
  string header = " 0v";

  vector<string> str_vec;
  str_vec.resize(6);
  str_vec[0] = str_obj.get_formatted_string_data(header, 4);
  str_vec[1] = str_obj.get_formatted_string_data(hname, 8);
  str_vec[2] = "*";
  str_vec[3] = str_obj.get_formatted_string_data(huse,16);
  str_vec[4] = "*";
  str_vec[5] = str_obj.get_formatted_int_data(ivers,-6);

  text.push_back(str_obj.get_merged_string_vector_data(str_vec));
  str_vec.clear();

  //1d
  header = " 1d";
  calc_1d_data();
  str_vec.resize(7);
  str_vec[0] = str_obj.get_formatted_string_data(header, 6);
  str_vec[1] = str_obj.get_formatted_int_data(npart, -6);
  str_vec[2] = str_obj.get_formatted_int_data(ntype, -6);
  str_vec[3] = str_obj.get_formatted_int_data(nholl, -6);
  str_vec[4] = str_obj.get_formatted_int_data(nmat,  -6);
  str_vec[5] = str_obj.get_formatted_int_data(matxw, -6);
  str_vec[6] = str_obj.get_formatted_int_data(length,-6);

  text.push_back(str_obj.get_merged_string_vector_data(str_vec));
  str_vec.clear();

  //2d
  header = " 2d";

  str_vec.resize(1);
  str_vec[0] = str_obj.get_formatted_string_data(header, 4);
  text.push_back(str_obj.get_merged_string_vector_data(str_vec));

  for(int i=0; i<static_cast<int>(hsetid.size()); i++)
  {
    str_vec[0] = str_obj.get_formatted_string_data(hsetid[i], 72);
    text.push_back(str_obj.get_merged_string_vector_data(str_vec));
  }
  str_vec.clear();

  //3d
  header = " 3d";

  str_vec.push_back(str_obj.get_formatted_string_data(header, 8));
  for(int i=0; i<npart; i++)
  {
    str_vec.push_back(str_obj.get_formatted_string_data(hpart[i], 8));
  }
  for(int i=0; i<ntype; i++)
  {
    str_vec.push_back(str_obj.get_formatted_string_data(htype[i], 8));
  }
  for(int i=0; i<nmat; i++)
  {
    str_vec.push_back(str_obj.get_formatted_string_data(hmatn[i], 8));
  }
  str_obj.add_string_vector_data(text, str_obj.get_merged_string_vector_data(str_vec, 9));
  str_vec.clear();

  for(int i=0; i<npart; i++)
  {
    str_vec.push_back(str_obj.get_formatted_int_data(ngrp[i],-6));
  }
  for(int i=0; i<ntype; i++)
  {
    str_vec.push_back(str_obj.get_formatted_int_data(jinp[i],-6));
  }
  for(int i=0; i<ntype; i++)
  {
    str_vec.push_back(str_obj.get_formatted_int_data(joutp[i],-6));
  }
  for(int i=0; i<nmat; i++)
  {
    str_vec.push_back(str_obj.get_formatted_int_data(nsubm[i],-6));
  }
  for(int i=0; i<nmat; i++)
  {
    str_vec.push_back(str_obj.get_formatted_int_data(locm[i],-6));
  }
  str_obj.add_string_vector_data(text, str_obj.get_merged_string_vector_data(str_vec, 12));
  str_vec.clear();

  //Write 4d data
  for(int i=0; i<npart; i++)
  {
    str_obj.add_string_vector_data(text, grp_obj[i].write_data());
  }

  //Write 5-10d data
  for(int i=0; i<nmat; i++)
  {
    str_obj.add_string_vector_data(text, mat_obj[i].write_data());
  }

  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCommonData::mod_tsl_name(Integer mt_no)
{
  string tsl_name = get_tsl_name(mt_no);
  if( static_cast<int>(tsl_name.length()) == 0 )
  {
    //Do not modify tsl name
    return;
  }

  int i_max = static_cast<int>(mat_obj.size());
  for(int i=0; i<i_max; i++)
  {
    vector<MatxsSubmaterialData> submat_obj = mat_obj[i].get_submat_obj();

    int j_max = static_cast<int>(submat_obj.size());
    for(int j=0; j<j_max; j++)
    {
      //Modify 6d data
      vector<string> hvps = submat_obj[j].get_hvps();
      int k_max = static_cast<int>(hvps.size());
      for(int k=0; k<k_max; k++)
      {
        mod_tsl_name(hvps[k], mt_no);
      }
      submat_obj[j].set_hvps(hvps);
      hvps.clear();

      //Modify 8d data
      vector<MatxsMatrixData> matrix_obj = submat_obj[j].get_matrix_obj();
      k_max = static_cast<int>(matrix_obj.size());
      for(int k=0; k<k_max; k++)
      {
        string hmtx = matrix_obj[k].get_hmtx();
        mod_tsl_name(hmtx, mt_no);
        matrix_obj[k].set_hmtx(hmtx);
        hmtx.clear();
      }
      submat_obj[j].set_matrix_obj(matrix_obj);
      vector<MatxsMatrixData>().swap(matrix_obj);
    }

    mat_obj[i].set_submat_obj(submat_obj);
    vector<MatxsSubmaterialData>().swap(submat_obj);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCommonData::mod_tsl_name(string& str_data, Integer mt_no)
{
  vector<string> tsl_name_ori;
  tsl_name_ori.push_back("other");
  tsl_name_ori.push_back("free");
  string str_data_mod = str_data;

  StringUtils str_obj;
  str_data_mod = str_obj.trim_space(str_data_mod);
  transform(str_data_mod.begin(), str_data_mod.end(), str_data_mod.begin(), ::tolower);
  
  for(int i=0; i<static_cast<int>(tsl_name_ori.size()); i++)
  {
    if( str_data_mod == tsl_name_ori[i] )
    {
      str_data_mod = get_tsl_name(mt_no);
      if( static_cast<int>(str_data_mod.length()) > 0 )
      {
        str_data = str_data_mod;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string MatxsCommonData::get_tsl_name(Integer mt_no)
{
  int i_max = 26;
  vector<string> tsl_name_list;
  tsl_name_list.resize(i_max);

  tsl_name_list[ 0] = "free";  //221
  tsl_name_list[ 1] = "hh2o";  //222
  tsl_name_list[ 2] = "poly";  //223
  tsl_name_list[ 3] = "poly";  //224
  tsl_name_list[ 4] = "hzrh";  //225
  tsl_name_list[ 5] = "hzrh";  //226
  tsl_name_list[ 6] = "benz";  //227
  tsl_name_list[ 7] = "dd2o";  //228
  tsl_name_list[ 8] = "graph"; //229
  tsl_name_list[ 9] = "graph"; //230
  tsl_name_list[10] = "be";    //231
  tsl_name_list[11] = "be";    //232
  tsl_name_list[12] = "bebeo"; //233
  tsl_name_list[13] = "bebeo"; //234
  tsl_name_list[14] = "zrzrh"; //235
  tsl_name_list[15] = "zrzrh"; //236
  tsl_name_list[16] = "obeo";  //237
  tsl_name_list[17] = "obeo";  //238
  tsl_name_list[18] = "ouo2";  //239
  tsl_name_list[19] = "ouo2";  //240
  tsl_name_list[20] = "uuo2";  //241
  tsl_name_list[21] = "uuo2";  //242
  tsl_name_list[22] = "al";    //243
  tsl_name_list[23] = "al";    //244
  tsl_name_list[24] = "fe";    //245
  tsl_name_list[25] = "fe";    //246

  string tsl_name = "";
  tsl_name.clear();

  int pos = static_cast<int>(mt_no) - 221;
  if( pos >= 0 && pos < i_max )
  {
    tsl_name = tsl_name_list[pos];
  }
  else if( pos >= 0 && mt_no <= 250 )
  {
    tsl_name = "other";
  }

  return tsl_name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string MatxsCommonData::get_react_name(Integer mt_no)
{
  string react_name = "";

  //This name list is copied from the convertMT2MatxsName function
  //in MGXSUtils/FMGenerator/FMZlib.h
  if( mt_no < 50 )
  {
         if(mt_no ==   1) react_name = "ntot0";
    else if(mt_no ==   2) react_name = "nelas";
    else if(mt_no ==   3) react_name = "nnonel";
    else if(mt_no ==   4) react_name = "ninel";
    else if(mt_no ==   5) react_name = "nx";
    else if(mt_no ==   6) react_name = "n2n1";
    else if(mt_no ==   7) react_name = "n2n2";
    else if(mt_no ==   8) react_name = "n2n3";
    else if(mt_no ==   9) react_name = "n2n4";
    else if(mt_no ==  16) react_name = "n2n";
    else if(mt_no ==  17) react_name = "n3n";
    else if(mt_no ==  18) react_name = "nftot";
    else if(mt_no ==  19) react_name = "nf";
    else if(mt_no ==  20) react_name = "nnf";
    else if(mt_no ==  21) react_name = "n2nf";
    else if(mt_no ==  22) react_name = "nna";
    else if(mt_no ==  23) react_name = "nn3a";
    else if(mt_no ==  24) react_name = "n2na";
    else if(mt_no ==  25) react_name = "n3na";
    else if(mt_no ==  26) react_name = "n2ni";
    else if(mt_no ==  28) react_name = "nnp";
    else if(mt_no ==  29) react_name = "nn2a";
    else if(mt_no ==  30) react_name = "n2n2a";
    else if(mt_no ==  32) react_name = "nnd";
    else if(mt_no ==  33) react_name = "nnt";
    else if(mt_no ==  34) react_name = "nnh";
    else if(mt_no ==  35) react_name = "nnd2a";
    else if(mt_no ==  36) react_name = "nnt2a";
    else if(mt_no ==  37) react_name = "n4n";
    else if(mt_no ==  38) react_name = "n3nf";
    else if(mt_no ==  41) react_name = "n2np";
    else if(mt_no ==  42) react_name = "n3np";
    else if(mt_no ==  44) react_name = "nn2p";
    else if(mt_no ==  45) react_name = "nnpa";
  }
  else if( mt_no < 100 )
  {
         if(mt_no ==  51) react_name = "n01";
    else if(mt_no ==  52) react_name = "n02";
    else if(mt_no ==  53) react_name = "n03";
    else if(mt_no ==  54) react_name = "n04";
    else if(mt_no ==  55) react_name = "n05";
    else if(mt_no ==  56) react_name = "n06";
    else if(mt_no ==  57) react_name = "n07";
    else if(mt_no ==  58) react_name = "n08";
    else if(mt_no ==  59) react_name = "n09";
    else if(mt_no ==  60) react_name = "n10";
    else if(mt_no ==  61) react_name = "n11";
    else if(mt_no ==  62) react_name = "n12";
    else if(mt_no ==  63) react_name = "n13";
    else if(mt_no ==  64) react_name = "n14";
    else if(mt_no ==  65) react_name = "n15";
    else if(mt_no ==  66) react_name = "n16";
    else if(mt_no ==  67) react_name = "n17";
    else if(mt_no ==  68) react_name = "n18";
    else if(mt_no ==  69) react_name = "n19";
    else if(mt_no ==  70) react_name = "n20";
    else if(mt_no ==  71) react_name = "n21";
    else if(mt_no ==  72) react_name = "n22";
    else if(mt_no ==  73) react_name = "n23";
    else if(mt_no ==  74) react_name = "n24";
    else if(mt_no ==  75) react_name = "n25";
    else if(mt_no ==  76) react_name = "n26";
    else if(mt_no ==  77) react_name = "n27";
    else if(mt_no ==  78) react_name = "n28";
    else if(mt_no ==  79) react_name = "n29";
    else if(mt_no ==  80) react_name = "n30";
    else if(mt_no ==  81) react_name = "n31";
    else if(mt_no ==  82) react_name = "n32";
    else if(mt_no ==  83) react_name = "n33";
    else if(mt_no ==  84) react_name = "n34";
    else if(mt_no ==  85) react_name = "n35";
    else if(mt_no ==  86) react_name = "n36";
    else if(mt_no ==  87) react_name = "n37";
    else if(mt_no ==  88) react_name = "n38";
    else if(mt_no ==  89) react_name = "n39";
    else if(mt_no ==  90) react_name = "n40";
    else if(mt_no ==  91) react_name = "ncn";
  }
  else if( mt_no < 200 )
  {
         if(mt_no == 101) react_name = "nabs";
    else if(mt_no == 102) react_name = "ng";
    else if(mt_no == 103) react_name = "np";
    else if(mt_no == 104) react_name = "nd";
    else if(mt_no == 105) react_name = "nt";
    else if(mt_no == 106) react_name = "nh";
    else if(mt_no == 107) react_name = "na";
    else if(mt_no == 108) react_name = "n2a";
    else if(mt_no == 109) react_name = "n3a";
    else if(mt_no == 111) react_name = "n2p";
    else if(mt_no == 112) react_name = "npa";
    else if(mt_no == 113) react_name = "nt2a";
    else if(mt_no == 114) react_name = "nd2a";
    else if(mt_no == 115) react_name = "npd";
    else if(mt_no == 116) react_name = "npt";
    else if(mt_no == 117) react_name = "nda";
  }
  else if( mt_no < 210 )
  {
         if(mt_no == 201) react_name = "n.neut";
    else if(mt_no == 202) react_name = "n.gam";
    else if(mt_no == 203) react_name = "n.h1";
    else if(mt_no == 204) react_name = "n.h2";
    else if(mt_no == 205) react_name = "n.h3";
    else if(mt_no == 206) react_name = "n.he3";
    else if(mt_no == 207) react_name = "n.he4";
  }
  else
  {
         if(mt_no == 221) react_name = "free";
    else if(mt_no == 222) react_name = "hh2o";
    else if(mt_no == 223) react_name = "poly";
    else if(mt_no == 224) react_name = "poly$";
    else if(mt_no == 225) react_name = "hzrh";
    else if(mt_no == 226) react_name = "hzrh$";
    else if(mt_no == 227) react_name = "benz";
    else if(mt_no == 228) react_name = "dd2o";
    else if(mt_no == 229) react_name = "graph";
    else if(mt_no == 230) react_name = "graph$";
    else if(mt_no == 231) react_name = "be";
    else if(mt_no == 232) react_name = "be$";
    else if(mt_no == 233) react_name = "bebeo";
    else if(mt_no == 234) react_name = "bebeo$";
    else if(mt_no == 235) react_name = "zrzrh";
    else if(mt_no == 236) react_name = "zrzrh$";
    else if(mt_no == 237) react_name = "obeo";
    else if(mt_no == 238) react_name = "obeo$";
    else if(mt_no == 239) react_name = "ouo2";
    else if(mt_no == 240) react_name = "ouo2$";
    else if(mt_no == 241) react_name = "uuo2";
    else if(mt_no == 242) react_name = "uuo2$";
    else if(mt_no == 243) react_name = "al";
    else if(mt_no == 244) react_name = "al$";
    else if(mt_no == 245) react_name = "fe";
    else if(mt_no == 246) react_name = "fe$";
    else if(mt_no == 249) react_name = "other";
    else if(mt_no == 250) react_name = "other$";

    else if(mt_no == 251) react_name = "mubar";
    else if(mt_no == 252) react_name = "xi";
    else if(mt_no == 253) react_name = "gamma";
    else if(mt_no == 258) react_name = "mt258";
    else if(mt_no == 259) react_name = "invel";
    else if(mt_no == 301) react_name = "heat";
    else if(mt_no == 443) react_name = "kerma";
    else if(mt_no == 444) react_name = "dame";

    else if(mt_no == 452) react_name = "nutot";
    else if(mt_no == 455) react_name = "nudel";
    else if(mt_no == 456) react_name = "nupmt";
  }

  return react_name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCommonData::add_photon_production_data(vector<GMF16Parser>& gmf_data,
                                                 vector<Real>& mg_ene_n, vector<Real>& mg_ene_g)
{
  Integer grp_pos    = -1;
  Integer mt_data_no = -1;

  sort(mg_ene_n.begin(), mg_ene_n.end(), greater<Real>());
  sort(mg_ene_g.begin(), mg_ene_g.end(), greater<Real>());

  int err_flg = add_photon_production_data_check_data(gmf_data, mg_ene_n, grp_pos, mt_data_no);
  if( err_flg > 0 )
  {
    return;
  }

  //Modify 1d data
  npart++; 
  ntype++; 

  //Modify 3d data
  int mg_ene_g_no = static_cast<int>(mg_ene_g.size()) - 1;

  hpart.push_back("g");
  htype.push_back("ng");
  ngrp.push_back(mg_ene_g_no);
  jinp.push_back(grp_pos);
  joutp.push_back(static_cast<int>(ngrp.size()));

  //Modify 4d data (MatxsGroupStructureData)
  MatxsGroupStructureData grp_obj_add;
  grp_obj_add.set_ngrp(mg_ene_g_no);
  grp_obj_add.set_gpb(mg_ene_g);
  grp_obj.push_back(grp_obj_add);
  grp_obj_add.clear();

  //Modify 5d data (MatxsMaterialData)
  vector<Real> temp_vec = mat_obj[0].get_temp(); 
  temp_vec.push_back(temp_vec[0]);
  mat_obj[0].set_temp(temp_vec);

  vector<Real> sigz_vec = mat_obj[0].get_sigz();
  sigz_vec.push_back(sigz_vec[0]);
  mat_obj[0].set_sigz(sigz_vec);

  vector<Integer> itype_vec = mat_obj[0].get_itype();
  itype_vec.push_back(static_cast<Integer>(hpart.size()));
  mat_obj[0].set_itype(itype_vec);

  vector<Integer> n1d_vec = mat_obj[0].get_n1d();
  n1d_vec.push_back(0);
  mat_obj[0].set_n1d(n1d_vec);

  vector<Integer> n2d_vec = mat_obj[0].get_n2d();
  n2d_vec.push_back(mt_data_no);
  mat_obj[0].set_n2d(n2d_vec);

  vector<Integer> locs_vec = mat_obj[0].get_locs();
  locs_vec.push_back(0);
  mat_obj[0].set_locs(locs_vec);

  Integer nsubm_val = mat_obj[0].get_nsubm();
  nsubm_val++;
  mat_obj[0].set_nsubm(nsubm_val);
  
  mat_obj[0].set_ngrp(ngrp);
  mat_obj[0].set_joutp(joutp);

  //Add 8d and 9d data (MatxsSubmaterialData)
  VectorClearer clr_obj;

  vector<MatxsMatrixData> matrix_obj;
  matrix_obj.resize(mt_data_no);
  int ele_no = 0;
  for(int i=0; i<static_cast<int>(gmf_data.size()); i++)
  {
    Integer mt_no_gendf = gmf_data[i].get_mt_no();
    if( mt_no_gendf != unassigned_mt_no )
    {
      //[ein][sigz][pl][eout]
      vector<vector<vector<vector<Real> > > > matrix_gendf = gmf_data[i].get_MATRIX();
      //[eout][ein]
      vector<vector<Real> >                   matrix_gendf_mod;

      //Modify order of array [ein][sigz][pl][eout] -> [eout][ein]
      int mg_ene_n_no = static_cast<int>(mg_ene_n.size()) - 1;
      matrix_gendf_mod.resize(mg_ene_g_no);
      for(int j=0; j<mg_ene_g_no; j++)
      {
        matrix_gendf_mod[j].resize(mg_ene_n_no);
        for(int k=0; k<mg_ene_n_no; k++)
        {
          matrix_gendf_mod[j][k] = 0.0;

          if( static_cast<int>(matrix_gendf[k+1].size()) > 0 )
          {
            if( j < static_cast<int>(matrix_gendf[k+1][0][0].size()) )
            {
              //matrix_gendf.size() = mg_ene_n_no + 1
              //(MF=6 MT=18 has NGN+1 data)
              matrix_gendf_mod[j][k] = matrix_gendf[k+1][0][0][j];
              if( fabs(matrix_gendf_mod[j][k]) < min_value )
              {
                matrix_gendf_mod[j][k] = 0.0;
              }
            }
          }
        }
      }
      clr_obj.clear_vec_array4_real(matrix_gendf);

      //[eout][pl][ein]
      vector<vector<vector<Real> > > scat; //For 9d
      vector<Integer>                e_in_low, e_in_high;
      e_in_low.resize(mg_ene_g_no);
      e_in_high.resize(mg_ene_g_no);

      for(int j=mg_ene_g_no-1; j>=0; j--)
      //for(int j=0; j<mg_ene_g_no; j++)
      {
        e_in_low[j]  = -1;
        e_in_high[j] = -1;
        for(int k=0; k<mg_ene_n_no; k++)
        {
          if( fabs(matrix_gendf_mod[j][k]) > min_value )
          {
            if( e_in_low[j] < 0 )
            {
              e_in_low[j] = k;
            }
            e_in_high[j] = k;
          }
        }

        if( e_in_low[j] >= 0 )
        {
          int scat_no = e_in_high[j] - e_in_low[j] + 1;

          vector<vector<Real> > scat_tmp;
          scat_tmp.resize(1); //pl
          scat_tmp[0].resize(scat_no);

          int ele_no = 0;
          for(int k=e_in_low[j]; k<=e_in_high[j]; k++)
          {
            scat_tmp[0][ele_no] = matrix_gendf_mod[j][k];
            ele_no++;
          }

          scat.push_back(scat_tmp);
          clr_obj.clear_vec_array2_real(scat_tmp);
        }
      }


      //8d
      string  hmtx   = get_react_name(mt_no_gendf);
      Integer lord   = 1;
      Integer jconst = 0;

      vector<Integer> jband_vec, ijj_vec;
      jband_vec.resize(mg_ene_g_no);
      ijj_vec.resize(mg_ene_g_no);
      for(int j=mg_ene_g_no-1; j>=0; j--)
      {
        jband_vec[j] = 0;
        ijj_vec[j]   = 0;
        if( e_in_low[j] >= 0 )
        {
          jband_vec[j] = e_in_high[j] - e_in_low[j] + 1;
          ijj_vec[j]   = mg_ene_n_no - e_in_low[j];
        }
      }

      //Copy 8d data
      matrix_obj[ele_no].set_hmtx(hmtx);
      matrix_obj[ele_no].set_lord(lord);
      matrix_obj[ele_no].set_jconst(jconst);
      matrix_obj[ele_no].set_jband(jband_vec);
      matrix_obj[ele_no].set_ijj(ijj_vec);

      //Copy 9d data
      matrix_obj[ele_no].set_scat(scat);
      clr_obj.clear_vec_array3_real(scat);
      ele_no++;
    }
  }

  //Copy 8d and 9d data
  MatxsSubmaterialData submat_obj;
  submat_obj.set_matrix_obj(matrix_obj);
  vector<MatxsMatrixData>().swap(matrix_obj);

  vector<MatxsSubmaterialData> submat_obj_vec = mat_obj[0].get_submat_obj();
  submat_obj_vec.push_back(submat_obj);
  submat_obj.clear();

  mat_obj[0].set_submat_obj(submat_obj_vec);
  vector<MatxsSubmaterialData>().swap(submat_obj_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int MatxsCommonData::add_photon_production_data_check_data
                       (vector<GMF16Parser>& gmf_data, vector<Real>& ene_mg,
                        Integer& grp_pos, Integer& mt_data_no)
{
  int err_flg = -1;

  //Check data size of MF=16 data
  int gmf_no   = static_cast<int>(gmf_data.size());
  if( gmf_no == 0 )
  {
    err_flg = 1;
    return  err_flg;
  }

  //Check MT number of MF=16 data
  mt_data_no = 0;
  for(int i=0; i<gmf_no; i++)
  {
    if( gmf_data[i].get_mt_no() != unassigned_mt_no )
    {
      mt_data_no++;
    }
  }

  if( mt_data_no <= 0 )
  {
    string class_name = "MatxsCommonData";
    string func_name  = "add_photon_production_data_check_data";

    vector<string> err_com;
    err_com.push_back("The data number of GMF16Parser is larger than 0.");
    err_com.push_back("However, the MT number of all GMF16Parser data is not assiigned.");
    err_com.push_back("");
    err_com.push_back("The addition of the photon production data to the MATXS file is skipped.");

    err_obj.output_caution(class_name, func_name, err_com);

    err_flg = 2;
    return err_flg;
  }


  //Check htype in 3d (hpart)
  for(int i=0; i<static_cast<int>(hpart.size()); i++)
  {
    transform(hpart[i].begin(), hpart[i].end(), hpart[i].begin(), ::tolower);

    if( hpart[i] == "g" )
    {
      string class_name = "MatxsCommonData";
      string func_name  = "add_photon_production_data_check_data";

      vector<string> err_com;
      err_com.push_back("The gammma data is found in 3d data (g in hpart).");
      err_com.push_back("");
      err_com.push_back("The additional of the photon production data is only available");
      err_com.push_back("when the gamma data is not found in the MATXS file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //Check htype in 3d (htype)
  for(int i=0; i<static_cast<int>(htype.size()); i++)
  {
    transform(htype[i].begin(), htype[i].end(), htype[i].begin(), ::tolower);

    if( htype[i] == "ng" )
    {
      string class_name = "MatxsCommonData";
      string func_name  = "add_photon_production_data_check_data";

      vector<string> err_com;
      err_com.push_back("The ng reaction is found in 3d data (ng in htype).");
      err_com.push_back("");
      err_com.push_back("The additional of the photon production data is only available");
      err_com.push_back("when the ng reaction is not found in the MATXS file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //Check number of MatxsMaterialData
  if( static_cast<int>(mat_obj.size()) != 1 )
  {
    string class_name = "MatxsCommonData";
    string func_name  = "add_photon_production_data_check_data";

    ostringstream oss01;
    oss01 << static_cast<int>(mat_obj.size());

    string str_data01 = "Data number of 5d data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("");
    err_com.push_back("The data number of 5d data is not equal to one.");
    err_com.push_back("");
    err_com.push_back("The additional of the photon production data is only available");
    err_com.push_back("when the data number of 5d data is one.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Check temperature data
  for(int i=0; i<gmf_no; i++)
  {
    if( gmf_data[i].get_mt_no() != unassigned_mt_no )
    {
      //Check Legendre order
      Integer lord = gmf_data[i].get_NL();
      if( lord != 1 )
      {
        string class_name = "MatxsCommonData";
        string func_name  = "add_photon_production_data_check_data";

        ostringstream oss01, oss02;
        oss01 << gmf_data[i].get_mt_no();
        oss02 << lord;

        string str_data01 = "MT number                : " + oss01.str();
        string str_data02 = "Number of Legendre order : " + oss02.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("");
        err_com.push_back("The number of Legendre order is not equal to one.");
        err_com.push_back("");
        //err_com.push_back("The additional of the photon production data is only available");
        //err_com.push_back("when the number of Legendre order is equal to zero.");
        //err_obj.output_runtime_error(class_name, func_name, err_com);

        err_com.push_back("This program may not be correctly treat this data.");
        err_obj.output_caution(class_name, func_name, err_com);
      }


      Real temp_mf16 = gmf_data[i].get_TEMP();
      if( fabs(temp_mf16) < min_value )
      {
        temp_mf16 = min_value;
      }

      vector<Real> temp_mat = mat_obj[0].get_temp();
      int j_max = static_cast<int>(temp_mat.size());
      if( j_max == 0 )
      {
        string class_name = "MatxsCommonData";
        string func_name  = "add_photon_production_data_check_data";

        vector<string> err_com;
        err_com.push_back("The temperature number in 5d data is zero.");
        err_com.push_back("");
        err_com.push_back("The additional of the photon production data is only available");
        err_com.push_back("when the temperature number in 5d data is larger than zero.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      for(int j=0; j<j_max; j++)
      {
        if( fabs(temp_mf16 - temp_mat[j]) < min_value * 1.0E-3 )
        {
          string class_name = "MatxsCommonData";
          string func_name  = "add_photon_production_data_check_data";

          ostringstream oss01, oss02, oss03, oss04, oss05;
          oss02.setf(ios::showpoint);
          oss02.precision(8);
          oss04.setf(ios::showpoint);
          oss04.precision(8);

          oss01 << gmf_data[i].get_mt_no();
          oss02 << temp_mf16;
          oss03 << j+1;
          oss04 << j_max;
          oss05 << temp_mat[j];

          string str_data01 = "Temperature from GENDF data (MF=16, MT=" + oss01.str() + ") : " + oss02.str();
          string str_data02 = "Temperature from 5d data (" + oss03.str() + " / " + oss04.str() + ") : " + oss05.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back("");
          err_com.push_back("The temperature data from GENDF data is not identical to that from 5d data.");

          err_obj.output_runtime_error(class_name, func_name, err_com);
        }
      }
    }
  }

  //Check energy grid data
      grp_pos = -1;
  int ene_no  = static_cast<int>(ene_mg.size());
  for(int i=0; i<static_cast<int>(grp_obj.size()); i++)
  {
    vector<Real> ene_matxs = grp_obj[i].get_gpb();
    if( static_cast<int>(ene_matxs.size()) == ene_no )
    {
      int ene_check_flg = -1;
      for(int j=0; j<ene_no; j++)
      {
        if( fabs(ene_mg[j] - ene_matxs[j]) > fabs(ene_mg[j] * min_ene_dif) )
        {
          ene_check_flg = j;
          break;
        }
      }

      if( ene_check_flg < 0 )
      {
        grp_pos = i+1;
        break;
      }
    }
  }

  if( grp_pos < 0 )
  {
    string class_name = "MatxsCommonData";
    string func_name  = "add_photon_production_data_check_data";

    vector<string> err_com;
    err_com.push_back("The energy grid data of the GENDF file is not found in the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  return err_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCommonData::calc_1d_data()
{
  npart = static_cast<Integer>(grp_obj.size());
  ntype = static_cast<Integer>(htype.size());
  nholl = static_cast<Integer>(hsetid.size()) * 9;
  nmat  = static_cast<Integer>(mat_obj.size());
  matxw = matxw_def;

  length = 6;
  for(int i=0; i<npart; i++)
  {
    length += grp_obj[i].get_loc_no();
  }

  for(int i=0; i<nmat; i++)
  {
    length += mat_obj[i].get_loc_no();
  }


  for(int i=0; i<nmat; i++)
  {
    nsubm[i] = static_cast<Integer>(mat_obj[i].get_temp().size());
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
//0v
void MatxsCommonData::set_hname(string str_data)
{
  hname = str_data;
}
void MatxsCommonData::set_huse(string str_data)
{
  huse = str_data;
}
void MatxsCommonData::set_ivers(Integer int_data)
{
  ivers = int_data;
}

//1d
void MatxsCommonData::set_npart(Integer int_data)
{
  npart = int_data;
}
void MatxsCommonData::set_ntype(Integer int_data)
{
  ntype = int_data;
}
void MatxsCommonData::set_nholl(Integer int_data)
{
  nholl = int_data;
}
void MatxsCommonData::set_nmat(Integer int_data)
{
  nmat = int_data;
}
void MatxsCommonData::set_matxw(Integer int_data)
{
  matxw = int_data;
}
void MatxsCommonData::set_length(Integer int_data)
{
  length = int_data;
}

//2d
void MatxsCommonData::set_hsetid(vector<string> str_vec)
{
  hsetid = str_vec;
}

//3d
void MatxsCommonData::set_hpart(vector<string> str_vec)
{
  hpart = str_vec;
}
void MatxsCommonData::set_htype(vector<string> str_vec)
{
  htype = str_vec;
}
void MatxsCommonData::set_hmatn(vector<string> str_vec)
{
  hmatn = str_vec;
}
void MatxsCommonData::set_ngrp(vector<Integer> int_vec)
{
  ngrp = int_vec;
}
void MatxsCommonData::set_jinp(vector<Integer> int_vec)
{
  jinp = int_vec;
}
void MatxsCommonData::set_joutp(vector<Integer> int_vec)
{
  joutp = int_vec;
}
void MatxsCommonData::set_nsubm(vector<Integer> int_vec)
{
  nsubm = int_vec;
}
void MatxsCommonData::set_locm(vector<Integer> int_vec)
{
  locm = int_vec;
}

//4d
void MatxsCommonData::set_grp_obj(vector<MatxsGroupStructureData> obj_vec)
{
  grp_obj = obj_vec;
  vector<MatxsGroupStructureData>().swap(obj_vec);
}

//5-10d
void MatxsCommonData::set_mat_obj(vector<MatxsMaterialData> obj_vec)
{
  mat_obj = obj_vec;
  vector<MatxsMaterialData>().swap(obj_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
//0v
string  MatxsCommonData::get_hname()
{
  return hname;
}
string  MatxsCommonData::get_huse()
{
  return huse;
}
Integer MatxsCommonData::get_ivers()
{
  return ivers;
}

//1d
Integer MatxsCommonData::get_npart()
{
  calc_1d_data();
  return npart;
}
Integer MatxsCommonData::get_ntype()
{
  calc_1d_data();
  return ntype;
}
Integer MatxsCommonData::get_nholl()
{
  calc_1d_data();
  return nholl;
}
Integer MatxsCommonData::get_nmat()
{
  calc_1d_data();
  return nmat;
}
Integer MatxsCommonData::get_matxw()
{
  calc_1d_data();
  return matxw;
}
Integer MatxsCommonData::get_length()
{
  calc_1d_data();
  return length;
}

//2d
vector<string> MatxsCommonData::get_hsetid()
{
  return hsetid;
}

//3d
vector<string>  MatxsCommonData::get_hpart()
{
  return hpart;
}
vector<string>  MatxsCommonData::get_htype()
{
  return htype;
}
vector<string>  MatxsCommonData::get_hmatn()
{
  return hmatn;
}
vector<Integer> MatxsCommonData::get_ngrp()
{
  return ngrp;
}
vector<Integer> MatxsCommonData::get_jinp()
{
  return jinp;
}
vector<Integer> MatxsCommonData::get_joutp()
{
  return joutp;
}
vector<Integer> MatxsCommonData::get_nsubm()
{
  return nsubm;
}
vector<Integer> MatxsCommonData::get_locm()
{
  return locm;
}

//4d
vector<MatxsGroupStructureData> MatxsCommonData::get_grp_obj()
{
  return grp_obj;
}

//5-10d
vector<MatxsMaterialData> MatxsCommonData::get_mat_obj()
{
  return mat_obj;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

// ***** MatxsGroupStructureData ***** //

//constructor
MatxsGroupStructureData::MatxsGroupStructureData(void)
{
  clear();
}

//destructor
MatxsGroupStructureData::~MatxsGroupStructureData(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsGroupStructureData::clear()
{
  ngrp = 0;

  //4d
  gpb.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsGroupStructureData::read_data(vector<string>& text_vec, int& line_no)
{
  StringUtils str_obj;
  string class_name = "MatxsGroupStructureData";
  string func_name  = "read_data";
  vector<string> str_vec;

  if( ngrp == 0 )
  {
    vector<string> err_com;
    err_com.push_back("Please set ngrp value to read 4d data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int line_no_ori = line_no;
  int data_no     = ngrp + 2;

  str_vec.clear();
  while( static_cast<int>(str_vec.size()) < data_no )
  {
    str_obj.check_string_vector_data_end(text_vec, line_no, class_name, func_name);

    str_obj.add_string_vector_data(str_vec, str_obj.divide_string_data(text_vec[line_no], 12, 72));
    line_no++;
  }
  str_obj.skip_no_space_string_data(text_vec, line_no);

  if( str_vec[0].find("4d") == string::npos )
  {
    string str_data = "line data : " + text_vec[line_no_ori];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This data is not 4d data in MATXS format.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  gpb.resize(ngrp+1);
  for(int i=1; i<data_no; i++)
  {
    gpb[i-1] = numeric_string_cast<Real>(str_vec[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MatxsGroupStructureData::write_data()
{
  StringUtils str_obj;

  vector<string> text, str_vec;
  text.clear();
  str_vec.clear();

  string header = " 4d";
  str_vec.push_back(str_obj.get_formatted_string_data(header, 12));
  for(int i=0; i<static_cast<int>(gpb.size()); i++)
  {
    str_vec.push_back(str_obj.get_formatted_real_data(gpb[i], 12));
  }
  str_obj.add_string_vector_data(text, str_obj.get_merged_string_vector_data(str_vec, 6));
  str_vec.clear();

  return text; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MatxsGroupStructureData::get_loc_no()
{
  Integer loc_no = 0;

  //Count 4d
  if( static_cast<int>(gpb.size()) > 0 )
  {
    loc_no++;
  }

  return loc_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MatxsGroupStructureData::set_ngrp(int int_data)
{
  ngrp = int_data;
}

void MatxsGroupStructureData::set_gpb(vector<Real> real_vec)
{
  gpb = real_vec;
}

//Getter
int          MatxsGroupStructureData::get_ngrp()
{
  return ngrp;
}

vector<Real> MatxsGroupStructureData::get_gpb()
{
  return gpb;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

// ***** MatxsMaterialData ***** //

//constructor
MatxsMaterialData::MatxsMaterialData(void)
{
  clear();
}

//destructor
MatxsMaterialData::~MatxsMaterialData(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMaterialData::clear()
{
  ngrp.clear();
  joutp.clear();
  nsubm = 0;

  //5d
  hmat.clear();

  amass = 0.0;

  temp.clear();
  sigz.clear();
  itype.clear();
  n1d.clear();
  n2d.clear();
  locs.clear();

  noutg.clear();

  //6-10d
  vector<MatxsSubmaterialData>().swap(submat_obj);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMaterialData::read_data(vector<string>& text_vec, int& line_no)
{
  StringUtils str_obj;
  string class_name = "MatxsMaterialData";
  string func_name  = "read_data";
  vector<string> str_vec;

  if( nsubm == 0 )
  {
    vector<string> err_com;
    err_com.push_back("Please set nsubm value to read 5d data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( static_cast<int>(text_vec[line_no].length()) <= 12 )
  {
    string str_data = "line data : " + text_vec[line_no];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("The number of characters in 5d data must be larger than 12.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Read Line No. 1
  str_vec.resize(3);
  str_vec[0] = text_vec[line_no].substr( 0, 4); // 5d
  str_vec[1] = text_vec[line_no].substr( 4, 8); //hmat
  str_vec[2] = text_vec[line_no].substr(12);    //amass
  str_vec[2] = str_obj.get_formatted_string_data(str_vec[2],12);

  if( str_vec[0].find("5d") == string::npos )
  {
    string str_data = "line data : " + text_vec[line_no];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This data is not 5d data in MATXS format.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  line_no++;
  str_obj.skip_no_space_string_data(text_vec, line_no);

  hmat  = str_vec[1];
  amass = numeric_string_cast<Real>(str_vec[2]);
  str_vec.clear();

  //Read Line No. 2
  temp.resize(nsubm);
  sigz.resize(nsubm);
  itype.resize(nsubm);
  n1d.resize(nsubm);
  n2d.resize(nsubm);
  locs.resize(nsubm);

  str_vec.resize(6);
  for(int i=0; i<nsubm; i++)
  {
    if( static_cast<int>(text_vec[line_no].length()) <= 42 )
    {
      ostringstream oss01, oss02;
      oss01 << i+1;
      oss01 << nsubm;

      string str_data01 = "line data : " + text_vec[line_no];
      string str_data02 = "nsubm     : " + oss01.str() + " / " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("The number of characters in 5d data must be larger than 42.");
      err_com.push_back("Please check the MATXS file.");
  
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    temp[i]  = numeric_string_cast<Real>(text_vec[line_no].substr( 0,12));
    sigz[i]  = numeric_string_cast<Real>(text_vec[line_no].substr(12,12));
    itype[i] = numeric_string_cast<Integer>(text_vec[line_no].substr(24, 6));
    n1d[i]   = numeric_string_cast<Integer>(text_vec[line_no].substr(30, 6));
    n2d[i]   = numeric_string_cast<Integer>(text_vec[line_no].substr(36, 6));
    locs[i]  = numeric_string_cast<Integer>(text_vec[line_no].substr(42, 6));
    line_no++;
  }
  str_obj.skip_no_space_string_data(text_vec, line_no);

  calc_noutg();

  //Read 6d - 10d data
  submat_obj.resize(nsubm);
  for(int i=0; i<nsubm; i++)
  {
    submat_obj[i].set_noutg(noutg[i]);
    submat_obj[i].set_n1d(n1d[i]);
    submat_obj[i].set_n2d(n2d[i]);
    submat_obj[i].read_data(text_vec, line_no);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMaterialData::calc_noutg()
{
  int i_max   = static_cast<int>(itype.size());
  int ngr_no  = static_cast<int>(ngrp.size());
  int jout_no = static_cast<int>(joutp.size());

  if( ngr_no == 0 || jout_no == 0 )
  {
    string class_name = "MatxsMaterialData";
    string func_name  = "calc_ng()";

    vector<string> err_com;
    err_com.push_back("Please set ngrp and joutp value to identify the number of energy grid.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  noutg.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    noutg[i] = 0;

    int i_pos = static_cast<int>(itype[i]);

    if( i_pos > jout_no )
    {
      string class_name = "MatxsMaterialData";
      string func_name  = "calc_noutg()";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << i_pos;
      oss04 << jout_no;
      string str_data01 = "Position             : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "itype                : " + oss03.str();
      string str_data03 = "Data number of joutp : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("The itype value is larger than the data number of joutp.");
      err_com.push_back("This MATXS file may not be incorrect.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int e_pos = static_cast<int>(joutp[i_pos-1]);
    if( e_pos > ngr_no )
    {
      string class_name = "MatxsMaterialData";
      string func_name  = "calc_noutg()";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << i_pos;
      oss04 << e_pos;
      oss05 << ngr_no;
      string str_data01 = "Position            : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "itype               : " + oss03.str();
      string str_data03 = "joutp               : " + oss04.str();
      string str_data04 = "Data number of ngrp : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("The joutp value is larger than the data number of ngrp.");
      err_com.push_back("This MATXS file may not be incorrect.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    noutg[i] = ngrp[e_pos-1];
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MatxsMaterialData::write_data()
{
  StringUtils str_obj;

  vector<string> text, str_vec;
  text.clear();
  str_vec.clear();

  calc_locs();

  string header = " 5d";
  str_vec.push_back(str_obj.get_formatted_string_data(header, 4));
  str_vec.push_back(str_obj.get_formatted_string_data(hmat, 8));
  str_vec.push_back(str_obj.get_formatted_real_data(amass,12));

  text.push_back(str_obj.get_merged_string_vector_data(str_vec));
  str_vec.clear();

  int i_max = static_cast<int>(temp.size());
  nsubm = i_max;
  for(int i=0; i<i_max; i++)
  {
    str_vec.push_back(str_obj.get_formatted_real_data(temp[i],12));
    str_vec.push_back(str_obj.get_formatted_real_data(sigz[i],12));
    str_vec.push_back(str_obj.get_formatted_int_data(itype[i],-6));
    str_vec.push_back(str_obj.get_formatted_int_data(n1d[i],  -6));
    str_vec.push_back(str_obj.get_formatted_int_data(n2d[i],  -6));
    str_vec.push_back(str_obj.get_formatted_int_data(locs[i], -6));

    text.push_back(str_obj.get_merged_string_vector_data(str_vec));
    str_vec.clear();
  }

  //Write 6d - 10d data
  for(int i=0; i<static_cast<int>(submat_obj.size()); i++)
  {
    if( n1d[i] > 0 || n2d[i] > 0 )
    {
      str_obj.add_string_vector_data(text, submat_obj[i].write_data());
    }
  }

  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMaterialData::calc_locs()
{
  if( static_cast<int>(locs.size()) == static_cast<int>(submat_obj.size()) )
  {
    for(int i=0; i<static_cast<int>(submat_obj.size()); i++)
    {
      if( i==0 )
      {
        locs[0] = 0;
      }
      else
      {
        locs[i] = locs[i-1] + submat_obj[i-1].get_loc_no();
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MatxsMaterialData::get_loc_no()
{
  Integer loc_no = 0;

  //Count 5d
  if( static_cast<int>(temp.size()) > 0 )
  {
    //loc_no++;
  }

  //Cout 6d - 10d
  for(int i=0; i<static_cast<int>(submat_obj.size()); i++)
  {
    loc_no += submat_obj[i].get_loc_no();
  }

  return loc_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MatxsMaterialData::set_ngrp(vector<Integer> int_vec)
{
  ngrp = int_vec;
}
void MatxsMaterialData::set_joutp(vector<Integer> int_vec)
{
  joutp = int_vec;
}
void MatxsMaterialData::set_nsubm(Integer int_data)
{
  nsubm = int_data;
}

void MatxsMaterialData::set_hmat(string str_data)
{
  hmat = str_data;
}
void MatxsMaterialData::set_amass(Real real_data)
{
  amass = real_data;
}

void MatxsMaterialData::set_temp(vector<Real> real_vec)
{
  temp = real_vec;
}
void MatxsMaterialData::set_sigz(vector<Real> real_vec)
{
  sigz = real_vec;
}
void MatxsMaterialData::set_itype(vector<Integer> int_vec)
{
  itype = int_vec;
}
void MatxsMaterialData::set_n1d(vector<Integer> int_vec)
{
  n1d = int_vec;
}
void MatxsMaterialData::set_n2d(vector<Integer> int_vec)
{
  n2d = int_vec;
}
void MatxsMaterialData::set_locs(vector<Integer> int_vec)
{
  locs = int_vec;
}

//6-10d
void MatxsMaterialData::set_submat_obj(vector<MatxsSubmaterialData> obj_vec)
{
  submat_obj = obj_vec;
  vector<MatxsSubmaterialData>().swap(obj_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
vector<Integer> MatxsMaterialData::get_ngrp()
{
  return ngrp;
}
vector<Integer> MatxsMaterialData::get_joutp()
{
  return joutp;
}
Integer MatxsMaterialData::get_nsubm()
{
  return nsubm;
}

string MatxsMaterialData::get_hmat()
{
  return hmat;
}
Real   MatxsMaterialData::get_amass()
{
  return amass;
}

vector<Real>    MatxsMaterialData::get_temp()
{
  return temp;
}
vector<Real>    MatxsMaterialData::get_sigz()
{
  return sigz;
}
vector<Integer> MatxsMaterialData::get_itype()
{
  return itype;
}
vector<Integer> MatxsMaterialData::get_n1d()
{
  return n1d;
}
vector<Integer> MatxsMaterialData::get_n2d()
{
  return n2d;
}
vector<Integer> MatxsMaterialData::get_locs()
{
  calc_locs();
  return locs;
}

//6-10d
vector<MatxsSubmaterialData> MatxsMaterialData::get_submat_obj()
{
  return submat_obj;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

// ***** MatxsSubmaterialData ***** //

//constructor
MatxsSubmaterialData::MatxsSubmaterialData(void)
{
  clear();
}

//destructor
MatxsSubmaterialData::~MatxsSubmaterialData(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsSubmaterialData::clear()
{
  noutg = 0;
  n1d   = 0;
  n2d   = 0;

  //6d
  hvps.clear();
  nfg.clear();
  nlg.clear();

  //7d
  VectorClearer clr_obj;
  clr_obj.clear_vec_array2_real(vps);

  //8-10d
  vector<MatxsMatrixData>().swap(matrix_obj);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsSubmaterialData::read_data(vector<string>& text_vec, int& line_no)
{
  if( noutg == 0 && n1d == 0 && n2d == 0 )
  {
    string class_name = "MatxsSubmaterialData";
    string func_name  = "read_data";

    ostringstream oss01, oss02, oss03;
    oss01 << noutg;
    oss02 << n1d;
    oss03 << n2d;

    string str_data01 = "noutg : " + oss01.str();
    string str_data02 = "n1d   : " + oss02.str();
    string str_data03 = "n2d   : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Please set noutg, n1d and n2d to read 6d and 7d data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( n1d > 0 )
  {
    if( text_vec[line_no].find("6d") != string::npos )
    {
      read_6d_data(text_vec, line_no);
    }
    if( text_vec[line_no].find("7d") != string::npos )
    {
      read_7d_data(text_vec, line_no);
    }
  }

  //Read 8d - 10d data
  matrix_obj.resize(n2d);
  for(int i=0; i<n2d; i++)
  {
    matrix_obj[i].set_noutg(noutg);
    matrix_obj[i].read_data(text_vec, line_no);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsSubmaterialData::read_6d_data(vector<string>& text_vec, int& line_no)
{
  StringUtils str_obj;
  string class_name = "MatxsSubmaterialData";
  string func_name  = "read_6d_data";
  vector<string> str_vec;

  //Line No. 1
  int line_no_ori = line_no;
  int data_no     = n1d + 1;

  str_vec.clear();
  while( static_cast<int>(str_vec.size()) < data_no )
  {
    str_obj.check_string_vector_data_end(text_vec, line_no, class_name, func_name);

    str_obj.add_string_vector_data(str_vec, str_obj.divide_string_data(text_vec[line_no], 8, 72));
    line_no++;
  }
  str_obj.skip_no_space_string_data(text_vec, line_no);

  if( str_vec[0].find("6d") == string::npos )
  {
    string str_data = "line data : " + text_vec[line_no_ori];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This data is not 6d data in MATXS format.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  hvps.resize(n1d);
  for(int i=1; i<data_no; i++)
  {
    hvps[i-1] = str_vec[i];
  }
  str_vec.clear();

  //Line No. 2
  data_no = 2*n1d;

  str_vec.clear();
  while( static_cast<int>(str_vec.size()) < data_no )
  {
    str_obj.check_string_vector_data_end(text_vec, line_no, class_name, func_name);

    str_obj.add_string_vector_data(str_vec, str_obj.divide_string_data(text_vec[line_no], 6, 72));
    line_no++;
  }
  str_obj.skip_no_space_string_data(text_vec, line_no);

  nfg.resize(n1d);
  nlg.resize(n1d);

  int ele_no = 0;
  for(int i=0; i<n1d; i++)
  {
    nfg[i] = numeric_string_cast<Integer>(str_vec[ele_no]);
    ele_no++;
  }
  for(int i=0; i<n1d; i++)
  {
    nlg[i] = numeric_string_cast<Integer>(str_vec[ele_no]);
    ele_no++;
  }
  str_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsSubmaterialData::read_7d_data(vector<string>& text_vec, int& line_no)
{
  StringUtils str_obj;
  string class_name = "MatxsSubmaterialData";
  string func_name  = "read_7d_data";
  vector<string> str_vec;

  //Line No. 1
  int line_no_ori = line_no;
  int data_no     = 1;
  vector<int> data_no_vec;

  vps.resize(n1d);
  for(int i=0; i<n1d; i++)
  {
    int ng2_no = nlg[i] - nfg[i] + 1;

    if( data_no + ng2_no > matxw_def )
    {
      data_no_vec.push_back(data_no);
      data_no = 1;
    }

    data_no += ng2_no;
    vps[i].resize(ng2_no);
  }

  if( data_no > 1 )
  {
    data_no_vec.push_back(data_no);
  }

  str_vec.clear();
  for(int i=0; i<static_cast<int>(data_no_vec.size()); i++)
  {
    vector<string> str_vec_each;
    while( static_cast<int>(str_vec_each.size()) < data_no_vec[i] )
    {
      str_obj.check_string_vector_data_end(text_vec, line_no, class_name, func_name);

      str_obj.add_string_vector_data(str_vec_each, str_obj.divide_string_data(text_vec[line_no], 12, 72));
      line_no++;
    }

    if( i == 0 )
    {
      str_vec.push_back(str_vec_each[0]);
    }

    for(int j=1; j<data_no_vec[i]; j++)
    {
      str_vec.push_back(str_vec_each[j]);
    }
    str_vec_each.clear();
  }
  str_obj.skip_no_space_string_data(text_vec, line_no);

  if( str_vec[0].find("7d") == string::npos )
  {
    string str_data = "line data : " + text_vec[line_no_ori];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This data is not 7d data in MATXS format.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int ele_no = 1;
  for(int i=0; i<static_cast<int>(vps.size()); i++)
  {
    for(int j=0; j<static_cast<int>(vps[i].size()); j++)
    {
      vps[i][j] = numeric_string_cast<Real>(str_vec[ele_no]);
      ele_no++;
    }
  }
  str_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MatxsSubmaterialData::write_data()
{
  StringUtils str_obj;

  vector<string> text, str_vec;
  text.clear();
  str_vec.clear();

  //Write 6d data
  if( static_cast<int>(nfg.size()) > 0 )
  {
    //Line No. 1
    string header = " 6d";
    str_vec.push_back(str_obj.get_formatted_string_data(header, 8));
    for(int i=0; i<static_cast<int>(hvps.size()); i++)
    {
      str_vec.push_back(str_obj.get_formatted_string_data(hvps[i], 8));
    }
    str_obj.add_string_vector_data(text, str_obj.get_merged_string_vector_data(str_vec, 9));
    str_vec.clear();

    //Line No. 2
    for(int i=0; i<static_cast<int>(nfg.size()); i++)
    {
      str_vec.push_back(str_obj.get_formatted_int_data(nfg[i],-6));
    }

    for(int i=0; i<static_cast<int>(nlg.size()); i++)
    {
      str_vec.push_back(str_obj.get_formatted_int_data(nlg[i],-6));
    }
    str_obj.add_string_vector_data(text, str_obj.get_merged_string_vector_data(str_vec, 12));
    str_vec.clear();
  }

  //Write 7d data
  if( static_cast<int>(vps.size()) > 0 )
  {
    string header = " 7d";
    str_vec.push_back(str_obj.get_formatted_string_data(header, 12));
    for(int i=0; i<static_cast<int>(vps.size()); i++)
    {
      int j_max = static_cast<int>(vps[i].size());
      if( static_cast<int>(str_vec.size()) + j_max > matxw_def )
      {
        str_obj.add_string_vector_data(text, str_obj.get_merged_string_vector_data(str_vec, 6));
        str_vec.clear();

        str_vec.push_back(str_obj.get_formatted_string_data(header, 12));
      }

      for(int j=0; j<j_max; j++)
      {
        str_vec.push_back(str_obj.get_formatted_real_data(vps[i][j], 12));
      }
    }

    if( static_cast<int>(str_vec.size()) > 1 )
    {
      str_obj.add_string_vector_data(text, str_obj.get_merged_string_vector_data(str_vec, 6));
    }
    str_vec.clear();
  }

  //Write 8d - 10d data
  for(int i=0; i<static_cast<int>(matrix_obj.size()); i++)
  {
    str_obj.add_string_vector_data(text, matrix_obj[i].write_data());
  }

  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MatxsSubmaterialData::get_loc_no()
{
  Integer loc_no = 0;

  //Count 6d
  if( static_cast<int>(nfg.size()) > 0 )
  {
    loc_no++;
  }

  //Cout 7d
  if( static_cast<int>(vps.size()) > 0 )
  {
    int no_7d   = 0;
    int data_no = 1;
    for(int i=0; i<static_cast<int>(vps.size()); i++)
    {
      int j_max = static_cast<int>(vps[i].size());
      if( data_no + j_max > matxw_def )
      {
        no_7d++;
        data_no = 1 + j_max;
      }
      else
      {
        data_no += j_max;
      }
    }

    if( data_no > 1 )
    {
      no_7d++;
    }

    loc_no += no_7d;
  }
 
  //Cout 8d - 10d
  for(int i=0; i<static_cast<int>(matrix_obj.size()); i++)
  {
    loc_no += matrix_obj[i].get_loc_no();
  }

  return loc_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MatxsSubmaterialData::set_noutg(Integer int_data)
{
  noutg = int_data;
}
void MatxsSubmaterialData::set_n1d(Integer int_data)
{
  n1d = int_data;
}
void MatxsSubmaterialData::set_n2d(Integer int_data)
{
  n2d = int_data;
}

//6d
void MatxsSubmaterialData::set_hvps(vector<string> str_vec)
{
  hvps = str_vec;
}
void MatxsSubmaterialData::set_nfg(vector<Integer> int_vec)
{
  nfg = int_vec;
}
void MatxsSubmaterialData::set_nlg(vector<Integer> int_vec)
{
  nlg = int_vec;
}

//7d
void MatxsSubmaterialData::set_vps(vector<vector<Real> > real_vec)
{
  vps = real_vec;
}

//8-10d
void MatxsSubmaterialData::set_matrix_obj(vector<MatxsMatrixData> obj_vec)
{
  matrix_obj = obj_vec;
  vector<MatxsMatrixData>().swap(obj_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer MatxsSubmaterialData::get_noutg()
{
  return noutg;
}
Integer MatxsSubmaterialData::get_n1d()
{
  return n1d;
}
Integer MatxsSubmaterialData::get_n2d()
{
  return n2d;
}

//6d
vector<string>  MatxsSubmaterialData::get_hvps()
{
  return hvps;
}
vector<Integer> MatxsSubmaterialData::get_nfg()
{
  return nfg;
}
vector<Integer> MatxsSubmaterialData::get_nlg()
{
  return nlg;
}

//7d
vector<vector<Real> > MatxsSubmaterialData::get_vps()
{
  return vps;
}

//8-10d
vector<MatxsMatrixData> MatxsSubmaterialData::get_matrix_obj()
{
  return matrix_obj;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

// ***** MatxsMatrixData ***** //

//constructor
MatxsMatrixData::MatxsMatrixData(void)
{
  clear();
}

//destructor
MatxsMatrixData::~MatxsMatrixData(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMatrixData::clear()
{
  noutg = 0;

  //8d
  hmtx.clear();
  lord   = 0;
  jconst = 0;
  jband.clear();
  ijj.clear();

  //9d
  VectorClearer clr_obj;
  clr_obj.clear_vec_array3_real(scat);

  //10d
  spec.clear();
  prod.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMatrixData::read_data(vector<string>& text_vec, int& line_no)
{
  if( noutg == 0 )
  {
    string class_name = "MatxsMatrixData";
    string func_name  = "read_data";

    vector<string> err_com;
    err_com.push_back("Please set noutg to read 8d - 10d data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( text_vec[line_no].find("8d") != string::npos )
  {
    read_8d_data(text_vec, line_no);
  }
  if( text_vec[line_no].find("9d") != string::npos )
  {
    read_9d_data(text_vec, line_no);
  }
  if( jconst > 0 )
  {
    read_10d_data(text_vec, line_no);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMatrixData::read_8d_data(vector<string>& text_vec, int& line_no)
{
  StringUtils str_obj;
  string class_name = "MatxsMatrixData";
  string func_name  = "read_8d_data";
  vector<string> str_vec;

  //Line No. 1
  str_vec = str_obj.divide_string_data(text_vec[line_no], 8, 16);

  if( str_vec[0].find("8d") == string::npos )
  {
    string str_data = "line data : " + text_vec[line_no];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This data is not 8d data in MATXS format.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  line_no++;
  str_obj.skip_no_space_string_data(text_vec, line_no);

  hmtx = str_vec[1];
  str_vec.clear();

  //Line No. 2
  int data_no = 2 + 2*noutg;
  while( static_cast<int>(str_vec.size()) < data_no )
  {
    str_obj.check_string_vector_data_end(text_vec, line_no, class_name, func_name);

    str_obj.add_string_vector_data(str_vec, str_obj.divide_string_data(text_vec[line_no], 6, 72));
    line_no++;
  }
  str_obj.skip_no_space_string_data(text_vec, line_no);

  lord   = numeric_string_cast<Integer>(str_vec[0]);
  jconst = numeric_string_cast<Integer>(str_vec[1]);

  jband.resize(noutg);
  ijj.resize(noutg);

  int ele_no = 2;
  for(int i=0; i<noutg; i++)
  {
    jband[i] = numeric_string_cast<Integer>(str_vec[ele_no]);
    ele_no++;
  }
  for(int i=0; i<noutg; i++)
  {
    ijj[i] = numeric_string_cast<Integer>(str_vec[ele_no]);
    ele_no++;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMatrixData::read_9d_data(vector<string>& text_vec, int& line_no)
{
  StringUtils str_obj;
  string class_name = "MatxsMatrixData";
  string func_name  = "read_9d_data";
  vector<string> str_vec;

  int line_no_ori = line_no;
  int data_no     = 1;
  vector<int> data_no_vec;

  for(int i=0; i<static_cast<int>(jband.size()); i++)
  {

    if( data_no + jband[i] * lord > matxw_def )
    {
      data_no_vec.push_back(data_no);
      data_no = 1;
    }

    data_no += jband[i] * lord;
  }

  if( data_no > 1 )
  {
    data_no_vec.push_back(data_no);
  }
  else
  {
    VectorClearer clr_obj;
    clr_obj.clear_vec_array3_real(scat);

    line_no++;
    return;
  }

  str_vec.clear();
  for(int i=0; i<static_cast<int>(data_no_vec.size()); i++)
  {
    vector<string> str_vec_each;
    while( static_cast<int>(str_vec_each.size()) < data_no_vec[i] )
    {
      str_obj.check_string_vector_data_end(text_vec, line_no, class_name, func_name);

      str_obj.add_string_vector_data(str_vec_each, str_obj.divide_string_data(text_vec[line_no], 12, 72));
      line_no++;
    }

    if( i == 0 )
    {
      str_vec.push_back(str_vec_each[0]);
    }

    for(int j=1; j<data_no_vec[i]; j++)
    {
      str_vec.push_back(str_vec_each[j]);
    }
    str_vec_each.clear();
  }
  str_obj.skip_no_space_string_data(text_vec, line_no);

  if( str_vec[0].find("9d") == string::npos )
  {
    string str_data = "line data : " + text_vec[line_no_ori];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This data is not 9d data in MATXS format.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int ele_no = 1;
  int i_max  = static_cast<int>(jband.size());
  scat.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(lord);
    scat[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(jband[i]);
      scat[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        scat[i][j][k] = numeric_string_cast<Real>(str_vec[ele_no]);
        ele_no++;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMatrixData::read_10d_data(vector<string>& text_vec, int& line_no)
{
  StringUtils str_obj;
  string class_name = "MatxsMatrixData";
  string func_name  = "read_10d_data";
  vector<string> str_vec;

  int line_no_ori = line_no;
  int data_no     = 1 + noutg + jconst;

  str_vec.clear();
  while( static_cast<int>(str_vec.size()) < data_no )
  {
    str_obj.check_string_vector_data_end(text_vec, line_no, class_name, func_name);

    str_obj.add_string_vector_data(str_vec, str_obj.divide_string_data(text_vec[line_no], 12, 72));
    line_no++;
  }
  str_obj.skip_no_space_string_data(text_vec, line_no);

  if( str_vec[0].find("10d") == string::npos )
  {
    string str_data = "line data : " + text_vec[line_no_ori];

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("This data is not 10d data in MATXS format.");
    err_com.push_back("Please check the MATXS file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int ele_no = 1;
  spec.resize(noutg);
  prod.resize(jconst);
  for(int i=0; i<noutg; i++)
  {
    spec[i] = numeric_string_cast<Real>(str_vec[ele_no]);
    ele_no++;
  } 
  for(int i=0; i<jconst; i++)
  {
    prod[i] = numeric_string_cast<Real>(str_vec[ele_no]);
    ele_no++;
  } 
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MatxsMatrixData::write_data()
{
  StringUtils str_obj;

  vector<string> text, str_vec;
  text.clear();
  str_vec.clear();

  //Write 8d data
  if( static_cast<int>(jband.size()) > 0 )
  {
    //Line No. 1
    string header = " 8d";
    str_vec.push_back(str_obj.get_formatted_string_data(header, 8));
    str_vec.push_back(str_obj.get_formatted_string_data(hmtx,   8));
    text.push_back(str_obj.get_merged_string_vector_data(str_vec));
    str_vec.clear();

    //Line No. 2
    str_vec.push_back(str_obj.get_formatted_int_data(lord,  -6));
    str_vec.push_back(str_obj.get_formatted_int_data(jconst,-6));
    for(int i=0; i<static_cast<int>(jband.size()); i++)
    {
      str_vec.push_back(str_obj.get_formatted_int_data(jband[i],-6));
    }
    for(int i=0; i<static_cast<int>(ijj.size()); i++)
    {
      str_vec.push_back(str_obj.get_formatted_int_data(ijj[i],-6));
    }
    str_obj.add_string_vector_data(text, str_obj.get_merged_string_vector_data(str_vec, 12));
    str_vec.clear();
  }

  //Write 9d data
  if( static_cast<int>(scat.size()) > 0 )
  {
    string header = " 9d";
    str_vec.push_back(str_obj.get_formatted_string_data(header, 12));
    for(int i=0; i<static_cast<int>(scat.size()); i++)
    {
      int j_max = static_cast<int>(scat[i].size());
      if( j_max == 0 )
      {
        continue;
      }

      int k_max = static_cast<int>(scat[i][0].size());
      if( static_cast<int>(str_vec.size()) + j_max * k_max > matxw_def )
      {
        str_obj.add_string_vector_data(text, str_obj.get_merged_string_vector_data(str_vec, 6));
        str_vec.clear();

        str_vec.push_back(str_obj.get_formatted_string_data(header, 12));
      }
      
      for(int j=0; j<j_max; j++)
      {
        for(int k=0; k<k_max; k++)
        {
          str_vec.push_back(str_obj.get_formatted_real_data(scat[i][j][k], 12));
        }
      }
    }

    if( static_cast<int>(str_vec.size()) > 1 )
    {
      str_obj.add_string_vector_data(text, str_obj.get_merged_string_vector_data(str_vec, 6));
    }
    str_vec.clear();
  }
  else if( static_cast<int>(jband.size()) > 0 )
  {
    string header = " 9d";
    str_vec.push_back(str_obj.get_formatted_string_data(header, 12));
    str_obj.add_string_vector_data(text, str_obj.get_merged_string_vector_data(str_vec, 6));
  }

  //Write 10d data
  if( static_cast<int>(spec.size()) > 0 )
  {
    string header = "10d";
    str_vec.push_back(str_obj.get_formatted_string_data(header, 12));
    for(int i=0; i<static_cast<int>(spec.size()); i++)
    {
      str_vec.push_back(str_obj.get_formatted_real_data(spec[i], 12));
    }
    for(int i=0; i<static_cast<int>(prod.size()); i++)
    {
      str_vec.push_back(str_obj.get_formatted_real_data(prod[i], 12));
    }
    str_obj.add_string_vector_data(text, str_obj.get_merged_string_vector_data(str_vec, 6));
    str_vec.clear();  
  }

  return text; 
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer MatxsMatrixData::get_loc_no()
{
  Integer loc_no = 0;

  //Count 8d
  if( static_cast<int>(jband.size()) > 0 )
  {
    loc_no++;
  }

  //Cout 9d
  if( static_cast<int>(scat.size()) > 0 )
  {
    int no_9d   = 0;
    int data_no = 1;
    for(int i=0; i<static_cast<int>(scat.size()); i++)
    {
      int j_max = static_cast<int>(scat[i].size());
      if( j_max > 0 )
      {
        int k_max = static_cast<int>(scat[i][0].size());
 
        if( data_no + j_max*k_max > matxw_def )
        {
          no_9d++;
          data_no = 1 + j_max*k_max;
        }
        else
        {
          data_no += j_max*k_max;
        }
      }
    }

    if( data_no > 1 )
    {
      no_9d++;
    }

    loc_no += no_9d;
  }
  else if( static_cast<int>(jband.size()) > 0 )
  {
    loc_no++;
  }
 
  //Cout 10d
  if( static_cast<int>(spec.size()) > 0 )
  {
    loc_no++;
  }

  return loc_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void MatxsMatrixData::set_noutg(Integer int_data)
{
  noutg = int_data;
}

//8d
void MatxsMatrixData::set_hmtx(string str_data)
{
  hmtx = str_data;
}
void MatxsMatrixData::set_lord(Integer int_data)
{
  lord = int_data;
}
void MatxsMatrixData::set_jconst(Integer int_data)
{
  jconst = int_data;
}
void MatxsMatrixData::set_jband(vector<Integer> int_vec)
{
  jband = int_vec;
}
void MatxsMatrixData::set_ijj(vector<Integer> int_vec)
{
  ijj = int_vec;
}

//9d
void MatxsMatrixData::set_scat(vector<vector<vector<Real> > > real_vec)
{
  scat = real_vec;
}

//10d
void MatxsMatrixData::set_spec(vector<Real> real_vec)
{
  spec = real_vec;
}
void MatxsMatrixData::set_prod(vector<Real> real_vec)
{
  prod = real_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer         MatxsMatrixData::get_noutg()
{
  return noutg;
}

//8d
string          MatxsMatrixData::get_hmtx()
{
  return hmtx;
}
Integer         MatxsMatrixData::get_lord()
{
  return lord;
}
Integer         MatxsMatrixData::get_jconst()
{
  return jconst;
}
vector<Integer> MatxsMatrixData::get_jband()
{
  return jband;
}
vector<Integer> MatxsMatrixData::get_ijj()
{
  return ijj;
}

//9d
vector<vector<vector<Real> > > MatxsMatrixData::get_scat()
{
  return scat;
}

//10d
vector<Real> MatxsMatrixData::get_spec()
{
  return spec;
}
vector<Real> MatxsMatrixData::get_prod()
{
  return prod;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

