#ifndef VECTOR_SIZE_CHECKER_H
#define VECTOR_SIZE_CHECKER_H

#include "ErrorManager.hpp"

namespace frendy
{
  class VectorSizeChecker
  {
    private:
      frendy::ErrorManager    err_obj;

      void output_error_message( string& class_name, string& func_name, int i, int i_max,
                                 int size_no_ori, int size_no_dif );

    public:
      //constructor
      VectorSizeChecker(void);

      //destructor
      virtual ~VectorSizeChecker(void);

      Integer vec_size_check_array2_int(string& class_name, string& func_name,
                                        vector<vector<Integer> >& vec);
      Integer vec_size_check_array3_int(string& class_name, string& func_name,
                                        vector<vector<vector<Integer> > >& vec);
      Integer vec_size_check_array4_int(string& class_name, string& func_name,
                                        vector<vector<vector<vector<Integer> > > >& vec);
      Integer vec_size_check_array5_int(string& class_name, string& func_name,
                                        vector<vector<vector<vector<vector<Integer> > > > >& vec);
      Integer vec_size_check_array6_int(string& class_name, string& func_name,
                                        vector<vector<vector<vector<vector<vector<Integer> > > > > >& vec);

      Integer vec_size_check_array2_real(string& class_name, string& func_name,
                                         vector<vector<Real> >& vec);
      Integer vec_size_check_array3_real(string& class_name, string& func_name,
                                         vector<vector<vector<Real> > >& vec);
      Integer vec_size_check_array4_real(string& class_name, string& func_name,
                                         vector<vector<vector<vector<Real> > > >& vec);
      Integer vec_size_check_array5_real(string& class_name, string& func_name,
                                         vector<vector<vector<vector<vector<Real> > > > >& vec);
      Integer vec_size_check_array6_real(string& class_name, string& func_name,
                                         vector<vector<vector<vector<vector<vector<Real> > > > > >& vec);

      Integer vec_size_check_array2_real8(string& class_name, string& func_name,
                                          vector<vector<Real8> >& vec);
      Integer vec_size_check_array3_real8(string& class_name, string& func_name,
                                          vector<vector<vector<Real8> > >& vec);
      Integer vec_size_check_array4_real8(string& class_name, string& func_name,
                                          vector<vector<vector<vector<Real8> > > >& vec);
      Integer vec_size_check_array5_real8(string& class_name, string& func_name,
                                          vector<vector<vector<vector<vector<Real8> > > > >& vec);
      Integer vec_size_check_array6_real8(string& class_name, string& func_name,
                                          vector<vector<vector<vector<vector<vector<Real8> > > > > >& vec);

      Integer vec_size_check_array2_str(string& class_name, string& func_name,
                                        vector<vector<string> >& vec);
      Integer vec_size_check_array3_str(string& class_name, string& func_name,
                                        vector<vector<vector<string> > >& vec);
  };
}

#endif //VECTOR_SIZE_CHECKER_H
