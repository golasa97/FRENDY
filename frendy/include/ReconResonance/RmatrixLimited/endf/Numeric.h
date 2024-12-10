#ifndef _Numeric_
#define _Numeric_

#include "ReconResonance/RmatrixLimited/basics/AlphaNumeric.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
using namespace Basics;

namespace ENDF {

string endf( const int, const int, const int, int );
string endf( const int, const int, const int, int* );
string endf( const int );
string endf( const double );

int    int_endf( const string );
double dbl_endf( const string& );

int num_of_lines( const int, const int );


void translate( ostream& os, const char* text, const int value, const int width = 11 );

double NaturalAbundance( const int za );
vector<double> NaturalIsotopes( const int z );





// Scan record from the file
template<class T> T* scan( T* o, const char* file_name ) {

  ifstream ifs;

    ifs.open( get_your_directory( file_name ).c_str(), ios::in );

      if( ! ifs.is_open() ) {

        cerr << "!! Failed to open file : " << file_name << endl;  return o;

      }

      o->Store( ifs );

    ifs.close();

  return o;

}

// Write record into the file
template<class T> void write( T* o, const char* file_name ) {

  ofstream ofs( get_your_directory( file_name ).c_str() );

    o->Write( ofs );

  return;

}

};

#endif
