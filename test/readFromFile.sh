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

rm historicDQM_rootfile.db
echo " removed existing database historicDQM_rootfile.db"


rootFileList=(`ls -ltr $1 |  awk '{print $9}' | grep ".root"`)
k=0
ListSize=${#rootFileList[*]}
echo $ListSize

while 
     [ "$k" -lt "$ListSize" ]
do
     rootFile=${rootFileList[$k]}
     runNumberList[$k]=${rootFile:17:5}
     
     echo "   processing " $1/$rootFile " for runNr " ${runNumberList[$k]}
     
     sed s/"theRunNr"/${runNumberList[$k]}/g  DQM/SiStripHistoricInfoClient/test/readFromFile.cfg > temporary
     mv temporary readFromFile.cfg
     
     sed s/"theFileName"/$rootFile/g  readFromFile.cfg > temporary
     mv temporary readFromFile.cfg
     
     #sed s/"theDirName"/"toto/ll"/g  readFromFile.cfg > temporary
     #mv temporary readFromFile.cfg
     
     cmsRun readFromFile.cfg
     
     let "k+=1"

done

rm readFromFile.cfg

echo "=============================================================="
echo " Done ! historicDQM_rootfile.db is filled !                     "
echo "=============================================================="

