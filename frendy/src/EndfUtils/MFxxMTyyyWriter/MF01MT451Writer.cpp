#include "EndfUtils/MFxxMTyyyWriter/MF01MT451Writer.hpp"

using namespace frendy;

//constructor
MF01MT451Writer::MF01MT451Writer(void)
{
  clear();
}

//destructor
MF01MT451Writer::~MF01MT451Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT451Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, LRP, LFI, NLIB, NMOD
  line_data = efw_obj.write_cont(par_obj.get_ZA(),  par_obj.get_AWR(),  par_obj.get_LRP(), 
                                 par_obj.get_LFI(), par_obj.get_NLIB(), par_obj.get_NMOD());
  text.push_back(line_data);

  //Line No.02
  //ELIS, STA, LIS, LISO, 0, NFOR
  line_data = efw_obj.write_cont(par_obj.get_ELIS(), par_obj.get_STA(), par_obj.get_LIS(),
                                 par_obj.get_LISO(), 0,                 par_obj.get_NFOR());
  text.push_back(line_data);

  if( par_obj.get_NFOR() >= 6 ) //For ENDF-6 format
  {
    //Line No.03
    //AWI, EMAX, LREL, 0, NSUB, NVER
    line_data = efw_obj.write_cont(par_obj.get_AWI(), par_obj.get_EMAX(), par_obj.get_LREL(), 
                                   0,                 par_obj.get_NSUB(), par_obj.get_NVER());
    text.push_back(line_data);
  }

  //Line No.04
  //TEMP, ERROR, LDRV, 0, NWD, NXC
  line_data = efw_obj.write_cont(par_obj.get_TEMP(), par_obj.get_ERROR(), par_obj.get_LDRV(), 0, 
                                 par_obj.get_NWD(), par_obj.get_NXC());
  text.push_back(line_data);

  int i_max = static_cast<int>(par_obj.get_NWD());
  str_vec = par_obj.get_comment_line();
  for(int i=0; i<i_max; i++)
  {
    line_data = efw_obj.write_text(str_vec[i]);
    text.push_back(line_data);
  }

  i_max = static_cast<int>(par_obj.get_NXC());
  vector<Integer> mf  = par_obj.get_MF();
  vector<Integer> mt  = par_obj.get_MT();
  vector<Integer> nc  = par_obj.get_NC();
  vector<Integer> mod = par_obj.get_MOD();
  for(int i=0; i<i_max; i++)
  {
    line_data = efw_obj.write_cont(0.0, 0.0, mf[i], mt[i], nc[i], mod[i]); 
    //Replace " 0.00000000 0.00000000" to blank.
    line_data = line_data.replace(0,22, "                      ");
    text.push_back(line_data);
  }
  mf.clear();
  mt.clear();
  nc.clear();
  mod.clear();

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  clr_obj.clear_vec_array1_str(str_vec);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT451Writer::mod_nc_data()
{
  //line no = text size - mt_end
  Integer line_no = static_cast<Integer>(text.size()) - 1;

  Integer         mod_flg = -1;
  vector<Integer> mf      = par_obj.get_MF();
  vector<Integer> mt      = par_obj.get_MT();
  vector<Integer> nc      = par_obj.get_NC();
  for(int i=0; i<static_cast<int>(mf.size()); i++)
  {
    if( mf[i] == 1 && mt[i] == 451 )
    {
      if( nc[i] != line_no )
      {
        nc[i]   = line_no;
        mod_flg = 1;
      }
      break;
    }
  }

  if( mod_flg > 0 )
  {
    par_obj.set_NC(nc);
    write_endf();
  }
  mf.clear();
  mt.clear();
  nc.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF01MT451Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF01MT451Writer::get_endf_text_data(MF01MT451Parser& mf01mt451parser_obj)
{
  clear();
  par_obj = mf01mt451parser_obj;

  write_endf();
  mod_nc_data();
  return text;
}

