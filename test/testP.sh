#!/bin/sh
USAGE="`basename $0` -write / -read"
case $# in
1)
  case "$1" in
        -write)  MODE="write"; ;;
        -read)   MODE="read";  ;;
        *)       echo $USAGE; exit 1; ;;
  esac
  shift
	;;
*)
	echo $USAGE; exit 1;
	;;
esac

eval `scramv1 runtime -sh`
SealPluginRefresh
export CORAL_AUTH_USER=""
export CORAL_AUTH_PASSWORD=""

if [ "$MODE" == "write" ]; then
 \rm historic.db
 \rm historic.xml
 cmsRun offline_historic.cfg
elif [ "$MODE" == "read" ]; then
 cmsRun performance_read.cfg
fi
