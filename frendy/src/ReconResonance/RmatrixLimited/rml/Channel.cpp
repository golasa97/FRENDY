#include "ReconResonance/RmatrixLimited/rml/Channel.h"

//ClassImp( RML::Channel );

namespace RML {


/*! @brief Constructor */
Channel::Channel() : l_val(99999), s_val(99999.), J_val(99999.) {}

/*! @brief Constructor */
Channel::Channel( const Channel& ch ) {

  this->Set( ch );

}

/*! @brief Constructor
@param[in] o : partition
*/
Channel::Channel( const TwoBody& o ) : l_val(99999), s_val(99999.), J_val(99999.){

  this->Set( o );

}

/*! @brief Constructor
@param[in] a : particle
@param[in] b : nucleus
*/
Channel::Channel( const Particle& a, const Nucleus& b ) : l_val(99999), s_val(99999.), J_val(99999.) {

  this->Set( a,b );

}

/*! @brief Constructor
@param[in] o : partition
@param[in] l : orbital angular momentum for the relative motion 
*/
Channel::Channel( const TwoBody& o, const int l ) : s_val(99999.), J_val(99999.) {

  this->Set( o,l );

}

/*! @brief Constructor
@param[in] a : particle
@param[in] b : nucleus
@param[in] l : orbital angular momentum for the relative motion 
*/
Channel::Channel( const Particle& a, const Nucleus& b, const int l ) : s_val(99999.), J_val(99999.) {

  this->Set( a,b,l );

}

/*! @brief Constructor
@param[in] o : partition
@param[in] J : total spin
@param[in] l : orbital angular momentum for the relative motion 
@param[in] s : channel spin
*/
Channel::Channel( const TwoBody& o, const double J, const int l, const double s ) : J_val(99999.) {

  this->Set( o,J,l,s );

}

/*! @brief Constructor
@param[in] a : particle
@param[in] b : nucleus
@param[in] J : total spin
@param[in] l : orbital angular momentum for the relative motion 
@param[in] s : channel spin
*/
Channel::Channel( const Particle& a, const Nucleus& b, const double J, const int l, const double s ) {

  this->Set( a,b,J,l,s );

}

/*! @brief Destructor */
Channel::~Channel() {}



/*! @brief Get partition */
const TwoBody& Channel::alpha() const { return *this; }
      TwoBody& Channel::alpha()       { return *this; }


/*! @brief Set explicit channel */
void Channel::Set( const Channel& ch ) {

  if( &ch == this ) return;

  this->TwoBody::Set( ch );

    J_val = ch.J();  l_val = ch.l();  s_val = ch.s();

  return;

}



/*! @brief Set partition
@param[in] o : partition
*/
void Channel::Set( const TwoBody& o ) {

  this->TwoBody::Set( o );  return;

}

/*! @brief Set particle + nucleus pair
@param[in] a : particle
@param[in] b : nucleus
*/
void Channel::Set( const Particle& a, const Nucleus& b ) {

  this->Particle::Set(a);
  this->Nucleus ::Set(b);

  return;

}

/*! @brief Set partition and angular momentum
@param[in] o : partition
@param[in] l : orbital angular momentum for the relative motion 
*/
void Channel::Set( const TwoBody& o, const int l ) {

  this->TwoBody::Set( o );  l_val = l;  return;

}

/*! @brief Set partition and angular momentum
@param[in] a : particle
@param[in] b : nucleus
@param[in] l : orbital angular momentum for the relative motion 
*/
void Channel::Set( const Particle& a, const Nucleus& b, const int l ) {

  this->Particle::Set(a);
  this->Nucleus ::Set(b);

  l_val = l;

  return;

}

/*! @brief Set partition total spin, angular momentum and channel spin
@param[in] o : partition
@param[in] J : total spin
@param[in] l : orbital angular momentum for the relative motion 
@param[in] s : channel spin
*/
void Channel::Set( const TwoBody& o, const double J, const int l, const double s ) {

  this->Set( o );

    J_val = J;  l_val = l;  s_val = s;

  return;

}

/*! @brief Set partition total spin, angular momentum and channel spin
@param[in] a : particle
@param[in] b : nucleus
@param[in] J : total spin
@param[in] l : orbital angular momentum for the relative motion 
@param[in] s : channel spin
*/
void Channel::Set( const Particle& a, const Nucleus& b, const double J, const int l, const double s ) {

  this->Set(a,b);

    J_val = J;  l_val = l;  s_val = s;

  return;

}


/*! @brief Get total parity */
int Channel::pi() const {

  return this->TwoBody::pi() * ( ( this->l()%2==0 ) ? 1:-1 );

}



bool Channel::Equiv( const Channel& ch ) const {

  return ( this->TwoBody::Equiv(ch) && eq( J_val,ch.J() ) && l_val == ch.l() && eq( s_val,ch.s() ) );

}

bool Channel::Equiv( const TwoBody& a, const double J, const int l ) const {

  return ( this->TwoBody::Equiv(a) && eq( J_val,J ) && l_val == l );

}

bool Channel::Equiv( const TwoBody& a, const int l ) const {

  return ( this->TwoBody::Equiv(a) && l_val == l );

}


/*
void Channel::Print( ostream& os ) const {

  os << "l = " << l_val << "   s = " << s_val
     << "  za1 = " << this->Particle::ZA() << "  za2 = " << this->Nucleus::ZA();

}
*/

void Channel::Print( ostream& os ) const {

  os.setf(ios::fixed, ios::floatfield);

  /*
  os << '(';

  os << setw(5) << setfill('0') << this->Particle::ZA() << ',' << setprecision(1) << this->Particle::Spin() << setw(1) << ( this->Particle::Parity()>=0 ? '+' : '-' ) << ':'
     << setw(5) << setfill('0') << this->Nucleus ::ZA() << ',' << setprecision(1) << this->Nucleus ::Spin() << ( this->Nucleus ::Parity()>=0 ? '+' : '-' ) << ';'
     << l_val << ',' << setprecision(1) << s_val;

  os << ')';
  */

  os << '(';

  os << setw(4) << setfill('0') << this->Particle::ZA() << ',' << setprecision(1) << this->Particle::Spin() << setw(1) << ( this->Particle::Parity()>=0 ? '+' : '-' ) << ':'
     << setw(5) << setfill('0') << this->Nucleus ::ZA() << ',' << setprecision(1) << this->Nucleus ::Spin() << ( this->Nucleus ::Parity()>=0 ? '+' : '-' ) << ';';


  if( l_val == 99999 ) os << '*'   << ',';
  else                 os << l_val << ',';

  if( s_val >  99998 ) os << "***" << ';';
  else                 os << setprecision(1) << s_val << ';';

  if( J_val >  99998 ) os << "***";
  else                 os << setprecision(1) << J_val;

  os << ')';

  return;

}


ostream& operator<<( ostream& os, const Channel& o ) {

  o.Print( os );  return os;


}

}
