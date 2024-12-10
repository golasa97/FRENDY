#if !defined(___Class_MultiThread)
    #define  ___Class_MultiThread

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <pthread.h>

#define MAX_THREAD_Q 500

using namespace std;

namespace Basics {

// Thread functions

template<class T> void Wait( T* o ) {

  if( *o->nthreads <= *o->maxthreads ) return;

  pthread_mutex_lock  ( o->mutex );
  pthread_cond_wait   ( o->cond, o->mutex );
  pthread_mutex_unlock( o->mutex );

}

template<class T> void Signal( T* o ) {

  if( *o->nthreads <= *o->maxthreads ) return;

  pthread_mutex_lock  ( o->mutex );
  pthread_cond_signal ( o->cond  );
  pthread_mutex_unlock( o->mutex );

}




// Thread class

template<class T> class MultiThread {

  int maxthreads, nthreads;  bool show_status;
  pthread_mutex_t mutex; pthread_cond_t cond;  vector<pthread_t> threads;

 public:

  MultiThread();
 ~MultiThread();

  MultiThread* ShowStatus( const bool option ) { show_status = option;  return this; }

  MultiThread* MaxThreads( const int n ) { maxthreads = n;  return this; }

  MultiThread* Create( void* f(void*), T* o, const int i0, const int ntt );

  MultiThread* Join();
  MultiThread* Join( const int nthreads_total, int* n_finish );

};


template<class T> MultiThread<T>:: MultiThread() : maxthreads(1), show_status(true) {}
template<class T> MultiThread<T>::~MultiThread(){}



template<class T> MultiThread<T>* MultiThread<T>::Create( void* f(void*), T* o, const int i0, const int ntt ) {
// i0  : beginning index of the array
// ntt : number of the total threads

  nthreads = ntt;

  pthread_mutex_init( &mutex, NULL );
  pthread_cond_init ( &cond,  NULL ); 

  threads.resize( nthreads );

//int m = 0;

    for( int i=i0; i<i0+ntt; i++ ) {

      o[i].mutex = &mutex;  o[i].cond = &cond;
      o[i].maxthreads = &maxthreads; o[i].nthreads = &nthreads;

      if( pthread_create( &threads[i-i0], NULL, f, &o[i] ) != 0 ) {

        cerr << "failed pthread_create" << endl;
        //abort();

      }

//m++;

    }

//cerr << m << endl;

  //cerr << "n_waiting = " << n_waiting << endl;

  return this;

}




template<class T> MultiThread<T>* MultiThread<T>::Join() {

  if( maxthreads < nthreads )

    for( int i=0; i<maxthreads; i++ ) {
  
      pthread_mutex_lock  ( &mutex );
      pthread_cond_signal( &cond );
      pthread_mutex_unlock( &mutex );

    }

  // join threads

  for( int i=0; i<nthreads; i++ ) pthread_join( threads[i], NULL );

    pthread_mutex_destroy( &mutex );
    pthread_cond_destroy ( &cond  );

  return this;

}


static void print_status( pthread_mutex_t* mutex, const int percent ) {

  pthread_mutex_lock  ( mutex );
    cerr << "\r" << " ... complete " << setw(3) << percent << " % ...";
  pthread_mutex_unlock( mutex );

}


// with message for the status
template<class T> MultiThread<T>* MultiThread<T>::Join( const int nthreads_total, int* n_finish ) {

  if( maxthreads < nthreads )

    for( int i=0; i<maxthreads; i++ ) {
  
      pthread_mutex_lock  ( &mutex );
      pthread_cond_signal( &cond );
      pthread_mutex_unlock( &mutex );

    }

  // join threads

  if( show_status ) print_status( &mutex, 100*(*n_finish)/nthreads_total );

  for( int i=0; i<nthreads; i++ )

    if( pthread_join( threads[i], NULL ) == 0 ) {

      if( show_status ) print_status( &mutex, 100*(++(*n_finish))/nthreads_total );

    }

    if( show_status ) cerr << "\r" << "\033[2K";

    //for( int i=0; i<23; i++ ) cerr << "\b" << ' ' << "\b";

    pthread_mutex_destroy( &mutex );
    pthread_cond_destroy ( &cond  );

  return this;

}



// do calculations (internal)
template<class T> void ExecuteMultiThread( void* f(void*), T* o, const int n, const int i0, const int ntt, const int maxthreads, int* n_finished, const bool monitor = true ) {
// i0  : beginning index of the array
// ntt : number of the total threads

  MultiThread<T> a;

    a.MaxThreads( maxthreads )->ShowStatus( monitor )->Create( f,o,i0,ntt )->Join( n, n_finished );

  return;

}

// do calculations (internal)
template<class T> void ExecuteMultiThread_Q( void* f(void*), T* o, const int n, const int maxthreads, const int max_queue, const bool monitor = true ) {

  int max_q = max_queue;  int m = n/max_q;  int n1 = n%max_q;  int n_finished = 0;

    for( int i=0; i<m; i++ ) ExecuteMultiThread( f, o, n, max_q*i, max_q,  maxthreads, &n_finished, monitor );
    if( n1 > 0 )             ExecuteMultiThread( f, o, n, max_q*m, n1,     maxthreads, &n_finished, monitor );

  return;

}



// do calculations
template<class T> void ExecuteMultiThread( void* f(void*), T* o, const int n, const int maxthreads, const int batch_mode = 1, const bool monitor = true ) {

  if( batch_mode == 1 ) return ExecuteMultiThread_Q( f,o,n,maxthreads, MAX_THREAD_Q, monitor );
  if( batch_mode == 2 ) return ExecuteMultiThread_Q( f,o,n,maxthreads, maxthreads,   monitor );


  MultiThread<T> a;  int n_finished = 0;

    a.MaxThreads( maxthreads )->Create( f,o,0,n )->Join( n, &n_finished );

  return;

}

// do calculations
template<class T> void ExecuteMultiThread( void* f(void*), vector<T>* o, const int maxthreads, const int batch_mode = 1, const bool monitor = true ) {

  return ExecuteMultiThread( f, o->data(), o->size(), maxthreads, batch_mode, monitor );

}


};

#endif
