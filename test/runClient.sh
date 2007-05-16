#!/bin/bash

eval `scramv1 runtime -sh`
export CORAL_AUTH_USER="me"
export CORAL_AUTH_PASSWORD="me"

\rm -f /tmp/dkcira/ss
\rm -f historic.db historic.xml
cmsRun  clients.cfg >& /tmp/dkcira/ss &
