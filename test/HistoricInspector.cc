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

#include "ExpressionEvaluator.h"


void HistoricInspector::style(){
  /*
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
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerColor(2);
  */
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

void HistoricInspector::createTrend(unsigned int detId, std::string ListItems, std::string CanvasName, std::string Conditions, unsigned int firstRun, unsigned int lastRun){   
  std::cout << "\n****************\nCreateTrend\n****************\n" << std::endl;
  std::cout << "ListItems : " << ListItems << std::endl;
  std::cout << "Conditions : " << Conditions << std::endl;
  //
  std::vector<unsigned int> vRun;
  std::vector <float> vSummary;
  std::vector<std::string> vlistItems;
  std::vector<float> vtmp;
  
  std::vector<std::string> vConditions;
  std::vector<float> vcond;
  


  size_t nPads=unpackItems(ListItems,vlistItems);   

  unpackConditions(Conditions,vConditions);
 
  //   double start = clock(); 

  std::cout << "firstRun " << firstRun << " lastRun " << lastRun << std::endl;
  if(!setRange(firstRun,lastRun)){
    Iterator->rewind();
    return;
  }
  const SiStripSummary* reference;
  while(reference = Iterator->next()) { 

    if(Iterator->getStartTime()<firstRun || Iterator->getStartTime()>lastRun)
      continue;

    if(vConditions.size()){
      vcond=reference->getSummaryObj(detId, vConditions);
   
      if(!ApplyConditions(Conditions,vConditions,vcond))
	continue;
    }

    vRun.push_back(reference->getRunNr());

    vtmp=reference->getSummaryObj(detId, vlistItems);
     
    vSummary.insert(vSummary.end(),vtmp.begin(),vtmp.end());   
    if(iDebug){
      std::cout << ListItems  << " run " << vRun.back() << " values \n" ;
      for(size_t i=0;i<vtmp.size();++i)
	std::cout << "\t" << vlistItems[i] << " " << vSummary[(vRun.size()-1)*vlistItems.size()+i] << " \n";
      std::cout << "\n" << std::endl;
    }
  }

  if(vRun.size())
    plot(detId, vRun, vSummary, vlistItems,nPads, CanvasName);    
   
  //   double end = clock();
  //if(iDebug)
  //std::cout <<"Time plotvsRun = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl; 
   
  std::cout << "\n****** Ignore this error *****\n" << std::endl;
  Iterator->rewind();
  std::cout << "\n******************************\n" << std::endl;

}

void HistoricInspector::plot(unsigned int detId, std::vector<unsigned int>& vRun, std::vector<float>& vSummary, std::vector<std::string>& vlistItems,size_t& nPads, std::string CanvasName){
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
  C=new TCanvas(CanvasName.c_str(),"");
  C->Divide(2,nPads/2+ (nPads%2?1:0));
 
  int padCount=0;
  for(size_t i=0;i<vlistItems.size();++i){
    std::cout << vlistItems[i] << std::endl;


    std::stringstream ss;
    ss << "TkRegion " << detId << " " << vlistItems[i];

    //graph = new TGraphErrors((int) vRun.size());
    
    int addShift=0;
    for(size_t j=0;j<vRun.size();++j){
      index=j*vlistItems.size()+i;
      X[j]=vRun[j];
      EX[j]=0;
      Y[j]=vSummary[index];
      if(Y[j]==-10 || Y[j]==-9999)
	Y[j]=0;

      if(vlistItems[i].find("mean")!=std::string::npos){
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
    
  }
  C->SaveAs(CanvasName.c_str());
}


size_t HistoricInspector::unpackItems(std::string& ListItems, std::vector<std::string>& vlistItems){
  std::string::size_type oldloc=0; 
  std::string::size_type loc = ListItems.find( ",", oldloc );
  size_t count=1;
  while( loc != std::string::npos ) {
    setItems(ListItems.substr(oldloc,loc-oldloc),vlistItems);
    oldloc=loc+1;
    loc=ListItems.find( ",", oldloc );
    count++; 
  } 
  //there is a single item
  setItems(ListItems.substr(oldloc,loc-oldloc),vlistItems);
  std::cout << std::endl;
  return count;
}

void HistoricInspector::unpackConditions( std::string& Conditions, std::vector<std::string>& vConditions){
  char * pch;
  char delimiters[128]="><=+-*/&|() ";
  char copyConditions[1024];
  sprintf(copyConditions,"%s",Conditions.c_str());
  pch = strtok (copyConditions,delimiters);
  while (pch != NULL){
    if(strstr(pch,"@")!=NULL){
      vConditions.push_back(pch);
      std::cout << "a Condition " << vConditions.back() << std::endl;
    }
    pch = strtok (NULL,delimiters);
  }
}


bool HistoricInspector::ApplyConditions(std::string& Conditions, std::vector<std::string>& vConditions, std::vector<float>& vcond){

  double resultdbl=1;
  char cConditions[1024];
  char singleCondition[1024];
  char condCVal[1024];   

  sprintf(cConditions,"%s",Conditions.c_str());
  //std::cout << "Conditions " << cConditions << " len " << strlen(cConditions)<< std::endl;
  for(size_t ic=0;ic<vConditions.size();++ic){
    sprintf(condCVal,"%f",vcond[ic]);
    
    sprintf(singleCondition,"%s",vConditions[ic].c_str());
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

void HistoricInspector::setItems(std::string item,std::vector<std::string>&vlistItems){

  
  vlistItems.push_back(item);
  if(iDebug)
    std::cout << "Found new item " << vlistItems.back() << std::endl;

  if(item.find("mean")!=std::string::npos){
    vlistItems.push_back(item.replace(item.find("mean"),4,"rms")); 
    if(iDebug)
      std::cout << "Found new item " << vlistItems.back() << std::endl;
    vlistItems.push_back(item.replace(item.find("rms"),3,"entries")); 
    if(iDebug)
      std::cout << "Found new item " << vlistItems.back() << std::endl;
  }
  else if(item.find("landauPeak")!=std::string::npos){
    vlistItems.push_back(item.replace(item.find("landauPeak"),10,"landauPeakErr")); 
    if(iDebug)
      std::cout << "Found new item " << vlistItems.back() << std::endl;
  }
}
