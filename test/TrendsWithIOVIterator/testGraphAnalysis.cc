{

gROOT->Reset();


GraphAnalysis A1("TotalNumberOfClusters_OnTrack_mean",false);
A1.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A2("ClusterChargeCorr_OnTrack_landauPeak",false);
A2.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A3("ClusterNoise_OnTrack_gaussMean",false);
A3.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A4("ClusterStoNCorr_OnTrack_landauPeak",false);
A4.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A5("ClusterWidth_OnTrack_landauPeak",false);
A5.plotGraphAnalysis("TIB,TOB,TID,TEC");


//


GraphAnalysis A6("TotalNumberOfClusters_OffTrack_mean",false);
A6.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A7("ClusterCharge_OffTrack_landauPeak",false);
A7.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A8("ClusterNoise_OffTrack_gaussMean",false);
A8.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A9("ClusterStoN_OffTrack_landauPeak",false);
A9.plotGraphAnalysis("TIB,TOB,TID,TEC");

GraphAnalysis A10("ClusterWidth_OffTrack_mean",false);
A10.plotGraphAnalysis("TIB,TOB,TID,TEC");


//


GraphAnalysis A11("Chi2",true);
A11.plotGraphAnalysis("CKFTk_mean,CosmicTk_mean,RSTk_mean");

GraphAnalysis A12("NumberOfRecHitsPerTrack",true);
A12.plotGraphAnalysis("CKFTk_mean,CosmicTk_mean,RSTk_mean");


//

gSystem->Exec("kill -9 "+TString(Form("%d", gSystem->GetPid())));

}
