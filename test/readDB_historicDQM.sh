baseDir=/afs/cern.ch/user/a/alebihan/CMSSW_2_1_9/src
lockFile=$baseDir/lockFile



if [ ! $1 ] ;
    then echo "please provide the number of runs you would like to consider..."
         echo "./readDM_historicDQM.sh 10 "
    exit 1
fi	



cd $baseDir
eval `scramv1 runtime -sh`



[ -e $lockFile ] && echo -e "lockFile " $lockFile "already exists. Process probably already running. If not remove the lockfile." && exit
touch $lockFile
echo -e "=============================================================="
echo " Creating lockFile :"
ls $lockFile
trap "rm -f $lockFile" exit



echo "=========================================================================="
echo " Extract the infos from the DB & do the trend plots for the last $1 runs  "  
echo "=========================================================================="

cat $baseDir/DQM/SiStripHistoricInfoClient/test/TrendsWithIOVIterator/template_testHistoricInspectorSelection.cc | sed -e "s@nRuns@$1@g" > $baseDir/testHistoricInspectorSelection.cc

root -l -b -q $baseDir/testHistoricInspectorSelection.cc

if [ `ls historicDQM.root` ]; then
root -l -b -q DQM/SiStripHistoricInfoClient/test/TrendsWithIOVIterator/testGraphAnalysis.cc
fi



rm -f testHistoricInspectorSelection.cc
rm -f $lockFile
