#ifndef MF02MT152_PARSER_H
#define MF02MT152_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF02MT152Parser
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer mat_no;
      static const Integer mf_no =   2;
      static const Integer mt_no = 152;

      vector<string> text;

      Real         ZAR,  AWR;
      Integer      LSSF, INT;

      Real         TEMP;
      Integer      OPT1, OPT2, NE;
      vector<Real> E, SIG_TOT, SIG_SC, SIG_FIS, SIG_RAD;
      vector<Real> SIG_ZERO;
      vector<vector<vector<Real> > > B_TABLE;

      void store_data();
      void store_data_reconr_mode(vector<Real>& e_vec);
      void store_data_purr_mode(vector<Real>& e_vec);

    public:
      //constructor
      MF02MT152Parser(void);

      //destructor
      virtual ~MF02MT152Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter 
      vector<string> get_text();

      Integer        get_mat_no();

      Real         get_ZAR();
      Real         get_AWR();
      Integer      get_LSSF();
      Integer      get_INT();

      Real         get_TEMP();
      Integer      get_OPT1();
      Integer      get_OPT2();
      Integer      get_NE();
      vector<Real> get_E();
      vector<Real> get_SIG_TOT();
      vector<Real> get_SIG_SC();
      vector<Real> get_SIG_FIS();
      vector<Real> get_SIG_RAD();
      vector<Real> get_SIG_ZERO();
      vector<vector<vector<Real> > > get_B_TABLE();

      //Setter
      void set_mat_no(Integer& int_data);

      void set_ZAR(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LSSF(Integer& int_data);
      void set_INT(Integer& int_data);

      void set_TEMP(Real& real_data);
      void set_OPT1(Integer& int_data);
      void set_OPT2(Integer& int_data);
      void set_NE(Integer& int_data);
      void set_E(vector<Real>& real_vec);
      void set_SIG_TOT(vector<Real>& real_vec);
      void set_SIG_SC( vector<Real>& real_vec);
      void set_SIG_FIS(vector<Real>& real_vec);
      void set_SIG_RAD(vector<Real>& real_vec);
      void set_SIG_ZERO(vector<Real>& real_vec);
      void set_B_TABLE(vector<vector<vector<Real> > >& real_vec);
  };
}

#endif // MF02MT152_PARSER_H
