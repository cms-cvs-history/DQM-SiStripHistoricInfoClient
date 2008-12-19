import FWCore.ParameterSet.Config as cms


process = cms.Process("Test")


process.maxEvents = cms.untracked.PSet(
   input = cms.untracked.int32(1))
    
    
process.source = cms.Source("EmptySource",
   firstRun = cms.untracked.uint32(1),
   numberEventsInRun = cms.untracked.uint32(1)
)    
    
    
process.MessageLogger = cms.Service("MessageLogger",
   destinations = cms.untracked.vstring('cout'),
   cout = cms.untracked.PSet( threshold = cms.untracked.string('INFO'))
)
    

process.PoolDBESSource = cms.ESSource("PoolDBESSource",
   toGet = cms.VPSet(record = cms.string("SiStripSummaryRcd"), tag = cms.string("SiStripSummary_test1")),

   connect = cms.string("oracle://devdb10/CMS_COND_STRIP"),
   timetype = cms.string("runnumber"),
   BlobStreamerName = cms.untracked.string("TBufferBlobStreamingService"),

   DBParameters = cms.PSet(
      authenticationPath = cms.untracked.string("/afs/cern.ch/cms/DB/conddb"), 
      messageLevel = cms.untracked.int32(2))
)
    
  
process.prod = cms.OutputModule("SiStripSummaryReader",
   printDebug = cms.untracked.uint32(6))
  
process.p = cms.Path(process.prod)
process.asciiPrint = cms.OutputModule("AsciiOutputModule") 
process.ep = cms.EndPath(process.asciiPrint)
    
