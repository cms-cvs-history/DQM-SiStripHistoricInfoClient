//------------------------------------------------------------------
///
// readPlotIOV.cpp does the work for condIter_extractSummary.cpp
//
//------------------------------------------------------------------
//------------------------------------------------------------------
// 
//  12-06-2008 - anne-catherine.le.bihan@cern.ch 
//
//------------------------------------------------------------------



//--------------------------------------
template <class T> void readRun(CondCachedIter<T>* Iterator, int runNr, const std::string & whatToPlot, 
                                std::vector<unsigned int>& vDetIds, std::vector<float>& vWhatToPlotSummary)
//--------------------------------------
{

    gROOT->SetStyle("Plain");
   
    const T* reference;
 
    while(reference = Iterator->next()) 
    {   
       if (runNr == reference->getRunNr()) 
       {
          vDetIds = reference->getDetIds();
          vWhatToPlotSummary = reference->getSummaryObj(whatToPlot);
	 /* if (whatToPlot.find("mean") != string::npos) 
	  { 
	     std::string strRMS = whatToPlot.replace(whatToPlot.find("mean"),4,"rms"));
	     std::vector<float> vRMS = reference->getSummaryObj(strRMS);
	     vWhatToPlotSummary.insert(vWhatToPlotSummary.end(),vRMS.begin(),vRMS.end());
	    }*/
       }
    }
 
}
	
	

//--------------------------------------
template <class T> void readRun2(CondCachedIter<T>* Iterator, unsigned int runNr, 
                                 std::vector<unsigned int>& vDetIds, std::vector<float>& vSummary, std::vector<string>& vDBContent)
//--------------------------------------
{

    gROOT->SetStyle("Plain");

    const T* reference;
 
    while(reference = Iterator->next()) 
    {  
       if (runNr == reference->getRunNr()) 
       {
          vDetIds = reference->getDetIds();
	  vDBContent = reference->getUserDBContent();
	  vSummary   = reference->getSummaryObj();
       }
    }
    
}	

//--------------------------------------
template <class T> void readDetIds(CondCachedIter<T>* Iterator, unsigned int detId, const std::string & whatToPlot, 
                                   std::vector<unsigned int>& vRun, std::vector<float>& vWhatToPlotSummary)
//--------------------------------------
{

    gROOT->SetStyle("Plain");

    const T* reference;
    reference = Iterator->next();
    whatToPlot.find("mean");
    
    while(reference) 
    { 
       vRun.push_back(reference->getRunNr());
       vWhatToPlotSummary.push_back(reference->getSummaryObj(detId, whatToPlot));
       reference = Iterator->next();
    }
    
}


//--------------------------------------
template <class T> void readDetIds2(CondCachedIter<T>* Iterator, unsigned int detId, 
                                    std::vector<unsigned int>& vRun, std::vector<float>& vSummary, std::vector<std::string>& listToPlot)
//--------------------------------------
{

    gROOT->SetStyle("Plain");

    const T* reference;
     
    while(reference = Iterator->next()) 
    { 

       vRun.push_back(reference->getRunNr());
       std::vector<float> v = reference->getSummaryObj(detId, listToPlot);
     
       for(int i=0;i<v.size();i++) vSummary.push_back(v.at(i));// to be changed !!   
    }
    
}


//--------------------------------------
void plotvsDetId(unsigned int runNr, std::vector<unsigned int>& vDetIds, std::vector<float>& vWhatToPlotSummary, std::string whatToPlot)
//--------------------------------------
{
    //
    std::ostringstream runstr; 
    runstr.str("");runstr <<"_run"<< runNr;
    TString ohistoid = whatToPlot+runstr.str();
    TString title = whatToPlot+" vs detID "+runstr.str();
    
    //
    style();
      
    //
    TCanvas * cc = new TCanvas(title.Data(), title.Data() ,10,10,700,400);
   
    //
    TH1F* histo = new TH1F(ohistoid,ohistoid,1,0,1);
    histo->SetBit(TH1::kCanRebin);
    histo->SetLineWidth(2);
    
    if (vWhatToPlotSummary.size() == vDetIds.size())
    {  
      for (unsigned int j = 0; j < vDetIds.size() ; j++) 
      {
         std::ostringstream osdetid; osdetid<< vDetIds.at(j); TString sdetid = osdetid.str();
         //std::cout <<vWhatToPlotSummary.size() <<" "<< vDetIds.size() <<std::endl;
         histo->Fill(sdetid,vWhatToPlotSummary.at(j));
       }
     }
    else std::cout << "Mismatch in DB ... no detID - info mapping ... " << std::endl;
    
    histo->LabelsDeflate("X");
    
  
    if  (vDetIds.size()>20) histo->Draw("AH"); 
    else                    histo->Draw(""); 
    histo->GetXaxis()->SetTitle("detID"); 
   
    cc->SaveAs(ohistoid+".eps");//cc->SaveAs(ohistoid+".pdf");
    
}



//--------------------------------------
void plotvsRun(unsigned int detId, std::vector<unsigned int>& vRun, std::vector<float>& vWhatToPlotSummary, std::string whatToPlot)
//--------------------------------------
{
   
    //
    std::ostringstream detidstr; 
    detidstr.str("");detidstr <<" - DetID "<< detId;
   
    //
    TString ohistoid = whatToPlot+detidstr.str();
    TString title = whatToPlot+detidstr.str();
     
    //
    style();
      
    //
    TCanvas * cc = new TCanvas(title.Data(), title.Data(),10,10,700,400);

    TH1F* histo = new TH1F(ohistoid,title,1,0,1);
    histo->SetBit(TH1::kCanRebin);
    histo->SetLineWidth(2);
    
    if (vWhatToPlotSummary.size() == vRun.size())
    {  
      for (unsigned int j = 0; j < vRun.size(); j++) 
      {
        std::ostringstream osrunid; osrunid<< vRun.at(j); TString srunid = osrunid.str();
        histo->Fill(srunid,vWhatToPlotSummary.at(j));
        std::cout << srunid <<" "<< vWhatToPlotSummary.at(j)<< std::endl;
      }
    }
    else std::cout << "Mismatch in DB ... no run - info mapping ... " << std::endl;
   
    
    histo->LabelsDeflate("X");
    histo->GetXaxis()->SetTitle("run number");
    histo->Draw();
    
    cc->SaveAs(ohistoid+".eps");//cc->SaveAs(ohistoid+".pdf");cc->SaveAs(ohistoid+".jpeg");
      
}



//--------------------------------------
void plotvsRun2(unsigned int detId, std::vector<unsigned int>& vRun, std::vector<float>& vWhatToPlotSummary, std::string whatToPlot, int minEntries)
//--------------------------------------
{
   
    //
    std::ostringstream detidstr; 
    detidstr.str("");detidstr <<" - DetID "<< detId;
   
    //
    TString ohistoid = whatToPlot+detidstr.str();
    TString title = whatToPlot+detidstr.str();
     
    //
    style();
      
    //
    TCanvas * cc = new TCanvas(title.Data(), title.Data(),10,10,700,400);

    TH1F* histo = new TH1F(ohistoid,title,1,0,1);
    histo->SetBit(TH1::kCanRebin);
    histo->SetLineWidth(2);
    
   for (unsigned int j = 0; j < vRun.size(); j++) 
   {
     if (vWhatToPlotSummary.at(3*j+2) > minEntries) {
     std::ostringstream osrunid; osrunid<< vRun.at(j); TString srunid = osrunid.str();
     histo->Fill(srunid,vWhatToPlotSummary.at(3*j));
     histo->SetBinError(j,vWhatToPlotSummary.at(3*j+1));
     std::cout << srunid <<" "<< vWhatToPlotSummary.at(3*j) <<" "<< vWhatToPlotSummary.at(3*j+1) <<" "<< vWhatToPlotSummary.at(3*j+2)<< std::endl;
     }
   }
    
       
    histo->LabelsDeflate("X");
    histo->GetXaxis()->SetTitle("run number");
    histo->Draw();
    
    cc->SaveAs(ohistoid+".eps");//cc->SaveAs(ohistoid+".pdf");cc->SaveAs(ohistoid+".jpeg");
      
}
	
//--------------------------------------
void style()
//--------------------------------------
{

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

}
