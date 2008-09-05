{

gROOT->Reset();



HistoricInspector A;
//A.setDB("oracle://cms_orcoff_int2r/CMS_COND_STRIP", "SiStripSummary_test1","cms_cond_strip","SSWDC3MCAI8HQHTC");
//A.setDB("oracle://devdb10/CMS_COND_STRIP", "SiStripSummary_test2","cms_cond_strip","w3807dev","COND/Services/TBufferBlobStreamingService");
A.setDB("sqlite_file:historicDQM.db", "SiStripSummary_test1","cms_cond_strip","w3807dev","");

A.setDebug(0);

//A.createTrend(1, "Summary_NumberOfClusters_OffTrack@mean","CanvasName.eps", 51093);

//A.createTrend(1, "Summary_NumberOfClusters_OffTrack@mean");
//A.createTrend(0, "NumberOfTracks_CKFTk@mean");


// //TK
A.createTrend(0, "NumberOfTracks_CKFTk@mean", "CKFTk_trends.eps","NumberOfTracks_CKFTk@entries>0 && Summary_TotalNumberOfClusters_OffTrack@mean<2.3");

// //TIB
//A.createTrend(1, "Summary_TotalNumberOfClusters_OffTrack@mean,Summary_ClusterCharge_OffTrack@mean,Summary_ClusterNoise_OffTrack@mean,Summary_ClusterStoN_OffTrack@mean,Summary_ClusterWidth_OffTrack@mean","TIB_OffTrack.eps");
//A.createTrend(1, "Summary_TotalNumberOfClusters_OnTrack@mean,Summary_ClusterChargeCorr_OnTrack@landauPeak,Summary_ClusterNoise_OnTrack@gaussMean,Summary_ClusterStoNCorr_OnTrack@landauPeak,Summary_ClusterWidth_OnTrack@mean","TIB_OnTrack.eps");


}
