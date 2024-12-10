#if !defined(___Class_Distant)
    #define  ___Class_Distant

#include <vector>
#include "ReconResonance/RmatrixLimited/numeric/Parameter.h"
#include "ReconResonance/RmatrixLimited/rml/Channel.h"

using namespace Numeric;

namespace RML {

/*!
@class Distant
@brief \~japanese 任意の関数を用いて非共鳴過程の効果を模擬する (to be developed)
       \~english  Mimic non-resonant process with an arbiturary function (to be developed)
*/
class Distant {

 public:

  class Section : public Channel {

    vector<Parameter> ary;

   public:

    Section();
   ~Section();

    const Parameter& at        ( const int i ) const;
          Parameter& at        ( const int i );
    const Parameter& operator[]( const int i ) const;
          Parameter& operator[]( const int i );

    int  size () const;
    bool empty() const;

    Section* Set( const Section& o );

    Section* ScaleEnergy( const double fac );

    Section* Rinf( const Parameter& o );
    Section* Rinf( const double val, const double error );

    double Rinf( const double e ) const;

    void CollectFreeParams( vector<Parameter*>* o );

    Section* Fix();

    void Print( ostream& os = cout ) const;

  };

 private:

  vector<Section> ary;

 public:

  Distant();
 ~Distant();

  Distant* Set( const Distant& o );

  Distant* ScaleEnergy( const double fac );

  double Rinf( const Channel& o, const double e ) const;

  Section* push_back( const Channel& o );

  void CollectFreeParams( vector<Parameter*>* o );

  void Clear() { ary.clear();  return; }

  void Print( ostream& os = cout ) const;

};

ostream& operator<<( ostream& os, const Distant::Section& o );
ostream& operator<<( ostream& os, const Distant& o );

}

#endif
