{
gSystem->Load("libFWCoreFWLite.so");  
gSystem->Load("libtestSiStripHistoricDQM.so"); 
gSystem->Load("libCondFormatsSiStripObjects.so"); 
// gSystem->Load("libIOPoolCMSSealPlugin.so"); 

AutoLibraryLoader::enable();
}
