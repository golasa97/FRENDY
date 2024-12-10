#ifndef READ_RECONR_INPUT_H
#define READ_RECONR_INPUT_H

#include <boost/algorithm/string.hpp>

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "NjoyUtils/NjoyInputReader.hpp"

namespace frendy
{
  class ReconrInputReader
  {
    private:
      frendy::NjoyInputReader rn_obj;
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;

      string                  input_reconr;
      string                  endf_name, pendf_name, label_name;
      vector<Integer>         mat, ncards, ngrid;
      vector<Real8>           err, err_max, err_int, tempr;
      vector<vector<string> > cards;
      vector<vector<Real8> >  grid; 

      void read_file_name(ifstream& fin);
      void read_mat_data(ifstream& fin);
      void read_err_data(ifstream& fin, int& mat_no);
      vector<string> read_cards_data(ifstream& fin, int& mat_no);
      vector<Real8>  read_grid_data(ifstream& fin, int& mat_no);

    public:
      //constructor
      ReconrInputReader(void);

      //destructor
      virtual ~ReconrInputReader(void);

      //read input file for reconr
      void read_input(string file_name);
      void read_input(string file_name, int line_no);

      void clear();

      string                  get_input_reconr();
      string                  get_endf_name();
      string                  get_pendf_name();
      string                  get_label_name();
      vector<Integer>         get_mat();
      vector<Integer>         get_ncards();
      vector<Integer>         get_ngrid();
      vector<Real8>           get_err();
      vector<Real8>           get_err_max();
      vector<Real8>           get_err_int();
      vector<Real8>           get_tempr();
      vector<vector<string> > get_cards();
      vector<vector<Real8> >  get_grid();
  }; 
}

#endif //READ_RECONR_INPUT_H
