#include "ReconResonance/RmatrixLimited/endf/LTT2.h"
#include "ReconResonance/RmatrixLimited/endf/Nodes.h"
#include "ReconResonance/RmatrixLimited/endf/Interp2.h"

#ifdef Use_CINT
//ClassImp( LTT2::Record );
//ClassImp( LTT2 );
#endif

namespace ENDF {

LTT2::Record:: Record() {}
LTT2::Record:: Record( const TAB1& o ) { this->Set( o ); }
LTT2::Record::~Record() {}

const double& LTT2::Record::T () const { return this->C1(); }
      double& LTT2::Record::T ()       { return this->C1(); }
const double& LTT2::Record::E () const { return this->C2(); }
      double& LTT2::Record::E ()       { return this->C2(); }
const int&    LTT2::Record::LT() const { return this->L1(); }
      int&    LTT2::Record::LT()       { return this->L1(); }

LTT2::Record* LTT2::Record::T ( const double val ) { this->C1(val);  return this; }
LTT2::Record* LTT2::Record::E ( const double val ) { this->C2(val);  return this; }
LTT2::Record* LTT2::Record::LT( const int    val ) { this->L1(val);  return this; }


LTT2:: LTT2(){}
LTT2:: LTT2( const int n, const int interpcode ) { this->Set( n, interpcode ); }
LTT2:: LTT2( const char* file_name ) { this->Read( file_name ); }
LTT2::~LTT2(){}

const LTT2::Record& LTT2::at( const int i ) const { return array.at(i); }
      LTT2::Record& LTT2::at( const int i )       { return array.at(i); }

const LTT2::Record& LTT2::operator[]( const int i ) const { return array.operator[](i); }
      LTT2::Record& LTT2::operator[]( const int i )       { return array.operator[](i); }

int  LTT2::size () const { return array.size (); }
bool LTT2::empty() const { return array.empty(); }
void LTT2::clear()       { return array.clear(); }

const LTT2::Record& LTT2::Front() const { return array.front(); }
      LTT2::Record& LTT2::Front()       { return array.front(); }
const LTT2::Record& LTT2::Back () const { return array.back (); }
      LTT2::Record& LTT2::Back ()       { return array.back (); }

const double& LTT2::C1() const { return control.C1(); }
      double& LTT2::C1()       { return control.C1(); }
const double& LTT2::C2() const { return control.C2(); }
      double& LTT2::C2()       { return control.C2(); }
const int&    LTT2::L1() const { return control.L1(); }
      int&    LTT2::L1()       { return control.L1(); }
const int&    LTT2::L2() const { return control.L2(); }
      int&    LTT2::L2()       { return control.L2(); }
const int&    LTT2::NR() const { return control.NR(); }
      int&    LTT2::NR()       { return control.NR(); }
const int&    LTT2::NE() const { return control.NZ(); }
      int&    LTT2::NE()       { return control.NZ(); }

LTT2* LTT2::C1( const double val ) { control.C1(val); return this; }
LTT2* LTT2::C2( const double val ) { control.C2(val); return this; }
LTT2* LTT2::L1( const int    val ) { control.L1(val); return this; }
LTT2* LTT2::L2( const int    val ) { control.L2(val); return this; }
LTT2* LTT2::NR( const int    val ) { control.NR(val); return this; }
LTT2* LTT2::NE( const int    val ) { control.NZ(val); return this; }

const int& LTT2::NBT( const int i ) const { return control.NBT(i); }
      int& LTT2::NBT( const int i )       { return control.NBT(i); }
const int& LTT2::INT( const int i ) const { return control.INT(i); }
      int& LTT2::INT( const int i )       { return control.INT(i); }

int LTT2::InterpCode( const int i ) const { return control.InterpCode(i); }



/*! @brief Print data with translation
@param[in] opt    : translate variables [1]
@param[in] os     : output stream [std::cout]
@param[in,out] ns : line number to be incremented [NULL]
@param[in] text1  : first variable names to be printed [",,,,NR,NE"]
@param[in] text2  : second variable names to be printed ["T,E,TL,,NR,NP/mu,f"]
*/
void LTT2::Translate( const int opt, ostream& os, unsigned long* ns, const int width_of_int, const char* text1, const char* text2 ) const {

  control.Translate( os,ns,opt, width_of_int, text1 );

    for( int i=0; i<this->NE(); i++ )

      this->at(i).Translate( os,ns,opt, width_of_int, text2 );

  return;


}



/*! @brief Read data from a stream */
void LTT2::Store( istream& is ) {

  return store( &control, &array, is );

}

/*! @brief Read data from a file */
void LTT2::Read( const char* file_name ) {

  return read( &control, &array, file_name );

}

/*! @brief Write data to a stream */
void LTT2::Write( ostream& os, const int MAT, const int MF, const int MT, int* NS ) const {

  write( &control, &array, os, MAT,MF,MT,NS );

}

/*! @brief Write data to a file */
void LTT2::Write( const char* file_name ) const {

  return write( &control, &array, file_name );

}

/*! @brief Count number of lines in the file */
unsigned long LTT2::NumberOfLines() const {

  return number_of_lines( &control, &array );

}

/*! @brief Set data */
LTT2* LTT2::Set( const LTT2& o ) {

  set_array( &control, &array, o.control, o.array );  return this;

}

/*! @brief Set data from a file ( same as Write ) */
LTT2* LTT2::Set( const char* file_name ) {

  this->Read( file_name );  return this;

}

/*! @brief Set TAB2 data, then resize array */
LTT2* LTT2::Set( const TAB2& o ) {

  control.Set(o);  array.resize( o.NZ() );  return this;

}

/*! @brief Resize array
@param[in] n           : number of the record
@param[in] interpcode  : interpolation code between the records
*/
LTT2* LTT2::Set( const int n, const int interpcode ) {

  set_array( &control, &array, n, interpcode );  return this;

}



/*! @brief Update record (update TAB2, to be developed further ...)  */
LTT2* LTT2::Update() {

  control.Update();

  return this;

}


/*! @brief Clear array */
LTT2* LTT2::Clear() {

  ENDF::clear( &control, &array );  return this;

}

/*! @brief Clear table array */
LTT2* LTT2::ClearArray() {

  control.ClearArray();  array.clear();  return this;

}

/*! @brief Push a record from the front */
LTT2* LTT2::PushFront( const Record& o, const int interpcode ) {

  push_front( &control, &array, o, interpcode );  return this;

}

/*! @brief Push a record from the back */
LTT2* LTT2::PushBack ( const Record& o, const int interpcode ) {

  push_back( &control, &array, o, interpcode );  return this;

}

/*! @brief Push a record from the front */
LTT2* LTT2::PushFront( const LTT2& o, const int interpcode ) {

  push_front( &control, &array, o.control, o.array, interpcode );  return this;

}

/*! @brief Push a record from the back */
LTT2* LTT2::PushBack ( const LTT2& o, const int interpcode ) {

  push_back( &control, &array, o.control, o.array, interpcode );  return this;

}

/*! @brief Put a record outside the covering energy range,
where the new record will be taken from the first/last node
*/
LTT2* LTT2::PutClone( const double elab ) {

  put_clone( &control, &array, elab );  return this;

}

/*! @brief Erase records from the front
@param[in] n : number of the records to be erased
*/
LTT2* LTT2::PopFront( const int num ) {

  pop_front( &control, &array, num );  return this;

}

/*! @brief Erase records from the back
@param[in] n : number of the records to be erased
*/
LTT2* LTT2::PopBack ( const int num ) {

  pop_back( &control, &array, num );  return this;

}

/*! @brief Erase a record */
LTT2* LTT2::Erase( const double E ) {

  erase( &control, &array, E );  return this;

}

/*! @brief Reduce the number of sub-records by half */
LTT2* LTT2::Thin() {

  thin( &control, &array );  return this;

}

/*! @brief Thin the number of points in the sub-records
@param[in] eps  : accuracy of the interpolation
*/
LTT2* LTT2::Thin( const double eps ) {

  for( int i=0; i<this->size(); i++ ) this->at(i).Thin( eps );

  return this;

}

/*! @brief Thin the number of points in the sub-records
@param[in] mu_min, mu_xmax : X-range to be thnning
@param[in] eps             : accuracy of the interpolation
*/
LTT2* LTT2::Thin( const double mu_min, const double mu_max, const double eps ) {

  for( int i=0; i<this->size(); i++ ) this->at(i).Thin( mu_min, mu_max, eps );

  return this;

}

/*! @brief Cut all the records below E=elab
@param[in] elab : incident energy
@param[in] eps  : accuracy of the interpolation
@note a record will be generated by the interpolation if it is missing at elab
*/
LTT2* LTT2::CutBelow( const double elab, const double eps ) {

  cut_below( &control, &array, elab );  if( this->empty() ) return this;

  if( this->Front().E() < elab ) this->Front() = this->Interp( elab, eps );

  return this;

}

/*! @brief Cut all the records above E=elab
@param[in] elab : incident energy
@param[in] eps  : accuracy of the interpolation
@note a record will be generated by the interpolation if it is missing at elab
*/
LTT2* LTT2::CutAbove( const double elab, const double eps ) {

  cut_above( &control, &array, elab );  if( this->empty() ) return this;

  if( this->Back().E() > elab ) this->Back() = this->Interp( elab, eps );

  return this;

}


/*! @brief Replace data with new records for the given energy range
@param[in] o : new records
*/
LTT2* LTT2::Replace( const LTT2& o ) {

  if( o.Back ().E() < this->Front().E() ) return this;
  if( o.Front().E() > this->Back ().E() ) return this;

  LTT2 lower(*this),upper(*this);

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
bool LTT2::Find( const double E ) const { return find( &control, &array, E ); }

/*! @brief Check if given energy is inside the range */
bool LTT2::Seek( const double E ) const { return seek( &control, &array, E ); }

/*! @brief Check if given energy is inside the range
@param[in]  E          : incident energy
@param[out] index      : index of the record where E should be in-between E(index) and E(index+1)
@param[out] interpcode : interpolation code between the two records
*/
bool LTT2::Seek( const double E, int* index, int* interpcode ) const {

  return seek( &control, &array, E, index, interpcode );

}


/*! @brief Reverse the sequential order */
LTT2* LTT2::Reverse() {

  LTT2 a(*this);

    this->ClearArray();

      for( int i=a.size()-1; i>=0; i-- )

        this->PushBack( a.at(i), a.InterpCode(i) );

  return this;

}


LTT2* LTT2::ScaleEnergy( const double fac ) {

  for( int i=0; i<this->NE(); i++ ) this->E(i) *= fac;  return this;

}

/*! @brief Get energy nodes E_(i=...NE)
@param[out] E : incident energies given in this record
*/
void LTT2::GetEnergyNodes( vector<double>* E ) const { return get_energy_nodes( &array, E ); }



void LTT2::Interp( Record* result, const double eps ) const {

  // exactly corresponding data

  for( int i=0; i<this->NE(); i++ ) if( this->E(i) == result->E() ) {

    *result = this->at(i);  return;
    
  }

  // interp.

  int index, interpcode;

    if( ! this->Seek( result->E(), &index, &interpcode ) ) return;

    Interp2( this->at(index), this->at(index+1), interpcode, result, eps );

    result->T() = Interp1( E(index), T(index), E(index+1), T(index+1), interpcode%20, result->E() );

  return;

}


void LTT2::Interp( TAB1* result, const double eps ) const {

  Record a;

    this->Interp( a.E( result->C2() ) );  result->Set( a );

  return;

}

LTT2::Record LTT2::Interp( const double elab, const double eps ) const {

  Record a;  this->Interp( a.E(elab), eps );  return a;

}

/*! @brief Y is weighted by X^power ( default: Y -> XY ) */
LTT2* LTT2::Weight( const double power ) {

  for( int i=0; i<this->size(); i++ ) this->at(i).Weight( power );  return this;

}

/*! @brief Average distribution (tentative) */
LTT2* LTT2::Average( const int ndiv ) {

  for( int i=0; i<this->size(); i++ ) this->at(i).Average( ndiv );  return this;

}


/*! @brief Calculate averaged distribution in respect to all the E_i */
void LTT2::Average( TAB1* result, const double eps ) const {

  if( this->NE() < 2 ) return;

  TAB1* a = result;

    Average2( this->at(0), this->at(1), this->InterpCode(0), a, eps );

    for( int i=1; i<this->NE()-1; i++ ) {

      Average2( *a, this->at(i+1), this->InterpCode(i), a, eps );

    }

  return;

}

/*! @brief Calculate averaged distribution between E1 and E2 */
void LTT2::Average( const double E1, const double E2, TAB1* result, const double eps ) const {

  LTT2 a(*this);

    a.CutBelow(E1);
    a.CutAbove(E2);

  return a.Average( result, eps );

}



/*! @brief Linearize TAB1 data */
LTT2* LTT2::Linearize( const double eps ) {

  for( int i=0; i<this->size(); i++ ) this->at(i).Linearize( eps );  return this;

}


/*! @brief Value of normalized distribution at given angle
@param[in] elab     : incident energy
@param[in] cosangle : cosine of the scattering angle
*/
double LTT2::f( const double elab, const double cosangle ) const {

  // exactly corresponding data

  for( int i=0; i<this->NE(); i++ ) if( eq( this->E(i), elab ) ) return this->at(i).Interp( cosangle );

  // interp.

  int index, interpcode;

  if( ! this->Seek( elab, &index, &interpcode ) ) return 0.0;

/*
    double E1 = this->E (index  );
    double E2 = this->E (index+1);
    double f1 = this->at(index  ).Interp( cosangle );
    double f2 = this->at(index+1).Interp( cosangle );

  return Interp1( E1, f1, E2, f2, interpcode, elab );
*/

  Record a;

    this->Interp( a.E(elab) );

  return a.Interp( cosangle );

}

/*! @brief Reconstruct normalized distribution at given incident energy
@param[in,out] result : normalized distribution
@param[in] eps        : accuracy of the interpolation
@note resut->C2() will be recognized as the incident energy 
*/
void LTT2::get_f_da( TAB1* result, const double eps ) const {

  Record a;

    this->Interp( a.E( result->C2() ) );  result->Set( a );

  return;

}


/*! @brief Calculate integral (tentative) */
double LTT2::I() const {
// integral (to be checled if this method is valid)

  double x1,x2,y1,y2, sum(0.);

  for( int i=0; i<this->NE()-1; i++ ) {

    x1 = this->E(i  );
    x2 = this->E(i+1);
    y1 = this->at(i  ).I();
    y2 = this->at(i+1).I();

    sum += Integral1( x1, y1, x2, y2, this->InterpCode(i)%20 );

  }

  return sum;

/*
  TAB1 temp;

  double sum = 0.0;

  for( int i=0; i<NE()-1; i++ ) {

    Integrate( ary[i], ary[i+1], this->InterpCode(i), temp.Clear(), 1000 );

    double a = temp.Integral();

    sum += temp.Integral( eps );

  }

  return sum;
*/

}


/*! @brief Get profile at \f$ \mu \f$
@param[in] mu      : cosine \f$ \mu \f$
@param[out] result : profile, viz., \f$ f(E) \f$ at \f$ \mu \f$
*/
void LTT2::GetProfile( const double mu, TAB1* result ) const {

  for( int i=0; i<this->NE(); i++ )

    result->PushBack( this->E(i), this->at(i).Interp(mu), this->InterpCode(i)%10 );

  return;

}


LTT2& LTT2::operator+=( const double val ) {

  for( int i=0; i<this->NE(); i++ ) this->at(i).operator+=( val );  return *this;

}

LTT2& LTT2::operator-=( const double val ) {

  for( int i=0; i<this->NE(); i++ ) this->at(i).operator-=( val );  return *this;

}

LTT2& LTT2::operator*=( const double val ) {

  for( int i=0; i<this->NE(); i++ ) this->at(i).operator*=( val );  return *this;

}

LTT2& LTT2::operator/=( const double val ) {

  for( int i=0; i<this->NE(); i++ ) this->at(i).operator/=( val );  return *this;

}



bool LTT2::operator==( const LTT2& o ) const { return ( control == o.control && array == o.array ); }
bool LTT2::operator!=( const LTT2& o ) const { return !( *this == o ); }
bool LTT2::operator< ( const LTT2& o ) const { return ( control <  o.control ); }
bool LTT2::operator> ( const LTT2& o ) const { return ( control >  o.control ); }
bool LTT2::operator<=( const LTT2& o ) const { return ( control <= o.control ); }
bool LTT2::operator>=( const LTT2& o ) const { return ( control >= o.control ); }




/*
void LTT2::Integral( TAB1* ans, const int nrandom ) const {
// under development
// integrate with Monte Carlo method to be used for e.g., angle-integral spectra
// nrandom : number of random numbers ( default = 1000 )

  for( int i=0; i<this->NE()-1; i++ ) {

    Integrate( this->at(i), this->at(i+1), this->InterpCode(i), ans, nrandom );

  }

  return;

}
*/

/*
void LTT2::Integral( TAB1* ans, const int nrandom ) const {
// integrate with Monte Carlo method to be used for e.g., angle-integral spectra
// nrandom : number of random numbers ( default = 1000 )

  TAB1 temp;

  for( int i=0; i<this->NE()-1; i++ ) {

    temp.Clear();

    Integrate( this->at(i), this->at(i+1), this->InterpCode(i), &temp, nrandom );

    *ans += temp;

  }

  return;

}
*/

};
