#include "NuclearDataModifier/Endf6Modifier.hpp"

using namespace frendy;

//constructor
Endf6Modifier::Endf6Modifier(void)
{
}

//destructor
Endf6Modifier::~Endf6Modifier(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void  Endf6Modifier::check_MF_number(Integer mf_no)
{
  if( mf_no == 11 || (mf_no >= 16 && mf_no <= 22) || mf_no == 24 || mf_no == 25 || mf_no == 29 ||
     (mf_no >= 36 && mf_no <= 39) || mf_no > 40 || mf_no < 1 )
  {
    string class_name = "Endf6Modifier";
    string func_name  = "check_MF_number(Integer mf_no)";

    ostringstream oss01;
    oss01 << mf_no;

    string str_data01 = "MF number : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This MF number is not defined in the ENDF-6 format.");
    err_com.push_back("Please check your input file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void  Endf6Modifier::check_MF_MT_number(Integer mf_no, Integer mt_no)
{
  check_MF_number(mf_no);

  int mf_mt_flg = 0;
  if( mt_no <= 0 || mt_no >= 1000 )
  {
    mf_mt_flg = 1;
  }

  if( mf_no == 1 )
  {
    if( mt_no != 451 && mt_no != 452 && mt_no != 455 &&
        mt_no != 456 && mt_no != 458 && mt_no != 460 )
    {
      mf_mt_flg = 1;
    }
  }
  else if( mf_no == 2 )
  {
    if( mt_no != 151 && mt_no != 152 && mt_no != 153 )
    {
      mf_mt_flg = 1;
    }
  }
  else if( mf_no == 7 )
  {
    if( mt_no != 2 && mt_no != 4 )
    {
      mf_mt_flg = 1;
    }
  }
  else if( mf_no == 30 )
  {
    if( mt_no != 1 && mt_no != 2 )
    {
      mf_mt_flg = 1;
    }
  }
  else if( mf_no == 32 )
  {
    if( mt_no != 151 )
    {
      mf_mt_flg = 1;
    }
  }

  if( mf_mt_flg > 0 )
  {
    string class_name = "Endf6Modifier";
    string func_name  = "check_MF_MT_number(Integer mf_no, Integer mt_no)";

    ostringstream oss01, oss02;
    oss01 << mf_no;
    oss02 << mt_no;

    string str_data01 = "MF number : " + oss01.str();
    string str_data02 = "MT number : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This MF/MT number is not defined in the ENDF-6 format.");
    err_com.push_back("Please check your input file.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::get_ZA_AWR_value(Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add)
{
  mat_ori = endf_obj_ori.get_mf01_mt451_data().get_mat_no();
  za_ori  = endf_obj_ori.get_mf01_mt451_data().get_ZA();
  awr_ori = endf_obj_ori.get_mf01_mt451_data().get_AWR();

  Integer mat_add = endf_obj_add.get_mf01_mt451_data().get_mat_no();
  Real    za_add  = endf_obj_add.get_mf01_mt451_data().get_ZA();
  Real    awr_add = endf_obj_add.get_mf01_mt451_data().get_AWR();

  if( mat_add != mat_ori )
  {
    string class_name = "Endf6Modifier";
    string func_name  = "get_ZA_AWR_value(Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add)";

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
    err_com.push_back("Please check your input file or nuclear data files.");

    err_obj.output_caution(class_name, func_name, err_com);
  }

  if( fabs(za_add - za_ori) > za_ori * 1.0E-3 )
  {
    string class_name = "Endf6Modifier";
    string func_name  = "get_ZA_AWR_value(Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add)";

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
    err_com.push_back("Please check your input file or nuclear data files.");

    err_obj.output_caution(class_name, func_name, err_com);
  }

  if( fabs(awr_add - awr_ori) > awr_ori * 1.0E-3 )
  {
    string class_name = "Endf6Modifier";
    string func_name  = "get_ZA_AWR_value(Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add)";

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
    err_com.push_back("Please check your input file or nuclear data files.");

    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::remove_specified_MF_data
                      (NuclearDataObject& nucl_obj, Integer mf_no)
{
  Endf6Parser endf_obj;
  endf_conv_obj.convert_frendy_to_endf_format(nucl_obj, endf_obj);

  remove_specified_MF_data(endf_obj, mf_no);

  endf_conv_obj.convert_endf_format_to_frendy(endf_obj, nucl_obj);
  endf_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::remove_specified_MF_data
                      (Endf6Parser& endf_obj, Integer mf_no)
{
  check_MF_number(mf_no);

  int remove_flg = 0;

  if( mf_no == 1 )
  {
    remove_specified_MF_MT_data_without_error_message(endf_obj, 1, 451, remove_flg);
    remove_specified_MF_MT_data_without_error_message(endf_obj, 1, 452, remove_flg);
    remove_specified_MF_MT_data_without_error_message(endf_obj, 1, 455, remove_flg);
    remove_specified_MF_MT_data_without_error_message(endf_obj, 1, 456, remove_flg);
    remove_specified_MF_MT_data_without_error_message(endf_obj, 1, 458, remove_flg);
    remove_specified_MF_MT_data_without_error_message(endf_obj, 1, 460, remove_flg);
  }
  else if( mf_no == 2 )
  {
    remove_specified_MF_MT_data_without_error_message(endf_obj, 2, 151, remove_flg);
    remove_specified_MF_MT_data_without_error_message(endf_obj, 2, 152, remove_flg);
    remove_specified_MF_MT_data_without_error_message(endf_obj, 2, 153, remove_flg);
  }
  else if( mf_no == 3 )
  {
    vector<MF03Parser> mf03_data;
    vector<MF03Parser>().swap(mf03_data);

    endf_obj.set_mf03_data(mf03_data);
  }
  else if( mf_no == 4 )
  {
    vector<MF04Parser> mf04_data;
    vector<MF04Parser>().swap(mf04_data);

    endf_obj.set_mf04_data(mf04_data);
  }
  else if( mf_no == 5 )
  {
    vector<MF05Parser> mf05_data;
    vector<MF05Parser>().swap(mf05_data);

    endf_obj.set_mf05_data(mf05_data);
  }
  else if( mf_no == 6 )
  {
    vector<MF06Parser> mf06_data;
    vector<MF06Parser>().swap(mf06_data);

    endf_obj.set_mf06_data(mf06_data);
  }
  else if( mf_no == 7 )
  {
    remove_specified_MF_MT_data_without_error_message(endf_obj, 7, 2, remove_flg);
    remove_specified_MF_MT_data_without_error_message(endf_obj, 7, 4, remove_flg);
  }
  else if( mf_no == 8 )
  {
    remove_specified_MF_MT_data_without_error_message(endf_obj, 8, 454, remove_flg);
    remove_specified_MF_MT_data_without_error_message(endf_obj, 8, 457, remove_flg);
    remove_specified_MF_MT_data_without_error_message(endf_obj, 8, 459, remove_flg);

    vector<MF08Parser> mf08_data;
    vector<MF08Parser>().swap(mf08_data);

    endf_obj.set_mf08_data(mf08_data);
  }
  else if( mf_no == 9 )
  {
    vector<MF09Parser> mf09_data;
    vector<MF09Parser>().swap(mf09_data);

    endf_obj.set_mf09_data(mf09_data);
  }
  else if( mf_no == 10 )
  {
    vector<MF10Parser> mf10_data;
    vector<MF10Parser>().swap(mf10_data);

    endf_obj.set_mf10_data(mf10_data);
  }
  else if( mf_no == 12 )
  {
    vector<MF12Parser> mf12_data;
    vector<MF12Parser>().swap(mf12_data);

    endf_obj.set_mf12_data(mf12_data);
  }
  else if( mf_no == 13 )
  {
    vector<MF13Parser> mf13_data;
    vector<MF13Parser>().swap(mf13_data);

    endf_obj.set_mf13_data(mf13_data);
  }
  else if( mf_no == 14 )
  {
    vector<MF14Parser> mf14_data;
    vector<MF14Parser>().swap(mf14_data);

    endf_obj.set_mf14_data(mf14_data);
  }
  else if( mf_no == 15 )
  {
    vector<MF15Parser> mf15_data;
    vector<MF15Parser>().swap(mf15_data);

    endf_obj.set_mf15_data(mf15_data);
  }
  else if( mf_no == 23 )
  {
    vector<MF23Parser> mf23_data;
    vector<MF23Parser>().swap(mf23_data);

    endf_obj.set_mf23_data(mf23_data);
  }
  else if( mf_no == 26 )
  {
    vector<MF26Parser> mf26_data;
    vector<MF26Parser>().swap(mf26_data);

    endf_obj.set_mf26_data(mf26_data);
  }
  else if( mf_no == 27 )
  {
    vector<MF27Parser> mf27_data;
    vector<MF27Parser>().swap(mf27_data);

    endf_obj.set_mf27_data(mf27_data);
  }
  else if( mf_no == 28 )
  {
    vector<MF28Parser> mf28_data;
    vector<MF28Parser>().swap(mf28_data);

    endf_obj.set_mf28_data(mf28_data);
  }
  else if( mf_no == 30 )
  {
    remove_specified_MF_MT_data_without_error_message(endf_obj, 30, 1, remove_flg);
    remove_specified_MF_MT_data_without_error_message(endf_obj, 30, 2, remove_flg);
  }
  else if( mf_no == 31 )
  {
    vector<MF31Parser> mf31_data;
    vector<MF31Parser>().swap(mf31_data);

    endf_obj.set_mf31_data(mf31_data);
  }
  else if( mf_no == 32 )
  {
    remove_specified_MF_MT_data_without_error_message(endf_obj, 32, 151, remove_flg);
  }
  else if( mf_no == 33 )
  {
    vector<MF33Parser> mf33_data;
    vector<MF33Parser>().swap(mf33_data);

    endf_obj.set_mf33_data(mf33_data);
  }
  else if( mf_no == 34 )
  {
    vector<MF34Parser> mf34_data;
    vector<MF34Parser>().swap(mf34_data);

    endf_obj.set_mf34_data(mf34_data);
  }
  else if( mf_no == 35 )
  {
    vector<MF35Parser> mf35_data;
    vector<MF35Parser>().swap(mf35_data);

    endf_obj.set_mf35_data(mf35_data);
  }
  else if( mf_no == 40 )
  {
    vector<MF40Parser> mf40_data;
    vector<MF40Parser>().swap(mf40_data);

    endf_obj.set_mf40_data(mf40_data);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::merge_specified_MF_data
                      (Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add, Integer mf_no,
                       int& ori_flg, int& mod_flg)
{
  check_MF_number(mf_no);

  get_ZA_AWR_value(endf_obj_ori, endf_obj_add);

  int no_data_flg = 0;
      ori_flg     = 0;
      mod_flg     = 0;
  if( mf_no == 1 )
  {
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 1, 451, ori_flg, mod_flg, no_data_flg);
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 1, 452, ori_flg, mod_flg, no_data_flg);
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 1, 455, ori_flg, mod_flg, no_data_flg);
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 1, 456, ori_flg, mod_flg, no_data_flg);
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 1, 458, ori_flg, mod_flg, no_data_flg);
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 1, 460, ori_flg, mod_flg, no_data_flg);
  }
  else if( mf_no == 2 )
  {
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 2, 151, ori_flg, mod_flg, no_data_flg);
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 2, 152, ori_flg, mod_flg, no_data_flg);
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 2, 153, ori_flg, mod_flg, no_data_flg);
  }
  else if( mf_no == 3 )
  {
    vector<MF03Parser> mf03_data = endf_obj_add.get_mf03_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf03_data().size());
    mod_flg = static_cast<int>(mf03_data.size());

    for(int i=0; i<static_cast<int>(mf03_data.size()); i++)
    {
      mf03_data[i].set_mat_no(mat_ori);
      mf03_data[i].set_ZA(za_ori);
      mf03_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf03_data(mf03_data);

    vector<MF03Parser>().swap(mf03_data);
  }
  else if( mf_no == 4 )
  {
    vector<MF04Parser> mf04_data = endf_obj_add.get_mf04_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf04_data().size());
    mod_flg = static_cast<int>(mf04_data.size());

    for(int i=0; i<static_cast<int>(mf04_data.size()); i++)
    {
      mf04_data[i].set_mat_no(mat_ori);
      mf04_data[i].set_ZA(za_ori);
      mf04_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf04_data(mf04_data);

    vector<MF04Parser>().swap(mf04_data);
  }
  else if( mf_no == 5 )
  {
    vector<MF05Parser> mf05_data = endf_obj_add.get_mf05_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf05_data().size());
    mod_flg = static_cast<int>(mf05_data.size());

    for(int i=0; i<static_cast<int>(mf05_data.size()); i++)
    {
      mf05_data[i].set_mat_no(mat_ori);
      mf05_data[i].set_ZA(za_ori);
      mf05_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf05_data(mf05_data);

    vector<MF05Parser>().swap(mf05_data);
  }
  else if( mf_no == 6 )
  {
    vector<MF06Parser> mf06_data = endf_obj_add.get_mf06_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf06_data().size());
    mod_flg = static_cast<int>(mf06_data.size());

    for(int i=0; i<static_cast<int>(mf06_data.size()); i++)
    {
      mf06_data[i].set_mat_no(mat_ori);
      mf06_data[i].set_ZA(za_ori);
      mf06_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf06_data(mf06_data);

    vector<MF06Parser>().swap(mf06_data);
  }
  else if( mf_no == 7 )
  {
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 7, 2, ori_flg, mod_flg, no_data_flg);
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 7, 4, ori_flg, mod_flg, no_data_flg);
  }
  else if( mf_no == 8 )
  {
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 8, 454, ori_flg, mod_flg, no_data_flg);
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 8, 457, ori_flg, mod_flg, no_data_flg);
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 8, 459, ori_flg, mod_flg, no_data_flg);

    vector<MF08Parser> mf08_data = endf_obj_add.get_mf08_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf08_data().size());
    mod_flg = static_cast<int>(mf08_data.size());

    for(int i=0; i<static_cast<int>(mf08_data.size()); i++)
    {
      mf08_data[i].set_mat_no(mat_ori);
      mf08_data[i].set_ZA(za_ori);
      mf08_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf08_data(mf08_data);

    vector<MF08Parser>().swap(mf08_data);
  }
  else if( mf_no == 9 )
  {
    vector<MF09Parser> mf09_data = endf_obj_add.get_mf09_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf09_data().size());
    mod_flg = static_cast<int>(mf09_data.size());

    for(int i=0; i<static_cast<int>(mf09_data.size()); i++)
    {
      mf09_data[i].set_mat_no(mat_ori);
      mf09_data[i].set_ZA(za_ori);
      mf09_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf09_data(mf09_data);

    vector<MF09Parser>().swap(mf09_data);
  }
  else if( mf_no == 10 )
  {
    vector<MF10Parser> mf10_data = endf_obj_add.get_mf10_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf10_data().size());
    mod_flg = static_cast<int>(mf10_data.size());

    for(int i=0; i<static_cast<int>(mf10_data.size()); i++)
    {
      mf10_data[i].set_mat_no(mat_ori);
      mf10_data[i].set_ZA(za_ori);
      mf10_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf10_data(mf10_data);

    vector<MF10Parser>().swap(mf10_data);
  }
  else if( mf_no == 12 )
  {
    vector<MF12Parser> mf12_data = endf_obj_add.get_mf12_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf12_data().size());
    mod_flg = static_cast<int>(mf12_data.size());

    for(int i=0; i<static_cast<int>(mf12_data.size()); i++)
    {
      mf12_data[i].set_mat_no(mat_ori);
      mf12_data[i].set_ZA(za_ori);
      mf12_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf12_data(mf12_data);

    vector<MF12Parser>().swap(mf12_data);
  }
  else if( mf_no == 13 )
  {
    vector<MF13Parser> mf13_data = endf_obj_add.get_mf13_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf13_data().size());
    mod_flg = static_cast<int>(mf13_data.size());

    for(int i=0; i<static_cast<int>(mf13_data.size()); i++)
    {
      mf13_data[i].set_mat_no(mat_ori);
      mf13_data[i].set_ZA(za_ori);
      mf13_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf13_data(mf13_data);

    vector<MF13Parser>().swap(mf13_data);
  }
  else if( mf_no == 14 )
  {
    vector<MF14Parser> mf14_data = endf_obj_add.get_mf14_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf14_data().size());
    mod_flg = static_cast<int>(mf14_data.size());

    for(int i=0; i<static_cast<int>(mf14_data.size()); i++)
    {
      mf14_data[i].set_mat_no(mat_ori);
      mf14_data[i].set_ZA(za_ori);
      mf14_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf14_data(mf14_data);

    vector<MF14Parser>().swap(mf14_data);
  }
  else if( mf_no == 15 )
  {
    vector<MF15Parser> mf15_data = endf_obj_add.get_mf15_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf15_data().size());
    mod_flg = static_cast<int>(mf15_data.size());

    for(int i=0; i<static_cast<int>(mf15_data.size()); i++)
    {
      mf15_data[i].set_mat_no(mat_ori);
      mf15_data[i].set_ZA(za_ori);
      mf15_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf15_data(mf15_data);

    vector<MF15Parser>().swap(mf15_data);
  }
  else if( mf_no == 23 )
  {
    vector<MF23Parser> mf23_data = endf_obj_add.get_mf23_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf23_data().size());
    mod_flg = static_cast<int>(mf23_data.size());

    for(int i=0; i<static_cast<int>(mf23_data.size()); i++)
    {
      mf23_data[i].set_mat_no(mat_ori);
      mf23_data[i].set_ZA(za_ori);
      mf23_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf23_data(mf23_data);

    vector<MF23Parser>().swap(mf23_data);
  }
  else if( mf_no == 26 )
  {
    vector<MF26Parser> mf26_data = endf_obj_add.get_mf26_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf26_data().size());
    mod_flg = static_cast<int>(mf26_data.size());

    for(int i=0; i<static_cast<int>(mf26_data.size()); i++)
    {
      mf26_data[i].set_mat_no(mat_ori);
      mf26_data[i].set_ZA(za_ori);
      mf26_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf26_data(mf26_data);

    vector<MF26Parser>().swap(mf26_data);
  }
  else if( mf_no == 27 )
  {
    vector<MF27Parser> mf27_data = endf_obj_add.get_mf27_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf27_data().size());
    mod_flg = static_cast<int>(mf27_data.size());

    for(int i=0; i<static_cast<int>(mf27_data.size()); i++)
    {
      mf27_data[i].set_mat_no(mat_ori);
      mf27_data[i].set_ZA(za_ori);
      mf27_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf27_data(mf27_data);

    vector<MF27Parser>().swap(mf27_data);
  }
  else if( mf_no == 28 )
  {
    vector<MF28Parser> mf28_data = endf_obj_add.get_mf28_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf28_data().size());
    mod_flg = static_cast<int>(mf28_data.size());

    for(int i=0; i<static_cast<int>(mf28_data.size()); i++)
    {
      mf28_data[i].set_mat_no(mat_ori);
      mf28_data[i].set_ZA(za_ori);
      mf28_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf28_data(mf28_data);

    vector<MF28Parser>().swap(mf28_data);
  }
  else if( mf_no == 30 )
  {
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 30, 1, ori_flg, mod_flg, no_data_flg);
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 30, 2, ori_flg, mod_flg, no_data_flg);
  }
  else if( mf_no == 31 )
  {
    vector<MF31Parser> mf31_data = endf_obj_add.get_mf31_data();

    ori_flg = static_cast<int>(endf_obj_ori.get_mf31_data().size());
    mod_flg = static_cast<int>(mf31_data.size());

    for(int i=0; i<static_cast<int>(mf31_data.size()); i++)
    {
      mf31_data[i].set_mat_no(mat_ori);
      mf31_data[i].set_ZA(za_ori);
      mf31_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf31_data(mf31_data);

    vector<MF31Parser>().swap(mf31_data);
  }
  else if( mf_no == 32 )
  {
    merge_specified_MF_MT_data_without_error_message
      (endf_obj_ori, endf_obj_add, 32, 151, ori_flg, mod_flg, no_data_flg);
  }
  else if( mf_no == 33 )
  {
    vector<MF33Parser> mf33_data = endf_obj_add.get_mf33_data();

    for(int i=0; i<static_cast<int>(mf33_data.size()); i++)
    {
      mf33_data[i].set_mat_no(mat_ori);
      mf33_data[i].set_ZA(za_ori);
      mf33_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf33_data(mf33_data);

    vector<MF33Parser>().swap(mf33_data);
  }
  else if( mf_no == 34 )
  {
    vector<MF34Parser> mf34_data = endf_obj_add.get_mf34_data();

    for(int i=0; i<static_cast<int>(mf34_data.size()); i++)
    {
      mf34_data[i].set_mat_no(mat_ori);
      mf34_data[i].set_ZA(za_ori);
      mf34_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf34_data(mf34_data);

    vector<MF34Parser>().swap(mf34_data);
  }
  else if( mf_no == 35 )
  {
    vector<MF35Parser> mf35_data = endf_obj_add.get_mf35_data();

    for(int i=0; i<static_cast<int>(mf35_data.size()); i++)
    {
      mf35_data[i].set_mat_no(mat_ori);
      mf35_data[i].set_ZA(za_ori);
      mf35_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf35_data(mf35_data);

    vector<MF35Parser>().swap(mf35_data);
  }
  else if( mf_no == 40 )
  {
    vector<MF40Parser> mf40_data = endf_obj_add.get_mf40_data();

    for(int i=0; i<static_cast<int>(mf40_data.size()); i++)
    {
      mf40_data[i].set_mat_no(mat_ori);
      mf40_data[i].set_ZA(za_ori);
      mf40_data[i].set_AWR(awr_ori);
    }
    endf_obj_ori.set_mf40_data(mf40_data);

    vector<MF40Parser>().swap(mf40_data);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::change_specified_MF_data
                      (NuclearDataObject& nucl_obj_ori, NuclearDataObject& nucl_obj_add, Integer mf_no)
{
  Endf6Parser endf_obj_ori, endf_obj_add;
  endf_conv_obj.convert_frendy_to_endf_format(nucl_obj_ori, endf_obj_ori);
  endf_conv_obj.convert_frendy_to_endf_format(nucl_obj_add, endf_obj_add);

  change_specified_MF_data(endf_obj_ori, endf_obj_add, mf_no);

  endf_conv_obj.convert_endf_format_to_frendy(endf_obj_ori, nucl_obj_ori);
  endf_obj_ori.clear();
  endf_obj_add.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::change_specified_MF_data
                      (Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add, Integer mf_no)
{
  int ori_flg = 0;
  int mod_flg = 0;
  merge_specified_MF_data(endf_obj_ori, endf_obj_add, mf_no, ori_flg, mod_flg);

  if( ori_flg != mod_flg )
  {
    string class_name = "Endf6Modifier";
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
    err_com.push_back("Please check your input file or nuclear data files.");

    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::add_specified_MF_data
                      (NuclearDataObject& nucl_obj_ori, NuclearDataObject& nucl_obj_add, Integer mf_no)
{
  Endf6Parser endf_obj_ori, endf_obj_add;
  endf_conv_obj.convert_frendy_to_endf_format(nucl_obj_ori, endf_obj_ori);
  endf_conv_obj.convert_frendy_to_endf_format(nucl_obj_add, endf_obj_add);

  add_specified_MF_data(endf_obj_ori, endf_obj_add, mf_no);

  endf_conv_obj.convert_endf_format_to_frendy(endf_obj_ori, nucl_obj_ori);
  endf_obj_ori.clear();
  endf_obj_add.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::add_specified_MF_data
                      (Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add, Integer mf_no)
{
  int ori_flg = 0;
  int mod_flg = 0;
  merge_specified_MF_data(endf_obj_ori, endf_obj_add, mf_no, ori_flg, mod_flg);

  if( ori_flg > 0 )
  {
    string class_name = "Endf6Modifier";
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

    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::remove_specified_MF_MT_data_without_error_message
                      (Endf6Parser& endf_obj, Integer mf_no, Integer mt_no, int& remove_flg)
{
  check_MF_MT_number(mf_no, mt_no);

  remove_flg = 0;;

  if( mf_no == 1 )
  {
    if( mt_no == 451 )
    {
      MF01MT451Parser mf01_mt451_data = endf_obj.get_mf01_mt451_data();
      vector<string> comment_line;
      comment_line.clear();
      mf01_mt451_data.set_comment_line(comment_line);

      endf_obj.set_mf01_mt451_data(mf01_mt451_data);
    }
    else if( mt_no == 452 )
    {
      MF01MT452Parser mf01_mt452_data;
      mf01_mt452_data.clear();
      endf_obj.set_mf01_mt452_data(mf01_mt452_data);
    }
    else if( mt_no == 455 )
    {
      MF01MT455Parser mf01_mt455_data;
      mf01_mt455_data.clear();
      endf_obj.set_mf01_mt455_data(mf01_mt455_data);
    }
    else if( mt_no == 456 )
    {
      MF01MT456Parser mf01_mt456_data;
      mf01_mt456_data.clear();
      endf_obj.set_mf01_mt456_data(mf01_mt456_data);
    }
    else if( mt_no == 458 )
    {
      MF01MT458Parser mf01_mt458_data;
      mf01_mt458_data.clear();
      endf_obj.set_mf01_mt458_data(mf01_mt458_data);
    }
    else if( mt_no == 460 )
    {
      MF01MT460Parser mf01_mt460_data;
      mf01_mt460_data.clear();
      endf_obj.set_mf01_mt460_data(mf01_mt460_data);
    }
  }
  else if( mf_no == 2 )
  {
    if( mt_no == 151 )
    {
      MF02MT151Parser mf02_mt151_data;
      mf02_mt151_data.clear();
      endf_obj.set_mf02_mt151_data(mf02_mt151_data);
    }
    else if( mt_no == 152 )
    {
      MF02MT152Parser mf02_mt152_data;
      mf02_mt152_data.clear();
      endf_obj.set_mf02_mt152_data(mf02_mt152_data);
    }
    else if( mt_no == 153 )
    {
      MF02MT153Parser mf02_mt153_data;
      mf02_mt153_data.clear();
      endf_obj.set_mf02_mt153_data(mf02_mt153_data);
    }
  }
  else if( mf_no == 3 )
  {
    remove_flg = 1;

    vector<MF03Parser> mf03_data;
    vector<MF03Parser>().swap(mf03_data);

    vector<MF03Parser> mf03_data_ori = endf_obj.get_mf03_data();

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

    endf_obj.set_mf03_data(mf03_data);
    vector<MF03Parser>().swap(mf03_data);
  }
  else if( mf_no == 4 )
  {
    remove_flg = 1;

    vector<MF04Parser> mf04_data;
    vector<MF04Parser>().swap(mf04_data);

    vector<MF04Parser> mf04_data_ori = endf_obj.get_mf04_data();

    for(int i=0; i<static_cast<int>(mf04_data_ori.size()); i++)
    {
      if( mt_no != mf04_data_ori[i].get_mt_no() )
      {
        mf04_data.push_back(mf04_data_ori[i]);
      }
      else //if( mt_no == mf04_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf04_data(mf04_data);
    vector<MF04Parser>().swap(mf04_data);
  }
  else if( mf_no == 5 )
  {
    remove_flg = 1;

    vector<MF05Parser> mf05_data;
    vector<MF05Parser>().swap(mf05_data);

    vector<MF05Parser> mf05_data_ori = endf_obj.get_mf05_data();

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

    endf_obj.set_mf05_data(mf05_data);
    vector<MF05Parser>().swap(mf05_data);
  }
  else if( mf_no == 6 )
  {
    remove_flg = 1;

    vector<MF06Parser> mf06_data;
    vector<MF06Parser>().swap(mf06_data);

    vector<MF06Parser> mf06_data_ori = endf_obj.get_mf06_data();

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

    endf_obj.set_mf06_data(mf06_data);
    vector<MF06Parser>().swap(mf06_data);
  }
  else if( mf_no == 7 )
  {
    if( mt_no == 2 )
    {
      MF07MT002Parser mf07_mt002_data;
      mf07_mt002_data.clear();
      endf_obj.set_mf07_mt002_data(mf07_mt002_data);
    }
    else if( mt_no == 4 )
    {
      MF07MT004Parser mf07_mt004_data;
      mf07_mt004_data.clear();
      endf_obj.set_mf07_mt004_data(mf07_mt004_data);
    }
  }
  else if( mf_no == 8 )
  {
    if( mt_no == 454 )
    {
      MF08MT454Parser mf08_mt454_data;
      mf08_mt454_data.clear();
      endf_obj.set_mf08_mt454_data(mf08_mt454_data);
    }
    else if( mt_no == 457 )
    {
      MF08MT457Parser mf08_mt457_data;
      mf08_mt457_data.clear();
      endf_obj.set_mf08_mt457_data(mf08_mt457_data);
    }
    else if( mt_no == 459 )
    {
      MF08MT459Parser mf08_mt459_data;
      mf08_mt459_data.clear();
      endf_obj.set_mf08_mt459_data(mf08_mt459_data);
    }
    else
    {
      remove_flg = 1;

      vector<MF08Parser> mf08_data;
      vector<MF08Parser>().swap(mf08_data);

      vector<MF08Parser> mf08_data_ori = endf_obj.get_mf08_data();

      for(int i=0; i<static_cast<int>(mf08_data_ori.size()); i++)
      {
        if( mt_no != mf08_data_ori[i].get_mt_no() )
        {
          mf08_data.push_back(mf08_data_ori[i]);
        }
        else //if( mt_no == mf08_data_ori[i].get_mt_no() )
        {
          remove_flg = 0;
        }
      }

      endf_obj.set_mf08_data(mf08_data);
      vector<MF08Parser>().swap(mf08_data);
    }
  }
  else if( mf_no == 9 )
  {
    remove_flg = 1;

    vector<MF09Parser> mf09_data;
    vector<MF09Parser>().swap(mf09_data);

    vector<MF09Parser> mf09_data_ori = endf_obj.get_mf09_data();

    for(int i=0; i<static_cast<int>(mf09_data_ori.size()); i++)
    {
      if( mt_no != mf09_data_ori[i].get_mt_no() )
      {
        mf09_data.push_back(mf09_data_ori[i]);
      }
      else //if( mt_no == mf09_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf09_data(mf09_data);
    vector<MF09Parser>().swap(mf09_data);
  }
  else if( mf_no == 10 )
  {
    remove_flg = 1;

    vector<MF10Parser> mf10_data;
    vector<MF10Parser>().swap(mf10_data);

    vector<MF10Parser> mf10_data_ori = endf_obj.get_mf10_data();

    for(int i=0; i<static_cast<int>(mf10_data_ori.size()); i++)
    {
      if( mt_no != mf10_data_ori[i].get_mt_no() )
      {
        mf10_data.push_back(mf10_data_ori[i]);
      }
      else //if( mt_no == mf10_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf10_data(mf10_data);
    vector<MF10Parser>().swap(mf10_data);
  }
  else if( mf_no == 12 )
  {
    remove_flg = 1;

    vector<MF12Parser> mf12_data;
    vector<MF12Parser>().swap(mf12_data);

    vector<MF12Parser> mf12_data_ori = endf_obj.get_mf12_data();

    for(int i=0; i<static_cast<int>(mf12_data_ori.size()); i++)
    {
      if( mt_no != mf12_data_ori[i].get_mt_no() )
      {
        mf12_data.push_back(mf12_data_ori[i]);
      }
      else //if( mt_no == mf12_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf12_data(mf12_data);
    vector<MF12Parser>().swap(mf12_data);
  }
  else if( mf_no == 13 )
  {
    remove_flg = 1;

    vector<MF13Parser> mf13_data;
    vector<MF13Parser>().swap(mf13_data);

    vector<MF13Parser> mf13_data_ori = endf_obj.get_mf13_data();

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

    endf_obj.set_mf13_data(mf13_data);
    vector<MF13Parser>().swap(mf13_data);
  }
  else if( mf_no == 14 )
  {
    remove_flg = 1;

    vector<MF14Parser> mf14_data;
    vector<MF14Parser>().swap(mf14_data);

    vector<MF14Parser> mf14_data_ori = endf_obj.get_mf14_data();

    for(int i=0; i<static_cast<int>(mf14_data_ori.size()); i++)
    {
      if( mt_no != mf14_data_ori[i].get_mt_no() )
      {
        mf14_data.push_back(mf14_data_ori[i]);
      }
      else //if( mt_no == mf14_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf14_data(mf14_data);
    vector<MF14Parser>().swap(mf14_data);
  }
  else if( mf_no == 15 )
  {
    remove_flg = 1;

    vector<MF15Parser> mf15_data;
    vector<MF15Parser>().swap(mf15_data);

    vector<MF15Parser> mf15_data_ori = endf_obj.get_mf15_data();

    for(int i=0; i<static_cast<int>(mf15_data_ori.size()); i++)
    {
      if( mt_no != mf15_data_ori[i].get_mt_no() )
      {
        mf15_data.push_back(mf15_data_ori[i]);
      }
      else //if( mt_no == mf15_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf15_data(mf15_data);
    vector<MF15Parser>().swap(mf15_data);
  }
  else if( mf_no == 23 )
  {
    remove_flg = 1;

    vector<MF23Parser> mf23_data;
    vector<MF23Parser>().swap(mf23_data);

    vector<MF23Parser> mf23_data_ori = endf_obj.get_mf23_data();

    for(int i=0; i<static_cast<int>(mf23_data_ori.size()); i++)
    {
      if( mt_no != mf23_data_ori[i].get_mt_no() )
      {
        mf23_data.push_back(mf23_data_ori[i]);
      }
      else //if( mt_no == mf23_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf23_data(mf23_data);
    vector<MF23Parser>().swap(mf23_data);
  }
  else if( mf_no == 26 )
  {
    remove_flg = 1;

    vector<MF26Parser> mf26_data;
    vector<MF26Parser>().swap(mf26_data);

    vector<MF26Parser> mf26_data_ori = endf_obj.get_mf26_data();

    for(int i=0; i<static_cast<int>(mf26_data_ori.size()); i++)
    {
      if( mt_no != mf26_data_ori[i].get_mt_no() )
      {
        mf26_data.push_back(mf26_data_ori[i]);
      }
      else //if( mt_no == mf26_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf26_data(mf26_data);
    vector<MF26Parser>().swap(mf26_data);
  }
  else if( mf_no == 27 )
  {
    remove_flg = 1;

    vector<MF27Parser> mf27_data;
    vector<MF27Parser>().swap(mf27_data);

    vector<MF27Parser> mf27_data_ori = endf_obj.get_mf27_data();

    for(int i=0; i<static_cast<int>(mf27_data_ori.size()); i++)
    {
      if( mt_no != mf27_data_ori[i].get_mt_no() )
      {
        mf27_data.push_back(mf27_data_ori[i]);
      }
      else //if( mt_no == mf27_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf27_data(mf27_data);
    vector<MF27Parser>().swap(mf27_data);
  }
  else if( mf_no == 28 )
  {
    remove_flg = 1;

    vector<MF28Parser> mf28_data;
    vector<MF28Parser>().swap(mf28_data);

    vector<MF28Parser> mf28_data_ori = endf_obj.get_mf28_data();

    for(int i=0; i<static_cast<int>(mf28_data_ori.size()); i++)
    {
      if( mt_no != mf28_data_ori[i].get_mt_no() )
      {
        mf28_data.push_back(mf28_data_ori[i]);
      }
      else //if( mt_no == mf28_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf28_data(mf28_data);
    vector<MF28Parser>().swap(mf28_data);
  }
  else if( mf_no == 30 )
  {
    if( mt_no == 1 )
    {
      MF30MT001Parser mf30_mt001_data;
      mf30_mt001_data.clear();
      endf_obj.set_mf30_mt001_data(mf30_mt001_data);
    }
    else if( mt_no == 2 )
    {
      MF30MT002Parser mf30_mt002_data;
      mf30_mt002_data.clear();
      endf_obj.set_mf30_mt002_data(mf30_mt002_data);
    }
  }
  else if( mf_no == 31 )
  {
    remove_flg = 1;

    vector<MF31Parser> mf31_data;
    vector<MF31Parser>().swap(mf31_data);

    vector<MF31Parser> mf31_data_ori = endf_obj.get_mf31_data();

    for(int i=0; i<static_cast<int>(mf31_data_ori.size()); i++)
    {
      if( mt_no != mf31_data_ori[i].get_mt_no() )
      {
        mf31_data.push_back(mf31_data_ori[i]);
      }
      else //if( mt_no == mf31_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf31_data(mf31_data);
    vector<MF31Parser>().swap(mf31_data);
  }
  else if( mf_no == 32 )
  {
    if( mt_no == 151 )
    {
      MF32MT151Parser mf32_mt151_data;
      mf32_mt151_data.clear();
      endf_obj.set_mf32_mt151_data(mf32_mt151_data);
    }
  }
  else if( mf_no == 33 )
  {
    remove_flg = 1;

    vector<MF33Parser> mf33_data;
    vector<MF33Parser>().swap(mf33_data);

    vector<MF33Parser> mf33_data_ori = endf_obj.get_mf33_data();

    for(int i=0; i<static_cast<int>(mf33_data_ori.size()); i++)
    {
      if( mt_no != mf33_data_ori[i].get_mt_no() )
      {
        mf33_data.push_back(mf33_data_ori[i]);
      }
      else //if( mt_no == mf33_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf33_data(mf33_data);
    vector<MF33Parser>().swap(mf33_data);
  }
  else if( mf_no == 34 )
  {
    remove_flg = 1;

    vector<MF34Parser> mf34_data;
    vector<MF34Parser>().swap(mf34_data);

    vector<MF34Parser> mf34_data_ori = endf_obj.get_mf34_data();

    for(int i=0; i<static_cast<int>(mf34_data_ori.size()); i++)
    {
      if( mt_no != mf34_data_ori[i].get_mt_no() )
      {
        mf34_data.push_back(mf34_data_ori[i]);
      }
      else //if( mt_no == mf34_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf34_data(mf34_data);
    vector<MF34Parser>().swap(mf34_data);
  }
  else if( mf_no == 35 )
  {
    remove_flg = 1;

    vector<MF35Parser> mf35_data;
    vector<MF35Parser>().swap(mf35_data);

    vector<MF35Parser> mf35_data_ori = endf_obj.get_mf35_data();

    for(int i=0; i<static_cast<int>(mf35_data_ori.size()); i++)
    {
      if( mt_no != mf35_data_ori[i].get_mt_no() )
      {
        mf35_data.push_back(mf35_data_ori[i]);
      }
      else //if( mt_no == mf35_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf35_data(mf35_data);
    vector<MF35Parser>().swap(mf35_data);
  }
  else if( mf_no == 40 )
  {
    remove_flg = 1;

    vector<MF40Parser> mf40_data;
    vector<MF40Parser>().swap(mf40_data);

    vector<MF40Parser> mf40_data_ori = endf_obj.get_mf40_data();

    for(int i=0; i<static_cast<int>(mf40_data_ori.size()); i++)
    {
      if( mt_no != mf40_data_ori[i].get_mt_no() )
      {
        mf40_data.push_back(mf40_data_ori[i]);
      }
      else //if( mt_no == mf40_data_ori[i].get_mt_no() )
      {
        remove_flg = 0;
      }
    }

    endf_obj.set_mf40_data(mf40_data);
    vector<MF40Parser>().swap(mf40_data);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::remove_specified_MF_MT_data
                      (NuclearDataObject& nucl_obj, Integer mf_no, Integer mt_no)
{
  Endf6Parser endf_obj;
  endf_conv_obj.convert_frendy_to_endf_format(nucl_obj, endf_obj);

  remove_specified_MF_MT_data(endf_obj, mf_no, mt_no);

  endf_conv_obj.convert_endf_format_to_frendy(endf_obj, nucl_obj);
  endf_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::remove_specified_MF_MT_data
                      (Endf6Parser& endf_obj, Integer mf_no, Integer mt_no)
{
  int remove_flg = 0;
  remove_specified_MF_MT_data_without_error_message(endf_obj, mf_no, mt_no, remove_flg);

  if( remove_flg == 1 )
  {
    string class_name = "Endf6Modifier";
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
    err_com.push_back("Please check your input file or nuclear data files.");

    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::merge_specified_MF_MT_data_without_error_message
                      (Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add, Integer mf_no, Integer mt_no,
                       int& ori_flg, int& mod_flg, int& no_data_flg)
{
  check_MF_MT_number(mf_no, mt_no);

  get_ZA_AWR_value(endf_obj_ori, endf_obj_add);

  no_data_flg = 0;

  if( mf_no == 1 )
  {
    if( mt_no == 451 )
    {
      MF01MT451Parser mf01_mt451_data = endf_obj_add.get_mf01_mt451_data();

      mf01_mt451_data.set_mat_no(mat_ori);
      mf01_mt451_data.set_ZA(za_ori);
      mf01_mt451_data.set_AWR(awr_ori);

      endf_obj_ori.set_mf01_mt451_data(mf01_mt451_data);

      mf01_mt451_data.clear();
    }
    else if( mt_no == 452 )
    {
      MF01MT452Parser mf01_mt452_data = endf_obj_add.get_mf01_mt452_data();

      ori_flg = endf_obj_ori.get_mf01_mt452_data().get_mat_no();
      mod_flg = mf01_mt452_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf01_mt452_data.set_mat_no(mat_ori);
        mf01_mt452_data.set_ZA(za_ori);
        mf01_mt452_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf01_mt452_data(mf01_mt452_data);

        mf01_mt452_data.clear();
      }
    }
    else if( mt_no == 455 )
    {
      MF01MT455Parser mf01_mt455_data = endf_obj_add.get_mf01_mt455_data();

      ori_flg = endf_obj_ori.get_mf01_mt455_data().get_mat_no();
      mod_flg = mf01_mt455_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf01_mt455_data.set_mat_no(mat_ori);
        mf01_mt455_data.set_ZA(za_ori);
        mf01_mt455_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf01_mt455_data(mf01_mt455_data);

        mf01_mt455_data.clear();
      }
    }
    else if( mt_no == 456 )
    {
      MF01MT456Parser mf01_mt456_data = endf_obj_add.get_mf01_mt456_data();

      ori_flg = endf_obj_ori.get_mf01_mt456_data().get_mat_no();
      mod_flg = mf01_mt456_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf01_mt456_data.set_mat_no(mat_ori);
        mf01_mt456_data.set_ZA(za_ori);
        mf01_mt456_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf01_mt456_data(mf01_mt456_data);

        mf01_mt456_data.clear();
      }
    }
    else if( mt_no == 458 )
    {
      MF01MT458Parser mf01_mt458_data = endf_obj_add.get_mf01_mt458_data();

      ori_flg = endf_obj_ori.get_mf01_mt458_data().get_mat_no();
      mod_flg = mf01_mt458_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf01_mt458_data.set_mat_no(mat_ori);
        mf01_mt458_data.set_ZA(za_ori);
        mf01_mt458_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf01_mt458_data(mf01_mt458_data);

        mf01_mt458_data.clear();
      }
    }
    else if( mt_no == 460 )
    {
      MF01MT460Parser mf01_mt460_data = endf_obj_add.get_mf01_mt460_data();

      ori_flg = endf_obj_ori.get_mf01_mt460_data().get_mat_no();
      mod_flg = mf01_mt460_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf01_mt460_data.set_mat_no(mat_ori);
        mf01_mt460_data.set_ZA(za_ori);
        mf01_mt460_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf01_mt460_data(mf01_mt460_data);

        mf01_mt460_data.clear();
      }
    }
  }
  else if( mf_no == 2 )
  {
    if( mt_no == 151 )
    {
      MF02MT151Parser mf02_mt151_data = endf_obj_add.get_mf02_mt151_data();

      ori_flg = endf_obj_ori.get_mf02_mt151_data().get_mat_no();
      mod_flg = mf02_mt151_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf02_mt151_data.set_mat_no(mat_ori);
        mf02_mt151_data.set_ZAR(za_ori);
        mf02_mt151_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf02_mt151_data(mf02_mt151_data);

        mf02_mt151_data.clear();
      }
    }
    else if( mt_no == 152 )
    {
      MF02MT152Parser mf02_mt152_data = endf_obj_add.get_mf02_mt152_data();

      ori_flg = endf_obj_ori.get_mf02_mt152_data().get_mat_no();
      mod_flg = mf02_mt152_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf02_mt152_data.set_mat_no(mat_ori);
        mf02_mt152_data.set_ZAR(za_ori);
        mf02_mt152_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf02_mt152_data(mf02_mt152_data);

        mf02_mt152_data.clear();
      }
    }
    else if( mt_no == 153 )
    {
      MF02MT153Parser mf02_mt153_data = endf_obj_add.get_mf02_mt153_data();

      ori_flg = endf_obj_ori.get_mf02_mt153_data().get_mat_no();
      mod_flg = mf02_mt153_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf02_mt153_data.set_mat_no(mat_ori);
        mf02_mt153_data.set_ZAR(za_ori);
        mf02_mt153_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf02_mt153_data(mf02_mt153_data);

        mf02_mt153_data.clear();
      }
    }
  }
  else if( mf_no == 3 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF03Parser> mf03_data_ori = endf_obj_ori.get_mf03_data();
    vector<MF03Parser> mf03_data_add = endf_obj_add.get_mf03_data();
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
      vector<MF03Parser> mf03_data;
      for(int i=0; i<static_cast<int>(mf03_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf03_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf03_data_add[mod_flg].set_mat_no(mat_ori);
          mf03_data_add[mod_flg].set_ZA(za_ori);
          mf03_data_add[mod_flg].set_AWR(awr_ori);
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

      endf_obj_ori.set_mf03_data(mf03_data);
      vector<MF03Parser>().swap(mf03_data);
    }

    vector<MF03Parser>().swap(mf03_data_ori);
    vector<MF03Parser>().swap(mf03_data_add);
  }
  else if( mf_no == 4 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF04Parser> mf04_data_ori = endf_obj_ori.get_mf04_data();
    vector<MF04Parser> mf04_data_add = endf_obj_add.get_mf04_data();
    for(int i=0; i<static_cast<int>(mf04_data_ori.size()); i++)
    {
      if( mf04_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf04_data_add.size()); i++)
    {
      if( mf04_data_add[i].get_mt_no() == mt_no )
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
      vector<MF04Parser> mf04_data;
      for(int i=0; i<static_cast<int>(mf04_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf04_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf04_data_add[mod_flg].set_mat_no(mat_ori);
          mf04_data_add[mod_flg].set_ZA(za_ori);
          mf04_data_add[mod_flg].set_AWR(awr_ori);
          mf04_data.push_back(mf04_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf04_data.push_back(mf04_data_ori[i]);
          }
        }
        else
        {
          mf04_data.push_back(mf04_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf04_data(mf04_data);
      vector<MF04Parser>().swap(mf04_data);
    }

    vector<MF04Parser>().swap(mf04_data_ori);
    vector<MF04Parser>().swap(mf04_data_add);
  }
  else if( mf_no == 5 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF05Parser> mf05_data_ori = endf_obj_ori.get_mf05_data();
    vector<MF05Parser> mf05_data_add = endf_obj_add.get_mf05_data();
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
      vector<MF05Parser> mf05_data;
      for(int i=0; i<static_cast<int>(mf05_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf05_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf05_data_add[mod_flg].set_mat_no(mat_ori);
          mf05_data_add[mod_flg].set_ZA(za_ori);
          mf05_data_add[mod_flg].set_AWR(awr_ori);
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

      endf_obj_ori.set_mf05_data(mf05_data);
      vector<MF05Parser>().swap(mf05_data);
    }

    vector<MF05Parser>().swap(mf05_data_ori);
    vector<MF05Parser>().swap(mf05_data_add);
  }
  else if( mf_no == 6 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF06Parser> mf06_data_ori = endf_obj_ori.get_mf06_data();
    vector<MF06Parser> mf06_data_add = endf_obj_add.get_mf06_data();
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
      vector<MF06Parser> mf06_data;
      for(int i=0; i<static_cast<int>(mf06_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf06_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf06_data_add[mod_flg].set_mat_no(mat_ori);
          mf06_data_add[mod_flg].set_ZA(za_ori);
          mf06_data_add[mod_flg].set_AWR(awr_ori);
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

      endf_obj_ori.set_mf06_data(mf06_data);
      vector<MF06Parser>().swap(mf06_data);
    }

    vector<MF06Parser>().swap(mf06_data_ori);
    vector<MF06Parser>().swap(mf06_data_add);
  }
  else if( mf_no == 7 )
  {
    if( mt_no == 2 )
    {
      MF07MT002Parser mf07_mt002_data = endf_obj_add.get_mf07_mt002_data();

      ori_flg = endf_obj_ori.get_mf07_mt002_data().get_mat_no();
      mod_flg = mf07_mt002_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf07_mt002_data.set_mat_no(mat_ori);
        mf07_mt002_data.set_ZA(za_ori);
        mf07_mt002_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf07_mt002_data(mf07_mt002_data);

        mf07_mt002_data.clear();
      }
    }
    else if( mt_no == 4 )
    {
      MF07MT004Parser mf07_mt004_data = endf_obj_add.get_mf07_mt004_data();

      ori_flg = endf_obj_ori.get_mf07_mt004_data().get_mat_no();
      mod_flg = mf07_mt004_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf07_mt004_data.set_mat_no(mat_ori);
        mf07_mt004_data.set_ZA(za_ori);
        mf07_mt004_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf07_mt004_data(mf07_mt004_data);

        mf07_mt004_data.clear();
      }
    }
  }
  else if( mf_no == 8 )
  {
    if( mt_no == 454 )
    {
      MF08MT454Parser mf08_mt454_data = endf_obj_add.get_mf08_mt454_data();

      ori_flg = endf_obj_ori.get_mf08_mt454_data().get_mat_no();
      mod_flg = mf08_mt454_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf08_mt454_data.set_mat_no(mat_ori);
        mf08_mt454_data.set_ZA(za_ori);
        mf08_mt454_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf08_mt454_data(mf08_mt454_data);

        mf08_mt454_data.clear();
      }
    }
    else if( mt_no == 457 )
    {
      MF08MT457Parser mf08_mt457_data = endf_obj_add.get_mf08_mt457_data();

      ori_flg = endf_obj_ori.get_mf08_mt457_data().get_mat_no();
      mod_flg = mf08_mt457_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf08_mt457_data.set_mat_no(mat_ori);
        mf08_mt457_data.set_ZA(za_ori);
        mf08_mt457_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf08_mt457_data(mf08_mt457_data);

        mf08_mt457_data.clear();
      }
    }
    else if( mt_no == 459 )
    {
      MF08MT459Parser mf08_mt459_data = endf_obj_add.get_mf08_mt459_data();

      ori_flg = endf_obj_ori.get_mf08_mt459_data().get_mat_no();
      mod_flg = mf08_mt459_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf08_mt459_data.set_mat_no(mat_ori);
        mf08_mt459_data.set_ZA(za_ori);
        mf08_mt459_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf08_mt459_data(mf08_mt459_data);

        mf08_mt459_data.clear();
      }
    }
    else
    {
      ori_flg = -1;
      mod_flg = -1;

      vector<MF08Parser> mf08_data_ori = endf_obj_ori.get_mf08_data();
      vector<MF08Parser> mf08_data_add = endf_obj_add.get_mf08_data();
      for(int i=0; i<static_cast<int>(mf08_data_ori.size()); i++)
      {
        if( mf08_data_ori[i].get_mt_no() == mt_no )
        {
          ori_flg = i;
          break;
        }
      }

      for(int i=0; i<static_cast<int>(mf08_data_add.size()); i++)
      {
        if( mf08_data_add[i].get_mt_no() == mt_no )
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
        vector<MF08Parser> mf08_data;
        for(int i=0; i<static_cast<int>(mf08_data_ori.size()); i++)
        {
          if( add_flg == 0 && ( i==ori_flg || mt_no < mf08_data_ori[i].get_mt_no() ) )
          {
            add_flg = 1;
            mf08_data_add[mod_flg].set_mat_no(mat_ori);
            mf08_data_add[mod_flg].set_ZA(za_ori);
            mf08_data_add[mod_flg].set_AWR(awr_ori);
            mf08_data.push_back(mf08_data_add[mod_flg]);
            if( i != ori_flg )
            {
              mf08_data.push_back(mf08_data_ori[i]);
            }
          }
          else
          {
            mf08_data.push_back(mf08_data_ori[i]);
          }
        }

        endf_obj_ori.set_mf08_data(mf08_data);
        vector<MF08Parser>().swap(mf08_data);
      }

      vector<MF08Parser>().swap(mf08_data_ori);
      vector<MF08Parser>().swap(mf08_data_add);
    }
  }
  else if( mf_no == 9 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF09Parser> mf09_data_ori = endf_obj_ori.get_mf09_data();
    vector<MF09Parser> mf09_data_add = endf_obj_add.get_mf09_data();
    for(int i=0; i<static_cast<int>(mf09_data_ori.size()); i++)
    {
      if( mf09_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf09_data_add.size()); i++)
    {
      if( mf09_data_add[i].get_mt_no() == mt_no )
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
      vector<MF09Parser> mf09_data;
      for(int i=0; i<static_cast<int>(mf09_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf09_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf09_data_add[mod_flg].set_mat_no(mat_ori);
          mf09_data_add[mod_flg].set_ZA(za_ori);
          mf09_data_add[mod_flg].set_AWR(awr_ori);
          mf09_data.push_back(mf09_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf09_data.push_back(mf09_data_ori[i]);
          }
        }
        else
        {
          mf09_data.push_back(mf09_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf09_data(mf09_data);
      vector<MF09Parser>().swap(mf09_data);
    }

    vector<MF09Parser>().swap(mf09_data_ori);
    vector<MF09Parser>().swap(mf09_data_add);
  }
  else if( mf_no == 10 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF10Parser> mf10_data_ori = endf_obj_ori.get_mf10_data();
    vector<MF10Parser> mf10_data_add = endf_obj_add.get_mf10_data();
    for(int i=0; i<static_cast<int>(mf10_data_ori.size()); i++)
    {
      if( mf10_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf10_data_add.size()); i++)
    {
      if( mf10_data_add[i].get_mt_no() == mt_no )
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
      vector<MF10Parser> mf10_data;
      for(int i=0; i<static_cast<int>(mf10_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf10_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf10_data_add[mod_flg].set_mat_no(mat_ori);
          mf10_data_add[mod_flg].set_ZA(za_ori);
          mf10_data_add[mod_flg].set_AWR(awr_ori);
          mf10_data.push_back(mf10_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf10_data.push_back(mf10_data_ori[i]);
          }
        }
        else
        {
          mf10_data.push_back(mf10_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf10_data(mf10_data);
      vector<MF10Parser>().swap(mf10_data);
    }

    vector<MF10Parser>().swap(mf10_data_ori);
    vector<MF10Parser>().swap(mf10_data_add);
  }
  else if( mf_no == 12 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF12Parser> mf12_data_ori = endf_obj_ori.get_mf12_data();
    vector<MF12Parser> mf12_data_add = endf_obj_add.get_mf12_data();
    for(int i=0; i<static_cast<int>(mf12_data_ori.size()); i++)
    {
      if( mf12_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf12_data_add.size()); i++)
    {
      if( mf12_data_add[i].get_mt_no() == mt_no )
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
      vector<MF12Parser> mf12_data;
      for(int i=0; i<static_cast<int>(mf12_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf12_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf12_data_add[mod_flg].set_mat_no(mat_ori);
          mf12_data_add[mod_flg].set_ZA(za_ori);
          mf12_data_add[mod_flg].set_AWR(awr_ori);
          mf12_data.push_back(mf12_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf12_data.push_back(mf12_data_ori[i]);
          }
        }
        else
        {
          mf12_data.push_back(mf12_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf12_data(mf12_data);
      vector<MF12Parser>().swap(mf12_data);
    }

    vector<MF12Parser>().swap(mf12_data_ori);
    vector<MF12Parser>().swap(mf12_data_add);
  }
  else if( mf_no == 13 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF13Parser> mf13_data_ori = endf_obj_ori.get_mf13_data();
    vector<MF13Parser> mf13_data_add = endf_obj_add.get_mf13_data();
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
      vector<MF13Parser> mf13_data;
      for(int i=0; i<static_cast<int>(mf13_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf13_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf13_data_add[mod_flg].set_mat_no(mat_ori);
          mf13_data_add[mod_flg].set_ZA(za_ori);
          mf13_data_add[mod_flg].set_AWR(awr_ori);
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

      endf_obj_ori.set_mf13_data(mf13_data);
      vector<MF13Parser>().swap(mf13_data);
    }

    vector<MF13Parser>().swap(mf13_data_ori);
    vector<MF13Parser>().swap(mf13_data_add);
  }
  else if( mf_no == 14 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF14Parser> mf14_data_ori = endf_obj_ori.get_mf14_data();
    vector<MF14Parser> mf14_data_add = endf_obj_add.get_mf14_data();
    for(int i=0; i<static_cast<int>(mf14_data_ori.size()); i++)
    {
      if( mf14_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf14_data_add.size()); i++)
    {
      if( mf14_data_add[i].get_mt_no() == mt_no )
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
      vector<MF14Parser> mf14_data;
      for(int i=0; i<static_cast<int>(mf14_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf14_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf14_data_add[mod_flg].set_mat_no(mat_ori);
          mf14_data_add[mod_flg].set_ZA(za_ori);
          mf14_data_add[mod_flg].set_AWR(awr_ori);
          mf14_data.push_back(mf14_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf14_data.push_back(mf14_data_ori[i]);
          }
        }
        else
        {
          mf14_data.push_back(mf14_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf14_data(mf14_data);
      vector<MF14Parser>().swap(mf14_data);
    }

    vector<MF14Parser>().swap(mf14_data_ori);
    vector<MF14Parser>().swap(mf14_data_add);
  }
  else if( mf_no == 15 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF15Parser> mf15_data_ori = endf_obj_ori.get_mf15_data();
    vector<MF15Parser> mf15_data_add = endf_obj_add.get_mf15_data();
    for(int i=0; i<static_cast<int>(mf15_data_ori.size()); i++)
    {
      if( mf15_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf15_data_add.size()); i++)
    {
      if( mf15_data_add[i].get_mt_no() == mt_no )
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
      vector<MF15Parser> mf15_data;
      for(int i=0; i<static_cast<int>(mf15_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf15_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf15_data_add[mod_flg].set_mat_no(mat_ori);
          mf15_data_add[mod_flg].set_ZA(za_ori);
          mf15_data_add[mod_flg].set_AWR(awr_ori);
          mf15_data.push_back(mf15_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf15_data.push_back(mf15_data_ori[i]);
          }
        }
        else
        {
          mf15_data.push_back(mf15_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf15_data(mf15_data);
      vector<MF15Parser>().swap(mf15_data);
    }

    vector<MF15Parser>().swap(mf15_data_ori);
    vector<MF15Parser>().swap(mf15_data_add);
  }
  else if( mf_no == 23 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF23Parser> mf23_data_ori = endf_obj_ori.get_mf23_data();
    vector<MF23Parser> mf23_data_add = endf_obj_add.get_mf23_data();
    for(int i=0; i<static_cast<int>(mf23_data_ori.size()); i++)
    {
      if( mf23_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf23_data_add.size()); i++)
    {
      if( mf23_data_add[i].get_mt_no() == mt_no )
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
      vector<MF23Parser> mf23_data;
      for(int i=0; i<static_cast<int>(mf23_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf23_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf23_data_add[mod_flg].set_mat_no(mat_ori);
          mf23_data_add[mod_flg].set_ZA(za_ori);
          mf23_data_add[mod_flg].set_AWR(awr_ori);
          mf23_data.push_back(mf23_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf23_data.push_back(mf23_data_ori[i]);
          }
        }
        else
        {
          mf23_data.push_back(mf23_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf23_data(mf23_data);
      vector<MF23Parser>().swap(mf23_data);
    }

    vector<MF23Parser>().swap(mf23_data_ori);
    vector<MF23Parser>().swap(mf23_data_add);
  }
  else if( mf_no == 26 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF26Parser> mf26_data_ori = endf_obj_ori.get_mf26_data();
    vector<MF26Parser> mf26_data_add = endf_obj_add.get_mf26_data();
    for(int i=0; i<static_cast<int>(mf26_data_ori.size()); i++)
    {
      if( mf26_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf26_data_add.size()); i++)
    {
      if( mf26_data_add[i].get_mt_no() == mt_no )
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
      vector<MF26Parser> mf26_data;
      for(int i=0; i<static_cast<int>(mf26_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf26_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf26_data_add[mod_flg].set_mat_no(mat_ori);
          mf26_data_add[mod_flg].set_ZA(za_ori);
          mf26_data_add[mod_flg].set_AWR(awr_ori);
          mf26_data.push_back(mf26_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf26_data.push_back(mf26_data_ori[i]);
          }
        }
        else
        {
          mf26_data.push_back(mf26_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf26_data(mf26_data);
      vector<MF26Parser>().swap(mf26_data);
    }

    vector<MF26Parser>().swap(mf26_data_ori);
    vector<MF26Parser>().swap(mf26_data_add);
  }
  else if( mf_no == 27 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF27Parser> mf27_data_ori = endf_obj_ori.get_mf27_data();
    vector<MF27Parser> mf27_data_add = endf_obj_add.get_mf27_data();
    for(int i=0; i<static_cast<int>(mf27_data_ori.size()); i++)
    {
      if( mf27_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf27_data_add.size()); i++)
    {
      if( mf27_data_add[i].get_mt_no() == mt_no )
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
      vector<MF27Parser> mf27_data;
      for(int i=0; i<static_cast<int>(mf27_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf27_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf27_data_add[mod_flg].set_mat_no(mat_ori);
          mf27_data_add[mod_flg].set_ZA(za_ori);
          mf27_data_add[mod_flg].set_AWR(awr_ori);
          mf27_data.push_back(mf27_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf27_data.push_back(mf27_data_ori[i]);
          }
        }
        else
        {
          mf27_data.push_back(mf27_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf27_data(mf27_data);
      vector<MF27Parser>().swap(mf27_data);
    }

    vector<MF27Parser>().swap(mf27_data_ori);
    vector<MF27Parser>().swap(mf27_data_add);
  }
  else if( mf_no == 28 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF28Parser> mf28_data_ori = endf_obj_ori.get_mf28_data();
    vector<MF28Parser> mf28_data_add = endf_obj_add.get_mf28_data();
    for(int i=0; i<static_cast<int>(mf28_data_ori.size()); i++)
    {
      if( mf28_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf28_data_add.size()); i++)
    {
      if( mf28_data_add[i].get_mt_no() == mt_no )
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
      vector<MF28Parser> mf28_data;
      for(int i=0; i<static_cast<int>(mf28_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf28_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf28_data_add[mod_flg].set_mat_no(mat_ori);
          mf28_data_add[mod_flg].set_ZA(za_ori);
          mf28_data_add[mod_flg].set_AWR(awr_ori);
          mf28_data.push_back(mf28_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf28_data.push_back(mf28_data_ori[i]);
          }
        }
        else
        {
          mf28_data.push_back(mf28_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf28_data(mf28_data);
      vector<MF28Parser>().swap(mf28_data);
    }

    vector<MF28Parser>().swap(mf28_data_ori);
    vector<MF28Parser>().swap(mf28_data_add);
  }
  else if( mf_no == 30 )
  {
    if( mt_no == 1 )
    {
      MF30MT001Parser mf30_mt001_data = endf_obj_add.get_mf30_mt001_data();

      ori_flg = endf_obj_ori.get_mf30_mt001_data().get_mat_no();
      mod_flg = mf30_mt001_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf30_mt001_data.set_mat_no(mat_ori);
        mf30_mt001_data.set_ZA(za_ori);
        mf30_mt001_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf30_mt001_data(mf30_mt001_data);

        mf30_mt001_data.clear();
      }
    }
    else if( mt_no == 2 )
    {
      MF30MT002Parser mf30_mt002_data = endf_obj_add.get_mf30_mt002_data();

      ori_flg = endf_obj_ori.get_mf30_mt002_data().get_mat_no();
      mod_flg = mf30_mt002_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf30_mt002_data.set_mat_no(mat_ori);
        mf30_mt002_data.set_ZA(za_ori);
        mf30_mt002_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf30_mt002_data(mf30_mt002_data);

        mf30_mt002_data.clear();
      }
    }
  }
  else if( mf_no == 31 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF31Parser> mf31_data_ori = endf_obj_ori.get_mf31_data();
    vector<MF31Parser> mf31_data_add = endf_obj_add.get_mf31_data();
    for(int i=0; i<static_cast<int>(mf31_data_ori.size()); i++)
    {
      if( mf31_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf31_data_add.size()); i++)
    {
      if( mf31_data_add[i].get_mt_no() == mt_no )
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
      vector<MF31Parser> mf31_data;
      for(int i=0; i<static_cast<int>(mf31_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf31_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf31_data_add[mod_flg].set_mat_no(mat_ori);
          mf31_data_add[mod_flg].set_ZA(za_ori);
          mf31_data_add[mod_flg].set_AWR(awr_ori);
          mf31_data.push_back(mf31_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf31_data.push_back(mf31_data_ori[i]);
          }
        }
        else
        {
          mf31_data.push_back(mf31_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf31_data(mf31_data);
      vector<MF31Parser>().swap(mf31_data);
    }

    vector<MF31Parser>().swap(mf31_data_ori);
    vector<MF31Parser>().swap(mf31_data_add);
  }
  else if( mf_no == 32 )
  {
    if( mt_no == 151 )
    {
      MF32MT151Parser mf32_mt151_data = endf_obj_add.get_mf32_mt151_data();

      ori_flg = endf_obj_ori.get_mf32_mt151_data().get_mat_no();
      mod_flg = mf32_mt151_data.get_mat_no();

      if( mod_flg == unassigned_mat_no )
      {
        no_data_flg = 1;
      }
      else
      {
        mf32_mt151_data.set_mat_no(mat_ori);
        mf32_mt151_data.set_ZAR(za_ori);
        mf32_mt151_data.set_AWR(awr_ori);

        endf_obj_ori.set_mf32_mt151_data(mf32_mt151_data);

        mf32_mt151_data.clear();
      }
    }
  }
  else if( mf_no == 33 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF33Parser> mf33_data_ori = endf_obj_ori.get_mf33_data();
    vector<MF33Parser> mf33_data_add = endf_obj_add.get_mf33_data();
    for(int i=0; i<static_cast<int>(mf33_data_ori.size()); i++)
    {
      if( mf33_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf33_data_add.size()); i++)
    {
      if( mf33_data_add[i].get_mt_no() == mt_no )
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
      vector<MF33Parser> mf33_data;
      for(int i=0; i<static_cast<int>(mf33_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf33_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf33_data_add[mod_flg].set_mat_no(mat_ori);
          mf33_data_add[mod_flg].set_ZA(za_ori);
          mf33_data_add[mod_flg].set_AWR(awr_ori);
          mf33_data.push_back(mf33_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf33_data.push_back(mf33_data_ori[i]);
          }
        }
        else
        {
          mf33_data.push_back(mf33_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf33_data(mf33_data);
      vector<MF33Parser>().swap(mf33_data);
    }

    vector<MF33Parser>().swap(mf33_data_ori);
    vector<MF33Parser>().swap(mf33_data_add);
  }
  else if( mf_no == 34 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF34Parser> mf34_data_ori = endf_obj_ori.get_mf34_data();
    vector<MF34Parser> mf34_data_add = endf_obj_add.get_mf34_data();
    for(int i=0; i<static_cast<int>(mf34_data_ori.size()); i++)
    {
      if( mf34_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf34_data_add.size()); i++)
    {
      if( mf34_data_add[i].get_mt_no() == mt_no )
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
      vector<MF34Parser> mf34_data;
      for(int i=0; i<static_cast<int>(mf34_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf34_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf34_data_add[mod_flg].set_mat_no(mat_ori);
          mf34_data_add[mod_flg].set_ZA(za_ori);
          mf34_data_add[mod_flg].set_AWR(awr_ori);
          mf34_data.push_back(mf34_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf34_data.push_back(mf34_data_ori[i]);
          }
        }
        else
        {
          mf34_data.push_back(mf34_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf34_data(mf34_data);
      vector<MF34Parser>().swap(mf34_data);
    }

    vector<MF34Parser>().swap(mf34_data_ori);
    vector<MF34Parser>().swap(mf34_data_add);
  }
  else if( mf_no == 35 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF35Parser> mf35_data_ori = endf_obj_ori.get_mf35_data();
    vector<MF35Parser> mf35_data_add = endf_obj_add.get_mf35_data();
    for(int i=0; i<static_cast<int>(mf35_data_ori.size()); i++)
    {
      if( mf35_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf35_data_add.size()); i++)
    {
      if( mf35_data_add[i].get_mt_no() == mt_no )
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
      vector<MF35Parser> mf35_data;
      for(int i=0; i<static_cast<int>(mf35_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf35_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf35_data_add[mod_flg].set_mat_no(mat_ori);
          mf35_data_add[mod_flg].set_ZA(za_ori);
          mf35_data_add[mod_flg].set_AWR(awr_ori);
          mf35_data.push_back(mf35_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf35_data.push_back(mf35_data_ori[i]);
          }
        }
        else
        {
          mf35_data.push_back(mf35_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf35_data(mf35_data);
      vector<MF35Parser>().swap(mf35_data);
    }

    vector<MF35Parser>().swap(mf35_data_ori);
    vector<MF35Parser>().swap(mf35_data_add);
  }
  else if( mf_no == 40 )
  {
    ori_flg = -1;
    mod_flg = -1;

    vector<MF40Parser> mf40_data_ori = endf_obj_ori.get_mf40_data();
    vector<MF40Parser> mf40_data_add = endf_obj_add.get_mf40_data();
    for(int i=0; i<static_cast<int>(mf40_data_ori.size()); i++)
    {
      if( mf40_data_ori[i].get_mt_no() == mt_no )
      {
        ori_flg = i;
        break;
      }
    }

    for(int i=0; i<static_cast<int>(mf40_data_add.size()); i++)
    {
      if( mf40_data_add[i].get_mt_no() == mt_no )
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
      vector<MF40Parser> mf40_data;
      for(int i=0; i<static_cast<int>(mf40_data_ori.size()); i++)
      {
        if( add_flg == 0 && ( i==ori_flg || mt_no < mf40_data_ori[i].get_mt_no() ) )
        {
          add_flg = 1;
          mf40_data_add[mod_flg].set_mat_no(mat_ori);
          mf40_data_add[mod_flg].set_ZA(za_ori);
          mf40_data_add[mod_flg].set_AWR(awr_ori);
          mf40_data.push_back(mf40_data_add[mod_flg]);
          if( i != ori_flg )
          {
            mf40_data.push_back(mf40_data_ori[i]);
          }
        }
        else
        {
          mf40_data.push_back(mf40_data_ori[i]);
        }
      }

      endf_obj_ori.set_mf40_data(mf40_data);
      vector<MF40Parser>().swap(mf40_data);
    }

    vector<MF40Parser>().swap(mf40_data_ori);
    vector<MF40Parser>().swap(mf40_data_add);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::merge_specified_MF_MT_data
                      (Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add, Integer mf_no, Integer mt_no,
                       int& ori_flg, int& mod_flg)
{
  int no_data_flg = 0;
  merge_specified_MF_MT_data_without_error_message
    (endf_obj_ori, endf_obj_add, mf_no, mt_no, ori_flg, mod_flg, no_data_flg);

  if( no_data_flg == 1 )
  {
    string class_name = "Endf6Modifier";
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
    err_com.push_back("Please check your input file or nuclear data files.");

    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::change_specified_MF_MT_data
                      (NuclearDataObject& nucl_obj_ori, NuclearDataObject& nucl_obj_add, Integer mf_no, Integer mt_no)
{
  Endf6Parser endf_obj_ori, endf_obj_add;
  endf_conv_obj.convert_frendy_to_endf_format(nucl_obj_ori, endf_obj_ori);
  endf_conv_obj.convert_frendy_to_endf_format(nucl_obj_add, endf_obj_add);

  change_specified_MF_MT_data(endf_obj_ori, endf_obj_add, mf_no, mt_no);

  endf_conv_obj.convert_endf_format_to_frendy(endf_obj_ori, nucl_obj_ori);
  endf_obj_ori.clear();
  endf_obj_add.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::change_specified_MF_MT_data
                      (Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add, Integer mf_no, Integer mt_no)
{
  int ori_flg = -1;
  int mod_flg = -1;
  merge_specified_MF_MT_data(endf_obj_ori, endf_obj_add, mf_no, mt_no, ori_flg, mod_flg);

  if( ori_flg < 0 || ori_flg == unassigned_mat_no )
  {
    string class_name = "Endf6Modifier";
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
    err_com.push_back("Please check your input file or nuclear data files.");

    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::add_specified_MF_MT_data
                      (NuclearDataObject& nucl_obj_ori, NuclearDataObject& nucl_obj_add, Integer mf_no, Integer mt_no)
{
  Endf6Parser endf_obj_ori, endf_obj_add;
  endf_conv_obj.convert_frendy_to_endf_format(nucl_obj_ori, endf_obj_ori);
  endf_conv_obj.convert_frendy_to_endf_format(nucl_obj_add, endf_obj_add);

  add_specified_MF_MT_data(endf_obj_ori, endf_obj_add, mf_no, mt_no);

  endf_conv_obj.convert_endf_format_to_frendy(endf_obj_ori, nucl_obj_ori);
  endf_obj_ori.clear();
  endf_obj_add.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Modifier::add_specified_MF_MT_data
                      (Endf6Parser& endf_obj_ori, Endf6Parser& endf_obj_add, Integer mf_no, Integer mt_no)
{
  int ori_flg = -1;
  int mod_flg = -1;
  merge_specified_MF_MT_data(endf_obj_ori, endf_obj_add, mf_no, mt_no, ori_flg, mod_flg);

  if( ori_flg >= 0 && ori_flg != unassigned_mat_no )
  {
    string class_name = "Endf6Modifier";
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
    err_com.push_back("Please check your input file or nuclear data files.");

    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

