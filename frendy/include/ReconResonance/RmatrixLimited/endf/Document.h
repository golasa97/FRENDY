#if !defined(___Class_Document)
    #define  ___Class_Document

#include <vector>
#include <iostream>
#include "ReconResonance/RmatrixLimited/endf/TEXT.h"

using namespace std;

namespace ENDF {

class Document {

  vector<TEXT> ary;

 public:

  Document();
 ~Document();

  const TEXT& at        ( const int i ) const;
        TEXT& at        ( const int i );
  const TEXT& operator[]( const int i ) const;
        TEXT& operator[]( const int i );

  int  size () const;
  bool empty() const;
  void clear();

  void Set( const Document& o );

  const TEXT& Front() const;
        TEXT& Front();
  const TEXT& Back () const;
        TEXT& Back ();

  //TEXT& PushFront( const string& msg );
  TEXT& PushBack ( const string& msg );

  //TEXT& PushFront( const TEXT& msg );
  TEXT& PushBack ( const TEXT& msg );

  //void PushFront( const Document& o );
  void PushBack ( const Document& o );

  //TEXT& PushFront( const int number_of_blank = 0 );
  TEXT& PushBack ( const int number_of_blank = 0 );

  void Print( ostream& os = cout ) const;

#ifdef Use_CINT
  ClassDef( Document, 1 );
#endif

};

};

#endif
