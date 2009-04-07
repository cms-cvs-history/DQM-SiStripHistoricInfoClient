import FWCore.ParameterSet.Config as cms

process = cms.Process("PWRITE")

#########################
# message logger
######################### 

process.MessageLogger = cms.Service("MessageLogger",
                                    destinations = cms.untracked.vstring('log/destinationFile'),
                                    destinationFile = cms.untracked.PSet(threshold = cms.untracked.string('DEBUG')),
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

process.load("DQMServices.Core.DQM_cfg")


########################
# DB parameters
########################

process.PoolDBOutputService = cms.Service("PoolDBOutputService",
                                          BlobStreamerName = cms.untracked.string('TBufferBlobStreamingService'),
                                          DBParameters = cms.PSet(
    messageLevel = cms.untracked.int32(2),
    authenticationPath = cms.untracked.string('/afs/cern.ch/cms/DB/conddb')
    ),
                                          timetype = cms.untracked.string('runnumber'),
                                          connect = cms.string('sqlite_file:dbfile.db'),
                                          toPut = cms.VPSet(cms.PSet(
    record = cms.string("HDQMSummary"),
    tag = cms.string("SiStripBadFiber_Ideal_31X")
    )),
                                          logconnect = cms.untracked.string("sqlite_file:log.db") 
                                          )

########################
# POPCON Application
########################
process.siStripDQMHistoryPopCon = cms.EDAnalyzer("SiStripDQMHistoryPopCon",
                                                 record = cms.string("HDQMSummary"),
                                                 loggingOn = cms.untracked.bool(True),
                                                 SinceAppendMode = cms.bool(True),
                                                 Source = cms.PSet(since = cms.untracked.uint32(theRunNr),debug = cms.untracked.bool(False))
                                                 ) 


########################
# HistoricDQMService
########################

process.SiStripHistoryDQMService = cms.Service("SiStripHistoryDQMService",
                                                   RunNb = cms.uint32(theRunNr),
                                                   accessDQMFile = cms.bool(True),
                                                   FILE_NAME = cms.untracked.string("theFileName"),
                                                   ME_DIR = cms.untracked.string("Run theRunNr"),
                                                   histoList = cms.VPSet(

    # quantities are 'stat', 'landau', 'gauss'
    # where 
    #'stat' includes entries, mean, rms
    #'landau' includes
    #'gauss' includes gaussMean, gaussSigma
    

    # CKFTk
    
    cms.PSet( keyName = cms.untracked.string("Chi2_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
    ,
    cms.PSet( keyName = cms.untracked.string("NumberOfTracks_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
    ,
    cms.PSet( keyName = cms.untracked.string("NumberOfRecHitsPerTrack_CKFTk"), quantitiesToExtract = cms.untracked.vstring("stat"))
    
    # Summary Cluster Properties
    ,
    cms.PSet( keyName = cms.untracked.string("Summary_TotalNumberOfClusters_OnTrack"),  quantitiesToExtract = cms.untracked.vstring("stat"))
    ,
    cms.PSet( keyName = cms.untracked.string("Summary_ClusterChargeCorr_OnTrack"),	    quantitiesToExtract = cms.untracked.vstring("stat","landau","user"))

    # Summary Cluster properties @ layer level
    ,
    cms.PSet( keyName = cms.untracked.string("Summary_TotalNumberOfClusters__OnTrack"),  quantitiesToExtract = cms.untracked.vstring("stat"))
    
    )
                                               )


# Schedule

process.p = cms.Path(process.siStripDQMHistoryPopCon)




