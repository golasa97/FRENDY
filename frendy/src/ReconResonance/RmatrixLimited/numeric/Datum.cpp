#include "ReconResonance/RmatrixLimited/numeric/Datum.h"
#include "ReconResonance/RmatrixLimited/numeric/Approx.h"

#ifdef Use_CINT
ClassImp( Numeric::Datum );
#endif


namespace Numeric {

/*
  Datum:: Datum() : v(0.,0.) {}
  Datum:: Datum( const double x, const double y ) : v(x,y) {}
  Datum::~Datum() {}

  const double& Datum::X() const { return v.first ; }
        double& Datum::X()       { return v.first ; }
  const double& Datum::Y() const { return v.second; }
        double& Datum::Y()       { return v.second; }
*/

  Datum:: Datum() { v[0] = 0.0;  v[1] = 0.0; }
  Datum:: Datum( const double x, const double y ) { this->Set(x,y); }
  Datum::~Datum() {}

  const double& Datum::X() const { return v[0]; }
        double& Datum::X()       { return v[0]; }
  const double& Datum::Y() const { return v[1]; }
        double& Datum::Y()       { return v[1]; }

  Datum* Datum::X( const double val ) { this->X() = val; return this; }
  Datum* Datum::Y( const double val ) { this->Y() = val; return this; }

  Datum* Datum::Set( const double x, const double y ) { return this->X(x)->Y(y); }

  void Datum::Write( ostream& os ) const {

    os.setf( ios::scientific );

    os << this->X() << " " << this->Y() << endl;

    os.unsetf( ios::scientific );

    return;

  }



  bool Datum::operator==( const Datum& o ) const {

    //return ( this->X() == o.X() && this->Y() == o.Y() );

    return ( eq( this->X(), o.X() ) && eq( this->Y(), o.Y() ) );
 
  }

  bool Datum::operator!=( const Datum& o ) const {

    return !( *this == o );

  }

  bool Datum::operator<( const Datum& o ) const {

    if( lt( this->X(), o.X() ) ) return true ;
    if( gt( this->X(), o.X() ) ) return false;
    if( lt( this->Y(), o.Y() ) ) return true ;
    if( gt( this->Y(), o.Y() ) ) return false;

    return false;

  }

  bool Datum::operator>( const Datum& o ) const {

    return( ! this->operator<=( o ) );

  }

  bool Datum::operator<=( const Datum& o ) const {

    return ( this->operator==( o ) || this->operator<( o ) );

  }

  bool Datum::operator>=( const Datum& o ) const {

    return ( this->operator==( o ) || this->operator>( o ) );

  }



  // out stream

  ostream& operator<<( ostream& os, const Datum& o ) {

    o.Write( os );

    /*
    os.setf( ios::scientific );

    os << o.X() << "  " << o.Y();

    os.unsetf( ios::scientific );
    */
  
    //os << endf( o.X() ) << endf( o.Y() );

    return os;

  }


}
