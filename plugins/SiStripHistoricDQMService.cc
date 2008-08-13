#include "DQM/SiStripHistoricInfoClient/plugins/SiStripHistoricDQMService.h"
#include "DQMServices/Core/interface/MonitorElement.h"
//#include "DQM/SiStripHistoricInfoClient/interface/fitME.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include <string>
#include <sstream>
#include <cctype>
#include <time.h>
#include <boost/cstdint.hpp>
#

SiStripHistoricDQMService::SiStripHistoricDQMService(const edm::ParameterSet& iConfig,const edm::ActivityRegistry& aReg):
  SiStripCondObjBuilderBase<SiStripSummary>::SiStripCondObjBuilderBase(iConfig), iConfig_(iConfig)
{
  edm::LogInfo("SiStripHistoricDQMService") <<  "[SiStripHistoricDQMService::SiStripHistoricDQMService]";
}


SiStripHistoricDQMService::~SiStripHistoricDQMService() { 
  edm::LogInfo("SiStripHistoricDQMService") <<  "[SiStripHistoricDQMService::~SiStripHistoricDQMService]";
}

void SiStripHistoricDQMService::initialize(){
  
  edm::LogInfo("SiStripHistoricDQMService") <<  "[SiStripHistoricDQMService::initialize]";

  //*GET Parameters*//
  FILE_NAME = iConfig_.getUntrackedParameter<std::string>("FILE_NAME","");
  ME_DIR = iConfig_.getUntrackedParameter<std::string>("ME_DIR","DQMData");
}


void SiStripHistoricDQMService::createSummary(){
    
  //*LOOP OVER THE LIST OF SUMMARY OBJECTS TO INSERT IN DB*//
  typedef std::vector<edm::ParameterSet> VParameters;
  edm::ParameterSet HList=iConfig_.getParameter<edm::ParameterSet>("HList");

  obj_=new SiStripSummary();

  obj_->setRunNr(getRunNumber());

  // **FIXME** //
  //obj_->setTag("");
  
  //* DISCOVER SET OF HISTOGRAMS & QUANTITIES TO BE UPLOADED*//
  std::vector<std::string> userDBContent;
  VParameters histoList = HList.getParameter<VParameters>("histoList");
  VParameters::iterator ithistoList = histoList.begin();
  VParameters::iterator ithistoListEnd = histoList.end();
  
  for(; ithistoList != ithistoListEnd; ++ithistoList ) {    
    std::string keyName = ithistoList->getUntrackedParameter<std::string>("keyName");
    std::vector<std::string> Quantities = ithistoList->getUntrackedParameter<std::vector<std::string> >("quantitiesToExtract"); 
    for (size_t i=0;i<Quantities.size();++i){
      
      if  ( Quantities[i] == "landau" ){ 
	userDBContent.push_back(keyName+std::string("@")+std::string("landauPeak"));
	userDBContent.push_back(keyName+std::string("@")+std::string("landauPeakErr"));
	userDBContent.push_back(keyName+std::string("@")+std::string("landauSFWHM"));
      }
      else if  ( Quantities[i] == "gauss" ){ 
	userDBContent.push_back(keyName+std::string("@")+std::string("gaussMean"));
	userDBContent.push_back(keyName+std::string("@")+std::string("gaussSigma"));
      }	
      else if  ( Quantities[i] == "stat" ){ 
	userDBContent.push_back(keyName+std::string("@")+std::string("entries"));
	userDBContent.push_back(keyName+std::string("@")+std::string("mean"));
	userDBContent.push_back(keyName+std::string("@")+std::string("rms"));
      }
      else{
	edm::LogError("SiStripHistoricDQMService") 
	  << "Quantity " << Quantities[i] 
	  << " cannot be handled\nAllowed quantities are" 
	  << "\n  'stat'   that includes: entries, mean, rms"
	  << "\n  'landau' that includes: landauPeak, landauPeakErr, landauSFWHM"
	  << "\n  'gauss'   that includes: gaussMean, gaussSigma"
	  << std::endl;
      }
    }
  }
  obj_->setUserDBContent(userDBContent);
    
  std::stringstream ss;
  ss << "[SiStripHistoricDQMService::scanTreeAndFillSummary] QUANTITIES TO BE INSERTED IN DB :" << std::endl;  
  std::vector<std::string> userDBContentA = obj_->getUserDBContent();
  for (size_t i=0;i<userDBContentA.size();++i){
    ss << userDBContentA[i]<< std::endl;
  }
  edm::LogInfo("SiStripSummary") << ss.str();

  //* OPEN DQM FILE*//
  openRequestedFile();

  //*FILL SUMMARY*//
  edm::LogInfo("SiStripSummary") << "\nSTARTING TO FILL OBJECT " << std::endl;
  ithistoList = histoList.begin();
  for(; ithistoList != ithistoListEnd; ++ithistoList ) {
    std::string keyName = ithistoList->getUntrackedParameter<std::string>("keyName");
    std::vector<std::string> Quantities = ithistoList->getUntrackedParameter<std::vector<std::string> >("quantitiesToExtract"); 
    scanTreeAndFillSummary(ME_DIR, obj_, keyName, Quantities);
  }
  
}

void SiStripHistoricDQMService::openRequestedFile() { 
  edm::LogInfo("SiStripHistoricDQMService") <<  "[SiStripHistoricDQMService::openRequestedFile] " << FILE_NAME;
  dqmStore_ = edm::Service<DQMStore>().operator->(); 
  // ** FIXME ** // 
  dqmStore_->setVerbose(0); //add config param
  dqmStore_->open(FILE_NAME, false); 
}


void SiStripHistoricDQMService::scanTreeAndFillSummary(std::string top_dir, SiStripSummary* summary,std::string& keyName, std::vector<std::string>& Quantities){
  //
  // -- Scan full root file and fill module numbers and histograms
  //
  //-----------------------------------------------------------------------------------------------

  edm::LogInfo("SiStripHistoricDQMService") <<  "[SiStripHistoricDQMService::scanTreeAndFillSummary]";


  const std::vector<MonitorElement*>& MEs = dqmStore_->getAllContents(top_dir);
  std::vector<MonitorElement*>::const_iterator iterMes = MEs.begin(); 
  std::vector<MonitorElement*>::const_iterator iterMesEnd = MEs.end(); 
  std::stringstream ss;

  for (; iterMes!=iterMesEnd; ++iterMes){
    std::string me_name = (*iterMes)->getName();
    if (me_name.find(keyName) == 0){ 

      SiStripSummary::InputVector values;
      std::vector<std::string> userDBContent;
      
      ss << "[SiStripHistoricDQMService::scanTreeAndFillSummary]\n-----------------------------\nFound compatible ME " << me_name << " for key " << keyName << std::endl;
      
      for(size_t i=0;i<Quantities.size();++i){
	

	if(Quantities[i]  =="landau"){  
	  userDBContent.push_back(keyName+std::string("@landauPeak"));
	  userDBContent.push_back(keyName+std::string("@landauPeakErr"));
	  userDBContent.push_back(keyName+std::string("@landauSFWHM"));
	  
	   //fitME pfitME((*iterMes));
	   //pfitME.doFit(); 
	  //values.push_back( pfitME.getFitPar()[1]); 
	  //values.push_back( pfitME.getFitParErr()[1]); 
	  //values.push_back( pfitME.pLanConv[1]);
	  values.push_back(1.);
	  values.push_back(2.);
	  values.push_back(3.);
	}
	else if(Quantities[i]  =="gauss"){  
	  userDBContent.push_back(keyName+std::string("@gaussMean"));
	  userDBContent.push_back(keyName+std::string("@gaussSigma"));
	  /*
	    fitME pfitME((*iterMes));
	    pfitME.doNoiseFit();
	    values.push_back( pfitME.getNoisePar()[1]);
	    values.push_back( pfitME.getNoiseParErr()[1]);
	  */
	  values.push_back(4.);
	  values.push_back(5.);
	}
	else if(Quantities[i]  == "stat"){  
	  userDBContent.push_back(keyName+std::string("@entries"));
	  userDBContent.push_back(keyName+std::string("@mean"));
	  userDBContent.push_back(keyName+std::string("@rms"));
	  
	  values.push_back( (*iterMes)->getEntries());
	  values.push_back( (*iterMes)->getMean());
	  values.push_back( (*iterMes)->getRMS());
	}
      }  
      

      uint32_t detid=returnDetComponent(me_name);

      ss << " detid " << detid << " \n ";
      for(size_t i=0;i<values.size();++i)
	ss << "Quantity " << userDBContent[i] << " value " << values[i] << std::endl;
      
      summary->put(detid,values,userDBContent);
    }
  }
}   
 
uint32_t SiStripHistoricDQMService::returnDetComponent(std::string& histoName){
  edm::LogInfo("SiStripHistoricDQMService") <<  "[SiStripHistoricDQMService::returnDetComponent]";

  size_t __key_length__=7;
  size_t __detid_length__=9;

  if(histoName.find("__det__")!= std::string::npos){
    return atoi(histoName.substr(histoName.find("__det__")+__key_length__,__detid_length__).c_str());
  }
  //TIB
  else if(histoName.find("TIB")!= std::string::npos){
    if (histoName.find("layer")!= std::string::npos) 
      return sistripsummary::TIB*10
	+atoi(histoName.substr(histoName.find("layer__")+__key_length__,1).c_str()); 
    return sistripsummary::TIB;
  }
  //TOB
  else if(histoName.find("TOB")!= std::string::npos){
    if (histoName.find("layer")!= std::string::npos) 
      return sistripsummary::TOB*10
	+atoi(histoName.substr(histoName.find("layer__")+__key_length__,1).c_str());
    return sistripsummary::TOB;
  }
  //TID
  else if(histoName.find("TID")!= std::string::npos){  
    if (histoName.find("side")!= std::string::npos){
      if (histoName.find("wheel")!= std::string::npos){
	return sistripsummary::TID*100
	  +atoi(histoName.substr(histoName.find("_side__")+__key_length__,1).c_str())*10
	  +atoi(histoName.substr(histoName.find("wheel__")+__key_length__,1).c_str());
      }
      return sistripsummary::TID*10
	+atoi(histoName.substr(histoName.find("_side__")+__key_length__,1).c_str());
    }
    return sistripsummary::TID;
  } 
  //TEC
  else if(histoName.find("TEC")!= std::string::npos){  
    if (histoName.find("side")!= std::string::npos){
      if (histoName.find("wheel")!= std::string::npos){
	return sistripsummary::TEC*100
	  +atoi(histoName.substr(histoName.find("_side__")+__key_length__,1).c_str())*10
	  +atoi(histoName.substr(histoName.find("wheel__")+__key_length__,1).c_str());
      }
      return sistripsummary::TEC*10
	+atoi(histoName.substr(histoName.find("_side__")+__key_length__,1).c_str());
    }
    return sistripsummary::TEC;
  } 
  else 
    return sistripsummary::TRACKER; //Full Tracker
}

uint32_t SiStripHistoricDQMService::getRunNumber() const {
  //Get RunNumber
  int pos1 = ME_DIR.find("Run ");
  int pos2 = ME_DIR.find("/SiStrip");
  
  std::string runStr = ME_DIR.substr(pos1+4,pos2-pos1-4);
  edm::LogInfo("SiStripHistoricDQMService") <<  "[SiStripHistoricDQMService::getRunNumber] " << runStr;

  return atoi(runStr.c_str());
}