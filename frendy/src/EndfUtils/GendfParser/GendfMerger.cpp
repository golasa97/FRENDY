#include "EndfUtils/GendfParser/GendfMerger.hpp"

using namespace frendy;

//constructor
GendfMerger::GendfMerger(void)
{
  clear();
}

//destructor
GendfMerger::~GendfMerger(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfMerger::clear()
{
  mat_new_gendf = -1;

  za_new_gendf = -1.0;
  awr_new_gendf = -1.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfMerger::initialize_data1(vector<vector<vector<Real> > >& data1,
                                   int ng, int nsigz, int pl_no)
{
  data1.resize(ng+1); //MF=6 MT=18 has IG=0-NGN
  for(int i=0; i<ng+1; i++)
  {
    data1[i].resize(nsigz);
    for(int j=0; j<nsigz; j++)
    {
      data1[i][j].resize(pl_no);
      for(int k=0; k<pl_no; k++)
      {
        data1[i][j][k] = 0.0;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfMerger::initialize_data2(vector<vector<vector<vector<Real> > > >& data2,
                                   int ng, int nsigz, int pl_no)
{
  data2.resize(ng+1); //MF=6 MT=18 has IG=0-NGN
  for(int i=0; i<ng+1; i++)
  {
    data2[i].resize(nsigz);
    for(int j=0; j<nsigz; j++)
    {
      data2[i][j].resize(pl_no);
      for(int k=0; k<pl_no; k++)
      {
        data2[i][j][k].resize(ng);
        for(int l=0; l<ng; l++)
        {
          data2[i][j][k][l] = 0.0;
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMFxxParserBase GendfMerger::merge_read_obj_micro(vector<GMFxxParserBase>& read_obj,
                                                  vector<Real> weight_vec)
{
  GMFxxParserBase read_obj_merge = merge_read_obj(read_obj, weight_vec);

  int i_max = static_cast<int>(weight_vec.size());
  if( i_max == 0 )
  {
    return read_obj_merge;
  }

  Real weight_tot = 0.0;
  for(int i=0; i<i_max; i++)
  {
    weight_tot += weight_vec[i];
  }

  if( fabs(weight_tot) > min_value )
  {
    weight_tot = 1.0 / weight_tot;
  }

  read_obj_merge.multiply_coef(weight_tot);

  return read_obj_merge;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMFxxParserBase GendfMerger::merge_read_obj(vector<GMFxxParserBase>& read_obj,
                                            vector<Real> weight_vec)
{
  check_data(read_obj);

  GMFxxParserBase read_obj_new;
  read_obj_new.clear();

  int i_max = static_cast<int>(read_obj.size());
  if( i_max==0 )
  {
    return read_obj_new;
  }

  vector<vector<vector<Real> > >          data1_new;
  vector<vector<vector<vector<Real> > > > data2_new;
  vector<vector<vector<Real> > >().swap(data1_new);
  vector<vector<vector<vector<Real> > > >().swap(data2_new);
  
  int init_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    if( read_obj[i].get_mat_no() == unassigned_mat_no ||
        read_obj[i].get_mt_no()  == unassigned_mt_no )
    {
      continue;
    }

    read_obj[i].multiply_coef(weight_vec[i]);

    if( init_flg == 0 )
    {
      init_flg = 1;

      read_obj_new.set_mat_no(mat_new_gendf);
      read_obj_new.set_mf_no(read_obj[i].get_mf_no());
      read_obj_new.set_mt_no(read_obj[i].get_mt_no());

      read_obj_new.set_ZA(za_new_gendf);
      read_obj_new.set_AWR(awr_new_gendf);

      read_obj_new.set_NL(read_obj[i].get_NL());
      read_obj_new.set_NSIGZ(read_obj[i].get_NSIGZ());
      read_obj_new.set_LR(read_obj[i].get_LR());
      read_obj_new.set_NGN(read_obj[i].get_NGN());

      read_obj_new.set_TEMP(read_obj[i].get_TEMP());

      initialize_data1(data1_new, read_obj[i].get_NGN(), read_obj[i].get_NSIGZ(), read_obj[i].get_NL());
      initialize_data2(data2_new, read_obj[i].get_NGN(), read_obj[i].get_NSIGZ(), read_obj[i].get_NL());
    }

    vector<int>                             ig_add    = read_obj[i].get_IG();
    vector<vector<vector<Real> > >          data1_add = read_obj[i].get_DATA1();
    vector<vector<vector<vector<Real> > > > data2_add = read_obj[i].get_DATA2_NG2_fill_data();

    int j_max = static_cast<int>(data1_add.size());
    for(int j=0; j<j_max; j++)
    {
      if( ig_add[j] < 0 )
      {
        continue;
      }

      int k_max = static_cast<int>(data1_add[j].size());
      for(int k=0; k<k_max; k++)
      {
        int l_max = static_cast<int>(data1_add[j][k].size());
        for(int l=0; l<l_max; l++)
        {
          data1_new[ig_add[j]][k][l] += data1_add[ig_add[j]][k][l];
        }
      }
    }

    j_max = static_cast<int>(data2_add.size());
    for(int j=0; j<j_max; j++)
    {
      if( ig_add[j] < 0 )
      {
        continue;
      }

      int k_max = static_cast<int>(data2_add[j].size());
      for(int k=0; k<k_max; k++)
      {
        int l_max = static_cast<int>(data2_add[j][k].size());
        for(int l=0; l<l_max; l++)
        {
          int m_max = static_cast<int>(data2_add[j][k][l].size());
          for(int m=0; m<m_max; m++)
          {
            data2_new[ig_add[j]][k][l][m] += data2_add[ig_add[j]][k][l][m];
          }
        }
      }
    }
    vector<vector<vector<Real> > >().swap(data1_add);
    vector<vector<vector<vector<Real> > > >().swap(data2_add);
  }

  vector<Integer> ig_new, ng2_new, ig2lo_new;

  int j_max = static_cast<int>(data2_new.size());
  ig_new.resize(j_max);
  ng2_new.resize(j_max);
  ig2lo_new.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    ig_new[j]    = j;
    ig2lo_new[j] = 1;

    int k_max = static_cast<int>(data2_new[j].size());
    for(int k=0; k<k_max; k++)
    {
      int l_max = static_cast<int>(data2_new[j][k].size());
      for(int l=0; l<l_max; l++)
      {
        int m_max = static_cast<int>(data2_new[j][k][l].size());
        ng2_new[j] = m_max;
      }
    }
  }
  read_obj_new.set_NG2(ng2_new);
  read_obj_new.set_IG2LO(ig2lo_new);
  read_obj_new.set_IG(ig_new);
  
  read_obj_new.set_DATA1(data1_new);
  read_obj_new.set_DATA2_NG2(data2_new);
  read_obj_new.remove_DATA2_NG2_zero_data();
  vector<vector<vector<Real> > >().swap(data1_new);
  vector<vector<vector<vector<Real> > > >().swap(data2_new);

  return read_obj_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMFxxParserBase GendfMerger::merge_read_obj_micro(vector<GMFxxParserBase>& read_obj,
                                                  vector<Real> weight_vec,
                                                  vector<GMF03Parser>& gmf03_obj)
{
  GMFxxParserBase read_obj_merge = merge_read_obj(read_obj, weight_vec, gmf03_obj);

  int i_max = static_cast<int>(weight_vec.size());
  if( i_max == 0 )
  {
    return read_obj_merge;
  }

  Real weight_tot = 0.0;
  for(int i=0; i<i_max; i++)
  {
    weight_tot += weight_vec[i];
  }

  if( fabs(weight_tot) > min_value )
  {
    weight_tot = 1.0 / weight_tot;
  }

  read_obj_merge.multiply_coef(weight_tot);

  return read_obj_merge;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMFxxParserBase GendfMerger::merge_read_obj(vector<GMFxxParserBase>& read_obj,
                                            vector<Real> weight_vec,
                                            vector<GMF03Parser>& gmf03_obj)
{
  check_data(read_obj);

  GMFxxParserBase read_obj_new;
  read_obj_new.clear();

  int i_max = static_cast<int>(read_obj.size());
  if( i_max==0 )
  {
    return read_obj_new;
  }
  else if( static_cast<int>(gmf03_obj.size()) != i_max )
  {
    string class_name = "GendfMerger";
    string func_name  = "merge_read_obj(vector<GMFxxParserBase>& read_obj, vector<Real> weight_vec, vector<GMF03Parser> gmf03_obj)";

    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << static_cast<int>(gmf03_obj.size());
    string str_data01 = "The number of read_obj data  : " + oss01.str();
    string str_data02 = "The number of gmf03_obj data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("");
    err_com.push_back("The number of read_obj data must be equal to that of gmf03_obj data.");
    err_com.push_back("Please check these data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  vector<vector<vector<Real> > >          data1_new, xs_sum;
  vector<vector<vector<vector<Real> > > > data2_new;
  vector<vector<vector<Real> > >().swap(xs_sum);
  vector<vector<vector<Real> > >().swap(data1_new);
  vector<vector<vector<vector<Real> > > >().swap(data2_new);
  
  int init_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    if( read_obj[i].get_mat_no() == unassigned_mat_no ||
        read_obj[i].get_mt_no()  == unassigned_mt_no )
    {
      continue;
    }

    if( read_obj[i].get_mat_no() != gmf03_obj[i].get_mat_no() ||
        read_obj[i].get_mt_no()  != gmf03_obj[i].get_mt_no() )
    {
      string class_name = "GendfMerger";
      string func_name  = "merge_read_obj(vector<GMFxxParserBase>& read_obj, vector<Real> weight_vec, vector<GMF03Parser> gmf03_obj)";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << read_obj[i].get_mf_no();
      oss02 << read_obj[i].get_mat_no();
      oss03 << read_obj[i].get_mt_no();
      oss04 << gmf03_obj[i].get_mat_no();
      oss05 << gmf03_obj[i].get_mt_no();
      string str_data01 = "MF number of read_obj : " + oss01.str();
      string str_data02 = "  read_obj  : MAT = " + oss02.str() + " / MT = " + oss03.str();
      string str_data03 = "  gmf03_obj : MAT = " + oss04.str() + " / MT = " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      err_com.push_back("The MAT and/or MT number of read_obj are different to those of gmf03_obj.");
      err_com.push_back("Please check these data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    read_obj[i].multiply_coef(weight_vec[i]);

    if( init_flg == 0 )
    {
      init_flg = 1;

      read_obj_new.set_mat_no(mat_new_gendf);
      read_obj_new.set_mf_no(read_obj[i].get_mf_no());
      read_obj_new.set_mt_no(read_obj[i].get_mt_no());

      read_obj_new.set_ZA(za_new_gendf);
      read_obj_new.set_AWR(awr_new_gendf);

      int ngn   = read_obj[i].get_NGN();
      int nsigz = read_obj[i].get_NSIGZ();
      int nl    = read_obj[i].get_NL();

      read_obj_new.set_NGN(ngn);
      read_obj_new.set_NSIGZ(nsigz);
      read_obj_new.set_NL(nl);
      read_obj_new.set_LR(read_obj[i].get_LR());

      read_obj_new.set_TEMP(read_obj[i].get_TEMP());


      initialize_data1(xs_sum,    ngn, nsigz, nl);
      initialize_data1(data1_new, ngn, nsigz, nl);
      initialize_data2(data2_new, ngn, nsigz, nl);
    }

    vector<int>                             ig_xs     = gmf03_obj[i].get_IG();
    vector<vector<vector<Real> > >          xs_add    = gmf03_obj[i].get_SIG();
    vector<int>                             ig_add    = read_obj[i].get_IG();
    vector<vector<vector<Real> > >          data1_add = read_obj[i].get_DATA1();
    vector<vector<vector<vector<Real> > > > data2_add = read_obj[i].get_DATA2_NG2_fill_data();

    int j_max = static_cast<int>(data1_add.size());
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(data1_add[j].size());
      for(int k=0; k<k_max; k++)
      {
        int l_max = static_cast<int>(data1_add[j][k].size());
        for(int l=0; l<l_max; l++)
        {
          data1_new[j][k][l] += data1_add[ig_add[j]][k][l];
        }
      }
    }

    j_max = static_cast<int>(data2_add.size());
    if( static_cast<int>(xs_add.size()) != j_max )
    {
      string class_name = "GendfMerger";
      string func_name  = "merge_read_obj(vector<GMFxxParserBase>& read_obj, vector<Real> weight_vec, vector<GMF03Parser> gmf03_obj)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
      oss01 << read_obj[i].get_mf_no();
      oss02 << read_obj[i].get_mat_no();
      oss03 << read_obj[i].get_mt_no();
      oss04 << j_max;
      oss05 << gmf03_obj[i].get_mat_no();
      oss06 << gmf03_obj[i].get_mt_no();
      oss07 << static_cast<int>(xs_add.size());
      string str_data01 = "MF number of read_obj : " + oss01.str();
      string str_data02 = "  read_obj  : MAT = " + oss02.str() + " / MT = " + oss03.str()
                        + " : ein = " + oss04.str();
      string str_data03 = "  gmf03_obj : MAT = " + oss05.str() + " / MT = " + oss06.str()
                        + " : ein = " + oss07.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      err_com.push_back("The number of number of incident energy (ein) is different.");
      err_com.push_back("Please check these data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(data2_add[j].size());
      for(int k=0; k<k_max; k++)
      {
        int l_max = static_cast<int>(data2_add[j][k].size());
        for(int l=0; l<l_max; l++)
        {
          Real xs_val = xs_add[j][k][l];
          xs_sum[ig_xs[j]][k][l] += xs_val;
          int m_max = static_cast<int>(data2_add[j][k][l].size());
          for(int m=0; m<m_max; m++)
          {
            data2_new[ig_add[j]][k][l][m] += data2_add[j][k][l][m] * xs_val;
          }
        }
      }
    }
    vector<vector<vector<Real> > >().swap(data1_add);
    vector<vector<vector<vector<Real> > > >().swap(data2_add);
  }

  vector<Integer> ig_new, ng2_new, ig2lo_new;

  int j_max = static_cast<int>(data2_new.size());
  ig_new.resize(j_max);
  ng2_new.resize(j_max);
  ig2lo_new.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    ig_new[j]    = j;
    ig2lo_new[j] = 0;

    int k_max = static_cast<int>(data2_new[j].size());
    for(int k=0; k<k_max; k++)
    {
      int l_max = static_cast<int>(data2_new[j][k].size());
      for(int l=0; l<l_max; l++)
      {
        Real xs_coef = 1.0;
        if( fabs(xs_sum[j][k][l]) > min_value )
        {
          xs_coef = 1.0 / xs_sum[j][k][l];
        }

        int m_max = static_cast<int>(data2_new[j][k][l].size());
        ng2_new[j] = m_max;
        for(int m=0; m<m_max; m++)
        {
          data2_new[j][k][l][m] *= xs_coef;
        }
      }
    }
  }
  
  read_obj_new.set_NG2(ng2_new);
  read_obj_new.set_IG2LO(ig2lo_new);
  read_obj_new.set_IG(ig_new);

  read_obj_new.set_DATA1(data1_new);
  read_obj_new.set_DATA2_NG2(data2_new);
  read_obj_new.remove_DATA2_NG2_zero_data();
  vector<vector<vector<Real> > >().swap(data1_new);
  vector<vector<vector<vector<Real> > > >().swap(data2_new);

  return read_obj_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMFxxParserBase GendfMerger::merge_read_obj_weight_flux_micro
                               (vector<GMFxxParserBase>& read_obj,  vector<Real> weight_vec,
                                vector<vector<vector<vector<Real> > > >& flux_vec)
{
  GMFxxParserBase read_obj_merge = merge_read_obj_weight_flux(read_obj, weight_vec, flux_vec);

  int i_max = static_cast<int>(weight_vec.size());
  if( i_max == 0 )
  {
    return read_obj_merge;
  }

  Real weight_tot = 0.0;
  for(int i=0; i<i_max; i++)
  {
    weight_tot += weight_vec[i];
  }

  if( fabs(weight_tot) > min_value )
  {
    weight_tot = 1.0 / weight_tot;
  }

  read_obj_merge.multiply_coef(weight_tot);

  return read_obj_merge;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMFxxParserBase GendfMerger::merge_read_obj_weight_flux
                               (vector<GMFxxParserBase>& read_obj,  vector<Real> weight_vec,
                                vector<vector<vector<vector<Real> > > >& flux_vec)
{
  GMFxxParserBase read_obj_merge;
  read_obj_merge.clear();

  int i_max = static_cast<int>(read_obj.size());
  if( i_max == 0 )
  {
    return read_obj_merge;
  }

  vector<GMF03Parser> gmf03_vec;
  gmf03_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
     GMFxxParserBase read_obj_mod = read_obj[i];
     read_obj_mod.set_mf_no(3);
     gmf03_vec[i].set_read_obj(read_obj_mod);
     read_obj_mod.clear();

    gmf03_vec[i].set_SIG(flux_vec[i]); //SIG -> FLUX
  }

  read_obj_merge = merge_read_obj(read_obj, weight_vec, gmf03_vec);
  vector<GMF03Parser>().swap(gmf03_vec);
  
  return read_obj_merge;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfMerger::check_data(vector<GMFxxParserBase>& read_obj)
{
  string class_name = "GendfMerger";
  string func_name  = "check_data";

  int i_max = static_cast<int>(read_obj.size());
  if( i_max < 1 )
  {
    vector<string> err_com;
    if( i_max == 0 )
    {
      err_com.push_back("The number of GMFxxParserBase data is zero.");
    }
    else
    {
      err_com.push_back("The number of GMFxxParserBase data is one.");
    }
    err_com.push_back("");
    err_com.push_back("This program cannot interpoalte the GENDF data.");
    err_com.push_back("Please check the GENDF data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int init_pos = -1;
  for(int i=0; i<i_max; i++)
  {
    if( read_obj[i].get_mt_no() == unassigned_mt_no )
    {
      continue;
    }

    if( init_pos < 0 )
    {
      init_pos = i;
    }


    if( read_obj[init_pos].get_mf_no()  != read_obj[i].get_mf_no() )
    {
      ostringstream oss_i0, oss_i1, oss_i_max;
      oss_i0    << init_pos+1;
      oss_i1    << i+1;
      oss_i_max << i_max;
      string str_data_i0 = "Position (init_pos) : " + oss_i0.str() + " / " + oss_i_max.str();
      string str_data_i1 = "Position (i)        : " + oss_i1.str() + " / " + oss_i_max.str();

      ostringstream oss_mat01, oss_mat02, oss_mf01,  oss_mf02, oss_mt01, oss_mt02,
                    oss_za01,  oss_za02,  oss_awr01, oss_awr02;

      oss_mat01 << read_obj[init_pos].get_mat_no();
      oss_mat02 << read_obj[i].get_mat_no();
      oss_mf01  << read_obj[init_pos].get_mf_no();
      oss_mf02  << read_obj[i].get_mf_no();
      oss_mt01  << read_obj[init_pos].get_mt_no();
      oss_mt02  << read_obj[i].get_mt_no();
      oss_za01  << setw(7) << std::showpoint << std::scientific << read_obj[init_pos].get_ZA();
      oss_za02  << setw(7) << std::showpoint << std::scientific << read_obj[i].get_ZA();
      oss_awr01 << setw(7) << std::showpoint << std::scientific << read_obj[init_pos].get_AWR();
      oss_awr02 << setw(7) << std::showpoint << std::scientific << read_obj[i].get_AWR();

      string str_data01 = "read_obj[init_pos]: MAT=" + oss_mat01.str()
                        + ", MF=" + oss_mf01.str() + ", MT=" + oss_mt01.str()
                        + ", ZA=" + oss_za01.str() + ", AWR=" + oss_awr01.str();
      string str_data02 = "read_obj[i]       : MAT=" + oss_mat02.str()
                        + ", MF=" + oss_mf02.str() + ", MT=" + oss_mt02.str()
                        + ", ZA=" + oss_za02.str() + ", AWR=" + oss_awr02.str();

      vector<string> err_com;
      err_com.push_back(str_data_i0);
      err_com.push_back(str_data_i1);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("");

      err_com.push_back("MF is different.");
      err_com.push_back("Please check the interpolation data (read_obj[init_pos], read_obj[i]).");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( read_obj[init_pos].get_NL()    != read_obj[i].get_NL()     ||
        read_obj[init_pos].get_NSIGZ() != read_obj[i].get_NSIGZ( ) ||
        read_obj[init_pos].get_NGN()   != read_obj[i].get_NGN() )
    {
      ostringstream oss_i0, oss_i1, oss_i_max;
      oss_i0    << init_pos+1;
      oss_i1    << i+1;
      oss_i_max << i_max;
      string str_data_i0 = "Position (init_pos) : " + oss_i0.str() + " / " + oss_i_max.str();
      string str_data_i1 = "Position (i)        : " + oss_i1.str() + " / " + oss_i_max.str();

      ostringstream oss_mat01, oss_mat02, oss_mf, oss_mt,
                    oss_nl01, oss_nl02, oss_nsigz01,  oss_nsigz02, oss_lr01, oss_lr02,
                    oss_ngn01, oss_ngn02;

      oss_mat01   << read_obj[init_pos].get_mat_no();
      oss_mat02   << read_obj[i].get_mat_no();
      oss_mf      << read_obj[init_pos].get_mf_no();
      oss_mt      << read_obj[init_pos].get_mt_no();
      oss_nl01    << read_obj[init_pos].get_NL();
      oss_nl02    << read_obj[i].get_NL();
      oss_nsigz01 << read_obj[init_pos].get_NSIGZ();
      oss_nsigz02 << read_obj[i].get_NSIGZ();
      oss_lr01    << read_obj[init_pos].get_LR();
      oss_lr02    << read_obj[i].get_LR();
      oss_ngn01   << read_obj[init_pos].get_NGN();
      oss_ngn02   << read_obj[i].get_NGN();

      string str_data00 = "MAT=" + oss_mat01.str() + " / " + oss_mat02.str()
                        + ", MF=" + oss_mf.str() + ", MT=" + oss_mt.str();
      string str_data01 = "read_obj[init_pos]: NL=" + oss_nl01.str() + ", NSIGZ=" + oss_nsigz01.str()
                        + ", LR=" + oss_lr01.str() + ", NGN=" + oss_ngn01.str();
      string str_data02 = "read_obj[i]       : NL=" + oss_nl02.str() + ", NSIGZ=" + oss_nsigz02.str()
                        + ", LR=" + oss_lr02.str() + ", NGN=" + oss_ngn02.str();

      vector<string> err_com;
      err_com.push_back(str_data_i0);
      err_com.push_back(str_data_i1);
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("");
      err_com.push_back("NL, NSIGZ, and/or NGN is different.");
      err_com.push_back("Please check the GENDF data (read_obj[init_pos], read_obj[i])");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( fabs(read_obj[init_pos].get_TEMP() - read_obj[i].get_TEMP()) > 1.0E-3 )
    {
      ostringstream oss_i0, oss_i1, oss_i_max;
      oss_i0    << init_pos+1;
      oss_i1    << i+1;
      oss_i_max << i_max;
      string str_data_i0 = "Position (init_pos) : " + oss_i0.str() + " / " + oss_i_max.str();
      string str_data_i1 = "Position (i)        : " + oss_i1.str() + " / " + oss_i_max.str();

      ostringstream oss_mat01, oss_mf01, oss_mt01, oss_temp01,
                    oss_mat02, oss_mf02, oss_mt02, oss_temp02, oss_pos;
      oss_mat01    << read_obj[init_pos].get_mat_no();
      oss_mf01     << read_obj[init_pos].get_mf_no();
      oss_mt01     << read_obj[init_pos].get_mt_no();
      oss_mat02    << read_obj[i].get_mat_no();
      oss_mf02     << read_obj[i].get_mf_no();
      oss_mt02     << read_obj[i].get_mt_no();
      oss_temp01 << setw(7) << std::showpoint << std::scientific << read_obj[init_pos].get_TEMP();
      oss_temp02 << setw(7) << std::showpoint << std::scientific << read_obj[i].get_TEMP();

      string str_data11 = "    MAT        : " + oss_mat01.str();
      string str_data12 = "    MF         : " + oss_mf01.str();
      string str_data13 = "    MT         : " + oss_mt01.str();
      string str_data14 = "    Tmperature : " + oss_temp01.str();
      string str_data21 = "    MAT        : " + oss_mat02.str();
      string str_data22 = "    MF         : " + oss_mf02.str();
      string str_data23 = "    MT         : " + oss_mt02.str();
      string str_data24 = "    Tmperature : " + oss_temp02.str();

      vector<string> err_com;
      err_com.push_back(str_data_i0);
      err_com.push_back("  read_obj[init_pos]");
      err_com.push_back(str_data11);
      err_com.push_back(str_data12);
      err_com.push_back(str_data13);
      err_com.push_back(str_data14);
      err_com.push_back(str_data_i1);
      err_com.push_back("  read_obj[i]");
      err_com.push_back(str_data21);
      err_com.push_back(str_data22);
      err_com.push_back(str_data23);
      err_com.push_back(str_data24);
      err_com.push_back("");
      err_com.push_back("The temperature is different.");
      err_com.push_back("Please check the GENDF data (read_obj[init_pos], read_obj[i])");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF03Parser GendfMerger::merge_gmf03_data(vector<GMF03Parser>& gmf03, vector<Real> weight_vec)
{
  int i_max = static_cast<int>(gmf03.size());
  GMF03Parser gmf_obj;
  gmf_obj.clear();
  if( i_max == 0 )
  {
    return gmf_obj;
  }

  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf03[i].get_read_obj();
  }

  GMFxxParserBase read_obj_new = merge_read_obj(read_obj, weight_vec);
  read_obj.clear();

  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF03Parser GendfMerger::merge_gmf03_data(vector<GMF03Parser>& gmf03, vector<Real> weight_vec,
                                          vector<GMF03Parser>& gmf03_fis)
{
  int i_max = static_cast<int>(gmf03.size());
  GMF03Parser gmf_obj;
  gmf_obj.clear();
  if( i_max == 0 )
  {
    return gmf_obj;
  }

  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf03[i].get_read_obj();
  }

  GMFxxParserBase read_obj_new = merge_read_obj(read_obj, weight_vec, gmf03_fis);
  read_obj.clear();

  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF05Parser GendfMerger::merge_gmf05_data(vector<GMF05Parser>& gmf05, vector<Real> weight_vec)
{
  int i_max = static_cast<int>(gmf05.size());
  GMF05Parser gmf_obj;
  gmf_obj.clear();
  if( i_max == 0 )
  {
    return gmf_obj;
  }

  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf05[i].get_read_obj();
  }

  GMFxxParserBase read_obj_new = merge_read_obj(read_obj, weight_vec);
  read_obj.clear();

  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF05Parser GendfMerger::merge_gmf05_data(vector<GMF05Parser>& gmf05, vector<Real> weight_vec,
                                          vector<GMF03Parser>& gmf03)
{
  int i_max = static_cast<int>(gmf05.size());
  GMF05Parser gmf_obj;
  gmf_obj.clear();
  if( i_max == 0 )
  {
    return gmf_obj;
  }

  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf05[i].get_read_obj();
  }

  GMFxxParserBase read_obj_new = merge_read_obj(read_obj, weight_vec, gmf03);
  read_obj.clear();

  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF05Parser GendfMerger::merge_gmf05_data_weight_flux
                           (vector<GMF05Parser>& gmf05, vector<Real> weight_vec,
                            vector<vector<vector<vector<Real> > > >& flux_vec)
{
  int i_max = static_cast<int>(gmf05.size());
  GMF05Parser gmf_obj;
  gmf_obj.clear();
  if( i_max == 0 )
  {
    return gmf_obj;
  }

  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf05[i].get_read_obj();
  }

  GMFxxParserBase read_obj_new = merge_read_obj_weight_flux(read_obj, weight_vec, flux_vec);
  read_obj.clear();

  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF06Parser GendfMerger::merge_gmf06_data(vector<GMF06Parser>& gmf06, vector<Real> weight_vec)
{
  int i_max = static_cast<int>(gmf06.size());
  GMF06Parser gmf_obj;
  gmf_obj.clear();
  if( i_max == 0 )
  {
    return gmf_obj;
  }

  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf06[i].get_read_obj();
  }

  GMFxxParserBase read_obj_new = merge_read_obj(read_obj, weight_vec);
  read_obj.clear();

  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF06Parser GendfMerger::merge_gmf06_data(vector<GMF06Parser>& gmf06, vector<Real> weight_vec,
                                          vector<GMF03Parser>& gmf03)
{
  int i_max = static_cast<int>(gmf06.size());
  GMF06Parser gmf_obj;
  gmf_obj.clear();
  if( i_max == 0 )
  {
    return gmf_obj;
  }

  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf06[i].get_read_obj();
  }

  GMFxxParserBase read_obj_new = merge_read_obj(read_obj, weight_vec, gmf03);
  read_obj.clear();

  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF06Parser GendfMerger::merge_gmf06_data_weight_flux
                           (vector<GMF06Parser>& gmf06, vector<Real> weight_vec,
                            vector<vector<vector<vector<Real> > > >& flux_vec)
{
  int i_max = static_cast<int>(gmf06.size());
  GMF06Parser gmf_obj;
  gmf_obj.clear();
  if( i_max == 0 )
  {
    return gmf_obj;
  }

  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf06[i].get_read_obj();
  }

  GMFxxParserBase read_obj_new = merge_read_obj_weight_flux(read_obj, weight_vec, flux_vec);
  read_obj.clear();

  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF13Parser GendfMerger::merge_gmf13_data(vector<GMF13Parser>& gmf13, vector<Real> weight_vec)
{
  int i_max = static_cast<int>(gmf13.size());
  GMF13Parser gmf_obj;
  gmf_obj.clear();
  if( i_max == 0 )
  {
    return gmf_obj;
  }

  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf13[i].get_read_obj();
  }

  GMFxxParserBase read_obj_new = merge_read_obj(read_obj, weight_vec);
  read_obj.clear();

  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF16Parser GendfMerger::merge_gmf16_data(vector<GMF16Parser>& gmf16, vector<Real> weight_vec)
{
  int i_max = static_cast<int>(gmf16.size());
  GMF16Parser gmf_obj;
  gmf_obj.clear();
  if( i_max == 0 )
  {
    return gmf_obj;
  }

  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf16[i].get_read_obj();
  }

  GMFxxParserBase read_obj_new = merge_read_obj(read_obj, weight_vec);
  read_obj.clear();

  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF16Parser GendfMerger::merge_gmf16_data(vector<GMF16Parser>& gmf16, vector<Real> weight_vec,
                                          vector<GMF03Parser>& gmf03)
{
  int i_max = static_cast<int>(gmf16.size());
  GMF16Parser gmf_obj;
  gmf_obj.clear();
  if( i_max == 0 )
  {
    return gmf_obj;
  }

  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf16[i].get_read_obj();
  }

  GMFxxParserBase read_obj_new = merge_read_obj(read_obj, weight_vec, gmf03);
  read_obj.clear();

  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Integer> GendfMerger::get_unit_mt_list(vector<vector<Integer> >& mt_list)
{
  vector<Integer> mt_list_all, mt_list_new;
  mt_list_all.size();
  mt_list_new.size();

  int i_max = static_cast<Integer>(mt_list.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<Integer>(mt_list[i].size());
    for(int j=0; j<j_max; j++)
    {
      if( mt_list[i][j] != 0 && mt_list[i][j] != unassigned_mt_no )
      {
        mt_list_all.push_back(mt_list[i][j]);
      }
    }
  }

  sort(mt_list_all.begin(), mt_list_all.end());

  i_max = static_cast<int>(mt_list_all.size());
  Integer mt_old = unassigned_mt_no;
  for(int i=0; i<i_max; i++)
  {
    if( mt_list_all[i] != mt_old )
    {
      mt_list_new.push_back(mt_list_all[i]);
      mt_old = mt_list_all[i];
    }
  }

  return mt_list_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GendfParser GendfMerger::merge_gendf_data(vector<GendfParser>& gendf_vec, vector<Real> weight_vec)
{
  int i_max = static_cast<int>(gendf_vec.size());
  GendfParser gendf_new;
  gendf_new.clear();
  if( i_max == 0 )
  {
    return gendf_new;
  }

  if( static_cast<int>(weight_vec.size()) != i_max )
  {
    string class_name = "GendfMerger";
    string func_name  = "merge_gendf_data(vector<GendfParser>& gendf_vec, vector<Real> weight_vec)";

    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << static_cast<int>(weight_vec.size());
    string str_data01 = "The number of gendf_vec data  : " + oss01.str();
    string str_data02 = "The number of weight_vec data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("");
    err_com.push_back("The number of gendf_vec data must be equal to that of weight_vec data.");
    err_com.push_back("Please check these data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  GMF01MT451Parser  mf01_mt451_data = gendf_vec[0].get_mf01_mt451_data();
  mf01_mt451_data.set_mat_no(mat_new_gendf);
  mf01_mt451_data.set_ZA(za_new_gendf);
  mf01_mt451_data.set_AWR(awr_new_gendf);
  gendf_new.set_mf01_mt451_data(mf01_mt451_data);
  mf01_mt451_data.clear();


  vector<vector<Integer> > mt_list03, mt_list05, mt_list06, mt_list13, mt_list16;
  mt_list03.resize(i_max);
  mt_list05.resize(i_max);
  mt_list06.resize(i_max);
  mt_list13.resize(i_max);
  mt_list16.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    mt_list03[i] = gendf_vec[i].get_mt_list(3);
    mt_list05[i] = gendf_vec[i].get_mt_list(5);
    mt_list06[i] = gendf_vec[i].get_mt_list(6);
    mt_list13[i] = gendf_vec[i].get_mt_list(13);
    mt_list16[i] = gendf_vec[i].get_mt_list(16);
  }

  vector<Integer> mt_list03_uni = get_unit_mt_list(mt_list03);
  vector<Integer> mt_list05_uni = get_unit_mt_list(mt_list05);
  vector<Integer> mt_list06_uni = get_unit_mt_list(mt_list06);
  vector<Integer> mt_list13_uni = get_unit_mt_list(mt_list13);
  vector<Integer> mt_list16_uni = get_unit_mt_list(mt_list16);
  vector<vector<Integer> >().swap(mt_list03);
  vector<vector<Integer> >().swap(mt_list05);
  vector<vector<Integer> >().swap(mt_list06);
  vector<vector<Integer> >().swap(mt_list13);
  vector<vector<Integer> >().swap(mt_list16);

  //For MF=3
  int mt_no = static_cast<int>(mt_list03_uni.size());
  vector<GMF03Parser> gmf03_new;
  gmf03_new.resize(mt_no);
  for(int p=0; p<mt_no; p++)
  {
    vector<GMF03Parser> gmf_obj;
    gmf_obj.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      gmf_obj[i] = gendf_vec[i].get_mf03_data(mt_list03_uni[p]);
    }

    if( mt_list03_uni[p] < 452 && mt_list03_uni[p] > 456 )
    {
      gmf03_new[p] = merge_gmf03_data(gmf_obj, weight_vec);
    }
    else //nu-d, nu-p, and nu-tot (MT=452-456)
    {
      vector<GMF03Parser> gmf_fis_obj;
      gmf_fis_obj.resize(i_max);
      for(int i=0; i<i_max; i++)
      {
        gmf_fis_obj[i] = gendf_vec[i].get_mf03_data(18);
      }

      gmf03_new[p] = merge_gmf03_data(gmf_obj, weight_vec, gmf_fis_obj);
      vector<GMF03Parser>().swap(gmf_fis_obj);
    }
    vector<GMF03Parser>().swap(gmf_obj);
  }
  
  gendf_new.set_mf03_data(gmf03_new);
  vector<GMF03Parser>().swap(gmf03_new);
  
  //For MF=5
  mt_no = static_cast<int>(mt_list05_uni.size());
  vector<GMF05Parser> gmf05_new;
  gmf05_new.resize(mt_no);
  for(int p=0; p<mt_no; p++)
  {
    vector<GMF05Parser> gmf05_obj;
    gmf05_obj.resize(i_max);
    if( mt_list05_uni[p] != 18 )
    {
      for(int i=0; i<i_max; i++)
      {
        gmf05_obj[i] = gendf_vec[i].get_mf05_data(mt_list05_uni[p]);
      }
      gmf05_new[p] = merge_gmf05_data(gmf05_obj, weight_vec);
    }
    else //Fission spectrum chi (MT=18)
    {
      vector<vector<vector<vector<Real> > > > flux_vec;
      flux_vec.resize(i_max);
      for(int i=0; i<i_max; i++)
      {
        flux_vec[i]  = gendf_vec[i].get_mf03_data(18).get_FLUX();
        gmf05_obj[i] = gendf_vec[i].get_mf05_data(mt_list05_uni[p]);
      }
      gmf05_new[p] = merge_gmf05_data_weight_flux(gmf05_obj, weight_vec, flux_vec);
      vector<vector<vector<vector<Real> > > >().swap(flux_vec);
    }
    vector<GMF05Parser>().swap(gmf05_obj);
  }

  gendf_new.set_mf05_data(gmf05_new);
  vector<GMF05Parser>().swap(gmf05_new); 

  //For MF=6
  mt_no = static_cast<int>(mt_list06_uni.size());
  vector<GMF06Parser> gmf06_new;
  gmf06_new.resize(mt_no);
  for(int p=0; p<mt_no; p++)
  {
    vector<GMF06Parser> gmf06_obj;
    gmf06_obj.resize(i_max);
    if( mt_list06_uni[p] != 18 )
    {
      for(int i=0; i<i_max; i++)
      {
        gmf06_obj[i] = gendf_vec[i].get_mf06_data(mt_list06_uni[p]);
      }
      gmf06_new[p] = merge_gmf06_data(gmf06_obj, weight_vec);
    }
    else
    {
      vector<vector<vector<vector<Real> > > > flux_vec;
      flux_vec.resize(i_max);
      for(int i=0; i<i_max; i++)
      {
        flux_vec[i]  = gendf_vec[i].get_mf03_data(18).get_FLUX();
        gmf06_obj[i] = gendf_vec[i].get_mf06_data(mt_list06_uni[p]);
      }
      gmf06_new[p] = merge_gmf06_data_weight_flux(gmf06_obj, weight_vec, flux_vec);
      vector<vector<vector<vector<Real> > > >().swap(flux_vec);
    }
    vector<GMF06Parser>().swap(gmf06_obj);
  }

  gendf_new.set_mf06_data(gmf06_new);
  vector<GMF06Parser>().swap(gmf06_new);


  //For MF=13
  mt_no = static_cast<int>(mt_list13_uni.size());
  vector<GMF13Parser> gmf13_new;
  gmf13_new.resize(mt_no);
  for(int p=0; p<mt_no; p++)
  {
    vector<GMF13Parser> gmf_obj;
    gmf_obj.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      gmf_obj[i] = gendf_vec[i].get_mf13_data(mt_list13_uni[p]);
    }

    gmf13_new[p] = merge_gmf13_data(gmf_obj, weight_vec);
    vector<GMF13Parser>().swap(gmf_obj);
  }

  gendf_new.set_mf13_data(gmf13_new);
  vector<GMF13Parser>().swap(gmf13_new);


  //For MF=16
  mt_no = static_cast<int>(mt_list16_uni.size());
  vector<GMF16Parser> gmf16_new;
  gmf16_new.resize(mt_no);
  for(int p=0; p<mt_no; p++)
  {
    vector<GMF16Parser> gmf16_obj;
    gmf16_obj.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      gmf16_obj[i] = gendf_vec[i].get_mf16_data(mt_list16_uni[p]);
    }

    gmf16_new[p] = merge_gmf16_data(gmf16_obj, weight_vec);
    vector<GMF16Parser>().swap(gmf16_obj);
  }

  gendf_new.set_mf16_data(gmf16_new);
  vector<GMF16Parser>().swap(gmf16_new);

  return gendf_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<GMF03Parser> GendfMerger::transform_gmf13_to_gmf03(vector<GMF13Parser>& gmf13_obj)
{
  vector<GMF03Parser> gmf03_obj;

  int i_max = static_cast<int>(gmf13_obj.size());
  gmf03_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( gmf13_obj[i].get_mat_no() == unassigned_mat_no ||
        gmf13_obj[i].get_mt_no()  == unassigned_mt_no )
    {
      gmf03_obj[i].clear();
      continue;
    }

    GMFxxParserBase read_obj = gmf13_obj[i].get_read_obj();
    read_obj.set_mf_no(3);

    gmf03_obj[i].set_read_obj(read_obj);
    read_obj.clear();
  }

  return gmf03_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfMerger::modify_total_xs(GMF03Parser& mf03_mt001_obj, vector<int>& ig_dif_vec,
                                  vector<vector<vector<Real> > >& xs_dif_vec)
{
  vector<int>                    ig_tot_vec  = mf03_mt001_obj.get_IG();
  vector<vector<vector<Real> > > xs_tot_vec  = mf03_mt001_obj.get_SIG();

  int ng = static_cast<int>(mf03_mt001_obj.get_NGN());
  ig_tot_vec.resize(ng+1);

  int tot_max = static_cast<int>(ig_tot_vec.size());
  int dif_max = static_cast<int>(ig_dif_vec.size());


  if( dif_max == 0 )
  {
    return;
  }
  else if( tot_max == 0 )
  {
    string class_name = "GendfMerger";
    string func_name  = "modify_total_xs";

    vector<string> err_com;
    err_com.push_back("The all total cross section is zero.");
    err_com.push_back("Please check the data");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int pos_tot = 0;
  int pos_dif = 0;
  for(int i=0; i<=ng; i++)
  {
     while( pos_tot < tot_max )
     {
       if( ig_tot_vec[pos_tot] > 0 )
       {
          break;
       }
       pos_tot++;
     }
     while( pos_dif < dif_max )
     {
       if( ig_dif_vec[pos_dif] > 0 )
       {
          break;
       }
       pos_dif++;
     }


    if( pos_tot == tot_max || pos_dif == dif_max )
    {
      break;
    }

    if( ig_tot_vec[pos_tot] == i && ig_dif_vec[pos_dif] == i )
    {
      int j_max = static_cast<int>(xs_tot_vec[pos_tot].size());
      for(int j=0; j<j_max; j++)
      {
        int k_max = static_cast<int>(xs_tot_vec[pos_tot][j].size());
        for(int k=0; k<k_max; k++)
        {
          xs_tot_vec[pos_tot][j][k] += xs_dif_vec[pos_dif][j][k];
        }
      }
      pos_tot++;
      pos_dif++;
    }
    else if( ig_tot_vec[pos_tot] == i )
    {
      pos_tot++;
      continue;
    }
    else if( ig_dif_vec[pos_dif] == i )
    {
      pos_dif++;

      string class_name = "GendfMerger";
      string func_name  = "modify_total_xs";

      ostringstream oss01, oss02;
      oss01 << i;
      oss02 << ng;
      string str_data01 = "Energy grid   : " + oss01.str() + " / " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("");
      err_com.push_back("This energy grid is only found in additional cross section data.");
      err_com.push_back("This situation is not considered in this probram.");
      err_com.push_back("Please check these data or modify this program.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  mf03_mt001_obj.set_SIG(xs_tot_vec);
  vector<vector<vector<Real> > >().swap(xs_tot_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

