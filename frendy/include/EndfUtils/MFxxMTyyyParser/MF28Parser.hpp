#ifndef MF28_PARSER_H
#define MF28_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF28Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =  28;
      Integer              mt_no;

      vector<string> text;

      Real                  ZA,   AWR; //Line No.01
      Integer               NSS;

      vector<Real>          SUBI, EBI,  ELN;
      vector<vector<Real> > SUBJ, SUBK, ETR, FTR;

      void store_data();

    public:
      //constructor
      MF28Parser(void);

      //destructor
      virtual ~MF28Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>        get_text();

      Integer               get_mat_no();
      Integer               get_mt_no();

      Real                  get_ZA();
      Real                  get_AWR();
      Integer               get_NSS();

      vector<Real>          get_SUBI();
      vector<Real>          get_EBI();
      vector<Real>          get_ELN();
      vector<vector<Real> > get_SUBJ();
      vector<vector<Real> > get_SUBK();
      vector<vector<Real> > get_ETR();
      vector<vector<Real> > get_FTR();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_NSS(Integer& int_data);
      void set_SUBI(vector<Real>& real_vec);
      void set_EBI(vector<Real>& real_vec);
      void set_ELN(vector<Real>& real_vec);
      void set_SUBJ(vector<vector<Real> >& real_vec);
      void set_SUBK(vector<vector<Real> >& real_vec);
      void set_ETR(vector<vector<Real> >& real_vec);
      void set_FTR(vector<vector<Real> >& real_vec);
  };
}

#endif // MF28_PARSER_H

