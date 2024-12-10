#include "EndfUtils/MFxxMTyyyWriter/MF07MT004Writer.hpp"

using namespace frendy;

//constructor
MF07MT004Writer::MF07MT004Writer(void)
{
  clear();
}

//destructor
MF07MT004Writer::~MF07MT004Writer(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT004Writer::write_endf()
{
  clr_obj.clear_vec_array1_str(text);

  string line_data;
  vector<string> str_vec;
  clr_obj.clear_vec_array1_str(str_vec);
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, NIS
  line_data = efw_obj.write_cont(par_obj.get_ZA(), par_obj.get_AWR(),
                                 0, par_obj.get_LAT(), par_obj.get_LASYM(), 0);
  text.push_back(line_data);
  line_data.clear();

  //Line No.02
  //LLN, NS
  Integer NR = static_cast<Integer>(par_obj.get_B().size());
  str_vec = efw_obj.write_list(0.0, 0.0, par_obj.get_LLN(), 0, NR, par_obj.get_NS(), par_obj.get_B());
  for(int i=0; i<static_cast<int>(str_vec.size()); i++)
  {
    text.push_back(str_vec[i]);
  }
  clr_obj.clear_vec_array1_str(str_vec);

  if( par_obj.get_NB() == 0 ) //For ENDF-5 format
  {
    return;
  }

  NR = static_cast<Integer>(par_obj.get_NBT_BETA().size());
  str_vec = efw_obj.write_tab2(0.0, 0.0, 0, 0, NR, par_obj.get_NB(),
                               par_obj.get_NBT_BETA(), par_obj.get_INT_BETA());
  for(int i=0; i<static_cast<int>(str_vec.size()); i++)
  {
    text.push_back(str_vec[i]);
  }
  clr_obj.clear_vec_array1_str(str_vec);

  int i_max = static_cast<int>(par_obj.get_NB());
  vector<vector<Integer> >       nbt_s0   = par_obj.get_NBT_S0();
  vector<vector<Integer> >       int_s0   = par_obj.get_INT_S0();
  vector<vector<Real> >          a_int_s0 = par_obj.get_A_INT_S0();
  vector<vector<Real> >          s0_tab   = par_obj.get_S0_TAB();
  vector<vector<vector<Real> > > s        = par_obj.get_S();
  for(int i=0; i<i_max; i++)
  {
    Integer LT = static_cast<Integer>(par_obj.get_T()[i].size());
            NR = static_cast<Integer>(nbt_s0[i].size());
    Integer NP = static_cast<Integer>(a_int_s0[i].size());
    str_vec = efw_obj.write_tab1(par_obj.get_T0()[i], par_obj.get_BETA()[i], LT, 0, NR, NP,
                                 nbt_s0[i], int_s0[i], a_int_s0[i], s0_tab[i]);
    for(int j=0; j<static_cast<int>(str_vec.size()); j++)
    {
      text.push_back(str_vec[j]);
    }
    clr_obj.clear_vec_array1_str(str_vec);

    int j_max = static_cast<int>(LT);
    for(int j=0; j<j_max; j++)
    {
      NP = static_cast<Integer>(s[i][j].size());
      str_vec = efw_obj.write_list(par_obj.get_T()[i][j], par_obj.get_BETA()[i], par_obj.get_LI()[i][j],
                                   0, NP, 0, s[i][j]);
      for(int k=0; k<static_cast<int>(str_vec.size()); k++)
      {
        text.push_back(str_vec[k]);
      }
      clr_obj.clear_vec_array1_str(str_vec);
    }
  }
  clr_obj.clear_vec_array2_int(nbt_s0);
  clr_obj.clear_vec_array2_int(int_s0);
  clr_obj.clear_vec_array2_real(a_int_s0);
  clr_obj.clear_vec_array2_real(s0_tab);
  clr_obj.clear_vec_array3_real(s);

  int b_size = static_cast<int>(par_obj.get_B().size());
  vector<vector<Integer> > nbt_t   = par_obj.get_NBT_T();
  vector<vector<Integer> > int_t   = par_obj.get_INT_T();
  vector<vector<Real> >    t_int_t = par_obj.get_T_INT_T();
  vector<vector<Real> >    t_tab   = par_obj.get_T_TAB();
  for( int i=0; i<4; i++)
  {
    int read_flg = -1;
    if( i==0 )
    {
      read_flg = 1;
    }
    else
    {
      if( b_size > i*6 )
      {
        if ( par_obj.get_B()[i*6]==0 )
        {
          read_flg = 1;
        }
      }
    }

    if( read_flg > 0 )
    {
              NR = static_cast<Integer>(nbt_t[i].size());
      Integer NP = static_cast<Integer>(t_int_t[i].size());
      str_vec = efw_obj.write_tab1(0.0, 0.0, 0, 0, NR, NP, nbt_t[i], int_t[i], t_int_t[i], t_tab[i]);
      for(int j=0; j<static_cast<int>(str_vec.size()); j++)
      {
        text.push_back(str_vec[j]);
      }
      clr_obj.clear_vec_array1_str(str_vec);
    }
  }
  clr_obj.clear_vec_array2_int(nbt_t);
  clr_obj.clear_vec_array2_int(int_t);
  clr_obj.clear_vec_array2_real(t_int_t);
  clr_obj.clear_vec_array2_real(t_tab);

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF07MT004Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF07MT004Writer::get_endf_text_data(MF07MT004Parser& mf07mt004parser_obj)
{
  clear();
  par_obj = mf07mt004parser_obj;

  write_endf();
  return text;
}

