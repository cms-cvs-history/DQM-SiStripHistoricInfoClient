{

gSystem->Load("libFWCoreFWLite.so");  
gSystem->Load("libCondFormatsSiStripObjects"); 
gSystem->Load("libCondCoreUtilities"); 
gSystem->Load("libDQMSiStripHistoricInfoClient.so");

AutoLibraryLoader::enable();
}
