{

gROOT->Reset();


HistoricInspector A;
//A.setDB("oracle://cms_orcoff_int2r/CMS_COND_STRIP", "SiStripSummary_test1","cms_cond_strip","SSWDC3MCAI8HQHTC");
A.setDB("oracle://devdb10/CMS_COND_STRIP", "historicFromT0_shift","cms_cond_strip","","COND/Services/TBufferBlobStreamingService");
//A.setDB("sqlite_file:historicDQM.db", "SiStripSummary_test2","cms_cond_strip","w3807dev","");

A.setDebug(1);
A.setDoStat(1);

//A.setBlackList("64741,64742,64747,66706,66720,67033,67085,66692,66703,66714,66733,66739,66740,66878,66955,66985,66989,66993,66711,66716,66722,66746,66748,66756,66709,66783,66887,66893,66904,66910,66987");
A.setBlackList("64741,64742,64747");

//week 42 : 65941-66746
//week 43 : 66748-67647

A.createTrend("0@NumberOfTracks_CKFTk@entries,0@NumberOfTracks_CKFTk@mean,0@NumberOfRecHitsPerTrack_CKFTk@mean,0@Chi2_CKFTk@mean,0@Chi2_CKFTk@entries","CKFTk_trends.gif",0,"0@NumberOfRecHitsPerTrack_CKFTk@entries>0000",firstRun,lastRun);
A.createTrend("0@NumberOfTracks_RSTk@entries,0@NumberOfTracks_RSTk@mean,0@NumberOfRecHitsPerTrack_RSTk@mean,0@Chi2_RSTk@mean,0@Chi2_RSTk@entries", "RSTk_trends.gif",0,"0@NumberOfRecHitsPerTrack_RSTk@entries>0000",firstRun,lastRun);
A.createTrend("0@NumberOfTracks_CosmicTk@entries,0@NumberOfTracks_CosmicTk@mean,0@NumberOfRecHitsPerTrack_CosmicTk@mean,0@Chi2_CosmicTk@mean,0@Chi2_CosmicTk@entries", "CosmicTk_trends.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);

A.createTrend("0@Chi2_CKFTk@entries", "number_of_tracks.gif",1,"0@NumberOfRecHitsPerTrack_CKFTk@entries>0",firstRun,lastRun);
A.createTrend("0@NumberOfTracks_CKFTk@entries", "number_of_events.gif",1,"0@NumberOfRecHitsPerTrack_CKFTk@entries>0",firstRun,lastRun);
A.createTrend("0@NumberOfTracks_CKFTk@mean","mean_number_of_tracks_per_event.gif",0,"0@NumberOfRecHitsPerTrack_CKFTk@entries>0",firstRun,lastRun);

A.createTrend("1@Summary_TotalNumberOfClusters_OnTrack@mean,1@Summary_ClusterChargeCorr_OnTrack@landauPeak,1@Summary_ClusterNoise_OnTrack@gaussMean,1@Summary_ClusterStoNCorr_OnTrack@landauPeak,1@Summary_ClusterWidth_OnTrack@mean","OnTrackClusters_1.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);
A.createTrend("2@Summary_TotalNumberOfClusters_OnTrack@mean,2@Summary_ClusterChargeCorr_OnTrack@landauPeak,2@Summary_ClusterNoise_OnTrack@gaussMean,2@Summary_ClusterStoNCorr_OnTrack@landauPeak,2@Summary_ClusterWidth_OnTrack@mean","OnTrackClusters_2.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);
A.createTrend("3@Summary_TotalNumberOfClusters_OnTrack@mean,3@Summary_ClusterChargeCorr_OnTrack@landauPeak,3@Summary_ClusterNoise_OnTrack@gaussMean,3@Summary_ClusterStoNCorr_OnTrack@landauPeak,3@Summary_ClusterWidth_OnTrack@mean","OnTrackClusters_3.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);
A.createTrend("4@Summary_TotalNumberOfClusters_OnTrack@mean,4@Summary_ClusterChargeCorr_OnTrack@landauPeak,4@Summary_ClusterNoise_OnTrack@gaussMean,4@Summary_ClusterStoNCorr_OnTrack@landauPeak,4@Summary_ClusterWidth_OnTrack@mean","OnTrackClusters_4.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);

A.createTrend("1@Summary_TotalNumberOfClusters_OffTrack@mean,1@Summary_ClusterCharge_OffTrack@landauPeak,1@Summary_ClusterNoise_OffTrack@gaussMean,1@Summary_ClusterStoN_OffTrack@landauPeak,1@Summary_ClusterWidth_OffTrack@mean","OffTrackClusters_1.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);
A.createTrend("2@Summary_TotalNumberOfClusters_OffTrack@mean,2@Summary_ClusterCharge_OffTrack@landauPeak,2@Summary_ClusterNoise_OffTrack@gaussMean,2@Summary_ClusterStoN_OffTrack@landauPeak,2@Summary_ClusterWidth_OffTrack@mean","OffTrackClusters_2.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);
A.createTrend("3@Summary_TotalNumberOfClusters_OffTrack@mean,3@Summary_ClusterCharge_OffTrack@landauPeak,3@Summary_ClusterNoise_OffTrack@gaussMean,3@Summary_ClusterStoN_OffTrack@landauPeak,3@Summary_ClusterWidth_OffTrack@mean","OffTrackClusters_3.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);
A.createTrend("4@Summary_TotalNumberOfClusters_OffTrack@mean,4@Summary_ClusterCharge_OffTrack@landauPeak,4@Summary_ClusterNoise_OffTrack@gaussMean,4@Summary_ClusterStoN_OffTrack@landauPeak,4@Summary_ClusterWidth_OffTrack@mean","OffTrackClusters_4.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);



}
