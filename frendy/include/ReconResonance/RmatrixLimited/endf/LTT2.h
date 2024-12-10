#if !defined(___Class_LTT2)
    #define  ___Class_LTT2

#include "ReconResonance/RmatrixLimited/endf/TAB1.h"

namespace ENDF {

/*!
@class LTT2
  @brief Array of Record (which inherits TAB1) with TAB2
*/
class LTT2 {

 public:

  class Record : public TAB1 {

   public:

    Record();
    Record( const TAB1& o );

    virtual ~Record();

    const double& T () const;
          double& T ();
    const double& E () const;
          double& E ();
    const int&    LT() const;
          int&    LT();

    Record* T ( const double val );
    Record* E ( const double val );
    Record* LT( const int    val );

#ifdef Use_CINT
    //ClassDef( LTT2::Record, 1 );
#endif

  };

 private:

  TAB2 control;  deque<LTT2::Record> array;

 public:

  LTT2();
  LTT2( const int n, const int interpcode = 2 );
  LTT2( const char* file_name );
  virtual ~LTT2();

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

  LTT2* C1( const double val );
  LTT2* C2( const double val );
  LTT2* L1( const int    val );
  LTT2* L2( const int    val );
  LTT2* NR( const int    val );
  LTT2* NE( const int    val );

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

  void Translate( const int opt = 1, ostream& os = cout, unsigned long* ns = NULL, const int width_of_int = 11,
                  const char* text1 =  ",,,,NR,NE", const char* text2 = "T,E,TL,,NR,NP/mu,f" ) const;

  void Store( istream& is );
  void Read ( const char* file_name );
  void Write( ostream& os = cout, const int MAT = 0, const int MF = 0, const int MT = 0, int* NS = NULL ) const;
  void Write( const char* file_name ) const;

  unsigned long NumberOfLines() const;

  LTT2* Set( const LTT2& o );
  LTT2* Set( const char* file_name );
  LTT2* Set( const int n, const int interpcode = 2 );
  LTT2* Set( const TAB2& o );

  LTT2* Update();

  LTT2* Clear();
  LTT2* ClearArray();

  LTT2* PushFront( const Record& o, const int interpcode = 2 );
  LTT2* PushBack ( const Record& o, const int interpcode = 2 );
  LTT2* PushFront( const LTT2&   o, const int interpcode = 2 );
  LTT2* PushBack ( const LTT2&   o, const int interpcode = 2 );

  LTT2* PutClone( const double elab );

  LTT2* PopFront( const int num = 1 );
  LTT2* PopBack ( const int num = 1 );

  LTT2* Erase( const double E );

  LTT2* Thin();
  LTT2* Thin( const double eps );
  LTT2* Thin( const double mu_min, const double mu_max, const double eps );

  LTT2* CutBelow( const double elab, const double eps = 1.e-3 );
  LTT2* CutAbove( const double elab, const double eps = 1.e-3 );

  LTT2* Replace( const LTT2& o );

  bool Find( const double E ) const;
  bool Seek( const double E ) const;
  bool Seek( const double E, int* index, int* interpcode ) const;

  LTT2* Reverse();

  LTT2* ScaleEnergy( const double fac );

  void GetEnergyNodes( vector<double>* E ) const;

  void   Interp( Record* result,    const double eps = 1.e-3 ) const;
  void   Interp( TAB1*   result,    const double eps = 1.e-3 ) const;
  Record Interp( const double elab, const double eps = 1.e-3 ) const;

  LTT2* Weight( const double power = 1.0 );

  LTT2* Average( const int ndiv );

  void  Average(                                   TAB1* result, const double eps = 1.e-3 ) const;
  void  Average( const double E1, const double E2, TAB1* result, const double eps = 1.e-3 ) const;

  LTT2* Linearize( const double eps = 1.e-3 );

  double f( const double elab, const double cosangle ) const;

  void   get_f_da( TAB1* result, const double eps = 1.e-3 ) const;

  double I() const;

  void GetProfile( const double mu, TAB1* result ) const;

  LTT2& operator+=( const double val );
  LTT2& operator-=( const double val );
  LTT2& operator*=( const double val );
  LTT2& operator/=( const double val );

  bool operator==( const LTT2& o ) const;
  bool operator!=( const LTT2& o ) const;
  bool operator< ( const LTT2& o ) const;
  bool operator> ( const LTT2& o ) const;
  bool operator<=( const LTT2& o ) const;
  bool operator>=( const LTT2& o ) const;

  //void   Integral( TAB1* ans, const int nrandom ) const;
  //void   Integral( TAB1* ans, const int nrandom ) const;

#ifdef Use_CINT
  //ClassDef( LTT2, 1 );
#endif

};

};

#endif


