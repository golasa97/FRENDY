#if !defined(___Class_Parameter)
    #define  ___Class_Parameter

#include <iostream>
#include <iomanip>
#include <cmath>

#ifdef Use_ROOT
#include <TObject.h>
#endif

using namespace std;

namespace Numeric {

/*!
@class Parameter
@brief This is a container which stores a pair of "Value" and its "Error" (and also its "Name" if necessary)
@note
Example :
@code
Parameter par( 3.14, 0.1 );
  cout << par << endl;
  cout << par.Value() << endl;
  cout << par.Error() << endl;
@endcode
*/
class Parameter {

  double value, error;  string text;

 public:

  Parameter();
  Parameter( const double val, const double err = 0., const char* name = "" );
  Parameter( const double val, const double err     , const char err_unit, const char* name = "" );
  Parameter( const Parameter& o );
  virtual ~Parameter();

  Parameter* Set( const double val, const double err = 0.,                      const char* name = "" );
  Parameter* Set( const double val, const double err     , const char err_unit, const char* name = "" );
  Parameter* Set( const Parameter& o );

  const double& Value() const;
        double& Value();
  const double& Error() const;
        double& Error();
  const char*   Name () const;

  double ErrorPercent() const;
  Parameter* Value( const double val );
  Parameter* Error( const double err );
  Parameter* ErrorPercent( const double percent );
  Parameter* Name( const char* name );

  Parameter* Fix();

  bool is_free() const;

  void Clear();

  void Print     ( ostream& os = cout ) const;
  void PrintLaTex( ostream& os = cout ) const;

  void Print( const int& nspace, const char* title = NULL, ostream& os = cout ) const;

  Parameter& operator*=( const double val );
  Parameter& operator/=( const double val );

  Parameter& operator*=( const Parameter& o );
  Parameter& operator/=( const Parameter& o );

  bool operator==( const Parameter& o ) const;
  bool operator!=( const Parameter& o ) const;

  double Perturb( const double eps = 1.e-5 );

#ifdef Use_CINT
  ClassDef( Numeric::Parameter, 1 );
#endif

};

ostream& operator<<( ostream& os, const Parameter& o );

}

#endif
