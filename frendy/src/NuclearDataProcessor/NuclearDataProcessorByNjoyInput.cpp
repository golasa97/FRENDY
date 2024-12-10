#include "NuclearDataProcessor/NuclearDataProcessorByNjoyInput.hpp"

using namespace frendy;

//constructor
NuclearDataProcessorByNjoyInput::NuclearDataProcessorByNjoyInput(void)
{
  clear();
}

//destructor
NuclearDataProcessorByNjoyInput::~NuclearDataProcessorByNjoyInput(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByNjoyInput::clear()
{
  recon_obj.clear();
  dop_obj.clear();
  prob_obj.clear();
  gas_xs_obj.clear();
  ace_gen_obj.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByNjoyInput::process_nucl_data(string input_file_name)
{
  common_obj.output_frendy_start();
  common_obj.output_frendy_input_file_information(input_file_name);

  process_nucl_data_without_title_output(input_file_name);

  common_obj.output_frendy_end(input_file_name);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void NuclearDataProcessorByNjoyInput::process_nucl_data_without_title_output(string input_file_name)
{
  vector<vector<int> > njoy_input_list = njoy_inp_obj.get_njoy_input_list(input_file_name);

  int i_max = static_cast<int>(njoy_input_list.size());

  vector<int> groupr_flg, matxsr_flg;
  groupr_flg.resize(i_max);
  matxsr_flg.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    groupr_flg[i] = 0;
    matxsr_flg[i] = 0;

    if( njoy_input_list[i][0] == static_cast<int>(njoy_inp_obj.pos_groupr) )
    {
      GrouprInputReader groupr_obj;
      groupr_obj.read_input(input_file_name, njoy_input_list[i][1]);
      groupr_flg[i] = njoy_inp_obj.get_file_no(groupr_obj.get_gendf_file_name_out());
      groupr_obj.clear();
    }
    else if( njoy_input_list[i][0] == static_cast<int>(njoy_inp_obj.pos_matxsr) )
    {
      MatxsrInputReader matxsr_obj;
      matxsr_obj.read_input(input_file_name, njoy_input_list[i][1]);
      matxsr_flg[i] = njoy_inp_obj.get_file_no(matxsr_obj.get_group_file_name());
      matxsr_obj.clear();
    }
  }

  for(int i=0; i<i_max; i++)
  {
    int line_no =  njoy_input_list[i][1];
    if( njoy_input_list[i][0] == static_cast<int>(njoy_inp_obj.pos_reconr) )
    {
      recon_obj.set_njoy_input_file_name(input_file_name, line_no);
      recon_obj.write_pendf_file();
      recon_obj.clear();
    }
    else if( njoy_input_list[i][0] == static_cast<int>(njoy_inp_obj.pos_broadr) )
    {
      dop_obj.set_njoy_input_file_name(input_file_name, line_no);
      dop_obj.write_pendf_file();
      dop_obj.clear();
    }
    else if( njoy_input_list[i][0] == static_cast<int>(njoy_inp_obj.pos_thermr) )
    {
      sab_obj.set_njoy_input_file_name(input_file_name, line_no);
      sab_obj.write_pendf_file();
      sab_obj.clear();
    }
    else if( njoy_input_list[i][0] == static_cast<int>(njoy_inp_obj.pos_purr) )
    {
      prob_obj.set_njoy_input_file_name(input_file_name, line_no);
      prob_obj.write_pendf_file();
      prob_obj.clear();
    }
    else if( njoy_input_list[i][0] == static_cast<int>(njoy_inp_obj.pos_unresr) )
    {
      prob_obj.set_read_inp_mode(prob_obj.unresr_mode);
      prob_obj.set_njoy_input_file_name(input_file_name, line_no);
      prob_obj.write_pendf_file();
      prob_obj.clear();
    }
    else if( njoy_input_list[i][0] == static_cast<int>(njoy_inp_obj.pos_gaspr) )
    {
      gas_xs_obj.set_njoy_input_file_name(input_file_name, line_no);
      gas_xs_obj.write_pendf_file();
      gas_xs_obj.clear();
    }
    else if( njoy_input_list[i][0] == static_cast<int>(njoy_inp_obj.pos_acer) )
    {
      ace_gen_obj.set_njoy_input_file_name(input_file_name, line_no);
      ace_gen_obj.generate_ace_data();
      ace_gen_obj.clear();
    }
    else if( njoy_input_list[i][0] == static_cast<int>(njoy_inp_obj.pos_moder) )
    {
      common_obj.change_pendf_name(input_file_name, line_no);
    }
    else if( njoy_input_list[i][0] == static_cast<int>(njoy_inp_obj.pos_groupr) )
    {
      vector<int> matxs_line_no;
      matxs_line_no.clear();
      for(int j=i+1; j<i_max; j++)
      {
        if( groupr_flg[i] == matxsr_flg[j] )
        {
          matxs_line_no.push_back(njoy_input_list[j][1]);
        }
      }

      mg_gen_obj.set_njoy_input_file_name(input_file_name, line_no, matxs_line_no);
      mg_gen_obj.generate_mg_data();
      mg_gen_obj.clear();
    }
    else if( njoy_input_list[i][0] == static_cast<int>(njoy_inp_obj.pos_matxsr) )
    {
      int run_matxsr_flg = 0;
      for(int j=0; j<i; j++)
      {
        if( matxsr_flg[i] == groupr_flg[j] )
        {
          run_matxsr_flg = 1;
          break;
        }
      }

      if( run_matxsr_flg == 0 )
      {
        string class_name = "NuclearDataProcessorByNjoyInput";
        string func_name  = "process_nucl_data(string input_file_name)";
        string str_data01 = "Input file name : " + input_file_name;
        string str_data02 = "Input case      : " + njoy_inp_obj.get_func_name_list()[njoy_input_list[i][0]];

        ostringstream oss;
        oss << line_no;
        string str_data03 = "Line number     : " + oss.str();

        vector<string> err_com;
        err_com.push_back(str_data01);
        err_com.push_back(str_data02);
        err_com.push_back(str_data03);
        err_com.push_back("This program needs input file of groupr module to generate matxs format");
        err_com.push_back("before tha input file of matxsr module.");
        err_com.push_back("This input case is skipped.");
        err_obj.output_caution(class_name, func_name, err_com);
      }
    }
    else
    {
      string class_name = "NuclearDataProcessorByNjoyInput";
      string func_name  = "process_nucl_data(string input_file_name)";
      string str_data01 = "Input file name : " + input_file_name;
      string str_data02 = "Input case      : " + njoy_inp_obj.get_func_name_list()[njoy_input_list[i][0]];

      vector<string> err_com;
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("This input case is not implemented in FRENDY.");
      err_com.push_back("This input case is skipped.");
      err_obj.output_caution(class_name, func_name, err_com);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

