#if !defined(___Class_Nodes)
    #define  ___Class_Nodes

#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"
#include "ReconResonance/RmatrixLimited/endf/TAB2.h"
#include "ReconResonance/RmatrixLimited/endf/TAB1.h"
#include "ReconResonance/RmatrixLimited/endf/Interp1.h"
#include "ReconResonance/RmatrixLimited/endf/Interp2.h"
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"
#include "ReconResonance/RmatrixLimited/basics/AlphaNumeric.h"

using namespace std;
using namespace Basics;
//using namespace Numeric;

namespace ENDF {

/* General functions for TAB2 + deque<Record> */

template<class T> void store( TAB2* o, deque<T>* array, istream& is ) {

  o->Store( is );

    array->resize( o->NZ() );

      for( int i=0; i<o->NZ(); i++ ) array->at(i).Store( is );

  return;

}

template<class T> void read( TAB2* o, deque<T>* array, const char* file_name ) {

  ifstream ifs;

    ifs.open( get_your_directory( file_name ).c_str(), ios::in );

      if( ! ifs.is_open() ) {

        cerr << "!! Failed to open file : " << file_name << endl;  return;

      }

      store( o, array, ifs );

    ifs.close();

  return;

}

template<class T> void write( const TAB2* o, const deque<T>* array, ostream& os, const int MAT, const int MF, const int MT, int* NS ) {

  if( o->NZ() == 0 ) return;

  o->Write( os, MAT,MF,MT,NS );

    for( int i=0; i<o->NZ(); i++ ) array->at(i).Write( os, MAT,MF,MT,NS );

  return;

}

template<class T> void write( const TAB2* o, const deque<T>* array, const char* file_name ) {

  ofstream ofs( get_your_directory( file_name ).c_str() );

    o->Write( ofs );

      for( int i=0; i<o->NZ(); i++ ) array->at(i).Write( ofs );

  return;

}

template<class T> unsigned long number_of_lines( const TAB2* o, const deque<T>* array ) {

  unsigned long n = o->NumberOfLines();

    for( int i=0; i<o->NZ(); i++ ) n += array->at(i).NumberOfLines();

  return n;

}


template<class T> void set_array( TAB2* o, deque<T>* array, const TAB2& a, const deque<T>& b ) {

  if( &a != o ) o->Set( a );  if( &b != array ) *array = b;  return;

}

template<class T> void set_array( TAB2* o, deque<T>* array, const int n, const int interpcode ) {

  o->Set( n, interpcode );  array->resize( n );  return;

}

template<class T> void clear( TAB2* o, deque<T>* array ) {

  o->Clear();  array->clear();  return;

}

template<class T> void push_front( TAB2* o, deque<T>* array, const T& r, const int interpcode ) {

  if( r.empty() ) return;

  if( ! array->empty() && array->front() == r ) return;

    o->PushFront( interpcode );  array->push_front( r );

  return;

}

template<class T> void push_back( TAB2* o, deque<T>* array, const T& r, const int interpcode ) {

  if( r.empty() ) return;

  if( ! array->empty() && array->back() == r ) return;

    o->PushBack( interpcode );  array->push_back( r );

  return;

}

template<class T> void push_front( TAB2* o, deque<T>* array, const TAB2& a, const deque<T>& b, const int interpcode ) {

  if( b.empty() ) return;

  if( array->empty() ) return set_array( o, array, a, b );

  if( array->front().C2() > b.back().C2() ) return;

  TAB2 aa;  deque<T> bb;

    set_array( &aa, &bb, a, b );

    aa.C1() = o->C1();  aa.C2() = o->C2();
    aa.L1() = o->L1();  aa.L2() = o->L2();

    push_back( &aa, &bb, *o, *array, interpcode );

  return set_array( o, array, aa, bb );

}

template<class T> void push_back( TAB2* o, deque<T>* array, const TAB2& a, const deque<T>& b, const int interpcode ) {

  if( b.empty() ) return;

  if( array->empty() ) return set_array( o, array, a,b );

  if( array->back().C2() > b.front().C2() ) return;

  if( eq( array->back().C2(), b.front().C2() ) && array->back() != b.front() ) {

    push_back( o, array, b.front(), a.Front().INT() );

  } else push_back( o, array, b.front(), interpcode );

  for( int i=1; i<a.NZ(); i++ ) push_back( o, array, b[i], a.InterpCode(i-1) );

  return;

}


template<class T> void pop_front( deque<T>* array, const int num ) { for( int i=0; i<num; i++ ) array->pop_front();  return; }
template<class T> void pop_back ( deque<T>* array, const int num ) { for( int i=0; i<num; i++ ) array->pop_back ();  return; }


template<class T> void pop_front( TAB2* o, deque<T>* array, const int num ) {

  for( int i=0; i<num; i++ ) o->PopFront();

  return pop_front( array, num );

}

template<class T> void pop_back( TAB2* o, deque<T>* array, const int num ) {

  for( int i=0; i<num; i++ ) o->PopBack();

  return pop_back( array, num );

}

template<class T> void erase( TAB2* o, deque<T>* array, const int index ) {

  typename deque<T>::iterator it = array->begin();  int i=0;

    for( it = array->begin(); it != array->end(); ) {

      if( i == index ) { it = array->erase(it);  break; } it++; i++;

    }

    o->Erase(index);

  return;

}

template<class T> void erase( TAB2* o, deque<T>* array, const double C2 ) {

  for( int i=0; i<array->size(); i++ )

    if( eq( array->at(i).C2(), C2 ) ) return erase( o, array, i );

  return;

}

template<class T> void thin( TAB2* o, deque<T>* array ) {

  int n = array->size();  vector<double> a;

    if( n <= 2 ) return;

    if( n%2 == 1 ) {

      for( int i=0; i<n; i++ ) if( i%2 == 1 ) a.push_back( array->at(i).C2() );

    }

    else {

      for( int i=1; i<n; i++ ) if( i%2 == 0 ) a.push_back( array->at(i).C2() );

    }

    for( int i=0; i<a.size(); i++ ) erase( o, array, a[i] );

  return;

}


// pop records from the beginnig points where val is evaluated between C1 and C2
template<class T> void cut_below_C1_C2( deque<T>* array, const double val ) {

  if( array->empty() ) return;

  if( val <= array->front().C1() ) return;
  if( val >  array->back ().C2() ) return array->clear();

  int npop = 0;

  for( int i=array->size()-1; i>=0; i-- ) if( array->at(i).C1() <= val ) npop++;

  return pop_front( array, npop-1 );

}

// pop records from the ending points where val is evaluated between C1 and C2
template<class T> void cut_above_C1_C2( deque<T>* array, const double val ) {

  if( array->empty() ) return;

  if( val >= array->back ().C2() ) return;
  if( val <  array->front().C1() ) return array->clear();

  int npop = 0;

    for( int i=0; i<array->size(); i++ ) if( array->at(i).C2() >= val ) npop++;

  return pop_back( array, npop-1 );

}




template<class T> void cut_below( TAB2* o, deque<T>* array, const double C2 ) {

  if( array->empty() ) return;
  if( C2 <= array->front().C2() ) return;
  if( C2 >  array->back ().C2() ) return clear( o, array );

  int npop = 0;

  for( int i=o->NZ()-1; i>=0; i-- ) if( array->at(i).C2() <= C2 ) npop++;

  return pop_front( o, array, npop-1 );

}

template<class T> void cut_above( TAB2* o, deque<T>* array, const double C2 ) {

  if( array->empty() ) return;
  if( C2 >= array->back ().C2() ) return;
  if( C2 <  array->front().C2() ) return clear( o, array );

  int npop = 0;

  for( int i=0; i<o->NZ(); i++ ) if( array->at(i).C2() >= C2 ) npop++;

  return pop_back( o, array, npop-1 );

}

template<class T> void put_clone( TAB2* o, deque<T>* array, const double C2, const double eps_e = 1.e-4 ) {  // 1.e-4 for JENDL-5 (2021/12/3)

  if( array->empty() ) return;

  if( C2 < array->front().C2() ) {

    if( eq( C2, array->front().C2(), eps_e ) ) { array->front().C2() = C2; return; }

    T a = array->front();  a.C2(C2);  push_front( o, array, a, o->Front().INT() );

  }

  if( C2 > array->back().C2() ) {

    T a = array->back();  a.C2(C2);  push_back( o, array, a, o->Back().INT() );

  }

  return;

}

/*
template<class T> void trim_lower( TAB2* o, deque<T>* array, const double C2 ) {

  if( array->empty() ) return;

  if( C2 < array->front().C2() ) {

    T a = array->front();  a.C2(C2);  push_front( o, array, a, o->Front().INT() );

  }

  return;

}

template<class T> void trim_upper( TAB2* o, deque<T>* array, const double C2 ) {

  if( array->empty() ) return;

  if( C2 > array->back().C2() ) {

    T a = array->back();  a.C2(C2);  push_back( o, array, a, o->Back().INT() );

  }

  return;

}
*/

template<class T> bool find( const TAB2* o, const deque<T>* array, const double C2 ) {

  for( int i=0; i<o->NZ(); i++ ) if( eq( C2, array->at(i).C2() ) ) return true;

  return false;

}



template<class T> bool seek( const TAB2* o, const T* array, const double C2 ) {

  if( o->NZ() == 0 ) return false;

  if( C2 < array[        0].C2() ) return false;
  if( C2 > array[o->NZ()-1].C2() ) return false;

  return true;

}

template<class T> bool seek( const TAB2* o, const deque<T>* array, const double C2 ) {

  if( array->empty() ) return false;

  if( C2 < array->front().C2() ) return false;
  if( C2 > array->back ().C2() ) return false;

  return true;

}

template<class T> bool seek( const TAB2* o, const T* array, const double C2, int* index, int* interpcode ) {

  if( ! seek( o, array, C2 ) ) return false;

  for( int i=0; i<o->NZ()-1; i++ ) if( array[i].C2() <= C2 && C2 < array[i+1].C2() ) { *index = i;  break; }

  *interpcode = o->InterpCode( *index );

  return true;

}


template<class T> bool seek( const TAB2* o, const deque<T>* array, const double C2, int* index, int* interpcode ) {

  if( ! seek( o, array, C2 ) ) return false;

  for( int i=0; i<o->NZ()-1; i++ ) if( array->at(i).C2() <= C2 && C2 < array->at(i+1).C2() ) { *index = i;  break; }

  *interpcode = o->InterpCode( *index );

  return true;

}



template<class T> void get_energy_nodes( const deque<T>* array, vector<double>* nodes ) {

  for( int i=0; i<array->size(); i++ ) nodes->push_back( array->at(i).E() );

    sort( nodes->begin(), nodes->end() );
    nodes->erase( unique( nodes->begin(), nodes->end() ), nodes->end() );

  return;

}





template<class T> void interpolate( const TAB2* o, const T* array, T* result, const double eps ) {

  // exactly corresponding data

  for( int i=0; i<o->NZ(); i++ ) if( array[i].C2() == result->C2() ) {

    *result = array[i];  return;
    
  }

  // interp.

  int index, interpcode;

    if( ! seek( o, array, result->C2(), &index, &interpcode ) ) return;

    Interp2( array[index], array[index+1], interpcode, result, eps );

    result->C1() = Interp1( array[index].C2(), array[index].C1(), array[index+1].C2(), array[index+1].C1(), interpcode%20, result->C2() );

  return;

}


template<class T> void interpolate( const TAB2* o, const deque<T>* array, T* result, const double eps ) {

  return interpolate( o, array->data(), result, eps );

}


// array -> results
void broad( const TAB1* array, const int m, const Function1& FWHM, const pair<double,double>* ranges_C2, const int num_of_ranges, TAB1* results, const int interpcode, const double eps, const int maxthreads );
void broad( const TAB1* array, const int m, const Function2& f,    const pair<double,double>* ranges_C2, const int num_of_ranges, TAB1* results, const int interpcode, const double eps, const int maxthreads );

// array -> array broadened (internal) -> results (by interpolation)
void broad( const TAB1* array, const int m, const Function1& FWHM, const pair<double,double>* ranges_C2, const int num_of_ranges, TAB1* results, const int n, const int interpcode = 22, const double eps = 1.e-3, const int maxthreads = 1 );
void broad( const TAB1* array, const int m, const Function2& f,    const pair<double,double>* ranges_C2, const int num_of_ranges, TAB1* results, const int n, const int interpcode = 22, const double eps = 1.e-3, const int maxthreads = 1 );
void broad( const TAB1* array, const int m, const Function1& FWHM, const double& C2min, const double& C2max, TAB1* results, const int n, const int interpcode = 22, const double eps = 1.e-3, const int maxthreads =1 );
void broad( const TAB1* array, const int m, const Function2& f,    const double& C2min, const double& C2max, TAB1* results, const int n, const int interpcode = 22, const double eps = 1.e-3, const int maxthreads =1 );




template<class T> T* replace_energy_range( T* a, const T* b ) {

  if( b->Back ().E() < a->Front().E() ) return a;
  if( b->Front().E() > a->Back ().E() ) return a;

  T lower(*a),upper(*a);

    lower.CutAbove( b->Front().E() );
    upper.CutBelow( b->Back ().E() );

    a->Clear();

    a->PushBack( lower );
    a->PushBack(    *b );
    a->PushBack( upper );

    if( eq( a->E(         0 ), a->E(         1 ) ) ) a->PopFront();
    if( eq( a->E( a->NE()-2 ), a->E( a->NE()-1 ) ) ) a->PopBack ();

  return a;

}


// I/O stream
/*
template<class Record> istream& operator>>( istream& is, Nodes<Record>& ary ) {

  ary.Store( is );  return is;

}


template<class Record> ostream& operator<<( ostream& os, const Nodes<Record>& ary ) {

  ary.Write( os );  return os;

}
*/
//template<class Record> istream& operator>>( istream& is,       Nodes<Record>& ary );
//template<class Record> ostream& operator<<( ostream& os, const Nodes<Record>& ary );

};

#endif
