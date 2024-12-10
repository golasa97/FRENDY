#ifndef ENDF6_CONVERTER_H
#define ENDF6_CONVERTER_H

#include "CommonUtils/TabInterpolator.hpp"
#include "EndfUtils/Endf6Parser/Endf6Parser.hpp"
#include "NuclearDataUtils/NuclearDataObject.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF01MT451Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF01MT452Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF01MT455Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF01MT456Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF01MT458Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF01MT460Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF02MT151Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF02MT152Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF02MT153Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF03Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF04Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF05Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF06Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF07MT002Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF07MT004Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF07MT451Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF08Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF08MT454Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF08MT457Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF08MT459Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF09Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF10Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF12Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF13Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF14Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF15Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF23Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF26Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF27Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF28Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF30MT001Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF30MT002Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF31Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF32MT151Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF33Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF34Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF35Converter.hpp"
#include "EndfUtils/MFxxMTyyyConverter/MF40Converter.hpp"

namespace frendy
{
  class Endf6Converter
  {
    private:
      static const Real min_check_dif; //= 1.0E-3;

      frendy::ErrorManager        err_obj;

      frendy::MF01MT451Converter  mf01mt451_conv_obj;
      frendy::MF01MT452Converter  mf01mt452_conv_obj;
      frendy::MF01MT455Converter  mf01mt455_conv_obj;
      frendy::MF01MT456Converter  mf01mt456_conv_obj;
      frendy::MF01MT458Converter  mf01mt458_conv_obj;
      frendy::MF01MT460Converter  mf01mt460_conv_obj;
      frendy::MF02MT151Converter  mf02mt151_conv_obj;
      frendy::MF02MT152Converter  mf02mt152_conv_obj;
      frendy::MF02MT153Converter  mf02mt153_conv_obj;
      frendy::MF03Converter       mf03_conv_obj;
      frendy::MF04Converter       mf04_conv_obj;
      frendy::MF05Converter       mf05_conv_obj;
      frendy::MF06Converter       mf06_conv_obj;
      frendy::MF07MT002Converter  mf07mt002_conv_obj;
      frendy::MF07MT004Converter  mf07mt004_conv_obj;
      frendy::MF07MT451Converter  mf07mt451_conv_obj;
      frendy::MF08Converter       mf08_conv_obj;
      frendy::MF08MT454Converter  mf08mt454_conv_obj;
      frendy::MF08MT457Converter  mf08mt457_conv_obj;
      frendy::MF08MT459Converter  mf08mt459_conv_obj;
      frendy::MF09Converter       mf09_conv_obj;
      frendy::MF10Converter       mf10_conv_obj;
      frendy::MF12Converter       mf12_conv_obj;
      frendy::MF13Converter       mf13_conv_obj;
      frendy::MF14Converter       mf14_conv_obj;
      frendy::MF15Converter       mf15_conv_obj;
      frendy::MF23Converter       mf23_conv_obj;
      frendy::MF26Converter       mf26_conv_obj;
      frendy::MF27Converter       mf27_conv_obj;
      frendy::MF28Converter       mf28_conv_obj;
      frendy::MF30MT001Converter  mf30mt001_conv_obj;
      frendy::MF30MT002Converter  mf30mt002_conv_obj;
      frendy::MF31Converter       mf31_conv_obj;
      frendy::MF32MT151Converter  mf32mt151_conv_obj;
      frendy::MF33Converter       mf33_conv_obj;
      frendy::MF34Converter       mf34_conv_obj;
      frendy::MF35Converter       mf35_conv_obj;
      frendy::MF40Converter       mf40_conv_obj;
 
      void check_mat_data(string func_name, Integer MF, Integer MT,
                          Integer& mat_no,   Integer& mat_no_base,
                          Real&    mat_data, Real&    mat_data_base, Real& mass, Real& mass_base);
      void check_temp_data(string func_name, Integer MF, Integer MT, Integer& mat_no,
                           Real& temp_data, Real& temp_data_base);
      void check_xs_data(string func_name, frendy::MF02MT151Parser& mf02mt151_data_obj,
                                           frendy::MF03Parser& mf03_data_obj);
      void modify_xs_data( frendy::MF03Parser& mf03_data_obj );

      void check_mt_list_all(vector<MF03Parser>& mf03_data_obj,
                             vector<MF04Parser>& mf04_data_obj,
                             vector<MF05Parser>& mf05_data_obj,
                             vector<MF06Parser>& mf06_data_obj,
                             vector<MF09Parser>& mf09_data_obj,
                             vector<MF10Parser>& mf10_data_obj);
      void check_mt_list(Integer mf_no_ref, Integer mf_no_com,
                         vector<Integer> mt_list_ref, vector<Integer> mt_list_com);

      void check_fission_data(MF01MT452Parser&    mf01mt452_data_obj,
                              vector<MF03Parser>& mf03_data_obj,
                              vector<MF04Parser>& mf04_data_obj,
                              vector<MF05Parser>& mf05_data_obj,
                              vector<MF06Parser>& mf06_data_obj);

    public:
      //constructor
      Endf6Converter(void);

      //destructor
      virtual ~Endf6Converter(void);

      //NuclearDataObject -> Endf6Parser
      void convert_frendy_to_endf_format(frendy::NuclearDataObject& frendy_obj,
                                         frendy::Endf6Parser& endf_obj);

      //Endf6Parser -> NuclearDataObject
      void convert_endf_format_to_frendy(frendy::Endf6Parser& endf_obj,
                                         frendy::NuclearDataObject& frendy_obj);


      //NuclearDataObject -> Endf6ParserNoCov
      void convert_frendy_to_endf_format(frendy::NuclearDataObject& frendy_obj,
                                         frendy::Endf6ParserNoCov& endf_obj);

      //Endf6ParserNoCov -> NuclearDataObject
      void convert_endf_format_to_frendy(frendy::Endf6ParserNoCov& endf_obj,
                                         frendy::NuclearDataObject& frendy_obj);


      //NuclearDataObject -> Endf6ParserCov
      void convert_frendy_to_endf_format(frendy::NuclearDataObject& frendy_obj,
                                         frendy::Endf6ParserCov& endf_obj);

      //Endf6ParserCov -> NuclearDataObject
      void convert_endf_format_to_frendy(frendy::Endf6ParserCov& endf_obj,
                                         frendy::NuclearDataObject& frendy_obj);
  };
}
#endif // ENDF6_CONVERTER_H
