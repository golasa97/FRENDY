#include "NjoyUtils/GrouprInputReader.hpp"

using namespace frendy;

GrouprInputReader::GrouprInputReader(void)
{
  clear();
}

GrouprInputReader::~GrouprInputReader(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GrouprInputReader::read_input(string file_name)
{
  read_input(file_name, 0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GrouprInputReader::read_input(string file_name, int line_no)
{
  clear();

  input_groupr = file_name;

  //open input file
  ifstream fin(input_groupr.c_str());
  if( !fin )
  {
    string class_name = "GrouprInputReader";
    string func_name  = "read_input(string file_name)";

    string str_data = "File name : " + file_name;

    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("There is no input file.");
    err_com.push_back("Please check the input file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //read until groupr input 
  string input_case = "groupr";
  rn_obj.search_each_input(fin, input_case, line_no);

  //read groupr input
  read_file_name(fin);

  while( !fin.eof() )
  {
    int data_no  = static_cast<int>(matb.size());
    int copy_flg = 0;

    Integer  matb_each, ign_each, igg_each, iwt_each, lord_each,
             ntemp_each, nsigz_each, iprint_each, ismooth_each;
    string   title_each;
    read_cards_two_and_three(fin, matb_each, ign_each, igg_each, iwt_each, lord_each,
                                  ntemp_each, nsigz_each, iprint_each, ismooth_each,
                                  title_each, data_no, copy_flg);
    if( matb_each == 0 )
    {
      break;
    }
    else if( copy_flg ==  0 )
    {
      matb.push_back(matb_each);
      ign.push_back(ign_each);
      igg.push_back(igg_each);
      iwt.push_back(iwt_each);
      lord.push_back(lord_each);
      ntemp.push_back(ntemp_each);
      nsigz.push_back(nsigz_each);
      iprint.push_back(iprint_each);
      ismooth.push_back(ismooth_each);
      title.push_back(title_each);

      vector<Real> temp_each, sigz_each, egn_each, egg_each;
      read_temp_and_sigz(fin, ntemp_each, temp_each, nsigz_each, sigz_each);
      temp.push_back(temp_each);
      sigz.push_back(sigz_each);

      egn_each.clear();
      if( ign_each == 1 )
      {
        //string out_data = "egn";
        read_energy_group_structure(fin, "egn", egn_each);
      }
      egn.push_back(egn_each);

      egg_each.clear();
      if( igg_each == 1 )
      {
        //string out_data = "egg";
        read_energy_group_structure(fin, "egg", egg_each);
      }
      egg.push_back(egg_each);

      Real            fehi_each      = 0.0;
      Real            sigpot_each    = 0.0;
      Real            alpha_add_each = 0.0;
      Real            sam_each       = 0.0;
      Real            beta_each      = 0.0;
      Real            alpha_ext_each = 0.0;
      Real            gamma_each     = 0.0;
      Integer         nflmax_each    = 0;
      Integer         jsigz_each     = 0;
      Real            eb_each        = 0.0;
      Real            tb_each        = 0.0;
      Real            ec_each        = 0.0;
      Real            tc_each        = 0.0;
      string          ninwt_each     = "";
      vector<Integer> wght_nbt_each, wght_int_each;
      vector<Real>    wght_e_each,   wght_w_each;
      wght_nbt_each.clear();
      wght_int_each.clear();
      wght_e_each.clear();
      wght_w_each.clear();

      if( iwt_each < 0 )
      {
        read_iwt_option_a(fin, fehi_each, sigpot_each, alpha_add_each, sam_each,
                               beta_each, alpha_ext_each, gamma_each,
                               nflmax_each, ninwt_each, jsigz_each);
      }

      if( iwt_each == -1 || iwt_each == 1 )
      {
        read_iwt_option_b(fin, wght_nbt_each, wght_int_each, wght_e_each, wght_w_each);
      }
      else if( iwt_each == -4 || iwt_each == 4 )
      {
        read_iwt_option_c(fin, eb_each, tb_each, ec_each, tc_each);
      }
      else if( iwt_each == 0 )
      {
        read_iwt_option_d(fin, ninwt_each);
      }

      fehi.push_back(fehi_each);
      sigpot.push_back(sigpot_each);
      alpha_add.push_back(alpha_add_each);
      sam.push_back(sam_each);
      beta.push_back(beta_each);
      alpha_ext.push_back(alpha_ext_each);
      gamma.push_back(gamma_each);
      nflmax.push_back(nflmax_each);
      jsigz.push_back(jsigz_each);
      wght_nbt.push_back(wght_nbt_each);
      wght_int.push_back(wght_int_each);
      wght_e.push_back(wght_e_each);
      wght_w.push_back(wght_w_each);
      eb.push_back(eb_each);
      tb.push_back(tb_each);
      ec.push_back(ec_each);
      tc.push_back(tc_each);
      ninwt.push_back(ninwt_each);
    }
    else //if( copy_flg != 0 )
    {
      matb.push_back(matb_each);
      ign.push_back(ign[data_no-1]);
      igg.push_back(igg[data_no-1]);
      iwt.push_back(iwt[data_no-1]);
      lord.push_back(lord[data_no-1]);
      ntemp.push_back(ntemp[data_no-1]);
      nsigz.push_back(nsigz[data_no-1]);
      iprint.push_back(iprint[data_no-1]);
      ismooth.push_back(ismooth[data_no-1]);
      title.push_back(title[data_no-1]);

      temp.push_back(temp[data_no-1]);
      sigz.push_back(sigz[data_no-1]);
      egn.push_back(egn[data_no-1]);
      egg.push_back(egg[data_no-1]);

      fehi.push_back(fehi[data_no-1]);
      sigpot.push_back(sigpot[data_no-1]);
      alpha_add.push_back(alpha_add[data_no-1]);
      sam.push_back(sam[data_no-1]);
      beta.push_back(beta[data_no-1]);
      alpha_ext.push_back(alpha_ext[data_no-1]);
      gamma.push_back(gamma[data_no-1]);
      nflmax.push_back(nflmax[data_no-1]);
      jsigz.push_back(jsigz[data_no-1]);
      wght_nbt.push_back(wght_nbt[data_no-1]);
      wght_int.push_back(wght_int[data_no-1]);
      wght_e.push_back(wght_e[data_no-1]);
      wght_w.push_back(wght_w[data_no-1]);
      eb.push_back(eb[data_no-1]);
      tb.push_back(tb[data_no-1]);
      ec.push_back(ec[data_no-1]);
      tc.push_back(tc[data_no-1]);
      ninwt.push_back(ninwt[data_no-1]);
    }

    vector<vector<Integer> > mf_each, mt_each;
    vector<vector<string> >  mtname_each;
    read_mf_and_mt(fin, mf_each, mt_each, mtname_each);
    mf.push_back(mf_each);
    mt.push_back(mt_each);
    mtname.push_back(mtname_each);
  }

  fin.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GrouprInputReader::read_file_name(ifstream& fin)
{
  string line_data;
  vector<string> input_data;

  //Card 01
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  int i_max = static_cast<int>(input_data.size());
  if( i_max > 4 )
  {
    i_max = 4;
  }
  for(int i=0; i<i_max; i++)
  {
    int j = static_cast<int>(input_data[i].find_first_of("-"));
    if( j >= 0 )
    {
      string class_name = "GrouprInputReader";
      string func_name  = "read_file_name(ifstream& fin)";

      string str_data = "tape no : " + input_data[i];

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("Binary mode, i.e., tape no less than 0, can not treat in FRENDY.");

      if( j==0 )
      {
        err_com.push_back("This file considered as the ascii mode file.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("Please check the input file name.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      input_data[i] = input_data[i].substr(j+1);
    }
  }

  if( i_max < 2 )
  {
    string class_name = "GrouprInputReader";
    string func_name  = "read_file_name(ifstream& fin)";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_groupr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 1 is less than 2.");
    err_com.push_back("In card 1, more than or equal to three integer data are required, i.e., nendf and npend");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  endf_file_name  = "tape" + input_data[0];
  pendf_file_name = "tape" + input_data[1];

  gendf_file_name_inp = "";
  if( i_max > 2 )
  {
    gendf_file_name_inp = "tape" + input_data[2];
  }

  gendf_file_name_out = "";
  if( i_max > 3 )
  {
    gendf_file_name_out = "tape" + input_data[3];
  }
  else
  {
    Integer tape_no_endf  = numeric_string_cast<Integer>(input_data[0]);
    Integer tape_no_pendf = numeric_string_cast<Integer>(input_data[1]);
    Integer tape_no = tape_no_pendf;
    if( tape_no < tape_no_endf )
    {
      tape_no = tape_no_endf;
    }
    tape_no++;

    ostringstream oss_tape;
    oss_tape << tape_no;
    gendf_file_name_out = "tape" + oss_tape.str();

    string class_name = "GrouprInputReader";
    string func_name  = "read_file_name(ifstream& fin)";

    string str_data01 = "Input file name = " + input_groupr;
    string str_data02 = "Input data      = " + line_data;
    string str_data03 = "ngout2          = " + gendf_file_name_out;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 1 is less than 4.");
    err_com.push_back("This input file is not found ngout2.");
    err_com.push_back("The file name of ngout2 is automatically set by nendf and npend data.");

    err_obj.output_caution(class_name, func_name, err_com);
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GrouprInputReader::read_cards_two_and_three
                          (ifstream& fin, Integer& matb_each, Integer& ign_each, Integer& igg_each,
                           Integer& iwt_each, Integer& lord_each, Integer& ntemp_each,
                           Integer& nsigz_each, Integer& iprint_each, Integer& ismooth_each,
                           string&  title_each, int& data_no, int& copy_flg)
{
  string line_data;
  vector<string> input_data;

  //Card 02
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);
  int i_max = static_cast<int>(input_data.size());

  int eof_flg = 0;
  if( fin.eof() )
  {
    eof_flg = 1;
  }
  if( i_max > 0 )
  {
    if( rn_obj.check_input_case(input_data[0]) >= 0 )
    {
      eof_flg = 2;
    }
    else if( numeric_string_cast<Integer>(input_data[0]) == 0 )
    {
      matb_each = 0;
      return;
    }
  }

  if( eof_flg > 0 )
  {
    string class_name = "GrouprInputReader";
    string func_name  = "read_cards_two_and_three(ifstream& fin)";

    vector<string> err_com;
    if( eof_flg == 1 )
    {
      err_com.push_back("This program reached the end of file without finish to the read input data."); 
    }
    else
    {
      err_com.push_back("This program reached the end of groupr input region without finish to read the input data."); 
    }
    err_com.push_back("Reading input file is stopped.");

    err_obj.output_caution(class_name, func_name, err_com);

    matb_each = 0;
    return;
  }

  if( i_max < 5 )
  {
    if( data_no == 0 || (data_no > 0 && i_max > 1) )
    {
      string class_name = "GrouprInputReader";
      string func_name  = "read_cards_two_and_three(ifstream& fin)";

      ostringstream oss;
      oss << input_data.size();
      string str_data01 = "Input file name = " + input_groupr;
      string str_data02 = "Data no         = " + oss.str();
      string str_data03 = "Input data      = " + line_data;

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("The data number of card 2 is less than 5.");
      err_com.push_back("In card 1, more than or equal to five integer data are required,");
      err_com.push_back("i.e., matb, ign, igg, iwt, and lord.");
      err_com.push_back("Please check the input file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  matb_each = numeric_string_cast<Integer>(input_data[0]);
  if( matb_each < 0 )
  {
    string class_name = "GrouprInputReader";
    string func_name  = "read_cards_two_and_three(ifstream& fin)";

    string str_data01 = "Input file name = " + input_groupr;
    string str_data02 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("matb in card 2 is less than 0.");
    err_com.push_back("This option cannot be available in this code.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  copy_flg = 0;
  if( i_max == 1 )
  {
    copy_flg = 1;
    return;
  }

  ign_each  = numeric_string_cast<Integer>(input_data[1]);
  igg_each  = numeric_string_cast<Integer>(input_data[2]);
  iwt_each  = numeric_string_cast<Integer>(input_data[3]);
  lord_each = numeric_string_cast<Integer>(input_data[4]);

  ntemp_each = 1;
  if( i_max > 5 )
  {
    ntemp_each = numeric_string_cast<Integer>(input_data[5]);
  }

  nsigz_each = 1;
  if( i_max > 6 )
  {
    nsigz_each = numeric_string_cast<Integer>(input_data[6]);
  }

  iprint_each = 1;
  if( i_max > 7 )
  {
    iprint_each = numeric_string_cast<Integer>(input_data[7]);
  }

  ismooth_each = 1;
  if( i_max > 8 )
  {
    ismooth_each = numeric_string_cast<Integer>(input_data[8]);
  }

  //Card 03
  getline(fin, line_data);
  input_data = rn_obj.read_line(line_data);

  title_each = "";
  if( static_cast<int>(input_data.size()) > 0 )
  {
    title_each = input_data[0];
  }

  if( static_cast<int>(title_each.length()) > 80 )
  {
    title_each = title_each.substr(0, 80);
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GrouprInputReader::read_temp_and_sigz
                          (ifstream& fin, Integer ntemp_each, vector<Real>& temp_each,
                                          Integer nsigz_each, vector<Real>& sigz_each)
{
  string line_data;
  vector<string> input_data;

  //Card 4
  temp_each.resize(static_cast<int>(ntemp_each));
  int ele_no = 0;
  while( ele_no < ntemp_each )
  {
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    int i_max = static_cast<int>(input_data.size());
    for(int i=0; i<i_max; i++)
    {
      temp_each[ele_no] = numeric_string_cast<Real>(input_data[i]);
      ele_no++;

      if( ele_no >= ntemp_each )
      {
        break;
      }
    }

    if( fin.eof() )
    {
      string class_name = "GrouprInputReader";
      string func_name  = "read_temp_and_sigz(ifstream& fin)";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the temp data in card 4.");
      err_com.push_back("The temp data may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  //Card 5
  sigz_each.resize(static_cast<int>(nsigz_each));
  ele_no = 0;
  while( ele_no < nsigz_each)
  {
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    int i_max = static_cast<int>(input_data.size());
    for(int i=0; i<i_max; i++)
    {
      sigz_each[ele_no] = numeric_string_cast<Real>(input_data[i]);
      ele_no++;

      if( ele_no >= nsigz_each )
      {
        break;
      }
    }

    if( fin.eof() )
    {
      string class_name = "GrouprInputReader";
      string func_name  = "read_temp_and_sigz(ifstream& fin)";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the temp data in card 5.");
      err_com.push_back("The temp data may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GrouprInputReader::read_energy_group_structure
                          (ifstream& fin, string data_name, vector<Real>& ene_vec)
{
  string line_data;
  vector<string> input_data;

  //Card 6 and 7
  int ng     = 1;
  int ele_no = 0;
  int ng_flg = 0;
  while( ele_no < ng )
  {
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    int i_max = static_cast<int>(input_data.size());
    for(int i=0; i<i_max; i++)
    {
      if( ng_flg == 0 )
      {
        ng     = numeric_string_cast<int>(input_data[i]) + 1;
        ng_flg = 1; 
        ele_no = 0;

        ene_vec.resize(ng);
      }
      else
      {
        ene_vec[ele_no] = numeric_string_cast<Real>(input_data[i]);
        ele_no++;

        if( ele_no >= ng )
        {
          break;
        }
      }
    }

    if( fin.eof() )
    {
      string class_name = "GrouprInputReader";
      string func_name  = "read_energy_group_structure";
      string str_data   = "Read data : " + data_name;

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("The input file is reached the end until reading the energy group structure data in card 6 and 7.");
      err_com.push_back("The temp data may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GrouprInputReader::read_iwt_option_a
                          (ifstream& fin, Real& fehi_each, Real& sigpot_each, Real& alpha_add_each,
                           Real& sam_each, Real& beta_each, Real& alpha_ext_each, Real& gamma_each,
                           Integer& nflmax_each, string& ninwt_each, Integer& jsigz_each)
{
  string line_data;
  vector<string> input_data;

  //Card 08a
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);
  int i_max = static_cast<int>(input_data.size());

  if( i_max < 3 )
  {
    string class_name = "GrouprInputReader";
    string func_name  = "read_iwt_option_a";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_groupr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 8a is less than 3.");
    err_com.push_back("In card 8a, more than or equal to three data are required, i.e., fehi, sigpot, and nflmax.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  fehi_each   = numeric_string_cast<Real>(input_data[0]);
  sigpot_each = numeric_string_cast<Real>(input_data[1]);
  nflmax_each = numeric_string_cast<Integer>(input_data[2]);

  ninwt_each = "";
  if( i_max > 3 )
  {
    int j = static_cast<int>(input_data[3].find_first_of("-"));
    if( j >= 0 )
    {
      string class_name = "GrouprInputReader";
      string func_name  = "read_iwt_option_a";

      string str_data = "tape no of ninwt : " + input_data[3];

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("Binary mode, i.e., tape no of ninwt is less than 0, can not treat in FRENDY.");

      if( j==0 )
      {
        err_com.push_back("This file considered as the ascii mode file.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("Please check the input file name.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      input_data[3] = input_data[3].substr(j+1);
    }

    ninwt_each = "tape" + input_data[3];
  }

  jsigz_each = 0;
  if( i_max > 4 )
  {
    jsigz_each = numeric_string_cast<Integer>(input_data[4]);
  }

  alpha_add_each = 0.0;
  if( i_max > 5 )
  {
    alpha_add_each = numeric_string_cast<Real>(input_data[5]);
  }

  sam_each = 0.0;
  if( i_max > 6 )
  {
    sam_each = numeric_string_cast<Real>(input_data[6]);
  }

  beta_each = 0.0;
  if( i_max > 7 )
  {
    beta_each = numeric_string_cast<Real>(input_data[7]);
  }

  alpha_ext_each = 0.0;
  if( i_max > 8 )
  {
    alpha_ext_each = numeric_string_cast<Real>(input_data[8]);
  }

  gamma_each = 0.0;
  if( i_max > 9 )
  {
    gamma_each = numeric_string_cast<Real>(input_data[9]);
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GrouprInputReader::read_iwt_option_b
                          (ifstream& fin, vector<Integer>& wght_nbt_each, vector<Integer>& wght_int_each,
                                          vector<Real>& wght_e_each, vector<Real>& wght_w_each)
{
  string line_data;
  vector<string> input_data;

  //Card 08b
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  int i_max = static_cast<int>(input_data.size());
  if( i_max < 6 )
  {
    string class_name = "GrouprInputReader";
    string func_name  = "read_iwt_option_b";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_groupr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of first line of card 8b is less than 6.");
    err_com.push_back("The data number of first line of card 8b is six, i.e., 0, 0, 0, 0, wght_nbt_no, and wght_ene_no.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int nbt_no = numeric_string_cast<int>(input_data[4]);
  int ene_no = numeric_string_cast<int>(input_data[5]);

  wght_nbt_each.resize(nbt_no);
  wght_int_each.resize(nbt_no);
  wght_e_each.resize(ene_no);
  wght_w_each.resize(ene_no);

  int i_sta = 0;
  if( i_max > 6 )
  {
    i_sta = 6;
  }

  //Read wght_nbt and wght_int
  vector<Integer> int_vec;
  int_vec.resize(nbt_no*2);

  int ele_no = 0;
  while( ele_no < nbt_no*2 )
  {
    if( i_sta == 0 )
    {
      getline(fin, line_data);
      input_data = rn_obj.read_line_without_slash(line_data);
    }

    i_max = static_cast<int>(input_data.size());
    for(int i=i_sta; i<i_max; i++)
    {
      int_vec[ele_no] = numeric_string_cast<Integer>(input_data[i]);
      ele_no++;

      if( ele_no >= nbt_no*2 )
      {
        i_sta = 0;
        if( i+1 < i_max )
        {
          i_sta = i+1;
        }
        break;
      }

      if( i+1 >= i_max )
      {
        i_sta = 0;
      }
    }

    if( fin.eof() )
    {
      string class_name = "GrouprInputReader";
      string func_name  = "read_iwt_option_b";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the temp data in card 8a (wght_nbt and wght_int).");
      err_com.push_back("The wght data may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  ele_no = 0;
  for(int i=0; i<nbt_no; i++)
  {
    wght_nbt_each[i] = int_vec[ele_no];
    wght_int_each[i] = int_vec[ele_no+1];
    ele_no += 2;
  }
  int_vec.clear();

  //Read wght_e and wght_w
  vector<Real> real_vec;
  real_vec.resize(ene_no*2);

  ele_no = 0;
  while( ele_no < ene_no*2 )
  {
    if( i_sta == 0 )
    {
      getline(fin, line_data);
      input_data = rn_obj.read_line_without_slash(line_data);
    }

    i_max = static_cast<int>(input_data.size());
    for(int i=i_sta; i<i_max; i++)
    {
      real_vec[ele_no] = numeric_string_cast<Real>(input_data[i]);
      ele_no++;

      if( ele_no >= ene_no*2 )
      {
        break;
      }

      if( i+1 >= i_max )
      {
        i_sta = 0;
      }
    }

    if( fin.eof() )
    {
      string class_name = "GrouprInputReader";
      string func_name  = "read_iwt_option_b";
      vector<string> err_com;
      err_com.push_back("The input file is reached the end until reading the temp data in card 8a (wght_e and wght_w).");
      err_com.push_back("The wght data may not be appropriate.");
      err_com.push_back("Please check input file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  ele_no = 0;
  for(int i=0; i<ene_no; i++)
  {
    wght_e_each[i] = real_vec[ele_no];
    wght_w_each[i] = real_vec[ele_no+1];
    ele_no += 2;
  }
  real_vec.clear();

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GrouprInputReader::read_iwt_option_c
                          (ifstream& fin, Real& eb_each, Real& tb_each, Real& ec_each, Real& tc_each)
{
  string line_data;
  vector<string> input_data;

  //Card 08c
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);
  int i_max = static_cast<int>(input_data.size());

  if( i_max < 4 )
  {
    string class_name = "GrouprInputReader";
    string func_name  = "read_iwt_option_c";

    ostringstream oss;
    oss << input_data.size();
    string str_data01 = "Input file name = " + input_groupr;
    string str_data02 = "Data no         = " + oss.str();
    string str_data03 = "Input data      = " + line_data;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data number of card 8c is less than 4.");
    err_com.push_back("In card 8c, four data are required, i.e., eb, tb, ec, and tc.");
    err_com.push_back("Please check the input file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  eb_each = numeric_string_cast<Real>(input_data[0]);
  tb_each = numeric_string_cast<Real>(input_data[1]);
  ec_each = numeric_string_cast<Real>(input_data[2]);
  tc_each = numeric_string_cast<Real>(input_data[3]);

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GrouprInputReader::read_iwt_option_d(ifstream& fin, string& ninwt_each)
{
  string line_data;
  vector<string> input_data;

  //Card 08d
  getline(fin, line_data);
  input_data = rn_obj.read_line_without_slash(line_data);

  ninwt_each = "";
  if( static_cast<int>(input_data.size()) > 0 )
  {
    int j = static_cast<int>(input_data[0].find_first_of("-"));
    if( j >= 0 )
    {
      string class_name = "GrouprInputReader";
      string func_name  = "read_iwt_option_d";

      string str_data = "tape no : " + input_data[0];

      vector<string> err_com;
      err_com.push_back(str_data);
      err_com.push_back("Binary mode, i.e., tape no of ninwt is less than 0, can not treat in FRENDY.");

      if( j==0 )
      {
        err_com.push_back("This file considered as the ascii mode file.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("Please check the input file name.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      input_data[0] = input_data[0].substr(j+1);
    }

    ninwt_each = "tape" + input_data[0];
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GrouprInputReader::read_mf_and_mt
                          (ifstream& fin, vector<vector<Integer> >& mf_each,
                                          vector<vector<Integer> >& mt_each,
                                          vector<vector<string> >&  mtname_each)
{
  string line_data;
  vector<string> input_data;

  clr_obj.clear_vec_array2_int(mf_each);
  clr_obj.clear_vec_array2_int(mt_each);
  clr_obj.clear_vec_array2_str(mtname_each);

  int             reflesh_flg = 0;
  vector<Integer> mf_vec, mt_vec;
  vector<string>  mtname_vec;
  mf_vec.clear();
  mt_vec.clear();
  mtname_vec.clear();

  while( !fin.eof() )
  {
    ios::pos_type oldpos = fin.tellg();
    getline(fin, line_data);
    input_data = rn_obj.read_line_without_slash(line_data);

    int i_max = static_cast<int>(input_data.size());
    if( i_max == 0 )
    {
      reflesh_flg = 0;

      if( static_cast<int>(mf_vec.size()) > 0 )
      {
        mf_each.push_back(mf_vec);
        mt_each.push_back(mt_vec);
        mtname_each.push_back(mtname_vec);
      }
      mf_vec.clear();
      mt_vec.clear();
      mtname_vec.clear();
      continue;
    }

    if( rn_obj.check_input_case(input_data[0]) >= 0 )
    {
      fin.seekg(oldpos);
      break;
    }

    if( numeric_string_cast<int>(input_data[0]) >= 100 )
    {
      if( numeric_string_cast<int>(input_data[0]) > 10000000 &&
          numeric_string_cast<int>(input_data[0]) < 50000000 )
      {
        //1zzzaaam: nuclide production for zzzaaam subsection from file  3
        //2zzzaaam: nuclide production for zzzaaam subsection from file  6
        //3zzzaaam: nuclide production for zzzaaam subsection from file  9
        //4zzzaaam: nuclide production for zzzaaam subsection from file 10
      }
      else
      {
        fin.seekg(oldpos);
        break;
      }
    }

    if( numeric_string_cast<int>(input_data[0]) == 0 )
    {
      if( reflesh_flg == 0 )
      {
        fin.seekg(oldpos);
        break;
      }
      reflesh_flg = 0;

      mf_each.push_back(mf_vec);
      mt_each.push_back(mt_vec);
      mtname_each.push_back(mtname_vec);
      mf_vec.clear();
      mt_vec.clear();
      mtname_vec.clear();
      continue;
    }
    reflesh_flg = 1;

    mf_vec.push_back(numeric_string_cast<Integer>(input_data[0]));

    if( i_max > 1 )
    {
      mt_vec.push_back(numeric_string_cast<Integer>(input_data[1]));
    }
    else
    {
      mt_vec.push_back(0);
    }

    if( i_max > 2 )
    {
      mtname_vec.push_back(input_data[2]);
    }
    else
    {
      mtname_vec.push_back("");
    }
  }

  if( static_cast<int>(mf_vec.size()) > 0 )
  {
    mf_each.push_back(mf_vec);
    mt_each.push_back(mt_vec);
    mtname_each.push_back(mtname_vec);
  }

  line_data.clear();
  clr_obj.clear_vec_array1_str(input_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GrouprInputReader::clear()
{
  input_groupr.clear();

  //Card 1
  endf_file_name.clear();
  pendf_file_name.clear();
  gendf_file_name_inp.clear();
  gendf_file_name_out.clear();

  //Card 2
  matb.clear();
  ign.clear();
  igg.clear();
  iwt.clear();
  lord.clear();
  ntemp.clear();
  nsigz.clear();
  iprint.clear();
  ismooth.clear();

  //Card 3
  clr_obj.clear_vec_array1_str(title);

  //Card 4-7
  clr_obj.clear_vec_array2_real(temp);
  clr_obj.clear_vec_array2_real(sigz);
  clr_obj.clear_vec_array2_real(egn);
  clr_obj.clear_vec_array2_real(egg);

  //Card 8
  fehi.clear();
  sigpot.clear();
  alpha_add.clear();
  sam.clear();
  beta.clear();
  alpha_ext.clear();
  gamma.clear();
  nflmax.clear();
  jsigz.clear();
  clr_obj.clear_vec_array2_int(wght_nbt);
  clr_obj.clear_vec_array2_int(wght_int);
  clr_obj.clear_vec_array2_real(wght_e);
  clr_obj.clear_vec_array2_real(wght_w);
  eb.clear();
  tb.clear();
  ec.clear();
  tc.clear();
  clr_obj.clear_vec_array1_str(ninwt);

  //Card 09
  clr_obj.clear_vec_array3_int(mf);
  clr_obj.clear_vec_array3_int(mt);
  clr_obj.clear_vec_array3_str(mtname);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string                   GrouprInputReader::get_input_groupr()
{
  return input_groupr;
}

string                   GrouprInputReader::get_endf_file_name()
{
  return endf_file_name;
}

string                   GrouprInputReader::get_pendf_file_name()
{
  return pendf_file_name;
}

string                   GrouprInputReader::get_gendf_file_name_inp()
{
  return gendf_file_name_inp;
}

string                   GrouprInputReader::get_gendf_file_name_out()
{
  return gendf_file_name_out;
}

string                   GrouprInputReader::get_ace_file_name()
{
  string ace_file_name = gendf_file_name_out + "_ace";
  return ace_file_name;
}

string                   GrouprInputReader::get_mcnp_dir_name()
{
  string mcnp_dir_name = gendf_file_name_out + "_xsdir";
  return mcnp_dir_name;
}

vector<Integer>          GrouprInputReader::get_matb()
{
  return matb;
}

vector<Integer>          GrouprInputReader::get_ign()
{
  return ign;
}

vector<Integer>          GrouprInputReader::get_igg()
{
  return igg;
}

vector<Integer>          GrouprInputReader::get_iwt()
{
  return iwt;
}

vector<Integer>          GrouprInputReader::get_lord()
{
  return lord;
}

vector<Integer>          GrouprInputReader::get_ntemp()
{
  return ntemp;
}

vector<Integer>          GrouprInputReader::get_nsigz()
{
  return nsigz;
}

vector<Integer>          GrouprInputReader::get_ismooth()
{
  return ismooth;
}

vector<Integer>          GrouprInputReader::get_iprint()
{
  return iprint;
}

vector<string>           GrouprInputReader::get_title()
{
  return title;
}

vector<vector<Real> >    GrouprInputReader::get_temp()
{
  return temp;
}

vector<vector<Real> >    GrouprInputReader::get_sigz()
{
  return sigz;
}

vector<vector<Real> >    GrouprInputReader::get_egn()
{
  return egn;
}

vector<vector<Real> >    GrouprInputReader::get_egg()
{
  return egg;
}

vector<Real>             GrouprInputReader::get_fehi()
{
  return fehi;
}

vector<Real>             GrouprInputReader::get_sigpot()
{
  return sigpot;
}

vector<Real>             GrouprInputReader::get_alpha_add()
{
  return alpha_add;
}

vector<Real>             GrouprInputReader::get_sam()
{
  return sam;
}

vector<Real>             GrouprInputReader::get_beta()
{
  return beta;
}

vector<Real>             GrouprInputReader::get_alpha_ext()
{
  return alpha_ext;
}

vector<Real>             GrouprInputReader::get_gamma()
{
  return gamma;
}

vector<Integer>          GrouprInputReader::get_nflmax()
{
  return nflmax;
}

vector<Integer>          GrouprInputReader::get_jsigz()
{
  return jsigz;
}

vector<vector<Integer> > GrouprInputReader::get_wght_nbt()
{
  return wght_nbt;
}

vector<vector<Integer> > GrouprInputReader::get_wght_int()
{
  return wght_int;
}

vector<vector<Real> >    GrouprInputReader::get_wght_e()
{
  return wght_e;
}

vector<vector<Real> >    GrouprInputReader::get_wght_w()
{
  return wght_w;
}

vector<Real>             GrouprInputReader::get_eb()
{
  return eb;
}

vector<Real>             GrouprInputReader::get_tb()
{
  return tb;
}

vector<Real>             GrouprInputReader::get_ec()
{
  return ec;
}

vector<Real>             GrouprInputReader::get_tc()
{
  return tc;
}

vector<string>           GrouprInputReader::get_ninwt()
{
  return ninwt;
}

vector<vector<vector<Integer> > > GrouprInputReader::get_mf()
{
  return mf;
}

vector<vector<vector<Integer> > > GrouprInputReader::get_mt()
{
  return mt;
}

vector<vector<vector<string> > >  GrouprInputReader::get_mtname()
{
  return mtname;
}


