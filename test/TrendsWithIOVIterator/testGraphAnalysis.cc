{

gROOT->Reset();


GraphAnalysis A1("TotalNumberOfClusters_OnTrack_mean",false,"");
A1.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A2("ClusterChargeCorr_OnTrack_landauPeak",false,"");
A2.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis C2("ClusterChargeCorr_OnTrack_mean",false,"");
C2.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A3("ClusterNoise_OnTrack_gaussMean",false,"");
A3.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A4("ClusterStoNCorr_OnTrack_landauPeak",false,"");
A4.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis C4("ClusterStoNCorr_OnTrack_mean",false,"");
C4.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A5("ClusterWidth_OnTrack_mean",false,"");
A5.plotGraphAnalysis("TIB,TOB,TID,TEC");


//

GraphAnalysis A21("ClusterChargeCorr__OnTrack_landauPeak",false,"_TIB_Layers");
A21.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A31("ClusterNoise__OnTrack_gaussMean",false,"_TIB_Layers");
A31.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A41("ClusterStoNCorr__OnTrack_landauPeak",false,"_TIB_Layers");
A41.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A51("ClusterWidth__OnTrack_mean",false,"_TIB_Layers");
A51.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

//

GraphAnalysis A22("ClusterChargeCorr__OnTrack_landauPeak",false,"_TOB_Layers");
A22.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A32("ClusterNoise__OnTrack_gaussMean",false,"_TOB_Layers");
A32.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A42("ClusterStoNCorr__OnTrack_landauPeak",false,"_TOB_Layers");
A42.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A52("ClusterWidth__OnTrack_mean",false,"_TOB_Layers");
A52.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

//

GraphAnalysis A23("ClusterChargeCorr__OnTrack_landauPeak",false,"_TID_Side1");
A23.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A33("ClusterNoise__OnTrack_gaussMean",false,"_TID_Side1");
A33.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A43("ClusterStoNCorr__OnTrack_landauPeak",false,"_TID_Side1");
A43.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A53("ClusterWidth__OnTrack_mean",false,"_TID_Side1");
A53.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A24("ClusterChargeCorr__OnTrack_landauPeak",false,"_TID_Side2");
A24.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A34("ClusterNoise__OnTrack_gaussMean",false,"_TID_Side2");
A34.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A44("ClusterStoNCorr__OnTrack_landauPeak",false,"_TID_Side2");
A44.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A54("ClusterWidth__OnTrack_mean",false,"_TID_Side2");
A54.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");


//

GraphAnalysis A6("TotalNumberOfClusters_OffTrack_mean",false,"");
A6.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A7("ClusterCharge_OffTrack_mean",false,"");
A7.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A8("ClusterNoise_OffTrack_gaussMean",false,"");
A8.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A9("ClusterStoN_OffTrack_mean",false,"");
A9.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A10("ClusterWidth_OffTrack_mean",false,"");
A10.plotGraphAnalysis("TIB,TOB,TID,TEC");

//

GraphAnalysis A71("ClusterCharge__OffTrack_mean",false,"_TIB_Layers");
A71.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A81("ClusterNoise__OffTrack_gaussMean",false,"_TIB_Layers");
A81.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A91("ClusterStoN__OffTrack_mean",false,"_TIB_Layers");
A91.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

GraphAnalysis A101("ClusterWidth__OffTrack_mean",false,"_TIB_Layers");
A101.plotGraphAnalysis("TIB_Layer1,TIB_Layer2,TIB_Layer3,TIB_Layer4");

//

GraphAnalysis A72("ClusterCharge__OffTrack_mean",false,"_TOB_Layers");
A72.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A82("ClusterNoise__OffTrack_gaussMean",false,"_TOB_Layers");
A82.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A92("ClusterStoN__OffTrack_mean",false,"_TOB_Layers");
A92.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

GraphAnalysis A102("ClusterWidth__OffTrack_mean",false,"_TOB_Layers");
A102.plotGraphAnalysis("TOB_Layer1,TOB_Layer2,TOB_Layer3,TOB_Layer4,TOB_Layer5,TOB_Layer6");

//

GraphAnalysis A73("ClusterCharge__OffTrack_mean",false,"_TID_Side1");
A73.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A83("ClusterNoise__OffTrack_gaussMean",false,"_TID_Side1");
A83.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A93("ClusterStoN__OffTrack_mean",false,"_TID_Side1");
A93.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A103("ClusterWidth__OffTrack_mean",false,"_TID_Side1");
A103.plotGraphAnalysis("TID_Side1_Layer1,TID_Side1_Layer2,TID_Side1_Layer3");

GraphAnalysis A74("ClusterCharge__OffTrack_mean",false,"_TID_Side2");
A74.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A84("ClusterNoise__OffTrack_gaussMean",false,"_TID_Side2");
A84.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A94("ClusterStoN__OffTrack_mean",false,"_TID_Side2");
A94.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

GraphAnalysis A104("ClusterWidth__OffTrack_mean",false,"_TID_Side2");
A104.plotGraphAnalysis("TID_Side2_Layer1,TID_Side2_Layer2,TID_Side2_Layer3");

//


GraphAnalysis B1("Chi2",true,"");
B1.plotGraphAnalysis("CKFTk_mean,CosmicTk_mean,RSTk_mean");

GraphAnalysis B2("NumberOfRecHitsPerTrack",true,"");
B2.plotGraphAnalysis("CKFTk_mean,CosmicTk_mean,RSTk_mean");



}
