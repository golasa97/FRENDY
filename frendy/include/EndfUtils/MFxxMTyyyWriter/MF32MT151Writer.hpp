#ifndef MF32MT151_WRITER_H
#define MF32MT151_WRITER_H

#include "EndfUtils/EndfFileWriter/EndfFileWriter.hpp"
#include "EndfUtils/MFxxMTyyyParser/MF32MT151Parser.hpp"

namespace frendy
{
  class MF32MT151Writer
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      frendy::EndfFileWriter   efw_obj;

      frendy::MF32MT151Parser  par_obj;
      vector<string>           text;

      static const Integer mf_no =  32;
      static const Integer mt_no = 151;

      void write_endf();
      void write_nro00(int i, int j);
      void write_nro01(int i, int j);
      void write_NI(int i, int j, int k);
      void write_NI_lb00(int i, int j, int k);
      void write_NI_lb05(int i, int j, int k);
      void write_NI_lb06(int i, int j, int k);

      void write_lcomp00(int i, int j);
      void write_lcomp01_lrf01(int i, int j);
      void write_lcomp01_lrf07(int i, int j);
      void write_lcomp02_lrf01(int i, int j);
      void write_lcomp02_lrf03(int i, int j);
      void write_lcomp02_lrf07(int i, int j);
      void write_lcomp02_intg(int i, int j);

      void write_lru01(int i, int j, int k);
      void write_lru02(int i, int j);

    public:
      //constructor
      MF32MT151Writer(void);

      //destructor
      virtual ~MF32MT151Writer(void);

      void clear();

      vector<string> get_endf_text_data(frendy::MF32MT151Parser& MF32MT151parser_obj);
  };
}

#endif // MF32MT151_WRITER_H
