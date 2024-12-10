#ifndef GMF13_PARSER_H
#define GMF13_PARSER_H

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/GendfParser/GMFxxParserBase.hpp"

namespace frendy
{
  class GMF13Parser
  {
    private:
      frendy::GMFxxParserBase read_obj;

      Integer              mat_no;
      static const Integer mf_no =  13;
      Integer              mt_no;

      vector<string> text;

      void store_data();

    public:
      //constructor
      GMF13Parser(void);

      //destructor
      virtual ~GMF13Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      frendy::GMFxxParserBase get_read_obj();

      Integer         get_mat_no();
      Integer         get_mt_no();

      //Getter at line No.01
      Real            get_ZA();
      Real            get_AWR();
      Integer         get_NL();
      Integer         get_NSIGZ();
      Integer         get_LR();
      Integer         get_NGN();

      //Getter at line No.02
      Real            get_TEMP();
      vector<int>     get_NG2();
      vector<int>     get_IG2LO();
      vector<int>     get_IG();
      vector<vector<vector<Real> > > get_FLUX();
      vector<vector<vector<Real> > > get_SIG();

      //Setter 
      void set_read_obj(frendy::GMFxxParserBase read_gendf_obj);

      void set_mat_no(Integer int_no);
      void set_mt_no(Integer int_no);

      //line No.01
      void set_ZA(Real real_data);
      void set_AWR(Real real_data);
      void set_NL(Integer int_data);
      void set_NSIGZ(Integer int_data);
      void set_LR(Integer int_data);
      void set_NGN(Integer int_data);

      //line No.02
      void set_TEMP(Real real_data);
      void set_NG2(vector<int> int_vec);
      void set_IG2LO(vector<int> int_vec);
      void set_IG(vector<int> int_vec);
      void set_FLUX(vector<vector<vector<Real> > > real_vec);
      void set_SIG(vector<vector<vector<Real> > > real_vec);
  };
}

#endif // GMF13_PARSER_H
