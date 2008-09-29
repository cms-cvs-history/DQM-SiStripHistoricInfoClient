#ifndef DQM_SiStripHistoricInfoClient_GraphAnalysis_H
#define DQM_SiStripHistoricInfoClient_GraphAnalysis_H
//---------------------------------------------------------//
//
// Superimpose graphs stored in historicDQM.root...
//
// GraphAnalysis A("ClusterStoNCorr_OnTrack_landauPeak");
// A.plotGraphAnalysis("TIB,TOB,TID,TEC");
// 
//---------------------------------------------------------//
//---------------------------------------------------------//
// 
//  2008 - anne-catherine.le.bihan@cern.ch 
//
//---------------------------------------------------------//

class TGraphErrors;


class GraphAnalysis {

public:   
  
   GraphAnalysis():_quantity(""){};
   GraphAnalysis(TString quantity){ _quantity = quantity;};
   ~GraphAnalysis(){};
   void plotGraphAnalysis(std::string& ListItems);
  
private:
 
   std::string _quantity;
   double findGraphMax(TGraphErrors* g);
   double findGraphMin(TGraphErrors* g);

};
#endif //DQM_SiStripHistoricInfoClient_GraphAnalysis
