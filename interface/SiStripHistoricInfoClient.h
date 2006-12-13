#ifndef SiStripHistoricInfoClient_SiStripHistoricInfoClient_h
#define SiStripHistoricInfoClient_SiStripHistoricInfoClient_h
// -*- C++ -*-
//
// Package:     SiStripHistoricInfoClient
// Class  :     SiStripHistoricInfoClient
// 
/**\class SiStripHistoricInfoClient SiStripHistoricInfoClient.h DQM/SiStripHistoricInfoClient/interface/SiStripHistoricInfoClient.h

 Description: <Non interactive DQM client of the SiStripTk. Writes out in a DB the information needed for the DQM historic plots: https://uimon.cern.ch/twiki/bin/view/CMS/DQMHistoricInfoPlots>

 Usage:
    <usage>

*/
//
// Original Author:  dkcira
//         Created:  Thu Jun 15 09:32:34 CEST 2006
// $Id: SiStripHistoricInfoClient.h,v 1.3 2006/12/12 12:40:06 dkcira Exp $
//

#include "DQMServices/Components/interface/DQMBaseClient.h"
#include "DQMServices/Components/interface/Updater.h"
#include "DQMServices/Components/interface/UpdateObserver.h"
#include "DQMServices/Core/interface/MonitorUserInterface.h"
#include "DQM/SiStripHistoricInfoClient/interface/SiStripHistoricInfoWebInterface.h"

#include "xoap/SOAPBody.h"
#include "xoap/SOAPEnvelope.h"
#include "xdata/Table.h"
#include "xdata/TimeVal.h"

class SiStripHistoricInfoClient : public DQMBaseClient,
                              public dqm::UpdateObserver
{
public:
  // You always need to have this line! Do not remove:
  XDAQ_INSTANTIATOR();

  // The class constructor:  
  SiStripHistoricInfoClient(xdaq::ApplicationStub *s);

  // implement the method that outputs the page with the widgets (declared in DQMBaseClient):
  void general(xgi::Input * in, xgi::Output * out ) throw (xgi::exception::Exception);

  // the method which answers all HTTP requests of the form ".../Request?RequestID=..."
  void handleWebRequest(xgi::Input * in, xgi::Output * out);

  // this obligatory method is called whenever the client enters the "Configured" state:
  void configure();

  // this obligatory method is called whenever the client enters the "Enabled" state:
  void newRun();

  // this obligatory method is called whenever the client enters the "Halted" state:
  void endRun();

  // this obligatory method is called by the Updater component, whenever there is an update 
  void onUpdate() const;

  // TStore 
  void tstore_sistrip();
  void tstore_connect();
  void tstore_connect_nestedview();
  DOMNode *getNodeNamed(xoap::MessageReference msg,const std::string &nodeName) throw (xcept::Exception);
  xdata::Table ExtractTableFromAttachment(xoap::MessageReference reply);
  void insertRandomRow(xdata::Table &table);
  xdata::TimeVal * randomDate();
//  template <class T> T * randomNumber();
template <class T> T * randomNumber() {
        switch (rand()%3) {
                case 0:
                        return new T(std::numeric_limits<T>::quiet_NaN());
                case 1:
                        //std::cout << "To infinity... and beyond!" << std::endl;
                        return new T(std::numeric_limits<T>::infinity());
                default:
                        if (std::numeric_limits<T>::is_integer) {
                                uint64_t range=(uint64_t)std::numeric_limits<T>::max()-std::numeric_limits<T>::min();
                                if (range<RAND_MAX) range++; //make sure we can get both endpoints
                                std::cout << "random with beginning: " << std::numeric_limits<T>::min() << "max: " << std::numeric_limits<T>::max() << " range: " << range << std::endl;
                                //rand returns 32 bit numbers, so square it to possibly get a 64 bit number
                                uint64_t r=((uint64_t)rand())*((uint64_t)rand());
                                return new T(std::numeric_limits<T>::min()+r%range); //this will not generate any 64 bit numbers
                        } else {
                                return new T(std::numeric_limits<T>::min()+(rand()-RAND_MAX/2)/100000);
                        }
        }
}


private:
  //
  void retrievePointersToModuleMEs() const;
  void fillSummaryObjects();

public:
  // this client has a web interface:  
  SiStripHistoricInfoWebInterface * webInterface_p;

private:
  //
  mutable bool firstTime;
  mutable int  firstUpdate;
  //
  mutable std::map<uint32_t, std::vector<MonitorElement *> > ClientPointersToModuleMEs;
  mutable std::map<uint32_t, std::pair<double, double> > ClusterChargeMeanRMS;
  mutable std::map<uint32_t, std::pair<double, double> > OccupancyMeanRMS;

private:

};

// You always need to have this line! Do not remove:
XDAQ_INSTANTIATOR_IMPL(SiStripHistoricInfoClient)

#endif
