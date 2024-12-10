#include "EndfUtils/MFxxMTyyyConverter/MF15Converter.hpp"

using namespace frendy;

//constructor
MF15Converter::MF15Converter(void)
{
}

//destructor
MF15Converter::~MF15Converter(void)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//PhotonDataContainer -> MF15Parser
void MF15Converter::convert_frendy_to_endf_format( PhotonDataContainer& frendy_obj, MF15Parser& endf_obj )
{
  //Get frendy data
  Integer                           mt_no        = frendy_obj.get_reaction_type();
  vector<Integer>                   LF           = frendy_obj.get_ene_distr_law_no();
  vector<vector<Integer> >          INT_P        = frendy_obj.get_ene_distr_weight_int_data();
  vector<vector<Integer> >          NBT_P        = frendy_obj.get_ene_distr_weight_range_data();
  vector<vector<Real> >             E_INT_P      = frendy_obj.get_ene_distr_weight_ene_data();
  vector<vector<Real> >             P_TAB        = frendy_obj.get_ene_distr_weight_data();
  vector<vector<Integer> >          INT_E_LF01   = frendy_obj.get_ene_distr_int_data();
  vector<vector<Integer> >          NBT_E_LF01   = frendy_obj.get_ene_distr_range_data();
  vector<vector<Real> >             E_LF01       = frendy_obj.get_incident_ene();
  vector<vector<vector<Integer> > > INT_G_LF01   = frendy_obj.get_ene_distr_nomalized_int_data();
  vector<vector<vector<Integer> > > NBT_G_LF01   = frendy_obj.get_ene_distr_nomalized_range_data();
  vector<vector<vector<Real> > >    E_INT_G_LF01 = frendy_obj.get_ene_distr_nomalized_ene_data();
  vector<vector<vector<Real> > >    G_TAB_LF01   = frendy_obj.get_ene_distr_nomalized_data();

  Integer mat_no = 0;
  if( static_cast<int>(LF.size())           == 0 && static_cast<int>(INT_P.size())      == 0 &&
      static_cast<int>(NBT_P.size())        == 0 && static_cast<int>(E_INT_P.size())    == 0 &&
      static_cast<int>(P_TAB.size())        == 0 && static_cast<int>(INT_E_LF01.size()) == 0 &&
      static_cast<int>(NBT_E_LF01.size())   == 0 && static_cast<int>(E_LF01.size())     == 0 &&
      static_cast<int>(INT_G_LF01.size())   == 0 && static_cast<int>(NBT_G_LF01.size()) == 0 &&
      static_cast<int>(E_INT_G_LF01.size()) == 0 && static_cast<int>(G_TAB_LF01.size()) == 0 )
  {
    mat_no = unassigned_mat_no;
    mt_no  = unassigned_mt_no;
  }
  
  Integer         NC = static_cast<Integer>(LF.size());
  vector<Integer> NE_LF01;
  vector<vector<Integer> >          NBT_S_LF05;
  vector<vector<Integer> >          INT_S_LF05;
  vector<vector<Real> >             E_INT_S_LF05;
  vector<vector<Real> >             S_TAB_LF05;
  vector<vector<Integer> >          NBT_G_LF05;
  vector<vector<Integer> >          INT_G_LF05;
  vector<vector<Real> >             E_INT_G_LF05;
  vector<vector<Real> >             G_TAB_LF05;
  
  int i_max = static_cast<int>(NC);
  NE_LF01.resize(i_max);
  NBT_S_LF05.resize(i_max);
  INT_S_LF05.resize(i_max);
  E_INT_S_LF05.resize(i_max);
  S_TAB_LF05.resize(i_max);
  NBT_G_LF05.resize(i_max);
  INT_G_LF05.resize(i_max);
  E_INT_G_LF05.resize(i_max);
  G_TAB_LF05.resize(i_max);
  for(int i=0; i<i_max; i++)
  {
    if( LF[i] == 1 )
    {
      NE_LF01[i] = static_cast<Integer>(E_LF01[i].size());
    }
    else
    {
      string class_name = "MF15Converter";
      string func_name  = "convert_frendy_to_endf_format( PhotonDataContainer& frendy_obj, MF15Parser& endf_obj )";

      ostringstream oss00, oss01, oss02, oss03;
      oss00 << mt_no;
      oss01 << i;
      oss02 << i_max;
      oss03 << LF[i];
      string str_data00 = "Section number (MT) : " + oss00.str();
      string str_data01 = "NC                  : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "LF                  : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("This LF value at MF=15 is not supported in this program.");
      err_com.push_back("Supported LF value is only 1.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    //else if( LF[i] == 5 )
    //{
    //}
    //else if( LF[i] == 7 )
    //{
    //}
    //else if( LF[i] == 9 )
    //{
    //}
    //else if( LF[i] == 11 )
    //{
    //}
  }
  

  //Set ENDF format data
  endf_obj.clear();
  endf_obj.set_mat_no(mat_no);
  endf_obj.set_mt_no(mt_no);
  endf_obj.set_NC(NC);
  endf_obj.set_LF(LF);
  endf_obj.set_NBT_P(NBT_P);
  endf_obj.set_INT_P(INT_P);
  endf_obj.set_E_INT_P(E_INT_P);
  endf_obj.set_P_TAB(P_TAB);
  endf_obj.set_NE_LF01(NE_LF01);
  endf_obj.set_NBT_E_LF01(NBT_E_LF01);
  endf_obj.set_INT_E_LF01(INT_E_LF01);
  endf_obj.set_E_LF01(E_LF01);
  endf_obj.set_NBT_G_LF01(NBT_G_LF01);
  endf_obj.set_INT_G_LF01(INT_G_LF01);
  endf_obj.set_E_INT_G_LF01(E_INT_G_LF01);
  endf_obj.set_G_TAB_LF01(G_TAB_LF01);
  endf_obj.set_NBT_S_LF05(NBT_S_LF05);
  endf_obj.set_INT_S_LF05(INT_S_LF05);
  endf_obj.set_E_INT_S_LF05(E_INT_S_LF05);
  endf_obj.set_S_TAB_LF05(S_TAB_LF05);
  endf_obj.set_NBT_G_LF05(NBT_G_LF05);
  endf_obj.set_INT_G_LF05(INT_G_LF05);
  endf_obj.set_E_INT_G_LF05(E_INT_G_LF05);
  endf_obj.set_G_TAB_LF05(G_TAB_LF05);

  //Clear declared data
  mt_no        = 0;
  LF.clear();
  clr_obj.clear_vec_array2_int(INT_P);
  clr_obj.clear_vec_array2_int(NBT_P);
  clr_obj.clear_vec_array2_real(E_INT_P);
  clr_obj.clear_vec_array2_real(P_TAB);
  clr_obj.clear_vec_array2_int(INT_E_LF01);
  clr_obj.clear_vec_array2_int(NBT_E_LF01);
  clr_obj.clear_vec_array2_real(E_LF01);
  clr_obj.clear_vec_array3_int(INT_G_LF01);
  clr_obj.clear_vec_array3_int(NBT_G_LF01);
  clr_obj.clear_vec_array3_real(E_INT_G_LF01);
  clr_obj.clear_vec_array3_real(G_TAB_LF01);
  
  NC = 0;
  NE_LF01.clear();
  clr_obj.clear_vec_array2_int(NBT_S_LF05);
  clr_obj.clear_vec_array2_int(INT_S_LF05);
  clr_obj.clear_vec_array2_real(E_INT_S_LF05);
  clr_obj.clear_vec_array2_real(S_TAB_LF05);
  clr_obj.clear_vec_array2_int(NBT_G_LF05);
  clr_obj.clear_vec_array2_int(INT_G_LF05);
  clr_obj.clear_vec_array2_real(E_INT_G_LF05);
  clr_obj.clear_vec_array2_real(G_TAB_LF05);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//MF15Parser -> PhotonDataContainer
void MF15Converter::convert_endf_format_to_frendy( MF15Parser& endf_obj, PhotonDataContainer& frendy_obj )
{
  //Get frendy data
  Integer                           reaction_type                  = endf_obj.get_mt_no();
  vector<Integer>                   ene_distr_law_no               = endf_obj.get_LF();
  vector<vector<Integer> >          ene_distr_weight_int_data      = endf_obj.get_INT_P();
  vector<vector<Integer> >          ene_distr_weight_range_data    = endf_obj.get_NBT_P();
  vector<vector<Real> >             ene_distr_weight_ene_data      = endf_obj.get_E_INT_P();
  vector<vector<Real> >             ene_distr_weight_data          = endf_obj.get_P_TAB();
  vector<vector<Integer> >          ene_distr_int_data             = endf_obj.get_INT_E_LF01();
  vector<vector<Integer> >          ene_distr_range_data           = endf_obj.get_NBT_E_LF01();
  vector<vector<Real> >             incident_ene                   = endf_obj.get_E_LF01();
  vector<vector<vector<Integer> > > ene_distr_nomalized_int_data   = endf_obj.get_INT_G_LF01();
  vector<vector<vector<Integer> > > ene_distr_nomalized_range_data = endf_obj.get_NBT_G_LF01();
  vector<vector<vector<Real> > >    ene_distr_nomalized_ene_data   = endf_obj.get_E_INT_G_LF01();
  vector<vector<vector<Real> > >    ene_distr_nomalized_data       = endf_obj.get_G_TAB_LF01();

  if( static_cast<int>(ene_distr_law_no.size())               == 0 &&
      static_cast<int>(ene_distr_weight_int_data.size())      == 0 &&
      static_cast<int>(ene_distr_weight_range_data.size())    == 0 &&
      static_cast<int>(ene_distr_weight_ene_data.size())      == 0 &&
      static_cast<int>(ene_distr_weight_data.size())          == 0 &&
      static_cast<int>(ene_distr_int_data.size())             == 0 &&
      static_cast<int>(ene_distr_range_data.size())           == 0 &&
      static_cast<int>(incident_ene.size())                   == 0 &&
      static_cast<int>(ene_distr_nomalized_int_data.size())   == 0 &&
      static_cast<int>(ene_distr_nomalized_range_data.size()) == 0 &&
      static_cast<int>(ene_distr_nomalized_ene_data.size())   == 0 &&
      static_cast<int>(ene_distr_nomalized_data.size())       == 0 )
  {
    reaction_type = unassigned_mt_no;
  }

  int i_max = static_cast<int>(ene_distr_law_no.size());
  for(int i=0; i<i_max; i++)
  {
    if( ene_distr_law_no[i] == 1 )
    {
    }
    else
    {
      string class_name = "MF15Converter";
      string func_name  = "convert_endf_format_to_frendy( MF15Parser& endf_obj, PhotonDataContainer& frendy_obj )";

      ostringstream oss00, oss01, oss02, oss03;
      oss00 << reaction_type;
      oss01 << i;
      oss02 << i_max;
      oss03 << ene_distr_law_no[i];
      string str_data00 = "Reaction type              : " + oss00.str();
      string str_data01 = "Element no                 : " + oss01.str() + " / " + oss02.str();
      string str_data02 = "Energy distribution law no : " + oss03.str();

      vector<string> err_com;
      err_com.push_back(str_data00);
      err_com.push_back(str_data01);
      err_com.push_back(str_data02);
      err_com.push_back("This energy distribution law no (LF) at MF=15 is not supported in this program.");
      err_com.push_back("Supported value is only 1.");

      err_obj.output_runtime_error(class_name, func_name, err_com);
    }
    //else if( ene_distr_law_no[i] == 5 )
    //{
    //}
    //else if( ene_distr_law_no[i] == 7 )
    //{
    //}
    //else if( ene_distr_law_no[i] == 9 )
    //{
    //}
    //else if( ene_distr_law_no[i] == 11 )
    //{
  }

  //Set ENDF format data
  //frendy_obj.clear();
  //text
  //mat_no
  frendy_obj.set_reaction_type(reaction_type);
  //ZA
  //AWR
  frendy_obj.set_ene_distr_law_no(ene_distr_law_no);
  frendy_obj.set_ene_distr_weight_range_data(ene_distr_weight_range_data);
  frendy_obj.set_ene_distr_weight_int_data(ene_distr_weight_int_data);
  frendy_obj.set_ene_distr_weight_ene_data(ene_distr_weight_ene_data);
  frendy_obj.set_ene_distr_weight_data(ene_distr_weight_data);
  frendy_obj.set_ene_distr_range_data(ene_distr_range_data);
  frendy_obj.set_ene_distr_int_data(ene_distr_int_data);
  frendy_obj.set_incident_ene(incident_ene);
  frendy_obj.set_ene_distr_nomalized_range_data(ene_distr_nomalized_range_data);
  frendy_obj.set_ene_distr_nomalized_int_data(ene_distr_nomalized_int_data);
  frendy_obj.set_ene_distr_nomalized_ene_data(ene_distr_nomalized_ene_data);
  frendy_obj.set_ene_distr_nomalized_data(ene_distr_nomalized_data);
/*
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Integer> > NBT_S_LF05
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Integer> > INT_S_LF05
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Real> > E_INT_S_LF05
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Real> > S_TAB_LF05
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Integer> > NBT_G_LF05
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Integer> > INT_G_LF05
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Real> > E_INT_G_LF05
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Real> > G_TAB_LF05
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Integer> > NBT_S_LF07 //Actual data name in Parser class is different (NBT_S_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Integer> > INT_S_LF07 //Actual data name in Parser class is different (INT_S_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Real> > E_INT_S_LF07 //Actual data name in Parser class is different (E_INT_S_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Real> > S_TAB_LF07 //Actual data name in Parser class is different (S_TAB_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Integer> > NBT_S_LF09 //Actual data name in Parser class is different (NBT_S_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Integer> > INT_S_LF09 //Actual data name in Parser class is different (INT_S_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Real> > E_INT_S_LF09 //Actual data name in Parser class is different (E_INT_S_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Real> > S_TAB_LF09 //Actual data name in Parser class is different (S_TAB_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Integer> > NBT_A_LF11 //Actual data name in Parser class is different (NBT_S_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Integer> > INT_A_LF11 //Actual data name in Parser class is different (INT_S_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Real> > E_INT_A_LF11 //Actual data name in Parser class is different (E_INT_S_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Real> > A_TAB_LF11 //Actual data name in Parser class is different (S_TAB_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Integer> > NBT_B_LF11 //Actual data name in Parser class is different (NBT_G_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Integer> > INT_B_LF11 //Actual data name in Parser class is different (INT_G_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Real> > E_INT_B_LF11 //Actual data name in Parser class is different (E_INT_G_LF05) 
  !!! This Parser data is not contained in the Container class !!! //vector<vector<Real> > B_TAB_LF11 //Actual data name in Parser class is different (G_TAB_LF05) 
*/

  //Clear declared data
  reaction_type                  = 0;
  ene_distr_law_no.clear();
  clr_obj.clear_vec_array2_int(ene_distr_weight_int_data);
  clr_obj.clear_vec_array2_int(ene_distr_weight_range_data);
  clr_obj.clear_vec_array2_real(ene_distr_weight_ene_data);
  clr_obj.clear_vec_array2_real(ene_distr_weight_data);
  clr_obj.clear_vec_array2_int(ene_distr_int_data);
  clr_obj.clear_vec_array2_int(ene_distr_range_data);
  clr_obj.clear_vec_array2_real(incident_ene);
  clr_obj.clear_vec_array3_int(ene_distr_nomalized_int_data);
  clr_obj.clear_vec_array3_int(ene_distr_nomalized_range_data);
  clr_obj.clear_vec_array3_real(ene_distr_nomalized_ene_data);
  clr_obj.clear_vec_array3_real(ene_distr_nomalized_data);
}

