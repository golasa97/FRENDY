#include "EndfUtils/Endf6Writer/Endf6Writer.hpp"

using namespace frendy;

//constructor
Endf6Writer::Endf6Writer(void)
{
  dummy_label = "PENDF FIlE WRITTEN BY FRENDY";
  clear();
}

//destructor
Endf6Writer::~Endf6Writer(void)
{
  dummy_label.clear();
  clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

const int Endf6Writer::no_clear_comment_data;
const int Endf6Writer::clear_comment_data;

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::write_pendf(string file_name)
{
  if( pendf_label_flg == 0 )
  {
    pendf_label = file_name;
  }

  vector<string> text = get_endf_text_data();

  //Write to pendf file
  ofstream fout;
  fout.open(file_name.c_str());

  if( fout.fail() )
  {
    string class_name = "Endf6Writer";
    string func_name  = "write_pendf(string file_name)";

    string str_data = "  Output file name : " + file_name;

    vector<string> err_com;
    err_com.push_back("Output file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  
  int i_max = static_cast<int>(text.size());
  for(int i=0; i<i_max; i++)
  {
    fout << text[i] << endl;
  }
  fout.close();

  clr_obj.clear_vec_array1_str(text);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::write_pendf_with_tape_end(string file_name)
{
  if( pendf_label_flg == 0 )
  {
    pendf_label = file_name;
  }

  vector<string> text = get_endf_text_data();

  //Write to pendf file
  ofstream fout;
  fout.open(file_name.c_str());

  if( fout.fail() )
  {
    string class_name = "Endf6Writer";
    string func_name  = "write_pendf_with_tape_end(string file_name)";

    string str_data = "  Output file name : " + file_name;

    vector<string> err_com;
    err_com.push_back("Output file can not be open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    err_com.push_back(str_data);

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = static_cast<int>(text.size());
  for(int i=0; i<i_max; i++)
  {
    fout << text[i] << endl;
  }

  //Write tape end
  fout <<  efw_obj.write_tape_end() << endl;
  fout.close();

  clr_obj.clear_vec_array1_str(text);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::convert_pendf_data(vector<string>& text)
{
  vector<string> text_tmp;
  clr_obj.clear_vec_array1_str(text);
  clr_obj.clear_vec_array1_str(text_tmp);
  
  line_no.clear();
  mf_list.clear();
  mt_list.clear();
  
  efw_obj.set_mat(mat_no);

  //Convert to text data
  //Write MF01
  if( mf01mt451_par.get_ZA() > 0.0 || mf01mt452_par.get_ZA() > 0.0 || mf01mt455_par.get_ZA() ||
      mf01mt456_par.get_ZA() > 0.0 || mf01mt458_par.get_ZA() > 0.0 || mf01mt460_par.get_ZA() )
  {
    //Write MT451
    if( mf01mt451_par.get_ZA() > 0.0 )
    {
      write_mf01mt451(text_tmp);
      add_text_data(text, text_tmp);
      mf_list.push_back(1);
      mt_list.push_back(451);

      clr_obj.clear_vec_array1_str(text); //MF01MT451 is added after.
    }

    //Write MT452
    if( mf01mt452_par.get_ZA() > 0.0 )
    {
      text_tmp = mf01mt452_wri.get_endf_text_data(mf01mt452_par);
      add_text_data(text, text_tmp);
      mf_list.push_back(1);
      mt_list.push_back(452);
    }

    //Write MT455
    if( mf01mt455_par.get_ZA() > 0.0 )
    {
      text_tmp = mf01mt455_wri.get_endf_text_data(mf01mt455_par);
      add_text_data(text, text_tmp);
      mf_list.push_back(1);
      mt_list.push_back(455);
    }

    //Write MT456
    if( mf01mt456_par.get_ZA() > 0.0 )
    {
      text_tmp = mf01mt456_wri.get_endf_text_data(mf01mt456_par);
      add_text_data(text, text_tmp);
      mf_list.push_back(1);
      mt_list.push_back(456);
    }

    //Write MT458
    if( mf01mt458_par.get_ZA() > 0.0 )
    {
      text_tmp = mf01mt458_wri.get_endf_text_data(mf01mt458_par);
      add_text_data(text, text_tmp);
      mf_list.push_back(1);
      mt_list.push_back(458);
    }

    //Write MT460
    if( mf01mt460_par.get_ZA() > 0.0 )
    {
      text_tmp = mf01mt460_wri.get_endf_text_data(mf01mt460_par);
      add_text_data(text, text_tmp);
      mf_list.push_back(1);
      mt_list.push_back(460);
    }

    add_file_end(text, 1, 1);
  }
  
  //Write MF02
  if( mf02mt151_par.get_ZAR() > 0.0 || mf02mt152_par.get_ZAR() > 0.0 || mf02mt153_par.get_ZAR() > 0.0 )
  {
    //Write MT151
    if( mf02mt151_par.get_ZAR() > 0.0 )
    {
      text_tmp = mf02mt151_wri.get_endf_text_data(mf02mt151_par);
      add_text_data(text, text_tmp);
      mf_list.push_back(2);
      mt_list.push_back(151);
    }
  
    //Write MT152
    if( mf02mt152_par.get_ZAR() > 0.0 )
    {
      text_tmp = mf02mt152_wri.get_endf_text_data(mf02mt152_par);
      add_text_data(text, text_tmp);
      mf_list.push_back(2);
      mt_list.push_back(152);
    }
  
    //Write MT153
    if( mf02mt153_par.get_ZAR() > 0.0 )
    {
      text_tmp = mf02mt153_wri.get_endf_text_data(mf02mt153_par);
      add_text_data(text, text_tmp);
      mf_list.push_back(2);
      mt_list.push_back(153);
    }
    add_file_end(text, 2, 1);
  }
  
  //Write MF03
  int i_max = static_cast<int>(mf03_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf03_wri.get_endf_text_data(mf03_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(3);
      mt_list.push_back(mf03_par[i].get_mt_no());
    }
    add_file_end(text, 3, 1);
  }

  //Write MF04
  i_max = static_cast<int>(mf04_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf04_wri.get_endf_text_data(mf04_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(4);
      mt_list.push_back(mf04_par[i].get_mt_no());
    }
    add_file_end(text, 4, 1);
  }

  //Write MF05
  i_max = static_cast<int>(mf05_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf05_wri.get_endf_text_data(mf05_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(5);
      mt_list.push_back(mf05_par[i].get_mt_no());
    }
    add_file_end(text, 5, 1);
  }

  //Write MF06
  i_max = static_cast<int>(mf06_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf06_wri.get_endf_text_data(mf06_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(6);
      mt_list.push_back(mf06_par[i].get_mt_no());
    }
    add_file_end(text, 6, 1);
  }

  //Write MF07
  if( mf07mt002_par.get_ZA() > 0.0 || mf07mt004_par.get_ZA() > 0.0 || mf07mt451_par.get_ZA() > 0.0 )
  {
    //Write MT002
    if( mf07mt002_par.get_ZA() > 0.0 )
    {
      text_tmp = mf07mt002_wri.get_endf_text_data(mf07mt002_par);
      add_text_data(text, text_tmp);
      mf_list.push_back(7);
      mt_list.push_back(2);
    }
  
    //Write MT004
    if( mf07mt004_par.get_ZA() > 0.0 )
    {
      text_tmp = mf07mt004_wri.get_endf_text_data(mf07mt004_par);
      add_text_data(text, text_tmp);
      mf_list.push_back(7);
      mt_list.push_back(4);
    }
  
    //Write MT451
    if( mf07mt451_par.get_ZA() > 0.0 )
    {
      text_tmp = mf07mt451_wri.get_endf_text_data(mf07mt451_par);
      add_text_data(text, text_tmp);
      mf_list.push_back(7);
      mt_list.push_back(451);
    }
    add_file_end(text, 7, 1);
  }

  //Write MF08
  i_max = static_cast<int>(mf08_par.size());
  if( i_max > 0 ||
      mf08mt454_par.get_ZA() > 0.0 || mf08mt457_par.get_ZA() > 0.0 || mf08mt459_par.get_ZA() > 0.0 )
  {
    if( i_max > 0 )
    {
      int mt454_flg = 1;
      if( mf08mt454_par.get_ZA() > 0.0 )
      {
        mt454_flg = 0;
      }

      int mt457_flg = 1;
      if( mf08mt457_par.get_ZA() > 0.0 )
      {
        mt457_flg = 0;
      }

      int mt459_flg = 1;
      if( mf08mt459_par.get_ZA() > 0.0 )
      {
        mt459_flg = 0;
      }

      for(int i=0; i<i_max; i++)
      {
        if( mt454_flg == 0 && mf08_par[i].get_mt_no() > 454 )
        {
          mt454_flg = 1;

          text_tmp = mf08mt454_wri.get_endf_text_data(mf08mt454_par);
          add_text_data(text, text_tmp);
          mf_list.push_back(8);
          mt_list.push_back(454);
        }

        if( mt457_flg == 0 && mf08_par[i].get_mt_no() > 457 )
        {
          mt457_flg = 1;

          text_tmp = mf08mt457_wri.get_endf_text_data(mf08mt457_par);
          add_text_data(text, text_tmp);
          mf_list.push_back(8);
          mt_list.push_back(457);
        }

        if( mt459_flg == 0 && mf08_par[i].get_mt_no() > 459 )
        {
          mt459_flg = 1;

          text_tmp = mf08mt459_wri.get_endf_text_data(mf08mt459_par);
          add_text_data(text, text_tmp);
          mf_list.push_back(8);
          mt_list.push_back(459);
        }

        text_tmp = mf08_wri.get_endf_text_data(mf08_par[i]);
        add_text_data(text, text_tmp);
        mf_list.push_back(8);
        mt_list.push_back(mf08_par[i].get_mt_no());
      }
    }
    else
    {
      //Write MT454
      if( mf08mt454_par.get_ZA() > 0.0 )
      {
        text_tmp = mf08mt454_wri.get_endf_text_data(mf08mt454_par);
        add_text_data(text, text_tmp);
        mf_list.push_back(8);
        mt_list.push_back(454);
      }

      //Write MT457
      if( mf08mt457_par.get_ZA() > 0.0 )
      {
        text_tmp = mf08mt457_wri.get_endf_text_data(mf08mt457_par);
        add_text_data(text, text_tmp);
        mf_list.push_back(8);
        mt_list.push_back(457);
      }

      //Write MT459
      if( mf08mt459_par.get_ZA() > 0.0 )
      {
        text_tmp = mf08mt459_wri.get_endf_text_data(mf08mt459_par);
        add_text_data(text, text_tmp);
        mf_list.push_back(8);
        mt_list.push_back(459);
      }
    }
    add_file_end(text, 8, 1);
  }

  //Write MF09
  i_max = static_cast<int>(mf09_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf09_wri.get_endf_text_data(mf09_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(9);
      mt_list.push_back(mf09_par[i].get_mt_no());
    }
    add_file_end(text, 9, 1);
  }
  
  //Write MF10
  i_max = static_cast<int>(mf10_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf10_wri.get_endf_text_data(mf10_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(10);
      mt_list.push_back(mf10_par[i].get_mt_no());
    }
    add_file_end(text, 10, 1);
  }
  
  //Write MF12
  i_max = static_cast<int>(mf12_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf12_wri.get_endf_text_data(mf12_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(12);
      mt_list.push_back(mf12_par[i].get_mt_no());
    }
    add_file_end(text, 12, 1);
  }
  
  //Write MF13
  i_max = static_cast<int>(mf13_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf13_wri.get_endf_text_data(mf13_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(13);
      mt_list.push_back(mf13_par[i].get_mt_no());
    }
    add_file_end(text, 13, 1);
  }
  
  //Write MF14
  i_max = static_cast<int>(mf14_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf14_wri.get_endf_text_data(mf14_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(14);
      mt_list.push_back(mf14_par[i].get_mt_no());
    }
    add_file_end(text, 14, 1);
  }
  
  //Write MF15
  i_max = static_cast<int>(mf15_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf15_wri.get_endf_text_data(mf15_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(15);
      mt_list.push_back(mf15_par[i].get_mt_no());
    }
    add_file_end(text, 15, 1);
  }
  
  //Write MF23
  i_max = static_cast<int>(mf23_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf23_wri.get_endf_text_data(mf23_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(23);
      mt_list.push_back(mf23_par[i].get_mt_no());
    }
    add_file_end(text, 23, 1);
  }
  
  //Write MF26
  i_max = static_cast<int>(mf26_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf26_wri.get_endf_text_data(mf26_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(26);
      mt_list.push_back(mf26_par[i].get_mt_no());
    }
    add_file_end(text, 26, 1);
  }
  
  //Write MF27
  i_max = static_cast<int>(mf27_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf27_wri.get_endf_text_data(mf27_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(27);
      mt_list.push_back(mf27_par[i].get_mt_no());
    }
    add_file_end(text, 27, 1);
  }
  
  //Write MF28
  i_max = static_cast<int>(mf28_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf28_wri.get_endf_text_data(mf28_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(28);
      mt_list.push_back(mf28_par[i].get_mt_no());
    }
    add_file_end(text, 28, 1);
  }
  
  //Write MF30
  if( mf30mt001_par.get_ZA() > 0.0 || mf30mt002_par.get_ZA() > 0.0 )
  {
    //Write MT001
    if( mf30mt001_par.get_ZA() > 0.0 )
    {
      if( static_cast<int>(mf30mt001_par.get_MP_NDIR().size())    > 0 ||
          static_cast<int>(mf30mt001_par.get_MFSEN_NDIR().size()) > 0 ||
          static_cast<int>(mf30mt001_par.get_MTSEN_NDIR().size()) > 0 ||
          static_cast<int>(mf30mt001_par.get_NC_NDIR().size())    > 0 ||
          static_cast<int>(mf30mt001_par.get_MP_NCTAB().size())   > 0 ||
          static_cast<int>(mf30mt001_par.get_LIBF_NCTAB().size()) > 0 ||
          static_cast<int>(mf30mt001_par.get_MATF_NCTAB().size()) > 0 ||
          static_cast<int>(mf30mt001_par.get_MPF_NCTAB().size())  > 0 )
      {
        text_tmp = mf30mt001_wri.get_endf_text_data(mf30mt001_par);
        add_text_data(text, text_tmp);
        mf_list.push_back(30);
        mt_list.push_back( 1);
      }
    }
  
    //Write MT002
    if( mf30mt002_par.get_ZA() > 0.0 )
    {
      text_tmp = mf30mt002_wri.get_endf_text_data(mf30mt002_par);
      add_text_data(text, text_tmp);
      mf_list.push_back(30);
      mt_list.push_back( 2);
    }
    add_file_end(text, 30, 1);
  }

  //Write MF31
  i_max = static_cast<int>(mf31_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf31_wri.get_endf_text_data(mf31_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(31);
      mt_list.push_back(mf31_par[i].get_mt_no());
    }
    add_file_end(text, 31, 1);
  }
  
  //Write MF32MT151
  if( mf32mt151_par.get_ZAR() > 0.0 )
  {
    text_tmp = mf32mt151_wri.get_endf_text_data(mf32mt151_par);
    add_text_data(text, text_tmp);
    mf_list.push_back( 32);
    mt_list.push_back(151);
  }
  
  //Write MF33
  i_max = static_cast<int>(mf33_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf33_wri.get_endf_text_data(mf33_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(33);
      mt_list.push_back(mf33_par[i].get_mt_no());
    }
    add_file_end(text, 33, 1);
  }
  
  //Write MF34
  i_max = static_cast<int>(mf34_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf34_wri.get_endf_text_data(mf34_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(34);
      mt_list.push_back(mf34_par[i].get_mt_no());
    }
    add_file_end(text, 34, 1);
  }
  
  //Write MF35
  i_max = static_cast<int>(mf35_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf35_wri.get_endf_text_data(mf35_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(35);
      mt_list.push_back(mf35_par[i].get_mt_no());
    }
    add_file_end(text, 35, 1);
  }
  
  //Write MF40
  i_max = static_cast<int>(mf40_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      text_tmp = mf40_wri.get_endf_text_data(mf40_par[i]);
      add_text_data(text, text_tmp);
      mf_list.push_back(40);
      mt_list.push_back(mf40_par[i].get_mt_no());
    }
    add_file_end(text, 40, 1);
  }
  
  if( modify_endf_flg == 0 || add_comment_flg >= 0 )
  {
    //Modify NC ad MF01MT451
    modify_mf01mt451();
  }

  combine_all_text(text);
  line_no.clear();
  mf_list.clear();
  mt_list.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::add_text_data(vector<string>& text, vector<string>& text_add)
{
  int i_max = static_cast<int>(text_add.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(text_add[i]);
  }
  line_no.push_back(static_cast<Integer>(text_add.size()) - 1); //erase SEND card
  
  clr_obj.clear_vec_array1_str(text_add);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::add_file_end(vector<string>& text, Integer mf_no, Integer mt_no)
{
  efw_obj.set_mf_mt(mf_no, mt_no);
  text.push_back(efw_obj.write_mf_end());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::write_mf01mt451(vector<string>& text)
{
  if( modify_endf_flg == 0 )
  {
    mf01mt451_par_mod = mf01mt451_par;
    
    Integer nlib = 0;
    Integer nmod = 0;
    
    mf01mt451_par_mod.set_NLIB(nlib);
    mf01mt451_par_mod.set_NMOD(nmod);
    
    add_mf_mt_mf01mt451();

    if( clear_comment_flg == clear_comment_data )
    {
      clear_comment_mf01mt451();
    }
  }
  
  if( add_comment_flg >= 1 )
  {
    clear_comment_mf01mt451();
    add_comment_mf01mt451();
  }
  
  text = mf01mt451_wri.get_endf_text_data(mf01mt451_par_mod);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::add_mf_mt_mf01mt451()
{
  vector<Integer> mf, mt, nc, mod;
  vector<Integer> mf_ori  = mf01mt451_par.get_MF();
  vector<Integer> mt_ori  = mf01mt451_par.get_MT();
  vector<Integer> nc_ori  = mf01mt451_par.get_NC();
  vector<Integer> mod_ori = mf01mt451_par.get_MOD();
  
  int i_max = static_cast<int>(mf_ori.size());
  Integer add_flg       = 0;
  Integer mf02mt152_flg = 0;
  Integer mf02mt153_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    add_flg = 0;
    if( mf_ori[i] == 1 && (mt_ori[i] == 451 || mt_ori[i] == 452 || mt_ori[i] == 455 ||
                           mt_ori[i] == 456 || mt_ori[i] == 458 || mt_ori[i] == 460 ) )
    {
      add_flg = 1;
    }
    else if( mf_ori[i] ==  2 && mt_ori[i] == 151 )
    {
      add_flg = 2;
    }
    else if( mf_ori[i] ==  3 || mf_ori[i] ==  4 || mf_ori[i] ==  5 || mf_ori[i] ==  6 ||
             mf_ori[i] ==  8 || mf_ori[i] ==  9 || mf_ori[i] == 10 || mf_ori[i] == 12 ||
             mf_ori[i] == 13 || mf_ori[i] == 14 || mf_ori[i] == 15 || mf_ori[i] == 23 ||
             mf_ori[i] == 26 || mf_ori[i] == 27 || mf_ori[i] == 28 || mf_ori[i] == 31 ||
             mf_ori[i] == 33 || mf_ori[i] == 34 || mf_ori[i] == 35 || mf_ori[i] == 40 )
    {
      add_flg = 3;
    }
    else if( mf_ori[i] ==  7 && (mt_ori[i] == 2 || mt_ori[i] == 4) )
    {
      add_flg = 7;
    }
    else if( mf_ori[i] == 30 && (mt_ori[i] == 1 || mt_ori[i] == 2) )
    {
      add_flg = 30;
    }
    else if( mf_ori[i] == 32 && mt_ori[i] == 151 )
    {
      add_flg = 32;
    }
    
    if( add_flg > 0 )
    {
      mf.push_back(mf_ori[i]);
      mt.push_back(mt_ori[i]);
      nc.push_back(nc_ori[i]);
      mod.push_back(mod_ori[i]);
    }
    else if( mf_ori[i] ==  2 && mt_ori[i] == 152 )
    {
      mf02mt152_flg = 1;
      mf.push_back(2);
      mt.push_back(152);
      nc.push_back(0);
      mod.push_back(0);
    }
    else if( mf_ori[i] ==  2 && mt_ori[i] == 153 )
    {
      mf02mt153_flg = 1;
      mf.push_back(2);
      mt.push_back(153);
      nc.push_back(0);
      mod.push_back(0);
    }
  }

  //Add MF02MT152 if mf01mt451_par.MF, MT, NC, MOD are not included MF02MT152
  if( mf02mt152_flg == 0 && mf02mt152_par.get_ZAR() > 0.0 )
  {
    i_max = static_cast<int>(mf.size()); 

    vector<Integer> mf_new, mt_new, nc_new, mod_new;
    Integer add_chk = 0;
    for(int i=0; i<i_max; i++)
    {
      mf_new.push_back(mf[i]);
      mt_new.push_back(mt[i]);
      nc_new.push_back(nc[i]);
      mod_new.push_back(mod[i]);

      if( mf[i] == 2 && mt[i] == 151 )
      {
        add_chk = 1;
        mf_new.push_back(2);
        mt_new.push_back(152);
        nc_new.push_back(0);
        mod_new.push_back(0);
      }
    }

    if( add_chk == 0 )
    {
      mf_new.push_back(2);
      mt_new.push_back(152);
      nc_new.push_back(0);
      mod_new.push_back(0);
    }

    mf  = mf_new;
    mt  = mt_new;
    nc  = nc_new;
    mod = mod_new;
    mf_new.clear();
    mt_new.clear();
    nc_new.clear();
    mod_new.clear();
  }

  //Add MF02MT153 if mf01mt451_par.MF, MT, NC, MOD are not included MF02MT153
  if( mf02mt153_flg == 0 && mf02mt153_par.get_ZAR() > 0.0 )
  {
    i_max = static_cast<int>(mf.size());

    vector<Integer> mf_new, mt_new, nc_new, mod_new;
    Integer add_chk = 0;
    for(int i=0; i<i_max; i++)
    {
      mf_new.push_back(mf[i]);
      mt_new.push_back(mt[i]);
      nc_new.push_back(nc[i]);
      mod_new.push_back(mod[i]);

      if( mf[i] == 2 && mt[i] == 151 )
      {
        add_chk = 1;
        mf_new.push_back(2);
        mt_new.push_back(153);
        nc_new.push_back(0);
        mod_new.push_back(0);
      }
    }

    if( add_chk == 0 )
    {
      mf_new.push_back(2);
      mt_new.push_back(153);
      nc_new.push_back(0);
      mod_new.push_back(0);
    }

    mf  = mf_new;
    mt  = mt_new;
    nc  = nc_new;
    mod = mod_new;
    mf_new.clear();
    mt_new.clear();
    nc_new.clear();
    mod_new.clear();
  }

  Integer nxc = static_cast<Integer>(mf.size());
  mf01mt451_par_mod.set_NXC(nxc);
  mf01mt451_par_mod.set_MF(mf);
  mf01mt451_par_mod.set_MT(mt);
  mf01mt451_par_mod.set_NC(nc);
  mf01mt451_par_mod.set_MOD(mod);
  
  //Clear vector
  mf_ori.clear();
  mt_ori.clear();
  nc_ori.clear();
  mod_ori.clear();
  mf.clear();
  mt.clear();
  nc.clear();
  mod.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::clear_comment_mf01mt451()
{
  Integer nwd = 0;
  mf01mt451_par_mod.set_NWD(nwd);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::add_comment_mf01mt451()
{
  //modify comment line
  vector<string> comment_line, comment_line_ori;
  clr_obj.clear_vec_array1_str(comment_line);
  comment_line_ori = mf01mt451_par_mod.get_comment_line();
  comment_line.push_back(comment_line_ori[0]);
  comment_line.push_back(comment_line_ori[1]);

  Integer  nwd = 2;
  if( add_comment_flg == 1 )
  {
    //add comment line
    int i_max = static_cast<int>(add_comment.size());
    for(int i=0; i<i_max; i++)
    {
      comment_line.push_back(add_comment[i]);
    }
  
    //modify NWD
    nwd += static_cast<Integer>(i_max);
  }
  mf01mt451_par_mod.set_comment_line(comment_line);
  mf01mt451_par_mod.set_NWD(nwd);
  clr_obj.clear_vec_array1_str(comment_line);
  clr_obj.clear_vec_array1_str(comment_line_ori);

  add_comment_flg = -1;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::modify_mf01mt451()
{
  //Modyfy MF, MT, NC and MOD at MF01MT451
  vector<Integer> mf_old  = mf01mt451_par.get_MF();
  vector<Integer> mt_old  = mf01mt451_par.get_MT();
  vector<Integer> mod_old = mf01mt451_par.get_MOD();

  int i_max = static_cast<int>(mf_list.size());
  int j_max = static_cast<int>(mf_old.size());
  vector<Integer> mod_list;
  mod_list.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    mod_list[i] = -1;
    for(int j=0; j<j_max; j++)
    {
      if( mf_list[i] == mf_old[j] )
      {
        if( mt_list[i] == mt_old[j] )
        {
          mod_list[i] = mod_old[j];
          break;
        }
      }
    }
  }
  
  Integer nxc = static_cast<Integer>(mf_list.size());
  mf01mt451_par_mod.set_NXC(nxc);
  mf01mt451_par_mod.set_MF(mf_list);
  mf01mt451_par_mod.set_MT(mt_list);
  mf01mt451_par_mod.set_NC(line_no);
  mf01mt451_par_mod.set_MOD(mod_list);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::combine_all_text(vector<string>& text)
{
  //Write modified MF01MT451
  vector<string> text_tmp = mf01mt451_wri.get_endf_text_data(mf01mt451_par_mod);
  
  //Update text
  vector<string> text_new;
  clr_obj.clear_vec_array1_str(text_new);

  //Write MF01MT451
  int i_max = static_cast<int>(text_tmp.size());
  for(int i=0; i<i_max; i++)
  {
    text_new.push_back(text_tmp[i]);
  }
  clr_obj.clear_vec_array1_str(text_tmp);

  //Add other data
  i_max = static_cast<int>(text.size());
  for(int i=0; i<i_max; i++)
  {
    text_new.push_back(text[i]);
  }

  //Add endf of file
  add_end_of_file(text_new);

  text = text_new;
  clr_obj.clear_vec_array1_str(text_new);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::add_end_of_file(vector<string>& text)
{
  //Write file end
  string text_tmp = efw_obj.write_file_end();
  text.push_back(text_tmp);

  text_tmp.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::check_set_data()
{
  //Check the all data was set or not
  if( endf_parser_flg == 0 )
  {
    string class_name = "Endf6Writer";
    string func_name  = "check_set_data()";

    vector<string> err_com;
    err_com.push_back("Endf6Paser or Endf6ParserNoCov object is not set.");
    err_com.push_back("Please check the program.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::check_material_number()
{
  ostringstream oss01;
  oss01 << mat_no;
  string str_data01 = "Material number from MF01MT451 : " + oss01.str();

  vector<string> err_com;
  err_com.clear();

  if( mf01mt452_par.get_ZA() > 0.0 && mf01mt452_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf01mt452_par.get_mat_no();
    oss03 << mf01mt452_par.get_ZA();
    string str_data02 = "Material number from MF01MT452 : " + oss02.str();
    string str_data03 = "ZA in MF01MT452                : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF01MT452 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  if( mf01mt455_par.get_ZA() > 0.0 && mf01mt455_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf01mt455_par.get_mat_no();
    oss03 << mf01mt455_par.get_ZA();
    string str_data02 = "Material number from MF01MT455 : " + oss02.str();
    string str_data03 = "ZA in MF01MT455                : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF01MT455 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  if( mf01mt456_par.get_ZA() > 0.0 && mf01mt456_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf01mt456_par.get_mat_no();
    oss03 << mf01mt456_par.get_ZA();
    string str_data02 = "Material number from MF01MT456 : " + oss02.str();
    string str_data03 = "ZA in MF01MT456                : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF01MT456 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  if( mf01mt458_par.get_ZA() > 0.0 && mf01mt458_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf01mt458_par.get_mat_no();
    oss03 << mf01mt458_par.get_ZA();
    string str_data02 = "Material number from MF01MT458 : " + oss02.str();
    string str_data03 = "ZA in MF01MT458                : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF01MT458 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  if( mf01mt460_par.get_ZA() > 0.0 && mf01mt460_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf01mt460_par.get_mat_no();
    oss03 << mf01mt460_par.get_ZA();
    string str_data02 = "Material number from MF01MT460 : " + oss02.str();
    string str_data03 = "ZA in MF01MT460                : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF01MT460 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  if( mf02mt151_par.get_ZAR() > 0.0 && mf02mt151_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf02mt151_par.get_mat_no();
    oss03 << mf02mt151_par.get_ZAR();
    string str_data02 = "Material number from MF02MT151 : " + oss02.str();
    string str_data03 = "ZAR in MF02MT151               : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF02MT151 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }
  
  if( mf02mt152_par.get_ZAR() > 0.0 && mf02mt152_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf02mt152_par.get_mat_no();
    oss03 << mf02mt152_par.get_ZAR();
    string str_data02 = "Material number from MF02MT152 : " + oss02.str();
    string str_data03 = "ZAR in MF02MT152               : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF02MT152 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }
  
  if( mf02mt153_par.get_ZAR() > 0.0 && mf02mt153_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf02mt153_par.get_mat_no();
    oss03 << mf02mt153_par.get_ZAR();
    string str_data02 = "Material number from MF02MT153 : " + oss02.str();
    string str_data03 = "ZAR in MF02MT153               : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF02MT153 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  int i_max = static_cast<int>(mf03_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf03_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf03_par[i].get_mat_no();
        oss03 << mf03_par[i].get_mt_no();
        string str_data02 = "Material number from MF03      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();
  
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF03 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf04_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf04_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf04_par[i].get_mat_no();
        oss03 << mf04_par[i].get_mt_no();
        string str_data02 = "Material number from MF04      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF04 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf05_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf05_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf05_par[i].get_mat_no();
        oss03 << mf05_par[i].get_mt_no();
        string str_data02 = "Material number from MF05      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF05 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf06_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf06_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf06_par[i].get_mat_no();
        oss03 << mf06_par[i].get_mt_no();
        string str_data02 = "Material number from MF06      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF06 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }
  
  if( mf07mt002_par.get_ZA() > 0.0 && mf07mt002_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf07mt002_par.get_mat_no();
    oss03 << mf07mt002_par.get_ZA();
    string str_data02 = "Material number from MF07MT002 : " + oss02.str();
    string str_data03 = "ZA in MF07MT002                : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF07MT002 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  if( mf07mt004_par.get_ZA() > 0.0 && mf07mt004_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf07mt004_par.get_mat_no();
    oss03 << mf07mt004_par.get_ZA();
    string str_data02 = "Material number from MF07MT004 : " + oss02.str();
    string str_data03 = "ZA in MF07MT004                : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF07MT004 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  if( mf07mt451_par.get_ZA() > 0.0 && mf07mt451_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf07mt451_par.get_mat_no();
    oss03 << mf07mt451_par.get_ZA();
    string str_data02 = "Material number from MF07MT451 : " + oss02.str();
    string str_data03 = "ZA in MF07MT451                : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF07MT451 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  i_max = static_cast<int>(mf08_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf08_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf08_par[i].get_mat_no();
        oss03 << mf08_par[i].get_mt_no();
        string str_data02 = "Material number from MF08      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF08 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  if( mf08mt454_par.get_ZA() > 0.0 && mf08mt454_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf08mt454_par.get_mat_no();
    oss03 << mf08mt454_par.get_ZA();
    string str_data02 = "Material number from MF08MT454 : " + oss02.str();
    string str_data03 = "ZA in MF08MT454                : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF08MT454 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  if( mf08mt457_par.get_ZA() > 0.0 && mf08mt457_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf08mt457_par.get_mat_no();
    oss03 << mf08mt457_par.get_ZA();
    string str_data02 = "Material number from MF08MT457 : " + oss02.str();
    string str_data03 = "ZA in MF08MT457                : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF08MT457 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  if( mf08mt459_par.get_ZA() > 0.0 && mf08mt459_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf08mt459_par.get_mat_no();
    oss03 << mf08mt459_par.get_ZA();
    string str_data02 = "Material number from MF08MT459 : " + oss02.str();
    string str_data03 = "ZA in MF08MT459                : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF08MT459 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  i_max = static_cast<int>(mf09_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf09_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf09_par[i].get_mat_no();
        oss03 << mf09_par[i].get_mt_no();
        string str_data02 = "Material number from MF09      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF09 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf10_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf10_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf10_par[i].get_mat_no();
        oss03 << mf10_par[i].get_mt_no();
        string str_data02 = "Material number from MF10      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF10 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }
  
  i_max = static_cast<int>(mf12_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf12_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf12_par[i].get_mat_no();
        oss03 << mf12_par[i].get_mt_no();
        string str_data02 = "Material number from MF12      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF12 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }
  
  i_max = static_cast<int>(mf13_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf13_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf13_par[i].get_mat_no();
        oss03 << mf13_par[i].get_mt_no();
        string str_data02 = "Material number from MF13      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF13 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf14_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf14_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf14_par[i].get_mat_no();
        oss03 << mf14_par[i].get_mt_no();
        string str_data02 = "Material number from MF14      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF14 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf15_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf15_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf15_par[i].get_mat_no();
        oss03 << mf15_par[i].get_mt_no();
        string str_data02 = "Material number from MF15      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF15 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }
  
  i_max = static_cast<int>(mf23_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf23_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf23_par[i].get_mat_no();
        oss03 << mf23_par[i].get_mt_no();
        string str_data02 = "Material number from MF23      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF23 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf26_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf26_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf26_par[i].get_mat_no();
        oss03 << mf26_par[i].get_mt_no();
        string str_data02 = "Material number from MF26      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF26 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf27_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf27_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf27_par[i].get_mat_no();
        oss03 << mf27_par[i].get_mt_no();
        string str_data02 = "Material number from MF27      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF27 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf28_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf28_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf28_par[i].get_mat_no();
        oss03 << mf28_par[i].get_mt_no();
        string str_data02 = "Material number from MF28      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF28 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  if( mf30mt002_par.get_ZA() > 0.0 && mf30mt002_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf30mt002_par.get_mat_no();
    oss03 << mf30mt002_par.get_ZA();
    string str_data02 = "Material number from MF30MT002 : " + oss02.str();
    string str_data03 = "ZA in MF30MT002                : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF30MT002 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  if( mf30mt001_par.get_ZA() > 0.0 && mf30mt001_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf30mt001_par.get_mat_no();
    oss03 << mf30mt001_par.get_ZA();
    string str_data02 = "Material number from MF30MT001 : " + oss02.str();
    string str_data03 = "ZA in MF30MT001                : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF30MT001 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  i_max = static_cast<int>(mf31_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf31_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf31_par[i].get_mat_no();
        oss03 << mf31_par[i].get_mt_no();
        string str_data02 = "Material number from MF31      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF31 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  if( mf32mt151_par.get_ZAR() > 0.0 && mf32mt151_par.get_mat_no() != mat_no )
  {
    ostringstream oss02, oss03;
    oss02 << mf32mt151_par.get_mat_no();
    oss03 << mf32mt151_par.get_ZAR();
    string str_data02 = "Material number from MF32MT151 : " + oss02.str();
    string str_data03 = "ZAR in MF32MT151               : " + oss03.str();

    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Material No of MF32MT151 is not identical to that of MF01MT451.");
    err_com.push_back("");
  }

  i_max = static_cast<int>(mf33_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf33_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf33_par[i].get_mat_no();
        oss03 << mf33_par[i].get_mt_no();
        string str_data02 = "Material number from MF33      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF33 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf34_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf34_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf34_par[i].get_mat_no();
        oss03 << mf34_par[i].get_mt_no();
        string str_data02 = "Material number from MF34      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF34 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf35_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf35_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf35_par[i].get_mat_no();
        oss03 << mf35_par[i].get_mt_no();
        string str_data02 = "Material number from MF35      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF35 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }

  i_max = static_cast<int>(mf40_par.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mf40_par[i].get_mat_no() != mat_no )
      {
        ostringstream oss02, oss03;
        oss02 << mf40_par[i].get_mat_no();
        oss03 << mf40_par[i].get_mt_no();
        string str_data02 = "Material number from MF40      : " + oss02.str();
        string str_data03 = "Section number (MT)            ; " + oss03.str();

        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("Material No of MF40 is not identical to that of MF01MT451.");
        err_com.push_back("");
      }
    }
  }
  if( static_cast<int>(err_com.size()) > 0 )
  {
    string class_name = "Endf6Writer";
    string func_name  = "check_material_number()";
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::set_modified_parser_data()
{
  endf_parser.set_mf01_mt451_data(mf01mt451_par_mod);
  endf_parser.set_mf01_mt452_data(mf01mt452_par);
  endf_parser.set_mf01_mt455_data(mf01mt455_par);
  endf_parser.set_mf01_mt456_data(mf01mt456_par);
  endf_parser.set_mf01_mt458_data(mf01mt458_par);
  endf_parser.set_mf01_mt460_data(mf01mt460_par);
  endf_parser.set_mf02_mt151_data(mf02mt151_par);
  endf_parser.set_mf02_mt152_data(mf02mt152_par);
  endf_parser.set_mf02_mt153_data(mf02mt153_par);
  endf_parser.set_mf07_mt002_data(mf07mt002_par);
  endf_parser.set_mf07_mt004_data(mf07mt004_par);
  endf_parser.set_mf07_mt451_data(mf07mt451_par);
  endf_parser.set_mf08_mt454_data(mf08mt454_par);
  endf_parser.set_mf08_mt457_data(mf08mt457_par);
  endf_parser.set_mf08_mt459_data(mf08mt459_par);
  endf_parser.set_mf30_mt001_data(mf30mt001_par);
  endf_parser.set_mf30_mt002_data(mf30mt002_par);
  endf_parser.set_mf32_mt151_data(mf32mt151_par);

  endf_parser.set_mf03_data(mf03_par);
  endf_parser.set_mf04_data(mf04_par);
  endf_parser.set_mf05_data(mf05_par);
  endf_parser.set_mf06_data(mf06_par);
  endf_parser.set_mf08_data(mf08_par);
  endf_parser.set_mf10_data(mf10_par);
  endf_parser.set_mf12_data(mf12_par);
  endf_parser.set_mf13_data(mf13_par);
  endf_parser.set_mf14_data(mf14_par);
  endf_parser.set_mf15_data(mf15_par);
  endf_parser.set_mf23_data(mf23_par);
  endf_parser.set_mf26_data(mf26_par);
  endf_parser.set_mf27_data(mf27_par);
  endf_parser.set_mf28_data(mf28_par);
  endf_parser.set_mf31_data(mf31_par);
  endf_parser.set_mf33_data(mf33_par);
  endf_parser.set_mf34_data(mf34_par);
  endf_parser.set_mf35_data(mf35_par);
  endf_parser.set_mf40_data(mf40_par);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::clear()
{
  endf_parser_flg = 0;
  
  endf_parser.clear();
  
  pendf_label_flg   = 0;
  add_comment_flg   = 0;
  clear_comment_flg = no_clear_comment_data;
  pendf_label.clear();
  clr_obj.clear_vec_array1_str(add_comment);

  clear_parser_data();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::clear_parser_data()
{
  clear_parser_data_no_cov();

  mf30mt001_par.clear();
  mf30mt002_par.clear();
  mf32mt151_par.clear();

  vector<MF31Parser>().swap(mf31_par);
  vector<MF33Parser>().swap(mf33_par);
  vector<MF34Parser>().swap(mf34_par);
  vector<MF35Parser>().swap(mf35_par);
  vector<MF40Parser>().swap(mf40_par);

  mf30mt001_wri.clear();
  mf30mt002_wri.clear();
  mf32mt151_wri.clear();
  mf31_wri.clear();
  mf33_wri.clear();
  mf34_wri.clear();
  mf35_wri.clear();
  mf40_wri.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::clear_parser_data_no_cov()
{
  mat_no          = 0;
  modify_endf_flg = 0;
  
  line_no.clear();
  mf_list.clear();
  mt_list.clear();

  mf01mt451_par.clear();
  mf01mt452_par.clear();
  mf01mt455_par.clear();
  mf01mt456_par.clear();
  mf01mt458_par.clear();
  mf01mt460_par.clear();
  mf02mt151_par.clear();
  mf02mt152_par.clear();
  mf02mt153_par.clear();
  mf07mt002_par.clear();
  mf07mt004_par.clear();
  mf07mt451_par.clear();
  mf08mt454_par.clear();
  mf08mt457_par.clear();
  mf08mt459_par.clear();
  
  mf01mt451_par_mod.clear();
  
  vector<MF03Parser>().swap(mf03_par);
  vector<MF04Parser>().swap(mf04_par);
  vector<MF05Parser>().swap(mf05_par);
  vector<MF06Parser>().swap(mf06_par);
  vector<MF08Parser>().swap(mf08_par);
  vector<MF09Parser>().swap(mf09_par);
  vector<MF10Parser>().swap(mf10_par);
  vector<MF12Parser>().swap(mf12_par);
  vector<MF13Parser>().swap(mf13_par);
  vector<MF14Parser>().swap(mf14_par);
  vector<MF15Parser>().swap(mf15_par);
  vector<MF23Parser>().swap(mf23_par);
  vector<MF26Parser>().swap(mf26_par);
  vector<MF27Parser>().swap(mf27_par);
  vector<MF28Parser>().swap(mf28_par);

  mf01mt451_wri.clear();
  mf01mt452_wri.clear();
  mf01mt455_wri.clear();
  mf01mt456_wri.clear();
  mf01mt458_wri.clear();
  mf01mt460_wri.clear();
  mf02mt151_wri.clear();
  mf02mt152_wri.clear();
  mf02mt153_wri.clear();
  mf07mt002_wri.clear();
  mf07mt004_wri.clear();
  mf07mt451_wri.clear();
  mf08mt454_wri.clear();
  mf08mt457_wri.clear();
  mf08mt459_wri.clear();
  mf03_wri.clear();
  mf04_wri.clear();
  mf05_wri.clear();
  mf06_wri.clear();
  mf08_wri.clear();
  mf09_wri.clear();
  mf10_wri.clear();
  mf12_wri.clear();
  mf13_wri.clear();
  mf14_wri.clear();
  mf15_wri.clear();
  mf23_wri.clear();
  mf26_wri.clear();
  mf27_wri.clear();
  mf28_wri.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::set_endf6_parser(Endf6Parser parser_obj)
{
  clear_parser_data();

  endf_parser_flg = 1;

  endf_parser = parser_obj;

  mf30mt001_par = parser_obj.get_mf30_mt001_data();
  mf30mt002_par = parser_obj.get_mf30_mt002_data();
  mf32mt151_par = parser_obj.get_mf32_mt151_data();

  mf31_par      = parser_obj.get_mf31_data();
  mf33_par      = parser_obj.get_mf33_data();
  mf34_par      = parser_obj.get_mf34_data();
  mf35_par      = parser_obj.get_mf35_data();
  mf40_par      = parser_obj.get_mf40_data();

  Endf6ParserNoCov endf_parser_no_cov = parser_obj.get_endf6_parser_no_cov();
  set_endf6_parser_no_cov(endf_parser_no_cov);
  endf_parser_no_cov.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::set_endf6_parser_no_cov(Endf6ParserNoCov parser_obj)
{
  clear_parser_data_no_cov();
  
  endf_parser_flg = 1;

  endf_parser.set_endf6_parser_no_cov(parser_obj);
  
  mf01mt451_par = parser_obj.get_mf01_mt451_data();
  mf01mt452_par = parser_obj.get_mf01_mt452_data();
  mf01mt455_par = parser_obj.get_mf01_mt455_data();
  mf01mt456_par = parser_obj.get_mf01_mt456_data();
  mf01mt458_par = parser_obj.get_mf01_mt458_data();
  mf01mt460_par = parser_obj.get_mf01_mt460_data();
  mf02mt151_par = parser_obj.get_mf02_mt151_data();
  mf02mt152_par = parser_obj.get_mf02_mt152_data();
  mf02mt153_par = parser_obj.get_mf02_mt153_data();
  mf07mt002_par = parser_obj.get_mf07_mt002_data();
  mf07mt004_par = parser_obj.get_mf07_mt004_data();
  mf07mt451_par = parser_obj.get_mf07_mt451_data();
  mf08mt454_par = parser_obj.get_mf08_mt454_data();
  mf08mt457_par = parser_obj.get_mf08_mt457_data();
  mf08mt459_par = parser_obj.get_mf08_mt459_data();

  mf03_par      = parser_obj.get_mf03_data();
  mf04_par      = parser_obj.get_mf04_data();
  mf05_par      = parser_obj.get_mf05_data();
  mf06_par      = parser_obj.get_mf06_data();
  mf08_par      = parser_obj.get_mf08_data();
  mf09_par      = parser_obj.get_mf09_data();
  mf10_par      = parser_obj.get_mf10_data();
  mf12_par      = parser_obj.get_mf12_data();
  mf13_par      = parser_obj.get_mf13_data();
  mf14_par      = parser_obj.get_mf14_data();
  mf15_par      = parser_obj.get_mf15_data();
  mf23_par      = parser_obj.get_mf23_data();
  mf26_par      = parser_obj.get_mf26_data();
  mf27_par      = parser_obj.get_mf27_data();
  mf28_par      = parser_obj.get_mf28_data();

  mf01mt451_par_mod = mf01mt451_par;
  
  mat_no = mf01mt451_par.get_mat_no();
  efw_obj.set_mat(mat_no);
  
  //Mat number check
#ifdef DEBUG_MODE
  check_material_number();
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::set_nucl_data_obj(NuclearDataObject data_obj)
{
  Endf6Converter conv_obj;
  Endf6Parser    parser_obj;
  conv_obj.convert_frendy_to_endf_format(data_obj, parser_obj);

  set_endf6_parser(parser_obj);
  parser_obj.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::set_pendf_label(string str_data)
{
  if( !str_data.empty() )
  {
    pendf_label_flg = 1;
    pendf_label     = str_data;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::set_additional_comment(vector<string> str_data)
{
  if( static_cast<int>(str_data.size()) > 0 )
  {
    add_comment_flg = 1;
    add_comment     = str_data;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Writer::set_clear_comment_flg(int flg_data)
{
  if( flg_data != no_clear_comment_data && flg_data != clear_comment_data )
  {
    string class_name = "Endf6Writer";
    string func_name  = "set_clear_comment_flg";

    ostringstream oss01, oss02, oss03;
    oss01 << flg_data;
    oss02 << no_clear_comment_data;
    oss03 << clear_comment_data;

    string str_data01 = "clear_comment_flg : " + oss01.str();
    string str_data02 = "clear_comment_flg is only available for " + oss02.str() + "(no_clear_comment_data)";
    string str_data03 = "or " + oss03.str() + "(clear_comment_data).";

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  clear_comment_flg = flg_data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> Endf6Writer::get_endf_text_data()
{
  vector<string> text, text_new;
  text = get_endf_text_data_without_label();

  int i_max = static_cast<int>(text.size());
  text_new.resize(i_max+1);

  //Write pendf label at top of the file
  if( static_cast<int>(pendf_label.size()) == 0 )
  {
    pendf_label = dummy_label;
  }
  efw_obj.set_mat(1);
  efw_obj.set_mf_mt(0, 0);
  text_new[0] = efw_obj.write_text(pendf_label);
  if( pendf_label_flg == 0 )
  {
    pendf_label = dummy_label;
  }

  for(int i=0; i<i_max; i++)
  {
    text_new[i+1] = text[i];
  }
  vector<string>().swap(text);

  return text_new;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> Endf6Writer::get_endf_text_data_without_label()
{
  vector<string> text;
  clr_obj.clear_vec_array1_str(text);
  
  if( modify_endf_flg == 0)
  {
    check_set_data();
  }

  convert_pendf_data(text);
  
  modify_endf_flg = 1;
  return text;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Endf6Parser      Endf6Writer::get_endf6_parser()
{
  set_modified_parser_data();

  return endf_parser;
}

Endf6ParserNoCov Endf6Writer::get_endf6_parser_no_cov()
{
  set_modified_parser_data();

  return endf_parser.get_endf6_parser_no_cov();
}

Endf6ParserCov   Endf6Writer::get_endf6_parser_cov()
{
  set_modified_parser_data();

  return endf_parser.get_endf6_parser_cov();
}

string Endf6Writer::get_pendf_label()
{
  return pendf_label;
}

vector<string> Endf6Writer::get_additional_comment()
{
  return add_comment;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

