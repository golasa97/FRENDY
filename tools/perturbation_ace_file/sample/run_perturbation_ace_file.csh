#!/bin/csh

set PWD     = `pwd`
set SRC_DIR = ../
set EXE     = perturbation_ace_file.exe

set INP     = perturbation_list.inp
set ACE     = 1001.710nc

cd ${SRC_DIR}
make
cd ${PWD}

cp -rpf ../../make_perturbation_factor/sample/output/1001 ./inp


set LOG = result.log
echo "${EXE}  ${ACE}  ${INP}"      > ${LOG}
echo ""                           >> ${LOG}
${SRC_DIR}/${EXE}  ${ACE}  ${INP} >> ${LOG}

mkdir -p       ./output
cp    -rf  0*  ./output/
rm    -rf  0*

