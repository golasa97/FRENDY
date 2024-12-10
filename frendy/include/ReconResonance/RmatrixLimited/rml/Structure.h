#if !defined(___Class_Structure)
    #define  ___Class_Structure

#include <vector>
#include <cmath>
#include <complex>
#include "ReconResonance/RmatrixLimited/rml/Group.h"
#include "ReconResonance/RmatrixLimited/numeric/Parameter.h"
#include "ReconResonance/RmatrixLimited/rml/Coulomb.h"
#include "ReconResonance/RmatrixLimited/rml/Boundary.h"
#include "ReconResonance/RmatrixLimited/rml/Distant.h"

#include <time.h>

typedef complex<double> complex_d;

namespace RML {

/*!
@class Structure
@brief \~japanese 同一の@f$J^{\pi}@f$を持つ励起順位のグループに対しR行列理論に関わる基本計算を行う。
       \~english  A group of excited levels which have the same @f$J^{\pi}@f$. This class also performs R-matrix calculation.
*/
class Structure : public Group {

  struct level { double eigenvalue,Gam;  Exclusive ex_opt; };

  /*double spin;  int parity;*/  double mass;  vector<pair< TwoBody,double> > se;
  
  int nlev,nch,npart;  vector<TwoBody> alpha;  vector<Coulomb> ch;  vector<level> lev;  vector<double> gam;

  bool opt;  // true if use level matrix

  vector<int> permu1,permu2;
  vector<complex_d> M1,M2, WORK1,WORK2;  // M1: A-matrix, M2: X-matrix

  vector<complex_d> R,Yinv;  // temporary matrix for X 

 public:

  Structure();
  Structure( const double J, const int pi );
  virtual ~Structure();

  Structure* Mass( const double m ) { mass = m;  return this; }

  const double& Mass() const { return mass; }
        double& Mass()       { return mass; }

  //double J () const { return spin;   }
  //double pi() const { return parity; }

  Structure* Set( const double J, const int pi );

  Structure* PushBack( const Particle& a, const Nucleus& A );
  Structure* PushBack( const Particle& a, const Nucleus& A, const double S_a );

  Structure* PushBack( const TwoBody& o );
  Structure* PushBack( const TwoBody& o, const double separation_energy );

  double Ba  ( const TwoBody& inc ) const;
  double Qval( const TwoBody& inc, const TwoBody& out ) const;

  int index( const Channel& c ) const;

  const double& gamma( const int& lambda, const int& c ) const;
        double& gamma( const int& lambda, const int& c );

  const complex<double>& L( const int& c ) const;
        complex<double>& L( const int& c );

  Structure* SetOption( const bool option );

  Structure* Configure( const Boundary* condition, const bool option = true );

  Structure* Update( const vector<double>& qval, const double ecm );

  Structure* Solve ( const TwoBody&         inc, const double ecm, const double ba );
  Structure* Solve ( const vector<double>& qval, const double ecm, const double ba );

  Structure* Solve1( const Particle& a, const vector<double>& qval, const double ecm, const double ba );
  Structure* Solve2( const Particle& a, const vector<double>& qval, const double ecm, const double ba );

  Structure* Solve1( const vector<double>& qval, const double ecm, const double ba );
  Structure* Solve2( const vector<double>& qval, const double ecm, const double ba );

  Structure* Solve1();
  Structure* Solve2();

  complex<double> xi( const int& i, const int& j ) const;

  inline complex<double>  A( const int& i, const int& j ) const { return M1[ i*nlev+j ]; }
  inline complex<double>& A( const int& i, const int& j )       { return M1[ i*nlev+j ]; }
  inline complex<double>  X( const int& i, const int& j ) const { return M2[ i*nch +j ]; }
  inline complex<double>& X( const int& i, const int& j )       { return M2[ i*nch +j ]; }

  complex<double> T( const Channel& c1                    ) const;
  complex<double> T( const Channel& c1, const Channel& c2 ) const;

  complex<double> U( const Channel& c1                    ) const;
  complex<double> U( const Channel& c1, const Channel& c2 ) const;

  complex<double> T( const int& i               ) const;
  complex<double> T( const int& i, const int& j ) const;

  complex<double> U( const int& i               ) const;
  complex<double> U( const int& i, const int& j ) const;

  double sigma  ( const TwoBody& inc, const double elab ) const;
  double sigma1 ( const TwoBody& inc, const double elab ) const;
  double sigma2 ( const TwoBody& inc, const double elab ) const;

  double sigma  ( const TwoBody& inc, const double elab, const TwoBody& out ) const;
  double sigma1 ( const TwoBody& inc, const double elab, const TwoBody& out ) const;
  double sigma2 ( const TwoBody& inc, const double elab, const TwoBody& out ) const;

  double sigma_c ( const TwoBody& inc, const double elab ) const;
  double sigma1_c( const TwoBody& inc, const double elab ) const;
  double sigma2_c( const TwoBody& inc, const double elab ) const;

  void Get_sigma_array( const TwoBody& inc, const double elab, double* result ) const;

  complex<double> A( const TwoBody& inc, const double s1, const double nu1,
                     const TwoBody& out, const double s2, const double nu2, const double cosangle ) const;

  double B( const TwoBody& inc, const double s1, const TwoBody& out, const double s2,
            const int L, const Structure* o ) const;

  complex<double> NI( const TwoBody& inc, const double s, const double elab, const int l ) const;
  double          NI( const TwoBody& inc, const double s, const double elab, const double cosangle ) const;

  void Print( ostream& os = cout ) const;

  void PrintLatex( ostream& os = cout ) const;

};

ostream& operator<<( ostream& os, const Structure& o );

}

#endif
