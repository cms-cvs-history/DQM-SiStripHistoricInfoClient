baseDir=/afs/cern.ch/user/a/alebihan/CMSSW_2_1_9/src
lockFile=$baseDir/lockFile



if [ ! $1 ] ;
    then echo "please provide the number of runs you would like to consider..."
         echo "./readDB_lastRuns_HDQM.sh 10 "
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

cat $baseDir/DQM/SiStripHistoricInfoClient/test/TrendsWithIOVIterator/template_historicInspectorSelection_lastRuns.cc | sed -e "s@nRuns@$1@g" > $baseDir/testHistoricInspectorSelection_lastRuns.cc

root -l -b -q $baseDir/testHistoricInspectorSelection_lastRuns.cc

if [ `ls historicDQM.root` ]; then
root -l -b -q DQM/SiStripHistoricInfoClient/test/TrendsWithIOVIterator/testGraphAnalysis.cc
fi

rm -rf CRAFT_last_$1_runs
mkdir CRAFT_last_$1_runs
mkdir CRAFT_last_$1_runs/details
mv *gif CRAFT_last_$1_runs/details/
mv CRAFT_last_$1_runs/details/*superimposed* CRAFT_last_$1_runs/
mv CRAFT_last_$1_runs/details/number_of*gif CRAFT_last_$1_runs/
mv CRAFT_last_$1_runs/details/mean_number_of_tracks_per_event.gif CRAFT_last_$1_runs/
mv CRAFT_last_$1_runs/details/*integrated*gif CRAFT_last_$1_runs/
mv *.C CRAFT_last_$1_runs/details/.
mv historicDQM.root CRAFT_last_$1_runs/details/.

cp $baseDir/DQM/SiStripHistoricInfoClient/test/diow.pl CRAFT_last_$1_runs/.
cd CRAFT_last_$1_runs
./diow.pl
cp $baseDir/DQM/SiStripHistoricInfoClient/test/index.html .

cd ..

rm -f testHistoricInspectorSelection_lastRuns.cc
rm -f $lockFile
