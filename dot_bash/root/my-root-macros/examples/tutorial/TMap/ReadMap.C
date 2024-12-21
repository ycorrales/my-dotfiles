void ReadMap()
{
  TFile* _file=new TFile("Event.root");
  TTree* tree=(TTree*)_file->Get("T");
  //Read tree branch
  TClonesArray* testClone;
  TMap*         testMap;
  tree->SetBranchAddress("testClone",&testClone);
  tree->SetBranchAddress("testMap",&testMap);
  tree->GetEntry(0);
  Printf("Reading MC part from TClonesArray");
  for(Int_t i=0;i<testClone->GetEntries();++i) {
    McPart* mcpart=(McPart*)testClone->At(i);
    Printf("Index %d, Type %d",i, mcpart->GetType());
  }
  Printf("\nReading keys and values from TMap");
  TMapIter next(testMap);
  aKey* key;
  while(key=(aKey*)next()) {
    aVal* val=(aVal*)testMap->GetValue(key);
    Int_t ikey = (*key).GetKey();
    Float_t ev = val->GetVal();
    Int_t type = val->GetMcPart()->GetType();
    Printf("Key %d, Val %.1f, type %d", ikey, ev, type);
  }
 return; 
}
