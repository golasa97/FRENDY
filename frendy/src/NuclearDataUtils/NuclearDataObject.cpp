#include "NuclearDataUtils/NuclearDataObject.hpp"

using namespace frendy;

//constructor
NuclearDataObject::NuclearDataObject(void)
{
  clear();
}

//destructor
NuclearDataObject::~NuclearDataObject(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObject::clear()
{
  general_data_obj.clear();
  fis_data_obj.clear();
  reso_data_obj.clear();
  thermal_scat_data_obj.clear();
  nucl_reaction_data_obj.clear();
  cov_general_data_obj.clear();
  cov_reso_data_obj.clear();
  cov_reaction_data_obj.clear();
  prob_data_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObject::modify_mt_no_for_endf5()
{
  if( general_data_obj.get_lib_format() >=6 )
  {
    //Skip modification
    return;
  }

  //For ENDF-5 format
  string class_name = "NuclearDataObject";
  string func_name  = "modify_mt_no_for_endf5()";

  ostringstream oss01;
  oss01 << general_data_obj.get_lib_format();
  string str_data01 = "Library format for original nuclear data : " + oss01.str();

  vector<string> err_com;
  err_com.push_back(str_data01);
  err_com.push_back("The library format is not equal to 6.");
  err_com.push_back("MT number of (n,p), (n,d), (n, t), (n,He3), and (n,alpha) are modified");
  err_com.push_back("from MT=600-849 to MT=700-798.");
  err_com.push_back("This modification affects the processing results and the processing");
  err_com.push_back("results may be incorrect.");
  err_com.push_back("Please check the processing results.");
  err_obj.output_caution(class_name, func_name, err_com);


  //Modify MT number
  vector<Integer> mt_endf5, mt_endf6;
  int mt_max = 10; //(n,p), (n,d), (n,t), (n,He3), and (n,alpha)
  mt_endf5.resize(mt_max);
  mt_endf6.resize(mt_max);

  mt_endf5[0] = 700; //(n,p)
  mt_endf5[1] = 718;
  mt_endf5[2] = 720; //(n,d)
  mt_endf5[3] = 738;
  mt_endf5[4] = 740; //(n,t)
  mt_endf5[5] = 758;
  mt_endf5[6] = 760; //(n,He3)
  mt_endf5[7] = 768;
  mt_endf5[8] = 780; //(n,alpha)
  mt_endf5[9] = 798;

  mt_endf6[0] = 600; //(n,p)
  mt_endf6[1] = 649;
  mt_endf6[2] = 650; //(n,d)
  mt_endf6[3] = 699;
  mt_endf6[4] = 700; //(n,t)
  mt_endf6[5] = 749;
  mt_endf6[6] = 750; //(n,He3)
  mt_endf6[7] = 799;
  mt_endf6[8] = 800; //(n,alpha)
  mt_endf6[9] = 849;

  modify_mt_no_for_endf5_no_cov(mt_endf5, mt_endf6);
  modify_mt_no_for_endf5_cov(mt_endf5, mt_endf6);


  //Modify library format (6: ENDF-6 format)
  general_data_obj.set_lib_format(6);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObject::modify_mt_no_for_endf5_no_cov(vector<Integer> mt_endf5, vector<Integer> mt_endf6)
{
  //For NuclearReactionDataContainer
  NuclearReactionDataContainer  mod_obj;
  vector<Integer> reaction_type_list = nucl_reaction_data_obj.get_reaction_type();
  vector<Integer> mt_list_ori, mt_list_mod;
  mt_list_ori.clear();
  mt_list_mod.clear();

  int i_max = static_cast<int>(reaction_type_list.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no = reaction_type_list[i];
    if( mt_no == unassigned_mt_no )
    {
      continue;
    }

    int mod_flg = -1;
    for(int j=0; j<static_cast<int>(mt_endf5.size()); j+=2)
    {
      if( mt_no < mt_endf5[j] && mt_no > mt_endf5[j+1] )
      {
        mod_flg = j;
        break;
      }
    }

    CrossSectionDataContainer        xs_obj    = nucl_reaction_data_obj.get_xs_data_obj(mt_no);
    EnergyAngularDataContainer       ene_obj   = nucl_reaction_data_obj.get_ene_angular_data_obj(mt_no);
    ProductDistributionDataContainer prod_obj  = nucl_reaction_data_obj.get_product_distr_data_obj(mt_no);
    RadioactiveProductDataContainer  rad_obj   = nucl_reaction_data_obj.get_radio_product_data_obj(mt_no);
    PhotonDataContainer              photo_obj = nucl_reaction_data_obj.get_photon_data_obj(mt_no);
    OtherNuclearDataContainer        other_obj = nucl_reaction_data_obj.get_other_data_obj(mt_no);

    Integer mt_no_mod = mt_no;
    if( mod_flg >= 0 )
    {
      Integer mt_no_mod = mt_no - mt_endf5[mod_flg] + mt_endf6[mod_flg];
      mt_list_ori.push_back(mt_no);
      mt_list_mod.push_back(mt_no_mod);
    }

    if( xs_obj.get_reaction_type() != unassigned_mt_no )
    {
      mod_obj.set_xs_data_obj(mt_no_mod, xs_obj);
    }
    if( ene_obj.get_reaction_type() != unassigned_mt_no )
    {
      mod_obj.set_ene_angular_data_obj(mt_no_mod, ene_obj);
    }
    if( prod_obj.get_reaction_type() != unassigned_mt_no )
    {
      mod_obj.set_product_distr_data_obj(mt_no_mod, prod_obj);
    }
    if( rad_obj.get_reaction_type() != unassigned_mt_no )
    {
      mod_obj.set_radio_product_data_obj(mt_no_mod, rad_obj);
    }
    if( photo_obj.get_reaction_type() != unassigned_mt_no )
    {
      mod_obj.set_photon_data_obj(mt_no_mod, photo_obj);
    }
    if( other_obj.get_reaction_type() != unassigned_mt_no )
    {
      mod_obj.set_other_data_obj(mt_no_mod, other_obj);
    }
    xs_obj.clear();
    ene_obj.clear();
    prod_obj.clear();
    rad_obj.clear();
    photo_obj.clear();
    other_obj.clear();
  }

  //Copy modified data
  nucl_reaction_data_obj = mod_obj;
  mod_obj.clear();

  //Output modified MT number list
  i_max = static_cast<int>(mt_list_ori.size());
  if( i_max > 0 )
  {
    string class_name = "NuclearDataObject";
    string func_name  = "modify_mt_no_for_endf5_no_cov()";

    vector<string> err_com;
    err_com.push_back("The following MT numbers in the non-covariance data are modified:");
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss01, oss02;
      oss01 << mt_list_ori[i];
      oss02 << mt_list_mod[i];
      string str_data01 = "  " + oss01.str() + " -> " + oss02.str();
      err_com.push_back(str_data01);
    }
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataObject::modify_mt_no_for_endf5_cov(vector<Integer> mt_endf5, vector<Integer> mt_endf6)
{
  //For CovarianceReactionDataContainer
  CovarianceReactionDataContainer  mod_obj;
  vector<Integer> reaction_type_list = cov_reaction_data_obj.get_reaction_type();
  vector<Integer> mt_list_ori, mt_list_mod;
  mt_list_ori.clear();
  mt_list_mod.clear();

  int i_max = static_cast<int>(reaction_type_list.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no = reaction_type_list[i];
    if( mt_no == unassigned_mt_no )
    {
      continue;
    }

    int mod_flg = -1;
    for(int j=0; j<static_cast<int>(mt_endf5.size()); j+=2)
    {
      if( mt_no < mt_endf5[j] && mt_no > mt_endf5[j+1] )
      {
        mod_flg = j;
        break;
      }
    }

    CovarianceFissionDataContainer            fis_obj  = cov_reaction_data_obj.get_cov_fis_data_obj(mt_no);
    CovarianceCrossSectionDataContainer       xs_obj   = cov_reaction_data_obj.get_cov_xs_data_obj(mt_no);
    CovarianceEnergyAngularDataContainer      ene_obj  = cov_reaction_data_obj.get_cov_ene_angular_data_obj(mt_no);
    CovarianceRadioactiveProductDataContainer prod_obj = cov_reaction_data_obj.get_cov_radio_product_data_obj(mt_no);

    Integer mt_no_mod = mt_no;
    if( mod_flg >= 0 )
    {
      Integer mt_no_mod = mt_no - mt_endf5[mod_flg] + mt_endf6[mod_flg];
      mt_list_ori.push_back(mt_no);
      mt_list_mod.push_back(mt_no_mod);
    }

    if( fis_obj.get_reaction_type() != unassigned_mt_no )
    {
      mod_obj.set_cov_fis_data_obj(mt_no_mod, fis_obj);
    }
    if( xs_obj.get_reaction_type() != unassigned_mt_no )
    {
      mod_obj.set_cov_xs_data_obj(mt_no_mod, xs_obj);
    }
    if( ene_obj.get_reaction_type() != unassigned_mt_no )
    {
      mod_obj.set_cov_ene_angular_data_obj(mt_no_mod, ene_obj);
    }
    if( prod_obj.get_reaction_type() != unassigned_mt_no )
    {
      mod_obj.set_cov_radio_product_data_obj(mt_no_mod, prod_obj);
    }
    fis_obj.clear();
    xs_obj.clear();
    ene_obj.clear();
    prod_obj.clear();
  }

  //Copy modified data
  cov_reaction_data_obj = mod_obj;
  mod_obj.clear();

  //Output modified MT number list
  i_max = static_cast<int>(mt_list_ori.size());
  if( i_max > 0 )
  {
    string class_name = "NuclearDataObject";
    string func_name  = "modify_mt_no_for_endf5_cov()";

    vector<string> err_com;
    err_com.push_back("The following MT numbers in the covariance data are modified:");
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss01, oss02;
      oss01 << mt_list_ori[i];
      oss02 << mt_list_mod[i];
      string str_data01 = "  " + oss01.str() + " -> " + oss02.str();
      err_com.push_back(str_data01);
    }
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
GeneralDataContainer              NuclearDataObject::get_general_data_obj()
{
  return general_data_obj;
}

FissionDataContainer              NuclearDataObject::get_fis_data_obj()
{
  return fis_data_obj;
}

ResonanceDataContainer            NuclearDataObject::get_reso_data_obj()
{
  return reso_data_obj;
}

ThermalScatterDataContainer       NuclearDataObject::get_thermal_scat_data_obj()
{
  return thermal_scat_data_obj;
}

NuclearReactionDataContainer      NuclearDataObject::get_nucl_reaction_data_obj()
{
  return nucl_reaction_data_obj;
}

CovarianceGeneralDataContainer    NuclearDataObject::get_cov_general_data_obj()
{
  return cov_general_data_obj;
}

CovarianceResonanceDataContainer  NuclearDataObject::get_cov_reso_data_obj()
{
  return cov_reso_data_obj;
}

CovarianceReactionDataContainer   NuclearDataObject::get_cov_reaction_data_obj()
{
  return cov_reaction_data_obj;
}

ProbabilityDataContainer          NuclearDataObject::get_prob_data_obj()
{
  return prob_data_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void NuclearDataObject::set_general_data_obj( GeneralDataContainer obj_data )
{
  general_data_obj.clear();
  general_data_obj = obj_data;
  obj_data.clear();
}

void NuclearDataObject::set_fis_data_obj( FissionDataContainer obj_data )
{
  fis_data_obj.clear();
  fis_data_obj = obj_data;
  obj_data.clear();
}

void NuclearDataObject::set_reso_data_obj( ResonanceDataContainer obj_data )
{
  reso_data_obj.clear();
  reso_data_obj = obj_data;
  obj_data.clear();
}

void NuclearDataObject::set_thermal_scat_data_obj( ThermalScatterDataContainer obj_data )
{
  thermal_scat_data_obj.clear();
  thermal_scat_data_obj = obj_data;
  obj_data.clear();
}

void NuclearDataObject::set_nucl_reaction_data_obj( NuclearReactionDataContainer obj_data )
{
  nucl_reaction_data_obj.clear();
  nucl_reaction_data_obj = obj_data;
  obj_data.clear();
}

void NuclearDataObject::set_cov_general_data_obj( CovarianceGeneralDataContainer obj_data )
{
  cov_general_data_obj.clear();
  cov_general_data_obj = obj_data;
  obj_data.clear();
}

void NuclearDataObject::set_cov_reso_data_obj( CovarianceResonanceDataContainer obj_data )
{
  cov_reso_data_obj.clear();
  cov_reso_data_obj = obj_data;
  obj_data.clear();
}

void NuclearDataObject::set_cov_reaction_data_obj( CovarianceReactionDataContainer obj_data )
{
  cov_reaction_data_obj.clear();
  cov_reaction_data_obj = obj_data;
  obj_data.clear();
}

void NuclearDataObject::set_prob_data_obj( ProbabilityDataContainer obj_data )
{
  prob_data_obj.clear();
  prob_data_obj = obj_data;
  obj_data.clear();
}


