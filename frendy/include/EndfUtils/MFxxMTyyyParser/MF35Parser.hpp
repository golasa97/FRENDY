#ifndef MF35_PARSER_H
#define MF35_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF35Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =  35;
      Integer              mt_no;

      vector<string> text;

      Real                           ZA,  AWR;           //Line No.01
      Integer                        NK;

      vector<Real>                   E1, E2; //Line No.02
      vector<Integer>                LS, LB, NT, NE;

      vector<vector<Real> >          E_K, E_T;
      vector<vector<vector<Real> > > F_K, F_T;

      void store_data();
      void store_lb00(vector<Real>& e_vec, int& i);
      void store_lb05(vector<Real>& e_vec, int& i);
      void store_lb06(vector<Real>& e_vec, int& i);

      void resize_matrix(int i_max);

    public:
      //constructor
      MF35Parser(void);

      //destructor
      virtual ~MF35Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();

      //Getter ad line No.01-02
      Real                           get_ZA();
      Real                           get_AWR();
      Integer                        get_NK();

      vector<Real>                   get_E1();
      vector<Real>                   get_E2();
      vector<Integer>                get_LS();
      vector<Integer>                get_LB();
      vector<Integer>                get_NT();
      vector<Integer>                get_NE();

      vector<vector<Real> >          get_E_K();
      vector<vector<vector<Real> > > get_F_K();

      vector<vector<Real> >          get_E_T();
      vector<vector<vector<Real> > > get_F_T();

      vector<vector<Real> >          get_E_K_NER();
      vector<vector<Real> >          get_E_K_NEC();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_NK(Integer& int_data);
      void set_E1(vector<Real>& real_vec);
      void set_E2(vector<Real>& real_vec);
      void set_LS(vector<Integer>& int_vec);
      void set_LB(vector<Integer>& int_vec);
      void set_NT(vector<Integer>& int_vec);
      void set_NE(vector<Integer>& int_vec);
      void set_E_K(vector<vector<Real> >& real_vec);
      void set_F_K(vector<vector<vector<Real> > >& real_vec);
  };
}

#endif // MF35_PARSER_H

