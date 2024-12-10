#include "EndfUtils/GendfParser/GendfInterpolator.hpp"

using namespace frendy;

//constructor
GendfInterpolator::GendfInterpolator(void)
{
  clear();
}

//destructor
GendfInterpolator::~GendfInterpolator(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfInterpolator::clear()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMFxxParserBase GendfInterpolator::interpolate_read_obj(GMFxxParserBase read_obj, int int_val,
                                                        Real sigz, vector<Real> sigz_vec)
{
  int sigz_no = static_cast<int>(sigz_vec.size());
  if( sigz_no <= 1 )
  {
    string class_name = "GendfInterpolator";
    string func_name  = "interpolate_read_obj(GMFxxParserBase read_obj, int int_val, Real sigz, vector<Real> sigz_vec)";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << read_obj.get_mat_no();
    oss02 << read_obj.get_mf_no();
    oss03 << read_obj.get_mt_no();
    oss04 << sigz_no;

    string str_data01 = "MAT Number     : " + oss01.str();
    string str_data02 = "MF  Number     : " + oss02.str();
    string str_data03 = "MT  Number     : " + oss03.str();
    string str_data04 = "Number of sigz : " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back(str_data04);

    err_com.push_back("");
    if( sigz_no == 0 )
    {
      err_com.push_back("The number of sigz is 0.");
      err_com.push_back("Please check sigz_vec.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    err_com.push_back("The number of sigz is 1.");
    err_com.push_back("Interpolation scheme was skipped.");
    err_obj.output_caution(class_name, func_name, err_com);

    return read_obj;
  }

  if( int_val >= 10 && int_val != int_monotone_cubic )
  {
    string class_name = "GendfInterpolator";
    string func_name  = "interpolate_read_obj(GMFxxParserBase read_obj, int int_val, Real sigz, vector<Real> sigz_vec)";

    ostringstream oss01, oss02;
    oss01 << int_val;
    oss02 << int_monotone_cubic;

    string str_data01 = "int_val : " + oss01.str();
    string str_data02 = "  monotone cubic interpolation : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This interpolation value is not available in this program.");
    err_com.push_back("The available interpolation type is as follows:");
    err_com.push_back("  constant                     : 1");
    err_com.push_back("  lin-lin                      : 2");
    err_com.push_back("  log-lin                      : 3");
    err_com.push_back("  lin-log                      : 4");
    err_com.push_back("  log-log                      : 5");
    err_com.push_back(str_data02);
    err_com.push_back("Please check the interpolation type (int_val).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }


  GMFxxParserBase read_obj_new;
  read_obj_new.clear();

  read_obj_new.set_mat_no(read_obj.get_mat_no());
  read_obj_new.set_mf_no(read_obj.get_mf_no());
  read_obj_new.set_mt_no(read_obj.get_mt_no());

  //Line No. 01
  read_obj_new.set_ZA(read_obj.get_ZA());
  read_obj_new.set_AWR(read_obj.get_AWR());
  read_obj_new.set_NL(read_obj.get_NL());
  read_obj_new.set_LR(read_obj.get_LR());
  read_obj_new.set_NGN(read_obj.get_NGN());

  read_obj_new.set_NSIGZ(1);

  //Line No. 02
  read_obj_new.set_TEMP(read_obj.get_TEMP());
  read_obj_new.set_NG2(read_obj.get_NG2());
  read_obj_new.set_IG2LO(read_obj.get_IG2LO());
  read_obj_new.set_IG(read_obj.get_IG());

  //ein, sigz_no, pl_no, eout;
  vector<vector<vector<Real> > >          data1, data1_new;
  vector<vector<vector<vector<Real> > > > data2, data2_new;
  data1 = read_obj.get_DATA1();
  data2 = read_obj.get_DATA2_NG2();

  int pos_m  = 0;
  int pos_p  = 0;
  if( sigz_vec[0] < sigz )
  {
    pos_m = 0;
    pos_p = 1;
  }
  else if( sigz_vec[sigz_no-1] > sigz )
  {
    pos_m = sigz_no-2;
    pos_p = sigz_no-1;
  }
  for(int i=1; i<sigz_no; i++)
  {
    if( sigz_vec[i] < sigz )
    {
      pos_m = i-1;
      pos_p = i;
      break;
    }
  }

  //Sig -> log10(Sig)
       sigz   = log10(sigz);
  Real sigz_m = log10(sigz_vec[pos_m]);
  Real sigz_p = log10(sigz_vec[pos_p]);
  

  int i_max = static_cast<int>(data1.size());
  data1_new.resize(i_max);
  data2_new.resize(i_max);
  for(int i=0; i<i_max; i++) //ein
  {
    int data_flg = 1;
    int j_max    = static_cast<int>(data1[i].size());

    if( j_max == 0 )
    {
      data_flg = 2;
      j_max = static_cast<int>(data2[i].size());
    }

    if( j_max != sigz_no && j_max > 0 )
    {
      string class_name = "GendfInterpolator";
      string func_name  = "interpolate_read_obj(GMFxxParserBase read_obj, int int_val, Real sigz, vector<Real> sigz_vec)";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << read_obj.get_mat_no();
      oss02 << read_obj.get_mf_no();
      oss03 << read_obj.get_mt_no();
      oss04 << j_max;
      oss05 << sigz_no;

      string str_data01 = "MAT Number                : " + oss01.str();
      string str_data02 = "MF  Number                : " + oss02.str();
      string str_data03 = "MT  Number                : " + oss03.str();
      string str_data04 = "Number of sigz from DATA1 : " + oss04.str();
      if( data_flg != 1 )
      {
        str_data04 = "Number of sigz from DATA2 : " + oss04.str();
      }
      string str_data05 = "Number of sigz            : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back("");
      if( data_flg == 1 )
      {
        err_com.push_back("The number of sigz from DATA1 is not equal to that of sigz_vec.");
      }
      else
      {
        err_com.push_back("The number of sigz from DATA2 is not equal to that of sigz_vec.");
      }
      err_com.push_back("Please check sigz_vec.");
      err_com.push_back("");
      err_com.push_back("sigz_vec");
      for(int j=0; j<sigz_no; j++)
      {
        ostringstream oss10;
        oss10 << setw(8) << std::showpoint << std::scientific << sigz_vec[j];
        string str_data10 = "  " + oss10.str(); 
        err_com.push_back(str_data10);
      }

      if( j_max == 1 )
      {
        err_obj.output_caution(class_name, func_name, err_com);
      }
      else
      {
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }

    if( static_cast<int>(data1[i].size()) == 1 )
    {
      data1_new[i] = data1[i];
    }
    else if( static_cast<int>(data1[i].size()) > 0 )
    {
      int k_max = static_cast<int>(data1[i][0].size());
      data1_new[i].resize(1);
      data1_new[i][0].resize(k_max);
      for(int k=0; k<k_max; k++) //pl_no
      {
        if( int_val < 10 )
        {
          ti_obj.interpolation_1d(int_val, sigz, data1_new[i][0][k],
                                  sigz_m, data1[i][pos_m][k], sigz_p, data1[i][pos_p][k]);
        }
        else
        {
          vector<Real> data1_vec;
          data1_vec.resize(sigz_no);
          for(int j=0; j<sigz_no; j++)
          {
            data1_vec[j] = data1[i][j][k];
          }
          data1_new[i][0][k] = FMGen::doMonotoneCubicInterpolation(sigz_vec, data1_vec, sigz);
          data1_vec.clear();
        }
      }
    }

    if( static_cast<int>(data2[i].size()) == 1 )
    {
      data2_new[i] = data2[i];
    }
    else if( static_cast<int>(data2[i].size()) > 0 )
    {
      int k_max = static_cast<int>(data2[i][0].size());
      data2_new[i].resize(1);
      data2_new[i][0].resize(k_max);
      for(int k=0; k<k_max; k++) //pl_no
      {
        int l_max = static_cast<int>(data2[i][0][k].size());
        data2_new[i][0][k].resize(l_max);
        for(int l=0; l<l_max; l++) //eout
        {
          if( int_val < 10 )
          {
            ti_obj.interpolation_1d(int_val, sigz, data2_new[i][0][k][l],
                                    sigz_m, data2[i][pos_m][k][l], sigz_p, data2[i][pos_p][k][l]);
          }
          else
          {
            vector<Real> data2_vec;
            data2_vec.resize(sigz_no);
            for(int j=0; j<sigz_no; j++)
            {
              data2_vec[j] = data2[i][j][k][l];
            }
            data2_new[i][0][k][l] = FMGen::doMonotoneCubicInterpolation(sigz_vec, data2_vec, sigz);
            data2_vec.clear();
          }
        }
      }
    }
  }
  read_obj.clear();

  read_obj_new.set_DATA1(data1_new);
  read_obj_new.set_DATA2_NG2(data2_new);
  vector<vector<vector<Real> > >().swap(data1);
  vector<vector<vector<Real> > >().swap(data1_new);
  vector<vector<vector<vector<Real> > > >().swap(data2);
  vector<vector<vector<vector<Real> > > >().swap(data2_new);

  return read_obj_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMFxxParserBase GendfInterpolator::interpolate_read_obj(vector<GMFxxParserBase> read_obj,
                                                        int int_val, Real temp)
{
  vector<Real> temp_vec;
  check_data(read_obj, temp_vec, temp);

  int i_m, i_p;
  ti_obj.search_neighbor_value(temp, temp_vec, i_m, i_p);

  int i_max = static_cast<int>(temp_vec.size());
  if( int_val < 10 )
  {
    return interpolate_read_obj(read_obj[i_m], read_obj[i_p], int_val, temp);
  }
  else if( int_val == int_quadratic )
  {
    if( i_max < 3 )
    {
      string class_name = "GendfInterpolator";
      string func_name  = "interpolate_read_obj(vector<GMFxxParserBase> read_obj, int int_val, Real temp)";

      ostringstream oss01, oss02;
      oss01 << i_max;
      oss02 << int_val;

      string str_data01 = "Number of GMFxxParserBase data : " + oss01.str();
      string str_data02 = "Interpolation type             : " + oss02.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("");
      err_com.push_back("The number of GMFxxParserBase data is less than two.");
      err_com.push_back("The 2-d interpolation is not available in this program.");
      err_com.push_back("Please check the GENDF data or interpolation type");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( i_m == 0 )
    {
      return interpolate_read_obj(read_obj[i_m], read_obj[i_p], read_obj[i_p+1], int_val, temp);
    }
    else if( i_p == i_max - 1 )
    {
      return interpolate_read_obj(read_obj[i_m-1], read_obj[i_m], read_obj[i_p], int_val, temp);
    }
    else
    {
      if( fabs(temp - temp_vec[i_m-1]) > fabs(temp_vec[i_p+1] - temp) )
      {
        return interpolate_read_obj(read_obj[i_m], read_obj[i_p], read_obj[i_p+1], int_val, temp);
      }
      else
      {
        return interpolate_read_obj(read_obj[i_m-1], read_obj[i_m], read_obj[i_p], int_val, temp);
      }
    }
  }
  else
  {
    string class_name = "GendfInterpolator";
    string func_name  = "interpolate_read_obj(vector<GMFxxParserBase> read_obj, int int_val, Real temp)";

    ostringstream oss01, oss02;
    oss01 << int_val;
    oss02 << int_quadratic;

    string str_data01 = "int_val : " + oss01.str();
    string str_data02 = "  quadratic interpolation : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This interpolation value is not available in this program.");
    err_com.push_back("The available interpolation type is as follows:");
    err_com.push_back("  constant                : 1");
    err_com.push_back("  lin-lin                 : 2");
    err_com.push_back("  log-lin                 : 3");
    err_com.push_back("  lin-log                 : 4");
    err_com.push_back("  log-log                 : 5");
    err_com.push_back(str_data02);
    err_com.push_back("Please check the interpolation type (int_val).");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  GMFxxParserBase dummy_vec;
  dummy_vec.clear();
  return dummy_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMFxxParserBase GendfInterpolator::interpolate_read_obj(GMFxxParserBase read_obj01,
                                                        GMFxxParserBase read_obj02,
                                                        int int_val, Real temp)
{
  Real temp_sq  = sqrt(temp);
  Real temp_min = sqrt(read_obj01.get_TEMP());
  Real temp_max = sqrt(read_obj02.get_TEMP());

  GMFxxParserBase read_obj_new;
  read_obj_new.clear();

  read_obj_new.set_mat_no(read_obj01.get_mat_no());
  read_obj_new.set_mf_no(read_obj01.get_mf_no());
  read_obj_new.set_mt_no(read_obj01.get_mt_no());

  //Line No. 01
  read_obj_new.set_ZA(read_obj01.get_ZA());
  read_obj_new.set_AWR(read_obj01.get_AWR());
  read_obj_new.set_NL(read_obj01.get_NL());
  read_obj_new.set_NSIGZ(read_obj01.get_NSIGZ());
  read_obj_new.set_LR(read_obj01.get_LR());
  read_obj_new.set_NGN(read_obj01.get_NGN());

  //Line No. 02
  read_obj_new.set_TEMP(temp);
//  read_obj_new.set_NG2(read_obj01.get_NG2());
//  read_obj_new.set_IG2LO(read_obj01.get_IG2LO());
  read_obj_new.set_IG(read_obj01.get_IG());

  //ein, sigz_no, pl_no, eout;
  vector<vector<vector<Real> > >          data1_01, data1_02, data1_new;
  vector<vector<vector<vector<Real> > > > data2_01, data2_02, data2_new;
  data1_01 = read_obj01.get_DATA1();
  data2_01 = read_obj01.get_DATA2_NG2_fill_data();
  data1_02 = read_obj02.get_DATA1();
  data2_02 = read_obj02.get_DATA2_NG2_fill_data();
  read_obj_new.set_NG2(read_obj01.get_NG2());
  read_obj_new.set_IG2LO(read_obj01.get_IG2LO());

  int i_max = static_cast<int>(data1_01.size());
  data1_new.resize(i_max);
  data2_new.resize(i_max);
  for(int i=0; i<i_max; i++) //ein
  {
    int j_max = static_cast<int>(data1_01[i].size());
    if( j_max > 0 )
    {
      data1_new[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        int k_max = static_cast<int>(data1_01[i][j].size());
        data1_new[i][j].resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          ti_obj.interpolation_1d(int_lin_lin, temp_sq, data1_new[i][j][k],
                                  temp_min, data1_01[i][j][k], temp_max, data1_02[i][j][k]);
        }
      }
    }

    j_max = static_cast<int>(data2_01[i].size());
    if( j_max > 0 )
    {
      data2_new[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        int k_max = static_cast<int>(data2_01[i][j].size());
        data2_new[i][j].resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          int l_max  = static_cast<int>(data2_01[i][j][k].size());
          data2_new[i][j][k].resize(l_max);
          for(int l=0; l<l_max; l++)
          {
            ti_obj.interpolation_1d(int_lin_lin, temp_sq, data2_new[i][j][k][l],
                                    temp_min, data2_01[i][j][k][l], temp_max, data2_02[i][j][k][l]);
          }
        }
      }
    }
  }
  read_obj01.clear();
  read_obj02.clear();

  read_obj_new.set_DATA1(data1_new);
  read_obj_new.set_DATA2_NG2(data2_new);
  read_obj_new.remove_DATA2_NG2_zero_data();

  vector<vector<vector<Real> > >().swap(data1_01);
  vector<vector<vector<Real> > >().swap(data1_02);
  vector<vector<vector<Real> > >().swap(data1_new);
  vector<vector<vector<vector<Real> > > >().swap(data2_01);
  vector<vector<vector<vector<Real> > > >().swap(data2_02);
  vector<vector<vector<vector<Real> > > >().swap(data2_new);

  return read_obj_new;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

GMFxxParserBase GendfInterpolator::interpolate_read_obj(GMFxxParserBase read_obj01,
                                                        GMFxxParserBase read_obj02,
                                                        GMFxxParserBase read_obj03,
                                                        int int_val, Real temp)
{
  //For Quadratic interpolation
  GMFxxParserBase read_obj_new;
  read_obj_new.clear();

  Real temp01 = read_obj01.get_TEMP();
  Real temp02 = read_obj02.get_TEMP();
  Real temp03 = read_obj03.get_TEMP();

  read_obj_new.set_mat_no(read_obj01.get_mat_no());
  read_obj_new.set_mf_no(read_obj01.get_mf_no());
  read_obj_new.set_mt_no(read_obj01.get_mt_no());

  //Line No. 01
  read_obj_new.set_ZA(read_obj01.get_ZA());
  read_obj_new.set_AWR(read_obj01.get_AWR());
  read_obj_new.set_NL(read_obj01.get_NL());
  read_obj_new.set_NSIGZ(read_obj01.get_NSIGZ());
  read_obj_new.set_LR(read_obj01.get_LR());
  read_obj_new.set_NGN(read_obj01.get_NGN());

  //Line No. 02
  read_obj_new.set_TEMP(temp);
//  read_obj_new.set_NG2(read_obj01.get_NG2());
//  read_obj_new.set_IG2LO(read_obj01.get_IG2LO());
  read_obj_new.set_IG(read_obj01.get_IG());

  //ein, sigz_no, pl_no, eout;
  vector<vector<vector<Real> > >          data1_01, data1_02, data1_03, data1_new;
  vector<vector<vector<vector<Real> > > > data2_01, data2_02, data2_03, data2_new;
  data1_01 = read_obj01.get_DATA1();
  data2_01 = read_obj01.get_DATA2_NG2_fill_data();
  data1_02 = read_obj02.get_DATA1();
  data2_02 = read_obj02.get_DATA2_NG2_fill_data();
  data1_03 = read_obj03.get_DATA1();
  data2_03 = read_obj03.get_DATA2_NG2_fill_data();
  read_obj_new.set_NG2(read_obj01.get_NG2());
  read_obj_new.set_IG2LO(read_obj01.get_IG2LO());

  int i_max = static_cast<int>(data1_01.size());
  data1_new.resize(i_max);
  data2_new.resize(i_max);
  for(int i=0; i<i_max; i++) //ein
  {
    int j_max = static_cast<int>(data1_01[i].size());
    if( j_max > 0 )
    {
      data1_new[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        int k_max = static_cast<int>(data1_01[i][j].size());
        data1_new[i][j].resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          data1_new[i][j][k] = FMGen::do2ndLagrangeInterpolation
                                        (temp, temp01, temp02, temp03,
                                         data1_01[i][j][k], data1_02[i][j][k], data1_03[i][j][k]);
        }
      }
    }

    j_max = static_cast<int>(data2_01[i].size());
    if( j_max > 0 )
    {
      data2_new[i].resize(j_max);
      for(int j=0; j<j_max; j++)
      {
        int k_max = static_cast<int>(data2_01[i][j].size());
        data2_new[i][j].resize(k_max);
        for(int k=0; k<k_max; k++)
        {
          int l_max  = static_cast<int>(data2_01[i][j][k].size());
          data2_new[i][j][k].resize(l_max);
          for(int l=0; l<l_max; l++)
          {
            data2_new[i][j][k][l] = FMGen::do2ndLagrangeInterpolation
                                            (temp, temp01, temp02, temp03,
                                             data2_01[i][j][k][l],
                                             data2_02[i][j][k][l],
                                             data2_03[i][j][k][l]);
          }
        }
      }
    }
  }
  read_obj01.clear();
  read_obj02.clear();
  read_obj03.clear();

  read_obj_new.set_DATA1(data1_new);
  read_obj_new.set_DATA2_NG2(data2_new);
  read_obj_new.remove_DATA2_NG2_zero_data();

  vector<vector<vector<Real> > >().swap(data1_01);
  vector<vector<vector<Real> > >().swap(data1_02);
  vector<vector<vector<Real> > >().swap(data1_03);
  vector<vector<vector<Real> > >().swap(data1_new);
  vector<vector<vector<vector<Real> > > >().swap(data2_01);
  vector<vector<vector<vector<Real> > > >().swap(data2_02);
  vector<vector<vector<vector<Real> > > >().swap(data2_03);
  vector<vector<vector<vector<Real> > > >().swap(data2_new);

  return read_obj_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfInterpolator::check_data(vector<GMFxxParserBase>& read_obj, vector<Real>& temp_vec, Real temp)
{
  string class_name = "GendfInterpolator";
  string func_name  = "check_data";

  int i_max = static_cast<int>(read_obj.size());
  if( i_max < 1 )
  {
    vector<string> err_com;
    if( i_max == 0 )
    {
      err_com.push_back("The number of GMFxxParserBase data is zero.");
    }
    else
    {
      err_com.push_back("The number of GMFxxParserBase data is one.");
    }
    err_com.push_back("");
    err_com.push_back("This program cannot interpoalte the GENDF data.");
    err_com.push_back("Please check the GENDF data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  for(int i=1; i<i_max; i++)
  {
    if( read_obj[0].get_mat_no() != read_obj[i].get_mat_no() ||
        read_obj[0].get_mf_no()  != read_obj[i].get_mf_no()  ||
        read_obj[0].get_mt_no()  != read_obj[i].get_mt_no()  ||
        fabs(read_obj[0].get_ZA()  - read_obj[i].get_ZA())  > 1.0E-3 ||
        fabs(read_obj[0].get_AWR() - read_obj[i].get_AWR()) > 1.0E-3 )
    {
      ostringstream oss_i, oss_i_max;
      oss_i     << i+1;
      oss_i_max << i_max;
      string str_data_i = "Position : " + oss_i.str() + " / " + oss_i_max.str();

      ostringstream oss_mat01, oss_mat02, oss_mf01,  oss_mf02, oss_mt01, oss_mt02,
                    oss_za01,  oss_za02,  oss_awr01, oss_awr02;

      oss_mat01 << read_obj[0].get_mat_no();
      oss_mat02 << read_obj[i].get_mat_no();
      oss_mf01  << read_obj[0].get_mf_no();
      oss_mf02  << read_obj[i].get_mf_no();
      oss_mt01  << read_obj[0].get_mt_no();
      oss_mt02  << read_obj[i].get_mt_no();
      oss_za01  << setw(7) << std::showpoint << std::scientific << read_obj[0].get_ZA();
      oss_za02  << setw(7) << std::showpoint << std::scientific << read_obj[i].get_ZA();
      oss_awr01 << setw(7) << std::showpoint << std::scientific << read_obj[0].get_AWR();
      oss_awr02 << setw(7) << std::showpoint << std::scientific << read_obj[i].get_AWR();

      string str_data01 = "read_obj[0]: MAT=" + oss_mat01.str()
                        + ", MF=" + oss_mf01.str() + ", MT=" + oss_mt01.str()
                        + ", ZA=" + oss_za01.str() + ", AWR=" + oss_awr01.str();
      string str_data02 = "read_obj[i]: MAT=" + oss_mat02.str()
                        + ", MF=" + oss_mf02.str() + ", MT=" + oss_mt02.str()
                        + ", ZA=" + oss_za02.str() + ", AWR=" + oss_awr02.str();

      vector<string> err_com;
      err_com.push_back(str_data_i);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("");
      err_com.push_back("MAT, MF, MT, ZA or/and AWR is different.");
      err_com.push_back("Please check the interpolation data (read_obj[0], read_obj[i]).");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( read_obj[0].get_NL()    != read_obj[i].get_NL()     ||
        read_obj[0].get_NSIGZ() != read_obj[i].get_NSIGZ( ) ||
        read_obj[0].get_LR()    != read_obj[i].get_LR()     ||
        read_obj[0].get_NGN()   != read_obj[i].get_NGN() )
    {
      ostringstream oss_i, oss_i_max;
      oss_i     << i+1;
      oss_i_max << i_max;
      string str_data_i = "Position : " + oss_i.str() + " / " + oss_i_max.str();

      ostringstream oss_mat, oss_mf, oss_mt,
                    oss_nl01, oss_nl02, oss_nsigz01,  oss_nsigz02, oss_lr01, oss_lr02,
                    oss_ngn01, oss_ngn02;

      oss_mat     << read_obj[0].get_mat_no();
      oss_mf      << read_obj[0].get_mf_no();
      oss_mt      << read_obj[0].get_mt_no();
      oss_nl01    << read_obj[0].get_NL();
      oss_nl02    << read_obj[i].get_NL();
      oss_nsigz01 << read_obj[0].get_NSIGZ();
      oss_nsigz02 << read_obj[i].get_NSIGZ();
      oss_lr01    << read_obj[0].get_LR();
      oss_lr02    << read_obj[i].get_LR();
      oss_ngn01   << read_obj[0].get_NGN();
      oss_ngn02   << read_obj[i].get_NGN();

      string str_data00 = "MAT=" + oss_mat.str() + ", MF=" + oss_mf.str() + ", MT=" + oss_mt.str();
      string str_data01 = "read_obj[0]: NL=" + oss_nl01.str() + ", NSIGZ=" + oss_nsigz01.str()
                        + ", LR=" + oss_lr01.str() + ", NGN=" + oss_ngn01.str();
      string str_data02 = "read_obj[i]: NL=" + oss_nl02.str() + ", NSIGZ=" + oss_nsigz02.str()
                        + ", LR=" + oss_lr02.str() + ", NGN=" + oss_ngn02.str();

      vector<string> err_com;
      err_com.push_back(str_data_i);
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("");
      err_com.push_back("NL, NSIGZ, LR, and/or NGN is different.");
      err_com.push_back("Please check the interpolation data (read_obj[0], read_obj[i]).");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  sort_temp(read_obj, temp_vec);

  Real temp_min = temp_vec[0];
  Real temp_max = temp_vec[i_max-1];
  if( temp < temp_min || temp_max < temp )
  {
    if( fabs(temp - temp_min) > 1.0E-3 && fabs(temp - temp_max) > 1.0E-3 )
    {
      ostringstream oss_mat, oss_mf, oss_mt, oss_temp01, oss_temp02, oss_temp;
      oss_mat    << read_obj[0].get_mat_no();
      oss_mf     << read_obj[0].get_mf_no();
      oss_mt     << read_obj[0].get_mt_no();
      oss_temp01 << setw(7) << std::showpoint << std::scientific << temp_min;
      oss_temp02 << setw(7) << std::showpoint << std::scientific << temp_max;
      oss_temp   << setw(7) << std::showpoint << std::scientific << temp;

      string str_data00 = "MAT=" + oss_mat.str() + ", MF=" + oss_mf.str() + ", MT=" + oss_mt.str();
      string str_data01 = "Minimum temperature from : " + oss_temp01.str();
      string str_data02 = "Maximum temperature from : " + oss_temp02.str();
      string str_data03 = "Temperature              : " + oss_temp.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      err_com.push_back("The interpolation temperature is out of the temperature range.");
      err_com.push_back("The cross section data is calcualted by extrapolation.");
      err_com.push_back("The cross section data may be incorrect.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GendfInterpolator::sort_temp(vector<GMFxxParserBase>& read_obj, vector<Real>& temp_vec)
{
  vector<int> pos_vec;
  vector<GMFxxParserBase> read_obj_new;
  temp_vec.clear();

  int i_max = static_cast<int>(read_obj.size());
  temp_vec.resize(i_max);
  pos_vec.resize(i_max);
  read_obj_new.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    pos_vec[i]  = -1;
    temp_vec[i] = read_obj[i].get_TEMP();
  }

  vector<Real> temp_vec_ori = temp_vec;
  sort(temp_vec.begin(), temp_vec.end());
  for(int i=0; i<i_max; i++)
  {
    Real temp_dif = temp_vec[i] * min_ene_dif;
    if( temp_dif < min_ene_dif )
    {
      temp_dif = min_ene_dif;
    }

    for(int j=0; j<i_max; j++)
    {
      if( pos_vec[j] > 0 )
      {
        continue;
      }

      if( fabs(temp_vec[j] - temp_vec[i]) < temp_dif )
      {
        read_obj_new[i] = read_obj[j];
        pos_vec[j]      = 1;
      }
    }
  }

  read_obj = read_obj_new;
  read_obj_new.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF03Parser GendfInterpolator::interpolate_gmf03_data(GMF03Parser gmf_obj, int int_val,
                                                      Real sigz, vector<Real> sigz_vec)
{
  GMFxxParserBase read_obj = interpolate_read_obj(gmf_obj.get_read_obj(), int_val, sigz, sigz_vec);

  gmf_obj.set_read_obj(read_obj);
  read_obj.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF05Parser GendfInterpolator::interpolate_gmf05_data(GMF05Parser gmf_obj, int int_val,
                                                      Real sigz, vector<Real> sigz_vec)
{
  GMFxxParserBase read_obj = interpolate_read_obj(gmf_obj.get_read_obj(), int_val, sigz, sigz_vec);

  gmf_obj.set_read_obj(read_obj);
  read_obj.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF06Parser GendfInterpolator::interpolate_gmf06_data(GMF06Parser gmf_obj, int int_val,
                                                      Real sigz, vector<Real> sigz_vec)
{
  GMFxxParserBase read_obj = interpolate_read_obj(gmf_obj.get_read_obj(), int_val, sigz, sigz_vec);

  gmf_obj.set_read_obj(read_obj);
  read_obj.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF13Parser GendfInterpolator::interpolate_gmf13_data(GMF13Parser gmf_obj, int int_val,
                                                      Real sigz, vector<Real> sigz_vec)
{
  GMFxxParserBase read_obj = interpolate_read_obj(gmf_obj.get_read_obj(), int_val, sigz, sigz_vec);

  gmf_obj.set_read_obj(read_obj);
  read_obj.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF16Parser GendfInterpolator::interpolate_gmf16_data(GMF16Parser gmf_obj, int int_val,
                                                      Real sigz, vector<Real> sigz_vec)
{
  GMFxxParserBase read_obj = interpolate_read_obj(gmf_obj.get_read_obj(), int_val, sigz, sigz_vec);

  gmf_obj.set_read_obj(read_obj);
  read_obj.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<GMF03Parser> GendfInterpolator::interpolate_gmf03_data(vector<GMF03Parser> gmf_vec, int int_val,
                                                              Real sigz, vector<Real> sigz_vec)
{
  int i_max = static_cast<int>(gmf_vec.size());
  for(int i=0; i<i_max; i++)
  {
    gmf_vec[i] = interpolate_gmf03_data(gmf_vec[i], int_val, sigz, sigz_vec);
  }

  return gmf_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<GMF05Parser> GendfInterpolator::interpolate_gmf05_data(vector<GMF05Parser> gmf_vec, int int_val,
                                                              Real sigz, vector<Real> sigz_vec)
{
  int i_max = static_cast<int>(gmf_vec.size());
  for(int i=0; i<i_max; i++)
  {
    gmf_vec[i] = interpolate_gmf05_data(gmf_vec[i], int_val, sigz, sigz_vec);
  }

  return gmf_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<GMF06Parser> GendfInterpolator::interpolate_gmf06_data(vector<GMF06Parser> gmf_vec, int int_val,
                                                              Real sigz, vector<Real> sigz_vec)
{
  int i_max = static_cast<int>(gmf_vec.size());
  for(int i=0; i<i_max; i++)
  {
    gmf_vec[i] = interpolate_gmf06_data(gmf_vec[i], int_val, sigz, sigz_vec);
  }

  return gmf_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<GMF13Parser> GendfInterpolator::interpolate_gmf13_data(vector<GMF13Parser> gmf_vec, int int_val,
                                                              Real sigz, vector<Real> sigz_vec)
{
  int i_max = static_cast<int>(gmf_vec.size());
  for(int i=0; i<i_max; i++)
  {
    gmf_vec[i] = interpolate_gmf13_data(gmf_vec[i], int_val, sigz, sigz_vec);
  }

  return gmf_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<GMF16Parser> GendfInterpolator::interpolate_gmf16_data(vector<GMF16Parser> gmf_vec, int int_val,
                                                              Real sigz, vector<Real> sigz_vec)
{
  int i_max = static_cast<int>(gmf_vec.size());
  for(int i=0; i<i_max; i++)
  {
    gmf_vec[i] = interpolate_gmf16_data(gmf_vec[i], int_val, sigz, sigz_vec);
  }

  return gmf_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GendfParser GendfInterpolator::interpolate_gendf_data(GendfParser gendf_obj, int int_val, Real sigz)
{
  GendfParser gendf_new;
  gendf_new.clear();

  GMF01MT451Parser  mf01_mt451_data = gendf_obj.get_mf01_mt451_data();
  vector<Real>      sigz_vec        = mf01_mt451_data.get_SIGZ();

  vector<Real> sigz_new;
  sigz_new.resize(1);
  sigz_new[0] = sigz;
  mf01_mt451_data.set_SIGZ(sigz_new);
  gendf_new.set_mf01_mt451_data(mf01_mt451_data);
  mf01_mt451_data.clear();

  //MF=03
  vector<GMF03Parser> gmf03_vec = interpolate_gmf03_data(gendf_obj.get_mf03_data(),
                                                         int_val, sigz, sigz_vec);
  gendf_new.set_mf03_data(gmf03_vec);
  vector<GMF03Parser>().swap(gmf03_vec);
  
  //MF=05
  vector<GMF05Parser> gmf05_vec = interpolate_gmf05_data(gendf_obj.get_mf05_data(),
                                                         int_val, sigz, sigz_vec);
  gendf_new.set_mf05_data(gmf05_vec);
  vector<GMF05Parser>().swap(gmf05_vec);
  
  //MF=06
  vector<GMF06Parser> gmf06_vec = interpolate_gmf06_data(gendf_obj.get_mf06_data(),
                                                         int_val, sigz, sigz_vec);
  gendf_new.set_mf06_data(gmf06_vec);
  vector<GMF06Parser>().swap(gmf06_vec);
  
  //MF=13
  vector<GMF13Parser> gmf13_vec = interpolate_gmf13_data(gendf_obj.get_mf13_data(),
                                                         int_val, sigz, sigz_vec);
  gendf_new.set_mf13_data(gmf13_vec);
  vector<GMF13Parser>().swap(gmf13_vec);
  
  //MF=16
  vector<GMF16Parser> gmf16_vec = interpolate_gmf16_data(gendf_obj.get_mf16_data(),
                                                         int_val, sigz, sigz_vec);
  gendf_new.set_mf16_data(gmf16_vec);
  vector<GMF16Parser>().swap(gmf16_vec);

  sigz_vec.clear();
  gendf_obj.clear();
  
  return gendf_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF03Parser GendfInterpolator::interpolate_gmf03_data(vector<GMF03Parser>& gmf, int int_val, Real temp)
{
  int i_max = static_cast<int>(gmf.size());
  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf[i].get_read_obj();
  }

  
  GMFxxParserBase read_obj_new = interpolate_read_obj(read_obj, int_val, temp);
  read_obj.clear();

  GMF03Parser gmf_obj;
  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF05Parser GendfInterpolator::interpolate_gmf05_data(vector<GMF05Parser>& gmf, int int_val, Real temp)
{
  int i_max = static_cast<int>(gmf.size());
  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf[i].get_read_obj();
  }
  
  GMFxxParserBase read_obj_new = interpolate_read_obj(read_obj, int_val, temp);
  read_obj.clear();

  GMF05Parser gmf_obj;
  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF06Parser GendfInterpolator::interpolate_gmf06_data(vector<GMF06Parser>& gmf, int int_val, Real temp)
{
  int i_max = static_cast<int>(gmf.size());
  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf[i].get_read_obj();
  }
  
  GMFxxParserBase read_obj_new = interpolate_read_obj(read_obj, int_val, temp);
  read_obj.clear();

  GMF06Parser gmf_obj;
  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF13Parser GendfInterpolator::interpolate_gmf13_data(vector<GMF13Parser>& gmf, int int_val, Real temp)
{
  int i_max = static_cast<int>(gmf.size());
  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf[i].get_read_obj();
  }
  
  GMFxxParserBase read_obj_new = interpolate_read_obj(read_obj, int_val, temp);
  read_obj.clear();

  GMF13Parser gmf_obj;
  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GMF16Parser GendfInterpolator::interpolate_gmf16_data(vector<GMF16Parser>& gmf, int int_val, Real temp)
{
  int i_max = static_cast<int>(gmf.size());
  vector<GMFxxParserBase> read_obj;
  read_obj.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    read_obj[i] = gmf[i].get_read_obj();
  }
  
  GMFxxParserBase read_obj_new = interpolate_read_obj(read_obj, int_val, temp);
  read_obj.clear();

  GMF16Parser gmf_obj;
  gmf_obj.set_read_obj(read_obj_new);
  read_obj_new.clear();

  return gmf_obj;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<GMF03Parser> GendfInterpolator::interpolate_gmf03_data
                                         (vector<vector<GMF03Parser> >& gmf_vec,
                                          int int_val, Real temp)
{
  vector<GMF03Parser> gmf_new;
  gmf_new.clear();

  int i_max = static_cast<int>(gmf_vec.size());
  if( i_max == 0 )
  {
    return gmf_new;
  }

  int j_max = static_cast<int>(gmf_vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( j_max != static_cast<int>(gmf_vec[i].size()) )
    {
      string class_name = "GendfInterpolator";
      string func_name  = "interpolate_gmf03_data";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << j_max;
      oss04 << static_cast<int>(gmf_vec[i].size());

      string str_data01 = "Position i           : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Number of gmf_vec[0] : " + oss03.str();
      string str_data03 = "Number of gmf_vec[i] : " + oss04.str();

      vector<string> err_com;
      err_com.push_back("MF=03");
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      err_com.push_back("The number of gmf_vec[0] is not equal to that of gmf_vec[i].");
      err_com.push_back("Please check gmf_vec[0] or gmf_vec[i] data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  gmf_new.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    vector<GMF03Parser> gmf_each;
    gmf_each.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      gmf_each[i] = gmf_vec[i][j];
    }

    gmf_new[j] = interpolate_gmf03_data(gmf_each, int_val, temp);
    gmf_each.clear();
  }

  return gmf_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<GMF05Parser> GendfInterpolator::interpolate_gmf05_data
                                         (vector<vector<GMF05Parser> >& gmf_vec,
                                          int int_val, Real temp)
{
  vector<GMF05Parser> gmf_new;
  gmf_new.clear();

  int i_max = static_cast<int>(gmf_vec.size());
  if( i_max == 0 )
  {
    return gmf_new;
  }

  int j_max = static_cast<int>(gmf_vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( j_max != static_cast<int>(gmf_vec[i].size()) )
    {
      string class_name = "GendfInterpolator";
      string func_name  = "interpolate_gmf05_data";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << j_max;
      oss04 << static_cast<int>(gmf_vec[i].size());

      string str_data01 = "Position i           : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Number of gmf_vec[0] : " + oss03.str();
      string str_data03 = "Number of gmf_vec[i] : " + oss04.str();

      vector<string> err_com;
      err_com.push_back("MF=05");
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      err_com.push_back("The number of gmf_vec[0] is not equal to that of gmf_vec[i].");
      err_com.push_back("Please check gmf_vec[0] or gmf_vec[i] data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  gmf_new.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    vector<GMF05Parser> gmf_each;
    gmf_each.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      gmf_each[i] = gmf_vec[i][j];
    }

    gmf_new[j] = interpolate_gmf05_data(gmf_each, int_val, temp);
    gmf_each.clear();
  }

  return gmf_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<GMF06Parser> GendfInterpolator::interpolate_gmf06_data
                                         (vector<vector<GMF06Parser> >& gmf_vec,
                                          int int_val, Real temp)
{
  vector<GMF06Parser> gmf_new;
  gmf_new.clear();

  int i_max = static_cast<int>(gmf_vec.size());
  if( i_max == 0 )
  {
    return gmf_new;
  }

  int j_max = static_cast<int>(gmf_vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( j_max != static_cast<int>(gmf_vec[i].size()) )
    {
      string class_name = "GendfInterpolator";
      string func_name  = "interpolate_gmf06_data";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << j_max;
      oss04 << static_cast<int>(gmf_vec[i].size());

      string str_data01 = "Position i           : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Number of gmf_vec[0] : " + oss03.str();
      string str_data03 = "Number of gmf_vec[i] : " + oss04.str();

      vector<string> err_com;
      err_com.push_back("MF=06");
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      err_com.push_back("The number of gmf_vec[0] is not equal to that of gmf_vec[i].");
      err_com.push_back("Please check gmf_vec[0] or gmf_vec[i] data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  gmf_new.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    vector<GMF06Parser> gmf_each;
    gmf_each.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      gmf_each[i] = gmf_vec[i][j];
    }

    gmf_new[j] = interpolate_gmf06_data(gmf_each, int_val, temp);
    gmf_each.clear();
  }

  return gmf_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<GMF13Parser> GendfInterpolator::interpolate_gmf13_data
                                         (vector<vector<GMF13Parser> >& gmf_vec,
                                          int int_val, Real temp)
{
  vector<GMF13Parser> gmf_new;
  gmf_new.clear();

  int i_max = static_cast<int>(gmf_vec.size());
  if( i_max == 0 )
  {
    return gmf_new;
  }

  int j_max = static_cast<int>(gmf_vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( j_max != static_cast<int>(gmf_vec[i].size()) )
    {
      string class_name = "GendfInterpolator";
      string func_name  = "interpolate_gmf13_data";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << j_max;
      oss04 << static_cast<int>(gmf_vec[i].size());

      string str_data01 = "Position i           : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Number of gmf_vec[0] : " + oss03.str();
      string str_data03 = "Number of gmf_vec[i] : " + oss04.str();

      vector<string> err_com;
      err_com.push_back("MF=13");
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      err_com.push_back("The number of gmf_vec[0] is not equal to that of gmf_vec[i].");
      err_com.push_back("Please check gmf_vec[0] or gmf_vec[i] data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  gmf_new.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    vector<GMF13Parser> gmf_each;
    gmf_each.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      gmf_each[i] = gmf_vec[i][j];
    }

    gmf_new[j] = interpolate_gmf13_data(gmf_each, int_val, temp);
    gmf_each.clear();
  }

  return gmf_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<GMF16Parser> GendfInterpolator::interpolate_gmf16_data
                                         (vector<vector<GMF16Parser> >& gmf_vec,
                                          int int_val, Real temp)
{
  vector<GMF16Parser> gmf_new;
  gmf_new.clear();

  int i_max = static_cast<int>(gmf_vec.size());
  if( i_max == 0 )
  {
    return gmf_new;
  }

  int j_max = static_cast<int>(gmf_vec[0].size());
  for(int i=1; i<i_max; i++)
  {
    if( j_max != static_cast<int>(gmf_vec[i].size()) )
    {
      string class_name = "GendfInterpolator";
      string func_name  = "interpolate_gmf16_data";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << j_max;
      oss04 << static_cast<int>(gmf_vec[i].size());

      string str_data01 = "Position i           : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Number of gmf_vec[0] : " + oss03.str();
      string str_data03 = "Number of gmf_vec[i] : " + oss04.str();

      vector<string> err_com;
      err_com.push_back("MF=16");
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("");
      err_com.push_back("The number of gmf_vec[0] is not equal to that of gmf_vec[i].");
      err_com.push_back("Please check gmf_vec[0] or gmf_vec[i] data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }

  gmf_new.resize(j_max);
  for(int j=0; j<j_max; j++)
  {
    vector<GMF16Parser> gmf_each;
    gmf_each.resize(i_max);
    for(int i=0; i<i_max; i++)
    {
      gmf_each[i] = gmf_vec[i][j];
    }

    gmf_new[j] = interpolate_gmf16_data(gmf_each, int_val, temp);
    gmf_each.clear();
  }

  return gmf_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GendfParser GendfInterpolator::interpolate_gendf_data(vector<GendfParser>& gendf_vec,
                                                      int int_val, Real temp)
{
  Real temp_dif = temp * 1.0E-5;
  if( temp_dif < min_ene_dif )
  {
    temp_dif = 1.0E-5;
  }

  int i_max = static_cast<int>(gendf_vec.size());
  for(int i=0; i<i_max; i++)
  {
    if( fabs(gendf_vec[i].get_mf01_mt451_data().get_TEMP() - temp) < temp_dif )
    {
      return gendf_vec[i];
    }
  }

  if( i_max < 2 )
  {
    string class_name = "GendfInterpolator";
    string func_name  = "interpolate_gendf_data(vector<GendfParser> gendf_vec, int int_val, Real temp)";

    ostringstream oss01;
    oss01 << i_max;

    string str_data01 = "Number of GMFxxParserBase data : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("");
    err_com.push_back("The number of GMFxxParserBase data is less than or equal to one.");
    err_com.push_back("Please check the GENDF data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  GendfParser gendf_new;
  gendf_new.clear();

  GMF01MT451Parser  mf01_mt451_data = gendf_vec[0].get_mf01_mt451_data();
  mf01_mt451_data.set_TEMP(temp);
  gendf_new.set_mf01_mt451_data(mf01_mt451_data);
  mf01_mt451_data.clear();

  //MF=03
  vector<vector<GMF03Parser> > gmf03_vec;
  gmf03_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    gmf03_vec[i] = gendf_vec[i].get_mf03_data();
  }
  vector<GMF03Parser> gmf03_new = interpolate_gmf03_data(gmf03_vec, int_val, temp);
  vector<vector<GMF03Parser> >().swap(gmf03_vec);

  gendf_new.set_mf03_data(gmf03_new);
  vector<GMF03Parser>().swap(gmf03_new);

  //MF=05
  vector<vector<GMF05Parser> > gmf05_vec;
  gmf05_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    gmf05_vec[i] = gendf_vec[i].get_mf05_data();
  }
  vector<GMF05Parser> gmf05_new = interpolate_gmf05_data(gmf05_vec, int_val, temp);
  vector<vector<GMF05Parser> >().swap(gmf05_vec);

  gendf_new.set_mf05_data(gmf05_new);
  vector<GMF05Parser>().swap(gmf05_new);

  //MF=06
  vector<vector<GMF06Parser> > gmf06_vec;
  gmf06_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    gmf06_vec[i] = gendf_vec[i].get_mf06_data();
  }
  vector<GMF06Parser> gmf06_new = interpolate_gmf06_data(gmf06_vec, int_val, temp);
  vector<vector<GMF06Parser> >().swap(gmf06_vec);

  gendf_new.set_mf06_data(gmf06_new);
  vector<GMF06Parser>().swap(gmf06_new);

  //MF=13
  vector<vector<GMF13Parser> > gmf13_vec;
  gmf13_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    gmf13_vec[i] = gendf_vec[i].get_mf13_data();
  }
  vector<GMF13Parser> gmf13_new = interpolate_gmf13_data(gmf13_vec, int_val, temp);
  vector<vector<GMF13Parser> >().swap(gmf13_vec);

  gendf_new.set_mf13_data(gmf13_new);
  vector<GMF13Parser>().swap(gmf13_new);

  //MF=16
  vector<vector<GMF16Parser> > gmf16_vec;
  gmf16_vec.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    gmf16_vec[i] = gendf_vec[i].get_mf16_data();
  }
  vector<GMF16Parser> gmf16_new = interpolate_gmf16_data(gmf16_vec, int_val, temp);
  vector<vector<GMF16Parser> >().swap(gmf16_vec);

  gendf_new.set_mf16_data(gmf16_new);
  vector<GMF16Parser>().swap(gmf16_new);

  return gendf_new;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GendfParser GendfInterpolator::interpolate_gendf_data(vector<GendfParser> gendf_vec,
                                                      int int_temp, Real temp,
                                                      int int_sigz, Real sigz)
{
  int i_max = static_cast<int>(gendf_vec.size());
  for(int i=0; i<i_max; i++)
  {
    gendf_vec[i] = interpolate_gendf_data(gendf_vec[i], int_sigz, sigz);
  }

  return interpolate_gendf_data(gendf_vec, int_temp, temp);
}

