// For more information on the TSelector framework see 
// $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The file for this selector can be found at
// http://lcg-heppkg.web.cern.ch/lcg-heppkg/ROOT/eventdata.root
// i.e run
//   root [0] f = TFile::Open("http://lcg-heppkg.web.cern.ch/lcg-heppkg/ROOT/eventdata.root");
//   root [1] EventTree->Process("Significance.C+")

// The following methods are defined in this file:
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers, a convenient place to create your histograms.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("Significance.C")
// Root > T->Process("Significance.C","some options")
// Root > T->Process("Significance.C+")
//

#include "Significance.h"

// For ROOT
ClassImp(Significance);

void Significance::Init(TTree *tree) {

  //Printf("=== TREE CHANGED (%s) ===", tree->ClassName());

  // Assign this tree to an internal variable
  fChain = tree;

  // Called at each file change: we set branch addresses here
  fChain->SetBranchAddress("PidTrackBit0", &fPidTrackBit0);  // Float_t
  fChain->SetBranchAddress("PidTrackBit1", &fPidTrackBit1);  // Float_t
  fChain->SetBranchAddress("PidTrackBit2", &fPidTrackBit2);  // Float_t

  fChain->SetBranchAddress("retcode", &fRetcodeFloat);  // Float_t

  fChain->SetBranchAddress("Pt0", &fPt0);  // Float_t
  fChain->SetBranchAddress("Pt1", &fPt1);  // Float_t
  fChain->SetBranchAddress("Pt2", &fPt2);  // Float_t
  fChain->SetBranchAddress("PtRec", &fPtRec);  // Float_t

  fChain->SetBranchAddress("PointingAngle", &fPointingAngle);  // Float_t
  fChain->SetBranchAddress("PointingAngleXY", &fPointingAngleXY);

  fChain->SetBranchAddress("DecLeng", &fDecLeng);
  fChain->SetBranchAddress("DecLengXY", &fDecLengXY);
  fChain->SetBranchAddress("NorDecLeng", &fNorDecLeng);
  fChain->SetBranchAddress("NorDecLengXY", &fNorDecLengXY);
  fChain->SetBranchAddress("sigvert", &fSigvert);

  fChain->SetBranchAddress("InvMassKKpi", &fInvMassKKpi);
  fChain->SetBranchAddress("InvMasspiKK", &fInvMasspiKK);
  fChain->SetBranchAddress("InvMassPhiKKpi", &fInvMassPhiKKpi);
  fChain->SetBranchAddress("InvMassPhipiKK", &fInvMassPhipiKK);

  fChain->SetBranchAddress("cosinePiDsFrameKKpi", &fCosinePiDsFrameKKpi);
  fChain->SetBranchAddress("cosinePiDsFramepiKK", &fCosinePiDsFramepiKK);
  fChain->SetBranchAddress("cosineKPhiFrameKKpi", &fCosineKPhiFrameKKpi);
  fChain->SetBranchAddress("cosineKPhiFramepiKK", &fCosineKPhiFramepiKK);

  fChain->SetBranchAddress("centrality", &fCentrality);

  // Unused branches
  //fChain->SetBranchAddress("labDs", &fLabDs);  // Float_t [unused]
  //fChain->SetBranchAddress("pdgcode0", &fPdgcode0);  // Float_t [unused]
  //fChain->SetBranchAddress("P0", &fP0);  // Float_t [unused]
  //fChain->SetBranchAddress("P1", &fP1);  // Float_t [unused]
  //fChain->SetBranchAddress("P2", &fP2);  // Float_t [unused]

}

Bool_t Significance::ParseCutString(const char *cutString, ...) {

  if (!cutString) return kFALSE;

  Bool_t ok = kTRUE;
  Int_t *intPtr;

  va_list varPtr;
  va_start(varPtr, cutString);

  TString cutTString = cutString;
  TObjArray *tokAry = cutTString.Tokenize("|");
  TIter tok(tokAry);
  TObjString *os;

  while (( os = (TObjString *)tok.Next() )) {
    intPtr = va_arg(varPtr, Int_t *);
    if (!intPtr) {
      Printf("Not enough pointers passed!");
      ok = kFALSE;
      break;
    }

    *intPtr = os->String().Atoi();
  }

  delete tokAry;

  if (va_arg(varPtr, Int_t *) != NULL) {
    Printf("Too many pointers passed!");
    ok = kFALSE;
  }

  va_end(varPtr);

  return ok;

}

void Significance::SlaveBegin(TTree *) {

  // Set mass constants
  fMassDs  = TDatabasePDG::Instance()->GetParticle(431)->Mass();
  fMassPhi = TDatabasePDG::Instance()->GetParticle(333)->Mass();

  // Zero counters
  fCounterpiKK = 0;
  fCounterKKpi = 0;
  fCounterEventsSlave = 0;

  // These strings are unused for now
  //suffixResonance = "Phi";    // TString
  //suffixCutset = "Strong";    // TString

  //
  // Here we set the cuts
  //

  // Analysis parameters as integers: will be converted in floats shortly
  Int_t cutIntPtmin, cutIntPtmax, cutIntDeltaInvMassPhi, cutIntPointingAngle,
    cutIntPointingAngleXY, cutIntDecLeng, cutIntDecLengXY, cutIntNorDecLeng,
    cutIntNorDecLengXY, cutIntSigvert, cutIntKin1, cutIntKin2,
    cutIntCentralityMin, cutIntCentralityMax;

  // Analysis parameters are passed with the option string
  Bool_t parseOk = ParseCutString(GetOption(), &cutIntPtmin, &cutIntPtmax,
    &cutIntDeltaInvMassPhi, &cutIntPointingAngle, &cutIntPointingAngleXY,
    &cutIntDecLeng, &cutIntDecLengXY, &cutIntNorDecLeng, &cutIntNorDecLengXY,
    &cutIntSigvert, &cutIntKin1, &cutIntKin2, &cutIntCentralityMin,
    &cutIntCentralityMax, NULL);  // last NULL is **REQUIRED**

  if (!parseOk) {
    Printf("Error in parsing cuts! Invalid analysis!");
    return;
  }
  else {
    Printf("-->8-- The following cuts will be used (as integers) --8<--");
    Printf("ptmin           = %4d", cutIntPtmin);
    Printf("ptmax           = %4d", cutIntPtmax);
    Printf("deltaInvMassPhi = %4d", cutIntDeltaInvMassPhi);
    Printf("pointingAngle   = %4d", cutIntPointingAngle);
    Printf("pointingAngleXY = %4d", cutIntPointingAngleXY);
    Printf("decLeng         = %4d", cutIntDecLeng);
    Printf("decLengXY       = %4d", cutIntDecLengXY);
    Printf("norDecLeng      = %4d", cutIntNorDecLeng);
    Printf("norDecLengXY    = %4d", cutIntNorDecLengXY);
    Printf("sigvert         = %4d", cutIntSigvert);
    Printf("kin1            = %4d", cutIntKin1);
    Printf("kin2            = %4d", cutIntKin2);
    Printf("centralityMin   = %4d", cutIntCentralityMin);
    Printf("centralityMax   = %4d", cutIntCentralityMax);

  }

  // Analysis parameters as floats (these are class variables)
  fCutPtmin           = (Float_t)cutIntPtmin / 10.;
  fCutPtmax           = (Float_t)cutIntPtmax / 10.;
  fCutDeltaInvMassPhi = (Float_t)cutIntDeltaInvMassPhi / 10000.;
  fCutPointingAngle   = (Float_t)cutIntPointingAngle / 100.;
  fCutPointingAngleXY = (Float_t)cutIntPointingAngleXY / 100.;
  fCutDecLeng         = (Float_t)cutIntDecLeng / 1000.;
  fCutDecLengXY       = (Float_t)cutIntDecLengXY / 1000.;
  fCutNorDecLeng      = (Float_t)cutIntNorDecLeng / 10.;
  fCutNorDecLengXY    = (Float_t)cutIntNorDecLengXY / 10.;
  fCutSigvert         = (Float_t)cutIntSigvert / 1000.;
  fCutKin1            = (Float_t)cutIntKin1 / 100.;
  fCutKin2            = (Float_t)cutIntKin2 / 100.;
  fCutCentralityMin   = (Float_t)cutIntCentralityMin;
  fCutCentralityMax   = (Float_t)cutIntCentralityMax;

  // Other parameters
  Double_t massRange = 0.8;
  Double_t massBinSize = 0.002;
  Int_t    nInvMassBins = (Int_t)( massRange/massBinSize+0.5 );

  if ((nInvMassBins % 2) == 1) nInvMassBins++;

  Double_t minMass = fMassDs - 0.5 * nInvMassBins * massBinSize;
  Double_t maxMass = fMassDs + 0.5 * nInvMassBins * massBinSize;

  // Type of PID
  fIsPID = 2;

  // Invoked once per worker: create output objects to merge here (i.e.,
  // histograms)
  fHistMass = new TH1F("fHistMass", "Invariant mass",
    nInvMassBins, minMass, maxMass);
  fHistMassPhi = new TH1F("fHistMassPhi", "Invariant mass Phi",
    100000, 0.9, 1.1);

  // Needed for PROOF
  GetOutputList()->Add(fHistMass);
  GetOutputList()->Add(fHistMassPhi);

}

Bool_t Significance::Process(Long64_t entry) {

  GetEntry(entry);

  fBitmap0 = (UInt_t)fPidTrackBit0;
  fBitmap1 = (UInt_t)fPidTrackBit1;
  fBitmap2 = (UInt_t)fPidTrackBit2;

  fRetcodeInt = (Int_t)fRetcodeFloat;

  Bool_t isKKpi, ispiKK, isPhiKKpi, isPhipiKK, isK0starKKpi, isK0starpiKK;

  isKKpi       = fRetcodeInt &  1;
  ispiKK       = fRetcodeInt &  2;
  isPhiKKpi    = fRetcodeInt &  4;
  isPhipiKK    = fRetcodeInt &  8;
  isK0starKKpi = fRetcodeInt & 16;
  isK0starpiKK = fRetcodeInt & 32;

  Float_t DeltaInvMassPhiKKpi = TMath::Abs(fInvMassPhiKKpi - fMassPhi);
  Float_t DeltaInvMassPhipiKK = TMath::Abs(fInvMassPhipiKK - fMassPhi);

  // Cubes
  Float_t cosineKPhiFrameKKpi_3 = \
    fCosineKPhiFrameKKpi * fCosineKPhiFrameKKpi * fCosineKPhiFrameKKpi;
  Float_t cosineKPhiFramepiKK_3 = \
    fCosineKPhiFramepiKK * fCosineKPhiFramepiKK * fCosineKPhiFramepiKK;

  //
  // Selection for events of type KKpi
  //

  if ((fPtRec > fCutPtmin) && (fPtRec < fCutPtmax)) {

    // The KKpi case
    if (isKKpi && isPhiKKpi) {
      if ((fPointingAngle >= fCutPointingAngle) &&
          (fPointingAngleXY >= fCutPointingAngleXY)) {
        if ((fDecLeng >= fCutDecLeng) && (fDecLengXY >= fCutDecLengXY)) {
          if ((fNorDecLeng >= fCutNorDecLeng) &&
              (fNorDecLengXY >= fCutNorDecLengXY) &&
              (fSigvert <= fCutSigvert)) {
            if (DeltaInvMassPhiKKpi <= fCutDeltaInvMassPhi) {
              if ((TMath::Abs(cosineKPhiFrameKKpi_3) > fCutKin1) &&
                  (fCosinePiDsFrameKKpi < fCutKin2)) {
                if ( (fCentrality >= fCutCentralityMin) &&
                     (fCentrality <= fCutCentralityMax)) {

                  if ((fIsPID > 0) && (IsSelectedPID() & 1)) {
                     fCounterKKpi++;
                     fHistMass->Fill(fInvMassKKpi);
                     fHistMassPhi->Fill(fInvMassPhiKKpi);
                  } // pid (KKpi)

               } // centrality
              } // kin cut (KKpi)
            } // inv. mass resonance (KKpi)
          } // normalized decay length
        } // decay length
      } // pointing angle
    } // is KKpi

    //
    // The piKK case
    //

    if (ispiKK && isPhipiKK) {
      if ((fPointingAngle >= fCutPointingAngle) &&
          (fPointingAngleXY >= fCutPointingAngleXY)) {
        if ((fDecLeng >= fCutDecLeng) && (fDecLengXY >= fCutDecLengXY)) {
          if ((fNorDecLeng >= fCutNorDecLeng) &&
              (fNorDecLengXY >= fCutNorDecLengXY) &&
              (fSigvert <= fCutSigvert)) {
            if (DeltaInvMassPhipiKK <= fCutDeltaInvMassPhi) {
              if ((TMath::Abs(cosineKPhiFramepiKK_3) > fCutKin1) &&
                  (fCosinePiDsFramepiKK < fCutKin2)) {
                if ( (fCentrality >= fCutCentralityMin) &&
                     (fCentrality <= fCutCentralityMax)) {

                  if ((fIsPID > 0) && (IsSelectedPID() & 2)) {
                    fCounterpiKK++;
                    fHistMass->Fill(fInvMasspiKK);
                    fHistMassPhi->Fill(fInvMassPhipiKK);
                  }  // pid (piKK)

                } // centrality
              } // kin cut (piKK)
            } // inv. mass resonance (piKK)
          } // normalized decay length
        } // decay length
      } // pointing angle
    } // is piKK

  } // Pt cut

  fHistMass->Fill(fInvMassKKpi);
  fHistMassPhi->Fill(fInvMassPhiKKpi);

  return kTRUE;
}

void Significance::Terminate() {

  //TCanvas *canvas = new TCanvas();
  //canvas->Divide(1, 2);

  // Cutset info string must be prepared here too
  Int_t cutIntPtmin, cutIntPtmax, cutIntDeltaInvMassPhi, cutIntPointingAngle,
    cutIntPointingAngleXY, cutIntDecLeng, cutIntDecLengXY, cutIntNorDecLeng,
    cutIntNorDecLengXY, cutIntSigvert, cutIntKin1, cutIntKin2,
    cutIntCentralityMin, cutIntCentralityMax;

  // Analysis parameters are passed with the option string
  Bool_t parseOk = ParseCutString(GetOption(), &cutIntPtmin, &cutIntPtmax,
    &cutIntDeltaInvMassPhi, &cutIntPointingAngle, &cutIntPointingAngleXY,
    &cutIntDecLeng, &cutIntDecLengXY, &cutIntNorDecLeng, &cutIntNorDecLengXY,
    &cutIntSigvert, &cutIntKin1, &cutIntKin2, &cutIntCentralityMin,
    &cutIntCentralityMax, NULL);  // last NULL is **REQUIRED**

  if (parseOk) {
    // Prepare "info" string (to univokely identify cutset)
    fCutsetInfo.Form(
      "cutset_%03d_%03d_%03d_%03d_%03d_%03d_%03d_"
      "%03d_%03d_%03d_%03d_%03d_%03d_%03d",
      cutIntPtmin, cutIntPtmax, cutIntDeltaInvMassPhi, cutIntPointingAngle,
      cutIntPointingAngleXY, cutIntDecLeng, cutIntDecLengXY, cutIntNorDecLeng,
      cutIntNorDecLengXY, cutIntSigvert, cutIntKin1, cutIntKin2,
      cutIntCentralityMin, cutIntCentralityMax);
  }
  else {
    Printf("Error in Terminate(): there is a problem with the parameters!");
    return;
  }

  TFile *outFile = TFile::Open("SignificanceResults.root", "update");
  outFile->mkdir(fCutsetInfo.Data(), "A cutset");
  outFile->cd(fCutsetInfo.Data());

  fHistMass = (TH1F *)( GetOutputList()->FindObject("fHistMass") );
  if (fHistMass) {
    //canvas->cd(1);
    //fHistMass->Draw();
    fHistMass->Write();
  }

  fHistMassPhi = (TH1F *)( GetOutputList()->FindObject("fHistMassPhi") );
  if (fHistMassPhi) {
    //canvas->cd(2);
    //fHistMassPhi->Draw();
    fHistMassPhi->Write();
  }

  outFile->Close();
  delete outFile;

  Printf(">> Results saved in file SignificanceResults.root, directory %s",
    fCutsetInfo.Data());

}

// Imported as-is
Int_t Significance::IsSelectedPID() {

  // return values: 0=not OK, 1=OK as KKpi, 2=OK as piKK, 3=OK as both
  Int_t retCode = 3;
  Bool_t okKKpi = kTRUE;
  Bool_t okpiKK = kTRUE;

  Int_t nKaons = 0;
  Int_t nNotKaons = 0;

  Int_t isPion0   = MatchTPCTOF(fPt0, 2, fBitmap0);
  Int_t isKaon0   = MatchTPCTOF(fPt0, 3, fBitmap0);
  Int_t isProton0 = MatchTPCTOF(fPt0, 4, fBitmap0);

  Int_t isPion1   = MatchTPCTOF(fPt1, 2, fBitmap1);
  Int_t isKaon1   = MatchTPCTOF(fPt1, 3, fBitmap1);
  Int_t isProton1 = MatchTPCTOF(fPt1, 4, fBitmap1);

  Int_t isPion2   = MatchTPCTOF(fPt2, 2, fBitmap2);
  Int_t isKaon2   = MatchTPCTOF(fPt2, 3, fBitmap2);
  Int_t isProton2 = MatchTPCTOF(fPt2, 4, fBitmap2);

  if ((isProton0 > 0) && (isKaon0 < 0) && (isPion0 < 0)) return 0;  // not OK

  if ((isKaon0 > 0) && (isPion0 < 0)) nKaons++;

  if (isKaon0 < 0) nNotKaons++;
  if (isKaon0 < 0) okKKpi = kFALSE;
  if (isPion0 < 0) okpiKK = kFALSE;

  if ((fPt0 < 1.5) && (fIsPID == 2)) {
    if (isKaon0 <= 0) okKKpi = kFALSE;
    if (isPion0 <= 0) okpiKK = kFALSE;
  }

  if ((isProton1 > 0) && (isKaon1 < 0) && (isPion1 < 0)) return 0;
  if ((isKaon1 > 0) && (isPion1 < 0)) nKaons++;
  if (isKaon1 < 0) nNotKaons++;
  if (isKaon1 < 0) return 0;
  if ((fPt1 < 1.5) && (fIsPID == 2) && (isKaon1 <= 0)) return 0;

  if ((isProton2 > 0) && (isKaon2 < 0) && (isPion2 < 0)) return 0;
  if ((isKaon2 > 0) && (isPion2 < 0)) nKaons++;
  if (isKaon2 < 0) nNotKaons++;
  if (isKaon2 < 0) okpiKK = kFALSE;
  if (isPion2 < 0) okKKpi = kFALSE;
  if ((fPt2 < 1.5) && (fIsPID == 2)) {
    if (isKaon2 <= 0) okpiKK = kFALSE;
    if (isPion2 <= 0) okKKpi = kFALSE;
  }

  if (nKaons > 2) return 0;
  if (nNotKaons > 1) return 0;

  if (!okKKpi) retCode -= 1;
  if (!okpiKK) retCode -= 2;

  return retCode;

}

// Imported as-is
Int_t Significance::MatchTPCTOF(Double_t mom, Int_t species, UInt_t bitmap) {
  
  Int_t kTPCLess1, kTPCMore1Less2, kTPCMore2Less3, kTPCMore3;
  Int_t kTOFLess1, kTOFMore1Less2, kTOFMore2Less3, kTOFMore3;
  
  if (species == 2) {
    kTPCLess1      = kTPCPionLess1;
    kTPCMore1Less2 = kTPCPionMore1Less2;
    kTPCMore2Less3 = kTPCPionMore2Less3;
    kTPCMore3      = kTPCPionMore3;
    kTOFLess1      = kTOFPionLess1;
    kTOFMore1Less2 = kTOFPionMore1Less2;
    kTOFMore2Less3 = kTOFPionMore2Less3;
    kTOFMore3      = kTOFPionMore3;}
  else if (species == 3) {
    kTPCLess1      = kTPCKaonLess1;
    kTPCMore1Less2 = kTPCKaonMore1Less2;
    kTPCMore2Less3 = kTPCKaonMore2Less3;
    kTPCMore3      = kTPCKaonMore3;
    kTOFLess1      = kTOFKaonLess1;
    kTOFMore1Less2 = kTOFKaonMore1Less2;
    kTOFMore2Less3 = kTOFKaonMore2Less3;
    kTOFMore3      = kTOFKaonMore3;
  }
  else if (species == 4) {
    kTPCLess1      = kTPCProtonLess1;
    kTPCMore1Less2 = kTPCProtonMore1Less2;
    kTPCMore2Less3 = kTPCProtonMore2Less3;
    kTPCMore3      = kTPCProtonMore3;
    kTOFLess1      = kTOFProtonLess1;
    kTOFMore1Less2 = kTOFProtonMore1Less2;
    kTOFMore2Less3 = kTOFProtonMore2Less3;
    kTOFMore3      = kTOFProtonMore3;
  }

  Bool_t isTPCLess1      = bitmap & (1 << kTPCLess1);
  Bool_t isTPCMore1Less2 = bitmap & (1 << kTPCMore1Less2);
  Bool_t isTPCMore2Less3 = bitmap & (1 << kTPCMore2Less3);
  Bool_t isTPCMore3      = bitmap & (1 << kTPCMore3);
  
  Bool_t isTOFLess1      = bitmap & (1 << kTOFLess1);
  Bool_t isTOFMore1Less2 = bitmap & (1 << kTOFMore1Less2);
  Bool_t isTOFMore2Less3 = bitmap & (1 << kTOFMore2Less3);
  Bool_t isTOFMore3      = bitmap & (1 << kTOFMore3);
  
  Bool_t isSignalTPC = (isTPCLess1 || isTPCMore1Less2 || \
                        isTPCMore2Less3 || isTPCMore3);
  Bool_t isSignalTOF = (isTOFLess1 || isTOFMore1Less2 || \
                        isTOFMore2Less3 || isTOFMore3);

  if (!isSignalTPC && !isSignalTOF) {
    //cout<<"*Strong *  both TPC and TOF OUT "<<endl; 
    return 0;
  }
  
  Int_t TPCinfo=0;
  
  if (isSignalTPC) {
    //printf("*Strong** ok TPC step1 \n");
    if (RawAsym(mom, species, kPidTPC, bitmap, kFALSE)) { 
      TPCinfo=1; 
      //printf("*Strong** ok TPC 2sigma \n");
    }
    else {
      TPCinfo=-1; 
      //printf("*Strong** NO TPC 2sigma \n");
    }
  }
  
  if (TPCinfo<0 && RawAsym(mom, species, kPidTPC, bitmap, kTRUE)) {
    TPCinfo=0; 
    //printf("Strong* ok 3 sigma TPC\n");
  }
  
  Int_t TOFinfo=0;
  
  if (!isSignalTOF) {
    //printf("*Strong *** only TPC ret TPC\n");
    return TPCinfo;
  }
    
  TOFinfo = -1;
  
  if (RawAsym(mom, species, kPidTOF, bitmap, kTRUE)) {
    TOFinfo = 1;  
    // printf("*Strong *** ok TOF 3sigma \n");
  }

  if ((TOFinfo > 0) && (mom > 1.5)) {
    TOFinfo = 0;
    //printf("*Strong*** particle with TOF less 2 but p big\n");
  }  
  
  //printf("*Strong*** TPC info %d TOF info %d\n",TPCinfo,TOFinfo);
  return TPCinfo + TOFinfo; 
}

// Imported as-is
Bool_t Significance::RawAsym(Double_t mom, Int_t species, PidDetector_t detector, UInt_t bitmap, Bool_t compat) {
  
  Int_t kLess1, kMore1Less2, kMore2Less3, kMore3;
  kLess1 = kMore1Less2 = kMore2Less3 = kMore3 = -999;
  
  if (detector == kPidTPC) {

    if (species == 2) {
      kLess1      = kTPCPionLess1;
      kMore1Less2 = kTPCPionMore1Less2;
      kMore2Less3 = kTPCPionMore2Less3;
      kMore3      = kTPCPionMore3;
    }
    else if (species == 3){
      kLess1      = kTPCKaonLess1;
      kMore1Less2 = kTPCKaonMore1Less2;
      kMore2Less3 = kTPCKaonMore2Less3;
      kMore3      = kTPCKaonMore3;
    }
    else if (species == 4) {
      kLess1      = kTPCProtonLess1;
      kMore1Less2 = kTPCProtonMore1Less2;
      kMore2Less3 = kTPCProtonMore2Less3;
      kMore3      = kTPCProtonMore3;
    }

  }
  else if (detector == kPidTOF) {

    if (species == 2) {
      kLess1      = kTOFPionLess1;
      kMore1Less2 = kTOFPionMore1Less2;
      kMore2Less3 = kTOFPionMore2Less3;
      kMore3      = kTOFPionMore3;
    }
    else if (species == 3){
      kLess1      = kTOFKaonLess1;
      kMore1Less2 = kTOFKaonMore1Less2;
      kMore2Less3 = kTOFKaonMore2Less3;
      kMore3      = kTOFKaonMore3;
    }
    else if (species == 4) {
      kLess1      = kTOFProtonLess1;
      kMore1Less2 = kTOFProtonMore1Less2;
      kMore2Less3 = kTOFProtonMore2Less3;
      kMore3      = kTOFProtonMore3;
    }

  }
 
  Bool_t isLess1      = bitmap & (1 << kLess1);
  Bool_t isMore1Less2 = bitmap & (1 << kMore1Less2);
  Bool_t isMore2Less3 = bitmap & (1 << kMore2Less3);
  Bool_t isMore3      = bitmap & (1 << kMore3);
  
  Bool_t isDect = (isLess1 || isMore1Less2 || isMore2Less3 ||isMore3);
  if (!isDect) return kFALSE;
  
  Bool_t returncode = kFALSE;
  
  if (compat) {
    if (isLess1 || isMore1Less2 || isMore2Less3) returncode = kTRUE;
    else returncode = kFALSE;
  }
  else {
    if ((mom > 0.6) && (mom < 0.8)) {
      if (isLess1) returncode = kTRUE;
      else returncode = kFALSE;
    }
    else { // if (mom<0.6 || mom>0.8) (not exactly the same thing, but...)
      if (isLess1 || isMore1Less2) returncode = kTRUE;
      else returncode = kFALSE;
    }
  }

  return returncode; 
  
}
