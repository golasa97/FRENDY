#ifndef MF07MT451_PARSER_H
#define MF07MT451_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF07MT451Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no = 7;
      static const Integer mt_no = 451;

      vector<string> text;

      //Common data
      Real                  ZA,  AWR;      //Line No.01
      Integer               NA,  NAS,  NI;
      vector<Real>          ZAI, AFI, SFI, AWRI;
      vector<Integer>       LISI;


      void store_data();

    public:
      //constructor
      MF07MT451Parser(void);

      //destructor
      virtual ~MF07MT451Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string> get_text();

      Integer        get_mat_no();

      //Common data
      Real                  get_ZA();
      Real                  get_AWR();
      Integer               get_NA();
      Integer               get_NAS();
      Integer               get_NI();

      vector<Real>          get_ZAI();
      vector<Real>          get_AFI();
      vector<Real>          get_SFI();
      vector<Real>          get_AWRI();
      vector<Integer>       get_LISI();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_NA(Integer& int_data);
      void set_NAS(Integer& int_data);
      void set_NI(Integer& int_data);


      void set_ZAI(vector<Real>& real_vec);
      void set_AFI(vector<Real>& real_vec);
      void set_SFI(vector<Real>& real_vec);
      void set_AWRI(vector<Real>& real_vec);
      void set_LISI(vector<Integer>& int_vec);
  };
}

#endif // MF07MT451_PARSER_H

