#!/bin/csh

foreach SHELL ( MatxsParserTest.sh  MatxsWriterTest.sh  MatxsMergerTest.sh)
  set NAME = `basename ${SHELL} .sh`

  echo ${NAME}
  sh   ${SHELL}
  ./${NAME}.exe
end

sh MatxsCompareTest.sh


