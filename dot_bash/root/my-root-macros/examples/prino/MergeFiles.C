void MergeFiles()
{
  printf("Setting strict fast timeouts\n");
  gEnv->SetValue("XNet.ConnectTimeout"    , 20);
  gEnv->SetValue("XNet.RequestTimeout"    , 40);
  gEnv->SetValue("XNet.MaxRedirectCount"  ,  2);
  gEnv->SetValue("XNet.ReconnectWait"     ,  2);
  gEnv->SetValue("XNet.FirstConnectMaxCnt",  3);
  gEnv->SetValue("XNet.TransactionTimeout", 300);

  gSystem->Load("libNetx.so") ;
  gSystem->Load("libRAliEn.so");

  TGrid::Connect("alien://") ;

  TString homedir = gGrid->GetHomeDirectory(); // has a trailing slash


  TString path("/alice/sim/2016/LHC16h1/245064/");
  TString filename("QAresults.root");

  TFileMerger mg;


  TGridResult* gr = gGrid->Query(path, filename);

  Int_t numFiles = gr->GetEntries();
  Int_t outFil = 1;
  Int_t nFiles = 0;
  printf("================>%d files found\n", numFiles);
  if (numFiles < 1) return;
  Int_t maxFiles = numFiles;
  for (Int_t iFil = 0; iFil < maxFiles ; iFil++) {

    if (nFiles % 100 == 0) {
      if (nFiles > 0) {
        printf("First step, merge into %s\n", mg.GetOutputFileName());
        mg.GetMergeList()->ls();
        mg.Merge();
        mg.Reset();
      }
      mg.OutputFile(Form("./OutputMass.Merged.Tmp%d.root", outFil));
      outFil++;
    }

    TString fileNameLong = Form("%s", gr->GetKey(iFil, "turl"));
    TFile* f = TFile::Open(fileNameLong.Data());
    if (!f->IsOpen()) continue;
    mg.AddFile(fileNameLong.Data());
    f->Close();

    nFiles++;
  }
  mg.GetMergeList()->ls();
  mg.Merge();
  mg.Reset();

  mg.OutputFile("./OutputMass.Merged.root");
  for (Int_t io = 1; io < outFil; io++) {
    TString mfilname = Form("./OutputMass.Merged.Tmp%d.root", io);
    TFile* f = TFile::Open(mfilname.Data());
    if (!f->IsOpen()) continue;
    f->Close();
    mg.AddFile(mfilname.Data());
  }
  mg.GetMergeList()->ls();
  mg.Merge();
  gSystem->Exec("rm OutputMass.Merged.Tmp*.root");


}

