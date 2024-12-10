#if !defined(___Class_System)
    #define  ___Class_System

#include <vector>
#include "ReconResonance/RmatrixLimited/rml/TwoBody.h"
#include "ReconResonance/RmatrixLimited/rml/Boundary.h"
#include "ReconResonance/RmatrixLimited/rml/Structure.h"

/**
* @namespace RML
* @brief The namespace includes a number of classes for the R-matrix limitted calculation
*/
namespace RML {

/*!
@class System
@brief \~japanese R行列理論の計算を行うためのメインクラス
       \~english  The main class for the R-matrix calculation
*/
class System : public Boundary {

  string title;  double mass;  vector<pair< TwoBody,double> > se;
  
  vector<Structure> ary;  vector<TwoBody> parts;  int size_free_pm;  int nparts;

 public:

  System();
  System( const string text );
  virtual ~System();

  void Title( const string text ) { title = text; }

  void    Mass( const double m );

  const double& Mass() const;
        double& Mass();

  Structure* PushBack( const double J, const int pi );

  void PushBack( const Particle& a, const Nucleus& A );
  void PushBack( const Particle& a, const Nucleus& A, const double S_a );

  void PushBack( const TwoBody& o );
  void PushBack( const TwoBody& o, const double S_a );

  System* ScaleEnergy( const double fac );

  System* SetOption( const bool option );

  System* Configure( const bool option = true );

  const TwoBody& Partition( const int i ) const;
        TwoBody& Partition( const int i );

  const int& n_partitions() const;
        int& n_partitions();

  double Ba  ( const TwoBody& inc ) const;
  double Qval( const TwoBody& inc, const TwoBody& out ) const;

  Structure* Solve( const double J, const int pi, const TwoBody& inc, const double elab );
  System*   Solve( const TwoBody& inc, const double elab );
  System*   Solve( const vector<double>& qval, const double ecm );

  double sigma  ( const TwoBody& inc, const double elab ) const;
  double sigma_c( const TwoBody& inc, const double elab ) const;
  double sigma  ( const TwoBody& inc, const double elab, const TwoBody& out ) const;
  double sigma  ( const TwoBody& inc, const double elab, const TwoBody& out,
                  const double cosangle, const int Lmax = 7 ) const;

  double POL( const TwoBody& inc, const double elab, const double cosangle, const int Lmax = 7 ) const;
  double RTH( const TwoBody& inc, const double elab, const double cosangle, const int Lmax = 7 ) const;

  double sigma( const TwoBody& inc, const double s1,
                const TwoBody& out, const double s2,
                const double elab, const double cosangle, const int Lmax ) const;

  double sigma( const TwoBody& inc, const double s1, const double nu1,
                const TwoBody& out, const double s2, const double nu2,
                const double elab, const double cosangle ) const;

  double sigma( const TwoBody& inc, const double s1,
                const TwoBody& out, const double s2, const double elab, const double cosangle ) const;

  complex<double> A( const TwoBody& inc, const double s1, const double nu1,
                     const TwoBody& out, const double s2, const double nu2,
                     const double elab, const double cosangle ) const;

  double B( const TwoBody& inc, const double s1, const TwoBody& out, const double s2, const int L ) const;

  double B( const TwoBody& inc, const TwoBody& out, const int L ) const;

  double LEG( const TwoBody& inc, const double elab, const TwoBody& out, const int L ) const;

  complex<double> NI( const TwoBody& inc,                 const double elab, const int l           ) const;
  complex<double> NI( const TwoBody& inc, const double s, const double elab, const int l           ) const;
  double          NI( const TwoBody& inc, const double s, const double elab, const double cosangle ) const;

  //void   a( const TwoBody& inc, const double elab, const TwoBody& out, const int Lmax,     LTT1::Record* a );
  //void   a( const TwoBody& inc, const double elab, const TwoBody& out, const double eps_c, LTT1::Record* a );

  const Structure& at        ( const int i ) const;
        Structure& at        ( const int i );
  const Structure& operator[]( const int i ) const;
        Structure& operator[]( const int i );

  int  size() const;
  void resize( const int size );

  void CollectFreeParams( vector<Parameter*>* o );

  int npm_free() const;

  Structure* Find( const double J, const int pi );

  bool Find( const TwoBody& partition ) const;
  bool Find( const Particle& a, const Nucleus& b ) const;

  void SetZero_gamma( const Particle& a, const Nucleus& b );

  void Fix_E();
  void Fix_gamma();
  void Fix_gamma( const Particle& a, const Nucleus& b );

  void Print( ostream& os = cout ) const;
  void PrintLatex( ostream& os = cout ) const;

  System* Clear();

  double Az( const TwoBody& inc, const double elab, const double cosangle, const int lmax ) const;

  complex<double> T( const Channel& c1 ) const;

  //ClassDef( RML::System, 0 );

};

}

#endif
