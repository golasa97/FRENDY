#include "NuclearDataUtils/OtherUtils/Endf6FileStore.hpp"

using namespace frendy;

//constructor
Endf6FileStore::Endf6FileStore(void)
{
  clear();
}

//destructor
Endf6FileStore::~Endf6FileStore(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6FileStore::clear()
{
  div_obj.clear();
  efr_obj.clear();
  parser_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::merge_nucl_data_obj(NuclearDataObject& nucl_data_obj_no_cov,
                                                      NuclearDataObject& nucl_data_obj_cov)
{
  NuclearDataObject nucl_data_obj = nucl_data_obj_no_cov;
  nucl_data_obj_no_cov.clear();

  nucl_data_obj.set_cov_general_data_obj(nucl_data_obj_cov.get_cov_general_data_obj());
  nucl_data_obj.set_cov_reso_data_obj(nucl_data_obj_cov.get_cov_reso_data_obj());
  nucl_data_obj.set_cov_reaction_data_obj(nucl_data_obj_cov.get_cov_reaction_data_obj());
  nucl_data_obj_cov.clear();

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj(vector<string> endf_file_text)
{
  NuclearDataObject nucl_data_obj_no_cov = get_nucl_data_obj_no_cov(endf_file_text);
  NuclearDataObject nucl_data_obj_cov    = get_nucl_data_obj_cov(endf_file_text);

  return merge_nucl_data_obj(nucl_data_obj_no_cov, nucl_data_obj_cov);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj(string endf_name, Integer mat_no, Real temp)
{
  NuclearDataObject nucl_data_obj_no_cov = get_nucl_data_obj_no_cov(endf_name, mat_no, temp);
  NuclearDataObject nucl_data_obj_cov    = get_nucl_data_obj_cov(endf_name, mat_no, temp);

  return merge_nucl_data_obj(nucl_data_obj_no_cov, nucl_data_obj_cov);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj(string endf_name, Integer mat_no)
{
  NuclearDataObject nucl_data_obj_no_cov = get_nucl_data_obj_no_cov(endf_name, mat_no);
  NuclearDataObject nucl_data_obj_cov    = get_nucl_data_obj_cov(endf_name, mat_no);

  return merge_nucl_data_obj(nucl_data_obj_no_cov, nucl_data_obj_cov);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj(string endf_name)
{
  NuclearDataObject nucl_data_obj_no_cov = get_nucl_data_obj_no_cov(endf_name);
  NuclearDataObject nucl_data_obj_cov    = get_nucl_data_obj_cov(endf_name);

  return merge_nucl_data_obj(nucl_data_obj_no_cov, nucl_data_obj_cov);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj_no_cov(vector<string> endf_file_text)
{
  NuclearDataObject nucl_data_obj;

  //Set text data to EndfFileReader class
  efr_obj.set_endf_data(endf_file_text);
  clr_obj.clear_vec_array1_str(endf_file_text);

  //Set EndfFileReader object to Endf6Parser class to parse all data.
  parser_obj.set_endf_file_reader_no_cov(efr_obj);
  efr_obj.clear();

  //Convert Endf6Parser object to NuclearDataObject using Endf6Converter
  conv_obj.convert_endf_format_to_frendy(parser_obj, nucl_data_obj);

  clear();

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj_no_cov(string endf_name, Integer mat_no, Real temp)
{
  NuclearDataObject nucl_data_obj;
  vector<string>    endf_file_text;

  //Set endf file name and mat_no to EndfTapeDivider class to get mat_no data
  div_obj.set_file_name(endf_name);
  endf_file_text = div_obj.get_designated_temp_data(mat_no, temp);
  div_obj.clear();

  //Convert text file to NuclearDataObject
  nucl_data_obj = get_nucl_data_obj_no_cov(endf_file_text);
  clr_obj.clear_vec_array1_str(endf_file_text);

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj_no_cov(string endf_name, Integer mat_no)
{
  NuclearDataObject nucl_data_obj;
  vector<string>    endf_file_text;

  //Set endf file name and mat_no to EndfTapeDivider class to get mat_no data
  div_obj.set_file_name(endf_name);
  vector<Real> temp_list = div_obj.get_temp_list(mat_no);

  int temp_no = static_cast<int>(temp_list.size());
  if( temp_no != 1 )
  {
    string class_name = "Endf6FileStore";
    string func_name  = "get_nucl_data_obj_no_cov(string endf_name, Integer mat_no)";

    vector<string> err_com;
    ostringstream oss01, oss02;
    oss01 << mat_no;
    oss02 << temp_no;

    string str_data01 = "Nuclear data file name     : " + endf_name;
    string str_data02 = "Material number            : " + oss01.str();
    string str_data03 = "Number of temperature data : " + oss02.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    for(int i=0; i<temp_no; i++)
    {
      ostringstream oss03, oss04;
      oss03 << i+1;
      oss04 << temp_list[i];
      string str_data04 = "  No. " + oss03.str() + " : " + oss04.str();
      err_com.push_back(str_data04);
    }

    if( temp_no > 1 )
    {
      err_com.push_back("The number of temperature is larger than one.");
      err_com.push_back("However, this program only convert the first temperature data");
      err_obj.output_caution(class_name, func_name, err_com);
    }
    else //if( temp_no == 0 )
    {
      err_com.push_back("The number of temperature is zero.");
      err_com.push_back("Please check the nuclear data file.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  endf_file_text = div_obj.get_designated_temp_data(mat_no, temp_list[0]);
  div_obj.clear();

  //Convert text file to NuclearDataObject
  nucl_data_obj = get_nucl_data_obj_no_cov(endf_file_text);
  clr_obj.clear_vec_array1_str(endf_file_text);

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj_no_cov(string endf_name)
{
  NuclearDataObject nucl_data_obj;

  //Set endf file name and mat_no to EndfTapeDivider class to get mat_no data
  div_obj.set_file_name(endf_name);
  vector<Integer> mat_list = div_obj.get_mat_list();

  int ele_no = 0;
  int i_max  = static_cast<int>(mat_list.size());
  if( i_max > 1 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mat_list[i] != 0 )
      {
        if( ele_no == 0 )
        {
          ele_no = i;
        }
        else
        {
          string class_name = "Endf6FileStore";
          string func_name  = "get_nucl_data_obj_no_cov(string endf_name)";

          vector<string> err_com;

          ostringstream oss01;
          oss01 << mat_list.size();
          string str_data01 = "Number of material data : " + oss01.str();
          err_com.push_back(str_data01);
          for(int i=0; i<i_max; i++)
          {
            if( mat_list[i] != 0 )
            {
              ostringstream oss02, oss03;
              oss02 << i+1;
              oss03 << mat_list[i];
              string str_data02 = "  No. " + oss02.str() + " : " + oss03.str();
              err_com.push_back(str_data02);
            }
          }

          err_com.push_back("The number of material is larger than one.");
          err_com.push_back("However, this program only convert the first material data");
          err_obj.output_caution(class_name, func_name, err_com);

          break;
        }
      }
    }
  }
  div_obj.clear();

  nucl_data_obj = get_nucl_data_obj_no_cov(endf_name, mat_list[ele_no]);

  return nucl_data_obj;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj_cov(vector<string> endf_file_text)
{
  NuclearDataObject nucl_data_obj;

  //Set text data to EndfFileReader class
  efr_obj.set_endf_data(endf_file_text);
  clr_obj.clear_vec_array1_str(endf_file_text);

  //Set EndfFileReader object to Endf6Parser class to parse all data.
  parser_obj.set_endf_file_reader_cov(efr_obj);
  efr_obj.clear();

  //Convert Endf6Parser object to NuclearDataObject using Endf6Converter
  conv_obj.convert_endf_format_to_frendy(parser_obj, nucl_data_obj);

  clear();

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj_cov(string endf_name, Integer mat_no, Real temp)
{
  NuclearDataObject nucl_data_obj;
  vector<string>    endf_file_text;

  //Set endf file name and mat_no to EndfTapeDivider class to get mat_no data
  div_obj.set_file_name(endf_name);
  endf_file_text = div_obj.get_designated_temp_data(mat_no, temp);
  div_obj.clear();

  //Convert text file to NuclearDataObject
  nucl_data_obj = get_nucl_data_obj_cov(endf_file_text);
  clr_obj.clear_vec_array1_str(endf_file_text);

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj_cov(string endf_name, Integer mat_no)
{
  NuclearDataObject nucl_data_obj;
  vector<string>    endf_file_text;

  //Set endf file name and mat_no to EndfTapeDivider class to get mat_no data
  div_obj.set_file_name(endf_name);
  vector<Real> temp_list = div_obj.get_temp_list(mat_no);
  if( temp_list.size() > 1 )
  {
    string class_name = "Endf6FileStore";
    string func_name  = "get_nucl_data_obj_cov(string endf_name, Integer mat_no)";

    vector<string> err_com;

    ostringstream oss01;
    oss01 << temp_list.size();
    string str_data01 = "Number of temperature data : " + oss01.str();
    err_com.push_back(str_data01);
    for(int i=0; i<static_cast<int>(temp_list.size()); i++)
    {
      ostringstream oss02, oss03;
      oss02 << i+1;
      oss03 << temp_list[i];
      string str_data02 = "  No. " + oss02.str() + " : " + oss03.str();
      err_com.push_back(str_data02);
    }

    err_com.push_back("The number of temperature is larger than one.");
    err_com.push_back("However, this program only convert the first temperature data");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  endf_file_text = div_obj.get_designated_temp_data(mat_no, temp_list[0]);
  div_obj.clear();

  //Convert text file to NuclearDataObject
  nucl_data_obj = get_nucl_data_obj_cov(endf_file_text);
  clr_obj.clear_vec_array1_str(endf_file_text);

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj_cov(string endf_name)
{
  NuclearDataObject nucl_data_obj;

  //Set endf file name and mat_no to EndfTapeDivider class to get mat_no data
  div_obj.set_file_name(endf_name);
  vector<Integer> mat_list = div_obj.get_mat_list();

  int ele_no = 0;
  int i_max  = static_cast<int>(mat_list.size());
  if( i_max > 1 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mat_list[i] != 0 )
      {
        if( ele_no == 0 )
        {
          ele_no = i;
        }
        else
        {
          string class_name = "Endf6FileStore";
          string func_name  = "get_nucl_data_obj_cov(string endf_name)";

          vector<string> err_com;

          ostringstream oss01;
          oss01 << mat_list.size();
          string str_data01 = "Number of material data : " + oss01.str();
          err_com.push_back(str_data01);
          for(int i=0; i<i_max; i++)
          {
            if( mat_list[i] != 0 )
            {
              ostringstream oss02, oss03;
              oss02 << i+1;
              oss03 << mat_list[i];
              string str_data02 = "  No. " + oss02.str() + " : " + oss03.str();
              err_com.push_back(str_data02);
            }
          }

          err_com.push_back("The number of material is larger than one.");
          err_com.push_back("However, this program only convert the first material data");
          err_obj.output_caution(class_name, func_name, err_com);

          break;
        }
      }
    }
  }
  div_obj.clear();

  nucl_data_obj = get_nucl_data_obj_cov(endf_name, mat_list[ele_no]);

  return nucl_data_obj;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj_xs_only(vector<string> endf_file_text)
{
  NuclearDataObject nucl_data_obj;

  //Set text data to EndfFileReader class
  efr_obj.set_endf_data(endf_file_text);
  clr_obj.clear_vec_array1_str(endf_file_text);

  vector<Integer> mt_no_list =  efr_obj.get_mt_list(3);
  int mt_no = static_cast<int>(mt_no_list.size());

  vector<MF03Parser> mf03_obj;
  mf03_obj.resize(mt_no);
  for(int i=0; i<mt_no; i++)
  {
    mf03_obj[i].set_text(efr_obj.get_data(3,mt_no_list[i]));
  }
  efr_obj.clear();

  //Set EndfFileReader object to Endf6Parser class to parse all data.
  parser_obj.clear();
  parser_obj.set_mf03_data(mf03_obj);
  mf03_obj.clear();

  //Convert Endf6Parser object to NuclearDataObject using Endf6Converter
  conv_obj.convert_endf_format_to_frendy(parser_obj, nucl_data_obj);

  clear();

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj_xs_only(string endf_name, Integer mat_no, Real temp)
{
  NuclearDataObject nucl_data_obj;
  vector<string>    endf_file_text;

  //Set endf file name and mat_no to EndfTapeDivider class to get mat_no data
  div_obj.set_file_name(endf_name);
  endf_file_text = div_obj.get_designated_temp_data(mat_no, temp);
  div_obj.clear();

  //Convert text file to NuclearDataObject
  nucl_data_obj = get_nucl_data_obj_xs_only(endf_file_text);
  clr_obj.clear_vec_array1_str(endf_file_text);

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj_xs_only(string endf_name, Integer mat_no)
{
  NuclearDataObject nucl_data_obj;
  vector<string>    endf_file_text;

  //Set endf file name and mat_no to EndfTapeDivider class to get mat_no data
  div_obj.set_file_name(endf_name);
  vector<Real> temp_list = div_obj.get_temp_list(mat_no);
  if( temp_list.size() > 1 )
  {
    string class_name = "Endf6FileStore";
    string func_name  = "get_nucl_data_obj_xs_only(string endf_name, Integer mat_no)";

    vector<string> err_com;

    ostringstream oss01;
    oss01 << temp_list.size();
    string str_data01 = "Number of temperature data : " + oss01.str();
    err_com.push_back(str_data01);
    for(int i=0; i<static_cast<int>(temp_list.size()); i++)
    {
      ostringstream oss02, oss03;
      oss02 << i+1;
      oss03 << temp_list[i];
      string str_data02 = "  No. " + oss02.str() + " : " + oss03.str();
      err_com.push_back(str_data02);
    }

    err_com.push_back("The number of temperature is larger than one.");
    err_com.push_back("However, this program only convert the first temperature data");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  endf_file_text = div_obj.get_designated_temp_data(mat_no, temp_list[0]);
  div_obj.clear();

  //Convert text file to NuclearDataObject
  nucl_data_obj = get_nucl_data_obj_xs_only(endf_file_text);
  clr_obj.clear_vec_array1_str(endf_file_text);

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject Endf6FileStore::get_nucl_data_obj_xs_only(string endf_name)
{
  NuclearDataObject nucl_data_obj;

  //Set endf file name and mat_no to EndfTapeDivider class to get mat_no data
  div_obj.set_file_name(endf_name);
  vector<Integer> mat_list = div_obj.get_mat_list();

  int ele_no = -1;
  int i_max  = static_cast<int>(mat_list.size());
  if( i_max > 1 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mat_list[i] != 0 )
      {
        if( ele_no < 0 )
        {
          ele_no = i;
        }
        else
        {
          string class_name = "Endf6FileStore";
          string func_name  = "get_nucl_data_obj_xs_only(string endf_name)";

          vector<string> err_com;

          ostringstream oss01;
          oss01 << mat_list.size();
          string str_data01 = "Number of material data : " + oss01.str();
          err_com.push_back(str_data01);
          for(int i=0; i<i_max; i++)
          {
            if( mat_list[i] != 0 )
            {
              ostringstream oss02, oss03;
              oss02 << i+1;
              oss03 << mat_list[i];
              string str_data02 = "  No. " + oss02.str() + " : " + oss03.str();
              err_com.push_back(str_data02);
            }
          }

          err_com.push_back("The number of material is larger than one.");
          err_com.push_back("However, this program only convert the first material data");
          err_obj.output_caution(class_name, func_name, err_com);

          break;
        }
      }
    }
  }
  div_obj.clear();

  nucl_data_obj = get_nucl_data_obj_xs_only(endf_name, mat_list[ele_no]);

  return nucl_data_obj;
}

