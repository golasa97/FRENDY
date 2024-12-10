#include "NuclearDataUtils/CovarianceDataContainer/CovarianceReactionDataContainer.hpp"

using namespace frendy;

//constructor
CovarianceReactionDataContainer::CovarianceReactionDataContainer(void)
{
  clear();
}

//destructor
CovarianceReactionDataContainer::~CovarianceReactionDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CovarianceReactionDataContainer::clear()
{
  reaction_type_add_flg = no_add_reaction_type;

  vector<CovarianceFissionDataContainer>().swap(cov_fis_data_obj);
  //for(int i=0; i<static_cast<int>(cov_fis_data_obj.size()); i++)
  //{
  //  cov_fis_data_obj[i].clear();
  //}
  //cov_fis_data_obj.resize(0);

  vector<CovarianceCrossSectionDataContainer>().swap(cov_xs_data_obj);
  //for(int i=0; i<static_cast<int>(cov_xs_data_obj.size()); i++)
  //{
  //  cov_xs_data_obj[i].clear();
  //}
  //cov_xs_data_obj.resize(0);

  vector<CovarianceEnergyAngularDataContainer>().swap(cov_ene_angular_data_obj);
  //for(int i=0; i<static_cast<int>(cov_ene_angular_data_obj.size()); i++)
  //{
  //  cov_ene_angular_data_obj[i].clear();
  //}
  //cov_ene_angular_data_obj.resize(0);

  vector<CovarianceRadioactiveProductDataContainer>().swap(cov_radio_product_data_obj);
  //for(int i=0; i<static_cast<int>(cov_radio_product_data_obj.size()); i++)
  //{
  //  cov_radio_product_data_obj[i].clear();
  //}
  //cov_radio_product_data_obj.resize(0);

  reaction_type.clear();
  reaction_type_no = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CovarianceReactionDataContainer::remove_reaction_type(Integer react_val)
{
  vector<Integer>                                   reaction_type_mod;
  vector<CovarianceFissionDataContainer>            cov_fis_data_obj_mod;
  vector<CovarianceCrossSectionDataContainer>       cov_xs_data_obj_mod;
  vector<CovarianceEnergyAngularDataContainer>      cov_ene_angular_data_obj_mod;
  vector<CovarianceRadioactiveProductDataContainer> cov_radio_product_data_obj_mod;


  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] != react_val )
    {
      reaction_type_mod.push_back(reaction_type[i]);

      cov_fis_data_obj_mod.push_back(cov_fis_data_obj[i]);
      cov_xs_data_obj_mod.push_back(cov_xs_data_obj[i]);
      cov_ene_angular_data_obj_mod.push_back(cov_ene_angular_data_obj[i]);
      cov_radio_product_data_obj_mod.push_back(cov_radio_product_data_obj[i]);
    }
  }

  reaction_type_no           = static_cast<int>(reaction_type_mod.size());
  reaction_type              = reaction_type_mod;
  cov_fis_data_obj           = cov_fis_data_obj_mod;
  cov_xs_data_obj            = cov_xs_data_obj_mod;
  cov_ene_angular_data_obj   = cov_ene_angular_data_obj_mod;
  cov_radio_product_data_obj = cov_radio_product_data_obj_mod;
  
  reaction_type_mod.clear();
  vector<CovarianceFissionDataContainer>().swap(cov_fis_data_obj_mod);
  vector<CovarianceCrossSectionDataContainer>().swap(cov_xs_data_obj_mod);
  vector<CovarianceEnergyAngularDataContainer>().swap(cov_ene_angular_data_obj_mod);
  vector<CovarianceRadioactiveProductDataContainer>().swap(cov_radio_product_data_obj_mod);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int CovarianceReactionDataContainer::check_reaction_type(Integer reaction_type_check)
{
  int react_type_flg = -1;
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] == reaction_type_check )
    {
      react_type_flg = i;
      break;
    }
  }

  return react_type_flg;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

int CovarianceReactionDataContainer::add_new_reaction_type( Integer int_data )
{
  if( int_data == unassigned_mt_no )
  {
    return -1;
  }

  reaction_type_add_flg = add_reaction_type;
 
  reaction_type_no++;
  reaction_type.push_back(int_data);

  cov_fis_data_obj.resize(reaction_type_no);
  cov_xs_data_obj.resize(reaction_type_no);
  cov_ene_angular_data_obj.resize(reaction_type_no);
  cov_radio_product_data_obj.resize(reaction_type_no);

  return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CovarianceReactionDataContainer::sort_reaction_data()
{
  if( reaction_type_add_flg == no_add_reaction_type )
  {
    return;
  }

  reaction_type_add_flg = no_add_reaction_type;

  vector<Integer>                                   reaction_type_old              = reaction_type;
  vector<CovarianceFissionDataContainer>            cov_fis_data_obj_old           = cov_fis_data_obj;
  vector<CovarianceCrossSectionDataContainer>       cov_xs_data_obj_old            = cov_xs_data_obj;
  vector<CovarianceEnergyAngularDataContainer>      cov_ene_angular_data_obj_old   = cov_ene_angular_data_obj;
  vector<CovarianceRadioactiveProductDataContainer> cov_radio_product_data_obj_old = cov_radio_product_data_obj;

  sort(reaction_type.begin(), reaction_type.end());
  for(int i=0; i<reaction_type_no; i++)
  {
    Integer react_val = reaction_type[i];
    for(int j=0; j<reaction_type_no; j++)
    {
      if( reaction_type_old[j] == react_val )
      {
        if( i != j )
        {
          cov_fis_data_obj[i]           = cov_fis_data_obj_old[j];
          cov_xs_data_obj[i]            = cov_xs_data_obj_old[j];
          cov_ene_angular_data_obj[i]   = cov_ene_angular_data_obj_old[j];
          cov_radio_product_data_obj[i] = cov_radio_product_data_obj_old[j];
        }

        cov_fis_data_obj_old[j].clear();
        cov_xs_data_obj_old[j].clear();
        cov_ene_angular_data_obj_old[j].clear();
        cov_radio_product_data_obj_old[j].clear();
        break;
      }
    }
  }

  cov_fis_data_obj_old.resize(0);
  cov_xs_data_obj_old.resize(0);
  cov_ene_angular_data_obj_old.resize(0);
  cov_radio_product_data_obj_old.resize(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
vector<Integer>                           CovarianceReactionDataContainer::get_reaction_type()
{
  return reaction_type;
}

vector<CovarianceFissionDataContainer>           CovarianceReactionDataContainer::get_cov_fis_data_obj()
{
  return cov_fis_data_obj;
}

vector<CovarianceCrossSectionDataContainer>       CovarianceReactionDataContainer::get_cov_xs_data_obj()
{
  return cov_xs_data_obj;
}

vector<CovarianceEnergyAngularDataContainer>      CovarianceReactionDataContainer::get_cov_ene_angular_data_obj()
{
  return cov_ene_angular_data_obj;
}

vector<CovarianceRadioactiveProductDataContainer> CovarianceReactionDataContainer::get_cov_radio_product_data_obj()
{
  return cov_radio_product_data_obj;
}


CovarianceFissionDataContainer              CovarianceReactionDataContainer::get_cov_fis_data_obj(Integer reaction_type_data)
{
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] == reaction_type_data )
    {
      return cov_fis_data_obj[i];
    }
  }

  //string class_name = "CovarianceReactionDataContainer";
  //string func_name  = "get_cov_fis_data_obj(Integer reaction_type_data)";
  //
  //ostringstream oss;
  //oss << reaction_type_data;
  //string str_data = "Data type : " + oss.str();
  //
  //vector<string> err_com;
  //err_com.push_back(str_data);
  //err_com.push_back("This data type is not included in this container class.");
  //err_com.push_back("Please check data type or container class.");
  //err_obj.output_runtime_error(class_name, func_name, err_com);

  CovarianceFissionDataContainer tmp_data_obj;
  tmp_data_obj.clear();
  return tmp_data_obj;
}

CovarianceCrossSectionDataContainer         CovarianceReactionDataContainer::get_cov_xs_data_obj(Integer reaction_type_data)
{
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] == reaction_type_data )
    {
      return cov_xs_data_obj[i];
    }
  }

  //string class_name = "CovarianceReactionDataContainer";
  //string func_name  = "get_cov_xs_data_obj(Integer reaction_type_data)";
  //
  //ostringstream oss;
  //oss << reaction_type_data;
  //string str_data = "Data type : " + oss.str();
  //
  //vector<string> err_com;
  //err_com.push_back(str_data);
  //err_com.push_back("This data type is not included in this container class.");
  //err_com.push_back("Please check data type or container class.");
  //err_obj.output_runtime_error(class_name, func_name, err_com);

  CovarianceCrossSectionDataContainer tmp_data_obj;
  tmp_data_obj.clear();
  return tmp_data_obj;
}

CovarianceEnergyAngularDataContainer        CovarianceReactionDataContainer::get_cov_ene_angular_data_obj(Integer reaction_type_data)
{
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] == reaction_type_data )
    {
      return cov_ene_angular_data_obj[i];
    }
  }

  //string class_name = "CovarianceReactionDataContainer";
  //string func_name  = "get_cov_ene_angular_data_obj(Integer reaction_type_data)";
  //
  //ostringstream oss;
  //oss << reaction_type_data;
  //string str_data = "Data type : " + oss.str();
  //
  //vector<string> err_com;
  //err_com.push_back(str_data);
  //err_com.push_back("This data type is not included in this container class.");
  //err_com.push_back("Please check data type or container class.");
  //err_obj.output_runtime_error(class_name, func_name, err_com);

  CovarianceEnergyAngularDataContainer tmp_data_obj;
  tmp_data_obj.clear();
  return tmp_data_obj;
}

CovarianceRadioactiveProductDataContainer   CovarianceReactionDataContainer::get_cov_radio_product_data_obj(Integer reaction_type_data)
{
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] == reaction_type_data )
    {
      return cov_radio_product_data_obj[i];
    }
  }

  //string class_name = "CovarianceReactionDataContainer";
  //string func_name  = "get_cov_radio_product_data_obj(Integer reaction_type_data)";
  //
  //ostringstream oss;
  //oss << reaction_type_data;
  //string str_data = "Data type : " + oss.str();
  //
  //vector<string> err_com;
  //err_com.push_back(str_data);
  //err_com.push_back("This data type is not included in this container class.");
  //err_com.push_back("Please check data type or container class.");
  //err_obj.output_runtime_error(class_name, func_name, err_com);

  CovarianceRadioactiveProductDataContainer tmp_data_obj;
  tmp_data_obj.clear();
  return tmp_data_obj;
}


vector<CovarianceFissionDataContainer>           CovarianceReactionDataContainer::get_cov_fis_data_obj_assigned()
{
  vector<CovarianceFissionDataContainer> cov_fis_data_obj_assigned;

  for(int i=0; i<reaction_type_no; i++)
  {
    if( cov_fis_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      cov_fis_data_obj_assigned.push_back(cov_fis_data_obj[i]);
    }
  }

  return cov_fis_data_obj_assigned;
}

vector<CovarianceCrossSectionDataContainer>       CovarianceReactionDataContainer::get_cov_xs_data_obj_assigned()
{
  vector<CovarianceCrossSectionDataContainer> cov_xs_data_obj_assigned;

  for(int i=0; i<reaction_type_no; i++)
  {
    if( cov_xs_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      cov_xs_data_obj_assigned.push_back(cov_xs_data_obj[i]);
    }
  }

  return cov_xs_data_obj_assigned;
}

vector<CovarianceEnergyAngularDataContainer>      CovarianceReactionDataContainer::get_cov_ene_angular_data_obj_assigned()
{
  vector<CovarianceEnergyAngularDataContainer> cov_ene_angular_data_obj_assigned;

  for(int i=0; i<reaction_type_no; i++)
  {
    if( cov_ene_angular_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      cov_ene_angular_data_obj_assigned.push_back(cov_ene_angular_data_obj[i]);
    }
  }

  return cov_ene_angular_data_obj_assigned;
}

vector<CovarianceRadioactiveProductDataContainer> CovarianceReactionDataContainer::get_cov_radio_product_data_obj_assigned()
{
  vector<CovarianceRadioactiveProductDataContainer> cov_radio_product_data_obj_assigned;

  for(int i=0; i<reaction_type_no; i++)
  {
    if( cov_radio_product_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      cov_radio_product_data_obj_assigned.push_back(cov_radio_product_data_obj[i]);
    }
  }

  return cov_radio_product_data_obj_assigned;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void CovarianceReactionDataContainer::set_reaction_type( vector<Integer> int_vec )
{
  int     i_max = static_cast<int>(int_vec.size());
  for(int i=0; i<i_max; i++)
  {
    set_reaction_type( int_vec[i] );
  }
  int_vec.clear();
}

void CovarianceReactionDataContainer::set_cov_fis_data_obj( vector<CovarianceFissionDataContainer> data_obj )
{
  int i_max = static_cast<int>(data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    set_cov_fis_data_obj(data_obj[i].get_reaction_type(), data_obj[i]);
    //data_obj[i].clear();
  }
  //data_obj.resize(0);

  vector<CovarianceFissionDataContainer>().swap(data_obj);
}

void CovarianceReactionDataContainer::set_cov_xs_data_obj( vector<CovarianceCrossSectionDataContainer> data_obj )
{
  int i_max = static_cast<int>(data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    set_cov_xs_data_obj(data_obj[i].get_reaction_type(), data_obj[i]);
    //data_obj[i].clear();
  }
  //data_obj.resize(0);

  vector<CovarianceCrossSectionDataContainer>().swap(data_obj);
}

void CovarianceReactionDataContainer::set_cov_ene_angular_data_obj( vector<CovarianceEnergyAngularDataContainer> data_obj )
{
  int i_max = static_cast<int>(data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    set_cov_ene_angular_data_obj(data_obj[i].get_reaction_type(), data_obj[i]);
    //data_obj[i].clear();
  }
  //data_obj.resize(0);

  vector<CovarianceEnergyAngularDataContainer>().swap(data_obj);
}

void CovarianceReactionDataContainer::set_cov_radio_product_data_obj( vector<CovarianceRadioactiveProductDataContainer> data_obj )
{
  int i_max = static_cast<int>(data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    set_cov_radio_product_data_obj(data_obj[i].get_reaction_type(), data_obj[i]);
    //data_obj[i].clear();
  }
  //data_obj.resize(0);

  vector<CovarianceRadioactiveProductDataContainer>().swap(data_obj);
}


void CovarianceReactionDataContainer::set_reaction_type( Integer reaction_type_data )
{
  Integer mod_flg = 0;
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type_data == reaction_type[i] )
    {
      mod_flg = 1;
      break;
    }
  }
  if( mod_flg == 0 )
  {
    mod_flg = add_new_reaction_type( reaction_type_data );
  }
}

void CovarianceReactionDataContainer::set_cov_fis_data_obj( Integer reaction_type_data, CovarianceFissionDataContainer data_obj )
{
  Integer mod_flg = 0;
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type_data == reaction_type[i] )
    {
      mod_flg   = 1;
      cov_fis_data_obj[i].clear();
      cov_fis_data_obj[i] = data_obj;
      break;
    }
  }
  if( mod_flg == 0 )
  {
    if( add_new_reaction_type( reaction_type_data ) > 0 )
    {
      cov_fis_data_obj[reaction_type_no-1] = data_obj;
    }
  }
  data_obj.clear();
}

void CovarianceReactionDataContainer::set_cov_xs_data_obj( Integer reaction_type_data, CovarianceCrossSectionDataContainer data_obj )
{
  Integer mod_flg = 0;
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type_data == reaction_type[i] )
    {
      mod_flg   = 1;
      cov_xs_data_obj[i].clear();
      cov_xs_data_obj[i] = data_obj;
      break;
    }
  }
  if( mod_flg == 0 )
  {
    if( add_new_reaction_type( reaction_type_data ) > 0 )
    {
      cov_xs_data_obj[reaction_type_no-1] = data_obj;
    }
  }
  data_obj.clear();
}

void CovarianceReactionDataContainer::set_cov_ene_angular_data_obj( Integer reaction_type_data, CovarianceEnergyAngularDataContainer data_obj )
{
  Integer mod_flg = 0;
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type_data == reaction_type[i] )
    {
      mod_flg   = 1;
      cov_ene_angular_data_obj[i].clear();
      cov_ene_angular_data_obj[i] = data_obj;
      break;
    }
  }
  if( mod_flg == 0 )
  {
    if( add_new_reaction_type( reaction_type_data ) > 0 )
    {
      cov_ene_angular_data_obj[reaction_type_no-1] = data_obj;
    }
  }
  data_obj.clear();
}

void CovarianceReactionDataContainer::set_cov_radio_product_data_obj( Integer reaction_type_data, CovarianceRadioactiveProductDataContainer data_obj )
{
  Integer mod_flg = 0;
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type_data == reaction_type[i] )
    {
      mod_flg   = 1;
      cov_radio_product_data_obj[i].clear();
      cov_radio_product_data_obj[i] = data_obj;
      break;
    }
  }
  if( mod_flg == 0 )
  {
    if( add_new_reaction_type( reaction_type_data ) > 0 )
    {
      cov_radio_product_data_obj[reaction_type_no-1] = data_obj;
    }
  }
  data_obj.clear();
}

