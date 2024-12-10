#ifndef MF07MT002_PARSER_H
#define MF07MT002_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF07MT002Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no = 7;
      static const Integer mt_no = 2;

      vector<string> text;

      //Common data
      Real                  ZA,  AWR;      //Line No.01
      Integer               LTHR;

      //LTHR=1
      Real                  T0;
      Integer               LT;
      vector<Integer>       NBT_S, INT_S;
      vector<Real>          E_INT_S, S_TAB;
      vector<Real>          T;
      vector<Integer>       LI;
      vector<vector<Real> > S;

      //LTHR=2
      Real                  SB;
      vector<Integer>       NBT_W, INT_W;
      vector<Real>          T_INT_W, W_TAB;

      void store_data();
      void store_lthr01(MultiParser& mp_obj, int& line_no);
      void store_lthr02(MultiParser& mp_obj, int& line_no);

    public:
      //constructor
      MF07MT002Parser(void);

      //destructor
      virtual ~MF07MT002Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string> get_text();

      Integer        get_mat_no();

      //Common data
      Real                  get_ZA();
      Real                  get_AWR();
      Integer               get_LTHR();

      //LTHR=1
      Real                  get_T0_LTHR01();
      Integer               get_LT_LTHR01();
      vector<Integer>       get_NBT_S_LTHR01();
      vector<Integer>       get_INT_S_LTHR01();
      vector<Real>          get_E_INT_S_LTHR01();
      vector<Real>          get_S_TAB_LTHR01();
      vector<Real>          get_T_LTHR01();
      vector<Integer>       get_LI_LTHR01();
      vector<vector<Real> > get_S_LTHR01();

      //LTHR=2
      Real                  get_SB_LTHR02();
      vector<Integer>       get_NBT_W_LTHR02();
      vector<Integer>       get_INT_W_LTHR02();
      vector<Real>          get_T_INT_W_LTHR02();
      vector<Real>          get_W_TAB_LTHR02();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LTHR(Integer& int_data);
      void set_T0_LTHR01(Real& real_data);
      void set_LT_LTHR01(Integer& int_data);
      void set_NBT_S_LTHR01(vector<Integer>& int_vec);
      void set_INT_S_LTHR01(vector<Integer>& int_vec);
      void set_E_INT_S_LTHR01(vector<Real>& real_vec);
      void set_S_TAB_LTHR01(vector<Real>& real_vec);
      void set_T_LTHR01(vector<Real>& real_vec);
      void set_LI_LTHR01(vector<Integer>& int_vec);
      void set_S_LTHR01(vector<vector<Real> >& real_vec);
      void set_SB_LTHR02(Real& real_data);
      void set_NBT_W_LTHR02(vector<Integer>& int_vec);
      void set_INT_W_LTHR02(vector<Integer>& int_vec);
      void set_T_INT_W_LTHR02(vector<Real>& real_vec);
      void set_W_TAB_LTHR02(vector<Real>& real_vec);
  };
}

#endif // MF07MT002_PARSER_H

