#include "CommonUtils/CommentRemover.hpp"

using namespace frendy;

CommentRemover::CommentRemover(void)
{
  clear();
}

CommentRemover::~CommentRemover(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> CommentRemover::remove_comment(vector<string>& original_text)
{
  clear();
  text_in  = original_text;

  erase_comment();

  text_in = text_out;

  VectorClearer clr_obj;
  clr_obj.clear_vec_array1_str(text_out);

  erase_blank_line();

  return text_out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CommentRemover::erase_comment()
{
  for(int i=0; i<static_cast<int>(text_in.size()); i++)
  {
    int slash_no    = static_cast<int>(text_in[i].find("//",0));
    int com_out_sta = static_cast<int>(text_in[i].find("/*",0));

    while( slash_no >= 0 || com_out_sta >= 0 )
    {
      if( slash_no < 0 && com_out_sta < 0 )
      {
        break;
      }

      if( (slash_no>=0 && slash_no<com_out_sta) || (slash_no>=0 && com_out_sta<0) )
      {
        text_in[i].erase(slash_no);
      }
      else if( (com_out_sta>=0 && com_out_sta<slash_no) || (com_out_sta>=0 && slash_no<0) )
      {
        int com_out_end = static_cast<int>(text_in[i].find("*/",0)) - com_out_sta;

        //When the /* - */ is exist same line.
        if( com_out_end >= 0 )
        {
          text_in[i].erase(com_out_sta, com_out_end+2); 
        }
        else
        {
          text_in[i].erase(com_out_sta);
          text_out.push_back(text_in[i]);

          delete_text(i);
        }
      }
      slash_no    = static_cast<int>(text_in[i].find("//",0));
      com_out_sta = static_cast<int>(text_in[i].find("/*",0));
    }
    text_out.push_back(text_in[i]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int CommentRemover::delete_text(int& line_no)
{
  int i_sta = line_no+1;
  for(int i=i_sta; i<static_cast<int>(text_in.size()); i++)
  {
    int com_out_end = static_cast<int>(text_in[i].find("*/",0));
    if( com_out_end >= 0 )
    {
      text_in[i].erase(0, com_out_end+2);
      line_no = i;
      return 0;
    }
  }

  string class_name = "CommentRemover";
  string func_name  = "delete_text(int& line_no)";

  vector<string> err_com;
  err_com.push_back("There is no end of comment out mark */.");

  err_obj.output_runtime_error(class_name, func_name, err_com);
  return -1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CommentRemover::erase_blank_line()
{
  for(int i=0; i<static_cast<int>(text_in.size()); i++)
  {
    while( text_in[i].find(" ",0)==0 || text_in[i].find("\t",0)==0 )
    {
      text_in[i].erase(0, 1);
    }

    if(text_in[i].size() > 0)
    {
      text_out.push_back(text_in[i]);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void CommentRemover::clear()
{
  VectorClearer clr_obj;

  clr_obj.clear_vec_array1_str(text_in);
  clr_obj.clear_vec_array1_str(text_out);
}

