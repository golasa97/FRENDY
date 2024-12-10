#ifndef ENDF6_PARSER_COV_H
#define ENDF6_PARSER_COV_H

#include <boost/timer/timer.hpp>

#include "EndfUtils/EndfFileReader/EndfFileReader.hpp"

#include "EndfUtils/MFxxMTyyyParser/MF30MT001Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF30MT002Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF32MT151Parser.hpp"

#include "EndfUtils/MFxxMTyyyParser/MF31Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF33Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF34Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF35Parser.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF40Parser.hpp"

namespace frendy
{
  class Endf6ParserCov
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

      frendy::MF30MT001Parser    mf30_mt001_data;
      frendy::MF30MT002Parser    mf30_mt002_data;
      frendy::MF32MT151Parser    mf32_mt151_data;

      vector<frendy::MF31Parser> mf31_data;
      vector<frendy::MF33Parser> mf33_data;
      vector<frendy::MF34Parser> mf34_data;
      vector<frendy::MF35Parser> mf35_data;
      vector<frendy::MF40Parser> mf40_data;

      void mod_list();

      void read_endf();
      void parse_data(Integer mf_no, Integer mt_no, vector<Real>& time_each_mf);

      void parse_mf30(Integer mf_no, Integer mt_no);
      void parse_mf31(Integer mf_no, Integer mt_no);
      void parse_mf32(Integer mf_no, Integer mt_no);
      void parse_mf33(Integer mf_no, Integer mt_no);
      void parse_mf34(Integer mf_no, Integer mt_no);
      void parse_mf35(Integer mf_no, Integer mt_no);
      void parse_mf40(Integer mf_no, Integer mt_no);

      void set_parser_list();

    public:
      //constructor
      Endf6ParserCov(void);

      //destructor
      virtual ~Endf6ParserCov(void);

      void clear();

      void set_file_name(string file_name);
      void set_endf_file_reader(frendy::EndfFileReader& obj);
      void set_text(vector<string>& text_data);

      string                   get_file_name();
      vector<Integer>          get_parser_list();
      vector<vector<Integer> > get_mt_list();
      Real                     get_time_total();
      vector<vector<Real> >    get_time_each();

      //Getter
      frendy::MF30MT001Parser    get_mf30_mt001_data();
      frendy::MF30MT002Parser    get_mf30_mt002_data();
      frendy::MF32MT151Parser    get_mf32_mt151_data();

      vector<frendy::MF31Parser> get_mf31_data();
      vector<frendy::MF33Parser> get_mf33_data();
      vector<frendy::MF34Parser> get_mf34_data();
      vector<frendy::MF35Parser> get_mf35_data();
      vector<frendy::MF40Parser> get_mf40_data();

      //Setter
      void set_mf30_mt001_data(frendy::MF30MT001Parser parser_obj);
      void set_mf30_mt002_data(frendy::MF30MT002Parser parser_obj);
      void set_mf32_mt151_data(frendy::MF32MT151Parser parser_obj);

      void set_mf31_data(vector<frendy::MF31Parser> parser_obj);
      void set_mf33_data(vector<frendy::MF33Parser> parser_obj);
      void set_mf34_data(vector<frendy::MF34Parser> parser_obj);
      void set_mf35_data(vector<frendy::MF35Parser> parser_obj);
      void set_mf40_data(vector<frendy::MF40Parser> parser_obj);
  };
}

#endif // ENDF6_PARSER_COV_H
