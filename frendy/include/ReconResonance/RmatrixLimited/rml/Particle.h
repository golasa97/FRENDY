#if !defined(___Class_Particle)
    #define  ___Class_Particle

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
//#include <TObject.h>
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"

using namespace std;
using namespace Numeric;

namespace RML {

/*!
@class Particle
@brief \~japanese 粒子（ZA、質量、スピン・パリティ）を定義するクラス
       \~english  Definition of the particle (ZA,mass,spin-parity)
*/
class Particle {

  int z,a,n, parity;  double mass,spin;

 public:

  Particle();
  Particle( const int za );
  Particle( const int za, const double j, const int pi, const double m );
  virtual ~Particle();

  void Set( const int za );
  void Set( const int za, const double j, const int pi, const double m );
  void Set( const Particle& o );

  const int& Z () const;
        int& Z ();
  const int& A () const;
        int& A ();
  const int& N () const;
        int& N ();

  int ZA() const;

  const double& Mass  () const;
        double& Mass  ();
  const double& Spin  () const;
        double& Spin  ();
  const int&    Parity() const;
        int&    Parity();

  double AW() const;

  bool operator==( const Particle& o ) const;
  bool operator!=( const Particle& o ) const;
  bool operator< ( const Particle& o ) const;
  bool operator> ( const Particle& o ) const;

  void Print( ostream& os = cout ) const;

  //ClassDef( RML::Particle, 1 );

};

ostream& operator<<( ostream& os, const Particle& o );

}

#endif
