#if !defined(___Class_TwoBody)
    #define  ___Class_TwoBody

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <complex>
#include "ReconResonance/RmatrixLimited/rml/Particle.h"
#include "ReconResonance/RmatrixLimited/rml/Nucleus.h"

using namespace std;

namespace RML {

/*!
@class TwoBody
@brief \~japanese 粒子と原子核のペア
       \~english  A pair of particle and nucleus
*/
class TwoBody : public Particle, public Nucleus {

 public:

  TwoBody();
  TwoBody( const Particle& a );
  TwoBody( const Particle& a, const Nucleus& b );
  TwoBody( const TwoBody& o );
  virtual ~TwoBody();

  void Set( const Particle& a );
  void Set( const Nucleus & b );
  void Set( const Particle& a, const Nucleus& b );
  void Set( const TwoBody& o );

  double I_min() const;
  double I_max() const;

  int pi() const;

  const double& M1() const;
        double& M1();
  const double& M2() const;
        double& M2();

  double QM( const TwoBody& o ) const;
  double QI( const TwoBody& o ) const;

  double Qval ( const TwoBody& o ) const;
  double Ethre( const TwoBody& o ) const;

  double mu() const;
  double ZZ() const;
  double Escale() const;
  double Ecm ( const double elab ) const;
  double Elab( const double ecm  ) const;
  double wk ( const double e ) const;
  double wk2( const double e ) const;
  double eta( const double e ) const;

  double CoulombPS( const double e, const int l ) const;
  void   CoulombWF( const double e, const double r, const int l, double* F, double* F1, double* G, double* G1 ) const;

  complex<double> C( const double elab, const double cosangle ) const;

  double sigma_c( const double elab, const double cosangle ) const;

  /*! @brief Spin statistical factor */
  inline double g( const double J ) const {

    double I1 = this->Particle::Spin();
    double I2 = this->Nucleus ::Spin();

    return (2.*J+1.)/( (2.*I1+1.)*(2.*I2+1.) );

  }


  bool operator==( const TwoBody& o ) const;
  bool operator!=( const TwoBody& o ) const;
  bool operator< ( const TwoBody& o ) const;
  bool operator> ( const TwoBody& o ) const;


  bool Equiv( const Particle& a, const Nucleus& b ) const;
  bool Equiv( const TwoBody& o ) const;

  void Print( ostream& os = cout ) const;

  //ClassDef( RML::TwoBody, 1 );

};

void coulomb_wave( const double& eta, const double& rho, const int& l, double* F, double* F1, double* G, double* G1 );


ostream& operator<<( ostream& os, const TwoBody& o );

}

#endif
