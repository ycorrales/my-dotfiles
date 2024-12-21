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

#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TSelector.h"
#include "TH1F.h"
#include "TDatabasePDG.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TSystem.h"

class Significance : public TSelector {

  public:

    typedef enum {
      kTPCPionLess1        =  0,
      kTPCPionMore1Less2   =  1,
      kTPCPionMore2Less3   =  2,
      kTPCPionMore3        =  3,
      kTPCKaonLess1        =  4,
      kTPCKaonMore1Less2   =  5,
      kTPCKaonMore2Less3   =  6,
      kTPCKaonMore3        =  7,
      kTPCProtonLess1      =  8,
      kTPCProtonMore1Less2 =  9,
      kTPCProtonMore2Less3 = 10,
      kTPCProtonMore3      = 11,
      kTOFPionLess1        = 12,
      kTOFPionMore1Less2   = 13,
      kTOFPionMore2Less3   = 14,
      kTOFPionMore3        = 15,
      kTOFKaonLess1        = 16,
      kTOFKaonMore1Less2   = 17,
      kTOFKaonMore2Less3   = 18,
      kTOFKaonMore3        = 19,
      kTOFProtonLess1      = 20,
      kTOFProtonMore1Less2 = 21,
      kTOFProtonMore2Less3 = 22,
      kTOFProtonMore3      = 23
    } TrackPIDBit_t;

    typedef enum {
      kPidTPC, kPidTOF
    } PidDetector_t;

    Significance(TTree * = NULL) : fHistMass(NULL), fHistMassPhi(NULL) {};
    virtual ~Significance() {};

    virtual void   Init(TTree *tree);
    virtual void   SlaveBegin(TTree *tree);
    virtual Bool_t Process(Long64_t entry);
    virtual Int_t  GetEntry(Long64_t entry, Int_t getall = 0) {
      return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
    virtual void   Terminate();
    //virtual Bool_t Notify() {
    //  Printf("Invoking Notify()!");
    //  return kTRUE;
    //}
    virtual Int_t  Version() const { return 2; };
    Bool_t ParseCutString(const char *cutString, ...);

    // For ROOT
    ClassDef(Significance, 0);

  private:

    // Imported functions from old "analysis"
    Int_t IsSelectedPID();
    Int_t MatchTPCTOF(Double_t mom, Int_t species, UInt_t bitmap);
    Bool_t RawAsym(Double_t mom, Int_t species, PidDetector_t detector,
      UInt_t bitmap, Bool_t compat);

    // Analysis parameters -- in SlaveBegin()
    //TString suffixResonance; // [unused for now]
    //TString suffixCutset;    // [unused for now]
    TString fCutsetInfo;

    // Harmonized analysis parameters -- in SlaveBegin()
    Float_t fCutPtmin;
    Float_t fCutPtmax;
    Float_t fCutDeltaInvMassPhi;
    Float_t fCutPointingAngle;
    Float_t fCutPointingAngleXY;
    Float_t fCutDecLeng;
    Float_t fCutDecLengXY;
    Float_t fCutNorDecLeng;
    Float_t fCutNorDecLengXY;
    Float_t fCutSigvert;
    Float_t fCutKin1, fCutKin2;
    Float_t fCutCentralityMin, fCutCentralityMax;

    // Masses
    Double_t fMassDs, fMassPhi;

    // Associated to TNtuple branches
    Float_t fPidTrackBit0, fPidTrackBit1, fPidTrackBit2;
    Float_t fRetcodeFloat, fPt0, fPt1, fPt2, fPtRec, fSigvert;
    Float_t fPointingAngle, fDecLeng,  fNorDecLeng;
    Float_t fPointingAngleXY, fDecLengXY, fNorDecLengXY;
    Float_t fInvMassKKpi, fInvMasspiKK, fInvMassPhiKKpi, fInvMassPhipiKK;
    Float_t fCosinePiDsFrameKKpi, fCosinePiDsFramepiKK, fCosineKPhiFrameKKpi,
      fCosineKPhiFramepiKK, fCentrality;
    //Float_t fLabDs, fPdgcode0, fP0, fP1, fP2 // [unused]

    // Converted from TNtuple entries
    UInt_t fBitmap0, fBitmap1, fBitmap2;
    Int_t fRetcodeInt;

    // Type of PID to use (1=? 2=? 3=?...)
    Int_t fIsPID;

    // Counters of event types (it is Long64_t because TTree::GetEntry() takes
    // a value that big)
    Long64_t fCounterpiKK;
    Long64_t fCounterKKpi;
    Long64_t fCounterEventsSlave;

    // Output histograms -- in SlaveBegin()
    TH1F *fHistMass;
    TH1F *fHistMassPhi;

    // Object holding the currently selected TNtuple
    TTree *fChain;

};

// For ROOT
ClassImp(Significance);
