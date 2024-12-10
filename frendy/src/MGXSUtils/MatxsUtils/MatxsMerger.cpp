#include "MGXSUtils/MatxsUtils/MatxsMerger.hpp"

using namespace frendy;

// ***** MatxsMerger ***** //
//constructor
MatxsMerger::MatxsMerger(void)
{
  clear();
}

//destructor
MatxsMerger::~MatxsMerger(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::clear()
{
  tolerance = 5.0E-5;

  matxs_obj.clear();
  vector<MatxsCommonData>().swap(matxs_obj_vec);

  hpart_new.clear();
  htype_new.clear();
  hmatn_new.clear();

  diff_data_list.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::merge_matxs_obj()
{
  int i_max = static_cast<int>(matxs_obj_vec.size());
  if( i_max == 0 )
  {
    return;
  }

  check_set_data();

  modify_part_and_type_data();

  check_energy_group();

  //Merge all data
  matxs_obj.clear();

  //0v
  matxs_obj.set_hname(matxs_obj_vec[0].get_hname());
  matxs_obj.set_huse(matxs_obj_vec[0].get_huse());
  matxs_obj.set_ivers(matxs_obj_vec[0].get_ivers());

  //2d
  matxs_obj.set_hsetid(matxs_obj_vec[0].get_hsetid());

  merge_3d_and_4d_data();
  merge_5d_data();

  sort_5d_data();

  mod_6d_10d_data();
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::check_set_data()
{
  //Read 3d data (hpart, htype, hmatn, ngrp, jinp, joutp, nsubm, locm)
  vector<vector<string> >  hpart, htype, hmatn;
  vector<vector<Integer> > ngrp,  jinp,  joutp,  nsubm, locm;

  string hmat_ref;
  int i_max = static_cast<int>(matxs_obj_vec.size());
  for(int i=0; i<i_max; i++)
  {
    hpart.push_back(matxs_obj_vec[i].get_hpart());
    htype.push_back(matxs_obj_vec[i].get_htype());
    hmatn.push_back(matxs_obj_vec[i].get_hmatn());

    ngrp.push_back(matxs_obj_vec[i].get_ngrp());
    jinp.push_back(matxs_obj_vec[i].get_jinp());
    joutp.push_back(matxs_obj_vec[i].get_joutp());
    nsubm.push_back(matxs_obj_vec[i].get_nsubm());
    locm.push_back(matxs_obj_vec[i].get_locm());

    if( static_cast<int>(matxs_obj_vec[i].get_hmatn().size()) != 1 )
    {
      ostringstream oss01, oss02, oss03;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << static_cast<int>(matxs_obj_vec[i].get_hmatn().size());

      string class_name = "MatxsMerger";
      string func_name  = "check_set_data()";

      string str_data01 = "Position of matxs data  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Number of material data : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("This program only available for one material data.");
      err_com.push_back("Please check the matxs files.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    string hmat_com = matxs_obj_vec[i].get_hmatn()[0];
    if( i==0 )
    {
      hmat_ref = hmat_com;
    }

    if( hmat_ref != hmat_com )
    {
      ostringstream oss01, oss02;
      oss01 << i+1;
      oss02 << i_max;

      string class_name = "MatxsMerger";
      string func_name  = "check_set_data()";

      string str_data01 = "Position of matxs data              : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "hmat of first matxs data            : " + hmat_ref;
      string str_data03 = "hmat of matxs data at this position : " + hmat_com;

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("Material data name (hmat) is different.");
      err_com.push_back("This program only available for one material data.");
      err_com.push_back("Please check the matxs files.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }


  //Make new hpart, htype, and hmatn data
  hpart_new = hpart[0];
  htype_new = htype[0];
  hmatn_new = hmatn[0];

  for(int i=1; i<i_max; i++)
  {
    add_name_list(hpart_new, hpart[i]);
    add_name_list(htype_new, htype[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::add_name_list(vector<string>& name_list, vector<string> name_list_add)
{
  int i_max = static_cast<int>(name_list_add.size());
  for(int i=0; i<i_max; i++)
  {
    if( check_name_list(name_list, name_list_add[i]) < 0 )
    {
      name_list.push_back(name_list_add[i]);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int MatxsMerger::check_name_list(vector<string>& name_list, string name_list_add)
{
  int ele_no = -1;

  name_list_add = str_util.trim_space(name_list_add);

  int i_max = static_cast<int>(name_list.size());
  for(int i=0; i<i_max; i++)
  {
    string name_list_ori = str_util.trim_space(name_list[i]);
    if( name_list_ori == name_list_add )
    {
      ele_no = i;
      break;
    }
  }

  return ele_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::modify_part_and_type_data()
{
  int i_max = static_cast<int>(matxs_obj_vec.size());
  for(int i=0; i<i_max; i++)
  {
    vector<string> hpart = matxs_obj_vec[i].get_hpart();
    vector<string> htype = matxs_obj_vec[i].get_htype();

    vector<int> hpart_no_list, htype_no_list;

    int j_max = static_cast<int>(hpart.size());
    hpart_no_list.resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      hpart_no_list[j] = check_name_list(hpart_new, hpart[j]);
    }

        j_max = static_cast<int>(htype.size());
    htype_no_list.resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      htype_no_list[j] = check_name_list(htype_new, htype[j]);
    }

    //Modify part data
    vector<int> ngrp  = matxs_obj_vec[i].get_ngrp();
    vector<int> jinp  = matxs_obj_vec[i].get_jinp();
    vector<int> joutp = matxs_obj_vec[i].get_joutp();
    vector<MatxsGroupStructureData> ng_obj = matxs_obj_vec[i].get_grp_obj();
    modify_part_data(hpart_no_list, ngrp, jinp, joutp, ng_obj);
    matxs_obj_vec[i].set_ngrp(ngrp);
    matxs_obj_vec[i].set_jinp(jinp);
    matxs_obj_vec[i].set_joutp(joutp);
    matxs_obj_vec[i].set_grp_obj(ng_obj);


    //Modify type data
    vector<MatxsMaterialData> mat_obj = matxs_obj_vec[i].get_mat_obj();
    vector<int> itype = mat_obj[0].get_itype();
    modify_type_data(htype_no_list, jinp, joutp, itype);
    matxs_obj_vec[i].set_jinp(jinp);
    matxs_obj_vec[i].set_joutp(joutp);
    mat_obj[0].set_itype(itype);
    matxs_obj_vec[i].set_mat_obj(mat_obj);
  }

}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::modify_part_data(vector<int> hpart_no_list, 
                                   vector<int>& ngrp, vector<int>& jinp, vector<int>& joutp,
                                   vector<MatxsGroupStructureData>& ng_obj)
{
  vector<int> ngrp_new, jinp_new, joutp_new;
  vector<MatxsGroupStructureData> ng_obj_new;

  int part_no = static_cast<int>(hpart_new.size());
  ngrp_new.resize(part_no);
  ng_obj_new.resize(part_no);
  for(int i=0; i<part_no; i++)
  {
    ngrp_new[i] = -1;
    ng_obj_new[i].clear();
  }

  int i_max = static_cast<int>(ngrp.size());
  for(int i=0; i<i_max; i++)
  {
    int pos = hpart_no_list[i];
    ngrp_new[pos]   = ngrp[i];
    ng_obj_new[pos] = ng_obj[i];
  }

  i_max = static_cast<int>(jinp.size());
  jinp_new.resize(i_max);
  joutp_new.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    jinp_new[i]  = hpart_no_list[jinp[i]-1]  + 1;
    joutp_new[i] = hpart_no_list[joutp[i]-1] + 1;
  }

  ngrp  = ngrp_new;
  jinp  = jinp_new;
  joutp = joutp_new;
  ngrp_new.clear();
  jinp_new.clear();
  joutp_new.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::modify_type_data(vector<int> htype_no_list,
                                   vector<int>& jinp, vector<int>& joutp, vector<int>& itype)
{
  vector<int> jinp_new, joutp_new, itype_new;

  int type_no = static_cast<int>(htype_new.size());
  jinp_new.resize(type_no);
  joutp_new.resize(type_no);
  for(int i=0; i<type_no; i++)
  {
    jinp_new[i]  = -1;
    joutp_new[i] = -1;
  }

  int i_max = static_cast<int>(jinp.size());
  for(int i=0; i<i_max; i++)
  {
    int pos = htype_no_list[i];
    jinp_new[pos]  = jinp[i];
    joutp_new[pos] = joutp[i];
  }

  i_max = static_cast<int>(itype.size());
  itype_new.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    itype_new[i] = htype_no_list[itype[i]-1] + 1;
  }

  jinp  = jinp_new;
  joutp = joutp_new;
  itype = itype_new;
  jinp_new.clear();
  joutp_new.clear();
  itype_new.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::check_energy_group()
{
  int ngrp_no = static_cast<int>(hpart_new.size());
  vector<Integer>       ngrp_ref;
  vector<vector<Real> > ng_ref;
  ngrp_ref.resize(ngrp_no);
  ng_ref.resize(ngrp_no);
  for(int i=0; i<ngrp_no; i++)
  {
    ngrp_ref[i] = -1;
    ng_ref[i].clear();
  }

  int i_max = static_cast<int>(matxs_obj_vec.size());
  for(int i=0; i<i_max; i++)
  {
    vector<Integer> ngrp_com = matxs_obj_vec[i].get_ngrp();

    for(int j=0; j<ngrp_no; j++)
    {
      if( ngrp_com[j] > 0 )
      {
        if( ngrp_ref[j] < 0 )
        {
          ngrp_ref[j] = ngrp_com[j];
          ng_ref[j]   = matxs_obj_vec[i].get_grp_obj()[j].get_gpb();
        }
        else
        {
          if( ngrp_ref[j] != ngrp_com[j] )
          {
            ostringstream oss01, oss02, oss03, oss04;
            oss01 << i+1;
            oss02 << i_max;
            oss03 << ngrp_ref[j];
            oss04 << ngrp_com[j];

            string class_name = "MatxsMerger";
            string func_name  = "check_energy_group()";

            string str_data01 = "Position of matxs data              : "
                              + oss01.str() + " / " + oss02.str();
            string str_data02 = "particle name                       : " + hpart_new[j];
            string str_data03 = "ngrp of first matxs data            : " + oss03.str();
            string str_data04 = "ngrp of matxs data at this position : " + oss04.str();

            vector<string> err_com;
            err_com.push_back(str_data01);
            err_com.push_back(str_data02);
            err_com.push_back(str_data03);
            err_com.push_back(str_data04);
            err_com.push_back("The number of energy group is different.");
            err_com.push_back("Please check the matxs files.");

            err_obj.output_runtime_error(class_name, func_name, err_com);
          }

          vector<Real> ng_com = matxs_obj_vec[i].get_grp_obj()[j].get_gpb();
          for(int k=0; k<ngrp_ref[j]+1; k++)
          {
            if( fabs((ng_ref[j][k] - ng_com[k])/ng_com[k]) > tolerance )
            {
              ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
              oss01 << i+1;
              oss02 << i_max;
              oss03 << k+1;
              oss04 << ngrp_ref[j]+1;
              oss05 << ng_ref[j][k];
              oss06 << ng_com[k];

              string class_name = "MatxsMerger";
              string func_name  = "check_energy_group()";

              string str_data01 = "Position of matxs data              : "
                                + oss01.str() + " / " + oss02.str();
              string str_data02 = "Position of energy grid             : "
                                + oss03.str() + " / " + oss04.str();
              string str_data03 = "particle name                       : " + hpart_new[j];
              string str_data04 = "grp of first matxs data             : " + oss05.str();
              string str_data05 = "grp of matxs data at this position  : " + oss06.str();

              vector<string> err_com;
              err_com.push_back(str_data01);
              err_com.push_back(str_data02);
              err_com.push_back(str_data03);
              err_com.push_back(str_data04);
              err_com.push_back(str_data05);
              err_com.push_back("The energy group boundry is different.");
              err_com.push_back("Please check the matxs files.");

              err_obj.output_runtime_error(class_name, func_name, err_com);
            }
          }
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::merge_3d_and_4d_data()
{
  matxs_obj.set_hpart(hpart_new);
  matxs_obj.set_htype(htype_new);
  matxs_obj.set_hmatn(hmatn_new);

  int hpart_no = static_cast<int>(hpart_new.size());
  int htype_no = static_cast<int>(htype_new.size());
  int hmatn_no = static_cast<int>(hmatn_new.size());

  vector<MatxsGroupStructureData> ng_obj_new;
  vector<Integer> ngrp_new, jinp_new, joutp_new, nsubm_new, locm_new;
  ng_obj_new.resize(hpart_no);
  ngrp_new.resize(hpart_no);
  jinp_new.resize(htype_no);
  joutp_new.resize(htype_no);
  nsubm_new.resize(hmatn_no); //hmatn_no = 1
  locm_new.resize(hmatn_no);  //hmatn_no = 1

  for(int i=0; i<hpart_no; i++)
  {
    ng_obj_new[i].clear();
    ngrp_new[i] = -1;
  }

  for(int i=0; i<htype_no; i++)
  {
    jinp_new[i]  = -1;
    joutp_new[i] = -1;
  }

  for(int i=0; i<hmatn_no; i++)
  {
    nsubm_new[i] = -1;
    locm_new[i]  = -1;
  }

  int i_max = matxs_obj_vec.size();
  for(int i=0; i<i_max; i++)
  {
    vector<Integer> ngrp_ori  = matxs_obj_vec[i].get_ngrp();
    vector<Integer> jinp_ori  = matxs_obj_vec[i].get_jinp();
    vector<Integer> joutp_ori = matxs_obj_vec[i].get_joutp();

    for(int j=0; j<hpart_no; j++)
    {
      if( ngrp_ori[j] > 0 && ngrp_new[j] < 0 )
      {
        ng_obj_new[j] = matxs_obj_vec[i].get_grp_obj()[j];
        ngrp_new[j]   = ngrp_ori[j];
      }
    }

    for(int j=0; j<htype_no; j++)
    {
      if( jinp_ori[j] > 0 && jinp_new[j] < 0 )
      {
        jinp_new[j] = jinp_ori[j];
      }

      if( joutp_ori[j] > 0 && joutp_new[j] < 0 )
      {
        joutp_new[j] = joutp_ori[j];
      }
    }

    if( i==0 )
    {
      locm_new = matxs_obj_vec[i].get_locm();
    }
  }

  matxs_obj.set_grp_obj(ng_obj_new);
  matxs_obj.set_ngrp(ngrp_new);
  matxs_obj.set_jinp(jinp_new);
  matxs_obj.set_joutp(joutp_new);
  matxs_obj.set_nsubm(nsubm_new);
  matxs_obj.set_locm(locm_new);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::merge_5d_data()
{
  vector<Integer>           nsubm_new_vec;
  vector<MatxsMaterialData> mat_obj_new;
  int mat_no = 1;
  mat_obj_new.resize(mat_no);
  nsubm_new_vec.resize(mat_no);

  for(int m=0; m<mat_no; m++)
  {
    vector<Integer> ngrp_new, joutp_new;
    Integer         nsubm_new = 0;

    string          hmat_new;
    Real            amass_new = 0.0;
    vector<Real>    temp_new, sigz_new;
    vector<Integer> itype_new, n1d_new, n2d_new, locs_new;

    vector<MatxsSubmaterialData> submat_obj_new;

    int i_max = static_cast<int>(matxs_obj_vec.size());
    for(int i=0; i<i_max; i++)
    {
      MatxsMaterialData mat_obj_ori = matxs_obj_vec[i].get_mat_obj()[m];

      Integer         nsubm_ori = mat_obj_ori.get_nsubm();

      vector<Real>    temp_ori  = mat_obj_ori.get_temp();
      vector<Real>    sigz_ori  = mat_obj_ori.get_sigz();
      vector<Integer> itype_ori = mat_obj_ori.get_itype();
      vector<Integer> n1d_ori   = mat_obj_ori.get_n1d();
      vector<Integer> n2d_ori   = mat_obj_ori.get_n2d();
      vector<Integer> locs_ori  = mat_obj_ori.get_locs(); 

      vector<MatxsSubmaterialData> submat_obj_ori = mat_obj_ori.get_submat_obj();

      if( nsubm_ori > 0 && nsubm_new == 0 )
      {
        nsubm_new = static_cast<Integer>(temp_ori.size());

        ngrp_new  = matxs_obj_vec[i].get_ngrp();
        joutp_new = matxs_obj_vec[i].get_joutp();

        hmat_new  = mat_obj_ori.get_hmat();
        amass_new = mat_obj_ori.get_amass();

        temp_new  = temp_ori;
        sigz_new  = sigz_ori;
        itype_new = itype_ori;
        n1d_new   = n1d_ori;
        n2d_new   = n2d_ori;
        locs_new  = locs_ori;

        submat_obj_new = submat_obj_ori;
      }
      else
      {
        int k_max = static_cast<int>(temp_ori.size());
        for(int k=0; k<k_max; k++)
        {
          if( check_temp_sigz_itype
                (temp_new, temp_ori[k], sigz_new, sigz_ori[k], itype_new, itype_ori[k]) < 0 )
          {
            nsubm_new++;
            temp_new.push_back(temp_ori[k]);
            sigz_new.push_back(sigz_ori[k]);
            itype_new.push_back(itype_ori[k]);
            n1d_new.push_back(n1d_ori[k]);
            n2d_new.push_back(n2d_ori[k]);
            locs_new.push_back(locs_ori[k]);

            submat_obj_new.push_back(submat_obj_ori[k]);
          }
        }
      }
      mat_obj_ori.clear();
      vector<MatxsSubmaterialData>().swap(submat_obj_ori);
    }

    nsubm_new_vec[m] = nsubm_new;

    mat_obj_new[m].clear();
    mat_obj_new[m].set_ngrp(ngrp_new);
    mat_obj_new[m].set_joutp(joutp_new);
    mat_obj_new[m].set_nsubm(nsubm_new);

    mat_obj_new[m].set_hmat(hmat_new);
    mat_obj_new[m].set_amass(amass_new);

    mat_obj_new[m].set_temp(temp_new);
    mat_obj_new[m].set_sigz(sigz_new);
    mat_obj_new[m].set_itype(itype_new);
    mat_obj_new[m].set_n1d(n1d_new);
    mat_obj_new[m].set_n2d(n2d_new);
    mat_obj_new[m].set_locs(locs_new);

    mat_obj_new[m].set_submat_obj(submat_obj_new);

    vector<MatxsSubmaterialData>().swap(submat_obj_new);
  }

  matxs_obj.set_mat_obj(mat_obj_new);
  vector<MatxsMaterialData>().swap(mat_obj_new);

  matxs_obj.set_nsubm(nsubm_new_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int MatxsMerger::check_temp_sigz_itype(vector<Real>&    temp_new,  Real&    temp_val,
                                       vector<Real>&    sigz_new,  Real&    sigz_val,
                                       vector<Integer>& itype_new, Integer& itype_val)
{
  int i_max = static_cast<int>(temp_new.size());

  Real temp_err = fabs(tolerance * temp_val);
  if( temp_err < min_value )
  {
    temp_err = min_value;
  }

  Real sigz_err = fabs(tolerance * sigz_val);
  if( sigz_err < min_value )
  {
    sigz_err = min_value;
  }

  int ele_no = -1;
  for(int i=0; i<i_max; i++)
  {
    if( fabs(temp_new[i] - temp_val) < temp_err &&
        fabs(sigz_new[i] - sigz_val) < sigz_err &&
        itype_new[i] == itype_val )
    {
      ele_no = i;
      break;
    }
  }

  return ele_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::sort_5d_data()
{
  vector<MatxsMaterialData> mat_obj_new, mat_obj_ori;

  mat_obj_ori = matxs_obj.get_mat_obj();
  mat_obj_new.clear();

  int i_max = static_cast<int>(mat_obj_ori.size());
  mat_obj_new.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    vector<Real>    temp  = mat_obj_ori[i].get_temp();
    vector<Real>    sigz  = mat_obj_ori[i].get_sigz();
    vector<Integer> itype = mat_obj_ori[i].get_itype();
    vector<Integer> n1d   = mat_obj_ori[i].get_n1d();
    vector<Integer> n2d   = mat_obj_ori[i].get_n2d();
    vector<Integer> locs  = mat_obj_ori[i].get_locs();
    vector<MatxsSubmaterialData> submat_obj = mat_obj_ori[i].get_submat_obj();

    int type_no = static_cast<int>(htype_new.size());
    vector<vector<int> > pos_ori;
    pos_ori.resize(type_no);

    int data_no = static_cast<int>(itype.size());
    for(int j=0; j<data_no; j++)
    {
      pos_ori[itype[j]-1].push_back(j);
    }

    mat_obj_new[i].set_ngrp(mat_obj_ori[i].get_ngrp());
    mat_obj_new[i].set_joutp(mat_obj_ori[i].get_joutp());
    mat_obj_new[i].set_nsubm(mat_obj_ori[i].get_nsubm());
    mat_obj_new[i].set_hmat(mat_obj_ori[i].get_hmat());
    mat_obj_new[i].set_amass(mat_obj_ori[i].get_amass());

    vector<Real>    temp_new, sigz_new;
    vector<Integer> itype_new, n1d_new, n2d_new, locs_new;
    vector<MatxsSubmaterialData> submat_obj_new;
    temp_new.resize(data_no);
    sigz_new.resize(data_no);
    itype_new.resize(data_no);
    n1d_new.resize(data_no);
    n2d_new.resize(data_no);
    locs_new.resize(data_no);
    submat_obj_new.resize(data_no);

    int ele_no = 0;
    for(int j=0; j<type_no; j++)
    {
      for(int k=0; k<static_cast<int>(pos_ori[j].size()); k++)
      {
        int l = pos_ori[j][k];
        temp_new[ele_no]  = temp[l];
        sigz_new[ele_no]  = sigz[l];
        itype_new[ele_no] = itype[l];
        n1d_new[ele_no]   = n1d[l];
        n2d_new[ele_no]   = n2d[l];
        locs_new[ele_no]  = locs[l];
        submat_obj_new[ele_no] = submat_obj[l];
        ele_no++;
      }
    }
    vector<MatxsSubmaterialData>().swap(submat_obj);

    mat_obj_new[i].set_temp(temp_new);
    mat_obj_new[i].set_sigz(sigz_new);
    mat_obj_new[i].set_itype(itype_new);
    mat_obj_new[i].set_n1d(n1d_new);
    mat_obj_new[i].set_n2d(n2d_new);
    mat_obj_new[i].set_locs(locs_new);
    mat_obj_new[i].set_submat_obj(submat_obj_new);
    vector<MatxsSubmaterialData>().swap(submat_obj_new);
  }

  matxs_obj.set_mat_obj(mat_obj_new);
  vector<MatxsMaterialData>().swap(mat_obj_ori);
  vector<MatxsMaterialData>().swap(mat_obj_new);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::mod_6d_10d_data()
{
  vector<MatxsMaterialData> mat_obj = matxs_obj.get_mat_obj();

  int i_max = static_cast<int>(mat_obj.size());
  for(int i=0; i<i_max; i++)
  {
    vector<Real>    temp  = mat_obj[i].get_temp();
    vector<Real>    sigz  = mat_obj[i].get_sigz();
    vector<Integer> itype = mat_obj[i].get_itype();

    vector<MatxsSubmaterialData> submat_obj = mat_obj[i].get_submat_obj();

    MatxsSubmaterialData submat_ori;
    submat_ori.clear();

    int j_max = static_cast<int>(temp.size());
    for(int j=1; j<j_max; j++)
    {
      int pos_dif = check_sigz_itype(j, sigz, itype);

      if( pos_dif >= 0 )
      {
        //Modify 6d and 7d data
        //mod_submat_data(submat_obj[pos_dif], submat_obj[j], -1);

        //Modify 8d - 10d data
        //mod_matrix_data(submat_obj[pos_dif], submat_obj[j], -1);

        Real temp_err_ini = fabs(tolerance * temp[0]);
        if( temp_err_ini < min_value )
        {
          temp_err_ini = min_value;
        }
        if( fabs(temp[j] - temp[0]) < temp_err_ini )
        {
          continue;
        }

        Real temp_err = fabs(tolerance * temp[j]);
        if( temp_err < min_value )
        {
          temp_err = min_value;
        }

        if( fabs(temp[j] - temp[j-1]) > temp_err )
        {
          //Modify 6d and 7d data
          mod_submat_data(submat_obj[pos_dif], submat_obj[j], -1);

          //Modify 8d - 10d data
          mod_matrix_data(submat_obj[pos_dif], submat_obj[j], -1);

          submat_ori = submat_obj[j];
        }
        else
        {
          //Modify 6d and 7d data (add original differential data)
          mod_submat_data(submat_ori, submat_obj[j], +1);

          //Modify 8d - 10d data (add original differential data)
          mod_matrix_data(submat_ori, submat_obj[j], +1);
        }
      }
    }

    mat_obj[i].set_submat_obj(submat_obj);
    vector<MatxsSubmaterialData>().swap(submat_obj);
  }

  matxs_obj.set_mat_obj(mat_obj);

  vector<MatxsMaterialData>().swap(mat_obj);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int MatxsMerger::check_sigz_itype(int pos, vector<Real>& sigz, vector<Integer>& itype)
{
  Real    sigz_val  = sigz[pos];
  Integer itype_val = itype[pos];

  Real sigz_err = fabs(tolerance * sigz_val);
  if( sigz_err < min_value )
  {
    sigz_err = min_value;
  }

  int ele_no = -1;
  for(int i=0; i<pos; i++)
  {
    if( fabs(sigz[i] - sigz_val) < sigz_err &&
        itype[i] == itype_val )
    {
      ele_no = i;
      break;
    }
  }

  return ele_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::mod_submat_data(MatxsSubmaterialData& submat_ori,
                                  MatxsSubmaterialData& submat_dif, int merge_flg)
{
  vector<string>          hvps_ori, hvps_dif;
  vector<Integer>         nfg_ori, nfg_dif, nlg_ori, nlg_dif;
  vector<vector<Real> >   vps_ori, vps_dif;
  vector<MatxsMatrixData> matrix_ori, matrix_dif;

  hvps_ori   = submat_ori.get_hvps();
  nfg_ori    = submat_ori.get_nfg();
  nlg_ori    = submat_ori.get_nlg();
  vps_ori    = submat_ori.get_vps();
  matrix_ori = submat_ori.get_matrix_obj();

  hvps_dif   = submat_dif.get_hvps();
  nfg_dif    = submat_dif.get_nfg();
  nlg_dif    = submat_dif.get_nlg();
  vps_dif    = submat_dif.get_vps();
  matrix_dif = submat_dif.get_matrix_obj();

  int i_max = static_cast<int>(hvps_ori.size());
  int j_max = static_cast<int>(hvps_dif.size());
  for(int i=0; i<i_max; i++)
  {
    string hvps_str_ori = str_util.trim_space(hvps_ori[i]);
    for(int j=0; j<j_max; j++)
    {
      string hvps_str_dif = str_util.trim_space(hvps_dif[j]);
      if( hvps_str_ori == hvps_str_dif )
      {
        mod_7d_data(hvps_str_ori, nfg_ori[i], nlg_ori[i], vps_ori[i],
                                  nfg_dif[j], nlg_dif[j], vps_dif[j], merge_flg);
        break;
      }
    }
  }

  submat_dif.set_nfg(nfg_dif);
  submat_dif.set_nlg(nlg_dif);
  submat_dif.set_vps(vps_dif);
  submat_dif.set_matrix_obj(matrix_dif); 

  vector<MatxsMatrixData>().swap(matrix_ori);
  vector<MatxsMatrixData>().swap(matrix_dif);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::mod_7d_data(string& hvps,
                              Integer& nfg_ori, Integer& nlg_ori, vector<Real>& vps_ori,
                              Integer& nfg_dif, Integer& nlg_dif, vector<Real>& vps_dif,
                              int merge_flg)
{
  vector<string> hvps_skip;
  hvps_skip.push_back("wt");

  int skip_flg = -1;
  for(int i=0; i<static_cast<int>(hvps_skip.size()); i++)
  {
    if( hvps.find(hvps_skip[i]) != string::npos )
    {
      skip_flg = i;
      break;
    }
  }

  if( skip_flg >= 0 )
  {
    //Skip modification
    return;
  }

  vector<Real> vps_ori_mod, vps_dif_mod, vps_comp;
  int i_max = nlg_ori;
  if( i_max < nlg_dif )
  {
    i_max = nlg_dif;
  }

  vps_ori_mod.resize(i_max);
  vps_dif_mod.resize(i_max);
  vps_comp.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    vps_ori_mod[i] = 0.0;
    vps_dif_mod[i] = 0.0;

    if( i+1 >= nfg_ori && i+1 <= nlg_ori )
    {
      vps_ori_mod[i] = vps_ori[i - (nfg_ori - 1)];
    }

    if( i+1 >= nfg_dif && i+1 <= nlg_dif )
    {
      vps_dif_mod[i] = vps_dif[i - (nfg_dif - 1)];
    }

    if( merge_flg < 0 )
    {
      vps_comp[i] = vps_dif_mod[i] - vps_ori_mod[i];
    }
    else if( merge_flg > 0 )
    {
      vps_comp[i] = vps_dif_mod[i] + vps_ori_mod[i];
    }
    else //if( merge_flg == 0 )
    {
      vps_comp[i] = vps_dif_mod[i];
    }

    Real err_val = fabs(tolerance * vps_ori_mod[i]);
    if( err_val < min_value )
    {
      err_val = min_value;
    }
    if( fabs(vps_comp[i]) < err_val )
    {
      vps_comp[i] = 0.0;
    }
  }

  Integer      nfg_new = -1;
  Integer      nlg_new = -1;
  vector<Real> vps_new;
  for(int i=0; i<i_max; i++)
  {
    if( fabs(vps_comp[i]) > min_value )
    {
      nfg_new = i+1;
      break;
    }
  }

  for(int i=i_max-1; i>=0; i--)
  {
    if( fabs(vps_comp[i]) > min_value )
    {
      nlg_new = i+1;
      break;
    }
  }

  vps_new.clear();
  if( nfg_new < 0 || nlg_new < 0 )
  {
    nfg_new = 1;
    nlg_new = 1;
    vps_new.resize(1);
    vps_new[0] = 0.0;
  }
  else
  {
    for(int i=0; i<i_max; i++)
    {
      if( i+1 >= nfg_new && i+1 <= nlg_new )
      {
        vps_new.push_back(vps_comp[i]);
      }
    }
  }

  nfg_dif = nfg_new;
  nlg_dif = nlg_new;
  vps_dif = vps_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::mod_matrix_data(MatxsSubmaterialData& submat_ori,
                                  MatxsSubmaterialData& submat_dif, int merge_flg)
{
  vector<MatxsMatrixData> matrix_ori = submat_ori.get_matrix_obj();
  vector<MatxsMatrixData> matrix_dif = submat_dif.get_matrix_obj();

  int i_max = static_cast<int>(matrix_ori.size());
  int j_max = static_cast<int>(matrix_dif.size());
  for(int i=0; i<i_max; i++)
  {
    string hmtx_ori = str_util.trim_space(matrix_ori[i].get_hmtx());
    for(int j=0; j<j_max; j++)
    {
      string hmtx_dif = str_util.trim_space(matrix_dif[j].get_hmtx());
      if( hmtx_ori == hmtx_dif )
      {
        mod_8d_10d_data(matrix_ori[i], matrix_dif[j], merge_flg);
        break;
      }
    }
  }

  submat_ori.set_matrix_obj(matrix_ori);
  submat_dif.set_matrix_obj(matrix_dif);
  vector<MatxsMatrixData>().swap(matrix_ori);
  vector<MatxsMatrixData>().swap(matrix_dif);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::mod_8d_10d_data(MatxsMatrixData& matrix_ori,
                                  MatxsMatrixData& matrix_dif, int merge_flg)
{
  check_matrix_data(matrix_ori, matrix_dif);

  //9d
  mod_9d_data(matrix_ori, matrix_dif, merge_flg);

  //10d
  vector<Real> spec_ori = matrix_ori.get_spec();
  vector<Real> spec_dif = matrix_dif.get_spec();
  vector<Real> prod_ori = matrix_ori.get_prod();
  vector<Real> prod_dif = matrix_dif.get_prod();

  int i_max = static_cast<int>(spec_ori.size());
  if( merge_flg < 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      spec_dif[i] = spec_dif[i] - spec_ori[i];
    }
  }
  else if( merge_flg > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      spec_dif[i] = spec_dif[i] + spec_ori[i];
    }
  }
  matrix_dif.set_spec(spec_dif);
  spec_ori.clear();
  spec_dif.clear();

  i_max = static_cast<int>(prod_ori.size());
  if( merge_flg < 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      prod_dif[i] = prod_dif[i] - prod_ori[i];
    }
  }
  else if( merge_flg > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      prod_dif[i] = prod_dif[i] + prod_ori[i];
    }
  }
  matrix_dif.set_prod(prod_dif);
  prod_ori.clear();
  prod_dif.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::check_matrix_data(MatxsMatrixData& matrix_ori, MatxsMatrixData& matrix_dif)
{
  Integer         lord_ori   = matrix_ori.get_lord();
  Integer         jconst_ori = matrix_ori.get_jconst();
  vector<Integer> jband_ori  = matrix_ori.get_jband();
  vector<Integer> ijj_ori    = matrix_ori.get_ijj();
  Integer         lord_dif   = matrix_dif.get_lord();
  Integer         jconst_dif = matrix_dif.get_jconst();
  vector<Integer> jband_dif  = matrix_dif.get_jband();
  vector<Integer> ijj_dif    = matrix_dif.get_ijj();

/*
string hmtx_err = "free";
string hmtx_chk = str_util.trim_space(matrix_ori.get_hmtx());
if( hmtx_err == hmtx_chk )
{
cout.precision(8);
cout.setf(ios::showpoint);
cout.setf(ios::scientific);
  vector<vector<vector<Real> > > scat_ori = matrix_ori.get_scat();
  vector<vector<vector<Real> > > scat_dif = matrix_dif.get_scat();
  int i_max = static_cast<int>(scat_dif.size());
  for(int i=0; i<i_max; i++)
  {
    cout << i+1 << " / " << i_max << " : jband : " << jband_ori[i] << " / " << jband_dif[i]
                                  << " : ijj : "   << ijj_ori[i]   << " / " << ijj_dif[i];
    if( jband_ori[i] != jband_dif[i] )
    {
      cout << " *****";
    }
    cout << endl;

    cout << "  === ori ===" << endl;
    int j_max = static_cast<int>(scat_ori[i].size());
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(scat_ori[i][j].size());
      cout << "    " << j+1 << " : " << j_max << " : " << k_max << " : ";
      for(int k=0; k<k_max; k++)
      {
         if( scat_ori[i][j][k] < -1.0 * min_value )
         {
           cout << "  " << scat_ori[i][j][k];
         }
         else
         {
           cout << "   " << scat_ori[i][j][k];
         }
      }
      cout << endl;
    }
    cout << endl;

    cout << "  === dif ===" << endl;
        j_max = static_cast<int>(scat_dif[i].size());
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(scat_dif[i][j].size());
      cout << "    " << j+1 << " : " << j_max << " : " << k_max << " : ";
      for(int k=0; k<k_max; k++)
      {
         if( scat_dif[i][j][k] < -1.0 * min_value )
         {
           cout << "  " << scat_dif[i][j][k];
         }
         else
         {
           cout << "   " << scat_dif[i][j][k];
         }
      }
      cout << endl;
    }
    cout << endl;
  }
}
*/

  if( lord_ori != lord_dif )
  {
    ostringstream oss01, oss02;
    oss01 << lord_ori;
    oss02 << lord_dif;

    string class_name = "MatxsMerger";
    string func_name  = "check_matrix_data";

    string str_data01 = "hmtx               : " + matrix_ori.get_hmtx();
    string str_data02 = "lord of first data : " + oss01.str();
    string str_data03 = "lord of other data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("lord of first data must be equal to that of other data.");
    err_com.push_back("Please check the 8d, 9d, and 10d data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( jconst_ori != jconst_dif )
  {
    ostringstream oss01, oss02;
    oss01 << jconst_ori;
    oss02 << jconst_dif;

    string class_name = "MatxsMerger";
    string func_name  = "check_matrix_data";

    string str_data01 = "hmtx                 : " + matrix_ori.get_hmtx();
    string str_data02 = "jconst of first data : " + oss01.str();
    string str_data03 = "jconst of other data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("jconst of first data must be equal to that of other data.");
    err_com.push_back("Please check the 8d, 9d, and 10d data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int noutg = static_cast<int>(jband_ori.size());
  if( noutg != static_cast<int>(jband_dif.size()) )
  {
    ostringstream oss01, oss02;
    oss01 << noutg;
    oss02 << static_cast<int>(jband_dif.size());

    string class_name = "MatxsMerger";
    string func_name  = "check_matrix_data";

    string str_data01 = "hmtx                : " + matrix_ori.get_hmtx();
    string str_data02 = "noutg of first data : " + oss01.str();
    string str_data03 = "noutg of other data : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("noutg of first data must be equal to that of other data.");
    err_com.push_back("Please check the 8d, 9d, and 10d data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::mod_9d_data(MatxsMatrixData& matrix_ori,
                              MatxsMatrixData& matrix_dif, int merge_flg)
{
  vector<Integer> jband_ori  = matrix_ori.get_jband();
  vector<Integer> ijj_ori    = matrix_ori.get_ijj();
  vector<Integer> jband_dif  = matrix_dif.get_jband();
  vector<Integer> ijj_dif    = matrix_dif.get_ijj();

  vector<vector<vector<Real> > > scat_ori = matrix_ori.get_scat();
  vector<vector<vector<Real> > > scat_dif = matrix_dif.get_scat();

  //Modify scat
  vector<vector<vector<Real> > > scat_ori_new, scat_dif_new;
  int i_max = static_cast<int>(jband_ori.size());
  scat_ori_new.resize(i_max);
  scat_dif_new.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int j_max = matrix_ori.get_lord();
    scat_ori_new[i].resize(j_max);
    scat_dif_new[i].resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      int k_max = i_max;
      scat_ori_new[i][j].resize(k_max);
      scat_dif_new[i][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        scat_ori_new[i][j][k] = calc_scat(j, k, jband_ori[i], ijj_ori[i], scat_ori[i]);
        scat_dif_new[i][j][k] = calc_scat(j, k, jband_dif[i], ijj_dif[i], scat_dif[i]);

        if( merge_flg < 0 )
        {
          scat_dif_new[i][j][k] = scat_dif_new[i][j][k] - scat_ori_new[i][j][k];
        }
        else if( merge_flg > 0 )
        {
          scat_dif_new[i][j][k] = scat_dif_new[i][j][k] + scat_ori_new[i][j][k];
        }
      }
    }
  }

  //Remove zero data
  vector<Integer> jband_new, ijj_new;
  mod_scat_data(jband_new, ijj_new, scat_dif_new);
  matrix_dif.set_jband(jband_new);
  matrix_dif.set_ijj(ijj_new);
  matrix_dif.set_scat(scat_dif_new);

  jband_new.clear();
  ijj_new.clear();
  vector<vector<vector<Real> > >().swap(scat_ori);
  vector<vector<vector<Real> > >().swap(scat_dif);
  vector<vector<vector<Real> > >().swap(scat_ori_new);
  vector<vector<vector<Real> > >().swap(scat_dif_new);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real MatxsMerger::calc_scat(int j, int k, Integer& jband, Integer& ijj, vector<vector<Real> >& scat)
{
  if( static_cast<int>(scat.size()) == 0 || (jband == 0 && ijj == 0 ) )
  {
    return 0.0;
  }
  else if( static_cast<int>(scat[j].size()) == 0 )
  {
    return 0.0;
  }

  int k_max = ijj - 1;
  int k_min = k_max - jband + 1;
  if( k_min <= k && k < k_max )
  {
    return scat[j][k - k_min];
  }
  else
  {
    return 0.0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::mod_scat_data(vector<Integer>& jband, vector<Integer>& ijj,
                                        vector<vector<vector<Real > > >& scat)
{
  int i_max = static_cast<int>(scat.size());
  jband.resize(i_max);
  ijj.resize(i_max);
  if( i_max == 0 )
  {
    return;
  }

  for(int i=0; i<i_max; i++)
  {
    remove_zero_scat_data(jband[i], ijj[i], scat[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::remove_zero_scat_data(Integer& jband, Integer& ijj, vector<vector<Real > >& scat)
{
  jband = 0;
  ijj   = 0;

  int j_max = static_cast<int>(scat.size());
  if( j_max == 0 )
  {
    return;
  }

  int ng = static_cast<int>(scat[0].size());
  int k_min = -1;
  int k_max = -1;
  for(int j=0; j<j_max; j++)
  {
    for(int k=0; k<ng; k++)
    {
      if( fabs(scat[j][k]) > min_value )
      {
        if( k_min == -1 || k < k_min )
        {
          k_min = k;
        }
        break;
      }
    }

    for(int k=ng-1; k>=0; k--)
    {
      if( fabs(scat[j][k]) > min_value )
      {
        if( k_max == -1 || k_max < k )
        {
          k_max = k;
        }
        break;
      }
    }
  }

  if( k_min < 0 || k_max < 0 )
  {
    jband = 0;
    ijj   = 0;

    vector<vector<Real> >().swap(scat);
  }
  else
  {
    ijj   = k_max + 1;
    jband = ijj - k_min;

    vector<vector<Real> > scat_new;
    scat_new.resize(j_max);
    for(int j=0; j<j_max; j++)
    {
      scat_new[j].resize(jband);

      int ele_no = 0;
      for(int k=k_min; k<ijj; k++)
      {
        scat_new[j][ele_no] = scat[j][k];
        ele_no++;
      }
    }

    scat = scat_new;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::merge_matxs_file(vector<string> file_name_vec)
{
  clear();

  int i_max = static_cast<int>(file_name_vec.size());
  for(int i=0; i<i_max; i++)
  {
    MatxsParser read_obj;
    read_obj.set_file_name(file_name_vec[i]);

    matxs_obj_vec.push_back(read_obj.get_matxs_obj());
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::merge_matxs_obj(vector<MatxsCommonData> matxs_vec)
{
  clear();

  matxs_obj_vec = matxs_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MatxsMerger::get_text()
{
  merge_matxs_obj();

  MatxsWriter wri_obj;
  wri_obj.set_matxs_obj(matxs_obj);

  return wri_obj.get_text();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

MatxsCommonData MatxsMerger::get_matxs_obj()
{
  merge_matxs_obj();

  return matxs_obj;
} 

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsMerger::write_matxs_obj(string file_name)
{
  merge_matxs_obj();

  MatxsWriter wri_obj;
  wri_obj.set_matxs_obj(matxs_obj);
  wri_obj.write_matxs(file_name);
}

