#ifndef MF14_PARSER_H
#define MF14_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF14Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =  14;
      Integer              mt_no;

      vector<string> text;

      Real                  ZA,   AWR;      //Line No.01
      Integer               LI,   NK,  LTT,  NI;

      vector<Real>             EG, ES;
      vector<Integer>          NE;
      vector<vector<Integer> > NBT_E, INT_E;
      vector<vector<Real> >    E;

      vector<vector<vector<Real> > >    A;
      vector<vector<vector<Integer> > > NBT_P, INT_P;
      vector<vector<vector<Real> > >    MU_INT_P, P_TAB;

      void store_data();
      void store_ltt01(MultiParser& mp_obj, int& line_no);
      void store_ltt02(MultiParser& mp_obj, int& line_no);

      void resize_matrix();

    public:
      //constructor
      MF14Parser(void);

      //destructor
      virtual ~MF14Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();


      Real                  get_ZA();
      Real                  get_AWR();
      Integer               get_LI();
      Integer               get_NK();
      Integer               get_LTT();
      Integer               get_NI();

      vector<Real>             get_EG();
      vector<Real>             get_ES();
      vector<Integer>          get_NE();
      vector<vector<Integer> > get_NBT_E();
      vector<vector<Integer> > get_INT_E();
      vector<vector<Real> >    get_E();

      vector<vector<vector<Real> > >    get_A();
      vector<vector<vector<Integer> > > get_NBT_P();
      vector<vector<vector<Integer> > > get_INT_P();
      vector<vector<vector<Real> > >    get_MU_INT_P();
      vector<vector<vector<Real> > >    get_P_TAB();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LI(Integer& int_data);
      void set_NK(Integer& int_data);
      void set_LTT(Integer& int_data);
      void set_NI(Integer& int_data);
      void set_EG(vector<Real>& real_vec);
      void set_ES(vector<Real>& real_vec);
      void set_NE(vector<Integer>& int_vec);
      void set_NBT_E(vector<vector<Integer> >& int_vec);
      void set_INT_E(vector<vector<Integer> >& int_vec);
      void set_E(vector<vector<Real> >& real_vec);
      void set_A(vector<vector<vector<Real> > >& real_vec);
      void set_NBT_P(vector<vector<vector<Integer> > >& int_vec);
      void set_INT_P(vector<vector<vector<Integer> > >& int_vec);
      void set_MU_INT_P(vector<vector<vector<Real> > >& real_vec);
      void set_P_TAB(vector<vector<vector<Real> > >& real_vec);
  };
}

#endif // MF14_PARSER_H

