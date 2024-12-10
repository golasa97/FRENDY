#include "EndfUtils/GendfWriter/GendfWriter.hpp"

using namespace frendy;

//constructor
GendfWriter::GendfWriter(void)
{
  dummy_label = "GENDF FIlE WRITTEN BY FRENDY";
  clear();
}

//destructor
GendfWriter::~GendfWriter(void)
{
  dummy_label.clear();
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfWriter::write_gendf(string file_name)
{
  if( gendf_label_flg == 0 )
  {
    gendf_label = file_name;
  }

  vector<string> text = get_gendf_text_data();

  //Write to gendf file
  ofstream fout;
  fout.open(file_name.c_str());

  if( fout.fail() )
  {
    string class_name = "GendfWriter";
    string func_name  = "write_gendf(string file_name)";

    string str_data = "  Output file name : " + file_name;

    vector<string> err_com;
    err_com.push_back("Output file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  
  int i_max = static_cast<int>(text.size());
  for(int i=0; i<i_max; i++)
  {
    fout << text[i] << endl;
  }
  fout.close();

  clr_obj.clear_vec_array1_str(text);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfWriter::write_gendf_with_tape_end(string file_name)
{
  if( gendf_label_flg == 0 )
  {
    gendf_label = file_name;
  }

  vector<string> text = get_gendf_text_data();

  //Write to gendf file
  ofstream fout;
  fout.open(file_name.c_str());

  if( fout.fail() )
  {
    string class_name = "GendfWriter";
    string func_name  = "write_gendf_with_tape_end(string file_name)";

    string str_data = "  Output file name : " + file_name;

    vector<string> err_com;
    err_com.push_back("Output file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = static_cast<int>(text.size());
  for(int i=0; i<i_max; i++)
  {
    fout << text[i] << endl;
  }

  //Write tape end
  fout <<  efw_obj.write_tape_end() << endl;
  fout.close();

  clr_obj.clear_vec_array1_str(text);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfWriter::convert_gendf_data(vector<string>& text)
{
  vector<string> text_tmp;
  clr_obj.clear_vec_array1_str(text);
  clr_obj.clear_vec_array1_str(text_tmp);
  
  line_no.clear();
  mf_list.clear();
  mt_list.clear();
  
  efw_obj.set_mat(mat_no);

  //Convert to text data
  //Write MF01
  if( mf01mt451_par.get_ZA() > 0.0 )
  {
    //Write MT451
    if( mf01mt451_par.get_ZA() > 0.0 )
    {
      cout << "    Write GENDF data (MF=01 / MT=451)" << endl;
      text_tmp = mf01mt451_wri.get_gendf_text_data(mf01mt451_par);
      add_text_data(text, text_tmp);
      mf_list.push_back(1);
      mt_list.push_back(451);
    }
    add_file_end(text, 1, 1);
  }
  
  //Write MF03
  int i_max = static_cast<int>(mf03_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      cout << "    Write GENDF data (MF=03 / MT=" << mf03_par[i].get_mt_no() << ")" << endl;
      text_tmp = mf03_wri.get_gendf_text_data(mf03_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(3);
      mt_list.push_back(mf03_par[i].get_mt_no());
    }
    //add_file_end(text, 3, 1);
  }

  //Write MF05
  i_max = static_cast<int>(mf05_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      cout << "    Write GENDF data (MF=05 / MT=" << mf05_par[i].get_mt_no() << ")" << endl;
      text_tmp = mf05_wri.get_gendf_text_data(mf05_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(5);
      mt_list.push_back(mf05_par[i].get_mt_no());
    }
    //add_file_end(text, 5, 1);
  }

  //Write MF06
  i_max = static_cast<int>(mf06_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      cout << "    Write GENDF data (MF=06 / MT=" << mf06_par[i].get_mt_no() << ")" << endl;
      text_tmp = mf06_wri.get_gendf_text_data(mf06_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(6);
      mt_list.push_back(mf06_par[i].get_mt_no());
    }
    //add_file_end(text, 6, 1);
  }

  //Write MF13
  i_max = static_cast<int>(mf13_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      cout << "    Write GENDF data (MF=13 / MT=" << mf13_par[i].get_mt_no() << ")" << endl;
      text_tmp = mf13_wri.get_gendf_text_data(mf13_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(13);
      mt_list.push_back(mf13_par[i].get_mt_no());
    }
    //add_file_end(text, 13, 1);
  }

  //Write MF16
  i_max = static_cast<int>(mf16_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      cout << "    Write GENDF data (MF=16 / MT=" << mf16_par[i].get_mt_no() << ")" << endl;
      text_tmp = mf16_wri.get_gendf_text_data(mf16_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(16);
      mt_list.push_back(mf16_par[i].get_mt_no());
    }
    //add_file_end(text, 16, 1);
  }

  //Write file end
  text.push_back(efw_obj.write_file_end());

  line_no.clear();
  mf_list.clear();
  mt_list.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfWriter::add_text_data(vector<string>& text, vector<string>& text_add)
{
  int i_max = static_cast<int>(text_add.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(text_add[i]);
  }
  line_no.push_back(static_cast<Integer>(text_add.size()) - 1); //erase SEND card
  
  clr_obj.clear_vec_array1_str(text_add);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfWriter::add_file_end(vector<string>& text, Integer mf_no, Integer mt_no)
{
  efw_obj.set_mf_mt(mf_no, mt_no);
  text.push_back(efw_obj.write_mf_end());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfWriter::add_end_of_file(vector<string>& text)
{
  //Write file end
  string text_tmp = efw_obj.write_file_end();
  text.push_back(text_tmp);

  text_tmp.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfWriter::check_set_data()
{
  //Check the all data was set or not
  if( gendf_parser_flg == 0 )
  {
    string class_name = "GendfWriter";
    string func_name  = "check_set_data()";

    vector<string> err_com;
    err_com.push_back("GendfPaser object is not set.");
    err_com.push_back("Please check the program.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfWriter::check_material_number()
{
  ostringstream oss01;
  oss01 << mat_no;
  string str_data01 = "Material number from MF01MT451 : " + oss01.str();

  vector<string> err_com;
  err_com.clear();

  int i_max = static_cast<int>(mf03_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf03_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf03_par[i].get_mat_no();
        oss03 << mf03_par[i].get_mt_no();
        string str_data02 = "Material number from MF03      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();
  
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF03 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf05_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf05_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf05_par[i].get_mat_no();
        oss03 << mf05_par[i].get_mt_no();
        string str_data02 = "Material number from MF05      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF05 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf06_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf06_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf06_par[i].get_mat_no();
        oss03 << mf06_par[i].get_mt_no();
        string str_data02 = "Material number from MF06      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF06 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf13_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf13_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf13_par[i].get_mat_no();
        oss03 << mf13_par[i].get_mt_no();
        string str_data02 = "Material number from MF13      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF13 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf16_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf16_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf16_par[i].get_mat_no();
        oss03 << mf16_par[i].get_mt_no();
        string str_data02 = "Material number from MF16      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF16 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }
  
  if( static_cast<int>(err_com.size()) > 0 )
  {
    string class_name = "GendfWriter";
    string func_name  = "check_material_number()";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfWriter::clear()
{
  gendf_parser_flg = 0;
  
  gendf_parser.clear();
  
  gendf_label_flg   = 0;
  gendf_label.clear();

  clear_parser_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfWriter::clear_parser_data()
{
  mat_no = 0;
  
  line_no.clear();
  mf_list.clear();
  mt_list.clear();

  mf01mt451_par.clear();
  
  vector<GMF03Parser>().swap(mf03_par);
  vector<GMF05Parser>().swap(mf05_par);
  vector<GMF06Parser>().swap(mf06_par);
  vector<GMF13Parser>().swap(mf13_par);
  vector<GMF16Parser>().swap(mf16_par);

  mf01mt451_wri.clear();
  mf03_wri.clear();
  mf05_wri.clear();
  mf06_wri.clear();
  mf13_wri.clear();
  mf16_wri.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfWriter::set_gendf_parser(GendfParser parser_obj)
{
  clear_parser_data();

  gendf_parser_flg = 1;

  gendf_parser = parser_obj;

  mf01mt451_par = parser_obj.get_mf01_mt451_data();

  mf03_par      = parser_obj.get_mf03_data();
  mf05_par      = parser_obj.get_mf05_data();
  mf06_par      = parser_obj.get_mf06_data();
  mf13_par      = parser_obj.get_mf13_data();
  mf16_par      = parser_obj.get_mf16_data();
  
  mat_no = mf01mt451_par.get_mat_no();
  efw_obj.set_mat(mat_no);
  
  //Mat number check
#ifdef DEBUG_MODE
  check_material_number();
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfWriter::set_gendf_label(string str_data)
{
  if( !str_data.empty() )
  {
    gendf_label_flg = 1;
    gendf_label     = str_data;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> GendfWriter::get_gendf_text_data()
{
  vector<string> text, text_new;
  text = get_gendf_text_data_without_label();

  int i_max = static_cast<int>(text.size());
  text_new.resize(i_max+1);

  //Write gendf label at top of the file
  if( static_cast<int>(gendf_label.size()) == 0 )
  {
    gendf_label = dummy_label;
  }
  efw_obj.set_mat(1);
  efw_obj.set_mf_mt(0, 0);
  text_new[0] = efw_obj.write_text(gendf_label);
  if( gendf_label_flg == 0 )
  {
    gendf_label = dummy_label;
  }

  for(int i=0; i<i_max; i++)
  {
    text_new[i+1] = text[i];
  }
  vector<string>().swap(text);

  return text_new;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> GendfWriter::get_gendf_text_data_without_label()
{
  vector<string> text;
  clr_obj.clear_vec_array1_str(text);
  
  check_set_data();

  convert_gendf_data(text);
  
  return text;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

GendfParser      GendfWriter::get_gendf_parser()
{
  return gendf_parser;
}

string GendfWriter::get_gendf_label()
{
  return gendf_label;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

