#include "ReconResonance/RmatrixLimited/rml/Distant.h"

namespace RML {

Distant::Section:: Section(){}
Distant::Section::~Section(){}


const Parameter& Distant::Section::at        ( const int i ) const { return ary[i]; }
      Parameter& Distant::Section::at        ( const int i )       { return ary[i]; }
const Parameter& Distant::Section::operator[]( const int i ) const { return this->at(i); }
      Parameter& Distant::Section::operator[]( const int i )       { return this->at(i); }

int  Distant::Section::size () const { return ary.size (); }
bool Distant::Section::empty() const { return ary.empty(); }


Distant::Section* Distant::Section::Set( const Distant::Section& o ) {

  ary = o.ary;  return this;

}


Distant::Section* Distant::Section::ScaleEnergy( const double fac ) {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i] /= pow( fac, (double) i );

  return this;

}


Distant::Section* Distant::Section::Rinf( const Parameter& o ) {

  ary.resize( ary.size()+1 );  ary.back() = o;  return this;

}

Distant::Section* Distant::Section::Rinf( const double val, const double error ) {

  return this->Rinf( Parameter( val, error ) );

}

double Distant::Section::Rinf( const double e ) const {

  double val = 0.0;

    for( int n=0; n<static_cast<int>(ary.size()); n++ ) val += ary[n].Value() * pow( e, (double) n );

  return val;

}


/*! Collect free parameters */
void Distant::Section::CollectFreeParams( vector<Parameter*>* o ) {

  for( int i=0; i<static_cast<int>(ary.size()); i++ )

    if( ary[i].is_free() ) o->push_back( &ary[i] );

  return;

}



Distant::Section* Distant::Section::Fix() {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].Fix();  return this;

}


void Distant::Section::Print( ostream& os ) const {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) { 

    os << "Rinf(" << i << ") = " << ary[i] << endl;

  }

  return;

}

ostream& operator<<( ostream& os, const Distant::Section& o ) {

  o.Print( os );  return os;

}







Distant:: Distant(){}
Distant::~Distant(){}

Distant* Distant::Set( const Distant& o ) {

  ary = o.ary;  return this;

}


Distant* Distant::ScaleEnergy( const double fac ) {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].ScaleEnergy( fac );  return this;

}


double Distant::Rinf( const Channel& o, const double e ) const {

  for( int i=0; i<static_cast<int>(ary.size()); i++ )

    if( ary[i].Channel::operator==( o ) ) return ary[i].Rinf( e );

  return 0.0;

}


Distant::Section* Distant::push_back( const Channel& o ) {

  ary.resize( ary.size() +1 );  ary.back().Channel::Set( o );  return &ary.back();

}



/*! Collect free parameters */
void Distant::CollectFreeParams( vector<Parameter*>* o ) {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) ary[i].CollectFreeParams( o );

  return;

}



void Distant::Print( ostream& os ) const {

  for( int i=0; i<static_cast<int>(ary.size()); i++ ) os << ary[i] << endl;  return;

}



ostream& operator<<( ostream& os, const Distant& o ) {

  o.Print( os );  return os;

}


}
