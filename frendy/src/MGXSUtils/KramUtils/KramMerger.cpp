#include "MGXSUtils/KramUtils/KramMerger.hpp"

using namespace frendy;

//constructor
KramMerger::KramMerger(void)
{
  clear();
}

//destructor
KramMerger::~KramMerger(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramMerger::clear()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> KramMerger::set_weight_vec(int data_no)
{
  vector<Real> weight_vec;
  weight_vec.resize(data_no);

  for(int i=0; i<data_no; i++)
  {
    weight_vec[i] = 1.0;
  }

  return weight_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

KramCommonData KramMerger::merge_kram(vector<KramCommonData> kram_obj, int mat_no)
{
  vector<Real> weight_vec = set_weight_vec(static_cast<int>(kram_obj.size()));

  return merge_kram(kram_obj, weight_vec, mat_no); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////

KramXsnData KramMerger::merge_xsn(vector<KramXsnData> xsn_obj, int mat_no)
{
  vector<Real> weight_vec = set_weight_vec(static_cast<int>(xsn_obj.size()));

  return merge_xsn(xsn_obj, weight_vec, mat_no); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////

KramFspData KramMerger::merge_fsp(vector<KramFspData> fsp_obj, int mat_no)
{
  vector<Real> weight_vec = set_weight_vec(static_cast<int>(fsp_obj.size()));

  return merge_fsp(fsp_obj, weight_vec, mat_no); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////

KramAscData KramMerger::merge_asc(vector<KramAscData> asc_obj, int mat_no)
{
  vector<Real> weight_vec = set_weight_vec(static_cast<int>(asc_obj.size()));

  return merge_asc(asc_obj, weight_vec, mat_no); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////

KramCommonData KramMerger::merge_kram(vector<KramCommonData> kram_obj, vector<Real> weight_vec, int mat_no)
{
  int i_max = static_cast<int>(kram_obj.size());
  vector<KramXsnData> xsn_vec;
  vector<KramFspData> fsp_vec;
  vector<KramAscData> asc_vec;
  xsn_vec.resize(i_max);
  fsp_vec.resize(i_max);
  asc_vec.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    if( static_cast<int>(kram_obj[i].get_mat_list_xsn().size()) > 1 ||
        static_cast<int>(kram_obj[i].get_mat_list_fsp().size()) > 1 ||
        static_cast<int>(kram_obj[i].get_mat_list_asc().size()) > 1 )
    {
      string class_name = "KramMerger";
      string func_name  = "merge_kram(vector<KramCommonData> kram_obj, vector<Real> weight_vec, int mat_no)";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << static_cast<int>(kram_obj[i].get_mat_list_xsn().size());
      oss04 << static_cast<int>(kram_obj[i].get_mat_list_fsp().size());
      oss05 << static_cast<int>(kram_obj[i].get_mat_list_asc().size());

      vector<string> err_com;
      string str_data01 = "Position               : " + oss01.str() + " / " + oss02.str();
      err_com.push_back(str_data01);
      string str_data02 = "The number of XSN data : " + oss03.str();
      err_com.push_back(str_data02);
      for(int j=0; j<static_cast<int>(kram_obj[i].get_mat_list_xsn().size()); j++)
      {
        ostringstream oss;
        oss << kram_obj[i].get_xsn_vec()[j].get_mat_no();
        string str_data = "  MAT = " + oss.str();
        err_com.push_back(str_data);
      }

      string str_data03 = "The number of FSP data : " + oss04.str();
      err_com.push_back(str_data03);
      for(int j=0; j<static_cast<int>(kram_obj[i].get_mat_list_fsp().size()); j++)
      {
        ostringstream oss;
        oss << kram_obj[i].get_fsp_vec()[j].get_mat_no();
        string str_data = "  MAT = " + oss.str();
        err_com.push_back(str_data);
      }

      string str_data04 = "The number of ASC data : " + oss05.str();
      err_com.push_back(str_data04);
      for(int j=0; j<static_cast<int>(kram_obj[i].get_mat_list_asc().size()); j++)
      {
        ostringstream oss;
        oss << kram_obj[i].get_asc_vec()[j].get_mat_no();
        string str_data = "  MAT = " + oss.str();
        err_com.push_back(str_data);
      }
      err_com.push_back("");
      err_com.push_back("The number of XSN, FSP, ASC data must be less than or equal to one.");
      err_com.push_back("Please check the KRAM data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    xsn_vec[i].clear();
    fsp_vec[i].clear();
    asc_vec[i].clear();
    if( static_cast<int>(kram_obj[i].get_mat_list_xsn().size()) > 0 )
    {
      xsn_vec[i] = kram_obj[i].get_xsn_vec()[0];
    }
    if( static_cast<int>(kram_obj[i].get_mat_list_fsp().size()) > 0 )
    {
      fsp_vec[i] = kram_obj[i].get_fsp_vec()[0];
    }
    if( static_cast<int>(kram_obj[i].get_mat_list_asc().size()) > 0 )
    {
      asc_vec[i] = kram_obj[i].get_asc_vec()[0];
    }
  }

  KramXsnData xsn_new = merge_xsn(xsn_vec, weight_vec, mat_no);
  KramFspData fsp_new = merge_fsp(fsp_vec, weight_vec, mat_no);
  KramAscData asc_new = merge_asc(asc_vec, weight_vec, mat_no);

  KramCommonData kram_new;
  kram_new.clear();
  kram_new.set_xsn(xsn_new);
  kram_new.set_fsp(fsp_new);
  kram_new.set_asc(asc_new);

  return kram_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

KramCommonData KramMerger::merge_kram(vector<KramCommonData> kram_obj, vector<Real> weight_vec,
                                      vector<vector<Real> > flux_vec, int mat_no)
{
  //Merge Kram data without FSP
  KramCommonData kram_new = merge_kram(kram_obj, weight_vec, mat_no);

  //Calc nsf_vec
  vector<vector<Real> > nsf_vec = get_nsf_vec(kram_obj, flux_vec);

  //Merge FSP data uwing weight_vec and nsf_vec
  int i_max = static_cast<int>(kram_obj.size());
  vector<KramFspData> fsp_vec;
  fsp_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    fsp_vec[i].clear();
    if( static_cast<int>(kram_obj[i].get_mat_list_fsp().size()) > 0 )
    {
      fsp_vec[i] = kram_obj[i].get_fsp_vec()[0];
    }
  }

  KramFspData fsp_new = merge_fsp(fsp_vec, weight_vec, nsf_vec, mat_no);
  kram_new.set_fsp(fsp_new);

  return kram_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real> > KramMerger::get_nsf_vec(vector<KramCommonData>& kram_obj,
                                             vector<vector<Real> >&  flux_vec)
{
  int i_max = static_cast<int>(kram_obj.size());
  if( i_max != static_cast<int>(flux_vec.size()) )
  {
    string class_name = "KramMerger";
    string func_name  = "get_nsf_vec(vector<KramCommonData>& kram_obj, vector<vector<Real> >&  flux_vec)";

    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << static_cast<int>(flux_vec.size());

    vector<string> err_com;
    string str_data01 = "Data size of kram_obj : " + oss01.str();
    string str_data02 = "Data size of flux_vec : " + oss02.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("");
    err_com.push_back("The data size of kram_obj is different to that of flux_vec.");
    err_com.push_back("Please check kram_obj or flux_vec");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  vector<vector<Real> > nsf_vec;
  nsf_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = kram_obj[i].get_ng();
    nsf_vec[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      nsf_vec[i][j] = 0.0;
    }

    if( j_max == 0 )
    {
      continue;
    }
    else if( static_cast<int>(kram_obj[i].get_mat_list_xsn().size()) == 0 )
    {
      continue;
    }
    else if( j_max != static_cast<int>(flux_vec[i].size()) )
    {
      string class_name = "KramMerger";
      string func_name  = "get_nsf_vec(vector<KramCommonData>& kram_obj, vector<vector<Real> >&  flux_vec)";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << j_max;
      oss04 << static_cast<int>(flux_vec[i].size());

      vector<string> err_com;
      string str_data01 = "Position i               : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Number of energy groups  : " + oss03.str();
      string str_data03 = "Data size of flux_vec[i] : " + oss04.str();
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      err_com.push_back("The number of energy groups is different to the data size of flux_vec[i].");
      err_com.push_back("Please check kram_obj or flux_vec");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    vector<Real> nsf_xsn = kram_obj[i].get_xsn_vec()[0].get_xs_prod();
    for(int j=0; j<j_max; j++)
    {
      nsf_vec[i][j] = flux_vec[i][j] * nsf_xsn[j];
    }
  }

  return nsf_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

KramXsnData KramMerger::merge_xsn(vector<KramXsnData> xsn_obj, vector<Real> weight_vec, int mat_no)
{
  int ng    = 0;
  int i_max = static_cast<int>(xsn_obj.size());
  if( i_max != static_cast<int>(weight_vec.size()) )
  {
    string class_name = "KramMerger";
    string func_name  = "merge_xsn(vector<KramXsnData> xsn_obj, vector<Real> weight_vec, int mat_no)";

    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << static_cast<int>(weight_vec.size());

    vector<string> err_com;
    string str_data01 = "Data size of xsn_obj    : " + oss01.str();
    string str_data02 = "Data size of weight_vec : " + oss02.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The data size of xsn_obj is different to that of weight_vec.");
    err_com.push_back("Please check xsn_obj or weight_vec.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<i_max; i++)
  {
    if( xsn_obj[i].get_ng() > 0 )
    {
      if( ng == 0 )
      {
        ng = xsn_obj[i].get_ng();
      }
      else if( ng != xsn_obj[i].get_ng() )
      {
        string class_name = "KramMerger";
        string func_name  = "merge_xsn(vector<KramXsnData> xsn_obj, vector<Real> weight_vec, int mat_no)";

        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss01 << i+1;
        oss02 << i_max;
        oss03 << xsn_obj[i].get_mat_no();
        oss04 << ng;
        oss05 << xsn_obj[i].get_ng();

        vector<string> err_com;
        string str_data01 = "Position                       : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "Mat number                     : " + oss03.str();
        string str_data03 = "Number of multi-groups (other) : " + oss04.str();
        string str_data04 = "Number of multi-groups (this)  : " + oss05.str();
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back("");
        err_com.push_back("The number of multi-groups (ng) is different.");
        err_com.push_back("Please check the XSN data.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }

  vector<vector<Real> > xs_sc_new;
  vector<Real>          xs_prod_new, xs_abs_new, xs_tot_new, xs_fis_new;
  xs_sc_new.resize(ng);
  xs_prod_new.resize(ng);
  xs_abs_new.resize(ng);
  xs_tot_new.resize(ng);
  xs_fis_new.resize(ng);
  for(int i=0; i<ng; i++)
  {
    xs_sc_new[i].resize(ng);
    for(int j=0; j<ng; j++)
    {
      xs_sc_new[i][j] = 0.0;
    }
    xs_prod_new[i] = 0.0;
    xs_abs_new[i] = 0.0;
    xs_tot_new[i] = 0.0;
    xs_fis_new[i] = 0.0;
  }

  for(int i=0; i<i_max; i++)
  {
    if( xsn_obj[i].get_ng() == 0 || xsn_obj[i].get_mat_no() == unassigned_mat_no )
    {
      continue;
    }

    vector<vector<Real> > xs_sc   = xsn_obj[i].get_xs_sc();
    vector<Real>          xs_prod = xsn_obj[i].get_xs_prod();
    vector<Real>          xs_abs  = xsn_obj[i].get_xs_abs();
    vector<Real>          xs_tot  = xsn_obj[i].get_xs_tot();
    vector<Real>          xs_fis  = xsn_obj[i].get_xs_fis();
    for(int j=0; j<ng; j++)
    {
      for(int k=0; k<ng; k++)
      {
        xs_sc_new[j][k] += weight_vec[i] * xs_sc[j][k];
      }
      xs_prod_new[j] += weight_vec[i] * xs_prod[j];
      xs_abs_new[j]  += weight_vec[i] * xs_abs[j];
      xs_tot_new[j]  += weight_vec[i] * xs_tot[j];
      xs_fis_new[j]  += weight_vec[i] * xs_fis[j];
    }
  }

  KramXsnData xsn_data_new;
  xsn_data_new.set_mat_no(mat_no);
  xsn_data_new.set_ng(ng);
  xsn_data_new.set_xs_sc(xs_sc_new);
  xsn_data_new.set_xs_prod(xs_prod_new);
  xsn_data_new.set_xs_abs(xs_abs_new);
  xsn_data_new.set_xs_tot(xs_tot_new);
  xsn_data_new.set_xs_fis(xs_fis_new);

  return xsn_data_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

KramFspData KramMerger::merge_fsp(vector<KramFspData> fsp_obj, vector<Real> weight_vec, int mat_no)
{
  int ng    = 0;
  int i_max = static_cast<int>(fsp_obj.size());
  if( i_max != static_cast<int>(weight_vec.size()) )
  {
    string class_name = "KramMerger";
    string func_name  = "merge_fsp(vector<KramFspData> fsp_obj, vector<Real> weight_vec, int mat_no)";

    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << static_cast<int>(weight_vec.size());

    vector<string> err_com;
    string str_data01 = "Data size of fsp_obj    : " + oss01.str();
    string str_data02 = "Data size of weight_vec : " + oss02.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The data size of fsp_obj is different to that of weight_vec.");
    err_com.push_back("Please check fsp_obj or weight_vec.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<i_max; i++)
  {
    if( fsp_obj[i].get_ng() > 0 )
    {
      if( ng == 0 )
      {
        ng = fsp_obj[i].get_ng();
      }
      else if( ng != fsp_obj[i].get_ng() )
      {
        string class_name = "KramMerger";
        string func_name  = "merge_fsp(vector<KramFspData> fsp_obj, vector<Real> weight_vec, int mat_no)";

        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss01 << i+1;
        oss02 << i_max;
        oss03 << fsp_obj[i].get_mat_no();
        oss04 << ng;
        oss05 << fsp_obj[i].get_ng();

        vector<string> err_com;
        string str_data01 = "Position                       : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "Mat number                     : " + oss03.str();
        string str_data03 = "Number of multi-groups (other) : " + oss04.str();
        string str_data04 = "Number of multi-groups (this)  : " + oss05.str();
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back("");
        err_com.push_back("The number of multi-groups (ng) is different.");
        err_com.push_back("Please check the FSP data.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }

  vector<Real> fsp_new, weight_tot;
  fsp_new.resize(ng);
  weight_tot.resize(ng);
  for(int i=0; i<ng; i++)
  {
    fsp_new[i]    = 0.0;
    weight_tot[i] = 0.0;
  }

  for(int i=0; i<i_max; i++)
  {
    if( fsp_obj[i].get_ng() == 0 || fsp_obj[i].get_mat_no() == unassigned_mat_no )
    {
      continue;
    }

    vector<Real> fsp = fsp_obj[i].get_fsp();
    for(int j=0; j<ng; j++)
    {
      fsp_new[j]    += weight_vec[i] * fsp[j];
      weight_tot[j] += weight_vec[i];
    }
  }

  //Devided by the weight total
  Real fsp_tot = 0.0;
  for(int i=0; i<ng; i++)
  {
    if( fabs(weight_tot[i]) > min_value )
    {
      fsp_new[i] /= weight_tot[i];
    }
    fsp_tot += fsp_new[i];
  }

  //Normalize fsp
  if( fabs(fsp_tot) > min_value )
  {
    for(int i=0; i<ng; i++)
    {
      fsp_new[i] /= fsp_tot;
    }
  }

  KramFspData fsp_data_new;
  fsp_data_new.set_mat_no(mat_no);
  fsp_data_new.set_ng(ng);
  fsp_data_new.set_fsp(fsp_new);

  return fsp_data_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

KramAscData KramMerger::merge_asc(vector<KramAscData> asc_obj, vector<Real> weight_vec, int mat_no)
{
  int ng    = 0;
  int pl_no = 0;
  int i_max = static_cast<int>(asc_obj.size());
  if( i_max != static_cast<int>(weight_vec.size()) )
  {
    string class_name = "KramMerger";
    string func_name  = "merge_asc(vector<KramAscData> asc_obj, vector<Real> weight_vec, int mat_no)";

    ostringstream oss01, oss02;
    oss01 << i_max;
    oss02 << static_cast<int>(weight_vec.size());

    vector<string> err_com;
    string str_data01 = "Data size of asc_obj    : " + oss01.str();
    string str_data02 = "Data size of weight_vec : " + oss02.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The data size of asc_obj is different to that of weight_vec.");
    err_com.push_back("Please check asc_obj or weight_vec.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<i_max; i++)
  {
    if( asc_obj[i].get_ng() > 0 && asc_obj[i].get_pl_no() > 0 )
    {
      if( ng == 0 )
      {
        ng = asc_obj[i].get_ng();
      }
      if( pl_no == 0 )
      {
        pl_no = asc_obj[i].get_pl_no();
      }

      if( ng != asc_obj[i].get_ng() || pl_no != asc_obj[i].get_pl_no() )
      {
        string class_name = "KramMerger";
        string func_name  = "merge_asc(vector<KramAscData> asc_obj, vector<Real> weight_vec, int mat_no)";

        ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07;
        oss01 << i+1;
        oss02 << i_max;
        oss03 << asc_obj[i].get_mat_no();
        oss04 << ng;
        oss05 << asc_obj[i].get_ng();
        oss06 << pl_no;
        oss07 << asc_obj[i].get_pl_no();

        vector<string> err_com;
        string str_data01 = "Position                       : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "Mat number                     : " + oss03.str();
        string str_data03 = "Number of multi-groups (other) : " + oss04.str();
        string str_data04 = "Number of multi-groups (this)  : " + oss05.str();
        string str_data05 = "Number of Legendres (other)    : " + oss06.str();
        string str_data06 = "Number of Legendres (this)     : " + oss07.str();
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back(str_data05);
        err_com.push_back(str_data06);
        err_com.push_back("");
        err_com.push_back("The number of multi-groups (ng) and/or number of Legendres (pl_no) is different.");
        err_com.push_back("Please check the ASC data.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }

  vector<vector<vector<Real> > > asc_new;
  asc_new.resize(pl_no);
  for(int i=0; i<pl_no; i++)
  {
    asc_new[i].resize(ng);
    for(int j=0; j<ng; j++)
    {
      asc_new[i][j].resize(ng);
      for(int k=0; k<ng; k++)
      {
        asc_new[i][j][k] = 0.0;
      }
    }
  }

  for(int i=0; i<i_max; i++)
  {
    if( asc_obj[i].get_ng() == 0 || asc_obj[i].get_mat_no() == unassigned_mat_no ||
        asc_obj[i].get_pl_no() == 0 )
    {
      continue;
    }

    vector<vector<vector<Real> > > asc = asc_obj[i].get_asc();
    for(int j=0; j<pl_no; j++)
    {
      for(int k=0; k<ng; k++)
      {
        for(int l=0; l<ng; l++)
        {
          asc_new[j][k][l] += weight_vec[i] * asc[j][k][l];
        }
      }
    }
  }

  KramAscData asc_data_new;
  asc_data_new.set_mat_no(mat_no);
  asc_data_new.set_ng(ng);
  asc_data_new.set_pl_no(pl_no);
  asc_data_new.set_asc(asc_new);

  return asc_data_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

KramFspData KramMerger::merge_fsp(vector<KramFspData> fsp_obj, vector<Real> weight_vec,
                                  vector<vector<Real> > nsf_vec, int mat_no)
{
  int ng    = 0;
  int i_max = static_cast<int>(fsp_obj.size());
  if( i_max != static_cast<int>(weight_vec.size()) || i_max != static_cast<int>(nsf_vec.size()) )
  {
    string class_name = "KramMerger";
    string func_name  = "merge_fsp(vector<KramFspData> fsp_obj, vector<Real> weight_vec, vector<vector<Real> > nsf_vec, int mat_no)";

    ostringstream oss01, oss02, oss03;
    oss01 << i_max;
    oss02 << static_cast<int>(weight_vec.size());
    oss03 << static_cast<int>(nsf_vec.size());

    vector<string> err_com;
    string str_data01 = "Data size of fsp_obj    : " + oss01.str();
    string str_data02 = "Data size of weight_vec : " + oss02.str();
    string str_data03 = "Data size of nsf_vec     : " + oss02.str();
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The data size of fsp_obj is different to that of weight_vec or that of nsf_vec.");
    err_com.push_back("Please check fsp_obj, weight_vec, or nsf_vec.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<i_max; i++)
  {
    if( fsp_obj[i].get_ng() > 0 )
    {
      if( ng == 0 )
      {
        ng = fsp_obj[i].get_ng();
      }
      else if( ng != fsp_obj[i].get_ng() )
      {
        string class_name = "KramMerger";
        string func_name  = "merge_fsp(vector<KramFspData> fsp_obj, vector<Real> weight_vec, vector<vector<Real> > nsf_vec, int mat_no)";

        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss01 << i+1;
        oss02 << i_max;
        oss03 << fsp_obj[i].get_mat_no();
        oss04 << ng;
        oss05 << fsp_obj[i].get_ng();

        vector<string> err_com;
        string str_data01 = "Position                       : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "Mat number                     : " + oss03.str();
        string str_data03 = "Number of multi-groups (other) : " + oss04.str();
        string str_data04 = "Number of multi-groups (this)  : " + oss05.str();
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back("");
        err_com.push_back("The number of multi-groups (ng) is different.");
        err_com.push_back("Please check the FSP data.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      if( ng != 0 && ng != static_cast<int>(nsf_vec[i].size()) )
      {
        string class_name = "KramMerger";
        string func_name  = "merge_fsp(vector<KramFspData> fsp_obj, vector<Real> weight_vec, vector<vector<Real> > nsf_vec, int mat_no)";

        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss01 << i+1;
        oss02 << i_max;
        oss03 << fsp_obj[i].get_mat_no();
        oss04 << ng;
        oss05 << static_cast<int>(nsf_vec[i].size());

        vector<string> err_com;
        string str_data01 = "Position i             : " + oss01.str() + " / " + oss02.str();
        string str_data02 = "Mat number             : " + oss03.str();
        string str_data03 = "Number of multi-groups : " + oss04.str();
        string str_data04 = "Data size of nsf_vec[i] : " + oss05.str();
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back(str_data04);
        err_com.push_back("");
        err_com.push_back("The number of multi-groups (ng) is different to the data size of nsf_vec[i].");
        err_com.push_back("Please check the FSP data or nsf_vec.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }

  vector<Real> fsp_new, weight_tot;
  fsp_new.resize(ng);
  weight_tot.resize(ng);
  for(int i=0; i<ng; i++)
  {
    fsp_new[i]    = 0.0;
    weight_tot[i] = 0.0;
  }

  for(int i=0; i<i_max; i++)
  {
    if( fsp_obj[i].get_ng() == 0 || fsp_obj[i].get_mat_no() == unassigned_mat_no )
    {
      continue;
    }

    Real nsf_tot = 0.0;
    for(int j=0; j<ng; j++)
    {
      nsf_tot += nsf_vec[i][j];
    }

    Real weight_val = weight_vec[i] * nsf_tot;

    vector<Real> fsp = fsp_obj[i].get_fsp();
    for(int j=0; j<ng; j++)
    {
      fsp_new[j]     += weight_val * fsp[j];
      weight_tot[j]  += weight_val;
    }
  }

  //Devided by the weight total
  Real fsp_tot = 0.0;
  for(int i=0; i<ng; i++)
  {
    if( fabs(weight_tot[i]) > min_value )
    {
      fsp_new[i] /= weight_tot[i];
    }
    fsp_tot += fsp_new[i];
  }

  //Normalize fsp
  if( fabs(fsp_tot) > min_value )
  {
    for(int i=0; i<ng; i++)
    {
      fsp_new[i] /= fsp_tot;
    }
  }

  KramFspData fsp_data_new;
  fsp_data_new.set_mat_no(mat_no);
  fsp_data_new.set_ng(ng);
  fsp_data_new.set_fsp(fsp_new);

  return fsp_data_new;
}

