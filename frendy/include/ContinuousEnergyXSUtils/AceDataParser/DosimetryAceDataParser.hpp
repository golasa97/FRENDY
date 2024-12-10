#ifndef DOSIMETRY_ACE_DATA_PARSER_H
#define DOSIMETRY_ACE_DATA_PARSER_H

#include "CommonUtils/ErrorManager.hpp"
#include "ContinuousEnergyXSUtils/OtherUtils/AceFileReader.hpp"
#include "ContinuousEnergyXSUtils/AceDataObject/DosimetryAceDataObject.hpp"

namespace frendy
{
  class DosimetryAceDataParser
  {
    private:
      frendy::ErrorManager      err_obj;
      frendy::VectorClearer     clr_obj;

      static const int max_zi_awr_pair_no = 16;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::AceFileReader ace_read_obj;

      //For read
      string          file_name;
      Integer         set_data_flg;

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

      void parse_ace_format_header();
      void parse_ace_format_xs();

      void clear_ace_data();
      void clear_ace_pointer_data();

      void copy_dosimetry_ace_data(frendy::DosimetryAceDataObject& ace_data_obj);

    public:
      //constructor
      DosimetryAceDataParser(void);

      //destructor
      virtual ~DosimetryAceDataParser(void);

      void clear();

      void parse_ace_format();

      void set_file_name(string& str_data);
      void set_text_data(vector<string>& str_vec);

      frendy::DosimetryAceDataObject get_ace_data_obj();
      string                         get_file_name();
  };
}

#endif //DOSIMETRY_ACE_DATA_PARSER_H
