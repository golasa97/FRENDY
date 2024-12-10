#include "EndfUtils/GendfWriter/GMF05Writer.hpp"

using namespace frendy;

//constructor
GMF05Writer::GMF05Writer(void)
{
  clear();
}

//destructor
GMF05Writer::~GMF05Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMF05Writer::clear()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> GMF05Writer::get_gendf_text_data(GMF05Parser& parser_obj)
{
  clear();

  GMFxxWriterBase wri_obj;
  return wri_obj.get_gendf_text_data(parser_obj.get_read_obj());
}

