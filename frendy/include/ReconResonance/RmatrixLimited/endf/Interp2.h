#ifndef _Interp2
#define _Interp2

#include "ReconResonance/RmatrixLimited/endf/TAB1.h"

using namespace std;
//using namespace ENDF;

namespace ENDF {

/* Two-dimensional interpolation */

//double Interp2( const TAB1& a, const TAB1& b, const int interpcode, const double x0, const double x );
//void   Interp2( const TAB1& a, const TAB1& b, const int interpcode, TAB1* ans, const double eps );

void Interp2( const TAB1& a, const TAB1& b, const int interpcode, TAB1* c, const double eps_c =1.e-3 );

void Average2( const TAB1& a, const TAB1& b, const int interpcode, TAB1* c, const double eps_c = 1.e-3 );

void UnitBase( TAB1* a, TAB1* b, const double x );

//void Integrate( const TAB1& a, const TAB1& b, const int interpcode, TAB1* ans, const int nrandom = 1000 );

void Integrate( const TAB1& a, const TAB1& b, const int interpcode, TAB1* c, const double eps_c =1.e-3 );

};

#endif

