{

gROOT->Reset();
gROOT->ProcessLine(".L HistoricInspector.cc");

HistoricInspector A;
//A.setDB("oracle://cms_orcoff_int2r/CMS_COND_STRIP", "SiStripSummary_test1","cms_cond_strip","SSWDC3MCAI8HQHTC");
//A.setDB("oracle://devdb10/CMS_COND_STRIP", "SiStripSummary_test2","cms_cond_strip","w3807dev","COND/Services/TBufferBlobStreamingService");
A.setDB("sqlite_file:historicDQM.db", "SiStripSummary_test1","cms_cond_strip","w3807dev","");

A.setDebug(1);
//A.createTrend(1, "Summary_NumberOfClusters_OffTrack@mean",51093);

//A.createTrend(1, "Summary_NumberOfClusters_OffTrack@mean");
//A.createTrend(0, "NumberOfTracks_CKFTk@mean");


// //TK
A.createTrend(0, "NumberOfTracks_CKFTk@entries,NumberOfTracks_CKFTk@mean,NumberOfRecHitsPerTrack_CKFTk@mean,Chi2_CKFTk@mean");
//A.createTrend(0, "NumberOfTracks_RSTk@entries,NumberOfTracks_RSTk@mean,NumberOfRecHitsPerTrack_RSTk@mean,Chi2_RSTk@mean");
//A.createTrend(0, "NumberOfTracks_CosmicTk@entries,NumberOfTracks_CosmicTk@mean,NumberOfRecHitsPerTrack_CosmicTk@mean,Chi2_CKFTk@mean");

// //TIB
//A.createTrend(1, "Summary_NumberOfClusters_OffTrack@mean,Summary_cCharge_OffTrack@mean,Summary_cNoise_OffTrack@mean,Summary_cStoN_OffTrack@mean,Summary_cWidth_OffTrack@mean");
A.createTrend(1, "Summary_NumberOfClusters_OnTrack@mean,Summary_cChargeCorr_OnTrack@landauPeak,Summary_cNoise_OnTrack@gaussMean,Summary_cStoNCorr_OnTrack@landauPeak,Summary_cWidth_OnTrack@mean");

// //TOB
//A.createTrend(2, "Summary_NumberOfClusters_OffTrack@mean,Summary_cCharge_OffTrack@mean,Summary_cNoise_OffTrack@mean,Summary_cStoN_OffTrack@mean,Summary_cWidth_OffTrack@mean");
A.createTrend(2, "Summary_NumberOfClusters_OnTrack@mean,Summary_cChargeCorr_OnTrack@landauPeak,Summary_cNoise_OnTrack@gaussMean,Summary_cStoNCorr_OnTrack@landauPeak,Summary_cWidth_OnTrack@mean");


// //TID
// A.createTrend(3, "Summary_NumberOfClusters_OffTrack@mean,Summary_cCharge_OffTrack@mean,Summary_cNoise_OffTrack@mean,Summary_cStoN_OffTrack@mean,Summary_cWidth_OffTrack@mean");
//A.createTrend(3, "Summary_NumberOfClusters_OnTrack@mean,Summary_cChargeCorr_OnTrack@landauPeak,Summary_cNoise_OnTrack@gaussMean,Summary_cStoNCorr_OnTrack@landauPeak,Summary_cWidth_OnTrack@mean");


// //TEC
// A.createTrend(4, "Summary_NumberOfClusters_OffTrack@mean,Summary_cCharge_OffTrack@mean,Summary_cNoise_OffTrack@mean,Summary_cStoN_OffTrack@mean,Summary_cWidth_OffTrack@mean");
// A.createTrend(4, "Summary_NumberOfClusters_OnTrack@mean,Summary_cChargeCorr_OnTrack@landauPeak,Summary_cNoise_OnTrack@gaussMean,Summary_cStoNCorr_OnTrack@landauPeak,Summary_cWidth_OnTrack@mean");



}
