#ifndef GENDF_WRITER_H
#define GENDF_WRITER_H

#include "EndfUtils/GendfParser/GendfParser.hpp"
#include "EndfUtils/GendfWriter/GMFxxWriterBase.hpp"
#include "EndfUtils/GendfWriter/GMF01MT451Writer.hpp"
#include "EndfUtils/GendfWriter/GMF03Writer.hpp"
#include "EndfUtils/GendfWriter/GMF05Writer.hpp"
#include "EndfUtils/GendfWriter/GMF06Writer.hpp"
#include "EndfUtils/GendfWriter/GMF13Writer.hpp"
#include "EndfUtils/GendfWriter/GMF16Writer.hpp"

namespace frendy
{
  class GendfWriter
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::GendfParser      gendf_parser;
      frendy::EndfFileWriter   efw_obj;

      string          gendf_label;
      string          dummy_label;
      vector<Integer> line_no, mf_list, mt_list;

      Integer mat_no;

      frendy::GMF01MT451Parser    mf01mt451_par;
      vector<frendy::GMF03Parser> mf03_par;
      vector<frendy::GMF05Parser> mf05_par;
      vector<frendy::GMF06Parser> mf06_par;
      vector<frendy::GMF13Parser> mf13_par;
      vector<frendy::GMF16Parser> mf16_par;

      Integer gendf_parser_flg, gendf_label_flg;

      frendy::GMF01MT451Writer    mf01mt451_wri;
      frendy::GMF03Writer         mf03_wri;
      frendy::GMF05Writer         mf05_wri;
      frendy::GMF06Writer         mf06_wri;
      frendy::GMF13Writer         mf13_wri;
      frendy::GMF16Writer         mf16_wri;

#ifdef DEBUG_MODE
  public:
#endif

      void convert_gendf_data(vector<string>& text);
      void add_text_data(vector<string>& text, vector<string>& text_add);

      void add_file_end(vector<string>& text, Integer mf_no, Integer mt_no);
      void add_end_of_file(vector<string>& text);
      
      void check_set_data();
      void check_material_number();
      
    public:
      //constructor
      GendfWriter(void);

      //destructor
      virtual ~GendfWriter(void);

      void clear();
      void clear_parser_data();

      void write_gendf(string file_name);
      void write_gendf_with_tape_end(string file_name);
      
      void set_gendf_parser(frendy::GendfParser parser_obj);
      
      void set_gendf_label(string str_data);

      vector<string>      get_gendf_text_data();
      vector<string>      get_gendf_text_data_without_label();
      frendy::GendfParser get_gendf_parser();
      
      string              get_gendf_label();
  };
}

#endif //GENDF_WRITER_H
