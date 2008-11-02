baseDir=/afs/cern.ch/user/a/alebihan/CMSSW_2_1_9/src
lockFile=$baseDir/lockFile



if [ ! $1 ] ;
    then echo "please provide the number of the week you are considering, the first run number, the last run number"
         echo "./readDB_intervalOfRuns_HDQM.sh 42 65941 66746 "
       # echo "./readDB_intervalOfRuns_HDQM.sh 43 66748 67647 "
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

cat $baseDir/DQM/SiStripHistoricInfoClient/test/TrendsWithIOVIterator/template_historicInspectorSelection_intervalOfRuns.cc | sed -e "s@firstRun@$2@g" | sed -e "s@lastRun@$3@g" > $baseDir/testHistoricInspectorSelection_intervalOfRuns.cc
cp $baseDir/DQM/SiStripHistoricInfoClient/test/TrendsWithIOVIterator/rootlogon.C $baseDir/.
root -l -b -q $baseDir/rootlogon.C
root -l -b -q $baseDir/testHistoricInspectorSelection_intervalOfRuns.cc

if [ `ls historicDQM.root` ]; then
root -l -b -q DQM/SiStripHistoricInfoClient/test/TrendsWithIOVIterator/testGraphAnalysis.cc
fi

rm -rf week_$1_CRAFT
mkdir week_$1_CRAFT
mkdir week_$1_CRAFT/details
mv *gif week_$1_CRAFT/details/
mv week_$1_CRAFT/details/*superimposed* week_$1_CRAFT/
mv week_$1_CRAFT/details/number_of*gif week_$1_CRAFT/
mv week_$1_CRAFT/details/mean_number_of_tracks_per_event.gif week_$1_CRAFT/
mv week_$1_CRAFT/details/*integrated*gif week_$1_CRAFT/
mv *.C week_$1_CRAFT/details/.
mv historicDQM.root week_$1_CRAFT/details/.


cp $baseDir/DQM/SiStripHistoricInfoClient/test/diow.pl week_$1_CRAFT/.
cd week_$1_CRAFT
./diow.pl
cp $baseDir/DQM/SiStripHistoricInfoClient/test/index.html .

cd ..

rm -f testHistoricInspectorSelection_intervalOfRuns.cc
rm -f $lockFile
