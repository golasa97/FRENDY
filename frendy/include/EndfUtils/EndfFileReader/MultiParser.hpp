#ifndef MULTI_PARSER_H
#define MULTI_PARSER_H

#include "Config/FrendyTypes.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/TabInterpolator.hpp"
#include "CommonUtils/TabAdjuster.hpp"
#include "EndfUtils/EndfFileReader/StringConverter.hpp"
#include "TabUtils/LinearizeTabData.hpp"

namespace frendy
{
  class MultiParser
  {
    private:
      static int  linearize_tab_flg;
      static Real linearize_tolerance;


      frendy::ErrorManager    err_obj;
      Integer                 ndigit_pre, char_no, data_no, int_size;
      frendy::StringConverter str_conv;
      frendy::TabInterpolator ti_obj;

      void check_ndigit(Integer& NDIGIT);
    
    public:
      //constructor
      MultiParser(void);

      //destructor
      virtual ~MultiParser(void);

      static const int skip_linearize_tab_data    = 0;
      static const int linearize_tab_data         = 1;

      void read_head(vector<string>& text, int& line_no,
                     Real& C1, Real& C2, Integer& L1, Integer& L2, Integer& N1, Integer& N2);

      void read_text(vector<string>& text, int& line_no, string& HL);

      void read_cont(vector<string>& text, int& line_no,
                     Real& C1, Real& C2, Integer& L1, Integer& L2, Integer& N1, Integer& N2);

      void read_cont_real(vector<string>& text, int& line_no,
                          Real& C1, Real& C2, Real& L1, Real& L2, Real& N1, Real& N2);

      void read_list(vector<string>& text, int& line_no,
                     Real& C1, Real& C2, Integer& L1, Integer& L2,
                     Integer& NPL, Integer& N2, vector<Real>& B);

      void read_tab1(vector<string>& text, int& line_no,
                     Real& C1, Real& C2, Integer& L1, Integer& L2,
                     Integer& NR, Integer& NP, vector<Integer>& NBT, vector<Integer>& INT,
                     vector<Real>& X, vector<Real>& Y);

      void read_tab2(vector<string>& text, int& line_no,
                 Real& C1, Real& C2, Integer& L1, Integer& L2,
                 Integer& NR, Integer& NZ, vector<Integer>& NBT, vector<Integer>& INT);

      void read_intg(vector<string>& text, int& line_no, Integer& NDIGIT,
                     Integer& II, Integer& JJ, vector<Integer>& KIJ);

      void get_mf_mt(vector<string>& text, Integer& MF, Integer& MT);

      void get_mat(vector<string>& text, Integer& MAT);

      void line_no_check(vector<string>& text, int line_no, Integer MF, Integer MT);

      Integer check_mf_mt(vector<string>& text, Integer MF, Integer MT);

      Integer check_mf(vector<string>& text, Integer MF);


      void set_linearize_tab_flg(int int_val);
      void set_linearize_tolerance(Real real_val);
      void set_linearize_tolerance_def();

      int  get_linearize_tab_flg();
      Real get_linearize_tolerance();
  };
}

#endif // MULTI_PARSER_H
