#!/bin/bash

NATOMS=$1
rm ./.tmp*

for TEMP in 425 475 525 575 625 675 725 775 825 875 925 975
do
  rm -r ./${TEMP}
  mkdir ./${TEMP}
  for EVERY in 1 10 20
  do
    SECTIONLENGTH=$(((9+${NATOMS})*${EVERY}))
    awk -v var="${SECTIONLENGTH}" '{if(NR%var == var - 1 || NR%var == 0) print;}' ./1_at_AuSi_${TEMP}.lammpstrj > ./.tmp_${EVERY} 
    for ((ATOM=1; ATOM <= ${NATOMS}; ATOM++ ))
    do
      awk -v natoms="${NATOMS}" -v atom="${ATOM}" '{if(atom!=natoms){ if(NR%natoms==atom) print; } if(atom==natoms){{ if(NR%natoms==0) print; }}}' ./.tmp_${EVERY} > ./.tmp_${EVERY}_${ATOM} 
      echo "./.tmp_${EVERY}_${ATOM} " >> ./.tmp_${EVERY}_names 
    done
    awk 'BEGIN { ORS = " " } { print }' ./.tmp_${EVERY}_names > ./.tmp_tmp
    mv ./.tmp_tmp ./.tmp_${EVERY}_names
    FILENAMES=$(cat ./.tmp_${EVERY}_names)
    rm ./.tmp_${EVERY}_names
    paste ${FILENAMES} > ${TEMP}/${TEMP}_${EVERY}.out
  done
done
