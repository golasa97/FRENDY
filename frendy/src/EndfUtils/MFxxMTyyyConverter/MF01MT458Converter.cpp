#include "EndfUtils/MFxxMTyyyConverter/MF01MT458Converter.hpp"

using namespace frendy;

//constructor
MF01MT458Converter::MF01MT458Converter(void)
{
}

//destructor
MF01MT458Converter::~MF01MT458Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//FissionDataContainer -> MF01MT458Parser
void MF01MT458Converter::convert_frendy_to_endf_format( FissionDataContainer& frendy_obj, MF01MT458Parser& endf_obj )
{
  //Get frendy data
  Integer      LFC   = frendy_obj.get_fis_ene_repr_flg();
  vector<Real> ET    = frendy_obj.get_fis_ene_tot();
  vector<Real> EFR   = frendy_obj.get_fis_ene_fp();
  vector<Real> ENP   = frendy_obj.get_fis_ene_n_p();
  vector<Real> END   = frendy_obj.get_fis_ene_n_d();
  vector<Real> EGP   = frendy_obj.get_fis_ene_gam_p();
  vector<Real> EGD   = frendy_obj.get_fis_ene_gam_d();
  vector<Real> EB    = frendy_obj.get_fis_ene_beta_d();
  vector<Real> ENU   = frendy_obj.get_fis_ene_neutrino();
  vector<Real> ER    = frendy_obj.get_fis_ene_non_neutrino();
  vector<Real> D_EFR = frendy_obj.get_fis_ene_tot_uncertainty();
  vector<Real> D_ENP = frendy_obj.get_fis_ene_fp_uncertainty();
  vector<Real> D_END = frendy_obj.get_fis_ene_n_p_uncertainty();
  vector<Real> D_EGP = frendy_obj.get_fis_ene_n_d_uncertainty();
  vector<Real> D_EGD = frendy_obj.get_fis_ene_gam_p_uncertainty();
  vector<Real> D_EB  = frendy_obj.get_fis_ene_gam_d_uncertainty();
  vector<Real> D_ENU = frendy_obj.get_fis_ene_beta_d_uncertainty();
  vector<Real> D_ER  = frendy_obj.get_fis_ene_neutrino_uncertainty();
  vector<Real> D_ET  = frendy_obj.get_fis_ene_non_neutrino_uncertainty();

  vector<Integer>          IFC        = frendy_obj.get_fis_ene_index();
  vector<Integer>          LDRV       = frendy_obj.get_fis_ene_evaluation_flg();
  vector<vector<Integer> > INT_EIFC   = frendy_obj.get_fis_ene_table_int_data();
  vector<vector<Integer> > NBT_EIFC   = frendy_obj.get_fis_ene_table_range_data();
  vector<vector<Real> >    E_INT_EIFC = frendy_obj.get_fis_ene_table_ene_data();
  vector<vector<Real> >    EIFC_TAB   = frendy_obj.get_fis_ene_table_data();

  Integer NFC  = static_cast<Integer>(IFC.size());

  Integer NPLY = static_cast<Integer>(ET.size()) - 1;
  Integer N1   = 18*(NPLY+1);
  Integer N2   =  9*(NPLY+1);

  Integer mat_no = 0;
  if( static_cast<int>(ET.size())    == 0 && static_cast<int>(EFR.size())   == 0 &&
      static_cast<int>(ENP.size())   == 0 && static_cast<int>(END.size())   == 0 &&
      static_cast<int>(EGP.size())   == 0 && static_cast<int>(EGD.size())   == 0 &&
      static_cast<int>(EB.size())    == 0 && static_cast<int>(ENU.size())   == 0 &&
      static_cast<int>(ER.size())    == 0 && static_cast<int>(D_EFR.size()) == 0 &&
      static_cast<int>(D_ENP.size()) == 0 && static_cast<int>(D_END.size()) == 0 &&
      static_cast<int>(D_EGP.size()) == 0 && static_cast<int>(D_EGD.size()) == 0 &&
      static_cast<int>(D_EB.size())  == 0 && static_cast<int>(D_ENU.size()) == 0 &&
      static_cast<int>(D_ER.size())  == 0 && static_cast<int>(D_ET.size())  == 0 )
  {
    mat_no = unassigned_mat_no;
  }

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_LFC(LFC);
  endf_obj.set_NFC(NFC);
  endf_obj.set_NPLY(NPLY);
  endf_obj.set_N1(N1);
  endf_obj.set_N2(N2);
  endf_obj.set_EFR(EFR);
  endf_obj.set_ENP(ENP);
  endf_obj.set_END(END);
  endf_obj.set_EGP(EGP);
  endf_obj.set_EGD(EGD);
  endf_obj.set_EB(EB);
  endf_obj.set_ENU(ENU);
  endf_obj.set_ER(ER);
  endf_obj.set_ET(ET);
  endf_obj.set_D_EFR(D_EFR);
  endf_obj.set_D_ENP(D_ENP);
  endf_obj.set_D_END(D_END);
  endf_obj.set_D_EGP(D_EGP);
  endf_obj.set_D_EGD(D_EGD);
  endf_obj.set_D_EB(D_EB);
  endf_obj.set_D_ENU(D_ENU);
  endf_obj.set_D_ER(D_ER);
  endf_obj.set_D_ET(D_ET);
  endf_obj.set_IFC(IFC);
  endf_obj.set_LDRV(LDRV);
  endf_obj.set_INT_EIFC(INT_EIFC);
  endf_obj.set_NBT_EIFC(NBT_EIFC);
  endf_obj.set_E_INT_EIFC(E_INT_EIFC);
  endf_obj.set_EIFC_TAB(EIFC_TAB);

  //Clear declared data
  ET.clear();
  EFR.clear();
  ENP.clear();
  END.clear();
  EGP.clear();
  EGD.clear();
  EB.clear();
  ENU.clear();
  ER.clear();
  D_EFR.clear();
  D_ENP.clear();
  D_END.clear();
  D_EGP.clear();
  D_EGD.clear();
  D_EB.clear();
  D_ENU.clear();
  D_ER.clear();
  D_ET.clear();
  IFC.clear();
  LDRV.clear();
  clr_obj.clear_vec_array2_int(INT_EIFC);
  clr_obj.clear_vec_array2_int(NBT_EIFC);
  clr_obj.clear_vec_array2_real(E_INT_EIFC);
  clr_obj.clear_vec_array2_real(EIFC_TAB);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF01MT458Parser -> FissionDataContainer
void MF01MT458Converter::convert_endf_format_to_frendy( MF01MT458Parser& endf_obj, FissionDataContainer& frendy_obj )
{
  //Get frendy data
  Integer      fis_ene_repr_flg                 = endf_obj.get_LFC();
  vector<Real> fis_ene_tot                      = endf_obj.get_ET();
  vector<Real> fis_ene_fp                       = endf_obj.get_EFR();
  vector<Real> fis_ene_n_p                      = endf_obj.get_ENP();
  vector<Real> fis_ene_n_d                      = endf_obj.get_END();
  vector<Real> fis_ene_gam_p                    = endf_obj.get_EGP();
  vector<Real> fis_ene_gam_d                    = endf_obj.get_EGD();
  vector<Real> fis_ene_beta_d                   = endf_obj.get_EB();
  vector<Real> fis_ene_neutrino                 = endf_obj.get_ENU();
  vector<Real> fis_ene_non_neutrino             = endf_obj.get_ER();
  vector<Real> fis_ene_tot_uncertainty          = endf_obj.get_D_EFR();
  vector<Real> fis_ene_fp_uncertainty           = endf_obj.get_D_ENP();
  vector<Real> fis_ene_n_p_uncertainty          = endf_obj.get_D_END();
  vector<Real> fis_ene_n_d_uncertainty          = endf_obj.get_D_EGP();
  vector<Real> fis_ene_gam_p_uncertainty        = endf_obj.get_D_EGD();
  vector<Real> fis_ene_gam_d_uncertainty        = endf_obj.get_D_EB();
  vector<Real> fis_ene_beta_d_uncertainty       = endf_obj.get_D_ENU();
  vector<Real> fis_ene_neutrino_uncertainty     = endf_obj.get_D_ER();
  vector<Real> fis_ene_non_neutrino_uncertainty = endf_obj.get_D_ET();

  vector<Integer>          fis_ene_index            = endf_obj.get_IFC();
  vector<Integer>          fis_ene_evaluation_flg   = endf_obj.get_LDRV();
  vector<vector<Integer> > fis_ene_table_int_data   = endf_obj.get_INT_EIFC();
  vector<vector<Integer> > fis_ene_table_range_data = endf_obj.get_NBT_EIFC();
  vector<vector<Real> >    fis_ene_table_ene_data   = endf_obj.get_E_INT_EIFC();
  vector<vector<Real> >    fis_ene_table_data       = endf_obj.get_EIFC_TAB();

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  //ZA
  //AWR
  frendy_obj.set_fis_ene_repr_flg(fis_ene_repr_flg);
  frendy_obj.set_fis_ene_fp(fis_ene_fp);
  frendy_obj.set_fis_ene_n_p(fis_ene_n_p);
  frendy_obj.set_fis_ene_n_d(fis_ene_n_d);
  frendy_obj.set_fis_ene_gam_p(fis_ene_gam_p);
  frendy_obj.set_fis_ene_gam_d(fis_ene_gam_d);
  frendy_obj.set_fis_ene_beta_d(fis_ene_beta_d);
  frendy_obj.set_fis_ene_neutrino(fis_ene_neutrino);
  frendy_obj.set_fis_ene_non_neutrino(fis_ene_non_neutrino);
  frendy_obj.set_fis_ene_tot(fis_ene_tot);
  frendy_obj.set_fis_ene_tot_uncertainty(fis_ene_tot_uncertainty);
  frendy_obj.set_fis_ene_fp_uncertainty(fis_ene_fp_uncertainty);
  frendy_obj.set_fis_ene_n_p_uncertainty(fis_ene_n_p_uncertainty);
  frendy_obj.set_fis_ene_n_d_uncertainty(fis_ene_n_d_uncertainty);
  frendy_obj.set_fis_ene_gam_p_uncertainty(fis_ene_gam_p_uncertainty);
  frendy_obj.set_fis_ene_gam_d_uncertainty(fis_ene_gam_d_uncertainty);
  frendy_obj.set_fis_ene_beta_d_uncertainty(fis_ene_beta_d_uncertainty);
  frendy_obj.set_fis_ene_neutrino_uncertainty(fis_ene_neutrino_uncertainty);
  frendy_obj.set_fis_ene_non_neutrino_uncertainty(fis_ene_non_neutrino_uncertainty);
  frendy_obj.set_fis_ene_index(fis_ene_index);
  frendy_obj.set_fis_ene_evaluation_flg(fis_ene_evaluation_flg);
  frendy_obj.set_fis_ene_table_int_data(fis_ene_table_int_data);
  frendy_obj.set_fis_ene_table_range_data(fis_ene_table_range_data);
  frendy_obj.set_fis_ene_table_ene_data(fis_ene_table_ene_data);
  frendy_obj.set_fis_ene_table_data(fis_ene_table_data);

  //Clear declared data
  fis_ene_tot.clear();
  fis_ene_fp.clear();
  fis_ene_n_p.clear();
  fis_ene_n_d.clear();
  fis_ene_gam_p.clear();
  fis_ene_gam_d.clear();
  fis_ene_beta_d.clear();
  fis_ene_neutrino.clear();
  fis_ene_non_neutrino.clear();
  fis_ene_tot_uncertainty.clear();
  fis_ene_fp_uncertainty.clear();
  fis_ene_n_p_uncertainty.clear();
  fis_ene_n_d_uncertainty.clear();
  fis_ene_gam_p_uncertainty.clear();
  fis_ene_gam_d_uncertainty.clear();
  fis_ene_beta_d_uncertainty.clear();
  fis_ene_neutrino_uncertainty.clear();
  fis_ene_non_neutrino_uncertainty.clear();
  fis_ene_index.clear();
  fis_ene_evaluation_flg.clear();
  clr_obj.clear_vec_array2_int(fis_ene_table_int_data);
  clr_obj.clear_vec_array2_int(fis_ene_table_range_data);
  clr_obj.clear_vec_array2_real(fis_ene_table_ene_data);
  clr_obj.clear_vec_array2_real(fis_ene_table_data);
}

