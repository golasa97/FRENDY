#include "ReconResonance/RmatrixLimited/rml/TwoBody.h"
#include "ReconResonance/RmatrixLimited/numeric/Constant.h"
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"

//ClassImp( RML::TwoBody );

using namespace Constant;
using namespace Numeric;

//#define hbarc ( hbar * c_speed_of_light * 1.e+15 )


namespace RML {


/*! @brief Constructor */
TwoBody::TwoBody() {}

/*! @brief Constructor */
TwoBody::TwoBody( const Particle& a ) {

  this->Set( a );

}

/*! @brief Constructor */
TwoBody::TwoBody( const Particle& a, const Nucleus& b ) {

  this->Set( a, b );

}

/*! @brief Constructor */
TwoBody::TwoBody( const TwoBody& o ) {

  this->Set( o );

}

/*! @brief Destructor */
TwoBody::~TwoBody() {}



/*! @brief Set particle */
void TwoBody::Set( const Particle& a ) {

  this->Particle::Set( a );

}


/*! @brief Set nucleus */
void TwoBody::Set( const Nucleus & b ) {

  this->Nucleus ::Set( b );

}


/* @brief Set particle and nucleus */
void TwoBody::Set( const Particle& a, const Nucleus& b ) {

  this->Set( a );
  this->Set( b );

}



void TwoBody::Set( const TwoBody& o ) {

  this->Particle::Set( o );
  this->Nucleus ::Set( o );

}


/*! @brief Get minimum value of total spin */
double TwoBody::I_min() const {

  return fabs( this->Particle::Spin() - this->Nucleus::Spin() );

}

/*! @brief Get maximum value of total spin */
double TwoBody::I_max() const {

  return this->Particle::Spin() + this->Nucleus::Spin();

}

/*! @brief Get total parity (product of particle and nucleus) */
int TwoBody::pi() const {

  return this->Particle::Parity() * this->Nucleus::Parity();

}


/*! @brief Get particle mass [amu] */
const double& TwoBody::M1() const { return this->Particle::Mass(); }
      double& TwoBody::M1()       { return this->Particle::Mass(); }

/*! @brief Get nucleus mass [amu] */
const double& TwoBody::M2() const { return this->Nucleus ::Mass(); }
      double& TwoBody::M2()       { return this->Nucleus ::Mass(); }



/*! @brief Q-value calculated by the mass-difference
@param[in] o : partition for the final channel
*/
double TwoBody::QM( const TwoBody& o ) const {

  if( eq( this->M1(), this->M2() ) && eq( o.M1(), o.M2() ) ) return 0.0;

  return amu * ( this->M1() + this->M2() - o.M1() - o.M2() );

}

/*! @brief Reaction Q-value calculated by the mass-difference
@param[in] o : partition for the final channel
*/
double TwoBody::QI( const TwoBody& o ) const {

  if( *this == o ) return 0.0;

  return this->QM( o ) - o.Nucleus::Energy();

}

/*! @brief Reaction Q-value (same sa QI)
@param[in] o : partition for the final channel
*/
double TwoBody::Qval( const TwoBody& o ) const {

  return this->QI( o );

  /*
  if( *this == o ) return 0.0;

  return AMU * ( this->M1() + this->M2() - o.M1() - o.M2() ) - o.Nucleus::Energy();
  */

}


/*! @brief Threshold energy in laboratory frame
@param[in] o : partition for the final channel
*/
double TwoBody::Ethre( const TwoBody& o ) const {

  double val = this->Elab( -1.*this->Qval(o) );

  return max( val, 0.0 );

}


/*! @brief Reduced mass */
double TwoBody::mu() const {

  return this->M1()*this->M2()/( this->M1() + this->M2() );

}


/*! @brief Product of particle and nucleus charges */
double TwoBody::ZZ() const {

  return this->Particle::Z() * this->Nucleus::Z();

}


double TwoBody::Escale() const {

  return 2.0* this->mu()*amu/(hbarc*hbarc);

}

/*! @brief particle energy in the center-of-mass system */
double TwoBody::Ecm( const double elab ) const {

  return elab * this->M2()/( this->M1() + this->M2() );

}

/*! @brief particle energy in the laboratory system */
double TwoBody::Elab( const double ecm ) const {

  return ecm * ( this->M1() + this->M2() )/this->M2();

}


/*! @brief Wave number
@param[in] e : energy of the system in the center-of-mass system (ecm+Q)
*/
double TwoBody::wk( const double e ) const {

  //cerr << "wk = " << e << "  " << this->Escale() << endl;

  return sqrt( fabs(e) * this->Escale() );

}

/*! @brief Square of the wave number
@param[in] e : energy of the system in the center-of-mass system (ecm+Q)
*/
double TwoBody::wk2( const double e ) const {

  return pow( this->wk(e), 2.0 );

}

/*! @brief The Sommerfeld parameter
@param[in] e : energy of the system in the center-of-mass system (ecm+Q)
*/
double TwoBody::eta( const double e ) const {

  if( e == 0.0 ) {

    cerr << "!! TwoBody::eta -> not obtained because E = 0.0" << endl; exit(1);
    
  }

  return ZZ() * mu() * amu *alpha_fine_structure /( hbarc*wk(e) );

  //double xwk = ( wk(_e) == 0. ) ? 1.e-15 : wk(_e);

  //return ZZ() * mu() * AMU*ALPHA /HBARC/xwk;

}


static double coulomb_ps( const double& eta, const int& l );

/*!
@brief Calculate Coulomb scattering phase-shift
@param[in] e : energy of the system [eV]
@param[in] l : quantum number of the angular momentum
*/
double TwoBody::CoulombPS( const double e, const int l ) const {

  return coulomb_ps( this->eta(e), l );

}

void coulomb_wave( const double& eta, const double& rho, const int& l, double* F, double* F1, double* G, double* G1 );

/*!
@brief Calculate Coulomb wave-function
@param[in] e : energy of the system [eV]
@param[in] r : radius where F,F1,G,G1 are evaluated [fm]
@param[in] l : quantum number of the angular momentum
@param[out] F,G,  : Coulomb functions
@param[out] F1,G1 : derivative of the Coulomb functions
*/
void TwoBody::CoulombWF( const double e, const double r, const int l, double* F, double* F1, double* G, double* G1 ) const {

  return coulomb_wave( this->eta(e), this->wk(e)*r, l, F,F1,G,G1 );

}


/*!
@brief Coulomb scattering amplitude
@param[in] elab     : energy of the projectile in the laboratory frame [eV]
@param[in] cosangle : scattering angle in the center-of-mass frame
*/
complex<double> TwoBody::C( const double elab, const double cosangle ) const {
// Coulomb scattering amplitude

  double e = this->Ecm( elab );
/*
  gsl_sf_result lnr, arg;

  int status = gsl_sf_lngamma_complex_e ( 1, this->eta(e), &lnr, &arg );

  double sigma0 = arg.val;
*/

  //double sigma0 = this->CoulombPS(e,0);  // new

  double sin2 = 0.5*(1.-cosangle);

//complex<double> a( 0.0, -1.*this->eta(e)*log( sin2 ) + 2.*sigma0 );
  complex<double> a( 0.0, -1.*this->eta(e)*log( sin2 ) );

  return 1.0/sqrt(4.*M_PI) * this->eta(e) * 1./sin2 * exp(a);

}

/*!
@brief Coulomb scattering differential cross-section [barn] in the center-of-mass frame
@param[in] elab     : energy of the projectile in the laboratory frame [eV]
@param[in] cosangle : scattering angle in the center-of-mass frame
*/
double TwoBody::sigma_c( const double elab, const double cosangle ) const {
// Coulomb scattering differential cross-section in cms

  return norm( this->C( elab, cosangle ) ) * M_PI/this->wk2( this->Ecm(elab) ) /100.;

}





bool TwoBody::operator==( const TwoBody& o ) const {

  return this->Particle::operator==( o ) && this->Nucleus::operator==( o );

}

bool TwoBody::operator!=( const TwoBody& o ) const { return !( *this == o ); }


bool TwoBody::operator<( const TwoBody& o ) const {

  if( this->Particle::ZA() <  o.Particle::ZA() ) return true;
  if( this->Particle::ZA() == o.Particle::ZA() ) return ( this->Nucleus::ZA() < o.Nucleus::ZA() );

  return false;

}

bool TwoBody::operator>( const TwoBody& o ) const {

  if( this->operator< ( o ) ) return false;
  if( this->operator==( o ) ) return false;

  return true;

}






static bool equiv( const Particle& a, const Nucleus& b ) {

  if( a.Z() == b.Z() && a.A() == b.A() && a.N() == b.N() && a.Parity() == b.Parity() &&
      eq( a.Mass(),b.Mass() ) && eq( a.Spin(),b.Spin() ) && eq( 0.0,b.Energy() ) ) return true;

  return false;

}

bool TwoBody::Equiv( const Particle& a, const Nucleus& b ) const {

  if( this->Particle::operator==(a) && this->Nucleus::operator==(b) ) return true;

  if( equiv(*this,b) && equiv(a,*this) ) return true;

  return false;

}

bool TwoBody::Equiv( const TwoBody& o ) const {

  return this->Equiv(o,o);

}


void TwoBody::Print( ostream& os ) const {

  this->Particle::Print( os );  os << "  ";
  this->Nucleus ::Print( os );

}


ostream& operator<<( ostream& os, const TwoBody& o ) {

  o.Print( os );  return os;

}






////////////////// Coulomb functions taken from the POD code //////////////////
//
// 1. Coulomb scattering phase-shift :
//    
//      double coulomb_ps( const double& eta, const int& l )
//
// 2. Coulomb scattering wave-function
//
//      void coulomb_wave( const double& eta, const double& rho, const int& l,
//                          double* F, double* F1, double* G, double* G1 );
//
//                                                    S.Kunieda (Nov.25, 2017)
///////////////////////////////////////////////////////////////////////////////


static void PHASE( const double& ETA, const int& LMAX, double* DELL ) {

  double ETA2(ETA*ETA),ETA4(ETA2*ETA2),ETA16(16.0+ETA2),DEL;

    DEL=-ETA+ETA/2.0*log(ETA16)+3.5*atan(ETA/4.0)
        -(atan(ETA)+atan(ETA/2.0)+atan(ETA/3.0))-ETA/12.0/ETA16
        *(1.0+(ETA2-48.0)/30.0/ETA16/ETA16+(ETA4-160.0*ETA2+1280.0)/105./pow(ETA16,4));

  int NPI;

      NPI=int(DEL/(2.0*M_PI));
      if( DEL < 0.0 ) NPI=NPI-1;
      DEL=DEL-double(NPI)*2.0*M_PI;

    DELL[0] = DEL;

    for( int L=1; L<=LMAX; L++ ) {

      DEL = DEL+atan(ETA/L);
      NPI=int(DEL/(2.0*M_PI));
      if( DEL < 0.0 ) NPI=NPI-1;
      DEL = DEL-double(NPI)*2.0*M_PI;

      DELL[L]=DEL;

    }

  return;

}


static double PHASE( const double& ETA, const int& L ) {

  double PS[L+1];

    PHASE( ETA, L, PS );

  return PS[L];

}



/*
static double A( const double& RHOA, const double& ETA, const int& N ) {

  return (2.*N+1.)*ETA/(2.*(N+1.)*RHOA);

 //return (2.*N+1.)*ETA/2./(N+1.)/RHOA;

}

static double B( const double& RHOA, const double& ETA, const int& N ) {

  return ( ETA*ETA-N*(N+1.) )/(2.*(N+1.)*RHOA);

//return ( ETA*ETA-N*(N+1.) )/2./(N+1.)/RHOA;

}
*/


static void COULA1( const double& ETA, double* RHOA, double* G0, double* G0P ) {

  // RHOA = 16, ETA > 15

  *RHOA = 16.;

  double tt[11],tm[18],g[8],g1[8], t0 = *RHOA/(2.*ETA);

    for( int i=0; i<11; i++ ) tt[i] = pow(   t0,i);
    for( int i=0; i<18; i++ ) tm[i] = pow(1.-t0,i);

    g[0] = sqrt(tt[1]*tm[1]) + asin( sqrt(tt[1]) ) - 0.5*M_PI;
    g[1] = 0.25 * log(tt[1]/tm[1]);
    g[2] = -(8.0*tt[2]-12.0*tt[1]+9.0) /(48.0*sqrt(tt[1]*tm[3]));
    g[3] = (8.0*tt[1]-3.0)/(64.0*tt[1]*tm[3]);
    g[4] = ( 2048.0*tt[6]- 9216.0*tt[5]+16128.0*tt[4] -13440.0*tt[3]-12240.0*tt[2]+ 7560.0*tt[1]-1890.0)
         / (92160.0*sqrt(tt[3]*tm[9]));
    g[5] = 3.0*(1024.0*tt[3]-448.0*tt[2]+208.0*tt[1]-39.0)/(8192.0*tt[2]*tm[6]);
    g[6] = -( 262144.0*tt[10]- 1966080.0*tt[9]+6389760.0*tt[8]-11714560.0*tt[7]+13178880.0*tt[6]-9225216.0*tt[5]
           +13520640.0*tt[4] -3588480.0*tt[3]+2487240.0*tt[2] - 873180.0*tt[1]+130977.0)
           /(10321920.0*sqrt(tt[5]*tm[15]));
    g[7] = (1105920.0*tt[5]-55296.0*tt[4]+314624.0*tt[3] -159552.0*tt[2]+45576.0*tt[1]-5697.0)
          /(393216.0*tt[3]*tm[9]);



    g1[0] = sqrt(tm[1]/tt[1]);
    g1[1] = 1.0/(4.0*tt[1]*tm[1]);
    g1[2] = -(8.0*tt[1]-3.0)/(32.0*sqrt(tt[3]*tm[5]));
    g1[3] = 3.0*(8.0*tt[2]-4.0*tt[1]+1.0)/(64.0*tt[2]*tm[4]);
    g1[4] = -(1536.0*tt[3]-704.0*tt[2]+336.0*tt[1]-63.0)/(2048.0*sqrt(tt[5]*tm[11]));
    g1[5] = 3.0*(2560.0*tt[4]-832.0*tt[3]+728.0*tt[2]- 260.0*tt[1]+ 39.0)/(4096.0*tt[3]*tm[7]);
    g1[6] = (-368640.0*tt[5]-30720.0*tt[4]+114944.0*tt[3]- 57792.0*tt[2]+16632.0*tt[1]-  2079.0)
            /(65536.0*sqrt(tt[7]*tm[17]));
    g1[7] = 3.0*(860160.0*tt[6]+196608.0*tt[5]+308480.0*tt[4]-177280.0*tt[3]
            + 73432.0*tt[2]- 17724.0*tt[1] +1899.0)/(131072.0*tt[4]*tm[10]);


    for( int i=0; i<8; i++ ) *G0  += g [i] * pow( -2.*ETA, 1.-i );
    for( int i=0; i<8; i++ ) *G0P += g1[i] * pow( -2.*ETA, 1.-i );

      *G0   = exp( *G0 );
      *G0P *= *G0/(2.*ETA);

    return;

}

static void COULA2( const double& ETA, double* RHOA, double* G0, double* G0P ) {

  // RHOA = 2*ETA, 15 > ETA > 4

  *RHOA = 2.*ETA;

    *G0=1.223404016*pow(ETA,1.0/6.0)
     *(1.0
      +0.04959570165  *pow(ETA,-4.0/3.0)
      -0.008888888889 *pow(ETA,-2.0)
      +0.002455199181 *pow(ETA,-10.0/3.0)
      -0.0009108958061*pow(ETA,-4.0)
      +0.0002534684115*pow(ETA,-16.0/3.0));

    *G0P=-0.7078817734*pow(ETA,-1.0/6.0)
      *(1.0
      -0.1728260369   *pow(ETA,- 2.0/3.0)
      +0.0003174603174*pow(ETA,- 2.0)
      -0.003581214850 *pow(ETA,- 8.0/3.0)
      +0.0003117824680*pow(ETA,- 4.0)
      -0.0009073966427*pow(ETA,-14.0/3.0));

    return;

}

static void COULA3( const double& ETA, double* RHOA, const double& RHO, double* G0, double* G0P ) {

  // ETA < 4

  *RHOA = max(2.*ETA+9.,RHO);

  double S0,T0,SL0,TL0,SS,TS,SL,TL;
  double FN,AN,BN,S1,T1,SL1,TL1,ST0,ST1,W,FAI;

      CONTINUE30:

      S0 = 1.0;
      T0 = 0.0;
      SL0= 0.0;
      TL0= 1.0-ETA/(*RHOA);
      SS = 1.0;
      TS = 0.0;
      SL = 0.0;
      TL = TL0;

    for( int N=1; N<=50; N++ ) {

      FN = double(N);
      AN = (2.0*FN-1.0)/(2.0*FN*(*RHOA))*ETA;
      BN = (ETA*ETA-FN*(FN-1.0))/(2.0*FN*(*RHOA));
      if( AN*AN+BN*BN-1.0 >= 0.0 ) goto CONTINUE42;
      S1 = AN*S0-BN*T0;
      T1 = AN*T0+BN*S0;
      SL1 = AN*SL0-BN*TL0-S1/(*RHOA);
      TL1 = AN*TL0+BN*SL0-T1/(*RHOA);
      ST0 = SL0*SL0+TL0*TL0;
      ST1 = SL1*SL1+TL1*TL1;
      if( ST1/ST0 > 1.0 ) goto CONTINUE42;
      SS = SS+S1;
      TS = TS+T1;
      SL = SL+SL1;
      TL = TL+TL1;
      ST0 = SS*SS+TS*TS;
      ST1 = S1*S1+T1*T1;
      if( ST1/ST0 >= 1.e-16 ) goto CONTINUE40;
      ST0 = SL *SL +TL *TL;
      ST1 = SL1*SL1+TL1*TL1;
      if( ST1/ST0 < 1.e-16 ) goto CONTINUE43;
      CONTINUE40:
      S0=S1;
      T0=T1;
      SL0=SL1;
      TL0=TL1;

    }

      CONTINUE42:

      *RHOA = *RHOA+5.0;
      goto CONTINUE30;

   CONTINUE43:
      W = SS*TL-TS*SL;
      if( fabs(W-1.0) >= 1.e-5 ) goto CONTINUE42;
      FAI = *RHOA-ETA*log(2.0*(*RHOA))+PHASE(ETA,0);
      *G0  = SS*cos(FAI)-TS*sin(FAI);
      *G0P = SL*cos(FAI)-TL*sin(FAI);

  return;

}


static void COULA( const double& ETA, double* RHOA, const double& RHO, double* G0, double* G0P ) {

  *G0 = 0.0;  *G0P = 0.0;

  if( ETA >= 15.0 )              COULA1( ETA, RHOA,      G0, G0P );
  if( ETA < 15.0 && ETA >= 4.0 ) COULA2( ETA, RHOA,      G0, G0P );
  if( ETA < 4.0 )                COULA3( ETA, RHOA, RHO, G0, G0P );

  return;

}




static void COULI( const double& ETA, const double& RHOA, const double& RHO, const double& G0, const double& G0P, double* GD0, double* GD0P ) {

  *GD0  = 0.0;
  *GD0P = 0.0;

  int N; double DELA(0.1),ETA2(2.*ETA),RDEL(RHO-RHOA),H;

    N = fabs(RDEL) < 1. ? 10      : fabs(RDEL)/DELA;
    H = fabs(RDEL) < 1. ? RDEL/10 : RDEL/N;

  double H2,H8,X,Y,Z,G0H,G1H,G2H;

    H2 = H/2.;
    H8 = H/8.;

    X = RHOA;
    Y = G0;
    Z = G0P;

    for( int i=0; i<N; i++ ) {

      G0H=H*(ETA2/X-1.0)*Y;
      X+=H2;
      G1H=H*(ETA2/X-1.)*(Y+H2*Z+H8*G0H);
      X+=H2;
      G2H=H*(ETA2/X-1.)*(Y+H *Z+H2*G1H);
      Y+=H*(Z+(G0H+2.*G1H)/6.);
      Z+=(G0H+4.*G1H+G2H)/6.;

    }

    *GD0  = Y;
    *GD0P = Z;

  return;

}



static void COULL( const double& ETA, const double& RHO, const double& GM0, const double& GM0P, const int& LMAX, double* G, double* GP, double* F, double* FP ) {

  double ETA2 = ETA*ETA;

/*
  if( RHO < 1.e-2 ) {

    cerr << "too small RHO = " << RHO << endl;
    abort();

  }
*/

  for( int L=0; L<=LMAX; L++ ) {

    G[L] = 0.0;  GP[L] = 0.0;
    F[L] = 0.0;  FP[L] = 0.0;

  }
  

  //double GNORM,H0,H1;  int LX,L1;
  double H0,H1;

    G[0]  = GM0;
    G[1]  = ((ETA+1./RHO)*GM0-GM0P)/sqrt(1.+ETA2);
    //GNORM = max( fabs(G[0]),fabs(G[1]) );

    for( int L=2; L<=LMAX; L++ ) {

      H0 = double(L-1);
      H1 = double(L);
      G[L]=H1/sqrt(ETA2+H1*H1)*((H0+H1)*(ETA/(H0*H1)+1./RHO)*G[L-1]
          -sqrt(ETA2+H0*H0)/H0*G[L-2]);

      //if( fabs(G[L]*G[L]/GNORM/GNORM) > 1.e+6 ) { LX = L;  goto CONTINUE11; }

    }

    //LX = 40;

    //CONTINUE11:

    //*LMAX = LX;
    //L1 = (*LMAX) + 10;


  double Y,Y1,Y2,R,T1,T2;

//    Start:

    //LX = L1;
    Y2 = 0.;
    Y1 = 1.e-36;

    for( int L=LMAX+1; L>=1; L-- ) {

      H0 = double(L);
      H1 = double(L+1);
      Y = H0/sqrt(ETA2+H0*H0)*((H0+H1)*(ETA/(H0*H1)+1./RHO)*Y1-sqrt(ETA2+H1*H1)/H1*Y2);
      /*if( L <= *LMAX+1 )*/ F[L-1] = Y;
      Y2 = Y1;
      Y1 = Y;
      
    }

    R = sqrt( 1.+ ETA2 )*( F[0]*G[1]-G[0]*F[1] );

    //for( int L=0; L<=*LMAX; L++ ) cerr << F[L] << endl;

    for( int L=0; L<=LMAX; L++ ) F[L] /= R;


    for( int L=0; L<=LMAX-1; L++ ) {

      H1 = double(L+1);
      T1 = H1/RHO+ETA/H1;
      T2 = sqrt(H1*H1+ETA2)/H1;
      GP[L] = T1*G[L]-T2*G[L+1];
      FP[L] = T1*F[L]-T2*F[L+1];
    //R = FP[L]*G[L]-F[L]*GP[L];

/*
      if( fabs(R-1.) > 1.e-5 ) { 

        L1 += 5;  goto Start;

      }
*/
    }

    //*LMAX -= 1;

  return;

}



static void COULL( const double& ETA, const double& RHO, const int& LMAX, double* G, double* GP, double* F, double* FP ) {

  double RHOA,G0,G0P,GM0,GM0P;

    COULA( ETA, &RHOA,  RHO, &G0, &G0P              );
    COULI( ETA,  RHOA,  RHO,  G0,  G0P, &GM0, &GM0P );
    COULL( ETA, RHO, GM0, GM0P, LMAX, G, GP, F, FP );

  return;

}





// Coulomb scattering phase-shift
/*
static void coulomb_ps_array( const double& eta, const int& lmax, double* ps ) {

  return PHASE( eta, lmax, ps );

}
*/

// Coulomb scattering phase-shift
static double coulomb_ps( const double& eta, const int& l ) {

  return PHASE( eta, l );

}

// Coulomb wf
static void coulomb_wave_array( const double& eta, const double& rho, const int& lmax, double* F, double* F1, double* G, double* G1 ) {

  int n = lmax+2;

  double FF[n],FF1[n],GG[n],GG1[n];

    COULL( eta, rho, lmax+1, GG, GG1, FF, FF1 );

    for( int l=0; l<=lmax; l++ ) {

      F [l] = FF [l];
      F1[l] = FF1[l];
      G [l] = GG [l];
      G1[l] = GG1[l];

    }

  return;

}


static inline bool eq( const double& a, const double& b, const double eps = 1.e-6 ) {

  return ( fabs(a-b)/max(fabs(a),fabs(b)) < eps );

}

// Coulomb wf
void coulomb_wave( const double& eta, const double& rho, const int& l, double* F, double* F1, double* G, double* G1 ) {

  int n = l+1;

  double FF[n],FF1[n],GG[n],GG1[n];

    coulomb_wave_array( eta, rho, l, FF,FF1,GG,GG1 );

    *F  = FF [l];
    *F1 = FF1[l];
    *G  = GG [l];
    *G1 = GG1[l];


    while( true ) {

      n += 5;

      double FF[n],FF1[n],GG[n],GG1[n];

      coulomb_wave_array( eta, rho, n-1, FF,FF1,GG,GG1 );

      //if( eq(*F,FF[l]) && eq(*F1,FF1[l]) && eq(*G,GG[l]) && eq(*G1,GG1[l]) ) break;

      if( eq(*F,FF[l]) && eq(*G,GG[l]) ) break;

      *F  = FF [l];
      *F1 = FF1[l];
      *G  = GG [l];
      *G1 = GG1[l];

    }

    //cerr << n-5 << endl;

    //cerr << *F << "  " << *F1 << "  " << *G << "  " << *G1 << endl;

  return;

}



}
