#ifndef THERMAL_SCATTER_ACE_DATA_COMPARE_H
#define THERMAL_SCATTER_ACE_DATA_COMPARE_H

#include <boost/timer/timer.hpp>

#include "ContinuousEnergyXSUtils/AceDataParser/ThermalScatterAceDataParser.hpp"
#include "ContinuousEnergyXSUtils/AceDataCompare/AceDataCompare.hpp"

namespace frendy
{
  class ThermalScatterAceDataCompare
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::AceDataCompare ace_comp_obj;

#ifdef DEBUG_MODE
  public:
#endif
      string                              ace_file_name, ace_file_name_ref;
      frendy::ThermalScatterAceDataObject ace_data_obj,  ace_data_obj_ref;

      //Real   time_read, time_read_ref;

      string class_name, func_name;

      int comp_pointer_flg;

      void comp_ace_data_header();
      void comp_ace_data_pointer();
      void comp_ace_data_inelastic();
      void comp_ace_data_elastic();

      frendy::ThermalScatterAceDataObject parse_ace_data_file(string& file_name);

    public:
      //constructor
      ThermalScatterAceDataCompare(void);

      //destructor
      virtual ~ThermalScatterAceDataCompare(void);

      static const int comp_pointer_mode    = 0;
      static const int no_comp_pointer_mode = 1;

      void clear();

      void comp_ace_data();

      //Setter
      void set_ace_data_obj(frendy::ThermalScatterAceDataObject& ace_obj,
                            frendy::ThermalScatterAceDataObject& ace_obj_ref);
      void set_ace_file_name(string ace_name, string ace_name_ref);

      //Getter
      frendy::ThermalScatterAceDataObject get_ace_data_obj();
      frendy::ThermalScatterAceDataObject get_ace_data_obj_ref();
      string                              get_ace_file_name();
      string                              get_ace_file_name_ref();

      void set_tolerance_val_def();
      void set_tolerance_val(Real tolerance_val);
      Real get_tolerance_val();

      void set_comp_pointer_flg(int comp_flg);
      int  get_comp_pointer_flg();
  };
}

#endif //THERMAL_SCATTER_ACE_DATA_COMPARE_H
