#ifndef MF30MT001_PARSER_H
#define MF30MT001_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF30MT001Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =  30;
      static const Integer mt_no  =   1;

      vector<string> text;

      Real            ZA,   AWR;     //Line No.01
      Integer         NP;
      Integer         NDIR, NCTAB;

      vector<Integer> MP_NDIR,  MFSEN_NDIR, MTSEN_NDIR, NC_NDIR;
      vector<Integer> MP_NCTAB, LIBF_NCTAB, MATF_NCTAB, MPF_NCTAB;

      void store_data();

    public:
      //constructor
      MF30MT001Parser(void);

      //destructor
      virtual ~MF30MT001Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();

      Real            get_ZA();
      Real            get_AWR();
      Integer         get_NP();
      Integer         get_NDIR();
      Integer         get_NCTAB();

      vector<Integer> get_MP_NDIR();
      vector<Integer> get_MFSEN_NDIR();
      vector<Integer> get_MTSEN_NDIR();
      vector<Integer> get_NC_NDIR();

      vector<Integer> get_MP_NCTAB();
      vector<Integer> get_LIBF_NCTAB();
      vector<Integer> get_MATF_NCTAB();
      vector<Integer> get_MPF_NCTAB();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_NP(Integer& int_data);
      void set_NDIR(Integer& int_data);
      void set_NCTAB(Integer& int_data);
      void set_MP_NDIR(vector<Integer>& int_vec);
      void set_MFSEN_NDIR(vector<Integer>& int_vec);
      void set_MTSEN_NDIR(vector<Integer>& int_vec);
      void set_NC_NDIR(vector<Integer>& int_vec);
      void set_MP_NCTAB(vector<Integer>& int_vec);
      void set_LIBF_NCTAB(vector<Integer>& int_vec);
      void set_MATF_NCTAB(vector<Integer>& int_vec);
      void set_MPF_NCTAB(vector<Integer>& int_vec);
  };
}

#endif // MF30MT001_PARSER_H

