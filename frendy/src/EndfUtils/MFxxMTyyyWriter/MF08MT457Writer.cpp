#include "EndfUtils/MFxxMTyyyWriter/MF08MT457Writer.hpp"

using namespace frendy;

//constructor
MF08MT457Writer::MF08MT457Writer(void)
{
  clear();
}

//destructor
MF08MT457Writer::~MF08MT457Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT457Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, LIS, LISO, NST, NSP
  line_data = efw_obj.write_cont
              (par_obj.get_ZA(), par_obj.get_AWR(), par_obj.get_LIS(), par_obj.get_LISO(),
               par_obj.get_NST(), par_obj.get_NSP());
  text.push_back(line_data);
  line_data.clear();

  if( par_obj.get_NST() == 0 )
  {
    write_nst00();
  }
  if( par_obj.get_NST() == 1 )
  {
    write_nst01();
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT457Writer::write_nst00() 
{
  vector<string> str_vec;

  vector<Real> real_vec;
  int vec_no = static_cast<int>(par_obj.get_E_X().size()) * 2;
  real_vec.resize(vec_no);

  int ele_no = 0;
  for(int i=0; i<vec_no; i+=2)
  {
    real_vec[i]   = par_obj.get_E_X()[ele_no];
    real_vec[i+1] = par_obj.get_D_E_X()[ele_no];
    ele_no++;
  }

  str_vec = efw_obj.write_list(par_obj.get_T_HALF(), par_obj.get_D_T_HALF(), 0, 0, vec_no, 0, real_vec);

  int i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(str_vec[i]);
  }


  vec_no = static_cast<int>(par_obj.get_RTYP0().size()) * 6;
  real_vec.resize(vec_no);

  ele_no = 0;
  for(int i=0; i<vec_no; i+=6)
  {
    real_vec[i]   = par_obj.get_RTYP0()[ele_no];
    real_vec[i+1] = par_obj.get_RFS()[ele_no];
    real_vec[i+2] = par_obj.get_Q()[ele_no];
    real_vec[i+3] = par_obj.get_D_Q()[ele_no];
    real_vec[i+4] = par_obj.get_BR()[ele_no];
    real_vec[i+5] = par_obj.get_D_BR()[ele_no];
    ele_no++;
  }

  str_vec = efw_obj.write_list(par_obj.get_SPI(), par_obj.get_PAR(), 0, 0, vec_no, vec_no/6, real_vec);

  i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(str_vec[i]);
  }


  for(int i=0; i<static_cast<int>(par_obj.get_NSP()); i++)
  {
    vec_no = 6;
    real_vec.resize(vec_no);
    real_vec[0] = par_obj.get_FD()[i];
    real_vec[1] = par_obj.get_D_FD()[i];
    real_vec[2] = par_obj.get_ER_AV()[i];
    real_vec[3] = par_obj.get_D_ER_AV()[i];
    real_vec[4] = par_obj.get_FC()[i];
    real_vec[5] = par_obj.get_D_FC()[i];

    str_vec = efw_obj.write_list(0.0, par_obj.get_STYP()[i], par_obj.get_LCON()[i], 0,
                                 vec_no, par_obj.get_NER()[i], real_vec);

    int j_max = static_cast<int>(str_vec.size());
    for(int j=0; j<j_max; j++)
    {
      text.push_back(str_vec[j]);
    }


    if( par_obj.get_LCON()[i] != 1 )
    {
      for(int j=0; j<static_cast<int>(par_obj.get_NER()[i]); j++)
      {
        vec_no = 12;
        if( static_cast<Integer>(round(par_obj.get_RIS()[i][j])) == unassigned_data_val )
        {
          vec_no = 4;
        }
        else if( static_cast<Integer>(round(par_obj.get_RICC()[i][j])) == unassigned_data_val )
        {
          vec_no = 6;
        }
        else if( static_cast<Integer>(round(par_obj.get_RICK()[i][j])) == unassigned_data_val )
        {
          vec_no = 8;
        }
        else if( static_cast<Integer>(round(par_obj.get_RICL()[i][j])) == unassigned_data_val )
        {
          vec_no = 10;
        }
        real_vec.resize(vec_no);
        real_vec[ 0] = par_obj.get_RTYP1()[i][j];
        real_vec[ 1] = par_obj.get_TYPE()[i][j];
        real_vec[ 2] = par_obj.get_RI()[i][j];
        real_vec[ 3] = par_obj.get_D_RI()[i][j];

        if( vec_no > 4 )
        {
          real_vec[ 4] = par_obj.get_RIS()[i][j];
          real_vec[ 5] = par_obj.get_D_RIS()[i][j];
        }

        if( vec_no > 6 )
        {
          real_vec[ 6] = par_obj.get_RICC()[i][j];
          real_vec[ 7] = par_obj.get_D_RICC()[i][j];
        }

        if( vec_no > 8 )
        {
          real_vec[ 8] = par_obj.get_RICK()[i][j];
          real_vec[ 9] = par_obj.get_D_RICK()[i][j];
        }

        if( vec_no > 10 )
        {
          real_vec[10] = par_obj.get_RICL()[i][j];
          real_vec[11] = par_obj.get_D_RICL()[i][j];
        }

        str_vec = efw_obj.write_list(par_obj.get_ER()[i][j], par_obj.get_D_ER()[i][j], 0, 0,
                                     vec_no, 0, real_vec);

        int k_max = static_cast<int>(str_vec.size());
        for(int k=0; k<k_max; k++)
        {
          text.push_back(str_vec[k]);
        }
      }
    }


    if( par_obj.get_LCON()[i] != 0 )
    {
      int nbt_no = static_cast<int>(par_obj.get_NBT_RP()[i].size());
          vec_no = static_cast<int>(par_obj.get_RP_TAB()[i].size());
      str_vec = efw_obj.write_tab1(par_obj.get_RTYP2()[i], 0.0, 0, par_obj.get_LCOV()[i], nbt_no, vec_no,
                                   par_obj.get_NBT_RP()[i], par_obj.get_INT_RP()[i],
                                   par_obj.get_E_INT_RP()[i], par_obj.get_RP_TAB()[i]);

      int j_max = static_cast<int>(str_vec.size());
      for(int j=0; j<j_max; j++)
      {
        text.push_back(str_vec[j]);
      }

      if( par_obj.get_LCOV()[i] != 0 )
      {
        vec_no = static_cast<int>(par_obj.get_E_K()[i].size()) * 2;
        real_vec.resize(vec_no);

        ele_no = 0;
        for(int j=0; j<vec_no; j+=2)
        {
          real_vec[j]   = par_obj.get_E_K()[i][ele_no];
          real_vec[j+1] = par_obj.get_F_K()[i][ele_no];
          ele_no++;
        }

        str_vec = efw_obj.write_list(0.0, 0.0, 0, par_obj.get_LB()[i], vec_no, vec_no/2, real_vec);

        int k_max = static_cast<int>(str_vec.size());
        for(int k=0; k<k_max; k++)
        {
          text.push_back(str_vec[k]);
        }
      }
    }
  }
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT457Writer::write_nst01() 
{
  vector<string> str_vec;


  vector<Real> real_vec;
  int vec_no = 6;
  real_vec.resize(vec_no);
  for(int i=0; i<vec_no; i++)
  {
    real_vec[i] = 0.0;
  }
  str_vec = efw_obj.write_list(0.0, 0.0, 0, 0, vec_no, 0, real_vec);

  int i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(str_vec[i]);
  }

  vec_no = 6;
  real_vec.resize(vec_no);
  for(int i=0; i<vec_no; i++)
  {
    real_vec[i] = 0.0;
  }
  str_vec = efw_obj.write_list(par_obj.get_SPI(), par_obj.get_PAR(), 0, 0, vec_no, 0, real_vec);

  i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(str_vec[i]);
  }

  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF08MT457Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF08MT457Writer::get_endf_text_data(MF08MT457Parser& MF08mt457parser_obj)
{
  clear();
  par_obj = MF08mt457parser_obj;

  write_endf();
  return text;
}

