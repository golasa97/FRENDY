#ifndef MF01MT451_PARSER_H
#define MF01MT451_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF01MT451Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer mat_no;
      static const Integer mf_no =   1;
      static const Integer mt_no = 451;

      vector<string> text;

      Real    ZA, AWR;                           //Line No.01
      Integer LRP,  LFI, NLIB, NMOD; 
      Real    ELIS;                              //Line No.02 
      Integer STA, LIS,  LISO, NFOR;
      Real    AWI,  EMAX;                        //Line No.03
      Integer LREL, NSUB, NVER;
      Real    TEMP, ERROR;                       //Line No.04
      Integer LDRV, NWD,  NXC;
      string  ZSYMAM, ALAB, EDATE, AUTH;         //Line No.05
      string  REF,  DDATE, RDATE, ENDATE;        //Line No.06
      string  HSUB;                              //Line No.07
      vector<string> comment_line;

  //    vector<string>  comment
      vector<Integer> MF, MT, NC, MOD;
    
      void store_data();

    public:
      //constructor
      MF01MT451Parser(void);

      //destructor
      virtual ~MF01MT451Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string> get_text();

      Integer        get_mat_no();

      //Getter at line No.01
      Real           get_ZA();
      Real           get_AWR();
      Integer        get_LRP();
      Integer        get_LFI();
      Integer        get_NLIB();
      Integer        get_NMOD();

      //Getter at line No.02
      Real           get_ELIS();
      Integer        get_STA();
      Integer        get_LIS();
      Integer        get_LISO();
      Integer        get_NFOR();

      //Getter at line No.03
      Real           get_AWI();
      Real           get_EMAX();
      Integer        get_LREL();
      Integer        get_NSUB();
      Integer        get_NVER();

      //Getter at line No.04
      Real           get_TEMP();
      Real           get_ERROR();
      Integer        get_LDRV();
      Integer        get_NWD();
      Integer        get_NXC();

      //Getter at line No.05
      string         get_ZSYMAM();
      string         get_ALAB();
      string         get_EDATE();
      string         get_AUTH();

      //Getter at line No.06
      string         get_REF();
      string         get_DDATE();
      string         get_RDATE();
      string         get_ENDATE();

      //Getter at line No.07
      string         get_HSUB();

      vector<string> get_comment_line();

      //Getter at other data (MF, MT, NC, MOD)
      vector<Integer> get_MF();
      vector<Integer> get_MT();
      vector<Integer> get_NC();
      vector<Integer> get_MOD();

      //Setter
      void set_mat_no(Integer& int_data);

      //Setter at line No.01
      void set_ZA(  Real&    real_data);
      void set_AWR( Real&    real_data);
      void set_LRP( Integer& int_data);
      void set_LFI( Integer& int_data);
      void set_NLIB(Integer& int_data);
      void set_NMOD(Integer& int_data);

      //Setter at line No.02
      void set_ELIS(Real&    real_data);
      void set_STA( Integer& int_data);
      void set_LIS( Integer& int_data);
      void set_LISO(Integer& int_data);
      void set_NFOR(Integer& int_data);

      //Setter at line No.03
      void set_AWI( Real&    real_data);
      void set_EMAX(Real&    real_data);
      void set_LREL(Integer& int_data);
      void set_NSUB(Integer& int_data);
      void set_NVER(Integer& int_data);

      //Setter at line No.04
      void set_TEMP(Real&    real_data);
      void set_ERROR(Real&   real_data);
      void set_LDRV(Integer& int_data);
      void set_NWD( Integer& int_data);
      void set_NXC( Integer& int_data);

      //Setter at line No.05
      void set_ZSYMAM(string& str_data);
      void set_ALAB(  string& str_data);
      void set_EDATE( string& str_data);
      void set_AUTH(  string& str_data);

      //Setter at line No.06
      void set_REF(   string& str_data);
      void set_DDATE( string& str_data);
      void set_RDATE( string& str_data);
      void set_ENDATE(string& str_data);

      //Setter at line No.07
      void set_HSUB(string& str_data);

      void set_comment_line(vector<string>& str_vec);

      //Setter at other data (MF, MT, NC, MOD)
      void set_MF( vector<Integer>& int_vec);
      void set_MT( vector<Integer>& int_vec);
      void set_NC( vector<Integer>& int_vec);
      void set_MOD(vector<Integer>& int_vec);
  };
}

#endif // MF01MT451_PARSER_H
