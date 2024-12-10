#ifndef NUCLEAR_DATA_PROCESSOR_COMMON_UTILS_H
#define NUCLEAR_DATA_PROCESSOR_COMMON_UTILS_H

#include <boost/timer/timer.hpp>

#include "CommonUtils/FileCommentRemover.hpp"
#include "CommonUtils/TimeUtils.hpp"
#include "NjoyUtils/ModerInputReader.hpp"
#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/OtherUtils/EndfTapeDivider.hpp"

namespace frendy
{
  class NuclearDataProcessorCommonUtils
  {
    private:
      frendy::ErrorManager       err_obj;
      frendy::TimeUtils          time_obj;
      frendy::FileCommentRemover file_obj;

  public:
      //constructor
      NuclearDataProcessorCommonUtils(void);

      //destructor
      virtual ~NuclearDataProcessorCommonUtils(void);

      void output_frendy_start();
      void output_frendy_end(string input_name);

      void output_frendy_input_file_information(string input_file_name);
      void output_frendy_input_file_information_without_comment(string input_file_name);

      void change_pendf_name(string input_file_name);
      void change_pendf_name(string input_file_name, int line_no);
  };
}

#endif // NUCLEAR_DATA_PROCESSOR_COMMON_UTILS_H
