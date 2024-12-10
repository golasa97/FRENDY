#if !defined(___Class_NItype)
    #define  ___Class_NItype

#include "LTT1.h"
#include "LB0.h"
#include "LB1.h"
#include "LB2.h"
#include "LB4.h"
#include "LB5.h"
#include "LB6.h"
#include "LB8.h"

namespace ENDF {

class NItype {

 public:

  class Record : public LB1, public LB2, public LB4, public LB6, public LB8 {

   public:

    Record();

    virtual ~Record();

    const int& LB() const { return this->LIST::L2 (); }
          int& LB()       { return this->LIST::L2 (); }
    const int& NT() const { return this->LIST::NPL(); }
          int& NT()       { return this->LIST::NPL(); }

    Record* LB( const int val );
    Record* NT( const int val );

    void Translate( const int opt = 1, ostream& os = cout, unsigned long* ns = NULL, const int width_of_int = 11 ) const;

    void CutBelow( const double E );
    void CutAbove( const double E );

    void CutBelow1( const double E1 );
    void CutAbove1( const double E1 );

    void TrimLower( const double E );
    void TrimUpper( const double E );

    void TrimLower1( const double E1 );
    void TrimUpper1( const double E1 );

    double Rcov( const double E, const double X, const double E1, const double Y ) const;

    double Cov( const double E, const double X, const double E1, const double Y ) const;

    double Cov( const double Elower,  const double Eupper,  const TAB1* X,
                const double Elower1, const double Eupper1, const TAB1* Y ) const;

    void GetVariance( const TAB1* X, TAB1* result, const bool opt = false ) const;

#ifdef Use_ROOT
    void GetCovariance( const TAB1* X, const TAB1* Y, TH2D* result, const int opt ) const;
#endif

    double Cov( const int L,  const double Elower,  const double Eupper,  const LTT1* X,
                const int L1, const double Elower1, const double Eupper1, const LTT1* Y ) const;

    void ScaleEnergy( const double fac );

    void GetEtable( vector<double>* E ) const;
    void GetEtable( vector<double>* ER, vector<double>* EC ) const;

    void Print( ostream& os = cout ) const;

#ifdef Use_CINT
    ClassDef( NItype::Record, 1 );
#endif

  };

 private:

  deque<Record> ary;

 public:

  NItype();
  virtual ~NItype();

  void Translate( const int opt = 1, ostream& os = cout,        unsigned long* ns = NULL, const int width_of_int = 11 ) const;
  void Translate( const int opt,     ostream& os, const int NI, unsigned long* ns = NULL, const int width_of_int = 11 ) const;

  const Record& at        ( const int i ) const;
        Record& at        ( const int i );
  const Record& operator[]( const int i ) const;
        Record& operator[]( const int i );

  int  size () const;
  bool empty() const;
  void clear();

  void Store( istream& is, const int n );
  void Write( ostream& os, const int n, const int mat, const int mf, const int mt, int* ns ) const;

  NItype* PushFront( const NItype& o );
  NItype* PushBack ( const NItype& o );

  NItype* PushFront( const Record& o );
  NItype* PushBack ( const Record& o );

  Record* PushFront();
  Record* PushBack ();

  unsigned long NumberOfLines() const;

  void CutBelow( const double E );
  void CutAbove( const double E );

  void CutBelow1( const double E1 );
  void CutAbove1( const double E1 );

  void TrimLower( const double E );
  void TrimUpper( const double E );

  void TrimLower1( const double E1 );
  void TrimUpper1( const double E1 );

  void Update();

  double Cov( const double E, const double X, const double E1, const double Y ) const;

  double Cov( const double Elower,  const double Eupper,  const TAB1* X,
              const double Elower1, const double Eupper1, const TAB1* Y ) const;

  void GetVariance( const TAB1* X, TAB1* result, const bool opt = false ) const;

#ifdef Use_ROOT
  void GetCovariance( const TAB1* X, const TAB1* Y, TH2D* result,
                      const int maxthreads = 1, const int opt = false ) const;
#endif

  double Cov( const int L,  const double Elower,  const double Eupper,  const LTT1* X,
              const int L1, const double Elower1, const double Eupper1, const LTT1* Y ) const;

  void ScaleEnergy( const double fac );

  void GetEtable( vector<double>* E ) const;
  void GetEtable( vector<double>* ER, vector<double>* EC ) const;

  void Print( ostream& os = cout ) const;

#ifdef Use_CINT
  ClassDef( NItype, 1 );
#endif

};

//istream& operator>>( istream& is,       NItype& arg );
//ostream& operator<<( ostream& os, const NItype& arg );

///@cond
// functions for TH2D
#ifdef Use_ROOT
void scale( TH2D* a, const double val );
void stack2( const TH2D& a, TH2D* result, const int maxthreads );
void normalize( TH2D* o );
#endif
///@endcond

};

#endif
