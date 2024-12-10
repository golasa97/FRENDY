#include "NuclearDataModifier/NuclearDataModifier.hpp"

using namespace frendy;

//constructor
NuclearDataModifier::NuclearDataModifier(void)
{
}

//destructor
NuclearDataModifier::~NuclearDataModifier(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataModifier::remove_specified_reaction_type_data
                            (NuclearDataObject& nucl_data_obj, Integer react_type_no)
{
  NuclearReactionDataContainer    react_data_obj     = nucl_data_obj.get_nucl_reaction_data_obj();
  CovarianceReactionDataContainer cov_react_data_obj = nucl_data_obj.get_cov_reaction_data_obj();

  react_data_obj.remove_reaction_type(react_type_no);
  cov_react_data_obj.remove_reaction_type(react_type_no);

  nucl_data_obj.set_nucl_reaction_data_obj(react_data_obj);
  nucl_data_obj.set_cov_reaction_data_obj(cov_react_data_obj);
  react_data_obj.clear();
  cov_react_data_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataModifier::change_specified_reaction_type_data
                            (NuclearDataObject& nucl_data_obj_ori,
                             NuclearDataObject& nucl_data_obj_add, Integer react_type_no)
{
  NuclearReactionDataContainer    react_data_obj_ori     = nucl_data_obj_ori.get_nucl_reaction_data_obj();
  CovarianceReactionDataContainer cov_react_data_obj_ori = nucl_data_obj_ori.get_cov_reaction_data_obj();

  NuclearReactionDataContainer    react_data_obj_add     = nucl_data_obj_add.get_nucl_reaction_data_obj();
  CovarianceReactionDataContainer cov_react_data_obj_add = nucl_data_obj_add.get_cov_reaction_data_obj();

  vector<Integer> react_data_react_type_ori     = react_data_obj_ori.get_reaction_type();
  vector<Integer> cov_react_data_react_type_ori = cov_react_data_obj_ori.get_reaction_type();
  vector<Integer> react_data_react_type_add     = react_data_obj_ori.get_reaction_type();
  vector<Integer> cov_react_data_react_type_add = cov_react_data_obj_ori.get_reaction_type();

  //Checking the reaction tyoe in the original nuclear data file
  if(     react_data_obj_ori.check_reaction_type(react_type_no) < 0 &&
      cov_react_data_obj_ori.check_reaction_type(react_type_no) < 0 )
  {
    string class_name = "NuclearDataModifier";
    string func_name  = "change_specified_reaction_type_data";

    ostringstream oss01;
    oss01 << react_type_no;

    string str_data01 = "Reaction type number : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This reaction type number is not found in the original nuclear data.");
    err_com.push_back("Please check your input file or original nuclear data file.");
    err_com.push_back("This program adds this reaction type data from the modified nuclear data.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  //Checking the reaction tyoe in the modified nuclear data file
  if(     react_data_obj_add.check_reaction_type(react_type_no) < 0 &&
      cov_react_data_obj_add.check_reaction_type(react_type_no) < 0 )
  {
    string class_name = "NuclearDataModifier";
    string func_name  = "change_specified_reaction_type_data";

    ostringstream oss01;
    oss01 << react_type_no;

    string str_data01 = "Reaction type number : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This reaction type number is not found in the modified nuclear data.");
    err_com.push_back("Please check your input file or modified nuclear data file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( react_data_obj_add.check_reaction_type(react_type_no) >= 0 )
  {
    add_specified_reaction_type_data_react
      (react_data_obj_ori, react_data_obj_add, react_type_no);
  }

  if( cov_react_data_obj_add.check_reaction_type(react_type_no) >= 0 )
  {
    add_specified_reaction_type_data_cov_react
      (cov_react_data_obj_ori, cov_react_data_obj_add, react_type_no);
  }

  nucl_data_obj_ori.set_nucl_reaction_data_obj(react_data_obj_ori);
  nucl_data_obj_ori.set_cov_reaction_data_obj(cov_react_data_obj_ori);
  react_data_obj_ori.clear();
  react_data_obj_add.clear();
  cov_react_data_obj_ori.clear();
  cov_react_data_obj_add.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataModifier::add_specified_reaction_type_data
                            (NuclearDataObject& nucl_data_obj_ori,
                             NuclearDataObject& nucl_data_obj_add, Integer react_type_no)
{
  NuclearReactionDataContainer    react_data_obj_ori     = nucl_data_obj_ori.get_nucl_reaction_data_obj();
  CovarianceReactionDataContainer cov_react_data_obj_ori = nucl_data_obj_ori.get_cov_reaction_data_obj();

  NuclearReactionDataContainer    react_data_obj_add     = nucl_data_obj_add.get_nucl_reaction_data_obj();
  CovarianceReactionDataContainer cov_react_data_obj_add = nucl_data_obj_add.get_cov_reaction_data_obj();

  vector<Integer> react_data_react_type_ori     = react_data_obj_ori.get_reaction_type();
  vector<Integer> cov_react_data_react_type_ori = cov_react_data_obj_ori.get_reaction_type();
  vector<Integer> react_data_react_type_add     = react_data_obj_ori.get_reaction_type();
  vector<Integer> cov_react_data_react_type_add = cov_react_data_obj_ori.get_reaction_type();

  //Checking the reaction tyoe in the original nuclear data file
  if(     react_data_obj_ori.check_reaction_type(react_type_no) > 0 ||
      cov_react_data_obj_ori.check_reaction_type(react_type_no) > 0 )
  {
    string class_name = "NuclearDataModifier";
    string func_name  = "add_specified_reaction_type_data";

    ostringstream oss01;
    oss01 << react_type_no;

    string str_data01 = "Reaction type number : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This reaction type number is found in the original nuclear data.");
    err_com.push_back("Please check your input file or original nuclear data file.");
    err_com.push_back("This program changes this reaction type data from the modified nuclear data.");
    err_obj.output_caution(class_name, func_name, err_com);
  }

  //Checking the reaction tyoe in the modified nuclear data file
  if(     react_data_obj_add.check_reaction_type(react_type_no) < 0 &&
      cov_react_data_obj_add.check_reaction_type(react_type_no) < 0 )
  {
    string class_name = "NuclearDataModifier";
    string func_name  = "add_specified_reaction_type_data";

    ostringstream oss01;
    oss01 << react_type_no;

    string str_data01 = "Reaction type number : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This reaction type number is not found in the modified nuclear data.");
    err_com.push_back("Please check your input file or modified nuclear data file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( react_data_obj_add.check_reaction_type(react_type_no) >= 0 )
  {
    add_specified_reaction_type_data_react
      (react_data_obj_ori, react_data_obj_add, react_type_no);
  }

  if( cov_react_data_obj_add.check_reaction_type(react_type_no) >= 0 )
  {
    add_specified_reaction_type_data_cov_react
      (cov_react_data_obj_ori, cov_react_data_obj_add, react_type_no);
  }

  nucl_data_obj_ori.set_nucl_reaction_data_obj(react_data_obj_ori);
  nucl_data_obj_ori.set_cov_reaction_data_obj(cov_react_data_obj_ori);
  react_data_obj_ori.clear();
  react_data_obj_add.clear();
  cov_react_data_obj_ori.clear();
  cov_react_data_obj_add.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataModifier::add_specified_reaction_type_data_react
                            (NuclearReactionDataContainer& react_data_obj_ori,
                             NuclearReactionDataContainer& react_data_obj_add, Integer react_type_no)
{
  CrossSectionDataContainer         xs_data_obj_add;
  EnergyAngularDataContainer        ene_angular_data_obj_add;
  ProductDistributionDataContainer  product_distr_data_obj_add;
  RadioactiveProductDataContainer   radio_product_data_obj_add;
  PhotonDataContainer               photon_data_obj_add;
  OtherNuclearDataContainer         other_data_obj_add;

  xs_data_obj_add            = react_data_obj_add.get_xs_data_obj(react_type_no);
  ene_angular_data_obj_add   = react_data_obj_add.get_ene_angular_data_obj(react_type_no);
  product_distr_data_obj_add = react_data_obj_add.get_product_distr_data_obj(react_type_no);
  radio_product_data_obj_add = react_data_obj_add.get_radio_product_data_obj(react_type_no);
  photon_data_obj_add        = react_data_obj_add.get_photon_data_obj(react_type_no);
  other_data_obj_add         = react_data_obj_add.get_other_data_obj(react_type_no);

  if( xs_data_obj_add.get_reaction_type() == react_type_no )
  {
    react_data_obj_ori.set_xs_data_obj(react_type_no, xs_data_obj_add);
  }

  if( ene_angular_data_obj_add.get_reaction_type() == react_type_no )
  {
    react_data_obj_ori.set_ene_angular_data_obj(react_type_no, ene_angular_data_obj_add);
  }

  if( product_distr_data_obj_add.get_reaction_type() == react_type_no )
  {
    react_data_obj_ori.set_product_distr_data_obj(react_type_no, product_distr_data_obj_add);
  }

  if( radio_product_data_obj_add.get_reaction_type() == react_type_no )
  {
    react_data_obj_ori.set_radio_product_data_obj(react_type_no, radio_product_data_obj_add);
  }

  if( photon_data_obj_add.get_reaction_type() == react_type_no )
  {
    react_data_obj_ori.set_photon_data_obj(react_type_no, photon_data_obj_add);
  }

  if( other_data_obj_add.get_reaction_type() == react_type_no )
  {
    react_data_obj_ori.set_other_data_obj(react_type_no, other_data_obj_add);
  }

  xs_data_obj_add.clear();
  ene_angular_data_obj_add.clear();
  product_distr_data_obj_add.clear();
  radio_product_data_obj_add.clear();
  photon_data_obj_add.clear();
  other_data_obj_add.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataModifier::add_specified_reaction_type_data_cov_react
                            (CovarianceReactionDataContainer& cov_react_data_obj_ori,
                             CovarianceReactionDataContainer& cov_react_data_obj_add, Integer react_type_no)
{
  CovarianceFissionDataContainer            cov_fis_data_obj_add;
  CovarianceCrossSectionDataContainer       cov_xs_data_obj_add;
  CovarianceEnergyAngularDataContainer      cov_ene_angular_data_obj_add;
  CovarianceRadioactiveProductDataContainer cov_radio_product_data_obj_add;

  cov_fis_data_obj_add           = cov_react_data_obj_add.get_cov_fis_data_obj(react_type_no);
  cov_xs_data_obj_add            = cov_react_data_obj_add.get_cov_xs_data_obj(react_type_no);
  cov_ene_angular_data_obj_add   = cov_react_data_obj_add.get_cov_ene_angular_data_obj(react_type_no);
  cov_radio_product_data_obj_add = cov_react_data_obj_add.get_cov_radio_product_data_obj(react_type_no);
 
  if( cov_fis_data_obj_add.get_reaction_type() == react_type_no )
  {
    cov_react_data_obj_ori.set_cov_fis_data_obj(react_type_no, cov_fis_data_obj_add);
  }

  if( cov_xs_data_obj_add.get_reaction_type() == react_type_no )
  {
    cov_react_data_obj_ori.set_cov_xs_data_obj(react_type_no, cov_xs_data_obj_add);
  }

  if( cov_ene_angular_data_obj_add.get_reaction_type() == react_type_no )
  {
    cov_react_data_obj_ori.set_cov_ene_angular_data_obj(react_type_no, cov_ene_angular_data_obj_add);
  }

  if( cov_radio_product_data_obj_add.get_reaction_type() == react_type_no )
  {
    cov_react_data_obj_ori.set_cov_radio_product_data_obj(react_type_no, cov_radio_product_data_obj_add);
  }

  cov_fis_data_obj_add.clear();
  cov_xs_data_obj_add.clear();
  cov_ene_angular_data_obj_add.clear();
  cov_radio_product_data_obj_add.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

