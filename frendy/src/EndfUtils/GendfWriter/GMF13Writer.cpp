#include "EndfUtils/GendfWriter/GMF13Writer.hpp"

using namespace frendy;

//constructor
GMF13Writer::GMF13Writer(void)
{
  clear();
}

//destructor
GMF13Writer::~GMF13Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMF13Writer::clear()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> GMF13Writer::get_gendf_text_data(GMF13Parser& parser_obj)
{
  clear();

  GMFxxWriterBase wri_obj;
  return wri_obj.get_gendf_text_data(parser_obj.get_read_obj());
}

