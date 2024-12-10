#ifndef ENDF6_FILE_STORE_H
#define ENDF6_FILE_STORE_H

#include "Config/FrendyTypes.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/OtherUtils/EndfTapeDivider.hpp"
#include "EndfUtils/Endf6Parser/Endf6Parser.hpp"
#include "EndfUtils/Endf6Converter/Endf6Converter.hpp"
#include "EndfUtils/Endf6Writer/Endf6Writer.hpp"

namespace frendy
{
  class Endf6FileStore
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;

      frendy::EndfTapeDivider div_obj;
      frendy::EndfFileReader  efr_obj;
      frendy::Endf6Parser     parser_obj;
      frendy::Endf6Converter  conv_obj;

      frendy::NuclearDataObject merge_nucl_data_obj(frendy::NuclearDataObject& nucl_data_obj_no_cov,
                                                    frendy::NuclearDataObject& nucl_data_obj_cov);
    
    public:
      //constructor
      Endf6FileStore(void);

      //destructor
      virtual ~Endf6FileStore(void);

      void clear();

      frendy::NuclearDataObject get_nucl_data_obj(vector<string> endf_file_text);
      frendy::NuclearDataObject get_nucl_data_obj(string endf_name, Integer mat_no, Real temp);
      frendy::NuclearDataObject get_nucl_data_obj(string endf_name, Integer mat_no);
      frendy::NuclearDataObject get_nucl_data_obj(string endf_name);

      frendy::NuclearDataObject get_nucl_data_obj_no_cov(vector<string> endf_file_text);
      frendy::NuclearDataObject get_nucl_data_obj_no_cov(string endf_name, Integer mat_no, Real temp);
      frendy::NuclearDataObject get_nucl_data_obj_no_cov(string endf_name, Integer mat_no);
      frendy::NuclearDataObject get_nucl_data_obj_no_cov(string endf_name);

      frendy::NuclearDataObject get_nucl_data_obj_cov(vector<string> endf_file_text);
      frendy::NuclearDataObject get_nucl_data_obj_cov(string endf_name, Integer mat_no, Real temp);
      frendy::NuclearDataObject get_nucl_data_obj_cov(string endf_name, Integer mat_no);
      frendy::NuclearDataObject get_nucl_data_obj_cov(string endf_name);

      frendy::NuclearDataObject get_nucl_data_obj_xs_only(vector<string> endf_file_text);
      frendy::NuclearDataObject get_nucl_data_obj_xs_only(string endf_name, Integer mat_no, Real temp);
      frendy::NuclearDataObject get_nucl_data_obj_xs_only(string endf_name, Integer mat_no);
      frendy::NuclearDataObject get_nucl_data_obj_xs_only(string endf_name);
  };
}

#endif // ENDF6_FILE_STORE_H
