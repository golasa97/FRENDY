#include "ReconResonance/RmatrixLimited/numeric/Function1.h"

//ClassImp( Numeric::Function1 );

namespace Numeric {


/*! @brief Default constructor */
Function1:: Function1() : func0(NULL), func1(NULL) {}

/*! @brief Constructor
@param[in] f : functional pointer
*/
Function1:: Function1( double (*f)( const double& ) ) : func0(NULL), func1(NULL) { this->Set(f); }

/*! @brief Constructor
@param[in] f : functional pointer
*/
Function1:: Function1( double (*f)( const double&, const Parameter* ) ) : func0(NULL), func1(NULL) { this->Set(f); }

/*! @brief Destructor */
Function1::~Function1(){}


/*! @brief Copy constructor */
Function1::Function1( const Function1& o ) {

  this->Set(o);

}

/*! @brief Assign operator */
Function1& Function1::operator=( const Function1& o ) {

  if( &o != this ) this->Set( o );  return *this;

}

/*! @brief Set function */
Function1* Function1::Set( const Function1& o ) {

  func0 = o.func0;  func1 = o.func1;

  this->resize( o.size() );

    for( int i=0; i<static_cast<int>(this->size()); i++ ) this->at(i) = o[i];

  return this;

}

/*! @brief Set function f(x)
@param[in] f : functional pointer
*/
Function1* Function1::Set( double (*f)( const double& ) ) {

  func0 = f;  return this;

}

/*! @brief Set function f(x) that includes Parameters
@param[in] f : functional pointer
*/
Function1* Function1::Set( double (*f)( const double&, const Parameter* ) ) {

  func1 = f;  return this;

}


/*! @brief Push-back parameter */
Parameter* Function1::PushBack( const Parameter& param ) {

  this->push_back( param );  return &this->back();

}

/*! @brief Push-back parameter value */
Parameter* Function1::PushBack( const double& param ) {

  return this->PushBack( Parameter(param) );

}


/*! @brief Calculate f(x) */
double Function1::Value( const double& x ) const {

//return ( func1 == NULL ) ? (*func0)( x ) : (*func1)( x, &this->at(0) );
  return ( func1 == NULL ) ? (*func0)( x ) : (*func1)( x, this->data() );

}

/*! @brief Calculate f(x) */
double Function1::operator()( const double& x ) const { return this->Value(x); }


/*! @brief Collect free parameters */
int Function1::CollectFreeParams( vector<Parameter*>* o ) {

  int num = 0;

    for( int i=0; i<static_cast<int>(this->size()); i++ )

      if( this->at(i).is_free() ) { o->push_back( &this->at(i) );  num++; }

  return num;

}

/*! @brief Get number of the free parameter */
int Function1::npm_free() const {

  int n = 0;

    for( int i=0; i<static_cast<int>(this->size()); i++ ) if( this->at(i).is_free() ) n++;

  return n;

}

}
