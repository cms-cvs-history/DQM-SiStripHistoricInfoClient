#!/bin/bash

eval `scramv1 runtime -sh`
export CORAL_AUTH_USER="me"
export CORAL_AUTH_PASSWORD="me"

cmsRun  readdb.cfg
