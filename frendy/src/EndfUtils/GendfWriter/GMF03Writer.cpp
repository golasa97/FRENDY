#include "EndfUtils/GendfWriter/GMF03Writer.hpp"

using namespace frendy;

//constructor
GMF03Writer::GMF03Writer(void)
{
  clear();
}

//destructor
GMF03Writer::~GMF03Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMF03Writer::clear()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> GMF03Writer::get_gendf_text_data(GMF03Parser& parser_obj)
{
  clear();

  GMFxxWriterBase wri_obj;
  return wri_obj.get_gendf_text_data(parser_obj.get_read_obj());
}

