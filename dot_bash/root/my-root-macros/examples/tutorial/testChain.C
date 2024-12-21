void testChain(const char *fname = "", Bool_t alien = kTRUE)
{
  FILE *fil = fopen(fname,"r");
  Char_t filname[200];
  TChain *esdChain = new TChain("fNtuple");
  if (alien) TGrid::Connect("alien:", 0, 0, "t");
  while (!feof(fil))
  {
    fscanf(fil, "%s\n", filname);
    TString fPath;
    if (alien) fPath.Form("alien://%s", filname);
    else fPath.Form("%s/%s", filname, "fNtuple");
    printf("Add file %s in chain\n", alienfile.Data());
    esdChain->Add(fPath.Data(), TChain::kBigNumber);
  }
  printf("Number of esd entries %d \n", esdChain->GetEntries());
}
