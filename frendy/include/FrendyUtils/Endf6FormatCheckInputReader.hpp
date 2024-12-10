#ifndef ENDF6_FORMAT_CHECK_INPUT_READER_H
#define ENDF6_FORMAT_CHECK_INPUT_READER_H

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/StringConverter.hpp"
#include "CommonUtils/FileCommentRemover.hpp"
#include "FrendyUtils/FrendyInputCommonUtils.hpp"

namespace frendy
{
  class Endf6FormatCheckInputReader
  {
    private:
      frendy::ErrorManager           err_obj;
      frendy::VectorClearer          clr_obj;
      frendy::StringConverter        str_obj;
      frendy::FrendyInputCommonUtils frendy_utils;

#ifdef DEBUG_MODE
  public:
#endif
      int    print_set_data_flg, print_title_flg;
      vector<string> nucl_file_name;

      void set_nucl_file_name(vector<string> input_data);

    public:

      //constructor
      Endf6FormatCheckInputReader(void);

      //destructor
      virtual ~Endf6FormatCheckInputReader(void);

      void clear();

      void read_input_data_from_input_file(string file_name);

      vector<int> read_input_data(vector<vector<string> >& input_data);
      int         read_input_data(vector<string>& input_type, vector<string>& input_data);
      int         read_input_data(string&         input_type, vector<string>& input_data);

      //Setter
      void set_nucl_file_name(string str_data);

      //Getter
      vector<string> get_nucl_file_name();
  }; 
}

#endif //ENDF6_FORMAT_CHECK_INPUT_READER_H
