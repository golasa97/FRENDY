#ifndef ENDF6_PARSER_H
#define ENDF6_PARSER_H

#include <boost/timer/timer.hpp>

#include "EndfUtils/Endf6Parser/Endf6ParserNoCov.hpp"
#include "EndfUtils/Endf6Parser/Endf6ParserCov.hpp"

namespace frendy
{
  class Endf6Parser
  {
    private:
      frendy::VectorClearer    clr_obj;
      frendy::ErrorManager     err_obj;
      frendy::EndfFileReader   efr_obj;

      string                   name;
      vector<Integer>          parser_list, parser_list_no_cov, parser_list_cov;
      vector<vector<Integer> > mt_list;

      vector<Real>             time_total;
      vector<vector<Real> >    time_each, time_each_no_cov, time_each_cov;

      frendy::Endf6ParserNoCov cp_no_cov;
      frendy::Endf6ParserCov   cp_cov;

      void mod_list();

      void read_endf();
      void read_endf_no_cov();
      void read_endf_cov();
      void read_endf_xs_only();

      void set_parser_list();
      void set_parser_list_no_cov();
      void set_parser_list_cov();

    public:
      //constructor
      Endf6Parser(void);

      //destructor
      virtual ~Endf6Parser(void);

      void clear();

      void set_file_name(string file_name);
      void set_endf_file_reader(frendy::EndfFileReader& obj);
      void set_text(vector<string>& text_data);

      void set_file_name_no_cov(string file_name);
      void set_endf_file_reader_no_cov(frendy::EndfFileReader& obj);
      void set_text_no_cov(vector<string>& text_data);

      void set_file_name_cov(string file_name);
      void set_endf_file_reader_cov(frendy::EndfFileReader& obj);
      void set_text_cov(vector<string>& text_data);

      void set_file_name_xs_only(string file_name);
      void set_endf_file_reader_xs_only(frendy::EndfFileReader& obj);
      void set_text_xs_only(vector<string>& text_data);

      string                   get_file_name();
      vector<Integer>          get_parser_list();
      vector<vector<Integer> > get_mt_list();
      vector<Real>             get_time_total();
      vector<vector<Real> >    get_time_each();

      //Getter
      frendy::Endf6ParserCov     get_endf6_parser_cov();
      frendy::Endf6ParserNoCov   get_endf6_parser_no_cov();

      frendy::MF01MT451Parser    get_mf01_mt451_data();
      frendy::MF01MT452Parser    get_mf01_mt452_data();
      frendy::MF01MT455Parser    get_mf01_mt455_data();
      frendy::MF01MT456Parser    get_mf01_mt456_data();
      frendy::MF01MT458Parser    get_mf01_mt458_data();
      frendy::MF01MT460Parser    get_mf01_mt460_data();
      frendy::MF02MT151Parser    get_mf02_mt151_data();
      frendy::MF02MT152Parser    get_mf02_mt152_data();
      frendy::MF02MT153Parser    get_mf02_mt153_data();
      frendy::MF07MT002Parser    get_mf07_mt002_data();
      frendy::MF07MT004Parser    get_mf07_mt004_data();
      frendy::MF07MT451Parser    get_mf07_mt451_data();
      frendy::MF08MT454Parser    get_mf08_mt454_data();
      frendy::MF08MT457Parser    get_mf08_mt457_data();
      frendy::MF08MT459Parser    get_mf08_mt459_data();
      frendy::MF30MT001Parser    get_mf30_mt001_data();
      frendy::MF30MT002Parser    get_mf30_mt002_data();
      frendy::MF32MT151Parser    get_mf32_mt151_data();

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
      vector<frendy::MF31Parser> get_mf31_data();
      vector<frendy::MF33Parser> get_mf33_data();
      vector<frendy::MF34Parser> get_mf34_data();
      vector<frendy::MF35Parser> get_mf35_data();
      vector<frendy::MF40Parser> get_mf40_data();


      //Setter
      void set_endf6_parser_cov(frendy::Endf6ParserCov parser_obj);
      void set_endf6_parser_no_cov(frendy::Endf6ParserNoCov parser_obj);

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
      void set_mf30_mt001_data(frendy::MF30MT001Parser parser_obj);
      void set_mf30_mt002_data(frendy::MF30MT002Parser parser_obj);
      void set_mf32_mt151_data(frendy::MF32MT151Parser parser_obj);

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
      void set_mf31_data(vector<frendy::MF31Parser> parser_obj);
      void set_mf33_data(vector<frendy::MF33Parser> parser_obj);
      void set_mf34_data(vector<frendy::MF34Parser> parser_obj);
      void set_mf35_data(vector<frendy::MF35Parser> parser_obj);
      void set_mf40_data(vector<frendy::MF40Parser> parser_obj);

      void set_linearize_tab_flg(int int_val);
      void set_linearize_tolerance(Real real_val);
      int  get_linearize_tab_flg();
      Real get_linearize_tolerance();
  };
}

#endif // ENDF6_PARSER_H
