#ifndef READ_PURR_INPUT_H
#define READ_PURR_INPUT_H

#include <boost/algorithm/string.hpp>

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "NjoyUtils/NjoyInputReader.hpp"

namespace frendy
{
  class PurrInputReader
  {
    private:
      frendy::NjoyInputReader rn_obj;
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;

      static const Integer random_seed_ini = 12345;
      static const Integer sample_no_ini   = 10000;

      string        input_purr;
      string        endf_name, pendf_name_old, pendf_name_new;
      Integer       mat, temp_no, sig_zero_no, bin_no, ladder_no, opt_print, ene_grid_no;
      Integer       random_seed, sample_no; //special input for FRENDY
      string        p_tab_file_name;        //special input for FRENDY
      vector<Real8> temp, sig_zero;

      void read_file_name(ifstream& fin);
      void read_card02_data(ifstream& fin);
      void read_card03_data(ifstream& fin);
      void read_card04_data(ifstream& fin);

    public:
      //constructor
      PurrInputReader(void);

      //destructor
      virtual ~PurrInputReader(void);

      //read input file for reconr
      void read_input(string file_name);
      void read_input(string file_name, int line_no);

      void clear();

      string        get_input_purr();
      string        get_endf_name();
      string        get_pendf_name_old();
      string        get_pendf_name_new();
      Integer       get_mat();
      Integer       get_temp_no();
      Integer       get_sig_zero_no();
      Integer       get_bin_no();
      Integer       get_ladder_no();
      Integer       get_opt_print();
      Integer       get_ene_grid_no();
      Integer       get_random_seed();
      Integer       get_sample_no();
      string        get_p_tab_file_name();
      vector<Real8> get_temp();
      vector<Real8> get_sig_zero();
  }; 
}

#endif //READ_PURR_INPUT_H
