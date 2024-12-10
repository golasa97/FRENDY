#include "../tools/frendy_parallel/FrendyParallelRunner.hpp"

using namespace frendy;

int main(int argc, char *argv[])
{
  ErrorManager err_obj;
  //err_obj.set_err_mes_opt(err_obj.err_mes_debug);
  err_obj.set_err_mes_opt(err_obj.err_mes_default);
  //err_obj.set_err_mes_opt(err_obj.err_mes_skip_warning);

  if( argc <= 1 )
  {
    NuclearDataProcessorCommonUtils frendy_common_obj;
    frendy_common_obj.output_frendy_start();

    string class_name = "main_frendy_parallel.cpp";
    string func_name  = "int main(int argc, char *argv[])";
    vector<string> err_com;
    err_com.push_back("The number of argument of this program is zero.");
    err_com.push_back("Please set input file name.");
    
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  string input_file_name = argv[1];

  FrendyParallelRunner frendy_parallel_obj;
  frendy_parallel_obj.run_frendy_parallel(input_file_name);

  return 0;
}

