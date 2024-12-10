#ifndef MF13_PARSER_H
#define MF13_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF13Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =  13;
      Integer              mt_no;

      vector<string> text;

      Real                     ZA,   AWR;      //Line No.01
      Integer                  NK;

      vector<Integer>          NBT_S_TOT,   INT_S_TOT;
      vector<Real>             E_INT_S_TOT, S_TOT_TAB;

      vector<Real>             EG,   ES;      //Line No.02
      vector<Integer>          LP,   LF;
      vector<vector<Integer> > NBT_S_K,   INT_S_K;
      vector<vector<Real> >    E_INT_S_K, S_K_TAB;

      void store_data();
      void resize_matrix(int i_max);

    public:
      //constructor
      MF13Parser(void);

      //destructor
      virtual ~MF13Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();


      Real                     get_ZA();
      Real                     get_AWR();
      Integer                  get_NK();

      vector<Integer>          get_NBT_S_TOT();
      vector<Integer>          get_INT_S_TOT();
      vector<Real>             get_E_INT_S_TOT();
      vector<Real>             get_S_TOT_TAB();

      vector<Real>             get_EG();
      vector<Real>             get_ES();
      vector<Integer>          get_LP();
      vector<Integer>          get_LF();
      vector<vector<Integer> > get_NBT_S_K();
      vector<vector<Integer> > get_INT_S_K();
      vector<vector<Real> >    get_E_INT_S_K();
      vector<vector<Real> >    get_S_K_TAB();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);

      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_NK(Integer& int_data);

      void set_NBT_S_TOT(vector<Integer>& int_vec);
      void set_INT_S_TOT(vector<Integer>& int_vec);
      void set_E_INT_S_TOT(vector<Real>& real_vec);
      void set_S_TOT_TAB(vector<Real>& real_vec);

      void set_EG(vector<Real>& real_vec);
      void set_ES(vector<Real>& real_vec);
      void set_LP(vector<Integer>& int_vec);
      void set_LF(vector<Integer>& int_vec);
      void set_NBT_S_K(vector<vector<Integer> >& int_vec);
      void set_INT_S_K(vector<vector<Integer> >& int_vec);
      void set_E_INT_S_K(vector<vector<Real> >& real_vec);
      void set_S_K_TAB(vector<vector<Real> >& real_vec);
  };
}

#endif // MF13_PARSER_H
