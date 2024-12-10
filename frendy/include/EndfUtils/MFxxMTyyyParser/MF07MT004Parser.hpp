#ifndef MF07MT004_PARSER_H
#define MF07MT004_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF07MT004Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no = 7;
      static const Integer mt_no = 4;

      vector<string> text;

      Real                     ZA,  AWR;      //Line No.01
      Integer                  LAT, LASYM;

      Integer                  LLN, NS;       //Line No.02
      vector<Real>             B;

      Integer                  NB;
      vector<Integer>          NBT_BETA, INT_BETA;

      vector<Real>             T0, BETA;
      vector<vector<Integer> > NBT_S0, INT_S0;
      vector<vector<Real> >    A_INT_S0, S0_TAB;

      vector<vector<Real> >    T;
      vector<vector<Integer> > LI;
      vector<vector<vector<Real> > > S;

      vector<vector<Integer> > NBT_T,   INT_T;
      vector<vector<Real> >    T_INT_T, T_TAB;

      void store_data();
      void resize_matrix();

    public:
      //constructor
      MF07MT004Parser(void);

      //destructor
      virtual ~MF07MT004Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string> get_text();

      Integer        get_mat_no();

      Real                     get_ZA();
      Real                     get_AWR();
      Integer                  get_LAT();
      Integer                  get_LASYM();

      Integer                  get_LLN();
      Integer                  get_NS();
      vector<Real>             get_B();

      Integer                  get_NB();
      vector<Integer>          get_NBT_BETA();
      vector<Integer>          get_INT_BETA();

      vector<Real>             get_T0();
      vector<Real>             get_BETA();
      vector<vector<Integer> > get_NBT_S0();
      vector<vector<Integer> > get_INT_S0();
      vector<vector<Real> >    get_A_INT_S0();
      vector<vector<Real> >    get_S0_TAB();

      vector<vector<Real> >    get_T();
      vector<vector<Integer> > get_LI();
      vector<vector<vector<Real> > > get_S();

      vector<vector<Integer> > get_NBT_T();
      vector<vector<Integer> > get_INT_T();
      vector<vector<Real> >    get_T_INT_T();
      vector<vector<Real> >    get_T_TAB();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LAT(Integer& int_data);
      void set_LASYM(Integer& int_data);
      void set_LLN(Integer& int_data);
      void set_NS(Integer& int_data);
      void set_B(vector<Real>& real_vec);
      void set_NB(Integer& int_data);
      void set_NBT_BETA(vector<Integer>& int_vec);
      void set_INT_BETA(vector<Integer>& int_vec);
      void set_T0(vector<Real>& real_vec);
      void set_BETA(vector<Real>& real_vec);
      void set_NBT_S0(vector<vector<Integer> >& int_vec);
      void set_INT_S0(vector<vector<Integer> >& int_vec);
      void set_A_INT_S0(vector<vector<Real> >& real_vec);
      void set_S0_TAB(vector<vector<Real> >& real_vec);
      void set_T(vector<vector<Real> >& real_vec);
      void set_LI(vector<vector<Integer> >& int_vec);
      void set_S(vector<vector<vector<Real> > >& real_vec);
      void set_NBT_T(vector<vector<Integer> >& int_vec);
      void set_INT_T(vector<vector<Integer> >& int_vec);
      void set_T_INT_T(vector<vector<Real> >& real_vec);
      void set_T_TAB(vector<vector<Real> >& real_vec);
  };
}

#endif // MF07MT004_PARSER_H

