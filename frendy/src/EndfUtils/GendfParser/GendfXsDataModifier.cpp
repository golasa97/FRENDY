#include "EndfUtils/GendfParser/GendfXsDataModifier.hpp"

using namespace frendy;

//constructor
GendfXsDataModifier::GendfXsDataModifier(void)
{
  clear();
}

//destructor
GendfXsDataModifier::~GendfXsDataModifier(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfXsDataModifier::clear()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GendfXsDataModifier::get_neutron_absorption(GendfParser& gendf_obj, Integer reaction_type)
{
  GMF01MT451Parser gmf01_obj = gendf_obj.get_mf01_mt451_data();
  GMF03Parser      gmf03_obj = gendf_obj.get_mf03_data(reaction_type);

  vector<Real> abs_no;
  abs_no.clear();
  if( gmf03_obj.get_mat_no() == unassigned_mat_no ||
      gmf03_obj.get_mt_no()  == unassigned_mt_no )
  {
    return abs_no;
  }

  int ng = static_cast<int>(gmf01_obj.get_NGN());
  abs_no.resize(ng+1);
  
  if( reaction_type == 5 ) //(z, anything), fission
  {
    GMFxxParserBase read_obj = gendf_obj.get_mf06_data(reaction_type).get_read_obj();
    if( read_obj.get_mat_no() == unassigned_mat_no ||
        read_obj.get_mt_no()  == unassigned_mt_no )
    {
      read_obj = gendf_obj.get_mf05_data(reaction_type).get_read_obj();
      if( read_obj.get_mat_no() == unassigned_mat_no ||
          read_obj.get_mt_no()  == unassigned_mt_no )
      {
        string class_name = "GendfXsDataModifier";
        string func_name  = "get_neutron_absorption(GendfParser& gendf_obj, Integer reaction_type)";

        ostringstream oss01;
        oss01 << reaction_type;
        string str_data01 = "MT=" + oss01.str() + " is not found in MF=5 and MF=6.";

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back("This program cannot set the neutron absorption number.");
        err_com.push_back("Please check the GENDF data or modify this program.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }

    vector<vector<vector<Real> > > xs_ddx = read_obj.get_DATA2_integ();
    vector<vector<vector<Real> > > xs_vec = gmf03_obj.get_SIG();

    int e_in_no = static_cast<int>(xs_vec.size());
    if( e_in_no != static_cast<int>(xs_ddx.size()) )
    {
      string class_name = "GendfXsDataModifier";
      string func_name  = "get_neutron_absorption(GendfParser& gendf_obj, Integer reaction_type)";

      ostringstream oss01, oss02, oss03;
      oss01 << reaction_type;
      oss02 << e_in_no;
      oss03 << static_cast<int>(xs_ddx.size());
      string str_data01 = "Reaction type (MT)                         : " + oss01.str();
      string str_data02 = "Incident neutron energy number from MF=3   : " + oss02.str();
      string str_data03 = "Incident neutron energy number from MF=5/6 : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      err_com.push_back("The inicident energy number is different.");
      err_com.push_back("Please check the GENDF data or modify this program.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    for(int i=0; i<ng+1; i++)
    {
      abs_no[i] = 0.0;
      if( static_cast<int>(xs_vec[i].size()) > 0 )
      {
        if( fabs(xs_vec[i][0][0]) > min_value )
        {
          abs_no[i] = xs_ddx[i][0][0] / xs_vec[i][0][0];
        }
      }
    }
  }
  else
  {
    NuclearDataObjectUtils nucl_util_obj;
    Real abs_no_val = static_cast<Real>(nucl_util_obj.get_neutron_absorption(reaction_type));
    for(int i=0; i<ng+1; i++)
    {
      abs_no[i] = abs_no_val;
    }
  }

  return abs_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real GendfXsDataModifier::get_neutron_absorption(GendfParser& gendf_obj, Integer reaction_type,
                                           Real ene)
{
  vector<Real> abs_no_vec = get_neutron_absorption(gendf_obj, reaction_type);
  vector<Real> ene_vec    = gendf_obj.get_mf01_mt451_data().get_EGN();

  int i_m, i_p;
  ti_obj.search_neighbor_value(ene, ene_vec, i_m, i_p);
  ene_vec.clear();

  return abs_no_vec[i_m];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfXsDataModifier::generate_absorption_xs(GendfParser& gendf_obj, Integer mt_abs_new)
{
  vector<Integer> mt_list = gendf_obj.get_mt_list(3);

  int i_max = static_cast<int>(mt_list.size());
  if( i_max == 0 )
  {
    return;
  }

  int ng         = static_cast<int>(gendf_obj.get_mf01_mt451_data().get_NGN());
  int pl_no      = gendf_obj.get_mf03_data(1).get_NL();
  int sigz_no    = gendf_obj.get_mf03_data(1).get_NSIGZ();
  int mt_no_init = 1;
  if( pl_no == 0 || sigz_no == 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( gendf_obj.get_mf03_data(mt_list[i]).get_mat_no() == unassigned_mat_no ||
          gendf_obj.get_mf03_data(mt_list[i]).get_mt_no()  == unassigned_mt_no )
      {
        continue;
      }

      pl_no      = gendf_obj.get_mf03_data(mt_list[i]).get_NL();
      sigz_no    = gendf_obj.get_mf03_data(mt_list[i]).get_NSIGZ();
      mt_no_init = mt_list[i];
      if( pl_no > 1 || sigz_no > 1 )
      {
        break;
      }
    }
  }

  vector<vector<vector<Real> > > xs_vec;
  //For MF=6 MT=18
  //This data has NGN+1 data. see store_data function in GMFxxParserBase.cpp
  xs_vec.resize(ng+1);
  for(int j=1; j<ng+1; j++)
  {
    xs_vec[j].resize(sigz_no);
    for(int k=0; k<sigz_no; k++)
    {
      xs_vec[j][k].resize(pl_no);
      for(int l=0; l<pl_no; l++)
      {
        xs_vec[j][k][l] = 0.0;
      }
    }
  }

  GMF03Parser gmf03_obj_new;
  gmf03_obj_new.clear();

  int init_mt_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    GMF03Parser gmf03_obj = gendf_obj.get_mf03_data(mt_list[i]);

    NuclearDataObjectUtils nucl_data_util;
    if( gmf03_obj.get_mat_no() == unassigned_mat_no ||
        gmf03_obj.get_mt_no()  == unassigned_mt_no )
    {
      continue;
    }
    else if( mt_list[i] >= 452 && mt_list[i] <= 456 ) //Nu values
    {
      continue;
    }
    else if( mt_list[i] >= 251 && mt_list[i] <= 253 ) //Mu, Xi, Gamma
    {
      continue;
    }

    if( init_mt_flg == 0 )
    {
      gmf03_obj_new = gmf03_obj;
      init_mt_flg   = 1;
    }

    if( nucl_data_util.get_neutron_absorption(mt_list[i]) == 0 )
    {
      continue;
    }

    vector<Real>  abs_coef = get_neutron_absorption(gendf_obj, mt_list[i]);
    //if( static_cast<int>(abs_coef.size()) > 0 )
    //{
    //  cout << mt_list[i] << " : " <<  abs_coef.size() << " : " << abs_coef[0] << endl;
    //}

    if( pl_no != gmf03_obj.get_NL() || sigz_no != gmf03_obj.get_NSIGZ() )
    {
      string class_name = "GendfXsDataModifier";
      string func_name  = "generate_absorption_xs(GendfParser& gendf_obj, Integer mt_abs_new)";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
      oss01 << mt_no_init;
      oss02 << mt_list[i];
      oss03 << sigz_no;
      oss04 << gmf03_obj.get_NSIGZ();
      oss05 << pl_no;
      oss06 << gmf03_obj.get_NL();
      string str_data01 = "Reaction type (MT)       : " + oss01.str() + " / " + oss02.str() + " (init / this)";
      string str_data02 = "NSIG (number of sigz)    : " + oss03.str() + " / " + oss04.str() + " (init / this)";
      string str_data03 = "NL (number of Legendres) : " + oss05.str() + " / " + oss06.str() + " (init / this)";

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      err_com.push_back("NSIG or NL is different in each MT number.");

      if( gmf03_obj.get_NL() == 1 &&
         (gmf03_obj.get_NSIGZ() == 1 || sigz_no == gmf03_obj.get_NSIGZ()) )
      {
        //err_obj.output_caution(class_name, func_name, err_com);
      }
      else
      {
        err_com.push_back("Please check the GENDF data or modify this program.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }

    vector<int>                    ig_vec      = gmf03_obj.get_IG();
    vector<vector<vector<Real> > > xs_vec_each = gmf03_obj.get_SIG();
    for(int j=0; j<static_cast<int>(ig_vec.size()); j++)
    {
      int e_pos = ig_vec[j];
      if( e_pos < 0 )
      {
        continue;
      }
      Real abs_coef_val = abs_coef[e_pos];

      for(int k=0; k<gmf03_obj.get_NSIGZ(); k++)
      {
        for(int l=0; l<gmf03_obj.get_NL(); l++)
        {
          xs_vec[e_pos][k][l] += xs_vec_each[e_pos][k][l] * abs_coef_val;
        }
      }
    }
  }

  vector<int> ng2_new, ig2lo_new, ig_new;
  ng2_new.resize(ng);
  ig2lo_new.resize(ng);
  ig_new.resize(ng);
  for(int i=0; i<ng; i++)
  {
    ng2_new[i]   = 2;
    ig2lo_new[i] = 1;
    ig_new[i]    = i+1;
  }
  gmf03_obj_new.set_mt_no(mt_abs_new);
  gmf03_obj_new.set_NG2(ng2_new);
  gmf03_obj_new.set_IG2LO(ig2lo_new);
  gmf03_obj_new.set_IG(ig_new);
  gmf03_obj_new.set_SIG(xs_vec);
  
  gendf_obj.set_mf03_data(gmf03_obj_new);

  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfXsDataModifier::generate_production_xs(GendfParser& gendf_obj, Integer mt_pro_new)
{
  GMF03Parser gmf03_obj = gendf_obj.get_mf03_data(18);

  if( gmf03_obj.get_mat_no() == unassigned_mat_no ||
      gmf03_obj.get_mt_no()  == unassigned_mt_no )
  {
    return;
  }

  GMF03Parser gmf03_obj_nu = gendf_obj.get_mf03_data(452);
  if( gmf03_obj_nu.get_mat_no() == unassigned_mat_no ||
      gmf03_obj_nu.get_mt_no()  == unassigned_mt_no )
  {
    return;
  }
  vector<vector<vector<vector<Real> > > > nu_vec = gmf03_obj_nu.get_NU();

  gmf03_obj.set_mt_no(mt_pro_new);

  vector<vector<vector<Real> > > xs_vec = gmf03_obj.get_SIG();
  int i_max = static_cast<int>(xs_vec.size()); //e_in
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(xs_vec[i].size()); //sigz
    for(int j=0; j<j_max; j++)
    {
      if( j < static_cast<int>(nu_vec[i].size()) )
      {
        int k_max = static_cast<int>(xs_vec[i][j].size()); //pl
        for(int k=0; k<k_max; k++)
        {
          if( k < static_cast<int>(nu_vec[i][k].size()) )
          {
              xs_vec[i][j][k] *= nu_vec[i][j][k][0];
          }
        }
      }
    }
  }

  gmf03_obj.set_SIG(xs_vec);
  vector<vector<vector<Real> > >().swap(xs_vec);

  gendf_obj.set_mf03_data(gmf03_obj);

  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GendfXsDataModifier::get_fission_spectrum(GendfParser& gendf_obj)
{
  int ng = gendf_obj.get_mf01_mt451_data().get_NGN();
  vector<Real> fsp_vec;
  fsp_vec.resize(ng);
  for(int i=0; i<ng; i++)
  {
    fsp_vec[i] = 0.0;
  }

  GMF06Parser gmf06_obj = gendf_obj.get_mf06_data(18);

  if( gmf06_obj.get_mat_no() == unassigned_mat_no ||
      gmf06_obj.get_mt_no()  == unassigned_mt_no )
  {
    return fsp_vec;
  }

  int sigz_no = 0;
  int pl_no = 0;
  vector<int> ig = gmf06_obj.get_IG();
  for(int i=0; i<static_cast<int>(ig.size()); i++)
  {
    if( ig[i] == 0 )
    {
      if( static_cast<int>(gmf06_obj.get_MATRIX()[i].size()) > sigz_no )
      {
        if( static_cast<int>(gmf06_obj.get_MATRIX()[i][sigz_no].size()) > pl_no )
        {
          fsp_vec = gmf06_obj.get_MATRIX()[i][sigz_no][pl_no];
        }
      }
    }
  }

  return fsp_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfXsDataModifier::merge_tsl_data_to_total(GendfParser& gendf_obj, Integer mt_tot_new, Integer mt_ela_new)
{
  vector<Integer> mt_list = gendf_obj.get_mt_list(3);
  sort(mt_list.begin(), mt_list.end());

  Integer mt_tot_flg   = -1;
  Integer mt_ela_flg   = -1;

  Integer mt_inela_tsl = -1;
  Integer mt_ela_tsl   = -1;
  int i_max = static_cast<int>(mt_list.size());
  for(int i=0; i<i_max; i++)
  {
    if( mt_list[i] == 1 )
    {
      mt_tot_flg = 1;
    }
    else if( mt_list[i] == 2 )
    {
      mt_ela_flg = 1;
    }
    else if( mt_list[i] >= 221 && mt_list[i] <= 250 )
    {
      if( mt_inela_tsl < 0 )
      {
        mt_inela_tsl = mt_list[i];
      }
      else if( mt_ela_tsl < 0 )
      {
        mt_ela_tsl = mt_list[i];
      }
      else //if( mt_inela_tsl >= 0 && me_ela_tsl >= 0 )
      {
        string class_name = "GendfXsDataModifier";
        string func_name  = "merge_tsl_data(GendfParser& gendf_obj)";

        ostringstream oss01, oss02, oss03;
        oss01 << mt_inela_tsl;
        oss02 << mt_ela_tsl;
        oss03 << mt_list[i];
        string str_data01 = "MT number for inelastic scattering : " + oss01.str();
        string str_data02 = "MT number for elastic scattering   : " + oss02.str();
        string str_data03 = "MT number for additional data      : " + oss03.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("");
        err_com.push_back("The MT numbers for inelastic and elastic scattering are available.");
        err_com.push_back("The additional MT number cannot treat this program.");
        err_com.push_back("Please check the GENDF data or modify this program.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
  }

  if( mt_tot_flg < 0 && mt_ela_flg < 0 )
  {
    string class_name = "GendfXsDataModifier";
    string func_name  = "merge_tsl_data(GendfParser& gendf_obj)";

    ostringstream oss01, oss02, oss03;

    vector<string> err_com;
    err_com.push_back("MT=1 and 2 are not found in gendf_obj.");
    err_com.push_back("Skip the modification of total and elastic scattering data.");
    err_obj.output_caution(class_name, func_name, err_com);

    return;
  }

  GMF03Parser mf03_mt001_obj, mf03_mt002_obj;
  GMF06Parser                 mf06_mt002_obj;
  if( mt_tot_flg > 0 )
  {
    mf03_mt001_obj = gendf_obj.get_mf03_data(1);
  }

  if( mt_ela_flg > 0 )
  {
    mf03_mt002_obj = gendf_obj.get_mf03_data(2);
    mf06_mt002_obj = gendf_obj.get_mf06_data(2);
  }

  vector<GMF03Parser>  mf03_tsl_vec;
  vector<GMF06Parser>  mf06_tsl_vec;
  vector<Real> weight_vec;
  if( mt_inela_tsl > 0 )
  {
    mf03_tsl_vec.push_back(gendf_obj.get_mf03_data(mt_inela_tsl));
    mf06_tsl_vec.push_back(gendf_obj.get_mf06_data(mt_inela_tsl));
    weight_vec.push_back(1.0);
  }

  if( mt_ela_tsl > 0 )
  {
    mf03_tsl_vec.push_back(gendf_obj.get_mf03_data(mt_ela_tsl));
    mf06_tsl_vec.push_back(gendf_obj.get_mf06_data(mt_ela_tsl));
    weight_vec.push_back(1.0);
  }

  if( static_cast<int>(weight_vec.size()) == 0 )
  {
    string class_name = "GendfXsDataModifier";
    string func_name  = "merge_tsl_data(GendfParser& gendf_obj)";

    ostringstream oss01, oss02, oss03;

    vector<string> err_com;
    err_com.push_back("The TSL data (MT=221 and 250 data) are not found in gendf_obj.");
    err_com.push_back("Skip the modification of total and elastic scattering data using TSL data.");
    err_obj.output_caution(class_name, func_name, err_com);

    return;
  }

  GendfMerger merge_obj;
  GMF03Parser mf03_merge = merge_obj.merge_gmf03_data(mf03_tsl_vec, weight_vec);
  GMF06Parser mf06_merge = merge_obj.merge_gmf06_data(mf06_tsl_vec, weight_vec);
  vector<GMF03Parser>().swap(mf03_tsl_vec);
  vector<GMF06Parser>().swap(mf06_tsl_vec);

  vector<int>                    ig_dif_vec;
  vector<vector<vector<Real> > > xs_dif_vec;
  modify_elastic_scattering(mf03_mt002_obj, mf06_mt002_obj, mf03_merge, mf06_merge,
                            ig_dif_vec, xs_dif_vec);
  mf03_merge.clear();
  mf06_merge.clear();

  //Modify total cross section using difference of scattering cross section
  //(xs_dif = xs_tsl - xs_ela)
  vector<vector<vector<Real> > > xs_tot = mf03_mt001_obj.get_SIG();
  for(int i=0; i<static_cast<int>(xs_dif_vec.size()); i++)
  {
    for(int j=0; j<static_cast<int>(xs_dif_vec[i].size()); j++)
    {
      for(int k=0; k<static_cast<int>(xs_dif_vec[i][j].size()); k++)
      {
        xs_tot[ig_dif_vec[i]][j][k] += xs_dif_vec[i][j][k];
      }
    }
  }
  vector<vector<vector<Real> > >().swap(xs_dif_vec);
  ig_dif_vec.clear();

  mf03_mt001_obj.set_mt_no(mt_tot_new);
  mf03_mt001_obj.set_SIG(xs_tot);
  vector<vector<vector<Real> > >().swap(xs_tot);

  mf03_mt002_obj.set_mt_no(mt_ela_new);
  mf06_mt002_obj.set_mt_no(mt_ela_new);

  gendf_obj.set_mf03_data(mf03_mt001_obj);
  gendf_obj.set_mf03_data(mf03_mt002_obj);
  gendf_obj.set_mf06_data(mf06_mt002_obj);
  mf03_mt001_obj.clear();
  mf03_mt002_obj.clear();
  mf06_mt002_obj.clear();

  modify_inelastic_scattering(gendf_obj, mt_ela_new);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfXsDataModifier::modify_elastic_scattering(GMF03Parser& mf03_mt002_obj, GMF06Parser& mf06_mt002_obj,
                                                    GMF03Parser& mf03_add_obj,   GMF06Parser& mf06_add_obj,
                                                    vector<int>& ig_dif_vec,
                                                    vector<vector<vector<Real> > >& xs_dif_vec)
{
  ig_dif_vec.clear();
  xs_dif_vec.clear();

  vector<int>                             ig_ela_vec    = mf03_mt002_obj.get_IG();
  vector<vector<vector<Real> > >          xs_ela_vec    = mf03_mt002_obj.get_SIG();
  vector<int>                             ig2lo_ela_vec = mf06_mt002_obj.get_IG2LO();
  vector<vector<vector<vector<Real> > > > ddx_ela_vec   = mf06_mt002_obj.get_MATRIX();
  vector<int>                             ig_add_vec    = mf03_add_obj.get_IG();
  vector<vector<vector<Real> > >          xs_add_vec    = mf03_add_obj.get_SIG();
  vector<int>                             ig2lo_add_vec = mf06_add_obj.get_IG2LO();
  vector<vector<vector<vector<Real> > > > ddx_add_vec   = mf06_add_obj.get_MATRIX();

  int ng = static_cast<int>(mf03_mt002_obj.get_NGN());
  ig_ela_vec.resize(ng+1);

  int ela_max = static_cast<int>(ig_ela_vec.size());
  int add_max = static_cast<int>(ig_add_vec.size());

  if( add_max == 0 )
  {
    return;
  }
  else if( ela_max == 0 )
  {
    mf03_mt002_obj = mf03_add_obj;
    mf06_mt002_obj = mf06_add_obj;
    ig_dif_vec     = ig_add_vec;
    xs_dif_vec     = xs_add_vec;
    return;
  }

  int pos_ela = 0;
  int pos_add = 0;
  for(int i=0; i<=ng; i++)
  {
     while( pos_ela < ela_max )
     {
       if( ig_ela_vec[pos_ela] > 0 )
       {
          break;
       }
       pos_ela++;
     }
     while( pos_add < add_max )
     {
       if( ig_add_vec[pos_add] > 0 )
       {
          break;
       }
       pos_add++;
     }

    if( pos_ela == ela_max || pos_add == add_max )
    {
      break;
    }

    if( ig_ela_vec[pos_ela] == i && ig_add_vec[pos_add] == i )
    {
      vector<vector<Real> > xs_dif_tmp;
      int j_max = static_cast<int>(xs_ela_vec[pos_ela].size());
      if( static_cast<int>(xs_add_vec[pos_add].size()) < j_max )
      {
        j_max = static_cast<int>(xs_add_vec[pos_add].size());
      }

      xs_dif_tmp.resize(j_max);
      for(int j=0; j<j_max; j++) //sigz
      {
        int k_max = static_cast<int>(xs_ela_vec[pos_ela][j].size());
        if( static_cast<int>(xs_add_vec[pos_add][j].size()) < k_max )
        {
          k_max = static_cast<int>(xs_add_vec[pos_add][j].size());
        }

        xs_dif_tmp[j].resize(k_max);
        for(int k=0; k<k_max; k++) //pl
        {
          xs_dif_tmp[j][k] = xs_add_vec[pos_add][j][k] - xs_ela_vec[pos_ela][j][k];
        }
      }

      ig_dif_vec.push_back(i);
      xs_dif_vec.push_back(xs_dif_tmp);
      xs_dif_tmp.clear();


      ig2lo_ela_vec[pos_ela] = ig2lo_add_vec[pos_add];
      for(int j=0; j<j_max; j++)
      {
        xs_ela_vec[pos_ela][j]  = xs_add_vec[pos_add][j];
        ddx_ela_vec[pos_ela][j] = ddx_add_vec[pos_add][j];
      }
      
      pos_ela++;
      pos_add++;
    }
    else if( ig_ela_vec[pos_ela] == i )
    {
      pos_ela++;
      continue;
    }
    else if( ig_add_vec[pos_add] == i )
    {
      pos_add++;

      string class_name = "GendfXsDataModifier";
      string func_name  = "modify_elastic_scattering";

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

  mf03_mt002_obj.set_SIG(xs_ela_vec);
  mf06_mt002_obj.set_IG2LO(ig2lo_ela_vec);
  mf06_mt002_obj.set_MATRIX(ddx_ela_vec);
  vector<vector<vector<Real> > >().swap(xs_ela_vec);
  vector<vector<vector<vector<Real> > > >().swap(ddx_ela_vec);
  vector<vector<vector<Real> > >().swap(xs_add_vec);
  vector<vector<vector<vector<Real> > > >().swap(ddx_add_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfXsDataModifier::modify_inelastic_scattering(GendfParser& gendf_obj, Integer mt_ela_new)
{
  vector<GMF06Parser> mf06_vec;
  vector<Real> weight_ddx;
  mf06_vec.push_back(gendf_obj.get_mf06_data(mt_ela_new));
  weight_ddx.push_back(1.0);

  NuclearDataObjectUtils nucl_util_obj;
  vector<Integer> mt_list  = gendf_obj.get_mt_list(6);
  for(int i=0; i<static_cast<int>(mt_list.size()); i++)
  {
    if( mt_list[i] == 2 )
    {
      continue;
    }

    Integer n_no = nucl_util_obj.get_emission_no_n(mt_list[i]);
    if( n_no > 0 &&
        gendf_obj.get_mf06_data(mt_list[i]).get_mat_no() != unassigned_mat_no )
    {
      mf06_vec.push_back(gendf_obj.get_mf06_data(mt_list[i]));
      weight_ddx.push_back(static_cast<Real>(n_no));
    }
  }

  GendfMerger merge_obj;
  GMF06Parser mf06_new = merge_obj.merge_gmf06_data(mf06_vec, weight_ddx);
  mf06_new.set_mt_no(mt_ela_new);
  weight_ddx.clear();

  gendf_obj.set_mf06_data(mf06_new);
  mf06_new.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

