#ifndef ENDF6_WRITER_H
#define ENDF6_WRITER_H

#include "EndfUtils/Endf6Parser/Endf6Parser.hpp"
#include "EndfUtils/Endf6Converter/Endf6Converter.hpp"

#include "EndfUtils/MFxxMTyyyWriter/MF01MT451Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF01MT452Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF01MT455Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF01MT456Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF01MT458Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF01MT460Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF02MT151Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF02MT152Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF02MT153Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF03Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF04Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF05Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF06Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF07MT002Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF07MT004Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF07MT451Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF08MT454Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF08MT457Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF08MT459Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF08Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF09Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF10Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF12Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF13Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF14Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF15Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF23Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF26Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF27Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF28Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF30MT001Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF30MT002Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF31Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF32MT151Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF33Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF34Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF35Writer.hpp"
#include "EndfUtils/MFxxMTyyyWriter/MF40Writer.hpp"

namespace frendy
{
  class Endf6Writer
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::Endf6Parser      endf_parser;
      frendy::EndfFileWriter   efw_obj;

      string          pendf_label;
      string          dummy_label;
      vector<string>  add_comment;
      vector<Integer> line_no, mf_list, mt_list;

      Integer mat_no;

      frendy::MF01MT451Parser    mf01mt451_par, mf01mt451_par_mod;
      frendy::MF01MT452Parser    mf01mt452_par;
      frendy::MF01MT455Parser    mf01mt455_par;
      frendy::MF01MT456Parser    mf01mt456_par;
      frendy::MF01MT458Parser    mf01mt458_par;
      frendy::MF01MT460Parser    mf01mt460_par;
      frendy::MF02MT151Parser    mf02mt151_par;
      frendy::MF02MT152Parser    mf02mt152_par;
      frendy::MF02MT153Parser    mf02mt153_par;
      frendy::MF07MT002Parser    mf07mt002_par;
      frendy::MF07MT004Parser    mf07mt004_par;
      frendy::MF07MT451Parser    mf07mt451_par;
      frendy::MF08MT454Parser    mf08mt454_par;
      frendy::MF08MT457Parser    mf08mt457_par;
      frendy::MF08MT459Parser    mf08mt459_par;
      frendy::MF30MT001Parser    mf30mt001_par;
      frendy::MF30MT002Parser    mf30mt002_par;
      frendy::MF32MT151Parser    mf32mt151_par;
      vector<frendy::MF03Parser> mf03_par;
      vector<frendy::MF04Parser> mf04_par;
      vector<frendy::MF05Parser> mf05_par;
      vector<frendy::MF06Parser> mf06_par;
      vector<frendy::MF08Parser> mf08_par;
      vector<frendy::MF09Parser> mf09_par;
      vector<frendy::MF10Parser> mf10_par;
      vector<frendy::MF12Parser> mf12_par;
      vector<frendy::MF13Parser> mf13_par;
      vector<frendy::MF14Parser> mf14_par;
      vector<frendy::MF15Parser> mf15_par;
      vector<frendy::MF23Parser> mf23_par;
      vector<frendy::MF26Parser> mf26_par;
      vector<frendy::MF27Parser> mf27_par;
      vector<frendy::MF28Parser> mf28_par;
      vector<frendy::MF31Parser> mf31_par;
      vector<frendy::MF33Parser> mf33_par;
      vector<frendy::MF34Parser> mf34_par;
      vector<frendy::MF35Parser> mf35_par;
      vector<frendy::MF40Parser> mf40_par;

      Integer modify_endf_flg, endf_parser_flg,
              pendf_label_flg, add_comment_flg, clear_comment_flg;

      frendy::MF01MT451Writer    mf01mt451_wri;
      frendy::MF01MT452Writer    mf01mt452_wri;
      frendy::MF01MT455Writer    mf01mt455_wri;
      frendy::MF01MT456Writer    mf01mt456_wri;
      frendy::MF01MT458Writer    mf01mt458_wri;
      frendy::MF01MT460Writer    mf01mt460_wri;
      frendy::MF02MT151Writer    mf02mt151_wri;
      frendy::MF02MT152Writer    mf02mt152_wri;
      frendy::MF02MT153Writer    mf02mt153_wri;
      frendy::MF07MT002Writer    mf07mt002_wri;
      frendy::MF07MT004Writer    mf07mt004_wri;
      frendy::MF07MT451Writer    mf07mt451_wri;
      frendy::MF08MT454Writer    mf08mt454_wri;
      frendy::MF08MT457Writer    mf08mt457_wri;
      frendy::MF08MT459Writer    mf08mt459_wri;
      frendy::MF30MT001Writer    mf30mt001_wri;
      frendy::MF30MT002Writer    mf30mt002_wri;
      frendy::MF32MT151Writer    mf32mt151_wri;
      frendy::MF03Writer         mf03_wri;
      frendy::MF04Writer         mf04_wri;
      frendy::MF05Writer         mf05_wri;
      frendy::MF06Writer         mf06_wri;
      frendy::MF08Writer         mf08_wri;
      frendy::MF09Writer         mf09_wri;
      frendy::MF10Writer         mf10_wri;
      frendy::MF12Writer         mf12_wri;
      frendy::MF13Writer         mf13_wri;
      frendy::MF14Writer         mf14_wri;
      frendy::MF15Writer         mf15_wri;
      frendy::MF23Writer         mf23_wri;
      frendy::MF26Writer         mf26_wri;
      frendy::MF27Writer         mf27_wri;
      frendy::MF28Writer         mf28_wri;
      frendy::MF31Writer         mf31_wri;
      frendy::MF33Writer         mf33_wri;
      frendy::MF34Writer         mf34_wri;
      frendy::MF35Writer         mf35_wri;
      frendy::MF40Writer         mf40_wri;


#ifdef DEBUG_MODE
  public:
#endif

      void convert_pendf_data(vector<string>& text);
      void add_text_data(vector<string>& text, vector<string>& text_add);
      void add_file_end(vector<string>& text, Integer mf_no, Integer mt_no);
      
      void write_mf01mt451(vector<string>& text);
      void add_mf_mt_mf01mt451();
      void clear_comment_mf01mt451();
      void add_comment_mf01mt451();
      void modify_mf01mt451();

      void combine_all_text(vector<string>& text);
      void add_end_of_file(vector<string>& text);
      
      void check_set_data();
      void check_material_number();

      void set_modified_parser_data();
      
    public:
      //constructor
      Endf6Writer(void);

      //destructor
      virtual ~Endf6Writer(void);

      static const int no_clear_comment_data = 0;
      static const int clear_comment_data    = 1;

      void clear();
      void clear_parser_data();
      void clear_parser_data_no_cov();

      void write_pendf(string file_name);
      void write_pendf_with_tape_end(string file_name);
      
      void set_endf6_parser(frendy::Endf6Parser parser_obj);
      void set_endf6_parser_no_cov(frendy::Endf6ParserNoCov parser_obj);
      void set_nucl_data_obj(frendy::NuclearDataObject data_obj);
      
      void set_pendf_label(string str_data);
      void set_additional_comment(vector<string> str_data);
      void set_clear_comment_flg(int flg_data);

      vector<string>           get_endf_text_data();
      vector<string>           get_endf_text_data_without_label();
      frendy::Endf6Parser      get_endf6_parser();
      frendy::Endf6ParserNoCov get_endf6_parser_no_cov();
      frendy::Endf6ParserCov   get_endf6_parser_cov();
      
      string         get_pendf_label();
      vector<string> get_additional_comment();
  };
}

#endif //ENDF6_WRITER_H
