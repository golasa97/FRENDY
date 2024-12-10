#include "NuclearDataModifier/GendfModifier.hpp"

using namespace frendy;

//constructor
GendfModifier::GendfModifier(void)
{
}

//destructor
GendfModifier::~GendfModifier(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void  GendfModifier::check_MF_number(Integer mf_no)
{
  if( mf_no == 1 || mf_no == 3 || mf_no == 5 || mf_no == 6 || mf_no == 13 || mf_no == 16 )
  {
  }
  else
  {
    string class_name = "GendfModifier";
    string func_name  = "check_MF_number(Integer mf_no)";

    ostringstream oss01;
    oss01 << mf_no;

    string str_data01 = "MF number : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This MF number cannot be treated in this program.");
    err_com.push_back("The available MF number is MF=1/MT=451, MF=3, MF=5, and MF=6.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void  GendfModifier::check_MF_MT_number(Integer mf_no, Integer mt_no)
{
  check_MF_number(mf_no);

  int mf_mt_flg = 0;
  if( mt_no <= 0 || mt_no >= 1000 )
  {
    mf_mt_flg = 1;
  }

  if( mf_no == 1 )
  {
    if( mt_no != 451 )
    {
      mf_mt_flg = 1;
    }
  }

  if( mf_mt_flg > 0 )
  {
    string class_name = "GendfModifier";
    string func_name  = "check_MF_MT_number(Integer mf_no, Integer mt_no)";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;

    string str_data01 = "MF number : " + oss01.str();
    string str_data02 = "MT number : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This MF number cannot be treated in this program.");
    err_com.push_back("The available MF number is MF=1/MT=451, MF=3, MF=5, and MF=6.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfModifier::get_ZA_AWR_value(GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add)
{
  mat_ori  = gendf_obj_ori.get_mf01_mt451_data().get_mat_no();
  za_ori   = gendf_obj_ori.get_mf01_mt451_data().get_ZA();
  awr_ori  = gendf_obj_ori.get_mf01_mt451_data().get_AWR();
  temp_ori = gendf_obj_ori.get_mf01_mt451_data().get_TEMP();

  Integer mat_add  = gendf_obj_add.get_mf01_mt451_data().get_mat_no();
  Real    za_add   = gendf_obj_add.get_mf01_mt451_data().get_ZA();
  Real    awr_add  = gendf_obj_add.get_mf01_mt451_data().get_AWR();
  Real    temp_add = gendf_obj_add.get_mf01_mt451_data().get_TEMP();

  if( mat_add != mat_ori )
  {
    string class_name = "GendfModifier";
    string func_name  = "get_ZA_AWR_value(GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add)";

    ostringstream oss01, oss02;
    oss01 << mat_ori;
    oss02 << mat_add;
    string str_data01 = "MAT number (ori) : " + oss01.str();
    string str_data02 = "MAT number (mod) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("MAT number of modified nuclear data file is different to that of original one.");
    err_com.push_back("Nucleus of each nuclear data file may not be different.");
    err_com.push_back("Please check your input file or nuclear data files");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( fabs(za_add - za_ori) > za_ori * 1.0E-3 )
  {
    string class_name = "GendfModifier";
    string func_name  = "get_ZA_AWR_value(GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add)";

    ostringstream oss01, oss02;
    oss01 << za_ori;
    oss02 << za_add;
    string str_data01 = "ZA value (ori) : " + oss01.str();
    string str_data02 = "ZA value (mod) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("ZA value of modified nuclear data file is different to that of original one.");
    err_com.push_back("Nucleus of each nuclear data file may not be different.");
    err_com.push_back("Please check your input file or nuclear data files");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( fabs(awr_add - awr_ori) > awr_ori * 1.0E-3 )
  {
    string class_name = "GendfModifier";
    string func_name  = "get_ZA_AWR_value(GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add)";

    ostringstream oss01, oss02;
    oss01 << awr_ori;
    oss02 << awr_add;
    string str_data01 = "AWR value (ori) : " + oss01.str();
    string str_data02 = "AWR value (mod) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("AWR value of modified nuclear data file is different to that of original one.");
    err_com.push_back("Nucleus of each nuclear data file may not be different.");
    err_com.push_back("Please check your input file or nuclear data files");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }


  if( fabs(temp_add - temp_ori) > temp_ori * 1.0E-3 + 1.0E-5 )
  {
    string class_name = "GendfModifier";
    string func_name  = "get_ZA_AWR_value(GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add)";

    ostringstream oss01, oss02;
    oss01 << temp_ori;
    oss02 << temp_add;
    string str_data01 = "TEMP value (ori) : " + oss01.str();
    string str_data02 = "TEMP value (mod) : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("TEMP value of modified nuclear data file is different to that of original one.");
    err_com.push_back("Nucleus of each nuclear data file may not be different.");
    err_com.push_back("Please check your input file or nuclear data files");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfModifier::get_EGN_EGG_value(GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add)
{
  vector<Real> egn_ori  = gendf_obj_ori.get_mf01_mt451_data().get_EGN();
  vector<Real> egg_ori  = gendf_obj_ori.get_mf01_mt451_data().get_EGG();
  vector<Real> sigz_ori = gendf_obj_ori.get_mf01_mt451_data().get_SIGZ();

  vector<Real> egn_add  = gendf_obj_add.get_mf01_mt451_data().get_EGN();
  vector<Real> egg_add  = gendf_obj_add.get_mf01_mt451_data().get_EGG();
  vector<Real> sigz_add = gendf_obj_add.get_mf01_mt451_data().get_SIGZ();

  if( static_cast<int>(egn_ori.size())  != static_cast<int>(egn_add.size())  ||
      static_cast<int>(egg_ori.size())  != static_cast<int>(egg_add.size())  ||
      static_cast<int>(sigz_ori.size()) != static_cast<int>(sigz_add.size()) )
  {
    string class_name = "GendfModifier";
    string func_name  = "get_EGN_EGG_value(GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << static_cast<int>(egn_ori.size());
    oss02 << static_cast<int>(egn_add.size());
    oss03 << static_cast<int>(egg_ori.size());
    oss04 << static_cast<int>(egg_add.size());
    oss05 << static_cast<int>(sigz_ori.size());
    oss06 << static_cast<int>(sigz_add.size());
    string str_data01 = "Number of EGN data (ori)  : " + oss01.str();
    string str_data02 = "Number of EGN data (mod)  : " + oss02.str();
    string str_data03 = "Number of EGG data (ori)  : " + oss03.str();
    string str_data04 = "Number of EGG data (mod)  : " + oss04.str();
    string str_data05 = "Number of SIGZ data (ori) : " + oss05.str();
    string str_data06 = "Number of SIGZ data (mod) : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Number of EGN, EGG, and SIGZ data of modified nuclear data file are different to those of original one.");
    err_com.push_back("Nucleus of each nuclear data file may not be different.");
    err_com.push_back("Please check your input file or nuclear data files");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = static_cast<int>(egn_ori.size());
  for(int i=0; i<i_max; i++)
  {
    if( fabs(egn_add[i] - egn_ori[i]) > egn_ori[i] * 1.0E-3 )
    {
      string class_name = "GendfModifier";
      string func_name  = "get_EGN_EGG_value(GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add)";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << egn_ori[i];
      oss04 << egn_add[i];
      string str_data01 = "Position        : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "EGN value (ori) : " + oss03.str();
      string str_data03 = "EGN value (mod) : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("EGN value of modified nuclear data file is different to that of original one.");
      err_com.push_back("Nucleus of each nuclear data file may not be different.");
      err_com.push_back("Please check your input file or nuclear data files");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  i_max = static_cast<int>(egg_ori.size());
  for(int i=0; i<i_max; i++)
  {
    if( fabs(egg_add[i] - egg_ori[i]) > egg_ori[i] * 1.0E-3 )
    {
      string class_name = "GendfModifier";
      string func_name  = "get_EGN_EGG_value(GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add)";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << egg_ori[i];
      oss04 << egg_add[i];
      string str_data01 = "Position        : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "EGG value (ori) : " + oss03.str();
      string str_data03 = "EGG value (mod) : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("EGG value of modified nuclear data file is different to that of original one.");
      err_com.push_back("Nucleus of each nuclear data file may not be different.");
      err_com.push_back("Please check your input file or nuclear data files");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  i_max = static_cast<int>(sigz_ori.size());
  for(int i=0; i<i_max; i++)
  {
    if( fabs(sigz_add[i] - sigz_ori[i]) > sigz_ori[i] * 1.0E-3 )
    {
      string class_name = "GendfModifier";
      string func_name  = "get_EGN_EGG_value(GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add)";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << sigz_ori[i];
      oss04 << sigz_add[i];
      string str_data01 = "Position         : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "SIGZ value (ori) : " + oss03.str();
      string str_data03 = "SIGZ value (mod) : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("SIGZ value of modified nuclear data file is different to that of original one.");
      err_com.push_back("Nucleus of each nuclear data file may not be different.");
      err_com.push_back("Please check your input file or nuclear data files");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfModifier::remove_specified_MF_data
                      (GendfParser& gendf_obj, Integer mf_no)
{
  check_MF_number(mf_no);

  int remove_flg = 0;

  if( mf_no == 1 )
  {
    remove_specified_MF_MT_data_without_error_message(gendf_obj, 1, 451, remove_flg);
  }
  else if( mf_no == 3 )
  {
    vector<GMF03Parser> mf03_data;
    vector<GMF03Parser>().swap(mf03_data);

    gendf_obj.set_mf03_data(mf03_data);
  }
  else if( mf_no == 5 )
  {
    vector<GMF05Parser> mf05_data;
    vector<GMF05Parser>().swap(mf05_data);

    gendf_obj.set_mf05_data(mf05_data);
  }
  else if( mf_no == 6 )
  {
    vector<GMF06Parser> mf06_data;
    vector<GMF06Parser>().swap(mf06_data);

    gendf_obj.set_mf06_data(mf06_data);
  }
  else if( mf_no == 13 )
  {
    vector<GMF13Parser> mf13_data;
    vector<GMF13Parser>().swap(mf13_data);

    gendf_obj.set_mf13_data(mf13_data);
  }
  else if( mf_no == 16 )
  {
    vector<GMF16Parser> mf16_data;
    vector<GMF16Parser>().swap(mf16_data);

    gendf_obj.set_mf16_data(mf16_data);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfModifier::merge_specified_MF_data
                      (GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add, Integer mf_no,
                       int& ori_flg, int& mod_flg)
{
  check_MF_number(mf_no);

  get_ZA_AWR_value(gendf_obj_ori, gendf_obj_add);
  get_EGN_EGG_value(gendf_obj_ori, gendf_obj_add);

  int no_data_flg = 0;
      ori_flg     = 0;
      mod_flg     = 0;
  if( mf_no == 1 )
  {
    merge_specified_MF_MT_data_without_error_message
      (gendf_obj_ori, gendf_obj_add, 1, 451, ori_flg, mod_flg, no_data_flg);
  }
  else if( mf_no == 3 )
  {
    vector<GMF03Parser> mf03_data = gendf_obj_add.get_mf03_data();

    ori_flg = static_cast<int>(gendf_obj_ori.get_mf03_data().size());
    mod_flg = static_cast<int>(mf03_data.size());

    for(int i=0; i<static_cast<int>(mf03_data.size()); i++)
    {
      mf03_data[i].set_mat_no(mat_ori);
      mf03_data[i].set_ZA(za_ori);
      mf03_data[i].set_AWR(awr_ori);
      mf03_data[i].set_TEMP(temp_ori);
    }
    gendf_obj_ori.set_mf03_data(mf03_data);

    vector<GMF03Parser>().swap(mf03_data);
  }
  else if( mf_no == 5 )
  {
    vector<GMF05Parser> mf05_data = gendf_obj_add.get_mf05_data();

    ori_flg = static_cast<int>(gendf_obj_ori.get_mf05_data().size());
    mod_flg = static_cast<int>(mf05_data.size());

    for(int i=0; i<static_cast<int>(mf05_data.size()); i++)
    {
      mf05_data[i].set_mat_no(mat_ori);
      mf05_data[i].set_ZA(za_ori);
      mf05_data[i].set_AWR(awr_ori);
      mf05_data[i].set_TEMP(temp_ori);
    }
    gendf_obj_ori.set_mf05_data(mf05_data);

    vector<GMF05Parser>().swap(mf05_data);
  }
  else if( mf_no == 6 )
  {
    vector<GMF06Parser> mf06_data = gendf_obj_add.get_mf06_data();

    ori_flg = static_cast<int>(gendf_obj_ori.get_mf06_data().size());
    mod_flg = static_cast<int>(mf06_data.size());

    for(int i=0; i<static_cast<int>(mf06_data.size()); i++)
    {
      mf06_data[i].set_mat_no(mat_ori);
      mf06_data[i].set_ZA(za_ori);
      mf06_data[i].set_AWR(awr_ori);
      mf06_data[i].set_TEMP(temp_ori);
    }
    gendf_obj_ori.set_mf06_data(mf06_data);

    vector<GMF06Parser>().swap(mf06_data);
  }
  else if( mf_no == 13 )
  {
    vector<GMF13Parser> mf13_data = gendf_obj_add.get_mf13_data();

    ori_flg = static_cast<int>(gendf_obj_ori.get_mf13_data().size());
    mod_flg = static_cast<int>(mf13_data.size());

    for(int i=0; i<static_cast<int>(mf13_data.size()); i++)
    {
      mf13_data[i].set_mat_no(mat_ori);
      mf13_data[i].set_ZA(za_ori);
      mf13_data[i].set_AWR(awr_ori);
      mf13_data[i].set_TEMP(temp_ori);
    }
    gendf_obj_ori.set_mf13_data(mf13_data);

    vector<GMF13Parser>().swap(mf13_data);
  }
  else if( mf_no == 16 )
  {
    vector<GMF16Parser> mf16_data = gendf_obj_add.get_mf16_data();

    ori_flg = static_cast<int>(gendf_obj_ori.get_mf16_data().size());
    mod_flg = static_cast<int>(mf16_data.size());

    for(int i=0; i<static_cast<int>(mf16_data.size()); i++)
    {
      mf16_data[i].set_mat_no(mat_ori);
      mf16_data[i].set_ZA(za_ori);
      mf16_data[i].set_AWR(awr_ori);
      mf16_data[i].set_TEMP(temp_ori);
    }
    gendf_obj_ori.set_mf16_data(mf16_data);

    vector<GMF16Parser>().swap(mf16_data);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfModifier::change_specified_MF_data
                      (GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add, Integer mf_no)
{
  int ori_flg = 0;
  int mod_flg = 0;
  merge_specified_MF_data(gendf_obj_ori, gendf_obj_add, mf_no, ori_flg, mod_flg);

  if( ori_flg != mod_flg )
  {
    string class_name = "GendfModifier";
    string func_name  = "change_specified_MF_data";

    ostringstream oss01, oss02, oss03;
    oss01 << mf_no;
    oss02 << ori_flg;
    oss03 << mod_flg;
    string str_data01 = "MF number               : " + oss01.str();
    string str_data02 = "Number of MT data (ori) : " + oss02.str();
    string str_data03 = "Number of MT data (mod) : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The number of MT data of modified nuclear data file is different to that of original one.");
    err_com.push_back("Nucleus of each nuclear data file may not be different.");
    err_com.push_back("Please check your input file or nuclear data files");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfModifier::add_specified_MF_data
                      (GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add, Integer mf_no)
{
  int ori_flg = 0;
  int mod_flg = 0;
  merge_specified_MF_data(gendf_obj_ori, gendf_obj_add, mf_no, ori_flg, mod_flg);

  if( ori_flg > 0 )
  {
    string class_name = "GendfModifier";
    string func_name  = "change_specified_MF_data";

    ostringstream oss01, oss02, oss03;
    oss01 << mf_no;
    oss02 << ori_flg;
    oss03 << mod_flg;
    string str_data01 = "MF number               : " + oss01.str();
    string str_data02 = "Number of MT data (ori) : " + oss02.str();
    string str_data03 = "Number of MT data (mod) : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("The original nuclear data file has this MF number data.");
    err_com.push_back("This MF number data is overwritten by the modified nuclear data file.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfModifier::remove_specified_MF_MT_data_without_error_message
                      (GendfParser& gendf_obj, Integer mf_no, Integer mt_no, int& remove_flg)
{
  check_MF_MT_number(mf_no, mt_no);

  remove_flg = 0;;

  if( mf_no == 1 )
  {
    if( mt_no == 451 )
    {
      //skip remove flg
    }
  }
  else if( mf_no == 3 )
  {
    remove_flg = 1;

    vector<GMF03Parser> mf03_data;
    vector<GMF03Parser>().swap(mf03_data);

    vector<GMF03Parser> mf03_data_ori = gendf_obj.get_mf03_data();

    for(int i=0; i<static_cast<int>(mf03_data_ori.size()); i++)
    {
      if( mt_no != mf03_data_ori[i].get_mt_no() )
      {
        mf03_data.push_back(mf03_data_ori[i]);
      }
      else //if( mt_no == mf03_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    gendf_obj.set_mf03_data(mf03_data);
    vector<GMF03Parser>().swap(mf03_data);
  }
  else if( mf_no == 5 )
  {
    remove_flg = 1;

    vector<GMF05Parser> mf05_data;
    vector<GMF05Parser>().swap(mf05_data);

    vector<GMF05Parser> mf05_data_ori = gendf_obj.get_mf05_data();

    for(int i=0; i<static_cast<int>(mf05_data_ori.size()); i++)
    {
      if( mt_no != mf05_data_ori[i].get_mt_no() )
      {
        mf05_data.push_back(mf05_data_ori[i]);
      }
      else //if( mt_no == mf05_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    gendf_obj.set_mf05_data(mf05_data);
    vector<GMF05Parser>().swap(mf05_data);
  }
  else if( mf_no == 6 )
  {
    remove_flg = 1;

    vector<GMF06Parser> mf06_data;
    vector<GMF06Parser>().swap(mf06_data);

    vector<GMF06Parser> mf06_data_ori = gendf_obj.get_mf06_data();

    for(int i=0; i<static_cast<int>(mf06_data_ori.size()); i++)
    {
      if( mt_no != mf06_data_ori[i].get_mt_no() )
      {
        mf06_data.push_back(mf06_data_ori[i]);
      }
      else //if( mt_no == mf06_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    gendf_obj.set_mf06_data(mf06_data);
    vector<GMF06Parser>().swap(mf06_data);
  }
  else if( mf_no == 13 )
  {
    remove_flg = 1;

    vector<GMF13Parser> mf13_data;
    vector<GMF13Parser>().swap(mf13_data);

    vector<GMF13Parser> mf13_data_ori = gendf_obj.get_mf13_data();

    for(int i=0; i<static_cast<int>(mf13_data_ori.size()); i++)
    {
      if( mt_no != mf13_data_ori[i].get_mt_no() )
      {
        mf13_data.push_back(mf13_data_ori[i]);
      }
      else //if( mt_no == mf13_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    gendf_obj.set_mf13_data(mf13_data);
    vector<GMF13Parser>().swap(mf13_data);
  }
  else if( mf_no == 16 )
  {
    remove_flg = 1;

    vector<GMF16Parser> mf16_data;
    vector<GMF16Parser>().swap(mf16_data);

    vector<GMF16Parser> mf16_data_ori = gendf_obj.get_mf16_data();

    for(int i=0; i<static_cast<int>(mf16_data_ori.size()); i++)
    {
      if( mt_no != mf16_data_ori[i].get_mt_no() )
      {
        mf16_data.push_back(mf16_data_ori[i]);
      }
      else //if( mt_no == mf16_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    gendf_obj.set_mf16_data(mf16_data);
    vector<GMF16Parser>().swap(mf16_data);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfModifier::remove_specified_MF_MT_data
                      (GendfParser& gendf_obj, Integer mf_no, Integer mt_no)
{
  int remove_flg = 0;
  remove_specified_MF_MT_data_without_error_message(gendf_obj, mf_no, mt_no, remove_flg);

  if( remove_flg == 1 )
  {
    string class_name = "GendfModifier";
    string func_name  = "remove_specified_MF_MT_data";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "MF number : " + oss01.str();
    string str_data02 = "MT number : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This MF/MT number han not found in the nuclear data file.");
    err_com.push_back("Please check your input file or nuclear data files");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfModifier::merge_specified_MF_MT_data_without_error_message
                      (GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add, Integer mf_no, Integer mt_no,
                       int& ori_flg, int& mod_flg, int& no_data_flg)
{
  check_MF_MT_number(mf_no, mt_no);

  get_ZA_AWR_value(gendf_obj_ori, gendf_obj_add);
  get_EGN_EGG_value(gendf_obj_ori, gendf_obj_add);

  no_data_flg = 0;

  if( mf_no == 1 )
  {
    if( mt_no == 451 )
    {
      GMF01MT451Parser mf01_mt451_data = gendf_obj_add.get_mf01_mt451_data();

      mf01_mt451_data.set_mat_no(mat_ori);
      mf01_mt451_data.set_ZA(za_ori);
      mf01_mt451_data.set_AWR(awr_ori);
      mf01_mt451_data.set_TEMP(temp_ori);

      gendf_obj_ori.set_mf01_mt451_data(mf01_mt451_data);

      mf01_mt451_data.clear();
    }
  }
  else if( mf_no == 3 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<GMF03Parser> mf03_data_ori = gendf_obj_ori.get_mf03_data();
    vector<GMF03Parser> mf03_data_add = gendf_obj_add.get_mf03_data();
    for(int i=0; i<static_cast<int>(mf03_data_ori.size()); i++)
    {
      if( mf03_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf03_data_add.size()); i++)
    {
      if( mf03_data_add[i].get_mt_no() == mt_no )
      {
        mod_flg = i;
        break;
      }
    }

    if( mod_flg < 0 )
    {
      no_data_flg = 1;
    }
    else
    {
      int add_flg = 0;
      vector<GMF03Parser> mf03_data;
      for(int i=0; i<static_cast<int>(mf03_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf03_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf03_data_add[mod_flg].set_mat_no(mat_ori);
          mf03_data_add[mod_flg].set_ZA(za_ori);
          mf03_data_add[mod_flg].set_AWR(awr_ori);
          mf03_data_add[mod_flg].set_TEMP(temp_ori);
          mf03_data.push_back(mf03_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf03_data.push_back(mf03_data_ori[i]);
          }
        }
        else
        {
          mf03_data.push_back(mf03_data_ori[i]);
        }
      }

      gendf_obj_ori.set_mf03_data(mf03_data);
      vector<GMF03Parser>().swap(mf03_data);
    }

    vector<GMF03Parser>().swap(mf03_data_ori);
    vector<GMF03Parser>().swap(mf03_data_add);
  }
  else if( mf_no == 5 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<GMF05Parser> mf05_data_ori = gendf_obj_ori.get_mf05_data();
    vector<GMF05Parser> mf05_data_add = gendf_obj_add.get_mf05_data();
    for(int i=0; i<static_cast<int>(mf05_data_ori.size()); i++)
    {
      if( mf05_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf05_data_add.size()); i++)
    {
      if( mf05_data_add[i].get_mt_no() == mt_no )
      {
        mod_flg = i;
        break;
      }
    }

    if( mod_flg < 0 )
    {
      no_data_flg = 1;
    }
    else
    {
      int add_flg = 0;
      vector<GMF05Parser> mf05_data;
      for(int i=0; i<static_cast<int>(mf05_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf05_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf05_data_add[mod_flg].set_mat_no(mat_ori);
          mf05_data_add[mod_flg].set_ZA(za_ori);
          mf05_data_add[mod_flg].set_AWR(awr_ori);
          mf05_data_add[mod_flg].set_TEMP(temp_ori);
          mf05_data.push_back(mf05_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf05_data.push_back(mf05_data_ori[i]);
          }
        }
        else
        {
          mf05_data.push_back(mf05_data_ori[i]);
        }
      }

      gendf_obj_ori.set_mf05_data(mf05_data);
      vector<GMF05Parser>().swap(mf05_data);
    }

    vector<GMF05Parser>().swap(mf05_data_ori);
    vector<GMF05Parser>().swap(mf05_data_add);
  }
  else if( mf_no == 6 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<GMF06Parser> mf06_data_ori = gendf_obj_ori.get_mf06_data();
    vector<GMF06Parser> mf06_data_add = gendf_obj_add.get_mf06_data();
    for(int i=0; i<static_cast<int>(mf06_data_ori.size()); i++)
    {
      if( mf06_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf06_data_add.size()); i++)
    {
      if( mf06_data_add[i].get_mt_no() == mt_no )
      {
        mod_flg = i;
        break;
      }
    }

    if( mod_flg < 0 )
    {
      no_data_flg = 1;
    }
    else
    {
      int add_flg = 0;
      vector<GMF06Parser> mf06_data;
      for(int i=0; i<static_cast<int>(mf06_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf06_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf06_data_add[mod_flg].set_mat_no(mat_ori);
          mf06_data_add[mod_flg].set_ZA(za_ori);
          mf06_data_add[mod_flg].set_AWR(awr_ori);
          mf06_data_add[mod_flg].set_TEMP(temp_ori);
          mf06_data.push_back(mf06_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf06_data.push_back(mf06_data_ori[i]);
          }
        }
        else
        {
          mf06_data.push_back(mf06_data_ori[i]);
        }
      }

      gendf_obj_ori.set_mf06_data(mf06_data);
      vector<GMF06Parser>().swap(mf06_data);
    }

    vector<GMF06Parser>().swap(mf06_data_ori);
    vector<GMF06Parser>().swap(mf06_data_add);
  }
  else if( mf_no == 13 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<GMF13Parser> mf13_data_ori = gendf_obj_ori.get_mf13_data();
    vector<GMF13Parser> mf13_data_add = gendf_obj_add.get_mf13_data();
    for(int i=0; i<static_cast<int>(mf13_data_ori.size()); i++)
    {
      if( mf13_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf13_data_add.size()); i++)
    {
      if( mf13_data_add[i].get_mt_no() == mt_no )
      {
        mod_flg = i;
        break;
      }
    }

    if( mod_flg < 0 )
    {
      no_data_flg = 1;
    }
    else
    {
      int add_flg = 0;
      vector<GMF13Parser> mf13_data;
      for(int i=0; i<static_cast<int>(mf13_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf13_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf13_data_add[mod_flg].set_mat_no(mat_ori);
          mf13_data_add[mod_flg].set_ZA(za_ori);
          mf13_data_add[mod_flg].set_AWR(awr_ori);
          mf13_data_add[mod_flg].set_TEMP(temp_ori);
          mf13_data.push_back(mf13_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf13_data.push_back(mf13_data_ori[i]);
          }
        }
        else
        {
          mf13_data.push_back(mf13_data_ori[i]);
        }
      }

      gendf_obj_ori.set_mf13_data(mf13_data);
      vector<GMF13Parser>().swap(mf13_data);
    }

    vector<GMF13Parser>().swap(mf13_data_ori);
    vector<GMF13Parser>().swap(mf13_data_add);
  }
  else if( mf_no == 16 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<GMF16Parser> mf16_data_ori = gendf_obj_ori.get_mf16_data();
    vector<GMF16Parser> mf16_data_add = gendf_obj_add.get_mf16_data();
    for(int i=0; i<static_cast<int>(mf16_data_ori.size()); i++)
    {
      if( mf16_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf16_data_add.size()); i++)
    {
      if( mf16_data_add[i].get_mt_no() == mt_no )
      {
        mod_flg = i;
        break;
      }
    }

    if( mod_flg < 0 )
    {
      no_data_flg = 1;
    }
    else
    {
      int add_flg = 0;
      vector<GMF16Parser> mf16_data;
      for(int i=0; i<static_cast<int>(mf16_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf16_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf16_data_add[mod_flg].set_mat_no(mat_ori);
          mf16_data_add[mod_flg].set_ZA(za_ori);
          mf16_data_add[mod_flg].set_AWR(awr_ori);
          mf16_data_add[mod_flg].set_TEMP(temp_ori);
          mf16_data.push_back(mf16_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf16_data.push_back(mf16_data_ori[i]);
          }
        }
        else
        {
          mf16_data.push_back(mf16_data_ori[i]);
        }
      }

      gendf_obj_ori.set_mf16_data(mf16_data);
      vector<GMF16Parser>().swap(mf16_data);
    }

    vector<GMF16Parser>().swap(mf16_data_ori);
    vector<GMF16Parser>().swap(mf16_data_add);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfModifier::merge_specified_MF_MT_data
                      (GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add, Integer mf_no, Integer mt_no,
                       int& ori_flg, int& mod_flg)
{
  int no_data_flg = 0;
  merge_specified_MF_MT_data_without_error_message
    (gendf_obj_ori, gendf_obj_add, mf_no, mt_no, ori_flg, mod_flg, no_data_flg);

  if( no_data_flg == 1 )
  {
    string class_name = "GendfModifier";
    string func_name  = "merge_specified_MF_MT_data";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "MF number : " + oss01.str();
    string str_data02 = "MT number : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This MF/MT number was not found in the modified nuclear data file.");
    err_com.push_back("Please check your input file or nuclear data files");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfModifier::change_specified_MF_MT_data
                      (GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add, Integer mf_no, Integer mt_no)
{
  int ori_flg = -1;
  int mod_flg = -1;
  merge_specified_MF_MT_data(gendf_obj_ori, gendf_obj_add, mf_no, mt_no, ori_flg, mod_flg);

  if( ori_flg < 0 || ori_flg == unassigned_mat_no )
  {
    string class_name = "GendfModifier";
    string func_name  = "change_specified_MF_data";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "MF number : " + oss01.str();
    string str_data02 = "MT number : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Specified MF/MT number is not found in the original nuclear data file.");
    err_com.push_back("This program adds specified MF/MT number from the modified nuclear data file.");
    err_com.push_back("Please check your input file or nuclear data files");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfModifier::add_specified_MF_MT_data
                      (GendfParser& gendf_obj_ori, GendfParser& gendf_obj_add, Integer mf_no, Integer mt_no)
{
  int ori_flg = -1;
  int mod_flg = -1;
  merge_specified_MF_MT_data(gendf_obj_ori, gendf_obj_add, mf_no, mt_no, ori_flg, mod_flg);

  if( ori_flg >= 0 && ori_flg != unassigned_mat_no )
  {
    string class_name = "GendfModifier";
    string func_name  = "add_specified_MF_MT_data";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;
    string str_data01 = "MF number : " + oss01.str();
    string str_data02 = "MT number : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("Specified MF/MT number is  found in the original nuclear data file.");
    err_com.push_back("This program changes specified MF/MT number from the modified nuclear data file.");
    err_com.push_back("Please check your input file or nuclear data files");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

