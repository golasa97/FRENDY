#include "ContinuousEnergyXSUtils/AceDataCompare/DosimetryAceDataCompare.hpp"

using namespace frendy;

//constructor
DosimetryAceDataCompare::DosimetryAceDataCompare(void)
{
  clear();
}

//destructor
DosimetryAceDataCompare::~DosimetryAceDataCompare(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataCompare::clear()
{
  time_read     = 0.0;
  time_read_ref = 0.0;

  class_name.clear();
  func_name.clear();

  ace_comp_obj.clear();

  ace_data_obj.clear();
  ace_data_obj_ref.clear();

  ace_file_name.clear();
  ace_file_name_ref.clear();

  comp_pointer_flg = comp_pointer_mode;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataCompare::comp_ace_data()
{
  boost::timer::cpu_timer timer_comp;

  if( comp_pointer_flg == no_comp_pointer_mode )
  {
    ace_comp_obj.set_comp_data_flg(ace_comp_obj.no_comp_data_number_mode);
  }

  class_name = "DosimetryAceDataCompare";
  
  func_name = "comp_ace_data_header";
  ace_comp_obj.set_information_data(class_name, func_name);
  comp_ace_data_header();
  
  if( comp_pointer_flg == comp_pointer_mode )
  {
    func_name = "comp_ace_data_pointer";
    ace_comp_obj.set_information_data(class_name, func_name);
    comp_ace_data_pointer();
  }
  
  func_name = "comp_ace_data_xs";
  ace_comp_obj.set_information_data(class_name, func_name);
  comp_ace_data_xs();
  
  Real time_comp = static_cast<Real>(timer_comp.elapsed().wall * 1.0E-9);
  Real time_tot  = time_comp;

  cout << endl;
  if( static_cast<int>(ace_file_name_ref.size()) > 0 )
  {
    time_tot += time_read_ref;
    cout << "  Reading time of reference ACE file : " << time_read_ref << " [s]" << endl;
    cout << "  Read reference ACE file end" << endl;
  }

  if( static_cast<int>(ace_file_name.size()) > 0 )
  {
    time_tot += time_read;
    cout << "  Reading time of compared ACE file  : " << time_read << " [s]" << endl;
    cout << "  Read compared ACE file end" << endl;
  }

  if( static_cast<int>(ace_file_name.size()) > 0 || static_cast<int>(ace_file_name_ref.size()) > 0 )
  {
    cout << "  Comparison time                    : " << time_comp << " [s]" << endl;
    cout << "  Total time                         : " << time_tot << " [s]" << endl;
  }
  else
  {
    cout << "  Comparison time : " << time_comp << " [s]" << endl;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataCompare::comp_ace_data_header()
{
  //Line No. 01-02
  ace_comp_obj.comp_title_data(ace_data_obj.get_aw0(),                  ace_data_obj.get_tz(), 
                               ace_data_obj.get_discriptive_data(),     ace_data_obj.get_title_data(),
                               ace_data_obj_ref.get_aw0(),              ace_data_obj_ref.get_tz(), 
                               ace_data_obj_ref.get_discriptive_data(), ace_data_obj_ref.get_title_data());

  //Line No. 03-06
  ace_comp_obj.comp_mat_data(ace_data_obj.get_zi_vec(),     ace_data_obj.get_awr_vec(),
                             ace_data_obj_ref.get_zi_vec(), ace_data_obj_ref.get_awr_vec());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataCompare::comp_ace_data_pointer()
{
  ace_comp_obj.set_comp_data_information("len2");
  ace_comp_obj.comp_int_data(ace_data_obj.get_len2(), ace_data_obj_ref.get_len2());
  ace_comp_obj.set_comp_data_information("za");
  ace_comp_obj.comp_int_data(ace_data_obj.get_za(),   ace_data_obj_ref.get_za());
  ace_comp_obj.set_comp_data_information("ntr");
  ace_comp_obj.comp_int_data(ace_data_obj.get_ntr(),  ace_data_obj_ref.get_ntr());
  ace_comp_obj.set_comp_data_information("lone");
  ace_comp_obj.comp_int_data(ace_data_obj.get_lone(), ace_data_obj_ref.get_lone());
  ace_comp_obj.set_comp_data_information("mtr");
  ace_comp_obj.comp_int_data(ace_data_obj.get_mtr(),  ace_data_obj_ref.get_mtr());
  ace_comp_obj.set_comp_data_information("lsig");
  ace_comp_obj.comp_int_data(ace_data_obj.get_lsig(), ace_data_obj_ref.get_lsig());
  ace_comp_obj.set_comp_data_information("sigd");
  ace_comp_obj.comp_int_data(ace_data_obj.get_sigd(), ace_data_obj_ref.get_sigd());
  ace_comp_obj.set_comp_data_information("end");
  ace_comp_obj.comp_int_data(ace_data_obj.get_end(),  ace_data_obj_ref.get_end());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataCompare::comp_ace_data_xs()
{
  //Ror reaction xs
  ace_comp_obj.set_comp_data_information("reaction_xs_reaction_type");
  ace_comp_obj.comp_list_data(ace_data_obj.get_reaction_xs_reaction_type(),
                              ace_data_obj_ref.get_reaction_xs_reaction_type());

  if( comp_pointer_flg == comp_pointer_mode )
  {
    ace_comp_obj.set_comp_data_information("reaction_xs_pointer");
    ace_comp_obj.comp_list_data(ace_data_obj.get_reaction_xs_pointer(),
                                ace_data_obj_ref.get_reaction_xs_pointer());
  }

  int i_max = static_cast<int>(ace_data_obj_ref.get_reaction_xs_reaction_type().size());
  for(int i=0; i<i_max; i++)
  {
    ace_comp_obj.set_comp_data_position(i+1);

    ace_comp_obj.set_comp_data_information("reaction_xs_range_data, reaction_xs_int_data, reaction_xs_ene_data, reaction_xs_data");
    ace_comp_obj.comp_table_data(ace_data_obj.get_reaction_xs_range_data()[i],
                                 ace_data_obj.get_reaction_xs_int_data()[i],
                                 ace_data_obj.get_reaction_xs_ene_data()[i],
                                 ace_data_obj.get_reaction_xs_data()[i],
                                 ace_data_obj_ref.get_reaction_xs_range_data()[i],
                                 ace_data_obj_ref.get_reaction_xs_int_data()[i],
                                 ace_data_obj_ref.get_reaction_xs_ene_data()[i],
                                 ace_data_obj_ref.get_reaction_xs_data()[i]);
  }


  //Ror production xs
  ace_comp_obj.set_comp_data_information("size of production_xs_state_no_product");
  i_max = static_cast<int>(ace_data_obj_ref.get_production_xs_state_no_product().size());
  ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_production_xs_state_no_product().size()), i_max);
  for(int i=0; i<i_max; i++)
  {
    ace_comp_obj.set_comp_data_information("production_xs_state_no_product");
    ace_comp_obj.comp_list_data(ace_data_obj.get_production_xs_state_no_product()[i],
                                ace_data_obj_ref.get_production_xs_state_no_product()[i]);

    if( comp_pointer_flg == comp_pointer_mode )
    {
      ace_comp_obj.set_comp_data_information("production_xs_pointer");
      ace_comp_obj.comp_list_data(ace_data_obj.get_production_xs_pointer()[i],
                                  ace_data_obj_ref.get_production_xs_pointer()[i]);
    }

    int j_max = static_cast<int>(ace_data_obj_ref.get_production_xs_state_no_product()[i].size());
    for(int j=0; j<j_max; j++)
    {
      ace_comp_obj.set_comp_data_position(i+1, j+1);

      ace_comp_obj.set_comp_data_information("production_xs_range_data, production_xs_int_data, production_xs_ene_data, production_xs_data");
      ace_comp_obj.comp_table_data(ace_data_obj.get_production_xs_range_data()[i][j],
                                   ace_data_obj.get_production_xs_int_data()[i][j],
                                   ace_data_obj.get_production_xs_ene_data()[i][j],
                                   ace_data_obj.get_production_xs_data()[i][j],
                                   ace_data_obj_ref.get_production_xs_range_data()[i][j],
                                   ace_data_obj_ref.get_production_xs_int_data()[i][j],
                                   ace_data_obj_ref.get_production_xs_ene_data()[i][j],
                                   ace_data_obj_ref.get_production_xs_data()[i][j]);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

DosimetryAceDataObject DosimetryAceDataCompare::parse_ace_data_file(string& file_name)
{
  //Read ACE format
  DosimetryAceDataParser parse_obj;
  parse_obj.set_file_name(file_name);
  parse_obj.parse_ace_format();

  //Copy ACE data object and clear read ace format class
  return parse_obj.get_ace_data_obj();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void DosimetryAceDataCompare::set_ace_data_obj(DosimetryAceDataObject& ace_obj,
                                               DosimetryAceDataObject& ace_obj_ref)
{
  ace_file_name.clear();
  ace_file_name_ref.clear();

  ace_data_obj     = ace_obj;
  ace_data_obj_ref = ace_obj_ref;
}

void DosimetryAceDataCompare::set_ace_file_name(string ace_name, string ace_name_ref)
{
  cout << "Read reference data : " << ace_name_ref << endl;
  boost::timer::cpu_timer timer_read_ref;
  ace_file_name_ref = ace_name_ref;
  ace_data_obj_ref  = parse_ace_data_file(ace_name_ref);
  time_read_ref     = static_cast<Real>(timer_read_ref.elapsed().wall * 1.0E-9);

  cout << "Read comparing data : " << ace_name << endl;
  boost::timer::cpu_timer timer_read;
  ace_file_name     = ace_name;
  ace_data_obj      = parse_ace_data_file(ace_name);
  time_read         = static_cast<Real>(timer_read.elapsed().wall * 1.0E-9);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

DosimetryAceDataObject DosimetryAceDataCompare::get_ace_data_obj()
{
  return ace_data_obj;
}

DosimetryAceDataObject DosimetryAceDataCompare::get_ace_data_obj_ref()
{
  return ace_data_obj_ref;
}

string  DosimetryAceDataCompare::get_ace_file_name()
{
  return ace_file_name;
}

string  DosimetryAceDataCompare::get_ace_file_name_ref()
{
  return ace_file_name_ref;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataCompare::set_tolerance_val_def()
{
  ace_comp_obj.set_tolerance_val_def();
}

void DosimetryAceDataCompare::set_tolerance_val(Real tolerance_val)
{
  ace_comp_obj.set_tolerance_val(tolerance_val);
}

Real DosimetryAceDataCompare::get_tolerance_val()
{
  return ace_comp_obj.get_tolerance_val();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void DosimetryAceDataCompare::set_comp_pointer_flg(int comp_flg)
{
  if( comp_flg != comp_pointer_mode && comp_flg != no_comp_pointer_mode )
  {
    func_name  = "set_comp_pointer_flg(int comp_flg)";

    ostringstream oss01;
    oss01 << comp_flg;
    string str_data01 = "comp_flg : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("The available comp_flg is only 0 (comp_pointer_mode) or 1 (no_comp_pointer_mode)");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  comp_pointer_flg = comp_flg;
}

int DosimetryAceDataCompare::get_comp_pointer_flg()
{
  return comp_pointer_flg;
}
