void RunPoD(
  TString dataset = "Data;Period=LHC13e;Run=195949;Variant=AOD134;Pass=muon_pass2",
  Bool_t usePhysicsSelection = kTRUE,
  Int_t numEvents = 999999999,
  Int_t firstEvent = 0
) {

  // Not needed on the VAF
  //gEnv->SetValue("XSec.GSI.DelegProxy","2");
   
  TString alirootMode = "ALIROOT";
  TString extraLibs = "ANALYSIS:ANALYSISalice"; // extraLibs = "ANALYSIS:OADB:ANALYSISalice:CORRFW:OADB:PWGmuon";

  TList *list = new TList(); 
  list->Add(new TNamed("ALIROOT_MODE", alirootMode.Data()));
  list->Add(new TNamed("ALIROOT_EXTRA_LIBS", extraLibs.Data()));
  list->Add(new TNamed("ALIROOT_ENABLE_ALIEN", "1"));  // important: creates token on every PROOF worker

  // Not needed on the VAF
  //TProof::Mgr("alice-caf.cern.ch")->SetROOTVersion("VO_ALICE@ROOT::v5-34-08");

  // Note the difference between CAF and VAF
  //TProof::Open("alice-caf.cern.ch");
  TProof::Open("pod://");

  // Check the dataset before running the analysis!
  gProof->ShowDataSet( dataset.Data() );
  //return;

  // Not needed on the VAF
  //gProof->EnablePackage("VO_ALICE@AliRoot::v5-04-81-AN", list);

  // A single AliRoot package for *all* AliRoot versions: new on VAF
  TFile::Cp("http://personalpages.to.infn.it/~berzano/cloud/extras/AliRoot.par", "AliRoot.par");
  gProof->UploadPackage("AliRoot.par");
  gProof->EnablePackage("AliRoot.par", list);  // this "list" is the same as always

  AliAnalysisManager *mgr  = new AliAnalysisManager("Analysis Train");

  AliAODInputHandler *aodH = new AliAODInputHandler();
  mgr->SetInputEventHandler(aodH);

  gProof->Load("AliAnalysisTaskSimplePt.cxx+");  // DON'T use double '+' when running multiple times: it uselessly recompiles everything!
  gROOT->LoadMacro("AddTaskSimplePt.C");

  AliAnalysisTaskSimplePt *simplePtTask = AddTaskSimplePt(usePhysicsSelection);
  if (usePhysicsSelection) {
    simplePtTask->SelectCollisionCandidates(AliVEvent::kAny);
  }
 
  if (!mgr->InitAnalysis()) return;

  mgr->StartAnalysis("proof", dataset, numEvents, firstEvent);

}
