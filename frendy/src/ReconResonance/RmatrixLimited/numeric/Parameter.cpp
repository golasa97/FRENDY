#include "ReconResonance/RmatrixLimited/numeric/Parameter.h"
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"

#ifdef Use_CINT
ClassImp( Numeric::Parameter );
#endif

namespace Numeric {


/*! @brief Default constructor */
Parameter::Parameter() : value(0.), error(0.), text("") {}

/*! @brief Constructor
@param[in] val      : value of parameter
@param[in] err      : error of parameter value
@param[in] name     : name of the parameter if necessary
*/
Parameter::Parameter( const double val, const double err, const char* name ) {

  this->Set( val, err, name );

}

/*! @brief Constructor
@param[in] val      : value of parameter
@param[in] err      : error of parameter value
@param[in] err_unit : unit of the error, e.g., '\%'
@param[in] name     : name of the parameter if necessary
*/
Parameter::Parameter( const double val, const double err, const char err_unit, const char* name ) {

  this->Set( val, err, err_unit, name );

}

/*! @brief Constructor */
Parameter::Parameter( const Parameter& o ) {

  this->Set( o );

}

/*! @brief Destructor */
Parameter::~Parameter(){}


/*! @brief Set parameter value, error and name
@param[in] val      : value of parameter
@param[in] err      : error of parameter value
@param[in] name     : name of the parameter if necessary
*/
Parameter* Parameter::Set( const double val, const double err, const char* name ) {

  value = val;  error = err;  text = name;  return this;

}

/*! @brief Set parameter value, error and name
@param[in] val      : value of parameter
@param[in] err      : error of parameter value
@param[in] err_unit : unit of the error, e.g., '\%'
@param[in] name     : name of the parameter if necessary
*/
Parameter* Parameter::Set( const double val, const double err, const char err_unit, const char* name ) {

  double e = ( err_unit == '%' ) ? fabs(val)*err/100. : err;

  return this->Set( val, e, name );

}

/*! @brief Set parameter */
Parameter* Parameter::Set( const Parameter& o ) {

  this->Set( o.value, o.error, o.text.c_str() );  return this;

}


/*! @brief Get value */
const double& Parameter::Value() const { return value; }
/*! @brief Get value */
      double& Parameter::Value()       { return value; }

/*! @brief Get uncertainty */
const double& Parameter::Error() const { return error; }
/*! @brief Get uncertainty */
      double& Parameter::Error()       { return error; }

 /*! @brief Get name of this object */
const char* Parameter::Name () const { return text.c_str(); }

/*! @brief Get uncertainty of the value in percent */
double Parameter::ErrorPercent() const { return (value == 0.0) ? 0.0 : 100.*error/fabs(value); }

/*! @brief Set value */
Parameter* Parameter::Value( const double val ) { value = val; return this; }

/*! @brief Set uncertainty */
Parameter* Parameter::Error( const double err ) { error = err; return this; }

/*! @brief Set uncertainty in percent */
Parameter* Parameter::ErrorPercent( const double percent ) { error = fabs(value)*percent/100.; return this; }

/*! @brief Set name if necessary */
Parameter* Parameter::Name( const char* name ) { text = name;  return this; }

/*! @brief Set value of uncertainty to zero (to be used for parameter search) */
Parameter* Parameter::Fix() { return this->Error(0.0); }

/*! @brief Check if value of uncertainty is larger than zero (to be used for parameter search) */
bool Parameter::is_free() const { return ( error > 0. ); } 


/*! @brief Clear this object */
void Parameter::Clear() {

  value = 0.;  error = 0.;  text.clear();


}


Parameter& Parameter::operator*=( const double val ) {

  value *= val;  error *= val;  return *this;

}

Parameter& Parameter::operator/=( const double val ) {

  value /= val;  error /= val;  return *this;

}

Parameter& Parameter::operator*=( const Parameter& o ) {

  error  = sqrt( pow( o.Value()*error, 2. ) + pow( value*o.Error(), 2. ) );
  value *= o.Value();

  return *this;

}

Parameter& Parameter::operator/=( const Parameter& o ) {

  Parameter temp;

    temp.Value() = 1./o.Value();
    temp.Error() = o.Error()/o.Value()/o.Value();

  return this->operator*=( temp );

}

bool Parameter::operator==( const Parameter& o ) const {

  return ( eq( this->Value(), o.Value() )
        && eq( this->Error(), o.Error() )
        && this->Name() == o.Name() );

}

bool Parameter::operator!=( const Parameter& o ) const {

  return !( *this == o );

}

/*! @brief Give perturbation and return its value : @f$ |Value| \times \epsilon @f$ */
double Parameter::Perturb( const double eps ) {

  double delta = fabs(value)*eps;  value += delta;

  return delta;

}




void Parameter::Print( ostream& os ) const {

  os.setf(ios::fixed, ios::floatfield);

  os << setfill(' ') << internal << right << setw(8) << setprecision(5) << this->Value();

  if( error == 0.0 ) os << "           ";
  else os << " ± " << fixed << setfill(' ') << setw(6) << setprecision(3) << this->ErrorPercent() << " %";

  return;

}


void Parameter::Print( const int& nspace, const char* title, ostream& os ) const {

  for( int i=0; i<nspace; i++ ) os << ' ';

    os << left << setw(16) << ( title==NULL ? text:title) << " = ";

      this->Print( os );

  return;

};



void Parameter::PrintLaTex( ostream& os ) const {

  os.setf(ios::fixed, ios::floatfield);

  os << '$' << setfill(' ') << internal << right << setw(8) << setprecision(5) << this->Value() << "$ ";


  if( error == 0.0 ) os << "          ";
  else os << "$\\pm " << setw(6) << setprecision(3) << this->ErrorPercent() << " \\%$";

  return;

}






ostream& operator<<( ostream& os, const Parameter& o ) {

  o.Print( os );  return os;

}


}
