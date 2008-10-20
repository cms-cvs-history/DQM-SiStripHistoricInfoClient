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
  
   GraphAnalysis():_quantity("",false){};
   GraphAnalysis(TString quantity, bool reverse_order){ _quantity = quantity; _reverse_order = reverse_order;};
   ~GraphAnalysis(){};
   void plotGraphAnalysis(std::string& ListItems);
  
private:
 
   std::string _quantity;
   bool _reverse_order;
   double findGraphMax(TGraphErrors* g);
   double findGraphMin(TGraphErrors* g);

};
#endif //DQM_SiStripHistoricInfoClient_GraphAnalysis
