#include "EndfUtils/MFxxMTyyyWriter/MF08MT459Writer.hpp"

using namespace frendy;

//constructor
MF08MT459Writer::MF08MT459Writer(void)
{
  clear();
}

//destructor
MF08MT459Writer::~MF08MT459Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT459Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, LE
  line_data = efw_obj.write_cont
	            (par_obj.get_ZA(), par_obj.get_AWR(), par_obj.get_LE()+1, 0, 0, 0);
  text.push_back(line_data);

  for(int i=0; i<static_cast<int>(par_obj.get_LE()+1); i++)
  {
    vector<Real> real_vec;
    int vec_no = static_cast<Integer>(par_obj.get_ZAFP()[i].size()) * 4;
    real_vec.resize(vec_no);
    
    int ele_no = 0;
    for(int j=0; j<vec_no; j+=4)
    {
      real_vec[j]   = par_obj.get_ZAFP()[i][ele_no];
      real_vec[j+1] = par_obj.get_FPS()[i][ele_no];
      real_vec[j+2] = par_obj.get_YC()[i][ele_no];
      real_vec[j+3] = par_obj.get_DYC()[i][ele_no];
      ele_no++;
    }
    
    str_vec = efw_obj.write_list(par_obj.get_E()[i], 0.0, par_obj.get_I()[i], 0, vec_no, 0, real_vec);

    int j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT459Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF08MT459Writer::get_endf_text_data(MF08MT459Parser& MF08mt459parser_obj)
{
  clear();
  par_obj = MF08mt459parser_obj;

  write_endf();
  return text;
}

