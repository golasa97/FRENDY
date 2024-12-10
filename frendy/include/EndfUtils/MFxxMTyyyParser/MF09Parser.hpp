#ifndef MF09_PARSER_H
#define MF09_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF09Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =   9;
      Integer              mt_no;

      vector<string> text;

      Real                     ZA,   AWR;      //Line No.01
      Integer                  LIS,  NS;
      vector<Real>             QM,   QI;      //Line No.02
      vector<Integer>          IZAP, LFS;
      vector<vector<Integer> > NBT_Y,   INT_Y;
      vector<vector<Real> >    E_INT_Y, Y_TAB;

      void store_data();

    public:
      //constructor
      MF09Parser(void);

      //destructor
      virtual ~MF09Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();


      Real                     get_ZA();
      Real                     get_AWR();
      Integer                  get_LIS();
      Integer                  get_NS();
      vector<Real>             get_QM();
      vector<Real>             get_QI();
      vector<Integer>          get_IZAP();
      vector<Integer>          get_LFS();
      vector<vector<Integer> > get_NBT_Y();
      vector<vector<Integer> > get_INT_Y();
      vector<vector<Real> >    get_E_INT_Y();
      vector<vector<Real> >    get_Y_TAB();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LIS(Integer& int_data);
      void set_NS(Integer& int_data);
      void set_QM(vector<Real>& real_vec);
      void set_QI(vector<Real>& real_vec);
      void set_IZAP(vector<Integer>& int_vec);
      void set_LFS(vector<Integer>& int_vec);
      void set_NBT_Y(vector<vector<Integer> >& int_vec);
      void set_INT_Y(vector<vector<Integer> >& int_vec);
      void set_E_INT_Y(vector<vector<Real> >& real_vec);
      void set_Y_TAB(vector<vector<Real> >& real_vec);
  };
}

#endif // MF09_PARSER_H

