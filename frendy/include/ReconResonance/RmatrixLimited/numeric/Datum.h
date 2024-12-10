#if !defined(___Class_Datum)
    #define  ___Class_Datum

#include <iostream>
#include <utility>
#include <cmath>

#ifdef Use_ROOT
#include <TObject.h>
#endif

using namespace std;


namespace Numeric {

/*!
  @class Datum
    @brief A pair of X and Y 
*/
  class Datum {

/*
#else
  class Datum {
#endif
*/
  //pair<double,double> v;

    double v[2];

   public:

    Datum();
    Datum( const double x, const double y = 0.0 );
   ~Datum();

    const double& X() const;
          double& X();
    const double& Y() const;
          double& Y();

    Datum* X( const double val );
    Datum* Y( const double val );

    Datum* Set( const double x, const double y );

    void Write( ostream& os = cout ) const;

    bool operator==( const Datum& o ) const;
    bool operator!=( const Datum& o ) const;
    bool operator< ( const Datum& o ) const;
    bool operator> ( const Datum& o ) const;
    bool operator<=( const Datum& o ) const;
    bool operator>=( const Datum& o ) const;

#ifdef Use_CINT
    ClassDef( Numeric::Datum, 1 );
#endif

  };

  ostream& operator<<( ostream& os, const Datum& o );

}

#endif
