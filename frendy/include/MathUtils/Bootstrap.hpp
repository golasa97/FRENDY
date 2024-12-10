#ifndef BOOT_STRAP
#define BOOT_STRAP

#include "MathUtils/RandomNumberGenerator.hpp"

namespace frendy
{
  class Bootstrap
  {
    private:
      frendy::RandomNumberGenerator rand_obj;

#ifdef DEBUG_MODE
  public:
#endif

    public:
      //constructor
      Bootstrap(void);

      //destructor
      virtual ~Bootstrap(void);

      void clear();

      void calc_average(vector<vector<Real8> >& result_data, vector<Real8>& ave_data);
      void calc_average(vector<Real8>& result_data, Real8& ave_data);
      void calc_average_sq(vector<vector<Real8> >& result_data, vector<Real8>& ave_data);
      void calc_average_sq(vector<Real8>& result_data, Real8& ave_data);

      void calc_average_and_error(vector<vector<Real8> >& result_data,
                                  vector<Real8>& ave_data, vector<Real8>& err_data);
      void calc_average_and_error(vector<Real8>& result_data,
                                  Real8& ave_data, Real8& err_data);

      //clt : central limit theorem
      void calc_average_and_error_clt_with_ave_and_max(vector<vector<Real8> >& result_data,
                                                       vector<Real8>& ave_data, vector<Real8>& err_data,
                                                       Real8& err_ave, Real8& err_max);
      void calc_average_and_error_clt(vector<vector<Real8> >& result_data,
                                      vector<Real8>& ave_data, vector<Real8>& err_data);
      void calc_average_and_error_clt(vector<Real8>& result_data,
                                      Real8& ave_data, Real8& err_data);

      void calc_average_and_max(vector<Real8> result_data,
                                Real8& ave_data, Real8& max_data);

      //For bootstrap method
      vector<vector<Real8> > get_random_sample(vector<vector<Real8> >& sample_ori);
      int                    get_random_pos(int rand_no);

      void calc_bootstrap(int sample_no, vector<vector<Real8> >& sample_ori,
                          vector<Real8>& ave_data, vector<Real8>& err_data);
      void calc_bootstrap_with_ave_and_max(int sample_no, vector<vector<Real8> >& sample_ori,
                                           vector<Real8>& ave_data, vector<Real8>& err_data,
                                           Real8& err_ave, Real8& err_max);

      //For jack knife method
      vector<vector<Real8> > get_jack_knife_sample
                               (vector<vector<Real8> >& sample_ori, int pos);

      void calc_jack_knife(vector<vector<Real8> >& sample_ori,
                           vector<Real8>& ave_data, vector<Real8>& err_data);
      void calc_jack_knife_with_ave_and_max(vector<vector<Real8> >& sample_ori,
                                            vector<Real8>& ave_data, vector<Real8>& err_data,
                                            Real8& err_ave, Real8& err_max);

      //Random seed
      void  set_seed(Integer seed_val);
      void  set_seed_time();
      Real8 get_seed();
  };
}

#endif // BOOT_STRAP
