#include "NuclearDataUtils/ProbabilityDataContainer/ProbabilityDataContainer.hpp"

using namespace frendy;

//constructor
ProbabilityDataContainer::ProbabilityDataContainer(void)
{
  clear();
}

//destructor
ProbabilityDataContainer::~ProbabilityDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityDataContainer::clear()
{
  clear_prob_table_data_obj(prob_table_data_obj);

  unreso_int_data    = 0;
  self_shielding_flg = 0;
  comp_flg_inela     = 0;
  comp_flg_abs       = 0;
  comp_flg           = 0;
  prob_table_ene_no  = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ProbabilityDataContainer::clear_prob_table_data_obj
                                 (vector<ProbabilityTableDataContainer>& data_obj)
{
  vector<ProbabilityTableDataContainer>().swap(data_obj);

  //int i_max = static_cast<int>(data_obj.size());
  //for(int i=0; i<i_max; i++)
  //{
  //  data_obj[i].clear();
  //}
  //data_obj.resize(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
Integer ProbabilityDataContainer::get_unreso_int_data()
{
  return unreso_int_data;
}

Integer ProbabilityDataContainer::get_self_shielding_flg()
{
  return self_shielding_flg;
}

Integer ProbabilityDataContainer::get_comp_flg_inela()
{
  return comp_flg_inela;
}

Integer ProbabilityDataContainer::get_comp_flg_abs()
{
  return comp_flg_abs;
}

Integer ProbabilityDataContainer::get_comp_flg()
{
  return comp_flg;
}

int ProbabilityDataContainer::get_prob_table_ene_no()
{
  return prob_table_ene_no;
}

vector<ProbabilityTableDataContainer> ProbabilityDataContainer::get_prob_table_data_obj()
{
  return prob_table_data_obj;
}

ProbabilityTableDataContainer ProbabilityDataContainer::get_prob_table_data_obj(int ene_no)
{
  if( ene_no >= prob_table_ene_no )
  {
    string class_name = "ProbabilityDataContainer";
    string func_name  = "get_prob_table_data_obj(int ene_no)";

    ostringstream oss01, oss02;
    oss01 << prob_table_ene_no;
    oss02 << ene_no;

    string str_data00 = "The element number is larger than the array size.";
    string str_data01 = "  Element number of energy (array size / set value) : "
                      + oss01.str() + " / " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i = static_cast<int>(ene_no);

  return prob_table_data_obj[i];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void ProbabilityDataContainer::set_unreso_int_data(Integer int_val)
{
  unreso_int_data = int_val;
}

void ProbabilityDataContainer::set_self_shielding_flg(Integer int_val)
{
  self_shielding_flg = int_val;
}

void ProbabilityDataContainer::set_comp_flg_inela(Integer int_val)
{
  comp_flg_inela = int_val;
}

void ProbabilityDataContainer::set_comp_flg_abs(Integer int_val)
{
  comp_flg_abs = int_val;
}

void ProbabilityDataContainer::set_comp_flg(Integer int_val)
{
  comp_flg = int_val;
}

void ProbabilityDataContainer::set_prob_table_ene_no(int ene_no)
{
  clear_prob_table_data_obj(prob_table_data_obj);

  prob_table_ene_no = ene_no;

  prob_table_data_obj.resize(prob_table_ene_no);
}

void ProbabilityDataContainer::set_prob_table_data_obj(vector<ProbabilityTableDataContainer> data_obj)
{
  clear_prob_table_data_obj(prob_table_data_obj);
  prob_table_ene_no = static_cast<int>(data_obj.size());

  prob_table_data_obj = data_obj;
  clear_prob_table_data_obj(data_obj);
}

void ProbabilityDataContainer::set_prob_table_data_obj( int ene_no, ProbabilityTableDataContainer data_obj )
{
  if( ene_no >= prob_table_ene_no )
  {
    string class_name = "ProbabilityDataContainer";
    string func_name  = "set_prob_table_data_obj( int ene_no, ProbabilityTableDataContainer data_obj )";

    ostringstream oss01, oss02;
    oss01 << prob_table_ene_no;
    oss02 << ene_no;

    string str_data00 = "The element number is larger than the array size.";
    string str_data01 = "  Element number of energy (array size / set value) : "
                      + oss01.str() + " / " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data00);
    err_com.push_back(str_data01);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i = static_cast<int>(ene_no);
  prob_table_data_obj[i] = data_obj;
  data_obj.clear();
}

