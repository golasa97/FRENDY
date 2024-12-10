#include "NjoyUtils/GroupStructureGamma.hpp"

using namespace frendy;

GroupStructureGamma::GroupStructureGamma(void)
{
  clear();
}

GroupStructureGamma::~GroupStructureGamma(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GroupStructureGamma::clear()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GroupStructureGamma::get_group_structure(int igg)
{
  vector<Real> ng_vec;
  ng_vec.clear();

  if( igg == 0 ) //none
  {
    ng_vec.resize(0);
  }
  else if( igg == 1 ) //arbitrary structure (read in)
  {
    ng_vec.resize(0);
  }
  else if( igg == 2 ) //CSEWG 94-group structure
  {
    ng_vec = get_eg2();
  }
  else if( igg == 3 ) //LANL 12-group structure
  {
    ng_vec = get_eg3();
  }
  else if( igg == 4 ) //Steiner 21-group gamma-ray structure (ORNL-TM-2564)
  {
    ng_vec = get_eg4();
  }
  else if( igg == 5 ) //Straker 22-group structure
  {
    ng_vec = get_eg5();
  }
  else if( igg == 6 ) //LANL 48-group structure
  {
    ng_vec = get_eg6();
  }
  else if( igg == 7 ) //LANL 24-group structure
  {
    ng_vec = get_eg7();
  }
  else if( igg == 8 ) //VITAMIN-C 36-group structure
  {
    ng_vec = get_eg8();
  }
  else if( igg == 9 ) //VITAMIN-E 38-group structure (R. Roussin, Feb 86)
  {
    ng_vec = get_eg9();
  }
  else if( igg == 10 ) //VITAMIN-J 42-group structure
  {
    ng_vec = get_eg10();
  }
  else
  {
    string class_name = "GroupStructureGamma";
    string func_name  = "get_group_structure(int igg)";

    ostringstream oss;
    oss << igg;
    string str_data01 = "Energy group structure type (igg) : " + oss.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back("This energy group structure type is not available in this program.");
    err_com.push_back("Available energy group structure type is as follows:");
    err_com.push_back("   0      none");
    err_com.push_back("   1      arbitrary structure (read in)");
    err_com.push_back("   2      CSEWG 94-group structure");
    err_com.push_back("   3      LANL 12-group structure");
    err_com.push_back("   4      Steiner 21-group gamma-ray structure (ORNL-TM-2564)");
    err_com.push_back("   5      Straker 22-group structure");
    err_com.push_back("   6      LANL 48-group structure");
    err_com.push_back("   7      LANL 24-group structure");
    err_com.push_back("   8      VITAMIN-C 36-group structure");
    err_com.push_back("   9      VITAMIN-E 38-group structure (R. Roussin, Feb 86)");
    err_com.push_back("  10      VITAMIN-J 42-group structure");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  sort(ng_vec.begin(), ng_vec.end());

  return ng_vec;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GroupStructureGamma::get_eg2()
{
  vector<Real> eg2;
  eg2.resize(95);
  eg2[ 0] = 5.000E+03;
  eg2[ 1] = 1.000E+04;
  eg2[ 2] = 1.500E+04;
  eg2[ 3] = 2.000E+04;
  eg2[ 4] = 3.000E+04;
  eg2[ 5] = 3.500E+04;
  eg2[ 6] = 4.000E+04;
  eg2[ 7] = 4.500E+04;
  eg2[ 8] = 5.500E+04;
  eg2[ 9] = 6.000E+04;
  eg2[10] = 6.500E+04;
  eg2[11] = 7.500E+04;
  eg2[12] = 8.000E+04;
  eg2[13] = 9.000E+04;
  eg2[14] = 1.000E+05;
  eg2[15] = 1.200E+05;
  eg2[16] = 1.400E+05;
  eg2[17] = 1.500E+05;
  eg2[18] = 1.600E+05;
  eg2[19] = 1.900E+05;
  eg2[20] = 2.200E+05;
  eg2[21] = 2.600E+05;
  eg2[22] = 3.000E+05;
  eg2[23] = 3.250E+05;
  eg2[24] = 3.500E+05;
  eg2[25] = 3.750E+05;
  eg2[26] = 4.000E+05;
  eg2[27] = 4.250E+05;
  eg2[28] = 4.500E+05;
  eg2[29] = 5.000E+05;
  eg2[30] = 5.250E+05;
  eg2[31] = 5.500E+05;
  eg2[32] = 5.750E+05;
  eg2[33] = 6.000E+05;
  eg2[34] = 6.250E+05;
  eg2[35] = 6.500E+05;
  eg2[36] = 6.750E+05;
  eg2[37] = 7.000E+05;
  eg2[38] = 7.500E+05;
  eg2[39] = 8.000E+05;
  eg2[40] = 8.250E+05;
  eg2[41] = 8.650E+05;
  eg2[42] = 9.000E+05;
  eg2[43] = 1.000E+06;
  eg2[44] = 1.125E+06;
  eg2[45] = 1.200E+06;
  eg2[46] = 1.250E+06;
  eg2[47] = 1.330E+06;
  eg2[48] = 1.420E+06;
  eg2[49] = 1.500E+06;
  eg2[50] = 1.600E+06;
  eg2[51] = 1.660E+06;
  eg2[52] = 1.750E+06;
  eg2[53] = 1.875E+06;
  eg2[54] = 2.000E+06;
  eg2[55] = 2.166E+06;
  eg2[56] = 2.333E+06;
  eg2[57] = 2.500E+06;
  eg2[58] = 2.666E+06;
  eg2[59] = 2.833E+06;
  eg2[60] = 3.000E+06;
  eg2[61] = 3.166E+06;
  eg2[62] = 3.333E+06;
  eg2[63] = 3.500E+06;
  eg2[64] = 3.650E+06;
  eg2[65] = 3.800E+06;
  eg2[66] = 3.900E+06;
  eg2[67] = 4.000E+06;
  eg2[68] = 4.200E+06;
  eg2[69] = 4.400E+06;
  eg2[70] = 4.500E+06;
  eg2[71] = 4.700E+06;
  eg2[72] = 5.000E+06;
  eg2[73] = 5.200E+06;
  eg2[74] = 5.400E+06;
  eg2[75] = 5.500E+06;
  eg2[76] = 5.750E+06;
  eg2[77] = 6.000E+06;
  eg2[78] = 6.250E+06;
  eg2[79] = 6.500E+06;
  eg2[80] = 6.750E+06;
  eg2[81] = 7.000E+06;
  eg2[82] = 7.250E+06;
  eg2[83] = 7.500E+06;
  eg2[84] = 7.750E+06;
  eg2[85] = 8.000E+06;
  eg2[86] = 8.500E+06;
  eg2[87] = 9.000E+06;
  eg2[88] = 9.500E+06;
  eg2[89] = 1.000E+07;
  eg2[90] = 1.060E+07;
  eg2[91] = 1.100E+07;
  eg2[92] = 1.200E+07;
  eg2[93] = 1.400E+07;
  eg2[94] = 2.000E+07;

  return eg2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GroupStructureGamma::get_eg3()
{
  vector<Real> eg3;
  eg3.resize(13);
  eg3[ 0] = 1.000E+04;
  eg3[ 1] = 1.000E+05;
  eg3[ 2] = 5.000E+05;
  eg3[ 3] = 1.000E+06;
  eg3[ 4] = 2.000E+06;
  eg3[ 5] = 3.000E+06;
  eg3[ 6] = 4.000E+06;
  eg3[ 7] = 5.000E+06;
  eg3[ 8] = 6.000E+06;
  eg3[ 9] = 7.000E+06;
  eg3[10] = 8.000E+06;
  eg3[11] = 9.000E+06;
  eg3[12] = 2.000E+07;

  return eg3;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GroupStructureGamma::get_eg4()
{
  vector<Real> eg4;
  eg4.resize(22);
  eg4[ 0] = 1.000E+04;
  eg4[ 1] = 1.000E+05;
  eg4[ 2] = 2.000E+05;
  eg4[ 3] = 4.000E+05;
  eg4[ 4] = 1.000E+06;
  eg4[ 5] = 1.500E+06;
  eg4[ 6] = 2.000E+06;
  eg4[ 7] = 2.500E+06;
  eg4[ 8] = 3.000E+06;
  eg4[ 9] = 3.500E+06;
  eg4[10] = 4.000E+06;
  eg4[11] = 4.500E+06;
  eg4[12] = 5.000E+06;
  eg4[13] = 5.500E+06;
  eg4[14] = 6.000E+06;
  eg4[15] = 6.500E+06;
  eg4[16] = 7.000E+06;
  eg4[17] = 7.500E+06;
  eg4[18] = 8.000E+06;
  eg4[19] = 1.000E+07;
  eg4[20] = 1.200E+07;
  eg4[21] = 1.400E+07;

  return eg4;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GroupStructureGamma::get_eg5()
{
  vector<Real> eg5;
  eg5.resize(23);
  eg5[ 0] = 1.000E+04;
  eg5[ 1] = 3.000E+04;
  eg5[ 2] = 6.000E+04;
  eg5[ 3] = 1.000E+05;
  eg5[ 4] = 1.500E+05;
  eg5[ 5] = 3.000E+05;
  eg5[ 6] = 4.500E+05;
  eg5[ 7] = 6.000E+05;
  eg5[ 8] = 8.000E+05;
  eg5[ 9] = 1.000E+06;
  eg5[10] = 1.330E+06;
  eg5[11] = 1.660E+06;
  eg5[12] = 2.000E+06;
  eg5[13] = 2.500E+06;
  eg5[14] = 3.000E+06;
  eg5[15] = 3.500E+06;
  eg5[16] = 4.000E+06;
  eg5[17] = 5.000E+06;
  eg5[18] = 6.000E+06;
  eg5[19] = 7.000E+06;
  eg5[20] = 8.000E+06;
  eg5[21] = 1.000E+07;
  eg5[22] = 1.400E+07;

  return eg5;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GroupStructureGamma::get_eg6()
{
  vector<Real> eg6;
  eg6.resize(49);
  eg6[ 0] = 1.000E+03;
  eg6[ 1] = 1.000E+04;
  eg6[ 2] = 2.000E+04;
  eg6[ 3] = 3.000E+04;
  eg6[ 4] = 4.500E+04;
  eg6[ 5] = 6.000E+04;
  eg6[ 6] = 8.000E+04;
  eg6[ 7] = 1.000E+05;
  eg6[ 8] = 1.500E+05;
  eg6[ 9] = 2.000E+05;
  eg6[10] = 3.000E+05;
  eg6[11] = 4.000E+05;
  eg6[12] = 4.500E+05;
  eg6[13] = 5.000E+05;
  eg6[14] = 5.250E+05;
  eg6[15] = 6.000E+05;
  eg6[16] = 7.000E+05;
  eg6[17] = 8.000E+05;
  eg6[18] = 9.000E+05;
  eg6[19] = 1.000E+06;
  eg6[20] = 1.125E+06;
  eg6[21] = 1.200E+06;
  eg6[22] = 1.330E+06;
  eg6[23] = 1.500E+06;
  eg6[24] = 1.660E+06;
  eg6[25] = 1.875E+06;
  eg6[26] = 2.000E+06;
  eg6[27] = 2.333E+06;
  eg6[28] = 2.500E+06;
  eg6[29] = 2.666E+06;
  eg6[30] = 3.000E+06;
  eg6[31] = 3.500E+06;
  eg6[32] = 4.000E+06;
  eg6[33] = 4.500E+06;
  eg6[34] = 5.000E+06;
  eg6[35] = 5.500E+06;
  eg6[36] = 6.000E+06;
  eg6[37] = 6.500E+06;
  eg6[38] = 7.000E+06;
  eg6[39] = 7.500E+06;
  eg6[40] = 8.000E+06;
  eg6[41] = 9.000E+06;
  eg6[42] = 1.000E+07;
  eg6[43] = 1.200E+07;
  eg6[44] = 1.400E+07;
  eg6[45] = 1.700E+07;
  eg6[46] = 2.000E+07;
  eg6[47] = 3.000E+07;
  eg6[48] = 5.000E+07;

  return eg6;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GroupStructureGamma::get_eg7()
{
  vector<Real> eg7;
  eg7.resize(25);
  eg7[ 0] = 1.000E+04;
  eg7[ 1] = 3.000E+04;
  eg7[ 2] = 6.000E+04;
  eg7[ 3] = 1.000E+05;
  eg7[ 4] = 2.000E+05;
  eg7[ 5] = 3.000E+05;
  eg7[ 6] = 5.000E+05;
  eg7[ 7] = 5.250E+05;
  eg7[ 8] = 7.500E+05;
  eg7[ 9] = 1.000E+06;
  eg7[10] = 1.330E+06;
  eg7[11] = 1.660E+06;
  eg7[12] = 2.000E+06;
  eg7[13] = 2.500E+06;
  eg7[14] = 3.000E+06;
  eg7[15] = 4.000E+06;
  eg7[16] = 5.000E+06;
  eg7[17] = 6.000E+06;
  eg7[18] = 7.000E+06;
  eg7[19] = 8.000E+06;
  eg7[20] = 9.000E+06;
  eg7[21] = 1.000E+07;
  eg7[22] = 1.200E+07;
  eg7[23] = 1.700E+07;
  eg7[24] = 3.000E+07;

  return eg7;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GroupStructureGamma::get_eg8()
{
  vector<Real> eg8;
  eg8.resize(37);
  eg8[ 0] = 1.000E+04;
  eg8[ 1] = 2.000E+04;
  eg8[ 2] = 3.000E+04;
  eg8[ 3] = 4.500E+04;
  eg8[ 4] = 6.000E+04;
  eg8[ 5] = 7.000E+04;
  eg8[ 6] = 1.000E+05;
  eg8[ 7] = 1.500E+05;
  eg8[ 8] = 2.000E+05;
  eg8[ 9] = 3.000E+05;
  eg8[10] = 4.000E+05;
  eg8[11] = 4.500E+05;
  eg8[12] = 5.100E+05;
  eg8[13] = 5.120E+05;
  eg8[14] = 6.000E+05;
  eg8[15] = 7.000E+05;
  eg8[16] = 8.000E+05;
  eg8[17] = 1.000E+06;
  eg8[18] = 1.330E+06;
  eg8[19] = 1.500E+06;
  eg8[20] = 1.660E+06;
  eg8[21] = 2.000E+06;
  eg8[22] = 2.500E+06;
  eg8[23] = 3.000E+06;
  eg8[24] = 3.500E+06;
  eg8[25] = 4.000E+06;
  eg8[26] = 4.500E+06;
  eg8[27] = 5.000E+06;
  eg8[28] = 5.500E+06;
  eg8[29] = 6.000E+06;
  eg8[30] = 6.500E+06;
  eg8[31] = 7.000E+06;
  eg8[32] = 7.500E+06;
  eg8[33] = 8.000E+06;
  eg8[34] = 1.000E+07;
  eg8[35] = 1.200E+07;
  eg8[36] = 1.400E+07;

  return eg8;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GroupStructureGamma::get_eg9()
{
  vector<Real> eg9;
  eg9.resize(39);
  eg9[ 0] = 1.000E+04;
  eg9[ 1] = 2.000E+04;
  eg9[ 2] = 3.000E+04;
  eg9[ 3] = 4.500E+04;
  eg9[ 4] = 6.000E+04;
  eg9[ 5] = 7.000E+04;
  eg9[ 6] = 7.500E+04;
  eg9[ 7] = 1.000E+05;
  eg9[ 8] = 1.500E+05;
  eg9[ 9] = 2.000E+05;
  eg9[10] = 3.000E+05;
  eg9[11] = 4.000E+05;
  eg9[12] = 4.500E+05;
  eg9[13] = 5.100E+05;
  eg9[14] = 5.120E+05;
  eg9[15] = 6.000E+05;
  eg9[16] = 7.000E+05;
  eg9[17] = 8.000E+05;
  eg9[18] = 1.000E+06;
  eg9[19] = 1.330E+06;
  eg9[20] = 1.500E+06;
  eg9[21] = 1.660E+06;
  eg9[22] = 2.000E+06;
  eg9[23] = 2.500E+06;
  eg9[24] = 3.000E+06;
  eg9[25] = 3.500E+06;
  eg9[26] = 4.000E+06;
  eg9[27] = 4.500E+06;
  eg9[28] = 5.000E+06;
  eg9[29] = 5.500E+06;
  eg9[30] = 6.000E+06;
  eg9[31] = 6.500E+06;
  eg9[32] = 7.000E+06;
  eg9[33] = 7.500E+06;
  eg9[34] = 8.000E+06;
  eg9[35] = 1.000E+07;
  eg9[36] = 1.200E+07;
  eg9[37] = 1.400E+07;
  eg9[38] = 2.000E+07;

  return eg9;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<Real> GroupStructureGamma::get_eg10()
{
  vector<Real> eg10;
  eg10.resize(43);
  eg10[ 0] = 1.000E+03;
  eg10[ 1] = 1.000E+04;
  eg10[ 2] = 2.000E+04;
  eg10[ 3] = 3.000E+04;
  eg10[ 4] = 4.500E+04;
  eg10[ 5] = 6.000E+04;
  eg10[ 6] = 7.000E+04;
  eg10[ 7] = 7.500E+04;
  eg10[ 8] = 1.000E+05;
  eg10[ 9] = 1.500E+05;
  eg10[10] = 2.000E+05;
  eg10[11] = 3.000E+05;
  eg10[12] = 4.000E+05;
  eg10[13] = 4.500E+05;
  eg10[14] = 5.100E+05;
  eg10[15] = 5.120E+05;
  eg10[16] = 6.000E+05;
  eg10[17] = 7.000E+05;
  eg10[18] = 8.000E+05;
  eg10[19] = 1.000E+06;
  eg10[20] = 1.330E+06;
  eg10[21] = 1.340E+06;
  eg10[22] = 1.500E+06;
  eg10[23] = 1.660E+06;
  eg10[24] = 2.000E+06;
  eg10[25] = 2.500E+06;
  eg10[26] = 3.000E+06;
  eg10[27] = 3.500E+06;
  eg10[28] = 4.000E+06;
  eg10[29] = 4.500E+06;
  eg10[30] = 5.000E+06;
  eg10[31] = 5.500E+06;
  eg10[32] = 6.000E+06;
  eg10[33] = 6.500E+06;
  eg10[34] = 7.000E+06;
  eg10[35] = 7.500E+06;
  eg10[36] = 8.000E+06;
  eg10[37] = 1.000E+07;
  eg10[38] = 1.200E+07;
  eg10[39] = 1.400E+07;
  eg10[40] = 2.000E+07;
  eg10[41] = 3.000E+07;
  eg10[42] = 5.000E+07;

  return eg10;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

