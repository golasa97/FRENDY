#include "MGXSUtils/MatxsUtils/MatxsCompare.hpp"

using namespace frendy;

// ***** MatxsCompare ***** //
//constructor
MatxsCompare::MatxsCompare(void)
{
  class_name = "MatxsCompare";
  clear();
}

//destructor
MatxsCompare::~MatxsCompare(void)
{
  class_name.clear();
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCompare::clear()
{
  add_original_data_flg = 1;

  matxs_obj_com.clear();
  matxs_obj_ref.clear();

  hmat_info.clear();
  hmtx_info.clear();

  structure_pos = 0;
  mat_pos       = 0;
  submat_pos    = 0;
  matrix_pos    = 0;

  comp_obj.clear();
  comp_obj.set_tolerance_val(1.0E-4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCompare::comp_matxs_file(string matxs_name_com, string matxs_name_ref)
{
  MatxsParser read_obj;

  cout << "Read MATXS file (com) : " + matxs_name_com << endl;
  read_obj.set_file_name(matxs_name_com);
  matxs_obj_com = read_obj.get_matxs_obj();

  cout << "Read MATXS file (ref) : " + matxs_name_ref << endl;
  read_obj.set_file_name(matxs_name_ref);
  matxs_obj_ref = read_obj.get_matxs_obj();

  comp_matxs_file();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCompare::comp_matxs_file(MatxsCommonData parse_obj_com, MatxsCommonData parse_obj_ref)
{
  matxs_obj_com = parse_obj_com;
  matxs_obj_ref = parse_obj_ref;
  parse_obj_com.clear();
  parse_obj_ref.clear();

  comp_matxs_file();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCompare::comp_matxs_file()
{
  //Comparison of 0v, 1d, 2d, and 3d data
  comp_common_data(matxs_obj_com, matxs_obj_ref);

  //Comparison of 4d data
  comp_structure_data(matxs_obj_com.get_grp_obj(), matxs_obj_ref.get_grp_obj());

  //Comparison of 5d - 10d data
  comp_material_data(matxs_obj_com.get_mat_obj(), matxs_obj_ref.get_mat_obj());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCompare::comp_common_data(MatxsCommonData parse_obj_com, MatxsCommonData parse_obj_ref)
{
  string func_name = "comp_common_data";
  comp_obj.set_information_data(class_name, func_name);

  //Comparison of 0v data
  comp_obj.set_comp_data_information("hname (0v)");
  comp_obj.comp_line_data(parse_obj_com.get_hname(), parse_obj_ref.get_hname());
  comp_obj.set_comp_data_information("huse (0v)");
  comp_obj.comp_line_data(parse_obj_com.get_huse(),  parse_obj_ref.get_huse());
  comp_obj.set_comp_data_information("ivers (0v)");
  comp_obj.comp_int_data(parse_obj_com.get_ivers(),  parse_obj_ref.get_ivers());

  //Comparison of 1d data
  comp_obj.set_comp_data_information("npart (1d)");
  comp_obj.comp_int_data(parse_obj_com.get_npart(),  parse_obj_ref.get_npart());
  comp_obj.set_comp_data_information("ntype (1d)");
  comp_obj.comp_int_data(parse_obj_com.get_ntype(),  parse_obj_ref.get_ntype());
  comp_obj.set_comp_data_information("nholl (1d)");
  comp_obj.comp_int_data(parse_obj_com.get_nholl(),  parse_obj_ref.get_nholl());
  comp_obj.set_comp_data_information("nmat (1d)");
  comp_obj.comp_int_data(parse_obj_com.get_nmat(),   parse_obj_ref.get_nmat());
  comp_obj.set_comp_data_information("matxw (1d)");
  comp_obj.comp_int_data(parse_obj_com.get_matxw(),  parse_obj_ref.get_matxw());
  comp_obj.set_comp_data_information("length (1d)");
  comp_obj.comp_int_data(parse_obj_com.get_length(), parse_obj_ref.get_length());

  //Comparison of 2d data
  int i_com = static_cast<int>(parse_obj_com.get_hsetid().size());
  int i_ref = static_cast<int>(parse_obj_ref.get_hsetid().size());
  comp_obj.set_comp_data_information("imax of hsetid (2d)");
  comp_obj.comp_int_data(i_com, i_ref);
  for(int i=0; i<i_com; i++)
  {
    comp_obj.set_comp_data_information("hsetid (2d)");
    comp_obj.set_comp_data_position(i);
    comp_obj.comp_line_data(parse_obj_com.get_hsetid()[i],  parse_obj_ref.get_hsetid()[i]);
    comp_obj.clear_comp_data_position();
  }

  //Comparison of 3d data
  i_com = static_cast<int>(parse_obj_com.get_hpart().size());
  i_ref = static_cast<int>(parse_obj_ref.get_hpart().size());
  comp_obj.set_comp_data_information("imax of hpart (3d)");
  comp_obj.comp_int_data(i_com, i_ref);
  for(int i=0; i<i_com; i++)
  {
    comp_obj.set_comp_data_information("hpart (3d)");
    comp_obj.set_comp_data_position(i);
    comp_obj.comp_line_data(parse_obj_com.get_hpart()[i],  parse_obj_ref.get_hpart()[i]);
    comp_obj.clear_comp_data_position();
  }

  i_com = static_cast<int>(parse_obj_com.get_htype().size());
  i_ref = static_cast<int>(parse_obj_ref.get_htype().size());
  comp_obj.set_comp_data_information("imax of htype (3d)");
  comp_obj.comp_int_data(i_com, i_ref);
  for(int i=0; i<i_com; i++)
  {
    comp_obj.set_comp_data_information("htype (3d)");
    comp_obj.set_comp_data_position(i);
    comp_obj.comp_line_data(parse_obj_com.get_htype()[i],  parse_obj_ref.get_htype()[i]);
    comp_obj.clear_comp_data_position();
  }

  i_com = static_cast<int>(parse_obj_com.get_hmatn().size());
  i_ref = static_cast<int>(parse_obj_ref.get_hmatn().size());
  comp_obj.set_comp_data_information("imax of hmatn (3d)");
  comp_obj.comp_int_data(i_com, i_ref);
  for(int i=0; i<i_com; i++)
  {
    comp_obj.set_comp_data_information("hmatn (3d)");
    comp_obj.set_comp_data_position(i);
    comp_obj.comp_line_data(parse_obj_com.get_hmatn()[i],  parse_obj_ref.get_hmatn()[i]);
    comp_obj.clear_comp_data_position();
  }

  comp_obj.set_comp_data_information("ngrp (3d)");
  comp_obj.comp_list_data(parse_obj_com.get_ngrp(), parse_obj_ref.get_ngrp());
  comp_obj.set_comp_data_information("jinp (3d)");
  comp_obj.comp_list_data(parse_obj_com.get_jinp(), parse_obj_ref.get_jinp());
  comp_obj.set_comp_data_information("joutp (3d)");
  comp_obj.comp_list_data(parse_obj_com.get_joutp(), parse_obj_ref.get_joutp());
  comp_obj.set_comp_data_information("nsubm (3d)");
  comp_obj.comp_list_data(parse_obj_com.get_nsubm(), parse_obj_ref.get_nsubm());
  comp_obj.set_comp_data_information("locm (3d)");
  comp_obj.comp_list_data(parse_obj_com.get_locm(), parse_obj_ref.get_locm());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCompare::comp_structure_data(vector<MatxsGroupStructureData> parse_obj_com,
                                       vector<MatxsGroupStructureData> parse_obj_ref)
{
  //Comparison of 4d data
  int vec_no_com = static_cast<int>(parse_obj_com.size());
  int vec_no_ref = static_cast<int>(parse_obj_ref.size());
  if( vec_no_com != vec_no_ref )
  {
    string class_name = "MatxsCompare";
    string func_name  = "comp_structure_data";

    ostringstream oss01, oss02;
    oss01 << vec_no_com;
    oss02 << vec_no_ref;
    string str_data01 = "Number of MatxsGroupStructureData (com) : " + oss01.str();
    string str_data02 = "Number of MatxsGroupStructureData (ref) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of MatxsGroupStructureData data is different.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<vec_no_com; i++)
  {
    structure_pos = i+1;
    comp_structure_data(parse_obj_com[i], parse_obj_ref[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCompare::comp_material_data(vector<MatxsMaterialData> parse_obj_com,
                                      vector<MatxsMaterialData> parse_obj_ref)
{
  //Comparison of 5d data
  int vec_no_com = static_cast<int>(parse_obj_com.size());
  int vec_no_ref = static_cast<int>(parse_obj_ref.size());
  if( vec_no_com != vec_no_ref )
  {
    string class_name = "MatxsCompare";
    string func_name  = "comp_material_data";

    ostringstream oss01, oss02;
    oss01 << vec_no_com;
    oss02 << vec_no_ref;
    string str_data01 = "Number of MatxsMaterialData (com) : " + oss01.str();
    string str_data02 = "Number of MatxsMaterialData (ref) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of MatxsMaterialData data is different.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<vec_no_com; i++)
  {
    mat_pos = i+1;
    comp_material_data(parse_obj_com[i], parse_obj_ref[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCompare::comp_submaterial_data(vector<MatxsSubmaterialData> parse_obj_com,
                                         vector<MatxsSubmaterialData> parse_obj_ref)
{
  //Comparison of 6d and 7d data
  int vec_no_com = static_cast<int>(parse_obj_com.size());
  int vec_no_ref = static_cast<int>(parse_obj_ref.size());
  if( vec_no_com != vec_no_ref )
  {
    string class_name = "MatxsCompare";
    string func_name  = "comp_submaterial_data";

    ostringstream oss01, oss02;
    oss01 << vec_no_com;
    oss02 << vec_no_ref;
    string str_data01 = "Number of MatxsSubmaterialData (com) : " + oss01.str();
    string str_data02 = "Number of MatxsSubmaterialData (ref) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of MatxsSubmaterialData data is different.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<vec_no_com; i++)
  {
    submat_pos = i+1;
    comp_submaterial_data(parse_obj_com[i], parse_obj_ref[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCompare::comp_matrix_data(vector<MatxsMatrixData> parse_obj_com,
                                    vector<MatxsMatrixData> parse_obj_ref)
{
  //Comparison of 8d, 9d, and 10d data
  int vec_no_com = static_cast<int>(parse_obj_com.size());
  int vec_no_ref = static_cast<int>(parse_obj_ref.size());
  if( vec_no_com != vec_no_ref )
  {
    string class_name = "MatxsCompare";
    string func_name  = "comp_matrix_data";

    ostringstream oss01, oss02;
    oss01 << vec_no_com;
    oss02 << vec_no_ref;
    string str_data01 = "Number of MatxsMatrixData (com) : " + oss01.str();
    string str_data02 = "Number of MatxsMatrixData (ref) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of MatxsMatrixData data is different.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=0; i<vec_no_com; i++)
  {
    matrix_pos = i+1;
    comp_matrix_data(parse_obj_com[i], parse_obj_ref[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////


void MatxsCompare::comp_structure_data(MatxsGroupStructureData parse_obj_com,
                                       MatxsGroupStructureData parse_obj_ref)
{
  //Comparison of 4d data
  string func_name = "comp_structure_data";
  comp_obj.set_information_data(class_name, func_name);
  comp_obj.set_comp_data_position(structure_pos);

  comp_obj.set_comp_data_information("ngrp (4d)");
  comp_obj.comp_int_data(parse_obj_com.get_ngrp(),  parse_obj_ref.get_ngrp());

  comp_obj.set_comp_data_information("gpb (4d)");
  comp_obj.comp_list_data(parse_obj_com.get_gpb(),  parse_obj_ref.get_gpb());

}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCompare::comp_material_data(MatxsMaterialData parse_obj_com,
                                      MatxsMaterialData parse_obj_ref)
{
  //Comparison of 5d data
  string func_name = "comp_material_data";
  comp_obj.set_information_data(class_name, func_name);

  comp_obj.set_comp_data_information("hmat (5d)");
  comp_obj.comp_line_data(parse_obj_com.get_hmat(), parse_obj_ref.get_hmat());

  hmat_info = parse_obj_ref.get_hmat();
  string info_str = "Material : " + hmat_info;
  comp_obj.set_comp_data_position(info_str);
  info_str.clear();

  comp_obj.set_comp_data_information("amass (5d)");
  comp_obj.comp_real_data(parse_obj_com.get_amass(), parse_obj_ref.get_amass());

  comp_obj.set_comp_data_information("temp (5d)");
  comp_obj.comp_list_data(parse_obj_com.get_temp(), parse_obj_ref.get_temp());

  comp_obj.set_comp_data_information("sigz (5d)");
  comp_obj.comp_list_data(parse_obj_com.get_sigz(), parse_obj_ref.get_sigz());

  comp_obj.set_comp_data_information("itype (5d)");
  comp_obj.comp_list_data(parse_obj_com.get_itype(), parse_obj_ref.get_itype());

  comp_obj.set_comp_data_information("n1d (5d)");
  comp_obj.comp_list_data(parse_obj_com.get_n1d(), parse_obj_ref.get_n1d());

  comp_obj.set_comp_data_information("n2d (5d)");
  comp_obj.comp_list_data(parse_obj_com.get_n2d(), parse_obj_ref.get_n2d());

  comp_obj.set_comp_data_information("locs (5d)");
  comp_obj.comp_list_data(parse_obj_com.get_locs(), parse_obj_ref.get_locs());

  vector<MatxsSubmaterialData> submat_obj_com = parse_obj_com.get_submat_obj();
  vector<MatxsSubmaterialData> submat_obj_ref = parse_obj_ref.get_submat_obj();
  if( add_original_data_flg > 0 )
  {
    //Modify submaterial data (Add original data)
    vector<Integer> itype_com = parse_obj_com.get_itype();
    vector<Integer> itype_ref = parse_obj_ref.get_itype();
    int i_max   = static_cast<int>(submat_obj_com.size());
    int pos_ori = 0;
    for(int i=1; i<i_max; i++)
    {
      if( itype_com[i] != itype_com[i-1] )
      {
        pos_ori = i;
        continue;
      }
      submat_obj_com[i] = add_submaterial_data(submat_obj_com[i], submat_obj_com[pos_ori]);
    }

    i_max   = static_cast<int>(submat_obj_ref.size());
    pos_ori = 0;
    for(int i=1; i<i_max; i++)
    {
      if( itype_ref[i] != itype_ref[i-1] )
      {
        pos_ori = i;
        continue;
      }
      submat_obj_ref[i] = add_submaterial_data(submat_obj_ref[i], submat_obj_ref[pos_ori]);
    }
  }

  //Comparison of 6d - 10d data
  comp_submaterial_data(submat_obj_com, submat_obj_ref);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCompare::comp_submaterial_data(MatxsSubmaterialData parse_obj_com,
                                         MatxsSubmaterialData parse_obj_ref)
{
  //Comparison of 6d and 7d data
  int i_com = static_cast<int>(parse_obj_com.get_hvps().size());
  int i_ref = static_cast<int>(parse_obj_ref.get_hvps().size());
  comp_obj.set_comp_data_information("imax of hvps (6d)");
  comp_obj.set_comp_data_position(mat_pos, submat_pos);
  comp_obj.comp_int_data(i_com, i_ref);
  for(int i=0; i<i_com; i++)
  {
    comp_obj.set_comp_data_information("hvps (6d)");
    comp_obj.comp_line_data(parse_obj_com.get_hvps()[i],  parse_obj_ref.get_hvps()[i]);
  }

  Integer               ng_com  = parse_obj_com.get_noutg();
  Integer               ng_ref  = parse_obj_ref.get_noutg();
  vector<Integer>       nfg_com = parse_obj_com.get_nfg();
  vector<Integer>       nfg_ref = parse_obj_ref.get_nfg();
  vector<Integer>       nlg_com = parse_obj_com.get_nlg();
  vector<Integer>       nlg_ref = parse_obj_ref.get_nlg();
  vector<vector<Real> > vps_com = parse_obj_com.get_vps();
  vector<vector<Real> > vps_ref = parse_obj_ref.get_vps();

  i_com = static_cast<int>(nfg_com.size());
  i_ref = static_cast<int>(nfg_ref.size());
  comp_obj.set_comp_data_information("imax of nfg, nlg, vps (6d and 7d)");
  comp_obj.comp_int_data(i_com, i_ref);
  for(int i=0; i<i_com; i++)
  {
    vector<Real> vps_mod_com = modify_vps_data(nfg_com[i], nlg_com[i], vps_com[i], ng_com);
    vector<Real> vps_mod_ref = modify_vps_data(nfg_ref[i], nlg_ref[i], vps_ref[i], ng_ref);
    comp_obj.set_comp_data_information("vps (7d)");
    comp_obj.set_comp_data_position(mat_pos, submat_pos, i+1);
    comp_obj.comp_list_data(vps_mod_com, vps_mod_ref);
  }
  nfg_com.clear();
  nfg_ref.clear();
  nlg_com.clear();
  nlg_ref.clear();
  vps_com.clear();
  vps_ref.clear();

  //Comparison of 8d - 10d data
  comp_matrix_data(parse_obj_com.get_matrix_obj(), parse_obj_ref.get_matrix_obj());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> MatxsCompare::modify_vps_data(Integer nfg, Integer nlg, vector<Real> vps, Integer ng)
{
  vector<Real> vps_mod;
  vps_mod.resize(ng);
  for(int i=0; i<ng; i++)
  {
    vps_mod[i] = 0.0;

    if( i+1 >= nfg && i+1 <= nlg )
    {
      vps_mod[i] = vps[i+1 - nfg];
    }
  }

  return vps_mod;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCompare::comp_matrix_data(MatxsMatrixData parse_obj_com,
                                    MatxsMatrixData parse_obj_ref)
{
  //Comparison of 8d, 9d, and 10d data
  string func_name = "comp_matrix_data";
  comp_obj.set_information_data(class_name, func_name);
  comp_obj.set_comp_data_position(mat_pos, submat_pos, matrix_pos);

  //Comparison of 8d data
  comp_obj.set_comp_data_information("hmtx (8d)");
  comp_obj.comp_line_data(parse_obj_com.get_hmtx(), parse_obj_ref.get_hmtx());

  hmtx_info = parse_obj_ref.get_hmtx();
  string info_str = "Material : " + hmat_info + ", Submaterial : " + hmtx_info;
  comp_obj.set_comp_data_position(info_str);
  info_str.clear();

  comp_obj.set_comp_data_information("lord (8d)");
  comp_obj.comp_int_data(parse_obj_com.get_lord(), parse_obj_ref.get_lord());

  comp_obj.set_comp_data_information("jconst (8d)");
  comp_obj.comp_int_data(parse_obj_com.get_jconst(), parse_obj_ref.get_jconst());

  vector<Integer>                jband_com = parse_obj_com.get_jband();
  vector<Integer>                jband_ref = parse_obj_ref.get_jband();
  vector<Integer>                ijj_com   = parse_obj_com.get_ijj();
  vector<Integer>                ijj_ref   = parse_obj_ref.get_ijj();

  int i_com = static_cast<int>(jband_com.size());
  int i_ref = static_cast<int>(jband_ref.size());
  comp_obj.set_comp_data_information("Data number of jband (8d)");
  comp_obj.comp_int_data(i_com, i_ref);

  i_com = static_cast<int>(ijj_com.size());
  i_ref = static_cast<int>(ijj_ref.size());
  comp_obj.set_comp_data_information("Data number of ijj (8d)");
  comp_obj.comp_int_data(i_com, i_ref);

  //Comparison of 9d data
  vector<vector<vector<Real> > > scat_com  = parse_obj_com.get_scat();
  vector<vector<vector<Real> > > scat_ref  = parse_obj_ref.get_scat();

  i_com = static_cast<int>(scat_com.size());
  i_ref = static_cast<int>(scat_ref.size());
  comp_obj.set_comp_data_information("imax of scat (9d)");
  comp_obj.comp_int_data(i_com, i_ref);
  for(int i=0; i<i_com; i++)
  {
    int j_max = static_cast<int>(scat_com[i].size()); //lord
    for(int j=0; j<j_max; j++)
    {
      //int k_com = static_cast<int>(scat_com[i][j].size());
      //int k_ref = static_cast<int>(scat_ref[i][j].size());
      //comp_obj.set_comp_data_information("kmax of scat (9d)");
      //comp_obj.set_comp_data_position(mat_pos, submat_pos, matrix_pos, i+1, j+1);
      //comp_obj.comp_int_data(k_com, k_ref);

      //if( k_com == 0 || k_ref == 0 )
      //{
      //  continue;
      //}

      vector<Real> scat_mod_com = modify_scat_data(jband_com[i], ijj_com[i], scat_com[i][j], i_com);
      vector<Real> scat_mod_ref = modify_scat_data(jband_ref[i], ijj_ref[i], scat_ref[i][j], i_ref);

      comp_obj.set_comp_data_information("scat (9d)");
      comp_obj.set_comp_data_position(mat_pos, submat_pos, matrix_pos, i+1, j+1);
      comp_obj.comp_list_data(scat_mod_com, scat_mod_ref);
    }
  }
  jband_com.clear();
  jband_ref.clear();
  ijj_com.clear();
  ijj_ref.clear();
  scat_com.clear();
  scat_ref.clear();

  //Comparison of 10d data
  comp_obj.set_comp_data_position(mat_pos, submat_pos, matrix_pos);
  comp_obj.set_comp_data_position(info_str);

  comp_obj.set_comp_data_information("spec (10d)");
  comp_obj.comp_list_data(parse_obj_com.get_spec(), parse_obj_ref.get_spec());
  comp_obj.set_comp_data_information("prod (10d)");
  comp_obj.comp_list_data(parse_obj_com.get_prod(), parse_obj_ref.get_prod());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> MatxsCompare::modify_scat_data(Integer jband, Integer ijj,
                                            vector<Real> scat, Integer ng)
{
  Integer i_max = ijj;
  Integer i_min = i_max - jband + 1;
  return modify_vps_data(i_min, i_max, scat, ng);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

MatxsSubmaterialData MatxsCompare::add_submaterial_data(MatxsSubmaterialData submat_obj_dif,
                                                        MatxsSubmaterialData submat_obj_ori)
{
  vector<string>        hvps_dif  = submat_obj_dif.get_hvps();
  vector<string>        hvps_ori  = submat_obj_ori.get_hvps();
  vector<Integer>       nfg_dif   = submat_obj_dif.get_nfg();
  vector<Integer>       nfg_ori   = submat_obj_ori.get_nfg();
  vector<Integer>       nlg_dif   = submat_obj_dif.get_nfg();
  vector<Integer>       nlg_ori   = submat_obj_ori.get_nfg();
  vector<vector<Real> > vps_dif   = submat_obj_dif.get_vps();
  vector<vector<Real> > vps_ori   = submat_obj_ori.get_vps();
  Integer               noutg_dif = submat_obj_dif.get_noutg();
  Integer               noutg_ori = submat_obj_ori.get_noutg();


  MatxsSubmaterialData  submat_obj_sum = submat_obj_dif;
  vector<string>        hvps_sum = hvps_dif;
  vector<Integer>       nfg_sum, nlg_sum;
  vector<vector<Real> > vps_sum;

  int i_max = static_cast<int>(hvps_dif.size());
  int j_max = static_cast<int>(hvps_ori.size());

  submat_obj_sum.clear();
  nfg_sum.resize(i_max);
  nlg_sum.resize(i_max);
  vps_sum.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    for(int j=0; j<j_max; j++)
    {
      if( hvps_dif[i] != hvps_ori[j] )
      {
        continue;
      }

      vector<Real> vps_vec_dif = modify_vps_data(nfg_dif[i], nlg_dif[i], vps_dif[i], noutg_dif);
      vector<Real> vps_vec_ori = modify_vps_data(nfg_ori[j], nlg_ori[j], vps_ori[j], noutg_ori);

      int ng_no = static_cast<int>(vps_vec_dif.size());
      if( ng_no != static_cast<int>(vps_vec_ori.size()) || ng_no == 0 )
      {
        nfg_sum[i] = nfg_dif[i];
        nlg_sum[i] = nlg_dif[i];
        vps_sum[i] = vps_dif[i];
        continue;
      }

      nfg_sum[i] = 1;
      nlg_sum[i] = ng_no;
      vps_sum[i].resize(ng_no);
      for(int k=0; k<ng_no; k++)
      {
        vps_sum[i][k] = vps_vec_dif[k] + vps_vec_ori[k];
      }
    }
  }

  submat_obj_sum.set_hvps(hvps_sum);
  submat_obj_sum.set_nfg(nfg_sum);
  submat_obj_sum.set_nlg(nlg_sum);
  submat_obj_sum.set_vps(vps_sum);
  hvps_dif.clear();
  hvps_ori.clear();
  hvps_sum.clear();
  nfg_dif.clear();
  nfg_ori.clear();
  nfg_sum.clear();
  nlg_dif.clear();
  nlg_ori.clear();
  nlg_sum.clear();
  vps_dif.clear();
  vps_ori.clear();
  vps_sum.clear();

  vector<MatxsMatrixData> matrix_obj_sum = add_matrix_data(submat_obj_dif.get_matrix_obj(),
                                                           submat_obj_ori.get_matrix_obj());
  submat_obj_sum.set_matrix_obj(matrix_obj_sum);
  vector<MatxsMatrixData>().swap(matrix_obj_sum);

  return submat_obj_sum;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<MatxsMatrixData> MatxsCompare::add_matrix_data(vector<MatxsMatrixData> matrix_obj_dif,
                                                      vector<MatxsMatrixData> matrix_obj_ori)
{
  vector<MatxsMatrixData> matrix_obj_sum = matrix_obj_dif;

  int i_max = static_cast<int>(matrix_obj_dif.size());
  int j_max = static_cast<int>(matrix_obj_ori.size());
  matrix_obj_sum.resize(i_max);

  for(int i=0; i<i_max; i++)
  {
    for(int j=0; j<j_max; j++)
    {
      if( matrix_obj_dif[i].get_hmtx() != matrix_obj_ori[j].get_hmtx() )
      {
        continue;
      }

       //Modify 8d data
       matrix_obj_sum[i].set_hmtx(matrix_obj_dif[i].get_hmtx());
       matrix_obj_sum[i].set_lord(matrix_obj_dif[i].get_lord());
       matrix_obj_sum[i].set_jconst(matrix_obj_dif[i].get_jconst());

       //Modify 9d data
       vector<Integer> jband_dif, jband_ori, jband_sum, ijj_dif, ijj_ori, ijj_sum;
       vector<vector<vector<Real> > > scat_dif, scat_ori, scat_sum;
       jband_dif = matrix_obj_dif[i].get_jband();
       jband_ori = matrix_obj_ori[j].get_jband();
       ijj_dif   = matrix_obj_dif[i].get_ijj();
       ijj_ori   = matrix_obj_ori[j].get_ijj();
       scat_dif  = matrix_obj_dif[i].get_scat();
       scat_ori  = matrix_obj_ori[j].get_scat();

       int k_max = static_cast<int>(scat_dif.size());
       if( k_max != static_cast<int>(scat_ori.size()) )
       {
         matrix_obj_sum[i] = matrix_obj_dif[i];
       }

       scat_sum.resize(k_max);
       jband_sum.resize(k_max);
       ijj_sum.resize(k_max);
       for(int k=0; k<k_max; k++)
       {
         jband_sum[k] = k_max;
         ijj_sum[k]   = k_max;

         int l_max = static_cast<int>(scat_dif[k].size());
         scat_sum[k].resize(l_max);
         for(int l=0; l<l_max; l++)
         {
           vector<Real> scat_vec_dif = modify_scat_data(jband_dif[k], ijj_dif[k], scat_dif[k][l],
                                                        k_max);
           vector<Real> scat_vec_ori = modify_scat_data(jband_ori[k], ijj_ori[k], scat_ori[k][l],
                                                        k_max);

           scat_sum[k][l].resize(k_max);
           for(int m=0; m<k_max; m++)
           {
             scat_sum[k][l][m] = scat_vec_dif[m] + scat_vec_ori[m];
           }
         }
       }
       matrix_obj_sum[i].set_jband(jband_sum);
       matrix_obj_sum[i].set_ijj(ijj_sum);
       matrix_obj_sum[i].set_scat(scat_sum);
       jband_dif.clear();
       jband_ori.clear();
       jband_sum.clear();
       ijj_dif.clear();
       ijj_ori.clear();
       ijj_sum.clear();
       scat_dif.clear();
       scat_ori.clear();
       scat_sum.clear();

       //Modify 10d data
       vector<Real> spec_dif, spec_ori, spec_sum, prod_dif, prod_ori, prod_sum;
       spec_dif  = matrix_obj_dif[i].get_spec();
       spec_ori  = matrix_obj_ori[j].get_spec();
       prod_dif  = matrix_obj_dif[i].get_prod();
       prod_ori  = matrix_obj_ori[j].get_prod();

       k_max = static_cast<int>(spec_dif.size());
       if( k_max != static_cast<int>(spec_ori.size()) )
       {
         spec_sum = spec_dif;
         prod_sum = prod_dif;
       }
       else
       {
         spec_sum.resize(k_max);
         for(int k=0; k<k_max; k++)
         {
           spec_sum[k] = spec_dif[k] + spec_ori[k];
         }

         k_max = static_cast<int>(prod_dif.size());
         prod_sum.resize(k_max);
         for(int k=0; k<k_max; k++)
         {
           prod_sum[k] = prod_dif[k] + prod_ori[k];
         }
       }

       matrix_obj_sum[i].set_spec(spec_sum);
       matrix_obj_sum[i].set_prod(prod_sum);
       spec_dif.clear();
       spec_ori.clear();
       spec_sum.clear();
       prod_dif.clear();
       prod_ori.clear();
       prod_sum.clear();
    }
  }

  return matrix_obj_sum;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MatxsCompare::set_tolerance_val(Real tolerance_val)
{
  comp_obj.set_tolerance_val(tolerance_val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real MatxsCompare::get_tolerance_val()
{
  return comp_obj.get_tolerance_val();
}

////////////////////////////////////////////////////////////////////////////////////////////////////


void MatxsCompare::set_add_original_data_flg(int int_data)
{
  add_original_data_flg = int_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int MatxsCompare::get_add_original_data_flg()
{
  return add_original_data_flg;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

