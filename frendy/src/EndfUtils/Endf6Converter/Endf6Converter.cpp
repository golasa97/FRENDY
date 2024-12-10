#include "EndfUtils/Endf6Converter/Endf6Converter.hpp"

using namespace frendy;

//Initialize static value
const Real Endf6Converter::min_check_dif = 1.0E-3;

//constructor
Endf6Converter::Endf6Converter(void)
{
}

//destructor
Endf6Converter::~Endf6Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Converter::check_mat_data(string func_name, Integer MF, Integer MT, 
                                    Integer& mat_no,   Integer& mat_no_base, 
                                    Real&    mat_data, Real&    mat_data_base, Real& mass, Real& mass_base)
{
  if( mat_no == unassigned_mat_no || MT == unassigned_mt_no )
  {
    return;
  }

  if( mat_no_base != mat_no || fabs(mat_data_base - mat_data) > min_value*mat_data_base ||
                               fabs(mass_base     - mass)     > min_value*mass_base )
  {
    if( mat_no_base == unassigned_mat_no && fabs(mat_data_base) < min_value && fabs(mass_base) < min_value )
    {
      mat_no_base   = mat_no;
      mat_data_base = mat_data;
      mass_base     = mass;
    }
    else if( mat_no != unassigned_mat_no || fabs(mat_data) > min_value || fabs(mass) > min_value )
    {
      string class_name = "Endf6Converter";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
      oss01 << MF;
      oss02 << MT;
      oss03 << mat_no;
      oss04 << mat_no_base;
      oss05 << mat_data;
      oss06 << mat_data_base;

      oss07.setf(ios::scientific);
      oss07.precision(7);
      oss07 << mass;

      oss08.setf(ios::scientific);
      oss08.precision(7);
      oss08 << mass_base;

      string str_data01, str_data02, str_data03, str_data04;
      str_data01 = "MF = " + oss01.str() + ", MT = " + oss02.str();
      str_data02 = "Material number (current/others) : " + oss03.str() + " / " + oss04.str();
      str_data03 = "Material data   (current/others) : " + oss05.str() + " / " + oss06.str();
      str_data04 = "Mass            (current/others) : " + oss07.str() + " / " + oss08.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);

      if( mat_no_base != mat_no || fabs(mat_data_base - mat_data) > min_check_dif*mat_data_base ||
                                   fabs(mass_base     - mass)     > min_check_dif*mass_base )
      {
        if( mat_no_base != mat_no )
        {
          err_com.push_back("The material number (MAT) is different.");
        }
        if( fabs(mat_data_base - mat_data) > min_check_dif*mat_data_base )
        {
          err_com.push_back("The material data (ZA) is different.");
        }
        if( fabs(mass_base - mass) > min_check_dif*mass_base )
        {
          err_com.push_back("The mass (AWR) is different.");
        }
        err_com.push_back("This endf-6 format data can't convert to NuclearDataObject.");
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      else
      {
        if( fabs(mat_data_base - mat_data) > min_value*mat_data_base )
        {
          err_com.push_back("The material data (ZA) is different.");
        }
        if( fabs(mass_base - mass) > min_value*mass_base )
        {
          err_com.push_back("The mass (AWR) is different.");
        }
        err_com.push_back("This endf-6 format data may not be appropriate data.");
        err_obj.output_caution_format(class_name, func_name, err_com);
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Converter::check_temp_data( string func_name, Integer MF, Integer MT, Integer& mat_no,
                                      Real& temp_data, Real& temp_data_base )
{
  if( mat_no == unassigned_mat_no )
  {
    return;
  }

  if( fabs(temp_data - temp_data_base) > min_value )
  {
    string class_name = "Endf6Converter";

    ostringstream oss01, oss02, oss03, oss04;
    oss01 << MF;
    oss02 << MT;

    oss03.precision(7);
    oss03.setf(ios::showpoint);
    oss03 << temp_data;

    oss04.precision(7);
    oss04.setf(ios::showpoint);
    oss04 << temp_data_base;

    string str_data01, str_data02, str_data03, str_data04;
    str_data01 = "MF = " + oss01.str() + ", MT = " + oss02.str();
    str_data02 = "Temperature (current/others) : " + oss03.str() + " / " + oss04.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("The temperature data is different.");
    if( fabs(temp_data_base - temp_data) > min_check_dif )
    {
      err_com.push_back("This endf-6 format data can't convert to NuclearDataObject.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    else
    {
      err_com.push_back("This endf-6 format data may not be appropriate data.");
      err_obj.output_caution_format(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Converter::check_xs_data( string func_name,
                                    MF02MT151Parser& mf02mt151_data_obj, MF03Parser& mf03_data_obj )
{
  //This check method only available for total cross section
  Integer mt_no  = mf03_data_obj.get_mt_no();
  Integer mat_no = mf03_data_obj.get_mat_no();
  if( ( mt_no != 1 && mt_no != 2 ) || mat_no == unassigned_mat_no )
  {
    return;
  }

  Real ene_min = -1.0;
  Real ene_max = -1.0;

  mat_no = mf02mt151_data_obj.get_mat_no();
  if( mat_no != unassigned_mat_no )
  {
    //Search minimum energy range in the resolved or unresolved resonance region
    int  i_max   = static_cast<int>(mf02mt151_data_obj.get_LRU().size());
    for(int i=0; i<i_max; i++)
    {
      int j_max = static_cast<int>(mf02mt151_data_obj.get_LRU()[i].size());
      for(int j=0; j<j_max; j++)
      {
        if( mf02mt151_data_obj.get_LRU()[i][j] == 1 || mf02mt151_data_obj.get_LRU()[i][j] == 2 )
        {
          if( ene_min < 0.0 )
          {
            ene_min = mf02mt151_data_obj.get_EL()[i][j];
          }
          else if( ene_min > mf02mt151_data_obj.get_EL()[i][j] )
          {
            ene_min = mf02mt151_data_obj.get_EL()[i][j];
          }

          if( ene_max < 0.0 )
          {
            ene_max = mf02mt151_data_obj.get_EH()[i][j];
          }
          else if( ene_max < mf02mt151_data_obj.get_EH()[i][j] )
          {
            ene_max = mf02mt151_data_obj.get_EH()[i][j];
          }
        }
      }
    }

    if( ene_min > 0.0 )
    {
      ene_min *= (1.0 - min_ene_dif);
    }
  }

  vector<Real> ene_vec = mf03_data_obj.get_E_INT_SIG();
  vector<Real> xs_vec  = mf03_data_obj.get_SIG_TAB();
  if( static_cast<int>(ene_vec.size()) < 1 )
  {
    return;
  }

  if( ene_vec[0] < ene_min || ene_min < 0.0 )
  {
    //If minimum energy grid is less than the lowest energy of the resolved or unresolved
    //resonance region or there is no resonance data in nuclear data file, check the
    //total cross section data.
    if( xs_vec[0] < min_sig_val )
    {
      string class_name = "Endf6Converter";

      ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
      oss01 << mat_no;
      oss02 << mt_no;
      oss03 << ene_min;
      oss04 << ene_vec[0];
      oss05 << xs_vec[0];
      string str_data01 = "Material data number / MT number        : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Lowest energy of the resonance region   : " + oss03.str();
      string str_data03 = "First element value (Energy/XS) in MF=3 : " + oss04.str() + " / " + oss05.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      if( ene_min > 0.0 )
      {
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("");
        err_com.push_back("The lowest energy grid data is less than the lowest energy of");
        err_com.push_back("the resolved or unresolved resonance region.");
      }
      else
      {
        oss06.setf(ios::scientific);
        oss06 << min_sig_val;
        string str_data06 = "Minimum xs value                        : " + oss06.str();

        err_com.push_back(str_data06);
        err_com.push_back(str_data03);
        err_com.push_back("");
        err_com.push_back("This nuclear data file does not have resonance data (MF=2, MT=151).");
      }

      err_com.push_back("The non zero value total cross section must be required in MF=3");
      err_com.push_back("However, 0 barn or very small cross section value is set");
      err_com.push_back("in the total cross section at first energy grid.");
      err_com.push_back("");
      err_com.push_back("The nuclear data file may not be appropriate.");
      err_com.push_back("Please check the nuclear data file or this program.");

      if( ene_min > 0.0 )
      {
        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
      else
      {
        err_obj.output_caution_format(class_name, func_name, err_com);
        modify_xs_data(mf03_data_obj);
      }
    }
  }

  //Serch initial non-zero xs point
  if( ene_max > 0.0 )
  {
    int non_zero_pos = -1;
    int i_max        = static_cast<int>(xs_vec.size());
    for(int i=0; i<i_max; i++)
    {
      if( xs_vec[i] > min_sig_val )
      {
        non_zero_pos = i;
        break;
      }
    }

    //Comparing non_zero xs grid and upper limit of the resonance region
    if( non_zero_pos > 0 )
    {
      if( ene_vec[non_zero_pos-1]  - ene_max > -1.0 * min_ene_dif )
      {
        if( ene_vec[non_zero_pos] - ene_max > fabs(5.0E-4 * ene_max) )
        {
          string class_name = "Endf6Converter";

          ostringstream oss01, oss02, oss03, oss04, oss05;
          oss01 << mat_no;
          oss02 << mt_no;
          oss03 << ene_max;
          oss04 << ene_vec[non_zero_pos];
          oss05 << (ene_vec[non_zero_pos] - ene_max) / ene_max;
          string str_data01 = "Material data number / MT number       : "
                            + oss01.str() + " / " + oss02.str();
          string str_data02 = "Highest energy of the resonance region : " + oss03.str();
          string str_data03 = "Non zero cross section energy grid     : " + oss04.str();
          string str_data04 = "Relative difference                    : " + oss05.str();

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back(str_data04);
          err_com.push_back("");
          err_com.push_back("The relative difference between highest energy of the");
          err_com.push_back("resonance region in MF=2 and non-zero cross section at MF=3");
          err_com.push_back("is larger than 0.05%.");
          err_com.push_back("The inappropriate low cross section may be observed at the");
          err_com.push_back("boundary of the resonance and non-resonance region when");
          err_com.push_back("linearization is applied.");
          err_com.push_back("");
          err_com.push_back("This nuclear data may not be appropriate.");
          err_obj.output_caution_format(class_name, func_name, err_com);
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Converter::modify_xs_data( MF03Parser& mf03_data_obj )
{
  string class_name = "Endf6Converter";
  string func_name  = "modify_xs_data( MF03Parser& mf03_data_obj )";
  ostringstream oss01, oss02;
  oss01 << mf03_data_obj.get_mat_no();
  oss02 << mf03_data_obj.get_mt_no();
  string str_data01 = "Material data number / MT number : " + oss01.str() + " / " + oss02.str();
  vector<string> err_com;
  err_com.push_back(str_data01);


  vector<Integer> range_vec = mf03_data_obj.get_NBT_SIG();
  vector<Integer> int_vec   = mf03_data_obj.get_INT_SIG();
  vector<Real>    ene_vec   = mf03_data_obj.get_E_INT_SIG();
  vector<Real>    xs_vec    = mf03_data_obj.get_SIG_TAB();


  //Check energy grid number
  int i_max = static_cast<int>(ene_vec.size());
  if( i_max < 3 )
  {
    ostringstream oss03;
    oss03 << i_max;
    string str_data02 = "Energy grid number : " + oss03.str();

    err_com.push_back(str_data02);
    err_com.push_back("Energy grid number is less than 3.");
    err_com.push_back("This nuclear data file can not extrapolate the first xs data.");
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }


  //Check ene and xs data
  ostringstream oss03, oss04, oss05, oss06, oss07, oss08;
  oss03 << xs_vec[0];
  oss04 << ene_vec[0];
  oss05 << xs_vec[1];
  oss06 << ene_vec[1];
  oss07 << xs_vec[2];
  oss08 << ene_vec[2];
  string str_data02 = "XS at first  energy grid : " + oss03.str() + " barn @ " + oss04.str() + " eV";
  string str_data03 = "XS at second energy grid : " + oss05.str() + " barn @ " + oss06.str() + " eV";
  string str_data04 = "XS at third  energy grid : " + oss07.str() + " barn @ " + oss08.str() + " eV";
  err_com.push_back(str_data02);
  err_com.push_back(str_data03);
  err_com.push_back(str_data04);

  if( xs_vec[0] > min_sig_val )
  {
    if( xs_vec[1] < min_sig_val || xs_vec[2] < min_sig_val )
    {
      ostringstream oss09;
      oss09.setf(ios::scientific);
      oss09 << min_sig_val;

      string str_data05 = "Minimum xs value         : " + oss09.str();
      err_com.push_back(str_data05);

      if( xs_vec[1] < min_sig_val )
      {
        err_com.push_back("Cross section data at second energy grid is less than minimum sigma value.");
      }
      if( xs_vec[2] < min_sig_val )
      {
        err_com.push_back("Cross section data at third energy grid is less than minimum sigma value.");
      }

      err_com.push_back("This nuclear data file can not appropriately extrapolate the first xs data.");
      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
  }


  //Calc initial xs data
  Real    ene_m   = ene_vec[1];
  Real    ene_p   = ene_vec[2];
  Real    xs_m    = xs_vec[1];
  Real    xs_p    = xs_vec[2];

  TabInterpolator ti_obj;
  Integer int_val = ti_obj.search_interpolation_range(range_vec, int_vec, 1);
  ti_obj.interpolation_1d(int_val, ene_vec[0], xs_vec[0], ene_m, xs_m, ene_p, xs_p);

  ostringstream oss10, oss11;
  oss10 << xs_vec[0];
  oss11 << ene_vec[0];
  string str_data06 = "Modified XS at first energy grid : " + oss10.str() + " barn @ " + oss11.str() + " eV";

  err_com.push_back("");
  err_com.push_back("The XS at first energy grid is modified extrapolating second and third grid data.");
  err_com.push_back(str_data06);

  err_com.push_back("");
  err_com.push_back("Note that total cross section is not used for the xs linearization.");
  err_com.push_back("In this program, total and elastic scattering cross section is only modified.");
  err_com.push_back("If other cross section data e.g., fission, radiation capture and so on, has");
  err_com.push_back("similar problem, the total cross section at first energy grid is modified to");
  err_com.push_back("the elastic scattering cross section when linearization is applied.");
  err_com.push_back("");
  err_com.push_back("It is strongly recommended to check the nuclear data not only total and");
  err_com.push_back("elastic scattering but also other reaction type.");

  err_obj.output_caution(class_name, func_name, err_com);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Converter::check_mt_list_all(vector<MF03Parser>& mf03_data_obj,
                                       vector<MF04Parser>& mf04_data_obj,
                                       vector<MF05Parser>& mf05_data_obj,
                                       vector<MF06Parser>& mf06_data_obj,
                                       vector<MF09Parser>& mf09_data_obj,
                                       vector<MF10Parser>& mf10_data_obj)
{
  vector<Integer> mt_list_mf03, mt_list_mf04, mt_list_mf05, mt_list_mf06, mt_list_mf09, mt_list_mf10;

  //Read MT list for MF=03
  int i_max = static_cast<int>(mf03_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no = mf03_data_obj[i].get_mt_no();
    if( mt_no == unassigned_mt_no )
    {
      continue;
    }

    int mt_add_flg = 0;

    //If all cross section data is zero, this MT number is skipped from MT list
    vector<Real> xs_vec = mf03_data_obj[i].get_SIG_TAB();
    int j_max = static_cast<int>(xs_vec.size());
    for(int j=0; j<j_max; j++)
    {
      if( fabs(xs_vec[j]) > min_value )
      {
        mt_add_flg = 1;
        break;
      }
    }

    if( mt_add_flg > 0 )
    {
      mt_list_mf03.push_back(mt_no);
    }
  }

  //Read MT list for MF=04
  i_max = static_cast<int>(mf04_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no = mf04_data_obj[i].get_mt_no();
    if( mt_no == unassigned_mt_no )
    {
      continue;
    }
    mt_list_mf04.push_back(mt_no);
  }
  check_mt_list(3, 4, mt_list_mf03, mt_list_mf04);

  //Read MT list for MF=05
  i_max = static_cast<int>(mf05_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no = mf05_data_obj[i].get_mt_no();
    if( mt_no == unassigned_mt_no )
    {
      continue;
    }
    mt_list_mf05.push_back(mt_no);
  }
  check_mt_list(3, 5, mt_list_mf03, mt_list_mf05);

  //Read MT list for MF=06
  i_max = static_cast<int>(mf06_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no = mf06_data_obj[i].get_mt_no();
    if( mt_no == unassigned_mt_no )
    {
      continue;
    }
    mt_list_mf06.push_back(mt_no);
  }
  check_mt_list(3, 6, mt_list_mf03, mt_list_mf06);

  //Read MT list for MF=09
  i_max = static_cast<int>(mf09_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no = mf09_data_obj[i].get_mt_no();
    if( mt_no == unassigned_mt_no )
    {
      continue;
    }
    mt_list_mf09.push_back(mt_no);
  }
  check_mt_list(3, 9, mt_list_mf03, mt_list_mf09);

  //Read MT list for MF=10
  i_max = static_cast<int>(mf10_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no = mf10_data_obj[i].get_mt_no();
    if( mt_no == unassigned_mt_no )
    {
      continue;
    }
    mt_list_mf10.push_back(mt_no);
  }
  check_mt_list(3, 10, mt_list_mf03, mt_list_mf10);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Converter::check_mt_list(Integer mf_no_ref, Integer mf_no_com,
                                   vector<Integer> mt_list_ref, vector<Integer> mt_list_com)
{
  sort(mt_list_ref.begin(), mt_list_ref.end());
  sort(mt_list_com.begin(), mt_list_com.end());

  vector<Integer> mt_err;
  mt_err.clear();

  int i_max = static_cast<int>(mt_list_com.size());
  for(int i=0; i<i_max; i++)
  {
    int mt_check_flg = 0;
    int j_max        = static_cast<int>(mt_list_ref.size());
    for(int j=0; j<j_max; j++)
    {
      if( mt_list_com[i] == mt_list_ref[j] )
      {
        mt_check_flg = 1;
        break;
      }
    }
    if( mt_check_flg == 0 )
    {
      mt_err.push_back(mt_list_com[i]);
    }
  }

  i_max = static_cast<int>(mt_err.size());
  if( i_max > 0 )
  {
    string class_name = "Endf6Converter";
    string func_name  = "check_mt_list";

    ostringstream oss01, oss02;
    oss01 << mf_no_ref;
    oss02 << mf_no_com;

    string str_data01, str_data02;
    str_data01 = "Reference MF number : " + oss01.str();
    str_data02 = "Target MF number    : " + oss02.str();

    vector<string> err_com;
    err_com.push_back(str_data01);
    err_com.push_back(str_data02);
    err_com.push_back("");
    err_com.push_back("The following MT numbers are only found in Target MF.");
    err_com.push_back("These MT numbers must be set in reference and target MF.");
    err_com.push_back("Please check the evaluated nuclear data library.");
    err_com.push_back("");
    for(int i=0; i<i_max; i++)
    {
      ostringstream oss03, oss04, oss05;
      oss03 << i+1;
      oss04 << i_max;
      oss05 << mt_err[i];

      string str_data03 = "  " + oss03.str() + " / " + oss04.str() + " : " + oss05.str();
      err_com.push_back(str_data03);
    }

    err_obj.output_caution_format(class_name, func_name, err_com);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Endf6Converter::check_fission_data(MF01MT452Parser& mf01mt452_data_obj,
       vector<MF03Parser>& mf03_data_obj, vector<MF04Parser>& mf04_data_obj,
       vector<MF05Parser>& mf05_data_obj, vector<MF06Parser>& mf06_data_obj)
{
  int i_max   = static_cast<int>(mf03_data_obj.size());
  int fis_flg = 0;
  for(int i=0; i<i_max; i++)
  {
    if( mf03_data_obj[i].get_mt_no() == 18 )
    {
      fis_flg = 1;
      break;
    }
  }

  if( fis_flg == 0 )
  {
    return;
  }
  else if( static_cast<int>(mf04_data_obj.size()) == 0 &&
           static_cast<int>(mf05_data_obj.size()) == 0 &&
           static_cast<int>(mf06_data_obj.size()) == 0 )
  {
    //This nuclear data file is PENDF file
    return;
  }

  int fis_flg_angle = 0;
  int fis_flg_ene   = 0;
  int fis_flg_nu    = 0;

  //Check MF=1, MT=452 (nu)
  if( static_cast<int>(mf01mt452_data_obj.get_C().size())  > 0 ||
      static_cast<int>(mf01mt452_data_obj.get_NU().size()) > 0 )
  {
    fis_flg_nu = 1;
  }

  //Check MF=04
  i_max = static_cast<int>(mf04_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    if( mf04_data_obj[i].get_mt_no() == 18 )
    {
      fis_flg_angle = 1;
      break;
    }
  }

  //Check MF=05
  i_max = static_cast<int>(mf05_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    if( mf05_data_obj[i].get_mt_no() == 18 )
    {
      fis_flg_ene   = 1;
      break;
    }
  }

  //Check MF=06
  i_max = static_cast<int>(mf06_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    if( mf06_data_obj[i].get_mt_no() == 18 )
    {
      fis_flg_angle = 1;
      fis_flg_ene   = 1;
      break;
    }
  }

  if( fis_flg_nu == 0 || fis_flg_angle == 0 || fis_flg_ene == 0 )
  {
    string class_name = "Endf6Converter";
    string func_name  = "check_fission_data";

    vector<string> err_com;
    err_com.push_back("The fission cross section is found (MF=3, MT18).");

    if( fis_flg_nu == 0 )
    {
      err_com.push_back("The number of neutrons per fission (MF=1, MT=452) is not found.");
      err_com.push_back("");
    }

    if( fis_flg_angle == 0 )
    {
      err_com.push_back("The angular distribution of neutron (MF=4, MT=18) is not found.");
      err_com.push_back("");
    }

    if( fis_flg_ene == 0 )
    {
      err_com.push_back("The energy distribution of neutron (MF=5, MT=18) is not found.");
      err_com.push_back("");
    }

    if( fis_flg_nu == 0 || fis_flg_ene == 0 )
    {
      err_obj.output_caution(class_name, func_name, err_com);
    }
    else //if( fis_flg_angle == 0)
    {
      err_com.push_back("The isotropic angular distribution is set in MF=4, MT=18.");
      err_com.push_back("");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }

  if( fis_flg_angle == 0 )
  {
    Integer mt_no  = 18;
    Integer mat_no = 0;
    Real    ZA     = 0.0;
    Real    AWR    = 0.0;

    i_max   = static_cast<int>(mf03_data_obj.size());
    for(int i=0; i<i_max; i++)
    {
      if( mf03_data_obj[i].get_mt_no() == 18 )
      {
        mat_no = mf03_data_obj[i].get_mat_no();
        ZA     = mf03_data_obj[i].get_ZA();
        AWR    = mf03_data_obj[i].get_AWR();
        break;
      }
    }

    MF04Parser  fis_angle_obj;
    fis_angle_obj.clear();

    fis_angle_obj.set_mt_no(mt_no);
    fis_angle_obj.set_mat_no(mat_no);
    fis_angle_obj.set_ZA(ZA);
    fis_angle_obj.set_AWR(AWR);

    Integer LTT = 0;
    Integer LI  = 1;
    Integer LCT = 1;
    fis_angle_obj.set_LTT(LTT);
    fis_angle_obj.set_LI(LI);
    fis_angle_obj.set_LCT(LCT);

    mf04_data_obj.push_back(fis_angle_obj);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//NuclearDataObject -> Endf6Parser
void Endf6Converter::convert_frendy_to_endf_format(NuclearDataObject& frendy_obj, Endf6Parser& endf_obj)
{
  Endf6ParserNoCov endf_obj_no_cov;
  Endf6ParserCov   endf_obj_cov;

  //cout << "NuclearDataObject -> Endf6ParserNoCov" << endl;
  convert_frendy_to_endf_format(frendy_obj, endf_obj_no_cov);

  //cout << "NuclearDataObject -> Endf6ParserCov" << endl;
  convert_frendy_to_endf_format(frendy_obj, endf_obj_cov);

  endf_obj.set_endf6_parser_no_cov(endf_obj_no_cov);
  endf_obj.set_endf6_parser_cov(endf_obj_cov);
  endf_obj_no_cov.clear();
  endf_obj_cov.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Endf6Parser -> NuclearDataObject
void Endf6Converter::convert_endf_format_to_frendy(Endf6Parser& endf_obj, NuclearDataObject& frendy_obj)
{
  Endf6ParserNoCov endf_obj_no_cov = endf_obj.get_endf6_parser_no_cov();
  Endf6ParserCov   endf_obj_cov    = endf_obj.get_endf6_parser_cov();

  //cout << "Endf6ParserNoCov -> NuclearDataObject" << endl;
  convert_endf_format_to_frendy(endf_obj_no_cov, frendy_obj);

  //cout << "Endf6ParserCov -> NuclearDataObject" << endl;
  convert_endf_format_to_frendy(endf_obj_cov,    frendy_obj);
  
  //Check mat_no, mat_data and mass
  string  func_name = "convert_endf_format_to_frendy(Endf6Parser& endf_obj, NuclearDataObject& frendy_obj)";
  Integer mat_no_base   = frendy_obj.get_general_data_obj().get_mat_no();
  Real    mat_data_base = frendy_obj.get_general_data_obj().get_mat_data();
  Real    mass_base     = frendy_obj.get_general_data_obj().get_mass();
  Integer mat_no        = frendy_obj.get_cov_general_data_obj().get_mat_no();
  Real    mat_data      = frendy_obj.get_cov_general_data_obj().get_mat_data();
  Real    mass          = frendy_obj.get_cov_general_data_obj().get_mass();
  check_mat_data(func_name,30, 1, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

  func_name.clear();
  endf_obj_no_cov.clear();
  endf_obj_cov.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//NuclearDataObject -> Endf6ParserNoCov
void Endf6Converter::convert_frendy_to_endf_format(NuclearDataObject& frendy_obj, Endf6ParserNoCov& endf_obj)
{
  endf_obj.clear();
  
  //Declare and get each container object
  GeneralDataContainer        general_data_obj      = frendy_obj.get_general_data_obj();
  FissionDataContainer        fis_data_obj          = frendy_obj.get_fis_data_obj();
  ResonanceDataContainer      reso_data_obj         = frendy_obj.get_reso_data_obj();
  ThermalScatterDataContainer thermal_scat_data_obj = frendy_obj.get_thermal_scat_data_obj();

  UnresolvedCrossSectionDataContainer unreso_xs_data_obj   = reso_data_obj.get_unreso_xs_data_obj();
  UnresolvedProbabilityDataContainer  unreso_prob_data_obj = reso_data_obj.get_unreso_prob_data_obj();

  vector<Integer>                          reaction_type;
  vector<CrossSectionDataContainer>        xs_data_obj;
  vector<EnergyAngularDataContainer>       ene_angular_data_obj;
  vector<ProductDistributionDataContainer> product_distr_data_obj;
  vector<RadioactiveProductDataContainer>  radio_product_data_obj;
  vector<PhotonDataContainer>              photon_data_obj;
  vector<OtherNuclearDataContainer>        other_data_obj;

  reaction_type          = frendy_obj.get_nucl_reaction_data_obj().get_reaction_type();
  xs_data_obj            = frendy_obj.get_nucl_reaction_data_obj().get_xs_data_obj();
  ene_angular_data_obj   = frendy_obj.get_nucl_reaction_data_obj().get_ene_angular_data_obj();
  product_distr_data_obj = frendy_obj.get_nucl_reaction_data_obj().get_product_distr_data_obj();
  radio_product_data_obj = frendy_obj.get_nucl_reaction_data_obj().get_radio_product_data_obj();
  photon_data_obj        = frendy_obj.get_nucl_reaction_data_obj().get_photon_data_obj();
  other_data_obj         = frendy_obj.get_nucl_reaction_data_obj().get_other_data_obj();

  //Get general data
  Integer mat_no   = general_data_obj.get_mat_no();
  Real    mat_data = general_data_obj.get_mat_data();
  Real    mass     = general_data_obj.get_mass();

  //Declare MFxxMTyyyParser object
  MF01MT451Parser  mf01mt451_data_obj;
  MF01MT452Parser  mf01mt452_data_obj;
  MF01MT455Parser  mf01mt455_data_obj;
  MF01MT456Parser  mf01mt456_data_obj;
  MF01MT458Parser  mf01mt458_data_obj;
  MF01MT460Parser  mf01mt460_data_obj;
  MF02MT151Parser  mf02mt151_data_obj;
  MF02MT152Parser  mf02mt152_data_obj;
  MF02MT153Parser  mf02mt153_data_obj;
  MF07MT002Parser  mf07mt002_data_obj;
  MF07MT004Parser  mf07mt004_data_obj;
  MF07MT451Parser  mf07mt451_data_obj;
  MF08MT454Parser  mf08mt454_data_obj;
  MF08MT457Parser  mf08mt457_data_obj;
  MF08MT459Parser  mf08mt459_data_obj;

  //Convert NuclearDataObject to MFxxMTyyyParser object
  mf01mt451_conv_obj.convert_frendy_to_endf_format(general_data_obj,      mf01mt451_data_obj);
  mf01mt452_conv_obj.convert_frendy_to_endf_format(fis_data_obj,          mf01mt452_data_obj);
  mf01mt455_conv_obj.convert_frendy_to_endf_format(fis_data_obj,          mf01mt455_data_obj);
  mf01mt456_conv_obj.convert_frendy_to_endf_format(fis_data_obj,          mf01mt456_data_obj);
  mf01mt458_conv_obj.convert_frendy_to_endf_format(fis_data_obj,          mf01mt458_data_obj);
  mf01mt460_conv_obj.convert_frendy_to_endf_format(fis_data_obj,          mf01mt460_data_obj);
  mf02mt151_conv_obj.convert_frendy_to_endf_format(reso_data_obj,         mf02mt151_data_obj);
  mf02mt152_conv_obj.convert_frendy_to_endf_format(unreso_xs_data_obj,    mf02mt152_data_obj);
  mf02mt153_conv_obj.convert_frendy_to_endf_format(unreso_prob_data_obj,  mf02mt153_data_obj);
  mf07mt002_conv_obj.convert_frendy_to_endf_format(thermal_scat_data_obj, mf07mt002_data_obj);
  mf07mt004_conv_obj.convert_frendy_to_endf_format(thermal_scat_data_obj, mf07mt004_data_obj);
  mf07mt451_conv_obj.convert_frendy_to_endf_format(thermal_scat_data_obj, mf07mt451_data_obj);
  mf08mt454_conv_obj.convert_frendy_to_endf_format(fis_data_obj,          mf08mt454_data_obj);
  mf08mt457_conv_obj.convert_frendy_to_endf_format(general_data_obj,      mf08mt457_data_obj);
  mf08mt459_conv_obj.convert_frendy_to_endf_format(fis_data_obj,          mf08mt459_data_obj);

  //Set ZA and AWR
  mf01mt451_data_obj.set_mat_no(mat_no);
  mf01mt451_data_obj.set_ZA(mat_data);
  mf01mt451_data_obj.set_AWR(mass);

  if( mf01mt452_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf01mt452_data_obj.set_mat_no(mat_no);
    mf01mt452_data_obj.set_ZA(mat_data);
    mf01mt452_data_obj.set_AWR(mass);
  }

  if( mf01mt455_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf01mt455_data_obj.set_mat_no(mat_no);
    mf01mt455_data_obj.set_ZA(mat_data);
    mf01mt455_data_obj.set_AWR(mass);
  }

  if( mf01mt456_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf01mt456_data_obj.set_mat_no(mat_no);
    mf01mt456_data_obj.set_ZA(mat_data);
    mf01mt456_data_obj.set_AWR(mass);
  }

  if( mf01mt458_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf01mt458_data_obj.set_mat_no(mat_no);
    mf01mt458_data_obj.set_ZA(mat_data);
    mf01mt458_data_obj.set_AWR(mass);
  }

  if( mf01mt460_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf01mt460_data_obj.set_mat_no(mat_no);
    mf01mt460_data_obj.set_ZA(mat_data);
    mf01mt460_data_obj.set_AWR(mass);
  }

  if( mf02mt151_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf02mt151_data_obj.set_mat_no(mat_no);
    mf02mt151_data_obj.set_ZAR(mat_data);
    mf02mt151_data_obj.set_AWR(mass);
  }

  if( mf02mt152_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf02mt152_data_obj.set_mat_no(mat_no);
    mf02mt152_data_obj.set_ZAR(mat_data);
    mf02mt152_data_obj.set_AWR(mass);
  }

  if( mf02mt153_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf02mt153_data_obj.set_mat_no(mat_no);
    mf02mt153_data_obj.set_ZAR(mat_data);
    mf02mt153_data_obj.set_AWR(mass);
  }

  if( mf07mt002_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf07mt002_data_obj.set_mat_no(mat_no);
    mf07mt002_data_obj.set_ZA(mat_data);
    mf07mt002_data_obj.set_AWR(mass);
  }

  if( mf07mt004_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf07mt004_data_obj.set_mat_no(mat_no);
    mf07mt004_data_obj.set_ZA(mat_data);
    mf07mt004_data_obj.set_AWR(mass);
  }

  if( mf07mt451_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf07mt451_data_obj.set_mat_no(mat_no);
    mf07mt451_data_obj.set_ZA(mat_data);
    mf07mt451_data_obj.set_AWR(mass);
  }

  if( mf08mt454_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf08mt454_data_obj.set_mat_no(mat_no);
    mf08mt454_data_obj.set_ZA(mat_data);
    mf08mt454_data_obj.set_AWR(mass);
  }

  if( mf08mt457_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf08mt457_data_obj.set_mat_no(mat_no);
    mf08mt457_data_obj.set_ZA(mat_data);
    mf08mt457_data_obj.set_AWR(mass);
  }

  if( mf08mt459_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf08mt459_data_obj.set_mat_no(mat_no);
    mf08mt459_data_obj.set_ZA(mat_data);
    mf08mt459_data_obj.set_AWR(mass);
  }

  //Declare MFxxParser object
  vector<MF03Parser>  mf03_data_obj;
  vector<MF04Parser>  mf04_data_obj;
  vector<MF05Parser>  mf05_data_obj;
  vector<MF06Parser>  mf06_data_obj;
  vector<MF08Parser>  mf08_data_obj;
  vector<MF09Parser>  mf09_data_obj;
  vector<MF10Parser>  mf10_data_obj;
  vector<MF12Parser>  mf12_data_obj;
  vector<MF13Parser>  mf13_data_obj;
  vector<MF14Parser>  mf14_data_obj;
  vector<MF15Parser>  mf15_data_obj;
  vector<MF23Parser>  mf23_data_obj;
  vector<MF26Parser>  mf26_data_obj;
  vector<MF27Parser>  mf27_data_obj;
  vector<MF28Parser>  mf28_data_obj;
  mf03_data_obj.clear();
  mf04_data_obj.clear();
  mf05_data_obj.clear();
  mf06_data_obj.clear();
  mf08_data_obj.clear();
  mf09_data_obj.clear();
  mf10_data_obj.clear();
  mf12_data_obj.clear();
  mf13_data_obj.clear();
  mf14_data_obj.clear();
  mf15_data_obj.clear();
  mf23_data_obj.clear();
  mf26_data_obj.clear();
  mf27_data_obj.clear();
  mf28_data_obj.clear();

  //Convert NuclearDataObject to MFxxParser object
  int i_max = static_cast<int>(reaction_type.size());
  MF03Parser mf03_data_tmp;
  MF04Parser mf04_data_tmp;
  MF05Parser mf05_data_tmp;
  MF06Parser mf06_data_tmp;
  MF08Parser mf08_data_tmp;
  MF09Parser mf09_data_tmp;
  MF10Parser mf10_data_tmp;
  MF12Parser mf12_data_tmp;
  MF13Parser mf13_data_tmp;
  MF14Parser mf14_data_tmp;
  MF15Parser mf15_data_tmp;
  MF23Parser mf23_data_tmp;
  MF26Parser mf26_data_tmp;
  MF27Parser mf27_data_tmp;
  MF28Parser mf28_data_tmp;
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no = reaction_type[i];

    if( xs_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      mf03_conv_obj.convert_frendy_to_endf_format(xs_data_obj[i], mf03_data_tmp);
      if( mf03_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf03_data_tmp.set_mt_no(mt_no);
        mf03_data_tmp.set_mat_no(mat_no);
        mf03_data_tmp.set_ZA(mat_data);
        mf03_data_tmp.set_AWR(mass);
        mf03_data_obj.push_back(mf03_data_tmp);
      }
      mf03_data_tmp.clear();
    }

    if( ene_angular_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      mf04_conv_obj.convert_frendy_to_endf_format(ene_angular_data_obj[i], mf04_data_tmp);
      if( mf04_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf04_data_tmp.set_mat_no(mat_no);
        mf04_data_tmp.set_ZA(mat_data);
        mf04_data_tmp.set_AWR(mass);
        mf04_data_obj.push_back(mf04_data_tmp);
      }
      mf04_data_tmp.clear();

      mf05_conv_obj.convert_frendy_to_endf_format(ene_angular_data_obj[i], mf05_data_tmp);
      if( mf05_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf05_data_tmp.set_mat_no(mat_no);
        mf05_data_tmp.set_ZA(mat_data);
        mf05_data_tmp.set_AWR(mass);
        mf05_data_obj.push_back(mf05_data_tmp);
      }
      mf05_data_tmp.clear();
    }

    if( product_distr_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      mf06_conv_obj.convert_frendy_to_endf_format(product_distr_data_obj[i], mf06_data_tmp);
      if( mf06_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf06_data_tmp.set_mat_no(mat_no);
        mf06_data_tmp.set_ZA(mat_data);
        mf06_data_tmp.set_AWR(mass);
        mf06_data_obj.push_back(mf06_data_tmp);
      }
      mf06_data_tmp.clear();

      mf26_conv_obj.convert_frendy_to_endf_format(product_distr_data_obj[i], mf26_data_tmp);
      if( mf26_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf26_data_tmp.set_mat_no(mat_no);
        mf26_data_tmp.set_ZA(mat_data);
        mf26_data_tmp.set_AWR(mass);
        mf26_data_obj.push_back(mf26_data_tmp);
      }
      mf26_data_tmp.clear();
    }

    if( radio_product_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      mf08_conv_obj.convert_frendy_to_endf_format(radio_product_data_obj[i], mf08_data_tmp);
      if( mf08_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf08_data_tmp.set_mat_no(mat_no);
        mf08_data_tmp.set_ZA(mat_data);
        mf08_data_tmp.set_AWR(mass);
        mf08_data_obj.push_back(mf08_data_tmp);
      }
      mf08_data_tmp.clear();

      mf09_conv_obj.convert_frendy_to_endf_format(radio_product_data_obj[i], mf09_data_tmp);
      if( mf09_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf09_data_tmp.set_mat_no(mat_no);
        mf09_data_tmp.set_ZA(mat_data);
        mf09_data_tmp.set_AWR(mass);
        mf09_data_obj.push_back(mf09_data_tmp);
      }
      mf09_data_tmp.clear();

      mf10_conv_obj.convert_frendy_to_endf_format(radio_product_data_obj[i], mf10_data_tmp);
      if( mf10_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf10_data_tmp.set_mat_no(mat_no);
        mf10_data_tmp.set_ZA(mat_data);
        mf10_data_tmp.set_AWR(mass);
        mf10_data_obj.push_back(mf10_data_tmp);
      }
      mf10_data_tmp.clear();
    }

    if( photon_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      mf12_conv_obj.convert_frendy_to_endf_format(photon_data_obj[i], mf12_data_tmp);
      if( mf12_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf12_data_tmp.set_mat_no(mat_no);
        mf12_data_tmp.set_ZA(mat_data);
        mf12_data_tmp.set_AWR(mass);
        mf12_data_obj.push_back(mf12_data_tmp);
      }
      mf12_data_tmp.clear();

      mf13_conv_obj.convert_frendy_to_endf_format(photon_data_obj[i], mf13_data_tmp);
      if( mf13_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf13_data_tmp.set_mat_no(mat_no);
        mf13_data_tmp.set_ZA(mat_data);
        mf13_data_tmp.set_AWR(mass);
        mf13_data_obj.push_back(mf13_data_tmp);
      }
      mf13_data_tmp.clear();

      mf14_conv_obj.convert_frendy_to_endf_format(photon_data_obj[i], mf14_data_tmp);
      if( mf14_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf14_data_tmp.set_mat_no(mat_no);
        mf14_data_tmp.set_ZA(mat_data);
        mf14_data_tmp.set_AWR(mass);
        mf14_data_obj.push_back(mf14_data_tmp);
      }
      mf14_data_tmp.clear();

      mf15_conv_obj.convert_frendy_to_endf_format(photon_data_obj[i], mf15_data_tmp);
      if( mf15_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf15_data_tmp.set_mat_no(mat_no);
        mf15_data_tmp.set_ZA(mat_data);
        mf15_data_tmp.set_AWR(mass);
        mf15_data_obj.push_back(mf15_data_tmp);
      }
      mf15_data_tmp.clear();

      mf23_conv_obj.convert_frendy_to_endf_format(photon_data_obj[i], mf23_data_tmp);
      if( mf23_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf23_data_tmp.set_mat_no(mat_no);
        mf23_data_tmp.set_ZA(mat_data);
        mf23_data_tmp.set_AWR(mass);
        mf23_data_obj.push_back(mf23_data_tmp);
      }
      mf23_data_tmp.clear();
    }

    if( other_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      mf27_conv_obj.convert_frendy_to_endf_format(other_data_obj[i], mf27_data_tmp);
      if( mf27_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf27_data_tmp.set_mat_no(mat_no);
        mf27_data_tmp.set_ZA(mat_data);
        mf27_data_tmp.set_AWR(mass);
        mf27_data_obj.push_back(mf27_data_tmp);
      }
      mf27_data_tmp.clear();

      mf28_conv_obj.convert_frendy_to_endf_format(other_data_obj[i], mf28_data_tmp);
      if( mf28_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf28_data_tmp.set_mat_no(mat_no);
        mf28_data_tmp.set_ZA(mat_data);
        mf28_data_tmp.set_AWR(mass);
        mf28_data_obj.push_back(mf28_data_tmp);
      }
      mf28_data_tmp.clear();
    }
  }

  //Set MFxxMTyyyParser object to endf_obj
  endf_obj.set_mf01_mt451_data(mf01mt451_data_obj);
  endf_obj.set_mf01_mt452_data(mf01mt452_data_obj);
  endf_obj.set_mf01_mt455_data(mf01mt455_data_obj);
  endf_obj.set_mf01_mt456_data(mf01mt456_data_obj);
  endf_obj.set_mf01_mt458_data(mf01mt458_data_obj);
  endf_obj.set_mf01_mt460_data(mf01mt460_data_obj);
  endf_obj.set_mf02_mt151_data(mf02mt151_data_obj);
  endf_obj.set_mf02_mt152_data(mf02mt152_data_obj);
  endf_obj.set_mf02_mt153_data(mf02mt153_data_obj);
  endf_obj.set_mf07_mt002_data(mf07mt002_data_obj);
  endf_obj.set_mf07_mt004_data(mf07mt004_data_obj);
  endf_obj.set_mf07_mt451_data(mf07mt451_data_obj);
  endf_obj.set_mf08_mt454_data(mf08mt454_data_obj);
  endf_obj.set_mf08_mt457_data(mf08mt457_data_obj);
  endf_obj.set_mf08_mt459_data(mf08mt459_data_obj);

  //Set MFxxParser object to endf_obj
  endf_obj.set_mf03_data(mf03_data_obj);
  endf_obj.set_mf04_data(mf04_data_obj);
  endf_obj.set_mf05_data(mf05_data_obj);
  endf_obj.set_mf06_data(mf06_data_obj);
  endf_obj.set_mf08_data(mf08_data_obj);
  endf_obj.set_mf09_data(mf09_data_obj);
  endf_obj.set_mf10_data(mf10_data_obj);
  endf_obj.set_mf12_data(mf12_data_obj);
  endf_obj.set_mf13_data(mf13_data_obj);
  endf_obj.set_mf14_data(mf14_data_obj);
  endf_obj.set_mf15_data(mf15_data_obj);
  endf_obj.set_mf23_data(mf23_data_obj);
  endf_obj.set_mf26_data(mf26_data_obj);
  endf_obj.set_mf27_data(mf27_data_obj);
  endf_obj.set_mf28_data(mf28_data_obj);

  //Clear MFxxMTyyyParser object
  mf01mt451_data_obj.clear();
  mf01mt452_data_obj.clear();
  mf01mt455_data_obj.clear();
  mf01mt456_data_obj.clear();
  mf01mt458_data_obj.clear();
  mf01mt460_data_obj.clear();
  mf02mt151_data_obj.clear();
  mf02mt152_data_obj.clear();
  mf02mt153_data_obj.clear();
  mf07mt002_data_obj.clear();
  mf07mt004_data_obj.clear();
  mf07mt451_data_obj.clear();
  mf08mt454_data_obj.clear();
  mf08mt457_data_obj.clear();
  mf08mt459_data_obj.clear();

  //Clear MFxxParser object
  for(int i=0; i<static_cast<int>(mf03_data_obj.size()); i++)
  {
    mf03_data_obj[i].clear();
  }
  mf03_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf04_data_obj.size()); i++)
  {
    mf04_data_obj[i].clear();
  }
  mf04_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf05_data_obj.size()); i++)
  {
    mf05_data_obj[i].clear();
  }
  mf05_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf06_data_obj.size()); i++)
  {
    mf06_data_obj[i].clear();
  }
  mf06_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf08_data_obj.size()); i++)
  {
    mf08_data_obj[i].clear();
  }
  mf08_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf09_data_obj.size()); i++)
  {
    mf09_data_obj[i].clear();
  }
  mf09_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf10_data_obj.size()); i++)
  {
    mf10_data_obj[i].clear();
  }
  mf10_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf12_data_obj.size()); i++)
  {
    mf12_data_obj[i].clear();
  }
  mf12_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf13_data_obj.size()); i++)
  {
    mf13_data_obj[i].clear();
  }
  mf13_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf14_data_obj.size()); i++)
  {
    mf14_data_obj[i].clear();
  }
  mf14_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf15_data_obj.size()); i++)
  {
    mf15_data_obj[i].clear();
  }
  mf15_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf23_data_obj.size()); i++)
  {
    mf23_data_obj[i].clear();
  }
  mf23_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf26_data_obj.size()); i++)
  {
    mf26_data_obj[i].clear();
  }
  mf26_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf27_data_obj.size()); i++)
  {
    mf27_data_obj[i].clear();
  }
  mf27_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf28_data_obj.size()); i++)
  {
    mf28_data_obj[i].clear();
  }
  mf28_data_obj.resize(0);

  //Clear each container object
  general_data_obj.clear();
  fis_data_obj.clear();
  reso_data_obj.clear();
  thermal_scat_data_obj.clear();
  unreso_xs_data_obj.clear();
  unreso_prob_data_obj.clear();

  i_max = static_cast<int>(reaction_type.size());
  for(int i=0; i<i_max; i++)
  {
    xs_data_obj[i].clear();
    ene_angular_data_obj[i].clear();
    product_distr_data_obj[i].clear();
    radio_product_data_obj[i].clear();
    photon_data_obj[i].clear();
    other_data_obj[i].clear();
  }
  reaction_type.resize(0);
  xs_data_obj.resize(0);
  ene_angular_data_obj.resize(0);
  product_distr_data_obj.resize(0);
  radio_product_data_obj.resize(0);
  photon_data_obj.resize(0);
  other_data_obj.resize(0);

  reaction_type.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Endf6ParserNoCov -> NuclearDataObject
void Endf6Converter::convert_endf_format_to_frendy(Endf6ParserNoCov& endf_obj, NuclearDataObject& frendy_obj)
{
  frendy_obj.clear();
  string func_name  = "convert_endf_format_to_frendy";
  func_name = func_name + "(Endf6ParserNoCov& endf_obj, NuclearDataObject& frendy_obj)";
  
  //Declare and get MFxxMTyyyParser object
  MF01MT451Parser  mf01mt451_data_obj = endf_obj.get_mf01_mt451_data();
  MF01MT452Parser  mf01mt452_data_obj = endf_obj.get_mf01_mt452_data();
  MF01MT455Parser  mf01mt455_data_obj = endf_obj.get_mf01_mt455_data();
  MF01MT456Parser  mf01mt456_data_obj = endf_obj.get_mf01_mt456_data();
  MF01MT458Parser  mf01mt458_data_obj = endf_obj.get_mf01_mt458_data();
  MF01MT460Parser  mf01mt460_data_obj = endf_obj.get_mf01_mt460_data();
  MF02MT151Parser  mf02mt151_data_obj = endf_obj.get_mf02_mt151_data();
  MF02MT152Parser  mf02mt152_data_obj = endf_obj.get_mf02_mt152_data();
  MF02MT153Parser  mf02mt153_data_obj = endf_obj.get_mf02_mt153_data();
  MF07MT002Parser  mf07mt002_data_obj = endf_obj.get_mf07_mt002_data();
  MF07MT004Parser  mf07mt004_data_obj = endf_obj.get_mf07_mt004_data();
  MF07MT451Parser  mf07mt451_data_obj = endf_obj.get_mf07_mt451_data();
  MF08MT454Parser  mf08mt454_data_obj = endf_obj.get_mf08_mt454_data();
  MF08MT457Parser  mf08mt457_data_obj = endf_obj.get_mf08_mt457_data();
  MF08MT459Parser  mf08mt459_data_obj = endf_obj.get_mf08_mt459_data();
  
  //Declare and get MFxxParser object
  vector<MF03Parser>  mf03_data_obj = endf_obj.get_mf03_data();
  vector<MF04Parser>  mf04_data_obj = endf_obj.get_mf04_data();
  vector<MF05Parser>  mf05_data_obj = endf_obj.get_mf05_data();
  vector<MF06Parser>  mf06_data_obj = endf_obj.get_mf06_data();
  vector<MF08Parser>  mf08_data_obj = endf_obj.get_mf08_data();
  vector<MF09Parser>  mf09_data_obj = endf_obj.get_mf09_data();
  vector<MF10Parser>  mf10_data_obj = endf_obj.get_mf10_data();
  vector<MF12Parser>  mf12_data_obj = endf_obj.get_mf12_data();
  vector<MF13Parser>  mf13_data_obj = endf_obj.get_mf13_data();
  vector<MF14Parser>  mf14_data_obj = endf_obj.get_mf14_data();
  vector<MF15Parser>  mf15_data_obj = endf_obj.get_mf15_data();
  vector<MF23Parser>  mf23_data_obj = endf_obj.get_mf23_data();
  vector<MF26Parser>  mf26_data_obj = endf_obj.get_mf26_data();
  vector<MF27Parser>  mf27_data_obj = endf_obj.get_mf27_data();
  vector<MF28Parser>  mf28_data_obj = endf_obj.get_mf28_data();
  
  
  //Declare each container object
  GeneralDataContainer        general_data_obj;
  FissionDataContainer        fis_data_obj;
  ResonanceDataContainer      reso_data_obj;
  ThermalScatterDataContainer thermal_scat_data_obj;

  UnresolvedCrossSectionDataContainer unreso_xs_data_obj;
  UnresolvedProbabilityDataContainer  unreso_prob_data_obj;
  
  NuclearReactionDataContainer     nucl_reaction_data_obj;
  CrossSectionDataContainer        xs_data_obj;
  EnergyAngularDataContainer       ene_angular_data_obj;
  ProductDistributionDataContainer product_distr_data_obj;
  RadioactiveProductDataContainer  radio_product_data_obj;
  PhotonDataContainer              photon_data_obj;
  OtherNuclearDataContainer        other_data_obj;
  
  
  //Check mat_no, mat_data and mass
  Integer mat_no_base, mat_no;
  Real    mat_data_base, mat_data, mass_base, mass, temp_base, temp;
  
  mat_no_base   = mf01mt451_data_obj.get_mat_no();
  mat_data_base = mf01mt451_data_obj.get_ZA();
  mass_base     = mf01mt451_data_obj.get_AWR();
  temp_base     = mf01mt451_data_obj.get_TEMP();
  
  mat_no   = mf01mt452_data_obj.get_mat_no();
  mat_data = mf01mt452_data_obj.get_ZA();
  mass     = mf01mt452_data_obj.get_AWR();
  check_mat_data(func_name, 1, 452, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  mat_no   = mf01mt455_data_obj.get_mat_no();
  mat_data = mf01mt455_data_obj.get_ZA();
  mass     = mf01mt455_data_obj.get_AWR();
  check_mat_data(func_name, 1, 455, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  mat_no   = mf01mt456_data_obj.get_mat_no();
  mat_data = mf01mt456_data_obj.get_ZA();
  mass     = mf01mt456_data_obj.get_AWR();
  check_mat_data(func_name, 1, 456, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  mat_no   = mf01mt458_data_obj.get_mat_no();
  mat_data = mf01mt458_data_obj.get_ZA();
  mass     = mf01mt458_data_obj.get_AWR();
  check_mat_data(func_name, 1, 458, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  mat_no   = mf01mt460_data_obj.get_mat_no();
  mat_data = mf01mt460_data_obj.get_ZA();
  mass     = mf01mt460_data_obj.get_AWR();
  check_mat_data(func_name, 1, 460, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  mat_no   = mf02mt151_data_obj.get_mat_no();
  mat_data = mf02mt151_data_obj.get_ZAR();
  mass     = mf02mt151_data_obj.get_AWR();
  check_mat_data(func_name, 2, 151, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  mat_no   = mf02mt152_data_obj.get_mat_no();
  mat_data = mf02mt152_data_obj.get_ZAR();
  mass     = mf02mt152_data_obj.get_AWR();
  temp     = mf02mt152_data_obj.get_TEMP();
  check_mat_data(func_name, 2, 152, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  check_temp_data(func_name, 2, 152, mat_no, temp, temp_base);
  
  mat_no   = mf02mt153_data_obj.get_mat_no();
  mat_data = mf02mt153_data_obj.get_ZAR();
  mass     = mf02mt153_data_obj.get_AWR();
  temp     = mf02mt153_data_obj.get_TEMP();
  check_mat_data(func_name, 2, 153, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  check_temp_data(func_name, 2, 153, mat_no, temp, temp_base);
  
  mat_no   = mf07mt002_data_obj.get_mat_no();
  mat_data = mf07mt002_data_obj.get_ZA();
  mass     = mf07mt002_data_obj.get_AWR();
  check_mat_data(func_name, 7,   2, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  mat_no   = mf07mt004_data_obj.get_mat_no();
  mat_data = mf07mt004_data_obj.get_ZA();
  mass     = mf07mt004_data_obj.get_AWR();
  check_mat_data(func_name, 7,   4, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  mat_no   = mf07mt451_data_obj.get_mat_no();
  mat_data = mf07mt451_data_obj.get_ZA();
  mass     = mf07mt451_data_obj.get_AWR();
  check_mat_data(func_name, 7, 451, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  mat_no   = mf08mt454_data_obj.get_mat_no();
  mat_data = mf08mt454_data_obj.get_ZA();
  mass     = mf08mt454_data_obj.get_AWR();
  check_mat_data(func_name, 8, 454, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  mat_no   = mf08mt457_data_obj.get_mat_no();
  mat_data = mf08mt457_data_obj.get_ZA();
  mass     = mf08mt457_data_obj.get_AWR();
  check_mat_data(func_name, 8, 457, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  mat_no   = mf08mt459_data_obj.get_mat_no();
  mat_data = mf08mt459_data_obj.get_ZA();
  mass     = mf08mt459_data_obj.get_AWR();
  check_mat_data(func_name, 8, 459, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  
  //Check MT number
  check_mt_list_all(mf03_data_obj, mf04_data_obj, mf05_data_obj, mf06_data_obj, 
                    mf09_data_obj, mf10_data_obj);
  
  if( static_cast<int>(mf02mt152_data_obj.get_SIG_TOT().size()) == 0 &&
      static_cast<int>(mf02mt153_data_obj.get_P_TABLE().size()) == 0 )
  {
    //Check fission reaction data (without PENDF file)
    check_fission_data(mf01mt452_data_obj, mf03_data_obj,
                       mf04_data_obj, mf05_data_obj, mf06_data_obj);
  }

  //Convert MFxxMTyyyParser object to NuclearDataObject
  general_data_obj.clear();
  fis_data_obj.clear();
  reso_data_obj.clear();
  thermal_scat_data_obj.clear();
  
  mf01mt451_conv_obj.convert_endf_format_to_frendy(mf01mt451_data_obj, general_data_obj);
  mf01mt452_conv_obj.convert_endf_format_to_frendy(mf01mt452_data_obj, fis_data_obj);
  mf01mt455_conv_obj.convert_endf_format_to_frendy(mf01mt455_data_obj, fis_data_obj);
  mf01mt456_conv_obj.convert_endf_format_to_frendy(mf01mt456_data_obj, fis_data_obj);
  mf01mt458_conv_obj.convert_endf_format_to_frendy(mf01mt458_data_obj, fis_data_obj);
  mf01mt460_conv_obj.convert_endf_format_to_frendy(mf01mt460_data_obj, fis_data_obj);
  mf02mt151_conv_obj.convert_endf_format_to_frendy(mf02mt151_data_obj, reso_data_obj);
  mf02mt152_conv_obj.convert_endf_format_to_frendy(mf02mt152_data_obj, unreso_xs_data_obj);
  mf02mt153_conv_obj.convert_endf_format_to_frendy(mf02mt153_data_obj, unreso_prob_data_obj);
  mf07mt002_conv_obj.convert_endf_format_to_frendy(mf07mt002_data_obj, thermal_scat_data_obj);
  mf07mt004_conv_obj.convert_endf_format_to_frendy(mf07mt004_data_obj, thermal_scat_data_obj);
  mf07mt451_conv_obj.convert_endf_format_to_frendy(mf07mt451_data_obj, thermal_scat_data_obj);
  mf08mt454_conv_obj.convert_endf_format_to_frendy(mf08mt454_data_obj, fis_data_obj);
  mf08mt457_conv_obj.convert_endf_format_to_frendy(mf08mt457_data_obj, general_data_obj);
  mf08mt459_conv_obj.convert_endf_format_to_frendy(mf08mt459_data_obj, fis_data_obj);

  reso_data_obj.set_unreso_xs_data_obj(unreso_xs_data_obj);
  reso_data_obj.set_unreso_prob_data_obj(unreso_prob_data_obj);

  //Check mat_no, mat_data and mass and convert MFxxParser object to NuclearDataObject
  Integer mt_no;
  
  nucl_reaction_data_obj.clear();
  xs_data_obj.clear();
  ene_angular_data_obj.clear();
  product_distr_data_obj.clear();
  radio_product_data_obj.clear();
  photon_data_obj.clear();
  other_data_obj.clear();
  
  int i_max = static_cast<int>(mf03_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf03_data_obj[i].get_mt_no();
    mat_no   = mf03_data_obj[i].get_mat_no();
    mat_data = mf03_data_obj[i].get_ZA();
    mass     = mf03_data_obj[i].get_AWR();
    check_mat_data(func_name, 3, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    xs_data_obj = nucl_reaction_data_obj.get_xs_data_obj(mt_no);
    mf03_conv_obj.convert_endf_format_to_frendy(mf03_data_obj[i], xs_data_obj);
    nucl_reaction_data_obj.set_xs_data_obj(mt_no, xs_data_obj);

    check_xs_data(func_name, mf02mt151_data_obj, mf03_data_obj[i]);
    
    mf03_data_obj[i].clear();
    xs_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf04_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf04_data_obj[i].get_mt_no();
    mat_no   = mf04_data_obj[i].get_mat_no();
    mat_data = mf04_data_obj[i].get_ZA();
    mass     = mf04_data_obj[i].get_AWR();
    check_mat_data(func_name, 4, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    ene_angular_data_obj = nucl_reaction_data_obj.get_ene_angular_data_obj(mt_no);
    mf04_conv_obj.convert_endf_format_to_frendy(mf04_data_obj[i], ene_angular_data_obj);
    nucl_reaction_data_obj.set_ene_angular_data_obj(mt_no, ene_angular_data_obj);
    
    mf04_data_obj[i].clear();
    ene_angular_data_obj.clear();
  }

  i_max = static_cast<int>(mf05_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf05_data_obj[i].get_mt_no();
    mat_no   = mf05_data_obj[i].get_mat_no();
    mat_data = mf05_data_obj[i].get_ZA();
    mass     = mf05_data_obj[i].get_AWR();
    check_mat_data(func_name, 5, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    ene_angular_data_obj = nucl_reaction_data_obj.get_ene_angular_data_obj(mt_no);
    mf05_conv_obj.convert_endf_format_to_frendy(mf05_data_obj[i], ene_angular_data_obj);
    nucl_reaction_data_obj.set_ene_angular_data_obj(mt_no, ene_angular_data_obj);
    
    mf05_data_obj[i].clear();
    ene_angular_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf06_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf06_data_obj[i].get_mt_no();
    mat_no   = mf06_data_obj[i].get_mat_no();
    mat_data = mf06_data_obj[i].get_ZA();
    mass     = mf06_data_obj[i].get_AWR();
    check_mat_data(func_name, 6, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    product_distr_data_obj = nucl_reaction_data_obj.get_product_distr_data_obj(mt_no);
    mf06_conv_obj.convert_endf_format_to_frendy(mf06_data_obj[i], product_distr_data_obj);
    nucl_reaction_data_obj.set_product_distr_data_obj(mt_no, product_distr_data_obj);
    
    mf06_data_obj[i].clear();
    product_distr_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf08_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf08_data_obj[i].get_mt_no();
    mat_no   = mf08_data_obj[i].get_mat_no();
    mat_data = mf08_data_obj[i].get_ZA();
    mass     = mf08_data_obj[i].get_AWR();
    check_mat_data(func_name, 8, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    radio_product_data_obj = nucl_reaction_data_obj.get_radio_product_data_obj(mt_no);
    mf08_conv_obj.convert_endf_format_to_frendy(mf08_data_obj[i], radio_product_data_obj);
    nucl_reaction_data_obj.set_radio_product_data_obj(mt_no, radio_product_data_obj);
    
    mf08_data_obj[i].clear();
    radio_product_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf09_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf09_data_obj[i].get_mt_no();
    mat_no   = mf09_data_obj[i].get_mat_no();
    mat_data = mf09_data_obj[i].get_ZA();
    mass     = mf09_data_obj[i].get_AWR();
    check_mat_data(func_name, 9, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    radio_product_data_obj = nucl_reaction_data_obj.get_radio_product_data_obj(mt_no);
    mf09_conv_obj.convert_endf_format_to_frendy(mf09_data_obj[i], radio_product_data_obj);
    nucl_reaction_data_obj.set_radio_product_data_obj(mt_no, radio_product_data_obj);
    
    mf09_data_obj[i].clear();
    radio_product_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf10_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf10_data_obj[i].get_mt_no();
    mat_no   = mf10_data_obj[i].get_mat_no();
    mat_data = mf10_data_obj[i].get_ZA();
    mass     = mf10_data_obj[i].get_AWR();
    check_mat_data(func_name,10, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    radio_product_data_obj = nucl_reaction_data_obj.get_radio_product_data_obj(mt_no);

    mf10_conv_obj.convert_endf_format_to_frendy(mf10_data_obj[i], radio_product_data_obj);
    nucl_reaction_data_obj.set_radio_product_data_obj(mt_no, radio_product_data_obj);
    
    mf10_data_obj[i].clear();
    radio_product_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf12_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf12_data_obj[i].get_mt_no();
    mat_no   = mf12_data_obj[i].get_mat_no();
    mat_data = mf12_data_obj[i].get_ZA();
    mass     = mf12_data_obj[i].get_AWR();
    check_mat_data(func_name,12, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    photon_data_obj = nucl_reaction_data_obj.get_photon_data_obj(mt_no);
    mf12_conv_obj.convert_endf_format_to_frendy(mf12_data_obj[i], photon_data_obj);
    nucl_reaction_data_obj.set_photon_data_obj(mt_no, photon_data_obj);
    
    mf12_data_obj[i].clear();
    photon_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf13_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf13_data_obj[i].get_mt_no();
    mat_no   = mf13_data_obj[i].get_mat_no();
    mat_data = mf13_data_obj[i].get_ZA();
    mass     = mf13_data_obj[i].get_AWR();
    check_mat_data(func_name,13, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    photon_data_obj = nucl_reaction_data_obj.get_photon_data_obj(mt_no);
    mf13_conv_obj.convert_endf_format_to_frendy(mf13_data_obj[i], photon_data_obj);
    nucl_reaction_data_obj.set_photon_data_obj(mt_no, photon_data_obj);
    
    mf13_data_obj[i].clear();
    photon_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf14_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf14_data_obj[i].get_mt_no();
    mat_no   = mf14_data_obj[i].get_mat_no();
    mat_data = mf14_data_obj[i].get_ZA();
    mass     = mf14_data_obj[i].get_AWR();
    check_mat_data(func_name,14, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    photon_data_obj = nucl_reaction_data_obj.get_photon_data_obj(mt_no);
    mf14_conv_obj.convert_endf_format_to_frendy(mf14_data_obj[i], photon_data_obj);
    nucl_reaction_data_obj.set_photon_data_obj(mt_no, photon_data_obj);
    
    mf14_data_obj[i].clear();
    photon_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf15_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf15_data_obj[i].get_mt_no();
    mat_no   = mf15_data_obj[i].get_mat_no();
    mat_data = mf15_data_obj[i].get_ZA();
    mass     = mf15_data_obj[i].get_AWR();
    check_mat_data(func_name,15, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    photon_data_obj = nucl_reaction_data_obj.get_photon_data_obj(mt_no);
    mf15_conv_obj.convert_endf_format_to_frendy(mf15_data_obj[i], photon_data_obj);
    nucl_reaction_data_obj.set_photon_data_obj(mt_no, photon_data_obj);
    
    mf15_data_obj[i].clear();
    photon_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf23_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf23_data_obj[i].get_mt_no();
    mat_no   = mf23_data_obj[i].get_mat_no();
    mat_data = mf23_data_obj[i].get_ZA();
    mass     = mf23_data_obj[i].get_AWR();
    check_mat_data(func_name,23, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    photon_data_obj = nucl_reaction_data_obj.get_photon_data_obj(mt_no);
    mf23_conv_obj.convert_endf_format_to_frendy(mf23_data_obj[i], photon_data_obj);
    nucl_reaction_data_obj.set_photon_data_obj(mt_no, photon_data_obj);
    
    mf23_data_obj[i].clear();
    photon_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf26_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf26_data_obj[i].get_mt_no();
    mat_no   = mf26_data_obj[i].get_mat_no();
    mat_data = mf26_data_obj[i].get_ZA();
    mass     = mf26_data_obj[i].get_AWR();
    check_mat_data(func_name,26, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    product_distr_data_obj = nucl_reaction_data_obj.get_product_distr_data_obj(mt_no);
    mf26_conv_obj.convert_endf_format_to_frendy(mf26_data_obj[i], product_distr_data_obj);
    nucl_reaction_data_obj.set_product_distr_data_obj(mt_no, product_distr_data_obj);
    
    mf26_data_obj[i].clear();
    product_distr_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf27_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf27_data_obj[i].get_mt_no();
    mat_no   = mf27_data_obj[i].get_mat_no();
    mat_data = mf27_data_obj[i].get_ZA();
    mass     = mf27_data_obj[i].get_AWR();
    check_mat_data(func_name,27, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    other_data_obj = nucl_reaction_data_obj.get_other_data_obj(mt_no);
    mf27_conv_obj.convert_endf_format_to_frendy(mf27_data_obj[i], other_data_obj);
    nucl_reaction_data_obj.set_other_data_obj(mt_no, other_data_obj);
    
    mf27_data_obj[i].clear();
    other_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf28_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf28_data_obj[i].get_mt_no();
    mat_no   = mf28_data_obj[i].get_mat_no();
    mat_data = mf28_data_obj[i].get_ZA();
    mass     = mf28_data_obj[i].get_AWR();
    check_mat_data(func_name,28, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    other_data_obj = nucl_reaction_data_obj.get_other_data_obj(mt_no);
    mf28_conv_obj.convert_endf_format_to_frendy(mf28_data_obj[i], other_data_obj);
    nucl_reaction_data_obj.set_other_data_obj(mt_no, other_data_obj);
    
    mf28_data_obj[i].clear();
    other_data_obj.clear();
  }

  //Set mat_no, mat_data and mass
  general_data_obj.set_mat_no( mat_no_base );
  general_data_obj.set_mat_data( mat_data_base );
  general_data_obj.set_mass( mass_base );
  
  
  //Set each data container to frendy_obj
  frendy_obj.set_general_data_obj(general_data_obj);
  frendy_obj.set_fis_data_obj(fis_data_obj);
  frendy_obj.set_reso_data_obj(reso_data_obj);
  frendy_obj.set_thermal_scat_data_obj(thermal_scat_data_obj);
  frendy_obj.set_nucl_reaction_data_obj(nucl_reaction_data_obj);

  
  //Clear MFxxMTyyyParser object
  mf01mt451_data_obj.clear();
  mf01mt452_data_obj.clear();
  mf01mt455_data_obj.clear();
  mf01mt456_data_obj.clear();
  mf01mt458_data_obj.clear();
  mf01mt460_data_obj.clear();
  mf02mt151_data_obj.clear();
  mf02mt152_data_obj.clear();
  mf02mt153_data_obj.clear();
  mf07mt002_data_obj.clear();
  mf07mt004_data_obj.clear();
  mf07mt451_data_obj.clear();
  mf08mt454_data_obj.clear();
  mf08mt457_data_obj.clear();
  mf08mt459_data_obj.clear();
  
  //Clear MFxxParser object
  mf03_data_obj.resize(0);
  mf04_data_obj.resize(0);
  mf05_data_obj.resize(0);
  mf06_data_obj.resize(0);
  mf08_data_obj.resize(0);
  mf09_data_obj.resize(0);
  mf10_data_obj.resize(0);
  mf12_data_obj.resize(0);
  mf13_data_obj.resize(0);
  mf14_data_obj.resize(0);
  mf15_data_obj.resize(0);
  mf23_data_obj.resize(0);
  mf26_data_obj.resize(0);
  mf27_data_obj.resize(0);
  mf28_data_obj.resize(0);

  //Clear each data container
  general_data_obj.clear();
  fis_data_obj.clear();
  reso_data_obj.clear();
  thermal_scat_data_obj.clear();
  nucl_reaction_data_obj.clear();
  
  func_name.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//NuclearDataObject -> Endf6ParserCov
void Endf6Converter::convert_frendy_to_endf_format(NuclearDataObject& frendy_obj, Endf6ParserCov& endf_obj)
{
  endf_obj.clear();

  //Declare and get each container object
  CovarianceGeneralDataContainer    cov_general_data_obj  = frendy_obj.get_cov_general_data_obj();
  CovarianceResonanceDataContainer  cov_reso_data_obj     = frendy_obj.get_cov_reso_data_obj();

  vector<Integer>                                    reaction_type;
  vector<CovarianceFissionDataContainer>             cov_fis_data_obj;
  vector<CovarianceCrossSectionDataContainer>        cov_xs_data_obj;
  vector<CovarianceEnergyAngularDataContainer>       cov_ene_angular_data_obj;
  vector<CovarianceRadioactiveProductDataContainer>  cov_radio_product_data_obj;

  reaction_type              = frendy_obj.get_cov_reaction_data_obj().get_reaction_type();
  cov_fis_data_obj           = frendy_obj.get_cov_reaction_data_obj().get_cov_fis_data_obj();
  cov_xs_data_obj            = frendy_obj.get_cov_reaction_data_obj().get_cov_xs_data_obj();
  cov_ene_angular_data_obj   = frendy_obj.get_cov_reaction_data_obj().get_cov_ene_angular_data_obj();
  cov_radio_product_data_obj = frendy_obj.get_cov_reaction_data_obj().get_cov_radio_product_data_obj();

  //Get general data
  Integer mat_no   = cov_general_data_obj.get_mat_no();
  Real    mat_data = cov_general_data_obj.get_mat_data();
  Real    mass     = cov_general_data_obj.get_mass();

  //Declare MFxxMTyyyParser object
  MF30MT001Parser  mf30mt001_data_obj;
  MF30MT002Parser  mf30mt002_data_obj;
  MF32MT151Parser  mf32mt151_data_obj;

  //Convert NuclearDataObject to MFxxMTyyyParser object
  mf30mt001_conv_obj.convert_frendy_to_endf_format(cov_general_data_obj, mf30mt001_data_obj);
  mf30mt002_conv_obj.convert_frendy_to_endf_format(cov_general_data_obj, mf30mt002_data_obj);
  mf32mt151_conv_obj.convert_frendy_to_endf_format(cov_reso_data_obj,    mf32mt151_data_obj);

  //Set ZA and AWR
  mf30mt001_data_obj.set_mat_no(mat_no);
  mf30mt001_data_obj.set_ZA(mat_data);
  mf30mt001_data_obj.set_AWR(mass);

  if( mf30mt002_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf30mt002_data_obj.set_mat_no(mat_no);
    mf30mt002_data_obj.set_ZA(mat_data);
    mf30mt002_data_obj.set_AWR(mass);
  }

  if( mf32mt151_data_obj.get_mat_no() != unassigned_mat_no )
  {
    mf32mt151_data_obj.set_mat_no(mat_no);
    mf32mt151_data_obj.set_ZAR(mat_data);
    mf32mt151_data_obj.set_AWR(mass);
  }

  //Declare MFxxParser object
  vector<MF31Parser>  mf31_data_obj;
  vector<MF33Parser>  mf33_data_obj;
  vector<MF34Parser>  mf34_data_obj;
  vector<MF35Parser>  mf35_data_obj;
  vector<MF40Parser>  mf40_data_obj;
  mf31_data_obj.clear();
  mf33_data_obj.clear();
  mf34_data_obj.clear();
  mf35_data_obj.clear();
  mf40_data_obj.clear();

  //Convert NuclearDataObject to MFxxParser object
  int i_max = static_cast<int>(reaction_type.size());
  MF31Parser  mf31_data_tmp;
  MF33Parser  mf33_data_tmp;
  MF34Parser  mf34_data_tmp;
  MF35Parser  mf35_data_tmp;
  MF40Parser  mf40_data_tmp;
  for(int i=0; i<i_max; i++)
  {
    Integer mt_no = reaction_type[i];

    if( cov_fis_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      mf31_conv_obj.convert_frendy_to_endf_format(cov_fis_data_obj[i], mf31_data_tmp);
      if( mf31_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf31_data_tmp.set_mt_no(mt_no);
        mf31_data_tmp.set_mat_no(mat_no);
        mf31_data_tmp.set_ZA(mat_data);
        mf31_data_tmp.set_AWR(mass);
        mf31_data_obj.push_back(mf31_data_tmp);
      }
      mf31_data_tmp.clear();
    }

    if( cov_xs_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      mf33_conv_obj.convert_frendy_to_endf_format(cov_xs_data_obj[i], mf33_data_tmp);
      if( mf33_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf33_data_tmp.set_mt_no(mt_no);
        mf33_data_tmp.set_mat_no(mat_no);
        mf33_data_tmp.set_ZA(mat_data);
        mf33_data_tmp.set_AWR(mass);
        mf33_data_obj.push_back(mf33_data_tmp);
      }
      mf33_data_tmp.clear();
    }

    if( cov_ene_angular_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      mf34_conv_obj.convert_frendy_to_endf_format(cov_ene_angular_data_obj[i], mf34_data_tmp);
      if( mf34_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf34_data_tmp.set_mt_no(mt_no);
        mf34_data_tmp.set_mat_no(mat_no);
        mf34_data_tmp.set_ZA(mat_data);
        mf34_data_tmp.set_AWR(mass);
        mf34_data_obj.push_back(mf34_data_tmp);
      }
      mf34_data_tmp.clear();

      mf35_conv_obj.convert_frendy_to_endf_format(cov_ene_angular_data_obj[i], mf35_data_tmp);
      if( mf35_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf35_data_tmp.set_mt_no(mt_no);
        mf35_data_tmp.set_mat_no(mat_no);
        mf35_data_tmp.set_ZA(mat_data);
        mf35_data_tmp.set_AWR(mass);
        mf35_data_obj.push_back(mf35_data_tmp);
      }
      mf35_data_tmp.clear();
    }

    if( cov_radio_product_data_obj[i].get_reaction_type() != unassigned_mt_no )
    {
      mf40_conv_obj.convert_frendy_to_endf_format(cov_radio_product_data_obj[i], mf40_data_tmp);
      if( mf40_data_tmp.get_mt_no() != unassigned_mt_no )
      {
        mf40_data_tmp.set_mt_no(mt_no);
        mf40_data_tmp.set_mat_no(mat_no);
        mf40_data_tmp.set_ZA(mat_data);
        mf40_data_tmp.set_AWR(mass);
        mf40_data_obj.push_back(mf40_data_tmp);
      }
      mf40_data_tmp.clear();
    }
  }

  //Set MFxxMTyyyParser object to endf_obj
  endf_obj.set_mf30_mt001_data(mf30mt001_data_obj);
  endf_obj.set_mf30_mt002_data(mf30mt002_data_obj);
  endf_obj.set_mf32_mt151_data(mf32mt151_data_obj);

  //Set MFxxParser object to endf_obj
  endf_obj.set_mf31_data(mf31_data_obj);
  endf_obj.set_mf33_data(mf33_data_obj);
  endf_obj.set_mf34_data(mf34_data_obj);
  endf_obj.set_mf35_data(mf35_data_obj);
  endf_obj.set_mf40_data(mf40_data_obj);

  //Clear MFxxMTyyyParser object
  mf30mt001_data_obj.clear();
  mf30mt002_data_obj.clear();
  mf32mt151_data_obj.clear();

  //Clear MFxxParser object to endf_obj
  for(int i=0; i<static_cast<int>(mf31_data_obj.size()); i++)
  {
    mf31_data_obj[i].clear();
  }
  mf31_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf33_data_obj.size()); i++)
  {
    mf33_data_obj[i].clear();
  }
  mf33_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf34_data_obj.size()); i++)
  {
    mf34_data_obj[i].clear();
  }
  mf34_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf35_data_obj.size()); i++)
  {
    mf35_data_obj[i].clear();
  }
  mf35_data_obj.resize(0);

  for(int i=0; i<static_cast<int>(mf40_data_obj.size()); i++)
  {
    mf40_data_obj[i].clear();
  }
  mf40_data_obj.resize(0);

  //Clear each container class
  cov_general_data_obj.clear();
  cov_reso_data_obj.clear();

  cov_fis_data_obj.clear();
  cov_xs_data_obj.clear();
  cov_ene_angular_data_obj.clear();
  cov_radio_product_data_obj.clear();

  reaction_type.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Endf6ParserCov -> NuclearDataObject
void Endf6Converter::convert_endf_format_to_frendy(Endf6ParserCov& endf_obj, NuclearDataObject& frendy_obj)
{
  string func_name  = "convert_endf_format_to_frendy";
  func_name = func_name + "(Endf6ParserCov& endf_obj, NuclearDataObject& frendy_obj)";
  
  //Declare and get MFxxMTyyyParser object
  MF30MT001Parser  mf30mt001_data_obj = endf_obj.get_mf30_mt001_data();
  MF30MT002Parser  mf30mt002_data_obj = endf_obj.get_mf30_mt002_data();
  MF32MT151Parser  mf32mt151_data_obj = endf_obj.get_mf32_mt151_data();
  
  //Declare and get MFxxParser object
  vector<MF31Parser>  mf31_data_obj = endf_obj.get_mf31_data();
  vector<MF33Parser>  mf33_data_obj = endf_obj.get_mf33_data();
  vector<MF34Parser>  mf34_data_obj = endf_obj.get_mf34_data();
  vector<MF35Parser>  mf35_data_obj = endf_obj.get_mf35_data();
  vector<MF40Parser>  mf40_data_obj = endf_obj.get_mf40_data();
  
  //Declare each container object
  CovarianceGeneralDataContainer             cov_general_data_obj;
  CovarianceResonanceDataContainer           cov_reso_data_obj;
  
  CovarianceReactionDataContainer            cov_reaction_data_obj;
  CovarianceFissionDataContainer             cov_fis_data_obj;
  CovarianceCrossSectionDataContainer        cov_xs_data_obj;
  CovarianceEnergyAngularDataContainer       cov_ene_angular_data_obj;
  CovarianceRadioactiveProductDataContainer  cov_radio_product_data_obj;
  
  //Check mat_no, mat_data and mass
  Integer mat_no_base, mat_no;
  Real    mat_data_base, mat_data, mass_base, mass;
  
  mat_no_base   = mf30mt001_data_obj.get_mat_no();
  mat_data_base = mf30mt001_data_obj.get_ZA();
  mass_base     = mf30mt001_data_obj.get_AWR();
  
  mat_no   = mf30mt002_data_obj.get_mat_no();
  mat_data = mf30mt002_data_obj.get_ZA();
  mass     = mf30mt002_data_obj.get_AWR();
  check_mat_data(func_name,30,   2, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  mat_no   = mf32mt151_data_obj.get_mat_no();
  mat_data = mf32mt151_data_obj.get_ZAR();
  mass     = mf32mt151_data_obj.get_AWR();
  check_mat_data(func_name,32, 151, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);
  
  //Convert MFxxMTyyyParser object to NuclearDataObject
  cov_general_data_obj.clear();
  cov_reso_data_obj.clear();
  
  mf30mt001_conv_obj.convert_endf_format_to_frendy(mf30mt001_data_obj, cov_general_data_obj);
  mf30mt002_conv_obj.convert_endf_format_to_frendy(mf30mt002_data_obj, cov_general_data_obj);
  mf32mt151_conv_obj.convert_endf_format_to_frendy(mf32mt151_data_obj, cov_reso_data_obj);


  //Check mat_no, mat_data and mass and convert MFxxParser object to NuclearDataObject
  Integer mt_no;
  
  cov_reaction_data_obj.clear();
  cov_fis_data_obj.clear();
  cov_xs_data_obj.clear();
  cov_ene_angular_data_obj.clear();
  cov_radio_product_data_obj.clear();
  
  int i_max = static_cast<int>(mf31_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf31_data_obj[i].get_mt_no();
    mat_no   = mf31_data_obj[i].get_mat_no();
    mat_data = mf31_data_obj[i].get_ZA();
    mass     = mf31_data_obj[i].get_AWR();
    check_mat_data(func_name,31, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    cov_fis_data_obj = cov_reaction_data_obj.get_cov_fis_data_obj(mt_no);
    mf31_conv_obj.convert_endf_format_to_frendy(mf31_data_obj[i], cov_fis_data_obj);
    cov_reaction_data_obj.set_cov_fis_data_obj(mt_no, cov_fis_data_obj);
    
    mf31_data_obj[i].clear();
    cov_fis_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf33_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf33_data_obj[i].get_mt_no();
    mat_no   = mf33_data_obj[i].get_mat_no();
    mat_data = mf33_data_obj[i].get_ZA();
    mass     = mf33_data_obj[i].get_AWR();
    check_mat_data(func_name,33, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    cov_xs_data_obj = cov_reaction_data_obj.get_cov_xs_data_obj(mt_no);
    mf33_conv_obj.convert_endf_format_to_frendy(mf33_data_obj[i], cov_xs_data_obj);
    cov_reaction_data_obj.set_cov_xs_data_obj(mt_no, cov_xs_data_obj);
    
    mf33_data_obj[i].clear();
    cov_xs_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf34_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf34_data_obj[i].get_mt_no();
    mat_no   = mf34_data_obj[i].get_mat_no();
    mat_data = mf34_data_obj[i].get_ZA();
    mass     = mf34_data_obj[i].get_AWR();
    check_mat_data(func_name,34, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    cov_ene_angular_data_obj = cov_reaction_data_obj.get_cov_ene_angular_data_obj(mt_no);
    mf34_conv_obj.convert_endf_format_to_frendy(mf34_data_obj[i], cov_ene_angular_data_obj);
    cov_reaction_data_obj.set_cov_ene_angular_data_obj(mt_no, cov_ene_angular_data_obj);
    
    mf34_data_obj[i].clear();
    cov_ene_angular_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf35_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf35_data_obj[i].get_mt_no();
    mat_no   = mf35_data_obj[i].get_mat_no();
    mat_data = mf35_data_obj[i].get_ZA();
    mass     = mf35_data_obj[i].get_AWR();
    check_mat_data(func_name,35, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    cov_ene_angular_data_obj = cov_reaction_data_obj.get_cov_ene_angular_data_obj(mt_no);
    mf35_conv_obj.convert_endf_format_to_frendy(mf35_data_obj[i], cov_ene_angular_data_obj);
    cov_reaction_data_obj.set_cov_ene_angular_data_obj(mt_no, cov_ene_angular_data_obj);
    
    mf35_data_obj[i].clear();
    cov_ene_angular_data_obj.clear();
  }
  
  i_max = static_cast<int>(mf40_data_obj.size());
  for(int i=0; i<i_max; i++)
  {
    mt_no    = mf40_data_obj[i].get_mt_no();
    mat_no   = mf40_data_obj[i].get_mat_no();
    mat_data = mf40_data_obj[i].get_ZA();
    mass     = mf40_data_obj[i].get_AWR();
    check_mat_data(func_name,40, mt_no, mat_no, mat_no_base, mat_data, mat_data_base, mass, mass_base);

    cov_radio_product_data_obj = cov_reaction_data_obj.get_cov_radio_product_data_obj(mt_no);
    mf40_conv_obj.convert_endf_format_to_frendy(mf40_data_obj[i], cov_radio_product_data_obj);
    cov_reaction_data_obj.set_cov_radio_product_data_obj(mt_no, cov_radio_product_data_obj);
    
    mf40_data_obj[i].clear();
    cov_radio_product_data_obj.clear();
  }

  //Set mat_no, mat_data and mass
  cov_general_data_obj.set_mat_no( mat_no_base );
  cov_general_data_obj.set_mat_data( mat_data_base );
  cov_general_data_obj.set_mass( mass_base );
  
  
  //Set each data container to frendy_obj
  frendy_obj.set_cov_general_data_obj(cov_general_data_obj);
  frendy_obj.set_cov_reso_data_obj(cov_reso_data_obj);
  frendy_obj.set_cov_reaction_data_obj(cov_reaction_data_obj);

  //Clear MFxxMTyyyParser
  mf30mt001_data_obj.clear();
  mf30mt002_data_obj.clear();
  mf32mt151_data_obj.clear();

  //Clear MFxxParser
  mf31_data_obj.resize(0);
  mf33_data_obj.resize(0);
  mf34_data_obj.resize(0);
  mf35_data_obj.resize(0);
  mf40_data_obj.resize(0);
  
  //Clear each data container
  cov_general_data_obj.clear();
  cov_reso_data_obj.clear();
  cov_reaction_data_obj.clear();
  
  func_name.clear();
}

