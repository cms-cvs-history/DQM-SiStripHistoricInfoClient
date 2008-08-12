{

gROOT->Reset();
gROOT->ProcessLine(".L HistoricInspector.cc");

HistoricInspector A;
//A.setDB("oracle://cms_orcoff_int2r/CMS_COND_STRIP", "SiStripSummary_test1","cms_cond_strip","SSWDC3MCAI8HQHTC");
A.setDB("oracle://devdb10/CMS_COND_STRIP", "SiStripSummary_test2","cms_cond_strip","w3807dev","COND/Services/TBufferBlobStreamingService");

//A.createTrend(1, "Summary_NumberOfClusters_OffTrack@mean");
A.createTrend(1, "Summary_NumberOfClusters_OnTrack@mean,Summary_NumberOfClusters_OffTrack@mean");
A.createTrend(2, "Summary_NumberOfClusters_OnTrack@mean,Summary_NumberOfClusters_OffTrack@mean");
//A.createTrend(1, "Summary_NumberOfClusters_OffTrack@mean",51093);
//A.createTrend(0, "NumberOfTracks@mean,NumberOfTracks@entries");
A.createTrend(0, "NumberOfTracks@mean,NumberOfTracks@entries");
}
