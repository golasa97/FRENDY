#include "ReconResonance/RmatrixLimited/run/RmatrixLimitedCalculator.hpp"
#include "ReconResonance/RmatrixLimited/endf/Construct.h"
#include "ReconResonance/RmatrixLimited/endf/Functions.h"
#include "ReconResonance/RmatrixLimited/endf/Interp1.h"
#include "ReconResonance/RmatrixLimited/numeric/Constant.h"
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"
#include "ReconResonance/RmatrixLimited/basics/MultiThread.h"
#include <cstdlib>

using namespace frendy;
using namespace Basics;

#define m_neutron ( Constant::mass(1) * Constant::amu )

#define zero_cs 1.e-24  // minimum value of cross-section
#define eps_e   1.e-10  // relative accuracy of threshold energy

RmatrixLimitedCalculator::Solver:: Solver() : n(0) {}
RmatrixLimitedCalculator::Solver::~Solver(){}

//////////////////////////////////////////////////////////////////////////////////////////////////////

const RML::TwoBody& RmatrixLimitedCalculator::Solver::Partition( const int i ) const { return partitions[i]; }
      RML::TwoBody& RmatrixLimitedCalculator::Solver::Partition( const int i )       { return partitions[i]; }
const double&  RmatrixLimitedCalculator::Solver::Qvalue   ( const int i ) const { return qvalues   [i]; }
      double&  RmatrixLimitedCalculator::Solver::Qvalue   ( const int i )       { return qvalues   [i]; }
const double&  RmatrixLimitedCalculator::Solver::Ethre    ( const int i ) const { return eths      [i]; }
      double&  RmatrixLimitedCalculator::Solver::Ethre    ( const int i )       { return eths      [i]; }

//////////////////////////////////////////////////////////////////////////////////////////////////////

/***************************/
/*! @brief Clear container
****************************/
void RmatrixLimitedCalculator::Solver::Clear()
{
  this->RML::System::Clear();  partitions.clear();  qvalues.clear();  n = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************/
/*! @brief Set total spin and parity
    @param[in] J  : total spin
    @param[in] pi : parity
***********************************************************/
void RmatrixLimitedCalculator::Solver::PushBack( const double J, const int pi )
{
  this->System::PushBack( J, pi );  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************/
/*! @brief Set partitions
    @param[in] partition : pair of particle + nucleus
***********************************************************/
void RmatrixLimitedCalculator::Solver::PushBack( const RML::TwoBody& partition )
{
  this->System::PushBack( partition );  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

/****************************************************************************/
/*! @brief Set partitions, Q-values and threshold energy for the reactions
    @param[in] partition : pair of particle + nucleus
    @param[in] qvalue    : reaction Q-value
    @param[in] eth       : threshold energy of reaction
*****************************************************************************/
void RmatrixLimitedCalculator::Solver::PushBack( const RML::TwoBody& partition,
                                                 const double& qvalue, const double& eth )
{
  partitions.push_back( partition );
  qvalues   .push_back( qvalue   );
  eths      .push_back( eth      );

  n++;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

/***************************************************************/
/*! @brief Calculate cross-sections
    @param[in]  elab   : incident neutron energy [eV]
    @param[out] result : cross-sections for total, capture, ...
****************************************************************/
void RmatrixLimitedCalculator::Solver::Run( const double elab, double* result )
{
  // result[0] : total cross-section
  // result[1] : capture cross-section
  // result[*] : the other reactions cross-sections

  this->Solve( qvalues, partitions[0].Ecm(elab) );

  // reaction cross-sections (except for capture)

  for( int i=2; i<n+2; i++ )
  {
  //result[i] = max( this->sigma( partitions[0], elab, partitions[i-2] ), zero );
  //result[i] = eq( elab, eths[i-2], 1.e-10 ) ? 0.0 : this->sigma( partitions[0], elab, partitions[i-2] );

    result[i] = eq( elab, eths[i-2], eps_e ) ? 0.0 : max( this->sigma( partitions[0], elab, partitions[i-2] ), zero_cs );
  }

  // total cross-sections

    result[0] = this->sigma( partitions[0], elab );

  // capture cross-sections with Reich-Moore approximation

    result[1] = result[0];

    for( int i=2; i<n+2; i++ ) result[1] -= result[i];

  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void RmatrixLimitedCalculator::Solver::Run( ENDF::LIST* result )
{
  //double a[n+2];
  double *a;
  a = new double[n+2];

  this->Run( result->C2(), a );

  for( int i=0; i<n+2; i++ ) result->B(i) = a[i];

  delete[] a;

  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Legendre polynomial coefficients for the angular distribution
static void run( RmatrixLimitedCalculator::Solver* o, const RML::TwoBody& inc, const double& elab,
                 const RML::TwoBody& out, vector<double>* result )
{
  if( o->sigma( inc, elab, out ) <= 0.0 ) return;

  double B0;  int L = 0;

  B0 = o->B( inc,out, 0 );

  do
  {
    L++;

    result->push_back( o->B(inc,out,L)/B0/(2.*L+1.) );

  } while ( fabs( result->back() ) > 1.e-16 );

  result->pop_back();

  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

/***********************************************************************************/
/*! @brief Calculate Legendre polynomial coefficients for the angular distribution
    @param[in]  elab   : incident neutron energy [eV]
    @param[out] result : array of the Legendre polynomial coefficients
************************************************************************************/
void RmatrixLimitedCalculator::Solver::Run( const double elab, vector<double>* result )
{
  this->SetOption(true);  // calculate A-matrix

  this->Solve( qvalues, partitions[0].Ecm(elab) );

  // reaction cross-sections (except for capture)

  for( int i=2; i<n+2; i++ ) run( this, partitions[0], elab, partitions[i-2], &result[i-2] );

  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Legendre polynomial coefficients for the angular distribution
static void run( RmatrixLimitedCalculator::Solver* o,
                 const RML::TwoBody& inc, const RML::TwoBody& out, ENDF::LTT1::Record* result )
{
  if( o->sigma( inc, result->E(), out ) <= 0.0 ) return;

  double B0;  int L = 0;

  B0 = o->B( inc,out, 0 );

  do
  {
    L++;

    result->PushBack( o->B(inc,out,L)/B0/(2.*L+1.) );

  } while ( fabs( result->Back() ) > 1.e-16 );

  result->PopBack();

  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// Legendre polynomial coefficients for the angular distribution
void RmatrixLimitedCalculator::Solver::Run( const double elab, vector<ENDF::LTT1::Record>* result )
{

  this->SetOption(true);  // calculate A-matrix

  this->Solve( qvalues, partitions[0].Ecm(elab) );

  // reaction cross-sections (except for capture)

  for( int i=2; i<n+2; i++ ) run( this, partitions[0], partitions[i-2], result->at(i-2).E(elab) );

  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

/* ------------------
      class RmatrixLimitedCalculator
--------------------- */

RmatrixLimitedCalculator:: RmatrixLimitedCalculator()
{
}

RmatrixLimitedCalculator::~RmatrixLimitedCalculator()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void RmatrixLimitedCalculator::clear()
{
  reso_data_obj.clear();
  r_matrix_data_obj.clear();

  iso_ene_set_flg = 0;

  iso_no      = 0;
  reso_ene_no = 0;
  react_no    = 0;

  react_type_list.clear();

  q_vec.clear();
  eth_vec.clear();

  sol_obj.Clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void RmatrixLimitedCalculator::calc_resonance_xs( Real8 elab, vector<Real8>& result,
                                                  vector<Integer>& react_type_vec )
{
  calc_resonance_xs(elab, result);

  react_type_vec = react_type_list;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void RmatrixLimitedCalculator::calc_resonance_xs( Real8 elab, vector<Real8>& result )
{
  // result[0] : total cross-section
  // result[1] : capture cross-section
  // result[*] : the other reactions cross-sections

  result.clear();
  result.resize(react_no+2);

  //double result_array[react_no+2];
  double *result_array;
  result_array = new double[react_no+2];

  sol_obj.Run(elab, result_array);

  for( int i=0; i<react_no+2; i++ )
  {
    result[i] = result_array[i];
  }

  delete[] result_array;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void RmatrixLimitedCalculator::set_resonance_data(int nis, int ner)
{
  iso_ene_set_flg = 1;

  iso_no      = nis;
  reso_ene_no = ner;

  set_resonance_data( reso_data_obj.get_r_matrix_data_obj(iso_no, reso_ene_no) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void RmatrixLimitedCalculator::set_resonance_data( RMatrixLimitedDataContainer data_obj )
{
  sol_obj.Clear();

  // Configure RML system
  if( iso_ene_set_flg == 0 )
  {
    iso_no      = 0;
    reso_ene_no = 0;
  }

  r_matrix_data_obj = data_obj;
  data_obj.clear();

  check_reso_data();

  // particle+nucleus pairs
  set_particle_pair_data();

  // set parameters for each J^pi
  set_spin_data();

  int i_max = static_cast<int>(r_matrix_data_obj.get_mass_a().size());
  for(int i=1; i<i_max; i++)
  {
    sol_obj.PushBack( sol_obj.Partition(i-1) );
  }

  sol_obj.Configure( false ); // false : use X-matrix,  true : use A-matrix

  // temporary if the threshold reaction exist
  set_threshold_data();

  //sol_obj.Print();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void RmatrixLimitedCalculator::check_reso_data()
{
  string class_name = "RmatrixLimitedCalculator";
  string func_name  = "check_reso_data()";

  if( r_matrix_data_obj.get_r_matrix_calc_flg() != 3 )
  {
    ostringstream oss01, oss02, oss03;
    oss01 << iso_no;
    oss02 << reso_ene_no;
    oss03 << r_matrix_data_obj.get_r_matrix_calc_flg();
    string str_data01 = "Isotope number (NIS)      : " + oss01.str();
    string str_data02 = "Energy range number (NER) : " + oss02.str();
    string str_data03 = "Calculation flag (KRM)    : " + oss03.str();

    vector<string> err_com;
    if( iso_ene_set_flg != 0 )
    {
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
    }
    err_com.push_back(str_data03);
    err_com.push_back("This calculation flag (KRM) can not be calculated.");
    err_com.push_back("Available calculation flag is 3 (Reich Moore).");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( r_matrix_data_obj.get_relativistic_flg() != 0 )
  {
    ostringstream oss01, oss02, oss03;
    oss01 << iso_no;
    oss02 << reso_ene_no;
    oss03 << r_matrix_data_obj.get_relativistic_flg();
    string str_data01 = "Isotope number (NIS)      : " + oss01.str();
    string str_data02 = "Energy range number (NER) : " + oss02.str();
    string str_data03 = "Kinematics flag (KRL)     : " + oss03.str();

    vector<string> err_com;
    if( iso_ene_set_flg != 0 )
    {
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
    }
    err_com.push_back(str_data03);
    err_com.push_back("This relativistic kinematics flag (KRL) can not be calculated.");
    err_com.push_back("Available relativistic kinematics flag is 0 (Non-relativistic).");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = static_cast<int>(r_matrix_data_obj.get_back_ground_r_matrix_flg().size());
  for(int i=0; i<i_max; i++)
  {
    if( r_matrix_data_obj.get_back_ground_r_matrix_flg()[i] > 0 )
    {
      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << iso_no;
      oss02 << reso_ene_no;
      oss03 << i+1;
      oss04 << i_max;
      oss05 << r_matrix_data_obj.get_back_ground_r_matrix_flg()[i];
      string str_data01 = "Isotope number (NIS)           : " + oss01.str();
      string str_data02 = "Energy range number (NER)      : " + oss02.str();
      string str_data03 = "Position                       : " + oss03.str() + " / " + oss04.str();
      string str_data04 = "Background R-matrix flag (KBK) : " + oss03.str();

      vector<string> err_com;
      if( iso_ene_set_flg != 0 )
      {
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
      }
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("The background R-matrix flag (KBK) is only available for KBK=0.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  i_max = static_cast<int>(r_matrix_data_obj.get_non_hard_sphere_flg().size());
  for(int i=0; i<i_max; i++)
  {
    if( r_matrix_data_obj.get_non_hard_sphere_flg()[i] > 0 )
    {
      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << iso_no;
      oss02 << reso_ene_no;
      oss03 << i+1;
      oss04 << i_max;
      oss05 << r_matrix_data_obj.get_non_hard_sphere_flg()[i];
      string str_data01 = "Isotope number (NIS)                   : " + oss01.str();
      string str_data02 = "Energy range number (NER)              : " + oss02.str();
      string str_data03 = "Position                               : " + oss03.str() + " / " + oss04.str();
      string str_data04 = "Non-hard-sphere phase shift flag (KPS) : " + oss03.str();

      vector<string> err_com;
      if( iso_ene_set_flg != 0 )
      {
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
      }
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("The non-hard-sphere phase shift flag (KPS) is only available for KPS=0.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  int gam_width_flg = static_cast<int>(round(r_matrix_data_obj.get_gam_width_flg()));
  if( gam_width_flg != 0 && gam_width_flg != 1 )
  {
    ostringstream oss01, oss02, oss03, oss04, oss05;
    oss01 << iso_no;
    oss02 << reso_ene_no;
    oss03 << gam_width_flg;
    string str_data01 = "Isotope number (NIS)      : " + oss01.str();
    string str_data02 = "Energy range number (NER) : " + oss02.str();
    string str_data03 = "Gamma width flag (IFG)    : " + oss03.str();

    vector<string> err_com;
    if( iso_ene_set_flg != 0 )
    {
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
    }
    err_com.push_back(str_data03);
    err_com.push_back("This gamma width flag (IFG) can not be calculated.");
    err_com.push_back("Available relativistic gamma width flag :");
    err_com.push_back("  IFG = 0 : Gamma width (GAM) is the channel width in eV");
    err_com.push_back("  IFG = 1 : Gamma width (GAM) is the reduced-width amplitude in eV^0.5");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void RmatrixLimitedCalculator::set_particle_pair_data()
{
/*! @brief Configure RML system */
//void LRF7::Configure( Solver* o ) const

  sol_obj.Clear();

  react_type_list.clear();

  react_type_list.push_back(  1);  //Total
  react_type_list.push_back(102);  //Radiation

  // particle+nucleus pairs
  int i_max = static_cast<int>(r_matrix_data_obj.get_mass_a().size());
  for(int i=1; i<i_max; i++)
  {
    double MA0 = r_matrix_data_obj.get_mass_a()[1];
    double MB0 = r_matrix_data_obj.get_mass_b()[1];

    double MA  = r_matrix_data_obj.get_mass_a()[i];
    double MB  = r_matrix_data_obj.get_mass_b()[i];
    double ZA  = r_matrix_data_obj.get_charge_a()[i];
    double ZB  = r_matrix_data_obj.get_charge_b()[i];
    double IA  = r_matrix_data_obj.get_spin_a()[i];
    double IB  = r_matrix_data_obj.get_spin_b()[i];
    double Q   = r_matrix_data_obj.get_q_value()[i];
    double PNT = r_matrix_data_obj.get_penetrability_calc_flg()[i];
    double SHF = r_matrix_data_obj.get_shift_factor_calc_flg()[i];
    double MT  = r_matrix_data_obj.get_reaction_type_flg()[i];
    double PA  = r_matrix_data_obj.get_parity_a()[i];
    double PB  = r_matrix_data_obj.get_parity_b()[i];
    
    RML::TwoBody a;

    a.Particle::Set( 1000.0*ZA+MA, fabs(IA), ( eq(IA,0.0) ? PA : sign(IA) ), MA*Constant::mass(1) );
    a.Nucleus:: Set( 1000.0*ZB+MB, fabs(IB), ( eq(IB,0.0) ? PB : sign(IB) ), MB*Constant::mass(1) );

    //if( this->Q(i) < 0.0 ) a.Nucleus::Energy( -1.* this->Q(i) );

    //cerr << "Q = " << this->Q(i) << endl;

    // !!! to be checked in future !!!

    if( int( round(PNT) ) ==  0 && int( round(MT) ) ==  19 ) sol_obj.Boundary::PenetOff( a );
    if( int( round(PNT) ) ==  0 && int( round(MT) ) == 102 ) sol_obj.Boundary::PenetOff( a );
    if( int( round(PNT) ) == -1                            ) sol_obj.Boundary::PenetOff( a );
    if( int( round(SHF) ) <=  0                            ) sol_obj.Boundary::ShiftOff( a );

    double eth = ( Q < 0. ) ? -1. * Q * (MA0+MB0)/MB0 : 0.0;

    //sol_obj.PushBack( a, Q );
    sol_obj.PushBack( a, Q, eth );

  
    q_vec.push_back(Q);
    eth_vec.push_back(eth);

    react_type_list.push_back( static_cast<int>(round(MT)) );
  }
  react_no = static_cast<int>(q_vec.size());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void RmatrixLimitedCalculator::set_spin_data()
{
/*! @brief Configuration of the RML system */
//void LRF7::Record::Configure( Solver* o, const int IFG ) const

  // set parameters for each J^pi
 
  int i_max  = static_cast<int>(r_matrix_data_obj.get_j_value_abs().size());
  for(int i=0; i<i_max; i++)
  {
    // Configure RML system
    double AJ = r_matrix_data_obj.get_j_value_abs()[i];
    double PJ = r_matrix_data_obj.get_parity()[i];

    // set effective channel radius, true channel radius and boundary condition number
    // radius * 10 : cm^{-12} -> fm
    int j_max = static_cast<int>(r_matrix_data_obj.get_scat_radius_eff()[i].size());
    for(int j=1; j<j_max; j++)
    {
      double ppi = r_matrix_data_obj.get_particle_pair_no()[i][j];
      RML::TwoBody part = sol_obj.Partition(ppi - 2.0);

      int   l_val = static_cast<int>(round(r_matrix_data_obj.get_l_value()[i][j]));
      Real8 sch   = fabs(r_matrix_data_obj.get_spin_channel()[i][j]);
      RML::Channel ch( part, fabs(AJ), l_val, sch );

      Real8 ape = r_matrix_data_obj.get_scat_radius_eff()[i][j]  * 10.0;
      Real8 apt = r_matrix_data_obj.get_scat_radius_true()[i][j] * 10.0;
      Real8 bnd = r_matrix_data_obj.get_boundary_condition()[i][j];

      //sol_obj.Boundary::Rh( ch, ape );
      //sol_obj.Boundary::Rc( ch, apt );
      //sol_obj.Boundary::Bc( ch, bnd );
      sol_obj.Rh( ch, ape );
      sol_obj.Rc( ch, apt );
      sol_obj.Bc( ch, bnd );
    }

    // set energy eigenvalue and channel width or reduced-width amplitude
    int pi = eq(AJ,0.0) ? PJ : sign( AJ );

    if( pi==0 ) pi = -1;  // this is consistent with NJOY, PREPRO

  // set energy eigenvalue and channel width or reduced-width amplitude

    sol_obj.PushBack(fabs(AJ), pi);

    // set energy eigenvalue and channel width or reduced-width amplitude
    set_gam_width_data(i, fabs(AJ), pi);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void RmatrixLimitedCalculator::set_gam_width_data( int i, Real8 aj, int pi )
{
  int gam_width_flg = static_cast<int>(r_matrix_data_obj.get_gam_width_flg());

  if( gam_width_flg == 0 )
  {
    set_gam_width_data_channel(i, aj, pi);
  }
  else if( gam_width_flg == 1 )
  {
    set_gam_width_data_reduced(i, aj, pi);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// GAM is the channel width in eV
void RmatrixLimitedCalculator::set_gam_width_data_channel( int i, Real8 aj, int pi )
{
//static void configure_IFG0( LRF7::Solver* o, const double J, const int pi, const LRF7::Record* r )
  RML::Structure* a = sol_obj.Find(aj, pi);

  // mass for particles and nuclei
  vector<Real8> m1, m2;

  int j_max = static_cast<int>( sol_obj.size() );
  m1.resize(j_max);
  m2.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    m1[j] = sol_obj.Partition(j).Particle::Mass();
    m2[j] = sol_obj.Partition(j).Nucleus::Mass();
  }

  // set energy eigenvalue and reduced-width amplitude
  vector<Real8>          ene_reso  = r_matrix_data_obj.get_ene_reso()[i];
  vector<vector<Real8> > gam_width = r_matrix_data_obj.get_gam_width()[i];

  int nrs = static_cast<int>(ene_reso.size());
  for(int j=0; j<nrs; j++)
  {
    // set energy eigenvalue measured from the neutron binding energy, gamma-width
    double ecm = ene_reso[j] * m2[0]/(m1[0]+m2[0]);

    RML::Level* lev = a->E( ecm )->Gamma( gam_width[j][0] * m2[0]/(m1[0]+m2[0]) );

    // do without gamma-ray channels
    int nch = static_cast<int>(gam_width[j].size());
    for(int k=1; k<nch; k++)
    {
      double ppi = r_matrix_data_obj.get_particle_pair_no()[i][k];
      RML::TwoBody part = sol_obj.Partition(ppi-2.0);

      double l_val =      r_matrix_data_obj.get_l_value()[i][k];
      double sch   = fabs(r_matrix_data_obj.get_spin_channel()[i][k]);
      RML::Coulomb ch( part, fabs(aj), l_val, sch );

      double e = ecm + sol_obj.Qvalue(ppi-2.0);
      ch.Update( fabs(e), &sol_obj ); // <= abs is not necessary ?

      double G     = gam_width[j][k] * m2[0]/(m1[0]+m2[0]);
      double gamma = sign( G ) * sqrt( fabs( G/( 2.0*ch.P() ) ) );  // reduced-width amplitude

      lev->gamma( ch, gamma );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

// GAM is the reduced-width amplitude in eV^(1/2)
void RmatrixLimitedCalculator::set_gam_width_data_reduced( int i, Real8 aj, int pi )
{
//static void configure_IFG1( LRF7::Solver* o, const double J, const int pi, const LRF7::Record* r )
  string class_name = "RmatrixLimitedCalculator";
  string func_name  = "set_gam_width_data_reduced(int i, Real8 aj, int pi)";

  ostringstream oss01, oss02;
  oss01 << iso_no;
  oss02 << reso_ene_no;
  string str_data01 = "Isotope number (NIS)      : " + oss01.str();
  string str_data02 = "Energy range number (NER) : " + oss02.str();

  vector<string> err_com;
  if( iso_ene_set_flg != 0 )
  {
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
  }
  err_com.push_back("Gamma width flag (IFG) = 1 (the reduced-width amplitude in eV^0.5");
  err_com.push_back("has not been completed.");
  err_com.push_back("The current version of FRENDY can not treat this option.");
  err_com.push_back("Available relativistic gamma width flag :");
  err_com.push_back("  IFG = 0 : Gamma width (GAM) is the channel width in eV");

  err_obj.output_runtime_error(class_name, func_name, err_com);



  RML::Structure* a = sol_obj.Find(aj, pi);

  vector<Real8>          ene_reso  = r_matrix_data_obj.get_ene_reso()[i];
  vector<vector<Real8> > gam_width = r_matrix_data_obj.get_gam_width()[i];

  int nrs = static_cast<int>(ene_reso.size());

  for(int j=0; j<nrs; j++)
  {
    int nch = static_cast<int>(gam_width[j].size());
    if( nch == 0 )
    {
      continue;
    }

    RML::Level* lev = a->E( ene_reso[j] )->Gamma( gam_width[j][0] );

    for(int k=1; k<nch; k++)
    {
      double       ppi      = r_matrix_data_obj.get_particle_pair_no()[i][k];
      RML::TwoBody part     = sol_obj.Partition(ppi-2.0);
      //double       q_val    = q_vec[ppi-2];
      double       l_val    = r_matrix_data_obj.get_l_value()[i][k];
      double       sch      = fabs(r_matrix_data_obj.get_spin_channel()[i][k]);

      lev->gamma( RML::Channel(part, fabs(aj), l_val, sch), gam_width[j][k] );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void RmatrixLimitedCalculator::set_threshold_data()
{
  // temporary if the threshold reaction exist
  int i_max = static_cast<int>(r_matrix_data_obj.get_mass_a().size());
  for(int i=1; i<i_max; i++)
  {
    if( r_matrix_data_obj.get_q_value()[i] < 0.0 )
    {
      sol_obj.SetOption( true );
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

//Copy from Functions.h
/*double RmatrixLimitedCalculator::sign( double x )
{

  if( eq(x,0.0) )
  {
    return 1.0;
  }
  else
  {
     return x/fabs(x);
  }
}*/

//////////////////////////////////////////////////////////////////////////////////////////////////////

void RmatrixLimitedCalculator::set_reso_data_obj(ResonanceDataContainer data_obj)
{
  clear();

  reso_data_obj = data_obj;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

ResonanceDataContainer RmatrixLimitedCalculator::get_reso_data_obj()
{
  return reso_data_obj;
}

RMatrixLimitedDataContainer RmatrixLimitedCalculator::get_r_matrix_data_obj()
{
  return r_matrix_data_obj;
}

vector<int> RmatrixLimitedCalculator::get_react_type_list()
{
  return react_type_list;
}

vector<Real8> RmatrixLimitedCalculator::get_q_val()
{
  int i_max = static_cast<int>(q_vec.size());

  vector<Real8> q_vec_mod;
  q_vec_mod.resize(i_max+2);

  q_vec_mod[0] = 0.0;  //Total
  q_vec_mod[1] = 0.0;  //Radiation

  for(int i=0; i<i_max; i++)
  {
    q_vec_mod[i+2] = q_vec[i];
  }

  return q_vec_mod;
}

vector<Real8> RmatrixLimitedCalculator::get_eth_val()
{
  int i_max = static_cast<int>(eth_vec.size());

  vector<Real8> eth_vec_mod;
  eth_vec_mod.resize(i_max+2);

  eth_vec_mod[0] = 0.0;  //Total
  eth_vec_mod[1] = 0.0;  //Radiation

  for(int i=0; i<i_max; i++)
  {
    eth_vec_mod[i+2] = eth_vec[i];
  }

  return eth_vec_mod;
}

