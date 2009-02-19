//-----------------------------------------------------------------------//
//
//-- plot summary informations vs run number and vs processing version--
//
//-----------------------------------------------------------------------//
//-----------------------------------------------------------------------//
// 
//  17-02-2009 - anne-catherine.le.bihan@cern.ch 
//
//-----------------------------------------------------------------------//

#include "vector"
#include "string"
#include "iostream"
#include "cmath"
#include "CondCore/Utilities/interface/CondCachedIter.h"
#include "CondFormats/SiStripObjects/interface/SiStripSummary.h"
#include "TFile.h" 

class TwoDTrends {

  struct DetIdItemList {
    unsigned int detid;
    std::vector<std::string> items;
    std::vector<float> values;
  };

public:  
  TwoDTrends():iDebug(0){};
  ~TwoDTrends(){};
  void plot(std::vector<unsigned int> vRun, std::vector<float> vSummary,
  std::vector<unsigned int> vdetId, std::vector<std::string> vlistItems,
  std::vector<unsigned int> tagInfos, std::string CanvasName, int logy, int nPads);
 
  
private:

  void style();
  int  iDebug;
   
};

