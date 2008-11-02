baseDir=/home/cmstacuser/historicDQM/CMSSW_Releases/CMSSW_2_1_9/src
lockFile=$baseDir/lockFile


if [ ! $1 ] ;
    then echo "please provide the number of runs you would like to consider..."
         echo "./readDM_lastRuns_HDQM_CRON.sh 10 "
    exit 1
fi	



cd $baseDir
eval `scramv1 runtime -sh`

export ROOTSYS=/afs/cern.ch/cms/sw/slc4_ia32_gcc345/lcg/root/5.18.00a-cms12
export PATH=/afs/cern.ch/cms/sw/common:/afs/cern.ch/cms/sw/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/lcg/root/5.18.00a-cms12/bin:/home/cmstacuser/historicDQM/CMSSW_Releases/CMSSW_2_1_9/bin/slc4_ia32_gcc345:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/cms/cmssw/CMSSW_2_1_9/bin/slc4_ia32_gcc345:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/cms/pool/POOL_2_7_3-cms20/slc4_ia32_gcc345/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/cms/seal/SEAL_1_9_4-cms20/slc4_ia32_gcc345/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/qt/3.3.8-cms/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/xdaq/03.14.00-cms3/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/graphviz/2.16.1-cms/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/lcg/root/5.18.00a-cms12/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/oracle/10.2.0.3-cms/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/millepede/2.0-cms2/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/python/2.4.2-cms2/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/xrootd/20071116.0000b/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/valgrind/3.3.0-cms/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/sqlite/3.4.0-cms2/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/mysql/5.0.45/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/gmake/3.81/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/glimpse/4.18.5-cms/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/expat/2.0.0-cms/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/doxygen/1.5.4-cms/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/cms/dbs-client/DBS_1_1_2_pre1-cms/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/db4/4.4.20-cms/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/curl/7.15.3-cms/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/gccxml/0.7.0_20070615-cms/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/alpgen/212-cms/bin:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/gcc/3.4.5-cms/bin:/afs/cern.ch/cms/sw/common:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/lcg/SCRAMV1/V2_0_5/bin:/home/cmstacuser/bin:/home/cmstacuser/scripts:/usr/sue/bin:/afs/cern.ch/cms/bin/i386_linux26:/afs/cern.ch/cms/system/bin:/usr/local/bin:/usr/local/bin/X11:/usr/bin:/bin:/usr/bin/X11:/cern/pro/bin:/afs/cern.ch/cms/sw/bin:/afs/cern.ch/cms/utils:/usr/kerberos/bin:/usr/X11R6/bin
export LD_LIBRARY_PATH=/home/cmstacuser/historicDQM/CMSSW_Releases/CMSSW_2_1_9/lib/slc4_ia32_gcc345:/home/cmstacuser/historicDQM/CMSSW_Releases/CMSSW_2_1_9/external/slc4_ia32_gcc345/lib:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/cms/cmssw/CMSSW_2_1_9/lib/slc4_ia32_gcc345:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/cms/cmssw/CMSSW_2_1_9/external/slc4_ia32_gcc345/lib:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/boost/1.34.1-cms/lib:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/xrootd/20071116.0000b/lib:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/clhep/1.9.3.2-cms/lib:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/external/gcc/3.4.5-cms/lib:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/lcg/SCRAMV1/V2_0_5/lib:/afs/cern.ch/cms/sw/slc4_ia32_gcc345/lcg/root/5.18.00a-cms12/lib


echo $ROOTSYS
echo $PATH
echo $LD_LIBRARY_PATH



[ -e $lockFile ] && echo -e "lockFile " $lockFile "already exists. Process probably already running. If not remove the lockfile." && exit
touch $lockFile
echo -e "=============================================================="
echo " Creating lockFile :"
ls $lockFile
trap "rm -f $lockFile" exit



echo "=========================================================================="
echo " Extract the infos from the DB & do the trend plots for the last $1 runs  "  
echo "=========================================================================="

pwd
cat
$baseDir/DQM/SiStripHistoricInfoClient/test/TrendsWithIOVIterator/template_historicInspectorSelection_intervalOfRuns.cc | sed -e "s@nRuns@$1@g" > $baseDir/testHistoricInspectorSelection_intervalOfRuns.cc
cp $baseDir/DQM/SiStripHistoricInfoClient/test/TrendsWithIOVIterator/rootlogon.C $baseDir/.

root -l -b -q $baseDir/rootlogon.C
root -l -b -q $baseDir/testHistoricInspectorSelection_intervalOfRuns.cc

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
rm -f testHistoricInspectorSelection_intervalOfRuns.cc
rm -f $lockFile

echo "=========================================================================="
echo " Processing finished at $(date)  "  
echo "=========================================================================="
