#ifndef READ_THERMR_INPUT_H
#define READ_THERMR_INPUT_H

#include <boost/algorithm/string.hpp>

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "NjoyUtils/NjoyInputReader.hpp"

namespace frendy
{
  class ThermrInputReader
  {
    private:
      frendy::NjoyInputReader rn_obj;
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;

      string        input_thermr;
      string        endf_name, pendf_name_old, pendf_name_new;
      Integer       mat_endf, mat_pendf, bin_no, temp_no, opt_inelastic, opt_elastic,
                    atom_no, mt_out, opt_print;
      vector<Real8> temp;
      Real8         err, ene_max;

      void read_file_name(ifstream& fin);
      void read_card02_data(ifstream& fin);
      void read_card03_data(ifstream& fin);
      void read_card04_data(ifstream& fin);

    public:
      //constructor
      ThermrInputReader(void);

      //destructor
      virtual ~ThermrInputReader(void);

      //read input file for reconr
      void read_input(string file_name);
      void read_input(string file_name, int line_no);

      void clear();

      string        get_input_thermr();
      string        get_endf_name();
      string        get_pendf_name_old();
      string        get_pendf_name_new();
      Integer       get_mat_endf();
      Integer       get_mat_pendf();
      Integer       get_bin_no();
      Integer       get_temp_no();
      Integer       get_opt_inelastic();
      Integer       get_opt_elastic();
      Integer       get_atom_no();
      Integer       get_mt_out();
      Integer       get_opt_print();
      vector<Real8> get_temp();
      Real8         get_err();
      Real8         get_ene_max();
  }; 
}

#endif //READ_THERMR_INPUT_H
