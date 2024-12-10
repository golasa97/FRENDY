#include "ReconResonance/ResonanceXSReconstructorByFrendyInput.hpp"

using namespace frendy;

//constructor
ResonanceXSReconstructorByFrendyInput::ResonanceXSReconstructorByFrendyInput(void)
{
  clear();
}

//destructor
ResonanceXSReconstructorByFrendyInput::~ResonanceXSReconstructorByFrendyInput(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByFrendyInput::clear()
{
  calc_flg               = 0;
  set_frendy_inp_obj_flg = 0;
  set_nucl_data_obj_flg  = 0;

  nucl_data_obj.clear();

  recon_obj.clear();
  frendy_inp_obj.clear();

  time_total = 0.0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByFrendyInput::calc_reconstruct_resonance_xs()
{
  if( calc_flg == 1 )
  {
    return;
  }
  calc_flg = 1;

  check_set_data_flg();

  cout << "****************************** Resonance reconstruct calculation ******************************";
  cout << endl << endl; 
  time_obj.output_current_time();

  boost::timer::cpu_timer time_tot;
  time_total = 0.0;

  //Set NuclearDataObject and input data to ResonanceXSReconstructor
  recon_obj.set_nucl_data_obj(nucl_data_obj);
  recon_obj.set_modify_photon_data_flg(1); //modify photon data
  recon_obj.set_err(frendy_inp_obj.get_error());
  recon_obj.set_err_int(frendy_inp_obj.get_error_integral());
  recon_obj.set_err_max(frendy_inp_obj.get_error_max());
  recon_obj.set_additional_grid(frendy_inp_obj.get_add_grid_data());

  //Run ResonanceXSReconstructor
  recon_obj.output_set_data_information();
  recon_obj.calc_reconstruct_resonance_xs();

  //Get calculation result
  nucl_data_obj = recon_obj.get_nucl_data_obj();
  vector<vector<vector<Real8> > > reso_grid  = recon_obj.get_reso_grid();
  vector<Real8>                   merge_grid = recon_obj.get_merge_grid();
  recon_obj.clear();

  time_total = static_cast<Real>(time_tot.elapsed().wall * 1.0E-9);

  //Output calculation result
  cout << "Total calculation time : " << time_total << " [s]" << endl;
  cout << "  Number of energy grid" << endl;
  int i_max = static_cast<int>(merge_grid.size());
  cout << "    Total grid number     : " << i_max << endl;

  cout << "    Resonance grid number : " << endl;
  i_max = static_cast<int>(reso_grid.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_grid[i].size());
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(reso_grid[i][j].size());
      cout << "        " << k_max
           << "\t(Isotopes No. = " << i+1 << ", Resonance energy ranges No. = " << j+1 << ")" << endl;
    }
  }
  cout << endl;
  cout << "***********************************************************************************************";
  cout << endl << endl;

  //Clear enegy grid data
  clr_obj.clear_vec_array3_real8(reso_grid);
  merge_grid.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByFrendyInput::check_set_data_flg()
{
  if( set_frendy_inp_obj_flg == 0 || set_nucl_data_obj_flg == 0 )
  {
    string class_name = "ResonanceXSReconstructorByFrendyInput";
    string func_name  = "check_set_data_flg()";

    vector<string> err_com;
    if( set_frendy_inp_obj_flg == 0 )
    {
      err_com.push_back("Please set the ReconResonanceInputReader object");
      err_com.push_back("using set_frendy_inp_obj() function.");
    }

    if( set_nucl_data_obj_flg == 0 )
    {
      err_com.push_back("Please set the NuclearDataObject");
      err_com.push_back("using set_nucl_data_obj() function.");
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByFrendyInput::set_frendy_inp_obj(ReconResonanceInputReader inp_obj)
{
  calc_flg               = 0;
  set_frendy_inp_obj_flg = 1;

  frendy_inp_obj = inp_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceXSReconstructorByFrendyInput::set_nucl_data_obj(NuclearDataObject data_obj)
{
  calc_flg              = 0;
  set_nucl_data_obj_flg = 1;

  nucl_data_obj = data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

ReconResonanceInputReader ResonanceXSReconstructorByFrendyInput::get_frendy_inp_obj()
{
  return frendy_inp_obj;
}

NuclearDataObject ResonanceXSReconstructorByFrendyInput::get_nucl_data_obj()
{
  calc_reconstruct_resonance_xs();

  return nucl_data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Real ResonanceXSReconstructorByFrendyInput::get_time_total()
{
  return time_total;
}

Real ResonanceXSReconstructorByFrendyInput::get_calc_time()
{
  return time_total;
}

