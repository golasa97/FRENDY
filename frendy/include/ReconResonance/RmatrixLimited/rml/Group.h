#if !defined(___Class_Level)
    #define  ___Class_Level

#include <vector>
#include "ReconResonance/RmatrixLimited/numeric/Parameter.h"
#include "ReconResonance/RmatrixLimited/rml/Coulomb.h"
#include "ReconResonance/RmatrixLimited/rml/Boundary.h"
#include "ReconResonance/RmatrixLimited/rml/Distant.h"

using namespace Numeric;

namespace RML {

class Exclusive : public Particle {

  bool opt;

 public:

  Exclusive();
 ~Exclusive();

  const bool is_true() const { return opt; }

  Exclusive* Set ( const Particle& o );
  bool       Find( const Particle& o ) const;

};


/*!
@class Level
@brief \~japanese 複合核の個々の励起準位情報と、あるチャンネルに対する換算幅振幅を定義する
       \~english  Definition of an excited level in the compound system and reduced-width amplitude for each channel
*/
class Level : public Parameter, public Exclusive {  // Parameter -> eigenvalue

 public:

  class Branch : public Channel, public Parameter {  // Parameter -> reduced width amplitude

   public:

    Branch();
    Branch( const Channel& ch, const Parameter& value );
   ~Branch();

    void gamma( const Channel& ch, const Parameter& value );

    const Parameter& gamma() const;
          Parameter& gamma();

    void ScaleEnergy( const double value );

    inline bool operator==( const Channel& ch ) const { return this->Channel::operator==( ch ); }
    inline bool operator!=( const Channel& ch ) const { return this->Channel::operator!=( ch ); }

    inline bool operator==( const TwoBody& o ) const { return this->TwoBody::operator==( o ); }
    inline bool operator!=( const TwoBody& o ) const { return this->TwoBody::operator!=( o ); }

    void Print( ostream& os = cout ) const;

  };

 private:

  double spin;  int parity;

  vector<Branch> ary;

  Parameter Gam_g; /* to be used only for Reich-Moore approximation */ 

 public:

  Level();
  //Level( const Parameter& eigenvalue );
 ~Level();

  Level* Set( const double J, const int pi );

  const double& J () const { return spin;   }
        double& J ()       { return spin;   }
  const int&    pi() const { return parity; }
        int&    pi()       { return parity; }

  const Branch& at( const int i ) const;
        Branch& at( const int i );

  const Branch& operator[]( const int i ) const;
        Branch& operator[]( const int i );

  int size() const;

  Level* E( const Parameter& eigenvalue );

  const Parameter& E() const;
        Parameter& E();


  Level* gamma( const Channel& ch, const double value, const double error, const char* name = "" );
  Level* gamma( const Channel& ch, const double value, const double error, const char error_unit, const char* name = "" );
  Level* gamma( const Channel& ch, const Parameter& pm );

  Parameter* gamma( const Channel& ch, const double value );
  Parameter  gamma( const Channel& ch ) const;

/*
  inline Parameter gamma( const Channel& ch ) const {

    for( int i=0; i<ary.size(); i++ ) if( ary[i] == ch ) return ary[i];

    return Parameter(0.0,0.0);

  }
*/
  Level*    Gamma( const Parameter& value );
  Level*    Gamma( const double value, const double error, const char* name = "" );
  Level*    Gamma( const double value, const double error, const char error_unit, const char* name = "" );

  const Parameter& Gamma() const;
        Parameter& Gamma();

  Level* ScaleEnergy( const double fac );

  void CollectFreeParams( vector<Parameter*>* o );

  void Print( ostream& os = cout ) const;

};

ostream& operator<<( ostream& os, const Level::Branch& o );
ostream& operator<<( ostream& os, const Level& o );



/*!
@class Group
@brief \~japanese 同一の@f$J^{\pi}@f$を持つ励起順位のグループ
       \~english  A group of excited levels which have the same @f$J^{\pi}@f$
*/
class Group : public Distant {

  double spin;  int parity;  vector<Level> ary;

 public:

  Group();
  virtual ~Group();

  Group* Set( const double J, const int pi );

  const double& J () const { return spin;   }
        double& J ()       { return spin;   }
  const int&    pi() const { return parity; }
        int&    pi()       { return parity; }

  const Level& at( const int i ) const;
        Level& at( const int i );

  const Level& operator[]( const int i ) const;
        Level& operator[]( const int i );

  int  size () const;
  bool empty() const;

  const Level::Branch& at( const int i, const int ii ) const;
        Level::Branch& at( const int i, const int ii );

  Level* ptr( const int i );

  Level* E( const double eigenvalue, const double error = 0.0,                      const char* name = "" );
  Level* E( const double eigenvalue,                     const Particle& exclusive, const char* name = "" );
  Level* E( const double eigenvalue, const double error, const Particle& exclusive, const char* name = "" );

  Level* E( const Parameter& eigenvalue );
  Level* E( const Parameter& eigenvalue, const Particle& exclusive );

  const Parameter& E( const int i ) const;
        Parameter& E( const int i );

  //Parameter  gamma( const int i, const Channel& ch ) const { return ary[i].gamma(ch); }

  Parameter gamma( const int i, const Channel& ch ) const;

  const Parameter& Gamma( const int i ) const;
        Parameter& Gamma( const int i );

  void Set( const Group& o );
  void Clear();

  void CollectFreeParams( vector<Parameter*>* o );

  Group* ScaleEnergy( const double fac );

  Group* ErrorPercent_E    (                    const double val );
  Group* ErrorPercent_gamma(                    const double val );
  Group* ErrorPercent_gamma( const Channel& ch, const double val );
  Group* ErrorPercent_gamma( const Particle& a, const Nucleus& b, const double val );

  Group* SetZero_gamma( const Particle& a, const Nucleus& b );

  Group* Fix_E();
  Group* Fix_gamma();
  Group* Fix_gamma( const Channel& ch );
  Group* Fix_gamma( const Particle& a, const Nucleus& b );
  Group* Fix();

  void Print( ostream& os = cout ) const;

};

ostream& operator<<( ostream& os, const Group& o );

}

#endif
