#if !defined(___Class_Boundary)
    #define  ___Class_Boundary

#include <vector>
#include <cstdlib>
#include <iostream>
#include <complex>
#include "ReconResonance/RmatrixLimited/numeric/Parameter.h"
#include "ReconResonance/RmatrixLimited/rml/Channel.h"

using namespace std;
using namespace Numeric;

namespace RML {

/*!
@class Boundary
@brief \~japanese 境界条件を定義する
       \~english  Definition of the boundary condition
*/
class Boundary {

 public:

  class Condition {

    vector< pair<Channel,Parameter> > ary;

   public:

    Condition();
   ~Condition();

    Parameter* push_back( const Channel& ch );

    Condition* Set( const Channel& ch, const Parameter& val );
    Condition* Set( const Particle& a, const Nucleus& b,                                              const Parameter& val );
    Condition* Set( const Particle& a, const Nucleus& b,                 const int l,                 const Parameter& val );
    Condition* Set( const Particle& a, const Nucleus& b, const double J, const int l,                 const Parameter& val );
    Condition* Set( const Particle& a, const Nucleus& b, const double J, const int l, const double s, const Parameter& val );

    const Channel& at( const int i ) const;
          Channel& at( const int i );

    bool Find( const Channel& ch, Parameter* val ) const;

    void CollectFreeParams( vector<Parameter*>* o );

    Condition* Clear();

    void Print( ostream& os, const string s ) const;

    //ClassDef( RML::Boundary::Condition, 1 );

  };

 private:

  Condition rc,rh,bc;    vector<TwoBody> shift_off, penet_off;

 public:

  Boundary();
  virtual ~Boundary();

  void Bc( const Particle& a, const Nucleus& b, const double val, const double error_percent=0.0, const char* name = "" );
  void Rc( const Particle& a, const Nucleus& b, const double val, const double error_percent=0.0, const char* name = "" );
  void Rh( const Particle& a, const Nucleus& b, const double val, const double error_percent=0.0, const char* name = "" );

  void Bc( const Particle& a, const Nucleus& b, const int l, const double val, const double error_percent=0.0, const char* name = "" );
  void Rc( const Particle& a, const Nucleus& b, const int l, const double val, const double error_percent=0.0, const char* name = "" );
  void Rh( const Particle& a, const Nucleus& b, const int l, const double val, const double error_percent=0.0, const char* name = "" );

  void Bc( const Particle& a, const Nucleus& b, const double J, const int l, const double val, const double error_percent=0.0, const char* name = "" );
  void Rc( const Particle& a, const Nucleus& b, const double J, const int l, const double val, const double error_percent=0.0, const char* name = "" );
  void Rh( const Particle& a, const Nucleus& b, const double J, const int l, const double val, const double error_percent=0.0, const char* name = "" );

  void Bc( const Channel& ch, const double val, const double error_percent=0.0, const char* name = "" );
  void Rc( const Channel& ch, const double val, const double error_percent=0.0, const char* name = "" );
  void Rh( const Channel& ch, const double val, const double error_percent=0.0, const char* name = "" );

  Parameter Bc( const Channel& ch ) const;
  Parameter Rc( const Channel& ch ) const;
  Parameter Rh( const Channel& ch ) const;

/*
  Condition* Bc() { return &bc; }
  Condition* Rc() { return &rc; }
  Condition* Rh() { return &rh; }
*/
  void ShiftOff( const TwoBody& o );
  void PenetOff( const TwoBody& o );

  bool do_Shift( const TwoBody& o ) const;
  bool do_Penet( const TwoBody& o ) const;

  void CollectFreeParams( vector<Parameter*>* o );

  void Print( ostream& os = cout ) const;

  Boundary* Clear();

  //ClassDef( RML::Boundary, 1 );

};


ostream& operator<<( ostream& os, const Boundary& o );


}

#endif
