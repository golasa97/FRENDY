#if !defined(___Class_Tabular)
    #define  ___Class_Tabular

#include <vector>
#include "ReconResonance/RmatrixLimited/numeric/Datum.h"

using namespace std;

namespace Numeric {

  class Tabular : public vector<Datum> {

    int interpcode;

   public:

    Tabular( const int code = 2 );
   ~Tabular();

    void push_front( const Datum& o );

    const double& X( const int i ) const;
    const double& Y( const int i ) const;
          double& X( const int i );
          double& Y( const int i );

    double I() const;

    Tabular* Set( const double x1, const double x2, double (*function)( const double&, const double* ), const double* params, const double eps = 1.e-3 );

    //ClassDef( Numeric::Tabular, 1 );

  };


/*
  template <typename TX, typename TY, typename T> class Tabular2 : public Matrix<T> {

    Vector<TX> x;  Vector<TY> z;

  };
*/

}

#endif
