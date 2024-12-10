#ifndef VECTOR_CLEARER_H
#define VECTOR_CLEARER_H

#include "Config/FrendyTypes.hpp"

namespace frendy
{
  class VectorClearer
  {
    private:
    
    public:
      //constructor
      VectorClearer(void);

      //destructor
      virtual ~VectorClearer(void);

      void clear_vec_array2_int(vector<vector<Integer> >& vec);
      void clear_vec_array3_int(vector<vector<vector<Integer> > >& vec);
      void clear_vec_array4_int(vector<vector<vector<vector<Integer> > > >& vec);
      void clear_vec_array5_int(vector<vector<vector<vector<vector<Integer> > > > >& vec);
      void clear_vec_array6_int(vector<vector<vector<vector<vector<vector<Integer> > > > > >& vec);

      void clear_vec_array2_real(vector<vector<Real> >& vec);
      void clear_vec_array3_real(vector<vector<vector<Real> > >& vec);
      void clear_vec_array4_real(vector<vector<vector<vector<Real> > > >& vec);
      void clear_vec_array5_real(vector<vector<vector<vector<vector<Real> > > > >& vec);
      void clear_vec_array6_real(vector<vector<vector<vector<vector<vector<Real> > > > > >& vec);

      void clear_vec_array2_int8(vector<vector<Integer8> >& vec);
      void clear_vec_array3_int8(vector<vector<vector<Integer8> > >& vec);
      void clear_vec_array4_int8(vector<vector<vector<vector<Integer8> > > >& vec);
      void clear_vec_array5_int8(vector<vector<vector<vector<vector<Integer8> > > > >& vec);
      void clear_vec_array6_int8(vector<vector<vector<vector<vector<vector<Integer8> > > > > >& vec);

      void clear_vec_array2_real8(vector<vector<Real8> >& vec);
      void clear_vec_array3_real8(vector<vector<vector<Real8> > >& vec);
      void clear_vec_array4_real8(vector<vector<vector<vector<Real8> > > >& vec);
      void clear_vec_array5_real8(vector<vector<vector<vector<vector<Real8> > > > >& vec);
      void clear_vec_array6_real8(vector<vector<vector<vector<vector<vector<Real8> > > > > >& vec);

      void clear_vec_array1_str(vector<string>& vec);
      void clear_vec_array2_str(vector<vector<string> >& vec);
      void clear_vec_array3_str(vector<vector<vector<string> > >& vec);
  };
}

#endif // VECTOR_CLEARER_H
