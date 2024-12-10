#ifndef MF31_PARSER_H
#define MF31_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF31Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =  31;
      Integer              mt_no;

      vector<string> text;

      Real                              ZA,  AWR;      //Line No.01
      Integer                           MTL, NL;
      vector<Real>                      XMF, XLFS;     //Line No.02
      vector<Integer>                   MAT, MT, NC, NI;

      //NC-type Sub-Subsections
      vector<vector<Integer> >          LTY;
      vector<vector<Real> >             E1,   E2;

      vector<vector<vector<Real> > >    CI,   XMTI;  //LTY=0

      vector<vector<Integer> >          MATS, MTS;   //LTY=1, 2 and 3
      vector<vector<Real> >             XMFS, XLFSS;
      vector<vector<vector<Real> > >    EI,   WEI;

      //NI-type Sub-Subsections
      vector<vector<Integer> >          LB;

      vector<vector<Integer> >          LT;               //LB=0-4, 8 and 9
      vector<vector<vector<Real> > >    E_K, E_T;
      vector<vector<vector<vector<Real> > > > F_K, F_T;

      void store_data();
      void store_NC(MultiParser& mp_obj, int& line_no, int& i, int& j);
      void store_NI(MultiParser& mp_obj, int& line_no, int& i, int& j);

      void store_NI_lb00(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, int& i, int& j);
      void store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, int& i, int& j);
      void store_NI_lb06(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, int& i, int& j);

      void resize_matrix_NL();
      void resize_matrix_NC(int& i);
      void resize_matrix_NI(int& i);

    public:
      //constructor
      MF31Parser(void);

      //destructor
      virtual ~MF31Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();

      //Getter ad line No.01-02
      Real                              get_ZA();
      Real                              get_AWR();
      Integer                           get_MTL();
      Integer                           get_NL();
      vector<Real>                      get_XMF();
      vector<Real>                      get_XLFS();
      vector<Integer>                   get_MAT();
      vector<Integer>                   get_MT();
      vector<Integer>                   get_NC();
      vector<Integer>                   get_NI();

      //NC-type Sub-Subsections
      vector<vector<Integer> >          get_LTY();
      vector<vector<Real> >             get_E1();
      vector<vector<Real> >             get_E2();

      vector<vector<vector<Real> > >    get_CI();
      vector<vector<vector<Real> > >    get_XMTI();

      vector<vector<Integer> >          get_MATS();
      vector<vector<Integer> >          get_MTS();
      vector<vector<Real> >             get_XMFS();
      vector<vector<Real> >             get_XLFSS();
      vector<vector<vector<Real> > >    get_EI();
      vector<vector<vector<Real> > >    get_WEI();

      //NI-type Sub-Subsections
      vector<vector<Integer> >          get_LB();

      vector<vector<Integer> >          get_LT();
      vector<vector<vector<Real> > >    get_E_K();
      vector<vector<vector<Real> > >    get_E_T();
      vector<vector<vector<vector<Real> > > > get_F_K();
      vector<vector<vector<vector<Real> > > > get_F_T();

      vector<vector<Integer> >          get_LS();

      vector<vector<vector<Real> > >    get_E_K_NER();
      vector<vector<vector<Real> > >    get_E_K_NEC();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_MTL(Integer& int_data);
      void set_NL(Integer& int_data);
      void set_XMF(vector<Real>& real_vec);
      void set_XLFS(vector<Real>& real_vec);
      void set_MAT(vector<Integer>& int_vec);
      void set_MT(vector<Integer>& int_vec);
      void set_NC(vector<Integer>& int_vec);
      void set_NI(vector<Integer>& int_vec);
      void set_LTY(vector<vector<Integer> >& int_vec);
      void set_E1(vector<vector<Real> >& real_vec);
      void set_E2(vector<vector<Real> >& real_vec);
      void set_CI(vector<vector<vector<Real> > >& real_vec);
      void set_XMTI(vector<vector<vector<Real> > >& real_vec);
      void set_MATS(vector<vector<Integer> >& int_vec);
      void set_MTS(vector<vector<Integer> >& int_vec);
      void set_XMFS(vector<vector<Real> >& real_vec);
      void set_XLFSS(vector<vector<Real> >& real_vec);
      void set_EI(vector<vector<vector<Real> > >& real_vec);
      void set_WEI(vector<vector<vector<Real> > >& real_vec);
      void set_LB(vector<vector<Integer> >& int_vec);
      void set_LT(vector<vector<Integer> >& int_vec);
      void set_E_K(vector<vector<vector<Real> > >& real_vec);
      void set_E_T(vector<vector<vector<Real> > >& real_vec);
      void set_F_K(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_F_T(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_LS(vector<vector<Integer> >& int_vec);
      void set_E_K_NER(vector<vector<vector<Real> > >& real_vec);
      void set_E_K_NEC(vector<vector<vector<Real> > >& real_vec);
  };
}

#endif // MF31_PARSER_H

