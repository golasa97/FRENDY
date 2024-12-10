#include "ReconResonance/RmatrixLimited/endf/CONT.h"
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"

#ifdef Use_CINT
ClassImp( ENDF::CONT );
#endif

namespace ENDF {

using namespace Basics;
using namespace Numeric;

//_____________________________________________________________
// [MAT,MF,MT/C1,C2,L1,L2,N1,N2]



CONT::CONT() { this->Clear(); }
CONT::CONT( const double C1, const double C2, const int L1, const int L2, const int N1, const int N2 ) { this->Set( C1,C2,L1,L2,N1,N2 ); }
CONT::CONT( istream& is ) { this->Store( is ); }
CONT::~CONT(){}


const double& CONT::C1() const { return c1; }
      double& CONT::C1()       { return c1; }
const double& CONT::C2() const { return c2; }
      double& CONT::C2()       { return c2; }
const int&    CONT::L1() const { return l1; }
      int&    CONT::L1()       { return l1; }
const int&    CONT::L2() const { return l2; }
      int&    CONT::L2()       { return l2; }
const int&    CONT::N1() const { return n1; }
      int&    CONT::N1()       { return n1; }
const int&    CONT::N2() const { return n2; }
      int&    CONT::N2()       { return n2; }

CONT* CONT::C1( const double val ) { c1 = val; return this; }
CONT* CONT::C2( const double val ) { c2 = val; return this; }
CONT* CONT::L1( const int    val ) { l1 = val; return this; }
CONT* CONT::L2( const int    val ) { l2 = val; return this; }
CONT* CONT::N1( const int    val ) { n1 = val; return this; }
CONT* CONT::N2( const int    val ) { n2 = val; return this; }



/*
template<class T> static string translate( const char* text, const T& x ) {

  stringstream ss;

    if( strcmp(text,"")==0 ) ss << setw(18) << "";

    else ss << setw(5) << left << string(text) << "= " << endf(x);

  return ss.str();

}
*/

static bool is_blank( const char* text ) {

  string s(text);

    for( int i=0; i<static_cast<int>(s.size()); i++ ) if( s[i] != ' ' ) return false;

  return true;

}

static string translate( const char* text, const double& x ) {

  stringstream ss;

  //if( strcmp(text,"")==0 ) ss << setw(18) << "";
    if( is_blank(text) ) ss << setw(18) << "";

    else ss << setw(5) << left << string(text) << "= " << endf(x);

  return ss.str();

}

static string translate( const char* text, const int& x, const int width = 11 ) {

  stringstream ss;

  //if( strcmp(text,"")==0 ) ss << setw(5+2+width) << "";
    if( is_blank(text) ) ss << setw(5+2+width) << "";

    else ss << setw(5) << left << string(text) << "= " << setw(width) << right << x;

  return ss.str();

}


static void translate( const CONT* o, const bool opt, ostream& os, unsigned long* ns, const char* C1, const char* C2, const char* L1, const char* L2, const char* N1, const char* N2, const int width_of_int, const char* front_space ) {

  if( ns != NULL ) (*ns)++;

    os << front_space;

    if( opt ) {

      os << translate( C1, o->C1()               ) << "    ";
      os << translate( C2, o->C2()               ) << "    ";
      os << translate( L1, o->L1(), width_of_int ) << "    ";
      os << translate( L2, o->L2(), width_of_int ) << "    ";
      os << translate( N1, o->N1(), width_of_int ) << "    ";
      os << translate( N2, o->N2(), width_of_int );

    } else {
/*
      os << setw(11) << ( strcmp(C1,"")==0  ? "" : endf( o->C1() ) );
      os << setw(11) << ( strcmp(C2,"")==0  ? "" : endf( o->C2() ) );
      os << setw(11) << ( strcmp(L1,"")==0  ? "" : endf( o->L1() ) );
      os << setw(11) << ( strcmp(L2,"")==0  ? "" : endf( o->L2() ) );
      os << setw(11) << ( strcmp(N1,"")==0  ? "" : endf( o->N1() ) );
      os << setw(11) << ( strcmp(N2,"")==0  ? "" : endf( o->N2() ) );
*/
      os << setw(11) << ( is_blank(C1)  ? "" : endf( o->C1() ) );
      os << setw(11) << ( is_blank(C2)  ? "" : endf( o->C2() ) );
      os << setw(11) << ( is_blank(L1)  ? "" : endf( o->L1() ) );
      os << setw(11) << ( is_blank(L2)  ? "" : endf( o->L2() ) );
      os << setw(11) << ( is_blank(N1)  ? "" : endf( o->N1() ) );
      os << setw(11) << ( is_blank(N2)  ? "" : endf( o->N2() ) );

    }
  
    if( ns == NULL ) os << endl;

    else os << setw(10) << right << "@NS=" << setw(6) << *ns << endl;

  return;

}


/*! @brief Print data with translation
@param[in] os     : output stream
@param[in,out] ns : line number to be incremented
@param[in] opt    : translate variables
@param[in] text   : variable names to be printed ["C1,C2,L1,L2,N1,N2"]
*/
void CONT::Translate( ostream& os, unsigned long* ns, const bool opt, const int width_of_int, const char* text, const char* front_space ) const {

  if( strcmp(text,"") == 0  ) return;

  vector<string> a;  int n;

    n = split( string(text), &a );

    const char* C1 = (n>0) ? a[0].c_str() : "";
    const char* C2 = (n>1) ? a[1].c_str() : "";
    const char* L1 = (n>2) ? a[2].c_str() : "";
    const char* L2 = (n>3) ? a[3].c_str() : "";
    const char* N1 = (n>4) ? a[4].c_str() : "";
    const char* N2 = (n>5) ? a[5].c_str() : "";

  return translate( this, opt,os,ns, C1,C2,L1,L2,N1,N2, width_of_int, front_space );

}



// ____ Store Record __________________________________________________________

void CONT::Store( istream& is ) {

  // Store Record

    const int vlen = 11;  string xline;

    getline( is, xline );

      this->C1() = dbl_endf( xline.substr( 0*vlen, vlen ) );
      this->C2() = dbl_endf( xline.substr( 1*vlen, vlen ) );
      this->L1() = int_endf( xline.substr( 2*vlen, vlen ) );
      this->L2() = int_endf( xline.substr( 3*vlen, vlen ) );
      this->N1() = int_endf( xline.substr( 4*vlen, vlen ) );
      this->N2() = int_endf( xline.substr( 5*vlen, vlen ) );

}



// ____ Write Record __________________________________________________________

void CONT::Write( ostream& os, const int MAT, const int MF, const int MT, int* NS ) const {

  os << endf( this->C1() );  os << endf( this->C2() );
  os << endf( this->L1() );  os << endf( this->L2() );
  os << endf( this->N1() );  os << endf( this->N2() );

  os << endf( MAT, MF, MT, NS );

}



/* __________ Set Values __________*/

CONT* CONT::Set( const double C1, const double C2, const int L1, const int L2, const int N1, const int N2 ) {

  this->C1(C1);  this->C2(C2);
  this->L1(L1);  this->L2(L2);
  this->N1(N1);  this->N2(N2);

  return this;

}


CONT* CONT::Set( const CONT& o ) {

  if( &o == this ) return this;

    this->C1( o.C1() );  this->C2( o.C2() );
    this->L1( o.L1() );  this->L2( o.L2() );
    this->N1( o.N1() );  this->N2( o.N2() );

  return this;

}




/* __________ Clear Values __________*/

CONT* CONT::Clear() {

  c1=0.0; c2=0.0; l1=0; l2=0; n1=0; n2=0;  return this;

  //return this->Set( 0.0, 0.0, 0, 0, 0, 0 ); 

  //return this->N1(0)->N2(0);

}


void CONT::Diagnose( Document* result, int* NS ) const {

  (*NS)++;  return;

}


unsigned long CONT::NumberOfLines() const { return 1; }


bool CONT::operator==( const CONT& o ) const {

  return (

         eq( this->C1(), o.C1() )
      && eq( this->C2(), o.C2() )

     //  this->C1() == o.C1() && this->C2() == o.C2()
      && this->L1() == o.L1() && this->L2() == o.L2()
      && this->N1() == o.N1() && this->N2() == o.N2()

         );

}

bool CONT::operator!=( const CONT& o ) const {

  return !( *this == o );

}


bool CONT::operator< ( const CONT& o ) const {

  /*
  if( this->C1() < o.C1() ) return true ;
  if( this->C1() > o.C1() ) return false;
  if( this->C2() < o.C2() ) return true ;
  if( this->C2() > o.C2() ) return false;
  */

  if( lt( this->C1(), o.C1() ) ) return true ;
  if( gt( this->C1(), o.C1() ) ) return false;
  if( lt( this->C2(), o.C2() ) ) return true ;
  if( gt( this->C2(), o.C2() ) ) return false;

  if( this->L1() < o.L1() ) return true ;
  if( this->L1() > o.L1() ) return false;
  if( this->L2() < o.L2() ) return true ;
  if( this->L2() > o.L2() ) return false;
  if( this->N1() < o.N1() ) return true ;
  if( this->N1() > o.N1() ) return false;
  if( this->N2() < o.N2() ) return true ;
  if( this->N2() > o.N2() ) return false;

  return false;

}


bool CONT::operator> ( const CONT& o ) const {

  return ( ! this->operator<=( o ) );

}


bool CONT::operator<=( const CONT& o ) const {

  return ( this->operator==( o ) || this->operator<( o )  );

}

bool CONT::operator>=( const CONT& o ) const {

  return ( this->operator==( o ) || this->operator>( o )  );

}



// I/O stream

istream& operator>>( istream& is,       CONT& o ) { o.Store( is );  return is; }
ostream& operator<<( ostream& os, const CONT& o ) { o.Write( os );  return os; }

};
