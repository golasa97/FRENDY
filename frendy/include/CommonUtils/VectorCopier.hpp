#ifndef VECTOR_COPIER_H
#define VECTOR_COPIER_H

#include "Config/FrendyTypes.hpp"
#include "VectorClearer.hpp"

namespace frendy
{
  class VectorCopier
  {
    private:
      frendy::VectorClearer clr_obj;
    
    public:
      //constructor
      VectorCopier(void);

      //destructor
      virtual ~VectorCopier(void);

      void copy_vec_array1_int(vector<int>& copy_vec, vector<Integer> ori_vec);
      void copy_vec_array2_int(vector<vector<int> >& copy_vec, vector<vector<Integer> > ori_vec);
      void copy_vec_array3_int(vector<vector<vector<int> > >& copy_vec, vector<vector<vector<Integer> > > ori_vec);
      void copy_vec_array1_real(vector<Real>& copy_vec, vector<Real8> ori_vec);
      void copy_vec_array2_real(vector<vector<Real> >& copy_vec, vector<vector<Real8> > ori_vec);
      void copy_vec_array3_real(vector<vector<vector<Real> > >& copy_vec, vector<vector<vector<Real8> > > ori_vec);
      void copy_vec_array1_real8(vector<Real8>& copy_vec, vector<Real> ori_vec);
      void copy_vec_array2_real8(vector<vector<Real8> >& copy_vec, vector<vector<Real> > ori_vec);
      void copy_vec_array3_real8(vector<vector<vector<Real8> > >& copy_vec, vector<vector<vector<Real> > > ori_vec);
  };
}

#endif // VECTOR_COPIER_H
