#include "GasProduction/GasProductionXSCalculatorByNjoyInput.hpp"

using namespace frendy;

//constructor
GasProductionXSCalculatorByNjoyInput::GasProductionXSCalculatorByNjoyInput(void)
{
  clear();
}

//destructor
GasProductionXSCalculatorByNjoyInput::~GasProductionXSCalculatorByNjoyInput(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByNjoyInput::calc_gas_product_xs()
{
  if( calc_flg == 1 )
  {
    return;
  }
  calc_flg = 1;

  cout << "****************************** Gas production XS calculation ******************************";
  cout << endl << endl;
  time_obj.output_current_time();

  boost::timer::cpu_timer timer_total;

  set_input_data();
  output_input_file_name();

  EndfTapeDivider div_obj;
  div_obj.set_file_name(pendf_input_name);
  vector<Integer>       mat_list  = div_obj.get_mat_list();
  vector<vector<Real> > temp_list = div_obj.get_temp_list();

  nucl_data_obj_ori = store_obj.get_nucl_data_obj_no_cov(endf_file_name);
  vector<vector<NuclearDataObject> >().swap(nucl_data_obj_gas);

  int case_no = 1;
  int mat_no  = static_cast<int>(mat_list.size());
  nucl_data_obj_gas.resize(mat_no);
  for(int i=0; i<mat_no; i++)
  {
    int temp_no = static_cast<int>(temp_list[i].size());
    nucl_data_obj_gas[i].resize(temp_no);
    for(int j=0; j<temp_no; j++)
    {
      vector<string> text = div_obj.get_designated_temp_data(mat_list[i], temp_list[i][j]);
      if( static_cast<int>(text.size()) <= 2 )
      {
        continue;
      }

      cout << "Case No. " << case_no
           << " (MAT = " << mat_list[i] << ", TEMP = " << temp_list[i][j] << ")" << endl << endl;
      nucl_data_obj_gas[i][j] = store_obj.get_nucl_data_obj_no_cov(pendf_input_name, mat_list[i], temp_list[i][j]);

      gas_prod_xs_obj.set_nucl_data_obj_ori(nucl_data_obj_ori);
      gas_prod_xs_obj.set_nucl_data_obj_dop(nucl_data_obj_gas[i][j]);
      gas_prod_xs_obj.output_set_data_information();
      gas_prod_xs_obj.calc_gas_production_xs();

      nucl_data_obj_gas[i][j] = gas_prod_xs_obj.get_nucl_data_obj();
      gas_prod_xs_obj.clear();

      case_no++;
    }
  }

  time_total = static_cast<Real>(timer_total.elapsed().wall * 1.0E-9);
  cout << "Total calculation time : " << time_total << " [s]" << endl;
  cout << endl;
  cout << "********************************************************************************************";
  cout << endl << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByNjoyInput::clear()
{
  calc_flg              = 0;
  set_nucl_data_obj_flg = 0;

  nucl_data_obj_ori.clear();
  vector<vector<NuclearDataObject> >().swap(nucl_data_obj_gas);

  gas_prod_xs_obj.clear();
  wri_obj.clear();
  
  input_file_name_njoy.clear();
  start_line_no = 0;

  endf_file_name.clear();
  pendf_input_name.clear();
  pendf_output_name.clear();
  
  time_total = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByNjoyInput::output_input_file_name()
{
  cout << "=== Nuclear data file information ===" << endl;
  cout << "  Input File Name          : " << input_file_name_njoy << endl;
  cout << "  ENDF  File Name          : " << endf_file_name       << endl;
  cout << "  PENDF File Name (input)  : " << pendf_input_name     << endl;
  cout << "  PENDF File Name (output) : " << pendf_output_name    << endl;
  cout << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByNjoyInput::set_input_data()
{
  GasprInputReader read_njoy_obj;
  read_njoy_obj.read_input(input_file_name_njoy, start_line_no);

  endf_file_name    = read_njoy_obj.get_endf_name();
  pendf_input_name  = read_njoy_obj.get_pendf_input_name();
  pendf_output_name = read_njoy_obj.get_pendf_output_name();

  read_njoy_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByNjoyInput::set_njoy_input_file_name(string file_name)
{
  set_njoy_input_file_name(file_name, 0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByNjoyInput::set_njoy_input_file_name(string file_name, int line_no)
{
  calc_flg = 0;
  if( set_nucl_data_obj_flg == 1 )
  {
    cout << endl;
    cout << "***************************************************************" << endl;
    cout << endl;
    cout << "              !!! C A U T I O N !!!" << endl;
    cout << "  Though the set_nucl_data_obj_ori function was called "    << endl;
    cout << "  before the set_njoy_input_file_name function, "           << endl;
    cout << "  the set_nucl_data_obj_ori function was declared."         << endl;
    cout << "  If you want to use the set_nucl_data_obj_ori function, "  << endl;
    cout << "  please call after the set_njoy_input_file_name function." << endl;
    cout << endl;
    cout << "***************************************************************" << endl;
    cout << endl;

    set_nucl_data_obj_flg = 0;
  }
  
  input_file_name_njoy = file_name;
  start_line_no        = line_no;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByNjoyInput::write_pendf_file()
{
  calc_gas_product_xs();
  
  vector<string> text;
  clr_obj.clear_vec_array1_str(text);

  //Get label data
  EndfTapeDivider div_obj;
  div_obj.set_file_name(pendf_input_name);
  string label_data = div_obj.get_label_data();
  div_obj.clear();

  //Open PENDF file
  ofstream fout;
  fout.open(pendf_output_name.c_str());

  if( fout.fail() )
  {
    string class_name = "GasProductionXSCalculatorByNjoyInput";
    string func_name  = "write_pendf_file()";

    string str_data = "  Output file name : " + pendf_output_name;

    vector<string> err_com;
    err_com.push_back("Output file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  
  int mat_no = static_cast<int>(nucl_data_obj_gas.size());
  for(int i=0; i<mat_no; i++)
  {
    int temp_no = static_cast<int>(nucl_data_obj_gas[i].size());
    for(int j=0; j<temp_no; j++)
    {
      if( nucl_data_obj_gas[i][j].get_general_data_obj().get_mat_no() < 0 )
      {
        continue;
      }

      wri_obj.set_nucl_data_obj(nucl_data_obj_gas[i][j]);

      if( i==0 && j==0 )
      {
        wri_obj.set_pendf_label(label_data);
      }
      text = wri_obj.get_endf_text_data();
      wri_obj.clear();

      //Write text data
      int k_max = static_cast<int>(text.size());
      for(int k=0; k<k_max; k++)
      {
        fout << text[k] << endl;
      }
      clr_obj.clear_vec_array1_str(text);
    }
  }

  //Write tape end
  EndfFileWriter efw_obj;
  fout <<  efw_obj.write_tape_end() << endl;

  fout.close();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void GasProductionXSCalculatorByNjoyInput::set_nucl_data_obj_ori(NuclearDataObject& data_obj)
{
  set_nucl_data_obj_flg = 1;
  calc_flg              = 0;

  nucl_data_obj_ori = data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string GasProductionXSCalculatorByNjoyInput::get_njoy_input_file_name()
{
  return input_file_name_njoy;
}

string GasProductionXSCalculatorByNjoyInput::get_endf_file_name()
{
  return endf_file_name;
}

string GasProductionXSCalculatorByNjoyInput::get_pendf_input_name()
{
  return pendf_input_name;
}

string GasProductionXSCalculatorByNjoyInput::get_pendf_output_name()
{
  return pendf_output_name;
}

Real GasProductionXSCalculatorByNjoyInput::get_time_total()
{
  return time_total;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
