/** Minimal macro to run on TAF.
 */
void runProofMinimal() {

  //
  // Customizable parameters go here
  //

  // PROOF connection string: use your ALICE (Alien) username
  TString proofConnStr = "dberzano@pmaster.to.infn.it";

  // Leave this empty for now (makes sense only if doing sim/rec)
  TString aliRootMode = "";

  // Additional libraries to load: they are processed in order. Required ROOT
  // libraries are loaded automatically, include AliRoot libraries only!
  TString aliRootExtraLibs = "STEERBase:ESD:AOD:ANALYSIS:OADB:ANALYSISalice";

  // Extra include paths (e.g., where to look for headers), colon-separated.
  // They all refer to $ALICE_ROOT. A possible example: "ITS:STEER:TOF"
  TString aliRootExtraIncs = "";

  // AliRoot and ROOT version. They must be compatible, elsewhere analysis won't
  // even start: check on http://alimonitor.cern.ch/packages. Use the same
  // versions locally!
  TString aliRootVersion = "v5-03-16-AN";
  TString rootVersion  = "v5-33-02b";

  // Dataset name
  //TString datasetName = "/alice/data/LHC10h_000139107_AOD086_p2";
  TString datasetListTxt = "ListOfDatasets.txt";

  // Maximum number of workers to use
  UInt_t maxWorkers = 99999;

  //
  // End of customizable parameters
  //

  // Params are put in a TList: it will be passed to the AliRoot PROOF package
  TList *aliParams = new TList();
  aliParams->SetOwner(kTRUE);
  aliParams->Add(new TNamed("ALIROOT_MODE", aliRootMode.Data()));
  aliParams->Add(new TNamed("ALIROOT_EXTRA_LIBS", aliRootExtraLibs.Data()));
  aliParams->Add(new TNamed("ALIROOT_EXTRA_INCLUDES", aliRootExtraIncs.Data()));

  // Required for AAF
  gEnv->SetValue("XSec.GSI.DelegProxy", "2");

  // Set ROOT version on PROOF
  TProof::Mgr(proofConnStr.Data())->SetROOTVersion(
                                                   Form("VO_ALICE@ROOT::%s", rootVersion.Data()));

  // Open PROOF connection
  TProof::Open(proofConnStr.Data(), Form("workers=%u", maxWorkers));
  if (!gProof) {
    Printf("Error: cannot connect to PROOF");
    return;
  }
  else if (gProof->GetParallel() == 0) {
    Printf("Error: no PROOF workers");
    gProof->Close();
    return;
  }

  // PROOF log level and things to log (you can OR them).
  // See http://root.cern.ch/root/html/TProofDebug.html
  //gProof->SetLogLevel(3, TProofDebug::kSubmerger | TProofDebug::kPacketizer);

  // Load list of datasets and count entries
  ifstream fp(datasetListTxt);
  if (!fp) {
    Printf("Error: can't open list of datasets %s", datasetListTxt.Data());
    gProof->Close();
    return;
  }

  TString dsName;
  TString proofDsString = "";
  TFileCollection *fc;
  Long64_t totEntries = 0;
  Long64_t nEntries;

  while (fp >> dsName) {

    // Skip empty and commented lines
    if ((dsName.Length() == 0) || (dsName[0] == '#')) continue;  // comment

    fc = gProof->GetDataSet(dsName.Data());

    if (!fc) {
      Printf("Error: can't retrieve dataset %s, skipping", dsName.Data());
      continue;
    }

    nEntries = fc->GetTotalEntries(NULL);
    if (nEntries <= 0) {
      Printf("Invalid number of entries in dataset %s, skipping",
        dsName.Data());
      delete fc;
      continue;
    }

    // All OK
    proofDsString += dsName + "|";
    totEntries += nEntries;

    delete fc;

  }

  fp.close();

  // Are there entries to process?
  if (totEntries == 0) {
    Printf("Error: no entries to process");
    gProof->Close();
    return;
  }
  else {
    Printf("Entries to process: %lld", totEntries);
  }

  // Enable AliRoot package (with extra libs)
  TString aliRootPackage = "VO_ALICE@AliRoot::" + aliRootVersion;
  if ( gProof->EnablePackage(aliRootPackage.Data(), aliParams) ) {
    Printf("Error: cannot find AliRoot version %s", aliRootVersion.Data());
    gProof->Close();
    return;
  }

  // Do not set it, or else it does not find the files to analyze!
  //gProof->SetParameter("PROOF_ForceLocal", 1);

  // We do not need to locate the files
  gProof->SetParameter("PROOF_LookupOpt", "none");

  // This is extremely important: do not try to make guesses on where input
  // files are located
  gProof->SetParameter("PROOF_PacketizerStrategy", 0);
  gProof->SetParameter("PROOF_PacketAsAFraction",
    (Int_t)(totEntries / gProof->GetParallel()) );

  //
  // Custom code to load your analysis task goes here
  //

  AliAnalysisManager *mgr = new AliAnalysisManager("testAnalysis");
  AliAODInputHandler* aodH = new AliAODInputHandler();
  mgr->SetInputEventHandler(aodH);

  Int_t c = 1;

  gProof->Load("AliSpectraAODHistoManager.cxx+");
  gProof->Load("AliSpectraAODEventCuts.cxx+");
  gProof->Load("AliSpectraAODTrackCuts.cxx+");
  gProof->Load("AliAnalysisTaskSpectraAOD.cxx+");

  // Add PID task
  gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C");
  Bool_t isMC = kFALSE;
  if (c == 2 || c == 3) isMC = kTRUE;   
  AliAnalysisTask * taskPID = AddTaskPIDResponse(isMC);
  mgr->AddTask(taskPID);

  // LOOP OVER SELECTION
  Double_t CentCutMin[4]={0,0,20,20};
  Double_t CentCutMax[4]={100,5,40,40};
  Double_t QvecCutMin[4]={0,0,0,3};
  Double_t QvecCutMax[4]={100,100,2,100};
  //Double_t CentCutMin[4]={5,10,20,30};
  //Double_t CentCutMax[4]={10,20,30,40};
  //Double_t QvecCutMin[4]={0,0,0,0};
  //Double_t QvecCutMax[4]={100,100,100,100};

  for(Int_t iCut=1; iCut<2; iCut++) {

    AliAnalysisTaskSpectraAOD *task =
      new AliAnalysisTaskSpectraAOD("TaskAODExercise");

    mgr->AddTask(task);

    //physics selection
    task->SelectCollisionCandidates();     

    // Set the cuts
    AliSpectraAODEventCuts * vcuts = new AliSpectraAODEventCuts("Event Cuts");
    AliSpectraAODTrackCuts  * tcuts = new AliSpectraAODTrackCuts("Track Cuts");
    tcuts->SetTrackType(5);
    tcuts->SetEta(.8);
    //tcuts->SetDCA(.1);
    tcuts->SetPt(5);
    tcuts->SetPtTOFMatching(0.6);   
    tcuts->SetQvecMin(QvecCutMin[iCut]);   
    tcuts->SetQvecMax(QvecCutMax[iCut]);    
    vcuts->SetCentralityCutMax(CentCutMax[iCut]);  
    vcuts->SetCentralityCutMin(CentCutMin[iCut]);
    task->SetEventCuts(vcuts);
    task->SetTrackCuts(tcuts);
    task->SetNSigmaForIdentification(5.); // FIXME
    task->SetYCut(.5);
    vcuts->PrintCuts();
    tcuts->PrintCuts();
     
    // Check for MC or real data
    if ((c == 2) || (c == 3)) {

      task->SetIsMC(kTRUE);
      AliAnalysisDataContainer *cinput = mgr->GetCommonInputContainer();

      AliAnalysisDataContainer *coutputpt1 = mgr->CreateContainer(
        Form("chistpt%d", iCut),
        AliSpectraAODHistoManager::Class(),
        AliAnalysisManager::kOutputContainer, 
        Form("Pt.AOD.1._MC_Cent%.0fto%.0f_QVec%.1fto%.1f.root",
          CentCutMin[iCut], CentCutMax[iCut], QvecCutMin[iCut], QvecCutMax[iCut]
        )
      );

      AliAnalysisDataContainer *coutputpt2 = mgr->CreateContainer(
        Form("cvcutpt%d", iCut),
        AliSpectraAODEventCuts::Class(),
        AliAnalysisManager::kOutputContainer, 
        Form("Pt.AOD.1._MC_Cent%.0fto%.0f_QVec%.1fto%.1f.root",
          CentCutMin[iCut],CentCutMax[iCut],QvecCutMin[iCut],QvecCutMax[iCut]
        )
      );

      AliAnalysisDataContainer *coutputpt3 = mgr->CreateContainer(
        Form("ctcutpt%d", iCut),
        AliSpectraAODTrackCuts::Class(),
        AliAnalysisManager::kOutputContainer, 
        Form("Pt.AOD.1._MC_Cent%.0fto%.0f_QVec%.1fto%.1f.root",
          CentCutMin[iCut], CentCutMax[iCut], QvecCutMin[iCut], QvecCutMax[iCut]
        )
      );

    }
    else if (c == 1) {

      AliAnalysisDataContainer *cinput = mgr->GetCommonInputContainer();

      AliAnalysisDataContainer *coutputpt1 = mgr->CreateContainer(
                                                                  Form("chistpt%d", iCut),
        AliSpectraAODHistoManager::Class(),
        AliAnalysisManager::kOutputContainer, 
        Form("Pt.AOD.1._data_ptcut_Cent%.0fto%.0f_QVec%.1fto%.1f.root",
          CentCutMin[iCut], CentCutMax[iCut], QvecCutMin[iCut], QvecCutMax[iCut]
        )
      );

      AliAnalysisDataContainer *coutputpt2 = mgr->CreateContainer(
        Form("cvcutpt%d", iCut),
        AliSpectraAODEventCuts::Class(),
        AliAnalysisManager::kOutputContainer, 
        Form("Pt.AOD.1._data_ptcut_Cent%.0fto%.0f_QVec%.1fto%.1f.root",
          CentCutMin[iCut], CentCutMax[iCut], QvecCutMin[iCut], QvecCutMax[iCut]
        )
      );

      AliAnalysisDataContainer *coutputpt3 = mgr->CreateContainer(
        Form("ctcutpt%d", iCut),
        AliSpectraAODTrackCuts::Class(),
        AliAnalysisManager::kOutputContainer,
        Form("Pt.AOD.1._data_ptcut_Cent%.0fto%.0f_QVec%.1fto%.1f.root",
          CentCutMin[iCut],CentCutMax[iCut],QvecCutMin[iCut],QvecCutMax[iCut]
        )
      );

    }

    mgr->ConnectInput(task, 0, cinput);
    mgr->ConnectOutput(task, 1, coutputpt1);
    mgr->ConnectOutput(task, 2, coutputpt2);
    mgr->ConnectOutput(task, 3, coutputpt3);

  } // end loop

  //
  // End of custom code to load your analysis task
  //

  if (!mgr->InitAnalysis()) {
    pp("Error: cannot initialize analysis");
    return;
  }

  // Debug level for AnalysisManager
  mgr->SetDebugLevel(2);

  // Start analysis on the specified dataset
  mgr->StartAnalysis("proof", proofDsString.Data());

}
