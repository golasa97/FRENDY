#include "NuclearDataUtils/NuclearDataContainer/NuclearReactionDataContainer.hpp"

using namespace frendy;

//constructor
NuclearReactionDataContainer::NuclearReactionDataContainer(void)
{
  clear();
}

//destructor
NuclearReactionDataContainer::~NuclearReactionDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearReactionDataContainer::clear()
{
  reaction_type_add_flg = no_add_reaction_type_mode;

  vector<CrossSectionDataContainer>().swap(xs_data_obj);
  //for(int i=0; i<static_cast<int>(xs_data_obj.size()); i++)
  //{
  //  xs_data_obj[i].clear();
  //}
  //xs_data_obj.resize(0);

  vector<EnergyAngularDataContainer>().swap(ene_angular_data_obj);
  //for(int i=0; i<static_cast<int>(ene_angular_data_obj.size()); i++)
  //{
  //  ene_angular_data_obj[i].clear();
  //}
  //ene_angular_data_obj.resize(0);

  vector<ProductDistributionDataContainer>().swap(product_distr_data_obj);
  //for(int i=0; i<static_cast<int>(product_distr_data_obj.size()); i++)
  //{
  //  product_distr_data_obj[i].clear();
  //}
  //product_distr_data_obj.resize(0);

  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj);
  //for(int i=0; i<static_cast<int>(radio_product_data_obj.size()); i++)
  //{
  //  radio_product_data_obj[i].clear();
  //}
  //radio_product_data_obj.resize(0);

  vector<PhotonDataContainer>().swap(photon_data_obj);
  //for(int i=0; i<static_cast<int>(photon_data_obj.size()); i++)
  //{
  //  photon_data_obj[i].clear();
  //}
  //photon_data_obj.resize(0);

  vector<OtherNuclearDataContainer>().swap(other_data_obj);
  //for(int i=0; i<static_cast<int>(other_data_obj.size()); i++)
  //{
  //  other_data_obj[i].clear();
  //}
  //other_data_obj.resize(0);

  reaction_type.clear();
  reaction_type_no = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int NuclearReactionDataContainer::add_new_reaction_type( Integer int_data )
{
  if( int_data == unassigned_mt_no )
  {
    return -1;
  }

  reaction_type_add_flg = add_reaction_type_mode;

  reaction_type_no++;
  reaction_type.push_back(int_data);

  CrossSectionDataContainer         xs_data_obj_tmp;
  EnergyAngularDataContainer        ene_angular_data_obj_tmp;
  ProductDistributionDataContainer  product_distr_data_obj_tmp;
  RadioactiveProductDataContainer   radio_product_data_obj_tmp;
  PhotonDataContainer               photon_data_obj_tmp;
  OtherNuclearDataContainer         other_data_obj_tmp;
  xs_data_obj_tmp.clear();
  ene_angular_data_obj_tmp.clear();
  product_distr_data_obj_tmp.clear();
  radio_product_data_obj_tmp.clear();
  photon_data_obj_tmp.clear();
  other_data_obj_tmp.clear();

  xs_data_obj.push_back(xs_data_obj_tmp);
  ene_angular_data_obj.push_back(ene_angular_data_obj_tmp);
  product_distr_data_obj.push_back(product_distr_data_obj_tmp);
  radio_product_data_obj.push_back(radio_product_data_obj_tmp);
  photon_data_obj.push_back(photon_data_obj_tmp);
  other_data_obj.push_back(other_data_obj_tmp);

  return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearReactionDataContainer::sort_reaction_data()
{
  if( reaction_type_add_flg == no_add_reaction_type_mode )
  {
    return;
  }

  reaction_type_add_flg = no_add_reaction_type_mode;

  vector<Integer>                           reaction_type_old           = reaction_type;
  vector<CrossSectionDataContainer>         xs_data_obj_old             = xs_data_obj;
  vector<EnergyAngularDataContainer>        ene_angular_data_obj_old    = ene_angular_data_obj;
  vector<ProductDistributionDataContainer>  product_distr_data_obj_old  = product_distr_data_obj;
  vector<RadioactiveProductDataContainer>   radio_product_data_obj_old  = radio_product_data_obj;
  vector<PhotonDataContainer>               photon_data_obj_old         = photon_data_obj;
  vector<OtherNuclearDataContainer>         other_data_obj_old          = other_data_obj;

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
          xs_data_obj[i]            = xs_data_obj_old[j];
          ene_angular_data_obj[i]   = ene_angular_data_obj_old[j];
          product_distr_data_obj[i] = product_distr_data_obj_old[j];
          radio_product_data_obj[i] = radio_product_data_obj_old[j];
          photon_data_obj[i]        = photon_data_obj_old[j];
          other_data_obj[i]         = other_data_obj_old[j];
        }

        xs_data_obj_old[j].clear();
        ene_angular_data_obj_old[j].clear();
        product_distr_data_obj_old[j].clear();
        radio_product_data_obj_old[j].clear();
        photon_data_obj_old[j].clear();
        other_data_obj_old[j].clear();
        break;
      }
    }
  }

  reaction_type_old.resize(0);
  xs_data_obj_old.resize(0);
  ene_angular_data_obj_old.resize(0);
  product_distr_data_obj_old.resize(0);
  radio_product_data_obj_old.resize(0);
  photon_data_obj_old.resize(0);
  other_data_obj_old.resize(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearReactionDataContainer::add_all_container_data(
                                     vector<CrossSectionDataContainer>&         xs_data_obj_mod,
                                     vector<EnergyAngularDataContainer>&        ene_angular_data_obj_mod,
                                     vector<ProductDistributionDataContainer>&  product_distr_data_obj_mod,
                                     vector<RadioactiveProductDataContainer>&   radio_product_data_obj_mod,
                                     vector<PhotonDataContainer>&               photon_data_obj_mod,
                                     vector<OtherNuclearDataContainer>&         other_data_obj_mod)
{
  Integer int_val = reaction_type_add_flg;
  clear();
  reaction_type_add_flg = int_val;

  int i_max = static_cast<int>(xs_data_obj_mod.size());
  for(int i=0; i<i_max; i++)
  {
    set_xs_data_obj(xs_data_obj_mod[i]);
  }

  i_max = static_cast<int>(ene_angular_data_obj_mod.size());
  for(int i=0; i<i_max; i++)
  {
    set_ene_angular_data_obj(ene_angular_data_obj_mod[i]);
  }

  i_max = static_cast<int>(product_distr_data_obj_mod.size());
  for(int i=0; i<i_max; i++)
  {
    set_product_distr_data_obj(product_distr_data_obj_mod[i]);
  }

  i_max = static_cast<int>(radio_product_data_obj_mod.size());
  for(int i=0; i<i_max; i++)
  {
    set_radio_product_data_obj(radio_product_data_obj_mod[i]);
  }

  i_max = static_cast<int>(photon_data_obj_mod.size());
  for(int i=0; i<i_max; i++)
  {
    set_photon_data_obj(photon_data_obj_mod[i]);
  }

  i_max = static_cast<int>(other_data_obj_mod.size());
  for(int i=0; i<i_max; i++)
  {
    set_other_data_obj(other_data_obj_mod[i]);
  }

  vector<CrossSectionDataContainer>().swap(xs_data_obj_mod);
  vector<EnergyAngularDataContainer>().swap(ene_angular_data_obj_mod);
  vector<ProductDistributionDataContainer>().swap(product_distr_data_obj_mod);
  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj_mod);
  vector<PhotonDataContainer>().swap(photon_data_obj_mod);
  vector<OtherNuclearDataContainer>().swap(other_data_obj_mod);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearReactionDataContainer::modify_reaction_type()
{
  int i_max = reaction_type_no;

  Integer end_chk = 1;
  while( end_chk != 0 )
  {
    end_chk = 0;
    for(int i=0; i<i_max; i++)
    {
      Integer react_val = reaction_type[i];
      if(  react_val == unassigned_mt_no ||
          (xs_data_obj[i].get_reaction_type()            != react_val &&
           ene_angular_data_obj[i].get_reaction_type()   != react_val &&
           product_distr_data_obj[i].get_reaction_type() != react_val &&
           radio_product_data_obj[i].get_reaction_type() != react_val &&
           photon_data_obj[i].get_reaction_type()        != react_val &&
           other_data_obj[i].get_reaction_type()         != react_val) )
      {
        remove_reaction_type(react_val);

        i_max   = reaction_type_no;
        end_chk = 1;
        break;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearReactionDataContainer::remove_reaction_type(Integer react_val)
{
  vector<Integer>                           reaction_type_mod;
  vector<CrossSectionDataContainer>         xs_data_obj_mod;
  vector<EnergyAngularDataContainer>        ene_angular_data_obj_mod;
  vector<ProductDistributionDataContainer>  product_distr_data_obj_mod;
  vector<RadioactiveProductDataContainer>   radio_product_data_obj_mod;
  vector<PhotonDataContainer>               photon_data_obj_mod;
  vector<OtherNuclearDataContainer>         other_data_obj_mod;

  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] != react_val )
    {
      reaction_type_mod.push_back(reaction_type[i]);

      xs_data_obj_mod.push_back(xs_data_obj[i]);
      ene_angular_data_obj_mod.push_back(ene_angular_data_obj[i]);
      product_distr_data_obj_mod.push_back(product_distr_data_obj[i]);
      radio_product_data_obj_mod.push_back(radio_product_data_obj[i]);
      photon_data_obj_mod.push_back(photon_data_obj[i]);
      other_data_obj_mod.push_back(other_data_obj[i]);
    }
  }

  reaction_type_no       = static_cast<int>(reaction_type_mod.size());
  reaction_type          = reaction_type_mod;
  xs_data_obj            = xs_data_obj_mod;
  ene_angular_data_obj   = ene_angular_data_obj_mod;
  product_distr_data_obj = product_distr_data_obj_mod;
  radio_product_data_obj = radio_product_data_obj_mod;
  photon_data_obj        = photon_data_obj_mod;
  other_data_obj         = other_data_obj_mod;
  
  reaction_type_mod.clear();
  vector<CrossSectionDataContainer>().swap(xs_data_obj_mod);
  vector<EnergyAngularDataContainer>().swap(ene_angular_data_obj_mod);
  vector<ProductDistributionDataContainer>().swap(product_distr_data_obj_mod);
  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj_mod);
  vector<PhotonDataContainer>().swap(photon_data_obj_mod);
  vector<OtherNuclearDataContainer>().swap(other_data_obj_mod);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Add vector data

void NuclearReactionDataContainer::add_reaction_type( vector<Integer> int_vec )
{
  int     i_max = static_cast<int>(int_vec.size());
  for(int i=0; i<i_max; i++)
  {
    set_reaction_type( int_vec[i] );
  }
  int_vec.clear();
}

void NuclearReactionDataContainer::add_xs_data_obj
                                     (vector<CrossSectionDataContainer> xs_data_obj_add)
{
  int i_max = static_cast<int>(xs_data_obj_add.size());
  for(int i=0; i<i_max; i++)
  {
    set_xs_data_obj(xs_data_obj_add[i].get_reaction_type(), xs_data_obj_add[i]);
  }

  vector<CrossSectionDataContainer>().swap(xs_data_obj_add);
}

void NuclearReactionDataContainer::add_ene_angular_data_obj
                                     (vector<EnergyAngularDataContainer> ene_angular_data_obj_add)
{
  int i_max = static_cast<int>(ene_angular_data_obj_add.size());
  for(int i=0; i<i_max; i++)
  {
    set_ene_angular_data_obj(ene_angular_data_obj_add[i].get_reaction_type(),
                             ene_angular_data_obj_add[i]);
  }

  vector<EnergyAngularDataContainer>().swap(ene_angular_data_obj_add);
}

void NuclearReactionDataContainer::add_product_distr_data_obj
                                    (vector<ProductDistributionDataContainer> product_distr_data_obj_add)
{
  int i_max = static_cast<int>(product_distr_data_obj_add.size());
  for(int i=0; i<i_max; i++)
  {
    set_product_distr_data_obj(product_distr_data_obj_add[i].get_reaction_type(),
                               product_distr_data_obj_add[i]);
  }

  vector<ProductDistributionDataContainer>().swap(product_distr_data_obj_add);
}

void NuclearReactionDataContainer::add_radio_product_data_obj
                                     (vector<RadioactiveProductDataContainer> radio_product_data_obj_add)
{
  int i_max = static_cast<int>(radio_product_data_obj_add.size());
  for(int i=0; i<i_max; i++)
  {
    set_radio_product_data_obj(radio_product_data_obj_add[i].get_reaction_type(),
                               radio_product_data_obj_add[i]);
  }

  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj_add);
}

void NuclearReactionDataContainer::add_photon_data_obj
                                     (vector<PhotonDataContainer> photon_data_obj_add)
{
  int i_max = static_cast<int>(photon_data_obj_add.size());
  for(int i=0; i<i_max; i++)
  {
    set_photon_data_obj(photon_data_obj_add[i].get_reaction_type(), photon_data_obj_add[i]);
  }

  vector<PhotonDataContainer>().swap(photon_data_obj_add);
}

void NuclearReactionDataContainer::add_other_data_obj
                                     (vector<OtherNuclearDataContainer> other_data_obj_add)
{
  int i_max = static_cast<int>(other_data_obj_add.size());
  for(int i=0; i<i_max; i++)
  {
    set_other_data_obj(other_data_obj_add[i].get_reaction_type(), other_data_obj_add[i]);
  }

  vector<OtherNuclearDataContainer>().swap(other_data_obj_add);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Getter

vector<Integer>                           NuclearReactionDataContainer::get_reaction_type()
{
  sort_reaction_data();
  return reaction_type;
}

vector<CrossSectionDataContainer>         NuclearReactionDataContainer::get_xs_data_obj()
{
  sort_reaction_data();
  return xs_data_obj;
}

vector<EnergyAngularDataContainer>        NuclearReactionDataContainer::get_ene_angular_data_obj()
{
  sort_reaction_data();
  return ene_angular_data_obj;
}

vector<ProductDistributionDataContainer>  NuclearReactionDataContainer::get_product_distr_data_obj()
{
  sort_reaction_data();
  return product_distr_data_obj;
}

vector<RadioactiveProductDataContainer>   NuclearReactionDataContainer::get_radio_product_data_obj()
{
  sort_reaction_data();
  return radio_product_data_obj;
}

vector<PhotonDataContainer>               NuclearReactionDataContainer::get_photon_data_obj()
{
  sort_reaction_data();
  return photon_data_obj;
}

vector<OtherNuclearDataContainer>         NuclearReactionDataContainer::get_other_data_obj()
{
  sort_reaction_data();
  return other_data_obj;
}


CrossSectionDataContainer         NuclearReactionDataContainer::get_xs_data_obj(Integer reaction_type_data)
{
  sort_reaction_data();

  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] == reaction_type_data )
    {
      return xs_data_obj[i];
    }
  }

  //string class_name = "NuclearReactionDataContainer";
  //string func_name  = "get_xs_data_obj(Integer reaction_type_data)";
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

  CrossSectionDataContainer tmp_data_obj;
  tmp_data_obj.clear();
  return tmp_data_obj;
}

EnergyAngularDataContainer        NuclearReactionDataContainer::get_ene_angular_data_obj(Integer reaction_type_data)
{
  sort_reaction_data();

  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] == reaction_type_data )
    {
      return ene_angular_data_obj[i];
    }
  }

  //string class_name = "NuclearReactionDataContainer";
  //string func_name  = "get_ene_angular_data_obj(Integer reaction_type_data)";
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

  EnergyAngularDataContainer tmp_data_obj;
  tmp_data_obj.clear();
  return tmp_data_obj;
}

ProductDistributionDataContainer  NuclearReactionDataContainer::get_product_distr_data_obj(Integer reaction_type_data)
{
  sort_reaction_data();

  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] == reaction_type_data )
    {
      return product_distr_data_obj[i];
    }
  }

  //string class_name = "NuclearReactionDataContainer";
  //string func_name  = "get_product_distr_data_obj(Integer reaction_type_data)";
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

  ProductDistributionDataContainer tmp_data_obj;
  tmp_data_obj.clear();
  return tmp_data_obj;
}

RadioactiveProductDataContainer   NuclearReactionDataContainer::get_radio_product_data_obj(Integer reaction_type_data)
{
  sort_reaction_data();

  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] == reaction_type_data )
    {
      return radio_product_data_obj[i];
    }
  }

  //string class_name = "NuclearReactionDataContainer";
  //string func_name  = "get_radio_product_data_obj(Integer reaction_type_data)";
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

  RadioactiveProductDataContainer tmp_data_obj;
  tmp_data_obj.clear();
  return tmp_data_obj;
}

PhotonDataContainer               NuclearReactionDataContainer::get_photon_data_obj(Integer reaction_type_data)
{
  sort_reaction_data();

  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] == reaction_type_data )
    {
      return photon_data_obj[i];
    }
  }

  //string class_name = "NuclearReactionDataContainer";
  //string func_name  = "get_photon_data_obj(Integer reaction_type_data)";
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

  PhotonDataContainer tmp_data_obj;
  tmp_data_obj.clear();
  return tmp_data_obj;
}

OtherNuclearDataContainer         NuclearReactionDataContainer::get_other_data_obj(Integer reaction_type_data)
{
  sort_reaction_data();

  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type[i] == reaction_type_data )
    {
      return other_data_obj[i];
    }
  }

  //string class_name = "NuclearReactionDataContainer";
  //string func_name  = "get_other_data_obj(Integer reaction_type_data)";
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

  OtherNuclearDataContainer tmp_data_obj;
  tmp_data_obj.clear();
  return tmp_data_obj;
}


vector<CrossSectionDataContainer>         NuclearReactionDataContainer::get_xs_data_obj_assigned()
{
  sort_reaction_data();

  vector<CrossSectionDataContainer> xs_data_obj_assigned;

  for(int i=0; i<reaction_type_no; i++)
  {
    if( xs_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      xs_data_obj_assigned.push_back(xs_data_obj[i]);
    }
  }

  return xs_data_obj_assigned;
}

vector<EnergyAngularDataContainer>        NuclearReactionDataContainer::get_ene_angular_data_obj_assigned()
{
  sort_reaction_data();

  vector<EnergyAngularDataContainer> ene_angular_data_obj_assigned;

  for(int i=0; i<reaction_type_no; i++)
  {
    if( ene_angular_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      ene_angular_data_obj_assigned.push_back(ene_angular_data_obj[i]);
    }
  }

  return ene_angular_data_obj_assigned;
}

vector<ProductDistributionDataContainer>  NuclearReactionDataContainer::get_product_distr_data_obj_assigned()
{
  sort_reaction_data();

  vector<ProductDistributionDataContainer> product_distr_data_obj_assigned;

  for(int i=0; i<reaction_type_no; i++)
  {
    if( product_distr_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      product_distr_data_obj_assigned.push_back(product_distr_data_obj[i]);
    }
  }

  return product_distr_data_obj_assigned;
}

vector<RadioactiveProductDataContainer>   NuclearReactionDataContainer::get_radio_product_data_obj_assigned()
{
  sort_reaction_data();

  vector<RadioactiveProductDataContainer> radio_product_data_obj_assigned;

  for(int i=0; i<reaction_type_no; i++)
  {
    if( radio_product_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      radio_product_data_obj_assigned.push_back(radio_product_data_obj[i]);
    }
  }

  return radio_product_data_obj_assigned;
}

vector<PhotonDataContainer>               NuclearReactionDataContainer::get_photon_data_obj_assigned()
{
  sort_reaction_data();

  vector<PhotonDataContainer> photon_data_obj_assigned;

  for(int i=0; i<reaction_type_no; i++)
  {
    if( photon_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      photon_data_obj_assigned.push_back(photon_data_obj[i]);
    }
  }

  return photon_data_obj_assigned;
}

vector<OtherNuclearDataContainer>         NuclearReactionDataContainer::get_other_data_obj_assigned()
{
  sort_reaction_data();

  vector<OtherNuclearDataContainer> other_data_obj_assigned;

  for(int i=0; i<reaction_type_no; i++)
  {
    if( other_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      other_data_obj_assigned.push_back(other_data_obj[i]);
    }
  }

  return other_data_obj_assigned;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//Setter
//Note that existence data is removed
//If you add the vector data, please use the add_... function.

void NuclearReactionDataContainer::set_reaction_type( vector<Integer> int_vec )
{
  int     i_max = static_cast<int>(int_vec.size());
  for(int i=0; i<i_max; i++)
  {
    set_reaction_type( int_vec[i] );
  }
  int_vec.clear();
}

void NuclearReactionDataContainer::set_xs_data_obj
                                     (vector<CrossSectionDataContainer> xs_data_obj_mod)
{
  for(int i=0; i<reaction_type_no; i++)
  {
    xs_data_obj[i].clear();
  }

  int i_max = static_cast<int>(xs_data_obj_mod.size());
  for(int i=0; i<i_max; i++)
  {
    set_xs_data_obj(xs_data_obj_mod[i]);
  }
  vector<CrossSectionDataContainer>().swap(xs_data_obj_mod);

  modify_reaction_type();
}

void NuclearReactionDataContainer::set_ene_angular_data_obj
                                     (vector<EnergyAngularDataContainer> ene_angular_data_obj_mod)
{
  for(int i=0; i<reaction_type_no; i++)
  {
    ene_angular_data_obj[i].clear();
  }

  int i_max = static_cast<int>(ene_angular_data_obj_mod.size());
  for(int i=0; i<i_max; i++)
  {
    set_ene_angular_data_obj(ene_angular_data_obj_mod[i]);
  }
  vector<EnergyAngularDataContainer>().swap(ene_angular_data_obj_mod);

  modify_reaction_type();
}

void NuclearReactionDataContainer::set_product_distr_data_obj
                                    (vector<ProductDistributionDataContainer> product_distr_data_obj_mod)
{
  for(int i=0; i<reaction_type_no; i++)
  {
    product_distr_data_obj[i].clear();
  }

  int i_max = static_cast<int>(product_distr_data_obj_mod.size());
  for(int i=0; i<i_max; i++)
  {
    set_product_distr_data_obj(product_distr_data_obj_mod[i]);
  }
  vector<ProductDistributionDataContainer>().swap(product_distr_data_obj_mod);

  modify_reaction_type();
}

void NuclearReactionDataContainer::set_radio_product_data_obj
                                     (vector<RadioactiveProductDataContainer> radio_product_data_obj_mod)
{
  for(int i=0; i<reaction_type_no; i++)
  {
    radio_product_data_obj[i].clear();
  }

  int i_max = static_cast<int>(radio_product_data_obj_mod.size());
  for(int i=0; i<i_max; i++)
  {
    set_radio_product_data_obj(radio_product_data_obj_mod[i]);
  }
  vector<RadioactiveProductDataContainer>().swap(radio_product_data_obj_mod);

  modify_reaction_type();
}

void NuclearReactionDataContainer::set_photon_data_obj
                                     (vector<PhotonDataContainer> photon_data_obj_mod)
{
  for(int i=0; i<reaction_type_no; i++)
  {
    photon_data_obj[i].clear();
  }

  int i_max = static_cast<int>(photon_data_obj_mod.size());
  for(int i=0; i<i_max; i++)
  {
    set_photon_data_obj(photon_data_obj_mod[i]);
  }
  vector<PhotonDataContainer>().swap(photon_data_obj_mod);

  modify_reaction_type();
}

void NuclearReactionDataContainer::set_other_data_obj
                                     (vector<OtherNuclearDataContainer> other_data_obj_mod)
{
  for(int i=0; i<reaction_type_no; i++)
  {
    other_data_obj[i].clear();
  }

  int i_max = static_cast<int>(other_data_obj_mod.size());
  for(int i=0; i<i_max; i++)
  {
    set_other_data_obj(other_data_obj_mod[i]);
  }
  vector<OtherNuclearDataContainer>().swap(other_data_obj_mod);

  modify_reaction_type();
}


void NuclearReactionDataContainer::set_reaction_type( Integer reaction_type_data )
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

void NuclearReactionDataContainer::set_xs_data_obj( Integer reaction_type_data, CrossSectionDataContainer data_obj )
{
  check_reaction_type(reaction_type_data, data_obj.get_reaction_type());

  Integer mod_flg = 0;
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type_data == reaction_type[i] )
    {
      mod_flg   = 1;
      xs_data_obj[i].clear();
      xs_data_obj[i] = data_obj;
      break;
    }
  }
  if( mod_flg == 0 )
  {
    if( add_new_reaction_type( reaction_type_data ) > 0 )
    {
      xs_data_obj[reaction_type_no-1] = data_obj;
    }
  }
  data_obj.clear();
}

void NuclearReactionDataContainer::set_ene_angular_data_obj( Integer reaction_type_data, EnergyAngularDataContainer data_obj )
{
  check_reaction_type(reaction_type_data, data_obj.get_reaction_type());

  Integer mod_flg = 0;
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type_data == reaction_type[i] )
    {
      mod_flg   = 1;
      ene_angular_data_obj[i].clear();
      ene_angular_data_obj[i] = data_obj;
      break;
    }
  }
  if( mod_flg == 0 )
  {
    if( add_new_reaction_type( reaction_type_data ) > 0 )
    { 
      ene_angular_data_obj[reaction_type_no-1] = data_obj;
    }
  }
  data_obj.clear();
}

void NuclearReactionDataContainer::set_product_distr_data_obj( Integer reaction_type_data, ProductDistributionDataContainer data_obj )
{
  check_reaction_type(reaction_type_data, data_obj.get_reaction_type());

  Integer mod_flg = 0;
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type_data == reaction_type[i] )
    {
      mod_flg   = 1;
      product_distr_data_obj[i].clear();
      product_distr_data_obj[i] = data_obj;
      break;
    }
  }
  if( mod_flg == 0 )
  {
    if( add_new_reaction_type( reaction_type_data ) > 0 )
    {
      product_distr_data_obj[reaction_type_no-1] = data_obj;
    }
  }
  data_obj.clear();
}

void NuclearReactionDataContainer::set_radio_product_data_obj( Integer reaction_type_data, RadioactiveProductDataContainer data_obj )
{
  check_reaction_type(reaction_type_data, data_obj.get_reaction_type());

  Integer mod_flg = 0;
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type_data == reaction_type[i] )
    {
      mod_flg   = 1;
      radio_product_data_obj[i].clear();
      radio_product_data_obj[i] = data_obj;
      break;
    }
  }
  if( mod_flg == 0 )
  {
    if( add_new_reaction_type( reaction_type_data ) > 0 )
    {
      radio_product_data_obj[reaction_type_no-1] = data_obj;
    }
  }
  data_obj.clear();
}

void NuclearReactionDataContainer::set_photon_data_obj( Integer reaction_type_data, PhotonDataContainer data_obj )
{
  check_reaction_type(reaction_type_data, data_obj.get_reaction_type());

  Integer mod_flg = 0;
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type_data == reaction_type[i] )
    {
      mod_flg   = 1;
      photon_data_obj[i].clear();
      photon_data_obj[i] = data_obj;
      break;
    }
  }
  if( mod_flg == 0 )
  {
    if( add_new_reaction_type( reaction_type_data ) > 0 )
    {
      photon_data_obj[reaction_type_no-1] = data_obj;
    }
  }
  data_obj.clear();
}

void NuclearReactionDataContainer::set_other_data_obj( Integer reaction_type_data, OtherNuclearDataContainer data_obj )
{
  check_reaction_type(reaction_type_data, data_obj.get_reaction_type());

  Integer mod_flg = 0;
  for(int i=0; i<reaction_type_no; i++)
  {
    if( reaction_type_data == reaction_type[i] )
    {
      mod_flg   = 1;
      other_data_obj[i].clear();
      other_data_obj[i] = data_obj;
      break;
    }
  }
  if( mod_flg == 0 )
  {
    if( add_new_reaction_type( reaction_type_data ) > 0 )
    {
      other_data_obj[reaction_type_no-1] = data_obj;
    }
  }
  data_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int NuclearReactionDataContainer::check_reaction_type(Integer reaction_type_check)
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

void NuclearReactionDataContainer::check_reaction_type( Integer reaction_type_inp, Integer reaction_type_nucl )
{
  if( reaction_type_inp != reaction_type_nucl )
  {
    string class_name = "NuclearReactionDataContainer";
    string func_name  = "check_reaction_type";

    ostringstream oss01, oss02;
    oss01 << reaction_type_inp;
    oss02 << reaction_type_nucl;

    string str_data00 = "Reaction type number is not identical.";
    string str_data01 = "  Reaction type number from parameter    : " + oss01.str();
    string str_data02 = "  Reaction type number from nuclear data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearReactionDataContainer::set_xs_data_obj( frendy::CrossSectionDataContainer data_obj )
{
  Integer reaction_type_data = data_obj.get_reaction_type();
  set_xs_data_obj(reaction_type_data, data_obj);
}

void NuclearReactionDataContainer::set_ene_angular_data_obj( frendy::EnergyAngularDataContainer data_obj )
{
  Integer reaction_type_data = data_obj.get_reaction_type();
  set_ene_angular_data_obj(reaction_type_data, data_obj);
}

void NuclearReactionDataContainer::set_product_distr_data_obj( frendy::ProductDistributionDataContainer data_obj )
{
  Integer reaction_type_data = data_obj.get_reaction_type();
  set_product_distr_data_obj(reaction_type_data, data_obj);
}

void NuclearReactionDataContainer::set_radio_product_data_obj( frendy::RadioactiveProductDataContainer data_obj )
{
  Integer reaction_type_data = data_obj.get_reaction_type();
  set_radio_product_data_obj(reaction_type_data, data_obj);
}

void NuclearReactionDataContainer::set_photon_data_obj( frendy::PhotonDataContainer data_obj )
{
  Integer reaction_type_data = data_obj.get_reaction_type();
  set_photon_data_obj(reaction_type_data, data_obj);
}

void NuclearReactionDataContainer::set_other_data_obj( frendy::OtherNuclearDataContainer data_obj )
{
  Integer reaction_type_data = data_obj.get_reaction_type();
  set_other_data_obj(reaction_type_data, data_obj);
}

