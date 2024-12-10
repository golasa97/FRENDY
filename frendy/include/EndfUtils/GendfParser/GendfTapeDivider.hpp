#ifndef GENDF_TAPE_DIVIDER_H
#define GENDF_TAPE_DIVIDER_H

#include "EndfUtils/OtherUtils/EndfTapeDivider.hpp"
#include "EndfUtils/GendfParser/GMF01MT451Parser.hpp"

namespace frendy
{
  class GendfTapeDivider : public EndfTapeDivider
  {
    private:
      //Check temperature data at each material data
      void set_endf_data_each_temp(vector<vector<string> >& endf_data_each_mat);

    public:
      //constructor
      GendfTapeDivider(void);

      //destructor
      virtual ~GendfTapeDivider(void);
  }; 
}

#endif //GENDF_TAPE_DIVIDER_H
