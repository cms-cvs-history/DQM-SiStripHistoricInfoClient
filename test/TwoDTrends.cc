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


#include "TwoDTrends.h"
#include <time.h>
#include "TGraphErrors.h"
#include "TGraph2DErrors.h"
#include "TCanvas.h"
#include "TString.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TAxis.h"


void TwoDTrends::style(){

  TStyle* theStyle= new TStyle();
  theStyle->SetOptStat(0);
  //gROOT->SetStyle("Plain");
  theStyle->SetOptStat(0);
  theStyle->SetOptFit(111);
  theStyle->SetStatFont(12);
  theStyle->SetStatBorderSize(1);
  theStyle->SetCanvasColor(0);
  theStyle->SetCanvasBorderMode(0);
  theStyle->SetPadBorderMode(0);
  theStyle->SetPadColor(0);
  theStyle->SetLineWidth(1);
  theStyle->SetLineStyle(2);
  theStyle->SetPalette(1);
  theStyle->SetMarkerStyle(20);
  theStyle->SetMarkerColor(2);
  theStyle->SetLabelSize(0.09,"y");
  theStyle->SetLabelSize(0.04,"x");
  theStyle->SetTitleFontSize(0.2);
  theStyle->SetTitleW(0.9);
  theStyle->SetPadLeftMargin(0.12);   
  theStyle->SetPadTopMargin(0.34);
  theStyle->cd();

}


void TwoDTrends::twoDplot(std::vector<unsigned int> vRun, std::vector<float> vSummary, 
std::vector<unsigned int> vdetId, std::vector<std::string> vlistItems, 
std::vector<unsigned int> tagInfos, std::string CanvasName, int logy, int nPads)
{
  
  //************************************************************

  style(); 
  TFile *target = new TFile( "twoDHistoricDQM.root","RECREATE" );
  target->cd();
  
  //************************************************************

  double *X, *Y, *Z, *EX, *EY, *EZ;
  X=new double[vRun.size()];
  Y=new double[vRun.size()];
  Z=new double[vRun.size()];
  EX=new double[vRun.size()];  
  EY=new double[vRun.size()];  
  EZ=new double[vRun.size()];  
  
 
  //************************************************************
  
  TCanvas *C;
  TGraph2DErrors *graph;
  
 
  if(CanvasName==""){ char name[128]; sprintf(name,"%d",(int) clock()); CanvasName=std::string(name);}
  std::string rootCName = CanvasName;
  rootCName.replace(rootCName.find("."),rootCName.size()-rootCName.find("."),"");
 
  C=new TCanvas(rootCName.c_str(),"");
  int ndiv=(int) sqrt(nPads);
  C->Divide(ndiv,nPads/ndiv+ (nPads%ndiv?1:0));
  
 
  //************************************************************
 
  size_t padCount   = 0;
  size_t index      = 0;
  size_t tagCount   = 0;
 
  //************************************************************
  

  for(size_t i=0;i<vlistItems.size();++i)
  {
   
    if(iDebug) std::cout << "TkRegion " << vdetId[i] << " " << vlistItems[i] << std::endl;  
 
    std::stringstream ss;
    if ( vdetId[i] == 0)  ss << vlistItems[i];
    else if ( vdetId[i] == 1)   ss << "TIB" << vlistItems[i];
    else if ( vdetId[i] == 2)   ss << "TOB" << vlistItems[i];
    else if ( vdetId[i] == 3)   ss << "TID" << vlistItems[i];
    else if ( vdetId[i] == 4)   ss << "TEC" << vlistItems[i];
    else if ( vdetId[i] == 11)  ss << "TIB_Layer1" << vlistItems[i];
    else if ( vdetId[i] == 12)  ss << "TIB_Layer2" << vlistItems[i];
    else if ( vdetId[i] == 13)  ss << "TIB_Layer3" << vlistItems[i];
    else if ( vdetId[i] == 14)  ss << "TIB_Layer4" << vlistItems[i];
    else if ( vdetId[i] == 21)  ss << "TOB_Layer1" << vlistItems[i];
    else if ( vdetId[i] == 22)  ss << "TOB_Layer2" << vlistItems[i];
    else if ( vdetId[i] == 23)  ss << "TOB_Layer3" << vlistItems[i];
    else if ( vdetId[i] == 24)  ss << "TOB_Layer4" << vlistItems[i];
    else if ( vdetId[i] == 25)  ss << "TOB_Layer5" << vlistItems[i];
    else if ( vdetId[i] == 26)  ss << "TOB_Layer6" << vlistItems[i];
    else if ( vdetId[i] == 311) ss << "TID_Side1_Layer1" << vlistItems[i];
    else if ( vdetId[i] == 312) ss << "TID_Side1_Layer2" << vlistItems[i];
    else if ( vdetId[i] == 313) ss << "TID_Side1_Layer3" << vlistItems[i];
    else if ( vdetId[i] == 321) ss << "TID_Side2_Layer1" << vlistItems[i];
    else if ( vdetId[i] == 322) ss << "TID_Side2_Layer2" << vlistItems[i];
    else if ( vdetId[i] == 323) ss << "TID_Side2_Layer3" << vlistItems[i];
    
    else ss << "Id " << vdetId[i]<< " " << vlistItems[i];
    
    size_t addShift=0;
    tagCount = 0;
    for(size_t j=0;j<vRun.size();++j)
    {
         
      index = j*vlistItems.size()+i;
      if ( index>tagInfos.at(tagCount) ) tagCount++;
      X[j]  = vRun[j];   
      Y[j]  = tagCount;   
      Z[j]  = vSummary[index];  
      EX[j] = 0.; 
      EY[j] = 0.; 
      if (Z[j]==-10 || Z[j]==-9999 || Z[j] ==-99) { EZ[j] = 0; Z[j] = 0;}
      
      // -9999 : existing SiStripSummary object in DB but part of the information not uploaded
      // -99   : SiStripSummary object not existing for this detId, informations are missing for all quantities 
      // -10 bad fit ?
      
      if(vlistItems[i].find("mean")!=std::string::npos){
	//if the quantity requested is mean, the error is evaluated as the error on the mean=rms/sqrt(entries)
	EZ[j]=vSummary[index+2]>0?vSummary[index+1]/sqrt(vSummary[index+2]):0;
	addShift=2;
      }else if (vlistItems[i].find("landauPeak")!=std::string::npos){
	EZ[j]=vSummary[index+1];
	addShift=1;
      }
      else if (vlistItems[i].find("gaussMean")!=std::string::npos){
	EZ[j]=vSummary[index+1];
	addShift=1;
      }
      else if (vlistItems[i].find("Chi2NDF")!=std::string::npos){
        EZ[j]= 0.;
      }
      else{
	EZ[j]=sqrt(Z[j]);
      }
       
     if(iDebug) std::cout <<" "<<j<<" "<<index<<" "<<vRun[j]<<" "<<Z[j]<<" "<<Y[j]<<" "<<EY[j]<<std::endl;
    }

    i+=addShift; 
   
    C->cd(++padCount);
    gPad->SetLogy(logy);
   
    graph = new TGraph2DErrors((int) vRun.size(),X,Y,Z,EX,EY,EZ);
    graph->SetTitle(ss.str().c_str());
    graph->SetName(ss.str().c_str());
    graph->GetXaxis()->SetTitle("Run number");
    graph->GetYaxis()->SetTitle("Processing version");
    graph->Draw("TRI2");
    graph->Write();
   
  }
 
  C->Write();
  C->SaveAs(CanvasName.c_str());
  C->SaveAs(CanvasName.replace(CanvasName.find("."),CanvasName.size()-CanvasName.find("."),".C").c_str());//savewith .C

}



void TwoDTrends::oneDplot(unsigned int run, std::vector<float> vSummary, 
std::vector<unsigned int> vdetId, std::vector<std::string> vlistItems, 
unsigned int nTag, std::string CanvasName, int logy, int nPads)
{
  
  //************************************************************

  style(); 
 
  //************************************************************

  double *X, *Y, *EX, *EY;
  X =new double[nTag];
  Y =new double[nTag];
  EX=new double[nTag];  
  EY=new double[nTag];  
 
  //************************************************************
  
  TCanvas *C;
  TGraphErrors *graph;
   
  if(CanvasName==""){ char name[128]; sprintf(name,"%d",(int) clock()); CanvasName=std::string(name);}
  std::string rootCName = CanvasName;
  rootCName.replace(rootCName.find("."),rootCName.size()-rootCName.find("."),"");
 
  C=new TCanvas(rootCName.c_str(),"");
  int ndiv=(int) sqrt(nPads);
  C->Divide(ndiv,nPads/ndiv+ (nPads%ndiv?1:0));
  
  
  //************************************************************
  
  size_t addShift = 0;
  size_t padCount = 0;
  size_t index    = 0;
    
  std::stringstream ss;
  for(size_t i=0;i<vlistItems.size();++i)
  {
   
    if(iDebug) std::cout << "TkRegion " << vdetId[i] << " " << vlistItems[i] << std::endl;  
    
    if ( vdetId[i] == 0)  ss << vlistItems[i];
    else if ( vdetId[i] == 1)   ss << "TIB" << vlistItems[i];
    else if ( vdetId[i] == 2)   ss << "TOB" << vlistItems[i];
    else if ( vdetId[i] == 3)   ss << "TID" << vlistItems[i];
    else if ( vdetId[i] == 4)   ss << "TEC" << vlistItems[i];
    else if ( vdetId[i] == 11)  ss << "TIB_Layer1" << vlistItems[i];
    else if ( vdetId[i] == 12)  ss << "TIB_Layer2" << vlistItems[i];
    else if ( vdetId[i] == 13)  ss << "TIB_Layer3" << vlistItems[i];
    else if ( vdetId[i] == 14)  ss << "TIB_Layer4" << vlistItems[i];
    else if ( vdetId[i] == 21)  ss << "TOB_Layer1" << vlistItems[i];
    else if ( vdetId[i] == 22)  ss << "TOB_Layer2" << vlistItems[i];
    else if ( vdetId[i] == 23)  ss << "TOB_Layer3" << vlistItems[i];
    else if ( vdetId[i] == 24)  ss << "TOB_Layer4" << vlistItems[i];
    else if ( vdetId[i] == 25)  ss << "TOB_Layer5" << vlistItems[i];
    else if ( vdetId[i] == 26)  ss << "TOB_Layer6" << vlistItems[i];
    else if ( vdetId[i] == 311) ss << "TID_Side1_Layer1" << vlistItems[i];
    else if ( vdetId[i] == 312) ss << "TID_Side1_Layer2" << vlistItems[i];
    else if ( vdetId[i] == 313) ss << "TID_Side1_Layer3" << vlistItems[i];
    else if ( vdetId[i] == 321) ss << "TID_Side2_Layer1" << vlistItems[i];
    else if ( vdetId[i] == 322) ss << "TID_Side2_Layer2" << vlistItems[i];
    else if ( vdetId[i] == 323) ss << "TID_Side2_Layer3" << vlistItems[i];
    
    else ss << "Id " << vdetId[i]<< " " << vlistItems[i];
    
    addShift = 0;
    
    for(size_t j=0;j<nTag;++j)
    { 
    
       index = i+j*vlistItems.size();
       
       X[j]  = j;   
       Y[j]  = vSummary[index];   
       EX[j] = 0.; 
       if (Y[j]==-10 || Y[j]==-9999 || Y[j] ==-99) { EY[j] = 0; Y[j] = 0;}
       
       // -9999 : existing SiStripSummary object in DB but part of the information not uploaded
       // -99	: SiStripSummary object not existing for this detId, informations are missing for all quantities 
       // -10 bad fit ?
       
       if(vlistItems[i].find("mean")!=std::string::npos){
         //if the quantity requested is mean, the error is evaluated as the error on the mean=rms/sqrt(entries)
         EY[j]=vSummary[index+2]>0?vSummary[index+1]/sqrt(vSummary[index+2]):0;
         addShift=2;
       }else if (vlistItems[i].find("landauPeak")!=std::string::npos){
         EY[j]=vSummary[index+1];
         addShift=1;
       }
       else if (vlistItems[i].find("gaussMean")!=std::string::npos){
         EY[j]=vSummary[index+1];
         addShift=1;
       }
       else if (vlistItems[i].find("Chi2NDF")!=std::string::npos){
         EY[j]= 0.;
       }
       else{
         EY[j]=sqrt(Y[j]);
       }
          
        if(iDebug) std::cout<<" "<<j<<" "<<X[j]<<" "<<Y[j]<<" "<<EY[j]<<std::endl;
      
    }
    
    i+=addShift; 
    
    C->cd(++padCount);
    gPad->SetLogy(logy);
   
    graph = new TGraphErrors(nTag,X,Y,EX,EY);
    graph->SetTitle(ss.str().c_str());
    graph->SetMarkerColor(2);
    graph->SetName(ss.str().c_str());
    graph->GetXaxis()->SetTitle("Processing version");
    graph->Draw("Alp");
    graph->Write();
   
  }
 
  C->Write();
  C->SaveAs(CanvasName.c_str());
  C->SaveAs(CanvasName.replace(CanvasName.find("."),CanvasName.size()-CanvasName.find("."),".C").c_str());//savewith .C

}

