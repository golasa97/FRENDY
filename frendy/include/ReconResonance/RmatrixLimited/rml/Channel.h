#if !defined(___Class_Channel)
    #define  ___Class_Channel

#include <iostream>
#include <iomanip>
#include <vector>
//#include <TObject.h>
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"
#include "ReconResonance/RmatrixLimited/rml/TwoBody.h"

using namespace std;
using namespace Numeric;

namespace RML {

/*!
@class Channel
@brief \~japanese 粒子・原子核のペア、および量子数@f$(J,l,s)@f$による定義されるチャンネル
       \~english  Explicit channel defined by a particle+nucleus pair and quantum numbers @f$(J,l,s)@f$
*/

class Channel : public TwoBody {

  int l_val;  double s_val;  double J_val;  // orbital angular momentum, channel spin, total spin

 public:

  Channel();
  Channel( const Channel& ch );
  Channel( const TwoBody& o );
  Channel( const Particle& a, const Nucleus& b );
  Channel( const TwoBody& o, const int l );
  Channel( const Particle& a, const Nucleus& b, const int l );
  Channel( const TwoBody& o,                    const double J, const int l, const double s =99999. );
  Channel( const Particle& a, const Nucleus& b, const double J, const int l, const double s =99999. );
  virtual ~Channel();

  const int&    l() const { return l_val; } /*! @brief Get orbital angular momentum */
        int&    l()       { return l_val; }
  const double& s() const { return s_val; } /*! @brief Get channel spin */
        double& s()       { return s_val; }
  const double& J() const { return J_val; } /*! @brief Get total spin */
        double& J()       { return J_val; }

  const TwoBody& alpha() const;
        TwoBody& alpha();

  void Set( const Channel& ch );
  void Set( const TwoBody& o );
  void Set( const Particle& a, const Nucleus& b );

  void Set( const TwoBody& o, const int l );
  void Set( const Particle& a, const Nucleus& b, const int l );

  void Set( const TwoBody& o,                    const double J, const int l, const double s =99999. );
  void Set( const Particle& a, const Nucleus& b, const double J, const int l, const double s =99999. );

  int pi() const;

  inline bool operator==( const Channel& ch ) const {

    return this->TwoBody::operator==( ch ) && eq( J_val,ch.J() ) && l_val == ch.l() && eq( s_val,ch.s() ) ;

  }

  inline bool operator!=( const Channel& ch ) const { return !( *this == ch ); }

  bool Equiv( const Channel& ch ) const;
  bool Equiv( const TwoBody& a, const double J, const int l ) const;
  bool Equiv( const TwoBody& a,                 const int l ) const;

  void Print( ostream& os = cout ) const;

  //ClassDef( RML::Channel, 1 );

};

ostream& operator<<( ostream& os, const Channel& o );

}

#endif

