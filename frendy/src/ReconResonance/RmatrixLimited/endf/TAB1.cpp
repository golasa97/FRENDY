#include "ReconResonance/RmatrixLimited/endf/TAB1.h"
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"
#include "ReconResonance/RmatrixLimited/numeric/Constant.h"
#include "ReconResonance/RmatrixLimited/basics/MultiThread.h"
#include "ReconResonance/RmatrixLimited/numeric/Doppler.h"
#include "ReconResonance/RmatrixLimited/endf/Numeric.h"
#include "ReconResonance/RmatrixLimited/endf/Interp1.h"

#include <iomanip>
#include <cstdlib>
#include <algorithm>

#ifdef Use_CINT
ClassImp( ENDF::TAB1 );
#endif

using namespace Basics;

namespace ENDF {

//using namespace Numeric;


//// static functions ////

//static bool eqx( const double& a, const double& b ) { return eq(a,b,1.e-12); }


// get indeces at a given jump (=step)
static void get_indeces_by_step( const TAB1* o, const int step, vector<int>* result ) {

  int n = o->NP();

    result->push_back(0);

      while( result->back() < n ) result->push_back( result->back() + step );

    if( result->back() >= n ) result->back() = n-1;

  return;

}




// Constructors

/*! @brief Constructor */
TAB1::TAB1() {}

/*!
@brief Constructor
@param[in] is         : input stream
*/
TAB1::TAB1( istream& is ) { this->Store( is ); }

/*!
@brief Constructor
@param[in] file_name  : input file name
*/
TAB1::TAB1( const char* file_name ) { this->Set( file_name ); }

/*!
@brief Constructor
@param[in] file_name  : input file name (file should be normal X-Y table)
@param[in] interpcode : interpolation code
@note ignore lines start with '#'
*/
TAB1::TAB1( const char* file_name, const int interpcode ) { this->Set( file_name, interpcode ); }

/*!
@brief Constructor
@param[in] file_name  : input file name (file should be normal X-Y table)
@param[in] index_x    : index for the x-column
@param[in] index_y    : index for the y-column
@param[in] interpcode : interpolation code
@note ignore lines start with '#'
*/
TAB1::TAB1( const char* file_name, const int index_x, const int index_y, const int interpcode ) {

  this->Set( file_name, index_x, index_y, interpcode );

}

/*!
@brief Constructor
@param[in] file_name  : input file name (file should be normal X-Y table)
@param[in] index_x    : index for the x-column
@param[in] indeices_y : indices for the y-columns, e.g., indices="1,2,3~6"
@param[in] interpcode : interpolation code
@note ignore lines start with '#'
*/
TAB1::TAB1( const char* file_name, const int index_x, const char* indices_y, const int interpcode ) {

  this->Set( file_name, index_x, indices_y, interpcode );

}

/*!
@brief Constructor
@param[in] np         : number of points
@param[in] interpcode : interpolation code
*/
TAB1::TAB1( const int np, const int interpcode ) {

  this->Set( np, interpcode );

}

/*!
@brief Constructor
@param[in] x_min      : minimum value of X
@param[in] x_max      : maximum value of X
@param[in] ndiv       : number of division
@param[in] interpcode : interpolation code
*/
TAB1::TAB1( const double x_min, const double x_max, const int ndiv, const int interpcode ) {

  this->Set( x_min,x_max, ndiv, interpcode );

}

/*!
@brief Constructor
@param[in] o          : (X,Y) pairs
@param[in] np         : number of (X,Y) pairs
@param[in] interpcode : interpolation code
*/
TAB1::TAB1( const Datum* o, const int np, const int interpcode ) {

  this->Set( o, np, interpcode );

}
/*
TAB1::TAB1( const vector<Datum>* o, const int interpcode ) {

  this->Set( o, interpcode );

}
*/

/*!
@brief Constructor
@param[in] x          : X-array
@param[in] np         : number of points
@param[in] interpcode : interpolation code
*/
TAB1::TAB1( const double* x, const int np, const int interpcode ) {

  this->Set( x, np, interpcode );

}

/*!
@brief Constructor
@param[in] x          : X-array
@param[in] y          : Y-array
@param[in] np         : number of points
@param[in] interpcode : interpolation code
*/
TAB1::TAB1( const double* x, const double* y, const int np, const int interpcode ) {

  this->Set( x, y, np, interpcode );

}

/*
TAB1::TAB1( const vector<double>* x, const int interpcode ) {

  this->Set( x, interpcode );

}

TAB1::TAB1( const vector<double>* x, const vector<double>* y, const int interpcode ) {

  this->Set( x, y, interpcode );

}
*/

/*
TAB1::TAB1( const deque <double>* x, const int interpcode ) {

  this->Set( x, interpcode );

}

TAB1::TAB1( const deque <double>* x, const deque <double>* y, const int interpcode ) {

  this->Set( x, y, interpcode );

}
*/

TAB1::~TAB1() {}


/*! @brief Copy constructor */
TAB1::TAB1( const TAB1& o ) { this->Set( o ); }

/*! @brief Assign operator */
TAB1& TAB1::operator=( const TAB1& o ) {

  if( &o != this ) this->Set( o );  return *this;

}



// STL-like methods

const Datum& TAB1::at        ( const int i ) const { return ary[i]; }
      Datum& TAB1::at        ( const int i )       { return ary[i]; }
const Datum& TAB1::operator[]( const int i ) const { return ary[i]; }
      Datum& TAB1::operator[]( const int i )       { return ary[i]; }

const Datum& TAB1::front() const { return ary.front(); }
      Datum& TAB1::front()       { return ary.front(); }
const Datum& TAB1::back () const { return ary.back (); }
      Datum& TAB1::back ()       { return ary.back (); }

int  TAB1::size () const { return ary.size (); }
bool TAB1::empty() const { return ary.empty(); }
void TAB1::clear()       { return ary.clear(); }



// ____ Store Record __________________________________________________________
/*!
@brief Store record
@param[in] is         : input stream
*/
TAB1* TAB1::Store( istream& is ) {

  this->Clear();

  const int vlen = 11;  string xline;

  header.Store( is );

    ary.resize( this->NP() );

     for( int l=0; l<num_of_lines(this->NP(),3); l++ ) {

        getline( is, xline );

          for( int i=0; i<3; i++ ) {

            int j = l*3 + i;  if( j+1 > this->NP() ) break;

	      this->X(j) = dbl_endf( xline.substr(       vlen*i*2, vlen ) );
	      this->Y(j) = dbl_endf( xline.substr(  vlen+vlen*i*2, vlen ) );

          }

      }

  return this;

}


/*!
@brief Read record from file
@param[in] file_name : input file name
*/
int TAB1::Read( const char* file_name ) {

  scan( this, file_name );  return 1;

}

/*
void TAB1::Read( const char* file_name ) {

  scan( this, file_name );  return;

}
*/






static void write( ostream& os, const TAB1* o, const int& n ) {

  int m(3);

    if( n == (num_of_lines(o->NP(),3)-1) && o->NP()%3 > 0 ) m=o->NP()%3;

    for( int i=3*n  ; i<3*n+m; i++ ) os << endf( o->X(i) ) << endf( o->Y(i) );
    for( int i=3*n+m; i<3*n+3; i++ ) os << "           " << "           ";

  return;

}

// ____ Write Record __________________________________________________________
/*!
@brief Write record
@param[in] os : output stream [cout]
*/
void TAB1::Write( ostream& os, const int MAT, const int MF, const int MT, int* NS ) const {

  if( this->NP() == 0 ) return;

/* to be programmed as follows
  header.Write( os, MAT, MF, MT, NS );

  for( int i=0; i<num_of_lines(this->NP(),3); i++ ) {

    write( os, this, i );  os << endf( MAT, MF, MT, NS );

  }

  return;
*/

  string blank = "           ";

  header.Write( os, MAT, MF, MT, NS );

  for( int i=0; i<this->NP(); i++  ) {

    os << endf( this->X(i) ) << endf( this->Y(i) );

      if( (i+1) % 3 == 0 ) os << endf( MAT, MF, MT, NS );

  }

  if( this->NP() % 3 != 0 ) {

    for( int i=0; i<(3-this->NP()%3)*2; i++ ) os << blank;

      os << endf( MAT, MF, MT, NS );

  }

  return;

}

/*!
@brief Write record
@param[in] file_name  : output file name
*/
void TAB1::Write( const char* file_name ) const {
// write record into the file

  return write( this, file_name );

}

/*!
@brief Write record beginning and ending parts
@param[in] num : number of lines for each part
@param[in] os  : output stream [cout]
*/
void TAB1::Write( const int num, ostream& os ) {

  int n = num_of_lines(this->NP(),3);

  if( n <= 2*num ) return this->Write( os );

  header.Write( os );

    for( int i=    0; i<num; i++ ) { write( os, this, i );  os << endl; }

      os << "                 .................................                " << endl;

    for( int i=n-num; i<  n; i++ ) { write( os, this, i );  os << endl; }

  return;

}


// ____ Set record __________________________________________________________
/*!
@brief Set record
@param[in] o          : another TAB1 record
@param[in] option     : true - values of C1,C2,L1,L2 will be ignored [false]
*/
TAB1* TAB1::Set( const TAB1& o, const bool option ) {

#ifdef Use_ROOT
  this->TGraph::operator=( o );  // -ROOT-
#endif

  ary = o.ary;  header.Set( o.header, option );  return this;

}

/*!
@brief Set record
@param[in] np         : number of points
@param[in] interpcode : interpolation code
*/
TAB1* TAB1::Set( const int np, const int interpcode ) {

  header.Set( np, interpcode );  ary.resize( np );  return this;

}

/*!
@brief Set record
@param[in] x_min      : minimum value of X
@param[in] x_max      : maximum value of X
@param[in] ndiv       : number of division
@param[in] interpcode : interpolation code
*/
TAB1* TAB1::Set( const double x_min, const double x_max, const int ndiv, const int interpcode ) {

  this->Set( ndiv+1, interpcode );

  if( interpcode == 1 || interpcode == 2 || interpcode == 4 ) {

    double dx = ( x_max-x_min )/ndiv;

    for( int i=0; i<this->NP(); i++ ) this->X(i) = x_min + dx*i;

  }

  if( interpcode == 3 || interpcode == 5 ) {

    double dx = ( log(x_max)-log(x_min) )/ndiv;

    for( int i=0; i<this->NP(); i++ ) this->X(i) = exp( log(x_min) + dx*i );

    this->Front().X() = x_min;
    this->Back ().X() = x_max;

  }

  for( int i=0; i<this->NP(); i++ ) this->Y(i) = 0.0;

  return this; 

}

/*!
@brief Set record
@param[in] o          : (X,Y) pairs
@param[in] np         : number of (X,Y) pairs
@param[in] interpcode : interpolation code
*/
TAB1* TAB1::Set( const Datum* a, const int np, const int interpcode ) {

  this->Set( np, interpcode );

  for( int i=0; i<this->NP(); i++ ) this->at(i) = a[i];

  return this; 

}
/*
TAB1* TAB1::Set( const vector<Datum>* a, const int interpcode ) {

  this->Set( a->size(), interpcode );

  for( int i=0; i<this->NP(); i++ ) this->at(i) = a->at(i);

  return this; 

}
*/

/*!
@brief Set record
@param[in] x          : X-array
@param[in] np         : number of points
@param[in] interpcode : interpolation code
*/
TAB1* TAB1::Set( const double* x, const int np, const int interpcode ) {

  this->Set( np, interpcode );

  for( int i=0; i<this->NP(); i++ ) this->X(i) = x[i];

  return this; 

}

/*!
@brief Set record
@param[in] x          : X-array
@param[in] y          : Y-array
@param[in] np         : number of points
@param[in] interpcode : interpolation code
*/
TAB1* TAB1::Set( const double* x, const double* y, const int np, const int interpcode ) {

  this->Set( np, interpcode );

  for( int i=0; i<this->NP(); i++ ) {

    this->X(i) = x[i];
    this->Y(i) = y[i];

  }

  return this; 

}

/*
TAB1* TAB1::Set( const vector<double>* x, const int interpcode ) {

  this->Set( x->size(), interpcode );

  for( int i=0; i<this->NP(); i++ ) this->X(i) = x->at(i);

  return this; 

}

TAB1* TAB1::Set( const vector<double>* x, const vector<double>* y, const int interpcode ) {

  this->Set( x->size(), interpcode );

  for( int i=0; i<this->NP(); i++ ) {

    this->X(i) = x->at(i);
    this->Y(i) = y->at(i);

  }

  return this; 

}
*/

/*
TAB1* TAB1::Set( const deque<double>* x, const int interpcode ) {

  this->Set( x->size(), interpcode );

  for( int i=0; i<NP(); i++ ) this->X(i) = x->at(i);

  return this; 

}

TAB1* TAB1::Set( const deque<double>* x, const deque<double>* y, const int interpcode ) {

  this->Set( x->size(), interpcode );

  for( int i=0; i<this->NP(); i++ ) {

    this->X(i) = x->at(i);
    this->Y(i) = y->at(i);

  }

  return this; 

}
*/

/*!
@brief Set record from file (same as Read)
@param[in] file_name : input file name
*/
TAB1* TAB1::Set( const char* file_name ) {

  return scan( this, file_name );

}


/*!
@brief Set record from normal X-Y table
@param[in] interpcode : interpolation code
@note ignore lines start with '#'
*/
TAB1* TAB1::Set( const char* file_name, const int interpcode ) {

  return this->Set( file_name, 0, 1, interpcode );

}




static double at_column( const vector<string>& v, const int index ) {

  return ( index < static_cast<int>(v.size()) ) ? atof( v[index].c_str() ) : 0.0;

}

static double at_column( const vector<string>& v, const vector<int> indices ) {

  double a = 0.0;  for( int i=0; i<static_cast<int>(indices.size()); i++ ) a += at_column(v,indices[i]);  return a;

}

static Datum at_column( const string& line, const int index_x, const int index_y ) {

  vector<string> v;  break_down( line, &v, " " );

  return Datum( at_column(v,index_x), at_column(v,index_y) );

}

//static Datum at_column( const string& line, const int index_x, const string index_y ) {
static Datum at_column( const string& line, const int index_x, const char* index_y ) {

  vector<string> v;  break_down( line, &v, " " );  vector<int> indices_y;  break_down( index_y, &indices_y );

  return Datum( at_column(v,index_x), at_column(v,indices_y) );

}

template<class T> static TAB1* set_columns( TAB1* o, const char* file_name, const int index_x, const T index_y, const int interpcode ) {

  ifstream ifs;

    ifs.open( get_your_directory( file_name ).c_str(), ios::in );

      if( ! ifs.is_open() ) {

        cerr << "!! TAB1::Set -> Failed to open file : " << file_name << endl;  return o;

      }

    string line;

      while( getline( ifs, line ) ) {

        if( line.empty() || line.find('#') != string::npos ) continue;

        o->PushBack( at_column(line,index_x,index_y), interpcode, false );

      }

    ifs.close();

  return o;

}

/*!
@brief Set record from normal X-Y table
@param[in] index_x : index for the x-column
@param[in] index_y : index for the y-column
@param[in] interpcode : interpolation code
@note ignore lines start with '#'
*/
TAB1* TAB1::Set( const char* file_name, const int index_x, const int index_y, const int interpcode ) {

  return set_columns( this, file_name, index_x, index_y, interpcode );

}

/*!
@brief Set record from normal X-Y table
@param[in] index_x : index for the x-column
@param[in] indeices_y : indices for the y-columns, e.g., indices="1,2,3~6"
@param[in] interpcode : interpolation code
@note ignore lines start with '#'
*/
TAB1* TAB1::Set( const char* file_name, const int index_x, const char* indices_y, const int interpcode ) {

  return set_columns( this, file_name, index_x, indices_y, interpcode );

}



/*! @brief Set X-Y table where values of C1,C2,L1,L2 and TGraph will not be copied */ 
TAB1* TAB1::SetArray( const TAB1& o ) {

//this->TGraph::operator=( o );  // -ROOT-

  ary = o.ary;  header.Set( o.header, true );  return this;

//return this->Set(o,true);

}


const double& TAB1::X( const int i ) const { return ary[i].X(); }
      double& TAB1::X( const int i )       { return ary[i].X(); }
const double& TAB1::Y( const int i ) const { return ary[i].Y(); }
      double& TAB1::Y( const int i )       { return ary[i].Y(); }


/*! @brief Minimum value of Y */
double TAB1::Ymin() const {

  if( this->Empty() ) { cerr << "!! TAB1::Ymin -> empty array" << endl;  return 0.0; }

  double y = this->Front().Y();

    for( int i=1; i<this->NP(); i++ ) y = min( y, this->Y(i) );

  return y;

}

/*! @brief Maximum value of Y */
double TAB1::Ymax() const {

  if( this->Empty() ) { cerr << "!! TAB1::Ymax -> empty array" << endl;  return 0.0; }

  double y = this->Front().Y();

    for( int i=1; i<this->NP(); i++ ) y = max( y, this->Y(i) );

  return y;

}



const Datum& TAB1::Front() const { return ary.front(); }
      Datum& TAB1::Front()       { return ary.front(); }
const Datum& TAB1::Back () const { return ary.back (); }
      Datum& TAB1::Back ()       { return ary.back (); }

TAB1* TAB1::Front( const Datum& o ) { this->Front() = o;  return this; }
TAB1* TAB1::Back ( const Datum& o ) { this->Back () = o;  return this; }


/*! @brief Check if the value is duplicated in a row */
bool TAB1::CheckDuplicated( const double& x ) const {

  for( int i=0; i<this->size()-1; i++ ) {

    if( eq( x, this->X(i) ) && eq( x, this->X(i+1) ) ) return true;
  //if( eq( x, this->X(i+1) ) && eq( x, this->X(i+1) ) ) return true; // wrong ! 2021/12/23 (S.K.)

  }

  return false;

}


// items to be checked

/*
static bool check_number_of_points( const TAB1* o ) {

  return ( o->NP() == o->size() && o->NP() > 1 );

}

static bool check_ordering( const TAB1* o, const int& i ) {

  return lt( o->X(i), o->X(i+1) );

}

static bool check_redundancy( const TAB1* o, const int& i ) {

  return ( o->at(i) == o->at(i+1) );

}

static bool check_redundancy2( const TAB1* o, const int& i ) {

  return ( eq( o->Y(i-1), o->Y(i) ) && eq( o->Y(i), o->Y(i+1) ) );

}

static bool check_interp_scheme( const TAB1* o, const int& i ) {

  if( eq( o->X(i), o->X(i+1) ) ) return true;

  int interpcode = o->InterpCode(i);

    bool a = ( interpcode == 3 || interpcode == 5 ) && ( le( o->X(i), 0.0 ) || le( o->X(i+1), 0.0 ) );
    bool b = ( interpcode == 4 || interpcode == 5 ) && ( le( o->Y(i), 0.0 ) || le( o->Y(i+1), 0.0 ) );

  return ( !a && !b );

}


// nw : number of blank
static void diagnose( const TAB1* o, const int i, Document* msg, const int nw, const int& ns, const bool opt ) {

  // ordering

  if( gt( o->X(i), o->X(i+1) ) )

    msg->PushBack(nw) << "=> @NS=" << endf(ns) << " -> wrong ordering : " << endf( o->X(i) ) << "," << endf( o->X(i+1) );

  // interpolation

  int interpcode = o->InterpCode(i);

    if( ne( o->X(i), o->X(i+1) ) ) {

      bool a = ( interpcode == 3 || interpcode == 5 ) && ( le( o->X(i), 0.0 ) || le( o->X(i+1), 0.0 ) );
      bool b = ( interpcode == 4 || interpcode == 5 ) && ( le( o->Y(i), 0.0 ) || le( o->Y(i+1), 0.0 ) );

      if( a || b  )

        msg->PushBack(nw) << "=> @NS=" << endf(ns) << " -> wrong interpolation code = " << interpcode << " : "
                          << endf( o->X(i) ) << "," << endf( o->X(i+1) );

    }

  if( ! opt ) return;

  // redundancy

  if( o->at(i) == o->at(i+1) )

    msg->PushBack(nw) << "=> @NS=" << endf(ns) << " -> redundant point : " << o->at(i);

  return;

}
*/

static void diagnose( const TAB1* o, const int i, Document* result, const int ns, const int level = 0 ) {
// diagnose the i-th interval
// level = 0 : ordering, interpolation
//       = 1 : + redundancy

  // ordering

  if( gt( o->X(i), o->X(i+1) ) )

    result->PushBack() << endf(ns) << " ---> " << endf( o->X(i) ) << "," << endf( o->X(i+1) ) << " : wrong ordering";

  // interpolation

  int interpcode = o->InterpCode(i);

    if( ne( o->X(i), o->X(i+1)) ) {

      if( ( interpcode == 3 || interpcode == 5 ) && ( le( o->X(i), 0.0 ) || le( o->X(i+1), 0.0 ) ) )

        result->PushBack() << endf(ns) << " ---> " << endf( o->X(i) ) << "," << endf( o->X(i+1) )
                           << " : wrong interpolation code = " << interpcode;

      if( ( interpcode == 4 || interpcode == 5 ) && ( le( o->Y(i), 0.0 ) || le( o->Y(i+1), 0.0 ) ) )

        result->PushBack() << endf(ns) << " ---> " << endf( o->X(i) ) << "," << endf( o->X(i+1) )
                           << " : wrong interpolation code = " << interpcode;

    }

  if( level < 1 ) return;

  // redundancy

  if( o->at(i) == o->at(i+1) )

    result->PushBack() << endf(ns) << " ---> " << o->at(i) << " : redundant point";

  return;

}


/*!
@brief Diagnose format, i.e., check
- size of the array
- ordering
- interpolation
- redundancy
@param[in,out] result : checkup list
@param[in,out] ns     : beginning index for number of the lines
*/
void TAB1::Diagnose( Document* result, int* ns ) const {

  if( this->NP() != static_cast<int>(ary.size()) )

    result->PushBack() << endf(*ns) << " ---> NP = " << this->NP() << " : inconsistent with array size";

  if( this->NP() <= 1 )

    result->PushBack() << endf(*ns) << " ---> NP = " << this->NP() << " : no intervals";

  header.Diagnose( result, ns );  (*ns)++;

  for( int i=1; i<this->NP(); i++  ) {

    if( i%3==0 ) (*ns)++;

    diagnose( this, i-1, result, *ns );

  }

  return;

}



/*!
@brief Narrow range
@param[in] x1 : lower X-value
@param[in] x2 : upper X-value
*/
TAB1* TAB1::Narrow( const double x1, const double x2 ) {

  return this->CutBelow( x1 )->CutAbove( x2 );

}

/*!
@brief Extract range
@param[in] x1 : lower X-value
@param[in] x2 : upper X-value
*/
TAB1 TAB1::Extract( const double x1, const double x2 ) const {

  TAB1 a(*this);  return *a.Narrow( x1,x2 );

}


/*!
@brief Cut data above x
@note  the boundary point will be interpolated
*/
TAB1* TAB1::CutAbove( const double x ) {
// discard points above x

  if( this->Empty() ) return this;

  // out of range

  if( gt( x, this->Back ().X() ) ) return this;
  if( lt( x, this->Front().X() ) ) return this->ClearArray();

  // get position

  int index(0);

    for( int ii=0; ii<this->NP(); ii++ ) if( ge( this->X(ii), x ) ) { index = ii; break; }

  // Cut

  header.CutAbove( index );  ary.resize( index+1 );

  if( ! this->Check() ) return this;

  /*
  if( header.Back().INT() == 1 ) {

    this->Back().X() =   x;
    this->Back().Y() = 0.0;

    return this;

  }
  */

  // Interp. edge

  if( eq( x, this->Back().X() ) ) return this;

    this->Back().Y() = Interp1( X(index-1), Y(index-1), X(index), Y(index), this->InterpCode(index-1), x );
    this->Back().X() = x;

  return this;

}


/*!
@brief Cut data below x
@note  the boundary point will be interpolated
*/
TAB1* TAB1::CutBelow( const double x ) {
// discard points below x

//cerr << "------------------------------------------------------------------------------" << endl;
//cerr << "x = " << x << endl;
//cerr << "before" << endl;
//this->Write();

  if( this->Empty() ) return this;

  // out of range

  if( lt( x, this->Front().X() ) ) return this;
  if( gt( x, this->Back ().X() ) ) return this->ClearArray();

  // get position

  int index( this->NP()-1 );

    for( int ii=this->NP()-1; ii>=0; ii-- ) if( le( this->X(ii), x ) ) { index = ii; break; }

//cerr << "index = " << index << endl;

  // Cut

  header.CutBelow( index );

    for( int ii=0; ii<index; ii++ ) ary.pop_front();

//cerr << "after" << endl;
//this->Write();

  if( ! this->Check() ) return this;

  // Interp edge

  if( eq( x, this->Front().X() ) ) return this;

    this->Front().Y() = Interp1( X(0), Y(0), X(1), Y(1), this->InterpCode(0), x );
    this->Front().X() = x;


//if( this->NP() == 2 && eq( this->Front().X(), this->Back().X(), 1.e-15 ) ) this->Clear(); 

//cerr << "------------------------------------------------------------------------------" << endl;

  return this;

}


/*!
@brief Put the new end-point at x (the same Y will be used)
@note  x should be outside the upper-edge
*/
TAB1* TAB1::PutClone( const double x ) {
// put the same last value at x

  if( this->Empty() ) return this;

  if( x <= this->Back().X() ) return this;

  return this->PushBack( x, this->Back().Y(), header.Back().INT() );

}


/*!
@brief Put zero value outside the front/end point
@note  x should be outside the lower/upper edge
*/
TAB1* TAB1::PutZero( const double x, const double eps_e ) {

  if( NP() == 0 ) return this;

  if( x < this->Front().X() && eq( x, this->Front().X(), eps_e ) ) {

    this->Front().X() = x;  return this;

  }

  if( this->Front().X() <= x && x <= this->Back().X() ) return this;

  if( x > this->Back().X() ) {

    this->PushBack( this->Back().X(), 0., 2, false )->PushBack( x, 0., 2 );

  }

  if( x < this->Front().X() ) {

    this->PushFront( this->Front().X(), 0., 2, false )->PushFront( x, 0., 2 );

    //if( NR() > 1 ) header.Front().NBT() += 1;

  }

  return this;

}



/*!
@brief Push a new point from the front
@param[in] x          : X-value
@param[in] y          : Y-value
@param[in] interpcode : interpolation code
@param[in] inspect    : true - avoid unnecessary point,
                        false - do as it is (may leave unnecessary point)
*/
TAB1* TAB1::PushFront( const double x, const double y, const int interpcode, const bool inspect ) {

  return this->PushFront( Datum(x,y), interpcode, inspect );

}

/*!
@brief Push a new point from the back
@param[in] x          : X-value
@param[in] y          : Y-value
@param[in] interpcode : interpolation code
@param[in] inspect    : true - avoid unnecessary point,
                        false - do as it is (may leave unnecessary point)
*/
TAB1* TAB1::PushBack( const double x, const double y, const int interpcode, const bool inspect ) {

  return this->PushBack( Datum(x,y), interpcode, inspect );

}

/*!
@brief Push a new point from the front
@param[in] o          : a (X,Y) pair
@param[in] interpcode : interpolation code
@param[in] inspect    : true - avoid unnecessary point,
                        false - do as it is (may leave unnecessary point)
*/
TAB1* TAB1::PushFront( const Datum& o, const int interpcode, const bool inspect ) {

  // push_back without any inspections

  if( ! inspect ) {

    ary.push_front( o );  header.PushFront( interpcode );  return this;

  }

  // with the same interpolation code

  if( interpcode == 0 ) {

    ary.push_front( o );  header.PushFront();  return this;

  }

  // put single point if empty

  if( this->Empty() ) return this->PushFront( o, 1, false );

  // take care the double points

  if( eq( this->Front().X(), o.X() ) ) {

    if( eq( this->Front().Y(), o.Y() ) ) return this;

    //if( this->NP() == 1 || this->InterpCode(0) == 1 ) return this->Front( o );

    if( this->NP() == 1 ) return this->Front( o );

    if( interpcode == 1 ) return this;

    //return this->PushFront( o, 0 );

    return this->PushFront( o, interpcode, false );

  }

  // outside the range

  if( lt( this->Front().X(), o.X() ) ) return this;

  // the others

  return this->PushFront( o, interpcode, false );

}

/*!
@brief Push a new point from the back
@param[in] o          : a (X,Y) pair
@param[in] interpcode : interpolation code
@param[in] inspect    : true - avoid unnecessary point,
                        false - do as it is (may leave unnecessary point)
*/
TAB1* TAB1::PushBack( const Datum& o, const int interpcode, const bool inspect ) {

  // without any inspections

  if( ! inspect ) {

    ary.push_back( o );  header.PushBack( interpcode );  return this;

  }

  // with the same interpolation code

  if( interpcode == 0 ) {

    ary.push_back( o );  header.PushBack();  return this;

  }

  // put single point if empty

  if( this->Empty() ) return this->PushBack( o, 1, false );

  // take care the double points

  if( eq( this->Back().X(), o.X() ) ) {

    if( eq( this->Back().Y(), o.Y() ) ) return this;

    if( this->NP() == 1 || this->InterpCode( this->NP()-1 ) == 1 ) return this->Back( o );

    //return this->PushBack( o, 0 );

    return this->PushBack( o, interpcode, false );

  }

  // outside the range

  if( gt( this->Back().X(), o.X() ) ) return this;

  // the others

  return this->PushBack( o, interpcode, false );

}


/*!
@brief Push a new data from the front
@param[in] o          : a new data to be pushed
@param[in] interpcode : interpolation code between o.Back() and this->Front()
@param[in] inspect    : true - avoid unnecessary point,
                        false - do as it is (may leave unnecessary point)
*/
TAB1* TAB1::PushFront( const TAB1& o, const int interpcode, const bool inspect ) {

  if( o.    Empty() ) return this;
//if( this->Empty() ) return this->Set( o, true );
  if( this->Empty() ) return this->SetArray( o );

  Datum a = this->Front();  int inter_a = this->InterpCode(        0 );
  Datum b = o.     Back();  int inter_b = o.    InterpCode( o.NP()-1 );

  // b -> a

  int inter = interpcode;

    if( eq( a.X(), b.X() ) ) {
/*
      inter = inter_b;

      if( eq( a.Y(), 0.0 ) ) inter = inter_a;
*/
      inter = inter_a;

      if( eq( b.Y(), 0.0 ) ) inter = inter_b;

    }

    this->PushFront( b, inter, inspect );

    for( int i=o.size()-2; i>=0; i-- ) this->PushFront( o.at(i), o.InterpCode(i), false );

  return this;

}



/*!
@brief Push a new data from the back
@param[in] o          : a new data to be pushed
@param[in] interpcode : interpolation code between this->Back() and o.Front()
@param[in] inspect    : true - avoid unnecessary point,
                        false - do as it is (may leave unnecessary point)
*/
TAB1* TAB1::PushBack( const TAB1& o, const int interpcode, const bool inspect ) {

  if( o.    Empty() ) return this;
//if( this->Empty() ) return this->Set( o, true );
  if( this->Empty() ) return this->SetArray( o );

  Datum a = this->Back ();  int inter_a = this->InterpCode( this->NP()-1 );
  Datum b = o.    Front();  int inter_b = o.    InterpCode(            0 );

  // a <- b

  int inter = interpcode;

    if( eq( a.X(), b.X() ) ) {

      inter = inter_b;

      if( eq( a.Y(), 0.0 ) ) inter = inter_a;

    }

    this->PushBack( b, inter, inspect );

    for( int i=1; i<o.size(); i++ ) this->PushBack( o.at(i), o.InterpCode( i-1 ), false );

  return this;

}


/*!
@brief Remove points from the front
@param[in] num  : number of points to be removed
*/
TAB1* TAB1::PopFront( const int num ) {
// num : number of points

  for( int i=0; i<num; i++ ) {

    header.PopFront();  ary.pop_front();

  }

  return this;

}

/*!
@brief Remove points from the back
@param[in] num  : number of points to be removed
*/
TAB1* TAB1::PopBack( const int num ) {
// num : number of points

  for( int i=0; i<num; i++ ) {

    header.PopBack();  ary.pop_back();

  }

  return this;

}


/*!
@brief Connect a new data to the front
@note to be used for the unique interpolation code
*/
TAB1* TAB1::ResizeFront( const TAB1& o ) {
// extend array with new data (to be used for unique interpolation code)

  if( this->Empty() ) return this->Set(o);

  TAB1 a(o);

    a.C1() = o.C1();  a.C2() = o.C2();
    a.L1() = o.L1();  a.L2() = o.L2();

    a.ResizeBack( *this );

  return this->Set(a);

}

/*!
@brief Connect a new data to the back
@note to be used for the unique interpolation code
*/
TAB1* TAB1::ResizeBack( const TAB1& o ) {
// extend array with new data (to be used for unique interpolation code)

//if( this->Empty() ) return this->Set(o);
  if( this->Empty() ) return this->SetArray(o);

  if( this->Back() == o.Front() ) this->PopBack();

  int n0 = this->NP();  int n1 = o.NP();  int n = n0+n1;

  ary.resize(n);

    for( int i=n0; i<n; i++ ) ary[i] = o[i-n0];

  header[0].NBT() += n1;

  return this->NP(n);

}


/*! @brief Replace an interval with new data */
TAB1* TAB1::Replace( const TAB1& o ) {
// replace

  if( ! o.Check() ) return this;

  // out of range

  if( ! this->Seek( o.Front().X() ) ) return this;
  if( ! this->Seek( o.Back ().X() ) ) return this;

  // replace

  TAB1 upper(*this);

    upper.CutBelow( o.Back ().X() );

  return this->CutAbove( o.Front().X() )->PushBack( o )->PushBack( upper );

}




/*!
@brief Trim the lower edge : same as this->CutBelow( x )->PutZero( x )
@param[in] x  : new boundary
*/
TAB1* TAB1::TrimLower( const double x ) {

  return this->CutBelow( x )->PutZero( x );

}

/*!
@brief Trim the lower edge : same as this->CutUpper( x )->PutZero( x )
@param[in] x  : new boundary
*/
TAB1* TAB1::TrimUpper( const double x ) {

  return this->CutAbove( x )->PutZero( x );

}


bool TAB1::CheckAll_X_equal_to( const double val ) const { for( int i=0; i<this->NP(); i++ ) if( ne( this->X(i), val ) ) return false;  return true; }
bool TAB1::CheckAll_Y_equal_to( const double val ) const { for( int i=0; i<this->NP(); i++ ) if( ne( this->Y(i), val ) ) return false;  return true; }


bool TAB1::CheckAll_X_less_than( const double val ) const { for( int i=0; i<this->NP(); i++ ) if( this->X(i) > val ) return false;  return true; }

bool TAB1::CheckAll_Y_less_than( const double val ) const { for( int i=0; i<this->NP(); i++ ) if( this->Y(i) > val ) return false;  return true; }


static bool erase_one_time_2( TAB1* o ) {

  if( o->NP() < 2 ) return false;

    for( int i=0; i<o->NP()-1; i++ )

      if( eq( o->X(i), o->X(i+1) ) && eq( o->Y(i), o->Y(i+1) ) ) { o->Remove(i);  return true; }

  return false;

}

static bool erase_one_time_3( TAB1* o ) {

  if( o->NP() < 3 ) return false;

    for( int i=1; i<o->NP()-1; i++ )

      if( eq( o->Y(i-1), o->Y(i) ) && eq( o->Y(i), o->Y(i+1) ) ) { o->Remove(i);  return true; }

  return false;

}

/*! @brief Remove redundant poins
- if the same Y-value appears more than 3 times in a row
- if the same (X,Y) values are given in a row
*/
TAB1* TAB1::Trim() {

  while( erase_one_time_2( this ) ) {};
  while( erase_one_time_3( this ) ) {};

  return this;

}


/*!
@brief Remove redundancy
@param[in] option  : true - clear array if all the Y-values are zero
*/
TAB1* TAB1::Update( const bool option ) {

  if( this->NP() == 0 ) return this;

  // clear if only one point

  if( this->NP() == 1 ) return this->ClearArray();

  // take care double-points
/*
  vector<TAB1> a;

    this->Split( &a );  this->ClearArray();

    for( int i=0; i<a.size(); i++ ) this->PushBack( a[i] );
*/

  // give zero for very-very small Y-values

  //for( int i=0; i<this->NP(); i++ ) if( eq( this->Y(i), 0.0 ) ) this->Y(i) = 0.0;

  // remove duplicated points at front

  //while( this->at(0) == this->at(1) ) { this->PopFront(); }

    //if( this->NP() == 1 ) return this->Update();



  // removethe same X-points at the end/back

  while( eq( this->X(0), this->X(1) ) ) {

    this->PopFront();  if( this->NP() == 1 ) break;

  }

  while( eq( this->X( this->NP()-1 ), this->X( this->NP()-2 ) ) ) {

    this->PopBack();  if( this->NP() == 1 ) break;

  }

  if( ! option ) return this;

  // check if all the values are zero

  if( this->CheckAll_Y_equal_to(0.0) ) return this->Clear();


  // additional corrections for JENDL-5 (2021/11/2)
  //while( erase_one_time( this ) ) {};

  return this;

/*
  for( int i=0; i<this->NP(); i++ ) if( ne( this->Y(i), 0.0 ) ) return this;

  return this->Clear();
*/
}





/*!
@brief Put a new point at x
@note duplication will be avoided. nothing to be done if x is outside the range
*/
TAB1* TAB1::Put( const double x ) {
// put point at x with interpolation (duplication is not allowed)
// nothing to be done if x is already given or x is outside the range

  //cerr << "put0" << endl;

  if( ! this->Seek( x ) ) return this;

  //this->Write();
  //cerr << x << endl;

  /*
  //cerr << "put1" << endl;

  if( this->Find( x ) && ! allow_double_points ) return this;

  //cerr << "put2" << endl;

  TAB1 temp = *this;

    temp.CutBelow( x );

    //cerr << "put3 " << x << endl;

    this->CutAbove( x );

    //cerr << "put4 " << x << endl;

    this->PushBack( *temp.PopFront(), temp.InterpCode(0) );

    //cerr << "put5 " << x << endl;

  return this;

  //return this->CutAbove( x )->PushBack( *temp.CutBelow( x )->PopFront() );
  */

  if( this->CheckDuplicated(x) ) return this;

  TAB1 upper(*this);

    upper.CutBelow( x );

  return this->CutAbove( x )->PushBack( upper );

}


/*!
@brief Put double points at x
@note nothing to be done if x is not given, at the both ends, outside the range
*/
TAB1* TAB1::PutSame( const double x ) {

  //if( eq( x, this->Front().X() ) ) { this->PushFront( this->Front(), 1, false ); return this; }
  //if( eq( x, this->Back ().X() ) ) { this->PushBack ( this->Back (), 1, false ); return this; }

  if( ge( x, this->Back ().X() ) ) return this;
  if( le( x, this->Front().X() ) ) return this;

  if( this->CheckDuplicated(x) ) return this;

  TAB1 upper(*this);

    upper.CutBelow( x );

  return this->CutAbove( x )->PushBack( upper.Front(), 1, false )->PushBack( upper, upper.InterpCode(0) );

}

/*!
@brief Put X values by the interpolation
*/
TAB1* TAB1::PutXvaleus( const TAB1* o ) {

  for( int i=0; i<o->NP(); i++ ) this->Put( o->X(i) );  return this;

}


bool TAB1::CheckDuplication( int* index ) const {
// check if there is duplication
// index : position where it is

  for( int i=0; i<this->size()-1; i++ ) {

    if( ary[i] == ary[i+1] ) { *index = i+1; return true; }

  }

  return false;

}


static void remove( TAB1* o, const int index, const int interpcode ) {
// remove point
// interpcode - 0      : use interpolation one point before [default]
//              others : interpolation is specified

  int n = o->size();

    if( index ==   0 ) { o->PopFront();  return; }
    if( index == n-1 ) { o->PopBack ();  return; }

  TAB1 upper(*o);

    for( int i=0; i<n-index; i++ ) o->PopBack ();
    for( int i=0; i<1+index; i++ ) upper.PopFront();

    o->PushBack( upper, interpcode );

  return;

}

/*!
@brief Remove a point
@param[in] index      : a point to be removed
@param[in] interpcode : 0 - use interpolation one point before, [default]
                        otherwise interpolation code should be specified
*/
TAB1* TAB1::Remove( const int index, const int interpcode ) {

  remove( this, index, interpcode );  return this;

}

/*!
@brief Remove a point
@param[in] x          : a point to be removed
@param[in] interpcode : 0 - use interpolation one point before,
                        otherwise interpolation code should be specified
*/
TAB1* TAB1::Remove( const double x, const int interpcode ) {

  int index;

  if( ! this->Find( x, &index ) ) return this;

    remove( this, index, interpcode );

  return this;

}



/*! @brief Set zero for Y <= y_min */
TAB1* TAB1::Truncate( const double y_min ) {

  //for( int i=0; i<this->size(); i++ ) if( this->Y(i) < y_min ) this->Y(i) = 0.0; 

  for( int i=0; i<this->size(); i++ ) if( le( this->Y(i), y_min ) ) this->Y(i) = 0.0; 

  //this->Trim()->Correct();

  return this->Update();

}

/*
// check if the same Y-value exists 3 times in a row
static bool check_same_y_3times( const TAB1* o, int* index ) {

  int n = o->size();

  for( int i=0; i<n-2; i++ )

    if( o->Y(i) == o->Y(i+1) && o->Y(i+1) == o->Y(i+2) ) {

      *index = i+1;  return true;

    }

  return false;

}

// remove redundant poins (double points are not allowed)
static void trim( TAB1* o ) {

  int index;

    while( check_same_y_3times( o, &index ) ) o->Remove( index );

  return;

}
*/

/*! @brief Remove redundant poins
@note remove points if the same Y-value exists more than 3 times in a row
*/
/*
TAB1* TAB1::Trim() {

  vector<TAB1> a;

    this->Split( &a );  this->ClearArray();

    for( int i=0; i<a.size(); i++ ) {

      trim( &a[i] );   this->PushBack( a[i] );

    }

  return this;

}
*/



static void correct( TAB1* o ) {

  TAB1 a;

    a.PushBack( o->Front() );

    for( int i=1; i<o->size(); i++ ) {

      int inter = o->InterpCode(i-1);

      // Log-Y interp. for Y=zero

/*
      if( o->Y(i-1) == 0.0 && inter == 4 ) inter = 2;
      if( o->Y(i-1) == 0.0 && inter == 5 ) inter = 3;
      if( o->Y(i  ) == 0.0 && inter == 4 ) inter = 2;
      if( o->Y(i  ) == 0.0 && inter == 5 ) inter = 3;
*/
      if( o->Y(i-1) == 0.0 && inter == 4 ) inter = 2;
      if( o->Y(i-1) == 0.0 && inter == 5 ) inter = 2;
      if( o->Y(i  ) == 0.0 && inter == 4 ) inter = 2;
      if( o->Y(i  ) == 0.0 && inter == 5 ) inter = 2;

      a.PushBack( o->at(i), inter );

    }

    o->Set( a, true );

  return;

}

/*! @brief Correct interpolation code
@note interpolation code will be corrected if Lin-Log(4) or Log-Log(5) is used for Y=0.0
*/
TAB1* TAB1::Correct() {

  if( this->empty() ) return this;

  bool q = false;

    for( int i=0; i<this->NR(); i++ ) q = q || ( header.at(i).INT() > 3 );

    if( ! q ) return this;


  vector<TAB1> a;

    this->Split( &a );  this->ClearArray();

    for( int i=0; i<static_cast<int>(a.size()); i++ ) {

      correct( &a[i] );  this->PushBack( a[i] );

    }

  return this;

}




/*! @brief Remove all the duplicated points */
TAB1* TAB1::Unique() {
// remove all the duplicated points

  int index;

  while( this->CheckDuplication( &index ) ) {

    remove( this, index, this->InterpCode(index) );

  }

  return this;

}


/*! @brief Clear TAB2 and X-Y table */
TAB1* TAB1::Clear() {

  header.Clear();  ary.clear();  return this;

}

/*! @brief Clear X-Y table */
TAB1* TAB1::ClearArray() {

  header.ClearArray();  ary.clear();  return this;

}


bool TAB1::Empty() const { return (this->NP() == 0) ? true : false; }


bool TAB1::Find( const double& x, const double eps ) const {

  for( int i=0; i<this->NP(); i++ ) if( eq( x, this->X(i), eps ) ) return true;

  return false;

}

bool TAB1::Find( const double x ) const {

//for( int i=0; i<this->NP(); i++ ) if( this->X(i) == x ) return true;
  for( int i=0; i<this->NP(); i++ ) if( eq( x, this->X(i) ) ) return true;

  return false;

}

bool TAB1::Find( const double x, int* index ) const {
// find point

  for( int i=0; i<this->size(); i++ )

    if( eq( this->X(i), x ) ) {

      *index = i;  return true;

    }

  return false;

}


/*! @brief Calculate integral for the i-th interval */
double TAB1::I( const int i ) const {
// Get value of integral for i-th interval

  return Integral1( X(i), Y(i), X(i+1), Y(i+1), this->InterpCode(i) );

}



/*! @brief Calculate integral */
double TAB1::I() const {
// Get value of integral over whole range

  double sum = 0.0;

    for( int i=0; i<NP()-1; i++ ) sum += this->I(i);

  return sum;

}

/*! @brief Calculate integral between x1 and x2 */
double TAB1::I( const double x1, const double x2 ) const {
// Get value of integral in a range between x1 and x2

  double sum = 0.0;

  if( NP() <=  1 ) return sum;

  if( ge(x1,x2) ) return sum;

  double xmin = this->Front().X();
  double xmax = this->Back ().X();

  if( ge( x1,xmax ) ) return sum;
  if( le( x2,xmin ) ) return sum;

  // check points

  int index1, interpcode1;
  int index2, interpcode2;

  this->Seek( x1, &index1, &interpcode1 );
  this->Seek( x2, &index2, &interpcode2 );


  // covered range : x1...x2

  if( le(x1,xmin) && le(xmax,x2) ) return this->I();

  // covered range : ...x1...x2

  if( ( le(xmin,x1) && lt(x1,xmax) ) && ge(x2,xmax) ) {

    sum += Integral1( x1,Interp(x1), X(index1+1),Y(index1+1), InterpCode(index1) );

    for( int i=index1+1; i<NP()-1; i++ ) sum += Integral1( X(i),Y(i), X(i+1),Y(i+1), InterpCode(i) );

    return sum;

  }

  // covered range : x1...x2...

  if( le(x1,xmin) && ( lt(xmin,x2) && le(x2,xmax) ) ) {

    for( int i=0; i<index2; i++ ) sum += Integral1( X(i),Y(i), X(i+1),Y(i+1), InterpCode(i) );

    sum += Integral1( X(index2),Y(index2), x2,Interp(x2), InterpCode(index2) );

    return sum;

  }

  // covered range : ...x1...x2...

  if( index1 == index2 ) return Integral1( x1,Interp(x1), x2,Interp(x2), InterpCode(index1) );

  sum += Integral1( x1,Interp(x1), X(index1+1),Y(index1+1), InterpCode(index1) );

  for( int i=index1+1; i<index2; i++ ) sum += Integral1( X(i),Y(i), X(i+1),Y(i+1), InterpCode(i) );

  sum += Integral1( X(index2),Y(index2), x2,Interp(x2), InterpCode(index2) );

  return sum;

}



static void print_titles( ostream& os, const char* text, const char* front_space ) {

  if( text == NULL ) return;

  vector<string> titles;

    if( split( text, &titles ) < 2 ) return;

  string blank(front_space);  blank.pop_back();

    os << '#' << blank << setw(11) << titles[0] << setw(14) << titles[1] << endl;

  return;

}

/*!
@brief Print X-Y table
@param[in] os   : output stream [std::cout]
@param[in] text : title for X and Y columns, e.g, text="X,Y". [NULL]
@note I shall recommend you to use this function after linearizing data
*/
void TAB1::PrintColumns( ostream& os, const char* text, const char* front_space ) const {

  print_titles( os, text, front_space );

  os.setf( ios::scientific );

    for( int i=0; i<this->NP(); i++ ) os << front_space << setw(13) << setprecision(6) << right << this->X(i) << "  " <<  this->Y(i) << endl;

  os.unsetf( ios::scientific );

  return;

}

/*!
@brief Print begining and ending parts of the X-Y table
@param[in] os          : output stream
@param[in] text        : title for X and Y columns, e.g, text="X,Y".
@param[in] num_of_rows : number of rows for each ends
@note I shall recommend you to use this function after linearizing data
*/
void TAB1::PrintColumns( ostream& os, const char* text, const int num_of_rows, const char* front_space ) const {

  print_titles( os, text, front_space );

  int n = num_of_rows;  string blank(front_space);

    if( num_of_rows*2 > this->NP() ) return this->PrintColumns( os, NULL, front_space );

    os.setf( ios::scientific );

      for( int i=           0; i<         n; i++ ) os << blank << setw(13) << setprecision(6) << right << this->X(i) << "  " <<  this->Y(i) << endl;
                                                   os << blank << "  .....................  " << endl;
      for( int i=this->NP()-n; i<this->NP(); i++ ) os << blank << setw(13) << setprecision(6) << right << this->X(i) << "  " <<  this->Y(i) << endl;

    os.unsetf( ios::scientific );

  return;

}


/*!
@brief Print X-Y table
@param[in] file_name : output file name
@param[in] text      : title for X and Y columns, e.g, text="X,Y". [NULL]
@note I shall recommend you to use this function after linearizing data
*/
void TAB1::PrintColumns( const char* file_name, const char* text ) const {

  ofstream ofs( get_your_directory( file_name ).c_str() );

  return this->PrintColumns( ofs, text );

}

/*!
@brief Print X-Y table
@param[in] file_name : output file name
@param[in] text      : title for X and Y columns, e.g, text="X,Y". [NULL]
@note I shall recommend you to use this function after linearizing data
*/
void TAB1::PrintColumns( const string file_name, const char* text ) const {

  return this->PrintColumns( file_name.c_str(), text );

}


TAB1* TAB1::C1( const double val ) { header.C1(val); return this; }
TAB1* TAB1::C2( const double val ) { header.C2(val); return this; }
TAB1* TAB1::L1( const int    val ) { header.L1(val); return this; }
TAB1* TAB1::L2( const int    val ) { header.L2(val); return this; }
TAB1* TAB1::NR( const int    val ) { header.NR(val); return this; }
TAB1* TAB1::NP( const int    val ) { header.NZ(val); return this; }

const double& TAB1::C1() const { return header.C1(); }
      double& TAB1::C1()       { return header.C1(); }
const double& TAB1::C2() const { return header.C2(); }
      double& TAB1::C2()       { return header.C2(); }
const int&    TAB1::L1() const { return header.L1(); }
      int&    TAB1::L1()       { return header.L1(); }
const int&    TAB1::L2() const { return header.L2(); }
      int&    TAB1::L2()       { return header.L2(); }
const int&    TAB1::NR() const { return header.NR(); }
      int&    TAB1::NR()       { return header.NR(); }
const int&    TAB1::NP() const { return header.NZ(); }
      int&    TAB1::NP()       { return header.NZ(); }

const int& TAB1::NBT( const int i ) const { return header.NBT(i); }
      int& TAB1::NBT( const int i )       { return header.NBT(i); }
const int& TAB1::INT( const int i ) const { return header.INT(i); }
      int& TAB1::INT( const int i )       { return header.INT(i); }

int TAB1::InterpCode( const int index ) const { return header.InterpCode(index); }



/*! @brief Print data with translation
@param[in] text   : variable names to be printed ["C1,C2,L1,L2,NR,NP/X,Y"]
@param[in] os     : output stream [std::cout]
@param[in,out] ns : line number to be incremented [NULL]
@param[in] opt    : translate variables [1]
@note opt :
@li 0 - Print header information without translation
@li 1 - Print header information with translation [default]
@li 2 - Print header information with translation + interpolation & X-Y table (opt works as in TAB1::PrintColumns)
*/
void TAB1::Translate( ostream& os, unsigned long* ns, const int opt, const int width_of_int, const char* text ) const {

  vector<string> t;  int n = split( text, &t, '/' );

    header.Translate( os,ns,opt, width_of_int, t[0].c_str() );

      if( opt>1 && n>1 ) this->PrintColumns( os, t[1].c_str(), opt, front_space_for_translation );

    if( ns != NULL ) (*ns) += num_of_lines( this->NP(), 3 );

  return;

}


TAB1* TAB1::SetY( const double val ) { for( int i=0; i<NP(); i++ ) Y(i)  = val; return this; }

/*! @brief Scale all the X-values */
TAB1* TAB1::ScaleX( const double fact ) { for( int i=0; i<NP(); i++ ) X(i) *= fact; return this; }
/*! @brief Scale all the Y-values */
TAB1* TAB1::ScaleY( const double fact ) { for( int i=0; i<NP(); i++ ) Y(i) *= fact; return this; }

/*!
@brief Scale X-values
@param[in] func : arbitrary function f(X)
*/
TAB1* TAB1::ScaleX( double (*func)( const double& ) ) {

  for( int i=0; i<this->NP(); i++ ) this->X(i) *= (*func)( this->X(i) );  return this;

}

/*!
@brief Scale X-values
@param[in] func : arbitrary function f(X)
@param[in] (Xmin,Xmax) : range of X to be scaled
*/
TAB1* TAB1::ScaleX( double (*func)( const double& ), const double Xmin, const double Xmax ) {

  for( int i=0; i<this->NP(); i++ ) {

    if( ge( this->X(i), Xmin ) && le( this->X(i), Xmax ) ) this->X(i) *= (*func)( this->X(i) );

  }

  return this;

}

/*!
@brief Scale Y-values
@param[in] func : arbitrary function f(X)
*/
TAB1* TAB1::ScaleY( double (*func)( const double& ) ) {

  for( int i=0; i<this->NP(); i++ ) this->Y(i) *= (*func)( this->X(i) );  return this;

}

/*!
@brief Scale Y-values
@param[in] func : arbitrary function f(X)
@param[in] (Xmin,Xmax) : range of X to be scaled
*/
TAB1* TAB1::ScaleY( double (*func)( const double& ), const double Xmin, const double Xmax ) {

  for( int i=0; i<this->NP(); i++ ) {

    if( ge( this->X(i), Xmin ) && le( this->X(i), Xmax ) ) this->Y(i) *= (*func)( this->X(i) );

  }

  return this;

}


TAB1* TAB1::ShiftX( const double val ) { for( int i=0; i<NP(); i++ ) X(i) += val; return this; }
TAB1* TAB1::ShiftY( const double val ) { for( int i=0; i<NP(); i++ ) Y(i) += val; return this; }

/*!
@brief Shift X-values
@param[in] func : arbitrary function f(X)
*/
TAB1* TAB1::ShiftX( double (*func)( const double& ) ) {

  for( int i=0; i<this->NP(); i++ ) this->X(i) += (*func)( this->X(i) );  return this;

}

/*!
@brief Shift X-values
@param[in] func : arbitrary function f(X)
@param[in] (Xmin,Xmax) : range of X to be scaled
*/
TAB1* TAB1::ShiftX( double (*func)( const double& ), const double Xmin, const double Xmax ) {

  for( int i=0; i<this->NP(); i++ ) {

    if( ge( this->X(i), Xmin ) && le( this->X(i), Xmax ) ) this->X(i) += (*func)( this->X(i) );

  }

  return this;

}

/*!
@brief Shift Y-values
@param[in] func : arbitrary function f(X)
*/
TAB1* TAB1::ShiftY( double (*func)( const double& ) ) {

  for( int i=0; i<this->NP(); i++ ) this->Y(i) += (*func)( this->X(i) );  return this;

}

/*!
@brief Shift Y-values
@param[in] func : arbitrary function f(X)
@param[in] (Xmin,Xmax) : range of X to be scaled
*/
TAB1* TAB1::ShiftY( double (*func)( const double& ), const double Xmin, const double Xmax ) {

  for( int i=0; i<this->NP(); i++ ) {

    if( ge( this->X(i), Xmin ) && le( this->X(i), Xmax ) ) this->Y(i) += (*func)( this->X(i) );

  }

  return this;

}


TAB1* TAB1::PowerX( const double val ) { for( int i=0; i<NP(); i++ ) X(i) = pow(X(i),val); return this; }
TAB1* TAB1::PowerY( const double val ) { for( int i=0; i<NP(); i++ ) Y(i) = pow(Y(i),val); return this; }

/*! @brief conversion of X=cosine to X=angle (degree) */
TAB1* TAB1::Cos2a() {

  for( int i=0; i<this->NP(); i++ ) this->X(i) = acos( this->X(i) ) /M_PI * 180.;

  return this->Reverse();

}




/*!
@brief Transform the base
@f{eqnarray*}{
  X' & = & (X-X_{min}) \times \frac{X'_{max}-X'_{min}}{X_{max}-X_{min}} + X'_{min} \\
  Y' & = & Y \times \frac{X_{max}-X_{min}}{X'_{max}-X'_{min}}
@f}
@param[in] Xmin : @f$X'_{min}@f$ (minimum value of X after transformation) [0.0]
@param[in] Xmax : @f$X'_{max}@f$ (maximum value of X after transformation) [1.0]
@note Integral value will be the same. This function may be used for, e.g., the "unit-base" transformation by giving Xmin=0.0 and Xmax=1.0.
@code

  TAB1 a = ...;

  double xmin = a.Front().X();
  double xmax = a.Back ().X();

  a.TransformBase();  // Unit-base transformation

  // ... do something here ...

  a.TransformBase( xmin, xmax );  // turn back to normal base

@endcode
*/
TAB1* TAB1::TransformBase( const double Xmin, const double Xmax ) {

  if( this->Empty() ) return this;

  double Xmin0,Xmax0;

    this->Unique();

    Xmin0 = this->Front().X();
    Xmax0 = this->Back ().X();

    for( int i=0; i<this->NP(); i++ ) this->X(i) = ( this->X(i) - Xmin0 ) * ( Xmax-Xmin )/( Xmax0-Xmin0 ) + Xmin;

      this->ScaleY( ( Xmax0-Xmin0 )/( Xmax-Xmin ) );

  return this;

}


/*! @brief Get Y-value through the interpolation */
double TAB1::Interp( const double x ) const {
// Calculate interpolated value at x-value

  if( this->NP() == 0 ) return 0.0;

  if( this->NP() == 1 && eq(x,this->Front().X()) ) return this->Front().Y();

  // exact

  //for( int i=0; i<NP(); i++ ) if( X(i) == x ) return this->Y(i); 
  //for( int i=0; i<NP(); i++ ) if( eq( X(i),x ) ) return this->Y(i); 

  // check entry

  int index, interpcode;

  if( ! this->Seek( x, &index, &interpcode ) ) return 0.0;

  // interp.

  //cerr << x << "  " << index << "  " << interpcode << endl;

  return Interp1( X(index),Y(index), X(index+1),Y(index+1), interpcode, x );

}

/*! @brief Get Y-value through the interpolation */
double TAB1::operator()( const double x ) const { return this->Interp(x); }





/*! @brief Calculate averaged value between x1 and x2 */
static double average( const TAB1* o, const double x1, const double x2 ) {

  if( eq(x1,x2) ) return 0.0;

  return o->I( x1,x2 )/( x2-x1 );

}

/*! @brief Calculate averaged value between x1 and x2 */
double TAB1::Average( const double x1, const double x2 ) const {

  return average( this, x1,x2 );

}


TAB1* TAB1::Average() {

  TAB1 a;

    for( int i=0; i<this->NP()-1; i++ ) {

      double x1 = this->X(i  );
      double x2 = this->X(i+1);
      double y1 = this->Y(i  );
      double y2 = this->Y(i+1);

      if( eq(x2,x1) ) continue;

      a.PushBack( x1, Integral1( x1,y1,x2,y2, this->InterpCode(i) )/(x2-x1), 1 );

    }

     a.Back().X() = this->Back().X();

  return this->Set( a );

}

/*! @brief Average with a constant bin
@param[in] dx : constant interval ( default = 0.0 : use original intervals )
*/
TAB1* TAB1::Average( const double dx ) {

  TAB1 a;  double x = this->Front().X();

    a.PushBack( x, average(this,x,x+dx), 1 );

  do {

    x += dx;

    a.PushBack( x, average(this,x,x+dx), 1 );

  } while( le( a.Back().X(), this->Back().X() ) );

  a.Back().Y() = a.Y( a.size()-2 );  // suggested by N.Iwamoto (2020/6/14)

  a.C1() = this->C1();  a.C2() = this->C2();
  a.L1() = this->L1();  a.L2() = this->L2();

  return this->SetArray( a );

}

/*!
@brief Average with arbitrary bins
@param[in] x     : bin array
@param[in] nbins : number of the bins
*/
TAB1* TAB1::Average( const double* x, const int nbins ) {

  if( nbins < 1 ) {

    cerr << "!! TAB1::Average -> not allowed, bin size = " << nbins << endl;  return this;

  }

  TAB1 a;

    for( int i=0; i<nbins; i++ ) a.PushBack( x[i], average(this,x[i],x[i+1]), 1 );

  a.PushBack( x[nbins], a.Back().Y(), 1 );

  a.C1() = this->C1();  a.C2() = this->C2();
  a.L1() = this->L1();  a.L2() = this->L2();

  return this->SetArray( a );

}

/*!
@brief Average with arbitrary bins
@param[in] x     : bin array
@param[in] nbins : number of the bins
@param[in] xmin  : starting point of averaging
*/
TAB1* TAB1::Average( const double* x, const int nbins, const double xmin ) {

  TAB1 a = *this;

    a.Average( x, nbins )->CutBelow( xmin );

  return this->CutAbove( xmin )->PushBack( a );

}

/*
TAB1* TAB1::Average( const int nstep, const double eps_c ) {

  if( nstep <= 0 ) return this;

  vector<double> x;

  for( int i=0; i<this->size(); i++ ) {

    if( i%nstep == 0 ) x.push_back( this->X(i) );

  }

  if( ne( x.back(), this->Back().X() ) ) x.push_back( this->Back().X() );

  return this->Average( &x[0], x.size()-1, eps_c );

}
*/

/*!
@brief Average with constant bins
@param[in] ndiv : number of the division
*/
TAB1* TAB1::Average( const int ndiv ) {

  if( this->size() <= ndiv+1 ) return this->Average( 0.0 );

  double xmin = this->Front().X();
  double xmax = this->Back ().X();

  TAB1 a( xmin,xmax, ndiv, 1 );

  for( int i=0; i<a.size()-1; i++ ) a.Y(i) = average( this, a.X(i), a.X(i+1) );

    //a.Back().Y() = this->Interp( a.Back().X() );

    a.Back().Y() = a.Y( a.size()-2 );  // suggested by N.Iwamoto (2020/6/14)

  return this->SetArray( a );

}


TAB1* TAB1::Average( const double xmin, const double xmax, const int ndiv ) {

  TAB1 a( xmin,xmax, ndiv, 1 );

    for( int i=0; i<a.size()-1; i++ ) a.Y(i) = this->Average( a.X(i), a.X(i+1) );

    a.Back().Y() = a.Y( a.size()-2 );  // suggested by N.Iwamoto (2020/6/14)

  return this->SetArray( a );

}


/*!
@brief Resize number of bins for histogram (INT=1)
@param[in] step : number of bins to be unified
@note tabular data is forced to histogram (INT=1)
*/
TAB1* TAB1::Rebin( const int step ) {

  if( step <= 1 ) return this->Average();

  vector<int> index;  get_indeces_by_step( this, step, &index );  int n = index.size();

  vector<double> x(n);  for( int i=0; i<n; i++ ) x[i] = this->X( index[i] );

  return this->Average( x.data(), n-1 );

}




static double gauss( double (*FWHM)( const double& ), const double& x0, const double& x ) {
// normal distribution

  double sigma = (*FWHM)( x0 )/2.354820;  // standard deviation

  return 1./ sqrt(2.*M_PI)/sigma * exp( -0.5*pow( ( x-x0 )/sigma, 2. ) );

}

static double integral( const Datum& lower, const Datum& upper, const int& interpcode,
                        const double& x, double (*FWHM)( const double& ), const double eps ) {
// calculate integral for the broadening at interval (lower <-> upper)
// FWHM : arbitrary functional form for the full width at half maximum
// eps  : accuracy of the integration

  int ndiv(1);  TAB1 a,b;  double Ia,Ib;

    a.Set( lower.X() ,upper.X(), ndiv, 2 );

      a.Front().Y() = lower.Y() * gauss( FWHM, lower.X(), x );
      a.Back ().Y() = upper.Y() * gauss( FWHM, upper.X(), x );

      b = a;

      Ia = a.I();
      Ib = b.I();

    do {

      a = b;  Ia = Ib;  b.Set( lower.X() ,upper.X(), ++ndiv, 2 );

      for( int i=0; i<ndiv+1; i++ )

        b.Y(i) = Interp1( lower,upper, interpcode, b.X(i) ) * gauss( FWHM, b.X(i), x );

      Ib = b.I();

    } while( fabs( 1.-Ib/Ia ) > eps );

  return Ia;

}

static double integral( const TAB1* o, const unsigned long& j, const double& x, double (*FWHM)( const double& ), const double eps ) {
// calculate integral for the broadening at j-th interval
// FWHM : arbitrary functional form for the full width at half maximum
// eps  : accuracy of the integration

  return integral( o->at(j), o->at(j+1), o->InterpCode(j), x, FWHM, eps );

}

///@cond
struct ARG_Integral {

  unsigned long jmin,jmax;  deque<double> I;

};
///@endcond

static void calculate_integral( const TAB1* o, const double* x, const unsigned long& n,
const unsigned long& i0, const unsigned long& i1,
double (*FWHM)( const double& ), vector<ARG_Integral>* result, const double eps ) {
// calculate integral for the broadening
// FWHM : arbitrary functional form for the full width at half maximum
// eps  : accuracy of the integration

  unsigned long ii;  double I;

    for( unsigned long i=i0; i<=i1; i++ ) {

      ii = i-i0;  // index for the matrix

      result->at(ii).jmin = i  ;  // j-min
      result->at(ii).jmax = i-1;  // j-max

      for( unsigned long j=i; j>0; j-- ) {  // go backward

        I = integral( o, j-1, x[i], FWHM, eps );

        if( eq( I, 0.0 ) ) break;

        result->at(ii).jmin = j-1;
        result->at(ii).I.push_front( I );

      }


      for( unsigned long j=i; j<n-1; j++ ) {  // go forward

        I = integral( o, j, x[i], FWHM, eps );

        if( eq( I, 0.0 ) ) break;

        result->at(ii).jmax = j;
        result->at(ii).I.push_back( I );

      }

      //cerr << result->at(ii).L1() << "  " << result->at(ii).L2() << endl;

    }

  return;

}

/*! @brief Broad distribution with an arbitrary resolution function
@param[in]  x      x-nodes where the calculation will be performed
@param[in]  n      size of the x-nodes
@param[in]  i0     beginning index of x-points
@param[in]  i1     end       index of x-points
@param[in]  FWHM   an arbitrary resolution function
@param[out] result broadened distribution
@param[in]  eps    accuracy of the integration
*/
static void broad( const TAB1* o, const double* x, const unsigned long& n, const unsigned long& i0, const unsigned long& i1, double (*FWHM)( const double& ), TAB1* result, const double eps ) {

  vector<ARG_Integral> I(i1-i0+1);

  /*vector<LIST> I(i1-i0+1);*/  unsigned long ii,jmin,jmax;

    result->Set( i1-i0+1 );

    calculate_integral( o,x,n,i0,i1,FWHM,&I,eps );

    for( unsigned long i=i0; i<=i1; i++ ) {

      ii = i-i0;

      jmin = I[ii].jmin;
      jmax = I[ii].jmax;

      result->X(ii) = x[i];
      result->Y(ii) =  0.0;

      for( unsigned long j=jmin; j<=jmax; j++ ) result->Y(ii) += I[ii].I[j-jmin];

    }

  return;

}


///@cond
struct ARG_TAB1_BroadA {

  const TAB1* obj;  int n,i0,i1;  const double* x;  double (*FWHM)( const double& );
  TAB1 result;  double eps;  pthread_mutex_t* mutex; pthread_cond_t* cond;  int* maxthreads;  int* nthreads;

};
///@endcond


static void* broad_a( void* o ) {

    ARG_TAB1_BroadA* a = ( ARG_TAB1_BroadA* ) o;

  Wait(a);

      if( a->i0 < a->i1 ) broad( a->obj, a->x, a->n, a->i0, a->i1-1, a->FWHM, &a->result, a->eps );

  Signal(a);

  return NULL;

};

/*! @brief Broad data with normal (gaussian) distribution
@param[in]  FWHM          an arbitrary resolution function
@param[in]  eps           accuracy of the interpolation/integration
@param[in]  maxthreads    maximum number of the threads
@attention  original x-points will be used for the nodes
            therefore, need to take care the range of the each interval
*/
TAB1* TAB1::Broad( double (*FWHM)( const double& ), const double eps, const int maxthreads ) {
// broad distribution with given resolution
// original points are assumed to be linearly interpolated with an enough accuracy
// therefore, original x-points are used for the broadening
// FWHM : arbitrary functional form for the full width at half maximum
// eps  : accuracy of the integration [default= 1.e-3]

  *this += 1.e-28;

  double xmin = this->Front().X();
  double xmax = this->Back ().X();

  // take care the boundaries

  //double dummy_lower_x = 1.e-5;
  //double dummy_lower_y = this->Front().Y();

  double dummy_upper_x = 1.5*this->Back().X();
  double dummy_upper_y =     this->Back().Y();

    //this->PushFront( dummy_lower_x, dummy_lower_y );
    this->PushBack ( dummy_upper_x, dummy_upper_y );


  // number of points

  unsigned long n = this->NP();

  // nodes

  double* x = new double[n];

    for( unsigned long i=0; i<n; i++ ) x[i] = this->X(i);

  // number of range

  int ndiv( maxthreads * max( int(n)/2500, 1 ) );
  vector<unsigned int> index;  unsigned int div(n/ndiv),mod(n%ndiv);

    for( int i=0; i<ndiv+1; i++ ) index.push_back( i*div );

      index.back() += mod;

  // broad

  TAB1 a;

  if( maxthreads <= 1 ) {  // with single-thread

    TAB1 b;  int i0,i1;

      for( int i=0; i<static_cast<int>(index.size())-1; i++ ) {

        i0 = index[i  ];
        i1 = index[i+1];

        broad( this, x,n, i0,i1-1, FWHM, b.Clear(), eps );

        a.ResizeBack( b );

      }

  }

  else {  // with multi-threads

    vector<ARG_TAB1_BroadA> ta(index.size()-1);

      for( int i=0; i<static_cast<int>(ta.size()); i++ ) {

        ta[i].obj    = this;
        ta[i].x      = x;
        ta[i].n      = n;
        ta[i].FWHM   = FWHM;
        ta[i].i0     = index[i  ];
        ta[i].i1     = index[i+1];
        ta[i].eps    = eps;

      }

      ExecuteMultiThread( broad_a, &ta, maxthreads );

      for( int i=0; i<static_cast<int>(ta.size()); i++ ) a.ResizeBack( ta[i].result );

  }

  delete [] x;

  this->Set( a, true );

  this->CutBelow( xmin );
  this->CutAbove( xmax );

  return this->Thin( eps );

}


// normal distribution
static double dist_at( const Function1* FWHM, const double&x, const double& y ) {

  double sigma = FWHM->Value( x )/2.354820;

  return 1./sqrt(2.*M_PI)/sigma * exp( -0.5*pow( ( y-x )/sigma, 2. ) );

}

// arbitrary distrubution
static double dist_at( const Function2* f, const double&x, const double& y ) { return f->Value(x,y); }

template<typename Function> static double broad( const TAB1* o, const int& j, const double& x, const Function* f, const double eps ) {
// calculate integral for the broadening at j-th interval
// f : FWHM (Function1) or arbitrary function (Function2)
// eps  : accuracy of the integration

  double x0 = o->X(j  );  double y0 = o->Y(j  );
  double x1 = o->X(j+1);  double y1 = o->Y(j+1);

  int ndiv(1);  TAB1 a,b;  //double sigma;

    a.Set( x0,x1,ndiv,2 );

      a.Front().Y() = y0;
      a.Back ().Y() = y1;

    do {

      a = b;  b.Set( x0,x1, ++ndiv, 2 );

      for( int i=0; i<ndiv+1; i++ ) {

        b.Y(i) = ENDF::Interp1( x0,y0,x1,y1, 2, b.X(i) ) * dist_at( f, b.X(i), x );

      }

    } while( fabs( 1.-b.I()/a.I() ) > eps );

/*
      double sigma0 = FWHM.Value( x0 )/2.354820;  // standard deviation
      double sigma1 = FWHM.Value( x1 )/2.354820;  // standard deviation

      a.Front().Y() = y0 / sqrt(2.*M_PI)/sigma0 * exp( -0.5*pow( ( x-x0 )/sigma0, 2. ) );
      a.Back ().Y() = y1 / sqrt(2.*M_PI)/sigma1 * exp( -0.5*pow( ( x-x1 )/sigma1, 2. ) );
*/

//cerr << x0 << "  " << x1 << "  " << a.I() << endl;

  return a.I();

}

template<typename Function> static double broad( const int& i, const TAB1* o, const Function* f, const double eps ) {
// broad distribution with given resolution (for internal use)
// f : FWHM (Function1) or arbitrary function (Function2)
// eps  : accuracy of the integration

  // go backward

  vector<double> sum1;  int j1 = 0;  int n1 = 0;

    if( i >= 1 ) sum1.push_back( broad( o, i-1, o->X(i), f, eps ) );

    for( int j=i-2; j>0; j-- ) {  j1++;

      sum1.push_back( sum1.back() + broad( o, j, o->X(i), f, eps ) );

      if( eq( sum1[j1],sum1[j1-1] ) ) n1++;

      if( n1 > 3 ) break;

    }

  // go forward

  vector<double> sum2;  int j2 = 0;  int n2 = 0;

    //cerr << i << "  " << o->X(i) << "  " << o->X(i+1) << "  "  << broad( o, i, o->X(i), FWHM, eps ) << endl;

    if( i < o->NP()-1 ) sum2.push_back( broad( o, i, o->X(i), f, eps ) );

    for( int j=i+1; j<o->NP()-1; j++ ) {  j2++;

      sum2.push_back( sum2.back() + broad( o, j, o->X(i), f, eps ) );

      if( eq( sum2[j2],sum2[j2-1] ) ) n2++;

      if( n2 > 3 ) break;

    }

  double sum = 0.0;

    sum += ( sum1.empty() ? 0.0 : sum1.back() );
    sum += ( sum2.empty() ? 0.0 : sum2.back() );

  return sum;

}

///@cond
template<typename Function> struct arg_broad {

  const TAB1* object;  int i0,i1;  const Function* f;  TAB1* result;  double eps;
  pthread_mutex_t* mutex; pthread_cond_t* cond;  int* maxthreads;  int* nthreads;

};
///@endcond

template<typename Function> static void* broad( void* o ) {

  arg_broad<Function>* a = ( arg_broad<Function>* ) o;

    Wait(a);

      for( int i=a->i0; i<a->i1; i++ ) a->result->Y(i) = broad( i, a->object, a->f, a->eps );

    Signal(a);

  return NULL;

};

static void chop( const int i0, const int i1, const int ndiv, vector<int>* result ) {

  int istep = (i1-i0)/ndiv, ndiv2 = ndiv;

  if( (i1-i0) < ndiv ) ndiv2 = 1;

    result->resize( ndiv2 );

      for( int n=0; n<ndiv2; n++ ) result->at(n) = i0 + n*istep;

    result->push_back(i1);

  return;

}

template<typename Function> static void broad( const TAB1* object, const Function* f, const int i0, const int i1,
TAB1* result, const double eps, const int maxthreads ) {

  if( f->is_nullptr() ) return;

  if( maxthreads == 1 ) {

    for( int i=i0; i<i1; i++ ) result->Y(i) = broad( i, object, f, eps );  return;

  }

  vector<int> index;

    chop( i0,i1,maxthreads, &index );

  vector<arg_broad<Function> > t( index.size()-1 );

    for( int k=0; k<t.size(); k++ ) {

      t[k].i0 = index[k  ];
      t[k].i1 = index[k+1];
      t[k].object = object;
      t[k].result = result;
      t[k].f   = f;
      t[k].eps = eps;

    }

    ExecuteMultiThread( broad<Function>, &t, maxthreads );

  return;

}

template<typename Function> static TAB1* broad( TAB1* o, const Function* f, const pair<double,double>* ranges, const int n, const double eps, const int maxthreads ) {

  if( f->is_nullptr() ) return o;

  TAB1 a(*o);

    for( int k=0; k<n; k++ ) {

      double x0 = ranges[k].first;
      double x1 = ranges[k].second;

      int i0,i1;

        for( i0=o->NP()-1; i0>=0;       i0-- ) if( o->X(i0) <= x0 ) break;
        for( i1=0;         i1< o->NP(); i1++ ) if( o->X(i1) >= x1 ) break;

      broad( &a,f,i0,i1,o, eps, maxthreads );

    }

  return o->Thin( eps );

}

template<typename Function> static TAB1* broad( TAB1* o, const Function* f, const double xmin, const double xmax, const double eps, const int maxthreads ) {

  pair<double,double> range[1] = { make_pair(xmin,xmax) };

  return broad( o,f,range,1,eps,maxthreads );

}


/*! @brief Broad data with the normal (gaussian) distribution
@param[in]  FWHM       : X-dependent functional form @f$ f(X) @f$ for full width at half maximum (FWHM)
@param[in]  ranges     : X-ranges where broadening is performed
@param[in]  n          : number of X-ranges
@param[in]  eps        : accuracy of the interpolation/integration
@param[in]  maxthreads : maximum number of the threads
*/
TAB1* TAB1::Broad( const Function1& FWHM, const pair<double,double>* ranges, const int n, const double eps, const int maxthreads ) { return broad( this,&FWHM,ranges,n ,eps,maxthreads ); }

/*! @brief Broad data with the normal (gaussian) distribution
@param[in]  FWHM       : X-dependent functional form @f$ f(X) @f$ for full width at half maximum (FWHM)
@param[in]  xmin,xmax  : X-range where broadening is performed
@param[in]  eps        : accuracy of the interpolation/integration
@param[in]  maxthreads : maximum number of the threads
*/
TAB1* TAB1::Broad( const Function1& FWHM, const double xmin, const double xmax,           const double eps, const int maxthreads ) { return broad( this,&FWHM,xmin,xmax,eps,maxthreads ); }

/*! @brief Broad distribution with an arbitrary resolution function
@param[in]  f          : an arbitrary resolution function @f$f(X,X')@f$
@param[in]  ranges     : X-ranges where broadening is performed
@param[in]  n          : number of X-ranges
@param[in]  eps        : accuracy of the interpolation/integration
@param[in]  maxthreads : maximum number of the threads
*/
TAB1* TAB1::Broad( const Function2& f, const pair<double,double>* ranges, const int n, const double eps, const int maxthreads ) { return broad( this,&f,ranges,n ,eps,maxthreads ); }

/*! @brief Broad distribution with an arbitrary resolution function
@param[in]  f          : an arbitrary resolution function @f$f(X,X')@f$
@param[in]  xmin,xmax  : X-range where broadening is performed
@param[in]  eps        : accuracy of the interpolation/integration
@param[in]  maxthreads : maximum number of the threads
*/
TAB1* TAB1::Broad( const Function2& f, const double xmin, const double xmax,           const double eps, const int maxthreads ) { return broad( this,&f,xmin,xmax,eps,maxthreads ); }


static void broad( const TAB1* o, const double* v_nodes, const double& u, Doppler* first, Doppler* second,
const unsigned long& i0, const unsigned long& i1, TAB1* result ) {
// Dopper cross-section with tabulated linearly interpolable point data
// v_nodes: nodes for velocity of the particle (c)
// first  : integral for the first term
// second : integral for the first term
// u      : velocity of the target (c)
// i0     : beginning point of v
// i1     : end point of v 

  result->Set( i1-i0+1 );

  int ii,jj;  unsigned long jmin,jmax;
  double v,vv,uu,uuu,uuuu;
  double Y0,Y1,w0,w1,ww0,ww1,a,b,t[5];

    uu = u*u;  uuu = uu*u;  uuuu = uuu*u;

    for( unsigned long i=i0; i<=i1; i++ ) {

      v = v_nodes[i];  vv = v*v;  ii = i-i0;

      result->X(ii) = o->X(i);
      result->Y(ii) =     0.0;

      // first term

      //cerr << first->jmin(i) << "  " << first->jmax(i) << endl;

      jmin = first->jmin(ii);
      jmax = first->jmax(ii);

      for( unsigned long j=jmin; j<=jmax; j++ ) {

        Y0 = o->Y(j  );  w0 = v_nodes[j  ];  ww0 = w0*w0;
        Y1 = o->Y(j+1);  w1 = v_nodes[j+1];  ww1 = w1*w1;

        if( eq(w0,w1) ) continue; 

        a = ( ww1*Y0-ww0*Y1 )/(ww1-ww0);  // [barn]
        b = (     Y1-    Y0 )/(ww1-ww0);  // [barn/c^2]

        t[0] = a       + b*vv;
        t[1] = 2*a*u/v + 4*b*u*v;
        t[2] = a*uu/vv + 6*b*uu;
        t[3] =           4*b*uuu/v;
        t[4] =           b*uuuu/vv;

        //jj = j-i0;

        jj = j-jmin;

        result->Y(ii) += t[0] * first->I(ii,jj,0)
                       + t[1] * first->I(ii,jj,1)
                       + t[2] * first->I(ii,jj,2)
                       + t[3] * first->I(ii,jj,3)
                       + t[4] * first->I(ii,jj,4);

      }

      // second term

      //cerr << second->jmin(i) << "  " << second->jmax(i) << endl;

      jmin = second->jmin(ii);
      jmax = second->jmax(ii);

      for( unsigned long j=jmin; j<=jmax; j++ ) {

        Y0 = o->Y(j  );  w0 = v_nodes[j  ];  ww0 = w0*w0;
        Y1 = o->Y(j+1);  w1 = v_nodes[j+1];  ww1 = w1*w1;

        if( eq(w0,w1) ) continue; 

        a = ( ww1*Y0-ww0*Y1 )/(ww1-ww0);  // [barn]
        b = (     Y1-    Y0 )/(ww1-ww0);  // [barn/c^2]

        t[0] = a       + b*vv;
        t[1] = 2*a*u/v + 4*b*u*v;
        t[2] = a*uu/vv + 6*b*uu;
        t[3] =           4*b*uuu/v;
        t[4] =           b*uuuu/vv;

        //jj = j-i0;

        jj = j-jmin;

        result->Y(ii) -= t[0] * second->I(ii,jj,0)
                       + t[1] * second->I(ii,jj,1)
                       + t[2] * second->I(ii,jj,2)
                       + t[3] * second->I(ii,jj,3)
                       + t[4] * second->I(ii,jj,4);

      }

    }

    result->ScaleY( 0.5 );

  return;

}


static void broad( const TAB1* o, const double* v, const unsigned long& n, const int& i0, const int& i1, const double& u, TAB1* result ) {

  Doppler first,second;  // integrals

    //cerr << "update" << endl;
    first .Update1( v,n, u, i0,i1 );
    second.Update2( v,n, u, i0,i1 );

    //cerr << "broad" << endl;
    broad( o, v,u, &first, &second, i0,i1, result );

  return;

}

///@cond
struct ARG_TAB1_Broad {

  const TAB1* obj;  const double* v;  int n,i0,i1;  double u;  TAB1 result; 
  pthread_mutex_t* mutex; pthread_cond_t* cond;  int* maxthreads;  int* nthreads;

};
///@endcond

static void* broad( void* o ) {

    ARG_TAB1_Broad* a = ( ARG_TAB1_Broad* ) o;

  Wait(a);

      if( a->i0 < a->i1 ) broad( a->obj, a->v, a->n, a->i0, a->i1-1, a->u, &a->result );

  Signal(a);

  return NULL;

};


/*! @brief Dopper cross-section for tabulated linearly interpolable point data
@param[in]  m          : particle mass (eV/c^2)
@param[in]  M          : target   mass (eV/c^2)
@param[in]  T          : temparature (K)
@param[in]  eps        : accuracy of interpolation for the data thnning
@param[in]  maxthreads : maximum number of the threads            
*/
TAB1* TAB1::Broad( const double m, const double M, const double T, const double eps, const int maxthreads ) {

  if( eq(T,0.0) ) return this;

  // real boundary

  double xmin = this->Front().X();
  double xmax = this->Back ().X();

  // take care the boundaries

  double dummy_lower_x = 0.0;
//double dummy_lower_y = 0.0;
  double dummy_lower_y = this->Front().Y();

  double dummy_upper_x = 100000.*xmax;
  double dummy_upper_y = this->Back().Y();

    this->PushFront( dummy_lower_x, dummy_lower_y );
    this->PushBack ( dummy_upper_x, dummy_upper_y );

  // number of points

  unsigned long n = this->NP();

  // velocity at nodes

  double* v = new double[n];

    for( unsigned long i=0; i<n; i++ ) v[i] = sqrt( 2.*this->X(i)/m );

  // velocity of the target

  double u = sqrt( 2.*Constant::k_Boltzmann*T/M );  // [c]

  // number of range

  int ndiv( maxthreads * max( int(n)/2500, 1 ) );  unsigned int div(n/ndiv),mod(n%ndiv);
  vector<unsigned int> index;

    /*
    if( n >    5000 ) ndiv *=   2;
    if( n >   10000 ) ndiv *=   5;
    if( n >   50000 ) ndiv *=   7;
    if( n >  100000 ) ndiv *=  15;
    if( n >  500000 ) ndiv *=  30;
    if( n > 1000000 ) ndiv *= 100;
    */

    for( int i=0; i<ndiv+1; i++ ) index.push_back( i*div );

      index.back() += mod;

  // broad

  TAB1 a;

  if( maxthreads <= 1 ) {  // with single-thread

    TAB1 b;  int i0,i1;

      for( int i=0; i<static_cast<int>(index.size())-1; i++ ) {

        i0 = index[i  ];
        i1 = index[i+1];

        broad( this, v,n, i0,i1-1, u, b.Clear() );

        a.ResizeBack( b );

      }

  }

  else {  // with multi-threads

    vector<ARG_TAB1_Broad> ta(index.size()-1);

      for( int i=0; i<static_cast<int>(ta.size()); i++ ) {

        ta[i].obj    = this;
        ta[i].v      = v;
        ta[i].n      = n;
        ta[i].u      = u;
        ta[i].i0     = index[i  ];
        ta[i].i1     = index[i+1];

        //cerr << i << "  " << n << "  " << ta[i].i0 << "  " << ta[i].i1 << endl;

      }

      ExecuteMultiThread( broad, &ta, maxthreads );

      for( int i=0; i<static_cast<int>(ta.size()); i++ ) a.ResizeBack( ta[i].result );

  }

  delete [] v;

  this->Set( a, true );

  this->CutBelow( xmin );
  this->CutAbove( xmax );

  //return this;

  return this->Thin( eps );

}


/*! @brief Dopper cross-section for tabulated linearly interpolable point data
@param[in]  m          : particle mass (eV/c^2)
@param[in]  M          : target   mass (eV/c^2)
@param[in]  T          : temparature (K)
@param[in]  emax       : maximum energy (eV)
@param[in]  eps        : accuracy of interpolation for the data thnning
@param[in]  maxthreads : maximum number of the threads            
*/
TAB1* TAB1::Broad( const double m, const double M, const double T, const double emax, const double eps, const int maxthreads ) {

  TAB1 lower(*this),upper(*this);

    lower.CutAbove( emax );
    upper.CutBelow( emax );

    lower.Broad( m,M,T, eps, maxthreads )->PushBack(upper);

  return this->Set( lower, true );

}



/*! @brief Thinning data points for the linearized data
@param[in]  eps : accuracy of interpolation for the data thnning
*/
TAB1* TAB1::Thin( const double eps ) {
// thinning data points for the linearized data
// eps : accuracy of interpolation

  // check if linearized

  bool linear(true);

    for( int i=0; i<header.size(); i++ ) linear *= ( header[i].INT() <= 2 );

    if( ! linear ) {

      cerr << "!! TAB1::Thin -> do nothing becaused this is not linearized" << endl;

      return this;

    }

  // do thinning

  thin( this, eps );  return this;

}

/*! @brief Thinning data points for the linearized data
@param[in]  xmin,xmax : X-range to be thnning
@param[in]  eps       : accuracy of interpolation for the data thnning
*/
TAB1* TAB1::Thin( const double xmin, const double xmax, const double eps ) {

  TAB1 a(*this),b(*this);

    a.CutAbove( xmin );
    b.CutBelow( xmax );

    this->CutBelow( xmin );
    this->CutAbove( xmax );

    this->Thin( eps );

    this->PushFront( a );
    this->PushBack ( b );

  return this;

}


/*! @brief Check if data is given in interpolatable tabular form */
bool TAB1::Check() const {

  if( this->NP() < 2 ) return false;

  if( eq( this->Front().X(), this->Back().X() ) ) return false;

  return true;

}

/*! @brief Check if x-value is inside the range */
bool TAB1::Seek( const double x ) const {

  if( ! this->Check() ) return false;

  //return le( this->Front().X(), x, 1.e-7 ) && ge( this->Back().X(), x, 1.e-7 ); 

  if( lt( x, this->Front().X() ) ) return false;
  if( gt( x, this->Back ().X() ) ) return false;

  return true;

}


/*! @brief Seek index of the nodes with interpolation code
@param[in]  x           : x-value
@param[out] index       : index for the interval
@param[out] interpcode  : interpolation code
*/
bool TAB1::Seek( const double x, int* index, int* interpcode ) const {

  if( ! this->Seek( x ) ) return false;

  // find interp. position

  *index = search( x, this );

  // get interp. scheme

  *interpcode = this->InterpCode( *index );

  return true;

}



/*! @brief Reverse the sequential order */
TAB1* TAB1::Reverse() {
// reverse the order of x-y sequence

  TAB1 a(*this);

    this->ClearArray();

      for( int i=a.size()-1; i>=0; i-- )

        this->PushBack( a.at(i), a.InterpCode(i), false );

  return this;

}




unsigned long TAB1::NumberOfLines() const {
// number of lines in the ENDF-formatted file

  return header.NumberOfLines() + num_of_lines( this->NP(), 3 );

}



// <ROOT---------------------------------------------------
#ifdef Use_ROOT

TAB1* TAB1::SetLineAttributes( const TAttLine* o ) {

  this->TGraph::SetLineColor  ( o->GetLineColor() );
  this->TGraph::SetMarkerColor( o->GetLineColor() );
  this->TGraph::SetLineStyle  ( o->GetLineStyle() ); 
  this->TGraph::SetLineWidth  ( o->GetLineWidth() ); 

  return this;

}

TAB1* TAB1::SetLineColor( const int color ) {

  this->TGraph::SetLineColor  ( color );
  this->TGraph::SetMarkerColor( color );

  return this;

}

TAB1* TAB1::SetLineStyle( const int style ) {

  this->TGraph::SetLineStyle( style );  return this;

}

TAB1* TAB1::SetMarkerStyle( const int style ) {

  this->TGraph::SetMarkerStyle( style );  return this;

}

TAB1* TAB1::SetMarkerColor( const int color ) {

  this->TGraph::SetMarkerColor( color );  return this;

}

TAB1* TAB1::SetLineWidth( const float width ) {

 this->TGraph::SetLineWidth( width );  return this;

}

TAB1* TAB1::SetColor( const int color ) {

  this->TGraph::SetLineColor  ( color );
  this->TGraph::SetMarkerColor( color );

  return this;

}

TAB1* TAB1::SetLine( const Style_t style, const Color_t color, const Width_t width ) {

 this->TGraph::SetLineStyle( style );
 this->TGraph::SetLineColor( color );
 this->TGraph::SetLineWidth( width );

 return this;

}


TAB1* TAB1::SetTitle( const string title ) {
// title for the graph (this will be reflected to the legend)

  this->TGraph::SetTitle( title.c_str() );  return this;

}


static void update_graph( TAB1* o, const bool cos2a, const double eps, const int ndiv ) {

  TAB1 a(*o);

    if( o->NP() > 1 ) reconstruct( &a, 2, eps );

  int n = (a.NP()-1) * ndiv;  o->TGraph::Set(n+1);  int iii = 0;

    for( int i=0; i<a.NP()-1; i++ ) {

      double dx = ( a.X(i+1) - a.X(i) )/ndiv;

      for( int ii=0; ii<ndiv; ii++ ) {

        double x = a.X(i) + ii*dx;

        iii++;

        o->TGraph::SetPoint( iii, x, a.Interp(x) );

      }

    }

    o->TGraph::SetPoint( n, a.Back().X(), a.Back().Y() );

  return;

}

static void update_graph( TAB1* o, const bool cos2a, const double eps = 1.e-3 ) {
// eps : accuracy of interpolation

  TAB1 a(*o);

    if( o->NP() > 1 ) reconstruct( &a, 2, eps );

  int np = a.NP();

    o->TGraph::Set(np);

    //if( np < 2 ) return this;

    //if( cos2a ) for( int i=0; i<np; i++ ) a.X(i) = 180./M_PI * acos( a.X(i) );

    for( int i=0; i<np; i++ ) o->TGraph::SetPoint( i, a.X(i), a.Y(i) );


  if( o->GetN() < 100 ) return update_graph( o, cos2a, eps, 100 );

  return;

}


/*
TAB1* TAB1::UpdateGraph( const bool cos2a, const double eps ) {

  update_graph( this, cos2a, eps );  return this;

}
*/

/*! @brief Draw x-y data reflecting the given interpolation schemes
@param[in]  opt     : draw option for TGraph, e.g.,
                      "AL" - line with frame,
                      "L"  - line without frame,
                      "P"  - points without frame
@param[in]  cos2ang : do cosine -> degree conversion
@param[in]  eps : accuracy of the interpolation
*/
void TAB1::Draw( const Option_t* opt, const bool cos2a, const double eps ) {

  if( this->NP() == 0 ) return;

    update_graph( this, cos2a, eps );

    //update_graph( this );

  if( cos2a ) {

    double* xx = this->TGraph::GetX();

      for( int i=0; i<this->TGraph::GetN(); i++ ) xx[i] = 180./M_PI * acos( xx[i] );

  }

  this->TGraph::SetFillColor(0);

  if( this->NP() == 1 ) return this->SetMarkerStyle(20)->TGraph::Draw("P");

  this->TGraph::Draw( opt );

  return;


//TF1* f = new TF1( "f",this, &TAB1::InterpY, 0,1,0,"TAB1","InterpY" );


}

#endif
// ---------------------------ROOT>




/*
// ____ Copy constructor ______________________________________________________

TAB1::TAB1( const TAB1& tab1 ) {

  this->Set( tab1 );

}



// ____ Assign operator _______________________________________________________

TAB1& TAB1::operator=( const TAB1& tab1 ) {

  if( &tab1 != this ) this->Set( tab1 );

  return *this;

}
*/



bool TAB1::operator==( const TAB1& o ) const {

  if( header != o.header ) return false;

  for( int i=0; i<this->NP(); i++ ) if( ary[i] != o.ary[i] ) return false;

  return true;

}

bool TAB1::operator!=( const TAB1& o ) const {

  return !( *this == o );

}


bool TAB1::operator<( const TAB1& o ) const {

  return ( header < o.header );

}

bool TAB1::operator>( const TAB1& o ) const {

  return ( header > o.header );

}

bool TAB1::operator<=( const TAB1& o ) const {

  return ( header <= o.header );

}

bool TAB1::operator>=( const TAB1& o ) const {

  return ( header >= o.header );

}



TAB1& TAB1::operator<<( const TAB1& o ) {

  this->PushBack( o );  return *this;

}


// arithmetic operators
/*
TAB1& TAB1::operator+=( const TAB1& o ) {

  if( ! this->Check() ) return *this->Set( o, true );

    for( int i=0; i<o.NP()-1; i++ ) sum( *this, o.at(i), o.at(i+1), o.InterpCode(i), this, 1.e-3 );

  return *this;

}
*/

/*
TAB1& TAB1::operator-=( const TAB1& o ) {

  TAB1 a = o;  return this->operator+=( *a.ScaleY( -1.0 ) );

}
*/

/*
TAB1& TAB1::operator*=( const TAB1& o ) {

  for( int i=0; i<o.NP(); i++ ) this->Put( o.X(i) );

  for( int i=0; i<this->NP(); i++ ) this->Y(i) *= o.Interp( this->X(i) );

  //Mul( *this, o, this, 1.e-3 );

  return *this;

}
*/

/*
TAB1& TAB1::operator/=( const TAB1& o ) {

  TAB1 a = o;

    // invert Y

    for( int i=0; i<a.NP(); i++ ) {

      if( eq( a.Y(i), 0.0 ) ) {

        cerr << "!! TAB1::operator/= -> not allowed (X,Y)=" << a[i] << endl;  abort();

      }

      a.Y(i) = 1./a.Y(i);

    }

  return this->operator*=( a );

}
*/

TAB1& TAB1::operator+=( const double val ) {

  for( int i=0; i<this->NP(); i++ ) this->Y(i) += val;  return *this;

}

TAB1& TAB1::operator-=( const double val ) {

  for( int i=0; i<this->NP(); i++ ) this->Y(i) -= val;  return *this;

}

TAB1& TAB1::operator*=( const double val ) { return *this->ScaleY(    val ); }
TAB1& TAB1::operator/=( const double val ) { return *this->ScaleY( 1./val ); }

TAB1  TAB1::operator+( const TAB1& o ) { TAB1 a(*this);  a += o;  return a; }
TAB1  TAB1::operator-( const TAB1& o ) { TAB1 a(*this);  a -= o;  return a; }
TAB1  TAB1::operator*( const TAB1& o ) { TAB1 a(*this);  a *= o;  return a; }
TAB1  TAB1::operator/( const TAB1& o ) { TAB1 a(*this);  a /= o;  return a; }

TAB1  TAB1::operator+( const double val ) { TAB1 a(*this);  a += val;  return a; }
TAB1  TAB1::operator-( const double val ) { TAB1 a(*this);  a -= val;  return a; }
TAB1  TAB1::operator*( const double val ) { TAB1 a(*this);  a *= val;  return a; }
TAB1  TAB1::operator/( const double val ) { TAB1 a(*this);  a /= val;  return a; }


/*! @brief Weight Y by X^{power}
\f[Y(X)=Y(X)\times X^{power}\f]
*/
TAB1* TAB1::Weight( const double power ) {
// Y is weighted by X^power ( default: Y -> XY )

  for( int i=0; i<this->NP(); i++ ) this->Y(i) *= pow( this->X(i), power );  return this;

}


/*! @brief Normalize by o */
TAB1* TAB1::Normalize( const TAB1& o ) { this->operator/=( o );  return this; }



/*! @brief Get difference (returns o - this)
@param[in] is_percent : result will be given in %
*/
TAB1 TAB1::Difference( const TAB1& o, const bool is_percent ) const {

  TAB1 a(o);  a-= *this;

  if( is_percent ) { a /= o;  a.ScaleY( 100. ); }

  return a;

}


// I/O stream

istream& operator>>( istream& is,       TAB1& o ) { o.Store( is );  return is; }
ostream& operator<<( ostream& os, const TAB1& o ) { o.Write( os );  return os; }




/*!
@brief Linearize all the intervals
@param[in] eps : accuracy of the interpolation
*/
TAB1* TAB1::Linearize( const double eps ) {

  reconstruct( this, 2, eps );  return this;

}

/*!
@brief Reconstruct all the intervals with given interpolation code
@param[in] interpcode : interpolation code
@param[in] eps        : accuracy of the interpolation
*/
TAB1* TAB1::Reconstruct( const int interpcode, const double eps ) {

  reconstruct( this, interpcode, eps );  return this;

}



void TAB1::Break( vector<TAB1>* result ) const {
// break into each interval

  result->clear();

  for( int i=0; i<this->NP()-1; i++ ) {

    //if( this->X(i) == this->X(i+1) ) continue;
    if( eq( this->X(i), this->X(i+1) ) ) continue;

    TAB1 a( this->X(i), this->X(i+1), 1, this->InterpCode(i) );

      a.C1() = this->C1();
      a.C2() = this->C2();
      a.L1() = this->L1();
      a.L2() = this->L2();

      a.Front().Y() = this->Y(i  );
      a.Back ().Y() = this->Y(i+1);

      result->push_back( a );

  }

  return;

}




static TAB1 sum( const double& x1, const double& x2,
const double& y1a, const double& y2a, const int& interpcode_a, 
const double& y1b, const double& y2b, const int& interpcode_b, const double& eps ) {

  //      x1      x2
  //  a : |-------|
  //  b : |-------|

  TAB1 a( x1,x2, 1, interpcode_a );
  TAB1 b( x1,x2, 1, interpcode_b );

    //a.Front().Y() = y1a;  a.Back().Y() = ( interpcode_a == 1 ) ? 0.0 :  y2a;  a.Update();
    //b.Front().Y() = y1b;  b.Back().Y() = ( interpcode_b == 1 ) ? 0.0 :  y2b;  b.Update();

    a.Front().Y() = y1a;  a.Back().Y() = y2a;  a.Update();  // suggested by N.Iwamoto (2020/6/14)
    b.Front().Y() = y1b;  b.Back().Y() = y2b;  b.Update();  // suggested by N.Iwamoto (2020/6/14)

//if( a.Empty() && b.Empty() ) return TAB1( x1, x2, 1, 2 );  // adopt INT=1 or 2
  if( a.Empty() && b.Empty() ) return TAB1( x1, x2, 1, min( min(interpcode_a,interpcode_b), 2 ) );  // adopt INT=1 or 2

  if( a.Empty() ) return b;
  if( b.Empty() ) return a;

  if( interpcode_a == interpcode_b ) {

    a.Front().Y() += b.Front().Y();
    a.Back ().Y() += b.Back ().Y();

    return a;

  }

  if( interpcode_a > interpcode_b ) swap( a, b );

  if( min(interpcode_a,interpcode_b) == 1 ) {

    a.Front().Y() += b.I() / ( b.Back().X() - b.Front().X() );
  //a.Back ().Y() += 0.0;
    a.Back ().Y()  = a.Front().Y();  // suggested by N.Iwamoto (2020/6/14)

    return a;

  }

  b.Reconstruct( min(interpcode_a,interpcode_b), eps );

    for( int i=0; i<b.size(); i++ ) b.Y(i) += a.Interp( b.X(i) );

  return b;

}

static TAB1 product( const double& x1, const double& x2,
const double& y1a, const double& y2a, const int& interpcode_a, 
const double& y1b, const double& y2b, const int& interpcode_b, const double& eps ) {

  //      x1      x2
  //  a : |-------|
  //  b : |-------|

  TAB1 a( x1,x2, 1, interpcode_a );
  TAB1 b( x1,x2, 1, interpcode_b );

    a.Front().Y() = y1a;  a.Back().Y() = y2a;
    b.Front().Y() = y1b;  b.Back().Y() = y2b;

  if( interpcode_a == interpcode_b ) {

    a.Front().Y() *= b.Front().Y();
    a.Back ().Y() *= b.Back ().Y();

    return a;

  }

  if( interpcode_a > interpcode_b ) swap( a, b );

  if( min(interpcode_a,interpcode_b) == 1 ) {

    a.Front().Y() *= b.I() / ( b.Back().X() - b.Front().X() );
    a.Back ().Y()  = 0.0;

    return a;

  }

  b.Reconstruct( min(interpcode_a,interpcode_b), eps );

    for( int i=0; i<b.size(); i++ ) b.Y(i) *= a.Interp( b.X(i) );

  return b;

}

static TAB1 quotient( const double& x1, const double& x2,
const double& y1a, const double& y2a, const int& interpcode_a, 
const double& y1b, const double& y2b, const int& interpcode_b, const double& eps ) {

  //      x1      x2
  //  a : |-------|
  //  b : |-------|

  TAB1 a( x1,x2, 1, interpcode_a );
  TAB1 b( x1,x2, 1, interpcode_b );

    a.Front().Y() = y1a;  a.Back().Y() = y2a;
    b.Front().Y() = y1b;  b.Back().Y() = y2b;

  if( interpcode_a == interpcode_b ) {

    a.Front().Y() /= b.Front().Y();
    a.Back ().Y() /= b.Back ().Y();

    return a;

  }

  if( interpcode_a > interpcode_b ) swap( a, b );

  if( min(interpcode_a,interpcode_b) == 1 ) {

    a.Front().Y() /= b.I() / ( b.Back().X() - b.Front().X() );
    a.Back ().Y()  = 0.0;

    return a;

  }

  b.Reconstruct( min(interpcode_a,interpcode_b), eps );

    for( int i=0; i<b.size(); i++ ) b.Y(i) /= a.Interp( b.X(i) );

  return b;

}


static TAB1 arithmetic( const TAB1& a, const TAB1& b, const char option, const double eps ) {

  //cerr << "option = " << option << endl;
  //a.Write();
  //b.Write();

  //      x1      x2
  //  a : |---|--|----|
  //  b : |-|--|----|-|

  TAB1 aa(a),bb(b);

    for( int i=0; i<b.NP(); i++ ) aa.Put( b.X(i) );
    for( int i=0; i<a.NP(); i++ ) bb.Put( a.X(i) );

//aa.Write();
//bb.Write();

    if( aa.NP() != bb.NP() ) {

//cerr << a.Back().X() << endl;
//cerr << b.Back().X() << endl;

//cerr << eq( a.Back().X(), b.Back().X(), 1.e-12 ) << endl;

      //a.Write(); b.Write(); aa.Write(); bb.Write();
      cerr << aa.NP() << "  " << bb.NP() << endl;

      cerr << "!! arithmetic -> NP values are not same" << endl;  abort();

    }

    if( ne( aa.Front().X(), bb.Front().X() ) ) {

      cerr << "!! arithmetic -> lower x values are not same" << endl;
      cerr << aa.Front().X() << "  " << bb.Front().X() << endl;
      abort();

    }

    if( ne( aa.Back().X(), bb.Back().X() ) ) {

      //a.Write(); b.Write(); aa.Write(); bb.Write();
      cerr << "!! arithmetic -> upper x values are not same" << endl;  abort();

    }

  TAB1 c;

    if( option == 's' ) {  // sum

      for( int i=0; i<aa.size()-1; i++ )

        c.PushBack( sum( aa.X(i), aa.X(i+1), aa.Y(i), aa.Y(i+1), aa.InterpCode(i),
                                             bb.Y(i), bb.Y(i+1), bb.InterpCode(i), eps ) );

    }

    if( option == 'p' ) {  // product

      for( int i=0; i<aa.size()-1; i++ )

        c.PushBack( product( aa.X(i), aa.X(i+1), aa.Y(i), aa.Y(i+1), aa.InterpCode(i),
                                                 bb.Y(i), bb.Y(i+1), bb.InterpCode(i), eps ) );

    }

    if( option == 'q' ) {  // quotinent

      for( int i=0; i<aa.size()-1; i++ )

        c.PushBack( quotient( aa.X(i), aa.X(i+1), aa.Y(i), aa.Y(i+1), aa.InterpCode(i),
                                                  bb.Y(i), bb.Y(i+1), bb.InterpCode(i), eps ) );

    }

  return c;

}







static void uniform_sub( const double xa, const double xb,
const double ya1, const double yb1, const int interpcode1, 
const double ya2, const double yb2, const int interpcode2, TAB1* a, TAB1* b, const double eps ) {

// (xa,ya1),(xb,yb1) and (xa,ya2),(xb,yb2)

  a->Set( xa,xb, 1, interpcode1 );

    a->Front().Y() = ya1;
    a->Back ().Y() = yb1;

  b->Set( xa,xb, 1, interpcode2 );

    b->Front().Y() = ya2;
    b->Back ().Y() = yb2;

  if( eq(xa,xb) ) return;
  if( interpcode1 == interpcode2 ) return;

  if( interpcode1 > interpcode2 ) swap( *a,*b );

  int interpcode =  min( interpcode1, interpcode2 );

  if( interpcode == 1 ) {

    a->Linearize();
    b->Linearize();

  }

  else {

    b->Reconstruct( interpcode, eps );

  }

  for( int i=0; i<b->size(); i++ ) a->Put( b->X(i) );

  if( interpcode1 > interpcode2 ) swap( *a,*b );

  return;

}


static void uniform_sub( TAB1* a, TAB1* b, const double eps ) {
// give same points and interpolation scheme
// should be same range

  TAB1 temp1(*a),temp2(*b);

  //temp1.Unique();
  //temp2.Unique();

  // put same points

  for( int i=0; i<temp1.size(); i++ )  temp2.Put( temp1.X(i) );
  for( int i=0; i<temp2.size(); i++ )  temp1.Put( temp2.X(i) );

  // take care double points

  for( int i=0; i<temp1.size()-1; i++ ) if( eq( temp1.X(i), temp1.X(i+1) ) ) temp2.PutSame( temp1.X(i) );
  for( int i=0; i<temp2.size()-1; i++ ) if( eq( temp2.X(i), temp2.X(i+1) ) ) temp1.PutSame( temp2.X(i) );

  if( temp1.size() != temp2.size() ) {

    a->Write();
    b->Write();
    cerr << temp1.size() << "  " <<  temp2.size() << endl;
    temp1.Write();
    temp2.Write();
    cerr << "!! unitform_sub no.1 -> check function" << endl;

    exit(1);

    return;

  }

  a->ClearArray( );
  b->ClearArray();

  // give same interpolation codes

  for( int i=0; i<temp1.size()-1; i++ ) {

    if( ne( temp1.X(i), temp2.X(i) ) || ne( temp1.X(i+1), temp2.X(i+1) ) ) {

      cerr << "!! uniform_sub no.2 -> check function" << endl;

    }

    TAB1 c,d;

    int int1 = temp1.InterpCode(i);
    int int2 = temp2.InterpCode(i);

    uniform_sub( temp1.X(i), temp1.X(i+1), temp1.Y(i), temp1.Y(i+1), int1, temp2.Y(i), temp2.Y(i+1), int2, &c, &d, eps );

    a->PushBack( c );
    b->PushBack( d );

  }

  return;

}


void Uniform( TAB1* a, TAB1* b, const double eps ) {
// give same points with same interpolation scheme

  if( a->Empty() && b->Empty() ) return;

  if( a->Empty() ) { a->Set( *b, true )->SetY( 0.0 );  return; }
  if( b->Empty() ) { b->Set( *a, true )->SetY( 0.0 );  return; }


//      x1       x2
// |--------------|
//       |---------------|

  double x1 = max( a->Front().X(), b->Front().X() );
  double x2 = min( a->Back ().X(), b->Back ().X() );

  TAB1 lower_a(*a),lower_b(*b),upper_a(*a),upper_b(*b);

    lower_a.CutAbove( x1 );
    lower_b.CutAbove( x1 );

    if( lower_a.size() < lower_b.size() ) lower_a.Set( lower_b )->SetY( 0.0 );
    if( lower_a.size() > lower_b.size() ) lower_b.Set( lower_a )->SetY( 0.0 );

    upper_a.CutBelow( x2 );
    upper_b.CutBelow( x2 );

    if( upper_a.size() < upper_b.size() ) upper_a.Set( upper_b )->SetY( 0.0 );
    if( upper_a.size() > upper_b.size() ) upper_b.Set( upper_a )->SetY( 0.0 );

//upper_a.Write();
//upper_b.Write();

  TAB1 temp1(*a),temp2(*b);

    uniform_sub( temp1.CutBelow(x1)->CutAbove(x2), temp2.CutBelow(x1)->CutAbove(x2), eps );

    if( lt( a->Back().X(), b->Front().X() ) ) {

      temp1.Set( a->Back().X(), b->Front().X(), 1, 1 );
      temp2.Set( a->Back().X(), b->Front().X(), 1, 1 );

    }

    if( lt( b->Back().X(), a->Front().X() ) ) {

      temp1.Set( b->Back().X(), a->Front().X(), 1, 1 );
      temp2.Set( b->Back().X(), a->Front().X(), 1, 1 );

    }

/*
cerr << "test1 " << a->size() << "  " << b->size() << endl;
*/
    a->Set( temp1 )->PushFront( lower_a )->PushBack( upper_a );
    b->Set( temp2 )->PushFront( lower_b )->PushBack( upper_b );

//cerr << "test2 " << a->size() << "  " << b->size() << endl;
/*
temp1.Write(2); cerr << endl;
upper_a.Write(2); cerr << endl;
a->Write(2); cerr << endl;

temp2.Write(2); cerr << endl;
upper_b.Write(2); cerr << endl;
b->Write(2); cerr << endl;
*/

  // take care double points

  for( int i=0; i<a->size()-1; i++ ) if( eq( a->X(i), a->X(i+1) ) ) b->PutSame( a->X(i) );
  for( int i=0; i<b->size()-1; i++ ) if( eq( b->X(i), b->X(i+1) ) ) a->PutSame( b->X(i) );

//a->Write(2); cerr << endl;
//b->Write(2); cerr << endl;

//abort();

  if( a->size() != b->size() ) {
/*
    cerr << a->size() << "  " << b->size() << endl;

    for( int i=0; i<min(a->size(),b->size()); i++ ) {

      if( ne( a->X(i), b->X(i) ) ) cerr << a->X(i) << "  " << b->X(i) << endl;

    }
*/
    cerr << "!! Unitform -> check function" << endl;  return;

  }

  return;

}



void add_logarithmic_points( vector<double>* o, const int ndiv ) {

  vector<double> a;  double x0,x1,z0,z1,dz;

  for( int i=0; i<static_cast<int>(o->size())-1; i++ ) {

    x0 = o->at(i);
    x1 = ( x0 + o->at(i+1) )/2.0;

    z0 = log(x0);
    z1 = log(x1);

    dz = (z1-z0)/ndiv;

    vector<double> b;

      for( int ii=   0; ii<=ndiv; ii++ ) b.push_back( exp( z0+ii*dz ) );
      for( int ii=ndiv; ii>    0; ii-- ) b.push_back( b.back() + ( b[ii]-b[ii-1] ) );

    for( int ii=0; ii<static_cast<int>(b.size())-1; ii++ ) a.push_back( b[ii] );

  }

  a.push_back( o->back() );

  *o = a;

}


void add_logarithmic_points( deque<double>* o, const int ndiv ) {

  deque<double> a;  double x0,x1,z0,z1,dz;

  for( int i=0; i<static_cast<int>(o->size())-1; i++ ) {

    x0 = o->at(i);
    x1 = ( x0 + o->at(i+1) )/2.0;

    z0 = log(x0);
    z1 = log(x1);

    dz = (z1-z0)/ndiv;

    deque<double> b;

      for( int ii=   0; ii<=ndiv; ii++ ) b.push_back( exp( z0+ii*dz ) );
      for( int ii=ndiv; ii>    0; ii-- ) b.push_back( b.back() + ( b[ii]-b[ii-1] ) );

    for( int ii=0; ii<static_cast<int>(b.size())-1; ii++ ) a.push_back( b[ii] );

  }

  a.push_back( o->back() );

  *o = a;

}



static void reconstruct( Datum& r0, Datum& r2, const int& interpcode0,
TAB1* o, const int& interpcode, deque<Datum>* trace, const double eps ) {
// reconstruct with different interpolation code

  // middle point

  Datum r1( 0.5*( r0.X()+r2.X() ) );

    r1.Y() = Interp1( r0,r2, interpcode0, r1.X() );

  // check if satisfy accuracy

  if( ! Satisfied( r0,r1,r2, interpcode, eps ) ) {

    trace->push_front( r2 );

    reconstruct( r0,r1, interpcode0, o, interpcode, trace, eps );

  }

  if( trace->empty() ) return;

  // new point

  o->PushBack( r2, interpcode );

  // step back

  r0 = r2;  r2 = trace->front();  trace->pop_front();

  reconstruct( r0,r2, interpcode0, o, interpcode, trace, eps );

  return;

}

static void reconstruct( const Datum& front, const Datum& back, const int& interpcode0,
TAB1* o, const int& interpcode, const double eps ) {
// reconstruct between two points with different interpolation code
// interpcode0 : old interpolation code
// interpcode  : new interpolation code
// eps : accuracy of the interpolation

  o->ClearArray();

  if( eq( front.X(), back.X() ) ) {

    o->PushFront( front, interpcode, false );
    o->PushBack ( back , interpcode, false );

    return;

  }

  if( interpcode0 == interpcode ) {

    o->PushFront( front, interpcode, false );
    o->PushBack ( back , interpcode, false );

    return;

  }

  if( interpcode0 == 1 && interpcode == 2 ) {

    o->PushFront( front,              interpcode, false );
    o->PushBack ( back.X(),front.Y(), interpcode, false );

    return;

  }

  if( interpcode0 < interpcode ) {

    cerr << "warning : interpcode0 > interpcode, keep original interpolation" << endl;

    return reconstruct( front, back, interpcode0, o, interpcode0, eps );

  }

  Datum rlower(front), rupper(back);  deque<Datum> trace;

    reconstruct( rlower,rupper, interpcode0, o, interpcode, &trace, eps );

      o->PushFront( front, interpcode );
      o->PushBack ( back , interpcode );

  return;

}

void reconstruct( TAB1* o, const int& interpcode, const double& eps ) {

  TAB1 a(*o);  o->ClearArray();

    for( int i=0; i<a.size()-1; i++ ) {

      TAB1 b;

        reconstruct( a[i], a[i+1], a.InterpCode(i), &b, interpcode, eps );

      o->PushBack(b);

    }

  return;

}



static void thin2( TAB1* a, const double eps ) {
// thinning with linear interpolation

  //TAB1 b(*a);  int i0(0),i1(1),i2(2);  vector<int> index;  int interpcode(2);
  TAB1 b(*a);  int i1(1),i2(2);  vector<int> index;  int interpcode(2);

    int np(b.size());  
/*
    while( i2 < np ) {

      index.push_back(i0);

      if( ! Satisfied( b[i0],b[i1],b[i2], interpcode, eps ) ) {

        index.push_back(i1);

      }

      i0 +=2;  i1 +=2;  i2 +=2;

    }

    if( index.back() != np-1 ) index.push_back(np-1);
*/


    if( np%2==1 ) {

      for( int i0=0; i0<np-2; i0+=2 ) {

        index.push_back(i0);

        i1=i0+1;
        i2=i0+2;

        if( ! Satisfied( b[i0],b[i1],b[i2], interpcode, eps ) ) index.push_back(i1);

      }

      index.push_back(i2);

    }

    else {

      for( int i0=0; i0<np-3; i0+=2 ) {

        index.push_back(i0);

        i1=i0+1;
        i2=i0+2;

        if( ! Satisfied( b[i0],b[i1],b[i2], interpcode, eps ) ) index.push_back(i1);

      }

      index.push_back(i2);
      index.push_back(i2+1);

    }

    a->ClearArray();

    for( int i=0; i<static_cast<int>(index.size()); i++ ) a->PushBack( b[ index[i] ], interpcode );

  return;

}

void thin( TAB1* a, const double eps ) {
// thinning with linear interpolation

  if( a->NP() < 3 ) return;

  Datum front = a->Front();
  Datum back  = a->Back ();

  TAB1 b(*a);

    do {

      *a = b;  thin2( &b, eps );

    } while( a->NP() != b.NP() );


    if( ! a->Check() ) {

      a->ClearArray();
      a->PushFront( front );
      a->PushBack ( back  );

    }

  return;

}



int which( const int& i, const TAB1* o ) {
// take care the double points

  if( i == 0 ) return 0;

  return ( o->X(i) == o->X(i-1) ) ? i-1 : i;

}


int search( const double& x, const TAB1* o ) {
// search index

  // with normal search

  for( int i=0; i<o->NP()-1; i++ ) {

    if( le( o->X(i), x ) && lt( x, o->X(i+1) ) ) return i;

  }

  if( eq( x, o->Back().X() ) ) return o->NP()-2;

  return 0;

  // with binary search
/*
  int i0(0),i1,i2(o->NP()-1);

  while( (i2-i0) != 1 ) {

    i1 = (i0+i2);  i1 = i1/2 + i1%2 -1;

    if( o->X(i1) <= x && x < o->X(i1+1) ) return which( i1,o );

    if( x < o->X(i1)                 ) i2 = i1  ;
    if(              o->X(i1+1) <= x ) i0 = i1+1;

  }

  return ( o[i0] == x ) ? which( i0,o ) : i0;
*/
}



static TAB1 extract( const TAB1* o, const double x1, const double x2 ) {

  //         NOT allowed situations
  //
  //  x1    x2                     x1    x2
  //  |-----|                      |-----|    
  //      |---------|        |---------|
  //

  if( le( x2, o->Front().X() ) ) return TAB1( x1,x2, 1 );
  if( ge( x1, o->Back ().X() ) ) return TAB1( x1,x2, 1 );

//if( le( x2, o->Front().X() ) ) return TAB1( x1,x2, 1, 1 );
//if( ge( x1, o->Back ().X() ) ) return TAB1( x1,x2, 1, 1 );

  TAB1 a(*o);

    a.CutBelow( x1 )->CutAbove( x2 );

  return a;

}


static void split( const TAB1* o, const vector<double>* x, vector<TAB1>* result ) {
// x : x-values where do split (include beginning and end points )

  for( int i=0; i<static_cast<int>(x->size())-1; i++ ) {

  //cerr << extract( o, x->at(i), x->at(i+1) ) << endl;

    result->push_back( extract( o, x->at(i), x->at(i+1) ) );

  }

  return;

}


static void push( vector<double>* a, const double& val ) {

  bool exist(false);

    for( int i=0; i<static_cast<int>(a->size()); i++ ) if( eq( a->at(i), val ) ) exist = true;

    if( ! exist ) a->push_back( val );

  return sort( a->begin(), a->end() );

}

static void get_double_X( const TAB1* o, vector<double>* result ) {

  for( int i=0; i<o->NP()-1; i++ )

    if( eq( o->X(i), o->X(i+1) ) ) push( result, o->X(i) );

  return;

}


static void arithmetic( TAB1* a, const TAB1* b, const char option, const double& eps ) {
// option = false --sum, true --product

//a->Write();
//b->Write();

  //cerr << "a" << endl;  a->Write();
  //cerr << "b" << endl;  b->Write();

  // take care the double points

  vector<double> xx;  // double-point nodes with lower and upper edges

    get_double_X( a, &xx );
    get_double_X( b, &xx );

    push( &xx, a->Front().X() );
    push( &xx, b->Front().X() );
    push( &xx, a->Back ().X() );
    push( &xx, b->Back ().X() );

    vector<TAB1> aa,bb;

      split( a, &xx, &aa );
      split( b, &xx, &bb );

      //cerr << "aa" << endl;  for( int i=0; i<aa.size(); i++ ) aa[i].Write();
      //cerr << "bb" << endl;  for( int i=0; i<bb.size(); i++ ) bb[i].Write();

      //abort();

      a->ClearArray();

      for( int i=0; i<static_cast<int>(aa.size()); i++ ) {

        //aa[i].Write();
        //bb[i].Write();
        //abort();

        a->PushBack( arithmetic( aa[i], bb[i], option, eps ) );

      }

  return;

}


/*! @brief Add tabular data
@param[in] eps : accuracy of the interpolation
*/
/*
TAB1* TAB1::Add( const TAB1& o, const double eps ) {

  if( ! o.    Check() ) return this;
  if( ! this->Check() ) return this->Set( o, true );

    arithmetic( this, &o, 's', eps );

  return this;

}
*/

///@cond
struct type_add {

  TAB1 *a,*b;  double eps;
  pthread_mutex_t* mutex; pthread_cond_t* cond;  int* maxthreads;  int* nthreads;

};
///@endcond

static void* add( void* o ) {

  type_add* x = ( type_add* ) o;

  Wait(x);
      x->a->Add( *x->b, x->eps );
  Signal(x);

  return NULL;

};


/*! @brief Add tabular data
@param[in] o          : tabular data to be added this object
@param[in] eps        : accuracy of the interpolation
@param[in] maxthreads : maximum number the threads
*/
TAB1* TAB1::Add( const TAB1& o, const double eps, const int maxthreads ) {

  if( ! o.    Check() ) return this;
  if( ! this->Check() ) return this->Set( o, true );

  if( maxthreads <= 1 ) {

    arithmetic( this, &o, 's', eps );  return this;

  }

  // with multi-threads

  int n = this->NP();

//cerr << "n = " << n << endl;

  int ndiv = ( n%maxthreads == 0 ) ? maxthreads : maxthreads-1;

    if( n < ndiv ) return this->Add( o, eps );

  int dn = n/ndiv;  vector<int> index;

    get_indeces_by_step( this, dn, &index );

  vector<double> x;

    for( int i=0; i<static_cast<int>(index.size()); i++ ) x.push_back( this->X( index[i] ) );

  vector<TAB1> a,b;

    split( this, &x, &a );
    split(   &o, &x, &b );

  vector<type_add> t( x.size()-1 );

    for( int i=0; i<static_cast<int>(x.size())-1; i++ ) {

      t[i].a = &a[i];  t[i].b = &b[i];  t[i].eps = eps;

    }

//cerr << x.size()-1 << "  " << maxthreads << endl;

    ExecuteMultiThread( add, &t, maxthreads, 1 );

    this->ClearArray();

    for( int i=0; i<static_cast<int>(x.size())-1; i++ ) this->PushBack( a[i] );

  return this;

}



/*! @brief Subtract tabular data
@param[in] eps : accuracy of the interpolation
*/
TAB1* TAB1::Subtract( const TAB1& o, const double eps ) {

  TAB1 a = o;  return this->Add( *a.ScaleY( -1.0 ), eps );

}

/*! @brief Multiply tabular data
@param[in] eps : accuracy of the interpolation
*/
TAB1* TAB1::Multiply( const TAB1& o, const double eps ) {

  if( ! o.    Check() ) return this->ClearArray();
  if( ! this->Check() ) return this->ClearArray();

    arithmetic( this, &o, 'p', eps );

  return this;

}

/*! @brief Divide tabular data
@param[in] eps : accuracy of the interpolation
*/
TAB1* TAB1::Divide( const TAB1& o, const double eps ) {

  if( ! o.Check() ) {

    cerr << "!! TAB1::Divide= -> invalid denominator" << endl;  abort();

  }

  if( ! this->Check() ) return this->ClearArray();

  arithmetic( this, &o, 'q', eps );

  return this;

}


TAB1& TAB1::operator+=( const TAB1& o ) { return *this->Add     ( o, 1.e-3 ); }
TAB1& TAB1::operator-=( const TAB1& o ) { return *this->Subtract( o, 1.e-3 ); }
TAB1& TAB1::operator*=( const TAB1& o ) { return *this->Multiply( o, 1.e-3 ); }
TAB1& TAB1::operator/=( const TAB1& o ) { return *this->Divide  ( o, 1.e-3 ); }


/*! @brief Split by the double-point nodes
@param[out] result : continuous X-Y tables (no double points)
*/
void TAB1::Split( vector<TAB1>* result ) const {

  if( ! this->Check() ) return;

  vector<double> xx;  // double-point nodes with lower and upper edges

    get_double_X( this, &xx );

    push( &xx, this->Front().X() );
    push( &xx, this->Back ().X() );

    split( this, &xx, result );

  return;

}

};
