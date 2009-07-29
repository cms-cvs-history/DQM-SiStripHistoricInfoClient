#include "DQM/SiStripHistoricInfoClient/test/HDQMInspectorConfigSiStrip.h"

HDQMInspectorConfigSiStrip::HDQMInspectorConfigSiStrip ()
{
}


HDQMInspectorConfigSiStrip::~HDQMInspectorConfigSiStrip ()
{
}


std::string HDQMInspectorConfigSiStrip::translateDetId(const uint32_t id) const
{
  switch (id) {
    case 1:   
       return "TIB";
    case 2:   
       return "TOB";
    case 3:   
       return "TID";
    case 4:   
       return "TEC";
    case 11:  
       return "TIB_Layer1";
    case 12:  
       return "TIB_Layer2";
    case 13:  
       return "TIB_Layer3";
    case 14:  
       return "TIB_Layer4";
    case 21:  
       return "TOB_Layer1";
    case 22:  
       return "TOB_Layer2";
    case 23:  
       return "TOB_Layer3";
    case 24:  
       return "TOB_Layer4";
    case 25:  
       return "TOB_Layer5";
    case 26:  
       return "TOB_Layer6";
    case 311: 
       return "TID_Side1_Layer1";
    case 312: 
       return "TID_Side1_Layer2";
    case 313: 
       return "TID_Side1_Layer3";
    case 321: 
       return "TID_Side2_Layer1";
    case 322: 
       return "TID_Side2_Layer2";
    case 323: 
       return "TID_Side2_Layer3";
    default:
      return "???";
  };
}
