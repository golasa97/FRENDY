#include "CommonUtils/VectorSizeChecker.hpp"

using namespace frendy;

//constructor
VectorSizeChecker::VectorSizeChecker(void)
{
}

//destructor
VectorSizeChecker::~VectorSizeChecker(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void VectorSizeChecker::output_error_message( string& class_name, string& func_name, int i, int i_max,
                                              int size_no_ori, int size_no_dif )
{
  ostringstream oss01, oss02, oss03, oss04;
  oss01 << i+1;
  oss02 << i_max;
  oss03 << size_no_ori;
  oss04 << size_no_dif;

  string str_data01 = "Position                  : " + oss01.str() + " / " + oss02.str();
  string str_data02 = "Size number at first data : " + oss03.str();
  string str_data03 = "Different size number     : " + oss04.str();

  vector<string> err_com;
  err_com.push_back(str_data01);
  err_com.push_back(str_data02);
  err_com.push_back(str_data03);
  err_com.push_back("The array size at each position is different.");
  err_com.push_back("Please check the array data");
  err_obj.output_runtime_error(class_name, func_name, err_com);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer VectorSizeChecker::vec_size_check_array2_int
                             (string& class_name, string& func_name, vector<vector<Integer> >& vec)
                           
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

Integer VectorSizeChecker::vec_size_check_array3_int
                             (string& class_name, string& func_name, vector<vector<vector<Integer> > >& vec)
                           
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

Integer VectorSizeChecker::vec_size_check_array4_int
                             ( string& class_name, string& func_name,
                               vector<vector<vector<vector<Integer> > > >& vec )
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

Integer VectorSizeChecker::vec_size_check_array5_int
                             ( string& class_name, string& func_name,
                               vector<vector<vector<vector<vector<Integer> > > > >& vec )
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

Integer VectorSizeChecker::vec_size_check_array6_int
                             ( string& class_name, string& func_name,
                               vector<vector<vector<vector<vector<vector<Integer> > > > > >& vec )
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer VectorSizeChecker::vec_size_check_array2_real
                             (string& class_name, string& func_name,  vector<vector<Real> >& vec)
                          
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

Integer VectorSizeChecker::vec_size_check_array3_real
                             (string& class_name, string& func_name, vector<vector<vector<Real> > >& vec)
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

Integer VectorSizeChecker::vec_size_check_array4_real
                             ( string& class_name, string& func_name,
                               vector<vector<vector<vector<Real> > > >& vec )
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

Integer VectorSizeChecker::vec_size_check_array5_real
                             ( string& class_name, string& func_name,
                               vector<vector<vector<vector<vector<Real> > > > >& vec )
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

Integer VectorSizeChecker::vec_size_check_array6_real
                             ( string& class_name, string& func_name,
                               vector<vector<vector<vector<vector<vector<Real> > > > > >& vec )
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer VectorSizeChecker::vec_size_check_array2_real8
                             (string& class_name, string& func_name, vector<vector<Real8> >& vec)
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

Integer VectorSizeChecker::vec_size_check_array3_real8
                             (string& class_name, string& func_name, vector<vector<vector<Real8> > >& vec)
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

Integer VectorSizeChecker::vec_size_check_array4_real8
                             ( string& class_name, string& func_name,
                               vector<vector<vector<vector<Real8> > > >& vec )
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

Integer VectorSizeChecker::vec_size_check_array5_real8
                             ( string& class_name, string& func_name,
                               vector<vector<vector<vector<vector<Real8> > > > >& vec )
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

Integer VectorSizeChecker::vec_size_check_array6_real8
                             ( string& class_name, string& func_name,
                               vector<vector<vector<vector<vector<vector<Real8> > > > > >& vec )
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer VectorSizeChecker::vec_size_check_array2_str
                             (string& class_name, string& func_name, vector<vector<string> >& vec)
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }
  return static_cast<Integer>(size_no_ori);
}

Integer VectorSizeChecker::vec_size_check_array3_str
                             (string& class_name, string& func_name, vector<vector<vector<string> > >& vec)
{
  int i_max = static_cast<int>(vec.size());
  if( i_max <= 0 )
  {
    return 0;
  }
  
  int size_no_ori = static_cast<int>(vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( size_no_ori != static_cast<int>(vec[i].size()) )
    {
      output_error_message( class_name, func_name, i, i_max,
                            size_no_ori, static_cast<int>(vec[i].size()) );
    }
  }

  return static_cast<Integer>(size_no_ori);
}
