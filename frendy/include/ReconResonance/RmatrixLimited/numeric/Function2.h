#if !defined(___Class_Function2)
    #define  ___Class_Function2

#include <vector>
#include "ReconResonance/RmatrixLimited/numeric/Parameter.h"

using namespace std;

namespace Numeric {

/*!
  @class Function2
    @brief Two dimensional function @f$ y=f(x,x')_{\alpha_{0},\alpha_{1},\cdots} @f$ where @f$ \alpha_{i} @f$ is a parameter

    Example use : Set functional pointer without parameters
    @code
    double func( const double& x, const double& xx ) { return 0.1*x + 0.01*xx; }

    void test() {
      Function2 f( func );
        cout << f( 3.14, 1.69 ) << endl;
    }
    @endcode

    Example use : Set functional pointer with parameters
    @code
    double func( const double& x, const double& xx, const Parameter* alpha ) { return alpha[0] + alpha[1]*x; }

    void test() {
      Function2 f( func );
        f.PushBack( 1.0 );  // give alpha[0]
        f.PushBack( 0.1 );  // give alpha[1]
        cout << f( 3.14, 1.69 ) << endl;
      }
    @endcode
*/
class Function2 : public vector<Parameter> {

  double (*func0)( const double&, const double&                   );
  double (*func1)( const double&, const double&, const Parameter* );

 public:

  Function2();
  Function2( double (*f)( const double&, const double&                   ) );
  Function2( double (*f)( const double&, const double&, const Parameter* ) );
 ~Function2();

  Function2           ( const Function2& o );
  Function2& operator=( const Function2& o );

  Function2* Set( const Function2& o );

  Function2* Set( double (*f)( const double&, const double&                   ) );
  Function2* Set( double (*f)( const double&, const double&, const Parameter* ) );

  Parameter* PushBack( const Parameter& param );
  Parameter* PushBack( const double&    param );

  double Value     ( const double& x, const double& xx ) const;
  double operator()( const double& x, const double& xx ) const;

  bool is_nullptr() const { return ( func0 == NULL ) && ( func1 == NULL ); }

  int CollectFreeParams( vector<Parameter*>* o );

  int npm_free() const;

//ClassDef( Numeric::Function2, 1 );

};

}

#endif
