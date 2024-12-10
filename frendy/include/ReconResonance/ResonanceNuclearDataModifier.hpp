#ifndef RESONANCE_NUCLEAR_DATA_MODIFIER_H
#define RESONANCE_NUCLEAR_DATA_MODIFIER_H

#include "Config/CommonData.hpp"
#include "EndfUtils/Endf6Writer/Endf6Writer.hpp"
#include "EndfUtils/Endf6Converter/Endf6Converter.hpp"

namespace frendy
{
  class ResonanceNuclearDataModifier
  {
    private:
      frendy::ErrorManager     err_obj;
      frendy::VectorClearer    clr_obj;
      
      vector<Real8>          ene_grid;
      vector<vector<Real8> > sig_data;
      vector<vector<vector<Real8> > >          reso_ene_grid;
      vector<vector<vector<vector<Real8> > > > reso_sig_data;

      int     modify_photon_data_flg;
      
      Integer mat_no, reso_flg;

      Integer modify_endf_flg, unreso_flg;
      Integer endf_parser_flg, merge_grid_flg, merge_xs_flg, reso_grid_flg, reso_xs_flg;
      Integer set_label_flg;

#ifdef DEBUG_MODE
  public:
#endif
      frendy::Endf6ParserNoCov parser_no_cov;

      frendy::MF01MT451Parser    mf01mt451_par;
      frendy::MF02MT151Parser    mf02mt151_par, mf02mt151_par_mod;
      frendy::MF02MT152Parser    mf02mt152_par;
      vector<frendy::MF03Parser> mf03_par;
      vector<frendy::MF10Parser> mf10_par;
      vector<frendy::MF12Parser> mf12_par;
      vector<frendy::MF13Parser> mf13_par;
      vector<frendy::MF23Parser> mf23_par;

      void modify_endf();

      void modify_mf02mt151();
      void search_spi_ap_mf02mt151(Real& spi_unreso_val, Real& ap_unreso_val);
      void search_el_eh_mf02mt151(vector<vector<Real> >& el, vector<vector<Real> >& eh);

      void set_void_mf02mt151();
      void modify_mf02mt152();
      void modify_unreso_data_mf02mt152(vector<Real8>& unreso_ene_grid,
                                        vector<vector<Real8> >& unreso_sig_data,
                                        Integer& lssf_val, Integer& int_val);
      void add_unreso_data(vector<Real8>& base_ene_grid, vector<vector<Real8> >& base_sig_data,
                           vector<Real8>& add_ene_grid,  vector<vector<Real8> >& add_sig_data, Real& abn);

      void set_endf6_parser_data();
      void check_set_data();
      void set_modified_endf6_parser_data();

      void remove_each_subsection_photon_data();
      
    public:
      //constructor
      ResonanceNuclearDataModifier(void);

      //destructor
      virtual ~ResonanceNuclearDataModifier(void);

      void clear();
      void clear_parser_data();

      void set_modify_photon_data_flg(int int_val);

      void set_endf6_parser_no_cov(frendy::Endf6ParserNoCov& parser_obj);
      void set_nucl_data_obj(frendy::NuclearDataObject& nucl_data_obj);

      void set_ene_grid(vector<Real8>& real_vec);
      void set_sig_data(vector<vector<Real8> >& real_vec);
      void set_reso_ene_grid(vector<vector<vector<Real8> > >& real_vec);
      void set_reso_sig_data(vector<vector<vector<vector<Real8> > > >& real_vec);
      
      int                       get_modify_photon_data_flg();
      frendy::Endf6ParserNoCov  get_endf6_parser_no_cov();
      frendy::NuclearDataObject get_nucl_data_obj();
      vector<Real8>             get_ene_grid();
      vector<vector<Real8> >    get_sig_data();
      
      vector<vector<vector<Real8> > >          get_reso_ene_grid();
      vector<vector<vector<vector<Real8> > > > get_reso_sig_data();
  };
}

#endif //RESONANCE_NUCLEAR_DATA_MODIFIER_H
