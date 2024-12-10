#include "ReconResonance/RmatrixLimited/rml/Particle.h"

//ClassImp( RML::Particle );

namespace RML {

/*! @brief Default constructor where the particle is set as neutron */
Particle::Particle()               { this->Set(  1 ); }

/*! @brief Constructor with built-in information
@param[in] za : 1000*Z+A of the particle
@li    0 (gamma-ray),
@li    1 (neutron)        : parity = +1;  spin = 0.5;  mass= 1.00866491574;
@li 1001 (proton)         : parity = +1;  spin = 0.5;  mass= 1.00782503207;
@li 1002 (deutron)        : parity = +1;  spin = 1.0;  mass= 2.01410177785;
@li 1003 (triton)         : parity = +1;  spin = 0.5;  mass= 3.01604927767;
@li 2003 (helium-3)       : parity = +1;  spin = 0.5;  mass= 3.01602931914;
@li 2004 (alpha-particle) : parity = +1;  spin = 0.0;  mass= 4.00260325415;
*/
Particle::Particle( const int za ) { this->Set( za ); }

/*! @brief Constructor with external values
@param[in] za : 1000*Z+A of the particle
@param[in] j  : spin
@param[in] pi : parity
@param[in] m  : mass [amu]
*/
Particle::Particle( const int za, const double j, const int pi, const double m ) { this->Set( za,j,pi,m ); }

/*! @brief Destructor */
Particle::~Particle() {}



/*! @brief Set particle
@param[in] za : 1000*Z+A of the particle
@li    0 (gamma-ray),
@li    1 (neutron)        : parity = +1;  spin = 0.5;  mass= 1.00866491574;
@li 1001 (proton)         : parity = +1;  spin = 0.5;  mass= 1.00782503207;
@li 1002 (deutron)        : parity = +1;  spin = 1.0;  mass= 2.01410177785;
@li 1003 (triton)         : parity = +1;  spin = 0.5;  mass= 3.01604927767;
@li 2003 (helium-3)       : parity = +1;  spin = 0.5;  mass= 3.01602931914;
@li 2004 (alpha-particle) : parity = +1;  spin = 0.0;  mass= 4.00260325415;
*/
void Particle::Set( const int za ) {

  z = za/1000;  a = za%1000;  n = a-z;

  switch( za ) {

    case    0 : parity = -1;  spin = 0.0;  mass= 0.00000000000;  break;
    case    1 : parity = +1;  spin = 0.5;  mass= 1.00866491574;  break;
    case 1001 : parity = +1;  spin = 0.5;  mass= 1.00782503207;  break;
    case 1002 : parity = +1;  spin = 1.0;  mass= 2.01410177785;  break;
    case 1003 : parity = +1;  spin = 0.5;  mass= 3.01604927767;  break;
    case 2003 : parity = +1;  spin = 0.5;  mass= 3.01602931914;  break;
    case 2004 : parity = +1;  spin = 0.0;  mass= 4.00260325415;  break;

    default:
      cerr << "!! Particle::Set -> not found ZA= " << za << endl;
      exit(1);

  }

  return;

}

/*! @brief Set particle with external values
@param[in] za : 1000*Z+A of the particle
@param[in] j  : spin
@param[in] pi : parity
@param[in] m  : mass [amu]
*/
void Particle::Set( const int za, const double j, const int pi, const double m ) {

  z = za/1000;  a = za%1000;  n = a-z;  spin = j;  parity = pi;  mass = m; 

}


void Particle::Set( const Particle& o ) {

  if( &o == this ) return;

  *this = o;  return;

}


/*! @brief Number of the protons */
const int& Particle::Z () const { return z; }
      int& Particle::Z ()       { return z; }

/*! @brief Number of the nucleons */
const int& Particle::A () const { return a; }
      int& Particle::A ()       { return a; }

/*! @brief Number of the neutrons */
const int& Particle::N () const { return n; }
      int& Particle::N ()       { return n; }

/*! @brief 1000*Z+A */
int  Particle::ZA() const { return 1000*z+a; }

/*! @brief Mass [amu] */
const double& Particle::Mass  () const { return mass  ; }
      double& Particle::Mass  ()       { return mass  ; }

/*! @brief Spin */
const double& Particle::Spin  () const { return spin  ; }
      double& Particle::Spin  ()       { return spin  ; }

/*! @brief Parity (positive/negative) */
const int& Particle::Parity() const { return parity; }
      int& Particle::Parity()       { return parity; }

/*! @brief Mass (ratio to that of the neutron) */
double Particle::AW() const { return mass/Particle(1).Mass(); }



bool Particle::operator==( const Particle& o ) const {

  return ( z == o.z && a == o.a && n == o.n && parity == o.parity && eq( mass,o.mass ) && eq( spin,o.spin ) );

}

bool Particle::operator!=( const Particle& o ) const { return !( *this == o ); }
bool Particle::operator< ( const Particle& o ) const { return ( this->ZA() < o.ZA() ); }
bool Particle::operator> ( const Particle& o ) const { return ( this->ZA() > o.ZA() ); }


void Particle::Print( ostream& os ) const {

  os << "(za,j,parity)=" << setw(4) << this->ZA() << ',' << setw(3) << spin << ',' << ((parity>0) ? '+' : '-');  return;

}



ostream& operator<<( ostream& os, const Particle& o ) {

  o.Print( os );  return os;

}


}
