//---------------------------------------------------------//
//
//-- extract summary informations from historic DB --
//-- plot summary informations vs run number or vs detID --
//
//---------------------------------------------------------//
//---------------------------------------------------------//
// 
//  12-08-2008 - domenico.giordano@cern.ch 
//  12-06-2008 - anne-catherine.le.bihan@cern.ch 
//
//---------------------------------------------------------//

#include "vector"
#include "string"
#include "iostream"
#include "cmath"
#include "CondCore/Utilities/interface/CondCachedIter.h"
#include "CondFormats/SiStripObjects/interface/SiStripSummary.h"
#include "TFile.h" 

class HistoricInspector {

  struct DetIdItemList {
    unsigned int detid;
    std::vector<std::string> items;
    std::vector<float> values;
  };

public:  
  HistoricInspector():
    DBName_(""),
    DBTag_(""),
    DBuser_(""),
    DBpasswd_(""),
    DBblob_(""),
    Iterator(0),
    iDebug(0)
    {TFile *target  = new TFile( "historicDQM.root","RECREATE" );};
  
  ~HistoricInspector(){
    delete Iterator;
  };
  
  void setDB(std::string DBName, std::string DBTag, std::string DBuser="", std::string DBpasswd="", std::string DBblob="");
  void createTrend(std::string ListItems, std::string CanvasName="", std::string Conditions="", unsigned int firstRun=1, unsigned int lastRun=0xFFFFFFFE);
  void setDebug(int i){iDebug=i;}
  void setBlackList(std::string& ListItems);

private:

  void style();
  void plot(std::vector<unsigned int>& vRun, std::vector<float>& vWhatToPlotSummary, std::vector<DetIdItemList>& vDetIdItemList,size_t& nPads, std::string CanvasName);
  void accessDB();
  void InitializeIOVList();
  bool setRange(unsigned int& firstRun, unsigned int& lastRun);
  void setItems(std::string,std::vector<DetIdItemList>&);
  size_t unpackItems(std::string& , std::vector<DetIdItemList>&);
  void unpackConditions(std::string& , std::vector<DetIdItemList>&);
  bool ApplyConditions(std::string& , std::vector<DetIdItemList>& );
  bool isListed(unsigned int run, std::vector<unsigned int>& vList);


  std::string DBName_, DBTag_, DBuser_, DBpasswd_, DBblob_;
  
  CondCachedIter<SiStripSummary>* Iterator; 
  
  std::vector<unsigned int> iovList;
  std::vector<unsigned int> blackList;
  int iDebug;
  
};

