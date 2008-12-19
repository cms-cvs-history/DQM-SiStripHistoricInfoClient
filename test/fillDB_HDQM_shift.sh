#!/bin/bash 
#

################
# settings ...
################

castorDir=$1
onDiskDir=/afs/cern.ch/user/a/alebihan/HDQM

tag=historicFromT0_shift
sqliteFile=historicDQM.db

#connectString="oracle://devdb10/CMS_COND_STRIP"
#connectString="oracle://cms_orcoff_int2r/CMS_COND_STRIP"
connectString="sqlite_file:$sqliteFile"
logDB=sqlite_file:log.db

baseDir=/afs/cern.ch/user/a/alebihan/CMSSW_3_0_X_2008-12-18-0500/src
logDir=$baseDir/log
lockFile=$baseDir/lockFile


######################
# lock the process ...
######################
[ -e $lockFile ] && echo -e "\nlockFile " $lockFile "already exists. Process probably already running. If not remove the lockfile." && exit
touch $lockFile
echo -e "=============================================================="
echo " Creating lockFile :"
echo -e "=============================================================="
ls $lockFile
trap "rm -f $lockFile" exit



##########################
# run over copied files
##########################

  if ls $onDiskDir | grep '.root' > /dev/null; then
       
    
    rootFile=`ls $onDiskDir`
    RunNb=`echo ${rootFile} | awk -F "R00" '{print $2}' | awk -F"_" '{print int($onDiskDir)}'`
 
    #
    # checking the WhiteList
    #
    [ "`grep -c "$RunNb DONE" $logDir/WhiteList.txt`" != "0" ] && echo "run " $RunNb " done already, exit !" && exit  
    

  fi


#########################


cd $baseDir

echo -e "\n=============================================================="
echo -e " Run readFromFile_cfg.py over root files located in :"  
dirname `echo $onDiskDir | awk '{print $onDiskDir}'`  
echo -e "==============================================================\n"

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

rootFileList=(`ls  $onDiskDir | grep ".root" | sort`)
k=0
ListSize=${#rootFileList[*]}
echo ListSize $ListSize

mkdir -p log
while [ "$k" -lt "$ListSize" ]
  do
     rootFile=${rootFileList[$k]}
     runNumberList[$k]=`echo ${rootFile} | awk -F "R00" '{print $2}' | awk -F"_" '{print int($onDiskDir)}'` 
     destinationFile=readFromFile_${runNumberList[$k]}_log
     echo -e "\n\n\nprocessing " $rootFile " for runNr " ${runNumberList[$k]} "\n\n"
     
     cat $CMSSW_BASE/src/DQM/SiStripHistoricInfoClient/test/template_HistoricDQMService_cfg.py | sed -e "s@theRunNr@${runNumberList[$k]}@g" -e "s@theFileName@$onDiskDir/$rootFile@g" -e "s@destinationFile@$destinationFile@g" -e "s@connectString@$connectString@" -e "s@insertTag@$tag@" -e "s@insertLogDB@$logDB@" > log/readFromFile_${runNumberList[$k]}_cfg.py
     
     cmsRun log/readFromFile_${runNumberList[$k]}_cfg.py
     status=$?
     
     [ "$status" != "0" ] && echo -e "Problem found in the processing. please have a look at \nlog/readFromFile_${runNumberList[$k]}_log" && exit
     [ "$status" == "0" ] && echo  ${runNumberList[$k]} "DONE" >> $logDir/WhiteList.txt
     
     let "k+=1"
done

rm -f $onDiskDir/*root
rm -f $lockFile

echo "  "
echo "=============================================================="
echo " Done ! $connectString is filled !			  "
echo "=============================================================="


