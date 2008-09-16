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
  theStyle->SetLineWidth(.5);
  theStyle->SetLineStyle(2.);
  theStyle->SetPalette(1);
  theStyle->SetMarkerStyle(20);
  theStyle->SetMarkerColor(2);
  theStyle->SetLabelSize(0.07,"y");
  theStyle->SetLabelSize(0.04,"x");
  theStyle->SetTitleFontSize(0.2);
  theStyle->SetTitleW(0.9);
  theStyle->SetPadLeftMargin(0.12);   
  theStyle->SetPadTopMargin(0.3);
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
  if (iter!=iovList.end())
    last=*iter;
  else{
    last=iovList.back();
  }
  
  firstRun=first;
  lastRun=last; 
  std::cout << "setting Range firstRun (" << first << ") - lastRun ("<<last<< ")"<<std::endl; 
  Iterator->setRange(first,last);
  
  return true;
}

void HistoricInspector::createTrend(std::string ListItems, std::string CanvasName, std::string Conditions, unsigned int firstRun, unsigned int lastRun){   
  std::cout << "\n****************\nCreateTrend\n****************\n" << std::endl;
  std::cout << "ListItems : " << ListItems << std::endl;
  std::cout << "Conditions : " << Conditions << std::endl;
  //
  std::vector<unsigned int> vRun;
  std::vector <float> vSummary;

  std::vector<DetIdItemList> vDetIdItemList, vDetIdItemListCut;

  size_t nPads=unpackItems(ListItems,vDetIdItemList);   

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

    vRun.push_back(reference->getRunNr());

    for(size_t ij=0;ij!=vDetIdItemList.size();++ij){
      vDetIdItemList[ij].values=reference->getSummaryObj(vDetIdItemList[ij].detid, vDetIdItemList[ij].items);
     
      vSummary.insert(vSummary.end(),vDetIdItemList[ij].values.begin(),vDetIdItemList[ij].values.end());   
      if(iDebug){
	std::cout << ListItems  << " run " << vRun.back() << " values \n" ;
	DetIdItemList detiditemlist=vDetIdItemList[ij];
	for(size_t i=0;i<detiditemlist.items.size();++i)
	  std::cout << "\t" << detiditemlist.items[i] << " " << detiditemlist.values[i] << " \n";
	std::cout << "\n" << std::endl;
      }
    }
  }

  if(vRun.size())
    plot(vRun, vSummary, vDetIdItemList, nPads, CanvasName);    
   
  //   double end = clock();
  //if(iDebug)
  //std::cout <<"Time plotvsRun = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl; 
   
  std::cout << "\n****** Ignore this error *****\n" << std::endl;
  Iterator->rewind();
  std::cout << "\n******************************\n" << std::endl;

}

void HistoricInspector::plot(std::vector<unsigned int>& vRun, std::vector<float>& vSummary, std::vector<DetIdItemList>& vDetIdItemList,size_t& nPads, std::string CanvasName){
  std::cout << "\n********\nplot\n*****\n"<< std::endl;

  style();

  double *X, *Y, *EX, *EY;
  X=new double[vRun.size()];
  Y=new double[vRun.size()];
  EX=new double[vRun.size()]; 
  EY=new double[vRun.size()]; 
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
  std::vector<std::string> vlistItems;
  std::vector<unsigned int> vdetId;
  for(size_t ic=0;ic<vDetIdItemList.size();++ic){
    vlistItems.insert(vlistItems.end(),vDetIdItemList[ic].items.begin(),vDetIdItemList[ic].items.end());
    vdetId.insert(vdetId.end(),vDetIdItemList[ic].items.size(),vDetIdItemList[ic].detid);
  }

  for(size_t i=0;i<vlistItems.size();++i){
    std::cout <<  "TkRegion " << vdetId[i] << " " << vlistItems[i] << std::endl;

    if(vlistItems.at(i).find("Summary")!= std::string::npos) vlistItems.at(i).replace(vlistItems.at(i).find("Summary"),7,"");
    if(vlistItems.at(i).find("@")!= std::string::npos) vlistItems.at(i).replace(vlistItems.at(i).find("@"),1,"_");
    
 
    std::stringstream ss;
    if ( vdetId[i] == 0)  ss << vlistItems[i];
    else if ( vdetId[i] == 1)  ss << "TIB" << vlistItems[i];
    else if ( vdetId[i] == 2)  ss << "TOB" << vlistItems[i];
    else if ( vdetId[i] == 3)  ss << "TID" << vlistItems[i];
    else if ( vdetId[i] == 4)  ss << "TEC" << vlistItems[i];
    else ss << "Id " << vdetId[i]<< " " << vlistItems[i];
   

    int addShift=0;
    for(size_t j=0;j<vRun.size();++j){
      index=j*vlistItems.size()+i;
      X[j]=vRun[j];
      EX[j]=0;
      Y[j]=vSummary[index];
      if(Y[j]==-10 || Y[j]==-9999)
	Y[j]=0;

      if(vlistItems[i].find("mean")!=std::string::npos){
	//if the quantity requested is mean, the error is evaluated as the error on the mean=rms/sqrt(entries)
	EY[j]=vSummary[index+2]>0?vSummary[index+1]/sqrt(vSummary[index+2]):0;
	addShift=2;
      }else if (vlistItems[i].find("landauPeak")!=std::string::npos){
	EY[j]=vSummary[index+1];
	addShift=1;
      }else{
	EY[j]=sqrt(Y[j]);
      }
      if(iDebug)
	std::cout << index-j*vlistItems.size() <<  " " << j  << " " << X[j]  << " " << Y[j] << " " << EY[j] << std::endl;
      //      graph->SetPoint(j,X[j],Y[j]);
    }

    i+=addShift;

    C->cd(++padCount);
    graph = new TGraphErrors((int) vRun.size(),X,Y,EX,EY);
    graph->SetTitle(ss.str().c_str());
    graph->Draw("Alp");
    graph->SetName(ss.str().c_str());
    graph->Write();
   
    
  }
  C->Write();
  C->SaveAs(CanvasName.c_str());
  C->SaveAs(CanvasName.replace(CanvasName.find("."),CanvasName.size()-CanvasName.find("."),".C").c_str());//savewith .C
}


size_t HistoricInspector::unpackItems(std::string& ListItems, std::vector<DetIdItemList>& vDetIdItemList){
  std::string::size_type oldloc=0; 
  std::string::size_type loc = ListItems.find( ",", oldloc );
  size_t count=1;
  while( loc != std::string::npos ) {
    setItems(ListItems.substr(oldloc,loc-oldloc),vDetIdItemList);
    oldloc=loc+1;
    loc=ListItems.find( ",", oldloc );
    count++; 
  } 
  //there is a single item
  setItems(ListItems.substr(oldloc,loc-oldloc),vDetIdItemList);
  std::cout << std::endl;
  return count;
}

void HistoricInspector::unpackConditions( std::string& Conditions, std::vector<DetIdItemList>& vDetIdItemList){
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
      
      if(vDetIdItemList.size())
	if(vDetIdItemList.back().detid==detiditemlist.detid)
	  vDetIdItemList.back().items.insert(vDetIdItemList.back().items.end(),detiditemlist.items.begin(),detiditemlist.items.end());
	else
	  vDetIdItemList.push_back(detiditemlist);
      else
	vDetIdItemList.push_back(detiditemlist); 
    }
    pch = strtok (NULL,delimiters);
  }
}


bool HistoricInspector::ApplyConditions(std::string& Conditions, std::vector<DetIdItemList>& vDetIdItemList){
  double resultdbl=1;
  char cConditions[1024];
  char singleCondition[1024];
  char condCVal[1024];   

  sprintf(cConditions,"%s",Conditions.c_str());
  std::cout << "Conditions " << cConditions << std::endl;
  for(size_t ic=0;ic<vDetIdItemList.size();++ic)
    for(size_t jc=0;jc<vDetIdItemList[ic].items.size();++jc){
      //scientific precision doesn't work in ExpressionEvaluator...
      //sprintf(condCVal,"%g",vDetIdItemList[ic].values[jc]);
      sprintf(condCVal,"%f",vDetIdItemList[ic].values[jc]);
      sprintf(singleCondition,"%d@%s",vDetIdItemList[ic].detid,vDetIdItemList[ic].items[jc].c_str());
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

void HistoricInspector::setItems(std::string itemD,std::vector<DetIdItemList>& vDetIdItemList){

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

  if(vDetIdItemList.size())
    if(vDetIdItemList.back().detid==detiditemlist.detid)
      vDetIdItemList.back().items.insert(vDetIdItemList.back().items.end(),detiditemlist.items.begin(),detiditemlist.items.end());
    else
      vDetIdItemList.push_back(detiditemlist);
  else
    vDetIdItemList.push_back(detiditemlist);
}
