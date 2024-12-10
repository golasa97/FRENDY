#if !defined(___Class_TAB2)
    #define  ___Class_TAB2

#include <deque>
//#include <vector>

#include "ReconResonance/RmatrixLimited/endf/CONT.h"
#include "ReconResonance/RmatrixLimited/endf/Document.h"

using namespace std;

namespace ENDF {

  class TAB2 {

   public:

    class Range { //--------------------------------

     private:

      int nsept,inter;

     public:

      Range();
      Range( const int n, const int i );
     ~Range();

      const int& NBT() const;
            int& NBT();
      const int& INT() const;
            int& INT();

      bool operator==( const Range& o ) const;
      bool operator!=( const Range& o ) const;

    }; //--------------------------------------------

   private:

    CONT header;  deque<TAB2::Range> ary;

   public:

    TAB2();
    TAB2( const int nz, const int interpcode = 2 );
    TAB2( istream& is );
   
    virtual ~TAB2();

    TAB2           ( const TAB2& o );
    TAB2& operator=( const TAB2& o );

    const Range& at        ( const int i ) const;
          Range& at        ( const int i );
    const Range& operator[]( const int i ) const;
          Range& operator[]( const int i );

    const Range& front() const;
          Range& front();
    const Range& back () const;
          Range& back ();

    int  size () const;
    bool empty() const;
    void clear();

    void Store( istream& is );
    void Write( ostream& os = cout, const int MAT = 0, const int MF = 0, const int MT = 0, int* NS = NULL ) const;

    TAB2* Set( const CONT& o );
    TAB2* Set( const TAB2& o, const bool option = false );
    TAB2* Set( const int NZ, const int interpcode = 2 );
  //TAB2* Set( const deque<Range>& ranges );

    TAB2* C1( const double val );
    TAB2* C2( const double val );
    TAB2* L1( const int    val );
    TAB2* L2( const int    val );
    TAB2* NR( const int    val );
    TAB2* NZ( const int    val );

    const double& C1() const;
          double& C1();
    const double& C2() const;
          double& C2();
    const int&    L1() const;
          int&    L1();
    const int&    L2() const;
          int&    L2();
    const int&    NR() const;
          int&    NR();
    const int&    NZ() const;
          int&    NZ();

    const int& NBT( const int i ) const;
          int& NBT( const int i );
    const int& INT( const int i ) const;
          int& INT( const int i );

    void Translate( ostream& os = cout, unsigned long* ns = NULL, const int opt = 1,
                    const int width_of_int = 11, const char* text = "C1,C2,L1,L2,NR,NZ" ) const;

    TAB2* Update();

    bool Check() const;

    TAB2* Clear();
    TAB2* ClearArray();

    const Range& Front() const;
          Range& Front();
    const Range& Back () const;
          Range& Back ();

    int InterpCode( const int i ) const;

    TAB2* SetInterpCode( const int interpcode );

    TAB2* CutAbove( const int index );
    TAB2* CutBelow( const int index );

    //void Insert( const int index, const int inter = 2 );
    TAB2* PushFront( const int inter );
    TAB2* PushBack ( const int inter );

    TAB2* PushFront();
    TAB2* PushBack ();

    TAB2* PushFront( const TAB2& o );  // change NR, NZ, NBT and INT
    TAB2* PushBack ( const TAB2& o );  // change NR, NZ, NBT and INT

    TAB2* PopFront();
    TAB2* PopBack ();

    TAB2* Erase( const int index );

    void Diagnose( Document* result, int* ns ) const;

    bool operator==( const TAB2& o ) const;
    bool operator!=( const TAB2& o ) const;
    bool operator< ( const TAB2& o ) const;
    bool operator> ( const TAB2& o ) const;
    bool operator<=( const TAB2& o ) const;
    bool operator>=( const TAB2& o ) const;

    unsigned long NumberOfLines() const;

#ifdef Use_CINT
    ClassDef( TAB2, 1 );
#endif

  };

  istream& operator>>( istream& is,       TAB2& o );
  ostream& operator<<( ostream& os, const TAB2& o );

};

#endif
