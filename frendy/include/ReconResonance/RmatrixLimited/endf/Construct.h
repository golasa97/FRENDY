#ifndef _Construct
#define _Construct

#include "ReconResonance/RmatrixLimited/endf/TAB1.h"
#include "ReconResonance/RmatrixLimited/endf/LIST.h"
#include "ReconResonance/RmatrixLimited/endf/Interp1.h"

using namespace ENDF;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T> void construct( double (*function)( const double&, T* ), T* o,
Datum& r0, Datum& r2, vector<Datum>* trace, TAB1* result, const int& interpcode, const double eps, const double eps_x ) {

  // avoid the same x point (or very narrow spacing)

  if( eq( r0.X(), r2.X(), eps_x ) ) return; 

  // calculate at the middle point

  Datum r1( 0.5*( r0.X()+r2.X() ) );

    r1.Y() = (*function)( r1.X(), o );

  // check if satisfy accuracy

  if( ! Satisfied( r0,r1,r2,interpcode,eps ) ) {

    trace->push_back( r2 );

    construct( function, o, r0,r1,trace,result,interpcode,eps,eps_x );

  }

  if( trace->empty() ) return;

  // new point

  result->PushBack( r2, interpcode );

  // step back

  r0 = r2;  r2 = trace->back();  trace->pop_back();

  construct( function, o, r0,r2,trace,result,interpcode,eps,eps_x );

  return;

}

template<class T> void construct( double (*function)( const double&, T* ), T* o,
const double& front, const double& back, TAB1* result, const int& interpcode, const double eps, const double eps_x = 1.e-6 ) {

  //cerr << front << "  " << back << endl;

  Datum r0(front),r2(back);

    r0.Y() = (*function)( r0.X(), o );
    r2.Y() = (*function)( r2.X(), o );

  Datum rlower(r0),rupper(r2);  vector<Datum> trace;

    construct( function, o, r0,r2, &trace, result, interpcode, eps, eps_x );

    result->PushFront( rlower, interpcode );
    result->PushBack ( rupper, interpcode );

  return;

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T1,class T2> void construct( double (*function)( const double&, T1*, T2* ), T1* o1, T2* o2,
Datum& r0, Datum& r2, vector<Datum>* trace, TAB1* result, const int& interpcode, const double eps, const double eps_x ) {

  // avoid the same x point (or very narrow spacing)

  if( eq( r0.X(), r2.X(), eps_x ) ) return; 

  // calculate at the middle point

  Datum r1( 0.5*( r0.X()+r2.X() ) );

    r1.Y() = (*function)( r1.X(), o1,o2 );

  // check if satisfy accuracy

  if( ! Satisfied( r0,r1,r2,interpcode,eps ) ) {

    trace->push_back( r2 );

    construct( function, o1,o2, r0,r1,trace,result,interpcode,eps,eps_x );

  }

  if( trace->empty() ) return;

  // new point

  result->PushBack( r2, interpcode );

  // step back

  r0 = r2;  r2 = trace->back();  trace->pop_back();

  construct( function, o1,o2, r0,r2,trace,result,interpcode,eps,eps_x );

  return;

}

template<class T1,class T2> void construct( double (*function)( const double&, T1*, T2* ), T1* o1, T2* o2,
const double& front, const double& back, TAB1* result, const int& interpcode, const double eps, const double eps_x = 1.e-6 ) {

  Datum r0(front),r2(back);

    r0.Y() = (*function)( r0.X(), o1,o2 );
    r2.Y() = (*function)( r2.X(), o1,o2 );

  Datum rlower(r0),rupper(r2);  vector<Datum> trace;

    construct( function, o1,o2, r0,r2, &trace, result, interpcode, eps, eps_x );

    result->PushFront( rlower, interpcode );
    result->PushBack ( rupper, interpcode );

  return;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T> void construct( void (*function)( LIST*, T* ), T* o,
LIST& r0, LIST& r2, vector<LIST>* trace, vector<TAB1>* result, const int& n, const int& interpcode, const double eps, const double eps_C2 ) {

  if( eq( r0.C2(), r2.C2(), eps_C2 ) ) return; 

  bool converge(true);

    // calculate cross-sections at the middle point

    LIST r1;

      r1.C2( 0.5*( r0.C2()+r2.C2() ) )->resize(n);  (*function)( &r1, o );

    // check if satisfy the accuracy

    //for( int i=0; i<1; i++ ) {
    for( int i=1; i<n; i++ ) {

      converge *= Satisfied( r0.C2(),r0.B(i), r1.C2(),r1.B(i), r2.C2(),r2.B(i), interpcode, eps );

    }

    // go to next if not converge

    if( ! converge ) {

      trace->push_back( r2 );

      construct( function, o, r0,r1, trace, result, n, interpcode, eps, eps_C2 );

    }

    if( trace->empty() ) return;

    // new point

    for( int i=0; i<n; i++ ) result->at(i).PushBack( r2.C2(),r2.B(i), interpcode );

    // step back

    r0 = r2;  r2 = trace->back();  trace->pop_back();

    construct( function, o, r0,r2, trace, result, n, interpcode, eps, eps_C2 );

  return;

}


template<class T> void construct( void (*function)( LIST*, T* ), T* o,
const double& front, const double& back, vector<TAB1>* result, const int n, const int interpcode, const double eps, const double eps_C2 = 1.e-6 ) {

  //cerr << "test1" << endl;

  LIST r0,r2;

    r0.C2( front )->resize(n);  (*function)( &r0, o );
    r2.C2( back  )->resize(n);  (*function)( &r2, o );

  LIST rlower(r0),rupper(r2);  vector<LIST> trace;

    construct( function, o, r0,r2, &trace, result, n, interpcode, eps, eps_C2 );

    for( int i=0; i<n; i++ ) result->at(i).PushFront( rlower.C2(),rlower.B(i), interpcode );
    for( int i=0; i<n; i++ ) result->at(i).PushBack ( rupper.C2(),rupper.B(i), interpcode );

//cerr << rlower.C2() << "  " << result->at(0).NP() << endl;

  return;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
