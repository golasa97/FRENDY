#ifndef DOSIMETRY_ACE_DATA_WRITER_H
#define DOSIMETRY_ACE_DATA_WRITER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/DigitAdjuster.hpp"
#include "ContinuousEnergyXSUtils/AceDataObject/DosimetryAceDataObject.hpp"
#include "ContinuousEnergyXSUtils/OtherUtils/AceFileWriter.hpp"

namespace frendy
{
  class DosimetryAceDataWriter
  {
    private:
      frendy::ErrorManager      err_obj;
      frendy::VectorClearer     clr_obj;
      frendy::DigitAdjuster     ad_obj;
      frendy::AceFileWriter     ace_wri_obj;

#ifdef DEBUG_MODE
  public:
#endif
      Integer set_data_flg, set_ace_data_obj_flg;

      frendy::DosimetryAceDataObject ace_data_obj;

      Integer pointer_data_count;

      //For output
      Integer opt_out_type;
      string  ace_file_name;

      Integer line_no_pre;

      //For ACE data
      Integer         mcnpx_mode_flg;
      Real            aw0, tz;
      vector<string>  title_data;
      string          discriptive_data;

      vector<Integer> zi_vec;
      vector<Real>    awr_vec;

      //For XS data
      vector<Integer>          reaction_xs_reaction_type, reaction_xs_pointer;
      vector<vector<Integer> > reaction_xs_range_data, reaction_xs_int_data;
      vector<vector<Real> >    reaction_xs_ene_data,   reaction_xs_data;

      vector<vector<Integer> >          production_xs_state_no_product, production_xs_pointer;
      vector<vector<vector<Integer> > > production_xs_range_data, production_xs_int_data;
      vector<vector<vector<Real> > >    production_xs_ene_data,   production_xs_data;

      //For pointer data
      int len2, za, ntr, lone, mtr, lsig, sigd, end;

      void clear_ace_data();
      void clear_ace_pointer_data();

      void copy_dosimetry_ace_data();
      void copy_dosimetry_ace_pointer_data(frendy::DosimetryAceDataObject& dosimetry_ace_data_obj);

      Integer get_line_no();

      //Write ace file
      void output_ace_format();
      void output_ace_format_header();
      void output_ace_format_xs();

      void output_ace_format_binary_mode();

      void calc_ace_header_file_data();

      void check_set_data();

    public:
      //constructor
      DosimetryAceDataWriter(void);

      //destructor
      virtual ~DosimetryAceDataWriter(void);

      static const Integer ascii_mode  = 1;
      static const Integer binary_mode = 2;

      void clear();

      void write_ace_format();
      vector<string> get_ace_text_data();
      void get_ace_data_for_mg(vector<string>& title_vec, vector<int>& izaw_vec,
                               vector<int>& nxs_vec, vector<int>& jxs_vec,
                               vector<double>& xss_vec);
      vector<double> get_xss_data();

      void   write_dir_data(string dir_name);
      string get_dir_data();

      //Setter
      void set_ace_data_obj(frendy::DosimetryAceDataObject& data_obj);
      void set_opt_out_type(Integer int_val);
      void set_ace_file_name(string str_data);
      void set_previous_line_no(Integer int_val);

      //Getter
      frendy::DosimetryAceDataObject get_ace_data_obj();
      Integer                        get_opt_out_type();
      string                         get_ace_file_name();
      Integer                        get_previous_line_no();
  };
}

#endif //DOSIMETRY_ACE_DATA_WRITER_H
