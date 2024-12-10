#ifndef GROUP_STRUCTURE_GAMMA_H
#define GROUP_STRUCTURE_GAMMA_H

#include "CommonUtils/ErrorManager.hpp"

namespace frendy
{
  class GroupStructureGamma
  {
    private:
      frendy::ErrorManager err_obj;

#ifdef DEBUG_MODE
  public:
#endif
      vector<Real> get_eg2();
      vector<Real> get_eg3();
      vector<Real> get_eg4();
      vector<Real> get_eg5();
      vector<Real> get_eg6();
      vector<Real> get_eg7();
      vector<Real> get_eg8();
      vector<Real> get_eg9();
      vector<Real> get_eg10();

    public:
      //constructor
      GroupStructureGamma(void);

      //destructor
      virtual ~GroupStructureGamma(void);

      void clear();

      vector<Real> get_group_structure(int igg);
  }; 
}

#endif //GROUP_STRUCTURE_GAMMA_H
