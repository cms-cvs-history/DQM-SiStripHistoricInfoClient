{

gROOT->Reset();
gROOT->ProcessLine(".x ~/rootlogon.C"); // in principle not needed but ...
gROOT->ProcessLine(".L HistoricInspector.cc");

HistoricInspector A;
//A.setDB("oracle://cms_orcoff_int2r/CMS_COND_STRIP", "SiStripSummary_test1","cms_cond_strip","SSWDC3MCAI8HQHTC");
//A.setDB("oracle://devdb10/CMS_COND_STRIP", "SiStripSummary_test2","cms_cond_strip","w3807dev","COND/Services/TBufferBlobStreamingService");
A.setDB("sqlite_file:historicDQM.db", "SiStripSummary_test2","cms_cond_strip","w3807dev","");

A.setDebug(1);
//A.createTrend(1, "Summary_TotalNumberOfClusters_OffTrack@mean");
//A.createTrend(0, "NumberOfTracks_CKFTk@mean");

A.setBlackList("57575, 57587, 57593, 57613, 57615, 57686, 57798, 57815, 57815, 57872, 57889");


// //TK
A.createTrend(0, "NumberOfTracks_CKFTk@entries,NumberOfTracks_CKFTk@mean,NumberOfRecHitsPerTrack_CKFTk@mean,Chi2_CKFTk@mean","CKFTracks");
A.createTrend(0, "NumberOfTracks_RSTk@entries,NumberOfTracks_RSTk@mean,NumberOfRecHitsPerTrack_RSTk@mean,Chi2_RSTk@mean","RSTracks");
A.createTrend(0, "NumberOfTracks_CosmicTk@entries,NumberOfTracks_CosmicTk@mean,NumberOfRecHitsPerTrack_CosmicTk@mean,Chi2_CosmicTk@mean","CosmicTracks");

// //TIB
A.createTrend(1, "Summary_TotalNumberOfClusters_OffTrack@mean,Summary_ClusterCharge_OffTrack@mean,Summary_ClusterNoise_OffTrack@mean,Summary_ClusterStoN_OffTrack@mean,Summary_ClusterWidth_OffTrack@mean","ClustersOffTrack");
A.createTrend(1, "Summary_TotalNumberOfClusters_OnTrack@mean,Summary_ClusterChargeCorr_OnTrack@landauPeak,Summary_ClusterNoise_OnTrack@gaussMean,Summary_ClusterStoNCorr_OnTrack@landauPeak,Summary_ClusterWidth_OnTrack@mean","ClustersOnTrack");

// //TOB
A.createTrend(2, "Summary_TotalNumberOfClusters_OffTrack@mean,Summary_ClusterCharge_OffTrack@mean,Summary_ClusterNoise_OffTrack@mean,Summary_ClusterStoN_OffTrack@mean,Summary_ClusterWidth_OffTrack@mean","ClustersOffTrack");
A.createTrend(2, "Summary_TotalNumberOfClusters_OnTrack@mean,Summary_ClusterChargeCorr_OnTrack@landauPeak,Summary_ClusterNoise_OnTrack@gaussMean,Summary_ClusterStoNCorr_OnTrack@landauPeak,Summary_ClusterWidth_OnTrack@mean","ClustersOnTrack");


// //TID
A.createTrend(3, "Summary_TotalNumberOfClusters_OffTrack@mean,Summary_ClusterCharge_OffTrack@mean,Summary_ClusterNoise_OffTrack@mean,Summary_ClusterStoN_OffTrack@mean,Summary_ClusterWidth_OffTrack@mean","ClustersOffTrack");
A.createTrend(3, "Summary_TotalNumberOfClusters_OnTrack@mean,Summary_ClusterChargeCorr_OnTrack@landauPeak,Summary_ClusterNoise_OnTrack@gaussMean,Summary_ClusterStoNCorr_OnTrack@landauPeak,Summary_ClusterWidth_OnTrack@mean","ClustersOnTrack");


// //TEC
A.createTrend(4, "Summary_TotalNumberOfClusters_OffTrack@mean,Summary_ClusterCharge_OffTrack@mean,Summary_ClusterNoise_OffTrack@mean,Summary_ClusterStoN_OffTrack@mean,Summary_ClusterWidth_OffTrack@mean","ClustersOffTrack");
A.createTrend(4, "Summary_TotalNumberOfClusters_OnTrack@mean,Summary_ClusterChargeCorr_OnTrack@landauPeak,Summary_ClusterNoise_OnTrack@gaussMean,Summary_ClusterStoNCorr_OnTrack@landauPeak,Summary_ClusterWidth_OnTrack@mean","ClustersOnTrack");



}
