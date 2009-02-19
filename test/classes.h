//---- Add the Class you need 

#include "CondFormats/SiStripObjects/interface/SiStripSummary.h"

#include "CondCore/Utilities/interface/CondCachedIter.h"

#include "DQM/SiStripHistoricInfoClient/test/HistoricInspector.h"

#include "DQM/SiStripHistoricInfoClient/test/GraphAnalysis.h"

#include "DQM/SiStripHistoricInfoClient/test/TwoDTrends.h"


namespace { 

  CondCachedIter<SiStripSummary> dummy13;

  HistoricInspector dummy1;
  GraphAnalysis dummy2;
  TwoDTrends dummy3;
}

