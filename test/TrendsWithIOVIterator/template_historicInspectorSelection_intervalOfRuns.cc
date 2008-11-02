{

gROOT->Reset();


HistoricInspector A;
A.setDB("oracle://devdb10/CMS_COND_STRIP", "historicFromT0_shift","cms_cond_strip","","COND/Services/TBufferBlobStreamingService");
//A.setDB("sqlite_file:historicDQM.db", "SiStripSummary_test2","cms_cond_strip","w3807dev","");

A.setDebug(1);
A.setDoStat(1);

//A.setBlackList("64741,64742,64747,66706,66720,67033,67085,66692,66703,66714,66733,66739,66740,66878,66955,66985,66989,66993,66711,66716,66722,66746,66748,66756,66709,66783,66887,66893,66904,66910,66987");
A.setBlackList("64741,64742,64747");

//week 42 : 65941-66746
//week 43 : 66748-67647


//

A.createTrend("0@Chi2_CKFTk@entries", "number_of_tracks.gif",1,"0@NumberOfRecHitsPerTrack_CKFTk@entries>0",firstRun,lastRun);
A.createTrend("0@NumberOfTracks_CKFTk@entries", "number_of_events.gif",1,"0@NumberOfRecHitsPerTrack_CKFTk@entries>0",firstRun,lastRun);
A.createTrend("0@NumberOfTracks_CKFTk@mean","mean_number_of_tracks_per_event.gif",0,"0@NumberOfRecHitsPerTrack_CKFTk@entries>0",firstRun,lastRun);

//Tracks

A.createTrend("0@NumberOfTracks_CKFTk@entries,0@NumberOfTracks_CKFTk@mean,0@NumberOfRecHitsPerTrack_CKFTk@mean,0@Chi2_CKFTk@mean,0@Chi2_CKFTk@entries","CKFTk_trends.gif",0,"0@NumberOfRecHitsPerTrack_CKFTk@entries>0000",firstRun,lastRun);
A.createTrend("0@NumberOfTracks_RSTk@entries,0@NumberOfTracks_RSTk@mean,0@NumberOfRecHitsPerTrack_RSTk@mean,0@Chi2_RSTk@mean,0@Chi2_RSTk@entries", "RSTk_trends.gif",0,"0@NumberOfRecHitsPerTrack_RSTk@entries>0000",firstRun,lastRun);
A.createTrend("0@NumberOfTracks_CosmicTk@entries,0@NumberOfTracks_CosmicTk@mean,0@NumberOfRecHitsPerTrack_CosmicTk@mean,0@Chi2_CosmicTk@mean,0@Chi2_CosmicTk@entries", "CosmicTk_trends.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);

// Clusters TIB, TOB, TEC, TID

A.createTrend("1@Summary_TotalNumberOfClusters_OnTrack@mean,1@Summary_ClusterChargeCorr_OnTrack@landauPeak,1@Summary_ClusterNoise_OnTrack@gaussMean,1@Summary_ClusterStoNCorr_OnTrack@landauPeak,1@Summary_ClusterWidth_OnTrack@mean","OnTrackClusters_1.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);
A.createTrend("2@Summary_TotalNumberOfClusters_OnTrack@mean,2@Summary_ClusterChargeCorr_OnTrack@landauPeak,2@Summary_ClusterNoise_OnTrack@gaussMean,2@Summary_ClusterStoNCorr_OnTrack@landauPeak,2@Summary_ClusterWidth_OnTrack@mean","OnTrackClusters_2.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);
A.createTrend("3@Summary_TotalNumberOfClusters_OnTrack@mean,3@Summary_ClusterChargeCorr_OnTrack@landauPeak,3@Summary_ClusterNoise_OnTrack@gaussMean,3@Summary_ClusterStoNCorr_OnTrack@landauPeak,3@Summary_ClusterWidth_OnTrack@mean","OnTrackClusters_3.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);
A.createTrend("4@Summary_TotalNumberOfClusters_OnTrack@mean,4@Summary_ClusterChargeCorr_OnTrack@landauPeak,4@Summary_ClusterNoise_OnTrack@gaussMean,4@Summary_ClusterStoNCorr_OnTrack@landauPeak,4@Summary_ClusterWidth_OnTrack@mean","OnTrackClusters_4.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);

A.createTrend("1@Summary_TotalNumberOfClusters_OffTrack@mean,1@Summary_ClusterCharge_OffTrack@landauPeak,1@Summary_ClusterNoise_OffTrack@gaussMean,1@Summary_ClusterStoN_OffTrack@landauPeak,1@Summary_ClusterWidth_OffTrack@mean","OffTrackClusters_1.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);
A.createTrend("2@Summary_TotalNumberOfClusters_OffTrack@mean,2@Summary_ClusterCharge_OffTrack@landauPeak,2@Summary_ClusterNoise_OffTrack@gaussMean,2@Summary_ClusterStoN_OffTrack@landauPeak,2@Summary_ClusterWidth_OffTrack@mean","OffTrackClusters_2.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);
A.createTrend("3@Summary_TotalNumberOfClusters_OffTrack@mean,3@Summary_ClusterCharge_OffTrack@landauPeak,3@Summary_ClusterNoise_OffTrack@gaussMean,3@Summary_ClusterStoN_OffTrack@landauPeak,3@Summary_ClusterWidth_OffTrack@mean","OffTrackClusters_3.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);
A.createTrend("4@Summary_TotalNumberOfClusters_OffTrack@mean,4@Summary_ClusterCharge_OffTrack@landauPeak,4@Summary_ClusterNoise_OffTrack@gaussMean,4@Summary_ClusterStoN_OffTrack@landauPeak,4@Summary_ClusterWidth_OffTrack@mean","OffTrackClusters_4.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0000",firstRun,lastRun);

// Clusters Layer levels

A.createTrend("11@Summary_ClusterChargeCorr__OnTrack@landauPeak,11@Summary_ClusterNoise__OnTrack@gaussMean,11@Summary_ClusterStoNCorr__OnTrack@landauPeak,11@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_11.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);
A.createTrend("12@Summary_ClusterChargeCorr__OnTrack@landauPeak,12@Summary_ClusterNoise__OnTrack@gaussMean,12@Summary_ClusterStoNCorr__OnTrack@landauPeak,12@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_12.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);
A.createTrend("13@Summary_ClusterChargeCorr__OnTrack@landauPeak,13@Summary_ClusterNoise__OnTrack@gaussMean,13@Summary_ClusterStoNCorr__OnTrack@landauPeak,13@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_13.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);
A.createTrend("14@Summary_ClusterChargeCorr__OnTrack@landauPeak,14@Summary_ClusterNoise__OnTrack@gaussMean,14@Summary_ClusterStoNCorr__OnTrack@landauPeak,14@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_14.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);

A.createTrend("21@Summary_ClusterChargeCorr__OnTrack@landauPeak,21@Summary_ClusterNoise__OnTrack@gaussMean,21@Summary_ClusterStoNCorr__OnTrack@landauPeak,21@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_21.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);
A.createTrend("22@Summary_ClusterChargeCorr__OnTrack@landauPeak,22@Summary_ClusterNoise__OnTrack@gaussMean,22@Summary_ClusterStoNCorr__OnTrack@landauPeak,22@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_22.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);
A.createTrend("23@Summary_ClusterChargeCorr__OnTrack@landauPeak,23@Summary_ClusterNoise__OnTrack@gaussMean,23@Summary_ClusterStoNCorr__OnTrack@landauPeak,23@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_23.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);
A.createTrend("24@Summary_ClusterChargeCorr__OnTrack@landauPeak,24@Summary_ClusterNoise__OnTrack@gaussMean,24@Summary_ClusterStoNCorr__OnTrack@landauPeak,24@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_24.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);
A.createTrend("25@Summary_ClusterChargeCorr__OnTrack@landauPeak,25@Summary_ClusterNoise__OnTrack@gaussMean,25@Summary_ClusterStoNCorr__OnTrack@landauPeak,25@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_25.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);
A.createTrend("26@Summary_ClusterChargeCorr__OnTrack@landauPeak,26@Summary_ClusterNoise__OnTrack@gaussMean,26@Summary_ClusterStoNCorr__OnTrack@landauPeak,26@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_26.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);

A.createTrend("311@Summary_ClusterChargeCorr__OnTrack@landauPeak,311@Summary_ClusterNoise__OnTrack@gaussMean,311@Summary_ClusterStoNCorr__OnTrack@landauPeak,311@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_311.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);
A.createTrend("312@Summary_ClusterChargeCorr__OnTrack@landauPeak,312@Summary_ClusterNoise__OnTrack@gaussMean,312@Summary_ClusterStoNCorr__OnTrack@landauPeak,312@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_312.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);
A.createTrend("313@Summary_ClusterChargeCorr__OnTrack@landauPeak,313@Summary_ClusterNoise__OnTrack@gaussMean,313@Summary_ClusterStoNCorr__OnTrack@landauPeak,313@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_313.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);

A.createTrend("321@Summary_ClusterChargeCorr__OnTrack@landauPeak,321@Summary_ClusterNoise__OnTrack@gaussMean,321@Summary_ClusterStoNCorr__OnTrack@landauPeak,321@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_321.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);
A.createTrend("322@Summary_ClusterChargeCorr__OnTrack@landauPeak,322@Summary_ClusterNoise__OnTrack@gaussMean,322@Summary_ClusterStoNCorr__OnTrack@landauPeak,322@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_322.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);
A.createTrend("323@Summary_ClusterChargeCorr__OnTrack@landauPeak,323@Summary_ClusterNoise__OnTrack@gaussMean,323@Summary_ClusterStoNCorr__OnTrack@landauPeak,323@Summary_ClusterWidth__OnTrack@mean","OnTrackClusters_323.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",firstRun,lastRuns);

// Clusters Off track Layer levels

A.createTrend("11@Summary_ClusterCharge__OffTrack@landauPeak,11@Summary_ClusterNoise__OffTrack@gaussMean,11@Summary_ClusterStoN__OffTrack@landauPeak,11@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_11.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);
A.createTrend("12@Summary_ClusterCharge__OffTrack@landauPeak,12@Summary_ClusterNoise__OffTrack@gaussMean,12@Summary_ClusterStoN__OffTrack@landauPeak,12@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_12.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);
A.createTrend("13@Summary_ClusterCharge__OffTrack@landauPeak,13@Summary_ClusterNoise__OffTrack@gaussMean,13@Summary_ClusterStoN__OffTrack@landauPeak,13@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_13.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);
A.createTrend("14@Summary_ClusterCharge__OffTrack@landauPeak,14@Summary_ClusterNoise__OffTrack@gaussMean,14@Summary_ClusterStoN__OffTrack@landauPeak,14@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_14.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);

A.createTrend("21@Summary_ClusterCharge__OffTrack@landauPeak,21@Summary_ClusterNoise__OffTrack@gaussMean,21@Summary_ClusterStoN__OffTrack@landauPeak,21@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_21.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);
A.createTrend("22@Summary_ClusterCharge__OffTrack@landauPeak,22@Summary_ClusterNoise__OffTrack@gaussMean,22@Summary_ClusterStoN__OffTrack@landauPeak,22@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_22.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);
A.createTrend("23@Summary_ClusterCharge__OffTrack@landauPeak,23@Summary_ClusterNoise__OffTrack@gaussMean,23@Summary_ClusterStoN__OffTrack@landauPeak,23@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_23.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);
A.createTrend("24@Summary_ClusterCharge__OffTrack@landauPeak,24@Summary_ClusterNoise__OffTrack@gaussMean,24@Summary_ClusterStoN__OffTrack@landauPeak,24@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_24.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);
A.createTrend("25@Summary_ClusterCharge__OffTrack@landauPeak,25@Summary_ClusterNoise__OffTrack@gaussMean,25@Summary_ClusterStoN__OffTrack@landauPeak,25@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_25.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);
A.createTrend("26@Summary_ClusterCharge__OffTrack@landauPeak,26@Summary_ClusterNoise__OffTrack@gaussMean,26@Summary_ClusterStoN__OffTrack@landauPeak,26@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_26.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);

A.createTrend("311@Summary_ClusterCharge__OffTrack@landauPeak,311@Summary_ClusterNoise__OffTrack@gaussMean,311@Summary_ClusterStoN__OffTrack@landauPeak,311@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_311.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);
A.createTrend("312@Summary_ClusterCharge__OffTrack@landauPeak,312@Summary_ClusterNoise__OffTrack@gaussMean,312@Summary_ClusterStoN__OffTrack@landauPeak,312@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_312.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);
A.createTrend("313@Summary_ClusterCharge__OffTrack@landauPeak,313@Summary_ClusterNoise__OffTrack@gaussMean,313@Summary_ClusterStoN__OffTrack@landauPeak,313@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_313.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);

A.createTrend("321@Summary_ClusterCharge__OffTrack@landauPeak,321@Summary_ClusterNoise__OffTrack@gaussMean,321@Summary_ClusterStoN__OffTrack@landauPeak,321@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_321.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);
A.createTrend("322@Summary_ClusterCharge__OffTrack@landauPeak,322@Summary_ClusterNoise__OffTrack@gaussMean,322@Summary_ClusterStoN__OffTrack@landauPeak,322@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_322.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);
A.createTrend("323@Summary_ClusterCharge__OffTrack@landauPeak,323@Summary_ClusterNoise__OffTrack@gaussMean,323@Summary_ClusterStoN__OffTrack@landauPeak,323@Summary_ClusterWidth__OffTrack@mean","OffTrackClusters_323.gif",0,"0@NumberOfRecHitsPerTrack_CosmicTk@entries>0",fisrtRun,lastRun);



}
