#ifndef ENDF_FILE_READER_H
#define ENDF_FILE_READER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"

namespace frendy
{
  class EndfFileReader
  {
    private:
      frendy::ErrorManager  err_obj;
      frendy::VectorClearer clr_obj;

      string          file_name;        //Name of endf file
      vector<string>  endf_data_all;    //All text data of endf file
      vector<string>  endf_data;        //Text data of the part of endf file(MF,MT)
      int             endf_line_no;     //Line number of the part of endf file(MF,MT)
      vector<Integer> mf_data_all;      //MF data at each line
      vector<Integer> mt_data_all;      //MT data at each line
      vector<Integer> mt_no_list;       //MT number list included in file number MF
      Integer         mat_no;

      //read endf file
      void read_endf_file();

      //clip endf file from endf_data_all to endf_data
      void clip_endf_file(Integer MF, Integer MT);

      //read MF and MT number from endf_data_all
      void read_mf_mt_no(string& data, Integer &mf_int, Integer &mt_int);
      void read_mat_no(string& data);

      //search all MT number included in file number MF.
      void  search_mt_number(Integer MF);

    public:
      //clear all data
      void clear();  

      //constructor
      EndfFileReader(void);

      //destructor
      virtual ~EndfFileReader(void);

      //read the endf file name from user input
      void set_file_name(string& name);

      //set endf text data
      void set_endf_data(vector<string>& text);

      //return the endf file name which read by set_file_name
      string get_file_name();

      //return total line number of the endf file
      int get_line_no_all();

      //return all text data of the endf file
      vector<string> get_data_all();

      //return line number of the part of the endf file(MF, MT)
      int get_line_no(Integer MF, Integer MT);

      //return text data of the part of the endf file(MF, MT)
      vector<string> get_data(Integer MF, Integer MT);

      //return initial MAT number
      Integer get_mat_no();

      //return all MT number included in file number MF.
      vector<Integer> get_mt_list(Integer MF);

      //return all MT number included in file number MF.
      vector<Integer> get_mf_list();
  }; 
}

#endif //ENDF_FILE_READER_H
