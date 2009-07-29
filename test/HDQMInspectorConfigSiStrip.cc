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
    default:
      return "???";
  };
}
