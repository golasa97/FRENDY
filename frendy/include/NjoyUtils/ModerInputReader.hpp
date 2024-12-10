#ifndef READ_MODER_INPUT_H
#define READ_MODER_INPUT_H

#include <boost/algorithm/string.hpp>

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "NjoyUtils/NjoyInputReader.hpp"

namespace frendy
{
  class ModerInputReader
  {
    private:
      frendy::NjoyInputReader rn_obj;
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;

      string   input_moder;
      string   pendf_in, pendf_out, tape_id;
      vector<string>   tape_in;
      vector<Integer>  mat;

      Integer  data_format_no;

      void read_file_name(ifstream& fin);
      void read_other_data(ifstream& fin);

    public:
      //constructor
      ModerInputReader(void);

      //destructor
      virtual ~ModerInputReader(void);

      //read input file for moder
      void read_input(string file_name);
      void read_input(string file_name, int line_no);

      void clear();

      string   get_input_moder();
      string   get_pendf_input_name();
      string   get_pendf_output_name();
      string   get_tape_id();
      vector<string>   get_tape_name();
      vector<Integer>  get_mat();

      Integer  get_data_format_no();
  }; 
}

#endif //READ_MODER_INPUT_H
