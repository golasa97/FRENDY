#ifndef MF30MT002_PARSER_H
#define MF30MT002_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF30MT002Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =  30;
      static const Integer mt_no  =   2;

      vector<string> text;

      Real                  ZA,   AWR;     //Line No.01
      Integer               NP;

      vector<Real>          PARM;
      vector<vector<Real> > R_COV;

      void store_data();

    public:
      //constructor
      MF30MT002Parser(void);

      //destructor
      virtual ~MF30MT002Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>        get_text();

      Integer               get_mat_no();
      Integer               get_mt_no();

      Real                  get_ZA();
      Real                  get_AWR();
      Integer               get_NP();

      vector<Real>          get_PARM();
      vector<vector<Real> > get_R_COV();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_NP(Integer& int_data);
      void set_PARM(vector<Real>& real_vec);
      void set_R_COV(vector<vector<Real> >& real_vec);
  };
}

#endif // MF30MT002_PARSER_H

