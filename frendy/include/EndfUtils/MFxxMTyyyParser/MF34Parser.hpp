#ifndef MF34_PARSER_H
#define MF34_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF34Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =  34;
      Integer              mt_no;

      vector<string> text;

      Real                              ZA,  AWR;           //Line No.01
      Integer                           LTT, NMT1;
      vector<Integer>                   MAT1, MT1, NL, NL1; //Line No.02

      vector<Integer>                   NSS;

      vector<vector<vector<Integer> > > L, L1, LCT, NI;
      vector<vector<vector<vector<Integer> > > > LS, LB, NT, NE;

      vector<vector<vector<vector<vector<Real> > > > >          E_K, E_T;
      vector<vector<vector<vector<vector<vector<Real> > > > > > F_K, F_T;

      void store_data();
      void store_NSS(MultiParser& mp_obj, int& line_no, int& i, int& j_max, vector<int>& k_max);
      void store_lb00(vector<Real>& e_vec, int& i, int& j, int& k, int& l);
      void store_lb05(vector<Real>& e_vec, int& i, int& j, int& k, int& l);
      void store_lb06(vector<Real>& e_vec, int& i, int& j, int& k, int& l);

      void resize_matrix_first( int i_max);
      void resize_matrix_second(int i, int j_max, vector<int> k_max);
      void resize_matrix_third( int i, int j, int k, int l_max);

    public:
      //constructor
      MF34Parser(void);

      //destructor
      virtual ~MF34Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();

      //Getter ad line No.01-02
      Real                              get_ZA();
      Real                              get_AWR();
      Integer                           get_LTT();
      Integer                           get_NMT1();
      vector<Integer>                   get_MAT1();
      vector<Integer>                   get_MT1();
      vector<Integer>                   get_NL();
      vector<Integer>                   get_NL1();

      vector<Integer>                   get_NSS();

      vector<vector<vector<Integer> > > get_L();
      vector<vector<vector<Integer> > > get_L1();
      vector<vector<vector<Integer> > > get_LCT();
      vector<vector<vector<Integer> > > get_NI();
      vector<vector<vector<vector<Integer> > > > get_LS();
      vector<vector<vector<vector<Integer> > > > get_LB();
      vector<vector<vector<vector<Integer> > > > get_NT();
      vector<vector<vector<vector<Integer> > > > get_NE();

      vector<vector<vector<vector<vector<Real> > > > >          get_E_K();
      vector<vector<vector<vector<vector<Real> > > > >          get_E_T();
      vector<vector<vector<vector<vector<vector<Real> > > > > > get_F_K();
      vector<vector<vector<vector<vector<vector<Real> > > > > > get_F_T();

      vector<vector<vector<vector<vector<Real> > > > >          get_E_K_NER();
      vector<vector<vector<vector<vector<Real> > > > >          get_E_K_NEC();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LTT(Integer& int_data);
      void set_NMT1(Integer& int_data);
      void set_MAT1(vector<Integer>& int_vec);
      void set_MT1(vector<Integer>& int_vec);
      void set_NL(vector<Integer>& int_vec);
      void set_NL1(vector<Integer>& int_vec);
      void set_NSS(vector<Integer>& int_vec);
      void set_L(vector<vector<vector<Integer> > >& int_vec);
      void set_L1(vector<vector<vector<Integer> > >& int_vec);
      void set_LCT(vector<vector<vector<Integer> > >& int_vec);
      void set_NI(vector<vector<vector<Integer> > >& int_vec);
      void set_LS(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_LB(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_NT(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_NE(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_E_K(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_E_T(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_F_K(vector<vector<vector<vector<vector<vector<Real> > > > > >& real_vec);
      void set_F_T(vector<vector<vector<vector<vector<vector<Real> > > > > >& real_vec);
      void set_E_K_NER(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_E_K_NEC(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
  };
}

#endif // MF34_PARSER_H

