#include "DQM/SiStripHistoricInfoClient/interface/CopyPerformanceSummary.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/Provenance/interface/RunID.h"
#include "CalibTracker/Records/interface/SiStripDetCablingRcd.h"
#include "CondCore/DBOutputService/interface/PoolDBOutputService.h"
#include "CondFormats/DataRecord/interface/SiStripPerformanceSummaryRcd.h"
#include <string>

//---- default constructor / destructor
CopyPerformanceSummary::CopyPerformanceSummary(const edm::ParameterSet& iConfig) {}
CopyPerformanceSummary::~CopyPerformanceSummary() {}

//---- called each event
void CopyPerformanceSummary::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  if(firstEventInRun){
    firstEventInRun=false;
  }
  ++nevents;
}

//---- called each BOR
void CopyPerformanceSummary::beginRun(const edm::Run& run, const edm::EventSetup& iSetup){
  edm::ESHandle<SiStripPerformanceSummary> tkperf;
  iSetup.get<SiStripPerformanceSummaryRcd>().get(tkperf);
  pSummary_ = new SiStripPerformanceSummary(*tkperf.product());
  firstEventInRun=true;
}

//---- called each EOR
void CopyPerformanceSummary::endRun(const edm::Run& run , const edm::EventSetup& iSetup){
  firstEventInRun=false;
  pSummary_->print();
  writeToDB(run);
}

//-----------------------------------------------------------------------------------------------
void CopyPerformanceSummary::beginJob(const edm::EventSetup&) {
  nevents = 0;
}

//-----------------------------------------------------------------------------------------------
void CopyPerformanceSummary::endJob() {
}

//-----------------------------------------------------------------------------------------------
void CopyPerformanceSummary::writeToDB(const edm::Run& run) const {
  unsigned int l_run  = run.run();
  std::cout<<"CopyPerformanceSummary::writeToDB()  run="<<l_run<<std::endl;
  //now write SiStripPerformanceSummary data in DB
  edm::Service<cond::service::PoolDBOutputService> mydbservice;
  if( mydbservice.isAvailable() ){
    if( mydbservice->isNewTagRequest("SiStripPerformanceSummaryRcd") ){
      mydbservice->createNewIOV<SiStripPerformanceSummary>(pSummary_,mydbservice->beginOfTime(),mydbservice->endOfTime(),"SiStripPerformanceSummaryRcd");
    } else {
      mydbservice->appendSinceTime<SiStripPerformanceSummary>(pSummary_,mydbservice->currentTime(),"SiStripPerformanceSummaryRcd");
    }
  }else{
    edm::LogError("writeToDB")<<"Service is unavailable"<<std::endl;
  }
}
