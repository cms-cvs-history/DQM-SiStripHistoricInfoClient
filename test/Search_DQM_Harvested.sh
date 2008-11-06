#!/bin/sh
if [ [ ! $1 ] || [ ! $2 ] ];
    then echo "Please specify a run number and a trigger and run the command like: ./Search_DQM_Harvested.sh 67810 Cosmics-Commissioning08-PromptReco-v2-RECO-DQMHarvest-OfflineDQM"
    exit 1
fi
rm *root
numb=OfflineDQM-$1
pathToLast=/castor/cern.ch/cms/store/unmerged/dqm/
onDiskDir=~/HDQM/

for dir1 in `nsls /castor/cern.ch/cms/store/unmerged/dqm/ `;
do 
  if nsls /castor/cern.ch/cms/store/unmerged/dqm/$dir1 | grep $numb | grep $2> /dev/null; then 

      path1=/castor/cern.ch/cms/store/unmerged/dqm/$dir1
    echo "=========> Found run number $1 in directory /castor/cern.ch/cms/store/unmerged/dqm/$dir1" 
    echo "=========> The following files match the run number $1 in $2:"
    for path2 in `nsls $path1 | grep $numb | grep $2`;
      do 
      echo $path2
    done
  fi
  if [ $path2 ];
    then echo "=========> ROOT FILE CAN BE DOWNLOADED FROM: $path1/$path2/`nsls $path1/$path2`"
    pathToLast=$path1/$path2/`nsls $path1/$path2`
    rootFileName=`nsls $path1/$path2`
  fi
done
rfcp $pathToLast $onDiskDir/$rootFileName

cat template_getEvents.C | sed -e "s@DQM.root@$rootFileName@g" -e "s@xxxx@$1@g" > getEvents.C


if [ `ls DQM*.root` ]; then
root -l -b -q getEvents.C
fi
