{
 
  TFile *f  = TFile::Open("DQM.root","read");
  if( f->IsZombie() || f == 0 ) return;
  
  TH1F *h = 0;
  h = (TH1F*)f->Get("DQMData/Run xxxx/SiStrip/Run summary/Tracks/NumberOfTracks_CKFTk");
 
  std::cout << "**********************************" << std::endl;
  if (h!=0) std::cout << "File contains " << h->GetEntries() << " events" << std::endl;
  else      std::cout << "No histogram found" << std::endl;
  std::cout << "**********************************" << std::endl;
}
