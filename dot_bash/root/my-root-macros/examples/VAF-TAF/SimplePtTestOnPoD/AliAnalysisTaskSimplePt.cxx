// ROOT includes
#include "TROOT.h"
#include "TH1.h"
#include "TH2.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"
#include "TObjString.h"
#include "TObjArray.h"
#include "TF1.h"
#include "TList.h"
#include "TStyle.h"
#include "TString.h"
#include "AliInputEventHandler.h"
#include "AliCentrality.h"
#include "AliAODEvent.h"
#include "AliAODTrack.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisTaskSE.h"
#include "AliAnalysisTaskSimplePt.h"

ClassImp(AliAnalysisTaskSimplePt);

//__________________________________________________________________________
AliAnalysisTaskSimplePt::AliAnalysisTaskSimplePt() :
  AliAnalysisTaskSE(),
  fAODEvent(0x0),
  fOutput(0x0)
{
  // Default ctor.
}

//__________________________________________________________________________
AliAnalysisTaskSimplePt::AliAnalysisTaskSimplePt(const char *name) :
  AliAnalysisTaskSE(name),
  fAODEvent(0x0),
  fOutput(0x0)
{
  // Constructor. Initialization of Inputs and Outputs
  DefineOutput(1, TList::Class());
}

//___________________________________________________________________________
AliAnalysisTaskSimplePt& AliAnalysisTaskSimplePt::operator=(const AliAnalysisTaskSimplePt& c) 
{
  // Assignment operator
  if (this != &c) {
    AliAnalysisTaskSE::operator=(c) ;
  }
  return *this;
}

//___________________________________________________________________________
AliAnalysisTaskSimplePt::AliAnalysisTaskSimplePt(const AliAnalysisTaskSimplePt& c) :
  AliAnalysisTaskSE(c),
  fAODEvent(c.fAODEvent),
  fOutput(c.fOutput)
 {
  // Copy ctor
 }

//___________________________________________________________________________
AliAnalysisTaskSimplePt::~AliAnalysisTaskSimplePt()
{
  // Destructor
  if (AliAnalysisManager::GetAnalysisManager()->GetAnalysisType() != AliAnalysisManager::kProofAnalysis)
    delete fOutput;
 }

//___________________________________________________________________________
void AliAnalysisTaskSimplePt::NotifyRun()
{}

//___________________________________________________________________________
void AliAnalysisTaskSimplePt::UserCreateOutputObjects(){

  // Output objects creation
  fOutput = new TList();
  fOutput->SetOwner(); 

  // Pt distribution
  fHistThePt = new TH1D("hThePt", "The pt Distribution", 200, 0, 10);
  fOutput->Add( fHistThePt );

  // Required both here and in UserExec()
  PostData(1, fOutput);
} 

//___________________________________________________________________________
void AliAnalysisTaskSimplePt::UserExec(Option_t *)
{
  // Execute analysis for current InputEvent

  fAODEvent = dynamic_cast<AliAODEvent*> (InputEvent());
  if ( ! fAODEvent ) {
    AliError ("AOD event not found. Nothing done!");
    return;
  }

  // Loop over Dimuons
  for(Int_t nd=0; nd<fAODEvent->GetNumberOfDimuons(); nd++) {
    AliAODDimuon *dimu = dynamic_cast<AliAODDimuon*>( fAODEvent->GetDimuon(nd) );
    fHistThePt->Fill( dimu->Pt() );
  }

  // Required both here and in UserCreateOutputObjects()
  PostData(1, fOutput);
}

//___________________________________________________________________________
void AliAnalysisTaskSimplePt::Terminate(Option_t *) 
{
  // Display the Pt histogram

  fOutput = dynamic_cast<TList*> (GetOutputData(1));
  if (fOutput) {
    fHistThePt = dynamic_cast<TH1D *>( fOutput->FindObject("hThePt") );
    if (fHistThePt) {
      fHistThePt->Draw();
    }
  }
}
