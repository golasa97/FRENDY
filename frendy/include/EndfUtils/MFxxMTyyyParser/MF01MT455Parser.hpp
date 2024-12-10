#ifndef MF01MT455_PARSER_H
#define MF01MT455_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF01MT455Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer mat_no;
      static const Integer mf_no =   1;
      static const Integer mt_no = 455;

      vector<string> text;

      Real    ZA, AWR;                           //Line No.01
      Integer LDG,  LNU;
      Integer NC,   NNF,  NR_E,  NE_E;           //Line No.02
      Integer NR_NU, NP_NU;

      vector<Integer> NBT_E, INT_E, NBT_NU, INT_NU;
      vector<Real>    RAMDA,  E, E_INT_NU, NU;
      vector<vector<Real> > ALPHA_MAP, RAMDA_MAP;

      void store_data();

    public:
      //constructor
      MF01MT455Parser(void);

      //destructor
      virtual ~MF01MT455Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string> get_text();

      Integer        get_mat_no();

      //Getter at line No.01
      Real           get_ZA();
      Real           get_AWR();
      Integer        get_LDG();
      Integer        get_LNU();

      //Getter at line No.02
      Integer        get_NC();
      Integer        get_NNF();
      Integer        get_NR_E();
      Integer        get_NE_E();
      Integer        get_NR_NU();
      Integer        get_NP_NU();

      vector<Integer> get_NBT_E();
      vector<Integer> get_INT_E();     //For LNU=0
      vector<Integer> get_NBT_NU();
      vector<Integer> get_INT_NU();

      vector<Real>    get_RAMDA();
      vector<Real>    get_E();
      vector<Real>    get_E_INT_NU();  //E_INT -> E_INT_NU (For LDG=1)
      vector<Real>    get_NU();

      vector<vector<Real> > get_ALPHA_MAP();
      vector<vector<Real> > get_RAMDA_MAP();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LDG(Integer& int_data);
      void set_LNU(Integer& int_data);
      void set_NC(Integer& int_data);
      void set_NNF(Integer& int_data);
      void set_NR_E(Integer& int_data);
      void set_NE_E(Integer& int_data);
      void set_NR_NU(Integer& int_data);
      void set_NP_NU(Integer& int_data);
      void set_NBT_E(vector<Integer>& int_vec);
      void set_INT_E(vector<Integer>& int_vec);
      void set_NBT_NU(vector<Integer>& int_vec);
      void set_INT_NU(vector<Integer>& int_vec);
      void set_RAMDA(vector<Real>& real_vec);
      void set_E(vector<Real>& real_vec);
      void set_E_INT_NU(vector<Real>& real_vec);
      void set_NU(vector<Real>& real_vec);
      void set_ALPHA_MAP(vector<vector<Real> >& real_vec);
      void set_RAMDA_MAP(vector<vector<Real> >& real_vec);
  };
}

#endif // MF01MT455_PARSER_H

