#define ProofParms_cxx

//////////////////////////////////////////////////////////
//
// Auxilliary TSelector used to test PROOF functionality
//
//////////////////////////////////////////////////////////

#include "ProofParms.h"
#include <TH1F.h>
#include <TH1I.h>
#include <TMath.h>
#include <TString.h>
#include <TSystem.h>
#include "MyParameters.h"

//_____________________________________________________________________________
ProofParms::ProofParms()
{
   // Constructor
}

//_____________________________________________________________________________
ProofParms::~ProofParms()
{
   // Destructor

}

//_____________________________________________________________________________
void ProofParms::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   // Get the parameters object
   MyParameters *mypar = dynamic_cast<MyParameters *>(fInput->FindObject("set1"));
   if (mypar) mypar->DumpParms();
}

//_____________________________________________________________________________
void ProofParms::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   // Get the parameters object
   MyParameters *mypar = dynamic_cast<MyParameters *>(fInput->FindObject("set1"));
   if (mypar) mypar->DumpParms();
}

//_____________________________________________________________________________
Bool_t ProofParms::Process(Long64_t)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either ProofParms::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   return kTRUE;
}

//_____________________________________________________________________________
void ProofParms::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

//_____________________________________________________________________________
void ProofParms::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
