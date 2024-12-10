#if !defined(___Class_TAB1)
    #define  ___Class_TAB1

#include <vector>
#include "ReconResonance/RmatrixLimited/endf/TAB2.h"
#include "ReconResonance/RmatrixLimited/numeric/Datum.h"
#include "ReconResonance/RmatrixLimited/numeric/Function1.h"
#include "ReconResonance/RmatrixLimited/numeric/Function2.h"

#ifdef Use_ROOT
#include <TGraph.h>
#endif

//using namespace std;

namespace ENDF {

#ifdef Use_ROOT
  class TAB1 : public TGraph {
#else
  class TAB1 {
#endif

    TAB2 header;  deque<Datum> ary;

   public:

    TAB1();
    TAB1( istream& is );
    TAB1( const char* file_name );
    TAB1( const char* file_name, const int interpcode );
    TAB1( const char* file_name, const int index_x, const int   index_y,   const int interpcode );
    TAB1( const char* file_name, const int index_x, const char* indices_y, const int interpcode );

    TAB1( const int np, const int interpcode = 2 );
    TAB1( const double x_min, const double x_max, const int ndiv = 1, const int interpcode = 2 );
    TAB1( const Numeric::Datum* o,          const int np,   const int interpcode = 2 );
    TAB1( const double* x,                  const int np,   const int interpcode = 2 );
    TAB1( const double* x, const double* y, const int np,   const int interpcode = 2 );
  //TAB1( const vector<Numeric::Datum>* o, const int interpcode = 2 );
  //TAB1( const vector<double>* x,                          const int interpcode = 2 );
  //TAB1( const vector<double>* x, const vector<double>* y, const int interpcode = 2 );
  //TAB1( const deque <double>* x,                          const int interpcode = 2 );
  //TAB1( const deque <double>* x, const deque <double>* y, const int interpcode = 2 );

    virtual ~TAB1();

    TAB1           ( const TAB1& o );
    TAB1& operator=( const TAB1& o );

    const Datum& at        ( const int i ) const;
          Datum& at        ( const int i );
    const Datum& operator[]( const int i ) const;
          Datum& operator[]( const int i );

    const Datum& front() const;
          Datum& front();
    const Datum& back () const;
          Datum& back ();

    int  size () const;
    bool empty() const;
    void clear();

    TAB1* Store( istream& is );
    int   Read( const char* file_name );
  //void  Read( const char* file_name );
    void  Write( ostream& os = cout, const int MAT = 0, const int MF = 0, const int MT = 0, int* NS = NULL ) const;
    void  Write( const char* file_name ) const;
    void  Write( const int num, ostream& os = cout );

    TAB1* Set( const TAB1& o, const bool option = false );
    TAB1* Set( const int np, const int interpcode = 2 );
    TAB1* Set( const double x_min, const double x_max, const int ndiv = 1, const int interpcode = 2 );
    TAB1* Set( const Numeric::Datum* a,          const int np,             const int interpcode = 2 );
    TAB1* Set( const double* x,                  const int np,             const int interpcode = 2 );
    TAB1* Set( const double* x, const double* y, const int np,             const int interpcode = 2 );
    TAB1* Set( const char* file_name );
    TAB1* Set( const char* file_name, const int interpcode );
    TAB1* Set( const char* file_name, const int index_x, const int   index_y, const int interpcode );
    TAB1* Set( const char* file_name, const int index_x, const char* index_y, const int interpcode );
  //TAB1* Set( const vector<Numeric::Datum>* a,                          const int interpcode = 2 );
  //TAB1* Set( const vector<double>* x,                          const int interpcode = 2 );
  //TAB1* Set( const vector<double>* x, const vector<double>* y, const int interpcode = 2 );
  //TAB1* Set( const deque<double>*  x,                          const int interpcode = 2 );
  //TAB1* Set( const deque<double>*  x, const deque<double>*  y, const int interpcode = 2 );

    TAB1* SetArray( const TAB1& o );

    const double& X( const int i ) const;
          double& X( const int i );
    const double& Y( const int i ) const;
          double& Y( const int i );

    double Ymin() const;
    double Ymax() const;

    const Datum& Front() const;
          Datum& Front();
    const Datum& Back () const;
          Datum& Back ();

    TAB1* Front( const Datum& o );
    TAB1* Back ( const Datum& o );

    bool CheckDuplicated( const double& x ) const;

    void Diagnose( Document* result, int* ns ) const;

    TAB1* Narrow ( const double x1, const double x2 );
    TAB1  Extract( const double x1, const double x2 ) const;

    TAB1* CutAbove( const double x );
    TAB1* CutBelow( const double x );
    TAB1* PutClone( const double x );
    TAB1* PutZero ( const double x, const double eps_e = 1.e-4 );  // 1.e-4 for JENDL-5 (2021/11/2)

    TAB1* PushFront( const double x, const double y = 0.0, const int interpcode = 2, const bool inspect = true );
    TAB1* PushBack ( const double x, const double y = 0.0, const int interpcode = 2, const bool inspect = true );

    TAB1* PushFront( const Datum& o, const int interpcode = 2, const bool inspect = true );
    TAB1* PushBack ( const Datum& o, const int interpcode = 2, const bool inspect = true );

    TAB1* PushFront( const TAB1& o, const int interpcode = 2, const bool inspect = true );
    TAB1* PushBack ( const TAB1& o, const int interpcode = 2, const bool inspect = true );

    TAB1* PopFront( const int num = 1 );
    TAB1* PopBack ( const int num = 1 );

    TAB1* ResizeFront( const TAB1& o );
    TAB1* ResizeBack ( const TAB1& o );

    TAB1* Replace( const TAB1& o );

    bool CheckAll_X_equal_to( const double val ) const;
    bool CheckAll_Y_equal_to( const double val ) const;

    bool CheckAll_X_less_than( const double val ) const;
    bool CheckAll_Y_less_than( const double val ) const;

    TAB1* Update( const bool option = true );
    TAB1* Clear();
    TAB1* ClearArray();

    bool Empty() const;

    TAB1* Put    ( const double x );
    TAB1* PutSame( const double x );

    TAB1* PutXvaleus( const TAB1* o );

    bool  CheckDuplication( int* index ) const;

    TAB1* Remove( const int index, const int interpcode = 0 );
    TAB1* Remove( const double  x, const int interpcode = 0 );

    TAB1* Truncate( const double y_min = 1.e-16 );
    TAB1* Trim();
  //TAB1* TrimNew();

    TAB1* Correct();

    TAB1* Unique();

    TAB1* TrimLower( const double x );
    TAB1* TrimUpper( const double x );

    bool Find( const double& x, const double eps ) const;
    bool Find( const double x ) const;
    bool Find( const double x, int* index ) const;

    double I( const int i ) const;
    double I() const;
    double I( const double x1, const double x2 ) const;

    TAB1* SetY( const double val );

    TAB1* ScaleX( const double fact );
    TAB1* ScaleY( const double fact );

    TAB1* ScaleX( double (*func)( const double& ) );
    TAB1* ScaleX( double (*func)( const double& ), const double Xmin, const double Xmax );
    TAB1* ScaleY( double (*func)( const double& ) );
    TAB1* ScaleY( double (*func)( const double& ), const double Xmin, const double Xmax );

    TAB1* ShiftX( const double val );
    TAB1* ShiftY( const double val );

    TAB1* ShiftX( double (*func)( const double& ) );
    TAB1* ShiftX( double (*func)( const double& ), const double Xmin, const double Xmax );
    TAB1* ShiftY( double (*func)( const double& ) );
    TAB1* ShiftY( double (*func)( const double& ), const double Xmin, const double Xmax );

    TAB1* PowerX( const double val );
    TAB1* PowerY( const double val );

    TAB1* Cos2a();

    TAB1* TransformBase( const double Xmin = 0.0, const double Xmax = 1.0 );

    double Interp    ( const double x ) const;
    double operator()( const double x ) const;

    double Average( const double x1, const double x2 ) const;

    TAB1*  Average();

    TAB1*  Average( const double dx );
    TAB1*  Average( const double* x, const int nbins );
    TAB1*  Average( const double* x, const int nbins, const double xmin );
    TAB1*  Average( const int ndiv );
    TAB1*  Average( const double xmin, const double xmax, const int ndiv );

    TAB1* Rebin( const int step );

    TAB1* Broad( double (*FWHM)( const double& ), const double eps = 1.e-3, const int maxthreads = 1 );

    TAB1* Broad( const Function1& FWHM, const double xmin, const double xmax,           const double eps = 1.e-3, const int maxthreads = 1 );
    TAB1* Broad( const Function1& FWHM, const pair<double,double>* ranges, const int n, const double eps = 1.e-3, const int maxthreads = 1 );
    TAB1* Broad( const Function2& f,    const double xmin, const double xmax,           const double eps = 1.e-3, const int maxthreads = 1 );
    TAB1* Broad( const Function2& f,    const pair<double,double>* ranges, const int n, const double eps = 1.e-3, const int maxthreads = 1 );

    TAB1* Broad( const double m, const double M, const double T, const double eps, const int maxthreads = 1 );
    TAB1* Broad( const double m, const double M, const double T, const double emax, const double eps, const int maxthreads = 1 );

    TAB1* Thin( const double eps );
    TAB1* Thin( const double xmin, const double xmax, const double eps );

    void PrintColumns( ostream& os = cout, const char* text = NULL,                                  const char* front_space = "" ) const;
    void PrintColumns( ostream& os,        const char* text,                  const int num_of_rows, const char* front_space = "" ) const;

    void PrintColumns( const char*  file_name, const char* text = NULL ) const;
    void PrintColumns( const string file_name, const char* text = NULL ) const;

    TAB1* C1( const double val );
    TAB1* C2( const double val );
    TAB1* L1( const int    val );
    TAB1* L2( const int    val );
    TAB1* NR( const int    val );
    TAB1* NP( const int    val );

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
    const int&    NP() const;
          int&    NP();

    const int& NBT( const int i ) const;
          int& NBT( const int i );
    const int& INT( const int i ) const;
          int& INT( const int i );

    int InterpCode( const int index ) const;

    void Translate( ostream& os = cout, unsigned long* ns = NULL, const int opt = 1, const int width_of_int = 11,
                    const char* text = "C1,C2,L1,L2,NR,NP/X,Y" ) const;

  //TAB1( const TAB1& tab1 );
  //TAB1& operator= ( const TAB1& tab1 );
    TAB1& operator<<( const TAB1& o );
    TAB1& operator+=( const TAB1& o );
    TAB1& operator-=( const TAB1& o );
    TAB1& operator*=( const TAB1& o );
    TAB1& operator/=( const TAB1& o );
    TAB1& operator+=( const double val );
    TAB1& operator-=( const double val );
    TAB1& operator*=( const double val );
    TAB1& operator/=( const double val );

    TAB1  operator+( const TAB1& o );
    TAB1  operator-( const TAB1& o );
    TAB1  operator*( const TAB1& o );
    TAB1  operator/( const TAB1& o );
    TAB1  operator+( const double val );
    TAB1  operator-( const double val );
    TAB1  operator*( const double val );
    TAB1  operator/( const double val );

    bool operator==( const TAB1& o ) const;
    bool operator!=( const TAB1& o ) const;
    bool operator< ( const TAB1& o ) const;
    bool operator> ( const TAB1& o ) const;
    bool operator<=( const TAB1& o ) const;
    bool operator>=( const TAB1& o ) const;

  //TAB1* Add     ( const TAB1& o, const double eps = 1.e-3 );
    TAB1* Add     ( const TAB1& o, const double eps = 1.e-3, const int maxthreads = 1 );
    TAB1* Subtract( const TAB1& o, const double eps = 1.e-3 );
    TAB1* Multiply( const TAB1& o, const double eps = 1.e-3 );
    TAB1* Divide  ( const TAB1& o, const double eps = 1.e-3 );

    TAB1* Weight( const double power = 1.0 );

    TAB1* Normalize( const TAB1& o );

    TAB1 Difference( const TAB1& o, const bool is_percent = false ) const;

    bool Check() const;
    bool Seek( const double x ) const;
    bool Seek( const double x, int* index, int* interpcode ) const;

    unsigned long NumberOfLines() const;

    TAB1* Reverse();

    TAB1* Linearize  (                       const double eps = 1.e-3 );
    TAB1* Reconstruct( const int interpcode, const double eps = 1.e-3 );

    void Break( vector<TAB1>* result ) const;
    void Split( vector<TAB1>* result ) const;

  // <ROOT----------------------------
#ifdef Use_ROOT
    TAB1* SetLineAttributes( const TAttLine* o );
    TAB1* SetLineColor  ( const int color );
    TAB1* SetLineStyle  ( const int style );
    TAB1* SetMarkerStyle( const int style );
    TAB1* SetMarkerColor( const int color );
    TAB1* SetLineWidth  ( const float width );
    TAB1* SetColor      ( const int color );
    TAB1* SetLine( const Style_t style, const Color_t color = 1, const Width_t width = 1 );
    TAB1* SetTitle( const string title );
    void  Draw( const Option_t* opt = "AL", const bool cos2a = false, const double eps = 1.e-3 );
#endif
  // ---------------------------------ROOT>

#ifdef Use_CINT
    ClassDef( TAB1, 1 );
#endif

  };

  void Uniform ( TAB1* a, TAB1* b, const double eps =1.e-3 );

  void add_logarithmic_points( vector<double>* o, const int ndiv = 13 );
  void add_logarithmic_points( deque<double>* o, const int ndiv = 13 );

  void reconstruct( TAB1* o, const int& interpcode, const double& eps );

  void thin( TAB1* a, const double eps );

  int search( const double& x, const TAB1* o );

  istream& operator>>( istream& is,       TAB1& o );
  ostream& operator<<( ostream& os, const TAB1& o );

};

#endif

