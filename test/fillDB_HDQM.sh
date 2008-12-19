#!/bin/bash 
#


################
# settings ...
################

tag=SiStripSummary_test2
sqliteFile=historicDQM.db

#connectString="oracle://devdb10/CMS_COND_STRIP"
#connectString="oracle://cms_orcoff_int2r/CMS_COND_STRIP"
connectString="sqlite_file:$sqliteFile"

logDB=sqlite_file:log.db

onDiskDir=/afs/cern.ch/user/a/alebihan/scratch0
castorDir=/castor/cern.ch/cms/store/unmerged/dqm/Cosmics-BeamCommissioning08-PromptReco-v1-RECO-DQMHarvest-OfflineDQM
baseDir=/afs/cern.ch/user/a/alebihan/CMSSW_2_1_9/src
logDir=$baseDir/log
lockFile=$baseDir/lockFile

rootFileOld=toto.root
rootFileInfoOld=0
RunNbOld=0


######################
# lock the process ...
######################
[ -e $lockFile ] && echo -e "\n lockFile already exists. Process probably already running. If not remove the lockfile." && exit
touch $lockFile
trap "rm -f $lockFile" exit


##########################
# copy files from castor
##########################

echo "=============================================================="
echo " Copy new DQM files from CASTOR "
echo "=============================================================="

path2=/toto
for dir in `nsls $castorDir `;
do 
  if nsls $castorDir/$dir | grep '.root' > /dev/null; then
       
    #
    # checking the date ...
    #
    rootFileDate=`nsls -l $castorDir/$dir | awk '{print $6 $7}'`
    rootFileDate2=`date -d "$rootFileDate" "+%Y%m%d"`
    daysAgo=`date --date '2 days ago' "+%Y%m%d"`
    
   # [ "$rootFileDate2" -lt "$daysAgo" ] && continue
    
    #
    # rootFile infos ...
    #
    rootFile=`nsls $castorDir/$dir`
    rootFileInfo=`nsls -i $castorDir/$dir | awk '{print $1}'` # strange integer which caraterizes the file
    RunNb=`echo ${rootFile} | awk -F "R00" '{print $2}' | awk -F"_" '{print int($onDiskDir)}'`
 
    #
    # checking the WhiteList
    #
    [ "`grep -c "$RunNb DONE" $logDir/WhiteList.txt`" != "0" ] && echo "run " $RunNb " done already, skipping!" && continue  
    
    
    #
    # taking the last produced DQM rootfile ... what a pain ...!
    #
    if [ "$RunNbOld" != "$RunNb" ]; then 
       if [ "$path2" != "/toto" ]; then 
          rfcp $path2/$rootFileOld $onDiskDir/$rootFileOld
       fi	  
       path2=$castorDir/$dir
    fi
    
    if [ "$rootFileInfo" -gt "$rootFileInfoOld" ] && [ "$RunNbOld" == "$RunNb" ]; then 
       path2=$castorDir/$dir
    fi

    rootFileInfoOld=$rootFileInfo
    rootFileOld=$rootFile
    RunNbOld=$RunNb

  fi
done

rfcp $path2/$rootFileOld $onDiskDir/$rootFileOld


#########################
# run over copied files 
#########################

cd $baseDir

echo "  "
echo "=============================================================="
echo " Run readFromFile_cfg.py over all root files located in "  
dirname `echo $onDiskDir | awk '{print $onDiskDir}'`  
echo "=============================================================="

eval `scramv1 runtime -csh`


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
echo " Done ! $sqliteFile is filled !			  "
echo "=============================================================="


