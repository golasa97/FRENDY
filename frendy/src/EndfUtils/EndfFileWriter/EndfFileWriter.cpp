#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"

using namespace frendy;

//constructor
EndfFileWriter::EndfFileWriter(void)
{
  set_digit_mod_mode_default();

  real_vec.resize(2);
  int_vec.resize(4);
  line_vec_real.resize(6);
  line_vec_int.resize(6);
  mat_vec.resize(4);
  mat_width.resize(4);

  mat_vec[0] = 0;
  mat_vec[1] = 0;
  mat_vec[2] = 0;
  mat_vec[3] = 0;

  mat_width[0] = 4;
  mat_width[1] = 2;
  mat_width[2] = 3;
  mat_width[3] = 5;

  vec_intg.resize(2);
  data_no_pre = 0;
  int_size    = 0;
  blank_sta = "";
  blank_end = "";
}

//destructor
EndfFileWriter::~EndfFileWriter(void)
{
  real_vec.clear();
  int_vec.clear();
  mat_vec.clear();
  mat_width.clear();

  vec_intg.clear();
  blank_sta.clear();
  blank_end.clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::write_cont(Real C1, Real C2, Integer L1, Integer L2, Integer N1, Integer N2)
{
  if( digit_mod_mode == mod_digit )
  {
    digit_obj.adjust_data(C1);
    digit_obj.adjust_data(C2);
  }

  real_vec[0] = C1;
  real_vec[1] = C2;
  int_vec[0]  = L1;
  int_vec[1]  = L2;
  int_vec[2]  = N1;
  int_vec[3]  = N2;

  string text = convert_to_string_real(real_vec) + convert_to_string_int(int_vec) + write_mat_data();
  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::write_cont_real(Real C1, Real C2, Real L1, Real L2, Real N1, Real N2)
{
  if( digit_mod_mode == mod_digit )
  {
    digit_obj.adjust_data(C1);
    digit_obj.adjust_data(C2);
    digit_obj.adjust_data(L1);
    digit_obj.adjust_data(L2);
    digit_obj.adjust_data(N1);
    digit_obj.adjust_data(N2);
  }

  line_vec_real[0] = C1;
  line_vec_real[1] = C2;
  line_vec_real[2] = L1;
  line_vec_real[3] = L2;
  line_vec_real[4] = N1;
  line_vec_real[5] = N2;

  string text = convert_to_string_real(line_vec_real) + write_mat_data();
  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::write_cont_int(Integer C1, Integer C2, Integer L1, Integer L2, Integer N1, Integer N2)
{
  line_vec_int[0] = C1;
  line_vec_int[1] = C2;
  line_vec_int[2] = L1;
  line_vec_int[3] = L2;
  line_vec_int[4] = N1;
  line_vec_int[5] = N2;

  string text = convert_to_string_int(line_vec_int) + write_mat_data();
  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> EndfFileWriter::write_list(Real C1, Real C2, Integer L1, Integer L2,
                                          Integer NPL, Integer N2, vector<Real> B)
{
  if( digit_mod_mode == mod_digit )
  {
    digit_obj.adjust_data(C1);
    digit_obj.adjust_data(C2);
    digit_obj.adjust_data(B);
  }

  string line_str;
  vector<string> text;
  text.clear();

  line_str = write_cont(C1, C2, L1, L2, NPL, N2);
  text.push_back(line_str);

  int i_max = static_cast<int>(NPL);
  if( i_max != static_cast<int>(B.size()) )
  {
    string class_name = "EndfFileWriter";
    string func_name  = "write_list(Real C1, Real C2, Integer L1, Integer L2, ";
           func_name += "Integer NPL, Integer N2, vector<Real> B)";

    ostringstream oss01, oss02;
    oss01 << static_cast<int>(NPL);
    oss02 << static_cast<int>(B.size());
    string str_data01 = "NPL        : " + oss01.str();
    string str_data02 = "Size of Bn : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The NPL is not equal to the size of vector Bn. Please check the list data.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
 
  for(int i=0; i<i_max; i+=6) 
  {
    if(i_max - (i+6) >= 0 )
    {
      for(int j=0; j<6; j++)
      {
        line_vec_real[j] = B[i+j];
      }
      line_str = write_cont_real(line_vec_real[0], line_vec_real[1], line_vec_real[2], 
                                 line_vec_real[3], line_vec_real[4], line_vec_real[5]);
      text.push_back(line_str);
    }
    else
    {
      int j_max = i_max-i;
      vector<Real> tmp_vec;
      tmp_vec.resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        tmp_vec[j] = B[i+j];
      }
      line_str = convert_to_string_real(tmp_vec);
      line_str = line_str + write_blank(6-j_max);
      line_str = line_str + write_mat_data();
      tmp_vec.clear();

      text.push_back(line_str);
    }
  }
  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> EndfFileWriter::write_tab1(Real C1, Real C2, Integer L1, Integer L2,
                                          Integer NR, Integer NP, vector<Integer> NBT, vector<Integer> INT,
                                          vector<Real> X, vector<Real> Y)
{
  if( digit_mod_mode == mod_digit )
  {
    digit_obj.adjust_data(C1);
    digit_obj.adjust_data(C2);
    digit_obj.adjust_data(X);
    digit_obj.adjust_data(Y);
  }

  string line_str;
  vector<string> text;
  text.clear();

  check_data_size_tab1(NR, NP, NBT, INT, X, Y);
#ifdef NJOY_MODE
  adjust_truncation_err_tab1_old(NR, NP, NBT, INT, X, Y);
#else
  adjust_truncation_err_tab1(NR, NP, NBT, INT, X, Y);
#endif

  line_str = write_cont(C1, C2, L1, L2, NR, NP);
  text.push_back(line_str);

  //For NBT and INT
  write_nbt_int(text, NBT, INT);

  //For X and Y
  write_x_y(text, X, Y);

  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfFileWriter::check_data_size_tab1(Integer& nr, Integer& np,
                                          vector<Integer>& nbt_vec, vector<Integer>& int_vec,
                                          vector<Real>&    x_vec,   vector<Real>&    y_vec)
{
  int i_max = static_cast<int>(nr);
  int j_max = static_cast<int>(np);
  if( ( i_max != static_cast<int>(nbt_vec.size()) ) || ( i_max != static_cast<int>(int_vec.size()) ) ||
      ( j_max != static_cast<int>(x_vec.size()) )   || ( j_max != static_cast<int>(y_vec.size()) )   )
  {
    string class_name = "EndfFileWriter";
    string func_name  = "check_data_size_tab1(Integer& nr, Integer& np, ";
           func_name += "vector<Integer>& nbt_vec, vector<Integer>& int_vec, ";
           func_name += "vector<Real>& x_vec, vector<Real>& y_vec)";

    ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
    oss01 << i_max;
    oss02 << static_cast<int>(nbt_vec.size());
    oss03 << static_cast<int>(int_vec.size());
    oss04 << j_max;
    oss05 << static_cast<int>(x_vec.size());
    oss06 << static_cast<int>(y_vec.size());
    string str_data01 = "NR          : " + oss01.str();
    string str_data02 = "Size of NBT : " + oss02.str();
    string str_data03 = "Size of INT : " + oss03.str();
    string str_data04 = "NP          : " + oss04.str();
    string str_data05 = "Size of X   : " + oss05.str();
    string str_data06 = "Size of Y   : " + oss06.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);
    err_com.push_back(str_data05);
    err_com.push_back(str_data06);

    //Comparing NR and vector size of NBT
    if( i_max != static_cast<int>(nbt_vec.size()) )
    {
      err_com.push_back("The NR is not equal to the size of vector NBT. Please check the tab1 data.");
    }
    if( i_max != static_cast<int>(int_vec.size()) )
    {
      err_com.push_back("The NR is not equal to the size of vector INT. Please check the tab1 data.");
    }

    //Comparing NP and vector size of X
    if( j_max != static_cast<int>(x_vec.size()) )
    {
      err_com.push_back("The NP is not equal to the size of vector X. Please check the tab1 data.");
    }
    if( j_max != static_cast<int>(y_vec.size()) )
    {
      err_com.push_back("The NP is not equal to the size of vector Y. Please check the tab1 data.");
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfFileWriter::adjust_truncation_err_tab1(Integer& nr, Integer& np,
                                                vector<Integer>& nbt_vec, vector<Integer>& int_vec,
                                                vector<Real>&    x_vec,   vector<Real>&    y_vec)
{
  int i_max = static_cast<int>(np);
  if( i_max == 0 )
  {
    return;
  }

  //Evaluate truncated value.
  Integer digit_no;
  Real8   tmp_real;

  vector<Real8> x_new, y_new;
  x_new.resize(i_max);
  y_new.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    tmp_real = static_cast<Real8>(x_vec[i]);
    digit_no = digit_obj.get_precision_no(tmp_real, default_data_width);
    x_new[i] = digit_obj.get_truncation_value(tmp_real, digit_no);

    tmp_real = static_cast<Real8>(y_vec[i]);
    digit_no = digit_obj.get_precision_no(tmp_real, default_data_width);
    y_new[i] = digit_obj.get_truncation_value(tmp_real, digit_no);
  }

  //Adjust x value and y value in Tab1
  i_max = static_cast<int>(x_new.size());
  y_new.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    int discon_flg_m = 0;
    int discon_flg_p = 0;
    if( i > 0 )
    {
      if( fabs(x_new[i] - x_new[i-1]) < fabs(x_new[i] * min_ene_dif) )
      {
        discon_flg_m = 1;
      }
    }

    if( i < i_max-1 )
    {
      if( fabs(x_new[i] - x_new[i+1]) < fabs(x_new[i] * min_ene_dif) )
      {
        discon_flg_p = 1;
      }
    }

    if( discon_flg_m == 0 && discon_flg_p == 0 )
    {
      ti_obj.interpolation_tab1(x_new[i], y_new[i], nbt_vec, int_vec, x_vec, y_vec);
    }
  }

  x_vec = x_new;
  y_vec = y_new;
  x_new.clear();
  y_new.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfFileWriter::adjust_truncation_err_tab1_old(Integer& nr, Integer& np,
                                                    vector<Integer>& nbt_vec, vector<Integer>& int_vec,
                                                    vector<Real>&    x_vec,   vector<Real>&    y_vec)
{
  int i_max = static_cast<int>(np);
  if( i_max == 0 )
  {
    return;
  }

  //Evaluate truncated value.
  Integer digit_no;
  Real8   tmp_real;

  vector<Real8> x_ori, y_ori;
  x_ori.resize(i_max);
  y_ori.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    tmp_real = static_cast<Real8>(x_vec[i]);
    digit_no = digit_obj.get_precision_no(tmp_real, default_data_width);
    x_ori[i] = digit_obj.get_truncation_value(tmp_real, digit_no);

    tmp_real = static_cast<Real8>(y_vec[i]);
    digit_no = digit_obj.get_precision_no(tmp_real, default_data_width);
    y_ori[i] = digit_obj.get_truncation_value(tmp_real, digit_no);
  }

  //Remove overlap value
  vector<Real8>   x_new, y_new;
  vector<Integer> nbt_new, int_new;
  x_new.clear();
  y_new.clear();
  nbt_new = nbt_vec;
  int_new = int_vec;

  Real8 x_mod;
  int   ele_no = 1;
  x_new.push_back(x_ori[0]);
  for(int i=1; i<i_max; i++)
  {
    if( fabs(x_ori[i] - x_ori[i-1]) > fabs(x_ori[i] * min_ene_dif) )
    {
      x_new.push_back(x_ori[i]);
      ele_no++;
    }
    else if( i < i_max-1 )
    {
      //Adjusting energy grid
      //If adjusted energy grid x_mod was smaller than the next energy grid x_ori[i+1],
      //the adjusted energy grid x_mod is added to x_new.
      //This procedure is effective for the discontinuity energy grid which is found in
      //the evaluated nuclear data library.
      digit_no = digit_obj.get_precision_no(x_ori[i], default_data_width);
      x_mod = digit_obj.get_adjusted_value(x_ori[i], digit_no, +1.0);
      if( x_ori[i+1] - x_mod > fabs(x_mod * min_ene_dif) )
      {
        x_new.push_back(x_mod);
        ele_no++;
      }
      else
      {
        modify_nbt_int_tab1(ele_no, nbt_new, int_new);
      }
    }
    else //if( i==i_max-1)
    {
      modify_nbt_int_tab1(ele_no, nbt_new, int_new);
    }
  }

  //Adjust x value and y value in Tab1
  i_max = static_cast<int>(x_new.size());
  y_new.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    ti_obj.interpolation_tab1(x_new[i], y_new[i], nbt_vec, int_vec, x_vec, y_vec);
    //y_new[i] = digit_obj.adjust_min_value(y_new[i]);
  }

  //Copy adjusted data and modify nr and np
  nbt_vec = nbt_new;
  int_vec = int_new;
  nr      = static_cast<Integer>(nbt_new.size());

  x_vec.clear();
  y_vec.clear();
  i_max = static_cast<int>(x_new.size());
  x_vec.resize(i_max);
  y_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    x_vec[i] = static_cast<Real>(x_new[i]);
    y_vec[i] = static_cast<Real>(y_new[i]);
  }
  np = static_cast<Integer>(i_max);

  nbt_new.clear();
  int_new.clear();
  x_new.clear();
  y_new.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfFileWriter::modify_nbt_int_tab1(int remove_no, vector<Integer>& nbt_data, vector<Integer>& int_data)
{
  //Search interpolation range when the element number is remove_no.
  int nbt_pos = ti_obj.get_interpolation_range_pos(nbt_data, int_data, remove_no);

  //nbt array data was modified.
  int nbt_max = static_cast<int>(nbt_data.size());
  for(int i=nbt_pos; i<nbt_max; i++)
  {
    nbt_data[i] -= 1;
  }

  //If nbt_data[nbt_pos] is identical to nbt_data[nbt_pos-1], i.e., 
  //the nbt_data[nbt_pos] is undesired value, nbt_data[nbt_pos] is removed.
  if( nbt_max > 1 )
  {
    int nbt_pre, nbt_cur;
    if( nbt_pos == 0 )
    {
      nbt_pre = nbt_pos;
      nbt_cur = nbt_pos + 1;
    }
    else
    {
      nbt_pre = nbt_pos - 1;
      nbt_cur = nbt_pos;
    }

    if( nbt_data[nbt_cur] - nbt_data[nbt_pre] <= 0 )
    {
      vector<Integer> nbt_new, int_new;
      nbt_new.resize(nbt_max - 1);
      int_new.resize(nbt_max - 1);

      int ele_no = 0;
      for(int i=0; i<nbt_max; i++)
      {
        if( i != nbt_cur )
        {
          nbt_new[ele_no] = nbt_data[i];
          int_new[ele_no] = int_data[i];
          ele_no++;
        }
      }
      nbt_data = nbt_new;
      int_data = int_new;
      nbt_new.clear();
      int_new.clear();

      //If int value at i and i+1 is identical, these data were combined.
      int i_max = static_cast<int>(nbt_data.size());
      ele_no = 0;
      nbt_new.push_back(nbt_data[0]);
      int_new.push_back(int_data[0]);
      for(int i=1; i<i_max; i++)
      {
        if( int_data[i] == int_data[i-1] )
        {
          nbt_new[ele_no] = nbt_data[i];
        }
        else
        {
          ele_no++;
          nbt_new.push_back(nbt_data[i]);
          int_new.push_back(int_data[i]);
        }
      }
      nbt_data = nbt_new;
      int_data = int_new;
      nbt_new.clear();
      int_new.clear();
    }  
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> EndfFileWriter::write_tab2(Real C1, Real C2, Integer L1, Integer L2,
                                          Integer NR, Integer NZ, vector<Integer> NBT, vector<Integer> INT)
{
  if( digit_mod_mode == mod_digit )
  {
    digit_obj.adjust_data(C1);
    digit_obj.adjust_data(C2);
  }

  string line_str;
  vector<string> text;
  text.clear();

  line_str = write_cont(C1, C2, L1, L2, NR, NZ);
  text.push_back(line_str);

  int i_max = static_cast<int>(NR);
  if( ( i_max != static_cast<int>(NBT.size()) ) || ( i_max != static_cast<int>(INT.size()) ) )
  {
    string class_name = "EndfFileWriter";
    string func_name  = "write_tab2(Real C1, Real C2, Integer L1, Integer L2, ";
           func_name += "Integer NR, Integer NZ, vector<Integer> NBT, vector<Integer> INT)";

    ostringstream oss01, oss02, oss03;
    oss01 << i_max;
    oss02 << static_cast<int>(NBT.size());
    oss03 << static_cast<int>(INT.size());
    string str_data01 = "NR          : " + oss01.str();
    string str_data02 = "Size of NBT : " + oss02.str();
    string str_data03 = "Size of INT : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    if( i_max != static_cast<int>(NBT.size()) )
    {
      err_com.push_back("The NR is not equal to the size of vector NBT. Please check the tab2 data.");
    }
    if( i_max != static_cast<int>(INT.size()) )
    {
      err_com.push_back("The NR is not equal to the size of vector INT. Please check the tab2 data.");
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
  write_nbt_int(text, NBT, INT);

  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfFileWriter:: write_nbt_int(vector<string>& text, vector<Integer>& NBT, vector<Integer>& INT)
{
  string line_str;

  int i_max = static_cast<int>(NBT.size()) * 2;
  for(int i=0; i<i_max; i+=6)
  {
    if(i_max - (i+6) >= 0 )
    {
      for(int j=0; j<3; j++)
      {
        line_vec_int[2*j]   = NBT[i/2+j];
        line_vec_int[2*j+1] = INT[i/2+j];
      }
      line_str = write_cont_int(line_vec_int[0], line_vec_int[1], line_vec_int[2],
                                line_vec_int[3], line_vec_int[4], line_vec_int[5]);
      text.push_back(line_str);
    }
    else
    {
      int j_max = (i_max-i)/2;
      vector<Integer> tmp_vec;
      tmp_vec.resize(j_max*2);
      for(int j=0; j<j_max; j++)
      {
        tmp_vec[2*j]   = NBT[i/2+j];
        tmp_vec[2*j+1] = INT[i/2+j];
      }
      line_str = convert_to_string_int(tmp_vec);
      line_str = line_str + write_blank(6-j_max*2);
      line_str = line_str + write_mat_data();
      tmp_vec.clear();

      text.push_back(line_str);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfFileWriter:: write_x_y(vector<string>& text, vector<Real>& X, vector<Real>& Y)
{
  string line_str;

  int i_max = static_cast<int>(X.size()) * 2;
  for(int i=0; i<i_max; i+=6)
  {
    if(i_max - (i+6) >= 0 )
    {
      for(int j=0; j<3; j++)
      {
        line_vec_real[2*j]   = X[i/2+j];
        line_vec_real[2*j+1] = Y[i/2+j];
      }
      line_str = write_cont_real(line_vec_real[0], line_vec_real[1], line_vec_real[2],
                                 line_vec_real[3], line_vec_real[4], line_vec_real[5]);
      text.push_back(line_str);
    }
    else
    {
      int j_max = (i_max-i)/2;
      vector<Real> tmp_vec;
      tmp_vec.resize(j_max*2);
      for(int j=0; j<j_max; j++)
      {
        tmp_vec[2*j]   = X[i/2+j];
        tmp_vec[2*j+1] = Y[i/2+j];
      }
      line_str = convert_to_string_real(tmp_vec);
      line_str = line_str + write_blank(6-j_max*2);
      line_str = line_str + write_mat_data();
      tmp_vec.clear();

      text.push_back(line_str);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::write_intg(Integer II, Integer JJ, vector<Integer> KIJ)
{
  int data_no = static_cast<int>(KIJ.size());
  check_kij_size(data_no);

  //For II and JJ
  vec_intg[0] = II;
  vec_intg[1] = JJ;

  string text = convert_to_string_int(vec_intg, 5)   + blank_sta 
              + convert_to_string_int(KIJ, int_size) + blank_end + write_mat_data();
  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfFileWriter::check_kij_size(int& data_no)
{
  if(data_no != data_no_pre)
  {
    data_no_pre = data_no;

    switch(data_no)
    {
      case  8:
        int_size =  7;
        blank_sta = "";    //0X
        blank_end = "";    //0X
        break;
      case  9:
        int_size =  6;
        blank_sta = " ";   //1X
        blank_end = " ";   //1X
        break;
      case 11:
        int_size =  5;
        blank_sta = " ";   //1X
        blank_end = "";    //0X
        break;
      case 13:
        int_size =  4;
        blank_sta = " ";   //1X
        blank_end = "   "; //3X
        break;
      case 18:
        int_size =  3;
        blank_sta = " ";   //1X
        blank_end = " ";   //1X
        break;
      default:
        string class_name = "EndfFileWriter";
        string func_name  = "check_kij_size(int& data_no)";

        ostringstream oss01;
        oss01 << data_no;
        string str_data01 = "Size of vector KIJ : " + oss01.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back("The size of vector KIJ is not equal to 18, 13, 11, 9 or 8.");
        err_com.push_back("Please check the intg data.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
        break;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::write_text(string HL)
{
  int hl_length = static_cast<int>(HL.length());
  if( hl_length < 66 )
  {
    HL = HL + "                                                                  ";
  }

  string text = HL.substr(0,66) + write_mat_data();
  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::write_mt_end()
{
  mat_vec[2] = 0;
  mat_vec[3] = 99999;

  string text = write_blank(6) + write_mat_data();
  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::write_mf_end()
{
  mat_vec[1] = 0;
  mat_vec[2] = 0;
  mat_vec[3] = 0;

  string text = write_blank(6) + write_mat_data();
  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::write_file_end()
{
  string text = write_blank(6);
  mat_vec[0] =  0;
  mat_vec[1] =  0;
  mat_vec[2] =  0;
  mat_vec[3] =  0;
  text = text + write_mat_data();

  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::write_tape_end()
{
  string text = write_blank(6);
  mat_vec[0] = -1;
  mat_vec[1] =  0;
  mat_vec[2] =  0;
  mat_vec[3] =  0;
  text = text + write_mat_data();

  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::write_blank()
{
  string text = "           ";
  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::write_blank(int blank_no)
{
  string text  = "";
  string blank = write_blank();
  for(int i=0; i<blank_no; i++)
  {
    text = text + blank;
  }
  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::write_mat_data()
{
  string          mat_str;
  vector<Integer> int_vec;

  mat_str.clear();
  int_vec.resize(1);

  for(int i=0; i<4; i++)
  {
    int_vec[0] = mat_vec[i];
    mat_str = mat_str + convert_to_string_int(int_vec, mat_width[i]);
  }
  mat_vec[3]++;
  if( mat_vec[3] > 99999 )
  {
    mat_vec[3] = 1;
  }

  return mat_str;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::convert_to_string_real(vector<Real>& real_vec)
{
  return convert_to_string_real(real_vec, default_data_width);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::convert_to_string_real(vector<Real>& real_vec, int width)
{
  ostringstream oss;
  int i_max = static_cast<int>(real_vec.size());
  //oss.setf(ios::showpoint, ios::fixed);
  oss.setf(ios::showpoint);

  int     precision_value;
  Integer exp_part;
  Real    real_data, mantissa;
  for(int i=0; i<i_max; i++)
  {
    real_data = static_cast<Real>(real_vec[i]);
    if( !isfinite(real_data) )
    {
      string class_name = "EndfFileWriter";
      string func_name  = "convert_to_string_real(vector<Real>& real_vec, int width)";

      vector<string> err_com;
      err_com.push_back("NaN (Nan, nan, Inf, inf, ...) data is observed.");

      if( err_obj.get_err_mes_nan_opt() == err_obj.warning_runtime_error )
      {
        err_com.push_back("Output of ENDF file is aborted.");
        err_com.push_back("");
        err_com.push_back("If you want to process this nuclear data, please use nan_err_mes_opt parameter.");
        err_com.push_back("  Sample of this parameter : nan_err_mes_opt  caution");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      else //if( err_obj.get_err_mes_nan_opt() == err_obj.warning_caution )
      {
        //real_data = 0.0;
        real_data = -99999999.0;

        ostringstream oss01;
        oss01 << setw(8) << std::showpoint << real_data;
        string str_data01 = "NaN data is modified to " + oss01.str();
        if( real_data < -99000000.0 )
        {
          str_data01 = "NaN data is modified to -99999999.0";
        }
        err_com.push_back(str_data01);
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }

    if( real_data >= 0.0 )
    {
      oss << " "; 
    }

    exp_part = digit_obj.get_digit_number(real_data);
    precision_value = digit_obj.get_precision_no(real_data, width);
#ifdef _WIN32
    if( real_data == 0.0 )
    {
      precision_value--;
    }
#endif
    oss.precision(precision_value);
    if( exp_part >= 0 && exp_part < width - 3 )
    {
      if( real_data >= 0 )
      {
        oss.width(width-1);
      }
      else
      {
        oss.width(width);
      }
      oss << real_data;
    }
    else
    {
      mantissa = real_data * pow(0.1, exp_part);
      oss << mantissa;
      oss.precision(10 - precision_value);
      oss.setf(ios::showpos);
      oss << exp_part;
      oss.unsetf(ios::showpos);
    }
  }
  return oss.str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::convert_to_string_int(vector<Integer>& int_vec)
{
  string text;

  text = convert_to_string_int(int_vec, default_data_width);
  return text;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string EndfFileWriter::convert_to_string_int(vector<Integer>& int_vec, int width)
{
  ostringstream oss;
  int int_max = static_cast<int>(int_vec.size());
  oss.width(width);
  oss.setf(ios::right);

  for(int i=0; i<int_max; i++)
  {
    if( !isfinite((double)int_vec[i]) )
    {
      string class_name = "EndfFileWriter";
      string func_name  = "convert_to_string_int(vector<Integer>& int_vec, int width)";

      vector<string> err_com;
      err_com.push_back("NaN data is observed.");
      err_com.push_back("Output of ENDF file is aborted.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    oss.width(width);
    oss << int_vec[i];
  }
  return oss.str();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfFileWriter::set_mat(Integer mat_no)
{
  mat_vec[0] = mat_no;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfFileWriter::set_mf_mt(Integer mf_no, Integer mt_no)
{
  mat_vec[1] = mf_no;
  mat_vec[2] = mt_no;
  mat_vec[3] = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfFileWriter::set_mat_mf_mt(Integer mat_no, Integer mf_no, Integer mt_no)
{
  mat_vec[0] = mat_no;
  mat_vec[1] = mf_no;
  mat_vec[2] = mt_no;
  mat_vec[3] = 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void EndfFileWriter::set_digit_mod_mode_default()
{
  digit_mod_mode = mod_digit;
}

void EndfFileWriter::set_digit_mod_mode(Integer int_val)
{
  if( int_val != mod_digit && int_val != no_mod_digit )
  {
    string class_name = "EndfFileWriter";
    string func_name  = "set_digit_mod_mode(Integer int_val)";

    ostringstream oss01, oss02, oss03;
    oss01 << int_val;
    oss02 << mod_digit;
    oss03 << no_mod_digit;
    string str_data01 = "set value           : " + oss01.str();
    string str_data02 = "mod_digit option    : " + oss02.str();
    string str_data03 = "no_mod_digit option : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Please select mod_digit or no_mod_digit option.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  digit_mod_mode = int_val;
}

Integer EndfFileWriter::get_digit_mod_mode()
{
  return digit_mod_mode;
}

