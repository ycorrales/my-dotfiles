//////////////////////////////////////////////////////////
//
// Auxilliary TSelector used to test PROOF functionality
//
//////////////////////////////////////////////////////////

#ifndef ProofParms_h
#define ProofParms_h

#include <TSelector.h>

class TH1I;

class ProofParms : public TSelector {
public :

   ProofParms();
   virtual ~ProofParms();
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual Bool_t  Process(Long64_t entry);
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(ProofParms,0);
};

#endif
