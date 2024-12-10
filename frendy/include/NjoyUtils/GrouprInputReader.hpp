#ifndef READ_GROUPR_INPUT_H
#define READ_GROUPR_INPUT_H

#include <boost/algorithm/string.hpp>

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "NjoyUtils/NjoyInputReader.hpp"

namespace frendy
{
  class GrouprInputReader
  {
    private:
      frendy::NjoyInputReader rn_obj;
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;

      string                  input_groupr;

      //Card 1
      string                  endf_file_name, pendf_file_name,
                              gendf_file_name_inp, gendf_file_name_out;

      //Card 2
      vector<Integer>         matb, ign, igg, iwt, lord, ntemp, nsigz, iprint, ismooth;

      //Card 3
      vector<string>          title;

      //Card 4-7
      vector<vector<Real> >   temp, sigz, egn, egg;

      //Card 08
      //Card 08a
      vector<Real>            fehi, sigpot, alpha_add, sam, beta, alpha_ext, gamma;
      vector<Integer>         nflmax, jsigz;
      //Card 08b
      vector<vector<Integer> > wght_nbt, wght_int;
      vector<vector<Real> >    wght_e,   wght_w;
      //Card 08c
      vector<Real>            eb, tb, ec, tc;
      //Card 08d
      vector<string>          ninwt;

      //Card 09
      vector<vector<vector<Integer> > > mf, mt;
      vector<vector<vector<string> > >  mtname;

      void read_file_name(ifstream& fin);

      void read_cards_two_and_three
             (ifstream& fin, Integer& matb_each,  Integer& ign_each,    Integer& igg_each,
                             Integer& iwt_each,   Integer& lord_each,   Integer& ntemp_each,
                             Integer& nsigz_each, Integer& iprint_each, Integer& ismooth_reach,
                             string&  title_each, int& data_no, int& copy_flg);
      void read_temp_and_sigz
             (ifstream& fin, Integer ntemp_each, vector<Real>& temp_each,
                             Integer nsigz_each, vector<Real>& sigz_each);
      void read_energy_group_structure
             (ifstream& fin, string data_name, vector<Real>& ene_vec);

      void read_iwt_option_a
             (ifstream& fin, Real& fehi_each, Real& sigpot_each, Real& alpha_add_each,
              Real& sam_each, Real& beta_each, Real& alpha_ext_each, Real& gamma_each,
             Integer& nflmax_each, string& ninwt_each, Integer& jsigz_each);
      void read_iwt_option_b
             (ifstream& fin, vector<Integer>& wght_nbt_each, vector<Integer>& wght_int_each,
                             vector<Real>&    wght_e_each,   vector<Real>&    wght_w_each);
      void read_iwt_option_c
             (ifstream& fin, Real& eb_each, Real& tb_each, Real& ec_each, Real& tc_each);
      void read_iwt_option_d
             (ifstream& fin, string& ninwt_each);

      void read_mf_and_mt(ifstream& fin,
                          vector<vector<Integer> >& mf_each, vector<vector<Integer> >& mt_each,
                          vector<vector<string> >&  mtname_each);

      void read_cards_four_to_nine(ifstream& fin);
      void read_card_ten(ifstream& fin);

    public:
      //constructor
      GrouprInputReader(void);

      //destructor
      virtual ~GrouprInputReader(void);

      //read input file for groupr
      void read_input(string file_name);
      void read_input(string file_name, int line_no);

      void clear();

      string                   get_input_groupr();

      string                   get_endf_file_name();
      string                   get_pendf_file_name();
      string                   get_gendf_file_name_inp();
      string                   get_gendf_file_name_out();
      string                   get_ace_file_name();
      string                   get_mcnp_dir_name();
      vector<Integer>          get_matb();
      vector<Integer>          get_ign();
      vector<Integer>          get_igg();
      vector<Integer>          get_iwt();
      vector<Integer>          get_lord();
      vector<Integer>          get_ntemp();
      vector<Integer>          get_nsigz();
      vector<Integer>          get_iprint();
      vector<Integer>          get_ismooth();
      vector<string>           get_title();
      vector<vector<Real> >    get_temp();
      vector<vector<Real> >    get_sigz();
      vector<vector<Real> >    get_egn();
      vector<vector<Real> >    get_egg();
      vector<Real>             get_fehi();
      vector<Real>             get_sigpot();
      vector<Real>             get_alpha_add();
      vector<Real>             get_sam();
      vector<Real>             get_beta();
      vector<Real>             get_alpha_ext();
      vector<Real>             get_gamma();
      vector<Integer>          get_nflmax();
      vector<Integer>          get_jsigz();
      vector<vector<Integer> > get_wght_nbt();
      vector<vector<Integer> > get_wght_int();
      vector<vector<Real> >    get_wght_e();
      vector<vector<Real> >    get_wght_w();
      vector<Real>             get_eb();
      vector<Real>             get_tb();
      vector<Real>             get_ec();
      vector<Real>             get_tc();
      vector<string>           get_ninwt();
      vector<vector<vector<Integer> > > get_mf();
      vector<vector<vector<Integer> > > get_mt();
      vector<vector<vector<string> > >  get_mtname();
  }; 
}

#endif //READ_GROUPR_INPUT_H
