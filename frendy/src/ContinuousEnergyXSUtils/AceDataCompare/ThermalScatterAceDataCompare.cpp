#include "ContinuousEnergyXSUtils/AceDataCompare/ThermalScatterAceDataCompare.hpp"

using namespace frendy;

//constructor
ThermalScatterAceDataCompare::ThermalScatterAceDataCompare(void)
{
  clear();
}

//destructor
ThermalScatterAceDataCompare::~ThermalScatterAceDataCompare(void)
{
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataCompare::clear()
{
  //time_read     = 0.0;
  //time_read_ref = 0.0;

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

void ThermalScatterAceDataCompare::comp_ace_data()
{
  //boost::timer timer_comp;

  if( comp_pointer_flg == no_comp_pointer_mode )
  {
    ace_comp_obj.set_comp_data_flg(ace_comp_obj.no_comp_data_number_mode);
  }

  class_name = "ThermalScatterAceDataCompare";
  
  func_name = "comp_ace_data_header";
  ace_comp_obj.set_information_data(class_name, func_name);
  comp_ace_data_header();
  
  if( comp_pointer_flg == comp_pointer_mode )
  {
    func_name = "comp_ace_data_pointer";
    ace_comp_obj.set_information_data(class_name, func_name);
    comp_ace_data_pointer();
  }
  
  func_name = "comp_ace_data_inelastic";
  ace_comp_obj.set_information_data(class_name, func_name);
  comp_ace_data_inelastic();
  
  func_name = "comp_ace_data_elastic";
  ace_comp_obj.set_information_data(class_name, func_name);
  comp_ace_data_elastic();

  //Real time_comp = static_cast<Real>(timer_comp.elapsed());
  //Real time_tot  = time_comp;

  cout << endl;
  if( static_cast<int>(ace_file_name_ref.size()) > 0 )
  {
    //time_tot += time_read_ref;
    //cout << "  Reading time of reference ACE file : " << time_read_ref << " [s]" << endl;
    cout << "  Read reference ACE file end" << endl;
  }

  if( static_cast<int>(ace_file_name.size()) > 0 )
  {
    //time_tot += time_read;
    //cout << "  Reading time of compared ACE file  : " << time_read << " [s]" << endl;
    cout << "  Read compared ACE file end" << endl;
  }

  //if( static_cast<int>(ace_file_name.size()) > 0 || static_cast<int>(ace_file_name_ref.size()) > 0 )
  //{
  //  cout << "  Comparison time                    : " << time_comp << " [s]" << endl;
  //  cout << "  Total time                         : " << time_tot << " [s]" << endl;
  //}
  //else
  //{
  //  cout << "  Comparison time : " << time_comp << " [s]" << endl;
  //}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataCompare::comp_ace_data_header()
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

void ThermalScatterAceDataCompare::comp_ace_data_pointer()
{
  ace_comp_obj.set_comp_data_information("len2");
  ace_comp_obj.comp_int_data(ace_data_obj.get_len2(),  ace_data_obj_ref.get_len2());
  ace_comp_obj.set_comp_data_information("idpni");
  ace_comp_obj.comp_int_data(ace_data_obj.get_idpni(), ace_data_obj_ref.get_idpni());
  ace_comp_obj.set_comp_data_information("nil");
  ace_comp_obj.comp_int_data(ace_data_obj.get_nil(),   ace_data_obj_ref.get_nil());
  ace_comp_obj.set_comp_data_information("nieb");
  ace_comp_obj.comp_int_data(ace_data_obj.get_nieb(),  ace_data_obj_ref.get_nieb());
  ace_comp_obj.set_comp_data_information("idpnc");
  ace_comp_obj.comp_int_data(ace_data_obj.get_idpnc(), ace_data_obj_ref.get_idpnc());
  ace_comp_obj.set_comp_data_information("ncl");
  ace_comp_obj.comp_int_data(ace_data_obj.get_ncl(),   ace_data_obj_ref.get_ncl());
  ace_comp_obj.set_comp_data_information("ifeng");
  ace_comp_obj.comp_int_data(ace_data_obj.get_ifeng(), ace_data_obj_ref.get_ifeng());
  ace_comp_obj.set_comp_data_information("itie");
  ace_comp_obj.comp_int_data(ace_data_obj.get_itie(),  ace_data_obj_ref.get_itie());
  ace_comp_obj.set_comp_data_information("itix");
  ace_comp_obj.comp_int_data(ace_data_obj.get_itix(),  ace_data_obj_ref.get_itix());
  ace_comp_obj.set_comp_data_information("itxe");
  ace_comp_obj.comp_int_data(ace_data_obj.get_itxe(),  ace_data_obj_ref.get_itxe());
  ace_comp_obj.set_comp_data_information("itce");
  ace_comp_obj.comp_int_data(ace_data_obj.get_itce(),  ace_data_obj_ref.get_itce());
  ace_comp_obj.set_comp_data_information("itcx");
  ace_comp_obj.comp_int_data(ace_data_obj.get_itcx(),  ace_data_obj_ref.get_itcx());
  ace_comp_obj.set_comp_data_information("itca");
  ace_comp_obj.comp_int_data(ace_data_obj.get_itca(),  ace_data_obj_ref.get_itca());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataCompare::comp_ace_data_inelastic()
{
  ace_comp_obj.set_comp_data_information("inelastic_ene_data, inelastic_xs_data");
  ace_comp_obj.comp_table_data(ace_data_obj.get_inelastic_ene_data(),
                               ace_data_obj.get_inelastic_xs_data(),
                               ace_data_obj_ref.get_inelastic_ene_data(),
                               ace_data_obj_ref.get_inelastic_xs_data());

  int i_max  = static_cast<int>(ace_data_obj_ref.get_inelastic_ene_data().size());
  int ele_no = static_cast<int>(ace_data_obj_ref.get_inelastic_scat_xs_int().size());
  for(int i=0; i<i_max; i++)
  {
    ace_comp_obj.set_comp_data_position(i+1);

    int j_max = static_cast<int>(ace_data_obj_ref.get_inelastic_second_ene()[i].size());
    ace_comp_obj.set_comp_data_information("size of inelastic_second_ene");
    ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_inelastic_second_ene()[i].size()),  j_max);

    if( ele_no == 0 )
    {
      for(int j=0; j<j_max; j++)
      {
        ace_comp_obj.set_comp_data_position(i+1, j+1);
        ace_comp_obj.set_comp_data_information("inelastic_second_ene");
        ace_comp_obj.comp_real_data(ace_data_obj.get_inelastic_second_ene()[i][j],
                                    ace_data_obj_ref.get_inelastic_second_ene()[i][j]);
        ace_comp_obj.set_comp_data_information("inelastic_scat_xs_weight");
        ace_comp_obj.comp_list_data(ace_data_obj.get_inelastic_scat_xs_weight()[i][j],
                                    ace_data_obj_ref.get_inelastic_scat_xs_weight()[i][j]);
      }
    }
    else
    {
      ace_comp_obj.set_comp_data_information("size of inelastic_scat_xs_int");
      ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_inelastic_scat_xs_int()[i].size()), j_max);
      for(int j=0; j<j_max; j++)
      {
        ace_comp_obj.set_comp_data_position(i+1, j+1);
        ace_comp_obj.set_comp_data_information("inelastic_second_ene");
        ace_comp_obj.comp_real_data(ace_data_obj.get_inelastic_second_ene()[i][j],
                                    ace_data_obj_ref.get_inelastic_second_ene()[i][j]);
        ace_comp_obj.set_comp_data_information("inelastic_scat_xs_int");
        ace_comp_obj.comp_real_data(ace_data_obj.get_inelastic_scat_xs_int()[i][j],
                                    ace_data_obj_ref.get_inelastic_scat_xs_int()[i][j]);
        ace_comp_obj.set_comp_data_information("inelastic_weight");
        ace_comp_obj.comp_real_data(ace_data_obj.get_inelastic_weight()[i][j],
                                    ace_data_obj_ref.get_inelastic_weight()[i][j]);
        ace_comp_obj.set_comp_data_information("inelastic_scat_xs_weight");
        ace_comp_obj.comp_list_data(ace_data_obj.get_inelastic_scat_xs_weight()[i][j],
                                    ace_data_obj_ref.get_inelastic_scat_xs_weight()[i][j]);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataCompare::comp_ace_data_elastic()
{
  int i_max = static_cast<int>(ace_data_obj_ref.get_coh_elastic_ene_data().size());
  ace_comp_obj.set_comp_data_information("size of coh_elastic_ene_data");
  ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_coh_elastic_ene_data().size()), i_max);
  if( i_max > 0 )
  {
    ace_comp_obj.set_comp_data_information("coh_elastic_ene_data, coh_elastic_e_xs_data");
    ace_comp_obj.comp_table_data(ace_data_obj.get_coh_elastic_ene_data(),
                                 ace_data_obj.get_coh_elastic_e_xs_data(),
                                 ace_data_obj_ref.get_coh_elastic_ene_data(),
                                 ace_data_obj_ref.get_coh_elastic_e_xs_data());
  }

  i_max = static_cast<int>(ace_data_obj_ref.get_incoh_elastic_ene_data().size());
  ace_comp_obj.clear_comp_data_position();
  ace_comp_obj.set_comp_data_information("size of incoh_elastic_ene_data");
  ace_comp_obj.comp_int_data(static_cast<int>(ace_data_obj.get_incoh_elastic_ene_data().size()), i_max);
  if( i_max > 0 )
  {
    ace_comp_obj.set_comp_data_information("incoh_elastic_ene_data, incoh_elastic_xs_data");
    ace_comp_obj.comp_table_data(ace_data_obj.get_incoh_elastic_ene_data(),
                                 ace_data_obj.get_incoh_elastic_xs_data(),
                                 ace_data_obj_ref.get_incoh_elastic_ene_data(),
                                 ace_data_obj_ref.get_incoh_elastic_xs_data());

    for(int i=0; i<i_max; i++)
    {
      ace_comp_obj.set_comp_data_position(i+1);
      ace_comp_obj.set_comp_data_information("incoh_elastic_scat_angle");
      ace_comp_obj.comp_list_data(ace_data_obj.get_incoh_elastic_scat_angle()[i],
                                  ace_data_obj_ref.get_incoh_elastic_scat_angle()[i]);
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

ThermalScatterAceDataObject ThermalScatterAceDataCompare::parse_ace_data_file(string& file_name)
{
  //Read ACE format
  ThermalScatterAceDataParser parse_obj;
  parse_obj.set_file_name(file_name);
  parse_obj.parse_ace_format();

  //Copy ACE data object and clear read ace format class
  return parse_obj.get_ace_data_obj();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter

void ThermalScatterAceDataCompare::set_ace_data_obj(ThermalScatterAceDataObject& ace_obj,
                                                    ThermalScatterAceDataObject& ace_obj_ref)
{
  ace_file_name.clear();
  ace_file_name_ref.clear();

  ace_data_obj     = ace_obj;
  ace_data_obj_ref = ace_obj_ref;
}

void ThermalScatterAceDataCompare::set_ace_file_name(string ace_name, string ace_name_ref)
{
  cout << "Read reference data : " << ace_name_ref << endl;
  //boost::timer timer_read_ref;
  ace_file_name_ref = ace_name_ref;
  ace_data_obj_ref  = parse_ace_data_file(ace_name_ref);
  //time_read_ref     = static_cast<Real>(timer_read_ref.elapsed());

  cout << "Read comparing data : " << ace_name << endl;
  //boost::timer timer_read;
  ace_file_name     = ace_name;
  ace_data_obj      = parse_ace_data_file(ace_name);
  //time_read         = static_cast<Real>(timer_read.elapsed());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

ThermalScatterAceDataObject ThermalScatterAceDataCompare::get_ace_data_obj()
{
  return ace_data_obj;
}

ThermalScatterAceDataObject ThermalScatterAceDataCompare::get_ace_data_obj_ref()
{
  return ace_data_obj_ref;
}

string  ThermalScatterAceDataCompare::get_ace_file_name()
{
  return ace_file_name;
}

string  ThermalScatterAceDataCompare::get_ace_file_name_ref()
{
  return ace_file_name_ref;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataCompare::set_tolerance_val_def()
{
  ace_comp_obj.set_tolerance_val_def();
}

void ThermalScatterAceDataCompare::set_tolerance_val(Real tolerance_val)
{
  ace_comp_obj.set_tolerance_val(tolerance_val);
}

Real ThermalScatterAceDataCompare::get_tolerance_val()
{
  return ace_comp_obj.get_tolerance_val();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void ThermalScatterAceDataCompare::set_comp_pointer_flg(int comp_flg)
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

int ThermalScatterAceDataCompare::get_comp_pointer_flg()
{
  return comp_pointer_flg;
}
