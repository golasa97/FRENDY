#include "EndfUtils/MFxxMTyyyWriter/MF02MT153Writer.hpp"

using namespace frendy;

//constructor
MF02MT153Writer::MF02MT153Writer(void)
{
  clear();
}

//destructor
MF02MT153Writer::~MF02MT153Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT153Writer::write_endf() 
{
  clr_obj.clear_vec_array1_str(text);

  string         line_data;
  vector<string> str_vec;
  efw_obj.set_mat_mf_mt(par_obj.get_mat_no(), mf_no, mt_no);

  //Line No.01
  //ZA, AWR, and NR
  line_data = efw_obj.write_cont(par_obj.get_ZAR(), par_obj.get_AWR(), 
                par_obj.get_INEL(), par_obj.get_ABSO(), par_obj.get_INT(), par_obj.get_NBIN());
  text.push_back(line_data);


  //Line No.02
  vector<Real> real_vec;
  real_vec.clear();

  int ene_max = static_cast<int>(par_obj.get_NUNR());
  int bin_max = static_cast<int>(par_obj.get_NBIN());
  int ele_max = ene_max * (1 + 6*bin_max);
  if( ene_max > 0 )
  {
    vector<Real>                   ene_vec     = par_obj.get_ENE();
    vector<vector<Real> >          heat_vec    = par_obj.get_HEAT();
    vector<vector<Real> >          p_count_vec = par_obj.get_P_COUNT();
    vector<vector<vector<Real> > > p_table_vec = par_obj.get_P_TABLE();
    if( ene_max    != static_cast<int>(ene_vec.size())  || 
        bin_max    != static_cast<int>(heat_vec[0].size()) ||
        xs_type_no != static_cast<int>(p_table_vec[0].size()) )
    {
      string class_name = "MF02MT153Writer";
      string func_name  = "write_endf()";
  
      ostringstream oss01, oss02, oss03, oss04, oss05, oss06;
      oss01 << ene_max;
      oss02 << ene_vec.size();
      oss03 << bin_max;
      oss04 << heat_vec.size();
      oss05 << xs_type_no;
      oss06 << p_table_vec.size();
      string str_data01 = "NUNR                   : " + oss01.str();
      string str_data02 = "Element No. of ENE     : " + oss02.str();
      string str_data03 = "NBIN                   : " + oss03.str();
      string str_data04 = "Element No. of HEAT    : " + oss04.str();
      string str_data05 = "XS type No.            : " + oss05.str();
      string str_data06 = "Element No. of P_TABLE : " + oss06.str();

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back(str_data03);
      err_com.push_back(str_data04);
      err_com.push_back(str_data05);
      err_com.push_back(str_data06);
      err_com.push_back("The number of element data is not identical.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }

    int ele_no = 0;
    real_vec.resize(ele_max); 
    for(int i=0; i<ene_max; i++)
    {
      real_vec[ele_no] = ene_vec[i];
      ele_no++;

      for(int j=0; j<bin_max; j++)
      {
        real_vec[ele_no] = p_count_vec[i][j];
        ele_no++;
      }

      for(int j=0; j<xs_type_no; j++)
      {
        for(int k=0; k<bin_max; k++)
        {
          real_vec[ele_no] = p_table_vec[i][j][k];
          ele_no++;
        }
      }

      for(int j=0; j<bin_max; j++)
      {
        real_vec[ele_no] = heat_vec[i][j];
        ele_no++;
      }

      //Check the order of total probability table
      for(int k=1; k<bin_max; k++)
      {
        if( p_table_vec[i][total_xs][k] - p_table_vec[i][total_xs][k-1] < 0.0 )
        {
          string class_name = "MF02MT153Writer";
          string func_name  = "write_endf()";

          ostringstream oss01, oss02, oss03, oss04, oss05, oss06, oss07, oss08;
          oss03.precision(8);
          oss06.precision(8);
          oss07.precision(8);
          oss03.setf(ios::showpoint);
          oss06.setf(ios::showpoint);
          oss07.setf(ios::showpoint);
          oss03.setf(ios::scientific);
          oss06.setf(ios::scientific);
          oss07.setf(ios::scientific);
          oss01 << i+1;
          oss02 << ene_max;
          oss03 << ene_vec[i];
          oss04 << k+1;
          oss05 << bin_max;
          oss06 << p_table_vec[i][total_xs][k-1];
          oss07 << p_table_vec[i][total_xs][k];
          string str_data01 = "Position of energy           : " + oss01.str() + " / " + oss02.str();
          string str_data02 = "Energy [eV]                  : " + oss03.str();
          string str_data03 = "Position of probability bin  : " + oss04.str() + " / " + oss05.str();
          string str_data04 = "Probability table (total)    : " + oss06.str() + " - " + oss07.str();
          string str_data05 = "                                (p_table_tot[i] - p_table_tot[i-1])";

          vector<string> err_com;
          err_com.push_back(str_data01);
          err_com.push_back(str_data02);
          err_com.push_back(str_data03);
          err_com.push_back(str_data04);
          err_com.push_back(str_data05);
          err_com.push_back("The order of the total probability table must be ascending order.");
          err_com.push_back("However, this probability table is not ascending order.");
          err_com.push_back("This probability table may be incorrect.");
          err_com.push_back("");
          err_com.push_back("  Order of total probability table");
          for(int l=0; l<bin_max; l++)
          {
            ostringstream oss11;
            oss11.precision(8);
            oss11.setf(ios::showpoint);
            oss11.setf(ios::scientific);
            oss11 << p_table_vec[i][total_xs][l];
            string str_data11 = "    " + oss11.str();
            if( l == k )
            {
              str_data11 = str_data11 + " ***";
            }
            err_com.push_back(str_data11);
          }

          //Modify total probability table
          if( p_count_vec[i][k] - p_count_vec[i][k-1] < min_value )
          {
            err_com.push_back("");
            err_com.push_back("The probability table at this energy grid is modified.");
            err_com.push_back("(p_table_tot[i] = p_table_tot[i-1])");
            for(int j=0; j<xs_type_no; j++)
            {
              p_table_vec[i][j][k] = p_table_vec[i][j][k-1];
            }
          }

          err_obj.output_caution(class_name, func_name, err_com);
        }
      }
    }

    ene_vec.clear();
    clr_obj.clear_vec_array2_real(heat_vec);
    clr_obj.clear_vec_array2_real(p_count_vec);
    clr_obj.clear_vec_array3_real(p_table_vec);
  }

  str_vec = efw_obj.write_list(par_obj.get_TEMP(), 0.0, par_obj.get_LSSF(), par_obj.get_ICOMP(),
                               ele_max, par_obj.get_NUNR(), real_vec);
  int i_max = static_cast<int>(str_vec.size());
  for(int i=0; i<i_max; i++)
  {
    text.push_back(str_vec[i]);
  }

  line_data = efw_obj.write_mt_end();
  text.push_back(line_data);

  line_data.clear();
  clr_obj.clear_vec_array1_str(str_vec);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void MF02MT153Writer::clear()
{
  clr_obj.clear_vec_array1_str(text);

  par_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> MF02MT153Writer::get_endf_text_data(MF02MT153Parser& mf02mt153parser_obj)
{
  clear();
  par_obj = mf02mt153parser_obj;

  write_endf();
  return text;
}

