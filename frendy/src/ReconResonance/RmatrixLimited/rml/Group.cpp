#include "ReconResonance/RmatrixLimited/rml/Group.h"

namespace RML {


static void print( const Parameter* o, ostream& os ) {

  os << right << setfill(' ')
     << setw(8) << setprecision(2) << o->Value() << "  "
     << setw(6) << setprecision(2) << o->ErrorPercent() << " %    ";

  return;

}



Exclusive:: Exclusive() : opt(false) {}
Exclusive::~Exclusive(){}


Exclusive* Exclusive::Set( const Particle& o ) {

  opt = true;  this->Particle::Set(o);  return this;

}

bool Exclusive::Find( const Particle& o ) const {

  if( ! opt ) return false;

  return this->Particle::operator!=( o );

}



/*! @brief Default constructor */
Level::Branch:: Branch() {}

/*! @brief Constructor
@param[in] ch    : explicit channel
@param[in] value : value of the reduced-width amplitude [eV^1/2]
*/
Level::Branch:: Branch( const Channel& ch, const Parameter& value ) { this->gamma(ch,value); }

/*! @brief Destructor */
Level::Branch::~Branch() {}


/*! @brief Set reduced-width amplitude
@param[in] ch    : explicit channel
@param[in] value : value of the reduced-width amplitude [eV^1/2]
*/
void Level::Branch::gamma( const Channel& ch, const Parameter& value ) {

  this->Channel  ::Set( ch );
  this->Parameter::Set( value );

  return;

}

/*! @brief Get reduced-width amplitude */
const Parameter& Level::Branch::gamma() const { return *this; }
      Parameter& Level::Branch::gamma()       { return *this; }


void Level::Branch::ScaleEnergy( const double value ) {

  this->Parameter::operator*=( sqrt(value) );  return;

}


/*! @brief Print reduced width amplitude (gamma) */
void Level::Branch::Print( ostream& os ) const {

  os << "gamma";  this->Channel::Print( os );  os << "= ";

  print( this, os );

  //this->Parameter::Print( os );
/*
  os << right << setfill(' ')
     << setw(8) << setprecision(2) << this->Parameter::Value() << "  "
     << setw(6) << setprecision(2) << this->Parameter::ErrorPercent() << " %    ";
*/
  return;

}


ostream& operator<<( ostream& os, const Level::Branch& o ) {

  o.Print( os );  return os;

}






/*! @brief Default constructor */
Level:: Level() : spin(0.), parity(+1), Gam_g(0.0) {}

/*! @brief Constructor with energy eigenvalue
@param[in] eigenvalue : Energy eigenvalue [eV]
*/
//Level:: Level( const Parameter& eigenvalue ) : Gam_g(0.0) { this->Parameter::Set(eigenvalue); }

/*! @brief Destructor */
Level::~Level() {}


/*! @brief Set total J^pi
@param[in] J  : Spin
@param[in] pi : Parity (positive/negative)
*/
Level* Level::Set( const double J, const int pi ) {

  spin = J;  parity = pi;  return this;
  
}

/*! @brief Get i-th branch */
const Level::Branch& Level::at( const int i ) const { return ary[i]; }
      Level::Branch& Level::at( const int i )       { return ary[i]; }

/*! @brief Get i-th branch */
const Level::Branch& Level::operator[]( const int i ) const { return ary[i]; }
      Level::Branch& Level::operator[]( const int i )       { return ary[i]; }

/*! @brief Number of the branches */
int Level::size() const { return ary.size(); }


/*! @brief Set energy eigenvalue
@param[in] eigenvalue : Energy eigenvalue [eV]
*/
Level* Level::E( const Parameter& eigenvalue ) {

  this->Parameter::Set( eigenvalue );  return this;

}

/*! @brief Set energy eigenvalue [eV] */
const Parameter& Level::E() const { return *this; }
      Parameter& Level::E()       { return *this; }


/*! @brief Set reduced-width amplitude
@param[in] ch    : explicit channel
@param[in] value : value of the reduced-width amplitude [eV^1/2]
@param[in] error : its prior uncertainty [eV^1/2]
@param[in] name  : name of the parameter if necessary
*/
Level* Level::gamma( const Channel& ch, const double value, const double error, const char* name ) {

  return this->gamma( ch, Parameter( value, error, name ) );

}

/*! @brief Set reduced-width amplitude
@param[in] ch         : explicit channel
@param[in] value      : value of the reduced-width amplitude [eV^1/2]
@param[in] error      : its prior uncertainty [eV^1/2]
@param[in] error_unit : unit of the uncertainty, e.g., '\%'
@param[in] name       : name of the parameter if necessary
*/
Level* Level::gamma( const Channel& ch, const double value, const double error, const char error_unit, const char* name ) {

  double err = ( error_unit == '%' ) ? fabs(value)*error/100. : error;

  return this->gamma( ch, Parameter( value, err, name ) );

}

/*! @brief Set reduced-width amplitude
@param[in] ch    : explicit channel
@param[in] o     : value of the reduced-width amplitude with its prior uncertainty [eV^1/2]
*/
Level* Level::gamma( const Channel& ch, const Parameter& o ) {

  ary.push_back( Branch( ch, o ) );  return this;

}

/*! @brief Set reduced-width amplitude
@param[in] ch    : explicit channel
@param[in] value : value of the reduced-width amplitude [eV^1/2]
*/
Parameter* Level::gamma( const Channel& ch, const double value ) {

  ary.push_back( Branch( ch, Parameter(value) ) );  return &ary.back();

}

/*! @brief Get reduced-width amplitude [eV^1/2] for given channel
@param[in] ch : explicit channel
*/
Parameter Level::gamma( const Channel& ch ) const {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) if( ary[i] == ch ) return ary[i];

  return Parameter(0.0,0.0);

}


/*! @brief Set "eliminated" channel width to be used for the Reich-Moore approximation
@param[in] value : value of the channel width [eV]
*/
Level* Level::Gamma( const Parameter& value ) {

  Gam_g.Set( value );  return this;

}

/*! @brief Set "eliminated" channel width to be used for the Reich-Moore approximation
@param[in] value : value of the channel width [eV]
@param[in] error : its prior uncertainty [eV]
@param[in] name  : name of the parameter if necessary
*/
Level* Level::Gamma( const double value, const double error, const char* name ) {

  return this->Gamma( Parameter( value, error, name ) );

}

/*! @brief Set "eliminated" channel width to be used for the Reich-Moore approximation
@param[in] value      : value of the channel width [eV]
@param[in] error      : its prior uncertainty [eV]
@param[in] error_unit : unit of the uncertainty, e.g., '\%'
@param[in] name       : name of the parameter if necessary
*/
Level* Level::Gamma( const double value, const double error, const char error_unit, const char* name ) {

  double err = ( error_unit == '%' ) ? fabs(value)*error/100. : error;

  return this->Gamma( Parameter( value, err, name ) );

}


/*
Level* Level::Gamma( const double value, const double error_percent ) {

  return this->Gamma( Parameter( value, fabs(value)*error_percent/100. ) );

}
*/

/*! @brief Get "eliminated" channel width to be used for the Reich-Moore approximation [eV] */
const Parameter& Level::Gamma() const { return Gam_g; }
      Parameter& Level::Gamma()       { return Gam_g; }


Level* Level::ScaleEnergy( const double fac ) {

  this->Parameter::operator*=( fac );  Gam_g *= fac;

    for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].ScaleEnergy( fac );

  return this;

}




/*! @brief Collect free parameters */
void Level::CollectFreeParams( vector<Parameter*>* o ) {

  if( this->is_free() ) o->push_back( this );  // E

    for( int i=0; i<static_cast<int>(ary.size()); i++ ) if( ary[i].is_free() ) o->push_back( &ary[i] );  // gamma

    if( Gam_g.is_free() ) o->push_back( &Gam_g );  // Gam_g

  return;

}


/*
void Level::Print( ostream& os ) const {
// show parameters

  os << "E= " << right << setw(10) << setprecision(1) << this->Parameter::Value() << "  "
                       << setw( 5) << setprecision(2) << this->Parameter::ErrorPercent() << " %    ";

  string blank("                          ");

  for( int i=0; i<ary.size(); i++ ) {

    if( i != 0 ) os << blank;

    ary[i].Print( os );  os << endl;

  }

  if( ne(Gam.Value(),0.0) ) {

    os << blank;
    os << "Gamma                                = ";
    print( &Gam, os );
    os << endl;

  }

  return;

}
*/




/*! @brief Print resonance parameters */
void Level::Print( ostream& os ) const {
// show parameters

  if( this->Exclusive::is_true() ) {

    if( this->Exclusive::ZA() ==    1 ) os << "n->  ";
    if( this->Exclusive::ZA() == 1001 ) os << "p->  ";
    if( this->Exclusive::ZA() == 1002 ) os << "d->  ";
    if( this->Exclusive::ZA() == 1003 ) os << "t->  ";
    if( this->Exclusive::ZA() == 2003 ) os << "h->  ";
    if( this->Exclusive::ZA() == 2004 ) os << "a->  ";

  }

  else                                  os << "     ";

  os << "E= " << right << setw(10) << setprecision(1) << this->Parameter::Value() << "  "
                       << setw( 5) << setprecision(2) << this->Parameter::ErrorPercent() << " %    ";

  string blank("                               ");

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) {

    if( i != 0 ) os << blank;

    ary[i].Print( os );  os << endl;

  }

  if( ne(Gam_g.Value(),0.0) ) {

    os << blank;
    os << "Gamma                                = ";
    print( &Gam_g, os );
    os << endl;

  }

  return;

}


ostream& operator<<( ostream& os, const Level& o ) {

  o.Print( os );  return os;

}







/*! @brief Default constructor */
Group:: Group() : spin(0.), parity(+1) {}

/*! @brief Destructor */
Group::~Group(){}


/*! @brief Set total J^pi
@param[in] J  : Spin
@param[in] pi : Parity (positive/negative)
*/
Group* Group::Set( const double J, const int pi ) {

  spin = J;  parity = pi;  return this;
  
}

/*! @brief Get i-th level */
const Level& Group::at( const int i ) const { return ary[i]; }
      Level& Group::at( const int i )       { return ary[i]; }

/*! @brief Get i-th level */
const Level& Group::operator[]( const int i ) const { return ary[i]; }
      Level& Group::operator[]( const int i )       { return ary[i]; }

/*! @brief Get ii-th branch of the i-th level */
const Level::Branch& Group::at( const int i, const int ii ) const { return this->at(i).at(ii); }
      Level::Branch& Group::at( const int i, const int ii )       { return this->at(i).at(ii); }

/*! @brief Number of the levels */
int  Group::size () const { return ary.size (); }

/*! @brief Check if the level array is empty */
bool Group::empty() const { return ary.empty(); }


/*! @brief Get pointer of the i-th level */
Level* Group::ptr( const int i ) { return &ary[i]; }


/*! @brief Set object */
void Group::Set( const Group& o ) {

  this->Distant::Set( o );  ary = o.ary;  return;

}

/*! @brief Clear object */
void Group::Clear() {

  this->Distant::Clear();  ary.clear();  return;

}

/*! @brief Push-back energy eigenvalue
@param[in] eigenvalue : Energy eigenvalue [eV]
@param[in] error      : its prior uncertainty [eV]
@param[in] name       : name of the parameter if necessary
*/
Level* Group::E( const double eigenvalue, const double error, const char* name ) {

  return this->E( Parameter( eigenvalue, error, name ) );

}

/*! @brief Push-back energy eigenvalue with "exclusive" option (test version)
@param[in] eigenvalue : Energy eigenvalue [eV]
@param[in] exclusive  : Particle channel which is independent from the other particle channels
@param[in] name       : name of the parameter if necessary
*/
Level* Group::E( const double eigenvalue, const Particle& exclusive, const char* name ) {

  return this->E( Parameter( eigenvalue, 0., name ), exclusive );

}

/*! @brief Push-back energy eigenvalue with "exclusive" option (test version)
@param[in] eigenvalue : Energy eigenvalue [eV]
@param[in] error      : its prior uncertainty [eV]
@param[in] exclusive  : Particle channel which is independent from the other particle channels
@param[in] name       : name of the parameter if necessary
*/
Level* Group::E( const double eigenvalue, const double error, const Particle& exclusive, const char* name ) {

  return this->E( Parameter( eigenvalue, error, name ), exclusive );

}

/*! @brief Push-back energy eigenvalue
@param[in] eigenvalue : Energy eigenvalue [eV]
*/
Level* Group::E( const Parameter& eigenvalue ) {

  ary.resize( ary.size()+1 );  ary.back().Set( spin, parity );  ary.back().E( eigenvalue );  return &ary.back();

}

/*! @brief Push-back energy eigenvalue with "exclusive" option (test version)
@param[in] eigenvalue : Energy eigenvalue [eV]
@param[in] exclusive  : Particle channel which is independent from the other particle channels
*/
Level* Group::E( const Parameter& eigenvalue, const Particle& exclusive ) {

  ary.resize( ary.size()+1 );  ary.back().Set( spin, parity );  ary.back().E( eigenvalue )->Exclusive::Set( exclusive );  return &ary.back();

}

/*! @brief Get energy eigenvalue of the i-th level */
const Parameter& Group::E( const int i ) const { return ary[i].E(); }
/*! @brief Get energy eigenvalue of the i-th level */
      Parameter& Group::E( const int i )       { return ary[i].E(); }


/*
Level* Group::E( const double eigenvalue, const double error_percent ) {

  return this->E( Parameter( eigenvalue, fabs(eigenvalue)*error_percent/100. ) );

}
*/

/*! @brief Get reduced-width amplitude [eV^1/2] for the i-th level and given channel
@param[in] i  : index for the level
@param[in] ch : explicit channel
*/
Parameter Group::gamma( const int i, const Channel& ch ) const {

  const Level* lev = &ary[i];

    for( int ii=0; ii<lev->size(); ii++ ) if( lev->at(ii) == ch ) return lev->at(ii);

  return Parameter(0.0,0.0);

}


/*! @brief Get "eliminated" value channel width to be used for the Reich-Moore approximation [eV] */
const Parameter& Group::Gamma( const int i ) const { return ary[i].Gamma(); }
      Parameter& Group::Gamma( const int i )       { return ary[i].Gamma(); }


/*! @brief Collect free parameters */
void Group::CollectFreeParams( vector<Parameter*>* o ) {

  this->Distant::CollectFreeParams( o );

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].CollectFreeParams( o );

  return;

}


Group* Group::ScaleEnergy( const double fac ) {

  this->Distant::ScaleEnergy( fac );

    for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].ScaleEnergy( fac );

  return this;

}

Group* Group::ErrorPercent_E( const double val ) {

  for( int i=0; i<this->size(); i++ ) this->E(i).ErrorPercent( val );  return this;

}

Group* Group::ErrorPercent_gamma( const double val ) {

  for( int i=0; i<this->size(); i++ )

    for( int ii=0; ii<this->at(i).size(); ii++ ) this->at(i,ii).ErrorPercent( val );

  return this;

}

Group* Group::ErrorPercent_gamma( const Channel& ch, const double val ) {

  for( int i=0; i<this->size(); i++ ) {

    for( int ii=0; ii<this->at(i).size(); ii++ )

      if( this->at(i,ii) == ch ) this->at(i,ii).ErrorPercent( val );

  }

  return this;

}

Group* Group::ErrorPercent_gamma( const Particle& a, const Nucleus& b, const double val ) {

  for( int i=0; i<this->size(); i++ ) {

    for( int ii=0; ii<this->at(i).size(); ii++ ) {

      if( this->at(i,ii) == TwoBody(a,b) ) this->at(i,ii).ErrorPercent( val );

    }

  }

  return this;

}


Group* Group::SetZero_gamma( const Particle& a, const Nucleus& b ) {

  for( int i=0; i<this->size(); i++ ) {

    for( int ii=0; ii<this->at(i).size(); ii++ ) {

      if( this->at(i,ii) == TwoBody(a,b) ) this->at(i,ii).Value( 0.0 );

    }

  }

  return this;

}


Group* Group::Fix_E() {

  return this->ErrorPercent_E( 0.0 );

}

Group* Group::Fix_gamma() {

  return this->ErrorPercent_gamma( 0.0 );

}

Group* Group::Fix_gamma( const Channel& ch ) {

  return this->ErrorPercent_gamma( ch, 0.0 );

}

Group* Group::Fix_gamma( const Particle& a, const Nucleus& b ) {

  return this->ErrorPercent_gamma( a,b, 0.0 );

}

Group* Group::Fix() {

  return this->Fix_E()->Fix_gamma();

}


void Group::Print( ostream& os ) const {

  this->Distant::Print( os );

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) { ary[i].Print( os );  /*os << endl;*/ }  return;

}


ostream& operator<<( ostream& os, const Group& o ) {

  o.Print( os );  return os;

}


}
