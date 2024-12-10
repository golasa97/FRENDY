#include "CommonUtils/FileCommentRemover.hpp"

using namespace frendy;

FileCommentRemover::FileCommentRemover(void)
{
  clear();
}

FileCommentRemover::~FileCommentRemover(void)
{
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FileCommentRemover::remove_comment_data_from_file(string& original_file_name)
{
  clear();
  file_in = original_file_name;

  erase_comment();

  VectorClearer clr_obj;
  file_in.clear();
  clr_obj.clear_vec_array1_str(text_in);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<string> FileCommentRemover::remove_comment(string original_file_name)
{
  remove_comment_data_from_file(original_file_name);

  return text_out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FileCommentRemover::remove_comment(string original_file_name, string erased_file_name)
{
  remove_comment_data_from_file(original_file_name);

  file_out = erased_file_name;
  write_erased_text();
  clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

vector<vector<string> > FileCommentRemover::remove_comment_and_devide_text_data(string original_file_name)
{
  remove_comment_data_from_file(original_file_name);

  StringUtils str_util_obj;
  str_util_obj.set_text_data(text_out);

  return str_util_obj.get_div_string_vec_all();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FileCommentRemover::erase_comment()
{
  ifstream fin(file_in.c_str());

  if(!fin)
  {
    string class_name = "FileCommentRemover";
    string func_name  = "erase_comment()";
    vector<string> err_com;
    err_com.push_back("Original file can not be found.");
    err_com.push_back("Please check the file name or directory name.");
    string str_data = "  File name : " + file_in;
    err_com.push_back(str_data);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  VectorClearer clr_obj;
  clr_obj.clear_vec_array1_str(text_in);
  clr_obj.clear_vec_array1_str(text_out);

  int blank_no = 0;
  CommentRemover rc_obj;
  while(!fin.eof())
  {
    string line_data;
    getline(fin, line_data);
    text_in.push_back(line_data);

    if( line_data.size() > 0 )
    {
      blank_no = 0;
    }
    else
    {
      blank_no++;

      if( blank_no > 100000000 )
      {
        string class_name = "FileCommentRemover";
        string func_name  = "erase_comment()";

        string str_data   = "  file name : " + file_in;

        vector<string> err_com;
        err_com.push_back("A huge number of blank line data is found.");
        err_com.push_back("The file name may not be the directory name.");
        err_com.push_back("Please check the file name is collect or not.");
        err_com.push_back("");
        err_com.push_back(str_data);
        err_com.push_back("");
        err_com.push_back("FRENDY recognizes that after // is comment line.");
        err_com.push_back("Please check that the file name contains // or not.");

        err_obj.output_runtime_error(class_name, func_name, err_com);
      }
    }
    line_data.clear();
  }
  fin.close();
    
  text_out = rc_obj.remove_comment(text_in);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FileCommentRemover::write_erased_text()
{
  ofstream fout(file_out.c_str());

  if(!fout)
  {
    string class_name = "FileCommentRemover";
    string func_name  = "write_erased_text()";
    vector<string> err_com;
    err_com.push_back("Output file which the comment data is removed can not open.");
    err_com.push_back("Please check the file name, directory name or access authority.");
    string str_data = "  File name : " + file_out;
    err_com.push_back(str_data);
    err_obj.output_runtime_error(class_name, func_name, err_com);
  }

  int i_max = static_cast<int>(text_out.size());
  for(int i=0; i<i_max-1; i++)
  {
    fout << text_out[i] << endl;
  }
  fout << text_out[i_max-1];

  fout.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void FileCommentRemover::clear()
{
  file_in.clear();
  file_out.clear();

  VectorClearer clr_obj;
  clr_obj.clear_vec_array1_str(text_in);
  clr_obj.clear_vec_array1_str(text_out);
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void FileCommentRemover::devide_full_path(string full_path,
                                          string& file_name, string& path_name, string& suffix_name)
{
  string separation_record = "/";
#ifdef _WIN32
  separation_record = "\/";
#endif

  int char_no  = static_cast<int>(full_path.length());
  int dir_end  = static_cast<int>(full_path.find_last_of(separation_record));
  int name_end = static_cast<int>(full_path.find_last_of("."));

  if( name_end < dir_end )
  {
     name_end = -1;
  }

  int separation_no = 1; //"/"
#ifdef _WIN32
  separation_no = 2; //"\/"
#endif

  if( dir_end > 0 )
  {
    path_name = full_path.substr(0, dir_end);
    file_name = full_path.substr(dir_end+separation_no, char_no - dir_end - separation_no);
  }
  else
  {
    path_name = "";
    file_name = full_path;
  }

  if( name_end >= 0 )
  {
    suffix_name = full_path.substr(name_end+1, char_no - name_end - 1);
  }
  else
  {
    suffix_name = "";
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string FileCommentRemover::get_file_name(string full_path)
{
  string file_name, path_name, suffix_name;
  devide_full_path(full_path, file_name, path_name, suffix_name);

  return file_name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string FileCommentRemover::get_path_name(string full_path)
{
  string file_name, path_name, suffix_name;
  devide_full_path(full_path, file_name, path_name, suffix_name);

  return path_name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

string FileCommentRemover::get_suffix_name(string full_path)
{
  string file_name, path_name, suffix_name;
  devide_full_path(full_path, file_name, path_name, suffix_name);

  return suffix_name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

