#bin/bash
settings=('sdsc_mt')

TIMES=5
START=1
END=64

PREFIX="Submitted batch job "

PRE=$1

for((k=$START; k<=$END; k*=2))
do
  for setting in ${settings[@]}
  do
    echo $setting
    cd $setting
    for((i=1; i<=$TIMES; i++))
    do
      if [ $PRE == "none" ]
      then
        PRE=$(sbatch run.$k.sub)
        PRE=${PRE#$PREFIX}        
      else
        PRE=$(sbatch --dependency=afterany:$PRE run.$k.sub)
        PRE=${PRE#$PREFIX}
      fi
      echo $PRE
    done
    cd ..
  done
done