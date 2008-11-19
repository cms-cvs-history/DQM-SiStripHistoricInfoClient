{

gROOT->Reset();


GraphAnalysis A1("TotalNumberOfClusters_OnTrack_mean",false,"");
A1.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A2("ClusterChargeCorr_OnTrack_landauPeak",false,"");
A2.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A3("ClusterChargeCorr_OnTrack_mean",false,"");
A3.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A4("ClusterChargeCorr_OnTrack_landauChi2NDF",false,"");
A4.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A5("ClusterNoise_OnTrack_gaussMean",false,"");
A5.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A6("ClusterNoise_OnTrack_gaussChi2NDF",false,"");
A6.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A7("ClusterStoNCorr_OnTrack_landauPeak",false,"");
A7.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A8("ClusterStoNCorr_OnTrack_landauChi2NDF",false,"");
A8.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A9("ClusterStoNCorr_OnTrack_mean",false,"");
A9.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A10("ClusterWidth_OnTrack_mean",false,"");
A10.plotGraphAnalysis("TIB,TOB,TID,TEC");


//

GraphAnalysis A21("ClusterChargeCorr__OnTrack_landauPeak",false,"_TIB_Layers");
A21.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A31("ClusterChargeCorr__OnTrack_mean",false,"_TIB_Layers");
A31.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A41("ClusterChargeCorr__OnTrack_landauChi2NDF",false,"_TIB_Layers");
A41.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A51("ClusterNoise__OnTrack_gaussMean",false,"_TIB_Layers");
A51.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A101("ClusterNoise__OnTrack_gaussChi2NDF",false,"_TIB_Layers");
A101.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A61("ClusterStoNCorr__OnTrack_landauPeak",false,"_TIB_Layers");
A61.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A71("ClusterStoNCorr__OnTrack_mean",false,"_TIB_Layers");
A71.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A81("ClusterStoNCorr__OnTrack_landauChi2NDF",false,"_TIB_Layers");
A81.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A91("ClusterWidth__OnTrack_mean",false,"_TIB_Layers");
A91.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

//

GraphAnalysis A22("ClusterChargeCorr__OnTrack_landauPeak",false,"_TOB_Layers");
A22.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A32("ClusterChargeCorr__OnTrack_mean",false,"_TOB_Layers");
A32.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A42("ClusterChargeCorr__OnTrack_landauChi2NDF",false,"_TOB_Layers");
A42.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A52("ClusterNoise__OnTrack_gaussMean",false,"_TOB_Layers");
A52.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A102("ClusterNoise__OnTrack_gaussChi2NDF",false,"_TOB_Layers");
A102.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A62("ClusterStoNCorr__OnTrack_landauPeak",false,"_TOB_Layers");
A62.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A72("ClusterStoNCorr__OnTrack_mean",false,"_TOB_Layers");
A72.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A82("ClusterStoNCorr__OnTrack_landauChi2NDF",false,"_TOB_Layers");
A82.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A92("ClusterWidth__OnTrack_mean",false,"_TOB_Layers");
A92.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

//

GraphAnalysis A23("ClusterChargeCorr__OnTrack_landauPeak",false,"_TID_Side1");
A23.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A33("ClusterChargeCorr__OnTrack_mean",false,"_TID_Side1");
A33.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A43("ClusterChargeCorr__OnTrack_landauChi2NDF",false,"_TID_Side1");
A43.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A53("ClusterNoise__OnTrack_gaussMean",false,"_TID_Side1");
A53.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A103("ClusterNoise__OnTrack_gaussChi2NDF",false,"_TID_Side1");
A103.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A63("ClusterStoNCorr__OnTrack_landauPeak",false,"_TID_Side1");
A63.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A73("ClusterStoNCorr__OnTrack_mean",false,"_TID_Side1");
A73.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A83("ClusterStoNCorr__OnTrack_landauChi2NDF",false,"_TID_Side1");
A83.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A93("ClusterWidth__OnTrack_mean",false,"_TID_Side1");
A93.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");


GraphAnalysis A14("ClusterChargeCorr__OnTrack_landauPeak",false,"_TID_Side2");
A14.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A24("ClusterChargeCorr__OnTrack_mean",false,"_TID_Side2");
A24.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A34("ClusterChargeCorr__OnTrack_landauChi2NDF",false,"_TID_Side2");
A34.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A44("ClusterNoise__OnTrack_gaussMean",false,"_TID_Side2");
A44.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A104("ClusterNoise__OnTrack_gaussChi2NDF",false,"_TID_Side2");
A104.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A54("ClusterStoNCorr__OnTrack_landauPeak",false,"_TID_Side2");
A54.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A64("ClusterStoNCorr__OnTrack_mean",false,"_TID_Side2");
A64.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A74("ClusterStoNCorr__OnTrack_landauChi2NDF",false,"_TID_Side2");
A74.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A84("ClusterWidth__OnTrack_mean",false,"_TID_Side2");
A84.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");


//

GraphAnalysis C1("TotalNumberOfClusters_OffTrack_mean",false,"");
C1.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis C2("ClusterCharge_OffTrack_mean",false,"");
C2.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis C3("ClusterNoise_OffTrack_gaussMean",false,"");
C3.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis C4("ClusterNoise_OffTrack_gaussChi2NDF",false,"");
C4.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis C5("ClusterStoN_OffTrack_mean",false,"");
C5.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis C6("ClusterWidth_OffTrack_mean",false,"");
C6.plotGraphAnalysis("TIB,TOB,TID,TEC");

//

GraphAnalysis C11("ClusterCharge__OffTrack_mean",false,"_TIB_Layers");
C11.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis C12("ClusterNoise__OffTrack_gaussMean",false,"_TIB_Layers");
C12.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis C13("ClusterNoise__OffTrack_gaussChi2NDF",false,"_TIB_Layers");
C13.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis C14("ClusterStoN__OffTrack_mean",false,"_TIB_Layers");
C14.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis C15("ClusterWidth__OffTrack_mean",false,"_TIB_Layers");
C15.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

//

GraphAnalysis C21("ClusterCharge__OffTrack_mean",false,"_TOB_Layers");
C21.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis C22("ClusterNoise__OffTrack_gaussMean",false,"_TOB_Layers");
C22.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis C23("ClusterNoise__OffTrack_gaussChi2NDF",false,"_TOB_Layers");
C23.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis C24("ClusterStoN__OffTrack_mean",false,"_TOB_Layers");
C24.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis C25("ClusterWidth__OffTrack_mean",false,"_TOB_Layers");
C25.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

//

GraphAnalysis C31("ClusterCharge__OffTrack_mean",false,"_TID_Side1");
C31.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis C32("ClusterNoise__OffTrack_gaussMean",false,"_TID_Side1");
C32.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis C39("ClusterNoise__OffTrack_gaussChi2NDF",false,"_TID_Side1");
C39.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis C33("ClusterStoN__OffTrack_mean",false,"_TID_Side1");
C33.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis C34("ClusterWidth__OffTrack_mean",false,"_TID_Side1");
C34.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis C35("ClusterCharge__OffTrack_mean",false,"_TID_Side2");
C35.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis C36("ClusterNoise__OffTrack_gaussMean",false,"_TID_Side2");
C36.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis C40("ClusterNoise__OffTrack_gaussChi2NDF",false,"_TID_Side2");
C40.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis C37("ClusterStoN__OffTrack_mean",false,"_TID_Side2");
C37.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis C38("ClusterWidth__OffTrack_mean",false,"_TID_Side2");
C38.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

//


GraphAnalysis B1("Chi2",true,"_mean");
B1.plotGraphAnalysis("CKFTk_mean,CosmicTk_mean,RSTk_mean");

GraphAnalysis B2("NumberOfRecHitsPerTrack",true,"_mean");
B2.plotGraphAnalysis("CKFTk_mean,CosmicTk_mean,RSTk_mean");

GraphAnalysis B3("NumberOfTracks",true,"_mean");
B3.plotGraphAnalysis("CKFTk_mean,CosmicTk_mean,RSTk_mean");



}
