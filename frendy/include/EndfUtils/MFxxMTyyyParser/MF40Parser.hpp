#ifndef MF40_PARSER_H
#define MF40_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF40Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =  40;
      Integer              mt_no;

      vector<string> text;

      Real                              ZA,  AWR; //Line No.01
      Integer                           LIS, NS;

      vector<Real>                      QM, QI;   //Line No.02
      vector<Integer>                   IZAP, LFS, NL;

      vector<vector<Real> >             XMF1, XLFS1;
      vector<vector<Integer> >          MAT1, MT1, NC, NI;

      //NC-type Sub-Sub-Subsections
      vector<vector<vector<Integer> > > LTY;
      vector<vector<vector<Real> > >    E1, E2;
      vector<vector<vector<vector<Real> > > > CI, XMTI;

      vector<vector<vector<Integer> > > MATS, MTS;
      vector<vector<vector<Real> > >    XMFS, XLFSS;
      vector<vector<vector<vector<Real> > > > EI, WEI;

      //NI-type Sub-Sub-Subsections
      vector<vector<vector<Integer> > > LB, LT;

      vector<vector<vector<vector<Real> > > >          E_K, E_T;
      vector<vector<vector<vector<vector<Real> > > > > F_K, F_T;

      void store_data();
      void store_NC(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k);
      void store_NI(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k);

      void store_NI_lb00(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec,
                         int& i, int& j, int& k);
      void store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec,
                         int& i, int& j, int& k);
      void store_NI_lb06(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec,
                         int& i, int& j, int& k);

      void resize_matrix_first(int i_max);
      void resize_matrix_second(int& i, int j_max);
      void resize_matrix_NC(int& i, int& j, int k_max);
      void resize_matrix_NI(int& i, int& j, int k_max);

    public:
      //constructor
      MF40Parser(void);

      //destructor
      virtual ~MF40Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();

      //Getter ad line No.01-02
      Real                              get_ZA();
      Real                              get_AWR();
      Integer                           get_LIS();
      Integer                           get_NS();

      vector<Real>                      get_QM();
      vector<Real>                      get_QI();
      vector<Integer>                   get_IZAP();
      vector<Integer>                   get_LFS();
      vector<Integer>                   get_NL();

      vector<vector<Real> >             get_XMF1();
      vector<vector<Real> >             get_XLFS1();
      vector<vector<Integer> >          get_MAT1();
      vector<vector<Integer> >          get_MT1();
      vector<vector<Integer> >          get_NC();
      vector<vector<Integer> >          get_NI();

      //NC-type Sub-Sub-Subsections
      vector<vector<vector<Integer> > > get_LTY();
      vector<vector<vector<Real> > >    get_E1();
      vector<vector<vector<Real> > >    get_E2();
      vector<vector<vector<vector<Real> > > > get_CI();
      vector<vector<vector<vector<Real> > > > get_XMTI();

      vector<vector<vector<Integer> > > get_MATS();
      vector<vector<vector<Integer> > > get_MTS();
      vector<vector<vector<Real> > >    get_XMFS();
      vector<vector<vector<Real> > >    get_XLFSS();
      vector<vector<vector<vector<Real> > > > get_EI();
      vector<vector<vector<vector<Real> > > > get_WEI();

      //NI-type Sub-Sub-Subsections
      vector<vector<vector<Integer> > > get_LB();
      vector<vector<vector<Integer> > > get_LT();
      vector<vector<vector<Integer> > > get_LS();

      vector<vector<vector<vector<Real> > > >          get_E_K();
      vector<vector<vector<vector<Real> > > >          get_E_T();
      vector<vector<vector<vector<vector<Real> > > > > get_F_K();
      vector<vector<vector<vector<vector<Real> > > > > get_F_T();
      vector<vector<vector<vector<Real> > > >          get_E_K_NER();
      vector<vector<vector<vector<Real> > > >          get_E_K_NEC();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LIS(Integer& int_data);
      void set_NS(Integer& int_data);
      void set_QM(vector<Real>& real_vec);
      void set_QI(vector<Real>& real_vec);
      void set_IZAP(vector<Integer>& int_vec);
      void set_LFS(vector<Integer>& int_vec);
      void set_NL(vector<Integer>& int_vec);
      void set_XMF1(vector<vector<Real> >& real_vec);
      void set_XLFS1(vector<vector<Real> >& real_vec);
      void set_MAT1(vector<vector<Integer> >& int_vec);
      void set_MT1(vector<vector<Integer> >& int_vec);
      void set_NC(vector<vector<Integer> >& int_vec);
      void set_NI(vector<vector<Integer> >& int_vec);
      void set_LTY(vector<vector<vector<Integer> > >& int_vec);
      void set_E1(vector<vector<vector<Real> > >& real_vec);
      void set_E2(vector<vector<vector<Real> > >& real_vec);
      void set_CI(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_XMTI(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_MATS(vector<vector<vector<Integer> > >& int_vec);
      void set_MTS(vector<vector<vector<Integer> > >& int_vec);
      void set_XMFS(vector<vector<vector<Real> > >& real_vec);
      void set_XLFSS(vector<vector<vector<Real> > >& real_vec);
      void set_EI(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_WEI(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_LB(vector<vector<vector<Integer> > >& int_vec);
      void set_LT(vector<vector<vector<Integer> > >& int_vec);
      void set_LS(vector<vector<vector<Integer> > >& int_vec);
      void set_E_K(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_E_T(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_F_K(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_F_T(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_E_K_NER(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_E_K_NEC(vector<vector<vector<vector<Real> > > >& real_vec);
  };
}

#endif // MF40_PARSER_H

