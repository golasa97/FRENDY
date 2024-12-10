#ifndef ENDF_FILE_WRITER_H
#define ENDF_FILE_WRITER_H

#include <limits>

#include "Config/FrendyTypes.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "CommonUtils/TabInterpolator.hpp"

namespace frendy
{
  class EndfFileWriter
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::DigitAdjuster   digit_obj;
      frendy::TabInterpolator ti_obj;

      Integer         digit_mod_mode;

      vector<Real>    real_vec, line_vec_real;
      vector<Integer> int_vec,  line_vec_int;
      vector<Integer> mat_vec;
      vector<int>     mat_width;

      vector<Integer> vec_intg;
      int data_no_pre, int_size;
      string blank_sta, blank_end;

#ifdef DEBUG_MODE
  public:
#endif

      void check_kij_size(int& data_no);

      void write_nbt_int(vector<string>& text, vector<Integer>& NBT, vector<Integer>& INT);
      void write_x_y(vector<string>& text, vector<Real>& X, vector<Real>& Y);

      string write_blank();
      string write_blank(int blank_no);
      string write_mat_data();
      string convert_to_string_real(vector<Real>& real_vec);
      string convert_to_string_real(vector<Real>& real_vec, int width);
      string convert_to_string_int(vector<Integer>& int_vec);
      string convert_to_string_int(vector<Integer>& int_vec, int width);

      void check_data_size_tab1(Integer& nr, Integer& np,
                                vector<Integer>& nbt_vec, vector<Integer>& int_vec,
                                vector<Real>&    x_vec,   vector<Real>&    y_vec);

      void adjust_truncation_err_tab1(Integer& nr, Integer& np, 
                                      vector<Integer>& nbt_vec, vector<Integer>& int_vec,
                                      vector<Real>&    x_vec,   vector<Real>&    y_vec);
      void adjust_truncation_err_tab1_old(Integer& nr, Integer& np, 
                                          vector<Integer>& nbt_vec, vector<Integer>& int_vec,
                                          vector<Real>&    x_vec,   vector<Real>&    y_vec);
      void modify_nbt_int_tab1(int remove_no, vector<Integer>& nbt_new, vector<Integer>& int_new);

    public:
      //constructor
      EndfFileWriter(void);

      //destructor
      virtual ~EndfFileWriter(void);

      static const Integer mod_digit    = 0;
      static const Integer no_mod_digit = 1;

      //writer
      string write_cont(Real C1, Real C2, Integer L1, Integer L2, Integer N1, Integer N2);
      string write_cont_real(Real C1, Real C2, Real L1, Real L2, Real N1, Real N2);
      string write_cont_int(Integer C1, Integer C2, Integer L1, Integer L2, Integer N1, Integer N2);

      vector<string> write_list(Real C1, Real C2, Integer L1, Integer L2, Integer NPL, Integer N2,
                                vector<Real> B);

      vector<string> write_tab1(Real C1, Real C2, Integer L1, Integer L2, Integer NR, Integer NP,
                                vector<Integer> NBT, vector<Integer> INT, vector<Real> X, vector<Real> Y);

      vector<string> write_tab2(Real C1, Real C2, Integer L1, Integer L2, Integer NR, Integer NZ,
                                vector<Integer> NBT, vector<Integer> INT);

      string write_intg(Integer II, Integer JJ, vector<Integer> KIJ);

      string write_text(string HL);
      string write_mt_end();
      string write_mf_end();
      string write_file_end();
      string write_tape_end();

      //setter
      void set_mat(Integer mat_no);
      void set_mf_mt(Integer mf_no, Integer mt_no);
      void set_mat_mf_mt(Integer mat_no, Integer mf_no, Integer mt_no);

      void    set_digit_mod_mode_default();
      void    set_digit_mod_mode(Integer int_val);
      Integer get_digit_mod_mode();

  };
}

#endif // ENDF_FILE_WRITER_H
