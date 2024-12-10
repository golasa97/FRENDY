#include "EndfUtils/GendfWriter/GMFxxWriterBase.hpp"

using namespace frendy;

//constructor
GMFxxWriterBase::GMFxxWriterBase(void)
{
  clear();
}

//destructor
GMFxxWriterBase::~GMFxxWriterBase(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMFxxWriterBase::write_gendf()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), par_obj.get_mf_no(), par_obj.get_mt_no());

  //Line No.01
  //ZA, AWR
  line_data = efw_obj.write_cont(par_obj.get_ZA(),    par_obj.get_AWR(), par_obj.get_NL(),
                                 par_obj.get_NSIGZ(), par_obj.get_LR(),  par_obj.get_NGN());
  text.push_back(line_data);

  vector<vector<vector<Real> > >          DATA1 = par_obj.get_DATA1();
  vector<vector<vector<vector<Real> > > > DATA2 = par_obj.get_DATA2_NG2();

  int g_max = static_cast<int>(DATA1.size());
  if( g_max == 0 )
  {
    //Modify DATA1
    g_max = static_cast<int>(DATA2.size());
    DATA1.resize(g_max);
    for(int g=0; g<g_max; g++)
    {
      int i_max = static_cast<int>(DATA2[g].size());
      DATA1[g].resize(i_max);
      for(int i=0; i<i_max; i++)
      {
        int j_max = static_cast<int>(DATA2[g][i].size());
        DATA1[g][i].resize(j_max);
        for(int j=0; j<j_max; j++)
        {
          DATA1[g][i][j] = 0.0;
        }
      }
    }
  }


  int ig2lo_pre = 0;
  for(int g=0; g<g_max; g++)
  {
    if( static_cast<int>(DATA1[g].size()) == 0 )
    {
      //NJOY2016 manual Sec. 8.17 GENDF Output
      //The last LIST record in the sequence is the one with IG=NGN.
      //It must be given even if its contents are zero. 
      if( g < g_max - 1 )
      {
        continue;
      }
    }

    vector<Real> e_vec;
    int i_max = static_cast<int>(DATA1[g].size());
    for(int i=0; i<i_max; i++)
    {
      int j_max = static_cast<int>(DATA1[g][i].size());
      for(int j=0; j<j_max; j++)
      {
        e_vec.push_back(DATA1[g][i][j]);
      }
    }

    int k_max = static_cast<int>(par_obj.get_NG2()[g]) - 1;
    for(int k=0; k<k_max; k++)
    {
      i_max = static_cast<int>(DATA2[g].size());
      for(int i=0; i<i_max; i++)
      {
        int j_max = static_cast<int>(DATA2[g][i].size());
        for(int j=0; j<j_max; j++)
        {
          e_vec.push_back(DATA2[g][i][j][k]);
        }
      }
    }

    //Line No.02
    //TEMP, DATA1 and DATA2
    vector<string> str_vec;
    int ele_no = static_cast<int>(e_vec.size());
    if( ele_no != 0 && k_max > 0 )
    {
      str_vec = efw_obj.write_list(par_obj.get_TEMP(),     0.0,    par_obj.get_NG2()[g],
                                   par_obj.get_IG2LO()[g], ele_no, par_obj.get_IG()[g], e_vec);
      ig2lo_pre = par_obj.get_IG2LO()[g];
    }
    else //if( ele_no == 0 && g == g_max - 1 )
    {
      //NJOY2016 manual Sec. 8.17 GENDF Output
      //The last LIST record in the sequence is the one with IG=NGN.
      //It must be given even if its contents are zero. 
      e_vec.resize(2);
      e_vec[0] = 1.0; //dummy flux
      e_vec[1] = 0.0; //dummy xs matrix
      if( static_cast<int>(DATA1[g].size()) > 0 )
      {
        e_vec[0] = DATA1[g][0][0];
      }
      str_vec = efw_obj.write_list(par_obj.get_TEMP(), 0.0, 2, ig2lo_pre, 2, g_max-1, e_vec);
    }
    e_vec.clear();

    i_max = static_cast<int>(str_vec.size());
    for(int i=0; i<i_max; i++)
    {
      text.push_back(str_vec[i]);
    }
    clr_vec.clear_vec_array1_str(str_vec);
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);
  line_data.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMFxxWriterBase::clear()
{
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>  GMFxxWriterBase::get_gendf_text_data(GMFxxParserBase parser_obj)
{
  clear();
  par_obj = parser_obj;

  write_gendf();
  return text;
}

