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


#include "HistoricInspector.h"
#include <time.h>
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TString.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TAxis.h"

#include "ExpressionEvaluator.h"


void HistoricInspector::style(){

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

void HistoricInspector::setDB(std::string DBName, std::string DBTag, std::string DBuser, std::string DBpasswd, std::string DBblob){

  if( DBName_==DBName && DBTag_==DBTag && DBuser_==DBuser && DBpasswd_==DBpasswd && DBblob_==DBblob)
    return;

  DBName_=DBName;
  DBTag_=DBTag;
  DBuser_=DBuser;
  DBpasswd_=DBpasswd;
  DBblob_=DBblob;

  std::cout << "Name of DB = "<< DBName << std::endl;
  std::cout << "DBTag = "<< DBTag << std::endl;
  std::cout << "DBuser = "<< DBuser << std::endl;
  std::cout << "DBpasswd = "<< DBpasswd<< std::endl;
  std::cout << "DBblob = "<< DBblob<< std::endl;
  std::cout <<std::endl;

  accessDB();
  
  TFile *target = new TFile( "historicDQM.root","RECREATE" );
  target->cd();
}

void HistoricInspector::accessDB(){
  //double start, end;
  // start = clock();   

  if(Iterator!=0)
    delete Iterator;
  
  Iterator = new CondCachedIter<SiStripSummary>();
  Iterator->create(DBName_,DBTag_,DBuser_,DBpasswd_,DBblob_);  

  InitializeIOVList();
  //  end = clock();
  //  if(iDebug)
  //std::cout <<"Time Creation link with Database = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl; 
}


void  HistoricInspector::setBlackList(std::string& ListItems)
{
   std::string::size_type oldloc = 0; 
   std::string::size_type loc = ListItems.find( ",", oldloc );
   
   while( loc != std::string::npos ) {
     blackList.push_back(atoi((ListItems.substr(oldloc,loc-oldloc)).c_str()));
     oldloc=loc+1;
     loc=ListItems.find( ",", oldloc );
     }
   
   blackList.push_back(atoi((ListItems.substr(oldloc,loc-oldloc)).c_str()));
   std::cout << std::endl; 
}


bool  HistoricInspector::isListed(unsigned int run, std::vector<unsigned int>& vList)
{
   bool isListed = false;
   for(unsigned int i=0; i<vList.size();i++){
     if(run== vList.at(i)){ 
      isListed = true;
      if(iDebug) std::cout << "\n Run "<< run << " is black listed !!\n" << std::endl;
     }
    }
   return isListed;
}


void HistoricInspector::InitializeIOVList(){

  const SiStripSummary* reference;
  while(reference = Iterator->next()) {
    iovList.push_back(Iterator->getStartTime());
    std::cout << "iovList " << iovList.back() << std::endl;
  } 
  Iterator->rewind();
}

bool HistoricInspector::setRange(unsigned int& firstRun, unsigned int& lastRun){
  unsigned int first,last;

  for(size_t i=0;i<iovList.size();++i)
    std::cout << iovList.at(i)<< std::endl;

  std::vector<unsigned int>::iterator iter;

  iter=std::lower_bound(iovList.begin(),iovList.end(),firstRun);
  if (iter!=iovList.end())
    first=*iter;
  else{
    std::cout << "firstRun (" << firstRun << ") > last iov ("<<iovList.back()<< ")"<<std::endl; 
    return false;
  }

  iter=std::lower_bound(iovList.begin(),iovList.end(),lastRun);
  if (iter!=iovList.end()){
    if (*iter>lastRun) last = *(iter-1);
    else last=*iter;
  }
  else{
    last=iovList.back();
  }
  
  firstRun=first;
  lastRun=last; 
  std::cout << "setting Range firstRun (" << first << ") - lastRun ("<<last<< ")"<<std::endl; 
  Iterator->setRange(first,last);
  
  return true;
}

void HistoricInspector::createTrendLastRuns(std::string ListItems, std::string CanvasName, int logy, std::string Conditions, unsigned int nRuns){   

unsigned int first,last;
unsigned int iovListSize = iovList.size();

if (iovListSize>0) 
{ 
  last = iovList.back();
  
  if (iovListSize>=nRuns) first = iovList.at(iovListSize-nRuns); 
  else first = *iovList.begin();
  }
  else return;
  
createTrend(ListItems,CanvasName,logy,Conditions,first,last);


}


void HistoricInspector::createTrend(std::string ListItems, std::string CanvasName, int logy, std::string Conditions, unsigned int firstRun, unsigned int lastRun){   
  std::cout << "\n****************\nCreateTrend\n****************\n" << std::endl;
  std::cout << "ListItems : " << ListItems << std::endl;
  std::cout << "Conditions : " << Conditions << std::endl;

  
  vRun_.clear();
  vSummary_.clear();
  vDetIdItemList_.clear();

  std::vector<DetIdItemList> vDetIdItemListCut;
  
  size_t nPads=unpackItems(ListItems);   

  unpackConditions(Conditions,vDetIdItemListCut);
 
  //   double start = clock(); 

  std::cout << "firstRun " << firstRun << " lastRun " << lastRun << std::endl;
  if(!setRange(firstRun,lastRun)){
    Iterator->rewind();
    return;
  }
  const SiStripSummary* reference;
  while(reference = Iterator->next()) { 

    if(Iterator->getStartTime()<firstRun || Iterator->getStartTime()>lastRun || isListed(reference->getRunNr(), blackList))
      continue;

    if(vDetIdItemListCut.size()){
      for(size_t ij=0;ij!=vDetIdItemListCut.size();++ij){
   	vDetIdItemListCut[ij].values=reference->getSummaryObj(vDetIdItemListCut[ij].detid, vDetIdItemListCut[ij].items);
      }

      if(!ApplyConditions(Conditions,vDetIdItemListCut))
	continue;
    }

    vRun_.push_back(reference->getRunNr());

    for(size_t ij=0;ij!=vDetIdItemList_.size();++ij){
      vDetIdItemList_[ij].values=reference->getSummaryObj(vDetIdItemList_[ij].detid, vDetIdItemList_[ij].items);
     
      vSummary_.insert(vSummary_.end(),vDetIdItemList_[ij].values.begin(),vDetIdItemList_[ij].values.end());   
      if(iDebug){
	std::cout << ListItems  << " run " << vRun_.back() << " values \n" ;
	DetIdItemList detiditemlist=vDetIdItemList_[ij];
	for(size_t i=0;i<detiditemlist.items.size();++i)
	  std::cout << "\t" << detiditemlist.items[i] << " " << detiditemlist.values[i] <<" " << i << " \n";
	std::cout << "\n" << std::endl;
      }
    }
  }

  if(vRun_.size())
    plot(nPads, CanvasName, logy);    
   
     
  std::cout << "\n****** Ignore this error *****\n" << std::endl;
  Iterator->rewind();
  std::cout << "\n******************************\n" << std::endl;

}

void HistoricInspector::plot(size_t& nPads, std::string CanvasName, int logy){
 
    
  std::cout << "\n********\nplot\n*****\n"<< std::endl;

  style();

  double *X, *Y, *EX, *EY, *YCumul;
  X=new double[vRun_.size()];
  Y=new double[vRun_.size()];
  EX=new double[vRun_.size()]; 
  EY=new double[vRun_.size()];  
  YCumul=new double[vRun_.size()];
  
  size_t index;
  TCanvas *C;
  TGraphErrors *graph;

  if(CanvasName==""){
    char name[128];
    sprintf(name,"%d",(int) clock());
    CanvasName=std::string(name);
  }
  
  
  std::string rootCName = CanvasName;
  rootCName.replace(rootCName.find("."),rootCName.size()-rootCName.find("."),"");
 
  C=new TCanvas(rootCName.c_str(),"");
  int ndiv=(int) sqrt(nPads);
  C->Divide(ndiv,nPads/ndiv+ (nPads%ndiv?1:0));
 
  int padCount=0;

  vlistItems_.clear();
  vdetId_.clear();
  
  for(size_t ic=0;ic<vDetIdItemList_.size();++ic){
    vlistItems_.insert(vlistItems_.end(),vDetIdItemList_[ic].items.begin(),vDetIdItemList_[ic].items.end());
    vdetId_.insert(vdetId_.end(),vDetIdItemList_[ic].items.size(),vDetIdItemList_[ic].detid);
  }

  for(size_t i=0;i<vlistItems_.size();++i){
    std::cout <<  "TkRegion " << vdetId_[i] << " " << vlistItems_[i] << std::endl;

    if(vlistItems_.at(i).find("Summary")!= std::string::npos) vlistItems_.at(i).replace(vlistItems_.at(i).find("Summary"),7,"");
    if(vlistItems_.at(i).find("@")!= std::string::npos) vlistItems_.at(i).replace(vlistItems_.at(i).find("@"),1,"_");
    
 
    std::stringstream ss;
    if ( vdetId_[i] == 0)  ss << vlistItems_[i];
    else if ( vdetId_[i] == 1)   ss << "TIB" << vlistItems_[i];
    else if ( vdetId_[i] == 2)   ss << "TOB" << vlistItems_[i];
    else if ( vdetId_[i] == 3)   ss << "TID" << vlistItems_[i];
    else if ( vdetId_[i] == 4)   ss << "TEC" << vlistItems_[i];
    else if ( vdetId_[i] == 11)  ss << "TIB_Layer1" << vlistItems_[i];
    else if ( vdetId_[i] == 12)  ss << "TIB_Layer2" << vlistItems_[i];
    else if ( vdetId_[i] == 13)  ss << "TIB_Layer3" << vlistItems_[i];
    else if ( vdetId_[i] == 14)  ss << "TIB_Layer4" << vlistItems_[i];
    else if ( vdetId_[i] == 21)  ss << "TOB_Layer1" << vlistItems_[i];
    else if ( vdetId_[i] == 22)  ss << "TOB_Layer2" << vlistItems_[i];
    else if ( vdetId_[i] == 23)  ss << "TOB_Layer3" << vlistItems_[i];
    else if ( vdetId_[i] == 24)  ss << "TOB_Layer4" << vlistItems_[i];
    else if ( vdetId_[i] == 25)  ss << "TOB_Layer5" << vlistItems_[i];
    else if ( vdetId_[i] == 26)  ss << "TOB_Layer6" << vlistItems_[i];
    else if ( vdetId_[i] == 311) ss << "TID_Side1_Layer1" << vlistItems_[i];
    else if ( vdetId_[i] == 312) ss << "TID_Side1_Layer2" << vlistItems_[i];
    else if ( vdetId_[i] == 313) ss << "TID_Side1_Layer3" << vlistItems_[i];
    else if ( vdetId_[i] == 321) ss << "TID_Side2_Layer1" << vlistItems_[i];
    else if ( vdetId_[i] == 322) ss << "TID_Side2_Layer2" << vlistItems_[i];
    else if ( vdetId_[i] == 323) ss << "TID_Side2_Layer3" << vlistItems_[i];
    
    else ss << "Id " << vdetId_[i]<< " " << vlistItems_[i];
    
    bool itemForIntegration = false;
   

    int addShift=0;
    for(size_t j=0;j<vRun_.size();++j){
      index=j*vlistItems_.size()+i;
      X[j]=vRun_[j];
      EX[j]=0;
      Y[j]=vSummary_[index];
      if (Y[j]==-10 || Y[j]==-9999 || Y[j] ==-99) {EY[j] = 0; Y[j] = 0;}
       
      // -9999 : existing SiStripSummary object in DB but part of the information not uploaded
      // -99   : SiStripSummary object not existing for this detId, informations are missing for all quantities 
      // -10 bad fit ?
      
     
      if(vlistItems_[i].find("mean")!=std::string::npos){
	//if the quantity requested is mean, the error is evaluated as the error on the mean=rms/sqrt(entries)
	EY[j]=vSummary_[index+2]>0?vSummary_[index+1]/sqrt(vSummary_[index+2]):0;
	addShift=2;
      }else if (vlistItems_[i].find("landauPeak")!=std::string::npos){
	EY[j]=vSummary_[index+1];
	addShift=1;
      }
      else if (vlistItems_[i].find("gaussMean")!=std::string::npos){
	EY[j]=vSummary_[index+1];
	addShift=1;
      }
      else if (vlistItems_[i].find("Chi2NDF")!=std::string::npos || vlistItems_[i].find("rms")!=std::string::npos){
        EY[j]= 0.;
      }
      else{
	EY[j]=sqrt(Y[j]);
      }
     
      // calculate integarted number of events / tracks ... 
      //  
      if ( iDoStat && vlistItems_[i].find("entries")!=std::string::npos  && 
          ( vlistItems_[i].find("NumberOfTracks_CKFTk")!=std::string::npos ||
	    vlistItems_[i].find("Chi2_RSTk") !=std::string::npos     || 
	    vlistItems_[i].find("Chi2_CosmicTk")!=std::string::npos    ||
	    vlistItems_[i].find("Chi2_CKFTk")!=std::string::npos    ))
      { 
          if (j == 0 ) YCumul[j] = Y[j]; 
          else         YCumul[j] = Y[j] + YCumul[j-1];
          itemForIntegration = true; }
      
      
      if(iDebug)
	std::cout << index-j*vlistItems_.size() <<  " " << j  << " " << X[j]  << " " << Y[j] << " " << EY[j] << std::endl;
     
    }

    i+=addShift;

    C->cd(++padCount);
    gPad->SetLogy(logy);
    
    graph = new TGraphErrors((int) vRun_.size(),X,Y,EX,EY);
    graph->SetTitle(ss.str().c_str());
    graph->Draw("Alp");
    graph->SetName(ss.str().c_str());
    graph->GetXaxis()->SetTitle("Run number");
    graph->Write();
    
    
    if (iDoStat && itemForIntegration) 
    {  
      std::stringstream ss2; std::stringstream ss3; 
      std::string title =  vlistItems_.at(i);
     
      
      if(title.find("_entries")!= std::string::npos)
      { 
        title.replace(title.find("_entries"),8,""); }
      if(title.find("Chi2_")!= std::string::npos)
      {  
        title.replace(title.find("Chi2_"),5,"");    }
      
      
      if(title == "NumberOfTracks_CKFTk") 
      {   ss2 << "Integrated number of events";
          ss3 << "number_of_events_integrated.gif"; }
      
      else                                         
      {   ss2 << "Integrated number of "<< title; 
          ss3 << vlistItems_[i]<< "_integrated.gif"; }
      
     
      TCanvas* C2 = new TCanvas(ss2.str().c_str(),"");
      TGraphErrors* graph2 = new TGraphErrors((int) vRun_.size(),X,YCumul,EX,EX);
      graph2->SetTitle(ss2.str().c_str());
      graph2->SetMarkerColor(1);
      graph2->Draw("Alp");
      graph2->SetName(ss2.str().c_str());
      graph2->GetXaxis()->SetTitle("Run number");
      graph2->Write();
      C2->Write();
      C2->SaveAs(ss3.str().c_str());
      C2->SaveAs(ss3.str().replace(ss3.str().find("."),ss3.str().size()-ss3.str().find("."),".C").c_str());
      }
   
    
  }
  C->Write();
  C->SaveAs(CanvasName.c_str());
  C->SaveAs(CanvasName.replace(CanvasName.find("."),CanvasName.size()-CanvasName.find("."),".C").c_str());//savewith .C
}


size_t HistoricInspector::unpackItems(std::string& ListItems){
  std::string::size_type oldloc=0; 
  std::string::size_type loc = ListItems.find( ",", oldloc );
  size_t count=1;
  while( loc != std::string::npos ) {
    setItems(ListItems.substr(oldloc,loc-oldloc));
    oldloc=loc+1;
    loc=ListItems.find( ",", oldloc );
    count++; 
  } 
  //there is a single item
  setItems(ListItems.substr(oldloc,loc-oldloc));
  std::cout << std::endl;
  return count;
}

void HistoricInspector::unpackConditions( std::string& Conditions, std::vector<DetIdItemList>& vdetIdItemList){
  char * pch;
  char delimiters[128]="><=+-*/&|() ";
  char copyConditions[1024];
  sprintf(copyConditions,"%s",Conditions.c_str());
  pch = strtok (copyConditions,delimiters);
  while (pch != NULL){
    if(strstr(pch,"@")!=NULL){
      DetIdItemList detiditemlist;
      std::string itemD(pch);
      detiditemlist.detid=atol(itemD.substr(0,itemD.find("@")).c_str());
      detiditemlist.items.push_back(itemD.substr(itemD.find("@")+1));
      std::cout << "Found a Condition " << detiditemlist.items.back() << " for detId " << detiditemlist.detid << std::endl;
      
      if(vdetIdItemList.size())
	if(vdetIdItemList.back().detid==detiditemlist.detid)
	  vdetIdItemList.back().items.insert(vdetIdItemList.back().items.end(),detiditemlist.items.begin(),detiditemlist.items.end());
	else
	  vdetIdItemList.push_back(detiditemlist);
      else
	vdetIdItemList.push_back(detiditemlist); 
    }
    pch = strtok (NULL,delimiters);
  }
}


bool HistoricInspector::ApplyConditions(std::string& Conditions, std::vector<DetIdItemList>& vdetIdItemList){
  double resultdbl=1;
  char cConditions[1024];
  char singleCondition[1024];
  char condCVal[1024];   

  sprintf(cConditions,"%s",Conditions.c_str());
  std::cout << "Conditions " << cConditions << std::endl;
  for(size_t ic=0;ic<vdetIdItemList.size();++ic)
    for(size_t jc=0;jc<vdetIdItemList[ic].items.size();++jc){
      //scientific precision doesn't work in ExpressionEvaluator...
      //sprintf(condCVal,"%g",vdetIdItemList[ic].values[jc]);
      sprintf(condCVal,"%f",vdetIdItemList[ic].values[jc]);
      sprintf(singleCondition,"%d@%s",vdetIdItemList[ic].detid,vdetIdItemList[ic].items[jc].c_str());
      char* fpos = strstr(cConditions,singleCondition);
      strncpy(fpos,condCVal,strlen(condCVal));
      memset(fpos+strlen(condCVal),' ',strlen(singleCondition)-strlen(condCVal));
    
      //std::cout << "fpos " << fpos << " len condCVal " << strlen(condCVal) << " strlen(singleCondition) " << strlen(singleCondition) << " len cConditions " << strlen(cConditions)<<std::endl;
      //std::cout << "Conditions Replace: Condition " << singleCondition << " string changed in " << cConditions << std::endl;
    }

  std::string stringToEvaluate;
  char * pch;
  pch = strtok (cConditions," ");
  while (pch != NULL){
    stringToEvaluate.append(pch);
    pch = strtok (NULL, " ");
  } 
  //for(size_t i=0;i<strlen(cConditions);++i)
  // if(cConditions[i] != " ")
  //  stringToEvaluate.push_back(cConditions[i]);

  if(iDebug)
    std::cout << "Conditions After SubStitution " << stringToEvaluate << std::endl;
  int errcode=ExpressionEvaluator::calculateDouble(stringToEvaluate, resultdbl);
  if(errcode!=0){    
    std::cout << "Problem in ExpressionEvaluator: errcode " << errcode << " Result " << resultdbl << std::endl;
    throw 1;
  }
  if(iDebug)
    std::cout << "Result " << resultdbl << std::endl;
  if(!resultdbl)
    return false;
  return true;
}

void HistoricInspector::setItems(std::string itemD){

  DetIdItemList detiditemlist;
  detiditemlist.detid=atol(itemD.substr(0,itemD.find("@")).c_str());

  std::string item=itemD.substr(itemD.find("@")+1);
  detiditemlist.items.push_back(item);

  if(iDebug)
    std::cout << "Found new item " << detiditemlist.items.back() << " for detid " << detiditemlist.detid << std::endl;

  if(item.find("mean")!=std::string::npos){
    detiditemlist.items.push_back(item.replace(item.find("mean"),4,"rms")); 
    if(iDebug)
      std::cout << "Found new item " << detiditemlist.items.back() << std::endl;
    detiditemlist.items.push_back(item.replace(item.find("rms"),3,"entries")); 
    if(iDebug)
      std::cout << "Found new item " << detiditemlist.items.back() << std::endl;
  }
  else if(item.find("landauPeak")!=std::string::npos){
    detiditemlist.items.push_back(item.replace(item.find("landauPeak"),10,"landauPeakErr")); 
    if(iDebug)
      std::cout << "Found new item " << detiditemlist.items.back() << std::endl;
  }
  else if(item.find("gaussMean")!=std::string::npos){
    detiditemlist.items.push_back(item.replace(item.find("gaussMean"),9,"gaussSigma")); 
    if(iDebug)
      std::cout << "Found new item " << detiditemlist.items.back() << std::endl;
  }
  

  if(vDetIdItemList_.size())
    if(vDetIdItemList_.back().detid==detiditemlist.detid)
      vDetIdItemList_.back().items.insert(vDetIdItemList_.back().items.end(),detiditemlist.items.begin(),detiditemlist.items.end());
    else
      vDetIdItemList_.push_back(detiditemlist);
  else
    vDetIdItemList_.push_back(detiditemlist);
}
