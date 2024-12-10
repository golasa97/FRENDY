#include "ReconResonance/RmatrixLimited/numeric/Tabular.h"
#include "ReconResonance/RmatrixLimited/numeric/Interp.h"

//ClassImp( Numeric::Tabular );


namespace Numeric {

  Tabular:: Tabular( const int code ) : interpcode(code) {}
  Tabular::~Tabular(){}

  void Tabular::push_front( const Datum& o ) {

    int n = this->size();

    vector<Datum> a = *this;

    this->resize(n+1);

      for( int i=0; i<n; i++ ) this->at(i+1) = a[i];

      this->front() = o;

    return;

  }


  const double& Tabular::X( const int i ) const { return this->at(i).X(); }
  const double& Tabular::Y( const int i ) const { return this->at(i).Y(); }
        double& Tabular::X( const int i )       { return this->at(i).X(); }
        double& Tabular::Y( const int i )       { return this->at(i).Y(); }


/*! @brief Calculate integral */
  double Tabular::I() const {
/*
    double sum = 0.0;

      for( int i=0; i<this->size()-1; i++ ) sum += Numeric::I( this->at(i), this->at(i+1), interpcode );

      //for( int i=0; i<this->size()-1; i++ ) cerr << Numeric::I( this->at(i), this->at(i+1), interpcode ) << endl;;
*/
    double sum = 0.0;  Datum d1,d2;

      for( int i=0; i<static_cast<int>(this->size())-1; i++ ) {

        d1 = this->at(i  );
        d2 = this->at(i+1);

        if( d2.X() <= d1.X()  ) continue;

        sum += Numeric::I( d1,d2, interpcode );

      }

    return sum;

  }

  static void construct( double (*function)( const double&, const double* ), const double* params,
                         Datum& r0, Datum& r2, vector<Datum>* trace, vector<Datum>* result,
                         const int& interpcode, const double eps ) {

    // calculate at the middle point

    Datum r1( 0.5*( r0.X()+r2.X() ) );

      r1.Y() = (*function)( r1.X(), params );

    // check if satisfy accuracy

    if( ! Satisfied( r0,r1,r2,interpcode,eps ) ) {

      trace->push_back( r2 );

      construct( function, params, r0,r1,trace,result,interpcode,eps );

    }

    if( trace->empty() ) return;

    // new point

    result->push_back( r2 );

    // step back

    r0 = r2;  r2 = trace->back();  trace->pop_back();

    construct( function, params, r0,r2,trace,result,interpcode,eps );

    return;

  }

  static void construct( double (*function)( const double&, const double* ), const double* params,
                         const double& front, const double& back, Tabular* result,
                         const int& interpcode, const double eps ) {

    Datum r0(front),r2(back);

      r0.Y() = (*function)( r0.X(), params );
      r2.Y() = (*function)( r2.X(), params );

    Datum rlower(r0),rupper(r2);  vector<Datum> trace;

        construct( function, params, r0,r2, &trace, result, interpcode, eps );

      result->push_front( rlower );
      result->push_back ( rupper );

    return;

  }

/*! @brief Set arbitrary function */
  Tabular* Tabular::Set( const double x1, const double x2, double (*function)( const double&, const double* ), const double* params, const double eps ) {

    this->clear();

    construct( function, params, x1,x2, this, interpcode, eps );

    return this;

  }

}
