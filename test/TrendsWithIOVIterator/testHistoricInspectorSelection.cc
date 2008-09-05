{

gROOT->Reset();



HistoricInspector A;
//A.setDB("oracle://cms_orcoff_int2r/CMS_COND_STRIP", "SiStripSummary_test1","cms_cond_strip","SSWDC3MCAI8HQHTC");
//A.setDB("oracle://devdb10/CMS_COND_STRIP", "SiStripSummary_test2","cms_cond_strip","w3807dev","COND/Services/TBufferBlobStreamingService");
A.setDB("sqlite_file:historicDQM.db", "SiStripSummary_test1","cms_cond_strip","w3807dev","");

A.setDebug(1);

//A.createTrend(1, "Summary_NumberOfClusters_OffTrack@mean","CanvasName.eps", 51093);

//A.createTrend(1, "Summary_NumberOfClusters_OffTrack@mean");
//A.createTrend(0, "NumberOfTracks_CKFTk@mean");


// //TK
A.createTrend(0, "NumberOfTracks_CKFTk@mean,NumberOfRecHitsPerTrack_CKFTk@mean,Chi2_CKFTk@mean", "CKFTk_trends.eps");

A.createTrend(0, "NumberOfTracks_CKFTk@mean,NumberOfRecHitsPerTrack_CKFTk@mean,Chi2_CKFTk@mean", "CKFTk_trends_Ntrack.eps","NumberOfTracks_CKFTk@mean > 0");

A.createTrend(0, "NumberOfTracks_CKFTk@mean,NumberOfRecHitsPerTrack_CKFTk@mean,Chi2_CKFTk@mean", "CKFTk_trends_Ntrack_rechit.eps","NumberOfTracks_CKFTk@mean>0 && NumberOfRecHitsPerTrack_CKFTk@mean>0");



}
