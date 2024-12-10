#include "NuclearDataUtils/NuclearDataContainer/ResonanceDataContainer.hpp"

using namespace frendy;

//constructor
ResonanceDataContainer::ResonanceDataContainer(void)
{
  clear();
}

//destructor
ResonanceDataContainer::~ResonanceDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceDataContainer::clear()
{
  mat_data_isotope.clear();
  abundance_isotope.clear();
  fis_width_flg.clear();
  clr_obj.clear_vec_array2_real( lower_ene_limit );
  clr_obj.clear_vec_array2_real( upper_ene_limit );
  clr_obj.clear_vec_array2_int( reso_region_flg );
  clr_obj.clear_vec_array2_int( xs_formula_flg );
  clr_obj.clear_vec_array2_int( scat_radius_ene_dependence_flg );
  clr_obj.clear_vec_array2_int( radius_calc_flg );
  clr_obj.clear_vec_array2_real( spin_data );
  clr_obj.clear_vec_array2_real( scat_radius );
  clr_obj.clear_vec_array3_int( scat_radius_tab_int_data );
  clr_obj.clear_vec_array3_int( scat_radius_tab_range_data );
  clr_obj.clear_vec_array3_real( scat_radius_tab_ene_data );
  clr_obj.clear_vec_array3_real( scat_radius_tab_data );
  clr_obj.clear_vec_array3_int( l_value );
  clr_obj.clear_vec_array3_real( mass_isotope );

  clear_bw_data_obj(bw_data_obj);
  clear_rm_data_obj(rm_data_obj);
  clear_adler_data_obj(adler_data_obj);
  clear_r_matrix_data_obj(r_matrix_data_obj);
  clear_unreso_data_obj(unreso_data_obj);

  unreso_xs_data_obj.clear(); 
  unreso_prob_data_obj.clear(); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceDataContainer::clear_bw_data_obj(vector<vector<BreitWignerDataContainer> >& data_obj)
{
  vector<vector<BreitWignerDataContainer> >().swap(data_obj);

  //int i_max = static_cast<int>(data_obj.size());
  //for(int i=0; i<i_max; i++)
  //{
  //  int j_max = static_cast<int>(data_obj[i].size());
  //  for(int j=0; j<j_max; j++)
  //  {
  //    data_obj[i][j].clear();
  //  }
  //  data_obj[i].resize(0);
  //}
  //data_obj.resize(0);
}

void ResonanceDataContainer::clear_rm_data_obj(vector<vector<ReichMooreDataContainer> >& data_obj)
{
  vector<vector<ReichMooreDataContainer> >().swap(data_obj);

  //int i_max = static_cast<int>(data_obj.size());
  //for(int i=0; i<i_max; i++)
  //{
  //  int j_max = static_cast<int>(data_obj[i].size());
  //  for(int j=0; j<j_max; j++)
  //  {
  //    data_obj[i][j].clear();
  //  }
  //  data_obj[i].resize(0);
  //}
  //data_obj.resize(0);
}

void ResonanceDataContainer::clear_adler_data_obj(vector<vector<AdlerAdlerDataContainer> >& data_obj)
{
  vector<vector<AdlerAdlerDataContainer> >().swap(data_obj);

  //int i_max = static_cast<int>(data_obj.size());
  //for(int i=0; i<i_max; i++)
  //{
  //  int j_max = static_cast<int>(data_obj[i].size());
  //  for(int j=0; j<j_max; j++)
  //  {
  //    data_obj[i][j].clear();
  //  }
  //  data_obj[i].resize(0);
  //}
  //data_obj.resize(0);
}

void ResonanceDataContainer::clear_r_matrix_data_obj(vector<vector<RMatrixLimitedDataContainer> >& data_obj)
{
  vector<vector<RMatrixLimitedDataContainer> >().swap(data_obj);

  //int i_max = static_cast<int>(data_obj.size());
  //for(int i=0; i<i_max; i++)
  //{
  //  int j_max = static_cast<int>(data_obj[i].size());
  //  for(int j=0; j<j_max; j++)
  //  {
  //    data_obj[i][j].clear();
  //  }
  //  data_obj[i].resize(0);
  //}
  //data_obj.resize(0);
}

void ResonanceDataContainer::clear_unreso_data_obj(vector<vector<UnresolvedResonanceDataContainer> >& data_obj)
{
  vector<vector<UnresolvedResonanceDataContainer> >().swap(data_obj);

  //int i_max = static_cast<int>(data_obj.size());
  //for(int i=0; i<i_max; i++)
  //{
  //  int j_max = static_cast<int>(data_obj[i].size());
  //  for(int j=0; j<j_max; j++)
  //  {
  //    data_obj[i][j].clear();
  //  }
  //  data_obj[i].resize(0);
  //}
  //data_obj.resize(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ResonanceDataContainer::check_data_size( int i, int j, int ele_no, int ele_max,
                                              string func_name, string ele_name )
{
  if( ele_no >= ele_max )
  {
    string class_name = "ResonanceDataContainer";
           func_name  = func_name + "(int i, int j)";
    ostringstream oss01, oss02, oss03;
    oss01 << i;
    oss02 << j;
    oss03 << ele_max;
    string str_data01 = "Position : i=" + oss01.str() + ", j=" + oss02.str();
    string str_data02 = ele_name + "    : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The position is over i_max");
    err_com.push_back("Please check position.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Getter
vector<Real> ResonanceDataContainer::get_mat_data_isotope()
{
  return mat_data_isotope;
}

vector<Real> ResonanceDataContainer::get_abundance_isotope()
{
  return abundance_isotope;
}

vector<Integer> ResonanceDataContainer::get_fis_width_flg()
{
  return fis_width_flg;
}

vector<vector<Real> > ResonanceDataContainer::get_lower_ene_limit()
{
  return lower_ene_limit;
}

vector<vector<Real> > ResonanceDataContainer::get_upper_ene_limit()
{
  return upper_ene_limit;
}

vector<vector<Integer> > ResonanceDataContainer::get_reso_region_flg()
{
  return reso_region_flg;
}

vector<vector<Integer> > ResonanceDataContainer::get_xs_formula_flg()
{
  return xs_formula_flg;
}

vector<vector<Integer> > ResonanceDataContainer::get_scat_radius_ene_dependence_flg()
{
  return scat_radius_ene_dependence_flg;
}

vector<vector<Integer> > ResonanceDataContainer::get_radius_calc_flg()
{
  return radius_calc_flg;
}

vector<vector<Real> > ResonanceDataContainer::get_spin_data()
{
  return spin_data;
}

vector<vector<Real> > ResonanceDataContainer::get_scat_radius()
{
  return scat_radius;
}

vector<vector<vector<Integer> > > ResonanceDataContainer::get_scat_radius_tab_int_data()
{
  return scat_radius_tab_int_data;
}

vector<vector<vector<Integer> > > ResonanceDataContainer::get_scat_radius_tab_range_data()
{
  return scat_radius_tab_range_data;
}

vector<vector<vector<Real> > > ResonanceDataContainer::get_scat_radius_tab_ene_data()
{
  return scat_radius_tab_ene_data;
}

vector<vector<vector<Real> > > ResonanceDataContainer::get_scat_radius_tab_data()
{
  return scat_radius_tab_data;
}

vector<vector<vector<Integer> > > ResonanceDataContainer::get_l_value()
{
  return l_value;
}

vector<vector<vector<Real> > > ResonanceDataContainer::get_mass_isotope()
{
  return mass_isotope;
}


vector<vector<BreitWignerDataContainer> >         ResonanceDataContainer::get_bw_data_obj()
{
  return bw_data_obj;
}

vector<vector<ReichMooreDataContainer> >          ResonanceDataContainer::get_rm_data_obj()
{
  return rm_data_obj;
}

vector<vector<AdlerAdlerDataContainer> >          ResonanceDataContainer::get_adler_data_obj()
{
  return adler_data_obj;
}

vector<vector<RMatrixLimitedDataContainer> >      ResonanceDataContainer::get_r_matrix_data_obj()
{
  return r_matrix_data_obj;
}

vector<vector<UnresolvedResonanceDataContainer> > ResonanceDataContainer::get_unreso_data_obj()
{
  return unreso_data_obj;
}


BreitWignerDataContainer            ResonanceDataContainer::get_bw_data_obj(int i, int j)
{
  string func_name = "get_bw_data_obj";

  int    i_max    = static_cast<int>(bw_data_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(bw_data_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return bw_data_obj[i][j];
}

ReichMooreDataContainer             ResonanceDataContainer::get_rm_data_obj(int i, int j)
{
  string func_name = "get_rm_data_obj";

  int    i_max    = static_cast<int>(rm_data_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(rm_data_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return rm_data_obj[i][j];
}

AdlerAdlerDataContainer             ResonanceDataContainer::get_adler_data_obj(int i, int j)
{
  string func_name = "get_adler_data_obj";

  int    i_max    = static_cast<int>(adler_data_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(adler_data_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return adler_data_obj[i][j];
}

RMatrixLimitedDataContainer         ResonanceDataContainer::get_r_matrix_data_obj(int i, int j)
{
  string func_name = "get_r_matrix_data_obj";

  int    i_max    = static_cast<int>(r_matrix_data_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(r_matrix_data_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return r_matrix_data_obj[i][j];
}

UnresolvedResonanceDataContainer    ResonanceDataContainer::get_unreso_data_obj(int i, int j)
{
  string func_name = "get_unreso_data_obj";

  int    i_max    = static_cast<int>(unreso_data_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(unreso_data_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return unreso_data_obj[i][j];
}

UnresolvedCrossSectionDataContainer ResonanceDataContainer::get_unreso_xs_data_obj()
{
  return unreso_xs_data_obj;
}

UnresolvedProbabilityDataContainer ResonanceDataContainer::get_unreso_prob_data_obj()
{
  return unreso_prob_data_obj;
}

Real ResonanceDataContainer::get_el_reso()
{
  int  ene_flg = 0;
  Real ene_val = 1.0E+50;

  int i_max = static_cast<int>(reso_region_flg.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_region_flg[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( reso_region_flg[i][j] == 1 && ene_val > lower_ene_limit[i][j] )
      {
        ene_flg = 1;
        ene_val = lower_ene_limit[i][j];
      }
    }
  }

  if( ene_flg == 0 )
  {
    ene_val = 0.0;
  }

  return ene_val;
}

Real ResonanceDataContainer::get_eh_reso()
{
  int  ene_flg = 0;
  Real ene_val = 0.0;

  int i_max = static_cast<int>(reso_region_flg.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_region_flg[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( reso_region_flg[i][j] == 1 && ene_val < upper_ene_limit[i][j] )
      {
        ene_flg = 1;
        ene_val = upper_ene_limit[i][j];
      }
    }
  }

  if( ene_flg == 0 )
  {
    ene_val = 0.0;
  }

  return ene_val;
}

Real ResonanceDataContainer::get_el_unreso()
{
  int  ene_flg = 0;
  Real ene_val = 1.0E+50;

  int i_max = static_cast<int>(reso_region_flg.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_region_flg[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( reso_region_flg[i][j] == 2 && ene_val > lower_ene_limit[i][j] )
      {
        ene_flg = 1;
        ene_val = lower_ene_limit[i][j];
      }
    }
  }

  if( ene_flg == 0 )
  {
    ene_val = 0.0;
  }

  return ene_val;
}

Real ResonanceDataContainer::get_eh_unreso()
{
  int  ene_flg = 0;
  Real ene_val = 0.0;

  int i_max = static_cast<int>(reso_region_flg.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(reso_region_flg[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( reso_region_flg[i][j] == 2 && ene_val < upper_ene_limit[i][j] )
      {
        ene_flg = 1;
        ene_val = upper_ene_limit[i][j];
      }
    }
  }

  if( ene_flg == 0 )
  {
    ene_val = 0.0;
  }

  return ene_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void ResonanceDataContainer::set_mat_data_isotope( vector<Real> real_vec )
{
  mat_data_isotope = real_vec;
  real_vec.clear();
}

void ResonanceDataContainer::set_abundance_isotope( vector<Real> real_vec )
{
  abundance_isotope = real_vec;
  real_vec.clear();
}

void ResonanceDataContainer::set_fis_width_flg( vector<Integer> int_vec )
{
  fis_width_flg = int_vec;
  int_vec.clear();
}

void ResonanceDataContainer::set_lower_ene_limit( vector<vector<Real> > real_vec )
{
  lower_ene_limit = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ResonanceDataContainer::set_upper_ene_limit( vector<vector<Real> > real_vec )
{
  upper_ene_limit = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ResonanceDataContainer::set_reso_region_flg( vector<vector<Integer> > int_vec )
{
  reso_region_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ResonanceDataContainer::set_xs_formula_flg( vector<vector<Integer> > int_vec )
{
  xs_formula_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ResonanceDataContainer::set_scat_radius_ene_dependence_flg( vector<vector<Integer> > int_vec )
{
  scat_radius_ene_dependence_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ResonanceDataContainer::set_radius_calc_flg( vector<vector<Integer> > int_vec )
{
  radius_calc_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void ResonanceDataContainer::set_spin_data( vector<vector<Real> > real_vec )
{
  spin_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ResonanceDataContainer::set_scat_radius( vector<vector<Real> > real_vec )
{
  scat_radius = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void ResonanceDataContainer::set_scat_radius_tab_int_data( vector<vector<vector<Integer> > > int_vec )
{
  scat_radius_tab_int_data = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void ResonanceDataContainer::set_scat_radius_tab_range_data( vector<vector<vector<Integer> > > int_vec )
{
  scat_radius_tab_range_data = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void ResonanceDataContainer::set_scat_radius_tab_ene_data( vector<vector<vector<Real> > > real_vec )
{
  scat_radius_tab_ene_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ResonanceDataContainer::set_scat_radius_tab_data( vector<vector<vector<Real> > > real_vec )
{
  scat_radius_tab_data = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ResonanceDataContainer::set_l_value( vector<vector<vector<Integer> > > int_vec )
{
  l_value = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void ResonanceDataContainer::set_mass_isotope( vector<vector<vector<Real> > > real_vec )
{
  mass_isotope = real_vec;
  clr_obj.clear_vec_array3_real( real_vec );
}

void ResonanceDataContainer::set_bw_data_obj( vector<vector<BreitWignerDataContainer> > obj_data )
{
  clear_bw_data_obj(bw_data_obj);

  bw_data_obj = obj_data;

  clear_bw_data_obj(obj_data);
}

void ResonanceDataContainer::set_rm_data_obj( vector<vector<ReichMooreDataContainer> > obj_data )
{
  clear_rm_data_obj(rm_data_obj);

  rm_data_obj = obj_data;

  clear_rm_data_obj(obj_data);
}

void ResonanceDataContainer::set_adler_data_obj( vector<vector<AdlerAdlerDataContainer> > obj_data )
{
  clear_adler_data_obj(adler_data_obj);

  adler_data_obj = obj_data;

  clear_adler_data_obj(obj_data);
}

void ResonanceDataContainer::set_r_matrix_data_obj( vector<vector<RMatrixLimitedDataContainer> > obj_data )
{
  clear_r_matrix_data_obj(r_matrix_data_obj);

  r_matrix_data_obj = obj_data;

  clear_r_matrix_data_obj(obj_data);
}

void ResonanceDataContainer::set_unreso_data_obj( vector<vector<UnresolvedResonanceDataContainer> > obj_data )
{
  clear_unreso_data_obj(unreso_data_obj);

  unreso_data_obj = obj_data;

  clear_unreso_data_obj(obj_data);
}


void ResonanceDataContainer::set_bw_data_obj( int i, int j, BreitWignerDataContainer obj_data )
{
  string func_name = "set_bw_data_obj";

  int    i_max    = static_cast<int>(bw_data_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(bw_data_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  bw_data_obj[i][j] = obj_data;
  obj_data.clear();
}

void ResonanceDataContainer::set_rm_data_obj( int i, int j, ReichMooreDataContainer obj_data )
{
  string func_name = "set_rm_data_obj";

  int    i_max    = static_cast<int>(rm_data_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(rm_data_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  rm_data_obj[i][j] = obj_data;
  obj_data.clear();
}

void ResonanceDataContainer::set_adler_data_obj( int i, int j, AdlerAdlerDataContainer obj_data )
{
  string func_name = "set_adler_data_obj";

  int    i_max    = static_cast<int>(adler_data_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(adler_data_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  adler_data_obj[i][j] = obj_data;
  obj_data.clear();
}

void ResonanceDataContainer::set_r_matrix_data_obj( int i, int j, RMatrixLimitedDataContainer obj_data )
{
  string func_name = "set_r_matrix_data_obj";

  int    i_max    = static_cast<int>(r_matrix_data_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(r_matrix_data_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  r_matrix_data_obj[i][j] = obj_data;
  obj_data.clear();
}

void ResonanceDataContainer::set_unreso_data_obj( int i, int j, UnresolvedResonanceDataContainer obj_data )
{
  string func_name = "set_unreso_data_obj";

  int    i_max    = static_cast<int>(unreso_data_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(unreso_data_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  unreso_data_obj[i][j] = obj_data;
  obj_data.clear();
}

void ResonanceDataContainer::set_unreso_xs_data_obj( UnresolvedCrossSectionDataContainer obj_data )
{
  unreso_xs_data_obj = obj_data;
  obj_data.clear();
}

void ResonanceDataContainer::set_unreso_prob_data_obj( UnresolvedProbabilityDataContainer obj_data )
{
  unreso_prob_data_obj = obj_data;
  obj_data.clear();
}


