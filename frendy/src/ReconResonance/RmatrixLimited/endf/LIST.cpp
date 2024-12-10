#include "ReconResonance/RmatrixLimited/endf/LIST.h"
#include "ReconResonance/RmatrixLimited/endf/Numeric.h"
#include "ReconResonance/RmatrixLimited/basics/AlphaNumeric.h"
#include <string>

#ifdef Use_CINT
ClassImp( ENDF::LIST );
#endif

namespace ENDF {

using namespace Basics;

/*! @brief Constructor */
LIST::LIST() {}

/*! @brief Constructor */
LIST::LIST( const double C1, const double C2, const int L1, const int L2, const int NPL, const int N2, const vector<double>* b ) {

  this->Set( C1,C2,L1,L2,NPL,N2, b );

}

/*! @brief Constructor */
LIST::LIST( const char* file_name ) { this->Set( file_name ); }

/*! @brief Constructor */
LIST::LIST( istream& is ) { this->Store( is ); }

/*! @brief Destructor */
LIST::~LIST() {}

/*! @brief Copy constructor */
LIST::LIST( const LIST& o ) { this->Set( o ); }

/*! @brief Assign operator */
LIST& LIST::operator=( const LIST& o ) {

  if( &o != this ) this->Set( o );  return *this;

}


const double& LIST::at        ( const int i ) const { return ary[i]; }
      double& LIST::at        ( const int i )       { return ary[i]; }
const double& LIST::operator[]( const int i ) const { return ary[i]; }
      double& LIST::operator[]( const int i )       { return ary[i]; }

const double& LIST::front() const { return ary.front(); }
      double& LIST::front()       { return ary.front(); }
const double& LIST::back () const { return ary.back (); }
      double& LIST::back ()       { return ary.back (); }

int  LIST::size () const { return ary.size (); }
bool LIST::empty() const { return ary.empty(); }
void LIST::clear()       { return ary.clear(); }

LIST* LIST::resize( const int n ) {

  ary.resize(n); return this->NPL(n);

}


// ____ Store Record __________________________________________________________

void LIST::Store( istream& is ){

  is >> header;

    const int vlen = 11;  string xline;

      ary.resize( this->NPL() );

      for( int l=0; l<num_of_lines(this->NPL(),6); l++ ){

        getline( is, xline );

          for( int i=0; i<6; i++ ) {

            int j = l*6 + i;  if( j+1 > this->NPL() ) break;

            this->B(j) = dbl_endf( xline.substr( vlen*i, vlen ) );

          }

      }

  return;

}



// ____ Write Record __________________________________________________________

void LIST::Write( ostream& os, const int MAT, const int MF, const int MT, int* NS ) const {

  //if( this->NPL() == 0 ) return;

  string blank = "           ";

    os << endf( this->C1() )  << endf( this->C2() )
       << endf( this->L1() )  << endf( this->L2() )
       << endf( this->NPL() ) << endf( this->N2() )
       << endf( MAT,MF,MT,NS );

  for( int i=0; i<this->NPL(); i++  ) {

    os << endf( this->B(i) );  if( (i+1) % 6 == 0 ) os << endf( MAT,MF,MT,NS );

  }

  if( this->NPL() % 6 != 0 ) {

    for( int i=0; i<(6-this->NPL()%6); i++  ) os << blank;

    os << endf( MAT,MF,MT,NS );

  }

}


/*! @brief write record into the file */
void LIST::Write( const char* file_name ) const {

  return write( this, file_name );

}


/* __________ Set Values __________*/

LIST* LIST::Set( const LIST& o ) {

  header = o.header;  ary = o.ary;  return this;

}


LIST* LIST::Set( const double C1, const double C2, const int L1, const int L2, const int NPL, const int N2 ) {

  header.Set( C1,C2,L1,L2,NPL,N2 );  return this;

}


LIST* LIST::Set( const vector<double>* b ) {

  ary = *b;  return this->NPL( b->size() );

}


LIST* LIST::Set( const double C1, const double C2, const int L1, const int L2, const int NPL, const int N2, const vector<double>* b ) {

  return this->Set( C1,C2,L1,L2,NPL,N2 )->Set( b );

}

LIST* LIST::Set( const char* file_name ) {
// set table from the file

  return scan( this, file_name );

}




/* @brief Print tabulated data */
void LIST::PrintColumns( const int num_of_columns ) const {

  return this->PrintColumns( cout, num_of_columns );

}

static int print_titles( ostream& os, const char* text, const char* front_space ) {

  if( text == NULL ) return 0;

  vector<string> titles;

    break_down( string(text), &titles, "," );

      os << front_space;

        for( int i=0; i<static_cast<int>(titles.size()); i++ ) os << setw(13) << right << titles[i] << "  ";  os << endl;

  return titles.size();

}

static void print_line( ostream& os, const int num_of_columns, const char* front_space ) {

  os << front_space;

    for( int i=0; i<num_of_columns; i++ ) os << "---------------";  os << endl;

  return;

}

static void print_dots( ostream& os, const int num_of_columns, const char* front_space ) {

  os << front_space;

    for( int i=0; i<num_of_columns; i++ ) os << "   .........   ";  os << endl;

  return;

}

void LIST::PrintColumns( ostream& os, const int num_of_columns, const char* front_space ) const {

  os.setf( ios::scientific );

    for( int i=0; i<this->NPL()/num_of_columns; i++ ) {

      os << front_space;  for( int ii=0; ii<num_of_columns; ii++ ) os << setw(13) << setprecision(6) << right << this->B( i*num_of_columns + ii ) << "  ";  os << endl;

    }

  os.unsetf( ios::scientific );

}


void LIST::PrintColumns( ostream& os, const char* titles, const char* front_space ) const {

  int num_of_columns = print_titles( os, titles, front_space );

    print_line( os, num_of_columns, front_space );

    this->PrintColumns( os, num_of_columns, front_space );

    print_line( os, num_of_columns, front_space );

  return;

}


void LIST::PrintColumns( ostream& os, const int num_of_columns, const int num_of_rows, const char* front_space ) const {

  int n(num_of_rows), m(num_of_columns);  int np = this->NPL()/m;

    if( num_of_rows*2 > np ) return this->PrintColumns( os, num_of_columns, front_space );

    os.setf( ios::scientific );

      for( int i=   0; i< n; i++ ) { os << front_space;  for( int ii=0; ii<m; ii++ ) os << setw(13) << setprecision(6) << right << this->B( i*m + ii ) << "  ";  os << endl; }

        print_dots( os, num_of_columns, front_space );


      for( int i=np-n; i<np; i++ ) { os << front_space;  for( int ii=0; ii<m; ii++ ) os << setw(13) << setprecision(6) << right << this->B( i*m + ii ) << "  ";  os << endl; }

    os.unsetf( ios::scientific );

}


void LIST::PrintColumns( ostream& os, const char* titles, const int num_of_rows, const char* front_space ) const {

  int num_of_columns = print_titles( os, titles, front_space );

    print_line( os, num_of_columns, front_space );

    this->PrintColumns( os, num_of_columns, num_of_rows, front_space );

    print_line( os, num_of_columns, front_space );

  return;

}







const double& LIST::B( const int i ) const { return ary[i]; }
double&       LIST::B( const int i )       { return ary[i]; }



void LIST::Extract( const int n, const int m, vector<double>* b ) const {

  for( int i=0; i<this->NPL()/n; i++ ) b->push_back( this->B( i*n+m ) );

  return;

}


LIST* LIST::B( const vector<double>* b ) { return this->Set(b); }

const double& LIST::C1 () const { return header.C1(); }
      double& LIST::C1 ()       { return header.C1(); }
const double& LIST::C2 () const { return header.C2(); }
      double& LIST::C2 ()       { return header.C2(); }
const int&    LIST::L1 () const { return header.L1(); }
      int&    LIST::L1 ()       { return header.L1(); }
const int&    LIST::L2 () const { return header.L2(); }
      int&    LIST::L2 ()       { return header.L2(); }
const int&    LIST::NPL() const { return header.N1(); }
      int&    LIST::NPL()       { return header.N1(); }
const int&    LIST::N2 () const { return header.N2(); }
      int&    LIST::N2 ()       { return header.N2(); }

LIST* LIST::C1 ( const double val ) { header.C1(val); return this; }
LIST* LIST::C2 ( const double val ) { header.C2(val); return this; }
LIST* LIST::L1 ( const int    val ) { header.L1(val); return this; }
LIST* LIST::L2 ( const int    val ) { header.L2(val); return this; }
LIST* LIST::NPL( const int    val ) { header.N1(val); return this; }
LIST* LIST::N2 ( const int    val ) { header.N2(val); return this; }



/*! @brief Print data with translation
@param[in] text   : variable names to be printed ["C1,C2,L1,L2,NPL,N2/B"]
@param[in] os     : output stream [std::cout]
@param[in,out] ns : line number to be incremented [NULL]
@param[in] opt    : translate variables [1]
*/
void LIST::Translate( ostream& os, unsigned long* ns, const int opt, const int width_of_int, const char* text ) const {

  vector<string> t;  int n = split( text, &t, '/' );

  header.Translate( os,ns,opt, width_of_int, t[0].c_str() );

  if( opt>1 && n>1 ) this->PrintColumns( os, t[1].c_str(), opt-1, front_space_for_translation );

  if( ns != NULL ) (*ns) += num_of_lines( this->NPL(), 6 );  return;

}


static void translate( const LIST* o, const char* text, ostream& os, const int num_of_data_in_a_line, const int index = 0 ) {

  vector<string> t;  int n = ENDF::split( text, &t, ',' );

    for( int i=0; i<n; i++ ) {

      if( (i) % num_of_data_in_a_line == 0 ) os << front_space_for_translation;

      os << setw(6) << left << t[i] << "= " << scientific << o->B( i + n*index )  << "    ";

      if( (i+1) % num_of_data_in_a_line == 0 ) os << endl;

    }

  return;

}

void LIST::Translate( ostream& os, const int num_of_data_in_a_line, unsigned long* ns, const int opt, const int width_of_int, const char* text ) const {

  vector<string> t;  int n = split( text, &t, '/' );

  header.Translate( os,ns,opt, width_of_int, t[0].c_str() );

  if( opt>1 && n>1 ) translate( this, t[1].c_str(), os, num_of_data_in_a_line );

  if( ns != NULL ) (*ns) += num_of_lines( this->NPL(), 6 );  return;

}




/*
LIST* LIST::PushFront( const double val ) {

  //ary.push_front( val );  this->NPL() += 1;  return this;

  this->resize( this->NPL() + 1 );

  for( int i=this->NPL()-1; i>=1; i-- ) this->B(i) = this->B(i-1); 

  this->B(0) = val;  return this;

}
*/

LIST* LIST::PushBack( const double val ) {

  ary.push_back( val );  this->NPL() += 1;  return this;

}

LIST* LIST::PushBack( const complex<double> val ) {

  ary.push_back( real(val) );
  ary.push_back( imag(val) );

  this->NPL() += 2;  return this;

}


LIST* LIST::PopFront( const int num ) {

  //for( int i=0; i<num; i++ ) ary.pop_front();  this->NPL() -= num;  return this;

  if( this->NPL() <= num ) return this->resize(0);

  for( int i=num; i<this->NPL(); i++ ) this->B(i-num) = this->B(i);

  return this->resize( this->NPL() -num );

}


LIST* LIST::PopBack( const int num ) {

  if( this->NPL() <= num ) return this->resize(0);

  for( int i=0; i<num; i++ ) ary.pop_back();  this->NPL() -= num;  return this;

}


const double& LIST::Front() const { return ary.front(); }
      double& LIST::Front()       { return ary.front(); }
const double& LIST::Back () const { return ary.back (); }
      double& LIST::Back ()       { return ary.back (); }


LIST* LIST::Scale( const double fac ) {

  for( int i=0; i<this->NPL(); i++ ) this->B(i) *= fac;  return this;

}


LIST* LIST::Clear() {

  header.Clear();  ary.clear();  return this;

}

LIST* LIST::ClearArray() {

  ary.clear();  return this->NPL(0)->N2(0);

}


bool LIST::Check() const {

  string warning = "!! LIST::Check -> found error(s)";

  if( static_cast<int>(ary.size()) != this->NPL() ) { cerr << warning << endl;  return false; }

  return true;

}



unsigned long LIST::NumberOfLines() const {

  return 1 + num_of_lines( this->NPL(), 6 );

}



bool LIST::operator==( const LIST& o ) const {

  return ( header == o.header && ary == o.ary );

}

bool LIST::operator!=( const LIST& o ) const {

  return !( *this == o );

}

bool LIST::operator< ( const LIST& o ) const {

  return ( header < o.header );

}

bool LIST::operator> ( const LIST& o ) const {

  return ( header > o.header );

}

bool LIST::operator<=( const LIST& o ) const {

  return ( header <= o.header );

}

bool LIST::operator>=( const LIST& o ) const {

  return ( header >= o.header );

}




// I/O stream

istream& operator>>( istream& is,       LIST& o ) { o.Store( is );  return is; }
ostream& operator<<( ostream& os, const LIST& o ) { o.Write( os );  return os; }

};

