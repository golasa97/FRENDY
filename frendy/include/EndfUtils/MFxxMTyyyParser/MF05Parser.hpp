#ifndef MF05_PARSER_H
#define MF05_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF05Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =   5;
      Integer              mt_no;

      vector<string> text;

      Real                              ZA, AWR;       //Line No.01
      Integer                           NK;
      vector<Real>                      U;             //Line No.02
      vector<Integer>                   LF;
      vector<vector<Integer> >          NBT_P,   INT_P;
      vector<vector<Real> >             E_INT_P, P_TAB;

      //LF = 1
      vector<Integer>                   NE_LF01;
      vector<vector<Integer> >          NBT_E_LF01, INT_E_LF01;
      vector<vector<Real> >             E_LF01;
      vector<vector<vector<Integer> > > NBT_G_LF01,   INT_G_LF01;
      vector<vector<vector<Real> > >    E_INT_G_LF01, G_TAB_LF01;

      //LF = 5
      vector<vector<Integer> >          NBT_S_LF05,   INT_S_LF05;
      vector<vector<Real> >             E_INT_S_LF05, S_TAB_LF05;
      vector<vector<Integer> >          NBT_G_LF05,   INT_G_LF05;
      vector<vector<Real> >             E_INT_G_LF05, G_TAB_LF05;

      //LF =12
      vector<Real>                      EFL, EFH;

      void store_data();
      void store_lf01(MultiParser& mp_obj, int& line_no, int& i);
      void store_lf05(MultiParser& mp_obj, int& line_no, int& i);
      void store_lf07(MultiParser& mp_obj, int& line_no, int& i);

      void resize_matrix();

    public:
      //constructor
      MF05Parser(void);

      //destructor
      virtual ~MF05Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();

      //Getter at line No.01-02
      Real                              get_ZA();
      Real                              get_AWR();
      Integer                           get_NK();
      vector<Real>                      get_U();
      vector<Integer>                   get_LF();
      vector<vector<Integer> >          get_NBT_P();
      vector<vector<Integer> >          get_INT_P();
      vector<vector<Real> >             get_E_INT_P();
      vector<vector<Real> >             get_P_TAB();

      //LF = 1
      vector<Integer>                   get_NE_LF01();
      vector<vector<Integer> >          get_NBT_E_LF01();
      vector<vector<Integer> >          get_INT_E_LF01();
      vector<vector<Real> >             get_E_LF01();
      vector<vector<vector<Integer> > > get_NBT_G_LF01();
      vector<vector<vector<Integer> > > get_INT_G_LF01();
      vector<vector<vector<Real> > >    get_E_INT_G_LF01();
      vector<vector<vector<Real> > >    get_G_TAB_LF01();

      //LF = 5
      vector<vector<Integer> >          get_NBT_S_LF05();
      vector<vector<Integer> >          get_INT_S_LF05();
      vector<vector<Real> >             get_E_INT_S_LF05();
      vector<vector<Real> >             get_S_TAB_LF05();
      vector<vector<Integer> >          get_NBT_G_LF05();
      vector<vector<Integer> >          get_INT_G_LF05();
      vector<vector<Real> >             get_E_INT_G_LF05();
      vector<vector<Real> >             get_G_TAB_LF05();

      //LF = 7
      vector<vector<Integer> >          get_NBT_S_LF07();
      vector<vector<Integer> >          get_INT_S_LF07();
      vector<vector<Real> >             get_E_INT_S_LF07();
      vector<vector<Real> >             get_S_TAB_LF07();

      //LF = 9
      vector<vector<Integer> >          get_NBT_S_LF09();
      vector<vector<Integer> >          get_INT_S_LF09();
      vector<vector<Real> >             get_E_INT_S_LF09();
      vector<vector<Real> >             get_S_TAB_LF09();

      //LF = 11
      vector<vector<Integer> >          get_NBT_A_LF11();
      vector<vector<Integer> >          get_INT_A_LF11();
      vector<vector<Real> >             get_E_INT_A_LF11();
      vector<vector<Real> >             get_A_TAB_LF11();
      vector<vector<Integer> >          get_NBT_B_LF11();
      vector<vector<Integer> >          get_INT_B_LF11();
      vector<vector<Real> >             get_E_INT_B_LF11();
      vector<vector<Real> >             get_B_TAB_LF11();

      //LF = 12
      vector<Real>                      get_EFL_LF12();
      vector<Real>                      get_EFH_LF12();
      vector<vector<Integer> >          get_NBT_TM_LF12();
      vector<vector<Integer> >          get_INT_TM_LF12();
      vector<vector<Real> >             get_E_INT_TM_LF12();
      vector<vector<Real> >             get_TM_TAB_LF12();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_NK(Integer& int_data);
      void set_U(vector<Real>& real_vec);
      void set_LF(vector<Integer>& int_vec);
      void set_NBT_P(vector<vector<Integer> >& int_vec);
      void set_INT_P(vector<vector<Integer> >& int_vec);
      void set_E_INT_P(vector<vector<Real> >& real_vec);
      void set_P_TAB(vector<vector<Real> >& real_vec);
      void set_NE_LF01(vector<Integer>& int_vec);
      void set_NBT_E_LF01(vector<vector<Integer> >& int_vec);
      void set_INT_E_LF01(vector<vector<Integer> >& int_vec);
      void set_E_LF01(vector<vector<Real> >& real_vec);
      void set_NBT_G_LF01(vector<vector<vector<Integer> > >& int_vec);
      void set_INT_G_LF01(vector<vector<vector<Integer> > >& int_vec);
      void set_E_INT_G_LF01(vector<vector<vector<Real> > >& real_vec);
      void set_G_TAB_LF01(vector<vector<vector<Real> > >& real_vec);
      void set_NBT_S_LF05(vector<vector<Integer> >& int_vec);
      void set_INT_S_LF05(vector<vector<Integer> >& int_vec);
      void set_E_INT_S_LF05(vector<vector<Real> >& real_vec);
      void set_S_TAB_LF05(vector<vector<Real> >& real_vec);
      void set_NBT_G_LF05(vector<vector<Integer> >& int_vec);
      void set_INT_G_LF05(vector<vector<Integer> >& int_vec);
      void set_E_INT_G_LF05(vector<vector<Real> >& real_vec);
      void set_G_TAB_LF05(vector<vector<Real> >& real_vec);
      void set_NBT_S_LF07(vector<vector<Integer> >& int_vec);
      void set_INT_S_LF07(vector<vector<Integer> >& int_vec);
      void set_E_INT_S_LF07(vector<vector<Real> >& real_vec);
      void set_S_TAB_LF07(vector<vector<Real> >& real_vec);
      void set_NBT_S_LF09(vector<vector<Integer> >& int_vec);
      void set_INT_S_LF09(vector<vector<Integer> >& int_vec);
      void set_E_INT_S_LF09(vector<vector<Real> >& real_vec);
      void set_S_TAB_LF09(vector<vector<Real> >& real_vec);
      void set_NBT_A_LF11(vector<vector<Integer> >& int_vec);
      void set_INT_A_LF11(vector<vector<Integer> >& int_vec);
      void set_E_INT_A_LF11(vector<vector<Real> >& real_vec);
      void set_A_TAB_LF11(vector<vector<Real> >& real_vec);
      void set_NBT_B_LF11(vector<vector<Integer> >& int_vec);
      void set_INT_B_LF11(vector<vector<Integer> >& int_vec);
      void set_E_INT_B_LF11(vector<vector<Real> >& real_vec);
      void set_B_TAB_LF11(vector<vector<Real> >& real_vec);
      void set_EFL_LF12(vector<Real>& real_vec);
      void set_EFH_LF12(vector<Real>& real_vec);
      void set_NBT_TM_LF12(vector<vector<Integer> >& int_vec);
      void set_INT_TM_LF12(vector<vector<Integer> >& int_vec);
      void set_E_INT_TM_LF12(vector<vector<Real> >& real_vec);
      void set_TM_TAB_LF12(vector<vector<Real> >& real_vec);
  };
}

#endif // MF05_PARSER_H

