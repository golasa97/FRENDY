#include "NuclearDataUtils/CovarianceDataContainer/CovarianceResonanceDataContainer.hpp"

using namespace frendy;

//constructor
CovarianceResonanceDataContainer::CovarianceResonanceDataContainer(void)
{
  clear();
}

//destructor
CovarianceResonanceDataContainer::~CovarianceResonanceDataContainer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CovarianceResonanceDataContainer::clear()
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
  clr_obj.clear_vec_array2_int( angular_distr_calc_flg );
  clr_obj.clear_vec_array2_int( compatibility_flg );
  clr_obj.clear_vec_array3_int( cov_matrix_data_flg );
  clr_obj.clear_vec_array4_real( cov_matrix_ene_k );
  clr_obj.clear_vec_array5_real( cov_matrix_coef_k );
  clr_obj.clear_vec_array4_real( cov_matrix_ene_l );
  clr_obj.clear_vec_array5_real( cov_matrix_coef_l );
  clr_obj.clear_vec_array2_real( mass_isotope );

  clear_compatible_obj(compatible_obj);
  clear_bw_obj(bw_obj);
  clear_rm_obj(rm_obj);
  clear_adler_obj(adler_obj);
  clear_r_matrix_obj(r_matrix_obj);
  clear_bw_compact_obj(bw_compact_obj);
  clear_rm_compact_obj(rm_compact_obj);
  clear_r_matrix_compact_obj(r_matrix_compact_obj);
  clear_unreso_obj(unreso_obj);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CovarianceResonanceDataContainer::clear_compatible_obj(vector<vector<CompatibleResolvedResonanceDataContainer> >& data_obj)
{
  vector<vector<CompatibleResolvedResonanceDataContainer> >().swap(data_obj);

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

void CovarianceResonanceDataContainer::clear_bw_obj(vector<vector<BreitWignerCovarianceDataContainer> >& data_obj)
{
  vector<vector<BreitWignerCovarianceDataContainer> >().swap(data_obj);

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

void CovarianceResonanceDataContainer::clear_rm_obj(vector<vector<ReichMooreCovarianceDataContainer> >& data_obj)
{
  vector<vector<ReichMooreCovarianceDataContainer> >().swap(data_obj);

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

void CovarianceResonanceDataContainer::clear_adler_obj(vector<vector<AdlerAdlerCovarianceDataContainer> >& data_obj)
{
  vector<vector<AdlerAdlerCovarianceDataContainer> >().swap(data_obj);

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

void CovarianceResonanceDataContainer::clear_r_matrix_obj(vector<vector<RMatrixLimitedCovarianceDataContainer> >& data_obj)
{
  vector<vector<RMatrixLimitedCovarianceDataContainer> >().swap(data_obj);

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

void CovarianceResonanceDataContainer::clear_bw_compact_obj(vector<vector<BreitWignerCompactCovarianceDataContainer> >& data_obj)
{
  vector<vector<BreitWignerCompactCovarianceDataContainer> >().swap(data_obj);

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

void CovarianceResonanceDataContainer::clear_rm_compact_obj(vector<vector<ReichMooreCompactCovarianceDataContainer> >& data_obj)
{
  vector<vector<ReichMooreCompactCovarianceDataContainer> >().swap(data_obj);

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

void CovarianceResonanceDataContainer::clear_r_matrix_compact_obj(vector<vector<RMatrixLimitedCompactCovarianceDataContainer> >& data_obj)
{
  vector<vector<RMatrixLimitedCompactCovarianceDataContainer> >().swap(data_obj);

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

void CovarianceResonanceDataContainer::clear_unreso_obj(vector<vector<UnresolvedResonanceCovarianceDataContainer> >& data_obj)
{
  vector<vector<UnresolvedResonanceCovarianceDataContainer> >().swap(data_obj);

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

void CovarianceResonanceDataContainer::check_data_size( int i, int j, int ele_no, int ele_max,
                                                        string func_name, string ele_name )
{
  if( ele_no >= ele_max )
  {
    string class_name = "CovarianceResonanceDataContainer";
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
vector<Real> CovarianceResonanceDataContainer::get_mat_data_isotope()
{
  return mat_data_isotope;
}

vector<Real> CovarianceResonanceDataContainer::get_abundance_isotope()
{
  return abundance_isotope;
}

vector<Integer> CovarianceResonanceDataContainer::get_fis_width_flg()
{
  return fis_width_flg;
}

vector<vector<Real> > CovarianceResonanceDataContainer::get_lower_ene_limit()
{
  return lower_ene_limit;
}

vector<vector<Real> > CovarianceResonanceDataContainer::get_upper_ene_limit()
{
  return upper_ene_limit;
}

vector<vector<Integer> > CovarianceResonanceDataContainer::get_reso_region_flg()
{
  return reso_region_flg;
}

vector<vector<Integer> > CovarianceResonanceDataContainer::get_xs_formula_flg()
{
  return xs_formula_flg;
}

vector<vector<Integer> > CovarianceResonanceDataContainer::get_scat_radius_ene_dependence_flg()
{
  return scat_radius_ene_dependence_flg;
}

vector<vector<Integer> > CovarianceResonanceDataContainer::get_radius_calc_flg()
{
  return radius_calc_flg;
}

vector<vector<Real> > CovarianceResonanceDataContainer::get_spin_data()
{
  return spin_data;
}

vector<vector<Real> > CovarianceResonanceDataContainer::get_scat_radius()
{
  return scat_radius;
}

vector<vector<Integer> > CovarianceResonanceDataContainer::get_angular_distr_calc_flg()
{
  return angular_distr_calc_flg;
}

vector<vector<Integer> > CovarianceResonanceDataContainer::get_compatibility_flg()
{
  return compatibility_flg;
}

vector<vector<vector<Integer> > > CovarianceResonanceDataContainer::get_cov_matrix_data_flg()
{
  return cov_matrix_data_flg;
}

vector<vector<vector<vector<Real> > > > CovarianceResonanceDataContainer::get_cov_matrix_ene_k()
{
  return cov_matrix_ene_k;
}

vector<vector<vector<vector<vector<Real> > > > > CovarianceResonanceDataContainer::get_cov_matrix_coef_k()
{
  return cov_matrix_coef_k;
}

vector<vector<vector<vector<Real> > > > CovarianceResonanceDataContainer::get_cov_matrix_ene_l()
{
  return cov_matrix_ene_l;
}

vector<vector<vector<vector<vector<Real> > > > > CovarianceResonanceDataContainer::get_cov_matrix_coef_l()
{
  return cov_matrix_coef_l;
}

vector<vector<Real> > CovarianceResonanceDataContainer::get_mass_isotope()
{
  return mass_isotope;
}

vector<vector<CompatibleResolvedResonanceDataContainer> >      CovarianceResonanceDataContainer::get_compatible_obj()
{
  return compatible_obj;
}

vector<vector<BreitWignerCovarianceDataContainer> >            CovarianceResonanceDataContainer::get_bw_obj()
{
  return bw_obj;
}

vector<vector<ReichMooreCovarianceDataContainer> >             CovarianceResonanceDataContainer::get_rm_obj()
{
  return rm_obj;
}

vector<vector<AdlerAdlerCovarianceDataContainer> >             CovarianceResonanceDataContainer::get_adler_obj()
{
  return adler_obj;
}

vector<vector<RMatrixLimitedCovarianceDataContainer> >         CovarianceResonanceDataContainer::get_r_matrix_obj()
{
  return r_matrix_obj;
}

vector<vector<BreitWignerCompactCovarianceDataContainer> >     CovarianceResonanceDataContainer::get_bw_compact_obj()
{
  return bw_compact_obj;
}

vector<vector<ReichMooreCompactCovarianceDataContainer> >      CovarianceResonanceDataContainer::get_rm_compact_obj()
{
  return rm_compact_obj;
}

vector<vector<RMatrixLimitedCompactCovarianceDataContainer> >  CovarianceResonanceDataContainer::get_r_matrix_compact_obj()
{
  return r_matrix_compact_obj;
}

vector<vector<UnresolvedResonanceCovarianceDataContainer> >    CovarianceResonanceDataContainer::get_unreso_obj()
{
  return unreso_obj;
}


CompatibleResolvedResonanceDataContainer      CovarianceResonanceDataContainer::get_compatible_obj(int i, int j)
{
  string func_name = "get_compatible_obj";

  int    i_max    = static_cast<int>(compatible_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(compatible_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return compatible_obj[i][j];
}

BreitWignerCovarianceDataContainer            CovarianceResonanceDataContainer::get_bw_obj(int i, int j)
{
  string func_name = "get_bw_obj";

  int    i_max    = static_cast<int>(bw_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(bw_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return bw_obj[i][j];
}

ReichMooreCovarianceDataContainer             CovarianceResonanceDataContainer::get_rm_obj(int i, int j)
{
  string func_name = "get_rm_obj";

  int    i_max    = static_cast<int>(rm_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(rm_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return rm_obj[i][j];
}

AdlerAdlerCovarianceDataContainer             CovarianceResonanceDataContainer::get_adler_obj(int i, int j)
{
  string func_name = "get_adler_obj";

  int    i_max    = static_cast<int>(adler_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(adler_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return adler_obj[i][j];
}

RMatrixLimitedCovarianceDataContainer         CovarianceResonanceDataContainer::get_r_matrix_obj(int i, int j)
{
  string func_name = "get_r_matrix_obj";

  int    i_max    = static_cast<int>(r_matrix_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(r_matrix_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return r_matrix_obj[i][j];
}

BreitWignerCompactCovarianceDataContainer     CovarianceResonanceDataContainer::get_bw_compact_obj(int i, int j)
{
  string func_name = "get_bw_compact_obj";

  int    i_max    = static_cast<int>(bw_compact_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(bw_compact_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return bw_compact_obj[i][j];
}

ReichMooreCompactCovarianceDataContainer      CovarianceResonanceDataContainer::get_rm_compact_obj(int i, int j)
{
  string func_name = "get_rm_compact_obj";

  int    i_max    = static_cast<int>(rm_compact_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(rm_compact_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return rm_compact_obj[i][j];
}

RMatrixLimitedCompactCovarianceDataContainer  CovarianceResonanceDataContainer::get_r_matrix_compact_obj(int i, int j)
{
  string func_name = "get_r_matrix_compact_obj";

  int    i_max    = static_cast<int>(r_matrix_compact_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(r_matrix_compact_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return r_matrix_compact_obj[i][j];
}

UnresolvedResonanceCovarianceDataContainer    CovarianceResonanceDataContainer::get_unreso_obj(int i, int j)
{
  string func_name = "get_unreso_obj";

  int    i_max    = static_cast<int>(unreso_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(unreso_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  return unreso_obj[i][j];
}



////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void CovarianceResonanceDataContainer::set_mat_data_isotope( vector<Real> real_vec )
{
  mat_data_isotope = real_vec;
  real_vec.clear();
}

void CovarianceResonanceDataContainer::set_abundance_isotope( vector<Real> real_vec )
{
  abundance_isotope = real_vec;
  real_vec.clear();
}

void CovarianceResonanceDataContainer::set_fis_width_flg( vector<Integer> int_vec )
{
  fis_width_flg = int_vec;
  int_vec.clear();
}

void CovarianceResonanceDataContainer::set_lower_ene_limit( vector<vector<Real> > real_vec )
{
  lower_ene_limit = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CovarianceResonanceDataContainer::set_upper_ene_limit( vector<vector<Real> > real_vec )
{
  upper_ene_limit = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CovarianceResonanceDataContainer::set_reso_region_flg( vector<vector<Integer> > int_vec )
{
  reso_region_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void CovarianceResonanceDataContainer::set_xs_formula_flg( vector<vector<Integer> > int_vec )
{
  xs_formula_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void CovarianceResonanceDataContainer::set_scat_radius_ene_dependence_flg( vector<vector<Integer> > int_vec )
{
  scat_radius_ene_dependence_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void CovarianceResonanceDataContainer::set_radius_calc_flg( vector<vector<Integer> > int_vec )
{
  radius_calc_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void CovarianceResonanceDataContainer::set_spin_data( vector<vector<Real> > real_vec )
{
  spin_data = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CovarianceResonanceDataContainer::set_scat_radius( vector<vector<Real> > real_vec )
{
  scat_radius = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CovarianceResonanceDataContainer::set_angular_distr_calc_flg( vector<vector<Integer> > int_vec )
{
  angular_distr_calc_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void CovarianceResonanceDataContainer::set_compatibility_flg( vector<vector<Integer> > int_vec )
{
  compatibility_flg = int_vec;
  clr_obj.clear_vec_array2_int( int_vec );
}

void CovarianceResonanceDataContainer::set_cov_matrix_data_flg( vector<vector<vector<Integer> > > int_vec )
{
  cov_matrix_data_flg = int_vec;
  clr_obj.clear_vec_array3_int( int_vec );
}

void CovarianceResonanceDataContainer::set_cov_matrix_ene_k( vector<vector<vector<vector<Real> > > > real_vec )
{
  cov_matrix_ene_k = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void CovarianceResonanceDataContainer::set_cov_matrix_coef_k( vector<vector<vector<vector<vector<Real> > > > > real_vec )
{
  cov_matrix_coef_k = real_vec;
  clr_obj.clear_vec_array5_real( real_vec );
}

void CovarianceResonanceDataContainer::set_cov_matrix_ene_l( vector<vector<vector<vector<Real> > > > real_vec )
{
  cov_matrix_ene_l = real_vec;
  clr_obj.clear_vec_array4_real( real_vec );
}

void CovarianceResonanceDataContainer::set_cov_matrix_coef_l( vector<vector<vector<vector<vector<Real> > > > > real_vec )
{
  cov_matrix_coef_l = real_vec;
  clr_obj.clear_vec_array5_real( real_vec );
}

void CovarianceResonanceDataContainer::set_mass_isotope( vector<vector<Real> > real_vec )
{
  mass_isotope = real_vec;
  clr_obj.clear_vec_array2_real( real_vec );
}

void CovarianceResonanceDataContainer::set_compatible_obj( vector<vector<CompatibleResolvedResonanceDataContainer> > obj_data )
{
  clear_compatible_obj(compatible_obj);

  compatible_obj = obj_data;

  clear_compatible_obj(obj_data);
}

void CovarianceResonanceDataContainer::set_bw_obj( vector<vector<BreitWignerCovarianceDataContainer> > obj_data )
{
  clear_bw_obj(bw_obj);

  bw_obj = obj_data;

  clear_bw_obj(obj_data);
}

void CovarianceResonanceDataContainer::set_rm_obj( vector<vector<ReichMooreCovarianceDataContainer> > obj_data )
{
  clear_rm_obj(rm_obj);

  rm_obj = obj_data;

  clear_rm_obj(obj_data);
}

void CovarianceResonanceDataContainer::set_adler_obj( vector<vector<AdlerAdlerCovarianceDataContainer> > obj_data )
{
  clear_adler_obj(adler_obj);

  adler_obj = obj_data;

  clear_adler_obj(obj_data);
}

void CovarianceResonanceDataContainer::set_r_matrix_obj( vector<vector<RMatrixLimitedCovarianceDataContainer> > obj_data )
{
  clear_r_matrix_obj(r_matrix_obj);

  r_matrix_obj = obj_data;

  clear_r_matrix_obj(obj_data);
}

void CovarianceResonanceDataContainer::set_bw_compact_obj( vector<vector<BreitWignerCompactCovarianceDataContainer> > obj_data )
{
  clear_bw_compact_obj(bw_compact_obj);

  bw_compact_obj = obj_data;

  clear_bw_compact_obj(obj_data);
}

void CovarianceResonanceDataContainer::set_rm_compact_obj( vector<vector<ReichMooreCompactCovarianceDataContainer> > obj_data )
{
  clear_rm_compact_obj(rm_compact_obj);

  rm_compact_obj = obj_data;

  clear_rm_compact_obj(obj_data);
}

void CovarianceResonanceDataContainer::set_r_matrix_compact_obj( vector<vector<RMatrixLimitedCompactCovarianceDataContainer> > obj_data )
{
  clear_r_matrix_compact_obj(r_matrix_compact_obj);

  r_matrix_compact_obj = obj_data;

  clear_r_matrix_compact_obj(obj_data);
}

void CovarianceResonanceDataContainer::set_unreso_obj( vector<vector<UnresolvedResonanceCovarianceDataContainer> > obj_data )
{
  clear_unreso_obj(unreso_obj);

  unreso_obj = obj_data;

  clear_unreso_obj(obj_data);
}


void CovarianceResonanceDataContainer::set_compatible_obj( int i, int j, CompatibleResolvedResonanceDataContainer obj_data )
{
  string func_name = "set_compatible_obj";

  int    i_max    = static_cast<int>(compatible_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(compatible_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  compatible_obj[i][j] = obj_data;
  obj_data.clear();
}

void CovarianceResonanceDataContainer::set_bw_obj( int i, int j, BreitWignerCovarianceDataContainer obj_data )
{
  string func_name = "set_bw_obj";

  int    i_max    = static_cast<int>(bw_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(bw_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  bw_obj[i][j] = obj_data;
  obj_data.clear();
}

void CovarianceResonanceDataContainer::set_rm_obj( int i, int j, ReichMooreCovarianceDataContainer obj_data )
{
  string func_name = "set_rm_obj";

  int    i_max    = static_cast<int>(rm_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(rm_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  rm_obj[i][j] = obj_data;
  obj_data.clear();
}

void CovarianceResonanceDataContainer::set_adler_obj( int i, int j, AdlerAdlerCovarianceDataContainer obj_data )
{
  string func_name = "set_adler_obj";

  int    i_max    = static_cast<int>(adler_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(adler_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  adler_obj[i][j] = obj_data;
  obj_data.clear();
}

void CovarianceResonanceDataContainer::set_r_matrix_obj( int i, int j, RMatrixLimitedCovarianceDataContainer obj_data )
{
  string func_name = "set_r_matrix_obj";

  int    i_max    = static_cast<int>(r_matrix_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(r_matrix_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  r_matrix_obj[i][j] = obj_data;
  obj_data.clear();
}

void CovarianceResonanceDataContainer::set_bw_compact_obj( int i, int j, BreitWignerCompactCovarianceDataContainer obj_data )
{
  string func_name = "set_bw_compact_obj";

  int    i_max    = static_cast<int>(bw_compact_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(bw_compact_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  bw_compact_obj[i][j] = obj_data;
  obj_data.clear();
}

void CovarianceResonanceDataContainer::set_rm_compact_obj( int i, int j, ReichMooreCompactCovarianceDataContainer obj_data )
{
  string func_name = "set_rm_compact_obj";

  int    i_max    = static_cast<int>(rm_compact_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(rm_compact_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  rm_compact_obj[i][j] = obj_data;
  obj_data.clear();
}

void CovarianceResonanceDataContainer::set_r_matrix_compact_obj( int i, int j, RMatrixLimitedCompactCovarianceDataContainer obj_data )
{
  string func_name = "set_r_matrix_compact_obj";

  int    i_max    = static_cast<int>(r_matrix_compact_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(r_matrix_compact_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  r_matrix_compact_obj[i][j] = obj_data;
  obj_data.clear();
}

void CovarianceResonanceDataContainer::set_unreso_obj( int i, int j, UnresolvedResonanceCovarianceDataContainer obj_data )
{
  string func_name = "set_unreso_obj";

  int    i_max    = static_cast<int>(unreso_obj.size());
  string ele_name = "i_max";
  check_data_size(i, j, i, i_max, func_name, ele_name);

  int    j_max    = static_cast<int>(unreso_obj[i].size());
         ele_name = "j_max";
  check_data_size(i, j, j, j_max, func_name, ele_name);

  unreso_obj[i][j] = obj_data;
  obj_data.clear();
}

