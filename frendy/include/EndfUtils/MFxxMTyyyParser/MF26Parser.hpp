#ifndef MF26_PARSER_H
#define MF26_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF26Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =  26;
      Integer              mt_no;

      vector<string> text;

      Real                     ZA, AWR; //Line No.01
      Integer                  NK;

      vector<Real>             ZAP;
      vector<Integer>          LAW;
      vector<vector<Integer> > NBT_Y,   INT_Y;
      vector<vector<Real> >    E_INT_Y, Y_TAB;

      vector<Integer>          LANG_LAW01, LEP_LAW01, NE;
      vector<vector<Integer> > NBT_E, INT_E;
      vector<vector<Real> >    E1_LAW01;
      vector<vector<Integer> > ND_LAW01;

      vector<vector<vector<Real> > > E2_LAW01;
      vector<vector<vector<vector<Real> > > > B_LAW01;

      vector<vector<Real> >    E_LAW02;
      vector<vector<Integer> > LANG_LAW02, NL_LAW02;
      vector<vector<vector<Real> > > A_LAW02;

      vector<vector<Integer> > NBT_ET,   INT_ET;
      vector<vector<Real> >    E_INT_ET, ET_TAB;

      void store_data();

      void store_law01(MultiParser& mp_obj, int& line_no, int& i);
      void store_law02(MultiParser& mp_obj, int& line_no, int& i);
      void store_law08(MultiParser& mp_obj, int& line_no, int& i);

      void resize_matrix(int i_max);

    public:
      //constructor
      MF26Parser(void);

      //destructor
      virtual ~MF26Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();

      Real                     get_ZA();
      Real                     get_AWR();
      Integer                  get_NK();

      vector<Real>             get_ZAP();
      vector<Integer>          get_LAW();
      vector<vector<Integer> > get_NBT_Y();
      vector<vector<Integer> > get_INT_Y();
      vector<vector<Real> >    get_E_INT_Y();
      vector<vector<Real> >    get_Y_TAB();

      vector<Integer>          get_LANG_LAW01();
      vector<Integer>          get_LEP_LAW01();
      vector<Integer>          get_NE_LAW01();
      vector<vector<Integer> > get_NBT_E_LAW01();
      vector<vector<Integer> > get_INT_E_LAW01();
      vector<vector<Real> >    get_E1_LAW01();
      vector<vector<Integer> > get_ND_LAW01();

      vector<vector<vector<Real> > > get_E2_LAW01();
      vector<vector<vector<vector<Real> > > > get_B_LAW01();

      vector<Integer>          get_NE_LAW02();
      vector<vector<Integer> > get_NBT_E_LAW02();
      vector<vector<Integer> > get_INT_E_LAW02();
      vector<vector<Real> >    get_E_LAW02();
      vector<vector<Integer> > get_LANG_LAW02();
      vector<vector<Integer> > get_NL_LAW02();
      vector<vector<vector<Real> > > get_A_LAW02();

      vector<vector<Integer> > get_NBT_ET_LAW08();
      vector<vector<Integer> > get_INT_ET_LAW08();
      vector<vector<Real> >    get_E_INT_ET_LAW08();
      vector<vector<Real> >    get_ET_TAB_LAW08();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_NK(Integer& int_data);
      void set_ZAP(vector<Real>& real_vec);
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
      void set_NBT_ET_LAW08(vector<vector<Integer> >& int_vec);
      void set_INT_ET_LAW08(vector<vector<Integer> >& int_vec);
      void set_E_INT_ET_LAW08(vector<vector<Real> >& real_vec);
      void set_ET_TAB_LAW08(vector<vector<Real> >& real_vec);
  };
}

#endif // MF26_PARSER_H

