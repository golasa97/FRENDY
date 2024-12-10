#if !defined(___Class_TEXT)
    #define  ___Class_TEXT

#include <iostream>
#include <vector>
#include <string>
#include "ReconResonance/RmatrixLimited/numeric/Datum.h"

#ifdef Use_ROOT
#include <TObject.h>
#endif

using namespace std;
using namespace Numeric;

namespace ENDF {

class TEXT {

  string record;

  public:

    TEXT();
    TEXT( istream& is );
    TEXT( const char*   text );
    TEXT( const string& text );

    virtual ~TEXT();

    TEXT& operator=( const TEXT&      o );
    TEXT& operator=( const char*   text );
    TEXT& operator=( const string& text );

    void Store( istream& is );
    void Write( ostream& os = cout, const int mat = 0, const int mf = 0, const int mt = 0, int* ns = NULL ) const;

    const char* c_str() const;
    string        str() const;

    bool empty() const;
    int  size () const;

    void erase( const int pos, const int num );

    const char& at        ( const int i ) const;
          char& at        ( const int i );
    const char& operator[]( const int i ) const;
          char& operator[]( const int i );

    void push_front( const char o );
    void push_back ( const char o );

    void PushFront( const char o );
    void PushBack ( const char o );

    void Print( ostream& os = cout ) const;

    void Set( const TEXT&   o );
    void Set( const char*   text );
    void Set( const string& text );

    bool Find( const string& text ) const;

    string Sub( const int index, const int n ) const;
    void   Sub( const char x, vector<string>* a ) const;

    TEXT* Replace( const int index, const int n, const string& with );
    TEXT* Replace( const string& s, const string& with );

    TEXT& operator<<( const char*   o );
    TEXT& operator<<( const string& o );
    TEXT& operator<<( const int&    o );
    TEXT& operator<<( const double& o );
    TEXT& operator<<( const TEXT&   o );
    TEXT& operator<<( const Datum&  o );

    bool is_blank() const;

    bool FixTab();

#ifdef Use_CINT
    ClassDef( TEXT, 1 );
#endif

};

istream& operator>>( istream& is,       TEXT& o );
ostream& operator<<( ostream& os, const TEXT& o );

};

#endif
