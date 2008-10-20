{

gROOT->Reset();


HistoricInspector A;
//A.setDB("oracle://cms_orcoff_int2r/CMS_COND_STRIP", "SiStripSummary_test1","cms_cond_strip","SSWDC3MCAI8HQHTC");
//A.setDB("oracle://devdb10/CMS_COND_STRIP", "SiStripSummary_test2","cms_cond_strip","w3807dev","COND/Services/TBufferBlobStreamingService");
A.setDB("sqlite_file:historicDQM.db", "SiStripSummary_test3","cms_cond_strip","w3807dev","");

A.setDebug(1);


// TK

A.createTrend("0@NumberOfTracks_CKFTk@entries,0@NumberOfTracks_CKFTk@mean,0@NumberOfRecHitsPerTrack_CKFTk@mean,0@Chi2_CKFTk@mean", "CKFTk_trends.png","0@NumberOfRecHitsPerTrack_CKFTk@entries>500");
A.createTrend("0@NumberOfTracks_RSTk@entries,0@NumberOfTracks_RSTk@mean,0@NumberOfRecHitsPerTrack_RSTk@mean,0@Chi2_RSTk@mean", "RSTk_trends.png","0@NumberOfRecHitsPerTrack_RSTk@entries>500");
A.createTrend("0@NumberOfTracks_CosmicTk@entries,0@NumberOfTracks_CosmicTk@mean,0@NumberOfRecHitsPerTrack_CosmicTk@mean,0@Chi2_CosmicTk@mean", "CosmicTk_trends.png","0@NumberOfRecHitsPerTrack_CosmicTk@entries>500");

A.createTrend("1@Summary_TotalNumberOfClusters_OnTrack@mean,1@Summary_ClusterChargeCorr_OnTrack@landauPeak,1@Summary_ClusterNoise_OnTrack@gaussMean,1@Summary_ClusterStoNCorr_OnTrack@landauPeak,1@Summary_ClusterWidth_OnTrack@landauPeak","OnTrackClusters_1.png","0@NumberOfRecHitsPerTrack_CosmicTk@entries>500");
A.createTrend("2@Summary_TotalNumberOfClusters_OnTrack@mean,2@Summary_ClusterChargeCorr_OnTrack@landauPeak,2@Summary_ClusterNoise_OnTrack@gaussMean,2@Summary_ClusterStoNCorr_OnTrack@landauPeak,2@Summary_ClusterWidth_OnTrack@landauPeak","OnTrackClusters_2.png","0@NumberOfRecHitsPerTrack_CosmicTk@entries>500");
A.createTrend("3@Summary_TotalNumberOfClusters_OnTrack@mean,3@Summary_ClusterChargeCorr_OnTrack@landauPeak,3@Summary_ClusterNoise_OnTrack@gaussMean,3@Summary_ClusterStoNCorr_OnTrack@landauPeak,3@Summary_ClusterWidth_OnTrack@landauPeak","OnTrackClusters_3.png","0@NumberOfRecHitsPerTrack_CosmicTk@entries>500");
A.createTrend("4@Summary_TotalNumberOfClusters_OnTrack@mean,4@Summary_ClusterChargeCorr_OnTrack@landauPeak,4@Summary_ClusterNoise_OnTrack@gaussMean,4@Summary_ClusterStoNCorr_OnTrack@landauPeak,4@Summary_ClusterWidth_OnTrack@landauPeak","OnTrackClusters_4.png","0@NumberOfRecHitsPerTrack_CosmicTk@entries>500");

A.createTrend("1@Summary_TotalNumberOfClusters_OffTrack@mean,1@Summary_ClusterCharge_OffTrack@landauPeak,1@Summary_ClusterNoise_OffTrack@gaussMean,1@Summary_ClusterStoN_OffTrack@landauPeak,1@Summary_ClusterWidth_OffTrack@mean","OffTrackClusters_1.png","0@NumberOfRecHitsPerTrack_CosmicTk@entries>500");
A.createTrend("2@Summary_TotalNumberOfClusters_OffTrack@mean,2@Summary_ClusterCharge_OffTrack@landauPeak,2@Summary_ClusterNoise_OffTrack@gaussMean,2@Summary_ClusterStoN_OffTrack@landauPeak,2@Summary_ClusterWidth_OffTrack@mean","OffTrackClusters_2.png","0@NumberOfRecHitsPerTrack_CosmicTk@entries>500");
A.createTrend("3@Summary_TotalNumberOfClusters_OffTrack@mean,3@Summary_ClusterCharge_OffTrack@landauPeak,3@Summary_ClusterNoise_OffTrack@gaussMean,3@Summary_ClusterStoN_OffTrack@landauPeak,3@Summary_ClusterWidth_OffTrack@mean","OffTrackClusters_3.png","0@NumberOfRecHitsPerTrack_CosmicTk@entries>500");
A.createTrend("4@Summary_TotalNumberOfClusters_OffTrack@mean,4@Summary_ClusterCharge_OffTrack@landauPeak,4@Summary_ClusterNoise_OffTrack@gaussMean,4@Summary_ClusterStoN_OffTrack@landauPeak,4@Summary_ClusterWidth_OffTrack@mean","OffTrackClusters_4.png","0@NumberOfRecHitsPerTrack_CosmicTk@entries>500");



}
