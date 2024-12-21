void MakeSystHistos(){

  TString cname[2]={"Pos","Neg"};
  TString spname[3]={"Pion","Kaon","Proton"};
  TString ratname[9] = {"Pi_pVsPi_m",
                        "Ka_pVsKa_m",
                        "Pr_pVsPr_m",
                        "Ka_pVsPi_p",
                        "Ka_mVsPi_m",
                        "Pr_pVsPi_p",
                        "Pr_mVsPi_m",
                        "Ka_tVsPi_t",
                        "Pr_tVsPr_t"}
  const Int_t nbins = 22;
  Double_t xbins[nbins+1]={0.08,0.10,0.12,0.14,0.16,0.18,0.20,0.25,0.30,0.35,0.40,0.45,0.50,0.55,0.60,0.65,0.70,0.75,0.80,0.85,0.90,0.95,1.0};
  Int_t firstBin[3]={1,6,8};
  Int_t lastBin[3]={14,12,16};

  // pt independent errors
  Float_t its[3]={0.02,0.02,0.02};
  Float_t fit[3]={0.01,0.05,0.03};
  
  TH1F* hSystFlat[6];
  for(Int_t iCharge=0; iCharge<2; iCharge++){
    for(Int_t iSpecie=0; iSpecie<3; iSpecie++){
      Int_t index=3*iCharge+iSpecie;
      TString hNameTit(Form("hSystFlat%s%s",cname[iCharge].Data(),spname[iSpecie].Data()));
      hSystFlat[index]=new TH1F(hNameTit.Data(),hNameTit.Data(),nbins,xbins);
      for(Int_t iBin=1; iBin<=hSystFlat[index]->GetNbinsX(); iBin++){
	Float_t err1=its[iSpecie];
	Float_t err2=fit[iSpecie];
	Float_t errtot=TMath::Sqrt(err1*err1+err2*err2);
	if((iBin-1)<firstBin[iSpecie] || (iBin-1)>lastBin[iSpecie]) errtot=0.;
	hSystFlat[index]->SetBinContent(iBin,errtot);
      }
    }
  }

  // pt dependent errors
  TH1F* hSystPt[6];
  for(Int_t iCharge=0; iCharge<2; iCharge++){
    for(Int_t iSpecie=0; iSpecie<3; iSpecie++){
      Int_t index=3*iCharge+iSpecie;
      TString hNameTit(Form("hSystPt%s%s",cname[iCharge].Data(),spname[iSpecie].Data()));
      hSystPt[index]=new TH1F(hNameTit.Data(),hNameTit.Data(),nbins,xbins);
    }
  }
  // material budget
  TFile* f6=new TFile("LHC10d6_2.0sigma_7DCA/SpectraReco.root");
  TFile* f7=new TFile("LHC10d7_3.0sigma_7DCA/SpectraReco.root");
  TH1F* h6[6];
  TH1F* h7[6];
  for(Int_t iCharge=0; iCharge<2; iCharge++){
    for(Int_t iSpecie=0; iSpecie<3; iSpecie++){
      TString hname=Form("hEffMCPID%s%d",cname[iCharge].Data(),iSpecie);
      Int_t index=3*iCharge+iSpecie;
      h6[index]=(TH1F*)f6->Get(hname.Data());
      h7[index]=(TH1F*)f7->Get(hname.Data());
      for(Int_t iBin=1; iBin<=h7[index]->GetNbinsX(); iBin++){
	Float_t orig=h6[index]->GetBinContent(iBin);
	Float_t modif=h7[index]->GetBinContent(iBin);
	Float_t delta=0.;
	if(orig>0.){
	  delta=TMath::Abs(1.-modif/orig)/3.;
	}
	if((iBin-1)<firstBin[iSpecie] || (iBin-1)>lastBin[iSpecie]) delta=0.;
	hSystPt[index]->SetBinContent(iBin,delta);
      }
    }
  }

  // secondaries (from fits to DCA) --> assume 50% error on the correction
  TFile* fseccorr = new TFile("../Combine/Files/CorrFac-SecProtonsFromDCA-ITSsa.root");
  TString histoName[2]={"hSecPCorrFromDCA","hSecPbarCorrFromDCA"};

  for(Int_t iCharge=0; iCharge<2; iCharge++){
    Int_t index=3*iCharge+2;
    TH1F* hcorrsec=(TH1F*)fseccorr->Get(histoName[iCharge].Data());
    for(Int_t iBin=1; iBin<=hSystPt[index]->GetNbinsX(); iBin++){
      Float_t orig=hSystPt[index]->GetBinContent(iBin);
      Float_t secerr=0.5*(1.-hcorrsec->GetBinContent(iBin));
      Float_t err=TMath::Sqrt(orig*orig+secerr*secerr);
      if((iBin-1)<firstBin[2] || (iBin-1)>lastBin[2]) err=0.;
      hSystPt[index]->SetBinContent(iBin,err);
    }
  }


  // Total error
  TH1F* hSystTot[6];
  for(Int_t iCharge=0; iCharge<2; iCharge++){
    for(Int_t iSpecie=0; iSpecie<3; iSpecie++){
      Int_t index=3*iCharge+iSpecie;
      TString hNameTit(Form("hSystTot%s%s",cname[iCharge].Data(),spname[iSpecie].Data()));
      hSystTot[index]=new TH1F(hNameTit.Data(),hNameTit.Data(),nbins,xbins);
      for(Int_t iBin=1; iBin<=hSystFlat[index]->GetNbinsX(); iBin++){
	Float_t err1=hSystFlat[index]->GetBinContent(iBin);
	Float_t err2=hSystPt[index]->GetBinContent(iBin);
	Float_t errtot=TMath::Sqrt(err1*err1+err2*err2);
	hSystTot[index]->SetBinContent(iBin,errtot);
      }
    }
  }

  Int_t colors[6]={2,3,4,kRed+1,kGreen+1,kBlue+1};
  TString splatex[6]={"#pi^{+}","K^{+}","p","#pi^{-}","K^{-}","#bar{p}"};
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  TCanvas* cR=new TCanvas("Syst","Syst");
  cR->SetGridy(); 
  cR->SetLeftMargin(0.12);
  cR->SetBottomMargin(0.12);
  TLegend* legR=new TLegend(0.7,0.5,0.89,0.89);
  legR->SetFillColor(0);
  for(Int_t iSpecie=0; iSpecie<3; iSpecie++){
    for(Int_t iCharge=0; iCharge<2; iCharge++){
      Int_t index=3*iCharge+iSpecie;
      hSystTot[index]->SetMarkerColor(colors[index]);
      hSystTot[index]->SetLineColor(colors[index]);
      hSystTot[index]->SetMarkerStyle(20+iCharge);
      if(index==0){
	hSystTot[index]->Draw("P");
	hSystTot[index]->GetXaxis()->SetTitle("p_{T}(GeV/c)");
	hSystTot[index]->GetYaxis()->SetTitle("Systematic Error");
	hSystTot[index]->GetYaxis()->SetTitleOffset(1.1);
	hSystTot[index]->GetYaxis()->SetTitleSize(0.05);
	hSystTot[index]->GetXaxis()->SetTitleSize(0.05);
	hSystTot[index]->GetYaxis()->SetRangeUser(0.,0.15);
      }else{
	hSystTot[index]->Draw("PSAME");
      }
      ent=legR->AddEntry(hSystTot[index],splatex[index].Data(),"PL");
    }
  }
  legR->Draw();

  TFile *outfil=new TFile("ITSsa-systematics.root","recreate");
  for(Int_t iSpecie=0; iSpecie<3; iSpecie++){
    for(Int_t iCharge=0; iCharge<2; iCharge++){
      Int_t index=3*iCharge+iSpecie;
      hSystFlat[index]->Write();
      hSystPt[index]->Write();
      hSystTot[index]->Write();
    }
  }
  outfil->Close();
}
