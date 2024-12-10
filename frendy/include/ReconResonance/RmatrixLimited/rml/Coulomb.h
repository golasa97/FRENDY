#if !defined(___Class_Coulomb)
    #define  ___Class_Coulomb

#include <vector>
#include <cstdlib>
#include <iostream>
#include <complex>
#include "ReconResonance/RmatrixLimited/rml/Channel.h"
#include "ReconResonance/RmatrixLimited/rml/Boundary.h"

namespace RML {

/*!
@class Coulomb
@brief \~japanese 与えられた境界面においてクーロン波動関数（外部波動関数）の位相差や貫通因子等を求める
       \~english  Calculate Coulomb wave (external) function and related quantities at the boundary
*/
class Coulomb : public Channel {

  double rc,rh,bc;  bool do_shift, do_penet;

  double coulomb_scatt_ps, coulomb_scatt_ps0, hard_sphere_scatt_ps, shift_factor, penetration_factor;

  complex<double> l0;

 public:

  Coulomb();
  Coulomb( const Channel& ch );
  Coulomb( const TwoBody& o,                    const double J, const int l, const double s );
  Coulomb( const Particle& a, const Nucleus& b, const double J, const int l, const double s );

  virtual ~Coulomb(){}

  Coulomb* Set( const Channel& ch );
  Coulomb* Set( const TwoBody& o,                    const double J, const int l, const double s );
  Coulomb* Set( const Particle& a, const Nucleus& b, const double J, const int l, const double s );

  void Update( const double e );
  void Update( const double e, const Boundary* condition );

  bool Update( const double e, const int pi );
  bool Update( const double e, const Boundary* condition, const int pi );

  void WKB( const double e, const double rch, double* S ) const;

  const double& Rc() const { return rc; }
        double& Rc()       { return rc; }
  const double& Rh() const { return rh; }
        double& Rh()       { return rh; }
  const double& Bc() const { return bc; }
        double& Bc()       { return bc; }

  const bool&  do_Shift() const { return do_shift; }
        bool&  do_Shift()       { return do_shift; }
  const bool&  do_Penet() const { return do_penet; }
        bool&  do_Penet()       { return do_penet; }

  const double& CoulombScattPaseShift    () const { return coulomb_scatt_ps    ; }
  const double& HardSphereScattPhaseShift() const { return hard_sphere_scatt_ps; }
  const double& ShiftFactor              () const { return shift_factor        ; }
  const double& PenetrationFactor        () const { return penetration_factor  ; }

  const double& omega0() const { return coulomb_scatt_ps0; }

  const double& omega() const { return this->CoulombScattPaseShift    (); }
  const double& phi  () const { return this->HardSphereScattPhaseShift(); }
  const double& S    () const { return this->ShiftFactor              (); }
  const double& P    () const { return this->PenetrationFactor        (); }

  const complex<double>& L0() const { return l0; }
        complex<double>& L0()       { return l0; }

  inline bool operator==( const TwoBody& o ) const { return this->TwoBody::operator==( o ); }
  inline bool operator==( const Channel& o ) const { return this->Channel::operator==( o ); }
  inline bool operator==( const Coulomb& o ) const { return this->Channel::operator==( o ); }

  inline bool operator!=( const TwoBody& o ) const { return !( *this == o ); }
  inline bool operator!=( const Channel& o ) const { return !( *this == o ); }
  inline bool operator!=( const Coulomb& o ) const { return !( *this == o ); }

  void Test( const double& eta, const double& rho, const int& l, double* P, double* S ) const;
  void Test( const double& eta, const double& rho, const int& l, double* ps ) const;
  void TestWhitS( const double& eta, const double& rho, const int& l, double* S ) const;

  //ClassDef( RML::Coulomb, 1 );

};

}

#endif


