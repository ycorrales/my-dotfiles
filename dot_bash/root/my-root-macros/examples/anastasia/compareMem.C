void compareMem() {
  TFile *_file0 = TFile::Open("Ds_test2.root");
  TFile *_file1 = TFile::Open("Dplus_CleanupAndDelete.root");//Ds_NOCleanupAndDelete.root");
  TFile *_file2 = TFile::Open("Ds_test3.root");//Dplus_CleanupAndDelete.root");

  TH1D *hMemR0 = (TH1D*)_file0->Get("hMemR");
  TH1D *hMemR1 = (TH1D*)_file1->Get("hMemR");
  TH1D *hMemR2 = (TH1D*)_file2->Get("hMemR");
  TH1D *hMemV0 = (TH1D*)_file0->Get("hMemV");
  TH1D *hMemV1 = (TH1D*)_file1->Get("hMemV");
  TH1D *hMemV2 = (TH1D*)_file2->Get("hMemV");

  hMemV0->SetMarkerStyle(24);
  hMemV1->SetMarkerStyle(24);
  hMemV2->SetMarkerStyle(24);
  hMemV0->SetMarkerColor(kRed);
  hMemR0->SetMarkerColor(kRed);
  hMemV1->SetMarkerColor(kBlue);
  hMemR1->SetMarkerColor(kBlue);
  hMemV2->SetMarkerColor(kGreen+2);
  hMemR2->SetMarkerColor(kGreen+2);

  TCanvas *c = new TCanvas("c","",800,600);
  hMemR0->GetYaxis()->SetTitle("MB");
  hMemR0->GetYaxis()->SetTitleOffset(1.3);
 
 hMemR0->Draw("p");
  hMemR1->Draw("psame");
  hMemR2->Draw("psame");
  hMemV0->Draw("psame");
  hMemV1->Draw("psame");
  hMemV2->Draw("psame");

  TLegend *l = new TLegend(0.1,0.1,0.4,0.4);
  l->AddEntry(hMemR1,"D+, delete + cleanUp");//Ds, no delete/CleanUp");
  l->AddEntry(hMemR0,"Ds, wo 2nd IsSelected");
  l->AddEntry(hMemR2,"Ds, w 2nd IsSelected");//");
  l->Draw("same");
}
