#include "ReconResonance/RmatrixLimited/rml/Nucleus.h"

//ClassImp( RML::Nucleus );


namespace RML {

/*! @brief Default constructor */
Nucleus::Nucleus() {

  this->Set( 0, 0.0, 0, 0.0, 0.0 );

}

/*! @brief Constructor
@param[in] za : 1000*Z+A of the particle
@param[in] j  : spin
@param[in] pi : parity
@param[in] m  : mass [amu]
@param[in] m  : excitation energy [eV]
*/
Nucleus::Nucleus( const int za, const double j, const int pi, const double m, const double ex ) {

  this->Set( za, j, pi, m, ex );

}

/*! @brief Destructor */
Nucleus::~Nucleus() {}


/*! @brief Set Particle
@param[in] za : 1000*Z+A of the particle
@param[in] j  : spin
@param[in] pi : parity
@param[in] m  : mass [amu]
@param[in] m  : excitation energy [eV]
*/
void Nucleus::Set( const int za, const double j, const int pi, const double m, const double ex ) {

  z = za/1000;  a = za%1000;  n = a-z;  spin = j;  parity = pi;  mass = m;  energy = ex;

}

void Nucleus::Set( const Nucleus& o ) {

  if( &o == this ) return;

  *this = o;

}


/*! @brief Number of the protons */
const int& Nucleus::Z () const { return z; }
      int& Nucleus::Z ()       { return z; }

/*! @brief Number of the nucleons */
const int& Nucleus::A () const { return a; }
      int& Nucleus::A ()       { return a; }

/*! @brief Number of the neutrons */
const int& Nucleus::N () const { return n; }
      int& Nucleus::N ()       { return n; }

/*! @brief 1000*Z+A */
int  Nucleus::ZA() const { return 1000*z+a; }


/*! @brief Mass [amu] */
const double& Nucleus::Mass  () const { return mass  ; }
      double& Nucleus::Mass  ()       { return mass  ; }

/*! @brief Spin */
const double& Nucleus::Spin  () const { return spin  ; }
      double& Nucleus::Spin  ()       { return spin  ; }

/*! @brief Parity (positive/negative) */
const int& Nucleus::Parity() const { return parity; }
      int& Nucleus::Parity()       { return parity; }

/*! @brief Excitation energy */
const double& Nucleus::Energy() const { return energy; }
      double& Nucleus::Energy()       { return energy; }

/*! @brief Mass (ratio to that of the neutron) */
double Nucleus::AW() const { return mass/Particle(1).Mass(); }


bool Nucleus::operator==( const Nucleus& o ) const {

  return ( z == o.z && a == o.a && n == o.n && parity == o.parity
       && eq( mass,o.mass ) && eq( spin,o.spin ) && eq( energy,o.energy ) );

}

bool Nucleus::operator!=( const Nucleus& o ) const { return !( *this == o ); }
bool Nucleus::operator< ( const Nucleus& o ) const { return ( this->ZA() < o.ZA() ); }
bool Nucleus::operator> ( const Nucleus& o ) const { return ( this->ZA() > o.ZA() ); }



void Nucleus::Print( ostream& os ) const {

  //os << "(za,j,parity)=" << this->ZA() << ',' << spin << ',' << ((parity>0) ? '+' : '-');  return;

  os << "(za,j,parity)=" << setw(4) << this->ZA() << ',' << setw(3) << spin << ',' << ((parity>0) ? '+' : '-');  return;

}



ostream& operator<<( ostream& os, const Nucleus& o ) {

  o.Print( os );  return os;

}


}
