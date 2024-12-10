#ifndef READ_GASPR_INPUT_H
#define READ_GASPR_INPUT_H

#include <boost/algorithm/string.hpp>

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "NjoyUtils/NjoyInputReader.hpp"

namespace frendy
{
  class GasprInputReader
  {
    private:
      frendy::NjoyInputReader rn_obj;
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;

      string                  input_gaspr;
      string                  endf_name, pendf_in, pendf_out;

      void read_file_name(ifstream& fin);

    public:
      //constructor
      GasprInputReader(void);

      //destructor
      virtual ~GasprInputReader(void);

      //read input file for gaspr
      void read_input(string file_name);
      void read_input(string file_name, int line_no);

      void clear();

      string                  get_input_gaspr();
      string                  get_endf_name();
      string                  get_pendf_input_name();
      string                  get_pendf_output_name();
  }; 
}

#endif //READ_GASPR_INPUT_H
