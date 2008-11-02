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
   GraphAnalysis(TString quantity, bool reverse_order, TString canvas_flag){ _quantity = quantity; _reverse_order = reverse_order; _canvas_flag = canvas_flag;};
   ~GraphAnalysis(){};
   void plotGraphAnalysis(std::string& ListItems);
  
private:
 
   std::string _quantity;
   bool _reverse_order;
   std::string _canvas_flag;
   double findGraphMax(TGraphErrors* g);
   double findGraphMin(TGraphErrors* g);

};
#endif //DQM_SiStripHistoricInfoClient_GraphAnalysis
