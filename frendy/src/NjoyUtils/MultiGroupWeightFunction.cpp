#include "NjoyUtils/MultiGroupWeightFunction.hpp"

using namespace frendy;

MultiGroupWeightFunction::MultiGroupWeightFunction(void)
{
  clear();
}

MultiGroupWeightFunction::~MultiGroupWeightFunction(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupWeightFunction::clear()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupWeightFunction::get_weighting_function(int iwt, Real temp, vector<Real>& e_vec, vector<Real>& w_vec)
{
  Real e_min = 1.0E-5; //1.0E-5eV
  Real e_max = 2.0E+8; //200MeV

  int iwt_ori = iwt;
  iwt = abs(iwt);

  e_vec.clear();
  w_vec.clear();
  e_vec.resize(0);
  w_vec.resize(0);

  if( iwt == 1 ) //read in
  {
  }
  else if( iwt == 2 ) //constant
  {
    e_vec.resize(2);
    w_vec.resize(2);
    e_vec[0] = e_min;
    e_vec[1] = e_max;
    w_vec[0] = 1.0;
    w_vec[1] = 1.0;
  }
  else if( iwt == 3 ) //1/e
  {
    //FRENDY/MG has this option
  }
  else if( iwt == 4 ) //1/e + fission spectrum + thermal Maxwellian
  {
    //FRENDY/MG has this option
  }
  else if( iwt == 5 ) //Straker 22-group structure
  {
    linearize_tab_data(iwt, e_vec, w_vec);
  }
  else if( iwt == 6 ) //(thermal) -- (1/e) -- (fission + fusion)
  {
    get_w6(iwt, e_vec, w_vec, temp, e_min, e_max);
  }
  else if( iwt == 7 ) //same with t-dep thermal part
  {
    get_w6(iwt, e_vec, w_vec, temp, e_min, e_max);
  }
  else if( iwt == 8 ) //thermal--1/e--fast reactor--fission + fusion
  {
    linearize_tab_data(iwt, e_vec, w_vec);
  }
  else if( iwt == 9 ) //claw weight function
  {
    linearize_tab_data(iwt, e_vec, w_vec);
  }
  else if( iwt == 10 ) //claw with t-dependent thermal part
  {
    linearize_tab_data(iwt, e_vec, w_vec);
  }
  else if( iwt == 11 ) //VITAMIN-E weight function (ORNL-5505)
  {
    get_w11(iwt, e_vec, w_vec, temp, e_min, e_max);
  }
  else if( iwt == 12 ) //VITAMIN-E with t-dep thermal part
  {
    get_w11(iwt, e_vec, w_vec, temp, e_min, e_max);
  }
  else if( iwt == 0 ) //read resonance flux for flux calculator
  {
    //Read other data file
  }
  else
  {
    string class_name = "MultiGroupWeightFunction";
    string func_name  = "get_weighting_function(int iwt, vector<Real>& e_vec, vector<Real>& w_vec)";

    ostringstream oss;
    oss << iwt_ori;
    string str_data01 = "Weighting function type (iwt) : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This weighting function type is not available in this program.");
    err_com.push_back("Available weighting function type is as follows:");
    err_com.push_back("   1      read in");
    err_com.push_back("   2      constant");
    err_com.push_back("   3      1/e");
    err_com.push_back("   4      1/e + fission spectrum + thermal Maxwellian");
    err_com.push_back("   5      EPRI-CELL LWR");
    err_com.push_back("   6      (thermal) -- (1/e) -- (fission + fusion)");
    err_com.push_back("   7      same with t-dep thermal part");
    err_com.push_back("   8      thermal--1/e--fast reactor--fission + fusion");
    err_com.push_back("   9      claw weight function");
    err_com.push_back("  10      claw with t-dependent thermal part");
    err_com.push_back("  11      VITAMIN-E weight function (ORNL-5505)");
    err_com.push_back("  12      VITAMIN-E with t-dep thermal part");
    err_com.push_back("   0      read resonance flux for flux calculator");
    err_com.push_back("  -n      read flux calc. input, and set up iwt=n.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  if( iwt == 5 )
  {
    string class_name = "MultiGroupWeightFunction";
    string func_name  = "get_weighting_function(int iwt, vector<Real>& e_vec, vector<Real>& w_vec)";

    ostringstream oss01;
    oss01 << iwt_ori;

    string str01 = "  Weight function option : " + oss01.str() + " (EPRI-CELL LWR)";

    vector<string> err_com;
    err_com.push_back("This weighting function type is not recommend to the use LWR calculation.");
    err_com.push_back("This weighting function has large fusion peak and this large fusion peak");
    err_com.push_back("makes the hard fission spectrum.");
    err_com.push_back("Please use other weighting function, e.g., 3 (1/E) or 4 (1/e + fission");
    err_com.push_back("spectrum + thermal Maxwellian) if you want to generate the multi-group");
    err_com.push_back("cross-section library for LWR.");
    err_obj.output_caution(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupWeightFunction::linearize_tab_data(int iwt, vector<Real>& e_vec, vector<Real>& w_vec)
{
  Real err_relative = 1.0E-3;
  Real err_min      = err_relative*1.0E-3;

  vector<Integer> nbt_vec, int_vec;
  nbt_vec.clear();
  int_vec.clear();
  if( iwt == 5 )
  {
    get_w1(nbt_vec, int_vec, e_vec, w_vec);
  }
  else if( iwt == 8 )
  {
    get_w8(nbt_vec, int_vec, e_vec, w_vec);
  }
  else if( iwt == 9 || iwt == 10 )
  {
    get_w9(nbt_vec, int_vec, e_vec, w_vec);
  }
  else
  {
    e_vec.clear();
    w_vec.clear();
    return;
  }

  LinearizeTabData tab_obj;
  tab_obj.linearize_tab1_data(nbt_vec, int_vec, e_vec, w_vec, err_relative, err_min);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupWeightFunction::get_w6(int iwt, vector<Real>& e_vec, vector<Real>& w_vec,
                                      Real temp, Real e_min, Real e_max)
{
  e_vec.clear();
  w_vec.clear();

  Real tt = 0.054e0;
  if( iwt == 7 )
  {
    tt = temp * boltzmann_const;
  }

  Real bb = 2.0*tt;

  Real cc = 1.0;
  if( iwt == 7 )
  {
    cc = 1.578551e-3 * exp(2.0) / (bb*bb);
  }

  Real e_val = e_min;
  while( e_val < e_max * 1.01 )
  {
    Real w_val = 0.0;
    if( e_val <= bb )
    {
      w_val = cc * e_val * exp(-1.0 * e_val/tt);
      e_vec.push_back(e_val);
      w_vec.push_back(w_val);

      e_val *= 1.01e0;
    }
    else if( e_val <= 2.1e6 )
    {
      w_val = 1.578551e-3 / e_val;
      e_vec.push_back(e_val);
      w_vec.push_back(w_val);

      e_val *= 1.01e0;
    }
    else
    {
      w_val = 2.32472e-12 * sqrt(e_val) * exp(-1.0*e_val/1.4e6);

      Real pow_val = sqrt(e_val/2.5e4) - sqrt(1.407e7/2.5e4);
           pow_val = -0.5 * pow_val * pow_val;
      if( pow_val > -89.e0 )
      {
        w_val = w_val + 2.51697e-11 * exp(pow_val);
      }

      e_vec.push_back(e_val);
      w_vec.push_back(w_val);

      Real e_check = fabs(e_val - 1.407e7);
      if( e_check <= 3.3e5 )
      {
        e_val *= 1.002e0;
      }
      else if( e_check <= 1.6e6 )
      {
        e_val *= 1.005e0;
      }
      else
      {
        e_val *= 1.01e0;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupWeightFunction::get_w11(int iwt, vector<Real>& e_vec, vector<Real>& w_vec,
                                      Real temp, Real e_min, Real e_max)
{
  e_vec.clear();
  w_vec.clear();

  Real e_val = e_min;
  while( e_val < e_max * 1.01 )
  {
    Real w_val  = 0.0;
    Real e_next = e_val * 1.01;
    if( e_val < 0.414e0 )
    {
      Real tt = 0.0253e0;
      Real cc = 7.45824e+07;
      if( iwt == 12 )
      {
        tt = temp * boltzmann_const;
        cc = 1.0e0 * exp(0.414e0/tt) / (0.414e0*0.414e0);
      }

      w_val = cc * e_val * exp(-1.0*e_val/tt);

      if( e_next > 0.414e0 )
      {
         e_next = 0.414e0;
      }
    }
    else if( e_val < 2.12e6  )
    {
      w_val = 1.e0 / e_val;
      if( e_next > 2.12e6 )
      {
         e_next = 2.12e6;
      }
    }
    else if( e_val < 1.0e7   )
    {
      w_val = 1.44934e-09 * sqrt(e_val) * exp(-1.0*e_val/1.415e6);
      if( e_next > 1.0e7 )
      {
         e_next = 1.0e7;
      }
    }
    else if( e_val < 1.252e7 )
    {
      w_val = 3.90797e-02 / e_val;
      if( e_next > 1.252e7 )
      {
         e_next = 1.252e7;
      }
    }
    else if( e_val < 1.568e7 )
    {
      w_val = sqrt(e_val) - sqrt(1.407e7);
      w_val = 2.64052e-05 * exp(-5.0*(w_val * w_val) / 2.5e4);
      if( fabs(e_val - 1.407e7) <= 5.e5 )
      {
        e_next = 1.002e0 * e_val;
      }

      if( e_next > 1.568e7 )
      {
         e_next = 1.568e7;
      }
    }
    else
    {
      w_val = 6.76517e-02 / e_val;
    }

    e_vec.push_back(e_val);
    w_vec.push_back(w_val);
    e_val = e_next;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupWeightFunction::get_w1(vector<Integer>& nbt_vec, vector<Integer>& int_vec,
                                      vector<Real>& e1, vector<Real>& w1)
{
  int ene_no = 88;
  nbt_vec.resize(1);
  int_vec.resize(1);
  nbt_vec[0] = ene_no;
  int_vec[0] = int_log_log; //int=5

  e1.resize(ene_no);
  w1.resize(ene_no);

  e1[ 0] = 1.00000E-05;
  w1[ 0] = 5.25000E-04;
  e1[ 1] = 9.00000E-03;
  w1[ 1] = 3.55000E-01;
  e1[ 2] = 1.60000E-02;
  w1[ 2] = 5.52000E-01;
  e1[ 3] = 2.40000E-02;
  w1[ 3] = 7.12000E-01;
  e1[ 4] = 2.90000E-02;
  w1[ 4] = 7.85000E-01;
  e1[ 5] = 3.30000E-02;
  w1[ 5] = 8.29000E-01;
  e1[ 6] = 4.30000E-02;
  w1[ 6] = 8.98000E-01;
  e1[ 7] = 5.00000E-02;
  w1[ 7] = 9.18000E-01;
  e1[ 8] = 5.40000E-02;
  w1[ 8] = 9.21000E-01;
  e1[ 9] = 5.90000E-02;
  w1[ 9] = 9.18000E-01;
  e1[10] = 7.00000E-02;
  w1[10] = 8.92000E-01;
  e1[11] = 9.00000E-02;
  w1[11] = 7.99000E-01;
  e1[12] = 1.12000E-01;
  w1[12] = 6.86000E-01;
  e1[13] = 1.40000E-01;
  w1[13] = 5.20000E-01;
  e1[14] = 1.70000E-01;
  w1[14] = 3.83000E-01;
  e1[15] = 2.10000E-01;
  w1[15] = 2.52000E-01;
  e1[16] = 3.00000E-01;
  w1[16] = 1.08000E-01;
  e1[17] = 4.00000E-01;
  w1[17] = 6.87000E-02;
  e1[18] = 4.90000E-01;
  w1[18] = 5.10000E-02;
  e1[19] = 5.70000E-01;
  w1[19] = 4.37000E-02;
  e1[20] = 6.00000E-01;
  w1[20] = 4.13000E-02;
  e1[21] = 1.00000E+00;
  w1[21] = 2.49140E-02;
  e1[22] = 1.01000E+03;
  w1[22] = 3.78290E-05;
  e1[23] = 2.00000E+04;
  w1[23] = 2.22570E-06;
  e1[24] = 3.07000E+04;
  w1[24] = 1.55710E-06;
  e1[25] = 6.07000E+04;
  w1[25] = 9.15950E-07;
  e1[26] = 1.20000E+05;
  w1[26] = 5.79340E-07;
  e1[27] = 2.01000E+05;
  w1[27] = 4.36450E-07;
  e1[28] = 2.83000E+05;
  w1[28] = 3.83090E-07;
  e1[29] = 3.56000E+05;
  w1[29] = 3.69260E-07;
  e1[30] = 3.77000E+05;
  w1[30] = 3.40270E-07;
  e1[31] = 3.99000E+05;
  w1[31] = 2.73870E-07;
  e1[32] = 4.42000E+05;
  w1[32] = 1.00750E-07;
  e1[33] = 4.74000E+05;
  w1[33] = 2.17540E-07;
  e1[34] = 5.02000E+05;
  w1[34] = 2.63330E-07;
  e1[35] = 5.40000E+05;
  w1[35] = 3.05010E-07;
  e1[36] = 6.50000E+05;
  w1[36] = 2.94930E-07;
  e1[37] = 7.70000E+05;
  w1[37] = 2.50050E-07;
  e1[38] = 9.00000E+05;
  w1[38] = 2.14790E-07;
  e1[39] = 9.41000E+05;
  w1[39] = 1.78610E-07;
  e1[40] = 1.00000E+06;
  w1[40] = 9.15950E-08;
  e1[41] = 1.05000E+06;
  w1[41] = 1.15180E-07;
  e1[42] = 1.12000E+06;
  w1[42] = 1.36480E-07;
  e1[43] = 1.19000E+06;
  w1[43] = 1.54790E-07;
  e1[44] = 1.21000E+06;
  w1[44] = 1.50220E-07;
  e1[45] = 1.31000E+06;
  w1[45] = 6.86960E-08;
  e1[46] = 1.40000E+06;
  w1[46] = 1.21820E-07;
  e1[47] = 2.22000E+06;
  w1[47] = 5.90330E-08;
  e1[48] = 2.35000E+06;
  w1[48] = 9.15950E-08;
  e1[49] = 2.63000E+06;
  w1[49] = 3.99810E-08;
  e1[50] = 3.00000E+06;
  w1[50] = 3.11420E-08;
  e1[51] = 4.00000E+06;
  w1[51] = 1.70730E-08;
  e1[52] = 5.00000E+06;
  w1[52] = 9.06790E-09;
  e1[53] = 6.00000E+06;
  w1[53] = 4.71530E-09;
  e1[54] = 8.00000E+06;
  w1[54] = 1.22760E-09;
  e1[55] = 1.00000E+07;
  w1[55] = 3.09530E-10;
  e1[56] = 1.25700E+07;
  w1[56] = 2.46190E-10;
  e1[57] = 1.26000E+07;
  w1[57] = 3.47310E-10;
  e1[58] = 1.27000E+07;
  w1[58] = 1.03570E-09;
  e1[59] = 1.28000E+07;
  w1[59] = 2.84360E-09;
  e1[60] = 1.29000E+07;
  w1[60] = 7.19100E-09;
  e1[61] = 1.30000E+07;
  w1[61] = 1.67760E-08;
  e1[62] = 1.31000E+07;
  w1[62] = 3.61220E-08;
  e1[63] = 1.32000E+07;
  w1[63] = 7.18640E-08;
  e1[64] = 1.33000E+07;
  w1[64] = 1.32220E-07;
  e1[65] = 1.34000E+07;
  w1[65] = 2.25110E-07;
  e1[66] = 1.35000E+07;
  w1[66] = 3.55120E-07;
  e1[67] = 1.36000E+07;
  w1[67] = 5.19460E-07;
  e1[68] = 1.37000E+07;
  w1[68] = 7.04780E-07;
  e1[69] = 1.38000E+07;
  w1[69] = 8.88250E-07;
  e1[70] = 1.39000E+07;
  w1[70] = 1.04080E-06;
  e1[71] = 1.40700E+07;
  w1[71] = 1.15400E-06;
  e1[72] = 1.42000E+07;
  w1[72] = 1.08700E-06;
  e1[73] = 1.43000E+07;
  w1[73] = 9.57570E-07;
  e1[74] = 1.44000E+07;
  w1[74] = 7.78040E-07;
  e1[75] = 1.45000E+07;
  w1[75] = 6.04030E-07;
  e1[76] = 1.46000E+07;
  w1[76] = 4.33170E-07;
  e1[77] = 1.47000E+07;
  w1[77] = 2.90410E-07;
  e1[78] = 1.48000E+07;
  w1[78] = 1.82130E-07;
  e1[79] = 1.49000E+07;
  w1[79] = 1.06990E-07;
  e1[80] = 1.50000E+07;
  w1[80] = 5.88320E-08;
  e1[81] = 1.51000E+07;
  w1[81] = 3.03540E-08;
  e1[82] = 1.52000E+07;
  w1[82] = 1.46870E-08;
  e1[83] = 1.53000E+07;
  w1[83] = 6.66880E-09;
  e1[84] = 1.54000E+07;
  w1[84] = 2.84500E-09;
  e1[85] = 1.55000E+07;
  w1[85] = 1.14060E-09;
  e1[86] = 1.56760E+07;
  w1[86] = 1.97800E-10;
  e1[87] = 2.00000E+07;
  w1[87] = 1.54770E-10;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupWeightFunction::get_w8(vector<Integer>& nbt_vec, vector<Integer>& int_vec,
                                      vector<Real>& e8, vector<Real>& w8)
{
  int ene_no = 29;
  nbt_vec.resize(1);
  int_vec.resize(1);
  nbt_vec[0] = ene_no;
  int_vec[0] = int_log_log; //int=5

  e8.resize(ene_no);
  w8.resize(ene_no);

  e8[ 0] = 1.390000E-04;
  w8[ 0] = 7.515160E-04;
  e8[ 1] = 1.000000E-02;
  w8[ 1] = 4.973600E-02;
  e8[ 2] = 2.000000E-02;
  w8[ 2] = 7.544880E-02;
  e8[ 3] = 4.000000E-02;
  w8[ 3] = 1.077560E-01;
  e8[ 4] = 6.000000E-02;
  w8[ 4] = 1.105200E-01;
  e8[ 5] = 8.000000E-02;
  w8[ 5] = 1.015420E-01;
  e8[ 6] = 1.000000E-01;
  w8[ 6] = 8.845110E-02;
  e8[ 7] = 6.140000E+01;
  w8[ 7] = 1.440570E-04;
  e8[ 8] = 7.889300E+01;
  w8[ 8] = 2.175040E-04;
  e8[ 9] = 3.120300E+02;
  w8[ 9] = 1.272780E-03;
  e8[10] = 1.795600E+03;
  w8[10] = 2.365460E-03;
  e8[11] = 8.047300E+03;
  w8[11] = 1.143110E-03;
  e8[12] = 4.630900E+04;
  w8[12] = 3.877340E-04;
  e8[13] = 1.616300E+05;
  w8[13] = 1.253190E-04;
  e8[14] = 6.392800E+05;
  w8[14] = 2.075410E-05;
  e8[15] = 2.865000E+06;
  w8[15] = 2.161110E-06;
  e8[16] = 4.723700E+06;
  w8[16] = 7.489980E-07;
  e8[17] = 1.000000E+07;
  w8[17] = 5.731630E-08;
  e8[18] = 1.279000E+07;
  w8[18] = 9.405280E-09;
  e8[19] = 1.290000E+07;
  w8[19] = 9.736480E-09;
  e8[20] = 1.355000E+07;
  w8[20] = 9.850380E-08;
  e8[21] = 1.375000E+07;
  w8[21] = 1.763880E-07;
  e8[22] = 1.395000E+07;
  w8[22] = 2.398010E-07;
  e8[23] = 1.407000E+07;
  w8[23] = 2.519630E-07;
  e8[24] = 1.419000E+07;
  w8[24] = 2.392980E-07;
  e8[25] = 1.439000E+07;
  w8[25] = 1.762260E-07;
  e8[26] = 1.459000E+07;
  w8[26] = 9.924220E-08;
  e8[27] = 1.555000E+07;
  w8[27] = 1.507370E-09;
  e8[28] = 2.000000E+07;
  w8[28] = 7.250000E-11;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MultiGroupWeightFunction::get_w9(vector<Integer>& nbt_vec, vector<Integer>& int_vec,
                                      vector<Real>& e9, vector<Real>& w9)
{
  int ene_no = 47;
  nbt_vec.resize(1);
  int_vec.resize(1);
  nbt_vec[0] = ene_no;
  int_vec[0] = int_log_log; //int=5

  e9.resize(ene_no);
  w9.resize(ene_no);

  e9[ 0] = 1.39000E-04;
  w9[ 0] = 3.01900E+06;
  e9[ 1] = 5.00000E-04;
  w9[ 1] = 1.07000E+07;
  e9[ 2] = 1.00000E-03;
  w9[ 2] = 2.09800E+07;
  e9[ 3] = 5.00000E-03;
  w9[ 3] = 8.93900E+07;
  e9[ 4] = 1.00000E-02;
  w9[ 4] = 1.46380E+08;
  e9[ 5] = 2.50000E-02;
  w9[ 5] = 2.00800E+08;
  e9[ 6] = 4.00000E-02;
  w9[ 6] = 1.76350E+08;
  e9[ 7] = 5.00000E-02;
  w9[ 7] = 1.47800E+08;
  e9[ 8] = 1.00000E-01;
  w9[ 8] = 4.00000E+07;
  e9[ 9] = 1.40000E-01;
  w9[ 9] = 1.13000E+07;
  e9[10] = 1.50000E-01;
  w9[10] = 7.60000E+06;
  e9[11] = 4.14000E-01;
  w9[11] = 2.79000E+06;
  e9[12] = 1.13000E+00;
  w9[12] = 1.02000E+06;
  e9[13] = 3.06000E+00;
  w9[13] = 3.77000E+05;
  e9[14] = 8.32000E+00;
  w9[14] = 1.39000E+05;
  e9[15] = 2.26000E+01;
  w9[15] = 5.11000E+04;
  e9[16] = 6.14000E+01;
  w9[16] = 1.88000E+04;
  e9[17] = 1.67000E+02;
  w9[17] = 6.91000E+03;
  e9[18] = 4.54000E+02;
  w9[18] = 2.54000E+03;
  e9[19] = 1.23500E+03;
  w9[19] = 9.35000E+02;
  e9[20] = 3.35000E+03;
  w9[20] = 3.45000E+02;
  e9[21] = 9.12000E+03;
  w9[21] = 1.26600E+02;
  e9[22] = 2.48000E+04;
  w9[22] = 4.65000E+01;
  e9[23] = 6.76000E+04;
  w9[23] = 1.71000E+01;
  e9[24] = 1.84000E+05;
  w9[24] = 6.27000E+00;
  e9[25] = 3.03000E+05;
  w9[25] = 3.88000E+00;
  e9[26] = 5.00000E+05;
  w9[26] = 3.60000E+00;
  e9[27] = 8.23000E+05;
  w9[27] = 2.87000E+00;
  e9[28] = 1.35300E+06;
  w9[28] = 1.75000E+00;
  e9[29] = 1.73800E+06;
  w9[29] = 1.13000E+00;
  e9[30] = 2.23200E+06;
  w9[30] = 7.30000E-01;
  e9[31] = 2.86500E+06;
  w9[31] = 4.00000E-01;
  e9[32] = 3.68000E+06;
  w9[32] = 2.05000E-01;
  e9[33] = 6.07000E+06;
  w9[33] = 3.90000E-02;
  e9[34] = 7.79000E+06;
  w9[34] = 1.63000E-02;
  e9[35] = 1.00000E+07;
  w9[35] = 6.50000E-03;
  e9[36] = 1.20000E+07;
  w9[36] = 7.60000E-03;
  e9[37] = 1.30000E+07;
  w9[37] = 1.23000E-02;
  e9[38] = 1.35000E+07;
  w9[38] = 2.64000E-02;
  e9[39] = 1.40000E+07;
  w9[39] = 1.14000E-01;
  e9[40] = 1.41000E+07;
  w9[40] = 1.14000E-01;
  e9[41] = 1.42000E+07;
  w9[41] = 1.01000E-01;
  e9[42] = 1.43000E+07;
  w9[42] = 6.50000E-02;
  e9[43] = 1.46000E+07;
  w9[43] = 1.49000E-02;
  e9[44] = 1.50000E+07;
  w9[44] = 4.00000E-03;
  e9[45] = 1.60000E+07;
  w9[45] = 1.54000E-03;
  e9[46] = 1.70000E+07;
  w9[46] = 8.50000E-04;
}

