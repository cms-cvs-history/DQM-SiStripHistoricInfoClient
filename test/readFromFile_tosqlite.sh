#!/bin/bash 
#
# Configuration for cmstac12 ...
#
# How to run : ./readFromFile.sh /home/cmstacuser/HistoricDQM
#
# Don't forget to modify ROOTFILE_DIR in DQM/SiStripHistoricInfoClient/readFromFile.cfg according to $1 !   (TO BE FIXED !)
#



echo "=============================================================="
echo " Run readFromFile.cfg over all root files located in " $1  ...
echo "=============================================================="
echo "  "


sqliteFile=historicDQM.db
[ -e $sqliteFile ] && rm $sqliteFile && echo " removed existing database $sqliteFile"


path=$CMSSW_BASE/src/CondTools/SiStrip/scripts
if [ ! -e $path ] ;then
    path=$CMSSW_RELEASE_BASE/src/CondTools/SiStrip/scripts
    if [ ! -e $path ]; then
	echo -e "Error: CondTools/SiStrip/scripts doesn't exist\nplease install that package\nexit"
	exit 1
    fi
fi

$path/CreatingTables.sh sqlite_file:$sqliteFile a b


rootFileList=(`ls -ltr $1 |  awk '{print $9}' | grep ".root"`)
k=0
ListSize=${#rootFileList[*]}
echo ListSize $ListSize

eval `scramv1 runtime -sh`

mkdir -p log
while 
     [ "$k" -lt "$ListSize" ]
do
     rootFile=${rootFileList[$k]}
     runNumberList[$k]=${rootFile:17:5}
     destinationFile=readFromFile_${runNumberList[$k]}.log
     echo "   processing " $1/$rootFile " for runNr " ${runNumberList[$k]}
     
     cat $CMSSW_BASE/src/DQM/SiStripHistoricInfoClient/test/readFromFile.cfg | sed -e "s@theRunNr@${runNumberList[$k]}@g" -e "s@theFileName@$rootFile@g" -e "s@theDirName@$1@" -e "s@destinationFile@$destinationFile@g" -e "s@connectString@sqlite_file:$sqliteFile@" > log/readFromFile_${runNumberList[$k]}.cfg
     
     cmsRun log/readFromFile_${runNumberList[$k]}.cfg
     
     let "k+=1"
done

echo "=============================================================="
echo " Done ! $sqliteFile is filled !                     "
echo "=============================================================="

