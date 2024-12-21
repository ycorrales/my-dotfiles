#include <stdlib.h>

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TMap.h"
#include "TClonesArray.h"
#include "TObject.h"

#include "KeyVal.h"

//______________________________________________________________________________
TMap() {

  // TROOT simple("simple","Example of creation of a tree");

   Int_t comp   = 1;       // by default file is compressed
   Int_t split  = 0;       // by default, split Event in sub branches
   Int_t write  = 1;       // by default the tree is filled

   Int_t testKey[] = {6,10,1,0};
   Int_t testType[] = {1,7,9,23};
   Float_t testE[] = {22.,1.,0.3,4.};

   Int_t nVal = 4;

   TFile *hfile;
   TMap *testMap = 0;
   TTree *tree;

   // Fill event, header and tracks with some random numbers

   Int_t nb = 0;
   Int_t ev;
   Int_t bufsize;

/// This file is now becoming the current directory.

   hfile = new TFile("Event.root","RECREATE","TTree benchmark ROOT file");
   hfile->SetCompressionLevel(comp);

// Create a ROOT Tree and one superbranch

   tree = new TTree("T","An example of a ROOT tree");
   tree->SetAutoSave(1000000000);  // autosave when 1 Gbyte written
   bufsize = 256000;


   // create the map to be written out and an iterator for it

   testMap = new TMap(1,0);
   TMapIter next(testMap);

   TClonesArray *testClone = new TClonesArray("McPart");
   TClonesArray &mcpart = *testClone;


   tree->Branch("testMap", "TMap", &testMap, bufsize,split);
   tree->Branch("testClone", "TClonesArray", &testClone, bufsize,split);

   for (Int_t i=0; i<nVal; ++i) {
     new(mcpart[i]) McPart(testType[i]);
     testMap->Add(new aKey(testKey[i]),new aVal(testE[i],
						(McPart*)mcpart[i]));
     printf("Particle type %i \n",((McPart*)mcpart[i])->GetType());

   }


   if (write) {
      nb += tree->Fill();  //fill the tree
      printf(" tree filled with %i bytes \n",nb);

      hfile->Write();
      tree->Print();
   }
   hfile->Close();
   return 0;
}
