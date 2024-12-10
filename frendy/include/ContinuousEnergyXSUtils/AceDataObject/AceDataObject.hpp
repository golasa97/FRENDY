#ifndef ACE_DATA_OBJECT_H
#define ACE_DATA_OBJECT_H

#include "ContinuousEnergyXSUtils/AceDataObject/FastAceDataObject.hpp"
#include "ContinuousEnergyXSUtils/AceDataObject/ThermalScatterAceDataObject.hpp"
#include "ContinuousEnergyXSUtils/AceDataObject/DosimetryAceDataObject.hpp"

namespace frendy
{
  class AceDataObject
  {
    private:
      frendy::FastAceDataObject           fast_ace_data_obj;
      frendy::ThermalScatterAceDataObject thermal_scat_ace_data_obj;
      frendy::DosimetryAceDataObject      dosimetry_ace_data_obj;

    public:
      //constructor
      AceDataObject(void);

      //destructor
      virtual ~AceDataObject(void);

      void clear();

      //Setter
      void set_fast_ace_data_obj(frendy::FastAceDataObject data_obj);
      void set_thermal_scat_ace_data_obj(frendy::ThermalScatterAceDataObject data_obj);
      void set_dosimetry_ace_data_obj(frendy::DosimetryAceDataObject data_obj);

      //Getter
      frendy::FastAceDataObject           get_fast_ace_data_obj();
      frendy::ThermalScatterAceDataObject get_thermal_scat_ace_data_obj();
      frendy::DosimetryAceDataObject      get_dosimetry_ace_data_obj();
  };
}

#endif //ACE_DATA_OBJECT_H
