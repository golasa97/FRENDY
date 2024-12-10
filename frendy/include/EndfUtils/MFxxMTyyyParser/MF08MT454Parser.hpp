#ifndef MF08MT454_PARSER_H
#define MF08MT454_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF08MT454Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer              mat_no;
      static const Integer mf_no  =   8;
      Integer              mt_no;

      vector<string> text;

      Real                  ZA,  AWR;      //Line No.01
      Integer               LE;

      vector<Real>          E;
      vector<Integer>       I;
      vector<vector<Real> > ZAFP, FPS, YI, DYI;

      void store_data();

    public:
      //constructor
      MF08MT454Parser(void);

      //destructor
      virtual ~MF08MT454Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string>  get_text();

      Integer         get_mat_no();
      Integer         get_mt_no();

      Real                  get_ZA();
      Real                  get_AWR();
      Integer               get_LE();

      vector<Real>          get_E();
      vector<Integer>       get_I();
      vector<vector<Real> > get_ZAFP();
      vector<vector<Real> > get_FPS();
      vector<vector<Real> > get_YI();
      vector<vector<Real> > get_DYI();

      //Setter
      void set_mat_no(Integer& int_data);
      void set_mt_no(Integer& int_data);
      void set_ZA(Real& real_data);
      void set_AWR(Real& real_data);
      void set_LE(Integer& int_data);
      void set_E(vector<Real>& real_vec);
      void set_I(vector<Integer>& int_vec);
      void set_ZAFP(vector<vector<Real> >& real_vec);
      void set_FPS(vector<vector<Real> >& real_vec);
      void set_YI(vector<vector<Real> >& real_vec);
      void set_DYI(vector<vector<Real> >& real_vec);
  };
}

#endif // MF08MT454_PARSER_H

