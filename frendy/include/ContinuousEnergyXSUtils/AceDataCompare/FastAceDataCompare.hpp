#ifndef FAST_ACE_DATA_COMPARE_H
#define FAST_ACE_DATA_COMPARE_H

#include <boost/timer/timer.hpp>

#include "ContinuousEnergyXSUtils/AceDataParser/FastAceDataParser.hpp"
#include "ContinuousEnergyXSUtils/AceDataCompare/AceDataCompare.hpp"

namespace frendy
{
  class FastAceDataCompare
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::AceDataCompare   ace_comp_obj;
      frendy::IntegrateTabData integ_obj;

#ifdef DEBUG_MODE
  public:
#endif
      string                    ace_file_name, ace_file_name_ref;
      frendy::FastAceDataObject ace_data_obj,  ace_data_obj_ref;

      Real   time_read, time_read_ref;

      string class_name, func_name;

      int comp_pointer_flg;
      int skip_prob_table_flg;

      void comp_ace_data_header();
      void comp_ace_data_pointer();
      void comp_ace_data_base_data();
      void comp_ace_data_angular_distribution_data();
      void comp_ace_data_energy_distribution_data();
      void comp_ace_data_unreso_prob_table_data();
      void comp_ace_data_nu_d_data();
      void comp_ace_data_gamma_production_xs();
      void comp_ace_data_photon_production_data();
      void comp_ace_data_photon_energy_distr_data();
      void comp_ace_data_particle_production_data();

      frendy::FastAceDataObject parse_ace_data_file(string& file_name);

    public:
      //constructor
      FastAceDataCompare(void);

      //destructor
      virtual ~FastAceDataCompare(void);

      static const int comp_pointer_mode    = 0;
      static const int no_comp_pointer_mode = 1;
      static const int no_skip_prob_table   = 0;
      static const int skip_prob_table      = 1;


      void clear();

      void comp_ace_data();

      //Setter
      void set_ace_data_obj(frendy::FastAceDataObject& ace_obj, frendy::FastAceDataObject& ace_obj_ref);
      void set_ace_file_name(string ace_name, string ace_name_ref);

      //Getter
      frendy::FastAceDataObject get_ace_data_obj();
      frendy::FastAceDataObject get_ace_data_obj_ref();
      string                    get_ace_file_name();
      string                    get_ace_file_name_ref();

      void set_tolerance_val_def();
      void set_tolerance_val(Real tolerance_val);
      Real get_tolerance_val();

      void set_comp_pointer_flg(int comp_flg);
      int  get_comp_pointer_flg();

      void set_skip_prob_table_flg(int skip_flg);
      int  get_skip_prob_table_flg();
  };
}

#endif //FAST_ACE_DATA_COMPARE_H
