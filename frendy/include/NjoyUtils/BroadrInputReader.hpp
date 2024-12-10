#ifndef READ_BROADR_INPUT_H
#define READ_BROADR_INPUT_H

#include <boost/algorithm/string.hpp>

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "NjoyUtils/NjoyInputReader.hpp"

namespace frendy
{
  class BroadrInputReader
  {
    private:
      frendy::NjoyInputReader rn_obj;
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;

      string                  input_broadr;
      string                  endf_name, pendf_in, pendf_out;
      vector<Integer>         mat, temp_no, istart, istrap;
      vector<Real8>           temp_ini;
      vector<Real8>           err, err_max, err_int, dop_ene_max;
      vector<vector<Real8> >  temp;

      void read_file_name(ifstream& fin);
      void read_mat_data(ifstream& fin);
      void read_mat_no(ifstream& fin, int& mat_no, vector<string>& input_data);
      void read_err_data(ifstream& fin, int& mat_no, int& copy_flg, vector<string>& input_data);
      void read_temp_data(ifstream& fin, int& mat_no);

    public:
      //constructor
      BroadrInputReader(void);

      //destructor
      virtual ~BroadrInputReader(void);

      //read input file for broadr
      void read_input(string file_name);
      void read_input(string file_name, int line_no);

      void clear();

      string                  get_input_broadr();
      string                  get_endf_name();
      string                  get_pendf_input_name();
      string                  get_pendf_output_name();
      vector<Integer>         get_mat();
      vector<Integer>         get_temp_no();
      vector<Integer>         get_istart();
      vector<Integer>         get_istrap();
      vector<Real8>           get_temp_ini();
      vector<Real8>           get_err();
      vector<Real8>           get_err_max();
      vector<Real8>           get_err_int();
      vector<Real8>           get_dop_ene_max();
      vector<vector<Real8> >  get_temp();
  }; 
}

#endif //READ_BROADR_INPUT_H
