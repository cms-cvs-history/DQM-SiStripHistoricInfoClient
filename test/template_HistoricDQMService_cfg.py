import FWCore.ParameterSet.Config as cms

process = cms.Process("PWRITE")

#########################
# message logger
######################### 

process.MessageLogger = cms.Service("MessageLogger",
   destinations = cms.untracked.vstring('log/destinationFile'),
   destinationFile = cms.untracked.PSet( threshold = cms.untracked.string('INFO'))
)

#########################
# DQMStore service
######################### 

process.DQMStore = cms.Service("DQMStore",
    referenceFileName = cms.untracked.string(''),
    verbose = cms.untracked.int32(0)
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
   connect = cms.string("connectString"),
   timetype = cms.untracked.string("runnumber"),
   BlobStreamerName = cms.untracked.string("TBufferBlobStreamingService"),
   DBParameters = cms.PSet(
      authenticationPath = cms.untracked.string("/afs/cern.ch/cms/DB/conddb"),
      messageLevel = cms.untracked.int32(4)),
   toPut = cms.VPSet(cms.PSet(
      record = cms.string("SiStripSummaryRcd"),
      tag = cms.string("SiStripSummary_test1"))),
   logconnect = cms.untracked.string("insertLogDB") 
)


########################
# POPCON Application
########################
process.siStripPopConHistoricDQM = cms.EDAnalyzer("SiStripPopConHistoricDQM",
   record = cms.string("SiStripSummaryRcd"),
   loggingOn = cms.untracked.bool(True),
   SinceAppendMode = cms.bool(True),
   Source = cms.PSet(
      since = cms.untracked.uint32(theRunNr),
      debug = cms.untracked.bool(False))
) 


########################
# HistoricDQMService
########################

process.SiStripHistoricDQMService = cms.Service("SiStripHistoricDQMService",
   RunNb = cms.uint32(theRunNr),
   accessDQMFile = cms.bool(True),
   FILE_NAME = cms.untracked.string("theFileName"),
   ME_DIR = cms.untracked.string("Run theRunNr/SiStrip"),
   
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
   ,
   cms.PSet( keyName = cms.untracked.string("TrackPt_CosmicTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackPz_CosmicTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackPx_CosmicTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackPy_CosmicTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackPhi_CosmicTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackEta_CosmicTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackTheta_CosmicTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("DistanceOfClosestApproach_CosmicTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   
	   
   # CKFTk
   ,
   cms.PSet( keyName = cms.untracked.string("Chi2_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("NumberOfTracks_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("NumberOfRecHitsPerTrack_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
    ,
   cms.PSet( keyName = cms.untracked.string("TrackPt_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackPz_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackPx_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackPy_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackPhi_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackEta_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackTheta_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("DistanceOfClosestApproach_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
 
      
   # RSTk
   ,
   cms.PSet( keyName = cms.untracked.string("Chi2_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("NumberOfTracks_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("NumberOfRecHitsPerTrack_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
    ,
   cms.PSet( keyName = cms.untracked.string("TrackPt_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackPz_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackPx_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackPy_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackPhi_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackEta_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("TrackTheta_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("DistanceOfClosestApproach_RSTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
 

   # Summary Cluster Properties
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_TotalNumberOfClusters_OffTrack"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_TotalNumberOfClusters_OnTrack"),  quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterChargeCorr_OnTrack"),      quantitiesToExtract = cms.untracked.vstring("stat,landau"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterCharge_OffTrack"),         quantitiesToExtract = cms.untracked.vstring("stat,landau"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterNoise_OnTrack"),	       quantitiesToExtract = cms.untracked.vstring("stat,gauss"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterNoise_OffTrack"),	       quantitiesToExtract = cms.untracked.vstring("stat,gauss"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterStoNCorr_OnTrack"),        quantitiesToExtract = cms.untracked.vstring("stat,landau"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterStoN_OffTrack"),	       quantitiesToExtract = cms.untracked.vstring("stat,landau"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterWidth_OnTrack"),	       quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterWidth_OffTrack"),	       quantitiesToExtract = cms.untracked.vstring("stat"))
    
   
   # Summary Cluster properties @ layer level
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_TotalNumberOfClusters__OffTrack"), quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_TotalNumberOfClusters__OnTrack"),  quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterChargeCorr__OnTrack"),	quantitiesToExtract = cms.untracked.vstring("stat,landau"))
   , 
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterCharge__OffTrack"), 	quantitiesToExtract = cms.untracked.vstring("stat,landau"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterNoise__OnTrack"),		quantitiesToExtract = cms.untracked.vstring("stat,gauss"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterNoise__OffTrack"),  	quantitiesToExtract = cms.untracked.vstring("stat,gauss"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterStoNCorr__OnTrack"),	quantitiesToExtract = cms.untracked.vstring("stat,landau"))
   , 
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterStoN__OffTrack"),		quantitiesToExtract = cms.untracked.vstring("stat,landau"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterWidth__OnTrack"),		quantitiesToExtract = cms.untracked.vstring("stat"))
   ,
   cms.PSet( keyName = cms.untracked.string("Summary_ClusterWidth__OffTrack"),  	quantitiesToExtract = cms.untracked.vstring("stat"))
    
   # Single module based quantities
   #,
   #( cms.PSet(keyName = cms.untracked.string("NumberOfClusters"),  quantitiesToExtract = cms.untracked.vstring("stat"))
   #,
   #( cms.PSet(keyName = cms.untracked.string("ClusterCharge"),    quantitiesToExtract = cms.untracked.vstring("stat"))
   
   )
)
  

# Schedule

process.p = cms.Path(process.siStripPopConHistoricDQM)
process.asciiPrint = cms.OutputModule("AsciiOutputModule") 
process.ep = cms.EndPath(process.asciiPrint)
    



