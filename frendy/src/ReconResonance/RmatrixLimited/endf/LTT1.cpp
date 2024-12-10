#include "ReconResonance/RmatrixLimited/endf/LTT1.h"
#include "ReconResonance/RmatrixLimited/endf/Nodes.h"
#include "ReconResonance/RmatrixLimited/endf/Interp1.h"
#include "ReconResonance/RmatrixLimited/endf/Functions.h"
#include "ReconResonance/RmatrixLimited/endf/Construct.h"

namespace ENDF {

#ifdef Use_CINT
//ClassImp( LTT1::Record );
//ClassImp( LTT1 );
#endif

LTT1::Record:: Record() {}
LTT1::Record:: Record( const LIST& o ) { this->Set( o ); }
LTT1::Record::~Record() {}


/*! @brief Legendre coefficient
@param[in] L : angular momentum
*/
double LTT1::Record::a( const int L ) const {

  if( L > this->NL() ) return 0.0;

  return ( L == 0 ) ? 1.0 : this->B(L-1);

}

/*! @brief Normalized distribution */
double LTT1::Record::f( const double cosangle ) const {

  double f = 0.0;

    for( int l=0; l<=this->NL(); l++ )

      f += 0.5*(2.0*l+1.0) * this->a(l) * P_Legendre( l, cosangle );

  return f;

}


static double func( const double& cosangle, const LTT1::Record* o ) { return o->f( cosangle ); }

/*! @brief Reconstruct normalized distribution from the Legendre polynomial expression
@param[out] f         : normalized distribution
@param[in] interpcode : interpolation code for the distribution
@param[in] eps        : accuracy of the interpolation
*/
void LTT1::Record::Reconstruct( TAB1* f, const int interpcode, const double eps ) const {
// calculate normalized distribution
// f          : normalized distribution
// interpcode : interpolation code for the distribution
// eps        : accuracy of the interpolation

  double nodes[] = { -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1,
                     0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };

    for( int i=0; i<20; i++ ) {

      TAB1 a;  construct( func, this, nodes[i],nodes[i+1], &a, interpcode, eps );  f->ResizeBack(a);

    }

    f->Thin( eps );

    f->C1() = this->T ();
    f->C2() = this->E ();
    f->L1() = this->LT();

  return;

}


/*! @brief Sclae Legendre coefficient (may used to give a perturbation)
@param[in] L     : angular momentum
@param[in] scale : scale factor
*/
double LTT1::Record::a( const int L, const double scale ) {

  if( L == 0 || L > this->NL() ) {

    cerr << "!! LTT1::Record::a -> data for L=" << L << " is not given in this file" << endl;

    return 0.0;

  }

  this->B(L-1) *= scale;  return this->B(L-1);

}




LTT1:: LTT1(){}
LTT1:: LTT1( const int n, const int interpcode ) { this->Set( n, interpcode ); }
LTT1:: LTT1( const char* file_name ) { this->Read( file_name ); }
LTT1::~LTT1(){}

const LTT1::Record& LTT1::at( const int i ) const { return array.at(i); }
      LTT1::Record& LTT1::at( const int i )       { return array.at(i); }

const LTT1::Record& LTT1::operator[]( const int i ) const { return array.operator[](i); }
      LTT1::Record& LTT1::operator[]( const int i )       { return array.operator[](i); }

int  LTT1::size () const { return array.size (); }
bool LTT1::empty() const { return array.empty(); }
void LTT1::clear()       { return array.clear(); }

const LTT1::Record& LTT1::Front() const { return array.front(); }
      LTT1::Record& LTT1::Front()       { return array.front(); }
const LTT1::Record& LTT1::Back () const { return array.back (); }
      LTT1::Record& LTT1::Back ()       { return array.back (); }


const double& LTT1::C1() const { return control.C1(); }
      double& LTT1::C1()       { return control.C1(); }
const double& LTT1::C2() const { return control.C2(); }
      double& LTT1::C2()       { return control.C2(); }
const int&    LTT1::L1() const { return control.L1(); }
      int&    LTT1::L1()       { return control.L1(); }
const int&    LTT1::L2() const { return control.L2(); }
      int&    LTT1::L2()       { return control.L2(); }
const int&    LTT1::NR() const { return control.NR(); }
      int&    LTT1::NR()       { return control.NR(); }
const int&    LTT1::NE() const { return control.NZ(); }
      int&    LTT1::NE()       { return control.NZ(); }

LTT1* LTT1::C1( const double val ) { control.C1(val); return this; }
LTT1* LTT1::C2( const double val ) { control.C2(val); return this; }
LTT1* LTT1::L1( const int    val ) { control.L1(val); return this; }
LTT1* LTT1::L2( const int    val ) { control.L2(val); return this; }
LTT1* LTT1::NR( const int    val ) { control.NR(val); return this; }
LTT1* LTT1::NE( const int    val ) { control.NZ(val); return this; }

const int& LTT1::NBT( const int i ) const { return control.NBT(i); }
      int& LTT1::NBT( const int i )       { return control.NBT(i); }
const int& LTT1::INT( const int i ) const { return control.INT(i); }
      int& LTT1::INT( const int i )       { return control.INT(i); }

int LTT1::InterpCode( const int i ) const { return control.InterpCode(i); }




/*! @brief Print data with translation
@param[in] opt    : translate variables [1]
@param[in] os     : output stream [std::cout]
@param[in,out] ns : line number to be incremented [NULL]
@param[in] text1  : first variable names to be printed [",,,,NR,NE"]
@param[in] text2  : second variable names to be printed ["T,E,TL,,NL,/a"]
*/
void LTT1::Translate( const int opt, ostream& os, unsigned long* ns, const int width_of_int, const char* text1, const char* text2 ) const {

  control.Translate( os,ns,opt, width_of_int, text1 );

    for( int i=0; i<this->NE(); i++ )

      this->at(i).Translate( os,ns,opt, width_of_int, text2 );

  return;

}




/*! @brief Read data from a stream */
void LTT1::Store( istream& is ) {

  return store( &control, &array, is );

}

/*! @brief Read data from a file */
void LTT1::Read( const char* file_name ) {

  return read( &control, &array, file_name );

}

/*! @brief Write data to a stream */
void LTT1::Write( ostream& os, const int MAT, const int MF, const int MT, int* NS ) const {

  write( &control, &array, os, MAT,MF,MT,NS );

}

/*! @brief Write data to a file */
void LTT1::Write( const char* file_name ) const {

  return write( &control, &array, file_name );

}

/*! @brief Count number of lines in the file */
unsigned long LTT1::NumberOfLines() const {

  return number_of_lines( &control, &array );

}

/*! @brief Set data */
LTT1* LTT1::Set( const LTT1& o ) {

  set_array( &control, &array, o.control, o.array );  return this;

}

/*! @brief Set data from a file ( same as Write ) */
LTT1* LTT1::Set( const char* file_name ) {

  this->Read( file_name );  return this;

}

/*! @brief Set TAB2 data, then resize array */
LTT1* LTT1::Set( const TAB2& o ) {

  control.Set(o);  array.resize( o.NZ() );  return this;

}

/*! @brief Resize array
@param[in] n           : number of the record
@param[in] interpcode  : interpolation code between the records
*/
LTT1* LTT1::Set( const int n, const int interpcode ) {

  set_array( &control, &array, n, interpcode );  return this;

}

/*! @brief Clear array */
LTT1* LTT1::Clear() {

  ENDF::clear( &control, &array );  return this;

}

/*! @brief Push a record from the front */
LTT1* LTT1::PushFront( const Record& o, const int interpcode ) {

  push_front( &control, &array, o, interpcode );  return this;

}

/*! @brief Push a record from the back */
LTT1* LTT1::PushBack ( const Record& o, const int interpcode ) {

  push_back( &control, &array, o, interpcode );  return this;

}

/*! @brief Push a record from the front */
LTT1* LTT1::PushFront( const LTT1& o, const int interpcode ) {

  push_front( &control, &array, o.control, o.array, interpcode );  return this;

}

/*! @brief Push a record from the back */
LTT1* LTT1::PushBack ( const LTT1& o, const int interpcode ) {

  push_back( &control, &array, o.control, o.array, interpcode );  return this;

}

/*! @brief Put a record outside the covering energy range,
where the new record will be taken from the first/last node
*/
LTT1* LTT1::PutClone( const double elab ) {

  put_clone( &control, &array, elab );  return this;

}

/*! @brief Erase records from the front
@param[in] n : number of the records to be erased
*/
LTT1* LTT1::PopFront( const int num ) {

  pop_front( &control, &array, num );  return this;

}

/*! @brief Erase records from the back
@param[in] n : number of the records to be erased
*/
LTT1* LTT1::PopBack ( const int num ) {

  pop_back( &control, &array, num );  return this;

}

/*! @brief Erase a record */
LTT1* LTT1::Erase( const double E ) {

  erase( &control, &array, E );  return this;

}

/*! @brief Reducing the number of nodes by half */
LTT1* LTT1::Thin() {

  thin( &control, &array );  return this;

}

/*! @brief Cut all the records below E=elab
@param[in] elab : incident energy
@param[in] eps  : accuracy of the interpolation
@note a record will be generated by the interpolation if it is missing at elab
*/
LTT1* LTT1::CutBelow( const double elab, const double eps ) {

  cut_below( &control, &array, elab );  if( this->empty() ) return this;

  if( this->Front().E() < elab ) this->Front() = this->Interp( elab );

  return this;

}

/*! @brief Cut all the records above E=elab
@param[in] elab : incident energy
@param[in] eps  : accuracy of the interpolation
@note a record will be generated by the interpolation if it is missing at elab
*/
LTT1* LTT1::CutAbove( const double elab, const double eps ) {

  cut_above( &control, &array, elab );  if( this->empty() ) return this;

  if( this->Back().E() > elab ) this->Back() = this->Interp( elab );

  return this;

}


/*! @brief Replace data with new records for the given energy range
@param[in] o : new records
*/
LTT1* LTT1::Replace( const LTT1& o ) {

  if( o.Back ().E() < this->Front().E() ) return this;
  if( o.Front().E() > this->Back ().E() ) return this;

  LTT1 lower(*this),upper(*this);

    lower.CutAbove( o.Front().E() );
    upper.CutBelow( o.Back ().E() );

    this->Clear();

    this->PushBack( lower );
    this->PushBack(     o );
    this->PushBack( upper );

    if( eq( this->E(      0 ), this->E(      1 ) ) ) this->PopFront();
    if( eq( this->E( NE()-2 ), this->E( NE()-1 ) ) ) this->PopBack ();

  return this;

}


/*! @brief Check if a record exist at E */
bool LTT1::Find( const double E ) const { return find( &control, &array, E ); }

/*! @brief Check if given energy is inside the range */
bool LTT1::Seek( const double E ) const { return seek( &control, &array, E ); }

/*! @brief Check if given energy is inside the range
@param[in]  E          : incident energy
@param[out] index      : index of the record where E should be in-between E(index) and E(index+1)
@param[out] interpcode : interpolation code between the two records
*/
bool LTT1::Seek( const double E, int* index, int* interpcode ) const {

  return seek( &control, &array, E, index, interpcode );

}







static double get_a( const LIST& o, const int l ) {

  if( l > o.NPL() ) return 0.0;

  return ( l == 0 ) ? 1.0 : o.B(l-1);

}

static double get_f( const LIST& o, const double cosangle ) {
// normalized distribution

  double f = 0.0;

    for( int l=0; l<=o.NPL(); l++ )

      f += 0.5*(2.0*l+1.0) * get_a(o,l) * P_Legendre( l, cosangle );

  return f;

}


static double get_f( const double& cosangle, const LIST* o ) { return get_f( *o, cosangle ); }

static void reconstruct( const LIST& o, TAB1* f, const int interpcode, const double eps ) {
// calculate normalized distribution
// f          : normalized distribution
// interpcode : interpolation code for the distribution
// eps        : accuracy of the interpolation

  double nodes[] = { -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1,
                     0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0 };

    for( int i=0; i<20; i++ ) {

      TAB1 a;  construct( get_f, &o, nodes[i],nodes[i+1], &a, interpcode, eps );  f->ResizeBack(a);

    }

    f->Thin( eps );

    f->C1() = o.C1();
    f->C2() = o.C2();
    f->L1() = o.L1();

  return;

}





LTT1* LTT1::ScaleEnergy( const double fac ) {

  for( int i=0; i<this->NE(); i++ ) this->E(i) *= fac;  return this;

}


/*! @brief Get energy nodes E_(i=...NE)
@param[out] E : incident energies given in this record
*/
void LTT1::GetEnergyNodes( vector<double>* E ) const { return get_energy_nodes( &array, E ); }



/*! @brief Legendre polynomial coefficient
@param[in] elab : incident energy
@param[in] l    : order of the Legendre polynomial
*/
double LTT1::a( const double elab, const int l ) const {

  // exactly corresponding data

  for( int i=0; i<this->NE(); i++ ) if( eq( this->E(i), elab ) ) return array[i].a(l);

  // interp.

  int index, interpcode;

  if( ! this->Seek( elab, &index, &interpcode ) ) return 0.0;

  return Interp1( E(index), array[index].a(l), E(index+1), array[index+1].a(l), interpcode%20, elab );

}

double LTT1::a( const double elab_lower, const double elab_upper, const int l ) const {

  TAB1 b;

    for( int i=0; i<this->NE(); i++ ) b.PushBack( this->E(i), array[i].a(l), this->InterpCode(i-1) );

  return b.Average( elab_lower,elab_upper );

}


void LTT1::Interp( Record* result ) const {

  double elab = result->E();

  // exactly corresponding data

  for( int i=0; i<this->NE(); i++ ) if( eq( this->E(i), elab ) ) {

      *result = this->at(i);  return;

  }

  // interp.

  int index, interpcode;

  if( ! this->Seek( elab, &index, &interpcode ) ) return;

  int NL1 = this->NL(index  );
  int NL2 = this->NL(index+1);

  *result = NL1 > NL2 ? this->at(index) : this->at(index+1);

  for( int i=0; i<min(NL1,NL2); i++ )

    result->B(i) = Interp1( E(index), array[index].B(i), E(index+1), array[index+1].B(i), interpcode%20, elab );

  for( int i=min(NL1,NL2); i<max(NL1,NL2); i++ ) {

    if( NL1 < NL2 ) result->B(i) = Interp1( E(index),            0.0, E(index+1), array[index+1].B(i), interpcode%20, elab );
    if( NL1 > NL2 ) result->B(i) = Interp1( E(index), array[index].B(i), E(index+1),              0.0, interpcode%20, elab );

  }

  result->T() = Interp1( E(index), T(index), E(index+1), T(index+1), interpcode%20, elab );
  result->E() = elab;

  return;

}


LTT1::Record LTT1::Interp( const double elab ) const {

  Record a;  this->Interp( a.E(elab) );  return a;

}



/*! @brief Value of normalized distribution at given angle
@param[in] elab     : incident energy
@param[in] cosangle : cosine of the scattering angle
*/
double LTT1::f( const double elab, const double cosangle ) const {

  // exactly corresponding data

  for( int i=0; i<this->NE(); i++ ) if( eq( this->E(i), elab ) ) return array[i].f( cosangle );

  // interp.

  int index, interpcode;

  if( ! this->Seek( elab, &index, &interpcode ) ) return 0.0;

    double E1 = this->E(index  );
    double E2 = this->E(index+1);
    double f1 = array[index  ].f( cosangle );
    double f2 = array[index+1].f( cosangle );

  return Interp1( E1, f1, E2, f2, interpcode, elab );

}

/*! @brief Reconstruct normalized distribution at given incident energy
@param[in,out] result : normalized distribution
@param[in] interpcode : interpolation code for the distribution
@param[in] eps        : accuracy of the interpolation
@note resut->C2() will be recognized as the incident energy 
*/
void LTT1::get_f_da( TAB1* result, const int interpcode, const double eps ) const {

  if( interpcode != 2 ) {

    cerr << "!! LTT1::Reconstruct -> should be interpcode = 2 due to a problem in data-thinning" << endl;
    return;

  }

  Record a;

    this->Interp( a.E( result->C2() ) );

  return reconstruct( a, result, interpcode, eps );

}


/*! @brief Reconstruct normalized distribution from Legendre polynomial expression
@param[out] result    : normalized distributions at all the energy nodes
@param[in] interpcode : interpolation code for the distribution
@param[in] eps        : accuracy of the interpolation
*/
void LTT1::Reconstruct( LTT2* result, const int interpcode, const double eps ) const {

  if( interpcode != 2 ) {

    cerr << "!! LTT1::Reconstruct -> should be interpcode = 2 due to a problem in data-thinning" << endl;
    return;

  }

  for( int i=0; i<this->NE(); i++ ) {

    TAB1 a;

      array[i].Reconstruct( &a, interpcode, eps );

    result->PushBack( a, this->InterpCode(i) );

  }

  return;

}



bool LTT1::operator==( const LTT1& o ) const { return ( control == o.control && array == o.array ); }
bool LTT1::operator!=( const LTT1& o ) const { return !( *this == o ); }
bool LTT1::operator< ( const LTT1& o ) const { return ( control <  o.control ); }
bool LTT1::operator> ( const LTT1& o ) const { return ( control >  o.control ); }
bool LTT1::operator<=( const LTT1& o ) const { return ( control <= o.control ); }
bool LTT1::operator>=( const LTT1& o ) const { return ( control >= o.control ); }




/*! @brief Sclae Legendre coefficient (may used to give a perturbation)
@param[in] E   : incident energy
@param[in] L   : angular momentum
@param[in] fac : scale factor
@note Energy node of E should be explicitly given in this record
*/
double LTT1::a( const double E, const int L, const double fac ) {

  if( ! this->Find(E) ) return 0.0;

    for( int i=0; i<this->NE(); i++ ) if( eq(this->E(i),E) ) return this->at(i).a(L,fac);

  return 0.0;

}

/*! @brief Put new Record at energy E with given interpolation
@note Duplication will be avoided. Also, nothing to be done if E is outside the range
@param[in] E   : incident energy
@param[in] eps : accuracy of the interpolation
*/
LTT1* LTT1::Put( const double E, const double eps ) {

  if(   this->Find(E) ) return this;
  if( ! this->Seek(E) ) return this;

  LTT1 upper(*this);

    upper.CutBelow( E, eps );

  return this->CutAbove( E, eps )->PushBack( upper );
  
}



};
