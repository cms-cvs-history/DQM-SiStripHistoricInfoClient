//---------------------------------------------------------//
//
//-- extract summary informations from historic DB --
//-- plot summary informations vs run number or vs detID --
//
//---------------------------------------------------------//
//---------------------------------------------------------//
// 
//  12-06-2008 - anne-catherine.le.bihan@cern.ch 
//
//---------------------------------------------------------//


#include "./readPlotIOV.cpp"
#include <time.h>
#include <memory>
#include <algorithm>
#include <vector>


//-----------------------------------------------
void condIter_accessRun(std::string DBName, std::string DBTag, int runNr, std::string whatToPlot)
//-----------------------------------------------
{

   std::cout << std::endl << "Name of DB = "<< DBName << std::endl;
   std::cout << "DBTag = "<< DBTag << std::endl;
   std::cout <<std::endl;
   
   double start, end;
       
   
   //
   start = clock();   
   
      CondCachedIter <SiStripSummary> *Iterator = new CondCachedIter <SiStripSummary>; 
      Iterator->create(DBName,DBTag);  
    
   end = clock();
   std::cout <<"Time Creation link with Database = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl;
   
    
   //
   std::vector<unsigned int> vDetIds;
   std::vector<float> vWhatToPlotSummary;
   
   start = clock(); 
   	 
      readRun<SiStripSummary>(Iterator, runNr, whatToPlot, vDetIds, vWhatToPlotSummary);

   end = clock();
   std::cout <<"Time readRun in DB = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl;
   
    
   //	   
   start = clock(); 
   	 
      plotvsDetId(runNr, vDetIds, vWhatToPlotSummary, whatToPlot);

   end = clock();
   std::cout <<"Time plotvsDetId = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl; 
   
   return;

}






  
//-----------------------------------------------
void condIter_accessRun(std::string DBName, std::string DBTag, unsigned int runNr, std::vector<std::string> listToPlot)
//-----------------------------------------------
{

  std::cout << std::endl << "Name of DB = "<< DBName << std::endl;
  std::cout << "DBTag = "<< DBTag << std::endl;
  std::cout <<std::endl;

  
  double start, end;
    
  
  //
  start = clock();   
  
     CondCachedIter <SiStripSummary> *Iterator = new CondCachedIter <SiStripSummary>;
     Iterator->create(DBName,DBTag);  
   
  end = clock();
  std::cout <<"Time Creation link with Database = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl;
  
  
   
  //
  std::vector<unsigned int>  vDetIds;
  std::vector<float>         vSummary;
  std::vector<std::string>   vDBContent;
  
  start = clock(); 
        
     readRun2<SiStripSummary>(Iterator, runNr, vDetIds, vSummary, vDBContent);

  end = clock();
  std::cout <<"Time read whatToPlot in DB = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl;
 
 
  
  //       
  start = clock();
   
     
     for (int i=0; i<listToPlot.size(); i++)
     { 
       std::vector<float> vWhatToPlotSummary;
       int k = getPosition(vDBContent, listToPlot.at(i));
       if(vDBContent.size()!=0) 
       {
         for (int j=0; j< vSummary.size()/vDBContent.size(); j++) 
         { 
           vWhatToPlotSummary.push_back(vSummary.at(j*vDBContent.size()+k));
	   }
	  }
        plotvsDetId(runNr, vDetIds, vWhatToPlotSummary, listToPlot.at(i));
      }
       
       

  end = clock();
  std::cout <<"Time plotvsDetId = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl; 


}
  
  
  

//-----------------------------------------------
void condIter_accessDetIds(std::string DBName, std::string DBTag, unsigned int detId, std::string whatToPlot, int minEntries)
//-----------------------------------------------
{

   std::cout << std::endl << "Name of DB = "<< DBName << std::endl;
   std::cout << "DBTag = "<< DBTag << std::endl;
   std::cout <<std::endl;

   double start, end;
     
   
   //
   start = clock();   
   
      CondCachedIter <SiStripSummary> *Iterator = new CondCachedIter <SiStripSummary>;
      Iterator->create(DBName,DBTag);  
    
   end = clock();
   std::cout <<"Time Creation link with Database = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl;
   
   
    
   //
   std::vector<unsigned int> vRun;
   std::vector<float> vWhatToPlotSummary;
   
   start = clock(); 
      
      if (whatToPlot.find("mean") ==  std::string::npos) {	 
      readDetIds<SiStripSummary>(Iterator, detId, whatToPlot, vRun, vWhatToPlotSummary);
      plotvsRun(detId, vRun, vWhatToPlotSummary, whatToPlot); }
      else {
      std::vector<std::string> listToPlot; 
      listToPlot.push_back(whatToPlot);
      
      std::string strRMS = whatToPlot; strRMS.replace(strRMS.find("mean"),4,"rms"); listToPlot.push_back(strRMS);
      std::string strEntries = whatToPlot; strEntries.replace(strEntries.find("mean"),4,"entries"); listToPlot.push_back(strEntries);
      
      readDetIds2<SiStripSummary>(Iterator, detId, vRun, vWhatToPlotSummary, listToPlot); 
    
      plotvsRun2(detId, vRun, vWhatToPlotSummary, whatToPlot, minEntries); }
  
} 
  
  
  
   
  
//-----------------------------------------------
void condIter_accessDetIds(std::string DBName, std::string DBTag, unsigned int detId, std::vector<std::string> listToPlot)
//-----------------------------------------------
{

   std::cout << std::endl << "Name of DB = "<< DBName << std::endl;
   std::cout << "DBTag = "<< DBTag << std::endl;
   std::cout <<std::endl;

   double start, end;
     
   
   //
   start = clock();   
   
      CondCachedIter <SiStripSummary> *Iterator = new CondCachedIter <SiStripSummary>;
      Iterator->create(DBName,DBTag);  
    
   end = clock();
   std::cout <<"Time Creation link with Database = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl;
   
   
    
   //
   std::vector<unsigned int> vRun;
   std::vector <float> vSummary;
   
   
   start = clock(); 
  	 
      readDetIds2<SiStripSummary>(Iterator, detId, vRun, vSummary, listToPlot);

   end = clock();
   std::cout <<"Time read readDetIds in DB = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl;
  
   
   //	   
   start = clock(); 
   
   
      
   for (int i; i<listToPlot.size(); i++)
   {   
       std::vector<float> vWhatToPlotSummary;
       for ( int j=0; j< vSummary.size()/listToPlot.size(); j++) 
       {  
  	  vWhatToPlotSummary.push_back(vSummary.at(i+j*listToPlot.size()));
  	 }
       plotvsRun(detId, vRun, vWhatToPlotSummary, listToPlot.at(i));
    }
  	  

   end = clock();
   std::cout <<"Time plotvsRun = " <<  ((double) (end - start)) << " (a.u.)" <<std::endl; 

}



//-----------------------------------------------
int getPosition(std::vector<std::string> vDBContent, std::string whatToPlot) 
//-----------------------------------------------
{
   
   int index = -1;
   for (int i = 0; i<vDBContent.size(); i++) if (vDBContent.at(i) == whatToPlot) index = i;
     
   return index;  
}   




