#ifndef MF08MT457_PARSER_H
#define MF08MT457_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF08MT457Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =   8;
      static const Integer mt_no  = 457;

      vector<string> text;

      Real                     ZA,  AWR;      //Line No.01
      Integer                  LIS, LISO, NST, NSP;

      Real                     T_HALF, D_T_HALF;
      vector<Real>             E_X,    D_E_X;

      Real                     SPI,   PAR;
      vector<Real>             RTYP0, RFS, Q, D_Q, BR, D_BR;

      vector<Integer>          NER, LCON;
      vector<Real>             STYP;
      vector<Real>             FD, D_FD, ER_AV, D_ER_AV, FC, D_FC;

      vector<vector<Real> >    ER,   D_ER;
      vector<vector<Real> >    RTYP1, TYPE,   RI,   D_RI,   RIS,  D_RIS;
      vector<vector<Real> >    RICC,  D_RICC, RICK, D_RICK, RICL, D_RICL;

      vector<Real>             RTYP2;
      vector<Integer>          LCOV;
      vector<vector<Integer> > NBT_RP,   INT_RP;
      vector<vector<Real> >    E_INT_RP, RP_TAB;

      vector<Integer>          LB;
      vector<vector<Real> >    E_K, F_K;

      void store_data();
      void store_nst00(MultiParser& mp_obj, int& line_no);
      void store_nst01(MultiParser& mp_obj, int& line_no);

      void resize_matrix();

    public:
      //constructor
      MF08MT457Parser(void);

      //destructor
      virtual ~MF08MT457Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();

      Real                     get_ZA();
      Real                     get_AWR();

      Integer                  get_LIS();
      Integer                  get_LISO();
      Integer                  get_NST();
      Integer                  get_NSP();

      Real                     get_T_HALF();
      Real                     get_D_T_HALF();
      vector<Real>             get_E_X();
      vector<Real>             get_D_E_X();

      Real                     get_SPI();
      Real                     get_PAR();
      vector<Real>             get_RTYP0();
      vector<Real>             get_RFS();
      vector<Real>             get_Q();
      vector<Real>             get_D_Q();
      vector<Real>             get_BR();
      vector<Real>             get_D_BR();

      vector<Real>             get_STYP();
      vector<Integer>          get_LCON();
      vector<Integer>          get_NER();
      vector<Real>             get_FD();
      vector<Real>             get_D_FD();
      vector<Real>             get_ER_AV();
      vector<Real>             get_D_ER_AV();
      vector<Real>             get_FC();
      vector<Real>             get_D_FC();

      vector<vector<Real> >    get_ER();
      vector<vector<Real> >    get_D_ER();
      vector<vector<Real> >    get_RTYP1();
      vector<vector<Real> >    get_TYPE();
      vector<vector<Real> >    get_RI();
      vector<vector<Real> >    get_D_RI();
      vector<vector<Real> >    get_RIS();
      vector<vector<Real> >    get_D_RIS();
      vector<vector<Real> >    get_RICC();
      vector<vector<Real> >    get_D_RICC();
      vector<vector<Real> >    get_RICK();
      vector<vector<Real> >    get_D_RICK();
      vector<vector<Real> >    get_RICL();
      vector<vector<Real> >    get_D_RICL();

      vector<Real>             get_RTYP2();
      vector<Integer>          get_LCOV();
      vector<vector<Integer> > get_NBT_RP();
      vector<vector<Integer> > get_INT_RP();
      vector<vector<Real> >    get_E_INT_RP();
      vector<vector<Real> >    get_RP_TAB();

      vector<Integer>          get_LB();
      vector<vector<Real> >    get_E_K();
      vector<vector<Real> >    get_F_K();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LIS(Integer& int_data);
      void set_LISO(Integer& int_data);
      void set_NST(Integer& int_data);
      void set_NSP(Integer& int_data);
      void set_T_HALF(Real& real_data);
      void set_D_T_HALF(Real& real_data);
      void set_E_X(vector<Real>& real_vec);
      void set_D_E_X(vector<Real>& real_vec);
      void set_SPI(Real& real_data);
      void set_PAR(Real& real_data);
      void set_RTYP0(vector<Real>& real_vec);
      void set_RFS(vector<Real>& real_vec);
      void set_Q(vector<Real>& real_vec);
      void set_D_Q(vector<Real>& real_vec);
      void set_BR(vector<Real>& real_vec);
      void set_D_BR(vector<Real>& real_vec);
      void set_STYP(vector<Real>& real_vec);
      void set_LCON(vector<Integer>& int_vec);
      void set_NER(vector<Integer>& int_vec);
      void set_FD(vector<Real>& real_vec);
      void set_D_FD(vector<Real>& real_vec);
      void set_ER_AV(vector<Real>& real_vec);
      void set_D_ER_AV(vector<Real>& real_vec);
      void set_FC(vector<Real>& real_vec);
      void set_D_FC(vector<Real>& real_vec);
      void set_ER(vector<vector<Real> >& real_vec);
      void set_D_ER(vector<vector<Real> >& real_vec);
      void set_RTYP1(vector<vector<Real> >& real_vec);
      void set_TYPE(vector<vector<Real> >& real_vec);
      void set_RI(vector<vector<Real> >& real_vec);
      void set_D_RI(vector<vector<Real> >& real_vec);
      void set_RIS(vector<vector<Real> >& real_vec);
      void set_D_RIS(vector<vector<Real> >& real_vec);
      void set_RICC(vector<vector<Real> >& real_vec);
      void set_D_RICC(vector<vector<Real> >& real_vec);
      void set_RICK(vector<vector<Real> >& real_vec);
      void set_D_RICK(vector<vector<Real> >& real_vec);
      void set_RICL(vector<vector<Real> >& real_vec);
      void set_D_RICL(vector<vector<Real> >& real_vec);
      void set_RTYP2(vector<Real>& real_vec);
      void set_LCOV(vector<Integer>& int_vec);
      void set_NBT_RP(vector<vector<Integer> >& int_vec);
      void set_INT_RP(vector<vector<Integer> >& int_vec);
      void set_E_INT_RP(vector<vector<Real> >& real_vec);
      void set_RP_TAB(vector<vector<Real> >& real_vec);
      void set_LB(vector<Integer>& int_vec);
      void set_E_K(vector<vector<Real> >& real_vec);
      void set_F_K(vector<vector<Real> >& real_vec);
  };
}

#endif // MF08MT457_PARSER_H

