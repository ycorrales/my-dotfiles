#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void plotMem(TString fname="THnFmem.root") {

  TH1D *hMemV = new TH1D("hMemV","Virt.mem",500,0,500);
  TH1D *hMemR = new TH1D("hMemR","Res.mem",500,0,500);

  string line;
  double memV,memR;
//  ifstream infile ("memV.txt");
//  int count = 1;
//  while (infile >> memV){
//    //  if(infile) {
//    //    infile>>memV;
//    //printf("%f, ",memV);
//    hMemV->SetBinContent(count,memV);
//    count++;
//  }
//  printf("\n");

  ifstream in_file("memR.txt");
  int count = 1;
  if (in_file.is_open()) {
    while (getline(in_file, line)){
      stringstream s_line(line);
      s_line >> memR;
      cout << memR << ", ";
      hMemR->SetBinContent(count, memR);
      count++;
    }
    cout << endl;
  } else {
    cout << "Unable to open file" << endl;
    reterun;
  }
  in_file.close();

  TCanvas *c = new TCanvas("c","",800,700);
  //  hMemR->GetYaxis()->SetRangeUser(2000,2200);
  hMemR->GetXaxis()->SetRangeUser(0, count);
  hMemV->SetMarkerStyle(20);
  hMemV->GetXaxis()->SetTitle("time");
  hMemR->GetXaxis()->SetTitle("time");
  hMemV->GetYaxis()->SetTitle("MB");
  hMemV->GetXaxis()->SetTitle("time");
  hMemV->GetYaxis()->SetTitleOffset(1.3);
  hMemV->SetStats(0);
  hMemR->SetStats(0);
// hMemV->Draw("p");
  hMemR->SetMarkerStyle(20);
  hMemR->SetMarkerColor(kRed);
  hMemR->Draw("p");

  gPad->BuildLegend();


  TFile *fout = new TFile(Form("%s",fname.Data()),"recreate");
  hMemV->Write();
  hMemR->Write();
  fout->Close();
}




