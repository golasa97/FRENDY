#ifndef READ_MATXSR_INPUT_H
#define READ_MATXSR_INPUT_H

#include <boost/algorithm/string.hpp>

#include "CommonUtils/VectorClearer.hpp"
#include "EndfUtils/EndfFileReader/EndfUtils.hpp"
#include "NjoyUtils/NjoyInputReader.hpp"

namespace frendy
{
  class MatxsrInputReader
  {
    private:
      frendy::NjoyInputReader rn_obj;
      frendy::ErrorManager    err_obj;
      frendy::VectorClearer   clr_obj;

      string                  input_matxsr;

      //Card 1
      string                  group_file_name, gamin_file_name, matxs_name,
                              proton_name, deuteron_name, triton_name, he_name, alpha_name;

      //Card 2
      Integer                 ivers;
      string                  huse;

      //Card 3
      Integer                 npart, ntype, nholl, nmat;

      //Card 4, 5
      vector<string>          hsetid, hpart;

      //Card 6
      vector<Integer>         ngrp;

      //Card 7, 8, 9
      vector<string>          htype;
      vector<Integer>         jinp, joutp;

      //Card 10
      vector<string>          hmat;
      vector<Integer>         matno, matgg;

      void read_file_name(ifstream& fin);
      void read_cards_two_and_three(ifstream& fin);
      void read_cards_four_to_nine(ifstream& fin);
      void read_card_ten(ifstream& fin);

    public:
      //constructor
      MatxsrInputReader(void);

      //destructor
      virtual ~MatxsrInputReader(void);

      //read input file for matxsr
      void read_input(string file_name);
      void read_input(string file_name, int line_no);

      void clear();

      string          get_input_matxsr();

      string          get_group_file_name();
      string          get_gamin_file_name();
      string          get_matxs_name();
      string          get_proton_name();
      string          get_deuteron_name();
      string          get_triton_name();
      string          get_he_name();
      string          get_alpha_name();
      Integer         get_ivers();
      string          get_huse();
      Integer         get_npart();
      Integer         get_ntype();
      Integer         get_nholl();
      Integer         get_nmat();
      vector<string>  get_hsetid();
      vector<string>  get_hpart();
      vector<Integer> get_ngrp();
      vector<string>  get_htype();
      vector<Integer> get_jinp();
      vector<Integer> get_joutp();
      vector<string>  get_hmat();
      vector<Integer> get_matno();
      vector<Integer> get_matgg();
  }; 
}

#endif //READ_MATXSR_INPUT_H
