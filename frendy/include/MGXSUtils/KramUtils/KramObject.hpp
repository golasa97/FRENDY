#ifndef KRAM_OBJECT_H
#define KRAM_OBJECT_H

#include "CommonUtils/VectorClearer.hpp"
#include "CommonUtils/ErrorManager.hpp"
#include "CommonUtils/StringUtils.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "EndfUtils/GendfParser/GMF16Parser.hpp"

namespace frendy
{
  class KramUtils //Common tools for KramXsnData, KramFspData, and KramAscData
  {
    public:
      //constructor
      KramUtils(void);

      //destructor
      virtual ~KramUtils(void);

      vector<vector<Real> > reverse_mg_array(vector<vector<Real> >& xs_vec);
      vector<Real>          reverse_mg_vec(vector<Real>& xs_vec);
  };

  class KramXsnData //KSN (Cross section)
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::VectorClearer  clr_obj;

#ifdef DEBUG_MODE
  public:
#endif
      int mat_no, ng;

      vector<vector<Real> > xs_sc;
      vector<Real>          xs_prod, xs_abs, xs_fis, xs_tot;

    public:

      //constructor
      KramXsnData(void);

      //destructor
      virtual ~KramXsnData(void);

      void clear();

      void           read_data(vector<string>& text_vec, int mg_no);
      void           read_data(vector<string>& text_vec, int& line_no, int mg_no);
      vector<string> write_data();

      bool isFissile();

      //Setter
      void set_mat_no(int int_data);
      void set_ng(int int_data);

      void set_xs_sc(vector<vector<Real> > xs_vec);
      void set_xs_prod(vector<Real> xs_vec);
      void set_xs_abs(vector<Real> xs_vec);
      void set_xs_fis(vector<Real> xs_vec);
      void set_xs_tot(vector<Real> xs_vec);

      void set_xs_sc_from_gendf(vector<vector<Real> > xs_vec);
      void set_xs_prod_from_gendf(vector<Real> xs_vec);
      void set_xs_abs_from_gendf(vector<Real> xs_vec);
      void set_xs_fis_from_gendf(vector<Real> xs_vec);
      void set_xs_tot_from_gendf(vector<Real> xs_vec);

      //Getter
      int get_mat_no();
      int get_ng();

      vector<vector<Real> > get_xs_sc();

      vector<Real> get_xs_prod();
      vector<Real> get_xs_abs();
      vector<Real> get_xs_fis();
      vector<Real> get_xs_tot();
  };

////////////////////////////////////////////////////////////////////////////////////////////////////

  class KramFspData //FSP (Fission Spectrum)
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::VectorClearer  clr_obj;

#ifdef DEBUG_MODE
  public:
#endif
      int mat_no, ng;

      vector<Real> fsp;

    public:

      //constructor
      KramFspData(void);

      //destructor
      virtual ~KramFspData(void);

      void clear();

      void           read_data(vector<string>& text_vec, int mg_no);
      void           read_data(vector<string>& text_vec, int& line_no, int mg_no);
      vector<string> write_data();

      bool isFissile();


      //Setter
      void set_mat_no(int int_data);
      void set_ng(int int_data);

      void set_fsp(vector<Real> fsp_vec);
      void set_fsp_from_gendf(vector<Real> fsp_vec);

      //Getter
      int get_mat_no();
      int get_ng();

      vector<Real> get_fsp();
  };

////////////////////////////////////////////////////////////////////////////////////////////////////

  class KramAscData //ASC (Angular scattering)
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::VectorClearer  clr_obj;

#ifdef DEBUG_MODE
  public:
#endif
      int mat_no, ng, pl_no;

      vector<vector<vector<Real> > > asc;

    public:

      //constructor
      KramAscData(void);

      //destructor
      virtual ~KramAscData(void);

      void clear();

      void           read_data(vector<string>& text_vec, int mg_no);
      void           read_data(vector<string>& text_vec, int& line_no, int mg_no);
      vector<string> write_data();


      //Setter
      void set_mat_no(int int_data);
      void set_ng(int int_data);
      void set_pl_no(int int_data);

      void set_asc(vector<vector<vector<Real> > > xs_vec);
      void set_asc(vector<vector<Real> > xs_vec, int pl_no_val);
      void set_asc_from_gendf(vector<vector<vector<Real> > > xs_vec);
      void set_asc_from_gendf(vector<vector<Real> > xs_vec, int pl_no_val);

      //Getter
      int get_mat_no();
      int get_ng();
      int get_pl_no();

      vector<vector<vector<Real> > > get_asc();
  };

////////////////////////////////////////////////////////////////////////////////////////////////////

  class KramCommonData //XSN, FSP, ASC
  {
    private:
      frendy::ErrorManager   err_obj;
      frendy::VectorClearer  clr_obj;

#ifdef DEBUG_MODE
  public:
#endif

      vector<frendy::KramXsnData> xsn_vec;
      vector<frendy::KramFspData> fsp_vec;
      vector<frendy::KramAscData> asc_vec;

      void read_xsn_data(vector<string>& text_vec, int& line_no, int mg_no);
      void read_fsp_data(vector<string>& text_vec, int& line_no, int mg_no);
      void read_asc_data(vector<string>& text_vec, int& line_no, int mg_no);

    public:

      //constructor
      KramCommonData(void);

      //destructor
      virtual ~KramCommonData(void);

      void clear();

      void           read_data(vector<string>& text_vec, int mg_no);
      void           read_data(vector<string>& text_vec, int& line_no, int mg_no);
      vector<string> write_data();

      //Setter
      void set_xsn(frendy::KramXsnData xsn_data);
      void set_fsp(frendy::KramFspData fsp_data);
      void set_asc(frendy::KramAscData asc_data);

      void set_xsn_vec(vector<frendy::KramXsnData> xsn_data);
      void set_fsp_vec(vector<frendy::KramFspData> fsp_data);
      void set_asc_vec(vector<frendy::KramAscData> asc_data);


      //Getter
      int         get_ng();

      vector<int> get_mat_list();
      vector<int> get_mat_list_xsn();
      vector<int> get_mat_list_fsp();
      vector<int> get_mat_list_asc();

      vector<frendy::KramXsnData> get_xsn_vec();
      vector<frendy::KramFspData> get_fsp_vec();
      vector<frendy::KramAscData> get_asc_vec();

      frendy::KramXsnData get_xsn(int mat_no);
      frendy::KramFspData get_fsp(int mat_no);
      frendy::KramAscData get_asc(int mat_no);
  };
}

#endif //KRAM_OBJECT_H
