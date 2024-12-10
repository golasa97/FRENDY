#include "ReconResonance/RmatrixLimited/numeric/Function2.h"

//ClassImp( Numeric::Function2 );

namespace Numeric {

/*! @brief Default constructor */
Function2:: Function2() : func0(NULL),func1(NULL) {}

/*! @brief Constructor
@param[in] f : functional pointer
*/
Function2:: Function2( double (*f)( const double&, const double& ) ) : func0(NULL),func1(NULL) { this->Set(f); }

/*! @brief Constructor
@param[in] f : functional pointer
*/
Function2:: Function2( double (*f)( const double&, const double&, const Parameter* ) ) : func0(NULL),func1(NULL) { this->Set(f); }

/*! @brief Destructor */
Function2::~Function2(){}


/*! @brief Copy constructor */
Function2::Function2( const Function2& o ) {

  this->Set(o);

}

/*! @brief Assign operator */
Function2& Function2::operator=( const Function2& o ) {

  if( &o != this ) this->Set( o );  return *this;

}

/*! @brief Set function */
Function2* Function2::Set( const Function2& o ) {

  func0 = o.func0;  func1 = o.func1;

  this->resize( o.size() );

    for( int i=0; i<static_cast<int>(this->size()); i++ ) this->at(i) = o[i];

  return this;

}

/*! @brief Set function f(x,x')
@param[in] f : functional pointer
*/
Function2* Function2::Set( double (*f)( const double&, const double& ) ) {

  func0 = f;  return this;

}

/*! @brief Set function f(x,x') that includes Parameters
@param[in] f : functional pointer
*/
Function2* Function2::Set( double (*f)( const double&, const double&, const Parameter* ) ) {

  func1 = f;  return this;

}


/*! @brief Push-back parameter */
Parameter* Function2::PushBack( const Parameter& param ) {

  this->push_back( param );  return &this->back();

}

/*! @brief Push-back parameter value */
Parameter* Function2::PushBack( const double& param ) {

  return this->PushBack( Parameter(param) );

}


/*! @brief Calculate f(x,x') */
double Function2::Value( const double& x, const double& xx ) const {

//return ( func1 == NULL ) ? (*func0)( x, xx ) : (*func1)( x, xx, &this->at(0) );
  return ( func1 == NULL ) ? (*func0)( x, xx ) : (*func1)( x, xx, this->data() );

}

/*! @brief Calculate f(x,x') */
double Function2::operator()( const double& x, const double& xx ) const { return this->Value(x,xx); }




/*! @brief Collect free parameters */
int Function2::CollectFreeParams( vector<Parameter*>* o ) {

  int num = 0;

    for( int i=0; i<static_cast<int>(this->size()); i++ )

      if( this->at(i).is_free() ) { o->push_back( &this->at(i) );  num++; }

  return num;

}

/*! @brief Get number of the free parameter */
int Function2::npm_free() const {

  int n = 0;

    for( int i=0; i<static_cast<int>(this->size()); i++ ) if( this->at(i).is_free() ) n++;

  return n;

}


}
