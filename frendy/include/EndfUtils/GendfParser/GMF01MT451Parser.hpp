#ifndef GMF01MT451_PARSER_H
#define GMF01MT451_PARSER_H

#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "CommonUtils/VectorClearer.hpp"

namespace frendy
{
  class GMF01MT451Parser
  {
    private:
      frendy::ErrorManager err_obj;

      Integer mat_no;
      static const Integer mf_no =   1;
      static const Integer mt_no = 451;

      vector<string> text;

      Real          ZA, AWR;                           //Line No.01
      Integer       NSIGZ, NLIB, NTW;
      Real          TEMP;                              //Line No.02 
      Integer       NGN,  NGG;
      vector<Real>  TITLE, SIGZ, EGN, EGG;

      void store_data();

    public:
      //constructor
      GMF01MT451Parser(void);

      //destructor
      virtual ~GMF01MT451Parser(void);

      void clear();

      void set_text(vector<string> text_data);

      //Getter (text data from ENDF format)
      vector<string> get_text();

      Integer        get_mat_no();

      //Getter at line No.01
      Real           get_ZA();
      Real           get_AWR();
      Integer        get_NSIGZ();
      Integer        get_NLIB();
      Integer        get_NTW();

      //Getter at line No.02
      Real           get_TEMP();
      Integer        get_NGN();
      Integer        get_NGG();
      vector<Real>   get_TITLE();
      vector<Real>   get_SIGZ();
      vector<Real>   get_EGN();
      vector<Real>   get_EGG();

      //Setter
      void set_mat_no(Integer int_data);

      //Setter at line No.01
      void set_ZA(Real real_data);
      void set_AWR(Real real_data);
      void set_NSIGZ(Integer int_data);
      void set_NLIB(Integer int_data);
      void set_NTW(Integer int_data);

      //Setter at line No.02
      void set_TEMP(Real real_data);
      void set_NGN(Integer int_data);
      void set_NGG(Integer int_data);
      void set_TITLE(vector<Real> real_vec);
      void set_SIGZ(vector<Real> real_vec);
      void set_EGN(vector<Real> real_vec);
      void set_EGG(vector<Real> real_vec);
  };
}

#endif // GMF01MT451_PARSER_H
