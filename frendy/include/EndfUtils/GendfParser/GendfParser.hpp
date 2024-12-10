#ifndef GENDF_PARSER_H
#define GENDF_PARSER_H

#include <boost/timer/timer.hpp>

#include "EndfUtils/GendfParser/GMF01MT451Parser.hpp"
#include "EndfUtils/GendfParser/GMF03Parser.hpp"
#include "EndfUtils/GendfParser/GMF05Parser.hpp"
#include "EndfUtils/GendfParser/GMF06Parser.hpp"
#include "EndfUtils/GendfParser/GMF13Parser.hpp"
#include "EndfUtils/GendfParser/GMF16Parser.hpp"
#include "EndfUtils/EndfFileReader/EndfFileReader.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"

namespace frendy
{
  class GendfParser
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

      frendy::GMF01MT451Parser mf01_mt451_data;

      vector<frendy::GMF03Parser> mf03_data;
      vector<frendy::GMF05Parser> mf05_data;
      vector<frendy::GMF06Parser> mf06_data;
      vector<frendy::GMF13Parser> mf13_data;
      vector<frendy::GMF16Parser> mf16_data;

      void mod_list();

      void read_gendf();
      void parse_data(Integer mf_no, Integer mt_no, vector<Real>& time_each_mf);

      void parse_mf01(Integer mf_no, Integer mt_no);
      void parse_mf03(Integer mf_no, Integer mt_no);
      void parse_mf05(Integer mf_no, Integer mt_no);
      void parse_mf06(Integer mf_no, Integer mt_no);
      void parse_mf13(Integer mf_no, Integer mt_no);
      void parse_mf16(Integer mf_no, Integer mt_no);

      void set_parser_list();

    public:
      //constructor
      GendfParser(void);

      //destructor
      virtual ~GendfParser(void);

      void clear();

      void set_file_name(string file_name);
      void set_endf_file_reader(frendy::EndfFileReader& obj);
      void set_text(vector<string>& text_data);

      void mod_reaction_flg(frendy::NuclearDataObject& nucl_data_obj);
      void mod_temp(Real temp_val);

      string                   get_file_name();
      vector<Integer>          get_parser_list();
      vector<vector<Integer> > get_mt_list();
      vector<Integer>          get_mt_list(Integer mf_no);
      Real                     get_time_total();
      vector<vector<Real> >    get_time_each();

      void sort_all_mf_data();
      void sort_mf03_data();
      void sort_mf05_data();
      void sort_mf06_data();
      void sort_mf13_data();
      void sort_mf16_data();

      //Getter
      Integer                     get_mat_no();

      frendy::GMF01MT451Parser    get_mf01_mt451_data();

      vector<frendy::GMF03Parser> get_mf03_data();
      vector<frendy::GMF05Parser> get_mf05_data();
      vector<frendy::GMF06Parser> get_mf06_data();
      vector<frendy::GMF13Parser> get_mf13_data();
      vector<frendy::GMF16Parser> get_mf16_data();

      frendy::GMF03Parser get_mf03_data(Integer mt_no);
      frendy::GMF05Parser get_mf05_data(Integer mt_no);
      frendy::GMF06Parser get_mf06_data(Integer mt_no);
      frendy::GMF13Parser get_mf13_data(Integer mt_no);
      frendy::GMF16Parser get_mf16_data(Integer mt_no);

      //Setter
      void set_mat_no(Integer mat_no);

      void set_mf01_mt451_data(frendy::GMF01MT451Parser parser_obj);

      void set_mf03_data(vector<frendy::GMF03Parser> parser_obj);
      void set_mf05_data(vector<frendy::GMF05Parser> parser_obj);
      void set_mf06_data(vector<frendy::GMF06Parser> parser_obj);
      void set_mf13_data(vector<frendy::GMF13Parser> parser_obj);
      void set_mf16_data(vector<frendy::GMF16Parser> parser_obj);

      void set_mf03_data(frendy::GMF03Parser parser_obj);
      void set_mf05_data(frendy::GMF05Parser parser_obj);
      void set_mf06_data(frendy::GMF06Parser parser_obj);
      void set_mf13_data(frendy::GMF13Parser parser_obj);
      void set_mf16_data(frendy::GMF16Parser parser_obj);
  };
}

#endif // GENDF_PARSER_H
