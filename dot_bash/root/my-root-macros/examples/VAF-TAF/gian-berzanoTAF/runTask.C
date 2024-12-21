/** Steering function
 */
void runTask(TString mode = "") {

  if (mode == "") {
    const char *_mode = Getline("Analysis mode: ");
    char *p;
    for (p=_mode; *p!='\0'; p++) if ((*p == '\n') || (*p == '\r')) *p = '\0';
    mode = _mode;
  }

  if (mode == "proof") {

    //
    // Run analysis on PROOF
    //

    runProof();

  }
  else if ((mode == "prooflite") || (mode == "single")) {

    //
    // Run analysis locally
    //

    runLocal(mode);

  }
  else {
    Printf("Unknown mode %s", mode.Data());
    return;
  }

}

/** Run on PROOF
 */
void runProof() {

  gEnv->SetValue("XSec.GSI.DelegProxy", "2");
  TProof::Open("dberzano@pmaster.to.infn.it", "workers=4");
  if (!gProof) return;

  gProof->SetParameter("PROOF_LookupOpt", "none");
  gProof->SetParameter("PROOF_UseMergers", -1);

  TString cutString;

  cutString = createCutString(
     50,  // cutIntPtmin
    999,  // cutIntPtmax
     20,  // cutIntDeltaInvMassPhi
     93,  // cutIntPointingAngle
     93,  // cutIntPointingAngleXY
     40,  // cutIntDecLeng
     40,  // cutIntDecLengXY
      0,  // cutIntNorDecLeng
     12,  // cutIntNorDecLengXY
     20,  // cutIntSigvert
      5,  // cutIntKin1
     90,  // cutIntKin2
     20,  // cutIntCentralityMin
     40   // cutIntCentralityMax
  );

  gProof->Process(
    "/default/ginnocen/NewDsMBSemiCentCent20_60_PtMin3_PID113Runs",
    "Significance.cxx+", cutString.Data());

  //gProof->Process(
  //  "/default/ginnocen/NewDsMBSemiCentCent20_60_PtMin3_PID113Runs",
  //  "Significance.cxx+", "");

}

/** Run locally
 */
void runLocal(TString &mode) {

  const char *files[] = {
     "AnalysisResults.root"
     //"AnalysisResults-merged.root"
     //"AnalysisResults-9997.root",
     //"AnalysisResults-9998.root",
     //"AnalysisResults-9999.root"
  };

  UInt_t n_files = sizeof(files) / sizeof(*files);
  TString buf;

  // Construct chain
  TChain *chain = new TChain("PWG3_D2H_InvMassDs/fNtupleDs", "La mia ntupla");
  for (UInt_t i=0; i<n_files; i++) chain->Add(files[i]);

  if (mode == "prooflite") {
    TProof::Open("");
    chain->SetProof();
  }

  TStopwatch ts;
  ts.Start();

  TString cutString;

  cutString = createCutString(
     50,  // cutIntPtmin
    999,  // cutIntPtmax
     20,  // cutIntDeltaInvMassPhi
     93,  // cutIntPointingAngle
     93,  // cutIntPointingAngleXY
     40,  // cutIntDecLeng
     40,  // cutIntDecLengXY
      0,  // cutIntNorDecLeng
     12,  // cutIntNorDecLengXY
     20,  // cutIntSigvert
      5,  // cutIntKin1
     90,  // cutIntKin2
     20,  // cutIntCentralityMin
     40   // cutIntCentralityMax
  );

  //chain->Process("Significance.cxx+", "", 100);
  chain->Process("Significance.cxx+", cutString.Data(), 10000);

  ts.Stop();
  ts.Print();

}

/** Prepare cut string
 */
TString createCutString(Int_t ptmin, Int_t ptmax, Int_t deltaInvMassPhi,
  Int_t pointingAngle, Int_t pointingAngleXY, Int_t decLeng, Int_t decLengXY,
  Int_t norDecLeng, Int_t norDecLengXY, Int_t sigvert, Int_t kin1, Int_t kin2,
  Int_t centralityMin, Int_t centralityMax) {

  TString cutString;
  cutString.Form("%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d",
    ptmin, ptmax, deltaInvMassPhi, pointingAngle, pointingAngleXY,
    decLeng, decLengXY, norDecLeng, norDecLengXY, sigvert, kin1, kin2,
    centralityMin, centralityMax);

  return cutString;
}
