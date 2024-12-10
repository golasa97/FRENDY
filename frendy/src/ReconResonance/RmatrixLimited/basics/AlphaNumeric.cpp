#include "ReconResonance/RmatrixLimited/basics/AlphaNumeric.h"

namespace Basics {

string wrap_in_parenthesize( const int a, const int b ) {

  stringstream ss;

    ss << '(' << a << ',' << b << ')';

  return ss.str();

}


void remove( string* o, const string expression ) {

  if( o == NULL ) return;

  for( size_t c = o->find_first_of(expression); c != string::npos; c = o->find_first_of(expression) )

    o->erase(c,1);

  return;

}


void push_back( const string& a, vector<int>*    v ) { v->push_back( atoi( a.c_str() ) ); }
void push_back( const string& a, vector<double>* v ) { v->push_back( atof( a.c_str() ) ); }
void push_back( const string& a, vector<string>* v ) { v->push_back(               a   ); }


void break_down( const string in, vector<string>* a, const string pattern ) {

  string xline(in);

    //remove_space( &xline );  do NOT so !!!

  a->clear();

  char x[ xline  .size() ];   strcpy( x, xline  .c_str() );
  char d[ pattern.size() ];   strcpy( d, pattern.c_str() );

  char* tp = strtok( x,d );

    while( tp != (char*) NULL ) {

      a->push_back( tp );  tp = strtok( (char*) NULL, d );

    }

  return;

}

void break_down( const string in, vector<int>* a ) {

  vector<string> v,vv;

    break_down( in, &v, "," );

      for( int i=0; i<static_cast<int>(v.size()); i++ ) {

        break_down( v.at(i), &vv, "~" );

        for( int ii=atoi(vv.front().c_str()); ii<=atoi(vv.back().c_str()); ii++ ) a->push_back(ii);

      }

  return;

}

void break_down( const string in, vector<float>* a ) {

  vector<string> v;

    break_down( in, &v, "," );

      for( int i=0; i<static_cast<int>(v.size()); i++ ) a->push_back( atof( v[i].c_str() ) );

  return;

}


// replace text
void replace( string* t, const string s, const string with ) {

  string::size_type  pos( t->find( s ) );

    while( pos != string::npos ) {

        t->replace( pos, s.length(), with );
	pos = t->find( s, pos + with.length() );

    }

  return;

}


// "~/***" -> absolute path
const string get_your_directory( const string file_name ) {

  string file_name_new = file_name;

    replace( &file_name_new, "~/", getenv("HOME") + string("/") );

  return file_name_new;

}

};
