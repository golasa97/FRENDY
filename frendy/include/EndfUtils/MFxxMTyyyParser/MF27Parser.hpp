#ifndef MF27_PARSER_H
#define MF27_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF27Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =  27;
      Integer              mt_no;

      vector<string> text;

      Real            ZA,      AWR; //Line No.01

      Real            Z;
      vector<Integer> NBT_H,   INT_H;
      vector<Real>    Q_INT_H, H_TAB;

      void store_data();

    public:
      //constructor
      MF27Parser(void);

      //destructor
      virtual ~MF27Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();

      Real            get_ZA();
      Real            get_AWR();
      Real            get_Z();

      vector<Integer> get_NBT_H();
      vector<Integer> get_INT_H();
      vector<Real>    get_Q_INT_H();
      vector<Real>    get_H_TAB();

      vector<Integer> get_NBT_F();
      vector<Integer> get_INT_F();
      vector<Real>    get_E_INT_F();
      vector<Real>    get_F_TAB();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_Z(Real& real_data);
      void set_NBT_H(vector<Integer>& int_vec);
      void set_INT_H(vector<Integer>& int_vec);
      void set_Q_INT_H(vector<Real>& real_vec);
      void set_H_TAB(vector<Real>& real_vec);
      void set_NBT_F(vector<Integer>& int_vec);
      void set_INT_F(vector<Integer>& int_vec);
      void set_E_INT_F(vector<Real>& real_vec);
      void set_F_TAB(vector<Real>& real_vec);
  };
}

#endif // MF27_PARSER_H

