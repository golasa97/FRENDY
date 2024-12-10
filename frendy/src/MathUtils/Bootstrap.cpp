#include "MathUtils/Bootstrap.hpp"

using namespace frendy;

//constructor
Bootstrap::Bootstrap(void)
{
  clear();
}

//destructor
Bootstrap::~Bootstrap(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::clear()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_average(vector<vector<Real8> >& result_data, vector<Real8>& ave_data)
{
  ave_data.clear();

  int i_max = static_cast<int>(result_data.size());
  if( i_max == 0 )
  {
    return;
  }

  int j_max = static_cast<int>(result_data[0].size());
  ave_data.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    vector<Real8> result_data_each;
    result_data_each.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      result_data_each[i] = result_data[i][j];
    }

    calc_average(result_data_each, ave_data[j]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_average(vector<Real8>& result_data, Real8& ave_data)
{
  int i_max = static_cast<int>(result_data.size());
  ave_data  = 0.0;
  for(int i=0; i<i_max; i++)
  {
    ave_data += result_data[i];
  }
  ave_data /= static_cast<Real8>(i_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_average_sq(vector<vector<Real8> >& result_data, vector<Real8>& ave_data)
{
  ave_data.clear();

  int i_max = static_cast<int>(result_data.size());
  if( i_max == 0 )
  {
    return;
  }

  int j_max = static_cast<int>(result_data[0].size());
  ave_data.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    vector<Real8> result_data_each;
    result_data_each.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      result_data_each[i] = result_data[i][j];
    }

    calc_average_sq(result_data_each, ave_data[j]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_average_sq(vector<Real8>& result_data, Real8& ave_data)
{
  int i_max = static_cast<int>(result_data.size());
  ave_data  = 0.0;
  for(int i=0; i<i_max; i++)
  {
    ave_data += result_data[i] * result_data[i];
  }
  ave_data /= static_cast<Real8>(i_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_average_and_error(vector<vector<Real8> >& result_data, 
                                       vector<Real8>& ave_data, vector<Real8>& err_data)
{
  ave_data.clear();
  err_data.clear();

  int i_max = static_cast<int>(result_data.size());
  if( i_max == 0 )
  {
    return;
  }

  int j_max = static_cast<int>(result_data[0].size());
  ave_data.resize(j_max);
  err_data.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    vector<Real8> result_data_each;
    result_data_each.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      result_data_each[i] = result_data[i][j];
    }

    calc_average_and_error(result_data_each, ave_data[j], err_data[j]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_average_and_error(vector<Real8>& result_data, Real8& ave_data, Real8& err_data)
{
  //Average
  calc_average(result_data, ave_data);

  //Statistical error
  int i_max = static_cast<int>(result_data.size());
  err_data  = 0.0;
  for(int i=0; i<i_max; i++)
  {
    err_data += (result_data[i] - ave_data) * (result_data[i] - ave_data);
  }

  if( i_max > 1 )
  {
    err_data /= static_cast<Real8>(i_max - 1);
  }
  else
  {
    err_data *= 1.0E+10;
  }

  err_data = sqrt(err_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_average_and_error_clt_with_ave_and_max
                  (vector<vector<Real8> >& result_data, 
                   vector<Real8>& ave_data, vector<Real8>& err_data, Real8& err_ave, Real8& err_max)
{
  calc_average_and_error_clt(result_data, ave_data, err_data);

  calc_average_and_max(err_data, err_ave, err_max);
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_average_and_error_clt(vector<vector<Real8> >& result_data, 
                                           vector<Real8>& ave_data, vector<Real8>& err_data)
{
  calc_average_and_error(result_data, ave_data, err_data);

  int i_max = static_cast<int>(result_data.size());
  if( i_max == 0 )
  {
    return;
  }

  Real8 coef = 1.0 / sqrt(static_cast<Real8>(i_max));

  int j_max = static_cast<int>(err_data.size());
  for(int j=0; j<j_max; j++)
  {
    err_data[j] *= coef;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_average_and_error_clt(vector<Real8>& result_data, Real8& ave_data, Real8& err_data)
{
  calc_average_and_error(result_data, ave_data, err_data);

  if( static_cast<int>(result_data.size()) > 1 )
  {
    err_data /= sqrt(static_cast<Real8>(result_data.size() - 1));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_average_and_max(vector<Real8> result_data,
                                     Real8& ave_data, Real8& max_data)
{
  calc_average(result_data, ave_data);

  sort(result_data.begin(), result_data.end());

  int data_no = static_cast<int>(result_data.size());
  max_data    = result_data[data_no - 1];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real8> > Bootstrap::get_random_sample(vector<vector<Real8> >& sample_ori)
{
  int i_max = static_cast<int>(sample_ori.size());

  vector<vector<Real8> > sample_new;
  sample_new.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int rand_pos  = get_random_pos(i_max);
    sample_new[i] = sample_ori[rand_pos]; 
  }

  return sample_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int Bootstrap::get_random_pos(int rand_no)
{
  Real8 rand_pos_real = static_cast<Real8>(rand_no) * rand_obj.uniform_distribution();

  int   rand_pos_int  = static_cast<int>(rand_pos_real);
  if( rand_pos_int == rand_no )
  {
    rand_pos_int--;
  }

  return rand_pos_int;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real8> > Bootstrap::get_jack_knife_sample(vector<vector<Real8> >& sample_ori, int pos)
{
  int i_max = static_cast<int>(sample_ori.size());

  vector<vector<Real8> > sample_new;
  sample_new.resize(i_max-1);

  int ele_no = 0;
  for(int i=0; i<i_max; i++)
  {
    if( i != pos )
    {
      sample_new[ele_no] = sample_ori[i];
      ele_no++;
    }
  }

  return sample_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_bootstrap(int sample_no, vector<vector<Real8> >& sample_ori, 
                               vector<Real8>& ave_data, vector<Real8>& err_data)
{
  if( sample_no > static_cast<int>(sample_ori.size()) )
  {
     sample_no = static_cast<int>(sample_ori.size());
  }

  vector<vector<Real8> > sample_ave;
  sample_ave.resize(sample_no);

  for(int i=0; i<sample_no; i++)
  {
    vector<vector<Real8> > sample_new = get_random_sample(sample_ori);
    calc_average(sample_new, sample_ave[i]);
  }

  calc_average_and_error(sample_ave, ave_data, err_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_bootstrap_with_ave_and_max
                  (int sample_no, vector<vector<Real8> >& sample_ori, 
                   vector<Real8>& ave_data, vector<Real8>& err_data, Real8& err_ave, Real8& err_max)
{
  calc_bootstrap(sample_no, sample_ori, ave_data, err_data);

  calc_average_and_max(err_data, err_ave, err_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_jack_knife(vector<vector<Real8> >& sample_ori, 
                                vector<Real8>& ave_data, vector<Real8>& err_data)
{
  int i_max = static_cast<int>(sample_ori.size());
  vector<vector<Real8> > sample_ave;
  sample_ave.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    vector<vector<Real8> > sample_new = get_jack_knife_sample(sample_ori, i);
    calc_average(sample_new, sample_ave[i]);
  }

  calc_average(sample_ave, ave_data);
  calc_average_sq(sample_ave, err_data);

  for(int i=0; i<static_cast<int>(err_data.size()); i++)
  {
    //err_data[i]  = sqrt(fabs(err_data[i] - ave_data[i]*ave_data[i]) * static_cast<Real8>(i_max - 1));
    //err_data[i] *= static_cast<Real8>(i_max) / static_cast<Real8>(i_max - 1);
    err_data[i]  = sqrt(fabs(err_data[i] - ave_data[i]*ave_data[i]) * static_cast<Real8>(i_max));
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::calc_jack_knife_with_ave_and_max
                  (vector<vector<Real8> >& sample_ori, 
                   vector<Real8>& ave_data, vector<Real8>& err_data, Real8& err_ave, Real8& err_max)
{
  calc_jack_knife(sample_ori, ave_data, err_data);

  calc_average_and_max(err_data, err_ave, err_max);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::set_seed(Integer seed_val)
{
  rand_obj.set_seed(seed_val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Bootstrap::set_seed_time()
{
  rand_obj.set_seed_time();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 Bootstrap::get_seed()
{
  return rand_obj.get_seed();
}

