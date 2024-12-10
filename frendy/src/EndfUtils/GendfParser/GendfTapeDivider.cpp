#include "EndfUtils/GendfParser/GendfTapeDivider.hpp"

using namespace frendy;

//constructor
GendfTapeDivider::GendfTapeDivider(void)
{
  endf_file_end = "                                                                     0 0  0    0";
  clear();
}

//destructor
GendfTapeDivider::~GendfTapeDivider(void)
{
  clear();
  endf_file_end.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfTapeDivider::set_endf_data_each_temp(vector<vector<string> >& endf_data_each_mat)
{
  EndfFileReader   efr_obj;
  GMF01MT451Parser parser_obj;

  int i_max = static_cast<int>(mat_list.size());
  temp_list.resize(i_max);
  endf_data_each.resize(i_max);

  vector<string> clip_data;
  for(int i=0; i<i_max; i++)
  {
    //Devide endf data in each temperature
    int line_tot = static_cast<int>(endf_data_each_mat[i].size());
    int line_no  = 0;
    while( line_no < line_tot )
    {
      clip_data = get_file_data(endf_data_each_mat[i], line_no);
      if( static_cast<int>(clip_data.size()) > 0 )
      {
        endf_data_each[i].push_back(clip_data);

        //Get temperature data from MF=1, MT=451
        Real temp = 0.0;
        efr_obj.set_endf_data(clip_data);
        clr_obj.clear_vec_array1_str(clip_data);
        if( efr_obj.get_line_no(1, 451) > 0 )
        {
          parser_obj.set_text(efr_obj.get_data(1, 451));
          efr_obj.clear();
          temp = parser_obj.get_TEMP();
          parser_obj.clear();
        }
        temp_list[i].push_back(temp);
      }
    }
  }

  clr_obj.clear_vec_array2_str(endf_data_each_mat);
}

