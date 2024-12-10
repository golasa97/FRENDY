#include "MGXSUtils/KramUtils/KramCompare.hpp"

using namespace frendy;

// ***** KramCompare ***** //
//constructor
KramCompare::KramCompare(void)
{
  class_name = "KramCompare";
  clear();
}

//destructor
KramCompare::~KramCompare(void)
{
  class_name.clear();
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCompare::clear()
{
  kram_obj_com.clear();
  kram_obj_ref.clear();

  comp_obj.clear();
  comp_obj.set_tolerance_val(1.0E-4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCompare::comp_kram_file(string kram_name_com, string kram_name_ref, int mg_no)
{
  KramParser read_obj;

  cout << "Read KRAM file (com) : " + kram_name_com << endl;
  read_obj.set_file_name(kram_name_com, mg_no);
  kram_obj_com = read_obj.get_kram_obj();

  cout << "Read KRAM file (ref) : " + kram_name_ref << endl;
  read_obj.set_file_name(kram_name_ref, mg_no);
  kram_obj_ref = read_obj.get_kram_obj();

  comp_kram_file();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCompare::comp_kram_file(KramCommonData parse_obj_com, KramCommonData parse_obj_ref)
{
  kram_obj_com = parse_obj_com;
  kram_obj_ref = parse_obj_ref;
  parse_obj_com.clear();
  parse_obj_ref.clear();

  comp_kram_file();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCompare::comp_kram_file()
{
  //Comparison of XSN data
  comp_xsn_vec(kram_obj_com.get_xsn_vec(), kram_obj_ref.get_xsn_vec());

  //Comparison of FSP data
  comp_fsp_vec(kram_obj_com.get_fsp_vec(), kram_obj_ref.get_fsp_vec());

  //Comparison of ASC data
  comp_asc_vec(kram_obj_com.get_asc_vec(), kram_obj_ref.get_asc_vec());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCompare::check_mat_list(string func_name, vector<Integer>& list_com, vector<Integer>& list_ref,
                                                   vector<Integer>& list_both)
{
  sort(list_com.begin(), list_com.end());
  sort(list_ref.begin(), list_ref.end());

  vector<Integer> list_com_only, list_ref_only;
  list_both.clear();

  int com_max = static_cast<int>(list_com.size());
  int ref_max = static_cast<int>(list_ref.size());
  list_com_only.resize(com_max);
  for(int i=0; i<com_max; i++)
  {
    list_com_only[i] = -1;
  }

  for(int i=0; i<ref_max; i++)
  {
    int pos_no = -1;
    for(int j=0; j<com_max; j++)
    {
      if( list_ref[i] == list_com[j] )
      {
        pos_no = j;
        break;
      }
    }

    if( pos_no >= 0 )
    {
      list_both.push_back(list_ref[i]);
      list_com_only[pos_no] = 1;
    }
    else
    {
      list_ref_only.push_back(list_ref[i]);
    }
  }

  int list_com_flg = 0;
  for(int i=0; i<com_max; i++)
  {
    if(list_com_only[i] < 0)
    {
      list_com_flg++;
    }
  }

  if( list_com_flg > 0  || static_cast<int>(list_ref_only.size()) > 0 )
  {
    vector<string> err_com;
    err_com.push_back("The following mat numbers are only found in reference or comparison file");
    err_com.push_back("The comparison of these mat numbers are skipped.");
    err_com.push_back("");
    err_com.push_back("Mat numbers only found in comparison file");
    for(int i=0; i<com_max; i++)
    {
      if( list_com_only[i] < 0 )
      {
        ostringstream oss;
        oss << list_com[i];
        string str_data = "    " + oss.str();
        err_com.push_back(str_data);
      }
    }
    err_com.push_back("");

    err_com.push_back("Mat numbers only found in reference file");
    for(int i=0; i<static_cast<int>(list_ref_only.size()); i++)
    {
      ostringstream oss;
      oss << list_ref_only[i];
      string str_data = "    " + oss.str();
      err_com.push_back(str_data);
    }
    err_com.push_back("");

    err_com.push_back("Comparison mat numbers (found in reference and comparison files)");
    for(int i=0; i<static_cast<int>(list_both.size());  i++)
    {
      ostringstream oss;
      oss << list_both[i];
      string str_data = "    " + oss.str();
      err_com.push_back(str_data);
    }
    err_com.push_back("");
    err_com.push_back("Please check the KRAM files.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCompare::comp_xsn_vec(vector<KramXsnData> xsn_vec_com, vector<KramXsnData> xsn_vec_ref)
{
  string func_name = "comp_xsn_vec";

  //Set and check material list
  vector<Integer> mat_list_com, mat_list_ref;
  mat_list_com.clear();
  mat_list_ref.clear();
  for(int i=0; i<static_cast<int>(xsn_vec_com.size()); i++)
  {
    if( xsn_vec_com[i].get_mat_no() != unassigned_mat_no &&
        xsn_vec_com[i].get_ng()     != 0 )
    {
      mat_list_com.push_back(xsn_vec_com[i].get_mat_no());
    }
  }

  for(int i=0; i<static_cast<int>(xsn_vec_ref.size()); i++)
  {
    if( xsn_vec_ref[i].get_mat_no() != unassigned_mat_no &&
        xsn_vec_ref[i].get_ng()     != 0 )
    {
      mat_list_ref.push_back(xsn_vec_ref[i].get_mat_no());
    }
  }

  vector<Integer> mat_list_both;
  check_mat_list(func_name, mat_list_com, mat_list_ref, mat_list_both);
  mat_list_com.clear();
  mat_list_ref.clear();


  //Comparison of XSN data
  int i_max = static_cast<int>(mat_list_both.size());
  for(int i=0; i<i_max; i++)
  {
    KramXsnData xsn_obj_com, xsn_obj_ref;
    xsn_obj_com.clear();
    for(int j=0; j<static_cast<int>(xsn_vec_com.size()); j++)
    {
      if( xsn_vec_com[j].get_mat_no() == mat_list_both[i] )
      {
        xsn_obj_com = xsn_vec_com[j];
        break;
      }
    }

    xsn_obj_ref.clear();
    for(int j=0; j<static_cast<int>(xsn_vec_ref.size()); j++)
    {
      if( xsn_vec_ref[j].get_mat_no() == mat_list_both[i] )
      {
        xsn_obj_ref = xsn_vec_ref[j];
        break;
      }
    }

    comp_xsn_data(xsn_obj_com, xsn_obj_ref);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCompare::comp_xsn_data(KramXsnData xsn_obj_com, KramXsnData xsn_obj_ref)
{
  string func_name = "comp_xsn_vec";
  comp_obj.set_information_data(class_name, func_name);

  comp_obj.set_comp_data_information("ng");
  comp_obj.comp_int_data(xsn_obj_com.get_ng(), xsn_obj_ref.get_ng());

  int ng = xsn_obj_ref.get_ng();
  for(int i=0; i<ng; i++)
  {
    ostringstream oss01, oss02;
    oss01 << i+1;
    oss02 << ng;
    string str_data = "xs_sc (Ein = " + oss01.str() + " / " + oss02.str() + ")";
    comp_obj.set_comp_data_information(str_data);
    comp_obj.comp_list_data(xsn_obj_com.get_xs_sc()[i], xsn_obj_ref.get_xs_sc()[i]);
  }

  comp_obj.set_comp_data_information("xs_prod");
  comp_obj.comp_list_data(xsn_obj_com.get_xs_prod(), xsn_obj_ref.get_xs_prod());
  comp_obj.set_comp_data_information("xs_abs");
  comp_obj.comp_list_data(xsn_obj_com.get_xs_abs(), xsn_obj_ref.get_xs_abs());
  comp_obj.set_comp_data_information("xs_tot");
  comp_obj.comp_list_data(xsn_obj_com.get_xs_tot(), xsn_obj_ref.get_xs_tot());
  comp_obj.set_comp_data_information("xs_fis");
  comp_obj.comp_list_data(xsn_obj_com.get_xs_fis(), xsn_obj_ref.get_xs_fis());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCompare::comp_fsp_vec(vector<KramFspData> fsp_vec_com, vector<KramFspData> fsp_vec_ref)
{
  string func_name = "comp_fsp_vec";

  //Set and check material list
  vector<Integer> mat_list_com, mat_list_ref;
  mat_list_com.clear();
  mat_list_ref.clear();
  for(int i=0; i<static_cast<int>(fsp_vec_com.size()); i++)
  {
    if( fsp_vec_com[i].get_mat_no() != unassigned_mat_no &&
        fsp_vec_com[i].get_ng()     != 0 )
    {
      mat_list_com.push_back(fsp_vec_com[i].get_mat_no());
    }
  }

  for(int i=0; i<static_cast<int>(fsp_vec_ref.size()); i++)
  {
    if( fsp_vec_ref[i].get_mat_no() != unassigned_mat_no &&
        fsp_vec_ref[i].get_ng()     != 0 )
    {
      mat_list_ref.push_back(fsp_vec_ref[i].get_mat_no());
    }
  }

  vector<Integer> mat_list_both;
  check_mat_list(func_name, mat_list_com, mat_list_ref, mat_list_both);
  mat_list_com.clear();
  mat_list_ref.clear();


  //Comparison of FSP data
  int i_max = static_cast<int>(mat_list_both.size());
  for(int i=0; i<i_max; i++)
  {
    KramFspData fsp_obj_com, fsp_obj_ref;
    fsp_obj_com.clear();
    for(int j=0; j<static_cast<int>(fsp_vec_com.size()); j++)
    {
      if( fsp_vec_com[j].get_mat_no() == mat_list_both[i] )
      {
        fsp_obj_com = fsp_vec_com[j];
        break;
      }
    }

    fsp_obj_ref.clear();
    for(int j=0; j<static_cast<int>(fsp_vec_ref.size()); j++)
    {
      if( fsp_vec_ref[j].get_mat_no() == mat_list_both[i] )
      {
        fsp_obj_ref = fsp_vec_ref[j];
        break;
      }
    }

    comp_fsp_data(fsp_obj_com, fsp_obj_ref);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCompare::comp_fsp_data(KramFspData fsp_obj_com, KramFspData fsp_obj_ref)
{
  string func_name = "comp_fsp_vec";
  comp_obj.set_information_data(class_name, func_name);

  comp_obj.set_comp_data_information("ng");
  comp_obj.comp_int_data(fsp_obj_com.get_ng(), fsp_obj_ref.get_ng());

  comp_obj.set_comp_data_information("fsp");
  comp_obj.comp_list_data(fsp_obj_com.get_fsp(), fsp_obj_ref.get_fsp());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCompare::comp_asc_vec(vector<KramAscData> asc_vec_com, vector<KramAscData> asc_vec_ref)
{
  string func_name = "comp_asc_vec";

  //Set and check material list
  vector<Integer> mat_list_com, mat_list_ref;
  mat_list_com.clear();
  mat_list_ref.clear();
  for(int i=0; i<static_cast<int>(asc_vec_com.size()); i++)
  {
    if( asc_vec_com[i].get_mat_no() != unassigned_mat_no &&
        asc_vec_com[i].get_ng()     != 0 )
    {
      mat_list_com.push_back(asc_vec_com[i].get_mat_no());
    }
  }

  for(int i=0; i<static_cast<int>(asc_vec_ref.size()); i++)
  {
    if( asc_vec_ref[i].get_mat_no() != unassigned_mat_no &&
        asc_vec_ref[i].get_ng()     != 0 )
    {
      mat_list_ref.push_back(asc_vec_ref[i].get_mat_no());
    }
  }

  vector<Integer> mat_list_both;
  check_mat_list(func_name, mat_list_com, mat_list_ref, mat_list_both);
  mat_list_com.clear();
  mat_list_ref.clear();


  //Comparison of ASC data
  int i_max = static_cast<int>(mat_list_both.size());
  for(int i=0; i<i_max; i++)
  {
    KramAscData asc_obj_com, asc_obj_ref;
    asc_obj_com.clear();
    for(int j=0; j<static_cast<int>(asc_vec_com.size()); j++)
    {
      if( asc_vec_com[j].get_mat_no() == mat_list_both[i] )
      {
        asc_obj_com = asc_vec_com[j];
        break;
      }
    }

    asc_obj_ref.clear();
    for(int j=0; j<static_cast<int>(asc_vec_ref.size()); j++)
    {
      if( asc_vec_ref[j].get_mat_no() == mat_list_both[i] )
      {
        asc_obj_ref = asc_vec_ref[j];
        break;
      }
    }

    comp_asc_data(asc_obj_com, asc_obj_ref);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCompare::comp_asc_data(KramAscData asc_obj_com, KramAscData asc_obj_ref)
{
  string func_name = "comp_asc_vec";
  comp_obj.set_information_data(class_name, func_name);

  comp_obj.set_comp_data_information("ng");
  comp_obj.comp_int_data(asc_obj_com.get_ng(), asc_obj_ref.get_ng());
  comp_obj.set_comp_data_information("pl_no");
  comp_obj.comp_int_data(asc_obj_com.get_pl_no(), asc_obj_ref.get_pl_no());

  int ng    = asc_obj_ref.get_ng();
  int pl_no = asc_obj_ref.get_pl_no();
  for(int i=0; i<pl_no; i++)
  {
    for(int j=0; j<ng; j++)
    {
      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << pl_no;
      oss03 << j+1;
      oss04 << ng;
      string str_data = "asc (Pl = " + oss01.str() + " / " + oss02.str()
                        + ", Ein = " + oss03.str() + " / " + oss04.str() + ")";
      comp_obj.set_comp_data_information(str_data);
      comp_obj.comp_list_data(asc_obj_com.get_asc()[i][j], asc_obj_ref.get_asc()[i][j]);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void KramCompare::set_tolerance_val(Real tolerance_val)
{
  comp_obj.set_tolerance_val(tolerance_val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real KramCompare::get_tolerance_val()
{
  return comp_obj.get_tolerance_val();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

