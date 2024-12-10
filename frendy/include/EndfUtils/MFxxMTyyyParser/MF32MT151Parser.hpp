#ifndef MF32MT151_PARSER_H
#define MF32MT151_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF32MT151Parser
  {
    private:
      ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no =  32;
      static const Integer mt_no = 151;

      static const Integer ner_max =    12;
      static const Integer np_max  = 10000;
      static const Integer nr_max  =    20;
      static const Integer nrs_max =  5000;

      vector<string> text;

      //Common data
      Real                              ZAR, AWR;      //Line No.01 (ZA -> ZAR)
      Integer                           NIS;

      vector<Real>                      ZAI, ABN;      //Line No.02
      vector<Integer>                   LFW, NER;
      vector<vector<Real> >             EL,  EH;       //Line No.03
      vector<vector<Integer> >          LRU, LRF, NRO, NAPS;

      //Common
      vector<vector<Real> >             SPI, AP;
      vector<vector<Integer> >          LAD, LCOMP, NLS, ISR;

      vector<vector<Real> >             DAP;
      vector<vector<vector<Real> > >    DAP_TAB;
      vector<vector<vector<vector<Real> > > >  DAP_LRF07;

      vector<vector<Real> >             AWRI, QX, APL;
      vector<vector<Integer> >          NSRS, NLRS, LRX;

      vector<vector<vector<Real> > >    AWRI_NLS;
      vector<vector<vector<Integer> > > L;

      vector<vector<vector<vector<vector<Real> > > > > V;

      vector<vector<Integer> >          NDIGIT, NNN, NM;
      vector<vector<vector<Integer> > > II, JJ;
      vector<vector<vector<vector<Integer> > > > KIJ;

      //LCOMP=0
      vector<vector<vector<vector<Real> > > > ER_LCOMP00,   AJ_LCOMP00,   GT_LCOMP00,   GN_LCOMP00;
      vector<vector<vector<vector<Real> > > > GG_LCOMP00,   GF_LCOMP00,   DE_LCOMP00,   DN_LCOMP00;
      vector<vector<vector<vector<Real> > > > DNDG_LCOMP00, DG_LCOMP00,   DNDF_LCOMP00, DGDF_LCOMP00;
      vector<vector<vector<vector<Real> > > > DF_LCOMP00,   DJDN_LCOMP00, DJDG_LCOMP00, DJDF_LCOMP00;
      vector<vector<vector<vector<Real> > > > DJ_LCOMP00;

      //LCOMP=1, LRF=1-4
      vector<vector<vector<Integer> > > MPAR_LCOMP01_LRF01;
      vector<vector<vector<vector<Real> > > > ER_LCOMP01_LRF01, AJ_LCOMP01_LRF01, GT_LCOMP01_LRF01;
      vector<vector<vector<vector<Real> > > > GN_LCOMP01_LRF01, GG_LCOMP01_LRF01, GF_LCOMP01_LRF01;

      vector<vector<vector<vector<Real> > > > ER_LCOMP01_LRF03, AJ_LCOMP01_LRF03,  GN_LCOMP01_LRF03;
      vector<vector<vector<vector<Real> > > > GG_LCOMP01_LRF03, GFA_LCOMP01_LRF03, GFB_LCOMP01_LRF03;

      vector<vector<vector<vector<Real> > > >
        DET_LCOMP01_LRF04, DWT_LCOMP01_LRF04, GRT_LCOMP01_LRF04, GIT_LCOMP01_LRF04,
        DEF_LCOMP01_LRF04, DWF_LCOMP01_LRF04, GRF_LCOMP01_LRF04, GIF_LCOMP01_LRF04,
        DEC_LCOMP01_LRF04, DWC_LCOMP01_LRF04, GRC_LCOMP01_LRF04, GIC_LCOMP01_LRF04;

      //LCOMP=1, LRF=7
      vector<vector<vector<Integer> > >                         NJSX_LCOMP01_LRF07;
      vector<vector<vector<vector<vector<Real> > > > >          ER_LCOMP01_LRF07;
      vector<vector<vector<vector<vector<vector<Real> > > > > > GAM_LCOMP01_LRF07;

      //LCOMP=2, LRF=1 or 2
      vector<vector<vector<Real> > >    ER_LCOMP02_LRF01,  AJ_LCOMP02_LRF01,  GT_LCOMP02_LRF01;
      vector<vector<vector<Real> > >    GN_LCOMP02_LRF01,  GG_LCOMP02_LRF01,  GF_LCOMP02_LRF01;
      vector<vector<vector<Real> > >    DER_LCOMP02_LRF01, DGN_LCOMP02_LRF01, DGG_LCOMP02_LRF01;
      vector<vector<vector<Real> > >    DGF_LCOMP02_LRF01;

      //LCOMP=2, LRF=3
      vector<vector<vector<Real> > >    ER_LCOMP02_LRF03,   AJ_LCOMP02_LRF03,   GN_LCOMP02_LRF03;
      vector<vector<vector<Real> > >    GG_LCOMP02_LRF03,   GFA_LCOMP02_LRF03,  GFB_LCOMP02_LRF03;
      vector<vector<vector<Real> > >    DER_LCOMP02_LRF03,  DGN_LCOMP02_LRF03,  DGG_LCOMP02_LRF03;
      vector<vector<vector<Real> > >    DGFA_LCOMP02_LRF03, DGFB_LCOMP02_LRF03;

      //LCOMP=2, LRF=7
      vector<vector<Integer> >          NJSX_LCOMP02_LRF07;
      vector<vector<vector<Real> > >    MA_LCOMP02_LRF07,   MB_LCOMP02_LRF07,   ZA_LCOMP02_LRF07;
      vector<vector<vector<Real> > >    ZB_LCOMP02_LRF07,   IA_LCOMP02_LRF07,   IB_LCOMP02_LRF07;
      vector<vector<vector<Real> > >    Q_LCOMP02_LRF07,    PNT_LCOMP02_LRF07,  SHF_LCOMP02_LRF07;
      vector<vector<vector<Real> > >    MT_LCOMP02_LRF07,   PA_LCOMP02_LRF07,   PB_LCOMP02_LRF07;

      vector<vector<vector<Real> > >    AJ_LCOMP02_LRF07, PJ_LCOMP02_LRF07;
      vector<vector<vector<vector<Real> > > > PPI_LCOMP02_LRF07, L_LCOMP02_LRF07,   SCH_LCOMP02_LRF07;
      vector<vector<vector<vector<Real> > > > BND_LCOMP02_LRF07, APE_LCOMP02_LRF07, APT_LCOMP02_LRF07;

      vector<vector<vector<vector<Real> > > >          ER_LCOMP02_LRF07,  DER_LCOMP02_LRF07;
      vector<vector<vector<vector<vector<Real> > > > > GAM_LCOMP02_LRF07, DGAM_LCOMP02_LRF07;

      //LRU=1
      vector<vector<vector<Integer> > > IDP_LRU01, LB_LRU01;
      vector<vector<vector<vector<Real> > > > E_K_LRU01;
      vector<vector<vector<vector<vector<Real> > > > > F_K_LRU01;

      //LRU=2
      vector<vector<vector<vector<Real> > > > D_LRU02,  AJ_LRU02, GNO_LRU02;
      vector<vector<vector<vector<Real> > > > GG_LRU02, GF_LRU02, GX_LRU02;
      vector<vector<Integer> >                MPAR_LRU02;
      vector<vector<vector<vector<Real> > > > RV_LRU02;


      //NRO!=0
      vector<vector<Integer> >          NI;
      vector<vector<vector<Integer> > > LB;
      vector<vector<vector<Integer> > > LT;
      vector<vector<vector<vector<Real> > > >          E_K, E_T;
      vector<vector<vector<vector<vector<Real> > > > > F_K, F_T;


      void store_data();

      void store_nro00(MultiParser& mp_obj, int& line_no, int& i, int& j);

      void store_lcomp00(MultiParser& mp_obj, int& line_no, int& i, int& j);

      void store_lcomp01_lrf01(MultiParser& mp_obj, int& line_no, int& i, int& j);
      void store_lcomp01_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j);

      void store_lcomp02_lrf01(MultiParser& mp_obj, int& line_no, int& i, int& j);
      void store_lcomp02_lrf03(MultiParser& mp_obj, int& line_no, int& i, int& j);
      void store_lcomp02_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j);

      void store_lcomp02_intg(MultiParser& mp_obj, int& line_no, int& i, int& j);

      void store_lru01(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k);
      void store_lru02(MultiParser& mp_obj, int& line_no, int& i, int& j);


      void store_nro01(MultiParser& mp_obj, int& line_no, int& i, int& j);

      void store_NI(MultiParser& mp_obj, int& line_no, int& i, int& j, int& k);

      void store_NI_lb00(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, int& i, int& j, int& k);
      void store_NI_lb05(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, int& i, int& j, int& k);
      void store_NI_lb06(vector<Real>& r_vec, vector<Integer>& i_vec, vector<Real>& e_vec, int& i, int& j, int& k);


      void resize_matrix_vec_first(int ele_no);
      void resize_matrix_vec_second(int i, int ele_no);

      void resize_matrix_vec_nro01(int i, int j, int ele_no);
      void resize_matrix_vec_nsrs( int i, int j);

      void clear_vector_array();

    public:
      //constructor
      MF32MT151Parser(void);

      //destructor
      virtual ~MF32MT151Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string> get_text();

      Integer        get_mat_no();

      Real                              get_ZAR();
      Real                              get_AWR();
      Integer                           get_NIS();

      vector<Real>                      get_ZAI();
      vector<Real>                      get_ABN();
      vector<Integer>                   get_LFW();
      vector<Integer>                   get_NER();
      vector<vector<Real> >             get_EL();
      vector<vector<Real> >             get_EH();
      vector<vector<Integer> >          get_LRU();
      vector<vector<Integer> >          get_LRF();
      vector<vector<Integer> >          get_NRO();
      vector<vector<Integer> >          get_NAPS();

      //Common
      vector<vector<Real> >             get_SPI();
      vector<vector<Real> >             get_AP();
      vector<vector<Integer> >          get_LAD();
      vector<vector<Integer> >          get_IFG();
      vector<vector<Integer> >          get_LCOMP();
      vector<vector<Integer> >          get_NLS();
      vector<vector<Integer> >          get_NJS(); //NLS -> NJS
      vector<vector<Integer> >          get_ISR();
      vector<vector<Real> >             get_AWRI();

      //LCOMP=0
      vector<vector<vector<Real> > >    get_AWRI_LCOMP00();
      vector<vector<vector<Integer> > > get_L_LCOMP00();
      vector<vector<Real> >             get_DAP_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_ER_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_AJ_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_GT_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_GN_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_GG_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_GF_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_DE_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_DN_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_DNDG_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_DG_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_DNDF_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_DGDF_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_DF_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_DJDN_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_DJDG_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_DJDF_LCOMP00();
      vector<vector<vector<vector<Real> > > > get_DJ_LCOMP00();

      //LCOMP=1, LRF=1 or 2
      vector<vector<Real> >             get_AWRI_LCOMP01_LRF01();
      vector<vector<Integer> >          get_NSRS_LCOMP01_LRF01();
      vector<vector<Integer> >          get_NLRS_LCOMP01_LRF01();
      vector<vector<Real> >             get_DAP_LCOMP01_LRF01();
      vector<vector<vector<Integer> > > get_MPAR_LCOMP01_LRF01();
      vector<vector<vector<vector<Real> > > > get_ER_LCOMP01_LRF01();
      vector<vector<vector<vector<Real> > > > get_AJ_LCOMP01_LRF01();
      vector<vector<vector<vector<Real> > > > get_GT_LCOMP01_LRF01();
      vector<vector<vector<vector<Real> > > > get_GN_LCOMP01_LRF01();
      vector<vector<vector<vector<Real> > > > get_GG_LCOMP01_LRF01();
      vector<vector<vector<vector<Real> > > > get_GF_LCOMP01_LRF01();
      vector<vector<vector<vector<vector<Real> > > > > get_V_LCOMP01_LRF01();

      //LCOMP=1, LRF=3
      vector<vector<vector<Real> > >    get_DAP_LCOMP01_LRF03();
      vector<vector<Real> >             get_AWRI_LCOMP01_LRF03();
      vector<vector<Integer> >          get_NSRS_LCOMP01_LRF03();
      vector<vector<Integer> >          get_NLRS_LCOMP01_LRF03();
      vector<vector<vector<Integer> > > get_MPAR_LCOMP01_LRF03();
      vector<vector<vector<vector<Real> > > > get_ER_LCOMP01_LRF03();
      vector<vector<vector<vector<Real> > > > get_AJ_LCOMP01_LRF03();
      vector<vector<vector<vector<Real> > > > get_GN_LCOMP01_LRF03();
      vector<vector<vector<vector<Real> > > > get_GG_LCOMP01_LRF03();
      vector<vector<vector<vector<Real> > > > get_GFA_LCOMP01_LRF03();
      vector<vector<vector<vector<Real> > > > get_GFB_LCOMP01_LRF03();
      vector<vector<vector<vector<vector<Real> > > > > get_V_LCOMP01_LRF03();

      //LCOMP=1, LRF=4
      vector<vector<Real> >             get_AWRI_LCOMP01_LRF04();
      vector<vector<Integer> >          get_NSRS_LCOMP01_LRF04();
      vector<vector<Integer> >          get_NLRS_LCOMP01_LRF04();
      vector<vector<Real> >             get_DAP_LCOMP01_LRF04();
      vector<vector<vector<Integer> > > get_MPAR_LCOMP01_LRF04();
      vector<vector<vector<vector<Real> > > > get_DET_LCOMP01_LRF04();
      vector<vector<vector<vector<Real> > > > get_DWT_LCOMP01_LRF04();
      vector<vector<vector<vector<Real> > > > get_GRT_LCOMP01_LRF04();
      vector<vector<vector<vector<Real> > > > get_GIT_LCOMP01_LRF04();
      vector<vector<vector<vector<Real> > > > get_DEF_LCOMP01_LRF04();
      vector<vector<vector<vector<Real> > > > get_DWF_LCOMP01_LRF04();
      vector<vector<vector<vector<Real> > > > get_GRF_LCOMP01_LRF04();
      vector<vector<vector<vector<Real> > > > get_GIF_LCOMP01_LRF04();
      vector<vector<vector<vector<Real> > > > get_DEC_LCOMP01_LRF04();
      vector<vector<vector<vector<Real> > > > get_DWC_LCOMP01_LRF04();
      vector<vector<vector<vector<Real> > > > get_GRC_LCOMP01_LRF04();
      vector<vector<vector<vector<Real> > > > get_GIC_LCOMP01_LRF04();
      vector<vector<vector<vector<vector<Real> > > > > get_V_LCOMP01_LRF04();

      //LCOMP=1, LRF=7
      vector<vector<vector<vector<Real> > > >  get_DAP_LCOMP01_LRF07();
      vector<vector<Real> >             get_AWRI_LCOMP01_LRF07();
      vector<vector<Integer> >          get_NSRS_LCOMP01_LRF07();
      vector<vector<Integer> >          get_NLRS_LCOMP01_LRF07();
      vector<vector<vector<Integer> > > get_NJSX_LCOMP01_LRF07();
      vector<vector<vector<vector<vector<Real> > > > > get_ER_LCOMP01_LRF07();
      vector<vector<vector<vector<vector<vector<Real> > > > > > get_GAM_LCOMP01_LRF07();
      vector<vector<vector<vector<vector<Real> > > > > get_V_LCOMP01_LRF07();

      //LCOMP=2, LRF=1 or 2
      vector<vector<Real> >             get_DAP_LCOMP02_LRF01();
      vector<vector<Real> >             get_AWRI_LCOMP02_LRF01();
      vector<vector<Real> >             get_QX_LCOMP02_LRF01();
      vector<vector<Integer> >          get_LRX_LCOMP02_LRF01();

      vector<vector<vector<Real> > >    get_ER_LCOMP02_LRF01();
      vector<vector<vector<Real> > >    get_AJ_LCOMP02_LRF01();
      vector<vector<vector<Real> > >    get_GT_LCOMP02_LRF01();
      vector<vector<vector<Real> > >    get_GN_LCOMP02_LRF01();
      vector<vector<vector<Real> > >    get_GG_LCOMP02_LRF01();
      vector<vector<vector<Real> > >    get_GF_LCOMP02_LRF01();
      vector<vector<vector<Real> > >    get_DER_LCOMP02_LRF01();
      vector<vector<vector<Real> > >    get_DGN_LCOMP02_LRF01();
      vector<vector<vector<Real> > >    get_DGG_LCOMP02_LRF01();
      vector<vector<vector<Real> > >    get_DGF_LCOMP02_LRF01();

      vector<vector<Integer> >          get_NDIGIT_LCOMP02_LRF01();
      vector<vector<Integer> >          get_NNN_LCOMP02_LRF01();
      vector<vector<Integer> >          get_NM_LCOMP02_LRF01();
      vector<vector<vector<Integer> > > get_II_LCOMP02_LRF01();
      vector<vector<vector<Integer> > > get_JJ_LCOMP02_LRF01();
      vector<vector<vector<vector<Integer> > > > get_KIJ_LCOMP02_LRF01();

      //LCOMP=2, LRF=3
      vector<vector<vector<Real> > >    get_DAP_LCOMP02_LRF03();
      vector<vector<Real> >             get_AWRI_LCOMP02_LRF03();
      vector<vector<Real> >             get_APL_LCOMP02_LRF03();
      vector<vector<vector<Real> > >    get_ER_LCOMP02_LRF03();
      vector<vector<vector<Real> > >    get_AJ_LCOMP02_LRF03();
      vector<vector<vector<Real> > >    get_GN_LCOMP02_LRF03();
      vector<vector<vector<Real> > >    get_GG_LCOMP02_LRF03();
      vector<vector<vector<Real> > >    get_GFA_LCOMP02_LRF03();
      vector<vector<vector<Real> > >    get_GFB_LCOMP02_LRF03();
      vector<vector<vector<Real> > >    get_DER_LCOMP02_LRF03();
      vector<vector<vector<Real> > >    get_DGN_LCOMP02_LRF03();
      vector<vector<vector<Real> > >    get_DGG_LCOMP02_LRF03();
      vector<vector<vector<Real> > >    get_DGFA_LCOMP02_LRF03();
      vector<vector<vector<Real> > >    get_DGFB_LCOMP02_LRF03();

      vector<vector<Integer> >          get_NDIGIT_LCOMP02_LRF03();
      vector<vector<Integer> >          get_NNN_LCOMP02_LRF03();
      vector<vector<Integer> >          get_NM_LCOMP02_LRF03();
      vector<vector<vector<Integer> > > get_II_LCOMP02_LRF03();
      vector<vector<vector<Integer> > > get_JJ_LCOMP02_LRF03();
      vector<vector<vector<vector<Integer> > > > get_KIJ_LCOMP02_LRF03();

      //LCOMP=2, LRF=7
      vector<vector<vector<vector<Real> > > >  get_DAP_LCOMP02_LRF07();
      vector<vector<Integer> >          get_NJSX_LCOMP02_LRF07();
      vector<vector<vector<Real> > >    get_MA_LCOMP02_LRF07();
      vector<vector<vector<Real> > >    get_MB_LCOMP02_LRF07();
      vector<vector<vector<Real> > >    get_ZA_LCOMP02_LRF07();
      vector<vector<vector<Real> > >    get_ZB_LCOMP02_LRF07();
      vector<vector<vector<Real> > >    get_IA_LCOMP02_LRF07();
      vector<vector<vector<Real> > >    get_IB_LCOMP02_LRF07();
      vector<vector<vector<Real> > >    get_Q_LCOMP02_LRF07();
      vector<vector<vector<Real> > >    get_PNT_LCOMP02_LRF07();
      vector<vector<vector<Real> > >    get_SHF_LCOMP02_LRF07();
      vector<vector<vector<Real> > >    get_MT_LCOMP02_LRF07();
      vector<vector<vector<Real> > >    get_PA_LCOMP02_LRF07();
      vector<vector<vector<Real> > >    get_PB_LCOMP02_LRF07();

      vector<vector<vector<Real> > >    get_AJ_LCOMP02_LRF07();
      vector<vector<vector<Real> > >    get_PJ_LCOMP02_LRF07();
      vector<vector<vector<vector<Real> > > > get_PPI_LCOMP02_LRF07();
      vector<vector<vector<vector<Real> > > > get_L_LCOMP02_LRF07();
      vector<vector<vector<vector<Real> > > > get_SCH_LCOMP02_LRF07();
      vector<vector<vector<vector<Real> > > > get_BND_LCOMP02_LRF07();
      vector<vector<vector<vector<Real> > > > get_APE_LCOMP02_LRF07();
      vector<vector<vector<vector<Real> > > > get_APT_LCOMP02_LRF07();

      vector<vector<vector<vector<Real> > > >          get_ER_LCOMP02_LRF07();
      vector<vector<vector<vector<Real> > > >          get_DER_LCOMP02_LRF07();
      vector<vector<vector<vector<vector<Real> > > > > get_GAM_LCOMP02_LRF07();
      vector<vector<vector<vector<vector<Real> > > > > get_DGAM_LCOMP02_LRF07();

      vector<vector<Integer> >          get_NDIGIT_LCOMP02_LRF07();
      vector<vector<Integer> >          get_NNN_LCOMP02_LRF07();
      vector<vector<Integer> >          get_NM_LCOMP02_LRF07();
      vector<vector<vector<Integer> > > get_II_LCOMP02_LRF07();
      vector<vector<vector<Integer> > > get_JJ_LCOMP02_LRF07();
      vector<vector<vector<vector<Integer> > > > get_KIJ_LCOMP02_LRF07();

      //LRU=1
      vector<vector<vector<Integer> > > get_IDP_LRU01();
      vector<vector<vector<Integer> > > get_LB_LRU01();
      vector<vector<vector<vector<Real> > > > get_E_K_LRU01();
      vector<vector<vector<vector<vector<Real> > > > > get_F_K_LRU01();

      //LRU=2
      vector<vector<vector<Real> > >    get_AWRI_LRU02();
      vector<vector<vector<Integer> > > get_L_LRU02();
      vector<vector<vector<vector<Real> > > > get_D_LRU02();
      vector<vector<vector<vector<Real> > > > get_AJ_LRU02();
      vector<vector<vector<vector<Real> > > > get_GNO_LRU02();
      vector<vector<vector<vector<Real> > > > get_GG_LRU02();
      vector<vector<vector<vector<Real> > > > get_GF_LRU02();
      vector<vector<vector<vector<Real> > > > get_GX_LRU02();
      vector<vector<Integer> >                get_MPAR_LRU02();
      vector<vector<vector<vector<Real> > > > get_RV_LRU02();


      //NRO!=0
      vector<vector<Integer> >          get_NI();
      vector<vector<vector<Integer> > > get_LB();
      vector<vector<vector<Integer> > > get_LT();
      vector<vector<vector<vector<Real> > > >          get_E_K();
      vector<vector<vector<vector<Real> > > >          get_E_T();
      vector<vector<vector<vector<vector<Real> > > > > get_F_K();
      vector<vector<vector<vector<vector<Real> > > > > get_F_T();

      vector<vector<vector<vector<Real> > > >          get_E_K_NER();
      vector<vector<vector<vector<Real> > > >          get_E_K_NEC();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_ZAR(Real& real_data);
      void set_AWR(Real& real_data);
      void set_NIS(Integer& int_data);
      void set_ZAI(vector<Real>& real_vec);
      void set_ABN(vector<Real>& real_vec);
      void set_LFW(vector<Integer>& int_vec);
      void set_NER(vector<Integer>& int_vec);
      void set_EL(vector<vector<Real> >& real_vec);
      void set_EH(vector<vector<Real> >& real_vec);
      void set_LRU(vector<vector<Integer> >& int_vec);
      void set_LRF(vector<vector<Integer> >& int_vec);
      void set_NRO(vector<vector<Integer> >& int_vec);
      void set_NAPS(vector<vector<Integer> >& int_vec);
      void set_SPI(vector<vector<Real> >& real_vec);
      void set_AP(vector<vector<Real> >& real_vec);
      void set_LAD(vector<vector<Integer> >& int_vec);
      void set_IFG(vector<vector<Integer> >& int_vec);
      void set_LCOMP(vector<vector<Integer> >& int_vec);
      void set_NLS(vector<vector<Integer> >& int_vec);
      void set_NJS(vector<vector<Integer> >& int_vec);
      void set_ISR(vector<vector<Integer> >& int_vec);
      void set_AWRI(vector<vector<Real> >& real_vec);
      void set_AWRI_LCOMP00(vector<vector<vector<Real> > >& real_vec);
      void set_L_LCOMP00(vector<vector<vector<Integer> > >& int_vec);
      void set_DAP_LCOMP00(vector<vector<Real> >& real_vec);
      void set_ER_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AJ_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GT_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GN_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GG_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GF_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DE_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DN_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DNDG_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DG_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DNDF_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DGDF_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DF_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DJDN_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DJDG_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DJDF_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DJ_LCOMP00(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AWRI_LCOMP01_LRF01(vector<vector<Real> >& real_vec);
      void set_NSRS_LCOMP01_LRF01(vector<vector<Integer> >& int_vec);
      void set_NLRS_LCOMP01_LRF01(vector<vector<Integer> >& int_vec);
      void set_DAP_LCOMP01_LRF01(vector<vector<Real> >& real_vec);
      void set_MPAR_LCOMP01_LRF01(vector<vector<vector<Integer> > >& int_vec);
      void set_ER_LCOMP01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AJ_LCOMP01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GT_LCOMP01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GN_LCOMP01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GG_LCOMP01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GF_LCOMP01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_V_LCOMP01_LRF01(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_DAP_LCOMP01_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_AWRI_LCOMP01_LRF03(vector<vector<Real> >& real_vec);
      void set_NSRS_LCOMP01_LRF03(vector<vector<Integer> >& int_vec);
      void set_NLRS_LCOMP01_LRF03(vector<vector<Integer> >& int_vec);
      void set_MPAR_LCOMP01_LRF03(vector<vector<vector<Integer> > >& int_vec);
      void set_ER_LCOMP01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AJ_LCOMP01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GN_LCOMP01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GG_LCOMP01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GFA_LCOMP01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GFB_LCOMP01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_V_LCOMP01_LRF03(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_AWRI_LCOMP01_LRF04(vector<vector<Real> >& real_vec);
      void set_NSRS_LCOMP01_LRF04(vector<vector<Integer> >& int_vec);
      void set_NLRS_LCOMP01_LRF04(vector<vector<Integer> >& int_vec);
      void set_DAP_LCOMP01_LRF04(vector<vector<Real> >& real_vec);
      void set_MPAR_LCOMP01_LRF04(vector<vector<vector<Integer> > >& int_vec);
      void set_DET_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DWT_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GRT_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GIT_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DEF_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DWF_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GRF_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GIF_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DEC_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DWC_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GRC_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GIC_LCOMP01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_V_LCOMP01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_DAP_LCOMP01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AWRI_LCOMP01_LRF07(vector<vector<Real> >& real_vec);
      void set_NSRS_LCOMP01_LRF07(vector<vector<Integer> >& int_vec);
      void set_NLRS_LCOMP01_LRF07(vector<vector<Integer> >& int_vec);
      void set_NJSX_LCOMP01_LRF07(vector<vector<vector<Integer> > >& int_vec);
      void set_ER_LCOMP01_LRF07(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_GAM_LCOMP01_LRF07(vector<vector<vector<vector<vector<vector<Real> > > > > >& real_vec);
      void set_V_LCOMP01_LRF07(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_DAP_LCOMP02_LRF01(vector<vector<Real> >& real_vec);
      void set_AWRI_LCOMP02_LRF01(vector<vector<Real> >& real_vec);
      void set_QX_LCOMP02_LRF01(vector<vector<Real> >& real_vec);
      void set_LRX_LCOMP02_LRF01(vector<vector<Integer> >& int_vec);
      void set_ER_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec);
      void set_AJ_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec);
      void set_GT_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec);
      void set_GN_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec);
      void set_GG_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec);
      void set_GF_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec);
      void set_DER_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec);
      void set_DGN_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec);
      void set_DGG_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec);
      void set_DGF_LCOMP02_LRF01(vector<vector<vector<Real> > >& real_vec);
      void set_NDIGIT_LCOMP02_LRF01(vector<vector<Integer> >& int_vec);
      void set_NNN_LCOMP02_LRF01(vector<vector<Integer> >& int_vec);
      void set_NM_LCOMP02_LRF01(vector<vector<Integer> >& int_vec);
      void set_II_LCOMP02_LRF01(vector<vector<vector<Integer> > >& int_vec);
      void set_JJ_LCOMP02_LRF01(vector<vector<vector<Integer> > >& int_vec);
      void set_KIJ_LCOMP02_LRF01(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_DAP_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_AWRI_LCOMP02_LRF03(vector<vector<Real> >& real_vec);
      void set_APL_LCOMP02_LRF03(vector<vector<Real> >& real_vec);
      void set_ER_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_AJ_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_GN_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_GG_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_GFA_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_GFB_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_DER_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_DGN_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_DGG_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_DGFA_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_DGFB_LCOMP02_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_NDIGIT_LCOMP02_LRF03(vector<vector<Integer> >& int_vec);
      void set_NNN_LCOMP02_LRF03(vector<vector<Integer> >& int_vec);
      void set_NM_LCOMP02_LRF03(vector<vector<Integer> >& int_vec);
      void set_II_LCOMP02_LRF03(vector<vector<vector<Integer> > >& int_vec);
      void set_JJ_LCOMP02_LRF03(vector<vector<vector<Integer> > >& int_vec);
      void set_KIJ_LCOMP02_LRF03(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_DAP_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_NJSX_LCOMP02_LRF07(vector<vector<Integer> >& int_vec);
      void set_MA_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_MB_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_ZA_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_ZB_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_IA_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_IB_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_Q_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_PNT_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_SHF_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_MT_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_PA_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_PB_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_AJ_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_PJ_LCOMP02_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_PPI_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_L_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_SCH_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_BND_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_APE_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_APT_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_ER_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_DER_LCOMP02_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GAM_LCOMP02_LRF07(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_DGAM_LCOMP02_LRF07(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_NDIGIT_LCOMP02_LRF07(vector<vector<Integer> >& int_vec);
      void set_NNN_LCOMP02_LRF07(vector<vector<Integer> >& int_vec);
      void set_NM_LCOMP02_LRF07(vector<vector<Integer> >& int_vec);
      void set_II_LCOMP02_LRF07(vector<vector<vector<Integer> > >& int_vec);
      void set_JJ_LCOMP02_LRF07(vector<vector<vector<Integer> > >& int_vec);
      void set_KIJ_LCOMP02_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_IDP_LRU01(vector<vector<vector<Integer> > >& int_vec);
      void set_LB_LRU01(vector<vector<vector<Integer> > >& int_vec);
      void set_E_K_LRU01(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_F_K_LRU01(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_AWRI_LRU02(vector<vector<vector<Real> > >& real_vec);
      void set_L_LRU02(vector<vector<vector<Integer> > >& int_vec);
      void set_D_LRU02(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AJ_LRU02(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GNO_LRU02(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GG_LRU02(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GF_LRU02(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GX_LRU02(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_MPAR_LRU02(vector<vector<Integer> >& int_vec);
      void set_RV_LRU02(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_NI(vector<vector<Integer> >& int_vec);
      void set_LB(vector<vector<vector<Integer> > >& int_vec);
      void set_LT(vector<vector<vector<Integer> > >& int_vec);
      void set_E_K(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_E_T(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_F_K(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_F_T(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_E_K_NER(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_E_K_NEC(vector<vector<vector<vector<Real> > > >& real_vec);
  };
}

#endif // MF32MT151_PARSER_H

