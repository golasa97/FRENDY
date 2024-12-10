#ifndef _AlphaNumeric_
#define _AlphaNumeric_

#include <vector>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

namespace Basics {

string wrap_in_parenthesize( const int a, const int b );
void remove( string* o, const string expression = " " );

void push_back( const string& a, vector<int>*    v );
void push_back( const string& a, vector<double>* v );
void push_back( const string& a, vector<string>* v );

template <class T> int split( const char* input, vector<T>* output, const char pattern = ',' ) {

  stringstream ss{input};  string buf;

    while ( getline( ss, buf, pattern ) ) push_back( buf, output );

  return output->size();

}

template <class T> int split( const string& input, vector<T>* output, const char pattern = ',' ) {

  return split( input.c_str(), output, pattern );

}


void break_down( const string in, vector<string>* v, const string pattern = "," );
void break_down( const string in, vector<int>*   a );
void break_down( const string in, vector<float>* a );

void replace( string* t, const string s, const string with );

const string get_your_directory( const string file_name );

};

#endif
