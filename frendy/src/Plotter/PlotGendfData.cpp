#include "Plotter/PlotGendfData.hpp"

using namespace frendy;

//constructor
PlotGendfData::PlotGendfData(void)
{
  clear();
}

//destructor
PlotGendfData::~PlotGendfData(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::clear()
{
  frendy_inp_obj.clear();

  graph_type = frendy_inp_obj.histogram;

  gendf_file_name.clear();
  mf_val     = -1;
  mt_val     = -1;
  temp_ori   = -1.0;

  sigz_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GendfParser PlotGendfData::read_gendf_file(string gendf_name)
{
  Integer mat = -1;
  Real temp   = -1.0;
  return read_gendf_file(gendf_name, mat, temp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GendfParser PlotGendfData::read_gendf_file(string gendf_name, Integer& mat)
{
  Real temp = -1.0;
  return read_gendf_file(gendf_name, mat, temp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GendfParser PlotGendfData::read_gendf_file(string gendf_name, Real& temp)
{
  Integer mat = -1;
  return read_gendf_file(gendf_name, mat, temp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

GendfParser PlotGendfData::read_gendf_file(string gendf_name, Integer& mat, Real& temp)
{
  cout << "****** Read GENDF file ******" << endl;
  cout << endl;

  GendfParser gendf_data;

  GendfTapeDivider div_obj;
  div_obj.set_file_name(gendf_name);

  gendf_file_name = gendf_name;

  vector<Integer> mat_list = div_obj.get_mat_list();

  int mat_no = static_cast<int>(mat_list.size());
  if( mat_no == 0 )
  {
    string class_name = "PlotGendfData";
    string func_name  = "read_gendf_file(string gendf_name, Integer& mat, Real& temp)";

    string str_data01 = "GENDF file name : " + gendf_name;

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("There is not MAT data list.");
    err_com.push_back("This file name may be incorrect.");
    err_com.push_back("Please check the file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( mat <= 0 )
  {
    mat = mat_list[0];
  }

  int mat_pos = -1;
  for(int i=0; i<mat_no; i++)
  {
    if( mat == mat_list[i] )
    {
      mat_pos = i;
      break;
    }
  }

  if( mat_pos < 0 )
  {
    string class_name = "PlotGendfData";
    string func_name  = "read_gendf_file(string gendf_name, Integer& mat, Real& temp)";

    ostringstream oss01;
    oss01 << mat;

    string str_data01 = "GENDF file name       : " + gendf_name;
    string str_data02 = "Material number (MAT) : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("This MAT number is not found in this GENDF file.");
    err_com.push_back("This file name may be incorrect.");
    err_com.push_back("Please check the file name or MAT number.");
    err_com.push_back("");
    err_com.push_back("Available MAT number is as follows:");
    for(int i=0; i<mat_no; i++)
    {
      ostringstream oss03;
      oss03 << mat_list[i];
      string str_data03 = "  " + oss03.str();
      err_com.push_back(str_data03);
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  vector<Real> temp_list = div_obj.get_temp_list(mat_list[mat_pos]);
  int temp_no = static_cast<int>(temp_list.size());
  if( temp_no == 0 )
  {
    string class_name = "PlotGendfData";
    string func_name  = "read_gendf_file(string gendf_name, Integer& mat, Real& temp)";

    ostringstream oss01;
    oss01 << mat;

    string str_data01 = "GENDF file name       : " + gendf_name;
    string str_data02 = "Material number (MAT) : " + oss01.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("There is not temperature data list.");
    err_com.push_back("This file name may be incorrect.");
    err_com.push_back("Please check the file name.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( temp < -1.0*min_value )
  {
    temp = temp_list[0];
  }
  temp_ori = temp;

  gendf_data.clear();

  int temp_pos = -1;
  for(int i=0; i<temp_no; i++)
  {
    if( fabs(temp - temp_list[i]) < min_ene_dif )
    {
      temp_pos = i;
      cout << "  Material no : " << mat << " / Temperature [K] : " << temp << endl;

      vector<string> text_data = div_obj.get_designated_temp_data(mat, temp);
      gendf_data.set_text(text_data);
      text_data.clear();

      break;
    }
  }
  cout << endl;

  if( temp_pos < 0 )
  {
    string class_name = "PlotGendfData";
    string func_name  = "read_gendf_file(string gendf_name, Integer& mat, Real& temp)";

    ostringstream oss01, oss02;
    oss01 << mat;
    oss02 << setw(8) << std::showpoint << std::scientific << temp;

    string str_data01 = "GENDF file name       : " + gendf_name;
    string str_data02 = "Material number (MAT) : " + oss01.str();
    string str_data03 = "Temperature           : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("This temperature is not found in this GENDF file.");
    err_com.push_back("This file name may be incorrect.");
    err_com.push_back("Please check the file name or temperature.");
    err_com.push_back("");
    err_com.push_back("Available temperature is as follows:");
    for(int i=0; i<temp_no; i++)
    {
      ostringstream oss04;
      oss04 << setw(8) << std::showpoint << std::scientific << temp_list[i];
      string str_data04 = "  " + oss04.str();
      err_com.push_back(str_data04);
    }

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  return gendf_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::output_1d_data(string case_name, vector<Real>& mg_vec_in,
                                   vector<vector<vector<Real> > >& xs_vec)
{
  int i_max = static_cast<int>(xs_vec.size());
  if( i_max == 0 )
  {
    return;
  }

  int sigz_no = static_cast<int>(xs_vec[0].size()); //No. of background cross sections
  for(int j=0; j<sigz_no; j++)
  {
    int pl_no = static_cast<int>(xs_vec[0][j].size()); //No. of Legendre orders
    string output_name = case_name;
    if( sigz_no > 1 )
    {
      ostringstream oss_sigz;

      int width  =  1;
      int sz_no  = 10;
      while( sigz_no >= sz_no )
      {
        sz_no *= 10;
        width++;
      }
      oss_sigz << setw(width) << setfill('0') << j+1;

      output_name = case_name + "_sigz" + oss_sigz.str();
    }

    ofstream fout;
    output_name = output_name + ".dat";
    fout.open(output_name.c_str());

    if( fout.fail() )
    {
      string class_name = "PlotGendfData";
      string func_name  = "output_1d_data";

      string str_data = "  Output file name : " + output_name;

      vector<string> err_com;
      err_com.push_back("Output file can not be open.");
      err_com.push_back("Please check the file name, directory name or access authority.");
      err_com.push_back(str_data);

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    fout.precision(8);
    fout.setf(ios::showpoint);
    fout.setf(ios::scientific);

    ostringstream oss_temp;
    oss_temp << setw(8) << std::showpoint << temp_ori;

    fout << "# Gendf file name     : " << gendf_file_name  << endl;
    fout << "# Temperature [K]     : " << oss_temp.str() << endl;
    fout << "# MF (file/data type) : " << mf_val << endl;
    fout << "# MT (reaction type)  : " << mt_val << endl;
    fout << "# sigz_no             : " << sigz_no  << " (Number of background cross sections)" << endl;
    fout << "# pl_no               : " << pl_no    << " (Number of Legendre orders)" << endl;
    fout << "#" << endl;
    fout << "# sigz_val            : " << sigz_vec[j] << endl;
    fout << "#" << endl;
    fout << "# energy [eV] / data" << endl;

    for(int i=0; i<i_max-1; i++)
    {
      fout << mg_vec_in[i];

      vector<Real> xs_vec_each;
      if( static_cast<int>(xs_vec[i].size()) > 0 )
      {
        xs_vec_each = xs_vec[i][j];
      }
      else
      {
        //If there is no background cross section data, all cross section data become 0.0.
        xs_vec_each.resize(pl_no);
        for(int k=0; k<pl_no; k++)
        {
          xs_vec_each[k] = 0.0;
        }
      }

      pl_no = static_cast<int>(xs_vec_each.size()); //No. of Legendre orders in each incident energy
      if( pl_no == 0 )
      {
         pl_no = 1;
         xs_vec_each.push_back(0.0);
      }

      for(int k=0; k<pl_no; k++)
      {
        fout << "  " << xs_vec_each[k];
      }
      fout << endl;
      if( graph_type == frendy_inp_obj.histogram )
      {
        //fout << mg_vec_in[i+1] * 0.9999999;
        fout << digit_obj.get_adjusted_value(mg_vec_in[i+1], sig_fig, -1.0); //eh of each energy grid
        for(int k=0; k<pl_no; k++)
        {
          fout << "  " << xs_vec_each[k];
        }
        fout << endl;
      }
      xs_vec_each.clear();
    }
    fout.close();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<vector<Real> > > PlotGendfData::make_xs_array(vector<Real>& xs_vec)
{
  vector<vector<vector<Real> > > xs_array;

  int i_max = static_cast<int>(xs_vec.size());
  xs_array.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    xs_array[i].resize(1);    //sigz_no
    xs_array[i][0].resize(1); //pl_no
    xs_array[i][0][0] = xs_vec[i];
  }

  return xs_array;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::output_1d_data(string case_name, vector<Real>& mg_vec_in, vector<Real>& xs_vec)
{
  vector<vector<vector<Real> > > xs_array = make_xs_array(xs_vec);

  output_1d_data(case_name, mg_vec_in, xs_array);
  xs_array.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::output_2d_data(string case_name, vector<Real>& mg_vec_in, vector<Real>& mg_vec_out,
                                   vector<vector<vector<vector<Real> > > >& ddx_vec)
{
  int e_in_no = static_cast<int>(ddx_vec.size());
  for(int i=0; i<e_in_no; i++)
  {
    //Check ddxs data
    int output_flg = 0;
    int e_out_no = static_cast<int>(ddx_vec[i].size());
    if( e_out_no == 0 )
    {
      continue;
    }

    for(int j=0; j<e_out_no; j++)
    {
      int sigz_no = static_cast<int>(ddx_vec[i][j].size());
      if( sigz_no == 0 )
      {
        break;
      }

      for(int k=0; k<sigz_no; k++)
      {
        int pl_no = static_cast<int>(ddx_vec[i][j][k].size());
        for(int l=0; l<pl_no; l++)
        {
          if( fabs(ddx_vec[i][j][k][l]) > min_value )
          {
            output_flg = 1;
            break;
          }
        }
        if( output_flg > 0 )
        {
          break;
        }
      }
      if( output_flg > 0 )
      {
        break;
      }
    }
    if( output_flg == 0 )
    {
      continue;
    }

    int width  =  1;
    int ene_no = 10;
    while( e_in_no >= ene_no )
    {
      ene_no *= 10;
      width++;
    }

    ostringstream oss_e_in;
    oss_e_in << setw(width) << setfill('0') << i+1;

    string output_name = case_name + "_mg" + oss_e_in.str();

    output_1d_data(output_name, mg_vec_out, ddx_vec[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::output_2d_data_angle(string case_name, vector<Real>& mg_vec_in,
                                         vector<Real>& mg_vec_out,
                                         vector<vector<vector<vector<Real> > > >& ddx_vec)
{
  LinearizeTabData lin_tab_obj;


  int e_in_no = static_cast<int>(ddx_vec.size());
  int width_e =  1;
  int ene_no  = 10;
  while( e_in_no >= ene_no )
  {
    ene_no *= 10;
    width_e++;
  }


  for(int i=0; i<e_in_no; i++)
  {
    int e_out_no = static_cast<int>(ddx_vec[i].size());
    for(int j=0; j<e_out_no; j++)
    {
      int sigz_no  = static_cast<int>(ddx_vec[i][j].size());
      int width_bg =  1;
      int bg_no    = 10;
      while( width_bg >= bg_no )
      {
        ene_no *= 10;
        width_bg++;
      }

      for(int k=0; k<sigz_no; k++)
      {
        vector<Real> pl_coef = ddx_vec[i][j][k];
        int pl_no = static_cast<int>(pl_coef.size());
        int zero_flg = 0;
        for(int l=0; l<pl_no; l++)
        {
          if( fabs(pl_coef[l]) > min_value )
          {
            zero_flg++;
          }
        }
        if( zero_flg == 0 )
        {
          continue;
        }

        vector<Real> x_vec, y_vec;
        lin_tab_obj.linearize_list_data_by_legendre_polynomial
                      (pl_coef, x_vec, y_vec);

        if( static_cast<int>(x_vec.size()) > 0 )
        {
          ostringstream oss_e_in, oss_e_out, oss_sigz;
          oss_e_in  << setw(width_e)  << setfill('0') << i+1;
          oss_e_out << setw(width_e)  << setfill('0') << j+1;
          oss_sigz  << setw(width_bg) << setfill('0') << k+1;

          string output_name = case_name + "_ein" + oss_e_in.str() + "_eout" + oss_e_out.str();
          if( sigz_no > 1 )
          {
            output_name = output_name + "_sigz" + oss_sigz.str();
          }

          output_1d_data(output_name, x_vec, y_vec);
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::get_1d_data(vector<int>& ig, vector<vector<vector<Real> > >& data2,
                                vector<Real>& mg_vec_in, vector<vector<vector<Real> > >& xs_vec)
{
  int ene_no = static_cast<int>(mg_vec_in.size());
  xs_vec.resize(ene_no);

  int i_max = static_cast<int>(ig.size());
  if( i_max == 0 )
  {
    return;
  }

  for(int i=0; i<i_max; i++)
  {
    int e_pos = ig[i] - 1;
    if( e_pos < 0 )
    {
      continue;
    }
    else if( e_pos >= ene_no )
    {
      string class_name = "PlotGendfData";
      string func_name  = "get_1d_data";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << ene_no;
      oss04 << ig[i];
      string str_data01 = "Position : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "  Maximum number of energy grids : " + oss03.str();
      string str_data03 = "  IG value at " + oss01.str() + " : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("The maximum number of energy grids is smaller than IG value.");
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("Please check the GENDF file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int j_max = static_cast<int>(data2[i].size());
    xs_vec[e_pos].resize(j_max);
    if( j_max == 0 )
    {
      string class_name = "PlotGendfData";
      string func_name  = "get_1d_data";

      ostringstream oss01, oss02, oss03;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << ig[i];
      string str_data01 = "Position : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "The number of sigz data of Data1 at " + oss03.str() + " group is zero.";

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("Please check the GENDF file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(data2[i][j].size());
      if( static_cast<int>(data2[i][j].size()) == 0 )
      {
        string class_name = "PlotGendfData";
        string func_name  = "get_1d_data";

        ostringstream oss01, oss02, oss03, oss04, oss05;
        oss01 << i+1;
        oss02 << i_max;
        oss03 << j+1;
        oss04 << j_max;
        oss05 << ig[i];
        string str_data01 = "Position : " + oss01.str() + " / " + oss02.str() + ", "
                                          + oss03.str() + " / " + oss04.str();
        string str_data02 = "The number of legendre orders of Data1 at " + oss03.str() + " group is zero.";

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back("Please check the GENDF file.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }

      xs_vec[e_pos][j].resize(k_max);
      for(int k=0; k<k_max; k++)
      {
        xs_vec[e_pos][j][k] = data2[i][j][k];
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::get_2d_data(vector<int>& ig, vector<int>& ng2, vector<int>& ig2,
                                vector<vector<vector<vector<Real> > > >& data2,
                                vector<Real>& mg_vec_in, vector<Real>& mg_vec_out,
                                vector<vector<vector<vector<Real> > > >& ddx_vec)
{
  vector<vector<vector<vector<Real> > > >().swap(ddx_vec);

  //Set sigz_no and pl_no
  int sigz_no = 0; //No. of background cross sections
  int pl_no   = 0; //No. of Legendre orders
  int i_max   = static_cast<int>(ig.size());
  for(int i=0; i<i_max; i++)
  {
    int e_pos = ig[i] - 1;
    if( e_pos < 0 )
    {
      continue;
    }

    sigz_no = static_cast<int>(data2[i].size());
    if( sigz_no == 0 )
    {
      string class_name = "PlotGendfData";
      string func_name  = "get_2d_data";

      ostringstream oss01, oss02, oss03;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << ig[i];
      string str_data01 = "Position : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "The number of sigz data of DATA2 at " + oss03.str() + " group is zero.";

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("Please check the GENDF file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    pl_no = static_cast<int>(data2[i][0].size());
    if( pl_no == 0 )
    {
      string class_name = "PlotGendfData";
      string func_name  = "get_2d_data";

      ostringstream oss01, oss02, oss03;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << ig[i];
      string str_data01 = "Position : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "The number of legendre orders of DATA2 at " + oss03.str() + " group is zero.";

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("Please check the GENDF file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    break;
  }

  //Set initial ddx data
  int ene_in_no  = static_cast<int>(mg_vec_in.size());
  int ene_out_no = static_cast<int>(mg_vec_out.size());
  ddx_vec.resize(ene_in_no);
  for(int i=0; i<ene_in_no; i++)
  {
    ddx_vec[i].resize(ene_out_no);
    for(int j=0; j<ene_out_no; j++)
    {
      ddx_vec[i][j].resize(sigz_no);
      for(int k=0; k<sigz_no; k++)
      {
        ddx_vec[i][j][k].resize(pl_no);
        for(int l=0; l<pl_no; l++)
        {
          ddx_vec[i][j][k][l] = 0.0;
        }
      }
    }
  }

  //Copy ddx data
  for(int i=0; i<i_max; i++)
  {
    int e_pos = ig[i] - 1;
    if( e_pos < 0 )
    {
      continue;
    }
    else if( e_pos >= ene_in_no )
    {
      string class_name = "PlotGendfData";
      string func_name  = "get_2d_data";

      ostringstream oss01, oss02, oss03, oss04;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << ene_in_no;
      oss04 << ig[i];
      string str_data01 = "Position : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "  Maximum number of energy grids : " + oss03.str();
      string str_data03 = "  IG value at " + oss01.str() + " : " + oss04.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("The maximum number of incident energy grids is smaller than IG value.");
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back("Please check the GENDF file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( (ig2[i] - 1) + (ng2[i] - 1) >= ene_out_no )
    {
      string class_name = "PlotGendfData";
      string func_name  = "get_2d_data";

      ostringstream oss01, oss02, oss03, oss04, oss05;
      oss01 << i+1;
      oss02 << i_max;
      oss03 << ene_in_no;
      oss04 << ig2[i];
      oss05 << ng2[i];
      string str_data01 = "Position : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "  Maximum number of energy grids : " + oss03.str();
      string str_data03 = "  IG2 value at " + oss01.str() + " : " + oss04.str();
      string str_data04 = "  NG2 value at " + oss01.str() + " : " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("The maximum number of outgoing energy grids is smaller than IG2 + NG2 value.");
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back("Please check the GENDF file.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    if( ig2[i] > 0 )
    {
      int ng2_sta = ig2[i] - 1;
      for(int j=0; j<ng2[i]-1; j++)
      {
        for(int k=0; k<sigz_no; k++)
        {
          for(int l=0; l<pl_no; l++)
          {
            ddx_vec[e_pos][j+ng2_sta][k][l] = data2[i][k][l][j];
          }
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::get_1d_data_from_2d_data(vector<int>& ig, vector<int>& ng2, vector<int>& ig2,
                                             vector<vector<vector<vector<Real> > > >& data2,
                                             vector<Real>& mg_vec_in, vector<Real>& mg_vec_out,
                                             vector<vector<vector<Real> > >& xs_vec)
{
  vector<vector<vector<Real> > >().swap(xs_vec);

  //Set sigz_no and pl_no
  int sigz_no = 0; //No. of background cross sections
  int pl_no   = 0; //No. of Legendre orders
  int i_max   = static_cast<int>(ig.size());
  for(int i=0; i<i_max; i++)
  {
    int e_pos = ig[i] - 1;
    if( e_pos < 0 )
    {
      continue;
    }

    sigz_no = static_cast<int>(data2[i].size());
    pl_no = static_cast<int>(data2[i][0].size());
    break;
  }

  //Set initial xs data
  int ene_in_no  = static_cast<int>(mg_vec_in.size());
  xs_vec.resize(ene_in_no);
  for(int i=0; i<ene_in_no; i++)
  {
    xs_vec[i].resize(sigz_no);
    for(int j=0; j<sigz_no; j++)
    {
      xs_vec[i][j].resize(pl_no);
      for(int k=0; k<pl_no; k++)
      {
        xs_vec[i][j][k] = 0.0;
      }
    }
  }

  //Copy xs data
  for(int i=0; i<i_max; i++)
  {
    int e_pos = ig[i] - 1;
    if( e_pos < 0 )
    {
      continue;
    }

    if( ig2[i] > 0 )
    {
      for(int j=0; j<ng2[i]-1; j++)
      {
        for(int k=0; k<sigz_no; k++)
        {
          for(int l=0; l<pl_no; l++)
          {
            xs_vec[e_pos][k][l] += data2[i][k][l][j];
          }
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::read_gmf03_data(string& out_name, string& gendf_name, GendfParser& gendf_obj,
                                    vector<Integer>& mt_list)
{
  vector<GMF03Parser> mf_data_obj = gendf_obj.get_mf03_data();

  //For MF=3
  vector<Real>        mg_vec_in   = gendf_obj.get_mf01_mt451_data().get_EGN();
  vector<Real>        mg_vec_out  = gendf_obj.get_mf01_mt451_data().get_EGN();

  int i_max = static_cast<int>(mt_list.size());
  int j_max = static_cast<int>(mf_data_obj.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      if( mt_list[i] > 250 && mt_list[i] < 260 )
      {
        //Skip output XS data when MT data is equal to following MT numbers.
        //259 Average inverse neutron velocity for group in s/m.
        //258 Average lethargy for group.
        //251 Average elastic scattering cosine computed from File 4.
        //252 Continuous-slowing-down parameter (average logarithmic energy decrement
        //    for elastic scattering) computed from File 4.
        //253 Continuous-slowing-down parameter (the average of the square of the
        //    logarithmic energy decrement for elastic scattering, divided by twice
        //    the average logarithmic energy decrement for elastic scattering) computed from File 4.
        continue;
      }

      cout << "      MT =" << setw(5) << setfill(' ') << mt_list[i] << endl;

      int mt_flg = 0;
      for(int j=0; j<j_max; j++)
      {
        if( mt_list[i] == mf_data_obj[j].get_mt_no() )
        {
          mt_flg = 1;

          output_gmf_data(out_name, gendf_name, mf_data_obj[j].get_read_obj(), mg_vec_in, mg_vec_out);
          break;
        }
      }

      if( mt_flg == 0 )
      {
        cout << "      This MT number is not found." << endl;
      }
    }
  }
  else
  {
    for(int j=0; j<j_max; j++)
    {
      if( mf_data_obj[j].get_mt_no() != unassigned_mt_no )
      {
        if( mf_data_obj[j].get_mt_no() <= 250 || mf_data_obj[j].get_mt_no() >= 260 )
        {
          cout << "      MT =" << setw(5) << setfill(' ') << mf_data_obj[j].get_mt_no() << endl;
          output_gmf_data(out_name, gendf_name, mf_data_obj[j].get_read_obj(), mg_vec_in, mg_vec_out);
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::read_gmf05_data(string& out_name, string& gendf_name, GendfParser& gendf_obj,
                                    vector<Integer>& mt_list)
{
  vector<GMF05Parser> mf_data_obj = gendf_obj.get_mf05_data();

  //For MF=5
  vector<Real>        mg_vec_in   = gendf_obj.get_mf01_mt451_data().get_EGN();
  vector<Real>        mg_vec_out  = gendf_obj.get_mf01_mt451_data().get_EGN();

  int i_max = static_cast<int>(mt_list.size());
  int j_max = static_cast<int>(mf_data_obj.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      cout << "      MT =" << setw(5) << setfill(' ') << mt_list[i] << endl;

      int mt_flg = 0;
      for(int j=0; j<j_max; j++)
      {
        if( mt_list[i] == mf_data_obj[j].get_mt_no() )
        {
          mt_flg = 1;

          output_gmf_data(out_name, gendf_name, mf_data_obj[j].get_read_obj(), mg_vec_in, mg_vec_out);
          break;
        }
      }

      if( mt_flg == 0 )
      {
        cout << "      This MT number is not found." << endl;
      }
    }
  }
  else
  {
    for(int j=0; j<j_max; j++)
    {
      if( mf_data_obj[j].get_mt_no() != unassigned_mt_no )
      {
        cout << "      MT =" << setw(5) << setfill(' ') << mf_data_obj[j].get_mt_no() << endl;
        output_gmf_data(out_name, gendf_name, mf_data_obj[j].get_read_obj(), mg_vec_in, mg_vec_out);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::read_gmf06_data(string& out_name, string& gendf_name, GendfParser& gendf_obj,
                                    vector<Integer>& mt_list)
{
  vector<GMF06Parser> mf_data_obj = gendf_obj.get_mf06_data();

  //For MF=6
  vector<Real>        mg_vec_in   = gendf_obj.get_mf01_mt451_data().get_EGN();
  vector<Real>        mg_vec_out  = gendf_obj.get_mf01_mt451_data().get_EGN();

  int i_max = static_cast<int>(mt_list.size());
  int j_max = static_cast<int>(mf_data_obj.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      cout << "      MT =" << setw(5) << setfill(' ') << mt_list[i] << endl;

      int mt_flg = 0;
      for(int j=0; j<j_max; j++)
      {
        if( mt_list[i] == mf_data_obj[j].get_mt_no() )
        {
          mt_flg = 1;

          output_gmf_data(out_name, gendf_name, mf_data_obj[j].get_read_obj(), mg_vec_in, mg_vec_out);
          break;
        }
      }

      if( mt_flg == 0 )
      {
        cout << "      This MT number is not found." << endl;
      }
    }
  }
  else
  {
    for(int j=0; j<j_max; j++)
    {
      if( mf_data_obj[j].get_mt_no() != unassigned_mt_no )
      {
        cout << "      MT =" << setw(5) << setfill(' ') << mf_data_obj[j].get_mt_no() << endl;
        output_gmf_data(out_name, gendf_name, mf_data_obj[j].get_read_obj(), mg_vec_in, mg_vec_out);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::read_gmf13_data(string& out_name, string& gendf_name, GendfParser& gendf_obj,
                                    vector<Integer>& mt_list)
{
  vector<GMF13Parser> mf_data_obj = gendf_obj.get_mf13_data();

  //For MF=13
  vector<Real>        mg_vec_in   = gendf_obj.get_mf01_mt451_data().get_EGN();
  vector<Real>        mg_vec_out  = gendf_obj.get_mf01_mt451_data().get_EGG();

  int i_max = static_cast<int>(mt_list.size());
  int j_max = static_cast<int>(mf_data_obj.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      cout << "      MT =" << setw(5) << setfill(' ') << mt_list[i] << endl;

      int mt_flg = 0;
      for(int j=0; j<j_max; j++)
      {
        if( mt_list[i] == mf_data_obj[j].get_mt_no() )
        {
          mt_flg = 1;

          output_gmf_data(out_name, gendf_name, mf_data_obj[j].get_read_obj(), mg_vec_in, mg_vec_out);
          break;
        }
      }

      if( mt_flg == 0 )
      {
        cout << "      This MT number is not found." << endl;
      }
    }
  }
  else
  {
    for(int j=0; j<j_max; j++)
    {
      if( mf_data_obj[j].get_mt_no() != unassigned_mt_no )
      {
        cout << "      MT =" << setw(5) << setfill(' ') << mf_data_obj[j].get_mt_no() << endl;
        output_gmf_data(out_name, gendf_name, mf_data_obj[j].get_read_obj(), mg_vec_in, mg_vec_out);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::read_gmf16_data(string& out_name, string& gendf_name, GendfParser& gendf_obj,
                                    vector<Integer>& mt_list)
{
  vector<GMF16Parser> mf_data_obj = gendf_obj.get_mf16_data();

  //For MF=16
  vector<Real>        mg_vec_in   = gendf_obj.get_mf01_mt451_data().get_EGN();
  vector<Real>        mg_vec_out  = gendf_obj.get_mf01_mt451_data().get_EGG();

  int i_max = static_cast<int>(mt_list.size());
  int j_max = static_cast<int>(mf_data_obj.size());
  if( i_max > 0 )
  {
    for(int i=0; i<i_max; i++)
    {
      cout << "      MT =" << setw(5) << setfill(' ') << mt_list[i] << endl;

      int mt_flg = 0;
      for(int j=0; j<j_max; j++)
      {
        if( mt_list[i] == mf_data_obj[j].get_mt_no() )
        {
          mt_flg = 1;

          output_gmf_data(out_name, gendf_name, mf_data_obj[j].get_read_obj(), mg_vec_in, mg_vec_out);
          break;
        }
      }

      if( mt_flg == 0 )
      {
        cout << "      This MT number is not found." << endl;
      }
    }
  }
  else
  {
    for(int j=0; j<j_max; j++)
    {
      if( mf_data_obj[j].get_mt_no() != unassigned_mt_no )
      {
        cout << "      MT =" << setw(5) << setfill(' ') << mf_data_obj[j].get_mt_no() << endl;
        output_gmf_data(out_name, gendf_name, mf_data_obj[j].get_read_obj(), mg_vec_in, mg_vec_out);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::output_gmf_data(string& out_name, string& gendf_name, GMFxxParserBase gmf_obj,
                                    vector<Real> mg_vec_in, vector<Real> mg_vec_out)
{
  mf_val = gmf_obj.get_mf_no();
  mt_val = gmf_obj.get_mt_no();

  //Set case name
  StringUtils str_obj;
  string gendf_case = str_obj.basename_without_suffix(gendf_name);

  ostringstream oss_mf, oss_mt;
  oss_mf << setw(2) << setfill('0') << mf_val;
  oss_mt << setw(3) << setfill('0') << mt_val;

  string case_name = out_name;
  if( static_cast<int>(case_name.length()) == 0 )
  {
    case_name = gendf_case;
  }
  case_name = case_name + "_mf" + oss_mf.str() + "_mt" + oss_mt.str();

  //Copy data
  vector<int> ig    = gmf_obj.get_IG();
  vector<int> ng2   = gmf_obj.get_NG2();
  vector<int> ig2   = gmf_obj.get_IG2LO();
  //Real        temp  = gmf_obj.get_TEMP();

  int ddx_flg = 1;
  if( mf_val == 3 || mf_val == 13 )
  {
     ddx_flg = 0;
     if( mt_val == 452 || mt_val == 455 || mt_val == 456 ) //nu-t, nu-d, nu-p
     {
       ddx_flg = 1;
     }
  }


  if( ddx_flg == 0 ) //For 1-dimensional data (like XS)
  {
    vector<vector<vector<Real> > > data2 = gmf_obj.get_DATA2();

    vector<vector<vector<Real> > > xs_vec;
    get_1d_data(ig, data2, mg_vec_in, xs_vec);

    output_1d_data(case_name, mg_vec_in, xs_vec);
    vector<vector<vector<Real> > >().swap(xs_vec);
  }
  else //if( ddx_flg == 1 ) //For 2-dimensional data (like DDX)
  {
    vector<vector<vector<vector<Real> > > > data2 = gmf_obj.get_DATA2_NG2();

    vector<vector<vector<Real> > >          xs_vec;
    vector<vector<vector<vector<Real> > > > ddx_vec;
    get_2d_data(ig, ng2, ig2, data2, mg_vec_in, mg_vec_out, ddx_vec);
    get_1d_data_from_2d_data(ig, ng2, ig2, data2, mg_vec_in, mg_vec_out, xs_vec);

    output_2d_data(case_name, mg_vec_in, mg_vec_out, ddx_vec);
    output_2d_data_angle(case_name, mg_vec_in, mg_vec_out, ddx_vec);
    vector<vector<vector<vector<Real> > > >().swap(ddx_vec);

    output_1d_data(case_name, mg_vec_in, xs_vec);
    vector<vector<vector<Real> > >().swap(xs_vec);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::output_gendf_data(string& out_name, string& gendf_name,
                                      GendfParser& gendf_obj, Integer& mat, Real& temp,
                                      vector<Integer>& mf_list, vector<Integer>& mt_list,
                                      int graph_type_flg)
{
  cout << "****** Output double differential cross section data ******" << endl;
  cout << endl;

  cout << "GENDF file name : " << gendf_name << endl;

  set_graph_type(graph_type_flg);

  ostringstream oss_mat, oss_temp;
  oss_mat  << mat;
  oss_temp << setw(6) << std::showpoint << temp;

  string mat_str  = oss_mat.str();
  string temp_str = oss_temp.str();
  if( mat < 1000 )
  {
    mat_str = "0" + mat_str;
    if( mat < 100 )
    {
      mat_str = "0" + mat_str;
      if( mat < 10 )
      {
        mat_str = "0" + mat_str;
      }
    }
  }

  string output_name = gendf_name + "_mat" + mat_str + "_temp" + temp_str;
  cout << "  MAT = " << mat_str << " / TEMP = " << temp_str << endl;

  int i_max = static_cast<int>(mf_list.size());
  if( i_max == 0 )
  {
    //This program only outputs cross section data in MF=3 if mf_list is empty.
    mf_list.push_back(3);
    i_max = static_cast<int>(mf_list.size());
  }

  sigz_vec = gendf_obj.get_mf01_mt451_data().get_SIGZ();

  for(int i=0; i<i_max; i++)
  {
    cout << "    MF = " << mf_list[i] << endl;
    if( mf_list[i] == 3 )
    {
      read_gmf03_data(out_name, output_name, gendf_obj, mt_list);
    }
    else if( mf_list[i] == 5 )
    {
      read_gmf05_data(out_name, output_name, gendf_obj, mt_list);
    }
    else if( mf_list[i] == 6 )
    {
      read_gmf06_data(out_name, output_name, gendf_obj, mt_list);
    }
    else if( mf_list[i] == 13 )
    {
      read_gmf13_data(out_name, output_name, gendf_obj, mt_list);
    }
    else if( mf_list[i] == 16 )
    {
      read_gmf16_data(out_name, output_name, gendf_obj, mt_list);
    }
    else
    {
      cout << "    This MF number is not available in this program." << endl;
      cout << "    The available MF number is MF=3, 5, 6, 13, and 16." << endl;
    }
  }
  cout << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::output_gendf_data(string& out_name, string& gendf_name, Integer& mat, Real& temp,
                                      vector<Integer>& mf_list, vector<Integer>& mt_list,
                                      int graph_type_flg)
{
  GendfParser gendf_obj = read_gendf_file(gendf_name, mat, temp);

  output_gendf_data(out_name, gendf_name, gendf_obj, mat, temp, mf_list, mt_list, graph_type_flg);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void PlotGendfData::set_graph_type(int graph_type_flg)
{
  graph_type = graph_type_flg;

  if( graph_type != frendy_inp_obj.one_point &&
      graph_type != frendy_inp_obj.two_point ) //two_point = histogram
  {
    string class_name = "PlotGendfData";
    string func_name  = "set_graph_type(int graph_type_flg)";

    ostringstream oss01, oss02, oss03;
    oss01 << graph_type_flg;
    oss02 << frendy_inp_obj.one_point;
    oss03 << frendy_inp_obj.two_point;

    string str_data01 = "graph_type_flg        : " + oss01.str();
    string str_data02 = "one point             : " + oss02.str();
    string str_data03 = "two point (histogram) : " + oss03.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("");
    err_com.push_back("This graph_type_flg is not available in this program.");
    err_com.push_back("Available graph_type_flg is histogram, two_point, and one_point.");
    err_com.push_back("Please check the edit_flg.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

int PlotGendfData::get_graph_type()
{
  return graph_type;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real PlotGendfData::get_temp_ori()
{
  return temp_ori;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

