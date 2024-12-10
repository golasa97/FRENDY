#ifndef MF03_PARSER_H
#define MF03_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF03Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no =   3;
      Integer              mt_no;

      vector<string> text;

      Real    ZA, AWR;                    //Line No.01
      Real    QM, QI;                     //Line No.02 
      Integer LR;
      vector<Integer> NBT_SIG,   INT_SIG;
      vector<Real>    E_INT_SIG, SIG_TAB;
    
      void store_data();

    public:
      //constructor
      MF03Parser(void);

      //destructor
      virtual ~MF03Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();

      //Getter at line No.01
      Real            get_ZA();
      Real            get_AWR();

      //Getter at line No.02
      Real            get_QM();
      Real            get_QI();
      Integer         get_LR();
      vector<Integer> get_NBT_SIG();
      vector<Integer> get_INT_SIG();
      vector<Real>    get_E_INT_SIG();
      vector<Real>    get_SIG_TAB();

      //Setter 
      void set_mat_no(Integer& int_no);
      void set_mt_no(Integer& int_no);

      //line No.01
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);

      //line No.02
      void set_QM(Real& real_data);
      void set_QI(Real& real_data);
      void set_LR(Integer& int_data);
      void set_NBT_SIG(vector<Integer>& int_vec);
      void set_INT_SIG(vector<Integer>& int_vec);
      void set_E_INT_SIG(vector<Real>& real_vec);
      void set_SIG_TAB(vector<Real>& real_vec);
  };
}

#endif // MF03_PARSER_H
