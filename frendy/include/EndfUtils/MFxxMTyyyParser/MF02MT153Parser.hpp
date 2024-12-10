#ifndef MF02MT153_PARSER_H
#define MF02MT153_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF02MT153Parser
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer mat_no;
      static const Integer mf_no =   2;
      static const Integer mt_no = 153;

      vector<string> text;

      Real         ZAR,  AWR;
      Integer      INEL, ABSO, INT, NBIN;

      Real         TEMP;
      Integer      LSSF, ICOMP, NUNR;
      vector<Real> ENE;
      vector<vector<Real> > HEAT, P_COUNT;
      vector<vector<vector<Real> > > P_TABLE;

      void store_data();

    public:
      //constructor
      MF02MT153Parser(void);

      //destructor
      virtual ~MF02MT153Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter 
      vector<string> get_text();

      Integer      get_mat_no();

      Real         get_ZAR();
      Real         get_AWR();
      Integer      get_INEL();
      Integer      get_ABSO();
      Integer      get_INT();
      Integer      get_NBIN();

      Real         get_TEMP();
      Integer      get_LSSF();
      Integer      get_ICOMP();
      Integer      get_NUNR();
      vector<Real> get_ENE();
      vector<vector<Real> > get_HEAT();
      vector<vector<Real> > get_P_COUNT();
      vector<vector<vector<Real> > > get_P_TABLE();

      //Setter
      void set_mat_no(Integer& int_data);

      void set_ZAR(Real& real_data);
      void set_AWR(Real& real_data);
      void set_INEL(Integer& int_data);
      void set_ABSO(Integer& int_data);
      void set_INT(Integer& int_data);
      void set_NBIN(Integer& int_data);

      void set_TEMP(Real& real_data);
      void set_LSSF(Integer& int_data);
      void set_ICOMP(Integer& int_data);
      void set_NUNR(Integer& int_data);
      void set_ENE(vector<Real>& real_vec);
      void set_HEAT(vector<vector<Real> >& real_vec);
      void set_P_COUNT(vector<vector<Real> >& real_vec);
      void set_P_TABLE(vector<vector<vector<Real> > >& real_vec);
  };
}

#endif // MF02MT153_PARSER_H
