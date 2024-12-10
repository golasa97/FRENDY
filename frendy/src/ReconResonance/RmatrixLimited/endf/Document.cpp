#include "ReconResonance/RmatrixLimited/endf/Document.h"

#ifdef Use_CINT
ClassImp( ENDF::Document );
#endif

namespace ENDF {

Document:: Document(){}
Document::~Document(){}


const TEXT& Document::at        ( const int i ) const { return ary[i]; }
      TEXT& Document::at        ( const int i )       { return ary[i]; }
const TEXT& Document::operator[]( const int i ) const { return ary[i]; }
      TEXT& Document::operator[]( const int i )       { return ary[i]; }

int  Document::size () const { return ary.size (); }
bool Document::empty() const { return ary.empty(); }
void Document::clear()       { return ary.clear(); }

const TEXT& Document::Front() const { return ary.front(); }
      TEXT& Document::Front()       { return ary.front(); }
const TEXT& Document::Back () const { return ary.back (); }
      TEXT& Document::Back ()       { return ary.back (); }


void Document::Set( const Document& o ) {

  ary = o.ary;  return;

}

/*
TEXT& Document::PushFront( const string& msg ) {

  ary.push_front( TEXT(msg) );  return ary.front();

}
*/
TEXT& Document::PushBack( const string& msg ) {

  ary.push_back( TEXT(msg) );  return ary.back();

}

/*
TEXT& Document::PushFront( const TEXT& msg ) {

  ary.push_front( msg );  return ary.front();

}
*/
TEXT& Document::PushBack( const TEXT& msg ) {

  ary.push_back( msg );  return ary.back();

}

/*
void Document::PushFront( const Document& o ) {

  Document a(o);

    for( int i=0; i<this->size(); i++ ) a.PushBack( this->at(i) );

  return this->Set(a);;

}
*/
void Document::PushBack( const Document& o ) {

  for( int i=0; i<o.size(); i++ ) this->PushBack( o[i] );  return;

}

/*
TEXT& Document::PushFront( const int number_of_blank ) {

  this->PushFront( TEXT("") );

    for( int i=0; i<number_of_blank; i++ ) this->Front().PushBack(' ');

  return this->Front();

}
*/
TEXT& Document::PushBack( const int number_of_blank ) {

  this->PushBack( TEXT("") );

    for( int i=0; i<number_of_blank; i++ ) this->Back().PushBack(' ');

  return this->Back();

}

void Document::Print( ostream& os ) const {

  for( int i=0; i<this->size(); i++ ) ary[i].Print( os );

}

};
