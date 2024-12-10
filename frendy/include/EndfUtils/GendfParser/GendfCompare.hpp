#ifndef GENDF_COMPARE_H
#define GENDF_COMPARE_H

#include "EndfUtils/GendfParser/GendfParser.hpp"
#include "ContinuousEnergyXSUtils/AceDataCompare/AceDataCompare.hpp"

namespace frendy
{
  class GendfCompare
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::AceDataCompare comp_obj;
      frendy::GendfParser    gendf_obj_com, gendf_obj_ref;

      string class_name;

      int    comp_flg;

      void comp_gendf_file();

    public:
      //constructor
      GendfCompare(void);

      //destructor
      virtual ~GendfCompare(void);

      void clear();

      void comp_gendf_file(string gendf_name_com, string gendf_name_ref);

      void comp_gendf_file(frendy::GendfParser parse_obj_com, frendy::GendfParser parse_obj_ref);

      void comp_mf01_mt451_data(frendy::GMF01MT451Parser parse_obj_com,
                                frendy::GMF01MT451Parser parse_obj_ref);

      void comp_mf03_data(vector<frendy::GMF03Parser> parse_obj_com,
                          vector<frendy::GMF03Parser> parse_obj_ref);
      void comp_mf05_data(vector<frendy::GMF05Parser> parse_obj_com,
                          vector<frendy::GMF05Parser> parse_obj_ref);
      void comp_mf06_data(vector<frendy::GMF06Parser> parse_obj_com,
                          vector<frendy::GMF06Parser> parse_obj_ref);
      void comp_mf13_data(vector<frendy::GMF13Parser> parse_obj_com,
                          vector<frendy::GMF13Parser> parse_obj_ref);
      void comp_mf16_data(vector<frendy::GMF16Parser> parse_obj_com,
                          vector<frendy::GMF16Parser> parse_obj_ref);

      void comp_mf03_data(frendy::GMF03Parser parse_obj_com,
                          frendy::GMF03Parser parse_obj_ref);
      void comp_mf05_data(frendy::GMF05Parser parse_obj_com,
                          frendy::GMF05Parser parse_obj_ref);
      void comp_mf06_data(frendy::GMF06Parser parse_obj_com,
                          frendy::GMF06Parser parse_obj_ref);
      void comp_mf13_data(frendy::GMF13Parser parse_obj_com,
                          frendy::GMF13Parser parse_obj_ref);
      void comp_mf16_data(frendy::GMF16Parser parse_obj_com,
                          frendy::GMF16Parser parse_obj_ref);

      void set_tolerance_val(Real tolerance_val);
      Real get_tolerance_val();

      void set_comp_flg(int int_val);
      int  get_comp_flg();
  };
}

#endif // GENDF_COMPARE_H
