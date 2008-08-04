{


 gROOT->ProcessLine(".L condIter_extractSummary.cpp");

 //===============================================================================
 //  PLOTS vs Run number - TIB=1 TOB=2 TID=3
 //===============================================================================
 
 // Clusters in TIB
 condIter_accessDetIds("sqlite_file:historicDQM.db", "testA", 1, "Summary_NumberOfClusters_OffTrack@mean",0);
/*
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test1_p", 1, "NumberOfClusters_OnTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test1_p", 1, "NumberOfClusters_OnTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test1_p", 1, "NumberOfClusters_OnTrack@entries");

 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test2_p", 1, "NumberOfClusters_OffTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test2_p", 1, "NumberOfClusters_OffTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test2_p", 1, "NumberOfClusters_OffTrack@entries");

 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test3_p", 1, "cChargeCorr_OnTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test3_p", 1, "cChargeCorr_OnTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test3_p", 1, "cChargeCorr_OnTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test4_p", 1, "cCharge_OffTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test4_p", 1, "cCharge_OffTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test4_p", 1, "cCharge_OffTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test5_p", 1, "cWidth_OnTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test5_p", 1, "cWidth_OnTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test5_p", 1, "cWidth_OnTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test6_p", 1, "cWidth_OffTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test6_p", 1, "cWidth_OffTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test6_p", 1, "cWidth_OffTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test7_p", 1, "cNoise_OnTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test7_p", 1, "cNoise_OnTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test7_p", 1, "cNoise_OnTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test8_p", 1, "cNoise_OffTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test8_p", 1, "cNoise_OffTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test8_p", 1, "cNoise_OffTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test9_p", 1, "cStoNCorr_OnTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test9_p", 1, "cStoNCorr_OnTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test9_p", 1, "cStoNCorr_OnTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test10_p", 1, "cStoN_OffTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test10_p", 1, "cStoN_OffTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test10_p", 1, "cStoN_OffTrack@entries");
 
// Clusters in TOB
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test1_p", 2, "NumberOfClusters_OnTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test1_p", 2, "NumberOfClusters_OnTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test1_p", 2, "NumberOfClusters_OnTrack@entries");

 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test2_p", 2, "NumberOfClusters_OffTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test2_p", 2, "NumberOfClusters_OffTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test2_p", 2, "NumberOfClusters_OffTrack@entries");

 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test3_p", 2, "cChargeCorr_OnTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test3_p", 2, "cChargeCorr_OnTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test3_p", 2, "cChargeCorr_OnTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test4_p", 2, "cCharge_OffTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test4_p", 2, "cCharge_OffTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test4_p", 2, "cCharge_OffTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test5_p", 2, "cWidth_OnTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test5_p", 2, "cWidth_OnTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test5_p", 2, "cWidth_OnTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test6_p", 2, "cWidth_OffTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test6_p", 2, "cWidth_OffTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test6_p", 2, "cWidth_OffTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test7_p", 2, "cNoise_OnTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test7_p", 2, "cNoise_OnTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test7_p", 2, "cNoise_OnTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test8_p", 2, "cNoise_OffTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test8_p", 2, "cNoise_OffTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test8_p", 2, "cNoise_OffTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test9_p", 2, "cStoNCorr_OnTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test9_p", 2, "cStoNCorr_OnTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test9_p", 2, "cStoNCorr_OnTrack@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test10_p", 2, "cStoN_OffTrack@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test10_p", 2, "cStoN_OffTrack@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test10_p", 2, "cStoN_OffTrack@entries");
 
 // Tracks
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "Chi2_CosmicTk@mean"); // 0 means full detector
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "Chi2_CosmicTk@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "Chi2_CosmicTk@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "NumberOfTracks_CosmicTk@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "NumberOfTracks_CosmicTk@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "NumberOfTracks_CosmicTk@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "NumberOfRecHitsPerTrack_CosmicTk@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "NumberOfRecHitsPerTrack_CosmicTk@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "NumberOfRecHitsPerTrack_CosmicTk@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "OffTrackNumberOfClusters@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "OffTrackNumberOfClusters@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "OffTrackNumberOfClusters@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "OnTrackNumberOfClusters@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "OnTrackNumberOfClusters@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "OnTrackNumberOfClusters@mean");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "TrackPhi_CosmicTk@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "TrackPhi_CosmicTk@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "TrackPhi_CosmicTk@entries");
 
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "TrackEta_CosmicTk@mean");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "TrackEta_CosmicTk@rms");
 condIter_accessDetIds("sqlite_file:historicDQM_rootFile.db", "test0_p", 0, "TrackEta_CosmicTk@entries");


 //===============================================================================
 //  PLOTS vs TIB=1 TOB=2 TID=3 for a given run, e. g. 51908  
 //===============================================================================
 
 //Clusters
 
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test1_p", 51908, "NumberOfClusters_OnTrack@mean");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test1_p", 51908, "NumberOfClusters_OnTrack@rms");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test1_p", 51908, "NumberOfClusters_OnTrack@entries");

 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test2_p", 51908, "NumberOfClusters_OffTrack@mean");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test2_p", 51908, "NumberOfClusters_OffTrack@rms");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test2_p", 51908, "NumberOfClusters_OffTrack@entries");

 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test3_p", 51908, "cChargeCorr_OnTrack@mean");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test3_p", 51908, "cChargeCorr_OnTrack@rms");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test3_p", 51908, "cChargeCorr_OnTrack@entries");
 
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test4_p", 51908, "cCharge_OffTrack@mean");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test4_p", 51908, "cCharge_OffTrack@rms");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test4_p", 51908, "cCharge_OffTrack@entries");
 
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test5_p", 51908, "cWidth_OnTrack@mean");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test5_p", 51908, "cWidth_OnTrack@rms");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test5_p", 51908, "cWidth_OnTrack@entries");
 
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test6_p", 51908, "cWidth_OffTrack@mean");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test6_p", 51908, "cWidth_OffTrack@rms");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test6_p", 51908, "cWidth_OffTrack@entries");
 
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test7_p", 51908, "cNoise_OnTrack@mean");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test7_p", 51908, "cNoise_OnTrack@rms");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test7_p", 51908, "cNoise_OnTrack@entries");
 
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test8_p", 51908, "cNoise_OffTrack@mean");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test8_p", 51908, "cNoise_OffTrack@rms");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test8_p", 51908, "cNoise_OffTrack@entries");
 
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test9_p", 51908, "cStoNCorr_OnTrack@mean");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test9_p", 51908, "cStoNCorr_OnTrack@rms");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test9_p", 51908, "cStoNCorr_OnTrack@entries");
 
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test10_p", 51908, "cStoN_OffTrack@mean");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test10_p", 51908, "cStoN_OffTrack@rms");
 condIter_accessRun("sqlite_file:historicDQM_rootFile.db", "test10_p", 51908, "cStoN_OffTrack@entries");
 

*/
					
}
