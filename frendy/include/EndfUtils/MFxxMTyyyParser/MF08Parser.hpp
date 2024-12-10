#ifndef MF08_PARSER_H
#define MF08_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF08Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =   8;
      Integer              mt_no;

      vector<string> text;

      Real                  ZA,  AWR;      //Line No.01
      Integer               LIS, LISO, NS, NO;

      vector<Real>          ZAP, ELFS;      //Line No.02
      vector<Integer>       LMF, LFS;
      vector<vector<Real> > HL,  RTYP, ZAN, BR, END, CT;

      void store_data();

    public:
      //constructor
      MF08Parser(void);

      //destructor
      virtual ~MF08Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();


      Real                  get_ZA();
      Real                  get_AWR();
      Integer               get_LIS();
      Integer               get_LISO();
      Integer               get_NS();
      Integer               get_NO();

      vector<Real>          get_ZAP();
      vector<Real>          get_ELFS();
      vector<Integer>       get_LMF();
      vector<Integer>       get_LFS();
      vector<vector<Real> > get_HL();
      vector<vector<Real> > get_RTYP();
      vector<vector<Real> > get_ZAN();
      vector<vector<Real> > get_BR();
      vector<vector<Real> > get_END();
      vector<vector<Real> > get_CT();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LIS(Integer& int_data);
      void set_LISO(Integer& int_data);
      void set_NS(Integer& int_data);
      void set_NO(Integer& int_data);
      void set_ZAP(vector<Real>& real_vec);
      void set_ELFS(vector<Real>& real_vec);
      void set_LMF(vector<Integer>& int_vec);
      void set_LFS(vector<Integer>& int_vec);
      void set_HL(vector<vector<Real> >& real_vec);
      void set_RTYP(vector<vector<Real> >& real_vec);
      void set_ZAN(vector<vector<Real> >& real_vec);
      void set_BR(vector<vector<Real> >& real_vec);
      void set_END(vector<vector<Real> >& real_vec);
      void set_CT(vector<vector<Real> >& real_vec);
  };
}

#endif // MF08_PARSER_H

