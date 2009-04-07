import FWCore.ParameterSet.Config as cms

process = cms.Process("PWRITE")

#########################
# message logger
######################### 

process.MessageLogger = cms.Service("MessageLogger",
destinations = cms.untracked.vstring('cout'),
readFromFile_57620 = cms.untracked.PSet(
    threshold = cms.untracked.string('DEBUG')),
debugModules = cms.untracked.vstring('*')
)


#########################
# maxEvents ...
#########################

process.maxEvents = cms.untracked.PSet(
     input = cms.untracked.int32(1))
     
process.source = cms.Source("EmptySource",
    timetype = cms.string("runnumber"),
    firstRun = cms.untracked.uint32(1),
    lastRun  = cms.untracked.uint32(1),
    interval = cms.uint32(1)
)

#########################
# DQM services
#########################
from DQMServices.Core.DQM_cfg import *


########################
# DB parameters
########################

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
connect = cms.string("sqlite_file:historicDQM.db"),
timetype = cms.untracked.string("runnumber"),
DBParameters = cms.PSet(
   authenticationPath = cms.untracked.string("/afs/cern.ch/cms/DB/conddb"),
   messageLevel = cms.untracked.int32(4)),
toPut = cms.VPSet(
   record = cms.string("SiStripSummaryRcd"),
   tag = cms.string("SiStripSummary_test1")),
logconnect = cms.untracked.string("sqlite_file:log.db") 
)


########################
# POPCON Application
########################
process.siStripPopConHistoricDQM = cms.OutputModule("SiStripPopConHistoricDQM",
record = cms.string("SiStripSummaryRcd"),
loggingOn = cms.untracked.bool(True),
SinceAppendMode = cms.bool(True),
Source = cms.PSet(
   since = cms.untracked.uint32(57620),
   debug = cms.untracked.bool(False))
) 


########################
# HistoricDQMService
########################

process.SiStripHistoricDQMService = cms.Service("SiStripHistoricDQMService",
RunNb = cms.uint32(57620),
accessDQMFile = cms.bool(True),
FILE_NAME = cms.untracked.string("/home/cmstacuser/HistoricDQM/DQM_R000057620__Cosmics__Commissioning08-CRUZET4_v1__RECO.root"),
ME_DIR = cms.untracked.string("Run 57620"),
histoList = cms.VPSet(
     
# quantities are 'stat', 'landau', 'gauss'
# where 
#'stat' includes entries, mean, rms
#'landau' includes
#'gauss' includes gaussMean, gaussSigma

#CosmicTk

cms.PSet( keyName = cms.untracked.string("NumberOfTracks_CosmicTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
,
cms.PSet( keyName = cms.untracked.string("Chi2_CosmicTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
,
cms.PSet( keyName = cms.untracked.string("NumberOfRecHitsPerTrack_CosmicTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
  
# CKFTk
,
cms.PSet( keyName = cms.untracked.string("Chi2_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
,
cms.PSet( keyName = cms.untracked.string("NumberOfTracks_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
,
cms.PSet( keyName = cms.untracked.string("NumberOfRecHitsPerTrack_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))

# RSTk
,
cms.PSet( keyName = cms.untracked.string("Chi2_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
,
cms.PSet( keyName = cms.untracked.string("NumberOfTracks_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
,
cms.PSet( keyName = cms.untracked.string("NumberOfRecHitsPerTrack_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))


# Summary Cluster Properties
,
cms.PSet( keyName = cms.untracked.string("Summary_TotalNumberOfClusters_OffTrack"), quantitiesToExtract = cms.untracked.vstring("stat"))
,
cms.PSet( keyName = cms.untracked.string("Summary_TotalNumberOfClusters_OnTrack"),  quantitiesToExtract = cms.untracked.vstring("stat"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterChargeCorr_OnTrack"),	    quantitiesToExtract = cms.untracked.vstring("stat,landau"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterCharge_OffTrack"),	    quantitiesToExtract = cms.untracked.vstring("stat,landau"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterNoise_OnTrack"),	    quantitiesToExtract = cms.untracked.vstring("stat,gauss"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterNoise_OffTrack"),	    quantitiesToExtract = cms.untracked.vstring("stat,gauss"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterStoNCorr_OnTrack"),	    quantitiesToExtract = cms.untracked.vstring("stat,landau"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterStoN_OffTrack"),	    quantitiesToExtract = cms.untracked.vstring("stat,landau"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterWidth_OnTrack"),	    quantitiesToExtract = cms.untracked.vstring("stat"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterWidth_OffTrack"),	    quantitiesToExtract = cms.untracked.vstring("stat"))
 

# Summary Cluster properties @ layer level
,
cms.PSet( keyName = cms.untracked.string("Summary_TotalNumberOfClusters__OffTrack"), quantitiesToExtract = cms.untracked.vstring("stat"))
,
cms.PSet( keyName = cms.untracked.string("Summary_TotalNumberOfClusters__OnTrack"),  quantitiesToExtract = cms.untracked.vstring("stat"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterChargeCorr__OnTrack"),      quantitiesToExtract = cms.untracked.vstring("stat,landau"))
, 
cms.PSet( keyName = cms.untracked.string("Summary_ClusterCharge__OffTrack"),	     quantitiesToExtract = cms.untracked.vstring("stat,landau"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterNoise__OnTrack"),	     quantitiesToExtract = cms.untracked.vstring("stat,gauss"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterNoise__OffTrack"),	     quantitiesToExtract = cms.untracked.vstring("stat,gauss"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterStoNCorr__OnTrack"),	     quantitiesToExtract = cms.untracked.vstring("stat,landau"))
, 
cms.PSet( keyName = cms.untracked.string("Summary_ClusterStoN__OffTrack"),	     quantitiesToExtract = cms.untracked.vstring("stat,landau"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterWidth__OnTrack"),	     quantitiesToExtract = cms.untracked.vstring("stat"))
,
cms.PSet( keyName = cms.untracked.string("Summary_ClusterWidth__OffTrack"),	     quantitiesToExtract = cms.untracked.vstring("stat"))
 
# Single module based quantities
#,
#( cms.PSet(keyName = cms.untracked.string("NumberOfClusters"),  quantitiesToExtract = cms.untracked.vstring("stat"))
#,
#( cms.PSet(keyName = cms.untracked.string("ClusterCharge"),	quantitiesToExtract = cms.untracked.vstring("stat"))

)

)
  

# Schedule

process.p = cms.Path(process.siStripPopConHistoricDQM)
process.asciiPrint = cms.OutputModule("AsciiOutputModule") 
process.ep = cms.EndPath(process.asciiPrint)
    



