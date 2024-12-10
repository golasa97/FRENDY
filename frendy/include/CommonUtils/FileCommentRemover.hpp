#ifndef FILE_COMMENT_REMOVER_H
#define FILE_COMMENT_REMOVER_H

#include "CommentRemover.hpp"
#include "StringUtils.hpp"

namespace frendy
{
  class FileCommentRemover
  {
    private:
      frendy::ErrorManager err_obj;

      string  file_in;
      string  file_out;

      vector<string> text_in;
      vector<string> text_out;

      void remove_comment_data_from_file(string& original_file_name);

      void erase_comment();
      void write_erased_text();

    public:
      //clear all data
      void clear();  

      //constructor
      FileCommentRemover(void);

      //destructor
      virtual ~FileCommentRemover(void);

      vector<string> remove_comment(string original_file_name);
      void           remove_comment(string original_file_name, string erased_file_name);

      vector<vector<string> > remove_comment_and_devide_text_data(string original_file_name);

      void devide_full_path(string full_path, string& file_name, string& path_name, string& suffix_name);
      string get_file_name(string full_path);
      string get_path_name(string full_path);
      string get_suffix_name(string full_path);
  }; 
}

#endif //FILE_COMMENT_REMOVER_H
