#include "EndfUtils/GendfParser/GMF16Parser.hpp"

using namespace frendy;

//constructor
GMF16Parser::GMF16Parser(void)
{
  clear();
}

//destructor
GMF16Parser::~GMF16Parser(void)
{ 
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMF16Parser::store_data() 
{
  read_obj.clear();
  read_obj.set_mf_no(mf_no);

  read_obj.set_text(text);

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMF16Parser::clear()
{
  read_obj.clear();

  VectorClearer clr_vec;
  clr_vec.clear_vec_array1_str(text);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void GMF16Parser::set_text(vector<string> text_data)
{
  clear();

  text = text_data;
  store_data();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string>  GMF16Parser::get_text()
{
  return read_obj.get_text();
}

GMFxxParserBase  GMF16Parser::get_read_obj()
{
  read_obj.set_mf_no(mf_no);
  return read_obj;
}

Integer         GMF16Parser::get_mat_no()
{
  return read_obj.get_mat_no();
}

Integer         GMF16Parser::get_mt_no()
{
  return read_obj.get_mt_no();
}

//Getter at line No.01
Real            GMF16Parser::get_ZA()
{
  return read_obj.get_ZA();
}

Real            GMF16Parser::get_AWR()
{
  return read_obj.get_AWR();
}

Integer         GMF16Parser::get_NL()
{
  return read_obj.get_NL();
}

Integer         GMF16Parser::get_NSIGZ()
{
  return read_obj.get_NSIGZ();
}

Integer         GMF16Parser::get_LR()
{
  return read_obj.get_LR();
}

Integer         GMF16Parser::get_NGN()
{
  return read_obj.get_NGN();
}

//Getter at line No.02
Real            GMF16Parser::get_TEMP()
{
  return read_obj.get_TEMP();
}

vector<int>     GMF16Parser::get_NG2()
{
  return read_obj.get_NG2();
}

vector<int>     GMF16Parser::get_IG2LO()
{
  return read_obj.get_IG2LO();
}

vector<int>     GMF16Parser::get_IG()
{
  return read_obj.get_IG();
}

vector<vector<vector<Real> > > GMF16Parser::get_FLUX()
{
  return read_obj.get_DATA1();
}

vector<vector<vector<vector<Real> > > > GMF16Parser::get_MATRIX()
{
  return read_obj.get_DATA2_NG2();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

//Setter
void GMF16Parser::set_read_obj(GMFxxParserBase read_gendf_obj)
{
  clear();
  read_obj = read_gendf_obj;
  read_obj.set_mf_no(mf_no);
}

void GMF16Parser::set_mat_no(Integer int_no)
{
  read_obj.set_mat_no(int_no);
}

void GMF16Parser::set_mt_no(Integer int_no)
{
  read_obj.set_mt_no(int_no);
}

//line No.01
void GMF16Parser::set_ZA(Real real_data)
{
  read_obj.set_ZA(real_data);
}

void GMF16Parser::set_AWR(Real real_data)
{
  read_obj.set_AWR(real_data);
}

void GMF16Parser::set_NL(Integer int_data)
{
  read_obj.set_NL(int_data);
}
void GMF16Parser::set_NSIGZ(Integer int_data)
{
  read_obj.set_NSIGZ(int_data);
}

void GMF16Parser::set_LR(Integer int_data)
{
  read_obj.set_LR(int_data);
}

void GMF16Parser::set_NGN(Integer int_data)
{
  read_obj.set_NGN(int_data);
}

//line No.02
void GMF16Parser::set_TEMP(Real real_data)
{
  read_obj.set_TEMP(real_data);
}

void GMF16Parser::set_NG2(vector<int> int_vec)
{
  read_obj.set_NG2(int_vec);
}

void GMF16Parser::set_IG2LO(vector<int> int_vec)
{
  read_obj.set_IG2LO(int_vec);
}

void GMF16Parser::set_IG(vector<int> int_vec)
{
  read_obj.set_IG(int_vec);
}

void GMF16Parser::set_FLUX(vector<vector<vector<Real> > > real_vec)
{
  read_obj.set_DATA1(real_vec);
}

void GMF16Parser::set_MATRIX(vector<vector<vector<vector<Real> > > > real_vec)
{
  read_obj.set_DATA2_NG2(real_vec);
}

