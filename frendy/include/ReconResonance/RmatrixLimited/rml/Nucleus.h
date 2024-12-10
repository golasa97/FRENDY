#if !defined(___Class_Nucleus)
    #define  ___Class_Nucleus

#include <iostream>
//#include <TObject.h>
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"
#include "ReconResonance/RmatrixLimited/rml/Particle.h"

using namespace std;
using namespace Numeric;

namespace RML {

/*!
@class Nucleus
@brief \~japanese 原子核（ZA、質量、スピン・パリティ、励起エネルギー）を定義するクラス
       \~english  Definition of the nuclues (ZA,mass,spin-parity,excitation energy)
*/
class Nucleus {

  int z,a,n, parity;  double mass,spin,energy;

 public:

  Nucleus();
  Nucleus( const int za, const double j, const int pi, const double m, const double ex = 0.0 );
  virtual ~Nucleus();

  void Set( const int za, const double j, const int pi, const double m, const double ex = 0.0 );
  void Set( const Nucleus& o );

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
  const double& Energy() const;
        double& Energy();

  void Mass  ( const double val ) { mass   = val;  return; }
  void Spin  ( const double val ) { spin   = val;  return; }
  void Parity( const int    val ) { parity = val;  return; }
  void Energy( const double val ) { energy = val;  return; }

  double AW() const;

  bool operator==( const Nucleus& o ) const;
  bool operator!=( const Nucleus& o ) const;
  bool operator< ( const Nucleus& o ) const;
  bool operator> ( const Nucleus& o ) const;


  void Print( ostream& os = cout ) const;

  //ClassDef( RML::Nucleus, 1 );

};

ostream& operator<<( ostream& os, const Nucleus& o );

}

#endif
