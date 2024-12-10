#include "EndfUtils/GendfWriter/GMF16Writer.hpp"

using namespace frendy;

//constructor
GMF16Writer::GMF16Writer(void)
{
  clear();
}

//destructor
GMF16Writer::~GMF16Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMF16Writer::clear()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> GMF16Writer::get_gendf_text_data(GMF16Parser& parser_obj)
{
  clear();

  GMFxxWriterBase wri_obj;
  return wri_obj.get_gendf_text_data(parser_obj.get_read_obj());
}

