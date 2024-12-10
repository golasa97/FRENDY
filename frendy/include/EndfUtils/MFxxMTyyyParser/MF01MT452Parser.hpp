#ifndef MF01MT452_PARSER_H
#define MF01MT452_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class MF01MT452Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer mat_no;
      static const Integer mf_no =   1;
      static const Integer mt_no = 452;

      vector<string> text;

      Real    ZA, AWR;                           //Line No.01
      Integer LNU; 
      Integer NC,   NR,   NP;                    //Line No.02 

      vector<Real>    C,   E_INT, NU;
      vector<Integer> NBT, INT; 

      void store_data();

    public:
      //constructor
      MF01MT452Parser(void);

      //destructor
      virtual ~MF01MT452Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      void set_mat_no(Integer int_data);

      //Setter at line No.01
      void set_ZA(Real real_data);
      void set_AWR(Real real_data);
      void set_LNU(Integer int_data);

      //Setter at line No.02
      void set_NC(Integer int_data);
      void set_NR(Integer int_data);
      void set_NP(Integer int_data);

      void set_C(vector<Real> real_vec);
      void set_NBT(vector<Integer> int_vec);
      void set_INT(vector<Integer> int_vec);
      void set_E_INT(vector<Real> real_vec);
      void set_NU(vector<Real> real_vec);

      //Getter (text data from ENDF format)
      vector<string> get_text();

      Integer        get_mat_no();

      //Getter at line No.01
      Real           get_ZA();
      Real           get_AWR();
      Integer        get_LNU();

      //Getter at line No.02
      Integer        get_NC();
      Integer        get_NR();
      Integer        get_NP();

      vector<Real>    get_C();
      vector<Integer> get_NBT();
      vector<Integer> get_INT();
      vector<Real>    get_E_INT();
      vector<Real>    get_NU();
  };
}

#endif // MF01MT452_PARSER_H
