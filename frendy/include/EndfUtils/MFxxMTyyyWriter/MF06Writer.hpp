#ifndef MF06_WRITER_H
#define MF06_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF06Parser.hpp"

namespace frendy
{
  class MF06Writer
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::VectorClearer  clr_obj;
      frendy::EndfFileWriter efw_obj;

      frendy::MF06Parser     par_obj;
      vector<string>         text;

      static const Integer mf_no = 6;

      void write_endf();
      void write_law01(int& i, vector<string>& text);
      void write_law02(int& i, vector<string>& text);
      void write_law05(int& i, vector<string>& text);
      void write_law07(int& i, vector<string>& text);

      void write_thermal_scatter(vector<string>& text);
      void write_incoherent_inelastic_scatter(vector<string>& text);
      void write_incoherent_elastic_scatter(vector<string>& text);

    public:
      //constructor
      MF06Writer(void);

      //destructor
      virtual ~MF06Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF06Parser& mf06parser_obj);
  };
}

#endif // MF06_WRITER_H

