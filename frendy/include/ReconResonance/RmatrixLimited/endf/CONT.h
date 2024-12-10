#if !defined(___Class_CONT)
    #define  ___Class_CONT

#include <iostream>
#include <string>
#include "ReconResonance/RmatrixLimited/endf/Numeric.h"
#include "ReconResonance/RmatrixLimited/endf/Document.h"

#ifdef Use_ROOT
#include <TObject.h>
#endif

using namespace std;

namespace ENDF {

#define front_space_for_translation "             "

class CONT {

  double c1,c2;  int l1,l2, n1,n2;

  public:

    CONT();
    CONT( const double C1, const double C2, const int L1, const int L2, const int N1, const int N2 );
    CONT( istream& is );

    virtual ~CONT();

    void Store( istream& is );
    void Write( ostream& os = cout, const int MAT = 0, const int MF = 0, const int MT = 0, int* NS = NULL ) const;

    CONT* Set( const double C1, const double C2, const int L1, const int L2, const int N1, const int N2 );
    CONT* Set( const CONT& o );

    const double& C1() const;
          double& C1();
    const double& C2() const;
          double& C2();
    const int&    L1() const;
          int&    L1();
    const int&    L2() const;
          int&    L2();
    const int&    N1() const;
          int&    N1();
    const int&    N2() const;
          int&    N2();

    CONT* C1( const double val );
    CONT* C2( const double val );
    CONT* L1( const int    val );
    CONT* L2( const int    val );
    CONT* N1( const int    val );
    CONT* N2( const int    val );

    void Translate( ostream& os = cout, unsigned long* ns = NULL, const bool opt = true, const int width_of_int = 11,
                    const char* text = "C1,C2,L1,L2,N1,N2", const char* front_space = front_space_for_translation ) const;

    CONT* Clear();

    void Diagnose( Document* result, int* NS ) const;

    unsigned long NumberOfLines() const;

    bool operator==( const CONT& o ) const;
    bool operator!=( const CONT& o ) const;
    bool operator< ( const CONT& o ) const;
    bool operator> ( const CONT& o ) const;
    bool operator<=( const CONT& o ) const;
    bool operator>=( const CONT& o ) const;

#ifdef Use_CINT
    ClassDef( CONT, 1 );
#endif

};

istream& operator>>( istream& is,       CONT& o );
ostream& operator<<( ostream& os, const CONT& o );

};

#endif
