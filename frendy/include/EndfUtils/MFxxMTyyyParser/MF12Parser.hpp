#ifndef MF12_PARSER_H
#define MF12_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF12Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =  12;
      Integer              mt_no;

      vector<string> text;

      Real                     ZA,   AWR;      //Line No.01
      Integer                  LO,   LG,  NK;

      vector<Integer>          NBT_Y_LO01,     INT_Y_LO01;
      vector<Real>             E_INT_Y_LO01,   Y_TAB_LO01;

      vector<Real>             EG_LO01,        ES_LO01;
      vector<Integer>          LP_LO01,        LF_LO01;
      vector<vector<Integer> > NBT_Y_K_LO01,   INT_Y_K_LO01;
      vector<vector<Real> >    E_INT_Y_K_LO01, Y_K_TAB_LO01;

      Real                     ES_LO02;
      Integer                  LP_LO02, NT_LO02;
      vector<Real>             B_LO02;

      void store_data();
      void store_lo01(MultiParser& mp_obj, int& line_no);
      void store_lo02(MultiParser& mp_obj, int& line_no);

    public:
      //constructor
      MF12Parser(void);

      //destructor
      virtual ~MF12Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();


      Real                     get_ZA();
      Real                     get_AWR();
      Integer                  get_LO();
      Integer                  get_LG();
      Integer                  get_NK();
      Integer                  get_NS();

      vector<Integer>          get_NBT_Y_LO01();
      vector<Integer>          get_INT_Y_LO01();
      vector<Real>             get_E_INT_Y_LO01();
      vector<Real>             get_Y_TAB_LO01();

      vector<Real>             get_EG_LO01();
      vector<Real>             get_ES_LO01();
      vector<Integer>          get_LP_LO01();
      vector<Integer>          get_LF_LO01();
      vector<vector<Integer> > get_NBT_Y_K_LO01();
      vector<vector<Integer> > get_INT_Y_K_LO01();
      vector<vector<Real> >    get_E_INT_Y_K_LO01();
      vector<vector<Real> >    get_Y_K_TAB_LO01();

      Real                     get_ES_LO02();
      Integer                  get_LP_LO02();
      Integer                  get_NT_LO02();
      vector<Real>             get_B_LO02();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);

      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LO(Integer& int_data);
      void set_LG(Integer& int_data);
      void set_NK(Integer& int_data);
      void set_NS(Integer& int_data);

      void set_NBT_Y_LO01(vector<Integer>& int_vec);
      void set_INT_Y_LO01(vector<Integer>& int_vec);
      void set_E_INT_Y_LO01(vector<Real>& real_vec);
      void set_Y_TAB_LO01(vector<Real>& real_vec);

      void set_EG_LO01(vector<Real>& real_vec);
      void set_ES_LO01(vector<Real>& real_vec);
      void set_LP_LO01(vector<Integer>& int_vec);
      void set_LF_LO01(vector<Integer>& int_vec);
      void set_NBT_Y_K_LO01(vector<vector<Integer> >& int_vec);
      void set_INT_Y_K_LO01(vector<vector<Integer> >& int_vec);
      void set_E_INT_Y_K_LO01(vector<vector<Real> >& real_vec);
      void set_Y_K_TAB_LO01(vector<vector<Real> >& real_vec);

      void set_ES_LO02(Real& real_data);
      void set_LP_LO02(Integer& int_data);
      void set_NT_LO02(Integer& int_data);
      void set_B_LO02(vector<Real>& real_vec);
  };
}

#endif // MF12_PARSER_H
