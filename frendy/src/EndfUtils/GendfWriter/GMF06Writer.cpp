#include "EndfUtils/GendfWriter/GMF06Writer.hpp"

using namespace frendy;

//constructor
GMF06Writer::GMF06Writer(void)
{
  clear();
}

//destructor
GMF06Writer::~GMF06Writer(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMF06Writer::clear()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> GMF06Writer::get_gendf_text_data(GMF06Parser& parser_obj)
{
  clear();

  GMFxxWriterBase wri_obj;
  return wri_obj.get_gendf_text_data(parser_obj.get_read_obj());
}

