#ifndef MF01MT460_PARSER_H
#define MF01MT460_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF01MT460Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer mat_no;
      static const Integer mf_no =   1;
      static const Integer mt_no = 460;

      vector<string> text;

      Real    ZA, AWR;                           //Line No.01
      Integer LO,   NG;
      Integer NR,   NP,   NNF;                   //Line No.02

      vector<Real>  E, RAMDA;
      vector<vector<Integer> > NBT_MAP,   INT_MAP;
      vector<vector<Real> >    T_INT_MAP, T_MAP;

      void store_data();

    public:
      //constructor
      MF01MT460Parser(void);

      //destructor
      virtual ~MF01MT460Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string> get_text();

      Integer        get_mat_no();

      //Getter at line No.01
      Real           get_ZA();
      Real           get_AWR();
      Integer        get_LO();
      Integer        get_NG();

      //Getter at line No.02
      Integer        get_NR();
      Integer        get_NP();
      Integer        get_NNF();

      vector<Real>    get_E();
      vector<Real>    get_RAMDA();

      vector<vector<Integer> > get_NBT_MAP();
      vector<vector<Integer> > get_INT_MAP();
      vector<vector<Real> >    get_T_INT_MAP();
      vector<vector<Real> >    get_T_MAP();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LO(Integer& int_data);
      void set_NG(Integer& int_data);
      void set_NR(Integer& int_data);
      void set_NP(Integer& int_data);
      void set_NNF(Integer& int_data);
      void set_E(vector<Real>& real_vec);
      void set_RAMDA(vector<Real>& real_vec);
      void set_NBT_MAP(vector<vector<Integer> >& int_vec);
      void set_INT_MAP(vector<vector<Integer> >& int_vec);
      void set_T_INT_MAP(vector<vector<Real> >& real_vec);
      void set_T_MAP(vector<vector<Real> >& real_vec);
  };
}

#endif // MF01MT460_PARSER_H

