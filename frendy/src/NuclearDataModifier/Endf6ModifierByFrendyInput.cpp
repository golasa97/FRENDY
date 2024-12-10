#include "NuclearDataModifier/Endf6ModifierByFrendyInput.hpp"

using namespace frendy;

//constructor
Endf6ModifierByFrendyInput::Endf6ModifierByFrendyInput(void)
{
  clear();
}

//destructor
Endf6ModifierByFrendyInput::~Endf6ModifierByFrendyInput(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierByFrendyInput::clear()
{
  calc_flg = 0;

  linearize_tolerance = -1.0;

  frendy_inp_obj.clear();

  nucl_data_obj_ori.clear();
  nucl_data_obj_add.clear();
  nucl_data_obj_mod.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierByFrendyInput::calc_endf6_modifier()
{
  if( calc_flg != 0 )
  {
    return;
  }

  calc_flg = 1;

  cout << endl;
  cout << "======================================================================" << endl;
  cout << endl;
  cout << "+++ Start ENDF file modification +++" << endl;
  cout << endl;

  int i_max = static_cast<int>(frendy_inp_obj.get_run_flg().size());
  for(int i=0; i<i_max; i++)
  {
    int             run_flg = frendy_inp_obj.get_run_flg()[i];
    vector<Integer> mf_no   = frendy_inp_obj.get_mf_no()[i];
    vector<Integer> mt_no   = frendy_inp_obj.get_mt_no()[i];

    string endf_name_ori = frendy_inp_obj.get_endf_name_ori()[i];
    string endf_name_add = frendy_inp_obj.get_endf_name_add()[i];
    string endf_name_mod = frendy_inp_obj.get_endf_name_mod()[i];

    int run_mode_flg    = run_flg / 100;
    int target_mode_flg = run_flg % 100;
    frendy_inp_obj.output_input_information(run_mode_flg, target_mode_flg, mf_no, mt_no,
                                            endf_name_ori, endf_name_add, endf_name_mod, i);

    modify_endf6_format(run_flg, mf_no, mt_no, endf_name_ori, endf_name_add, endf_name_mod);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierByFrendyInput::modify_endf6_format
                                   (int run_flg, vector<Integer> mf_no, vector<Integer> mt_no,
                                    string endf_name_ori_inp, string endf_name_add_inp, string endf_name_mod_inp)
{
  int run_mode_flg    = run_flg / 100;
  int target_mode_flg = run_flg % 100;

  nucl_data_obj_ori = read_obj.get_nucl_data_obj(endf_name_ori_inp);
  nucl_data_obj_mod = nucl_data_obj_ori;

  if( run_mode_flg == frendy_inp_obj.remove_data_mode )
  {
    remove_endf6_data(target_mode_flg, mf_no, mt_no, nucl_data_obj_mod);
  }
  else if( run_mode_flg == frendy_inp_obj.change_data_mode )
  {
    nucl_data_obj_add = read_obj.get_nucl_data_obj(endf_name_add_inp);
    change_endf6_data(target_mode_flg, mf_no, mt_no, nucl_data_obj_mod, nucl_data_obj_add);
  }
  else if( run_mode_flg == frendy_inp_obj.add_data_mode )
  {
    nucl_data_obj_add = read_obj.get_nucl_data_obj(endf_name_add_inp);
    add_endf6_data(target_mode_flg, mf_no, mt_no, nucl_data_obj_mod, nucl_data_obj_add);
  }
  else if( run_mode_flg == frendy_inp_obj.linearize_data_mode )
  {
    linearize_endf6_data(target_mode_flg, mf_no, mt_no, endf_name_ori_inp, nucl_data_obj_mod);
  }

  endf_wri_obj.set_nucl_data_obj(nucl_data_obj_mod);
  endf_wri_obj.write_pendf_with_tape_end(endf_name_mod_inp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierByFrendyInput::remove_endf6_data
                                   (int target_mode_flg, vector<Integer> mf_no, vector<Integer> mt_no,
                                    NuclearDataObject& nucl_data_obj)
{
  if( target_mode_flg == frendy_inp_obj.mt_mode )
  {
    for(int i=0; i<static_cast<int>(mt_no.size()); i++)
    {
      nucl_mod_obj.remove_specified_reaction_type_data(nucl_data_obj, mt_no[i]);
    }
  }
  else if( target_mode_flg == frendy_inp_obj.mf_mode )
  {
    for(int i=0; i<static_cast<int>(mf_no.size()); i++)
    {
      endf_mod_obj.remove_specified_MF_data(nucl_data_obj, mf_no[i]);
    }
  }
  else if( target_mode_flg == frendy_inp_obj.mf_mt_mode )
  {
    for(int i=0; i<static_cast<int>(mf_no.size()); i++)
    {
      for(int j=0; j<static_cast<int>(mt_no.size()); j++)
      {
        endf_mod_obj.remove_specified_MF_MT_data(nucl_data_obj, mf_no[i], mt_no[j]);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierByFrendyInput::change_endf6_data
                                   (int target_mode_flg, vector<Integer> mf_no, vector<Integer> mt_no,
                                    NuclearDataObject& nucl_data_obj, NuclearDataObject& nucl_data_obj_add)
{
  if( target_mode_flg == frendy_inp_obj.mt_mode )
  {
    for(int i=0; i<static_cast<int>(mt_no.size()); i++)
    {
      nucl_mod_obj.change_specified_reaction_type_data(nucl_data_obj, nucl_data_obj_add, mt_no[i]);
    }
  }
  else if( target_mode_flg == frendy_inp_obj.mf_mode )
  {
    for(int i=0; i<static_cast<int>(mf_no.size()); i++)
    {
      endf_mod_obj.change_specified_MF_data(nucl_data_obj, nucl_data_obj_add, mf_no[i]);
    }
  }
  else if( target_mode_flg == frendy_inp_obj.mf_mt_mode )
  {
    for(int i=0; i<static_cast<int>(mf_no.size()); i++)
    {
      for(int j=0; j<static_cast<int>(mt_no.size()); j++)
      {
        endf_mod_obj.change_specified_MF_MT_data(nucl_data_obj, nucl_data_obj_add, mf_no[i], mt_no[j]);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierByFrendyInput::add_endf6_data
                                   (int target_mode_flg, vector<Integer> mf_no, vector<Integer> mt_no,
                                    NuclearDataObject& nucl_obj, NuclearDataObject& nucl_obj_add)
{
  if( target_mode_flg == frendy_inp_obj.mt_mode )
  {
    for(int i=0; i<static_cast<int>(mt_no.size()); i++)
    {
      nucl_mod_obj.add_specified_reaction_type_data(nucl_obj, nucl_obj_add, mt_no[i]);
    }
  }
  else if( target_mode_flg == frendy_inp_obj.mf_mode )
  {
    for(int i=0; i<static_cast<int>(mf_no.size()); i++)
    {
      endf_mod_obj.add_specified_MF_data(nucl_obj, nucl_obj_add, mf_no[i]);
    }
  }
  else if( target_mode_flg == frendy_inp_obj.mf_mt_mode )
  {
    for(int i=0; i<static_cast<int>(mf_no.size()); i++)
    {
      for(int j=0; j<static_cast<int>(mt_no.size()); j++)
      {
        endf_mod_obj.add_specified_MF_MT_data(nucl_obj, nucl_obj_add, mf_no[i], mt_no[j]);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierByFrendyInput::linearize_endf6_data
                                   (int target_mode_flg, vector<Integer> mf_no, vector<Integer> mt_no,
                                    string endf_name_ori_inp, NuclearDataObject& nucl_data_obj)
{
  linearize_tolerance = frendy_inp_obj.get_linearize_tolerance();

  MultiParser parse_obj;
  parse_obj.set_linearize_tab_flg(parse_obj.linearize_tab_data);
  if( linearize_tolerance > min_value )
  {
    parse_obj.set_linearize_tolerance(linearize_tolerance);
  }

  GeneralDataContainer gen_data_ori = nucl_data_obj.get_general_data_obj();

  EndfFileReader efr_obj;
  efr_obj.set_file_name(endf_name_ori_inp);
  vector<string> text_linearize;
  clr_obj.clear_vec_array1_str(text_linearize);

  if( target_mode_flg == frendy_inp_obj.mt_mode )
  {
    string class_name = "Endf6ModifierByFrendyInput";
    string func_name  = "linearize_endf6_data";

    vector<string> err_com;
    err_com.push_back("MT mode is not available in the linearization process.");
    err_com.push_back("Please use MF and MT mode or MF mode.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  else if( target_mode_flg == frendy_inp_obj.mf_mode )
  {
    for(int j=0; j<static_cast<int>(mf_no.size()); j++)
    {
      cout << "MF number = " << mf_no[j] << endl; 
      vector<Integer> mt_list = efr_obj.get_mt_list(mf_no[j]);

      int i_max = static_cast<int>(mt_list.size());
      if( i_max == 0 )
      {
        string class_name = "Endf6ModifierByFrendyInput";
        string func_name  = "linearize_endf6_data";

        ostringstream oss;
        oss << mf_no[j];
        string str_data01 = "MF number : " + oss.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back("This MF number was not found in the original nuclear data file.");
        err_com.push_back("Please check your input file or nuclear data files.");

        err_obj.output_caution(class_name, func_name, err_com);
      }

      cout << "  Number of reaction types : " << i_max << endl;
      for(int i=0; i<i_max; i++)
      {
        cout << "    Linearized reaction type : " << mt_list[i] << endl;
        text_linearize = efr_obj.get_data(mf_no[j], mt_list[i]);
        NuclearDataObject nucl_data_obj_lin = read_obj.get_nucl_data_obj(text_linearize);
        nucl_data_obj_lin.set_general_data_obj(gen_data_ori);

        endf_mod_obj.change_specified_MF_MT_data(nucl_data_obj, nucl_data_obj_lin, mf_no[j], mt_list[i]);
        nucl_data_obj_lin.clear();
        clr_obj.clear_vec_array1_str(text_linearize);
      }
      cout << endl;
    }
  }
  else if( target_mode_flg == frendy_inp_obj.mf_mt_mode )
  {
    for(int i=0; i<static_cast<int>(mf_no.size()); i++)
    {
      for(int j=0; j<static_cast<int>(mt_no.size()); j++)
      {
        text_linearize = efr_obj.get_data(mf_no[i], mt_no[j]);
        NuclearDataObject nucl_data_obj_lin = read_obj.get_nucl_data_obj(text_linearize);
        nucl_data_obj_lin.set_general_data_obj(gen_data_ori);

        endf_mod_obj.change_specified_MF_MT_data(nucl_data_obj, nucl_data_obj_lin, mf_no[i], mt_no[j]);
        nucl_data_obj_lin.clear();
        clr_obj.clear_vec_array1_str(text_linearize);
      }
    }
  }

  //Modify parse policy in the MultiParser class
  parse_obj.set_linearize_tab_flg(parse_obj.skip_linearize_tab_data);
  parse_obj.set_linearize_tolerance_def();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierByFrendyInput::set_frendy_input(string input_file_name)
{
  calc_flg = 0;
  frendy_inp_obj.read_input_data_from_input_file(input_file_name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6ModifierByFrendyInput::set_frendy_inp_obj(Endf6ModifierInputReader inp_obj)
{
  calc_flg = 0;
  frendy_inp_obj = inp_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Endf6ModifierInputReader Endf6ModifierByFrendyInput::get_frendy_inp_obj()
{
  return frendy_inp_obj;
}

NuclearDataObject Endf6ModifierByFrendyInput::get_nucl_data_obj_ori()
{
  calc_endf6_modifier();
  return nucl_data_obj_ori;
}

NuclearDataObject Endf6ModifierByFrendyInput::get_nucl_data_obj_add()
{
  calc_endf6_modifier();
  return nucl_data_obj_add;
}

NuclearDataObject Endf6ModifierByFrendyInput::get_nucl_data_obj_mod()
{
  calc_endf6_modifier();
  return nucl_data_obj_mod;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real Endf6ModifierByFrendyInput::get_time_total()
{
  return time_total;
}

Real Endf6ModifierByFrendyInput::get_calc_time()
{
  return time_total;
}

