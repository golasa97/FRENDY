#include "EndfUtils/GendfParser/GendfCompare.hpp"

using namespace frendy;

//constructor
GendfCompare::GendfCompare(void)
{
  class_name = "GendfCompare";
  clear();
}

//destructor
GendfCompare::~GendfCompare(void)
{ 
  class_name.clear();
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::clear()
{
  comp_flg = 0;

  gendf_obj_com.clear();
  gendf_obj_ref.clear();

  comp_obj.clear();
  comp_obj.set_tolerance_val(5.0E-2); //5%
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::comp_gendf_file(string gendf_name_com, string gendf_name_ref)
{
  cout << "Read GENDF file (com) : " + gendf_name_com << endl;
  gendf_obj_com.set_file_name(gendf_name_com);

  cout << "Read GENDF file (ref) : " + gendf_name_ref << endl;
  gendf_obj_ref.set_file_name(gendf_name_ref);

  comp_gendf_file();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::comp_gendf_file(GendfParser parse_obj_com, GendfParser parse_obj_ref)
{
  gendf_obj_com = parse_obj_com;
  gendf_obj_ref = parse_obj_ref;
  parse_obj_com.clear();
  parse_obj_ref.clear();

  comp_gendf_file();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::comp_gendf_file()
{
  //Comparison of MF01MT451 data
  cout << "Comparison of MF01MT451 data" << endl;
  GMF01MT451Parser    mf01_mt451_com = gendf_obj_com.get_mf01_mt451_data();
  GMF01MT451Parser    mf01_mt451_ref = gendf_obj_ref.get_mf01_mt451_data();
  comp_mf01_mt451_data(mf01_mt451_com, mf01_mt451_ref);
  mf01_mt451_com.clear();
  mf01_mt451_ref.clear();

  //Comparison of MF03 data
  cout << "Comparison of MF03 data" << endl;
  vector<GMF03Parser> mf03_com = gendf_obj_com.get_mf03_data();
  vector<GMF03Parser> mf03_ref = gendf_obj_ref.get_mf03_data();
  comp_mf03_data(mf03_com, mf03_ref);
  vector<GMF03Parser>().swap(mf03_com);
  vector<GMF03Parser>().swap(mf03_ref);

  //Comparison of MF05 data
  cout << "Comparison of MF05 data" << endl;
  vector<GMF05Parser> mf05_com = gendf_obj_com.get_mf05_data();
  vector<GMF05Parser> mf05_ref = gendf_obj_ref.get_mf05_data();
  comp_mf05_data(mf05_com, mf05_ref);
  vector<GMF05Parser>().swap(mf05_com);
  vector<GMF05Parser>().swap(mf05_ref);

  //Comparison of MF06 data
  cout << "Comparison of MF06 data" << endl;
  vector<GMF06Parser> mf06_com = gendf_obj_com.get_mf06_data();
  vector<GMF06Parser> mf06_ref = gendf_obj_ref.get_mf06_data();
  comp_mf06_data(mf06_com, mf06_ref);
  vector<GMF06Parser>().swap(mf06_com);
  vector<GMF06Parser>().swap(mf06_ref);

  //Comparison of MF13 data
  cout << "Comparison of MF13 data" << endl;
  vector<GMF13Parser> mf13_com = gendf_obj_com.get_mf13_data();
  vector<GMF13Parser> mf13_ref = gendf_obj_ref.get_mf13_data();
  comp_mf13_data(mf13_com, mf13_ref);
  vector<GMF13Parser>().swap(mf13_com);
  vector<GMF13Parser>().swap(mf13_ref);

  //Comparison of MF16 data
  cout << "Comparison of MF16 data" << endl;
  vector<GMF16Parser> mf16_com = gendf_obj_com.get_mf16_data();
  vector<GMF16Parser> mf16_ref = gendf_obj_ref.get_mf16_data();
  comp_mf16_data(mf16_com, mf16_ref);
  vector<GMF16Parser>().swap(mf16_com);
  vector<GMF16Parser>().swap(mf16_ref);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::comp_mf01_mt451_data(GMF01MT451Parser parse_obj_com,
                                        GMF01MT451Parser parse_obj_ref)
{
  string func_name = "comp_mf01_mt451_data";
  comp_obj.set_information_data(class_name, func_name);

  //MAT number
  comp_obj.set_comp_data_information("MAT number");
  comp_obj.comp_real_data(parse_obj_com.get_mat_no(), parse_obj_ref.get_mat_no());

  //Line No.01
  //ZA, AWR, NSIGZ, NLIB, NTW
  comp_obj.set_comp_data_information("ZA");
  comp_obj.comp_real_data(parse_obj_com.get_ZA(), parse_obj_ref.get_ZA());

  comp_obj.set_comp_data_information("AWR");
  comp_obj.comp_real_data(parse_obj_com.get_AWR(), parse_obj_ref.get_AWR());

  comp_obj.set_comp_data_information("NSIGZ");
  comp_obj.comp_int_data(parse_obj_com.get_NSIGZ(), parse_obj_ref.get_NSIGZ());

  comp_obj.set_comp_data_information("NLIB");
  comp_obj.comp_int_data(parse_obj_com.get_NLIB(), parse_obj_ref.get_NLIB());

  comp_obj.set_comp_data_information("NTW");
  comp_obj.comp_int_data(parse_obj_com.get_NTW(), parse_obj_ref.get_NTW());


  //Line No.02
  //TEMP, NGN, NGG
  comp_obj.set_comp_data_information("TEMP");
  comp_obj.comp_real_data(parse_obj_com.get_TEMP(), parse_obj_ref.get_TEMP());

  comp_obj.set_comp_data_information("NGN");
  comp_obj.comp_int_data(parse_obj_com.get_NGN(), parse_obj_ref.get_NGN());

  comp_obj.set_comp_data_information("NGG");
  comp_obj.comp_int_data(parse_obj_com.get_NGG(), parse_obj_ref.get_NGG());

  comp_obj.set_comp_data_information("TITLE");
  comp_obj.comp_list_data(parse_obj_com.get_TITLE(), parse_obj_ref.get_TITLE());

  comp_obj.set_comp_data_information("EGN");
  comp_obj.comp_list_data(parse_obj_com.get_EGN(), parse_obj_ref.get_EGN());

  comp_obj.set_comp_data_information("EGG");
  comp_obj.comp_list_data(parse_obj_com.get_EGG(), parse_obj_ref.get_EGG());
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::comp_mf03_data(vector<GMF03Parser> parse_obj_com,
                                  vector<GMF03Parser> parse_obj_ref)
{
  int mt_no_com = static_cast<int>(parse_obj_com.size());
  int mt_no_ref = static_cast<int>(parse_obj_ref.size());

  for(int i=0; i<mt_no_ref; i++)
  {
    int mt_pos = -1;
    for(int j=0; j<mt_no_com; j++)
    {
      if( parse_obj_ref[i].get_mt_no() == parse_obj_com[j].get_mt_no() )
      {
        mt_pos = j;
        comp_mf03_data(parse_obj_com[j], parse_obj_ref[i]);
        break;
      }
    }

    if( mt_pos < 0 )
    {
      string class_name = "GendfCompare";
      string func_name  = "comp_mf03_data";

      ostringstream oss01;
      oss01 << parse_obj_ref[i].get_mt_no();
      string str_data01 = "MT : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("This MT number is only found in the reference data and not found in the comparison data");

      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::comp_mf05_data(vector<GMF05Parser> parse_obj_com,
                                  vector<GMF05Parser> parse_obj_ref)
{
  int mt_no_com = static_cast<int>(parse_obj_com.size());
  int mt_no_ref = static_cast<int>(parse_obj_ref.size());

  for(int i=0; i<mt_no_ref; i++)
  {
    int mt_pos = -1;
    for(int j=0; j<mt_no_com; j++)
    {
      if( parse_obj_ref[i].get_mt_no() == parse_obj_com[j].get_mt_no() )
      {
        mt_pos = j;
        comp_mf05_data(parse_obj_com[j], parse_obj_ref[i]);
        break;
      }
    }

    if( mt_pos < 0 )
    {
      string class_name = "GendfCompare";
      string func_name  = "comp_mf05_data";

      ostringstream oss01;
      oss01 << parse_obj_ref[i].get_mt_no();
      string str_data01 = "MT : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("This MT number is only found in the reference data and not found in the comparison data");

      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::comp_mf06_data(vector<GMF06Parser> parse_obj_com,
                                  vector<GMF06Parser> parse_obj_ref)
{
  int mt_no_com = static_cast<int>(parse_obj_com.size());
  int mt_no_ref = static_cast<int>(parse_obj_ref.size());

  for(int i=0; i<mt_no_ref; i++)
  {
    int mt_pos = -1;
    for(int j=0; j<mt_no_com; j++)
    {
      if( parse_obj_ref[i].get_mt_no() == parse_obj_com[j].get_mt_no() )
      {
        mt_pos = j;
        comp_mf06_data(parse_obj_com[j], parse_obj_ref[i]);
        break;
      }
    }

    if( mt_pos < 0 )
    {
      string class_name = "GendfCompare";
      string func_name  = "comp_mf06_data";

      ostringstream oss01;
      oss01 << parse_obj_ref[i].get_mt_no();
      string str_data01 = "MT : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("This MT number is only found in the reference data and not found in the comparison data");

      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////


void GendfCompare::comp_mf13_data(vector<GMF13Parser> parse_obj_com,
                                  vector<GMF13Parser> parse_obj_ref)
{
  int mt_no_com = static_cast<int>(parse_obj_com.size());
  int mt_no_ref = static_cast<int>(parse_obj_ref.size());

  for(int i=0; i<mt_no_ref; i++)
  {
    int mt_pos = -1;
    for(int j=0; j<mt_no_com; j++)
    {
      if( parse_obj_ref[i].get_mt_no() == parse_obj_com[j].get_mt_no() )
      {
        mt_pos = j;
        comp_mf13_data(parse_obj_com[j], parse_obj_ref[i]);
        break;
      }
    }

    if( mt_pos < 0 )
    {
      string class_name = "GendfCompare";
      string func_name  = "comp_mf13_data";

      ostringstream oss01;
      oss01 << parse_obj_ref[i].get_mt_no();
      string str_data01 = "MT : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("This MT number is only found in the reference data and not found in the comparison data");

      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::comp_mf16_data(vector<GMF16Parser> parse_obj_com,
                                  vector<GMF16Parser> parse_obj_ref)
{
  int mt_no_com = static_cast<int>(parse_obj_com.size());
  int mt_no_ref = static_cast<int>(parse_obj_ref.size());

  for(int i=0; i<mt_no_ref; i++)
  {
    int mt_pos = -1;
    for(int j=0; j<mt_no_com; j++)
    {
      if( parse_obj_ref[i].get_mt_no() == parse_obj_com[j].get_mt_no() )
      {
        mt_pos = j;
        comp_mf16_data(parse_obj_com[j], parse_obj_ref[i]);
        break;
      }
    }

    if( mt_pos < 0 )
    {
      string class_name = "GendfCompare";
      string func_name  = "comp_mf16_data";

      ostringstream oss01;
      oss01 << parse_obj_ref[i].get_mt_no();
      string str_data01 = "MT : " + oss01.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("This MT number is only found in the reference data and not found in the comparison data");

      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::comp_mf03_data(GMF03Parser parse_obj_com,  GMF03Parser parse_obj_ref)
{
  string func_name = "comp_mf03_data";
  comp_obj.set_information_data(class_name, func_name);
  comp_obj.set_comp_data_position(parse_obj_com.get_mt_no());

  //MAT and MT number
  comp_obj.set_comp_data_information("MAT number");
  comp_obj.comp_real_data(parse_obj_com.get_mat_no(), parse_obj_ref.get_mat_no());

  comp_obj.set_comp_data_information("MT number");
  comp_obj.comp_real_data(parse_obj_com.get_mt_no(), parse_obj_ref.get_mt_no());

  //Line No.01
  comp_obj.set_comp_data_information("ZA");
  comp_obj.comp_real_data(parse_obj_com.get_ZA(), parse_obj_ref.get_ZA());

  comp_obj.set_comp_data_information("NL");
  comp_obj.comp_int_data(parse_obj_com.get_NL(), parse_obj_ref.get_NL());

  comp_obj.set_comp_data_information("NSIGZ");
  comp_obj.comp_int_data(parse_obj_com.get_NSIGZ(), parse_obj_ref.get_NSIGZ());

  comp_obj.set_comp_data_information("LR");
  comp_obj.comp_int_data(parse_obj_com.get_LR(), parse_obj_ref.get_LR());

  comp_obj.set_comp_data_information("NGN");
  comp_obj.comp_int_data(parse_obj_com.get_NGN(), parse_obj_ref.get_NGN());

  //Line No.02
  comp_obj.set_comp_data_information("TEMP");
  comp_obj.comp_real_data(parse_obj_com.get_TEMP(), parse_obj_ref.get_TEMP());

  comp_obj.set_comp_data_information("NG2");
  comp_obj.comp_list_data(parse_obj_com.get_NG2(), parse_obj_ref.get_NG2());

  comp_obj.set_comp_data_information("IG2LO");
  comp_obj.comp_list_data(parse_obj_com.get_IG2LO(), parse_obj_ref.get_IG2LO());

  vector<int> ng2_ref = parse_obj_ref.get_NG2();
  vector<int> ng2_com = parse_obj_com.get_NG2();
  int i_ref           = static_cast<int>(ng2_ref.size());
  int i_com           = static_cast<int>(ng2_com.size());
  int i_max           = min(i_ref, i_com);
  int init_flux_flg   = 0;
  vector<vector<Real> > flux_coef;
  for(int i=0; i<i_max; i++)
  {
    vector<vector<Real> > flux_com = parse_obj_com.get_FLUX()[i];
    vector<vector<Real> > flux_ref = parse_obj_ref.get_FLUX()[i];

    int j_com = static_cast<int>(flux_com.size());
    int j_ref = static_cast<int>(flux_ref.size());
    comp_obj.set_comp_data_information("j_max of FLUX");
    comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1);
    comp_obj.comp_int_data(j_com, j_ref);

    int j_max = min(j_ref, j_com);
    if( j_com > 0 && j_ref > 0 && init_flux_flg == 0 )
    {
      init_flux_flg = 1;
      flux_coef.resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        int k_com = static_cast<int>(flux_com[j].size());
        int k_ref = static_cast<int>(flux_ref[j].size());
        int k_max = min(k_ref, k_com);
        flux_coef[j].resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          flux_coef[j][k] = 1.0;
          if( fabs(flux_com[j][k]) > min_value )
          {
            flux_coef[j][k] = flux_ref[j][k] / flux_com[j][k];
          }
        }
      }
    }
    else
    {
      for(int j=0; j<j_max; j++)
      {
        int k_com = static_cast<int>(flux_com[j].size());
        int k_ref = static_cast<int>(flux_ref[j].size());
        int k_max = min(k_ref, k_com);
        for(int k=0; k<k_max; k++)
        {
          flux_com[j][k] *= flux_coef[j][k];
        }

        comp_obj.set_comp_data_information("FLUX");
        comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1);
        comp_obj.comp_list_data(flux_com[j], flux_ref[j]);
        comp_obj.clear_comp_data_position();
      }
    }
   
    if( ng2_ref[i] == 1 ) //Comp SIGMA data
    {
      vector<vector<Real> > sig_com = parse_obj_com.get_SIG()[i];
      vector<vector<Real> > sig_ref = parse_obj_ref.get_SIG()[i];

      int j_com = static_cast<int>(sig_com.size());
      int j_ref = static_cast<int>(sig_ref.size());
      comp_obj.set_comp_data_information("j_max of SIG");
      comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1);
      comp_obj.comp_int_data(j_com, j_ref);

      int j_max = min(j_ref, j_com);
      for(int j=0; j<j_max; j++)
      {
        comp_obj.set_comp_data_information("SIG");
        comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1);
        comp_obj.comp_list_data(sig_com[j], sig_ref[j]);
        comp_obj.clear_comp_data_position();
      }
    }
    else //Comp NU data
    {
      vector<vector<vector<Real> > > nu_com = parse_obj_com.get_NU()[i];
      vector<vector<vector<Real> > > nu_ref = parse_obj_ref.get_NU()[i];

      int j_com = static_cast<int>(nu_com.size());
      int j_ref = static_cast<int>(nu_ref.size());
      comp_obj.set_comp_data_information("j_max of NU");
      comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1);
      comp_obj.comp_int_data(j_com, j_ref);

      int j_max = min(j_ref, j_com);
      for(int j=0; j<j_max; j++)
      {
        int k_com = static_cast<int>(nu_com[j].size());
        int k_ref = static_cast<int>(nu_ref[j].size());
        comp_obj.set_comp_data_information("k_max of NU");
        comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1);
        comp_obj.comp_int_data(k_com, k_ref);

        int k_max = min(k_ref, k_com);
        for(int k=0; k<k_max; k++)
        {
          comp_obj.set_comp_data_information("NU");
          comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1, k+1);
          comp_obj.comp_list_data(nu_com[j][k], nu_ref[j][k]);
          comp_obj.clear_comp_data_position();
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::comp_mf05_data(GMF05Parser parse_obj_com, GMF05Parser parse_obj_ref)
{
  string func_name = "comp_mf05_data";
  comp_obj.set_information_data(class_name, func_name);
  comp_obj.set_comp_data_position(parse_obj_com.get_mt_no());

  //MAT and MT number
  comp_obj.set_comp_data_information("MAT number");
  comp_obj.comp_real_data(parse_obj_com.get_mat_no(), parse_obj_ref.get_mat_no());

  comp_obj.set_comp_data_information("MT number");
  comp_obj.comp_real_data(parse_obj_com.get_mt_no(), parse_obj_ref.get_mt_no());

  //Line No.01
  comp_obj.set_comp_data_information("ZA");
  comp_obj.comp_real_data(parse_obj_com.get_ZA(), parse_obj_ref.get_ZA());

  comp_obj.set_comp_data_information("NL");
  comp_obj.comp_int_data(parse_obj_com.get_NL(), parse_obj_ref.get_NL());

  comp_obj.set_comp_data_information("NSIGZ");
  comp_obj.comp_int_data(parse_obj_com.get_NSIGZ(), parse_obj_ref.get_NSIGZ());

  comp_obj.set_comp_data_information("LR");
  comp_obj.comp_int_data(parse_obj_com.get_LR(), parse_obj_ref.get_LR());

  comp_obj.set_comp_data_information("NGN");
  comp_obj.comp_int_data(parse_obj_com.get_NGN(), parse_obj_ref.get_NGN());

  if( comp_flg == 0 )
  {
    return;
  }

  //Line No.02
  comp_obj.set_comp_data_information("TEMP");
  comp_obj.comp_real_data(parse_obj_com.get_TEMP(), parse_obj_ref.get_TEMP());

  comp_obj.set_comp_data_information("NG2");
  comp_obj.comp_list_data(parse_obj_com.get_NG2(), parse_obj_ref.get_NG2());

  comp_obj.set_comp_data_information("IG2LO");
  comp_obj.comp_list_data(parse_obj_com.get_IG2LO(), parse_obj_ref.get_IG2LO());

  vector<vector<vector<Real> > >          lamda_com, lamda_ref;
  vector<vector<vector<vector<Real> > > > chi_com, chi_ref;
  lamda_com = parse_obj_com.get_LAMDA();
  chi_com   = parse_obj_com.get_CHI();
  lamda_ref = parse_obj_ref.get_LAMDA();
  chi_ref   = parse_obj_ref.get_CHI();

  int i_com = static_cast<int>(lamda_com.size());
  int i_ref = static_cast<int>(lamda_ref.size());
  comp_obj.set_comp_data_information("i_max of LAMDA");
  comp_obj.comp_int_data(i_com, i_ref);
  int i_max = min(i_ref, i_com);
  for(int i=0; i<i_max; i++)
  {
    int j_com = static_cast<int>(lamda_com[i].size());
    int j_ref = static_cast<int>(lamda_ref[i].size());
    comp_obj.set_comp_data_information("j_max of LAMDA");
    comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1);
    comp_obj.comp_int_data(j_com, j_ref);

    int j_max = min(j_ref, j_com);
    for(int j=0; j<j_max; j++)
    {
      comp_obj.set_comp_data_information("LAMDA");
      comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1);
      comp_obj.comp_list_data(lamda_com[i][j], lamda_ref[i][j]);
      comp_obj.clear_comp_data_position();
    }
  }

  i_com = static_cast<int>(chi_com.size());
  i_ref = static_cast<int>(chi_ref.size());
  comp_obj.set_comp_data_information("i_max of CHI");
  comp_obj.comp_int_data(i_com, i_ref);
  i_max = min(i_ref, i_com);
  for(int i=0; i<i_max; i++)
  {
    int j_com = static_cast<int>(chi_com[i].size());
    int j_ref = static_cast<int>(chi_ref[i].size());
    comp_obj.set_comp_data_information("j_max of CHI");
    comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1);
    comp_obj.comp_int_data(j_com, j_ref);

    int j_max = min(j_ref, j_com);
    for(int j=0; j<j_max; j++)
    {
      int k_com = static_cast<int>(chi_com[i][j].size());
      int k_ref = static_cast<int>(chi_ref[i][j].size());
      comp_obj.set_comp_data_information("k_max of CHI");
      comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1);
      comp_obj.comp_int_data(k_com, k_ref);

      int k_max = min(k_ref, k_com);
      for(int k=0; k<k_max; k++)
      {
        comp_obj.set_comp_data_information("CHI");
        comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1, k+1);
        comp_obj.comp_list_data(chi_com[i][j][k], chi_ref[i][j][k]);
        comp_obj.clear_comp_data_position();
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::comp_mf06_data(GMF06Parser parse_obj_com, GMF06Parser parse_obj_ref)
{
  string func_name = "comp_mf06_data";
  comp_obj.set_information_data(class_name, func_name);
  comp_obj.set_comp_data_position(parse_obj_com.get_mt_no());

  //MAT and MT number
  comp_obj.set_comp_data_information("MAT number");
  comp_obj.comp_real_data(parse_obj_com.get_mat_no(), parse_obj_ref.get_mat_no());

  comp_obj.set_comp_data_information("MT number");
  comp_obj.comp_real_data(parse_obj_com.get_mt_no(), parse_obj_ref.get_mt_no());

  //Line No.01
  comp_obj.set_comp_data_information("ZA");
  comp_obj.comp_real_data(parse_obj_com.get_ZA(), parse_obj_ref.get_ZA());

  comp_obj.set_comp_data_information("NL");
  comp_obj.comp_int_data(parse_obj_com.get_NL(), parse_obj_ref.get_NL());

  comp_obj.set_comp_data_information("NSIGZ");
  comp_obj.comp_int_data(parse_obj_com.get_NSIGZ(), parse_obj_ref.get_NSIGZ());

  comp_obj.set_comp_data_information("LR");
  comp_obj.comp_int_data(parse_obj_com.get_LR(), parse_obj_ref.get_LR());

  comp_obj.set_comp_data_information("NGN");
  comp_obj.comp_int_data(parse_obj_com.get_NGN(), parse_obj_ref.get_NGN());

  if( comp_flg == 0 )
  {
    return;
  }

  //Line No.02
  comp_obj.set_comp_data_information("TEMP");
  comp_obj.comp_real_data(parse_obj_com.get_TEMP(), parse_obj_ref.get_TEMP());

  comp_obj.set_comp_data_information("NG2");
  comp_obj.comp_list_data(parse_obj_com.get_NG2(), parse_obj_ref.get_NG2());

  comp_obj.set_comp_data_information("IG2LO");
  comp_obj.comp_list_data(parse_obj_com.get_IG2LO(), parse_obj_ref.get_IG2LO());

  vector<vector<vector<Real> > >          flux_com, flux_ref;
  vector<vector<vector<vector<Real> > > > matrix_com, matrix_ref;
  flux_com   = parse_obj_com.get_FLUX();
  matrix_com = parse_obj_com.get_MATRIX();
  flux_ref   = parse_obj_ref.get_FLUX();
  matrix_ref = parse_obj_ref.get_MATRIX();

  int i_com = static_cast<int>(flux_com.size());
  int i_ref = static_cast<int>(flux_ref.size());
  comp_obj.set_comp_data_information("i_max of FLUX");
  comp_obj.comp_int_data(i_com, i_ref);
  int i_max = min(i_ref, i_com);
  for(int i=0; i<i_max; i++)
  {
    int j_com = static_cast<int>(flux_com[i].size());
    int j_ref = static_cast<int>(flux_ref[i].size());
    comp_obj.set_comp_data_information("j_max of FLUX");
    comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1);
    comp_obj.comp_int_data(j_com, j_ref);

    int j_max = min(j_ref, j_com);
    for(int j=0; j<j_max; j++)
    {
      comp_obj.set_comp_data_information("FLUX");
      comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1);
      comp_obj.comp_list_data(flux_com[i][j], flux_ref[i][j]);
      comp_obj.clear_comp_data_position();
    }
  }

  i_com = static_cast<int>(matrix_com.size());
  i_ref = static_cast<int>(matrix_ref.size());
  comp_obj.set_comp_data_information("i_max of MATRIX");
  comp_obj.comp_int_data(i_com, i_ref);
  i_max = min(i_ref, i_com);
  for(int i=0; i<i_max; i++)
  {
    int j_com = static_cast<int>(matrix_com[i].size());
    int j_ref = static_cast<int>(matrix_ref[i].size());
    comp_obj.set_comp_data_information("j_max of MATRIX");
    comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1);
    comp_obj.comp_int_data(j_com, j_ref);

    int j_max = min(j_ref, j_com);
    for(int j=0; j<j_max; j++)
    {
      int k_com = static_cast<int>(matrix_com[i][j].size());
      int k_ref = static_cast<int>(matrix_ref[i][j].size());
      comp_obj.set_comp_data_information("k_max of MATRIX");
      comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1);
      comp_obj.comp_int_data(k_com, k_ref);

      int k_max = min(k_ref, k_com);
      for(int k=0; k<k_max; k++)
      {
        comp_obj.set_comp_data_information("MATRIX");
        comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1, k+1);
        comp_obj.comp_list_data(matrix_com[i][j][k], matrix_ref[i][j][k]);
        comp_obj.clear_comp_data_position();
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::comp_mf13_data(GMF13Parser parse_obj_com,  GMF13Parser parse_obj_ref)
{
  string func_name = "comp_mf13_data";
  comp_obj.set_information_data(class_name, func_name);
  comp_obj.set_comp_data_position(parse_obj_com.get_mt_no());

  //MAT and MT number
  comp_obj.set_comp_data_information("MAT number");
  comp_obj.comp_real_data(parse_obj_com.get_mat_no(), parse_obj_ref.get_mat_no());

  comp_obj.set_comp_data_information("MT number");
  comp_obj.comp_real_data(parse_obj_com.get_mt_no(), parse_obj_ref.get_mt_no());

  //Line No.01
  comp_obj.set_comp_data_information("ZA");
  comp_obj.comp_real_data(parse_obj_com.get_ZA(), parse_obj_ref.get_ZA());

  comp_obj.set_comp_data_information("NL");
  comp_obj.comp_int_data(parse_obj_com.get_NL(), parse_obj_ref.get_NL());

  comp_obj.set_comp_data_information("NSIGZ");
  comp_obj.comp_int_data(parse_obj_com.get_NSIGZ(), parse_obj_ref.get_NSIGZ());

  comp_obj.set_comp_data_information("LR");
  comp_obj.comp_int_data(parse_obj_com.get_LR(), parse_obj_ref.get_LR());

  comp_obj.set_comp_data_information("NGN");
  comp_obj.comp_int_data(parse_obj_com.get_NGN(), parse_obj_ref.get_NGN());

  //Line No.02
  comp_obj.set_comp_data_information("TEMP");
  comp_obj.comp_real_data(parse_obj_com.get_TEMP(), parse_obj_ref.get_TEMP());

  comp_obj.set_comp_data_information("NG2");
  comp_obj.comp_list_data(parse_obj_com.get_NG2(), parse_obj_ref.get_NG2());

  comp_obj.set_comp_data_information("IG2LO");
  comp_obj.comp_list_data(parse_obj_com.get_IG2LO(), parse_obj_ref.get_IG2LO());

  vector<int> ng2_ref = parse_obj_ref.get_NG2();
  vector<int> ng2_com = parse_obj_com.get_NG2();
  int i_ref           = static_cast<int>(ng2_ref.size());
  int i_com           = static_cast<int>(ng2_com.size());
  int i_max           = min(i_ref, i_com);
  int init_flux_flg   = 0;
  vector<vector<Real> > flux_coef;
  for(int i=0; i<i_max; i++)
  {
    vector<vector<Real> > flux_com = parse_obj_com.get_FLUX()[i];
    vector<vector<Real> > flux_ref = parse_obj_ref.get_FLUX()[i];

    int j_com = static_cast<int>(flux_com.size());
    int j_ref = static_cast<int>(flux_ref.size());
    comp_obj.set_comp_data_information("j_max of FLUX");
    comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1);
    comp_obj.comp_int_data(j_com, j_ref);

    int j_max = min(j_ref, j_com);
    if( j_com > 0 && j_ref > 0 && init_flux_flg == 0 )
    {
      init_flux_flg = 1;
      flux_coef.resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        int k_com = static_cast<int>(flux_com[j].size());
        int k_ref = static_cast<int>(flux_ref[j].size());
        int k_max = min(k_ref, k_com);
        flux_coef[j].resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          flux_coef[j][k] = 1.0;
          if( fabs(flux_com[j][k]) > min_value )
          {
            flux_coef[j][k] = flux_ref[j][k] / flux_com[j][k];
          }
        }
      }
    }
    else
    {
      for(int j=0; j<j_max; j++)
      {
        int k_com = static_cast<int>(flux_com[j].size());
        int k_ref = static_cast<int>(flux_ref[j].size());
        int k_max = min(k_ref, k_com);
        for(int k=0; k<k_max; k++)
        {
          flux_com[j][k] *= flux_coef[j][k];
        }

        comp_obj.set_comp_data_information("FLUX");
        comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1);
        comp_obj.comp_list_data(flux_com[j], flux_ref[j]);
        comp_obj.clear_comp_data_position();
      }
    }

    vector<vector<Real> > sig_com = parse_obj_com.get_SIG()[i];
    vector<vector<Real> > sig_ref = parse_obj_ref.get_SIG()[i];

    j_com = static_cast<int>(sig_com.size());
    j_ref = static_cast<int>(sig_ref.size());
    comp_obj.set_comp_data_information("j_max of SIG");
    comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1);
    comp_obj.comp_int_data(j_com, j_ref);

    j_max = min(j_ref, j_com);
    for(int j=0; j<j_max; j++)
    {
      comp_obj.set_comp_data_information("SIG");
      comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1);
      comp_obj.comp_list_data(sig_com[j], sig_ref[j]);
      comp_obj.clear_comp_data_position();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::comp_mf16_data(GMF16Parser parse_obj_com, GMF16Parser parse_obj_ref)
{
  string func_name = "comp_mf16_data";
  comp_obj.set_information_data(class_name, func_name);
  comp_obj.set_comp_data_position(parse_obj_com.get_mt_no());

  //MAT and MT number
  comp_obj.set_comp_data_information("MAT number");
  comp_obj.comp_real_data(parse_obj_com.get_mat_no(), parse_obj_ref.get_mat_no());

  comp_obj.set_comp_data_information("MT number");
  comp_obj.comp_real_data(parse_obj_com.get_mt_no(), parse_obj_ref.get_mt_no());

  //Line No.01
  comp_obj.set_comp_data_information("ZA");
  comp_obj.comp_real_data(parse_obj_com.get_ZA(), parse_obj_ref.get_ZA());

  comp_obj.set_comp_data_information("NL");
  comp_obj.comp_int_data(parse_obj_com.get_NL(), parse_obj_ref.get_NL());

  comp_obj.set_comp_data_information("NSIGZ");
  comp_obj.comp_int_data(parse_obj_com.get_NSIGZ(), parse_obj_ref.get_NSIGZ());

  comp_obj.set_comp_data_information("LR");
  comp_obj.comp_int_data(parse_obj_com.get_LR(), parse_obj_ref.get_LR());

  comp_obj.set_comp_data_information("NGN");
  comp_obj.comp_int_data(parse_obj_com.get_NGN(), parse_obj_ref.get_NGN());

  if( comp_flg == 0 )
  {
    return;
  }

  //Line No.02
  comp_obj.set_comp_data_information("TEMP");
  comp_obj.comp_real_data(parse_obj_com.get_TEMP(), parse_obj_ref.get_TEMP());

  comp_obj.set_comp_data_information("NG2");
  comp_obj.comp_list_data(parse_obj_com.get_NG2(), parse_obj_ref.get_NG2());

  comp_obj.set_comp_data_information("IG2LO");
  comp_obj.comp_list_data(parse_obj_com.get_IG2LO(), parse_obj_ref.get_IG2LO());

  vector<vector<vector<Real> > >          flux_com, flux_ref;
  vector<vector<vector<vector<Real> > > > matrix_com, matrix_ref;
  flux_com   = parse_obj_com.get_FLUX();
  matrix_com = parse_obj_com.get_MATRIX();
  flux_ref   = parse_obj_ref.get_FLUX();
  matrix_ref = parse_obj_ref.get_MATRIX();

  int i_com = static_cast<int>(flux_com.size());
  int i_ref = static_cast<int>(flux_ref.size());
  comp_obj.set_comp_data_information("i_max of FLUX");
  comp_obj.comp_int_data(i_com, i_ref);
  int i_max = min(i_ref, i_com);
  for(int i=0; i<i_max; i++)
  {
    int j_com = static_cast<int>(flux_com[i].size());
    int j_ref = static_cast<int>(flux_ref[i].size());
    comp_obj.set_comp_data_information("j_max of FLUX");
    comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1);
    comp_obj.comp_int_data(j_com, j_ref);

    int j_max = min(j_ref, j_com);
    for(int j=0; j<j_max; j++)
    {
      comp_obj.set_comp_data_information("FLUX");
      comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1);
      comp_obj.comp_list_data(flux_com[i][j], flux_ref[i][j]);
      comp_obj.clear_comp_data_position();
    }
  }

  i_com = static_cast<int>(matrix_com.size());
  i_ref = static_cast<int>(matrix_ref.size());
  comp_obj.set_comp_data_information("i_max of MATRIX");
  comp_obj.comp_int_data(i_com, i_ref);
  i_max = min(i_ref, i_com);
  for(int i=0; i<i_max; i++)
  {
    int j_com = static_cast<int>(matrix_com[i].size());
    int j_ref = static_cast<int>(matrix_ref[i].size());
    comp_obj.set_comp_data_information("j_max of MATRIX");
    comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1);
    comp_obj.comp_int_data(j_com, j_ref);

    int j_max = min(j_ref, j_com);
    for(int j=0; j<j_max; j++)
    {
      int k_com = static_cast<int>(matrix_com[i][j].size());
      int k_ref = static_cast<int>(matrix_ref[i][j].size());
      comp_obj.set_comp_data_information("k_max of MATRIX");
      comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1);
      comp_obj.comp_int_data(k_com, k_ref);

      int k_max = min(k_ref, k_com);
      for(int k=0; k<k_max; k++)
      {
        comp_obj.set_comp_data_information("MATRIX");
        comp_obj.set_comp_data_position(parse_obj_com.get_mt_no(), i+1, j+1, k+1);
        comp_obj.comp_list_data(matrix_com[i][j][k], matrix_ref[i][j][k]);
        comp_obj.clear_comp_data_position();
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::set_tolerance_val(Real tolerance_val)
{
  comp_obj.set_tolerance_val(tolerance_val);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real GendfCompare::get_tolerance_val()
{
  return comp_obj.get_tolerance_val();
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfCompare::set_comp_flg(int int_val)
{
  comp_flg = int_val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int GendfCompare::get_comp_flg()
{
  return comp_flg;
}

