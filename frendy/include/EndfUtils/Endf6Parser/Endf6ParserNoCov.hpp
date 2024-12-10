#ifndef ENDF6_PARSER_NO_COV_H
#define ENDF6_PARSER_NO_COV_H

#include <boost/timer/timer.hpp>

#include "EndfUtils/EndfFileReader/EndfFileReader.hpp"

#include "EndfUtils/MFxxMTyyyParser/MF01MT451Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF01MT452Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF01MT455Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF01MT456Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF01MT458Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF01MT460Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF02MT151Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF02MT152Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF02MT153Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF07MT002Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF07MT004Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF07MT451Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF08MT454Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF08MT457Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF08MT459Parser.hpp"

#include "EndfUtils/MFxxMTyyyParser/MF03Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF04Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF05Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF06Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF08Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF09Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF10Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF12Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF13Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF14Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF15Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF23Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF26Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF27Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF28Parser.hpp"

namespace frendy
{
  class Endf6ParserNoCov
  {
    private:
      frendy::VectorClearer    clr_obj;
      frendy::ErrorManager     err_obj;
      frendy::EndfFileReader   efr_obj;

      string                   name;
      vector<Integer>          parser_list;
      vector<vector<Integer> > mt_list;

      Real                     time_total;
      vector<vector<Real> >    time_each;

      frendy::MF01MT451Parser  mf01_mt451_data;
      frendy::MF01MT452Parser  mf01_mt452_data;
      frendy::MF01MT455Parser  mf01_mt455_data;
      frendy::MF01MT456Parser  mf01_mt456_data;
      frendy::MF01MT458Parser  mf01_mt458_data;
      frendy::MF01MT460Parser  mf01_mt460_data;
      frendy::MF02MT151Parser  mf02_mt151_data;
      frendy::MF02MT152Parser  mf02_mt152_data;
      frendy::MF02MT153Parser  mf02_mt153_data;
      frendy::MF07MT002Parser  mf07_mt002_data;
      frendy::MF07MT004Parser  mf07_mt004_data;
      frendy::MF07MT451Parser  mf07_mt451_data;
      frendy::MF08MT454Parser  mf08_mt454_data;
      frendy::MF08MT457Parser  mf08_mt457_data;
      frendy::MF08MT459Parser  mf08_mt459_data;

      vector<frendy::MF03Parser> mf03_data;
      vector<frendy::MF04Parser> mf04_data;
      vector<frendy::MF05Parser> mf05_data;
      vector<frendy::MF06Parser> mf06_data;
      vector<frendy::MF08Parser> mf08_data;
      vector<frendy::MF09Parser> mf09_data;
      vector<frendy::MF10Parser> mf10_data;
      vector<frendy::MF12Parser> mf12_data;
      vector<frendy::MF13Parser> mf13_data;
      vector<frendy::MF14Parser> mf14_data;
      vector<frendy::MF15Parser> mf15_data;
      vector<frendy::MF23Parser> mf23_data;
      vector<frendy::MF26Parser> mf26_data;
      vector<frendy::MF27Parser> mf27_data;
      vector<frendy::MF28Parser> mf28_data;

      void mod_list();

      void read_endf();
      void parse_data(Integer mf_no, Integer mt_no, vector<Real>& time_each_mf);

      void parse_mf01(Integer mf_no, Integer mt_no);
      void parse_mf02(Integer mf_no, Integer mt_no);
      void parse_mf03(Integer mf_no, Integer mt_no);
      void parse_mf04(Integer mf_no, Integer mt_no);
      void parse_mf05(Integer mf_no, Integer mt_no);
      void parse_mf06(Integer mf_no, Integer mt_no);
      void parse_mf07(Integer mf_no, Integer mt_no);
      void parse_mf08(Integer mf_no, Integer mt_no);
      void parse_mf09(Integer mf_no, Integer mt_no);
      void parse_mf10(Integer mf_no, Integer mt_no);
      void parse_mf12(Integer mf_no, Integer mt_no);
      void parse_mf13(Integer mf_no, Integer mt_no);
      void parse_mf14(Integer mf_no, Integer mt_no);
      void parse_mf15(Integer mf_no, Integer mt_no);
      void parse_mf23(Integer mf_no, Integer mt_no);
      void parse_mf26(Integer mf_no, Integer mt_no);
      void parse_mf27(Integer mf_no, Integer mt_no);
      void parse_mf28(Integer mf_no, Integer mt_no);

      void set_parser_list();

    public:
      //constructor
      Endf6ParserNoCov(void);

      //destructor
      virtual ~Endf6ParserNoCov(void);

      void clear();

      void set_file_name(string file_name);
      void set_endf_file_reader(frendy::EndfFileReader& obj);
      void set_text(vector<string>& text_data);

      string                   get_file_name();
      vector<Integer>          get_parser_list();
      vector<vector<Integer> > get_mt_list();
      Real                     get_time_total();
      vector<vector<Real> >    get_time_each();

      //Getter for each parser
      frendy::MF01MT451Parser get_mf01_mt451_data();
      frendy::MF01MT452Parser get_mf01_mt452_data();
      frendy::MF01MT455Parser get_mf01_mt455_data();
      frendy::MF01MT456Parser get_mf01_mt456_data();
      frendy::MF01MT458Parser get_mf01_mt458_data();
      frendy::MF01MT460Parser get_mf01_mt460_data();
      frendy::MF02MT151Parser get_mf02_mt151_data();
      frendy::MF02MT152Parser get_mf02_mt152_data();
      frendy::MF02MT153Parser get_mf02_mt153_data();
      frendy::MF07MT002Parser get_mf07_mt002_data();
      frendy::MF07MT004Parser get_mf07_mt004_data();
      frendy::MF07MT451Parser get_mf07_mt451_data();
      frendy::MF08MT454Parser get_mf08_mt454_data();
      frendy::MF08MT457Parser get_mf08_mt457_data();
      frendy::MF08MT459Parser get_mf08_mt459_data();

      vector<frendy::MF03Parser> get_mf03_data();
      vector<frendy::MF04Parser> get_mf04_data();
      vector<frendy::MF05Parser> get_mf05_data();
      vector<frendy::MF06Parser> get_mf06_data();
      vector<frendy::MF08Parser> get_mf08_data();
      vector<frendy::MF09Parser> get_mf09_data();
      vector<frendy::MF10Parser> get_mf10_data();
      vector<frendy::MF12Parser> get_mf12_data();
      vector<frendy::MF13Parser> get_mf13_data();
      vector<frendy::MF14Parser> get_mf14_data();
      vector<frendy::MF15Parser> get_mf15_data();
      vector<frendy::MF23Parser> get_mf23_data();
      vector<frendy::MF26Parser> get_mf26_data();
      vector<frendy::MF27Parser> get_mf27_data();
      vector<frendy::MF28Parser> get_mf28_data();


      //Setter for each parser
      void set_mf01_mt451_data(frendy::MF01MT451Parser parser_obj);
      void set_mf01_mt452_data(frendy::MF01MT452Parser parser_obj);
      void set_mf01_mt455_data(frendy::MF01MT455Parser parser_obj);
      void set_mf01_mt456_data(frendy::MF01MT456Parser parser_obj);
      void set_mf01_mt458_data(frendy::MF01MT458Parser parser_obj);
      void set_mf01_mt460_data(frendy::MF01MT460Parser parser_obj);
      void set_mf02_mt151_data(frendy::MF02MT151Parser parser_obj);
      void set_mf02_mt152_data(frendy::MF02MT152Parser parser_obj);
      void set_mf02_mt153_data(frendy::MF02MT153Parser parser_obj);
      void set_mf07_mt002_data(frendy::MF07MT002Parser parser_obj);
      void set_mf07_mt004_data(frendy::MF07MT004Parser parser_obj);
      void set_mf07_mt451_data(frendy::MF07MT451Parser parser_obj);
      void set_mf08_mt454_data(frendy::MF08MT454Parser parser_obj);
      void set_mf08_mt457_data(frendy::MF08MT457Parser parser_obj);
      void set_mf08_mt459_data(frendy::MF08MT459Parser parser_obj);

      void set_mf03_data(vector<frendy::MF03Parser> parser_obj);
      void set_mf04_data(vector<frendy::MF04Parser> parser_obj);
      void set_mf05_data(vector<frendy::MF05Parser> parser_obj);
      void set_mf06_data(vector<frendy::MF06Parser> parser_obj);
      void set_mf08_data(vector<frendy::MF08Parser> parser_obj);
      void set_mf09_data(vector<frendy::MF09Parser> parser_obj);
      void set_mf10_data(vector<frendy::MF10Parser> parser_obj);
      void set_mf12_data(vector<frendy::MF12Parser> parser_obj);
      void set_mf13_data(vector<frendy::MF13Parser> parser_obj);
      void set_mf14_data(vector<frendy::MF14Parser> parser_obj);
      void set_mf15_data(vector<frendy::MF15Parser> parser_obj);
      void set_mf23_data(vector<frendy::MF23Parser> parser_obj);
      void set_mf26_data(vector<frendy::MF26Parser> parser_obj);
      void set_mf27_data(vector<frendy::MF27Parser> parser_obj);
      void set_mf28_data(vector<frendy::MF28Parser> parser_obj);
  };
}

#endif // ENDF6_PARSER_NO_COV_H
