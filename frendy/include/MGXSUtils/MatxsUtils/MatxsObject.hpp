#ifndef MATXS_OBJECT_H
#define MATXS_OBJECT_H

#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/StringUtils.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "EndfUtils/GendfParser/GMF16Parser.hpp"

namespace frendy
{
  static const Integer matxw_def = 5000;

  class MatxsMatrixData //8d, 9d, and 10d
  {
    private:
      frendy::ErrorManager   err_obj;

#ifdef DEBUG_MODE
  public:
#endif
      Integer noutg;

      //8d
      string          hmtx;
      Integer         lord, jconst;
      vector<Integer> jband, ijj;

      //9d
      vector<vector<vector<Real> > > scat;

      //10d
      vector<Real> spec, prod;

      void read_8d_data(vector<string>& text_vec, int& line_no);
      void read_9d_data(vector<string>& text_vec, int& line_no);
      void read_10d_data(vector<string>& text_vec, int& line_no);

    public:

      //constructor
      MatxsMatrixData(void);

      //destructor
      virtual ~MatxsMatrixData(void);

      void clear();

      void           read_data(vector<string>& text_vec, int& line_no);
      vector<string> write_data();

      Integer get_loc_no();

      //Setter
      void set_noutg(Integer int_data);

      //8d
      void set_hmtx(string str_data);
      void set_lord(Integer int_data);
      void set_jconst(Integer int_data);
      void set_jband(vector<Integer> int_vec);
      void set_ijj(vector<Integer> int_vec);

      //9d
      void set_scat(vector<vector<vector<Real> > > real_vec);

      //10d
      void set_spec(vector<Real> real_vec);
      void set_prod(vector<Real> real_vec);

      //Getter
      Integer         get_noutg();

      //8d
      string          get_hmtx();
      Integer         get_lord();
      Integer         get_jconst();
      vector<Integer> get_jband();
      vector<Integer> get_ijj();

      //9d
      vector<vector<vector<Real> > > get_scat();

      //10d
      vector<Real> get_spec();
      vector<Real> get_prod();
  };

////////////////////////////////////////////////////////////////////////////////////////////////////

  class MatxsSubmaterialData //6d and 7d
  {
    private:
      frendy::ErrorManager   err_obj;

#ifdef DEBUG_MODE
  public:
#endif
      Integer noutg, n1d, n2d;

      //6d
      vector<string>  hvps;
      vector<Integer> nfg, nlg;

      //7d
      vector<vector<Real> > vps;

      //8-10d
      vector<frendy::MatxsMatrixData> matrix_obj;

      void read_6d_data(vector<string>& text_vec, int& line_no);
      void read_7d_data(vector<string>& text_vec, int& line_no);

    public:

      //constructor
      MatxsSubmaterialData(void);

      //destructor
      virtual ~MatxsSubmaterialData(void);

      void clear();

      void           read_data(vector<string>& text_vec, int& line_no);
      vector<string> write_data();

      Integer get_loc_no();

      //Setter
      void set_noutg(Integer int_data);
      void set_n1d(Integer int_data);
      void set_n2d(Integer int_data);

      //6d
      void set_hvps(vector<string> str_vec);
      void set_nfg(vector<Integer> int_vec);
      void set_nlg(vector<Integer> int_vec);

      //7d
      void set_vps(vector<vector<Real> > real_vec);

      //8-10d
      void set_matrix_obj(vector<frendy::MatxsMatrixData> obj_vec);

      //Getter
      Integer get_noutg();
      Integer get_n1d();
      Integer get_n2d();

      //6d
      vector<string>  get_hvps();
      vector<Integer> get_nfg();
      vector<Integer> get_nlg();

      //7d
      vector<vector<Real> > get_vps();

      //8-10d
      vector<frendy::MatxsMatrixData> get_matrix_obj();
  };

////////////////////////////////////////////////////////////////////////////////////////////////////

  class MatxsMaterialData //5d
  {
    private:
      frendy::ErrorManager   err_obj;

#ifdef DEBUG_MODE
  public:
#endif
      vector<Integer> ngrp, joutp;
      Integer         nsubm;

      //5d
      string hmat;
      Real   amass;

      vector<Real>    temp,  sigz;
      vector<Integer> itype, n1d, n2d, locs;
      vector<Integer> noutg;

      //6-10d
      vector<frendy::MatxsSubmaterialData> submat_obj;

      void calc_noutg();

    public:

      //constructor
      MatxsMaterialData(void);

      //destructor
      virtual ~MatxsMaterialData(void);

      void clear();

      void           read_data(vector<string>& text_vec, int& line_no);
      vector<string> write_data();

      void    calc_locs();
      Integer get_loc_no();

      //Setter
      void set_ngrp(vector<Integer> int_vec);
      void set_joutp(vector<Integer> int_vec);
      void set_nsubm(Integer int_data);

      void set_hmat(string str_data);
      void set_amass(Real real_data);

      void set_temp(vector<Real> real_vec);
      void set_sigz(vector<Real> real_vec);
      void set_itype(vector<Integer> int_vec);
      void set_n1d(vector<Integer> int_vec);
      void set_n2d(vector<Integer> int_vec);
      void set_locs(vector<Integer> int_vec);

      //6-10d
      void set_submat_obj(vector<frendy::MatxsSubmaterialData> obj_vec);

      //Getter
      vector<Integer> get_ngrp();
      vector<Integer> get_joutp();
      Integer         get_nsubm();

      string get_hmat();
      Real   get_amass();

      vector<Real>    get_temp();
      vector<Real>    get_sigz();
      vector<Integer> get_itype();
      vector<Integer> get_n1d();
      vector<Integer> get_n2d();
      vector<Integer> get_locs();

      //6-10d
      vector<frendy::MatxsSubmaterialData> get_submat_obj();
  };

////////////////////////////////////////////////////////////////////////////////////////////////////

  class MatxsGroupStructureData //4d
  {
    private:
      frendy::ErrorManager   err_obj;

#ifdef DEBUG_MODE
  public:
#endif

      int          ngrp;

      //4d
      vector<Real> gpb; //gpb + emin

    public:

      //constructor
      MatxsGroupStructureData(void);

      //destructor
      virtual ~MatxsGroupStructureData(void);

      void clear();

      void           read_data(vector<string>& text_vec, int& line_no);
      vector<string> write_data();

      Integer get_loc_no();

      //Setter
      void set_ngrp(int int_data);
      void set_gpb(vector<Real> real_vec);

      //Getter
      int          get_ngrp();
      vector<Real> get_gpb();
  };

////////////////////////////////////////////////////////////////////////////////////////////////////

  class MatxsCommonData //0v, 1d, 2d, and 3d
  {
    private:
      frendy::ErrorManager   err_obj;

#ifdef DEBUG_MODE
  public:
#endif

      //0v
      string  hname, huse;
      Integer ivers;

      //1d
      Integer npart, ntype, nholl, nmat, matxw, length;

      //2d
      vector<string> hsetid;

      //3d
      vector<string>  hpart, htype, hmatn;
      vector<Integer> ngrp, jinp, joutp, nsubm, locm;

      //4d
      vector<frendy::MatxsGroupStructureData> grp_obj;

      //5-10d
      vector<frendy::MatxsMaterialData> mat_obj;

      void search_0v_data(vector<string>& text_vec, int& line_no);

      void read_0v_data(vector<string>& text_vec, int& line_no);
      void read_1d_data(vector<string>& text_vec, int& line_no);
      void read_2d_data(vector<string>& text_vec, int& line_no);
      void read_3d_data(vector<string>& text_vec, int& line_no);

      void calc_1d_data();

      void mod_tsl_name(string& str_data, Integer mt_no);

      int  add_photon_production_data_check_data
             (vector<frendy::GMF16Parser>& gmf_data, vector<Real>& ene_mg,
              Integer& grp_pos, Integer& mt_data_no);

    public:

      //constructor
      MatxsCommonData(void);

      //destructor
      virtual ~MatxsCommonData(void);

      void clear();

      void           read_data(vector<string>& text_vec);
      void           read_data(vector<string>& text_vec, int& line_no);
      vector<string> write_data();

      void           mod_tsl_name(Integer mt_no);
      string         get_tsl_name(Integer mt_no);
      string         get_react_name(Integer mt_no);

      void           add_photon_production_data
                       (vector<frendy::GMF16Parser>& gmf_data,
                        vector<Real>& mg_ene_n, vector<Real>& mg_ene_g);

      //Setter
      //0v
      void set_hname(string str_data);
      void set_huse(string str_data);
      void set_ivers(Integer int_data);

      //1d
      void set_npart(Integer int_data);
      void set_ntype(Integer int_data);
      void set_nholl(Integer int_data);
      void set_nmat(Integer int_data);
      void set_matxw(Integer int_data);
      void set_length(Integer int_data);

      //2d
      void set_hsetid(vector<string> str_vec);

      //3d
      void set_hpart(vector<string> str_vec);
      void set_htype(vector<string> str_vec);
      void set_hmatn(vector<string> str_vec);
      void set_ngrp(vector<Integer> int_vec);
      void set_jinp(vector<Integer> int_vec);
      void set_joutp(vector<Integer> int_vec);
      void set_nsubm(vector<Integer> int_vec);
      void set_locm(vector<Integer> int_vec);

      //4d
      void set_grp_obj(vector<frendy::MatxsGroupStructureData> obj_vec);

      //5-10d
      void set_mat_obj(vector<frendy::MatxsMaterialData> obj_vec);

      //Getter
      //0v
      string  get_hname();
      string  get_huse();
      Integer get_ivers();

      //1d
      Integer get_npart();
      Integer get_ntype();
      Integer get_nholl();
      Integer get_nmat();
      Integer get_matxw();
      Integer get_length();

      //2d
      vector<string> get_hsetid();

      //3d
      vector<string>  get_hpart();
      vector<string>  get_htype();
      vector<string>  get_hmatn();
      vector<Integer> get_ngrp();
      vector<Integer> get_jinp();
      vector<Integer> get_joutp();
      vector<Integer> get_nsubm();
      vector<Integer> get_locm();

      //4d
      vector<frendy::MatxsGroupStructureData> get_grp_obj();

      //5-10d
      vector<frendy::MatxsMaterialData> get_mat_obj();
  };
}

#endif //MATXS_OBJECT_H
