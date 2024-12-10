#include "MathUtils/RandomNumberGeneratorWithNjoyFormula.hpp"

using namespace frendy;

//constructor
RandomNumberGeneratorWithNjoyFormula::RandomNumberGeneratorWithNjoyFormula(void)
{
  clear();

  chi_sq_vec.resize(chi_sq_max_freedom);
  for(int i=0; i<chi_sq_max_freedom; i++)
  {
    chi_sq_vec[i].resize(chi_sq_data_no);
  }
  
  //freedom = 1
  chi_sq_vec[0][ 0] =  1.3100300e-3;
  chi_sq_vec[0][ 1] =  9.1950100e-3;
  chi_sq_vec[0][ 2] =  0.0250905;
  chi_sq_vec[0][ 3] =  0.0492540;
  chi_sq_vec[0][ 4] =  0.0820892;
  chi_sq_vec[0][ 5] =  0.1241690;
  chi_sq_vec[0][ 6] =  0.1762680;
  chi_sq_vec[0][ 7] =  0.2394170;
  chi_sq_vec[0][ 8] =  0.3149770;
  chi_sq_vec[0][ 9] =  0.4047490;
  chi_sq_vec[0][10] =  0.5111450;
  chi_sq_vec[0][11] =  0.6374610;
  chi_sq_vec[0][12] =  0.7883150;
  chi_sq_vec[0][13] =  0.9704190;
  chi_sq_vec[0][14] =  1.1940000;
  chi_sq_vec[0][15] =  1.4757300;
  chi_sq_vec[0][16] =  1.8454700;
  chi_sq_vec[0][17] =  2.3652200;
  chi_sq_vec[0][18] =  3.2037100;
  chi_sq_vec[0][19] =  5.5820100;

  //freedom = 2
  chi_sq_vec[1][ 0] =  0.0508548;
  chi_sq_vec[1][ 1] =  0.1561670;
  chi_sq_vec[1][ 2] =  0.2673350;
  chi_sq_vec[1][ 3] =  0.3850500;
  chi_sq_vec[1][ 4] =  0.5101310;
  chi_sq_vec[1][ 5] =  0.6435640;
  chi_sq_vec[1][ 6] =  0.7865430;
  chi_sq_vec[1][ 7] =  0.9405410;
  chi_sq_vec[1][ 8] =  1.1074000;
  chi_sq_vec[1][ 9] =  1.2894700;
  chi_sq_vec[1][10] =  1.4898100;
  chi_sq_vec[1][11] =  1.7124900;
  chi_sq_vec[1][12] =  1.9631400;
  chi_sq_vec[1][13] =  2.2498400;
  chi_sq_vec[1][14] =  2.5847300;
  chi_sq_vec[1][15] =  2.9874400;
  chi_sq_vec[1][16] =  3.4927800;
  chi_sq_vec[1][17] =  4.1723800;
  chi_sq_vec[1][18] =  5.2188800;
  chi_sq_vec[1][19] =  7.9914600;

  //freedom = 3
  chi_sq_vec[2][ 0] =  0.2068320;
  chi_sq_vec[2][ 1] =  0.4707190;
  chi_sq_vec[2][ 2] =  0.6919330;
  chi_sq_vec[2][ 3] =  0.9016740;
  chi_sq_vec[2][ 4] =  1.1086800;
  chi_sq_vec[2][ 5] =  1.3176500;
  chi_sq_vec[2][ 6] =  1.5319300;
  chi_sq_vec[2][ 7] =  1.7544400;
  chi_sq_vec[2][ 8] =  1.9881200;
  chi_sq_vec[2][ 9] =  2.2362100;
  chi_sq_vec[2][10] =  2.5025700;
  chi_sq_vec[2][11] =  2.7921300;
  chi_sq_vec[2][12] =  3.1114300;
  chi_sq_vec[2][13] =  3.4696700;
  chi_sq_vec[2][14] =  3.8805300;
  chi_sq_vec[2][15] =  4.3658600;
  chi_sq_vec[2][16] =  4.9641700;
  chi_sq_vec[2][17] =  5.7542300;
  chi_sq_vec[2][18] =  6.9464600;
  chi_sq_vec[2][19] = 10.0048000;

  //freedom = 4
  chi_sq_vec[3][ 0] =  0.4594620;
  chi_sq_vec[3][ 1] =  0.8937350;
  chi_sq_vec[3][ 2] =  1.2175300;
  chi_sq_vec[3][ 3] =  1.5087200;
  chi_sq_vec[3][ 4] =  1.7860500;
  chi_sq_vec[3][ 5] =  2.0585400;
  chi_sq_vec[3][ 6] =  2.3319400;
  chi_sq_vec[3][ 7] =  2.6106900;
  chi_sq_vec[3][ 8] =  2.8987800;
  chi_sq_vec[3][ 9] =  3.2003200;
  chi_sq_vec[3][10] =  3.5199500;
  chi_sq_vec[3][11] =  3.8633100;
  chi_sq_vec[3][12] =  4.2377600;
  chi_sq_vec[3][13] =  4.6534500;
  chi_sq_vec[3][14] =  5.1253300;
  chi_sq_vec[3][15] =  5.6771200;
  chi_sq_vec[3][16] =  6.3504400;
  chi_sq_vec[3][17] =  7.2299600;
  chi_sq_vec[3][18] =  8.5410000;
  chi_sq_vec[3][19] = 11.8359000;
}

//destructor
RandomNumberGeneratorWithNjoyFormula::~RandomNumberGeneratorWithNjoyFormula(void)
{
  clear();

  for(int i=0; i<chi_sq_max_freedom; i++)
  {
    chi_sq_vec[i].clear();
  }
  chi_sq_vec.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void RandomNumberGeneratorWithNjoyFormula::clear()
{
  RandomNumberGenerator::clear();

  chi_freedom_no = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGeneratorWithNjoyFormula::chi_square_distribution(Real8& freedom)
{
  set_chi_freedom(freedom);
  return chi_square_distribution();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 RandomNumberGeneratorWithNjoyFormula::chi_square_distribution()
{
  Real8 rand_uni = uniform_distribution();
  rand_uni *= 19.9999;

  int ele_no = static_cast<int>(floor(rand_uni));

  return chi_sq_vec[chi_freedom_no][ele_no];
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void RandomNumberGeneratorWithNjoyFormula::set_chi_freedom(Real8 freedom)
{
  chi_freedom_no = -1;
  if( freedom > 1.0 - min_ene_val && freedom < 1.0 + min_ene_val )
  {
    chi_freedom_no = 0;
  }
  else if( freedom > 2.0 - min_ene_val && freedom < 2.0 + min_ene_val )
  {
    chi_freedom_no = 1;
  }
  else if( freedom > 3.0 - min_ene_val && freedom < 3.0 + min_ene_val )
  {
    chi_freedom_no = 2;
  }
  else if( freedom > 4.0 - min_ene_val && freedom < 4.0 + min_ene_val )
  {
    chi_freedom_no = 3;
  }
  else
  {
    string class_name = "RandomNumberGeneratorWithNjoyFormula";
    string func_name  = "set_chi_freedom(Real8 freedom)";

    ostringstream oss01, oss02, oss03;
    oss01 << freedom;
    oss02 << 1;
    oss03 << chi_sq_max_freedom;
    string str_data01 = "Freedom of chi-square distribution (input) : " + oss01.str();
    string str_data02 = "Freedom of chi-square distribution (max)   : " + oss02.str();
    string str_data03 = "Freedom of chi-square distribution (min)   : " + oss03.str();
     

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back(str_data03);
    err_com.push_back("Please check the freedom of chi-square distribution.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

