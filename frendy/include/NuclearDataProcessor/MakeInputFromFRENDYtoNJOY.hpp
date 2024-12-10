#ifndef MAKE_INPUT_FROM_FRENDY_TO_NJOY_H
#define MAKE_INPUT_FROM_FRENDY_TO_NJOY_H

#include "FrendyUtils/FrendyInputReader.hpp"
#include "FrendyUtils/ThermalScatterMatList.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "NuclearDataUtils/OtherUtils/Endf6FileStore.hpp"

namespace frendy
{
  class MakeInputFromFRENDYtoNJOY
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::VectorClearer  clr_obj;

      Real tolerance_input;
      int  precision, comment_row_number;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::FrendyInputReader       frendy_inp_obj;
      frendy::FrendyInputCommonUtils  frendy_inp_common_obj;
      frendy::MakeNJOYInputReader     njoy_module_flg_obj;

      frendy::NuclearDataObject nucl_data_obj_ori, nucl_data_obj_tsl;

      int     calc_mode;

      vector<string> njoy_input_data;

      Integer nendf_ori, nendf_tsl,
              npend_reconr, npend_broadr, npend_gaspr, npend_purr, npend_thermr,
              npend_heatr,  nace, nacedir, ngendf, nmatxs;
      Integer mt_tsl_iin, mt_tsl_icoh;

      void make_input_ace_fast();
      void make_input_ace_therm();
      void make_input_ace_dosi();
      void make_input_matxs();
      void make_input_matxs_tsl();

      void make_input_reconr();
      void make_input_broadr();
      void make_input_gaspr();
      void make_input_purr();
      void make_input_thermr();
      void make_input_thermr_freegas();
      void make_input_acer_common(Integer iopt);
      void make_input_acer_fast();
      void make_input_acer_therm();
      void make_input_acer_dosi();
      void make_input_groupr();
      void make_input_matxsr();

      void make_input_heatr();

      void make_groupr_mf_mt_list(); //card 09

      Integer get_tape_no(string tape_str, Integer tape_no_ori);
      Real    search_thn_max();
      Integer check_elastic_scattering_tsl(); //0:coherent, 1:incoherent
      Integer get_inelastic_options_tsl();
      Integer get_elastic_options_tsl();
      Integer get_atom_no_principal_tsl(int ele_no);
      Integer get_atom_no_mix_tsl(int ele_no);
      Integer get_moderator_component(int ele_no);
      Real    get_max_thermal_ene();
      
      void set_default_tape_no();

      void adjust_comment_data(vector<string>& text_vec, int row_number);
      void adjust_comment_line(string& text_data, int row_number);

    public:
      //constructor
      MakeInputFromFRENDYtoNJOY(void);

      //destructor
      virtual ~MakeInputFromFRENDYtoNJOY(void);

      void clear();

      vector<Integer> get_moderator_za_data(frendy::NuclearDataObject& nucl_obj_tsl,
                                            frendy::NuclearDataObject& nucl_obj, int ele_no);
      Integer         get_mat_data_principal(frendy::NuclearDataObject& nucl_obj_tsl,
                                             frendy::NuclearDataObject& nucl_obj);

      void make_input_from_frendy_to_njoy(frendy::FrendyInputReader inp_obj);
      void make_input_from_frendy_to_njoy(frendy::FrendyInputReader inp_obj, string output_name);

      void write_njoy_input(string output_name);

      vector<string> get_njoy_input_data();
  };
}

#endif // MAKE_INPUT_FROM_FRENDY_TO_NJOY_H
