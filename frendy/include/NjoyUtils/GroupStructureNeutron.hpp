#ifndef GROUP_STRUCTURE_NEUTRON_H
#define GROUP_STRUCTURE_NEUTRON_H

#include "CommonUtils/ErrorManager.hpp"

namespace frendy
{
  class GroupStructureNeutron
  {
    private:
      frendy::ErrorManager err_obj;

      vector<Real> set_sandii_structure(int ng);

#ifdef DEBUG_MODE
  public:
#endif
      vector<Real> get_gl2();
      vector<Real> get_eg3();
      vector<Real> get_gl4();
      vector<Real> get_gl5();
      vector<Real> get_eg6();
      vector<Real> get_eg9();
      vector<Real> get_eg10a();
      vector<Real> get_eg10b();
      vector<Real> get_eg11();
      vector<Real> get_deltl();
      vector<int>  get_ndelta();
      vector<Real> get_u80();
      vector<int>  get_ig14();
      vector<Real> get_gl14();
      vector<Real> get_eg16();
      vector<Real> get_eg17();
      vector<Real> get_eg18();
      vector<Real> get_eg19();
      vector<Real> get_eg20();
      vector<Real> get_eg21();
      vector<Real> get_eg22();
      vector<Real> get_eg23();
      vector<Real> get_eg24();
      vector<Real> get_eg25();
      vector<Real> get_eg26();
      vector<Real> get_eg27();
      vector<Real> get_eg28();
      vector<Real> get_eg29();
      vector<Real> get_eg30();
      vector<Real> get_eg31();
      vector<Real> get_eg32();
      vector<Real> get_eg33();
      vector<Real> get_eg618();
      vector<Real> get_vit199();
      vector<Real> get_vit200();
      vector<Real> get_srac107();
      vector<Real> get_srac108();
      vector<Real> get_srac200();

    public:
      //constructor
      GroupStructureNeutron(void);

      //destructor
      virtual ~GroupStructureNeutron(void);

      void clear();

      vector<Real> get_group_structure(int ign);
  }; 
}

#endif //GROUP_STRUCTURE_NEUTRON_H
