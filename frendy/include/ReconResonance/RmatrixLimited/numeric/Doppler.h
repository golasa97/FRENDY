#ifndef _Doppler_
#define _Doppler_

#include <cstdlib>
#include <cmath>
#include <vector>
#include <deque>

using namespace std;

namespace Numeric {

class Doppler {

 public:

  class double5 {

    double I[5];

   public:

    double5();
   ~double5();

    const double& operator[]( const int i ) const { return I[i]; } 
          double& operator[]( const int i )       { return I[i]; } 

  };

 public:

  class Array {

    deque<double5> ary;

   public:

    Array();
   ~Array();

    int size() const { return ary.size(); }

    double5& push_front() { ary.push_front( double5() );  return ary.front(); }
    double5& push_back () { ary.push_back ( double5() );  return ary.back (); }

    void push_front( const double5& o ) { return ary.push_front( o ); }
    void push_back ( const double5& o ) { return ary.push_back ( o ); }

    const double5& operator[]( const int j ) const { return ary[j]; } 
          double5& operator[]( const int j )       { return ary[j]; } 

  };

 private:

  unsigned long n;  vector<Array> ary;  vector<unsigned long> j0,j1;

 public:

  Doppler();
 ~Doppler();

  void Allocate( const unsigned long size );

  const double& I( const unsigned long i, const unsigned long j, const unsigned long k ) const { return ary[i][j][k]; }
        double& I( const unsigned long i, const unsigned long j, const unsigned long k )       { return ary[i][j][k]; }

  unsigned long& jmin( const unsigned long i ) { return j0[i]; }
  unsigned long& jmax( const unsigned long i ) { return j1[i]; }

  void Update1( const double* v, const unsigned long& n, const double& u,
                const unsigned long& i0, const unsigned long& i1 );
  void Update2( const double* v, const unsigned long& n, const double& u,
                const unsigned long& i0, const unsigned long& i1 );

};

}

#endif
