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


#include <time.h>
#include "vector.h"
#include "string.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TString.h"

class HistoricInspector {

public:  
  HistoricInspector():
    DBName_(""),
    DBTag_(""),
    DBuser_(""),
    DBpasswd_(""),
    DBBlob_(""),
    Iterator(0)
  {
    //VERY POOR WAY TO CREATE A STD VECTOR, BUT IT SEEMS THAT CINT DOESN'T ALLOW TO DO BETTER
    std::vector<unsigned int>* a = new std::vector<unsigned int>(0);
    iovList=a;
  };
  
  ~HistoricInspector(){
    delete Iterator;
  };
  
  void setDB(std::string DBName, std::string DBTag, std::string DBuser="", std::string DBpasswd="", std::string DBblob="");
  void createTrend(unsigned int detId, std::string ListItems, unsigned int firstRun=1, unsigned int lastRun=0xFFFFFFFE);
  
private:

  void style();
  void plot(unsigned int detId, std::vector<unsigned int>& vRun, std::vector<float>& vWhatToPlotSummary, std::vector<std::string>& vlistItems,size_t& nPads);
  void accessDB();
  void InitializeIOVList();
  bool setRange(unsigned int& firstRun, unsigned int& lastRun);
  void setItems(std::string,std::vector<std::string>&);
  size_t unpackItems(std::string& ListItems, std::vector<std::string>& vlistItems);
  
  std::string DBName_, DBTag_, DBuser_, DBpasswd_, DBblob_;
  
  CondCachedIter<SiStripSummary>* Iterator; 
  
  std::vector<unsigned int>* iovList;
};

void HistoricInspector::style(){

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
   double start, end;
   start = clock();   

   if(Iterator!=0)
     delete Iterator;
  
  Iterator = new CondCachedIter<SiStripSummary>();
  Iterator->create(DBName_,DBTag_,DBuser_,DBpasswd_,DBblob_);  

  InitializeIOVList();
  end = clock();
  std::cout <<"Time Creation link with Database = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl; 
}


void HistoricInspector::InitializeIOVList(){

  int count=0;
  const SiStripSummary* reference;
  while(reference = Iterator->next()) {
    iovList->push_back(Iterator->getStartTime());
    std::cout << "iovList " << iovList->back() << std::endl;
  } 
  Iterator->rewind();
}

bool HistoricInspector::setRange(unsigned int& firstRun, unsigned int& lastRun){
  unsigned int first,last;

  for(size_t i=0;i<iovList->size();++i)
    std::cout << iovList->at(i)<< std::endl;

  std::vector<unsigned int>::iterator iter;

  iter=std::lower_bound(iovList->begin(),iovList->end(),firstRun);
  if (iter!=iovList->end())
    first=*iter;
  else{
    std::cout << "firstRun (" << firstRun << ") > last iov ("<<iovList->back()<< ")"<<std::endl; 
    return false;
  }

  iter=std::lower_bound(iovList->begin(),iovList->end(),lastRun);
  if (iter!=iovList->end())
    last=*iter;
  else{
    last=iovList->back();
  }
  
  firstRun=first;
  lastRun=last; 
  std::cout << "setting Range firstRun (" << first << ") - lastRun ("<<last<< ")"<<std::endl; 
  Iterator->setRange(first,last);
  
  return true;
}

void HistoricInspector::createTrend(unsigned int detId, std::string ListItems, unsigned int firstRun, unsigned int lastRun)
{   
  std::cout << "\n****************\nCreateTrend\n****************\n" << std::endl;
  std::cout << ListItems << std::endl;
   //
   std::vector<unsigned int> vRun;
   std::vector <float> vSummary;
   std::vector<std::string> vlistItems;
   std::vector<float> vtmp;

   size_t nPads=unpackItems(ListItems,vlistItems);   

   double start = clock(); 

   std::cout << "firstRun " << firstRun << " lastRun " << lastRun << std::endl;
   if(!setRange(firstRun,lastRun)){
     Iterator->rewind();
     return;
   }
   const SiStripSummary* reference;
   while(reference = Iterator->next()) { 

     if(Iterator->getStartTime()<firstRun || Iterator->getStartTime()>lastRun)
       continue;
     
     vRun.push_back(reference->getRunNr());
     vtmp=reference->getSummaryObj(detId, vlistItems);
     
     //vSummary.insert(vSummary.end(),vtmp.begin(),vtmp.end());     //<<<<<<<<< THIS DOESN'T WORK IN ROOT INTERPRETED
     std::cout << ListItems  << " run " << vRun.back() << " values " ;
     for(size_t i=0;i<vtmp.size();++i){
       vSummary.push_back(vtmp[i]);
       std::cout << vSummary.back() << " ";
     }
     std::cout << "\n" << std::endl;
   }

   
   plot(detId, vRun, vSummary, vlistItems,nPads);    
   
   double end = clock();
   std::cout <<"Time plotvsRun = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl; 
   
   std::cout << "\n****** Ignore this error *****\n" << std::endl;
   Iterator->rewind();
   std::cout << "\n******************************\n" << std::endl;

}

void HistoricInspector::plot(unsigned int detId, std::vector<unsigned int>& vRun, std::vector<float>& vSummary, std::vector<std::string>& vlistItems,size_t& nPads){
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

  char name[128];
  sprintf(name,"%d",clock());
  C=new TCanvas(name);
  C->Divide(2,nPads/2+ (nPads%2?1:0));
 
  int padCount=0;
  for(size_t i=0;i<vlistItems.size();++i){
    std::cout << vlistItems[i] << std::endl;


    bool rms=false;
    if(vlistItems[i].find("mean")!=string::npos){
      rms=true;
    }

    std::stringstream ss;
    ss << "TkRegion " << detId << " " << vlistItems[i];

    //graph = new TGraphErrors((int) vRun.size());
    
    for(size_t j=0;j<vRun.size();++j){
      index=j*vlistItems.size()+i;
      X[j]=vRun[j];
      EX[j]=0;
      Y[j]=vSummary[index];
      EY[j]=rms?vSummary[index+1]:sqrt(Y[j]);
      std::cout << i <<  " " << j  << " " << X[j]  << " " << Y[j] << " " << EY[j] << endl;
      //      graph->SetPoint(j,X[j],Y[j]);
    }

    C->cd(++padCount);
    graph = new TGraphErrors((int) vRun.size(),X,Y,EX,EY);
    graph->SetTitle(ss.str().c_str());
    graph->Draw("Alp");
    
    if(rms)
      i++;
  }
  //C->SaveAs("name.png");
}


size_t HistoricInspector::unpackItems(std::string& ListItems, std::vector<std::string>& vlistItems){
  string::size_type oldloc=0; 
  string::size_type loc = ListItems.find( ",", oldloc );
  size_t count=1;
  while( loc != string::npos ) {
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

void HistoricInspector::setItems(std::string item,std::vector<std::string>&vlistItems){

  
  vlistItems.push_back(item);
  cout << "Found new item " << vlistItems.back() << endl;

  if(item.find("mean")!=std::string::npos){
    vlistItems.push_back(item.replace(item.find("mean"),4,"rms")); 
    cout << "Found new item " << vlistItems.back() << endl;
 }
}
