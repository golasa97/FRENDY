#include "ReconResonance/RmatrixLimited/rml/System.h"
#include "ReconResonance/RmatrixLimited/numeric/Constant.h"
#include "ReconResonance/RmatrixLimited/numeric/Coupling.h"
#include "ReconResonance/RmatrixLimited/numeric/Legendre.h"
//#include <gsl/gsl_errno.h>
//#include <gsl/gsl_sf_legendre.h>
//#include <gsl/gsl_sf_coupling.h>

using namespace Numeric;

//ClassImp( RML::System );

#define pm(l) ( (l)%2 == 0 ? 1 : -1 )


namespace RML {


/*! @brief Default constructor */
System:: System() {
	nparts = 0;
	size_free_pm = 0;
}

/*! @brief Constructor with title */
System:: System( const string text ) {
	title = text;
	nparts = 0;
	size_free_pm = 0;
}

/*! @brief Destructor */
System::~System(){}

/*! @brief Set mass of the compound nucleus [amu] */
void System::Mass( const double m ) { mass = m; }

/*! @brief Get mass of the compound nucleus [amu] */
const double& System::Mass() const { return mass; }
      double& System::Mass()       { return mass; }


/*! @brief Add a J^pi group to this system
@param[in] J  : total spin
@param[in] pi : parity (positive/negative)
*/
Structure* System::PushBack( const double J, const int pi ) {

  if( this->Find(J,pi) != NULL ) return this->Find(J,pi);

  ary.resize( ary.size() + 1 );  return ary.back().Set(J,pi);

}


/*! @brief Set partition, then store explicit channels
@param[in] a   : Particle which defines the partition
@param[in] A   : Nucleus which defines the partition
*/
void System::PushBack( const Particle& a, const Nucleus& A ) {

  parts.push_back( TwoBody(a,A) );

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].PushBack( a,A );  return;

}

/*! @brief Set partition, then store explicit channels
@param[in] a   : Particle which defines the partition
@param[in] A   : Nucleus which defines the partition
@param[in] S_a : Separation energy (to remove particle "a" from nucleus "a+A" )
*/
void System::PushBack( const Particle& a, const Nucleus& A, const double S_a ) {

  parts.push_back( TwoBody(a,A) );

  se.push_back( make_pair( TwoBody(a,A), S_a ) );

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].PushBack( a,A, S_a );  return;

}

/*! @brief Set partition, then store explicit channels
@param[in] o   : Partition
*/
void System::PushBack( const TwoBody& o ) {

  parts.push_back( o );

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].PushBack( o );  return;

}

/*! @brief Set partition, then store explicit channels
@param[in] o   : Partition
@param[in] S_a : Separation energy (to remove particle from nucleus "o=particle+nucleus" )
*/
void System::PushBack( const TwoBody& o, const double S_a ) {

  parts.push_back( o );

  se.push_back( make_pair( o, S_a ) );

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].PushBack( o, S_a );  return;

}


System* System::ScaleEnergy( const double fac ) {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].ScaleEnergy( fac );  return this;

}

/*! @brief Set computational option
@param[in] option : Computational option (calculate "level matrix" or "channel matrix")
  @li option = true : Calculate "level matrix (A-matrix)".
                      Cross-sections and angular distribution will be obtained.
  @li option = fase : Calculate "channel matrix (X-matrix)".
                      Computational time is fast, but use only for the calculation of cross-sections.
*/
System* System::SetOption( const bool option ) {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].SetOption( option );  return this;

}

/*! @brief Configure the system with computational option
@param[in] option : Computational option (calculate "level matrix" or "channel matrix")
  @li option = true : Calculate "level matrix (A-matrix)".
                      Cross-sections and angular distribution will be obtained.
  @li option = fase : Calculate "channel matrix (X-matrix)".
                      Computational time is fast, but use only for the calculation of cross-sections.
*/
System* System::Configure( const bool option ) {

  nparts = parts.size();

  for( int i=0; i<static_cast<int>(ary.size()); i++ )

    ary[i].Mass( mass )->Configure( this, option );


  // count number of free parameters

  vector<Parameter*> pm_free;

    this->CollectFreeParams( &pm_free );

      size_free_pm = pm_free.size();

  return this;

}


/*! @brief Get i-th partition */
const TwoBody& System::Partition( const int i ) const { return parts[i]; }
      TwoBody& System::Partition( const int i )       { return parts[i]; }

/*! @brief Number of the partitions */
const int& System::n_partitions() const { return nparts; }
      int& System::n_partitions()       { return nparts; }


/*! @brief Get binding energy (eV)
@param[in] partition : Partition
*/
double System::Ba( const TwoBody& partition ) const {

  const TwoBody* a = &partition;

  for( int i=0; i<static_cast<int>(se.size()); i++ )

    if( se[i].first == *a ) return se[i].second;

  return ( a->Particle::Mass() + a->Nucleus::Mass() -mass ) *Constant::amu + a->Nucleus::Energy();

}


/*! @brief Get reaction Q-value (eV)
@param[in] inc : Partition for the incident channel
@param[in] out : Partition for the exit channel
*/
double System::Qval( const TwoBody& inc, const TwoBody& out ) const {

  //cerr << this->Ba(inc) << "  " << this->Ba(out) << endl;

  return this->Ba(inc) - this->Ba(out);

}

/*! @brief The level matrix is calculated for all the J^pi
@param[in] inc  : Partition for the incident channel
@param[in] elab : Energy of the incident particle in the laboratory system (eV)
*/
System* System::Solve( const TwoBody& inc, const double elab ) {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].Solve( inc, inc.Ecm( elab ), this->Ba(inc) );

  return this;

}

/*! @brief The level matrix is calculated for given J^pi (rarely used)
@param[in] J    : Total spin
@param[in] pi   : Parity
@param[in] inc  : Partition for the incident channel
@param[in] elab : Energy of the incident particle in the laboratory system (eV)
*/
Structure* System::Solve( const double J, const int pi, const TwoBody& inc, const double elab ) {

  for( int i=0; i<static_cast<int>(ary.size()); i++ )

    if( ary[i].J() == J && ary[i].pi() == pi )

      return ary[i].Solve( inc, inc.Ecm( elab ), this->Ba(inc) );

  return NULL;

}

/*! @brief The level matrix is calculated. In this case,
@param[in] qval : Reaction Q-values
@param[in] ecm  : Energy of the incident particle in center-of-mass system (eV)
@note the energy eigenvalue should be measured from binding energy of compound nuclei
(negative energy eigenvalues may be required).
*/
System* System::Solve( const vector<double>& qval, const double ecm ) {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].Solve( qval, ecm, 0.0 );

  return this;

}


/*! @brief Calculate total cross-sections (barn)
@param[in] inc  : Partition for the incident channel
@param[in] elab : Energy of the incident particle in the laboratory system (eV)
*/
double System::sigma( const TwoBody& inc, const double elab ) const {

  double val = 0.0;

    for( int i=0; i<static_cast<int>(ary.size()); i++ ) val += ary[i].sigma( inc, elab );

  return val;

}

/*! @brief Calculate reaction cross-sections (barn)
@param[in] inc  : Partition for the incident channel
@param[in] elab : Energy of the incident particle in the laboratory system (eV)
@param[in] out  : Partition for the exit channel
*/
double System::sigma( const TwoBody& inc, const double elab, const TwoBody& out ) const {
// reaction cross section

  double val = 0.0;

    for( int i=0; i<static_cast<int>(ary.size()); i++ ) {

      val += ary[i].sigma( inc, elab, out );

      //cerr << ary[i].J() << "  " << ary[i].pi() << "  sig = " << ary[i].sigma( inc, elab, out ) << endl;

    }

  return val;

}

/*! @brief Calculate neutron radiative capture cross-sections with Reich-Moore approximation (barn)
@param[in] inc  : Partition for the incident channel
@param[in] elab : Energy of the incident particle in the laboratory system (eV)
*/
double System::sigma_c( const TwoBody& inc, const double elab ) const {

  double val = 0.0;

    for( int i=0; i<static_cast<int>(ary.size()); i++ ) val += ary[i].sigma_c( inc, elab );

  return val;

}

/*! @brief Calculate polarization/analyzing power for the elastic channel
@param[in] inc      : Partition for the incident channel
@param[in] elab     : Energy of the incident particle in the laboratory system (eV)
@param[in] cosangle : Scattering angle in the center-of-mass system
@param[in] Lmax     : maximum order of the Legendre polynomial expansion (see Lane-Thomas,VIII,eq(2.6))
*/
double System::POL( const TwoBody& inc, const double elab, const double cosangle, const int Lmax ) const {

  return this->Az( inc, elab, cosangle, Lmax );

}

/*! @brief Calculate ratio to the Rutherford cross section
@param[in] inc      : Partition for the incident channel
@param[in] elab     : Energy of the incident particle in the laboratory system (eV)
@param[in] cosangle : Scattering angle in the center-of-mass system
@param[in] Lmax     : maximum order of the Legendre polynomial expansion (see Lane-Thomas,VIII,eq(2.6))
*/
double System::RTH( const TwoBody& inc, const double elab, const double cosangle, const int Lmax ) const {

  return this->sigma( inc,elab,inc,cosangle,Lmax)/inc.sigma_c( elab,cosangle );

}



/*! @brief Calculate differential cross section with analytical formula
@param[in] inc      : Partition for the incident channel
@param[in] elab     : Energy of the incident particle in the laboratory system (eV)
@param[in] out      : Partition for the exit channel
@param[in] cosangle : Scattering angle in the center-of-mass system
@param[in] Lmax     : maximum order of the Legendre polynomial expansion (see Lane-Thomas,VIII,eq(2.6))
*/
double System::sigma( const TwoBody& inc, const double elab, const TwoBody& out, const double cosangle, const int Lmax ) const {

  double sigma = 0.0;

  double i1 = inc.Particle::Spin();  double I1 = inc.Nucleus::Spin();
  double i2 = out.Particle::Spin();  double I2 = out.Nucleus::Spin();

  // channel-spin sum

  for( double s1=fabs(i1-I1); s1<=(i1+I1); s1+=1.0 )

    for( double s2=fabs(i2-I2); s2<=(i2+I2); s2+=1.0 )

      sigma += this->sigma( inc,s1, out,s2, elab, cosangle, Lmax );

  return sigma/(2.*i1+1.)/(2.*I1+1.);

}


/*! @brief Calculate differential cross section with analytical formula
@param[in] inc      : Partition for the incident channel
@param[in] s1       : channel spin for incident channel
@param[in] elab     : Energy of the incident particle in the laboratory system (eV)
@param[in] out      : Partition for the exit channel
@param[in] s2       : channel spin for exit channel
@param[in] cosangle : Scattering angle in the center-of-mass system
@param[in] Lmax     : maximum order of the Legendre polynomial expansion (see Lane-Thomas,VIII,eq(2.6))
@note if Lmax=0, channel-spin component sum is performed
*/
double System::sigma( const TwoBody& inc, const double s1, const TwoBody& out, const double s2,
const double elab, const double cosangle, const int Lmax ) const {

  if( Lmax == 0 ) return this->sigma( inc,s1, out,s2, elab, cosangle );

  double sigma_rh(0.0),sigma_ni(0.0),sigma_n(0.0);

  for( int L=0; L<=Lmax; L++ )

  //sigma_n += 1./M_PI * this->B( inc,s1, out,s2, L ) * gsl_sf_legendre_Pl( L, cosangle );
    sigma_n += 1./M_PI * this->B( inc,s1, out,s2, L ) * Legendre_PL( L, cosangle );

  // elastic scattering for charged particle

  if( inc == out && eq(s1,s2) ) {

    // Coulomb term

    sigma_rh = ( 2.*s1+1. ) * norm( inc.C( elab, cosangle ) );

    // Coulomb-Nuclear interference terms

    sigma_ni = this->NI( inc, s1, elab, cosangle );

  }

  //cerr << sigma_rh << "  " <<  sigma_n  << "  " << sigma_ni << endl;

  return ( sigma_rh + sigma_n + sigma_ni ) * M_PI/inc.wk2( inc.Ecm(elab) ) /100.;

}


/*! @brief Calculate differential cross section from the amplitudes
@param[in] inc      : Partition for the incident channel
@param[in] s1       : channel spin for incident channel
@param[in] nu1      : component of channel spin s1
@param[in] out      : Partition for the exit channel
@param[in] s2       : channel spin for exit channel
@param[in] nu2      : component of channel spin s2
@param[in] elab     : Energy of the incident particle in the laboratory system (eV)
@param[in] cosangle : Scattering angle in the center-of-mass system
*/
double System::sigma( const TwoBody& inc, const double s1, const double nu1,
                      const TwoBody& out, const double s2, const double nu2, const double elab, const double cosangle ) const {
// s1,s2  : channel spin 
// nu1,n2 : component of channel spin

  complex<double> A = this->A( inc,s1,nu1,out,s2,nu2, elab, cosangle );

  return pow( abs( A ), 2. )/100.;

}


/*! @brief Calculate differential cross section from the amplitudes (channel-spin component sum is performed)
@param[in] inc      : Partition for the incident channel
@param[in] s1       : channel spin for incident channel
@param[in] out      : Partition for the exit channel
@param[in] s2       : channel spin for exit channel
@param[in] elab     : Energy of the incident particle in the laboratory system (eV)
@param[in] cosangle : Scattering angle in the center-of-mass system
*/
double System::sigma( const TwoBody& inc, const double s1,
                      const TwoBody& out, const double s2, const double elab, const double cosangle ) const {
// s1,s2  : channel spin 

  double sigma = 0.0;

  for( double nu1=-s1; nu1<=s1; nu1+=1. )

    for( double nu2=-s2; nu2<=s2; nu2+=1. )

      sigma += this->sigma( inc,s1,nu1, out,s2,nu2, elab, cosangle );

  return sigma;

}




/*! @brief Calculate amplitudes (see Lane-Thomas,VIII,eq(2.3))
@param[in] inc      : Partition for the incident channel
@param[in] s1       : channel spin for incident channel
@param[in] nu1      : component of channel spin s1
@param[in] out      : Partition for the exit channel
@param[in] s2       : channel spin for exit channel
@param[in] nu2      : component of channel spin s2
@param[in] elab     : Energy of the incident particle in the laboratory system (eV)
@param[in] cosangle : Scattering angle in the center-of-mass system
*/
complex<double> System::A( const TwoBody& inc, const double s1, const double nu1,
                           const TwoBody& out, const double s2, const double nu2,
                           const double elab, const double cosangle ) const {
// calculate amplitude
// see Lane-Thomas,VIII,eq(2.3)
// s1,s2  : channel spin 
// nu1,n2 : channel spin conponent

  //cerr << elab << endl;

  //double ecm = inc.Ecm(elab);
  complex<double> I(0.,1.),T,A(0.,0.);

    for( int i=0; i<this->size(); i++ ) A += ary[i].A( inc,s1,nu1, out,s2,nu2, cosangle );

  A *= I;

  // Coulomb amplitude

  if( inc==out && eq(s1,s2) && eq(nu1,nu2) ) A -= inc.C( elab, cosangle );

  return A *sqrt(M_PI)/inc.wk( inc.Ecm( elab ) );

}



double System::B( const TwoBody& inc, const double s1, const TwoBody& out, const double s2, const int L ) const {
// RESCAL

  double B = 0.0;

    for( int i=0; i<this->size(); i++ )

      for( int j=0; j<this->size(); j++ ) B += ary[i].B( inc,s1, out,s2, L, &ary[j] );

  return 0.25 * pm( int (s1-s2) ) * B;

}


double System::B( const TwoBody& inc, const TwoBody& out, const int L ) const {

  double B = 0.0;

  double i1 = inc.Particle::Spin();  double I1 = inc.Nucleus::Spin();
  double i2 = out.Particle::Spin();  double I2 = out.Nucleus::Spin();

  // channel-spin sum

  for( double s1=fabs(i1-I1); s1<=(i1+I1); s1+=1.0 )

    for( double s2=fabs(i2-I2); s2<=(i2+I2); s2+=1.0 )

      B += this->B( inc,s1, out,s2, L );

  return B/(2.*i1+1.)/(2.*I1+1.);

}


double System::LEG( const TwoBody& inc, const double elab, const TwoBody& out, const int L ) const {
// Legendre coefficient
// L : order of the legendre expansion

  return this->B( inc, out, L )/(2.*L+1.)/inc.wk2( inc.Ecm(elab) )/100.;

}




/*! @brief Calculate Coulomb-nuclear interference term for charged particle
@param[in] inc  : Partition for the incident channel
@param[in] elab : Energy of the incident particle in the laboratory system (eV)
@param[in] l    : angular momentum of the relative motion
*/
complex<double> System::NI( const TwoBody& inc, const double elab, const int l ) const {

  complex<double> a(0.0,0.0);

  double i1 = inc.Particle::Spin();  double I1 = inc.Nucleus::Spin();
  double i2 = inc.Particle::Spin();  double I2 = inc.Nucleus::Spin();

  // channel-spin sum

  for( double s1=fabs(i1-I1); s1<=(i1+I1); s1+=1.0 )

    for( double s2=fabs(i2-I2); s2<=(i2+I2); s2+=1.0 )

      if( eq(s1,s2) ) a += this->NI( inc, s1, elab, l );

  return a/(2.*i1+1.)/(2.*I1+1.);

  /*
  double i = inc.Particle::Spin();
  double I = inc.Nucleus ::Spin();

  // channel-spin sum

  for( double s=fabs(i-I); s<=(i+I); s+=1.0 ) a += this->NI( inc, s, elab, l );

  return a/(2.*i+1.)/(2.*I+1.);
  */
}


complex<double> System::NI( const TwoBody& inc, const double s, const double elab, const int l ) const {
// Coulomb-nuclear interference term for charged particle
// complex coefficients for expanding the trace of the nuclear scattering amplitude matrix (see ENDF manual)
// to be used for FILE6, LAW=5, LTP=1

  complex<double> sum(0.,0.);

    for( unsigned int i=0; i<ary.size(); i++ )

      sum += ( 2.*ary[i].J() + 1. ) * ary[i].NI( inc, s, elab, l );

  return sum;

}


double System::NI( const TwoBody& inc, const double s, const double elab, const double cosangle ) const {
// Coulomb-nuclear interference term for charged particle
// elastic scattering differential cross-section
// note : T-matrix should be conjugated (R.E.Azuma2010,PRC81,045805)
// s : channel spin

  double sum(0.0);

    for( unsigned int i=0; i<ary.size(); i++ )

      sum += ( 2.*ary[i].J() + 1. ) * ary[i].NI( inc, s, elab, cosangle );

  return sum;

  /*
  double sum(0.0);  complex<double> I(0.,1.),T,W;

  for( unsigned int i=0; i<ary.size(); i++ ) {

    Partition a = *this->at(i).alpha( inc );

    for( int ii=0; ii<a.size(); ii++ ) {

      if( ne( a[ii].s(), s ) ) continue;

      T = this->at(i).T( a[ii], a[ii] );

    //W = I * conj(T) * inc.C( elab, cosangle ) * gsl_sf_legendre_Pl( a[ii].l(), cosangle );
      W = I * conj(T) * inc.C( elab, cosangle ) * Legendre_PL( a[ii].l(), cosangle );

      sum += ( 2.*this->J(i) + 1. ) * 2.*real(W);

    }

  }

  return sum/sqrt(4.*M_PI);
  */

}


/*
void System::B( const TwoBody* out, const int Lmax, LIST& ans ) {

  deque<double> b;

    for( int l=1; l<=Lmax; l++ ) b.push_back( this->B(out,l) );

    ans.Set( 0.0, elab, 0, 0, Lmax, 0, b );

  return;

}

void System::B( const TwoBody& incident, const double energy_lab, const TwoBody* out, const int Lmax, LIST& ans ) {

  return this->System::Solve( incident, energy_lab )->B( out, Lmax, ans );

}
*/

/*
void System::a( const TwoBody& incident, const double energy_lab, const TwoBody* out, const int Lmax, LTT1::Record& ans ) {
// Legendre coefficient in ENDF definition

  double sigma = this->System::Solve( incident, energy_lab )->sigma( out );

  deque<double> a;

    for( int l=1; l<=Lmax; l++ ) a.push_back( this->B(out,l)/sigma/(2.*l+1.) );

    ans.Set( 0.0, elab, 0, 0, Lmax, 0, a );

    //cerr << ans.f().Integral() << endl;

  return;

}
*/


/*
void System::a( const TwoBody& inc, const double elab, const TwoBody& out, const int Lmax, LTT1::Record* a ) {
// Legendre coefficient in ENDF definition

  double sigma = this->sigma( inc, elab, out );

  for( int l=1; l<=Lmax; l++ ) a->PushBack( this->B(inc,elab,out,l)/sigma/(2.*l+1.) );

    a->E( elab );

  return;

}


void System::a( const TwoBody& inc, const double elab, const TwoBody& out, const double eps_c, LTT1::Record* a ) {
// Legendre coefficient in ENDF definition

  double sigma = this->sigma( inc, elab, out );

  int l = 0;

  double f1a,f2a,f3a,f4a,f5a;
  double f1b,f2b,f3b,f4b,f5b;

    do {  l++;

      f1a = a->f(-1.0); f2a = a->f(-0.5); f3a = a->f(0.0); f4a = a->f(0.5); f5a = a->f(1.0);

      a->PushBack( this->B(inc,elab,out,l)/sigma/(2.*l+1.) );

      f1b = a->f(-1.0); f2b = a->f(-0.5); f3b = a->f(0.0); f4b = a->f(0.5); f5b = a->f(1.0);

    } while ( fabs(1.-f1b/f1a) > eps_c ||
              fabs(1.-f2b/f2a) > eps_c ||
              fabs(1.-f3b/f3a) > eps_c ||
              fabs(1.-f4b/f4a) > eps_c ||
              fabs(1.-f5b/f5a) > eps_c );

    a->E( elab );

  return;

}
*/

/*! @brief Get i-th J^pi group */
const Structure& System::at        ( const int i ) const { return ary[i]; }
      Structure& System::at        ( const int i )       { return ary[i]; }

/*! @brief Get i-th J^pi group */
const Structure& System::operator[]( const int i ) const { return ary[i]; }
      Structure& System::operator[]( const int i )       { return ary[i]; }

/*! @brief Number of the J^pi group */
int  System::size () const { return ary.size(); }

/*! @brief Resize the number of the J^pi group */
void System::resize( const int size ) { ary.resize( size ); }




/*! @brief Collect free parameters */
void System::CollectFreeParams( vector<Parameter*>* o ) {

  this->Boundary::CollectFreeParams( o );

    for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].CollectFreeParams( o );

  return;

}


/*! @brief Number of the free parameters */
int System::npm_free() const { return size_free_pm; }



/*! @brief Check if given J^pi exists for this system
@param[in] J  : Spin
@param[in] pi : Parity (positive/negative)
*/
Structure* System::Find( const double J, const int pi ) {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) {

    if( eq( ary[i].J(), J ) && ary[i].pi() == pi  ) return &ary[i];

  }

  return NULL;

}

/*! @brief Check if given partition exists for this system */
bool System::Find( const TwoBody& partition ) const {

  for( int i=0; i<static_cast<int>(parts.size()); i++ )

    if( partition == parts[i] ) return true;

  return false;

}

/*! @brief Check if given partition exists for this system */
bool System::Find( const Particle& a, const Nucleus& b ) const {

  for( int i=0; i<static_cast<int>(parts.size()); i++ )

    if( a == parts[i] && b == parts[i] ) return true;

  return false;

}


void System::SetZero_gamma( const Particle& a, const Nucleus& b ) {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].SetZero_gamma(a,b);  return;

}

void System::Fix_E() {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].Fix_E();  return;

}

void System::Fix_gamma() {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].Fix_gamma();  return;

}

void System::Fix_gamma( const Particle& a, const Nucleus& b ) {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].Fix_gamma(a,b);  return;

}


/*! @brief Print all the R-matrix parameters given for this object */
void System::Print( ostream& os ) const {

  os << "Title : " << title << endl;

  os << endl;

  os << "<Boundary>" << endl;

  this->Boundary::Print( os );

  os << endl;

  os << "<Reduced width amplitude>" << endl;

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].Print( os );

  return;

}


void System::PrintLatex( ostream& os ) const {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) this->at(i).PrintLatex( os );  return;

}



/*! @brief Clear this object */
System* System::Clear() {

  this->Boundary::Clear();

  mass = 0.0;

  title.clear();
  ary  .clear();

  return this;

}








static complex<double> get_A( const System* o, const TwoBody& inc, const double elab, const double cosangle, const int lmax ) {
// for Az

  double ecm = inc.Ecm(elab);

  double i1 = inc.Particle::Spin();
  double I1 = inc.Nucleus ::Spin();

  complex<double> i(0.,1.),sum(0.,0);

    for( double s1=fabs(i1-I1); s1<=(i1+I1); s1+=1.0 ) {

      for( int l=0; l<=lmax; l++ ) {

        double Ja = fabs(l-s1);
        double Jb = fabs(l+s1);

        Channel ca( inc,Ja,l,s1 );//  ca.Update( ecm, this );
        Channel cb( inc,Jb,l,s1 );//  cb.Update( ecm, this );

      //sum += ( double(l+1) * o->T( cb )
      //     +   double(l  ) * o->T( ca ) ) * gsl_sf_legendre_Pl( l, cosangle );

        sum += ( double(l+1) * o->T( cb )
             +   double(l  ) * o->T( ca ) ) * Legendre_PL( l, cosangle );

      }

    }

    sum *= i/2./inc.wk( ecm );

    if( inc.ZZ() ) sum -= inc.C( elab, cosangle );

    //sum /= (2.*i1+1.)/(2.*I1+1.);

  return sum;

}


static complex<double> get_B( const System* o, const TwoBody& inc, const double elab, const double cosangle, const int lmax ) {
// for Az

  double ecm = inc.Ecm(elab);

  double i1 = inc.Particle::Spin();
  double I1 = inc.Nucleus ::Spin();

  complex<double> sum(0.,0);

    for( double s1=fabs(i1-I1); s1<=(i1+I1); s1+=1.0 ) {

      for( int l=1; l<=lmax; l++ ) {

        double Ja = fabs(l-s1);
        double Jb = fabs(l+s1);

        Channel ca( inc,Ja,l,s1 );//  ca.Update( ecm, this );
        Channel cb( inc,Jb,l,s1 );//  cb.Update( ecm, this );

      //sum += ( o->T( cb )
      //     -   o->T( ca ) ) * gsl_sf_legendre_Plm( l, 1, cosangle );

        sum += ( o->T( cb )
             -   o->T( ca ) ) * Legendre_PLM( l, 1, cosangle );

      }

    }

    sum *= 1./2./inc.wk( ecm );

    //sum /= (2.*i1+1.)/(2.*I1+1.);

  return sum;

}


/*! @brief Calculate analyzing power for the I=1/2 particle
@param[in] inc      : Partition for the incident channel
@param[in] elab     : Energy of the incident particle in the laboratory system (eV)
@param[in] cosangle : Scattering angle in the center-of-mass system
@param[in] lmax     : Maximum number of the angular momentum
*/
double System::Az( const TwoBody& inc, const double elab, const double cosangle, const int lmax ) const {
// analyzing power for the I=1/2 particle

  complex<double> A = get_A( this, inc,elab,cosangle,lmax );
  complex<double> B = get_B( this, inc,elab,cosangle,lmax );

  //cerr << A << "  " << B << endl;
  //cerr << real( conj(A)*B+A*conj(B) ) << endl;
  //return ( norm(A)+norm(B) )/100.;

  return real( conj(A)*B+A*conj(B) ) / ( norm(A)+norm(B) );

}


/*! @brief T-matrix element for the elastic channel c1 */
complex<double> System::T( const Channel& c1 ) const {

  for( int i=0; i<this->size(); i++ )

    if( ary[i].J() == c1.J() && ary[i].pi() == c1.pi() ) return this->at(i).T( c1 );

  return complex<double>( 0.0, 0.0 );

}


}
