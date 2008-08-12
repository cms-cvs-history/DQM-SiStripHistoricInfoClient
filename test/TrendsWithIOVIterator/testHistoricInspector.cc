{

gROOT->Reset();
gROOT->ProcessLine(".L HistoricInspector.cc");

HistoricInspector A;
//A.setDB("oracle://cms_orcoff_int2r/CMS_COND_STRIP", "SiStripSummary_test1","cms_cond_strip","SSWDC3MCAI8HQHTC");
//A.setDB("oracle://devdb10/CMS_COND_STRIP", "SiStripSummary_test2","cms_cond_strip","w3807dev","COND/Services/TBufferBlobStreamingService");
A.setDB("sqlite_file:historicDQM.db", "SiStripSummary_test1","cms_cond_strip","w3807dev","");


//TIB
A.createTrend(1, "Summary_NumberOfClusters_OnTrack@mean,Summary_NumberOfClusters_OffTrack@mean");

//TOB
A.createTrend(2, "Summary_NumberOfClusters_OnTrack@mean,Summary_NumberOfClusters_OffTrack@mean,Summary_cStoNCorr_OnTrack@mean,Summary_cStoNCorr_OnTrack@landauPeak");
//A.createTrend(1, "Summary_NumberOfClusters_OffTrack@mean",51093);


//TK
A.createTrend(0, "NumberOfTracks_CKFTk@mean,NumberOfTracks_CKFTk@entries,NumberOfRecHitsPerTrack_CKFTk@mean,Chi2_CKFTk@mean");
}
