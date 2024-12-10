#ifndef MF06_PARSER_H
#define MF06_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF06Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no = 6;
      Integer              mt_no;

      vector<string> text;

      Real                              ZA,  AWR;      //Line No.01
      Integer                           JP, JPP, JPN, LCT, NK;
      vector<Real>                      ZAP, AWP;      //Line No.02
      vector<Integer>                   LIP, LAW;
      vector<vector<Integer> >          NBT_Y,   INT_Y;
      vector<vector<Real> >             E_INT_Y, Y_TAB;
      vector<Integer>                   NE;
      vector<vector<Integer> >          NBT_E,   INT_E;

      //LAW = 1
      vector<Integer>                   LANG_LAW01, LEP_LAW01;
      vector<vector<Real> >             E1_LAW01;
      vector<vector<Integer> >          ND_LAW01;
      vector<vector<vector<Real> > >    E2_LAW01;
      vector<vector<vector<vector<Real> > > > B_LAW01;

      //LAW = 2
      vector<vector<Real> >             E_LAW02;
      vector<vector<Integer> >          LANG_LAW02, NL_LAW02;
      vector<vector<vector<Real> > >    A_LAW02;

      //LAW = 5
      vector<Real>                      SPI_LAW05;
      vector<Integer>                   LIDP_LAW05;
      vector<vector<Real> >             E_LAW05;
      vector<vector<Integer> >          LTP_LAW05;
      vector<vector<vector<Real> > >    B_LAW05, P_LAW05, RA_LAW05, IA_LAW05;

      //LAW = 6
      vector<Real>                      APSX_LAW06;
      vector<Integer>                   NPSX_LAW06;

      //LAW = 7
      vector<vector<Real> >             E_LAW07;
      vector<vector<Integer> >          NMU_LAW07;
      vector<vector<vector<Integer> > > NBT_MU_LAW07,  INT_MU_LAW07;
      vector<vector<vector<Real> > >    MU_LAW07;
      vector<vector<vector<vector<Integer> > > > NBT_F_LAW07,   INT_F_LAW07;
      vector<vector<vector<vector<Real> > > >    E_INT_F_LAW07, F_TAB_LAW07;

      //For thermal scatter (LCT = 5-7 )
      Integer                        NBRAGG, NNE;
      Real                           TEMP;
      vector<Real>                   EN;
      vector<vector<Real> >          EP, PP, U;
      vector<vector<vector<Real> > > EPM;

      void store_data();
      void store_law01(MultiParser& mp_obj, int& line_no, int& i);
      void store_law02(MultiParser& mp_obj, int& line_no, int& i);
      void store_law05(MultiParser& mp_obj, int& line_no, int& i);
      void store_law07(MultiParser& mp_obj, int& line_no, int& i);

      //Store thermal scatter data calculated by NJOY99
      void store_thermal_scatter(MultiParser& mp_obj, int& line_no);
      void store_thermal_scatter_new_format
            (MultiParser& mp_obj, int& line_no, Integer law_val, Integer ltt_val);
      void store_incoherent_inelastic_scatter(MultiParser& mp_obj, int& line_no);
      void store_incoherent_elastic_scatter(MultiParser& mp_obj, int& line_no);

      void resize_matrix();

    public:
      //constructor
      MF06Parser(void);

      //destructor
      virtual ~MF06Parser(void);

      void clear();
      void clear_vec_data();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();

      //Getter at line No.01-02
      Real                              get_ZA();
      Real                              get_AWR();
      Integer                           get_JP();
      Integer                           get_JPP();
      Integer                           get_JPN();
      Integer                           get_LCT();
      Integer                           get_NK();

      vector<Real>                      get_ZAP();
      vector<Real>                      get_AWP();
      vector<Integer>                   get_LIP();
      vector<Integer>                   get_LAW();
      vector<vector<Integer> >          get_NBT_Y();
      vector<vector<Integer> >          get_INT_Y();
      vector<vector<Real> >             get_E_INT_Y();
      vector<vector<Real> >             get_Y_TAB();

      //LAW = 1
      vector<Integer>                   get_LANG_LAW01();
      vector<Integer>                   get_LEP_LAW01();
      vector<Integer>                   get_NE_LAW01();
      vector<vector<Integer> >          get_NBT_E_LAW01();
      vector<vector<Integer> >          get_INT_E_LAW01();
      vector<vector<Real> >             get_E1_LAW01();
      vector<vector<Integer> >          get_ND_LAW01();
      vector<vector<vector<Real> > >    get_E2_LAW01();
      vector<vector<vector<vector<Real> > > > get_B_LAW01();

      //LAW = 2
      vector<Integer>                   get_NE_LAW02();
      vector<vector<Integer> >          get_NBT_E_LAW02();
      vector<vector<Integer> >          get_INT_E_LAW02();
      vector<vector<Real> >             get_E_LAW02();
      vector<vector<Integer> >          get_LANG_LAW02();
      vector<vector<Integer> >          get_NL_LAW02();
      vector<vector<vector<Real> > >    get_A_LAW02();

      //LAW = 5
      vector<Real>                      get_SPI_LAW05();
      vector<Integer>                   get_LIDP_LAW05();
      vector<Integer>                   get_NE_LAW05();
      vector<vector<Integer> >          get_NBT_E_LAW05();
      vector<vector<Integer> >          get_INT_E_LAW05();
      vector<vector<Real> >             get_E_LAW05();
      vector<vector<Integer> >          get_LTP_LAW05();
      vector<vector<vector<Real> > >    get_B_LAW05();
      vector<vector<vector<Real> > >    get_RA_LAW05();
      vector<vector<vector<Real> > >    get_IA_LAW05();
      vector<vector<vector<Real> > >    get_C_LAW05();
      vector<vector<vector<Real> > >    get_MU_LAW05();
      vector<vector<vector<Real> > >    get_P_LAW05();

      //LAW = 6
      vector<Real>                      get_APSX_LAW06();
      vector<Integer>                   get_NPSX_LAW06();

      //LAW = 7
      vector<Integer>                   get_NE_LAW07();
      vector<vector<Integer> >          get_NBT_E_LAW07();
      vector<vector<Integer> >          get_INT_E_LAW07();
      vector<vector<Real> >             get_E_LAW07();
      vector<vector<Integer> >          get_NMU_LAW07();
      vector<vector<vector<Integer> > > get_NBT_MU_LAW07();
      vector<vector<vector<Integer> > > get_INT_MU_LAW07();
      vector<vector<vector<Real> > >    get_MU_LAW07();
      vector<vector<vector<vector<Integer> > > > get_NBT_F_LAW07();
      vector<vector<vector<vector<Integer> > > > get_INT_F_LAW07();
      vector<vector<vector<vector<Real> > > >    get_E_INT_F_LAW07();
      vector<vector<vector<vector<Real> > > >    get_F_TAB_LAW07();

      //For thermal scatter (LCT = 5-7 )
      Integer                        get_NBRAGG();
      Integer                        get_NNE();
      Real                           get_TEMP();
      vector<vector<Real> >          get_EP();
      vector<vector<Real> >          get_PP();
      vector<vector<vector<Real> > > get_EPM();
      vector<vector<Real> >          get_U();
      vector<Real>                   get_EN();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_JP(Integer int_data);
      void set_JPP(Integer int_data);
      void set_JPN(Integer int_data);
      void set_LCT(Integer int_data);
      void set_NK(Integer int_data);
      void set_ZAP(vector<Real>& real_vec);
      void set_AWP(vector<Real>& real_vec);
      void set_LIP(vector<Integer>& int_vec);
      void set_LAW(vector<Integer>& int_vec);
      void set_NBT_Y(vector<vector<Integer> >& int_vec);
      void set_INT_Y(vector<vector<Integer> >& int_vec);
      void set_E_INT_Y(vector<vector<Real> >& real_vec);
      void set_Y_TAB(vector<vector<Real> >& real_vec);
      void set_LANG_LAW01(vector<Integer>& int_vec);
      void set_LEP_LAW01(vector<Integer>& int_vec);
      void set_NE_LAW01(vector<Integer>& int_vec);
      void set_NBT_E_LAW01(vector<vector<Integer> >& int_vec);
      void set_INT_E_LAW01(vector<vector<Integer> >& int_vec);
      void set_E1_LAW01(vector<vector<Real> >& real_vec);
      void set_ND_LAW01(vector<vector<Integer> >& int_vec);
      void set_E2_LAW01(vector<vector<vector<Real> > >& real_vec);
      void set_B_LAW01(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_NE_LAW02(vector<Integer>& int_vec);
      void set_NBT_E_LAW02(vector<vector<Integer> >& int_vec);
      void set_INT_E_LAW02(vector<vector<Integer> >& int_vec);
      void set_E_LAW02(vector<vector<Real> >& real_vec);
      void set_LANG_LAW02(vector<vector<Integer> >& int_vec);
      void set_NL_LAW02(vector<vector<Integer> >& int_vec);
      void set_A_LAW02(vector<vector<vector<Real> > >& real_vec);
      void set_SPI_LAW05(vector<Real>& real_vec);
      void set_LIDP_LAW05(vector<Integer>& int_vec);
      void set_NE_LAW05(vector<Integer>& int_vec);
      void set_NBT_E_LAW05(vector<vector<Integer> >& int_vec);
      void set_INT_E_LAW05(vector<vector<Integer> >& int_vec);
      void set_E_LAW05(vector<vector<Real> >& real_vec);
      void set_LTP_LAW05(vector<vector<Integer> >& int_vec);
      void set_B_LAW05(vector<vector<vector<Real> > >& real_vec);
      void set_RA_LAW05(vector<vector<vector<Real> > >& real_vec);
      void set_IA_LAW05(vector<vector<vector<Real> > >& real_vec);
      void set_C_LAW05(vector<vector<vector<Real> > >& real_vec);
      void set_MU_LAW05(vector<vector<vector<Real> > >& real_vec);
      void set_P_LAW05(vector<vector<vector<Real> > >& real_vec);
      void set_APSX_LAW06(vector<Real>& real_vec);
      void set_NPSX_LAW06(vector<Integer>& int_vec);
      void set_NE_LAW07(vector<Integer>& int_vec);
      void set_NBT_E_LAW07(vector<vector<Integer> >& int_vec);
      void set_INT_E_LAW07(vector<vector<Integer> >& int_vec);
      void set_E_LAW07(vector<vector<Real> >& real_vec);
      void set_NMU_LAW07(vector<vector<Integer> >& int_vec);
      void set_NBT_MU_LAW07(vector<vector<vector<Integer> > >& int_vec);
      void set_INT_MU_LAW07(vector<vector<vector<Integer> > >& int_vec);
      void set_MU_LAW07(vector<vector<vector<Real> > >& real_vec);
      void set_NBT_F_LAW07(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_INT_F_LAW07(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_E_INT_F_LAW07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_F_TAB_LAW07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_NBRAGG(Integer& int_data);
      void set_NNE(Integer& int_data);
      void set_TEMP(Real& real_data);
      void set_EP(vector<vector<Real> >& real_vec);
      void set_PP(vector<vector<Real> >& real_vec);
      void set_EPM(vector<vector<vector<Real> > >& real_vec);
      void set_EN(vector<Real>& real_vec);
      void set_U(vector<vector<Real> >& real_vec);
  };
}

#endif // MF06_PARSER_H

