#ifndef READ_ACER_INPUT_H
#define READ_ACER_INPUT_H

#include <boost/algorithm/string.hpp>

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "NjoyUtils/NjoyInputReader.hpp"

namespace frendy
{
  class AcerInputReader
  {
    private:
      frendy::NjoyInputReader rn_obj;
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;

      static const int     thinning_ene_no                     =   3;
      static const int     mod_za_no                           =   3;

      static const Integer mcnpx_mode_flg_def                  =   0;
      static const Integer opt_print_def                       =   1; //max
      static const Integer zi_awr_pair_no_def                  =   0;
      static const Real    suffix_za_id_def;                    //=   0.0;
      static const Real    temp_def;                            //= 300.0;
      static const Integer new_cummulative_angle_distr_flg_def =   1; //on
      static const Integer detailed_photon_flg_def             =   1; //on
      static const Integer mod_za_def                          =   0;
      static const Integer atom_no_th_def                      =   1;
      static const Integer opt_weight_def                      =   0; //variable
      static const Real    ene_max_th_def;                      //= 1.0E+3;

      string          input_acer;

      //*** Common data (Card 01, 02) ***//
      //Card 01
      string          endf_name, pendf_name, gendf_name, ace_name, mcnp_dir;

      //Card 02
      Integer         mcnpx_mode_flg, opt_run, opt_print, opt_out_type, zi_awr_pair_no;
      Real            suffix_za_id;

      //Card03
      string          discriptive_data;

      //Card04
      vector<Integer> zi_vec;
      vector<Real>    awr_vec; 

      //*** Fast data (opt_run == 1) ***//
      //Card 05
      Integer         mat;
      Real            temp;

      //Card 06
      Integer         new_cummulative_angle_distr_flg, detailed_photon_flg;

      //Card 07
      vector<Real>    thinning_ene;
 
      //*** Thermal data (opt_run == 2) ***//
      //Card 08
      string          thermal_za_id_name;

      //Card 08a
      vector<Integer> mod_za;

      //Card 09
      Integer         mt_inelastic, bin_no, mt_elastic, elastic_flg, atom_no_th, opt_weight; 
      Real            ene_max_th;

      void read_common_data(ifstream& fin);
      void read_fast_data(ifstream& fin);
      void read_thermal_data(ifstream& fin);
      void read_dosimetry_data(ifstream& fin);
      void read_photo_atomic_nuclear_data(ifstream& fin);

    public:
      //constructor
      AcerInputReader(void);

      //destructor
      virtual ~AcerInputReader(void);

      //read input file for reconr
      void read_input(string file_name);
      void read_input(string file_name, int line_no);

      void clear();

      string          get_input_acer();
      string          get_endf_name();
      string          get_pendf_name();
      string          get_gendf_name();
      string          get_ace_name();
      string          get_mcnp_dir();
      Integer         get_mcnpx_mode_flg();
      Integer         get_opt_run();
      Integer         get_opt_print();
      Integer         get_opt_out_type();
      Integer         get_zi_awr_pair_no();
      Real            get_suffix_za_id();
      string          get_discriptive_data();
      vector<Integer> get_zi_vec();
      vector<Real>    get_awr_vec();
      Integer         get_mat();
      Real            get_temp();
      Integer         get_new_cummulative_angle_distr_flg();
      Integer         get_detailed_photon_flg();
      vector<Real>    get_thinning_ene();
      string          get_thermal_za_id_name();
      vector<Integer> get_mod_za();
      Integer         get_mt_inelastic();
      Integer         get_bin_no();
      Integer         get_mt_elastic();
      Integer         get_elastic_flg();
      Integer         get_atom_no_th();
      Integer         get_opt_weight();
      Real            get_ene_max_th();
  }; 
}

#endif //READ_ACER_INPUT_H
