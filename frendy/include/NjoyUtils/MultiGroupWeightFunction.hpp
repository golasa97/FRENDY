#ifndef MULTI_GROUP_WEIGHT_FUNCTION_H
#define MULTI_GROUP_WEIGHT_FUNCTION_H

#include "CommonUtils/ErrorManager.hpp"
#include "TabUtils/LinearizeTabData.hpp"

namespace frendy
{
  class MultiGroupWeightFunction
  {
    private:
      frendy::ErrorManager err_obj;

#ifdef DEBUG_MODE
  public:
#endif
      void get_w6(int iwt, vector<Real>& e_vec, vector<Real>& w_vec, Real temp, Real e_min, Real e_max);
      void get_w11(int iwt, vector<Real>& e_vec, vector<Real>& w_vec, Real temp, Real e_min, Real e_max);

      void get_w1(vector<Integer>& nbt_vec, vector<Integer>& int_vec, vector<Real>& e1, vector<Real>& w1);
      void get_w8(vector<Integer>& nbt_vec, vector<Integer>& int_vec, vector<Real>& e8, vector<Real>& w8);
      void get_w9(vector<Integer>& nbt_vec, vector<Integer>& int_vec, vector<Real>& e9, vector<Real>& w9);

      void linearize_tab_data(int iwt, vector<Real>& e_vec, vector<Real>& w_vec);

    public:
      //constructor
      MultiGroupWeightFunction(void);

      //destructor
      virtual ~MultiGroupWeightFunction(void);

      void clear();

      void get_weighting_function(int iwt, Real temp, vector<Real>& e_vec, vector<Real>& w_vec);
  }; 
}

#endif //MULTI_GROUP_WEIGHT_FUNCTION_H
