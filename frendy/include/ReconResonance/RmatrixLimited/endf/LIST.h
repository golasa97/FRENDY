#if !defined(___Class_LIST)
    #define  ___Class_LIST

#include <iostream>
#include <vector>
#include <complex>
#include "ReconResonance/RmatrixLimited/endf/CONT.h"

//using namespace std;

namespace ENDF {

  class LIST {

    CONT header;  vector<double> ary;

   public:

    LIST();
    LIST( const double C1, const double C2, const int L1, const int L2, const int NPL, const int N2,
          const vector<double>* b );
    LIST( const char* file_name );
    LIST( istream& is );

    virtual ~LIST();

    LIST           ( const LIST& o ); 
    LIST& operator=( const LIST& o );

    const double& at        ( const int i ) const;
          double& at        ( const int i );
    const double& operator[]( const int i ) const;
          double& operator[]( const int i );

    const double& front() const;
          double& front();
    const double& back () const;
          double& back ();

    int  size () const;
    bool empty() const;
    void clear();

    LIST* resize( const int n );

    void Store( istream& is );
    void Write( ostream& os = cout, const int MAT = 0, const int MF = 0, const int MT = 0, int* NS = NULL ) const;
    void Write( const char* file_name ) const;

    LIST* Set( const LIST& o );
    LIST* Set( const double C1, const double C2, const int L1, const int L2, const int NPL, const int N2 );
    LIST* Set( const vector<double>* b );
    LIST* Set( const double C1, const double C2, const int L1, const int L2, const int NPL, const int N2,
               const vector<double>* b );
    LIST* Set( const char* file_name );

    void PrintColumns( const int num_of_columns = 1 ) const;

    void PrintColumns( ostream& os, const int   num_of_columns,                        const char* front_space = "" ) const;
    void PrintColumns( ostream& os, const char* titles,                                const char* front_space = "" ) const;
    void PrintColumns( ostream& os, const int   num_of_columns, const int num_of_rows, const char* front_space = "" ) const;
    void PrintColumns( ostream& os, const char* titles,         const int num_of_rows, const char* front_space = "" ) const;

    const double& B( const int i ) const;
          double& B( const int i );

    void Extract( const int n, const int m, vector<double>* b ) const;

    LIST* B( const vector<double>* b );

    const double& C1 () const;
          double& C1 ();
    const double& C2 () const;
          double& C2 ();
    const int&    L1 () const;
          int&    L1 ();
    const int&    L2 () const;
          int&    L2 ();
    const int&    NPL() const;
          int&    NPL();
    const int&    N2 () const;
          int&    N2 ();

    LIST* C1 ( const double val );
    LIST* C2 ( const double val );
    LIST* L1 ( const int    val );
    LIST* L2 ( const int    val );
    LIST* NPL( const int    val );
    LIST* N2 ( const int    val );

    void Translate( ostream& os = cout, unsigned long* ns = NULL, const int opt = 1, const int width_of_int = 11,
                    const char* text1 = "C1,C2,L1,L2,NPL,N2/B" ) const;

    void Translate( ostream& os, const int num_of_data_in_a_line, unsigned long* ns, const int opt, const int width_of_int = 11,
                    const char* text = "C1,C2,L1,L2,NPL,N2/B" ) const;

    //LIST* PushFront( const double val );
    LIST* PushBack ( const double val );
    LIST* PushBack ( const complex<double> val );

    LIST* PopFront( const int num = 1 );
    LIST* PopBack ( const int num = 1 );

    const double& Front() const;
          double& Front();
    const double& Back () const;
          double& Back ();

    LIST* Scale( const double fac );

    LIST* Clear();
    LIST* ClearArray();

    bool Empty() const { return this->NPL() == 0 ? true : false; }

    bool Check() const;

    bool operator==( const LIST& o ) const;
    bool operator!=( const LIST& o ) const;
    bool operator< ( const LIST& o ) const;
    bool operator> ( const LIST& o ) const;
    bool operator<=( const LIST& o ) const;
    bool operator>=( const LIST& o ) const;

    unsigned long NumberOfLines() const;

#ifdef Use_CINT
    ClassDef( LIST, 1 );
#endif

  };

  istream& operator>>( istream& is,       LIST& o );
  ostream& operator<<( ostream& os, const LIST& o );

};

#endif
