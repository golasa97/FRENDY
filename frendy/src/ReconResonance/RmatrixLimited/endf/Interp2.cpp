#include "ReconResonance/RmatrixLimited/endf/Interp2.h"
#include "ReconResonance/RmatrixLimited/endf/Interp1.h"
#include "ReconResonance/RmatrixLimited/endf/Numeric.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

/* Two-dimensional interpolation */

namespace ENDF {

void Interp2( const TAB1& a, const TAB1& b, const int interpcode, TAB1* c, const double eps_c ) {
// two-dimensional interpolation

  if( a.Empty() && b.Empty() ) return;

  double x1 = a.C2();
  double x2 = b.C2();

  TAB1 temp1(a),temp2(b);

  // unit-base interp. if necessary

  if( interpcode/10 == 2 ) UnitBase( &temp1, &temp2, c->C2() );

  // get same nodes and interp. scheme

  Uniform( &temp1, &temp2, eps_c );

    c->Set( temp1, true );

    for( int i=0; i<c->size(); i++ ) c->Y(i) = Interp1( x1, temp1.Y(i), x2, temp2.Y(i), interpcode%10, c->C2() );

  return;

}


void Average2( const TAB1& a, const TAB1& b, const int interpcode, TAB1* c, const double eps_c ) {
// averaged distribution with the two-dimensional interpolation

  if( a.Empty() && b.Empty() ) return;

  double x1 = a.C2();
  double x2 = b.C2();

  TAB1 temp1(a),temp2(b);

  // unit-base interp. if necessary

  if( interpcode/10 == 2 ) UnitBase( &temp1, &temp2, x1 );

  // get same nodes and interp. scheme

  Uniform( &temp1, &temp2, eps_c );

    c->Set( temp1, true );

    for( int i=0; i<c->size(); i++ ) c->Y(i) = Average1( x1, temp1.Y(i), x2, temp2.Y(i), interpcode%10 );

}


/* Unit-base interpolation */

void UnitBase( TAB1* a, TAB1* b, const double x ) {

  if( a->Empty() ) return;
  if( b->Empty() ) return;

  //a->Write();
  //b->Write();

  a->Unique();
  b->Unique();

  double E, E1, E2, Epl, Eph, Epl1, Eph1, Epl2, Eph2;

    E  = x;
    E1 = a->C2();
    E2 = b->C2();

    Epl1 = a->Front().X();
    Epl2 = b->Front().X();
    Eph1 = a->Back ().X();
    Eph2 = b->Back ().X();

    Epl = Epl1 + ( Epl2 - Epl1 )*( E - E1 )/( E2 -E1 );
    Eph = Eph1 + ( Eph2 - Eph1 )*( E - E1 )/( E2 -E1 );

    for( int i=0; i<a->NP(); i++ ) a->X(i) = ( a->X(i) - Epl1 ) * ( Eph-Epl )/( Eph1-Epl1 ) + Epl;
    for( int i=0; i<b->NP(); i++ ) b->X(i) = ( b->X(i) - Epl2 ) * ( Eph-Epl )/( Eph2-Epl2 ) + Epl;

    //cerr << ( Eph1-Epl1 )/( Eph-Epl ) << "  " << ( Eph2-Epl2 )/( Eph-Epl ) << endl;

    a->ScaleY( ( Eph1-Epl1 )/( Eph-Epl ) );
    b->ScaleY( ( Eph2-Epl2 )/( Eph-Epl ) );

  return;

}





/*
void Integrate( const TAB1& a, const TAB1& b, const int interpcode, TAB1* ans, const int nrandom ) {
// under development
// MC integration
// nrandom : number of random number generation

  double xmax, xmin, ymax, ymin, zmin(0.0), zmax, sum0;

    ymin = min( a.C2(), b.C2() );
    ymax = max( a.C2(), b.C2() );

  srand( (unsigned)time( NULL ) );

  for( int i=0; i<ans->NP()-1; i++ ) {

    xmin = ans->X(i  );
    xmax = ans->X(i+1);
    zmax = max( max( a.Interp(xmin), a.Interp(xmax) ), max( b.Interp(xmin), b.Interp(xmax) ) );

    sum0 = ( xmax-xmin ) * ( ymax-ymin ) * ( zmax-zmin );

    cerr << ( xmax-xmin ) << "  " <<  ( ymax-ymin ) << "  " << ( zmax-zmin ) << endl;

    double x,y,z;

    int nx = 0;

    for( int j=0; j<nrandom; j++ ) {

      x = xmin + (xmax-xmin) * rand()/(RAND_MAX+1.0);
      y = ymin + (ymax-ymin) * rand()/(RAND_MAX+1.0);
      z = zmin + (zmax-zmin) * rand()/(RAND_MAX+1.0);

      if( z <= Interp2( a, b, interpcode, y, x ) ) nx++;

    }

    ans->Y(i) += sum0 * (double) nx/nrandom / (xmax-xmin);

  }

  return;

}
*/


/*
void Integrate( const TAB1& a, const TAB1& b, const int interpcode, TAB1* ans, const int nrandom ) {

// number of random number generation

  ans->Set( min( a.Front().X(), b.Front().X() ), max( a.Back().X(), b.Back().X() ), 1, 1 );

    for( int i=0; i<a.NP(); i++ ) ans->Put( a.X(i) );
    for( int i=0; i<b.NP(); i++ ) ans->Put( b.X(i) );

  double xmax, xmin, ymax, ymin, zmin(0.0), zmax, sum0;

    ymin = min( a.C2(), b.C2() );
    ymax = max( a.C2(), b.C2() );


  srand( (unsigned)time( NULL ) );

  for( int i=0; i<ans->NP()-1; i++ ) {

    xmin = ans->X(i  );
    xmax = ans->X(i+1);
    zmax = max( max( a.Interp(xmin), a.Interp(xmax) ), max( b.Interp(xmin), b.Interp(xmax) ) );

    sum0 = ( xmax-xmin ) * ( ymax-ymin ) * ( zmax-zmin );

    double x,y,z;

    int nx = 0;

    for( int j=0; j<nrandom; j++ ) {

      x = xmin + (xmax-xmin) * rand()/(RAND_MAX+1.0);
      y = ymin + (ymax-ymin) * rand()/(RAND_MAX+1.0);
      z = zmin + (zmax-zmin) * rand()/(RAND_MAX+1.0);

      if( z <= Interp2( a, b, interpcode, y, x ) ) nx++;

    }

    ans->Y(i) = sum0 * (double) nx/nrandom / (xmax-xmin);

  }

  return;

}
*/


void Intg( const TAB1& a, const TAB1& b, const int interpcode, TAB1* c, const double eps_c ) {

  TAB1 temp1(a),temp2(b);

    Uniform( &temp1, &temp2, eps_c );

  double x1,x2,y1,y2,z;

    x1 = temp1.C2();
    x2 = temp2.C2();

    for( int i=0; i<temp1.size()-1; i++ ) {

      y1 = temp1.I( i );
      y2 = temp2.I( i );

      z  = Integral1( x1, y1, x2, y2, interpcode%20 );

      c->PushBack( temp1.X(i), z, 1 );

    }

    c->PushBack( temp1.Back().X(), 0.0, 1 );

  return;

}



};
