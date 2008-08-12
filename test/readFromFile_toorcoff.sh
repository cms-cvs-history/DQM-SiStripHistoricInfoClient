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


[ "$1" == "" ] && echo "specify directory of input root file" && exit

tag=SiStripSummary_test2
connectString="oracle://devdb10/CMS_COND_STRIP"
#connectString="oracle://cms_orcoff_int2r/CMS_COND_STRIP"

rootFileList=(`ls -ltr $1 |  awk '{print $9}' | grep ".root"`)
k=0
ListSize=${#rootFileList[*]}
echo ListSize $ListSize

eval `scramv1 runtime -sh`
export TNS_ADMIN=/afs/cern.ch/project/oracle/admin

mkdir -p log
while 
     [ "$k" -lt "$ListSize" ]
do
     rootFile=${rootFileList[$k]}
     runNumberList[$k]=${rootFile:17:5}
     destinationFile=readFromFile_${runNumberList[$k]}.log
     echo "   processing " $1/$rootFile " for runNr " ${runNumberList[$k]}
     
     cat $CMSSW_BASE/src/DQM/SiStripHistoricInfoClient/test/readFromFile.cfg | sed -e "s@theRunNr@${runNumberList[$k]}@g" -e "s@theFileName@$rootFile@g" -e "s@theDirName@$1@" -e "s@destinationFile@$destinationFile@g" -e "s@connectString@$connectString@" -e "s@insertTag@$tag@" > log/readFromFile_${runNumberList[$k]}.cfg
     
     cmsRun log/readFromFile_${runNumberList[$k]}.cfg
     
     let "k+=1"
exit
done

echo "=============================================================="
echo " Done ! historicDQM_rootfile.db is filled !                     "
echo "=============================================================="

