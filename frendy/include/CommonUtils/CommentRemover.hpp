#ifndef COMMENT_REMOVER_H
#define COMMENT_REMOVER_H

#include "VectorClearer.hpp"
#include "ErrorManager.hpp"

namespace frendy
{
  class CommentRemover
  {
    private:
      vector<string>  text_in;
      vector<string>  text_out;

      frendy::ErrorManager    err_obj;

      void erase_comment();
      int  delete_text(int& line_no);

      void erase_blank_line();

    public:
      //clear all data
      void clear();  

      //constructor
      CommentRemover(void);

      //destructor
      virtual ~CommentRemover(void);

      vector<string> remove_comment(vector<string>& original_text);
  }; 
}

#endif //COMMENT_REMOVER_H
