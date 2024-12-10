#ifndef MF02MT151_WRITER_H
#define MF02MT151_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF02MT151Parser.hpp"

namespace frendy
{
  class MF02MT151Writer
  {
    private:
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;
      frendy::EndfFileWriter  efw_obj;

      frendy::MF02MT151Parser par_obj;
      vector<string>          text;

      static const Integer mf_no =   2;
      static const Integer mt_no = 151;

      void write_endf();
      void write_lru00(int& i, int& j);
      void write_lru01_lrf01_02(int& i, int& j);
      void write_lru01_lrf03(int& i, int& j);
      void write_lru01_lrf04(int& i, int& j);
      void write_lru01_lrf07(int& i, int& j);
      void write_lru01_lrf07_kbk_b80(int& i, int& j, int& k);
      void write_lru01_lrf07_kbk_b81(int& i, int& j, int& k);
      void write_lru01_lrf07_kps(int& i, int& j, int& k);

      void write_lru02(int& i, int& j);
      void write_lru02_a(int& i, int& j);
      void write_lru02_b(int& i, int& j);
      void write_lru02_c(int& i, int& j);

      void write_nro(int& i, int& j);

    public:
      //constructor
      MF02MT151Writer(void);

      //destructor
      virtual ~MF02MT151Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF02MT151Parser& mf02mt151parser_obj);
  };
}

#endif // MF02MT151_WRITER_H
