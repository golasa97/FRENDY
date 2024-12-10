#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "EndfUtils/EndfFileReader/MultiParser.hpp"
#include "EndfUtils/EndfFileReader/EndfFileReader.hpp"

using namespace frendy;

////////////////////////////////////////////////////////////////////////////////////////////////////

int read_za_data(vector<string> text)
{
  //Read energy grid data from MF=1/MT=451
  MultiParser mp_obj;

  vector<Real>    r_vec, e_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  int line_no = 0;

  //Read first line (head / cont data)
  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);

  return static_cast<int>(round(r_vec[0]));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> read_ene_data(vector<string> text)
{
  //Read energy grid data from MF=1/MT=451
  MultiParser mp_obj;

  vector<Real>    r_vec, e_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  int line_no = 0;

  //Read first line (head / cont data)
  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);

  //Check GENDF format
  if( i_vec[2] != -11 )
  {
    string class_name = "read_cov_data.cpp";
    string func_name  = "vector<Real> read_ene_data(vector<string> text)";

    vector<string> err_com;
    err_com.push_back("This GENDF file may not be a covariance data file.");
    err_com.push_back("Please check the GENDF file or modify this program.");

    ErrorManager err_obj;
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  //Read second line (list data)
  mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3], e_vec);

  //Remove text data
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);

  return e_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void read_cov_data(vector<string> text, vector<Real> ene_data,
                   vector<Integer>& cov_mt_list, vector<vector<vector<Real> > >& cov_data_list)
{
  int ene_no_ori = static_cast<int>(ene_data.size()) - 1;

  //Read energy grid data from MF=1/MT=451
  MultiParser mp_obj;

  vector<Real>    r_vec, e_vec;
  vector<Integer> i_vec;
  r_vec.resize(6);
  i_vec.resize(6);

  int line_no = 0;

  //Read first line (head / cont data)
  mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);

  int cov_mt_no = i_vec[3];
  cov_mt_list.resize(cov_mt_no);
  cov_data_list.resize(cov_mt_no);
  for(int i=0; i<cov_mt_no; i++)
  {
    //Read second line (cont data)
    mp_obj.read_cont(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3]);

    cov_mt_list[i] = i_vec[1];

     //Check energy grid number between MF=1/MT=451 and MF=33
    if( i_vec[3] != ene_no_ori )
    {
      string class_name = "read_cov_data.cpp";
      string func_name  = "read_cov_data";

      ostringstream oss01, oss02;
      oss01 << ene_no_ori;
      oss02 << i_vec[3];

      string str_data01 = "Energy grid number from MF=1/MT=451 : " + oss01.str();
      string str_data02 = "Energy grid number from MF=33       : " + oss02.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("Energy grid number from MF=1/MT=451 is different to that from MF=33.");
      err_com.push_back("This GENDF file may be incorrect.");
      err_com.push_back("Please check the GENDF file or modify this program.");

      ErrorManager err_obj;
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    //Initializa cov_data_list
    cov_data_list[i].resize(ene_no_ori);
    for(int j=0; j<ene_no_ori; j++)
    {
      cov_data_list[i][j].resize(ene_no_ori);
      for(int k=0; k<ene_no_ori; k++)
      {
        cov_data_list[i][j][k] = 0.0;
      }
    }

    for(int j=0; j<ene_no_ori; j++)
    {
      //Read third line (list data)
      mp_obj.read_list(text, line_no, r_vec[0], r_vec[1], i_vec[0], i_vec[1], i_vec[2], i_vec[3], e_vec);
      j = i_vec[3] - 1;

      int ene_sta_no = i_vec[1] - 1;
      for(int k=0; k<i_vec[2]; k++)
      {
        cov_data_list[i][j][ene_sta_no+k] = e_vec[k];
      }
    }
  }

  //Remove text data
  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void ene_order_check(vector<Real>& ene_data, vector<vector<vector<vector<Real> > > >& cov_data)
{
  int i_max = static_cast<int>(ene_data.size());
  if( i_max <= 1 )
  {
    return;
  }

  int ene_order = 1;
  if( ene_data[0] > ene_data[1] )
  {
    ene_order = -1;
  } 
  if( ene_order == -1 )
  {
    return;
  }
  //Checking energy order at all energy grid is skipped.
  //(e[0] and e[1] is only checked.)

  vector<Real>                            ene_data_ori = ene_data;
  vector<vector<vector<vector<Real> > > > cov_data_ori = cov_data;

  //Modify order of ene_data
  for(int i=0; i<i_max; i++)
  {
    ene_data[i] = ene_data_ori[i_max-1-i];
  }
  ene_data_ori.clear();

  //Modify order of cov_data
  i_max = static_cast<int>(cov_data.size());
  for(int i=0; i<i_max; i++)
  {
    int j_max = static_cast<int>(cov_data[i].size());
    for(int j=0; j<j_max; j++)
    {
      int k_max = static_cast<int>(cov_data[i][j].size());
      for(int k=0; k<k_max; k++)
      {
        int l_max = static_cast<int>(cov_data[i][j][k].size());
        for(int l=0; l<l_max; l++)
        {
          cov_data[i][j][k][l] = cov_data_ori[i][j][k_max-1-k][l_max-1-l];
        }
      }
    }
  }
  cov_data_ori.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void check_mt_output_list(vector<Integer> mt_output_list, vector<Integer> mt_list,
                          vector<vector<Integer> > cov_mt_list )
{
  //Check whether user input mt number is exist in GENDF file or not.
  int i_max = static_cast<int>(mt_output_list.size());
  for(int i=0; i<i_max; i++)
  {
    int mt_flg = 0;
    int j_max  = static_cast<int>(mt_list.size());
    for(int j=0; j<j_max; j++)
    {
      if( mt_output_list[i] == mt_list[j] )
      {
        mt_flg = 1;
        break;
      }

      int k_max = static_cast<int>(cov_mt_list[j].size());
      for(int k=0; k<k_max; k++)
      {
        if( mt_output_list[i] == cov_mt_list[j][k] )
        {
          mt_flg = 10;
          break;
        }
      }

      if( mt_flg > 0 )
      {
        break;
      }
    }

    if( mt_flg == 0 )
    {
      string class_name = "read_cov_data.cpp";
      string func_name  = "check_mt_output_list";

      ostringstream oss01;
      oss01 << mt_output_list[i];

      string str_data01 = "MT number : " + oss01.str();
      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back("This MT number is not found in GENDF file.");
      err_com.push_back("Please check the GENDF file or modify MT number.");

      ErrorManager err_obj;
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real> > merge_cov_data(vector<vector<vector<vector<Real> > > > cov_data_ori)
{
  vector<vector<Real> > cov_data_mod;

  int mt_no = static_cast<int>(cov_data_ori.size());
  if( mt_no == 0 )
  {
    return cov_data_mod;
  }

  int ene_no = static_cast<int>(cov_data_ori[0][0].size());

  int ele_no = mt_no * ene_no;
  cov_data_mod.resize(ele_no);
  for(int i=0; i<ele_no; i++)
  {
    cov_data_mod[i].resize(ele_no);
  }

  for(int i=0; i<mt_no; i++)
  {
    for(int j=0; j<mt_no; j++)
    {
      for(int k=0; k<ene_no; k++)
      {
        for(int l=0; l<ene_no; l++)
        {
          int x_pos = i * ene_no + k;
          int y_pos = j * ene_no + l;

          cov_data_mod[x_pos][y_pos] = cov_data_ori[i][j][k][l];
        }
      }
    }
  }

  return cov_data_mod;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<Real> > get_specified_cov_data(vector<Real> ene_data,
                                             vector<Integer> mt_output_list, vector<Integer> mt_list, 
                                             vector<vector<Integer> > cov_mt_list,
                                             vector<vector<vector<vector<Real> > > > cov_data_list)
{
  sort(mt_output_list.begin(), mt_output_list.end());
  check_mt_output_list(mt_output_list, mt_list, cov_mt_list);

  int ene_no = static_cast<int>(ene_data.size()) - 1;
  vector<vector<Real> > cov_data_zero;
  cov_data_zero.resize(ene_no);
  for(int i=0; i<ene_no; i++)
  {
    cov_data_zero[i].resize(ene_no);
    for(int j=0; j<ene_no; j++)
    {
      cov_data_zero[i][j] = 0.0;
    }
  }

  vector<vector<vector<vector<Real> > > > cov_data_list_specified;

  int mt_out_no = static_cast<int>(mt_output_list.size());
  cov_data_list_specified.resize(mt_out_no);
  for(int i=0; i<mt_out_no; i++)
  {
    cov_data_list_specified[i].resize(mt_out_no);
    for(int j=0; j<mt_out_no; j++)
    {
      int set_flg = 0;
      for(int k=0; k<static_cast<int>(mt_list.size()); k++)
      {
        if( mt_list[k] == mt_output_list[i] )
        {
          for(int l=0; l<static_cast<int>(cov_mt_list[k].size()); l++)
          {
            if( cov_mt_list[k][l] == mt_output_list[j] )
            {
              set_flg = 1;
              cov_data_list_specified[i][j] = cov_data_list[k][l];
              break;
            }
          }
          break;
        }
      }

      if( set_flg == 0 )
      {
        cov_data_list_specified[i][j] = cov_data_zero;
      }
    }
  }

  return merge_cov_data(cov_data_list_specified);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void write_cov_data(vector<Real> ene_data, vector<Integer> mt_list, 
                    vector<vector<Integer> > cov_mt_list,
                    vector<vector<vector<vector<Real> > > > cov_data_list)
{
  int ene_no = static_cast<int>(ene_data.size());
  cout.precision(6);
  cout.setf(ios::showpoint);
  cout.setf(ios::scientific);

  cout << endl;
  cout << "Energy grid structure (ng = " << ene_no - 1 << ")" << endl;
  cout << "  ";
  for(int i=0; i<ene_no; i++)
  {
    cout << ene_data[i] << " ";
  }
  cout << endl << endl;

  int mt_no = static_cast<int>(cov_mt_list.size());
  for(int i=0; i<mt_no; i++)
  {
    cout << "MT = " << mt_list[i] << endl;
    int j_max = static_cast<int>(cov_mt_list[i].size());
    for(int j=0; j<j_max; j++)
    {
      cout << "  MT = " << mt_list[i] << " / " << cov_mt_list[i][j] << endl;
      int k_max = static_cast<int>(cov_data_list[i][j].size());
      for(int k=0; k<k_max; k++)
      {
        cout << "   ";
        for(int l=0; l<k_max; l++)
        {
          cout << " " << cov_data_list[i][j][k][l];
        }
        cout << endl;
      }
      cout << endl << endl;
    }
    cout << endl; 
    cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl; 
    cout << endl; 
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void write_cov_data_to_file(string output_case_name,
                            vector<Real> ene_data, vector<Integer> mt_list,
                            vector<vector<Integer> > cov_mt_list,
                            vector<vector<vector<vector<Real> > > > cov_data_list)
{
  string output_name = output_case_name + "_all_cov.dat";

  ofstream fout;
  fout.open(output_name.c_str());

  int ene_no = static_cast<int>(ene_data.size());
  fout.precision(6);
  fout.setf(ios::showpoint);
  fout.setf(ios::scientific);

  fout << endl;
  fout << "Energy grid structure (ng = " << ene_no - 1 << ")" << endl;
  fout << "  ";
  for(int i=0; i<ene_no; i++)
  {
    fout << ene_data[i] << " ";
  }
  fout << endl << endl;

  int mt_no = static_cast<int>(cov_mt_list.size());
  for(int i=0; i<mt_no; i++)
  {
    fout << "MT = " << mt_list[i] << endl;
    int j_max = static_cast<int>(cov_mt_list[i].size());
    for(int j=0; j<j_max; j++)
    {
      fout << "  MT = " << mt_list[i] << " / " << cov_mt_list[i][j] << endl;
      int k_max = static_cast<int>(cov_data_list[i][j].size());
      for(int k=0; k<k_max; k++)
      {
        fout << "   ";
        for(int l=0; l<k_max; l++)
        {
          fout << " " << cov_data_list[i][j][k][l];
        }
        fout << endl;
      }
      fout << endl << endl;
    }
    fout << endl;
    fout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    fout << endl;
  }

  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void write_cov_data_specified_mt(string output_case_name, vector<Integer> mt_output_list,
                                 int za_data, vector<Real> ene_data, vector<Integer> mt_list,
                                 vector<vector<Integer> > cov_mt_list,
                                 vector<vector<vector<vector<Real> > > > cov_data_list)
{
  string output_name_ene = output_case_name + "_inp.dat";
  string output_name_cov = output_case_name + "_cov.csv";

  //Output energy structure and MT data
  //(Input for random sampling tool)
  ofstream fout;
  fout.open(output_name_ene.c_str());

  fout.precision(8);
  fout.setf(ios::showpoint);
  fout.setf(ios::scientific);

  fout << "//General inforamtion"          << endl;
  fout << "  <sample_size>           100"  << endl;
  fout << "  <seed>                12345"  << endl;
  fout << "  <relative_covariance> "  << output_name_cov << endl;
  fout << "  <nuclide>             ( " << za_data << " )" << endl;
  fout << endl;

  fout << "//MT information" << endl;
  fout << "  <reaction> (";
  sort(mt_output_list.begin(), mt_output_list.end());
  for(int i=0; i<static_cast<int>(mt_output_list.size()); i++)
  {
    fout << " " << mt_output_list[i] << " ";
  }
  fout << ")" << endl;
  fout << endl;

  fout << "//Energy grid structure" << endl;
  int ene_no = static_cast<int>(ene_data.size());
  for(int i=0; i<ene_no; i++)
  {
    Real ene_val = ene_data[i] * unit_micro; //eV -> MeV
    if( i==0 )
    {
      fout << "  <energy_grid>         (" << ene_val << endl;
    }
    else if( i==ene_no-1 )
    {
      fout << "                         " << ene_val << ")" << endl;
    }
    else
    {
      fout << "                         " << ene_val << endl;
    }
  }
  fout << endl;
  fout.close();


  //Output covariance data
  vector<vector<Real> > cov_data = get_specified_cov_data
                                     (ene_data, mt_output_list, mt_list, cov_mt_list,
                                      cov_data_list);

  fout.open(output_name_cov.c_str());

  fout.precision(6);
  fout.setf(ios::showpoint);
  fout.setf(ios::scientific);

  int ele_no = static_cast<int>(cov_data.size());
  for(int i=0; i<ele_no; i++)
  {
    for(int j=0; j<ele_no; j++)
    {
      if( j == ele_no-1 )
      {
        fout << cov_data[i][j];
      }
      else
      {
        fout << cov_data[i][j] << ", ";
      }
    }
    fout << endl;
  }
  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int main (int argc, char *argv[])
{
  if( argc <= 1 )
  {
    throw runtime_error("Please set GENDF name.");
  }
  
  string gendf_file_name  = argv[1];
  cout << "GENDF file name : " << gendf_file_name << endl;

  string output_case_name;
  if( argc > 2 )
  {
    output_case_name = argv[2];
    cout << "case name : " << output_case_name << endl;
  }

  vector<Integer> mt_output_list;
  int mt_output_no = argc - 3;
  if( mt_output_no > 0 )
  {
    mt_output_list.resize(mt_output_no);
    for(int i=0; i<mt_output_no; i++)
    {
      mt_output_list[i] = atoi(argv[3+i]);
      cout << "MT list (" << i+1 << " / " << mt_output_no << ") : " 
           << mt_output_list[i] << endl;
    }
  }
 
  EndfFileReader efr_obj;
  efr_obj.set_file_name(gendf_file_name);
  vector<Integer> mt_list = efr_obj.get_mt_list(33);

  int mt_no = static_cast<int>(mt_list.size());
  if( mt_no == 0 )
  {
    cout << "There is no covariance data (MF=33).";
    cout << "The processing is finished.";
  }

  //Read ZA data (Z*1000 + A) from MF=1/MT=451
  int za_data = read_za_data(efr_obj.get_data(1, 451));

  //Read energy grid data from MF=1/MT=451
  vector<Real> ene_data = read_ene_data(efr_obj.get_data(1, 451));

  vector<vector<Integer> >                cov_mt_list;
  vector<vector<vector<vector<Real> > > > cov_data_list;
  cov_mt_list.resize(mt_no);
  cov_data_list.resize(mt_no);
  for(int i=0; i<mt_no; i++)
  {
    //cout << "Read MT = " << mt_list[i] << endl;

    //Read covariance data from MF=33
    read_cov_data(efr_obj.get_data(33, mt_list[i]), ene_data, cov_mt_list[i], cov_data_list[i]); 
  }

  ene_order_check(ene_data, cov_data_list);

  if( argc <= 2 )
  {
    write_cov_data(ene_data, mt_list, cov_mt_list, cov_data_list);
  }
  else if( argc <= 3 )
  {
    write_cov_data_to_file(output_case_name, ene_data, mt_list, cov_mt_list, cov_data_list);
  }
  else if( mt_output_no > 0 )
  {
    write_cov_data_specified_mt(output_case_name, mt_output_list, za_data,
                                ene_data, mt_list, cov_mt_list, cov_data_list);
  }
}

