#!/bin/csh

set PWD = `pwd`

foreach CASE ( read_errorr_data          make_xsdir_list \
               perturbation_ace_file     make_perturbation_factor \
               frendy_parallel )
  echo ${CASE}
  cd ${PWD}/${CASE}
  make
end

