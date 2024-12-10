#ifndef MF01MT458_PARSER_H
#define MF01MT458_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF01MT458Parser
  {
    private:
      frendy::ErrorManager err_obj;
      frendy::MultiParser  mp_obj;

      Integer mat_no;
      static const Integer mf_no =   1;
      static const Integer mt_no = 458;

      vector<string> text;
      Integer        line_no;

      //Line No.01
      Real    ZA, AWR;
      Integer LFC, NFC;

      //Line No.02
      Integer NPLY,  N1,  N2;

      vector<Real>    D_EFR, D_ENP, D_END, D_EGP, D_EGD, D_EB, D_ENU, D_ER, D_ET;
      vector<Real>      EFR,   ENP,   END,   EGP,   EGD,   EB,   ENU,   ER,   ET;

      //Line No.03
      vector<Integer>          LDRV, IFC;
      vector<vector<Integer> > NBT_EIFC,   INT_EIFC;
      vector<vector<Real> >    E_INT_EIFC, EIFC_TAB;

      void store_data();
      void store_polynomial_evaluation();
      void store_tabular_evaluation();

      void set_energy_independent_data(Integer NPLY, vector<Real>& real_data);

    public:
      //constructor
      MF01MT458Parser(void);

      //destructor
      virtual ~MF01MT458Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string> get_text();

      Integer        get_mat_no();

      //Getter at line No.01
      Real           get_ZA();
      Real           get_AWR();
      Integer        get_LFC();
      Integer        get_NFC();

      //Getter at line No.02
      Integer        get_NPLY();
      Integer        get_N1();
      Integer        get_N2();

      vector<Real>   get_EFR();
      vector<Real>   get_ENP();
      vector<Real>   get_END();
      vector<Real>   get_EGP();
      vector<Real>   get_EGD();
      vector<Real>   get_EB();
      vector<Real>   get_ENU();
      vector<Real>   get_ER();
      vector<Real>   get_ET();

      vector<Real>   get_D_EFR();
      vector<Real>   get_D_ENP();
      vector<Real>   get_D_END();
      vector<Real>   get_D_EGP();
      vector<Real>   get_D_EGD();
      vector<Real>   get_D_EB();
      vector<Real>   get_D_ENU();
      vector<Real>   get_D_ER();
      vector<Real>   get_D_ET();

      //Getter at line No.03
      vector<Integer>          get_LDRV();
      vector<Integer>          get_IFC();
      vector<vector<Integer> > get_NBT_EIFC();
      vector<vector<Integer> > get_INT_EIFC();
      vector<vector<Real> >    get_E_INT_EIFC();
      vector<vector<Real> >    get_EIFC_TAB();


      //Setter
      void set_mat_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LFC(Integer& int_data);
      void set_NFC(Integer& int_data);

      void set_NPLY(Integer& int_data);
      void set_N1(Integer& int_data);
      void set_N2(Integer& int_data);
      void set_EFR(vector<Real>& real_vec);
      void set_ENP(vector<Real>& real_vec);
      void set_END(vector<Real>& real_vec);
      void set_EGP(vector<Real>& real_vec);
      void set_EGD(vector<Real>& real_vec);
      void set_EB(vector<Real>& real_vec);
      void set_ENU(vector<Real>& real_vec);
      void set_ER(vector<Real>& real_vec);
      void set_ET(vector<Real>& real_vec);
      void set_D_EFR(vector<Real>& real_vec);
      void set_D_ENP(vector<Real>& real_vec);
      void set_D_END(vector<Real>& real_vec);
      void set_D_EGP(vector<Real>& real_vec);
      void set_D_EGD(vector<Real>& real_vec);
      void set_D_EB(vector<Real>& real_vec);
      void set_D_ENU(vector<Real>& real_vec);
      void set_D_ER(vector<Real>& real_vec);
      void set_D_ET(vector<Real>& real_vec);

      void set_LDRV(vector<Integer>& int_vec);
      void set_IFC(vector<Integer>& int_vec);
      void set_NBT_EIFC(vector<vector<Integer> >& int_vec);
      void set_INT_EIFC(vector<vector<Integer> >& int_vec);
      void set_E_INT_EIFC(vector<vector<Real> >& real_vec);
      void set_EIFC_TAB(vector<vector<Real> >& real_vec);
  };
}

#endif // MF01MT458_PARSER_H

