#ifndef MF04_PARSER_H
#define MF04_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF04Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =   4;
      Integer              mt_no;

      static const Integer nl_max =  64;
      static const Integer nr_max = 201;
      static const Integer np_max = 201;

      vector<string> text;

      Real    ZA, AWR;                    //Line No.01
      Integer LVT, LTT;
      Integer LI, LCT, NK, NM;            //Line No.02
      vector<Real> U;

      //LTT = 1
      Integer                       NE_LTT01;
      vector<Integer>               NBT_E_LTT01, INT_E_LTT01;
      vector<vector<Real> >         A_LTT01;
      vector<Real>                  T_LTT01,   E_LTT01;
      vector<Integer>               LT_LTT01,  NL_LTT01;

      //LTT = 2
      Integer                       NE_LTT02;
      vector<Integer>               NBT_E_LTT02,     INT_E_LTT02;
      vector<vector<Integer> >      NBT_F_LTT02,     INT_F_LTT02;
      vector<vector<Real> >         M_INT_F_LTT02,   F_TAB_LTT02;
      vector<Real>                  T_LTT02,         E_LTT02;
      vector<Integer>               LT_LTT02;
      vector<Integer>               NR_LTT02,        NP_LTT02;

      void store_data();
      void store_ltt01(MultiParser& mp_obj, int& line_no);
      void store_ltt02(MultiParser& mp_obj, int& line_no);

      void resize_matrix_ltt01(int i_max);
      void resize_matrix_ltt02(int i_max);

    public:
      //constructor
      MF04Parser(void);

      //destructor
      virtual ~MF04Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();

      //Getter at line No.01-02
      Real            get_ZA();
      Real            get_AWR();
      Integer         get_LVT();
      Integer         get_LTT();
      Integer         get_LI();
      Integer         get_LCT();
      Integer         get_NK();
      Integer         get_NM();
      vector<Real>    get_U();

      //LTT = 1
      Integer                       get_NE_LTT01();
      vector<Integer>               get_NBT_E_LTT01();
      vector<Integer>               get_INT_E_LTT01();
      vector<vector<Real> >         get_A_LTT01();
      vector<Real>                  get_T_LTT01();
      vector<Real>                  get_E_LTT01();
      vector<Integer>               get_LT_LTT01();
      vector<Integer>               get_NL_LTT01();

      //LTT = 2
      Integer                       get_NE_LTT02();
      vector<Integer>               get_NBT_E_LTT02();
      vector<Integer>               get_INT_E_LTT02();
      vector<vector<Integer> >      get_NBT_F_LTT02();
      vector<vector<Integer> >      get_INT_F_LTT02();
      vector<vector<Real> >         get_M_INT_F_LTT02();
      vector<vector<Real> >         get_F_TAB_LTT02();
      vector<Real>                  get_T_LTT02();
      vector<Real>                  get_E_LTT02();
      vector<Integer>               get_LT_LTT02();
      vector<Integer>               get_NR_LTT02();
      vector<Integer>               get_NP_LTT02();

      //LTT = 3, Legendre coefficients
      Integer                       get_NE_LTT03_L();
      vector<Integer>               get_NBT_E_LTT03_L();
      vector<Integer>               get_INT_E_LTT03_L();
      vector<vector<Real> >         get_A_LTT03_L();
      vector<Real>                  get_T_LTT03_L();
      vector<Real>                  get_E_LTT03_L();
      vector<Integer>               get_LT_LTT03_L();
      vector<Integer>               get_NL_LTT03_L();

      //LTT = 3, Tabulated data
      Integer                       get_NE_LTT03_T();
      vector<Integer>               get_NBT_E_LTT03_T();
      vector<Integer>               get_INT_E_LTT03_T();
      vector<vector<Integer> >      get_NBT_F_LTT03_T();
      vector<vector<Integer> >      get_INT_F_LTT03_T();
      vector<vector<Real> >         get_M_INT_F_LTT03_T();
      vector<vector<Real> >         get_F_TAB_LTT03_T();
      vector<Real>                  get_T_LTT03_T();
      vector<Real>                  get_E_LTT03_T();
      vector<Integer>               get_LT_LTT03_T();
      vector<Integer>               get_NR_LTT03_T();
      vector<Integer>               get_NP_LTT03_T();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LVT(Integer& int_data);
      void set_LTT(Integer& int_data);
      void set_LI(Integer& int_data);
      void set_LCT(Integer& int_data);
      void set_NK(Integer& int_data);
      void set_NM(Integer& int_data);
      void set_U(vector<Real>& real_vec);
      void set_NE_LTT01(Integer& int_data);
      void set_NBT_E_LTT01(vector<Integer>& int_vec);
      void set_INT_E_LTT01(vector<Integer>& int_vec);
      void set_A_LTT01(vector<vector<Real> >& real_vec);
      void set_T_LTT01(vector<Real>& real_vec);
      void set_E_LTT01(vector<Real>& real_vec);
      void set_LT_LTT01(vector<Integer>& int_vec);
      void set_NL_LTT01(vector<Integer>& int_vec);
      void set_NE_LTT02(Integer& int_data);
      void set_NBT_E_LTT02(vector<Integer>& int_vec);
      void set_INT_E_LTT02(vector<Integer>& int_vec);
      void set_NBT_F_LTT02(vector<vector<Integer> >& int_vec);
      void set_INT_F_LTT02(vector<vector<Integer> >& int_vec);
      void set_M_INT_F_LTT02(vector<vector<Real> >& real_vec);
      void set_F_TAB_LTT02(vector<vector<Real> >& real_vec);
      void set_T_LTT02(vector<Real>& real_vec);
      void set_E_LTT02(vector<Real>& real_vec);
      void set_LT_LTT02(vector<Integer>& int_vec);
      void set_NR_LTT02(vector<Integer>& int_vec);
      void set_NP_LTT02(vector<Integer>& int_vec);
      void set_NE_LTT03_L(Integer& int_data);
      void set_NBT_E_LTT03_L(vector<Integer>& int_vec);
      void set_INT_E_LTT03_L(vector<Integer>& int_vec);
      void set_A_LTT03_L(vector<vector<Real> >& real_vec);
      void set_T_LTT03_L(vector<Real>& real_vec);
      void set_E_LTT03_L(vector<Real>& real_vec);
      void set_LT_LTT03_L(vector<Integer>& int_vec);
      void set_NL_LTT03_L(vector<Integer>& int_vec);
      void set_NE_LTT03_T(Integer& int_data);
      void set_NBT_E_LTT03_T(vector<Integer>& int_vec);
      void set_INT_E_LTT03_T(vector<Integer>& int_vec);
      void set_NBT_F_LTT03_T(vector<vector<Integer> >& int_vec);
      void set_INT_F_LTT03_T(vector<vector<Integer> >& int_vec);
      void set_M_INT_F_LTT03_T(vector<vector<Real> >& real_vec);
      void set_F_TAB_LTT03_T(vector<vector<Real> >& real_vec);
      void set_T_LTT03_T(vector<Real>& real_vec);
      void set_E_LTT03_T(vector<Real>& real_vec);
      void set_LT_LTT03_T(vector<Integer>& int_vec);
      void set_NR_LTT03_T(vector<Integer>& int_vec);
      void set_NP_LTT03_T(vector<Integer>& int_vec);
  };
}

#endif // MF04_PARSER_H

