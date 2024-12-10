#include "ReconResonance/RmatrixLimited/endf/TAB2.h"
#include "ReconResonance/RmatrixLimited/endf/Numeric.h"
#include <utility>

#ifdef Use_CINT
ClassImp( ENDF::TAB2 );
#endif

namespace ENDF {

TAB2::Range:: Range() : nsept(0), inter(2) {}
TAB2::Range:: Range( const int n, const int i ) : nsept(n), inter(i) {}
TAB2::Range::~Range() {}

const int& TAB2::Range::NBT() const { return nsept; }
      int& TAB2::Range::NBT()       { return nsept; }
const int& TAB2::Range::INT() const { return inter; }
      int& TAB2::Range::INT()       { return inter; }

bool TAB2::Range::operator==( const Range& o ) const { return ( nsept == o.nsept && inter == o.inter ); }
bool TAB2::Range::operator!=( const Range& o ) const { return !( *this == o ); }



TAB2:: TAB2() : header() {}
TAB2:: TAB2( const int nz, const int interpcode ) : header() { this->Set(nz,interpcode); }
TAB2:: TAB2( istream& is ) { this->Store( is ); }
TAB2::~TAB2() {}

/*! @brief Copy constructor */
TAB2::TAB2( const TAB2& o ) { this->Set( o ); }

/*! @brief Assign operator */
TAB2& TAB2::operator=( const TAB2& o ) {

  if( &o != this ) this->Set( o );  return *this;

}


const TAB2::Range& TAB2::at        ( const int i ) const { return ary[i]; }
      TAB2::Range& TAB2::at        ( const int i )       { return ary[i]; }
const TAB2::Range& TAB2::operator[]( const int i ) const { return ary[i]; }
      TAB2::Range& TAB2::operator[]( const int i )       { return ary[i]; }

const TAB2::Range& TAB2::front() const { return ary.front(); }
      TAB2::Range& TAB2::front()       { return ary.front(); }
const TAB2::Range& TAB2::back () const { return ary.back (); }
      TAB2::Range& TAB2::back ()       { return ary.back (); }

int  TAB2::size () const { return ary.size (); }
bool TAB2::empty() const { return ary.empty(); }
void TAB2::clear()       { return ary.clear(); }


// ____ Store Record __________________________________________________________

void TAB2::Store( istream& is ){

  is >> header;

  /* read interp. table */

  string xline;

  ary.resize( NR() );

    for( int l=0; l<num_of_lines(NR(),3); l++ ) {

      getline( is, xline );

        for( int i=0; i<3; i++ ){

          int j = l*3 + i;  if( j+1 > this->NR() ) break;

	    ary[j].NBT() = int_endf( xline.substr(    11*i*2, 11 ) );
	    ary[j].INT() = int_endf( xline.substr( 11+11*i*2, 11 ) );

        }

    }

  return;

}




// ____ Write Record __________________________________________________________

void TAB2::Write( ostream& os, const int MAT, const int MF, const int MT, int* NS ) const {


  string blank = "           ";
//string blank = "          0";

  header.Write( os, MAT,MF,MT,NS );

  // write interp. scheme

  for( int i=0; i<this->NR(); i++  ) {

    os << endf( ary[i].NBT() ) << endf( ary[i].INT() );

    if( (i+1) % 3 == 0 ) os << endf( MAT,MF,MT,NS );

  }

  if( this->NR() % 3 != 0 ) {

    for( int i=0; i<(3-this->NR()%3)*2; i++  ) os << blank;

    os << endf( MAT,MF,MT,NS );

  }

  return;

}




/* __________ Set Values __________*/

TAB2* TAB2::Set( const CONT& o ) {

  header.Set( o );  return this;

  //return this->Set( arg );

}

/*
TAB2* TAB2::Set( const deque< pair<int,int> > arg ) {

  interval = arg;

  this->NR( arg.size() );
  this->NZ( arg.back().first );

  return this;

}
*/


TAB2* TAB2::Set( const TAB2& o, const bool option ) {
// option = true  : all values are copied except for C1,C2,L1,L2
//        = false : all values are copied [default]

  ary = o.ary;

  if( option ) return this->NR( o.NR() )->NZ( o.NZ() );

  return this->Set( o.header );

}


TAB2* TAB2::Set( const int NZ, const int interpcode ) {

  this->NR() =  1;
  this->NZ() = NZ;

  ary.resize(1);

  this->Front().NBT() = NZ;
  this->Front().INT() = interpcode;

  return this;

}

/*
TAB2* TAB2::Set( const deque<Range>& ranges ) {

  ary = ranges;

  this->NR() = ary.size();
  this->NZ() = ary.back().NBT();

  return this;

}
*/


TAB2* TAB2::C1( const double val ) { header.C1(val); return this; }
TAB2* TAB2::C2( const double val ) { header.C2(val); return this; }
TAB2* TAB2::L1( const int    val ) { header.L1(val); return this; }
TAB2* TAB2::L2( const int    val ) { header.L2(val); return this; }
TAB2* TAB2::NR( const int    val ) { header.N1(val); return this; }
TAB2* TAB2::NZ( const int    val ) { header.N2(val); return this; }

const double& TAB2::C1() const { return header.C1(); }
      double& TAB2::C1()       { return header.C1(); }
const double& TAB2::C2() const { return header.C2(); }
      double& TAB2::C2()       { return header.C2(); }
const int&    TAB2::L1() const { return header.L1(); }
      int&    TAB2::L1()       { return header.L1(); }
const int&    TAB2::L2() const { return header.L2(); }
      int&    TAB2::L2()       { return header.L2(); }
const int&    TAB2::NR() const { return header.N1(); }
      int&    TAB2::NR()       { return header.N1(); }
const int&    TAB2::NZ() const { return header.N2(); }
      int&    TAB2::NZ()       { return header.N2(); }

const int& TAB2::NBT( const int i ) const { return ary[i].NBT(); }
      int& TAB2::NBT( const int i )       { return ary[i].NBT(); }
const int& TAB2::INT( const int i ) const { return ary[i].INT(); }
      int& TAB2::INT( const int i )       { return ary[i].INT(); }


static void translate( ostream& os, const TAB2* o ) {

  string blank(front_space_for_translation);  blank.pop_back();

  os << '#' << blank << "{NBT,INT} = ";

    for( int i=0; i<o->size(); i++ ) {

      os << '{' << o->NBT(i) << ',' << o->INT(i) << "}, "; 

    }

    os << endl;

  return;

}


/*! @brief Print data with translation
@param[in] os     : output stream [std::cout]
@param[in,out] ns : line number to be incremented [NULL]
@param[in] opt    : translate variables [1]
@param[in] text   : first variable names to be printed ["C1,C2,L1,L2,NR,NZ"]
*/
void TAB2::Translate( ostream& os, unsigned long* ns, const int opt, const int width_of_int, const char* text ) const {

  header.Translate( os,ns,opt, width_of_int, text );

    if( opt > 1 ) translate( os, this );

    if( ns != NULL ) (*ns) += num_of_lines( this->NR(), 3 );

  return;

}

/*! @brief Update record (value of last NBT is forced to NZ)  */
TAB2* TAB2::Update() {

  this->Back().NBT() = this->NZ();  return this;

}






// ____ Discard above index ___________________________________________________

TAB2* TAB2::CutAbove( const int index ) {


  if( index < 0 || this->NZ()-1 < index ) return this;

  this->NZ( index +1 );

  int n = 0;

  for( int i=0; i<this->NR()-1; i++  ) {

    if ( this->NBT(i) < this->NZ() && this->NZ() <= this->NBT(i+1) ) n = i+1;

  }

  this->NR( n+1 );

  deque<Range> temp;

    for( int i=0; i<this->NR(); i++ ) temp.push_back( ary[i] ); 

      ary = temp;  ary.back().NBT() = this->NZ();

  return this;

}




// ____ Discard below index ___________________________________________________

TAB2* TAB2::CutBelow( const int index ) {


  if( index < 0 || this->NZ()-1 < index ) return this;

  this->NZ( this->NZ() - index );

  int n = 0;

  for( int i=0; i<this->NR()-1; i++  ) {

    if ( this->NBT(i) < index+1 && index+1 <= this->NBT(i+1) ) n = i+1;

  }

  this->NR( this->NR() - n );

  deque<Range> temp;

    for( int i=0; i<this->NR(); i++ ) temp.push_back( Range( this->NBT(i+n)-index, this->INT(i+n) ) );

      ary = temp;  ary.back().NBT() = this->NZ();


      if( this->NR() >= 2 ) {

	if( this->NBT(0) == 1 ) { 

          ary.pop_front();  this->NR() -= 1;

	}

      }

  return this;

}




// ____ Merge data ____________________________________________________________


TAB2* TAB2::PushFront( const TAB2& o ) {

  TAB2 temp = o;

    temp.C1( this->C1() );
    temp.C2( this->C2() );
    temp.L1( this->L1() );
    temp.L2( this->L2() );

    temp.PushBack( *this );

    *this = temp;

  return this;

}


TAB2* TAB2::PushBack( const TAB2& o ) {

  if( this->NR() == 0 || this->NZ() == 0 || ary.empty() ) {

    this->NR( o.ary.size() );
    this->NZ( o.NZ()       );

      ary = o.ary;

    return this;

  }

  deque<Range> temp( this->NR() + o.NR() );

  if( ary.back().INT() == o.ary.front().INT() ) {

    temp.resize( temp.size() -1 );

    for( int i=0; i<this->NR(); i++ ) {

      temp[i].NBT() = this->NBT(i);
      temp[i].INT() = this->INT(i);

    }

    temp.back().NBT() += o.ary.front().NBT();

    for( int i=this->NR(); i<static_cast<int>(temp.size()); i++ ) {

      temp[i].NBT() = o.NBT( i-NR() +1 ) + ary.back().NBT();
      temp[i].INT() = o.INT( i-NR() +1 );

    }

  }

  else {

    for( int i=0; i<this->NR(); i++ ) {

      temp[i].NBT() = this->NBT(i);
      temp[i].INT() = this->INT(i);

    }

    for( int i=this->NR(); i<static_cast<int>(temp.size()); i++ ) {

      temp[i].NBT() = o.NBT( i-NR() ) + ary.back().NBT();
      temp[i].INT() = o.INT( i-NR() );

    }

  }

  this->NR( temp.size() );
  this->NZ( this->NZ() + o.NZ() );

  ary = temp;

  return this;

}



/*
void TAB2::Insert( const int index, const int inter ) {


  this->NZ( NZ()+1 );

  int i = index + 1;


  deque< pair<int,int> >::iterator it = interval.begin();

  for( ; it != interval.end(); it++ ) {

    if( i <= it->first ) break;

  }

  //cerr << it->first << endl;

  if( it->second == inter ) {

    for( ; it != interval.end(); it++ ) { it->first += 1; }  return;

  }

  pair<int,int> int1 = make_pair( i - 1, it->second );
  pair<int,int> int2 = make_pair( i    , inter      );
  pair<int,int> int3 = make_pair( it->first + 1, it->second );


  this->NR( NR()+2 );

  TAB2 old1 = *this;  old1.CutAbove( index );
  TAB2 old2 = *this;  old2.CutBelow( index );

  interval.clear();

  for( int n=0; n<old1.NZ(); n++ ) this->PushBack( old1.INT(n) );

    interval.push_back( int1 );
    interval.push_back( int2 );
    interval.push_back( int3 );

  for( int n=0; n<old2.NZ(); n++ ) this->PushBack( old2.INT(n) );


  it = interval.erase( it );

  cerr << it->first << endl;


    interval.insert( it, int3 );
    interval.insert( it, int2 );
    interval.insert( it, int1 );


  it++; it++; it++;

  //cerr << it->first << endl;

    for( ; it != interval.end(); it++ ) it->first += 1;

}
*/


TAB2* TAB2::PushFront( const int inter ) {

  if( ary.empty() ) {

    ary.push_back( Range(1,inter) );

    this->NZ() = 1;
    this->NR() = 1;

    return this;

  }

  if( this->NZ() == 1 ) {

    ary.clear();  ary.push_back( Range(2,inter) );  

    this->NZ() = 2;
    this->NR() = 1;

    return this;

  }

  this->NZ() += 1;

  deque<Range>::iterator it;

  for( it=ary.begin(); it != ary.end(); it++ ) it->NBT() += 1;

  if( ary.front().INT() == inter ) return this;

//ary.push_front( Range(1,inter) );
  ary.push_front( Range(2,inter) );

    this->NR() += 1;

  return this;

}


TAB2* TAB2::PushBack( const int inter ) {

  if( ary.empty() ) {

    ary.push_back( Range(1,inter) );

    this->NZ() = 1;
    this->NR() = 1;

    return this;

  }

  this->NZ() += 1;

  if( ary.back().INT() == inter ) {

    ary.back().NBT() += 1;  return this;

  }

  ary.push_back( Range(NZ(),inter) );

    this->NR() += 1;

  if( this->NZ() > 1 && ary.front().NBT() == 1 ) {

    ary.pop_front();  this->NR() -= 1;

  }

  return this;

}


TAB2* TAB2::PushFront() {
// push-front a point with the same interpolation code with the front

  this->NZ() += 1;

    for( int i=0; i<this->NR(); i++ ) this->NBT(i) += 1;

  return this;

}

TAB2* TAB2::PushBack() {
// push-back a point with the same interpolation code of with back

  this->NZ() += 1;

    this->Back().NBT() += 1;

  return this;

}



/* Pop datum */

TAB2* TAB2::PopFront() {

  this->NZ() -= 1;

  deque<Range>::iterator it;

  for( it=ary.begin(); it != ary.end(); it++ ) it->NBT() -= 1;

//if( ary.front().NBT() == 0 ) {
  if( ary.front().NBT() <= 1 ) {

    ary.pop_front();  this->NR() -= 1;

  }

  return this;

}


TAB2* TAB2::PopBack() {

  this->NZ() -= 1;

  ary.back().NBT() -= 1;

  if( this->NR() <= 1 ) return this;

  if( this->NBT( NR()-1 ) == this->NBT( NR()-2 ) ) {

    ary.pop_back();  this->NR() -= 1;

  }

  return this;

}


/*!
@brief update interpolation table if a point at index (of e.g., TAB1, LTT1, ...) is removed
*/
TAB2* TAB2::Erase( const int index ) {

  this->NZ() -= 1;

  for( int i=0; i<this->size(); i++ ) {

    if( index <= this->NBT(i) ) this->NBT(i)--;

  }

  if( this->NR() <= 1 ) return this;

  if( this->NBT( NR()-1 ) == this->NBT( NR()-2 ) ) {

    ary.pop_back();  this->NR() -= 1;

  }

  return this;

}




int TAB2::InterpCode( const int i ) const {

  int m = 0;

  int a = this->INT(m);

    for( int m=1; m<this->NR(); m++ ) {

      if( this->NBT(m-1) <= (i+1) ) a = this->INT(m);

    }

  return a;

}



TAB2* TAB2::SetInterpCode( const int interpcode ) {

  ary.resize(1);

    this->NBT(0) = this->NZ();
    this->INT(0) = interpcode;

  return this->NR(1);

}




bool TAB2::Check() const {

  string warning = "!! TAB2::Check -> found error(s)";

  if( static_cast<int>(ary.size()) != this->NR() ) { cerr << warning << endl;  return false; }
  if( ary.back().NBT()             != this->NZ() ) { cerr << warning << endl;  return false; }

  return true;

}



/* __________ Clear Values __________*/

TAB2* TAB2::Clear() {

  header.Clear();  ary.clear();  return this;

}

TAB2* TAB2::ClearArray() {

  ary.clear();  return this->NR(0)->NZ(0);

}


const TAB2::Range& TAB2::Front() const { return this->front(); }
      TAB2::Range& TAB2::Front()       { return this->front(); }
const TAB2::Range& TAB2::Back () const { return this->back (); }
      TAB2::Range& TAB2::Back ()       { return this->back (); }


void TAB2::Diagnose( Document* result, int* ns ) const {

  (*ns)++;

  if( this->NR() != static_cast<int>(ary.size()) )

    result->PushBack() << *ns << " ---> NR = " << this->NR() << " : inconsistent array size";

  if( this->NR() <= 0 )

    result->PushBack() << *ns << " ---> NR = " << this->NR() << " : no interpolation codes";

  int interpcode;

    for( int i=0; i<this->NR(); i++ ) {

      if( i%3==0 ) (*ns)++;

      interpcode = this->INT(i);

      if( 1 <= interpcode%10 && interpcode%10 <= 5 ) continue;

      result->PushBack() << *ns << " ---> INT = " << interpcode << " : interpolation code is not defined";

    }

  return;

}





bool TAB2::operator==( const TAB2& o ) const {

  return ( header == o.header && ary == o.ary );

}

bool TAB2::operator!=( const TAB2& o ) const {

  return !( *this == o );

}

bool TAB2::operator< ( const TAB2& o ) const {

  return ( header < o.header );

}

bool TAB2::operator> ( const TAB2& o ) const {

  return ( header > o.header );

}

bool TAB2::operator<=( const TAB2& o ) const {

  return ( header <= o.header );

}

bool TAB2::operator>=( const TAB2& o ) const {

  return ( header >= o.header );

}


unsigned long TAB2::NumberOfLines() const { return 1 + num_of_lines( this->NR(), 3 ); }



// ____ Insert operator _______________________________________________________
/*
TAB2& TAB2::operator<<( const TAB2& o ) {

  this->PushBack( o );  return *this;

}
*/


// I/O stream

istream& operator>>( istream& is,       TAB2& o ) { o.Store( is );  return is; }
ostream& operator<<( ostream& os, const TAB2& o ) { o.Write( os );  return os; }


};

