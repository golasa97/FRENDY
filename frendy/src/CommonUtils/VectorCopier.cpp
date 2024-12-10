#include "CommonUtils/VectorCopier.hpp"

using namespace frendy;

//constructor
VectorCopier::VectorCopier(void)
{
}

//destructor
VectorCopier::~VectorCopier(void)
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void VectorCopier::copy_vec_array1_int(vector<int>& copy_vec, vector<Integer> ori_vec)
{
  int i_max = static_cast<int>(ori_vec.size());
  copy_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    copy_vec[i] = static_cast<int>(ori_vec[i]);
  }
  ori_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void VectorCopier::copy_vec_array2_int(vector<vector<int> >& copy_vec, vector<vector<Integer> > ori_vec)
{
  int i_max = static_cast<int>(ori_vec.size());
  copy_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(ori_vec[i].size());
    copy_vec[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      copy_vec[i][j] = static_cast<int>(ori_vec[i][j]);
    }
  }

  clr_obj.clear_vec_array2_int(ori_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void VectorCopier::copy_vec_array3_int(vector<vector<vector<int> > >& copy_vec, vector<vector<vector<Integer> > > ori_vec)
{
  int i_max = static_cast<int>(ori_vec.size());
  copy_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(ori_vec[i].size());
    copy_vec[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(ori_vec[i][j].size());
      copy_vec[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        copy_vec[i][j][k] = static_cast<int>(ori_vec[i][j][k]);
      }
    }
  }
  clr_obj.clear_vec_array3_int(ori_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void VectorCopier::copy_vec_array1_real8(vector<Real8>& copy_vec, vector<Real> ori_vec)
{
  int i_max = static_cast<int>(ori_vec.size());
  copy_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    copy_vec[i] = static_cast<Real8>(ori_vec[i]);
  }
  ori_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void VectorCopier::copy_vec_array2_real8(vector<vector<Real8> >& copy_vec, vector<vector<Real> > ori_vec)
{
  int i_max = static_cast<int>(ori_vec.size());
  copy_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(ori_vec[i].size());
    copy_vec[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      copy_vec[i][j] = static_cast<Real8>(ori_vec[i][j]);
    }
  }
  clr_obj.clear_vec_array2_real(ori_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void VectorCopier::copy_vec_array3_real8(vector<vector<vector<Real8> > >& copy_vec, vector<vector<vector<Real> > > ori_vec)
{
  int i_max = static_cast<int>(ori_vec.size());
  copy_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(ori_vec[i].size());
    copy_vec[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(ori_vec[i][j].size());
      copy_vec[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        copy_vec[i][j][k] = static_cast<Real8>(ori_vec[i][j][k]);
      }
    }
  }
  clr_obj.clear_vec_array3_real(ori_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void VectorCopier::copy_vec_array1_real(vector<Real>& copy_vec, vector<Real8> ori_vec)
{
  int i_max = static_cast<int>(ori_vec.size());
  copy_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    copy_vec[i] = static_cast<Real>(ori_vec[i]);
  }
  ori_vec.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void VectorCopier::copy_vec_array2_real(vector<vector<Real> >& copy_vec, vector<vector<Real8> > ori_vec)
{
  int i_max = static_cast<int>(ori_vec.size());
  copy_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(ori_vec[i].size());
    copy_vec[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      copy_vec[i][j] = static_cast<Real>(ori_vec[i][j]);
    }
  }
  clr_obj.clear_vec_array2_real8(ori_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void VectorCopier::copy_vec_array3_real(vector<vector<vector<Real> > >& copy_vec, vector<vector<vector<Real8> > > ori_vec)
{
  int i_max = static_cast<int>(ori_vec.size());
  copy_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(ori_vec[i].size());
    copy_vec[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(ori_vec[i][j].size());
      copy_vec[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        copy_vec[i][j][k] = static_cast<Real>(ori_vec[i][j][k]);
      }
    }
  }
  clr_obj.clear_vec_array3_real8(ori_vec);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

