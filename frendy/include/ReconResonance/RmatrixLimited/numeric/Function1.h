#if !defined(___Class_Function1)
    #define  ___Class_Function1

#include <vector>
#include "ReconResonance/RmatrixLimited/numeric/Parameter.h"

using namespace std;

namespace Numeric {

/*!
  @class Function1
    @brief One dimensional function @f$ y=f(x)_{\alpha_{0},\alpha_{1},\cdots} @f$ where @f$ \alpha_{i} @f$ is a parameter

    Example use : Set functional pointer without parameters
    @code
    double func( const double& x ) { return 0.1*x; }

    void test() {
      Function1 f( func );
        cout << f( 3.14 ) << endl;
    }
    @endcode

    Example use : Set functional pointer with parameters
    @code
    double func( const double& x, const Parameter* alpha ) { return alpha[0] + alpha[1]*x; }

    void test() {
      Function1 f( func );
        f.PushBack( 1.0 );  // give alpha[0]
        f.PushBack( 0.1 );  // give alpha[1]
        cout << f( 3.14 ) << endl;
      }
    @endcode
*/
class Function1 : public vector<Parameter> {

  double (*func0)( const double&                   );
  double (*func1)( const double&, const Parameter* );

  vector<Parameter> array;

 public:

  Function1();
  Function1( double (*f)( const double&                   ) );
  Function1( double (*f)( const double&, const Parameter* ) );
 ~Function1();

  Function1           ( const Function1& o );
  Function1& operator=( const Function1& o );

  Function1* Set( const Function1& o );

  Function1* Set( double (*f)( const double&                   ) );
  Function1* Set( double (*f)( const double&, const Parameter* ) );

  Parameter* PushBack( const Parameter& param );
  Parameter* PushBack( const double&    param );

  double Value     ( const double& x ) const;
  double operator()( const double& x ) const;

  bool is_nullptr() const { return ( func0 == NULL && func1 == NULL ); }

  int CollectFreeParams( vector<Parameter*>* o );

  int npm_free() const;

//ClassDef( Numeric::Function1, 1 );

};

}

#endif
