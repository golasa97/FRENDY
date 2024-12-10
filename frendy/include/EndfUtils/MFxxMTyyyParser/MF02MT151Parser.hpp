#ifndef MF02MT151_PARSER_H
#define MF02MT151_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF02MT151Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer mat_no;
      static const Integer mf_no =   2;
      static const Integer mt_no = 151;

      static const Integer ner_max =    12;
      static const Integer np_max  = 10000;
      static const Integer nr_max  =    20;
      static const Integer nrs_max =  5000;

      vector<string> text;

      //Common data
      Real                           ZAR, AWR;      //Line No.01 (ZA -> ZAR)
      Integer                        NIS;
      vector<Real>                   ZAI, ABN;      //Line No.02
      vector<Integer>                LFW, NER; 
      vector<vector<Real> >          EL,  EH;       //Line No.03
      vector<vector<Integer> >       LRU, LRF, NRO, NAPS;

      vector<vector<Real> >          SPI, AP;
      vector<vector<Integer> >       NLS;
      vector<vector<vector<Real> > > AWRI;

      //For NRO>0
      vector<vector<vector<Integer> > > NBT_AP_NRO,   INT_AP_NRO;
      vector<vector<vector<Real> > >    E_INT_AP_NRO, AP_TAB_NRO;

      //LRU=1, LRF=1 or 2
      vector<vector<vector<Real> > >    QX_LRU01_LRF01;
      vector<vector<vector<Integer> > > L_LRU01_LRF01,    LRX_LRU01_LRF01, NRS_LRU01_LRF01;
      vector<vector<vector<vector<Real> > > > ER_LRU01_LRF01, AJ_LRU01_LRF01, GT_LRU01_LRF01,
                                              GN_LRU01_LRF01, GG_LRU01_LRF01, GF_LRU01_LRF01;

      //LRU=1, LRF=3
      vector<vector<Integer> >          LAD_LRU01_LRF03,  NLSC_LRU01_LRF03;
      vector<vector<vector<Real> > >    APL_LRU01_LRF03;
      vector<vector<vector<Integer> > > L_LRU01_LRF03,    NRS_LRU01_LRF03;
      vector<vector<vector<vector<Real> > > > ER_LRU01_LRF03, AJ_LRU01_LRF03,  GN_LRU01_LRF03,
                                              GG_LRU01_LRF03, GFA_LRU01_LRF03, GFB_LRU01_LRF03;

      //LRU=1, LRF=4;
      vector<vector<Integer> >          LI_LRU01_LRF04,   NX_LRU01_LRF04;
      vector<vector<vector<Real> > >    AT_LRU01_LRF04, AF_LRU01_LRF04, AC_LRU01_LRF04;
      vector<vector<vector<Integer> > >          L_LRU01_LRF04,  NJS_LRU01_LRF04;
      vector<vector<vector<vector<Real> > > >    AJ_LRU01_LRF04;
      vector<vector<vector<vector<Integer> > > > NLJ_LRU01_LRF04;

      vector<vector<vector<vector<vector<Real> > > > > DET_LRU01_LRF04, DWT_LRU01_LRF04, GRT_LRU01_LRF04,
                                                       GIT_LRU01_LRF04, DEF_LRU01_LRF04, DWF_LRU01_LRF04,
                                                       GRF_LRU01_LRF04, GIF_LRU01_LRF04, DEC_LRU01_LRF04,
                                                       DWC_LRU01_LRF04, GRC_LRU01_LRF04, GIC_LRU01_LRF04;

      //LRU=1, LRF=7
      vector<vector<Integer> >          IFG_LRU01_LRF07, KRM_LRU01_LRF07, NJS_LRU01_LRF07, KRL_LRU01_LRF07;
      vector<vector<Integer> >          NPP_LRU01_LRF07;
      vector<vector<vector<Real> > >    MA_LRU01_LRF07,  MB_LRU01_LRF07,  ZA_LRU01_LRF07,  ZB_LRU01_LRF07,
                                        IA_LRU01_LRF07,  IB_LRU01_LRF07,  Q_LRU01_LRF07,   PNT_LRU01_LRF07,
                                        SHF_LRU01_LRF07, MT_LRU01_LRF07,  PA_LRU01_LRF07,  PB_LRU01_LRF07;

      vector<vector<vector<Real> > >             AJ_LRU01_LRF07,  PJ_LRU01_LRF07;
      vector<vector<vector<Integer> > >          KBK_LRU01_LRF07, KPS_LRU01_LRF07, NCH_LRU01_LRF07;
      vector<vector<vector<vector<Real> > > >    PPI_LRU01_LRF07, L_LRU01_LRF07,   SCH_LRU01_LRF07,
                                                 BND_LRU01_LRF07, APE_LRU01_LRF07, APT_LRU01_LRF07;

      vector<vector<vector<Integer> > >          NRS_LRU01_LRF07, NX_LRU01_LRF07;
      vector<vector<vector<vector<Real> > > >    ER_LRU01_LRF07;
      vector<vector<vector<vector<vector<Real> > > > > GAM_LRU01_LRF07;

      vector<vector<vector<Integer> > >          LBK_LRU01_LRF07, LCH_LRU01_LRF07;
      vector<vector<vector<vector<Integer> > > > NBT_RBR_LRU01_LRF07,   INT_RBR_LRU01_LRF07;
      vector<vector<vector<vector<Real> > > >    E_INT_RBR_LRU01_LRF07, RBR_TAB_LRU01_LRF07;
      vector<vector<vector<vector<Integer> > > > NBT_RBI_LRU01_LRF07,   INT_RBI_LRU01_LRF07;
      vector<vector<vector<vector<Real> > > >    E_INT_RBI_LRU01_LRF07, RBI_TAB_LRU01_LRF07;

      vector<vector<vector<Real> > >             ED_LRU01_LRF07, EU_LRU01_LRF07;
      vector<vector<vector<Real> > >             R0_LRU01_LRF07, R1_LRU01_LRF07, R2_LRU01_LRF07,
                                                 S0_LRU01_LRF07, S1_LRU01_LRF07, GA_LRU01_LRF07;

      vector<vector<vector<Integer> > >          LPS_LRU01_LRF07;
      vector<vector<vector<vector<Integer> > > > NBT_PSR_LRU01_LRF07,   INT_PSR_LRU01_LRF07;
      vector<vector<vector<vector<Real> > > >    E_INT_PSR_LRU01_LRF07, PSR_TAB_LRU01_LRF07;
      vector<vector<vector<vector<Integer> > > > NBT_PSI_LRU01_LRF07,   INT_PSI_LRU01_LRF07;
      vector<vector<vector<vector<Real> > > >    E_INT_PSI_LRU01_LRF07, PSI_TAB_LRU01_LRF07;

      //LRU=2
      vector<vector<Integer> >          LSSF_LRU02;
      vector<vector<vector<Integer> > > L_LRU02,    NJS_LRU02;

      //LRU=2, Case A
      vector<vector<vector<vector<Real> > > > D_LRU02_A,   AJ_LRU02_A,  AMUN_LRU02_A,
                                              GNO_LRU02_A, GG_LRU02_A;

      //LRU=2, Case B
      vector<vector<Integer> >                   NE_LRU02_B;
      vector<vector<vector<Real> > >             ES_LRU02_B;
      vector<vector<vector<vector<Integer> > > > MUF_LRU02_B;
      vector<vector<vector<vector<Real> > > >    D_LRU02_B,   AJ_LRU02_B,  AMUN_LRU02_B,
                                                 GNO_LRU02_B, GG_LRU02_B;
      vector<vector<vector<vector<vector<Real> > > > > GF_LRU02_B;

      //LRU=2, Case C
      vector<vector<vector<vector<Real> > > >    AJ_LRU02_C;
      vector<vector<vector<vector<Integer> > > > INT_LRU02_C,  NE_LRU02_C;
      vector<vector<vector<vector<Real> > > >    AMUX_LRU02_C, AMUN_LRU02_C, AMUG_LRU02_C, AMUF_LRU02_C;
      vector<vector<vector<vector<vector<Real> > > > > ES_LRU02_C,  D_LRU02_C,  GX_LRU02_C,
                                                       GNO_LRU02_C, GG_LRU02_C, GF_LRU02_C;

      void store_data();
      void store_lru00(MultiParser& mp_obj, int& line_no, int& i, int& j);
      void store_lru01_lrf01_02(MultiParser& mp_obj, int& line_no, int& i, int& j);
      void store_lru01_lrf03(MultiParser& mp_obj, int& line_no, int& i, int& j);
      void store_lru01_lrf04(MultiParser& mp_obj, int& line_no, int& i, int& j);
      void store_lru01_lrf07(MultiParser& mp_obj, int& line_no, int& i, int& j);
      void store_lru01_lrf07_kbk(MultiParser& mp_obj, int& line_no, int& i, int& j, int& njs);
      void store_lru01_lrf07_kps(MultiParser& mp_obj, int& line_no, int& i, int& j, int& njs);

      void store_lru02(MultiParser& mp_obj, int& line_no, int& i, int& j);
      void store_lru02_a(MultiParser& mp_obj, int& line_no, int& i, int& j);
      void store_lru02_b(MultiParser& mp_obj, int& line_no, int& i, int& j);
      void store_lru02_c(MultiParser& mp_obj, int& line_no, int& i, int& j);

      void store_nro(MultiParser& mp_obj, int& line_no, int& i, int& j);

      void resize_matrix_vec_first(int ele_no);
      void resize_matrix_vec_second(int i, int ele_no);
      void resize_matrix_vec_lru01_lrf04(int i, int j, int k, int k_max, int l_max);
      void resize_matrix_vec_lru01_lrf07(int i, int j, int ele_no);
      void resize_matrix_vec_lru02_a(int i, int j, int ele_no);
      void resize_matrix_vec_lru02_b(int i, int j, int ele_no);
      void resize_matrix_vec_lru02_c(int i, int j, int k, int k_max, int l_max);

      void init_multi_array_lru01_lrf07(int i, int j, int k_max);

      void clear_vector_array();

      void check_spin_data();
      void check_energy_range();

    public:
      //constructor
      MF02MT151Parser(void);

      //destructor
      virtual ~MF02MT151Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string> get_text();

      Integer        get_mat_no();

      Real                                             get_ZAR();
      Real                                             get_AWR(); 
      Integer                                          get_NIS();
      vector<Real>                                     get_ZAI(); 
      vector<Real>                                     get_ABN(); 
      vector<Integer>                                  get_LFW(); 
      vector<Integer>                                  get_NER(); 
      vector<vector<Real> >                            get_EL(); 
      vector<vector<Real> >                            get_EH(); 
      vector<vector<Integer> >                         get_LRU();
      vector<vector<Integer> >                         get_LRF();
      vector<vector<Integer> >                         get_NRO();
      vector<vector<Integer> >                         get_NAPS();

      vector<vector<Real> >                            get_SPI();
      vector<vector<Real> >                            get_AP();
      vector<vector<Integer> >                         get_NLS();
      vector<vector<vector<Real> > >                   get_AWRI();

      //NRO>0
      vector<vector<vector<Integer> > >                get_NBT_AP_NRO();
      vector<vector<vector<Integer> > >                get_INT_AP_NRO();
      vector<vector<vector<Real> > >                   get_E_INT_AP_NRO();
      vector<vector<vector<Real> > >                   get_AP_TAB_NRO();

      //LRU=1, LRF=1 or 2
      vector<vector<vector<Real> > >                   get_QX_LRU01_LRF01();
      vector<vector<vector<Integer> > >                get_L_LRU01_LRF01();
      vector<vector<vector<Integer> > >                get_LRX_LRU01_LRF01();
      vector<vector<vector<Integer> > >                get_NRS_LRU01_LRF01();
      vector<vector<vector<vector<Real> > > >          get_ER_LRU01_LRF01();
      vector<vector<vector<vector<Real> > > >          get_AJ_LRU01_LRF01();
      vector<vector<vector<vector<Real> > > >          get_GT_LRU01_LRF01();
      vector<vector<vector<vector<Real> > > >          get_GN_LRU01_LRF01();
      vector<vector<vector<vector<Real> > > >          get_GG_LRU01_LRF01();
      vector<vector<vector<vector<Real> > > >          get_GF_LRU01_LRF01();

      vector<vector<vector<Real> > >                   get_QX_LRU01_LRF02();
      vector<vector<vector<Integer> > >                get_L_LRU01_LRF02();
      vector<vector<vector<Integer> > >                get_LRX_LRU01_LRF02();
      vector<vector<vector<Integer> > >                get_NRS_LRU01_LRF02();
      vector<vector<vector<vector<Real> > > >          get_ER_LRU01_LRF02();
      vector<vector<vector<vector<Real> > > >          get_AJ_LRU01_LRF02();
      vector<vector<vector<vector<Real> > > >          get_GT_LRU01_LRF02();
      vector<vector<vector<vector<Real> > > >          get_GN_LRU01_LRF02();
      vector<vector<vector<vector<Real> > > >          get_GG_LRU01_LRF02();
      vector<vector<vector<vector<Real> > > >          get_GF_LRU01_LRF02();

      //LRU=1, LRF=3
      vector<vector<Integer> >                         get_LAD_LRU01_LRF03();
      vector<vector<Integer> >                         get_NLSC_LRU01_LRF03();
      vector<vector<vector<Real> > >                   get_APL_LRU01_LRF03();
      vector<vector<vector<Integer> > >                get_L_LRU01_LRF03();
      vector<vector<vector<Integer> > >                get_NRS_LRU01_LRF03();
      vector<vector<vector<vector<Real> > > >          get_ER_LRU01_LRF03();
      vector<vector<vector<vector<Real> > > >          get_AJ_LRU01_LRF03();
      vector<vector<vector<vector<Real> > > >          get_GN_LRU01_LRF03();
      vector<vector<vector<vector<Real> > > >          get_GG_LRU01_LRF03();
      vector<vector<vector<vector<Real> > > >          get_GFA_LRU01_LRF03();
      vector<vector<vector<vector<Real> > > >          get_GFB_LRU01_LRF03();

      //LRU=1, LRF=4
      vector<vector<Integer> >                         get_LI_LRU01_LRF04();
      vector<vector<Integer> >                         get_NX_LRU01_LRF04();
      vector<vector<vector<Real> > >                   get_AT_LRU01_LRF04();
      vector<vector<vector<Real> > >                   get_AF_LRU01_LRF04();
      vector<vector<vector<Real> > >                   get_AC_LRU01_LRF04();
      vector<vector<vector<Integer> > >                get_L_LRU01_LRF04();
      vector<vector<vector<Integer> > >                get_NJS_LRU01_LRF04();
      vector<vector<vector<vector<Real> > > >          get_AJ_LRU01_LRF04();
      vector<vector<vector<vector<Integer> > > >       get_NLJ_LRU01_LRF04();

      vector<vector<vector<vector<vector<Real> > > > > get_DET_LRU01_LRF04();
      vector<vector<vector<vector<vector<Real> > > > > get_DWT_LRU01_LRF04();
      vector<vector<vector<vector<vector<Real> > > > > get_GRT_LRU01_LRF04();
      vector<vector<vector<vector<vector<Real> > > > > get_GIT_LRU01_LRF04();
      vector<vector<vector<vector<vector<Real> > > > > get_DEF_LRU01_LRF04();
      vector<vector<vector<vector<vector<Real> > > > > get_DWF_LRU01_LRF04();
      vector<vector<vector<vector<vector<Real> > > > > get_GRF_LRU01_LRF04();
      vector<vector<vector<vector<vector<Real> > > > > get_GIF_LRU01_LRF04();
      vector<vector<vector<vector<vector<Real> > > > > get_DEC_LRU01_LRF04();
      vector<vector<vector<vector<vector<Real> > > > > get_DWC_LRU01_LRF04();
      vector<vector<vector<vector<vector<Real> > > > > get_GRC_LRU01_LRF04();
      vector<vector<vector<vector<vector<Real> > > > > get_GIC_LRU01_LRF04();

      //LRU=1, LRF=7
      vector<vector<Integer> >                         get_IFG_LRU01_LRF07();
      vector<vector<Integer> >                         get_KRM_LRU01_LRF07();
      vector<vector<Integer> >                         get_NJS_LRU01_LRF07();
      vector<vector<Integer> >                         get_KRL_LRU01_LRF07();
      vector<vector<Integer> >                         get_NPP_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_MA_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_MB_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_ZA_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_ZB_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_IA_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_IB_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_Q_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_PNT_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_SHF_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_MT_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_PA_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_PB_LRU01_LRF07();

      vector<vector<vector<Real> > >                   get_AJ_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_PJ_LRU01_LRF07();
      vector<vector<vector<Integer> > >                get_KBK_LRU01_LRF07();
      vector<vector<vector<Integer> > >                get_KPS_LRU01_LRF07();
      vector<vector<vector<Integer> > >                get_NCH_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_PPI_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_L_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_SCH_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_BND_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_APE_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_APT_LRU01_LRF07();

      vector<vector<vector<Integer> > >                get_NRS_LRU01_LRF07();
      vector<vector<vector<Integer> > >                get_NX_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_ER_LRU01_LRF07();
      vector<vector<vector<vector<vector<Real> > > > > get_GAM_LRU01_LRF07();

      vector<vector<vector<Integer> > >                get_LCH_LRU01_LRF07();
      vector<vector<vector<Integer> > >                get_LBK_LRU01_LRF07();
      vector<vector<vector<vector<Integer> > > >       get_NBT_RBR_LRU01_LRF07();
      vector<vector<vector<vector<Integer> > > >       get_INT_RBR_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_E_INT_RBR_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_RBR_TAB_LRU01_LRF07();
      vector<vector<vector<vector<Integer> > > >       get_NBT_RBI_LRU01_LRF07();
      vector<vector<vector<vector<Integer> > > >       get_INT_RBI_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_E_INT_RBI_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_RBI_TAB_LRU01_LRF07();

      vector<vector<vector<Real> > >                   get_ED_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_EU_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_R0_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_R1_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_R2_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_S0_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_S1_LRU01_LRF07();
      vector<vector<vector<Real> > >                   get_GA_LRU01_LRF07();

      vector<vector<vector<Integer> > >                get_LPS_LRU01_LRF07();
      vector<vector<vector<vector<Integer> > > >       get_NBT_PSR_LRU01_LRF07();
      vector<vector<vector<vector<Integer> > > >       get_INT_PSR_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_E_INT_PSR_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_PSR_TAB_LRU01_LRF07();
      vector<vector<vector<vector<Integer> > > >       get_NBT_PSI_LRU01_LRF07();
      vector<vector<vector<vector<Integer> > > >       get_INT_PSI_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_E_INT_PSI_LRU01_LRF07();
      vector<vector<vector<vector<Real> > > >          get_PSI_TAB_LRU01_LRF07();

      //LRU=2
      vector<vector<Integer> >                         get_LSSF_LRU02();
      vector<vector<vector<Integer> > >                get_L_LRU02();
      vector<vector<vector<Integer> > >                get_NJS_LRU02();

      //LRU=2, Case A
      vector<vector<vector<vector<Real> > > >          get_D_LRU02_A();
      vector<vector<vector<vector<Real> > > >          get_AJ_LRU02_A();
      vector<vector<vector<vector<Real> > > >          get_AMUN_LRU02_A();
      vector<vector<vector<vector<Real> > > >          get_GNO_LRU02_A();
      vector<vector<vector<vector<Real> > > >          get_GG_LRU02_A();

      //LRU=2, Case B
      vector<vector<Integer> >                         get_NE_LRU02_B();
      vector<vector<vector<Real> > >                   get_ES_LRU02_B();
      vector<vector<vector<vector<Integer> > > >       get_MUF_LRU02_B();
      vector<vector<vector<vector<Real> > > >          get_D_LRU02_B();
      vector<vector<vector<vector<Real> > > >          get_AJ_LRU02_B();
      vector<vector<vector<vector<Real> > > >          get_AMUN_LRU02_B();
      vector<vector<vector<vector<Real> > > >          get_GNO_LRU02_B();
      vector<vector<vector<vector<Real> > > >          get_GG_LRU02_B();
      vector<vector<vector<vector<vector<Real> > > > > get_GF_LRU02_B();

      //LRU=2, Case C
      vector<vector<vector<vector<Real> > > >          get_AJ_LRU02_C();
      vector<vector<vector<vector<Integer> > > >       get_INT_LRU02_C();
      vector<vector<vector<vector<Integer> > > >       get_NE_LRU02_C();
      vector<vector<vector<vector<Real> > > >          get_AMUX_LRU02_C();
      vector<vector<vector<vector<Real> > > >          get_AMUN_LRU02_C();
      vector<vector<vector<vector<Real> > > >          get_AMUG_LRU02_C();
      vector<vector<vector<vector<Real> > > >          get_AMUF_LRU02_C();
      vector<vector<vector<vector<vector<Real> > > > > get_ES_LRU02_C();
      vector<vector<vector<vector<vector<Real> > > > > get_D_LRU02_C();
      vector<vector<vector<vector<vector<Real> > > > > get_GX_LRU02_C();
      vector<vector<vector<vector<vector<Real> > > > > get_GNO_LRU02_C();
      vector<vector<vector<vector<vector<Real> > > > > get_GG_LRU02_C();
      vector<vector<vector<vector<vector<Real> > > > > get_GF_LRU02_C();

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
      void set_NLS(vector<vector<Integer> >& int_vec);
      void set_AWRI(vector<vector<vector<Real> > >& real_vec);

      //NRO>0
      void set_NBT_AP_NRO(vector<vector<vector<Integer> > >& int_vec);
      void set_INT_AP_NRO(vector<vector<vector<Integer> > >& int_vec);
      void set_E_INT_AP_NRO(vector<vector<vector<Real> > >& real_vec);
      void set_AP_TAB_NRO(vector<vector<vector<Real> > >& real_vec);

      //LRU=1, LRF=1 or 2
      void set_QX_LRU01_LRF01(vector<vector<vector<Real> > >& real_vec);
      void set_L_LRU01_LRF01(vector<vector<vector<Integer> > >& int_vec);
      void set_LRX_LRU01_LRF01(vector<vector<vector<Integer> > >& int_vec);
      void set_NRS_LRU01_LRF01(vector<vector<vector<Integer> > >& int_vec);
      void set_ER_LRU01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AJ_LRU01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GT_LRU01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GN_LRU01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GG_LRU01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GF_LRU01_LRF01(vector<vector<vector<vector<Real> > > >& real_vec);

      //LRU=1, LRF=3
      void set_LAD_LRU01_LRF03(vector<vector<Integer> >& int_vec);
      void set_NLSC_LRU01_LRF03(vector<vector<Integer> >& int_vec);
      void set_APL_LRU01_LRF03(vector<vector<vector<Real> > >& real_vec);
      void set_L_LRU01_LRF03(vector<vector<vector<Integer> > >& int_vec);
      void set_NRS_LRU01_LRF03(vector<vector<vector<Integer> > >& int_vec);
      void set_ER_LRU01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AJ_LRU01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GN_LRU01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GG_LRU01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GFA_LRU01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GFB_LRU01_LRF03(vector<vector<vector<vector<Real> > > >& real_vec);

      //LRU=1, LRF=4
      void set_LI_LRU01_LRF04(vector<vector<Integer> >& int_vec);
      void set_NX_LRU01_LRF04(vector<vector<Integer> >& int_vec);
      void set_AT_LRU01_LRF04(vector<vector<vector<Real> > >& real_vec);
      void set_AF_LRU01_LRF04(vector<vector<vector<Real> > >& real_vec);
      void set_AC_LRU01_LRF04(vector<vector<vector<Real> > >& real_vec);
      void set_L_LRU01_LRF04(vector<vector<vector<Integer> > >& int_vec);
      void set_NJS_LRU01_LRF04(vector<vector<vector<Integer> > >& int_vec);
      void set_AJ_LRU01_LRF04(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_NLJ_LRU01_LRF04(vector<vector<vector<vector<Integer> > > >& int_vec);

      void set_DET_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_DWT_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_GRT_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_GIT_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_DEF_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_DWF_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_GRF_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_GIF_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_DEC_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_DWC_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_GRC_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_GIC_LRU01_LRF04(vector<vector<vector<vector<vector<Real> > > > >& real_vec);

      //LRU=1, LRF=7
      void set_IFG_LRU01_LRF07(vector<vector<Integer> >& int_vec);
      void set_KRM_LRU01_LRF07(vector<vector<Integer> >& int_vec);
      void set_NJS_LRU01_LRF07(vector<vector<Integer> >& int_vec);
      void set_KRL_LRU01_LRF07(vector<vector<Integer> >& int_vec);
      void set_NPP_LRU01_LRF07(vector<vector<Integer> >& int_vec);
      void set_MA_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_MB_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_ZA_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_ZB_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_IA_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_IB_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_Q_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_PNT_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_SHF_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_MT_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_PA_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_PB_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);

      void set_AJ_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_PJ_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_KBK_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec);
      void set_KPS_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec);
      void set_NCH_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec);
      void set_PPI_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_L_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_SCH_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_BND_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_APE_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_APT_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);

      void set_NRS_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec);
      void set_NX_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec);
      void set_ER_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GAM_LRU01_LRF07(vector<vector<vector<vector<vector<Real> > > > >& real_vec);

      void set_LCH_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec);
      void set_LBK_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec);
      void set_NBT_RBR_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_INT_RBR_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_E_INT_RBR_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_RBR_TAB_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_NBT_RBI_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_INT_RBI_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_E_INT_RBI_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_RBI_TAB_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);

      void set_ED_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_EU_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_R0_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_R1_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_R2_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_S0_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_S1_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);
      void set_GA_LRU01_LRF07(vector<vector<vector<Real> > >& real_vec);

      void set_LPS_LRU01_LRF07(vector<vector<vector<Integer> > >& int_vec);
      void set_NBT_PSR_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_INT_PSR_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_E_INT_PSR_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_PSR_TAB_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_NBT_PSI_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_INT_PSI_LRU01_LRF07(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_E_INT_PSI_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_PSI_TAB_LRU01_LRF07(vector<vector<vector<vector<Real> > > >& real_vec);

      //LRU=2
      void set_LSSF_LRU02(vector<vector<Integer> >& int_vec);
      void set_L_LRU02(vector<vector<vector<Integer> > >& int_vec);
      void set_NJS_LRU02(vector<vector<vector<Integer> > >& int_vec);

      //LRU=2, Case A
      void set_D_LRU02_A(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AJ_LRU02_A(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AMUN_LRU02_A(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GNO_LRU02_A(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GG_LRU02_A(vector<vector<vector<vector<Real> > > >& real_vec);

      //LRU=2, Case B
      void set_NE_LRU02_B(vector<vector<Integer> >& int_vec);
      void set_ES_LRU02_B(vector<vector<vector<Real> > >& real_vec);
      void set_MUF_LRU02_B(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_D_LRU02_B(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AJ_LRU02_B(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AMUN_LRU02_B(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GNO_LRU02_B(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GG_LRU02_B(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_GF_LRU02_B(vector<vector<vector<vector<vector<Real> > > > >& real_vec);

      //LRU=2, Case C
      void set_AJ_LRU02_C(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_INT_LRU02_C(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_NE_LRU02_C(vector<vector<vector<vector<Integer> > > >& int_vec);
      void set_AMUX_LRU02_C(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AMUN_LRU02_C(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AMUG_LRU02_C(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_AMUF_LRU02_C(vector<vector<vector<vector<Real> > > >& real_vec);
      void set_ES_LRU02_C(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_D_LRU02_C(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_GX_LRU02_C(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_GNO_LRU02_C(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_GG_LRU02_C(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
      void set_GF_LRU02_C(vector<vector<vector<vector<vector<Real> > > > >& real_vec);
  };
}

#endif // MF02MT151_PARSER_H
