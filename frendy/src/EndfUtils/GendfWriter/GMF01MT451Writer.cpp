#include "EndfUtils/GendfWriter/GMF01MT451Writer.hpp"

using namespace frendy;

//constructor
GMF01MT451Writer::GMF01MT451Writer(void)
{
  clear();
}

//destructor
GMF01MT451Writer::~GMF01MT451Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMF01MT451Writer::write_gendf()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  string         line_data;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);


  //Line No.01
  //ZA, AWR, 0, NSIGZ, NLIB, NTW
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(), 0, par_obj.get_NSIGZ(),
                                 par_obj.get_NLIB(), par_obj.get_NTW());
  text.push_back(line_data);

  //Line No.02
  //TEMP, NGN, NGG
  vector<Real> e_vec;
  vector<Real> TITLE = par_obj.get_TITLE();
  vector<Real> SIGZ  = par_obj.get_SIGZ();
  vector<Real> EGN   = par_obj.get_EGN();
  vector<Real> EGG   = par_obj.get_EGG();

  int title_no = static_cast<int>(TITLE.size());
  int sigz_no  = static_cast<int>(SIGZ.size());
  int egn_no   = static_cast<int>(EGN.size());
  int egg_no   = static_cast<int>(EGG.size());
  e_vec.resize(title_no + sigz_no + egn_no + egg_no);

  int ele_no = 0;
  for(int i=0; i<title_no; i++)
  {
    e_vec[ele_no] = TITLE[i];
    ele_no++;
  }

  for(int i=0; i<sigz_no; i++)
  {
    e_vec[ele_no] = SIGZ[i];
    ele_no++;
  }

  for(int i=0; i<egn_no; i++)
  {
    e_vec[ele_no] = EGN[i];
    ele_no++;
  }

  for(int i=0; i<egg_no; i++)
  {
    e_vec[ele_no] = EGG[i];
    ele_no++;
  }

  vector<string> str_vec;
  str_vec = efw_obj.write_list(par_obj.get_TEMP(), 0.0, par_obj.get_NGN(), par_obj.get_NGG(),
                               ele_no, 0, e_vec);
  e_vec.clear();

  for(int i=0; i<static_cast<int>(str_vec.size()); i++)
  {
    text.push_back(str_vec[i]);
  }
  clr_vec.clear_vec_array1_str(str_vec);

  //line_data = efw_obj.write_mt_end();
  //text.push_back(line_data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMF01MT451Writer::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> GMF01MT451Writer::get_gendf_text_data(frendy::GMF01MT451Parser& parser_obj)
{
  clear();
  par_obj = parser_obj;

  write_gendf();
  return text;
}

