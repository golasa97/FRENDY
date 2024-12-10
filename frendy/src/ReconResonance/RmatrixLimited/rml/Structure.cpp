#include "ReconResonance/RmatrixLimited/rml/Structure.h"
#include "ReconResonance/RmatrixLimited/numeric/Coupling.h"
#include "ReconResonance/RmatrixLimited/numeric/Legendre.h"
#include "ReconResonance/RmatrixLimited/numeric/Constant.h"

#define pm(l) ( (l)%2 == 0 ? 1 : -1 )

extern "C" void zsytrf_( char* uplo, int* n, complex<double>* a, int* lda, int* ipiv, complex<double>* work, int* lwork, int* info );
extern "C" void zsytri_( char* uplo, int* n, complex<double>* a, int* lda, int* ipiv, complex<double>* work, int* info );

//extern "C" void zsptrf_( char* uplo, int* n, complex<double>* a, int* ipiv, int* info );
//extern "C" void zsptri_( char* uplo, int* n, complex<double>* a, int* ipiv, complex<double>* work, int* info );

namespace RML {

Structure:: Structure() : mass(0.), opt(true) {}
Structure:: Structure( const double J, const int pi ) { this->Set(J,pi);  mass = 0.0; }
Structure::~Structure() {}

/*! @brief Set total J^pi
@param[in] J  : Spin
@param[in] pi : Parity (positive/negative)
*/
Structure* Structure::Set( const double J, const int pi ) {

  this->Group::Set( J,pi );

  /*spin = J;  parity = pi;*/  alpha.clear();  ch.clear();  se.clear();  return this;
  
}




/*! @brief Set partition, then store explicit channels
@param[in] a   : Particle which defines the partition
@param[in] A   : Nucleus which defines the partition
*/
Structure* Structure::PushBack( const Particle& a, const Nucleus& b ) {

  alpha.push_back( TwoBody(a,b) );

  double I1  = a.Spin  (), I2  = b.Spin  ();
  int    pi1 = a.Parity(), pi2 = b.Parity();

  // set channels (a,J,l,s)

  double s = fabs(I1-I2);

    while( le( s, (I1+I2) ) ) {

      int l = (int) fabs(this->J()-s);

      while( l <= (int) (this->J()+s) ) {

        if( this->pi() == pi1 * pi2 * ( ( l%2 == 0 ) ? 1:-1 ) ) {

          ch.push_back( Coulomb( Channel( a,b, this->J(),l,s ) ) );

        }

        l++;

      }

      s += 1.0;

    }

  return this;

}

/*! @brief Set partition, then store explicit channels
@param[in] a   : Particle which defines the partition
@param[in] A   : Nucleus which defines the partition
@param[in] S_a : Separation energy (to remove particle "a" from nucleus "a+A" )
*/
Structure* Structure::PushBack( const Particle& a, const Nucleus& A, const double S_a ) {

  se.push_back( make_pair( TwoBody(a,A), S_a ) );

  return this->PushBack( a,A );

}



Structure* Structure::PushBack( const TwoBody& o ) {
// set partition and explicit channels

  alpha.push_back( o );

  double I1  = o.Particle::Spin  ();
  double I2  = o.Nucleus ::Spin  ();
  int    pi1 = o.Particle::Parity();
  int    pi2 = o.Nucleus ::Parity();

  // set channels (a,J,l,s)

  double s = fabs(I1-I2);

    while( le( s, (I1+I2) ) ) {

      int l = (int) fabs(this->J()-s);

      while( l <= (int) (this->J()+s) ) {

        if( this->pi() == pi1 * pi2 * ( ( l%2 == 0 ) ? 1:-1 ) ) {

          ch.push_back( Coulomb( Channel( o, this->J(),l,s ) ) );

        }

        l++;

      }

      s += 1.0;

    }

  return this;

}

Structure* Structure::PushBack( const TwoBody& o, const double separation_energy ) {

  se.push_back( make_pair( o, separation_energy ) );

  return this->PushBack( o );

}


double Structure::Ba( const TwoBody& inc ) const {
// Binding energy

  for( int i=0; i<static_cast<int>(se.size()); i++ )

    if( se[i].first == inc ) return se[i].second;

  return ( inc.Particle::Mass() + inc.Nucleus::Mass() -mass ) *Constant::amu + inc.Nucleus::Energy();

}

double Structure::Qval( const TwoBody& inc, const TwoBody& out ) const {

  //cerr << this->Ba(inc) << "  " << this->Ba(out) << endl;

  return this->Ba(inc) - this->Ba(out);

}



int Structure::index( const Channel& c ) const {

  for( int i=0; i<nch; i++ ) if( ch[i] == c ) return i;

  cerr << "!! Structure::index -> not found channel = " << c << endl;  abort();

}


Structure* Structure::SetOption( const bool option ) {
// option : true  - calculate A-matrix (must be true for the angular distribution)
//        : false - calculate X-matrix (computation is fast, only for cross-sections)

  opt = option;  return this;

}



Structure* Structure::Configure( const Boundary* condition, const bool option ) {
// configure this system

  opt = option;

  nch = ch.size();  nlev = this->Group::size();  npart = alpha.size();

  for( int c=0; c<nch; c++ ) {

    ch[c].Rc() = condition->Rc( ch[c] ).Value();
    ch[c].Rh() = condition->Rh( ch[c] ).Value();
    ch[c].Bc() = condition->Bc( ch[c] ).Value();

    ch[c].do_Shift() = condition->do_Shift( ch[c] );
    ch[c].do_Penet() = condition->do_Penet( ch[c] );

  }

  lev.resize(nlev);  gam.resize(nlev*nch);

    for( int l=0; l<nlev; l++ ) {

      lev[l].eigenvalue = this->E    (l).Value();
      lev[l].Gam        = this->Gamma(l).Value();
      lev[l].ex_opt     = this->at   (l);

      for( int c=0; c<nch; c++ )

        gam[ l*nch + c ] = this->Group::gamma(l,ch[c]).Value();

    }

    permu1.resize(2*nlev);
    M1    .resize(nlev*nlev);
    WORK1 .resize(nlev*nlev);

    permu2.resize(2*nch);
    M2    .resize(nch*nch);
    WORK2 .resize(nch*nch);

    R    .resize(nch*nch);
    Yinv .resize(nch*nch);

  return this;

}


/*
void Structure::Exclude( const int ilev ) {

  Gam[ilev] = 0.0;

  for( int c=0; c<nch; c++ )  gam[ ilev*nch + c ] = 0.0;

  return;

}
*/


/*! Update channel wave-function */
Structure* Structure::Update( const vector<double>& qval, const double ecm ) {

  for( int i=0; i<nch; i++ )

    for( int ii=0; ii<npart; ii++ )

      if( ch[i] == alpha[ii] ) ch[i].Update( ecm+qval[ii] );

  return this;

}



/*! Reduced width amplitude
@param[in] lambda : index for the level
@param[in] c      : index for the channel
*/
const double& Structure::gamma( const int& lambda, const int& c ) const { return gam[ lambda*nch + c ]; }
      double& Structure::gamma( const int& lambda, const int& c )       { return gam[ lambda*nch + c ]; }

/*! L = S-B+iP
@param[in] c      : index for the channel
*/
const complex<double>& Structure::L( const int& c ) const { return ch[c].L0(); }
      complex<double>& Structure::L( const int& c )       { return ch[c].L0(); }


static double delta( const int& i, const int& j ) { return ( i==j ) ? 1.:0.; }



/*! @brief Calculate A or X matrix (with exclusive option for the incident particle)
@param[in] a    : incident particle
@param[in] qval : reaction Q-value
@param[in] ba   : binding energy for incident channel
*/
Structure* Structure::Solve( const TwoBody& inc, const double ecm, const double ba ) {

  vector<double> qval( npart );

    //for( int i=0; i<npart; i++ ) qval[i] = inc.Qval( alpha[i] );

    for( int i=0; i<npart; i++ ) qval[i] = this->Qval( inc, alpha[i] );

    //for( int i=0; i<npart; i++ ) cerr << qval[i] << endl;  abort();

  return ( opt ) ? this->Solve1( inc, qval, ecm, ba )
                 : this->Solve2( inc, qval, ecm, ba );

}

/*! @brief Calculate A or X matrix
@param[in] qval : reaction Q-value
@param[in] ba   : binding energy for incident channel
*/
Structure* Structure::Solve( const vector<double>& qval, const double ecm, const double ba ){

  return ( opt ) ? this->Solve1( qval, ecm, ba )
                 : this->Solve2( qval, ecm, ba );

}


/*! @brief Calculate level matrix A (with exclusive option for the incident particle)
@param[in] a    : incident particle
@param[in] qval : reaction Q-value
@param[in] ba   : binding energy for incident channel
*/
Structure* Structure::Solve1( const Particle& a, const vector<double>& qval, const double ecm, const double ba ) {

  this->Update( qval, ecm );

  // level matrix

  if( this->Group::empty() ) return this;

  bool exclude1,exclude2;

  for( int i=0; i<nlev; i++ ) {

    exclude1 = lev[i].ex_opt.Find( a );  // exclusive level

    complex<double> E( lev[i].eigenvalue, (exclude1) ? 0. : -0.5 * lev[i].Gam );  // Reich-Moore approxiamtion

    for( int j=i; j<nlev; j++ ) {

      exclude2 = ( lev[j].ex_opt.Find( a ) || exclude1 );  // exclusive level

      this->A(i,j) = (exclude2) ? 0. : -1.*this->xi( i,j );

      if( i==j ) this->A(i,j) += E - (ecm+ba);

    }

  }

  // invert

  return this->Solve1();

}





/*! @brief Calculate level matrix A
@param[in] qval : reaction Q-value
@param[in] ba   : binding energy for incident channel
*/
Structure* Structure::Solve1( const vector<double>& qval, const double ecm, const double ba ) {

  this->Update( qval, ecm );

  // level matrix

  if( this->Group::empty() ) return this;

  for( int i=0; i<nlev; i++ ) {

    complex<double> E( lev[i].eigenvalue, -0.5 * lev[i].Gam );  // Reich-Moore approxiamtion

    for( int j=i; j<nlev; j++ ) {

      this->A(i,j) = -1. * this->xi( i,j );

      if( i==j ) this->A(i,j) += E - (ecm+ba);

        //this->A(i,j) = z;

    }

  }

  // invert

  return this->Solve1();

}


/*! @brief Calculate channel matrix X (with exclusive option for the incident particle)
@param[in] a    : incident particle
@param[in] qval : reaction Q-value
@param[in] ba   : binding energy for incident channel
*/
Structure* Structure::Solve2( const Particle& a, const vector<double>& qval, const double ecm, const double ba ){

  this->Update( qval, ecm );

  bool exclude;

    for( int i=0; i<nch; i++ ) for( int j=i; j<nch; j++ ) R[i*nch+j] = 0.;

    for( int l=0; l<nlev; l++ ) {

      exclude = lev[l].ex_opt.Find( a );  // exclusive level

      complex<double> fac = 1./ complex<double>( lev[l].eigenvalue-(ecm+ba), (exclude) ? 0. : -0.5 * lev[l].Gam );

      for( int i=0; i<nch; i++ ) {

        if( eq( this->gamma(l,i), 0.0 ) ) continue;

        for( int j=i; j<nch; j++ )

          R[i*nch+j] +=  (exclude) ? 0. : this->gamma(l,i) * this->gamma(l,j) *fac;

      }

    }

    // (L^-1-R)

    for( int i=0; i<nch; i++ )

      for( int j=i; j<nch; j++ ) Yinv[i*nch+j] = delta(i,j)/this->L(i) - R[i*nch+j];

  // invert matrix : (L^-1-R)^-1

  return this->Solve2();

}





/*! @brief Calculate channel matrix X
@param[in] qval : reaction Q-value
@param[in] ba   : binding energy for incident channel
*/
Structure* Structure::Solve2( const vector<double>& qval, const double ecm, const double ba ){

  this->Update( qval, ecm );

    for( int i=0; i<nch; i++ ) for( int j=i; j<nch; j++ ) R[i*nch+j] = 0.;

    for( int l=0; l<nlev; l++ ) {

      complex<double> fac = 1./ complex<double>( lev[l].eigenvalue-(ecm+ba), -0.5 * lev[l].Gam );

      for( int i=0; i<nch; i++ ) {

        if( eq( this->gamma(l,i), 0.0 ) ) continue;

        for( int j=i; j<nch; j++ )

          R[i*nch+j] +=  this->gamma(l,i) * this->gamma(l,j) * fac;

      }

    }

    // (L^-1-R)
/*
    for( int i=0; i<nch; i++ )

      for( int j=i; j<nch; j++ ) Yinv[i*nch+j] = delta(i,j)/this->L(i) - R[i*nch+j];
*/
    for( int i=0; i<nch; i++ )

      for( int j=i; j<nch; j++ ) {

        Yinv[i*nch+j] = ( i==j ) ? 1./this->L(i) - R[i*nch+j] : -1.* R[i*nch+j];

        //cerr << i << "  " << j << "  " << Yinv[i*nch+j] << "  " << this->L(i) << "  " << R[i*nch+j] << endl;

      }

  // invert matrix : (L^-1-R)^-1

  return this->Solve2();

}


/*! @brief Calculate level matrix A */
Structure* Structure::Solve1() {

  // invert

  char uplo = 'L';  int LWORK(100*nlev), INFO;

  //zsytrf_( &uplo, &nlev, &*M1.begin(), &nlev, &*permu1.begin(), &*WORK1.begin(), &LWORK, &INFO );
  //zsytri_( &uplo, &nlev, &*M1.begin(), &nlev, &*permu1.begin(), &*WORK1.begin(),         &INFO );

  zsytrf_( &uplo, &nlev, M1.data(), &nlev, permu1.data(), WORK1.data(), &LWORK, &INFO );
  zsytri_( &uplo, &nlev, M1.data(), &nlev, permu1.data(), WORK1.data(),         &INFO );

  //zsptrf_( &uplo, &nlev, M1.data(), permu1.data(),               &INFO );
  //zsptri_( &uplo, &nlev, M1.data(), permu1.data(), WORK1.data(), &INFO );

  for( int i=0; i<nlev; i++ )

    for( int j=i; j<nlev; j++ ) this->A(j,i) = this->A(i,j);

  return this;

}

/*! @brief Calculate channel matrix X */
Structure* Structure::Solve2() {

  // invert matrix : (L^-1-R)^-1

  char uplo = 'L';  int LWORK(100*nch), INFO;

    //zsytrf_( &uplo, &nch, &Yinv[0], &nch, &permu2[0], &WORK2[0], &LWORK, &INFO );
    //zsytri_( &uplo, &nch, &Yinv[0], &nch, &permu2[0], &WORK2[0],         &INFO );

    zsytrf_( &uplo, &nch, Yinv.data(), &nch, permu2.data(), WORK2.data(), &LWORK, &INFO );
    zsytri_( &uplo, &nch, Yinv.data(), &nch, permu2.data(), WORK2.data(),         &INFO );

    //zsytrf_( &uplo, &nch, &*M2.begin(), &nch, &*permu2.begin(), &*WORK2.begin(), &LWORK, &INFO );
    //zsytri_( &uplo, &nch, &*M2.begin(), &nch, &*permu2.begin(), &*WORK2.begin(),         &INFO );

    // symmetric matrix

    for( int i=0; i<nch; i++ )

      for( int j=i; j<nch; j++ ) { 

        Yinv[j*nch+i] = Yinv[i*nch+j];
        R   [j*nch+i] = R   [i*nch+j];

      }

    // M2 = 0.0

    for( int i=0; i<nch; i++ )

      for( int j=0; j<nch; j++ ) M2[i*nch+j] = complex<double>(0.,0.);


    // M2 = Yinv * R

    for( int i=0; i<nch; i++ )

      for( int j=0; j<nch; j++ )

        for( int k=0; k<nch; k++ ) M2[i*nch+j] += Yinv[i*nch+k] * R[k*nch+j];

    // M2 = P_1^1/2 * L^-1 * M2

    for( int i=0; i<nch; i++ ) {

      complex<double> L1 = this->L(i);  double P1 = imag(L1);

      for( int j=0; j<nch; j++ ) M2[i*nch+j] *= sqrt(P1)/L1;

    }

    // M2 = M2 * P_2^1/2

    for( int j=0; j<nch; j++ ) {

      complex<double> L2 = this->L(j);  double P2 = imag(L2);

      for( int i=0; i<nch; i++ ) M2[i*nch+j] *= sqrt(P2);

    }

  return this;

}






complex<double> Structure::xi( const int& i, const int& j ) const {
// off-diagonal element of the inverse level-matrix (A^-1)
// (i,j) : indices for the combination of the levels

  complex<double> sum(0.,0.);

    for( int k=0; k<nch; k++ )

      sum += gamma(i,k) * gamma(j,k) * ch[k].L0();

  return sum;

}


complex<double> Structure::T( const Channel& c1 ) const {
// T-matrix element for elastic channel c1

  return this->T( this->index(c1) );

  //return exp( complex<double>( 0.0, 2.*c1.omega() ) ) - U( c1 );

}


complex<double> Structure::T( const Channel& c1, const Channel& c2 ) const {
// T-matrix element
// c1 : incident channel
// c2 : outgoing channel

  return ( c1==c2 ) ? this->T( c1 ) : -1.0 * U( c1,c2 );

}


complex<double> Structure::T( const int& i ) const {
// T-matrix element for elastic channel

  return exp( complex<double>( 0.0, 2.*ch[i].omega() ) ) - U( i );

}

complex<double> Structure::T( const int& i, const int& j ) const {
// T-matrix element
// i : index for incident channel
// j : index for outgoing channel

  return ( i==j ) ? this->T( i ) : -1.0 * U( i,j );

}


complex<double> Structure::U( const Channel& c1 ) const {
// collision matrix (S-matrix) element for elastic channel c1

  return this->U( this->index(c1) );

}



complex<double> Structure::U( const Channel& c1, const Channel& c2 ) const {
// collision matrix (S-matrix) element
// ch1 : incident channel
// ch2 : outgoing channel

  return this->U( this->index(c1), this->index(c2) );

}

/*
complex<double> Structure::W( const Coulomb& ch1, const Coulomb& ch2 ) const {

  int n = this->Group::size();

  complex<double> A,sum(0.,0.);

    for( int i=0; i<n; i++ ) {

      for( int j=0; j<n; j++ ) {

        A = complex<double>( R(i,j), I(i,j) );  // Level matrix

        double gam1 = this->Group::at(i).gamma( ch1 ).Value();
        double gam2 = this->Group::at(j).gamma( ch2 ).Value();

        sum += gam1*gam2 *A;

      }

    }

  return sum;

}
*/



complex<double> Structure::U( const int& i ) const {
// collision matrix (S-matrix) element for elastic channel

  complex<double> W(0.,0.);  double gam1,gam2;

    for( int l1=0; l1<nlev; l1++ ) {  // off-diagonal

      if( lev[l1].ex_opt.Find( ch[i] ) ) continue;  // exclusive level

      gam1 = gamma(l1,i);

      if( eq(gam1,0.0) ) continue;

      for( int l2=l1+1; l2<nlev; l2++ ) {

        if( lev[l2].ex_opt.Find( ch[i] ) ) continue;  // exclusive level

        gam2 = gamma(l2,i);

          W += gam1*gam2 * this->A(l1,l2);

      }

    }  W *= 2.0;

    for( int l=0; l<nlev; l++ ) {  // diagonal

      if( lev[l].ex_opt.Find( ch[i] ) ) continue;  // exclusive level

      gam1 = gamma(l,i);

        W += gam1*gam1 * this->A(l,l);

    }

    //if( ch1 == ch2 ) W += this->Rinf( ch1, ecm ) / ( 1. - this->Rinf( ch1, ecm ) * ch1.L0() );

    //cerr << ch1.P() << "  " << ch2.P() << endl;

    W *= complex<double>( 0.0, 2.0 ) * ch[i].P();

    W += 1.;

    double omega = ch[i].omega() - ch[i].phi();

//cerr << ch[i].phi() << endl; abort();

    //if( ch1.ZZ() > 0 ) omega1 = ch1.omega();  // hard-sphere is ignored
    //if( ch2.ZZ() > 0 ) omega2 = ch2.omega();  // hard-sphere is ignored

    //double omega1 = -1.0* ch1.phi();
    //double omega2 = -1.0* ch2.phi();

    W *= exp( complex<double>( 0.0, 2.*omega ) );

    //cout << ch1 << "  " << ch2 << "  " << W << endl;

  return W;

}



complex<double> Structure::U( const int& i, const int& j ) const {
// collision matrix (S-matrix) element
// i : index for incident channel
// j : index outgoing channel

  if( i==j ) return this->U( i );

  complex<double> W(0.,0.);  double gam1,gam2;

    for( int l1=0; l1<nlev; l1++ ) {

      if( lev[l1].ex_opt.Find( ch[i] ) ) continue;  // exclusive level

      gam1 = gamma(l1,i);

      if( eq(gam1,0.0) ) continue;

      for( int l2=0; l2<nlev; l2++ ) {

        if( lev[l2].ex_opt.Find( ch[j] ) ) continue;  // exclusive level

        gam2 = gamma(l2,j);

	//gam1 /= ( 1. - this->Rinf( ch1, ecm ) * ch1.L0() );
	//gam2 /= ( 1. - this->Rinf( ch2, ecm ) * ch2.L0() );

        W += gam1*gam2 * this->A(l1,l2);

      }

    }

    W *= complex<double>( 0.0, 2.0 ) * sqrt( ch[i].P() * ch[j].P() );

    double omega1 = ch[i].omega() - ch[i].phi();
    double omega2 = ch[j].omega() - ch[j].phi();

/*
    cerr << "W = " << W << endl;

    cerr << omega1 << endl;
    cerr << omega2 << endl;
    abort();
*/  
    W *= exp( complex<double>( 0.0, omega1 + omega2 ) );

  return W;

}



double Structure::sigma( const TwoBody& inc, const double elab ) const {
// total cross section

  return ( opt ) ? this->sigma1( inc, elab )
                 : this->sigma2( inc, elab );

}

double Structure::sigma1( const TwoBody& inc, const double elab ) const {
// total cross section

  double sigma = 0.0, ecm = inc.Ecm(elab);

    for( int i=0; i<nch; i++ )

      if( ch[i] == inc ) sigma += this->T(i).real();

  return 2.* sigma * inc.g( this->J() ) * M_PI /inc.wk2( ecm ) /100.;

}

double Structure::sigma2( const TwoBody& inc, const double elab ) const {
// total cross section (use X-matrix)

  double sigma = 0.0, ecm = inc.Ecm(elab);  Coulomb c1;  double phi;  complex<double> X;

    for( int i=0; i<nch; i++ ) {

      c1 = ch[i];  if( c1 == inc ) {

        phi = c1.phi();  X = this->X(i,i);

        sigma += pow( sin(phi), 2. ) + imag(X)*cos(2.*phi) - real(X)*sin(2.*phi);

      }

    }

  return 4.* sigma * inc.g( this->J() ) * M_PI / ( inc.wk2( ecm ) *100. );

}




double Structure::sigma( const TwoBody& inc, const double elab, const TwoBody& out ) const {
// reaction cross section

  return ( opt ) ? this->sigma1( inc, elab, out )
                 : this->sigma2( inc, elab, out );

}


double Structure::sigma1( const TwoBody& inc, const double elab, const TwoBody& out ) const {
// reaction cross section

  //if( out == NULL ) return this->sigma( inc, elab );

  if( out.Particle::ZA() == 0 ) return this->sigma_c( inc, elab );

  double sigma = 0.0, ecm = inc.Ecm(elab);

    for( int i=0; i<nch; i++ ) if( ch[i] == inc )

      for( int j=0; j<nch; j++ ) if( ch[j] == out )

        sigma += norm( this->T( i,j ) );

  return sigma * inc.g( this->J() ) * M_PI /inc.wk2( ecm ) /100.;

}


double Structure::sigma2( const TwoBody& inc, const double elab, const TwoBody& out ) const {
// reaction cross section (use X-matrix)

  //if( out == NULL ) return this->sigma( inc, elab );

  double sigma = 0.0, ecm = inc.Ecm(elab);

  if( out.Particle::ZA() == 0 ) return this->sigma_c( inc, elab );

    for( int i=0; i<nch; i++ ) {

      if( ch[i] == inc )

        for( int j=0; j<nch; j++ )

          if( ch[j] == out ) sigma += norm( this->X(i,j) );

    }

    if( inc != out ) return 4.*sigma * inc.g( this->J() ) * M_PI / ( inc.wk2( ecm ) *100. );

  // elastic

  Coulomb c1;  double phi;  complex<double> X;

    for( int i=0; i<nch; i++ ) {

      c1 = ch[i];  if( c1 == inc ) {

        phi = c1.phi();  X = this->X(i,i);

        sigma += pow( sin(phi), 2. ) * ( 1.-2.*imag(X) ) - real(X)*sin(2.*phi);

      }

    }

  return 4.*sigma * inc.g( this->J() ) * M_PI / ( inc.wk2( ecm ) *100. );

}



double Structure::sigma_c( const TwoBody& inc, const double elab ) const {
// capture cross-section with Reich-Moore approximation

  return ( opt ) ? this->sigma1_c( inc, elab )
                 : this->sigma2_c( inc, elab );

}


double Structure::sigma1_c( const TwoBody& inc, const double elab ) const {
// capture cross-section with Reich-Moore approximation

  double sigma = 0.0;  // total reation

    for( int i=0; i<npart; i++ ) sigma += this->sigma( inc, elab, alpha[i] );

  return this->sigma( inc, elab ) - sigma;

}


double Structure::sigma2_c( const TwoBody& inc, const double elab ) const {
// capture cross-section with Reich-Moore approximation

  double sigma = 0.0;  double ecm = inc.Ecm(elab);

    for( int i=0; i<nch; i++ ) {

      if( ch[i] == inc ) {

        sigma += imag( this->X(i,i) );

        for( int j=0; j<nch; j++ ) sigma -= norm( this->X(i,j) );

      }

    }

  return 4.*sigma * inc.g( this->J() ) * M_PI /inc.wk2( ecm ) /100.;

}




void Structure::Get_sigma_array( const TwoBody& inc, const double elab, double* result ) const {
// cross-section (barn)
// result[0] - total
// result[*] - reactions

  result[0] = this->sigma( inc, elab );

    for( int i=0; i<npart; i++ ) result[i+1] += this->sigma( inc, elab, alpha[i] );

  return;

}







complex<double> Structure::A( const TwoBody& inc, const double s1, const double nu1,
                             const TwoBody& out, const double s2, const double nu2, const double cosangle ) const {
// calculate amplitude
// see Lane-Thomas,VIII,eq(2.3)
// s1,s2  : channel spin 
// nu1,n2 : channel spin conponent

  //cerr << elab << endl;

  complex<double> T,A(0.,0.);  int l1,l2;  double J = this->J();

    for( int i=0; i<nch; i++ ) { // l1

      if( ch[i] != inc || ne( ch[i].s(), s1 ) ) continue;

      l1 = ch[i].l();

      for( int j=0; j<nch; j++ ) { // l2

        if( ch[j] != out || ne( ch[j].s(), s2 ) ) continue;

        l2 = ch[j].l();

        T = this->T( i,j );

        for( double M=-J; M<=J; M+= 1.0 ) {  // M : component of J

          for( int m2=-l2; m2<=l2; m2++ ) {

          //double Ylm = pm( (m2+abs(m2))/2 ) * gsl_sf_legendre_sphPlm( l2,abs(m2), cosangle );  // Ylm
            double Ylm = pm( (m2+abs(m2))/2 ) * Legendre_PLM( l2,abs(m2), cosangle );  // Ylm

            double C1 = C( s1,l1,nu1, 0, J,M );
            double C2 = C( s2,l2,nu2,m2, J,M );

            A += sqrt(2.*l1+1.) * C1*C2 * T * Ylm;
 
          }

        }

      }

    }

  return A;

}



double Structure::B( const TwoBody& inc, const double s1, const TwoBody& out, const double s2, const int L, const Structure* o ) const {
// RESCAL

  double J1 = this->J (), J2 = o->J ();
  int    P1 = this->pi(), P2 = o->pi();

  double B = 0.0;  double Z1,Z2;  complex<double> T1,T2;  int l11,l12,l21,l22;

    // first J^pi group

    for( int i1=0; i1<nch; i1++ ) { // l1

      if( ch[i1] != inc || ne( ch[i1].s(), s1 ) ) continue;

      l11 = ch[i1].l();

      for( int i2=0; i2<nch; i2++ ) { // l1'

        if( ch[i2] != out || ne( ch[i2].s(), s2 ) ) continue;

        l12 = ch[i2].l();

        T1 = this->T( i1,i2 );

          // second J^pi group

          if( ! ( P1 == P2 * ( ( L%2==0 ) ? 1:-1 ) ) ) continue;

          for( int j1=0; j1<o->nch; j1++ ) { // l2

            if( o->ch[j1] != inc || ne( o->ch[j1].s(), s1 ) ) continue;

            l21 = o->ch[j1].l();

            if( l21 < abs(L-l11) ) continue;
            if( l21 > abs(L+l11) ) continue;

            for( int j2=0; j2<o->nch; j2++ ) { // l2'

              if( o->ch[j2] != out || ne( o->ch[j2].s(), s2 ) ) continue;

              l22 = o->ch[j2].l();

              if( l22 < abs(L-l12) ) continue;
              if( l22 > abs(L+l12) ) continue;

              T2 = o->T( j1,j2 );

              Z1 = Z( l11,J1,l21,J2, s1,L );
              Z2 = Z( l12,J1,l22,J2, s2,L );

              B += Z1*Z2 *real( T1*conj(T2) );

            }

          }

      }

    }

  return B;

}





complex<double> Structure::NI( const TwoBody& inc, const double s, const double elab, const int l ) const {
// Coulomb-nuclear interference term for charged particle
// complex coefficients for expanding the trace of the nuclear scattering amplitude matrix (see ENDF manual)
// to be used for FILE6, LAW=5, LTP=1


  return this->T( Channel( inc, this->J(), l, s ) );

/*
  Coulomb c1;

    double J = this->J ();
    int    P = this->pi();

    int lmin = (int) fabs(J-s);
    int lmax = (int)     (J+s);

    if( ! ( lmin <= l && l <= lmax ) ) return 0.0;

    //if( ! c1.Set( inc,J,l,s )->Update( inc, inc.Ecm(elab), bc, P ) ) return 0.0;

    if( ! c1.Set( inc,J,l,s )->Update( inc.Ecm(elab), bc, P ) ) return 0.0;

  return this->T( c1, inc.Ecm(elab) );
*/
}


double Structure::NI( const TwoBody& inc, const double s, const double elab, const double cosangle ) const {
// Coulomb-nuclear interference term for charged particle
// elastic scattering differential cross-section
// note : T-matrix should be conjugated (R.E.Azuma2010,PRC81,045805)
// s : channel spin

  double sum(0.0);  complex<double> NI,I(0.,1.),T,W;  Coulomb c1;

    for( int i=0; i<nch; i++ ) {

      if( ch[i] != inc || ne( ch[i].s(), s ) ) continue;

      T = this->T(i);

    //W = I * conj(T) * inc.C( elab, cosangle ) * gsl_sf_legendre_Pl( ch[i].l(), cosangle );
      W = I * conj(T) * inc.C( elab, cosangle ) * Legendre_PL( ch[i].l(), cosangle );

      sum += 2.*real(W);

    }

  return sum/sqrt(4.*M_PI);



/*
  double J = this->J ();
  int    P = this->pi();

  int lmin = (int) fabs(J-s);
  int lmax = (int)     (J+s);

    for( int l=lmin; l<=lmax; l++ ) {

      if( ! c1.Set( inc,J,l,s )->Update( inc.Ecm(elab), bc, P ) ) continue;

      T = this->T( c1, inc.Ecm(elab) );

    //W = I * conj(T) * inc.C( elab, cosangle ) * gsl_sf_legendre_Pl( l, cosangle );
      W = I * conj(T) * inc.C( elab, cosangle ) * Legendre_PL( l, cosangle );

      sum += 2.*real(W);

    }

  return sum/sqrt(4.*M_PI);
*/

}




void Structure::Print( ostream& os ) const {

  os.setf(ios::fixed, ios::floatfield);

  os << "... J^pi= " << setw(4) << setprecision(1) << this->J() << ( this->pi()>=0 ? '+' : '-' ) << " ..." << endl;

  this->Group::Print( os );

  //os << endl;

  return;

}


void Structure::PrintLatex( ostream& os ) const {

  os << "------------" << endl;
  os << " J^p = ";
  os << setw(3) << setprecision(1) << this->J();
  os << setw(1) << ( ( this->pi() < 0 ) ? '-' : '+' ) << endl;
  os << "------------" << endl;

  os.setf(ios::fixed, ios::floatfield);

  Group lev = *this;

  os << setprecision(2) << right;

  for( int i=0; i<lev.size(); i++ ) {

    os << setw(12) << lev[i].E().Value() << " (" << setw(6) << lev[i].E().ErrorPercent() << "%)  ";

    //os << setw(4) << setprecision(1) << lev[i].J();
    //os << setw(1) << ( ( lev[i].pi() < 0 ) ? '-' : '+' ) << "  ";

    os << setprecision(2) << right;

    for( int ii=0; ii<static_cast<int>(ch.size()); ii++ ) {

      bool x = true;

      for( int iii=0; iii<lev[i].size(); iii++ ) {

        x = ( lev[i][iii] == ch[ii] );

        if( x ) {

          os << setw(8) << lev[i][iii].gamma().Value() << " (";
          os << setw(6) << lev[i][iii].gamma().ErrorPercent() << "%)  ";

          break;

        }

      }

      if( ! x ) os << setw(16) << "" << "    ";

    }

    os << setw(8) << lev[i].Gamma().Value() << "  (";
    os << setw(6) << lev[i].Gamma().ErrorPercent() << "%)";

    os << endl;

  }


}


ostream& operator<<( ostream& os, const Structure& o ) {

  o.Print( os );  return os;

}


}
