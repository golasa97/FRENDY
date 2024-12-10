#include "ReconResonance/ResonanceXSReconstructorByNjoyInput.hpp"

using namespace frendy;

//constructor
ResonanceXSReconstructorByNjoyInput::ResonanceXSReconstructorByNjoyInput(void)
{
  clear();
}

//destructor
ResonanceXSReconstructorByNjoyInput::~ResonanceXSReconstructorByNjoyInput(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByNjoyInput::calc_reconstruct_resonance_xs()
{
  if( calc_flg == 1 )
  {
    return;
  }
  calc_flg = 1;

  cout << "****************************** Resonance reconstruct calculation ******************************";
  cout << endl << endl; 
  time_obj.output_current_time();

  boost::timer::cpu_timer time_tot;
  time_total = 0.0;

  set_input_data();
  output_input_file_name();

  check_set_data();
  
  //Divide endf tape in each endf file
  int mat_no_max = static_cast<int>(mat_no_list.size());
  for(int mat_no=0; mat_no<mat_no_max; mat_no++)
  {
    boost::timer::cpu_timer time_each_mat;
    calc_reconstruct_resonance_xs_each_mat(mat_no);
    time_each[mat_no] = static_cast<Real>(time_each_mat.elapsed().wall * 1.0E-9);
  }

  time_total = static_cast<Real>(time_tot.elapsed().wall * 1.0E-9);

  cout << "Total calculation time : " << time_total << " [s]" << endl;
  cout << "  Number of energy grid" << endl;
  for(int mat_no=0; mat_no<mat_no_max; mat_no++)
  {
    cout << "    Material No. " << mat_no << endl;
    int i_max = static_cast<int>(merge_grid[mat_no].size());
    cout << "      Total grid number     : " << i_max << endl;
    cout << "      Resonance grid number : " << endl;
    i_max = static_cast<int>(reso_grid[mat_no].size());
    for(int i=0; i<i_max; i++)
    {
      int j_max = static_cast<int>(reso_grid[mat_no][i].size());
      for(int j=0; j<j_max; j++)
      {
        int k_max = static_cast<int>(reso_grid[mat_no][i][j].size());
        cout << "        " << k_max << "\t(NIS=" << i+1 << ", NER=" << j+1 << ")" << endl;
      }
    }
  }
  cout << endl;
  cout << "***********************************************************************************************";
  cout << endl << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByNjoyInput::calc_reconstruct_resonance_xs_each_mat(int& mat_no)
{
  //Get NuclearDataObject from Endf-6 format data
  nucl_data_obj[mat_no] = store_obj.get_nucl_data_obj_no_cov(endf_file_name, mat_no_list[mat_no]);
  store_obj.clear();

  //Set NuclearDataObject and input data to ResonanceXSReconstructor
  recon_obj.set_nucl_data_obj(nucl_data_obj[mat_no]);
  recon_obj.set_modify_photon_data_flg(1); //modify photon data
  recon_obj.set_err(err[mat_no]);
  recon_obj.set_err_int(err_int[mat_no]);
  recon_obj.set_err_max(err_max[mat_no]);
  recon_obj.set_temp(temp[mat_no]);
  recon_obj.set_additional_grid(additional_grid[mat_no]);

  //Run ResonanceXSReconstructor
  recon_obj.output_set_data_information();
  recon_obj.calc_reconstruct_resonance_xs();

  //Get calculation result
  nucl_data_obj[mat_no] = recon_obj.get_nucl_data_obj();
  non_reso_grid[mat_no] = recon_obj.get_non_reso_grid();
  reso_grid[mat_no]     = recon_obj.get_reso_grid();
  reso_xs[mat_no]       = recon_obj.get_reso_xs();
  merge_grid[mat_no]    = recon_obj.get_merge_grid();
  merge_xs[mat_no]      = recon_obj.get_merge_xs();
  recon_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByNjoyInput::check_set_data()
{
  if( ( mat_no_list.size() < 1 ) || ( err.size() < 1 ) || ( err_int.size() < 1 ) ||
      ( err_max.size() < 1 ) || ( temp.size() < 1 ) || ( err.size() != mat_no_list.size() ) ||
      ( err_int.size() != mat_no_list.size() ) || ( err_max.size() != mat_no_list.size() ) ||
      ( temp.size() != mat_no_list.size() ) || ( comment_line.size() != mat_no_list.size() ) ||
      ( additional_grid.size() != mat_no_list.size() ) )
  {
    string class_name = "ResonanceXSReconstructorByNjoyInput";
    string func_name  = "check_set_data()";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
    oss01 << mat_no_list.size();
    oss02 << err.size();
    oss03 << err_int.size();
    oss04 << err_max.size();
    oss05 << temp.size();
    oss06 << comment_line.size();
    oss07 << additional_grid.size();
    string str_data01 = "Size of material data          : " + oss01.str();
    string str_data02 = "Size of error data             : " + oss02.str();
    string str_data03 = "Size of integral error data    : " + oss03.str();
    string str_data04 = "Size of maximum error data     : " + oss04.str();
    string str_data05 = "Size of temperature data       : " + oss05.str();
    string str_data06 = "Size of comment line data      : " + oss06.str();
    string str_data07 = "Size of additional energy grid : " + oss07.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);
    err_com.push_back(str_data07);

    if( mat_no_list.size() < 1 )
    {
      err_com.push_back("The material data is not set.");
      err_com.push_back("Please set the material data.");
    }
    if( err.size() < 1 )
    {
      err_com.push_back("The error data is not set.");
      err_com.push_back("Please set the error data.");
    }
    if( err_int.size() < 1 )
    {
      err_com.push_back("The error int data is not set.");
      err_com.push_back("Please set the error int data.");
    }
    if( err_max.size() < 1 )
    {
      err_com.push_back("The max error data is not set.");
      err_com.push_back("Please set the max error data.");
    }
    if( temp.size() < 1 )
    {
      err_com.push_back("The temperature data is not set.");
      err_com.push_back("Please set the temperature data.");
    }
  
    if( err.size() != mat_no_list.size() )
    {
      err_com.push_back("The size of error data is not equal to that of material data.");
    }
    if( err_int.size() != mat_no_list.size() )
    {
      err_com.push_back("The size of error int data is not equal to that of material data.");
    }
    if( err_max.size() != mat_no_list.size() )
    {
      err_com.push_back("The size of max error data is not equal to that of material data.");
    }
    if( temp.size() != mat_no_list.size() )
    {
      err_com.push_back("The size of temperature data is not equal to that of material data.");
    }
    if( comment_line.size() != mat_no_list.size() )
    {
      err_com.push_back("The size of comment line is not equal to that of material data.");
    }
    if( additional_grid.size() != mat_no_list.size() )
    {
      err_com.push_back("The size of additional energy grid is not equal to that of material data.");
    }
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByNjoyInput::clear()
{
  calc_flg = 0;

  recon_obj.clear();
  wri_obj.clear();

  input_file_name_njoy.clear();
  start_line_no = 0;
  
  endf_file_name.clear();
  pendf_file_name.clear();
  pendf_label.clear();
  
  mat_no_list.clear();
  err.clear();
  err_int.clear();
  err_max.clear();
  temp.clear();
  
  clr_obj.clear_vec_array2_str(comment_line);
  clr_obj.clear_vec_array2_real8(additional_grid);
  
  vector<NuclearDataObject>().swap(nucl_data_obj);
  
  clr_obj.clear_vec_array2_real8(non_reso_grid);
  clr_obj.clear_vec_array4_real8(reso_grid);
  clr_obj.clear_vec_array5_real8(reso_xs);
  clr_obj.clear_vec_array2_real8(merge_grid);
  clr_obj.clear_vec_array3_real8(merge_xs);

  time_total = 0.0;
  time_each.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByNjoyInput::output_input_file_name()
{
  cout << "=== Nuclear data file information ===" << endl;
  cout << "  Input File Name : " << input_file_name_njoy << endl;
  cout << "  ENDF  File Name : " << endf_file_name       << endl;
  cout << "  PENDF File Name : " << pendf_file_name      << endl;
  cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByNjoyInput::set_input_data()
{
  ReconrInputReader read_njoy_obj;
  read_njoy_obj.read_input(input_file_name_njoy, start_line_no);

  endf_file_name  = read_njoy_obj.get_endf_name();
  pendf_file_name = read_njoy_obj.get_pendf_name();
  pendf_label     = read_njoy_obj.get_label_name();
  mat_no_list     = read_njoy_obj.get_mat();
  err             = read_njoy_obj.get_err();
  err_int         = read_njoy_obj.get_err_int();
  err_max         = read_njoy_obj.get_err_max();
  temp            = read_njoy_obj.get_tempr();
  comment_line    = read_njoy_obj.get_cards();
  additional_grid = read_njoy_obj.get_grid();

  read_njoy_obj.clear();

  //resize matrix
  int i_max = static_cast<int>(mat_no_list.size());
  nucl_data_obj.resize(i_max);
  non_reso_grid.resize(i_max);
  reso_grid.resize(i_max);
  reso_xs.resize(i_max);
  merge_grid.resize(i_max);
  merge_xs.resize(i_max);
  time_each.resize(i_max);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByNjoyInput::set_njoy_input_file_name(string file_name)
{
  set_njoy_input_file_name(file_name, 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByNjoyInput::set_njoy_input_file_name(string file_name, int line_no)
{
  calc_flg = 0;
  input_file_name_njoy = file_name;
  start_line_no        = line_no;

  file_name.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByNjoyInput::write_pendf_file()
{
  vector<vector<string> > text = get_text();
  
  //Write string data to pendf file
  ofstream fout;
  fout.open(pendf_file_name.c_str());

  if( fout.fail() )
  {
    string class_name = "ResonanceXSReconstructorByNjoyInput";
    string func_name  = "write_pendf_file()";

    string str_data = "  Output file name : " + pendf_file_name;

    vector<string> err_com;
    err_com.push_back("Output file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }


  int mat_no_max = static_cast<int>(mat_no_list.size());
  for(int mat_no=0; mat_no<mat_no_max; mat_no++)
  {
    int i_max = static_cast<int>(text[mat_no].size());
    for(int i=0; i<i_max; i++)
    {
      fout << text[mat_no][i] << endl;
    }
  }

  //Write tape end
  EndfFileWriter efw_obj;
  fout <<  efw_obj.write_tape_end() << endl;

  fout.close();
  clr_obj.clear_vec_array2_str(text);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

string        ResonanceXSReconstructorByNjoyInput::get_njoy_input_file_name()
{
  return input_file_name_njoy;
}

string        ResonanceXSReconstructorByNjoyInput::get_endf_file_name()
{
  return endf_file_name;
}

string        ResonanceXSReconstructorByNjoyInput::get_pendf_file_name()
{
  return pendf_file_name;
}

vector<Real8>           ResonanceXSReconstructorByNjoyInput::get_err()
{
  return err;
}

vector<Real8>           ResonanceXSReconstructorByNjoyInput::get_err_int()
{
  return err_int;
}

vector<Real8>           ResonanceXSReconstructorByNjoyInput::get_err_max()
{
  return err_max;
}

vector<Real8>           ResonanceXSReconstructorByNjoyInput::get_temp()
{
  return temp;
}

vector<vector<string> > ResonanceXSReconstructorByNjoyInput::get_comment_line()
{
  return comment_line;
}

vector<vector<Real8> >  ResonanceXSReconstructorByNjoyInput::get_additional_grid()
{
  return additional_grid;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<string> > ResonanceXSReconstructorByNjoyInput::get_text()
{
  calc_reconstruct_resonance_xs();
  
  //get endf file (string data)
  vector<vector<string> > text;
  clr_obj.clear_vec_array2_str(text);

  int mat_no_max = static_cast<int>(mat_no_list.size());
  text.resize(mat_no_max);
  for(int mat_no=0; mat_no<mat_no_max; mat_no++)
  {
    wri_obj.set_nucl_data_obj(nucl_data_obj[mat_no]);
    wri_obj.set_additional_comment(comment_line[mat_no]);
    if( mat_no == 0 )
    {
      wri_obj.set_pendf_label(pendf_label);
      text[mat_no] = wri_obj.get_endf_text_data();
    }
    else
    {
      text[mat_no] = wri_obj.get_endf_text_data_without_label();
    }
    wri_obj.clear();
  }
  return text;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

NuclearDataObject ResonanceXSReconstructorByNjoyInput::get_nucl_data_obj(Integer mat_no)
{
  calc_reconstruct_resonance_xs();

  NuclearDataObject data_obj;
  data_obj.clear();

  int i_max  = static_cast<int>(mat_no_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( mat_no_list[i] == mat_no )
    {
      data_obj = nucl_data_obj[i];
      break;
    }
  }

  return data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<NuclearDataObject> ResonanceXSReconstructorByNjoyInput::get_nucl_data_obj()
{
  calc_reconstruct_resonance_xs();

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Endf6ParserNoCov ResonanceXSReconstructorByNjoyInput::get_endf_obj(Integer mat_no)
{
  calc_reconstruct_resonance_xs();

  Endf6ParserNoCov  endf_obj;
  NuclearDataObject data_obj = get_nucl_data_obj(mat_no);

  conv_obj.convert_frendy_to_endf_format(data_obj, endf_obj);
  data_obj.clear();

  return endf_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Endf6ParserNoCov> ResonanceXSReconstructorByNjoyInput::get_endf_obj()
{
  calc_reconstruct_resonance_xs();

  vector<Endf6ParserNoCov> endf_obj;
  int i_max = static_cast<int>(mat_no_list.size());
  endf_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    conv_obj.convert_frendy_to_endf_format(nucl_data_obj[i], endf_obj[i]);
  }

  return endf_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real8> > ResonanceXSReconstructorByNjoyInput::get_non_reso_grid()
{
  calc_reconstruct_resonance_xs();
  return non_reso_grid;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<vector<Real8> > > > ResonanceXSReconstructorByNjoyInput::get_reso_grid()
{
  calc_reconstruct_resonance_xs();
  return reso_grid;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<vector<vector<Real8> > > > > ResonanceXSReconstructorByNjoyInput::get_reso_xs()
{
  calc_reconstruct_resonance_xs();
  return reso_xs;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real8> > ResonanceXSReconstructorByNjoyInput::get_merge_grid()
{
  calc_reconstruct_resonance_xs();
  return merge_grid;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<Real8> > > ResonanceXSReconstructorByNjoyInput::get_merge_xs()
{
  calc_reconstruct_resonance_xs();
  return merge_xs;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real ResonanceXSReconstructorByNjoyInput::get_time_total()
{
  return time_total;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> ResonanceXSReconstructorByNjoyInput::get_time_each_mat()
{
  return time_each;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

