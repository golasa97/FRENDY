#include "ReconResonance/RmatrixLimited/rml/Boundary.h"

//ClassImp( RML::Boundary::Condition );
//ClassImp( RML::Boundary );

namespace RML {


Boundary::Condition:: Condition(){}
Boundary::Condition::~Condition(){}


Parameter* Boundary::Condition::push_back( const Channel& ch ) {

  ary.push_back( make_pair( ch, Parameter() ) );  return &ary.back().second;

}




Boundary::Condition* Boundary::Condition::Set( const Channel& ch, const Parameter& val ) {

  ary.push_back( make_pair( ch,val ) );  return this;

}

Boundary::Condition* Boundary::Condition::Set( const Particle& a, const Nucleus& b, const Parameter& val ) {

  return this->Set( Channel(a,b), val );

}

Boundary::Condition* Boundary::Condition::Set( const Particle& a, const Nucleus& b, const int l, const Parameter& val ) {

  return this->Set( Channel(a,b,l), val );

}

Boundary::Condition* Boundary::Condition::Set( const Particle& a, const Nucleus& b, const double J, const int l, const Parameter& val ) {

  return this->Set( Channel(a,b,J,l), val );

}

Boundary::Condition* Boundary::Condition::Set( const Particle& a, const Nucleus& b,
const double J, const int l, const double s, const Parameter& val ) {

  return this->Set( Channel(a,b,J,l,s), val );

}


const Channel& Boundary::Condition::at( const int i ) const { return ary[i].first; }
      Channel& Boundary::Condition::at( const int i )       { return ary[i].first; }



static bool set( const Parameter& i, Parameter* o ) {

  o->Set(i);  return true;

}

bool Boundary::Condition::Find( const Channel& ch, Parameter* val ) const {

  int n = ary.size();

  // explicit channel

  for( int i=0; i<n; i++ )

    if( this->at(i).Equiv( ch ) ) return set( ary[i].second, val );

  // particle + nulceus + J + l

  for( int i=0; i<n; i++ )

    if( this->at(i).Equiv( ch, ch.J(), ch.l() ) ) return set( ary[i].second, val );

  // particle + nulceus + l

  for( int i=0; i<n; i++ )

    if( this->at(i).Equiv( ch, ch.l() ) ) return set( ary[i].second, val );

  // particle + nulceus

  for( int i=0; i<n; i++ )

    if( this->at(i).TwoBody::Equiv( ch ) ) return set( ary[i].second, val );

  // particle

  for( int i=0; i<n; i++ )

    if( this->at(i).Particle::operator==( ch ) ) return set( ary[i].second, val );


  return false;

}



/*! Collect free parameters */
void Boundary::Condition::CollectFreeParams( vector<Parameter*>* o ) {

  for( int i=0; i<static_cast<int>(ary.size()); i++ )

    if( ary[i].second.is_free() ) o->push_back( &ary[i].second );

  return;

}


Boundary::Condition* Boundary::Condition::Clear() {

  ary.clear();  return this;

}

void Boundary::Condition::Print( ostream& os, const string s ) const {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) {

    os << s;  ary[i].first.Print( os );  os << "= ";

    ary[i].second.Print( os );  os << endl;

  }

  return;

}




/*! @brief Constructor */
Boundary:: Boundary(){}

/*! @brief Destructor */
Boundary::~Boundary(){}


/*! @brief Share a boundary condition number (Bc) among all the channels with the partition a+b, i.e., channel=(a,b,*,*;*).
@param[in] a             : particle
@param[in] b             : nucleus
@param[in] val           : value
@param[in] error_percent : prior uncertainty of the value
@param[in] name          : name of the parameter (normally blank)
@note The name may be useful when you seek this parameter during the analysis.
*/
void Boundary::Bc( const Particle& a, const Nucleus& b, const double val, const double error_percent, const char* name ) {

  bc.Set( a,b, Parameter( val, fabs(val)*error_percent/100., name ) );  return;

}

/*! @brief Share a channel radius (Rc) among all the channels with the partition a+b, i.e., channel=(a,b,*,*;*).
@param[in] a             : particle
@param[in] b             : nucleus
@param[in] val           : value [fm]
@param[in] error_percent : prior uncertainty of the value
@param[in] name          : name of the parameter (normally blank)
@note The name may be useful when you seek this parameter during the analysis.
*/
void Boundary::Rc( const Particle& a, const Nucleus& b, const double val, const double error_percent, const char* name ) {

  rc.Set( a,b, Parameter( val, fabs(val)*error_percent/100., name ) );  return;

}

/*! @brief Share a hard-sphere radius (Rh) among all the channels with the partition a+b, i.e., channel=(a,b,*,*;*).
@param[in] a             : particle
@param[in] b             : nucleus
@param[in] val           : value [fm]
@param[in] error_percent : prior uncertainty of the value
@param[in] name          : name of the parameter (normally blank)
@note The name may be useful when you seek this parameter during the analysis.
@attention In the standard R-matrix, the hard-sphere radius is equal to channel radius (Rc).
Therefore, you may not give value of Rh in most cases.
However, sometimes, users may want to set different value for Rh to perform
a sensitivity analysis on the elastic channels. Also, in the ENDF-6 format (LRF=7),
Rh is called as "effective" channel radius allowing it is different from "true" channel radius (Rc).
*/
void Boundary::Rh( const Particle& a, const Nucleus& b, const double val, const double error_percent, const char* name ) {

  rh.Set( a,b, Parameter( val, fabs(val)*error_percent/100., name ) );  return;

}



/*! @brief Share a boundary condition number (Bc) among all the channels with the partition a+b and angular momentum l, i.e., channel=(a,b,l,*;*).
@param[in] a             : particle
@param[in] b             : nucleus
@param[in] l             : angular momentum of the relative motion
@param[in] val           : value
@param[in] error_percent : prior uncertainty of the value
@param[in] name          : name of the parameter (normally blank)
@note The name may be useful when you seek this parameter during the analysis.
*/
void Boundary::Bc( const Particle& a, const Nucleus& b, const int l, const double val, const double error_percent, const char* name ) {

  bc.Set( a,b,l, Parameter( val, fabs(val)*error_percent/100., name ) );  return;

}

/*! @brief Share a channel radius (Rc) among all the channels with the partition a+b and angular momentum l, i.e., channel=(a,b,l,*;*).
@param[in] a             : particle
@param[in] b             : nucleus
@param[in] l             : angular momentum of the relative motion
@param[in] val           : value [fm]
@param[in] error_percent : prior uncertainty of the value
@param[in] name          : name of the parameter (normally blank)
@note The name may be useful when you seek this parameter during the analysis.
*/
void Boundary::Rc( const Particle& a, const Nucleus& b, const int l, const double val, const double error_percent, const char* name ) {

  rc.Set( a,b,l, Parameter( val, fabs(val)*error_percent/100., name ) );  return;

}

/*! @brief Share a hard-sphere radius (Rh) among all the channels with the partition a+b and angular momentum l, i.e., channel=(a,b,l,*;*).
@param[in] a             : particle
@param[in] b             : nucleus
@param[in] l             : angular momentum of the relative motion
@param[in] val           : value [fm]
@param[in] error_percent : prior uncertainty of the value
@param[in] name          : name of the parameter (normally blank)
@note The name may be useful when you seek this parameter during the analysis.
@attention In the standard R-matrix, the hard-sphere radius is equal to channel radius (Rc).
Therefore, you may not give value of Rh in most cases.
However, sometimes, users may want to set different value for Rh to perform
a sensitivity analysis on the elastic channels. Also, in the ENDF-6 format (LRF=7),
Rh is called as "effective" channel radius allowing it is different from "true" channel radius (Rc).
*/
void Boundary::Rh( const Particle& a, const Nucleus& b, const int l, const double val, const double error_percent, const char* name ) {

  rh.Set( a,b,l, Parameter( val, fabs(val)*error_percent/100., name ) );  return;

}



/*! @brief Share a boundary condition number (Bc) among all the channels with the partition a+b, total spin J and angular momentum l, i.e., channel=(a,b,l,*;J).
@param[in] a             : particle
@param[in] b             : nucleus
@param[in] J             : total spin of the compound nucleus
@param[in] l             : angular momentum of the relative motion
@param[in] val           : value
@param[in] error_percent : prior uncertainty of the value
@param[in] name          : name of the parameter (normally blank)
@note The name may be useful when you seek this parameter during the analysis.
*/
void Boundary::Bc( const Particle& a, const Nucleus& b, const double J, const int l, const double val, const double error_percent, const char* name ) {

  bc.Set( a,b,J,l, Parameter( val, fabs(val)*error_percent/100., name ) );  return;

}

/*! @brief Share a channel radius (Rc) among all the channels with the partition a+b, total spin J and angular momentum l, i.e., channel=(a,b,l,*;J).
@param[in] a             : particle
@param[in] b             : nucleus
@param[in] J             : total spin of the compound nucleus
@param[in] l             : angular momentum of the relative motion
@param[in] val           : value [fm]
@param[in] error_percent : prior uncertainty of the value
@param[in] name          : name of the parameter (normally blank)
@note The name may be useful when you seek this parameter during the analysis.
*/
void Boundary::Rc( const Particle& a, const Nucleus& b, const double J, const int l, const double val, const double error_percent, const char* name ) {

  rc.Set( a,b,J,l, Parameter( val, fabs(val)*error_percent/100., name ) );  return;

}

/*! @brief Share a hard-sphere radius (Rh) among all the channels with the partition a+b, total spin J and angular momentum l, i.e., channel=(a,b,l,*;J).
@param[in] a             : particle
@param[in] b             : nucleus
@param[in] J             : total spin of the compound nucleus
@param[in] l             : angular momentum of the relative motion
@param[in] val           : value [fm]
@param[in] error_percent : prior uncertainty of the value
@param[in] name          : name of the parameter (normally blank)
@note The name may be useful when you seek this parameter during the analysis.
@attention In the standard R-matrix, the hard-sphere radius is equal to channel radius (Rc).
Therefore, you may not give value of Rh in most cases.
However, sometimes, users may want to set different value for Rh to perform
a sensitivity analysis on the elastic channels. Also, in the ENDF-6 format (LRF=7),
Rh is called as "effective" channel radius allowing it is different from "true" channel radius (Rc).
*/
void Boundary::Rh( const Particle& a, const Nucleus& b, const double J, const int l, const double val, const double error_percent, const char* name ) {

  rh.Set( a,b,J,l, Parameter( val, fabs(val)*error_percent/100., name ) );  return;

}




/*! @brief Set boundary condition number (Bc) for each explicit-channel
@param[in] ch            : explicit channel
@param[in] val           : value
@param[in] error_percent : prior uncertainty of the value
@param[in] name          : name of the parameter (normally blank)
@note The name may be useful when you seek this parameter during the analysis.
*/
void Boundary::Bc( const Channel& ch, const double val, const double error_percent, const char* name ) {

  bc.Set( ch, Parameter( val, fabs(val)*error_percent/100., name ) );  return;

}

/*! @brief Set channel radius (Rc) for each explicit-channel
@param[in] ch            : explicit channel
@param[in] val           : value [fm]
@param[in] error_percent : prior uncertainty of the value
@param[in] name          : name of the parameter (normally blank)
@note The name may be useful when you seek this parameter during the analysis.
*/
void Boundary::Rc( const Channel& ch, const double val, const double error_percent, const char* name ) {

  rc.Set( ch, Parameter( val, fabs(val)*error_percent/100., name ) );  return;

}

/*! @brief Set hard-sphere radius (Rh) for each explicit-channel (for optional use)
@param[in] ch            : explicit channel
@param[in] val           : value [fm]
@param[in] error_percent : prior uncertainty of the value
@param[in] name          : name of the parameter (normally blank)
@note The name may be useful when you seek this parameter during the analysis.
@attention In the standard R-matrix, the hard-sphere radius is equal to channel radius (Rc).
Therefore, you may not give value of Rh in most cases.
However, sometimes, users may want to set different value for Rh to perform
a sensitivity analysis on the elastic channels. Also, in the ENDF-6 format (LRF=7),
Rh is called as "effective" channel radius allowing it is different from "true" channel radius (Rc).
*/
void Boundary::Rh( const Channel& ch, const double val, const double error_percent, const char* name ) {

  rh.Set( ch, Parameter( val, fabs(val)*error_percent/100., name ) );  return;

}



/*! @brief Get boundary condition number (Bc) for the given channel
@param[in] ch : explicit channel
*/
Parameter Boundary::Bc( const Channel& ch ) const {

  Parameter val( 0.0 );

    if( bc.Find( ch, &val ) ) return val;

    //cerr << "!! Boundary::Bc -> not found for ch = " << ch << endl;

  return val;

}

/*! @brief Get boundary channel radius (Rc) for the given channel
@param[in] ch : explicit channel
*/
Parameter Boundary::Rc( const Channel& ch ) const {

  Parameter val( 1.2 * pow( ch.Nucleus::Mass(), 1./3 ) );

    if( rc.Find( ch, &val ) ) return val;

    //cerr << "!! Boundary::Rc -> not found for ch = " << ch << endl;

  return val;

}

/*! @brief Get hard-sphere radius (Rh) for the given channel
@param[in] ch : explicit channel
@note This is called "effective" channel radius int the ENDF-6 format
(to be used for calculation of the hard-sphere scattering phase-shif)
*/
Parameter Boundary::Rh( const Channel& ch ) const {

  Parameter val( this->Rc(ch) );

    if( rh.Find( ch, &val ) ) return val;

    //cerr << "!! Boundary::Rh -> not found for ch = " << ch << endl;

  return val;

}



/*! @brief The shift factor will not be calculated for the given partition (rarely use)
@param[in] o : partition
*/
void Boundary::ShiftOff( const TwoBody& o ) { shift_off.push_back( o );  return; }

/*! @brief The penetration factor will not be calculated for the given partition (rarely use)
@param[in] o : partition
*/
void Boundary::PenetOff( const TwoBody& o ) { penet_off.push_back( o );  return; }

/*! @brief Check if the shift factor is being calculated for the given partition (rarely use)
@param[in] o : partition
*/
bool Boundary::do_Shift( const TwoBody& o ) const {

  for( int i=0; i<static_cast<int>(shift_off.size()); i++ ) if( shift_off[i] == o ) return false;  return true;

}

/*! @brief Check if the penetration factor is being calculated for the given partition (rarely use)
@param[in] o : partition
*/
bool Boundary::do_Penet( const TwoBody& o ) const {

  for( int i=0; i<static_cast<int>(penet_off.size()); i++ ) if( penet_off[i] == o ) return false;  return true;

}




/*! @brief Collect free parameters */
void Boundary::CollectFreeParams( vector<Parameter*>* o ) {

  rc.CollectFreeParams( o );
  rh.CollectFreeParams( o );
  bc.CollectFreeParams( o );

  return;

}

/*! @brief Print parameter valeus, e.g., for Rc and Bc */
void Boundary::Print( ostream& os ) const {

  rc.Print( os, "Rc" );
  rh.Print( os, "Rh" );
  bc.Print( os, "Bc" );

  return;

}


Boundary* Boundary::Clear() {

  rc.Clear();
  rh.Clear();
  bc.Clear();

  shift_off.clear();
  penet_off.clear();

  return this;

}


ostream& operator<<( ostream& os, const Boundary& o ) {

  o.Print( os );  return os;

}

}
