#ifndef ACE_DATA_COLLECTOR_H
#define ACE_DATA_COLLECTOR_H

#ifdef _WIN32
#include <msdirent.h>
#include <io.h>
#else
#include <dirent.h>
#include <unistd.h>
#endif

#include "CommonUtils/TimeUtils.hpp"
#include "ContinuousEnergyXSUtils/AceDataWriter/FastAceDataWriter.hpp"
#include "ContinuousEnergyXSUtils/AceDataWriter/ThermalScatterAceDataWriter.hpp"
#include "ContinuousEnergyXSUtils/AceDataWriter/DosimetryAceDataWriter.hpp"
#include "ContinuousEnergyXSUtils/AceDataParser/FastAceDataParser.hpp"
#include "ContinuousEnergyXSUtils/AceDataParser/ThermalScatterAceDataParser.hpp"
#include "ContinuousEnergyXSUtils/AceDataParser/DosimetryAceDataParser.hpp"

namespace frendy
{
  class AceDataCollector
  {
    private:
      frendy::ErrorManager err_obj;
      frendy::StringUtils  str_obj;

      static const int max_line_no     = 10000000; //1E7

      vector<string> alphabet_list;

      vector<Real>   awr_nat_list, awr_list;
      vector<int>    zaid_list;
      vector<string> xsdir_header_list;

      vector<string> ace_file_list;
      vector<int>    mat_list;

      int            calc_mode;
      int            output_ace_file_mode;
      string         output_ace_file_name;
      string         output_xsdir_name;
      string         ace_dir_name;
      string         mod_suffix;

      void set_awr_nat_list();
      void set_data_check();

      void search_ace_data_file(string dir_name);
      int  check_ace_file_name(string file_name);
      void modify_ace_file_list_order();
 
      vector<string> copy_ace_file(string file_name);

      void read_ace_data(vector<string>& text);

      void write_ace_file(ofstream& fout, string& ace_output, vector<string>& text,
                          int ele_no, int alpha_no);

      void modify_file_name_route(string ace_output, string& xsdir_data);

      void set_xsdir_header_list();
      vector<string> get_awr_list();
      void get_zaid_awr_list(vector<int>& z_sort, vector<vector<int> >&  zaid_sort,
                             vector<vector<Real> >& awr_sort);

    public:
      //constructor
      AceDataCollector(void);

      //destructor
      virtual ~AceDataCollector(void);

      static const int collect_mode       = 1;
      static const int individual_mode    = 2;

      static const int fast_ace_mode      = 1;
      static const int thermal_ace_mode   = 2;
      static const int dosimetry_ace_mode = 3;

      void collect_ace_file();

      int  read_mat_data(string file_name);
      void modify_suffix_id(string& line_data, string suffix_new);

      void clear();

      //Setter
      void set_calc_mode(int int_val);
      void set_output_ace_file_mode(int int_val);
      void set_output_ace_file_name(string str_data);
      void set_output_xsdir_name(string str_data);
      void set_ace_dir_name(string str_data);
      void set_mod_suffix_id(string str_data);

      //Getter
      int    get_calc_mode();
      int    get_output_ace_file_mode();
      string get_output_ace_file_name();
      string get_output_xsdir_name();
      string get_ace_dir_name();
      string get_mod_suffix_id();
  };
}

#endif //ACE_DATA_COLLECTOR_H
