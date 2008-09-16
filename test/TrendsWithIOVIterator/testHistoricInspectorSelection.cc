{

gROOT->Reset();


HistoricInspector A;
//A.setDB("oracle://cms_orcoff_int2r/CMS_COND_STRIP", "SiStripSummary_test1","cms_cond_strip","SSWDC3MCAI8HQHTC");
//A.setDB("oracle://devdb10/CMS_COND_STRIP", "SiStripSummary_test2","cms_cond_strip","w3807dev","COND/Services/TBufferBlobStreamingService");
A.setDB("sqlite_file:historicDQM.db", "SiStripSummary_test2","cms_cond_strip","w3807dev","");

A.setDebug(1);

//A.createTrend(1, "Summary_NumberOfClusters_OffTrack@mean","CanvasName.eps", 51093);

//A.createTrend(1, "Summary_NumberOfClusters_OffTrack@mean");
//A.createTrend(0, "NumberOfTracks_CKFTk@mean");


// //TK
//A.createTrend("0@NumberOfTracks_CKFTk@mean,1@Summary_NumberOfClusters_OffTrack@mean", "CKFTk_trends.eps");

//A.createTrend(0, "NumberOfTracks_CKFTk@mean,NumberOfRecHitsPerTrack_CKFTk@mean,Chi2_CKFTk@mean", "CKFTk_trends.eps");

A.createTrend("0@NumberOfTracks_CKFTk@entries,0@NumberOfRecHitsPerTrack_CKFTk@entries,0@NumberOfTracks_CKFTk@mean,0@NumberOfRecHitsPerTrack_CKFTk@mean,0@Chi2_CKFTk@mean,1@Summary_TotalNumberOfClusters_OnTrack@mean,1@Summary_ClusterStoNCorr_OnTrack@landauPeak,1@Summary_ClusterStoNCorr_OnTrack@entries,1@Summary_ClusterWidth_OnTrack@mean,1@Summary_ClusterStoN_OffTrack@mean,1@Summary_TotalNumberOfClusters_OffTrack@mean,1@Summary_ClusterWidth_OffTrack@mean,2@Summary_TotalNumberOfClusters_OnTrack@mean,2@Summary_ClusterStoNCorr_OnTrack@landauPeak,2@Summary_ClusterWidth_OnTrack@mean,2@Summary_ClusterStoNCorr_OnTrack@entries,2@Summary_TotalNumberOfClusters_OffTrack@mean,2@Summary_ClusterStoN_OffTrack@mean,2@Summary_ClusterWidth_OffTrack@mean", "CKFTk_trends_Ntrack.eps","0@NumberOfTracks_CKFTk@mean>0 && 0@NumberOfRecHitsPerTrack_CKFTk@entries>500",57500);

//A.createTrend(0, "NumberOfTracks_CKFTk@mean,NumberOfRecHitsPerTrack_CKFTk@mean,Chi2_CKFTk@mean", "CKFTk_trends_Ntrack_rechit.eps","NumberOfRecHitsPerTrack_CKFTk@mean>0 && (NumberOfRecHitsPerTrack_CKFTk@mean<15 || Chi2_CKFTk@mean<30 )");



}
