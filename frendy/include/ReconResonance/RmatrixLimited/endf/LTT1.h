#if !defined(___Class_LTT1)
    #define  ___Class_LTT1

#include "ReconResonance/RmatrixLimited/endf/LIST.h"
#include "ReconResonance/RmatrixLimited/endf/LTT2.h"

namespace ENDF {

/*!
@class LTT1
  @brief Array of Record (which inherits LIST) with TAB2
*/
class LTT1 {

 public:

  class Record : public LIST {

   public:

    Record();
    Record( const LIST& o );

    virtual ~Record();

    const double& T () const { return this->C1 (); }
          double& T ()       { return this->C1 (); }
    const double& E () const { return this->C2 (); }
          double& E ()       { return this->C2 (); }
    const int&    LT() const { return this->L1 (); }
          int&    LT()       { return this->L1 (); }
    const int&    NL() const { return this->NPL(); }
          int&    NL()       { return this->NPL(); }

    Record* T ( const double val ) { this->C1 (val);  return this; }
    Record* E ( const double val ) { this->C2 (val);  return this; }
    Record* LT( const int    val ) { this->L1 (val);  return this; }
    Record* NL( const int    val ) { this->NPL(val);  return this; }

    double  a( const int L ) const;
    double  f( const double cosangle ) const;

    void Reconstruct( TAB1* f, const int interpcode = 2, const double eps = 1.e-3 ) const;

    double a( const int L, const double scale );

#ifdef Use_CINT
    //ClassDef( LTT1::Record, 1 );
#endif

  };

 private:

  TAB2 control;  deque<LTT1::Record> array;

 public:

  LTT1();
  LTT1( const int n, const int interpcode = 2 );
  LTT1( const char* file_name );
  virtual ~LTT1();

  const Record& at( const int i ) const;
        Record& at( const int i );

  const Record& operator[]( const int i ) const;
        Record& operator[]( const int i );

  int  size () const;
  bool empty() const;
  void clear();

  const Record& Front() const;
        Record& Front();
  const Record& Back () const;
        Record& Back ();

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
  const int&    NE() const;
        int&    NE();

  LTT1* C1( const double val );
  LTT1* C2( const double val );
  LTT1* L1( const int    val );
  LTT1* L2( const int    val );
  LTT1* NR( const int    val );
  LTT1* NE( const int    val );

  const int& NBT( const int i ) const;
        int& NBT( const int i );
  const int& INT( const int i ) const;
        int& INT( const int i );

  int InterpCode( const int i ) const;

  const double& T ( const int i ) const { return this->at(i).T (); }
        double& T ( const int i )       { return this->at(i).T (); }
  const double& E ( const int i ) const { return this->at(i).E (); }
        double& E ( const int i )       { return this->at(i).E (); }
  const int&    LT( const int i ) const { return this->at(i).LT(); }
        int&    LT( const int i )       { return this->at(i).LT(); }
  const int&    NL( const int i ) const { return this->at(i).NL(); }
        int&    NL( const int i )       { return this->at(i).NL(); }

  void Translate( const int opt = 1, ostream& os = cout, unsigned long* ns = NULL, const int width_of_int = 11,
                  const char* text1 = ",,,,NR,NE", const char* text2 = "T,E,TL,,NL,/a" ) const;

  void Store( istream& is );
  void Read ( const char* file_name );
  void Write( ostream& os = cout, const int MAT = 0, const int MF = 0, const int MT = 0, int* NS = NULL ) const;
  void Write( const char* file_name ) const;

  unsigned long NumberOfLines() const;

  LTT1* Set( const LTT1& o );
  LTT1* Set( const char* file_name );
  LTT1* Set( const int n, const int interpcode = 2 );
  LTT1* Set( const TAB2& o );

  LTT1* Clear();

  LTT1* PushFront( const Record& o, const int interpcode = 2 );
  LTT1* PushBack ( const Record& o, const int interpcode = 2 );
  LTT1* PushFront( const LTT1&   o, const int interpcode = 2 );
  LTT1* PushBack ( const LTT1&   o, const int interpcode = 2 );

  LTT1* PutClone( const double elab );

  LTT1* PopFront( const int num = 1 );
  LTT1* PopBack ( const int num = 1 );

  LTT1* Erase( const double E );

  LTT1* Thin();

  LTT1* CutBelow( const double elab, const double eps = 1.e-3 );
  LTT1* CutAbove( const double elab, const double eps = 1.e-3 );

  LTT1* Replace( const LTT1& o );

  bool Find( const double E ) const;
  bool Seek( const double E ) const;
  bool Seek( const double E, int* index, int* interpcode ) const;

  LTT1* ScaleEnergy( const double fac );

  void GetEnergyNodes( vector<double>* E ) const;

  double a( const double elab, const int l ) const;
  double a( const double elab_lower, const double elab_upper, const int l ) const;

  void   Interp( Record* result ) const;
  Record Interp( const double elab ) const;

  double f( const double elab, const double cosangle ) const;

  void get_f_da( TAB1* result, const int interpcode = 2, const double eps = 1.e-3 ) const;

  void Reconstruct( LTT2* result, const int interpcode = 2, const double eps = 1.e-3 ) const;

  bool operator==( const LTT1& o ) const;
  bool operator!=( const LTT1& o ) const;
  bool operator< ( const LTT1& o ) const;
  bool operator> ( const LTT1& o ) const;
  bool operator<=( const LTT1& o ) const;
  bool operator>=( const LTT1& o ) const;

  double a( const double E, const int L, const double fac );

  LTT1* Put( const double E, const double eps = 1.e-3 );

#ifdef Use_CINT
  //ClassDef( LTT1, 1 );
#endif

};

};

#endif

