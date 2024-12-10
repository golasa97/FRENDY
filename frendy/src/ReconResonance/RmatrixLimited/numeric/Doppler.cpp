#include "ReconResonance/RmatrixLimited/numeric/Doppler.h"
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"
#include "ReconResonance/RmatrixLimited/numeric/Constant.h"

namespace Numeric {


// fundamental functions

static inline void Integral( const double& x, double* I ) {

  double xx(x*x);

    I[0] = erfc(x);
    I[1] = 1./sqrt(M_PI)*exp(-1.*xx);
    I[2] = 0.5*I[0]+I[1]*x;
    I[3] = I[1]*(xx+1.);
    I[4] = 0.75*I[0]+I[1]*x*(xx+1.5);

  return;

}

static inline void Integral( const double& x0, const double& x1, double I[2][5] ) {

  Integral( x0, I[0] );
  Integral( x1, I[1] );

  return;

}

static inline void Integral1( const double& x0, const double& x1, Doppler::double5& result ) {

  double I[2][5];

    Integral( x0,x1, I );

    result[0] = ( I[0][0] - I[1][0] );
    result[1] = ( I[0][1] - I[1][1] );
    result[2] = ( I[0][2] - I[1][2] );
    result[3] = ( I[0][3] - I[1][3] );
    result[4] = ( I[0][4] - I[1][4] );

  return;

}

static inline void Integral2( const double& x0, const double& x1, Doppler::double5& result ) {

  double I[2][5];

    Integral( x0,x1, I );

    result[0] =      ( I[0][0] - I[1][0] );
    result[1] = -1.* ( I[0][1] - I[1][1] );
    result[2] =      ( I[0][2] - I[1][2] );
    result[3] = -1.* ( I[0][3] - I[1][3] );
    result[4] =      ( I[0][4] - I[1][4] );

  return;

}


Doppler::double5:: double5(){}
Doppler::double5::~double5(){}

Doppler::Array:: Array(){}
Doppler::Array::~Array(){}


// main class

Doppler:: Doppler(){}
Doppler::~Doppler(){}

void Doppler::Allocate( const unsigned long size ) {

/*
  ary.resize(5);  n = size;

    for( int i=0; i<5; i++ ) ary[i].Allocate(size,size-1);
*/

  ary.resize(size);
  j0 .resize(size);
  j1 .resize(size);

  return;

}


void Doppler::Update1( const double* v, const unsigned long& n, const double& u,
const unsigned long& i0, const unsigned long& i1 ) {
// calculate integrals for the first term
// v  : velocity of the incident particle
// u  : velocity of the target
// i0 : beginning point of v
// i1 : end point of v 

  this->Allocate( i1 -i0 +1 );

  int ii;  double w0,w1, x0,x1;

    for( unsigned long i=i0; i<=i1; i++ ) {

      ii = i-i0;  // index for the matrix

      j0[ii] = i;    // j-min
      j1[ii] = i-1;  // j-max

      for( unsigned long j=i; j>0; j-- ) {  // go backward

        w0 = v[j-1];  x0 = ( w0 -v[i] )/u;
        w1 = v[j  ];  x1 = ( w1 -v[i] )/u;

        if( -4. < x1 && x0 < 4. ) { 

          j0[ii] = j-1;

          Integral1( x0,x1, ary[ii].push_front() );  // <--- new

          continue;

        } break;

      }

      for( unsigned long j=i; j<n; j++ ) {  // go forward

        w0 = v[j  ];  x0 = ( w0 -v[i] )/u;
        w1 = v[j+1];  x1 = ( w1 -v[i] )/u;

        if( -4. < x1 && x0 < 4. ) { 

          j1[ii] = j;

          Integral1( x0,x1, ary[ii].push_back() );  // <--- new

          continue;

        } break;

      }

      //cerr << ary[ii].size() << endl;
      //if( (j1[ii]-j0[ii]+1) != ary[ii].size() ) cerr << j1[ii]-j0[ii]+1 << "  " << ary[ii].size() << endl;

    }

  return;

}


void Doppler::Update2( const double* v, const unsigned long& n, const double& u,
const unsigned long& i0, const unsigned long& i1 ) {
// calculate integrals for the second term
// v  : velocity of the incident particle
// u  : velocity of the target
// i0 : beginning point of v
// i1 : end point of v 

  this->Allocate( i1 -i0 +1 );

  int ii;  double w0,w1, x0,x1;

    for( unsigned long i=i0; i<=i1; i++ ) {

      ii = i-i0;  // index for the matrix

      j0[ii] = i;    // j-min
      j1[ii] = i-1;  // j-max

      for( unsigned long j=i; j>0; j-- ) {  // go backward

        w0 = v[j-1];  x0 = ( w0 +v[i] )/u;
        w1 = v[j  ];  x1 = ( w1 +v[i] )/u;

        if( 0.0 <= w0 && w1 < 4.*u ) { 

          j0[ii] = j-1;

          Integral2( x0,x1, ary[ii].push_front() );  // <--- new

          continue;

        } break;

      }

      for( unsigned long j=i; j<n; j++ ) {  // go forward

        w0 = v[j  ];  x0 = ( w0 +v[i] )/u;
        w1 = v[j+1];  x1 = ( w1 +v[i] )/u;

        if( 0.0 <= w0 && w1 < 4.*u ) { 

          j1[ii] = j;

          Integral2( x0,x1, ary[ii].push_back() );  // <--- new

          continue;

        } break;

      }

      //if( (j1[ii]-j0[ii]+1) != ary[ii].size() ) cerr << j1[ii]-j0[ii]+1 << "  " << ary[ii].size() << endl;

    }

  return;

}


}
