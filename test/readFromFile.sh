#!/bin/bash 
#
# Configuration for cmstac12 ...
#
# How to run : ./readFromFile.sh /home/cmstacuser/HistoricDQM
#
# Don't forget to modify ROOTFILE_DIR in DQM/SiStripHistoricInfoClient/readFromFile.cfg according to $1 !   (TO BE FIXED !)
#


tag=SiStripSummary_test1
sqliteFile=historicDQM.db

connectString="oracle://devdb10/CMS_COND_STRIP"
#connectString="oracle://cms_orcoff_int2r/CMS_COND_STRIP"
#connectString="sqlite_file:$sqliteFile"

logDB=sqlite_file:log.db

#############

[ "$1" == "" ] && echo -e "specify directory of input root file\n EXAMPLE:\n ./readFromFile.sh /storage/data1/SiStrip/SiStripDQM/output/cruzet/\*Alone.\*" && exit



echo "=============================================================="
echo " Run readFromFile.cfg over all root files located in "  
dirname `echo $1 | awk '{print $1}'`  
echo "=============================================================="
echo "  "

eval `scramv1 runtime -sh`


#### In case of sqlite file
if [ `echo $connectString | grep -c sqlite` ]; then
    [ -e $sqliteFile ] && rm $sqliteFile $logDB && echo " removed existing database $sqliteFile"
    
    path=$CMSSW_BASE/src/CondTools/SiStrip/scripts
    if [ ! -e $path ] ;then
	path=$CMSSW_RELEASE_BASE/src/CondTools/SiStrip/scripts
	if [ ! -e $path ]; then
	    echo -e "Error: CondTools/SiStrip/scripts doesn't exist\nplease install that package\nexit"
	    exit 1
	fi
    fi

   #UNCOMMENT to have BLOB
   #$path/CreatingTables.sh sqlite_file:$sqliteFile a b

fi

rootFileList=(`ls  $1 | grep ".root" | sort`)
k=0
ListSize=${#rootFileList[*]}
echo ListSize $ListSize

mkdir -p log
while [ "$k" -lt "$ListSize" ]
  do
     rootFile=${rootFileList[$k]}
     runNumberList[$k]=`echo ${rootFile} | awk -F "R00" '{print $2}' | awk -F"_" '{print int($1)}'` 
     destinationFile=readFromFile_${runNumberList[$k]}.log
     echo -e "\n\n\nprocessing " $rootFile " for runNr " ${runNumberList[$k]} "\n\n"
     
     cat $CMSSW_BASE/src/DQM/SiStripHistoricInfoClient/test/template_HistoricDQMService.cfg | sed -e "s@theRunNr@${runNumberList[$k]}@g" -e "s@theFileName@$rootFile@g" -e "s@destinationFile@$destinationFile@g" -e "s@connectString@$connectString@" -e "s@insertTag@$tag@" -e "s@insertLogDB@$logDB@" > log/readFromFile_${runNumberList[$k]}.cfg
     
     cmsRun log/readFromFile_${runNumberList[$k]}.cfg
     [ "$?" != "0" ] && echo -e "Problem found in the processing. please have a look at \nlog/readFromFile_${runNumberList[$k]}.log" && exit
     let "k+=1"
done

echo "=============================================================="
echo " Done ! $sqliteFile is filled !                     "
echo "=============================================================="

