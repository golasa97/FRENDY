#!/bin/csh

set PWD     = `pwd`
set SRC_DIR = ../
set EXE     = make_perturbation_factor.exe

set INP     = sample.inp

if( ! -e ../Eigen ) then
  echo "There is no Eigen library."
  echo "This tool requres Eigen library and source directory must be set in tools/make_perturbation_factor."
  echo "Please download Eingen library and/or copy Eigen library in tools/make_perturbation_factor."
endif

cd ${SRC_DIR}
make
cd ${PWD}


set LOG = result.log
echo "${EXE}  ${INP}"      > ${LOG}
echo ""                   >> ${LOG}
${SRC_DIR}/${EXE}  ${INP} >> ${LOG}

mkdir -p          ./output
cp    -rf ./1001  ./output
rm    -rf ./1001

