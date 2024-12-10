#include "ReconResonance/RmatrixLimited/rml/Coulomb.h"

#include <cmath>

#include "ReconResonance/RmatrixLimited/numeric/Tabular.h"

//ClassImp( RML::Coulomb );

namespace RML {

Coulomb::Coulomb() : rc(0.0), rh(0.0), bc(0.0), do_shift(true), do_penet(true) {

  coulomb_scatt_ps     = 0.0;
  hard_sphere_scatt_ps = 0.0;
  shift_factor         = 0.0;
  penetration_factor   = 0.0;

  l0 = complex<double>(0.,0.);

}

Coulomb::Coulomb( const Channel& ch ) : rc(0.0), rh(0.0), bc(0.0), do_shift(true), do_penet(true) {

  this->Set( ch );

}

Coulomb::Coulomb( const TwoBody& o, const double J, const int l, const double s ) : rc(0.0), rh(0.0), bc(0.0), do_shift(true), do_penet(true) {

  this->Set( o,J,l,s );

}

Coulomb::Coulomb( const Particle& a, const Nucleus& b, const double J, const int l, const double s ) : rc(0.0), rh(0.0), bc(0.0), do_shift(true), do_penet(true) {

  this->Set( a,b,J,l,s );

}



Coulomb* Coulomb::Set( const Channel& ch ) {

  this->Channel::Set( ch );  return this;

}

Coulomb* Coulomb::Set( const TwoBody& o, const double J, const int l, const double s ) {

  this->Channel::Set( o,J,l,s ); return this;

}

Coulomb* Coulomb::Set( const Particle& a, const Nucleus& b, const double J, const int l, const double s ) {

  this->Channel::Set( a,b,J,l,s );  return this;

}



// Whittaker function

static double func_w( const double& t, const double* params ) {

  double l   = params[0];
  double eta = params[1];
  double rho = params[2];

  return pow(t,l+eta) * exp(-1.*t) * pow(1.+t/(2.*rho),l-eta);

}



static double Whittaker( const double& rho, const double& eta, const int& l ) {

  ///// non-GSL with an integral method /////

  double params[3];

    params[0] = l;
    params[1] = eta;
    params[2] = rho;

  double x1(1.e-16),x2(10.*rho), sum,save, eps(1.e-4);  Tabular a(5);

    if( x1 > x2 ) return 0.0;  // to be checked for 19F(n,n1) 

    a.reserve(1000);

    sum = a.Set( x1,x2, func_w, params, eps )->I();

    do {

      save = sum;  x1 = x2;  x2 += x2;

      sum += a.Set( x1,x2, func_w, params, eps )->I();

    } while( fabs( (save-sum)/save ) > 1.e-3 );

  return exp(-1.*rho-eta*log(2.*rho))/tgamma(1.+l+eta) * sum;

}



// derivative
static double Whittaker_p( double x, double eta, int l ) {

  double x1 = x * ( 1. - 0.001 );
  double x2 = x * ( 1. + 0.001 );

  return ( Whittaker(x2,eta,l) - Whittaker(x1,eta,l) ) / ( x2-x1 );

}



static double ShiftFactor( const int& l, const double& rho );
static double Penetration( const int& l, const double& rho );

// Penetration factor for the neutrons
static double Penetration( const int& l, const double& rho ) {

  if( l == 0 ) return rho;

  double rho2 = rho*rho;
  double rho3 = rho*rho2;
  double rho4 = rho*rho3;

  switch( l ) {

    case 1:  return rho3/( 1.0 + rho2 );
    case 2:  return rho2*rho3/( 9.0 + 3.0*rho2 + rho2*rho2 );
    case 3:  return rho3*rho3*rho/( 225.0 + 45.0*rho2 + 6.0*rho2*rho2 + rho3*rho3 );

    case 4 : return rho4*rho4*rho/( 11025. + 1575.*rho2 + 135.*rho4 + 10.*rho3*rho3 + rho4*rho4 );

    default:
      //cerr << " l should be less than 5 " << endl;  exit(1);

      double P = Penetration(l-1,rho);
      double S = ShiftFactor(l-1,rho);

      return rho2 * P / ( pow(l-S,2.) + P*P  );

  }

}

// Shift factor for the neutrons
static double ShiftFactor( const int& l, const double& rho ) {

  if( l == 0 ) return 0.0;

  double rho2 = rho*rho;
  double rho4 = rho2*rho2;

  switch( l ) {

    case 1:  return -1.0/( 1.0 + rho2 );
    case 2:  return -1.0*( 18.0 + 3.0*rho2 )/( 9.0 + 3.0*rho2 + rho2*rho2 );
    case 3:  return -1.0*( 675.0 + 90.0*rho2
                    + 6.0*rho2*rho2 )/( 225.0 + 45.0*rho2 + 6.0*rho2*rho2 + rho2*rho2*rho2 );

    case 4:  return -1.0*( 44100. + 4725.*rho2 + 270.*rho4 + 10.*rho2*rho4 )
                    / ( 11025. + 1575.*rho*2 + 135.*rho4 + 10.*rho4*rho2 + rho4*rho4 );

    default:
      //cerr << " l should be less than 5 " << endl;  exit(1);

      double P = Penetration(l-1,rho);
      double S = ShiftFactor(l-1,rho);

      return rho2 * (l-S) / ( pow(l-S,2.) + P*P ) - l;

  }

}

// Hard-sphere scattering p.s. for the neutrons
static double HardSpherePhaseShift( const int& l, const double& rho ) {

  switch( l ) {

    case 0:  return rho;
    case 1:  return rho - atan(rho);
    case 2:  return rho - atan( 3.0*rho/(3.0-rho*rho) );
    case 3:  return rho - atan( rho*(15.0-rho*rho)/(15.0-6.0*rho*rho) );

    case 4 : return rho - atan( rho*(105.-10.*rho*rho)/(105.-45.*rho*rho+ rho*rho*rho*rho) );

    default:
      //cerr << " l should be less than 5 " << endl;  exit(1);

      double P = Penetration(l-1,rho);
      double S = ShiftFactor(l-1,rho);

      return HardSpherePhaseShift(l-1,rho) - atan( P/(l-S) );

  }

}

// penetration and shift factor
static void coulomb_wf( const double& eta, const double& rho, const int& l, double* P, double* S ) {

  if( eq(eta,0.0) && l < 5 ) {

    *P = Penetration( l, rho );
    *S = ShiftFactor( l, rho );

    return;

  }

  double F0,F1,G0,G1;

  ///// POD /////

  coulomb_wave( eta, rho, l, &F0,&F1,&G0,&G1 );

    *P = rho / ( F0*F0 + G0*G0 );
    *S = *P  * ( F0*F1 + G0*G1 );

  return;

}

// hard-sphere scattering phase-shift
static void coulomb_wf( const double& eta, const double& rho, const int& l, double* ps ) {

  if( eq(eta,0.0) && l < 5 ) {

    *ps = HardSpherePhaseShift( l, rho );  return;

  }

  double F0,F1,G0,G1;

  ///// POD /////

  coulomb_wave( eta, rho, l, &F0,&F1,&G0,&G1 );

  *ps = atan2( F0, G0 );

  return;

}


void Coulomb::Update( const double e ) {
// Caluclate Coulomb scattering phase-shift, hard-sphere phase-shift, shift factor
// penetration factor and L0(=S-B+iP) value
// e         : ecm + Q

  //cerr << inc.Qval( *this ) << endl;

  //double e = ecm + inc.Qval( *this );

  //this->Particle::Print();
  //cerr << "  " << inc.Qval( *this ) << endl;

  coulomb_scatt_ps     = 0.0;
  hard_sphere_scatt_ps = 0.0;
  shift_factor         = 0.0;
  penetration_factor   = 0.0;

  if( eq(e,0.0) ) return;

  double wk = this->wk(e);

  double rho_c = wk * this->Rc();
  double rho_h = wk * this->Rh();

  double eta0 = this->eta( e );
  bool   open = ( e > 0.0 );

  //cerr << *this << "  " << e << "  " << rho_c << "  " << rho_h << "  " << eta0 << endl;

  //cerr << eta0 << endl;

  //if( eta0 > 100.0 ) cerr << eta0 << endl;

  double eta = min( eta0, 80. );  // if eta > 100., gsl_sf_coulomb_wave_FG_e report an error

  //int status;

  /* Coulomb scattering phase-shift */

/*
  gsl_sf_result lnr, arg;

    status = gsl_sf_lngamma_complex_e ( 1., eta0, &lnr, &arg );

    coulomb_scatt_ps0 = arg.val;

    status = gsl_sf_lngamma_complex_e ( double( this->l()+1. ), eta0, &lnr, &arg );

  //coulomb_scatt_ps = arg.val;
    coulomb_scatt_ps = arg.val - coulomb_scatt_ps0;
*/
    coulomb_scatt_ps = this->CoulombPS( e, this->l() ) - this->CoulombPS( e, 0 );  // new


  /* Hard-sphere scatt. phase-shift, shift & penetration factor */

  if( open ) {

    double p,s;  //double F0,F1,G0,G1;

    // penetration and shift factors

      coulomb_wf( eta, rho_c, this->l(), &p, &s );

        if( this->do_Penet() ) penetration_factor = p;
        if( this->do_Shift() ) shift_factor       = s;


    // hard-sphere scattering p.s.

      coulomb_wf( eta, rho_h, this->l(), &hard_sphere_scatt_ps );


	/*
	cerr << endl;

	inc.Print(); cerr << endl;
	this->TwoBody::Print(); cerr << endl;

	cerr << "eta    = " << eta << endl;
	cerr << "e      = " << e << endl;
	cerr << "l      = " << this->l() << endl;
	cerr << "sigma0 = " << coulomb_scatt_ps0 << endl;
	cerr << "sigma  = " << temp << endl;
	cerr << "omega  = " << coulomb_scatt_ps << endl;
	cerr << "phi    = " << hard_sphere_scatt_ps << endl;

	//exit(1);
	*/

  }

  else {  // shift factor for closed channel

    //cerr << "begin close" << endl;

    //eta = eta0;

    //cerr << eta << endl;

    //cerr << e << "  " << eta <<  endl;

    //if( this->do_Penet() ) penetration_factor = 0.0;
    if( this->do_Shift() ) shift_factor = rho_c * Whittaker_p(rho_c,eta,this->l())/Whittaker(rho_c,eta,this->l());

    //if( this->do_Shift() ) this->WKB( e, this->Rc(), &shift_factor );

    //cerr << "end close" << endl;

    //cerr << shift_factor << endl;
  }

  l0 = complex<double>( shift_factor - this->Bc(), penetration_factor );

  return;

}


void Coulomb::Update( const double e, const Boundary* condition ) {

  this->Rc() = condition->Rc( *this ).Value();
  this->Rh() = condition->Rh( *this ).Value();
  this->Bc() = condition->Bc( *this ).Value();

  this->do_Shift() = condition->do_Shift( *this );
  this->do_Penet() = condition->do_Penet( *this );

  return this->Update( e );

}


bool Coulomb::Update( const double e, const int pi ) {

  if( pi != this->pi() ) return false;

  this->Update( e );

  return true;

}

bool Coulomb::Update( const double e, const Boundary* condition, const int pi ) {

  if( pi != this->pi() ) return false;

  this->Update( e, condition );

  return true;

}



void Coulomb::WKB( const double e, const double rch, double* S ) const {
// calculate shift factor with the WKB approximation

  double ALPHA(1/137.03599976), AMU(931.494013e+6), HBARC(197.327e+6);

  double rhoeta = rch * this->ZZ() * this->mu() * AMU*ALPHA /HBARC;

  double rho_c = this->wk ( e ) * rch;

  int l = this->l();

    *S = -1. * sqrt( (l+0.5)*(l+0.5) + 2.*rhoeta + rho_c*rho_c )
    + ( rhoeta + (l+0.5)*(l+0.5) )/2./( (l+0.5)*(l+0.5) + 2.*rhoeta + rho_c*rho_c );

  return;

}



/*! @brief Test calculation for Coulomb wave functions
@param[in]  eta : Sommerfeld (Coulomb field) parameter
@param[in]  rho : product of wave number and radius, viz., rho=k*r
@param[in]  l   : orbital angular momentum
@param[out] P   : penetration factor
@param[out] S   : shift factor
*/
void Coulomb::Test( const double& eta, const double& rho, const int& l, double* P, double* S ) const {

  return coulomb_wf( eta, rho, l, P, S );

}

/*! @brief Test calculation for Coulomb wave functions
@param[in]  eta : Sommerfeld (Coulomb field) parameter
@param[in]  rho : product of wave number and radius, viz., rho=k*r
@param[in]  l   : orbital angular momentum
@param[out] ps  : hard-sphere phase-shift
*/
void Coulomb::Test( const double& eta, const double& rho, const int& l, double* ps ) const {

  return coulomb_wf( eta, rho, l, ps );

}


void Coulomb::TestWhitS( const double& eta, const double& rho, const int& l, double* S ) const {


  *S = rho * Whittaker_p(rho,eta,l)/Whittaker(rho,eta,l);  return;

}



}
