void SystFromMaterial(){
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  TFile* f6=new TFile("LHC10d6_2.0sigma_7DCA/SpectraReco.root");
  TFile* f7=new TFile("LHC10d7_3.0sigma_7DCA/SpectraReco.root");

  TH1F* h6[6];
  TH1F* h7[6];
  TH1F* hRatio[6];
  TString cname[2]={"Pos","Neg"};
  TString spname[3]={"Pion","Kaon","Proton"};
  Int_t colors[6]={2,3,4,kRed+1,kGreen+1,kBlue+1};
  TString splatex[6]={"#pi^{+}","K^{+}","p","#pi^{-}","K^{-}","#bar{p}"};
  for(Int_t iCharge=0; iCharge<2; iCharge++){
    for(Int_t iSpecie=0; iSpecie<3; iSpecie++){
      TString hname=Form("hEffMCPID%s%d",cname[iCharge].Data(),iSpecie);
      Int_t index=3*iCharge+iSpecie;
      h6[index]=(TH1F*)f6->Get(hname.Data());
      h7[index]=(TH1F*)f7->Get(hname.Data());
      hRatio[index]=(TH1F*)h7[index]->Clone(Form("hRatio%s%s",cname[iCharge].Data(),spname[iSpecie].Data()));
      hRatio[index]->Divide(h6[index]);
    }
  }

  TLegend* leg[3];
  TLegendEntry *ent;
  for(Int_t iSpecie=0; iSpecie<3; iSpecie++){
    new TCanvas(Form("c%s",spname[iSpecie].Data()),Form("c%s",spname[iSpecie].Data()));
    gPad->SetGridy();
    Int_t ind1=iSpecie;
    Int_t ind2=3+iSpecie;
    h6[ind1]->SetMarkerStyle(20);
    h7[ind1]->SetMarkerStyle(24);
    h6[ind2]->SetMarkerStyle(21);
    h7[ind2]->SetMarkerStyle(25);
    h6[ind1]->SetMarkerColor(colors[iSpecie]);
    h7[ind1]->SetMarkerColor(colors[iSpecie]);
    h6[ind2]->SetMarkerColor(colors[iSpecie+3]);
    h7[ind2]->SetMarkerColor(colors[iSpecie+3]);
    h6[ind1]->SetLineColor(colors[iSpecie]);
    h7[ind1]->SetLineColor(colors[iSpecie]);
    h6[ind2]->SetLineColor(colors[iSpecie+3]);
    h7[ind2]->SetLineColor(colors[iSpecie+3]);

    h6[ind1]->Draw("P");
    h6[ind1]->GetXaxis()->SetTitle("p_{T}(GeV/c)");
    h6[ind1]->GetYaxis()->SetTitle("Efficiency");
    h6[ind1]->GetYaxis()->SetRangeUser(0.,1.1);
    h7[ind1]->Draw("PSAME");
    h6[ind2]->Draw("PSAME");
    h7[ind2]->Draw("PSAME");
    leg[iSpecie]=new TLegend(0.15,0.7,0.35,0.89);
    leg[iSpecie]->SetFillColor(0);
    ent=leg[iSpecie]->AddEntry(h6[ind1],Form("%s LHC10d6",splatex[ind1].Data()),"PL");
    ent->SetTextColor(h6[ind1]->GetMarkerColor());
    ent=leg[iSpecie]->AddEntry(h7[ind1],Form("%s LHC10d7",splatex[ind1].Data()),"PL");
    ent->SetTextColor(h7[ind1]->GetMarkerColor());
    ent=leg[iSpecie]->AddEntry(h6[ind2],Form("%s LHC10d6",splatex[ind2].Data()),"PL");
    ent->SetTextColor(h6[ind2]->GetMarkerColor());
    ent=leg[iSpecie]->AddEntry(h7[ind2],Form("%s LHC10d7",splatex[ind2].Data()),"PL");
    ent->SetTextColor(h7[ind2]->GetMarkerColor());
    leg[iSpecie]->Draw();
    gPad->Update();
  }

  TCanvas* cR=new TCanvas("Ratios","Ratios");
  cR->SetGridy(); 
  cR->SetLeftMargin(0.12);
  cR->SetBottomMargin(0.12);
  TLegend* legR=new TLegend(0.7,0.15,0.89,0.55);
  legR->SetFillColor(0);
  for(Int_t iSpecie=0; iSpecie<3; iSpecie++){
    for(Int_t iCharge=0; iCharge<2; iCharge++){
      Int_t index=3*iCharge+iSpecie;
      hRatio[index]->SetMarkerColor(colors[index]);
      hRatio[index]->SetLineColor(colors[index]);
      hRatio[index]->SetMarkerStyle(20+iCharge);
      if(index==0){
	hRatio[index]->Draw("P");
	hRatio[index]->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	hRatio[index]->GetYaxis()->SetTitle("Efficiency LHC10d7/LHC10d6");
	hRatio[index]->GetYaxis()->SetTitleOffset(1.1);
	hRatio[index]->GetYaxis()->SetTitleSize(0.05);
	hRatio[index]->GetXaxis()->SetTitleSize(0.05);
	hRatio[index]->GetYaxis()->SetRangeUser(0.6,1.1);
      }else{
	hRatio[index]->Draw("PSAME");
      }
      ent=legR->AddEntry(hRatio[index],splatex[index].Data(),"PL");
    }
  }
  legR->Draw();
}
