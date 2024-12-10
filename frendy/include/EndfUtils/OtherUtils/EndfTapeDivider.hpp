#ifndef ENDF_TAPE_DIVIDER_H
#define ENDF_TAPE_DIVIDER_H

#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/EndfFileReader.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF01MT451Parser.hpp"

namespace frendy
{
  class EndfTapeDivider
  {
    private:

    protected:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;

#ifdef DEBUG_MODE
  public:
#endif

      string endf_file_end;

      string                           file_name;      //Name of endf file
      string                           label_data;
      vector<Integer>                  mat_list;       //MAT data at each data
      vector<vector<Real> >            temp_list;      //Temp data at each data
      vector<vector<vector<string> > > endf_data_each; //Text data at each material and temperature

      //read endf file
      void read_endf_file();

      //Check whether file_name is the ENDF formatted file or not.
      void check_endf_format();

      //add endf data in each mat
      void add_endf_data_each_mat(vector<vector<string> >& endf_data_each_mat,
                                  Integer mat_cur, Integer mat_pre, vector<string>& clip_data);

      //Search material data in mat_list
      int search_mat_data(Integer mat_no);

      //Check temperature data at each material data
      void set_endf_data_each_temp(vector<vector<string> >& endf_data_each_mat);

      //get all file data
      vector<string> get_file_data(Integer mat, vector<string>& endf_data_all, int& line_no);
      vector<string> get_file_data(vector<string>& endf_data_all, int& line_no);

    public:
      //clear all data
      void clear();  

      //constructor
      EndfTapeDivider(void);

      //destructor
      virtual ~EndfTapeDivider(void);

      //read MF and MT number from endf_data_all
      void read_mat_no(string& data, Integer& mat_int, Integer& mf_int, Integer& mt_int);
      void read_mat_no(string& data, Integer& mat_int);

      //read the endf file name from user input
      void set_file_name(string& name);

      //return the endf file name which read by set_file_name
      string get_file_name();

      //return the endf tape label
      string get_label_data();

      //return all text data of the endf file
      vector<string> get_data_all();

      //return text data of the part of the endf file(MAT)
      vector<string>          get_data(Integer mat);
      vector<string>          get_data(Integer mat, int  file_no);
      vector<string>          get_designated_temp_data(Integer mat, Real temp);
      vector<string>          get_data_without_specified_mat(Integer mat);
      vector<vector<string> > get_data_all(Integer mat);

      //Get closed tempearture data not exceeded temp.
      vector<string>          get_nearby_temp_data(Integer mat, Real temp);
      void                    get_nearby_mat_temp_pos(Integer mat, Real temp,
                                                      int& mat_pos, int& temp_pos);

      //return material and temperature list
      vector<Integer>       get_mat_list();
      vector<Real>          get_temp_list(Integer mat);
      vector<vector<Real> > get_temp_list();
  }; 
}

#endif //ENDF_TAPE_DIVIDER_H
