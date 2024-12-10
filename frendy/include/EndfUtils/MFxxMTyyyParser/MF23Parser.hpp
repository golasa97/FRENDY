#ifndef MF23_PARSER_H
#define MF23_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF23Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =  23;
      Integer              mt_no;

      vector<string> text;

      Real            ZA,      AWR; //Line No.01

      Real            EPE,     EFL;
      vector<Integer> NBT_S,   INT_S;
      vector<Real>    E_INT_S, S_TAB;

      void store_data();

    public:
      //constructor
      MF23Parser(void);

      //destructor
      virtual ~MF23Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();

      Real            get_ZA();
      Real            get_AWR();
      Real            get_EPE();
      Real            get_EFL();
      vector<Integer> get_NBT_S();
      vector<Integer> get_INT_S();
      vector<Real>    get_E_INT_S();
      vector<Real>    get_S_TAB();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);

      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_EPE(Real& real_data);
      void set_EFL(Real& real_data);
      void set_NBT_S(vector<Integer>& int_vec);
      void set_INT_S(vector<Integer>& int_vec);
      void set_E_INT_S(vector<Real>& real_vec);
      void set_S_TAB(vector<Real>& real_vec);
  };
}

#endif // MF23_PARSER_H
