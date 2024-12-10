#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "Config/FrendyTypes.hpp"
#include "ErrorManager.hpp"

using namespace std;

namespace frendy
{
  class StringUtils
  {
    private:
      frendy::ErrorManager    err_obj;

      string                  space_list;
      string                  linefeed_list;
      string                  quote_list;
      string                  quote_single;
      string                  quote_double;
      vector<int>             quote_pos_list;

      string                  bracket_sta, curly_bracket_sta, angled_bracket_sta,
                              bracket_end, curly_bracket_end, angled_bracket_end;

      int                     data_no, data_no_tot;
      vector<string>          text_data;
      vector<vector<string> > div_data;

      void                 divide_text_data();
      void                 divide_string_data(string str_data);
      vector<vector<int> > get_quote_pos_data(vector<string>& text_vec);

      void                 divide_string_data_by_bracket();
    
    public:
      //constructor
      StringUtils(void);

      //destructor
      virtual ~StringUtils(void);

      void clear();

      string trim_space(string str_data);
      string trim_data(string str_data, string trim_character);
      string replace_space(string str_data, string replace_data);

      string basename(string str_data); //Similar to the basename command in Linux
      string basename(string str_data, string suffix);
      string basename_without_suffix(string str_data);
      string remove_suffix(string str_data, string suffix);
      string remove_after_space(string str_data);

      string get_formatted_string_data(string str_data, int char_no);
      string get_formatted_real_data(Real real_data, int char_no);
      string get_formatted_int_data(Integer int_data, int char_no);

      string         get_merged_string_vector_data(vector<string> str_vec);
      vector<string> get_merged_string_vector_data(vector<string> str_vec, int data_no);

      void           add_string_vector_data(vector<string>& text, vector<string> text_add);

      vector<string> divide_string_data(string str_data, int data_width);
      vector<string> divide_string_data(string str_data, int data_width, int max_char_no);

      vector<string> divide_string_data_by_linefeed_code(string str_data);
      vector<string> divide_string_data_by_space_code(string str_data);

      void           check_string_vector_data_end(vector<string>& text, int line_no,
                                                  string class_name, string func_name);

      int            get_no_space_string_length(string str_data);

      void           skip_no_space_string_data(vector<string>& str_vec, int& line_no);

      void           set_file_name(string file_name);
      void           set_text_data(vector<string>& str_vec);
      vector<string> get_text_data();

      int            get_data_no();
      string         get_div_string_data();
      vector<string> get_div_string_vec();
      string         get_div_string_data(int pos);
      vector<string> get_div_string_vec(int pos);
      vector<vector<string> > get_div_string_vec_all();

      vector<string> divide_minus_value(vector<string> str_vec);

      string get_string_num(int int_val, int int_max);

      vector<string> read_data(vector<string>& text_vec, int& line_no);
      vector<string> read_data(vector<string>& text_vec, int& line_no, int& str_no);
  };
}

#endif // STRING_UTILS_H
