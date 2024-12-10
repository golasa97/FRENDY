#define _CRT_SECURE_NO_WARNINGS
#include "CommonUtils/DigitAdjuster.hpp"

using namespace frendy;

//constructor
DigitAdjuster::DigitAdjuster(void)
{
  char_data = new char[30];
  mantissa  = new char[15];
}

//destructor
DigitAdjuster::~DigitAdjuster(void)
{
  delete [] char_data;
  delete [] mantissa;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int DigitAdjuster::get_precision_no(Real& real_val, int width)
{
  //This subroutine is used to output ENDF-6 format data
  Integer exp_part = get_digit_number(real_val);

  int precision_value;
  if( exp_part >= 0 && exp_part < width - 3 )
  {
    precision_value = width - 2; //ex:-1.23456789 - -123456789.
  }
  else
  {
    precision_value = width - 4; //ex:-1.2345678+1
    if( exp_part >= 10 || exp_part <= -10 )
    {
      precision_value--;           //ex:-1.234567+12
      if( exp_part >= 100 || exp_part <= -100 )
      {
        precision_value--;         //ex:-1.23456+123
      }
    }
  }
  return precision_value;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

Integer DigitAdjuster::get_digit_number(Real8 real_data)
{
  sprintf(char_data, "%+2.10e", real_data);
  strncpy(mantissa, &char_data[14],10);
  Integer digit = atoi(mantissa);
  return digit;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

/*
Integer DigitAdjuster::get_digit_number(Real real_data)
{
  sprintf(char_data, "%+2.6e", real_data);
  strncpy(mantissa, &char_data[10],10);
  Integer digit = atoi(mantissa);
  return digit;
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////

Integer DigitAdjuster::get_digit_number(Integer int_data)
{
  return get_digit_number(static_cast<Real8>(int_data));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 DigitAdjuster::get_adjusted_value(Real8 real_data, Integer adjust_digit, Real8 adjust_amount)
{
  if(adjust_digit <= 0)
  {
    string class_name = "DigitAdjuster";
    string func_name  = "get_adjusted_value(Real8 real_data, Integer adjust_digit, Real8 adjust_amount)";

    ostringstream oss;
    oss << adjust_digit;
    string str_data = "Adjust digit number : " + oss.str();
    
    vector<string> err_com;
    err_com.push_back(str_data);
    err_com.push_back("Adjust digit must be larger than 0.");
    err_com.push_back("Please check the Adjust digit number.");

    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  Integer digit_no = get_digit_number(real_data);
          digit_no = digit_no - adjust_digit + 1;

  Real8 adjusted_value = real_data + adjust_amount * (pow(10.0, digit_no));

  Integer digit_no_chk = get_digit_number(adjusted_value) - adjust_digit + 1;
  if( digit_no_chk != digit_no )
  {
    digit_no -= 1;
    adjusted_value = real_data + adjust_amount * (pow(10.0, digit_no));
  }

  return adjusted_value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 DigitAdjuster::get_truncation_value(Real8 real_data)
{
  Real tmp_real = real_data;
  int truncation_digit = get_precision_no(tmp_real, default_data_width);
  return get_truncation_value(tmp_real, truncation_digit);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real8 DigitAdjuster::get_truncation_value(Real8 real_data, int truncation_digit)
{
  ostringstream ostr;
  ostr.setf(ios::scientific);
  ostr.precision(truncation_digit-1);

  ostr << real_data;

  Real          real_data_mod;
  istringstream istr(ostr.str());
  istr >> real_data_mod;

  if( real_data_mod < real_data - min_ene_dif )
  {
    real_data_mod = get_adjusted_value(real_data_mod, truncation_digit, +1.0);
  }

  return real_data_mod;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Real DigitAdjuster::adjust_min_value(Real real_data)
{
  if( real_data < min_sig_val )
  {
    if( fabs(real_data) < min_sig_dif )
    {
      real_data = 0.0;
    }
    else
    {
      real_data = min_sig_val;
    }
  }

  return real_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DigitAdjuster::adjust_data( vector<vector<vector<vector<vector<vector<Real> > > > > >& real_vec )
{
  int i_max = static_cast<int>(real_vec.size());
  for(int i=0; i<i_max; i++)
  {
    adjust_data(real_vec[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DigitAdjuster::adjust_data( vector<vector<vector<vector<vector<Real> > > > >& real_vec )
{
  int i_max = static_cast<int>(real_vec.size());
  for(int i=0; i<i_max; i++)
  {
    adjust_data(real_vec[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DigitAdjuster::adjust_data( vector<vector<vector<vector<Real> > > >& real_vec )
{
  int i_max = static_cast<int>(real_vec.size());
  for(int i=0; i<i_max; i++)
  {
    adjust_data(real_vec[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DigitAdjuster::adjust_data( vector<vector<vector<Real> > >& real_vec )
{
  int i_max = static_cast<int>(real_vec.size());
  for(int i=0; i<i_max; i++)
  {
    adjust_data(real_vec[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DigitAdjuster::adjust_data( vector<vector<Real> >& real_vec )
{
  int i_max = static_cast<int>(real_vec.size());
  for(int i=0; i<i_max; i++)
  {
    adjust_data(real_vec[i]);
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void DigitAdjuster::adjust_data( vector<Real>& real_vec )
{
  int i_max = static_cast<int>(real_vec.size());
  for(int i=0; i<i_max; i++)
  {
    adjust_data(real_vec[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void DigitAdjuster::adjust_data( Real& real_val )
{
  if( fabs(real_val) < min_sig_val )
  {
    real_val = 0.0;
  }
}
