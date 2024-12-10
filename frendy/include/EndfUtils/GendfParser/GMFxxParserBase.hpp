#ifndef GMFxxParserBase_H
#define GMFxxParserBase_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class GMFxxParserBase
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      Integer              mat_no, mf_no, mt_no;

      vector<string> text;

      Real    ZA, AWR;                    //Line No.01
      Integer NL, NSIGZ, LR, NGN;


      Real    TEMP;                       //Line No.02 
      vector<int> NG2, IG2LO, IG;
      vector<vector<vector<Real> > >          DATA1;
      vector<vector<vector<vector<Real> > > > DATA2;
    
      void store_data();

    public:
      //constructor
      GMFxxParserBase(void);

      //destructor
      virtual ~GMFxxParserBase(void);

      void clear();

      void set_text(vector<string> text_data);
      void remove_DATA2_NG2_zero_data();

      void multiply_coef(Real weight_val);
      void multiply_coef_data1(Real weight_val);
      void multiply_coef_data2(Real weight_val);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mf_no();
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
      vector<vector<vector<Real> > >          get_DATA1();
      vector<vector<vector<Real> > >          get_DATA2();
      vector<vector<vector<vector<Real> > > > get_DATA2_NG2();

      vector<vector<vector<vector<Real> > > > get_DATA2_NG2_fill_data();

      vector<vector<vector<Real> > > get_DATA2_integ();
      Real                           get_DATA2_integ(int ene_in, int sigz_no, int pl_no);

      vector<Real>          get_DATA1(vector<vector<vector<Real> > >& data1_vec,
                                      int sigz_no, int pl_no);
      vector<Real>          get_DATA1(int sigz_no, int pl_no);
      vector<Real>          get_DATA1_fill_data(int sigz_no, int pl_no);
      vector<Real>          get_DATA2(int sigz_no, int pl_no);

      vector<vector<Real> > get_DATA2_NG2(vector<vector<vector<vector<Real> > > >& data2_vec,
                                          int sigz_no, int pl_no);
      vector<vector<Real> > get_DATA2_NG2(int sigz_no, int pl_no);
      vector<vector<Real> > get_DATA2_NG2_fill_data(int sigz_no, int pl_no);

      //Setter 
      void set_mat_no(Integer int_no);
      void set_mf_no(Integer int_no);
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
      void set_DATA1(vector<vector<vector<Real> > > real_vec);
      void set_DATA2(vector<vector<vector<Real> > > real_vec);
      void set_DATA2_NG2(vector<vector<vector<vector<Real> > > > real_vec);
  };
}

#endif // GMFxxParserBase_H
