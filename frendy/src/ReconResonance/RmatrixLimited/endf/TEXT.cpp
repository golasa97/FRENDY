#include "ReconResonance/RmatrixLimited/endf/TEXT.h"
#include "ReconResonance/RmatrixLimited/endf/Numeric.h"
#include "ReconResonance/RmatrixLimited/basics/AlphaNumeric.h"
#include <sstream>

#ifdef Use_CINT
ClassImp( ENDF::TEXT );
#endif

using namespace Basics;

namespace ENDF {

TEXT::TEXT() {}
TEXT::TEXT( istream& is ) { this->Store( is ); }
TEXT::TEXT( const char*   text ) { this->Set(text); }
TEXT::TEXT( const string& text ) { this->Set(text); }

TEXT::~TEXT(){}


/*! @brief Assign operator */
TEXT& TEXT::operator=( const TEXT& o ) {

  if( &o != this ) this->Set( o );  return *this;

}

TEXT& TEXT::operator=( const char*   text ) { this->Set( text );  return *this; }
TEXT& TEXT::operator=( const string& text ) { this->Set( text );  return *this; }


void TEXT::Store( istream& is ){

  string xline;

    getline( is, xline ); record = xline.substr( 0, 66 );

  return;

}




void TEXT::Write( ostream& os, const int mat, const int mf, const int mt, int* ns ) const {

  string text66(record);

    text66.resize( 66, ' ' );
  
  os << text66 << endf( mat, mf, mt, ns );

}



const char* TEXT::c_str() const { return record.c_str(); }
string      TEXT::  str() const { return record        ; }

bool TEXT::empty() const { return record.empty(); }
int  TEXT::size () const { return record.size (); }

const char& TEXT::at        ( const int i ) const { return record[i]; }
      char& TEXT::at        ( const int i )       { return record[i]; }
const char& TEXT::operator[]( const int i ) const { return record[i]; }
      char& TEXT::operator[]( const int i )       { return record[i]; }


void TEXT::erase( const int pos, const int num ) {

  record.erase( pos, num );  return;

}

void TEXT::push_front( const char o ) {

  string temp;

    temp.push_back(o);  temp += record;  record = temp;  return;

}

void TEXT::push_back( const char o ) {

  record.push_back( o );  return;

}




void TEXT::PushFront( const char o ) {

  string temp;

    temp.push_back(o);  temp += record;  record = temp;  return;

}

void TEXT::PushBack( const char o ) {

  record.push_back( o );  return;

}


void TEXT::Print( ostream& os ) const {

  os << record << endl;

}


void TEXT::Set( const TEXT& o ) {

  record = o.record;

}

void TEXT::Set( const char* text ) {

  this->Set( string(text) );

}

void TEXT::Set( const string& text ) {

  record = text;  //record.resize( 66, ' ' );

}




bool TEXT::Find( const string& text ) const {

  return ( record.find(text) != string::npos );

}


string TEXT::Sub( const int index, const int n ) const {

  return record.substr(index,n);

}


/*! @brief Get strings enclosed by */
void TEXT::Sub( const char x, vector<string>* a ) const {

  a->clear();

  bool enter(false);  string temp;

  for( int i=0; i<static_cast<int>(record.size()); i++ ) {

    if( record[i] == x && ! enter ) { temp.clear();       enter = true;  continue; }
    if( record[i] == x &&   enter ) { a->push_back(temp); enter = false; continue; }

    if( enter ) {

      temp.push_back( record[i] );

    }

  }

  return;

}


/*! @brief Replace string
@param[in] index : position
@param[in] n     : length
@param[in] with  : new string
*/
TEXT* TEXT::Replace( const int index, const int n, const string& with ) {

  record.replace(index,n,with);  return this;

}

/*! @brief Replace string
@param[in] s    : string to be replaced
@param[in] with : new string
*/
TEXT* TEXT::Replace( const string& s, const string& with ) {

  replace( &record, s, with );  return this;

}

TEXT& TEXT::operator<<( const char* o ) {

  record += string(o);  return *this;

}

TEXT& TEXT::operator<<( const string& o ) {

  record += o;  return *this;

}

TEXT& TEXT::operator<<( const int& o ) {

  stringstream ss;  ss << o;

  record += ss.str();  return *this;

}

TEXT& TEXT::operator<<( const double& o ) {

  stringstream ss;  ss << o;

  record += ss.str();  return *this;

}

TEXT& TEXT::operator<<( const TEXT& o ) {

  record += o.record;  return *this;

}

TEXT& TEXT::operator<<( const Datum& o ) {

  stringstream ss;

    ss << "(X,Y)=(" << endf( o.X() ) << ',' << endf( o.Y() ) << ')';

    record += ss.str();

  return *this;

}


bool TEXT::is_blank() const {

  for( int i=0; i<static_cast<int>(record.size()); i++ ) if( record[i] != ' ' ) return false;

  return true;

}

bool TEXT::FixTab() {

  size_t pos; bool a = false;

    while( (pos = record.find("\t") ) != string::npos ) {

      a = true;
      record.erase(pos, 1);
      record.insert( pos, 1, ' ' );

    }

  return a;

}



// I/O stream

istream& operator>>( istream& is,       TEXT& o ) { o.Store( is );  return is; }
ostream& operator<<( ostream& os, const TEXT& o ) { o.Write( os );  return os; }

};




