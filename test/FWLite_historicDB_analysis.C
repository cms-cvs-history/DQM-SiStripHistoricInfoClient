{
#include <sstream>

std::string nameDB  = "sqlite_file://historicDQM.db";
std::string TagData = "SiStripPerformanceSummaryRcd_v1";

CondCachedIter <SiStripPerformanceSummary> *Iterator = new CondCachedIter <SiStripPerformanceSummary>;
Iterator->create(nameDB,TagData);  

const SiStripPerformanceSummary* reference;
double Run[1000]; float ME[7][1000];

int counter = 0;  
while(reference=Iterator.next())
{
   Run[counter] = reference->getRunNr();
   
   std::vector<uint32_t> vdetids; reference->getDetIds(vdetids);
   for (int j=0; j<vdetids.size(); j++)
   {
    const std::vector<float> summary; 
    reference->getSummary(vdetids.at(j), summary);
    
    for (int k=0; k<7 ;k++) ME[k][counter] = summary.at(k);
    }
    
    counter++;
}



 //
 gStyle->SetOptStat(0);
 gROOT->SetStyle("Plain");
 gStyle->SetOptStat(0);
 gStyle->SetOptFit(111);
 gStyle->SetStatFont(12);
 gStyle->SetStatBorderSize(1);
 gStyle->SetCanvasColor(0);
 gStyle->SetCanvasBorderMode(0);
 gStyle->SetPadBorderMode(0);
 gStyle->SetPadColor(0);
 gStyle->SetLineWidth(2.);
 gStyle->SetPalette(1);


 //
 TCanvas * cc = new TCanvas("X vs Run","X vs Run",10,10,700,400);

 TObjArray *AllDetHistograms = new TObjArray();
 
 std::ostringstream detidstr; 


 //
 for (int i = 0; i < vdetids.size() ; i++) 
 {
  TString ohistoid;
  detidstr.str("");detidstr <<"DetId"<< vdetids.at(i);
  std ::cout << vdetids.at(i) << std::endl;
  for (int k = 0; k < 7 ; k++)
  {
    if (k==0) ohistoid = detidstr.str()+"_ClusterSize_Mean";
    if (k==1) ohistoid = detidstr.str()+"_ClusterSize_RMS";
    if (k==2) ohistoid = detidstr.str()+"_ClusterCharge_Mean";
    if (k==3) ohistoid = detidstr.str()+"_ClusterCharge_RMS";
    if (k==4) ohistoid = detidstr.str()+"_Occupancy_Mean";
    if (k==5) ohistoid = detidstr.str()+"_Occupancy_RMS";
    if (k==6) ohistoid = detidstr.str()+"_PercentNoisyStrips";
   
    AllDetHistograms->Add( new TH1F(ohistoid,ohistoid,1,0,1));
    ((TH1F*) AllDetHistograms->FindObject(ohistoid))->SetBit(TH1::kCanRebin);
    ((TH1F*) AllDetHistograms->FindObject(ohistoid))->SetLineWidth(2);
  
    for (int j = 0; j < counter ; j++) 
    {
       std::ostringstream osrunid; osrunid<< Run[j]; TString srunid = osrunid.str();
       ((TH1F*) AllDetHistograms->FindObject(ohistoid))->Fill(srunid,ME[k][j]);
     }
    
    ((TH1F*) AllDetHistograms->FindObject(ohistoid))->LabelsDeflate("X");
    ((TH1F*) AllDetHistograms->FindObject(ohistoid))->GetXaxis()->SetTitle("run number");
    ((TH1F*) AllDetHistograms->FindObject(ohistoid))->Draw();
    
    cc->SaveAs(ohistoid+".eps");cc->SaveAs(ohistoid+".pdf");cc->SaveAs(ohistoid+".jpeg");
    }
   }

}
