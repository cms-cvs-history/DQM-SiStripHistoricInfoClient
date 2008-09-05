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

class HistoricInspector {

public:  
  HistoricInspector():
    DBName_(""),
    DBTag_(""),
    DBuser_(""),
    DBpasswd_(""),
    DBblob_(""),
    Iterator(0),
    iDebug(0)
  {
    //VERY POOR WAY TO CREATE A STD VECTOR, BUT IT SEEMS THAT CINT DOESN'T ALLOW TO DO BETTER
    std::vector<unsigned int>* a = new std::vector<unsigned int>(0);
    iovList=a;
  };
  
  ~HistoricInspector(){
    delete Iterator;
  };
  
  void setDB(std::string DBName, std::string DBTag, std::string DBuser="", std::string DBpasswd="", std::string DBblob="");
  void createTrend(unsigned int detId, std::string ListItems, std::string CanvasName="", std::string Conditions="", unsigned int firstRun=1, unsigned int lastRun=0xFFFFFFFE);
  void setDebug(int i){iDebug=i;}

private:

  void style();
  void plot(unsigned int detId, std::vector<unsigned int>& vRun, std::vector<float>& vWhatToPlotSummary, std::vector<std::string>& vlistItems,size_t& nPads, std::string CanvasName);
  void accessDB();
  void InitializeIOVList();
  bool setRange(unsigned int& firstRun, unsigned int& lastRun);
  void setItems(std::string,std::vector<std::string>&);
  size_t unpackItems(std::string& ListItems, std::vector<std::string>& vlistItems);
  
  std::string DBName_, DBTag_, DBuser_, DBpasswd_, DBblob_;
  
  CondCachedIter<SiStripSummary>* Iterator; 
  
  std::vector<unsigned int>* iovList;
  int iDebug;
};

