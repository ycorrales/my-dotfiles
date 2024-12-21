#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TH1.h>
#include <TH2F.h>
#include <TNtuple.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TMath.h>
#include <TFile.h>
#include <TStyle.h>
#include <TSystem.h>
#include <Riostream.h>
#endif

Float_t deltaetacut=0.04;  
Float_t deltaphicut=0.04;  
Float_t minITSclu=4.1;
Float_t minTPCclu=90;
Bool_t cutOnDCA=kTRUE;
Float_t chi2cutits=2.5;
Float_t chi2cuttpc=5;

void DoMatch(Int_t nsa,
	     Float_t* ptsa,
	     Float_t* etasa,
	     Float_t* phisa,
	     Bool_t* usedsa,
	     Int_t ntpc,
	     Float_t* pttpc,
	     Float_t* etatpc,
	     Float_t* phitpc,
	     TH1F* hpttpc,
	     TH1F* hptsa);

void MatchTracks(Int_t icase=0, Bool_t isMC=kFALSE){

  const Int_t nCentBins=1;
  Float_t centLimits[nCentBins+1]={-100000.,100000.};
  Int_t colors[nCentBins]={1};


  TH1F* hpttpc=new TH1F("hpttpc","hpttpc",50,0.,5.);
  TH1F* hptpuresa=new TH1F("hptpuresa","hptpuresa",50,0.,5.);

  Double_t ptbins[31]={0.0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,
		       1.0,1.2,1.4,1.6,1.8,2.0,2.2,2.4,2.6,2.8,
		       3.0,3.5,4.0,4.5,5.0,6.0,7.0,8.0,9.0,10.0,12.0};

  const Int_t kSets = 2;
  const Int_t kCases = 3;
  TString direc[kCases] = {"pp900_LHC10c", "pp7TeV_LHC10d", "pp7TeV_LHC10c"};
  TString flPatts[kSets*kCases] = {"LHC10c_118506","LHC11b1a_118506","LHC10d_126424","LHC11f6a_126424","LHC10c_120829","LHC10d4_120829"}
  
  Int_t lastjob=40;
  Double_t xyP[3];
  xyP[0]=32.7;
  xyP[1]=44.8;
  xyP[2]=1.3;

  if(isMC){
 //   lastjob=2;
    xyP[0]=36.; //MC LHC10d1
    xyP[1]=43.9;
    xyP[2]=1.3;
  }

  Float_t pttpc[10000],etatpc[10000],phitpc[10000];
  Float_t ptsa[10000],etasa[10000],phisa[10000];
  Bool_t usedsa[10000];
  Int_t index = icase*2+isMC;

  for(Int_t iFil=0; iFil<lastjob; iFil++){
    TFile* fil=TFile::Open(Form("%s/%s/%03d/AnalysisResults.root",direc[icase].Data(),flPatts[index].Data(), iFil));
    if(!fil) continue;
    TDirectoryFile* df=(TDirectoryFile*)fil->Get("ITSsaTracks");
    if(!df) continue;
    TList* l=(TList*)df->Get("clistITSsaTracks");
    if(!l) continue;
    TNtuple* nt=(TNtuple*)l->FindObject("ntupleTracks");
    if(!nt) continue;
    Int_t nEntries=nt->GetEntriesFast();

    Float_t pt,eta,phi,ITSrefit,TPCrefit,TPCin,ITSpureSA,nITSclu,nTPCclu,chi2,TPCchi2,centr,event;
    Float_t d0xy;

    nt->SetBranchAddress("iEvent",&event);
    nt->SetBranchAddress("pt",&pt);
    nt->SetBranchAddress("eta",&eta);
    nt->SetBranchAddress("phi",&phi);
    nt->SetBranchAddress("ITSrefit",&ITSrefit);
    nt->SetBranchAddress("TPCin",&TPCin);
    nt->SetBranchAddress("TPCrefit",&TPCrefit);
    nt->SetBranchAddress("ITSpureSA",&ITSpureSA);
    nt->SetBranchAddress("nITSclu",&nITSclu);
    nt->SetBranchAddress("nTPCclu",&nTPCclu);
    nt->SetBranchAddress("chi2ITS",&chi2);
    nt->SetBranchAddress("chi2TPC",&TPCchi2);
    nt->SetBranchAddress("centr",&centr);
    nt->SetBranchAddress("d0xy",&d0xy);
 
    Int_t iEventOld=-9999;
    Float_t centrold=-999.;
    Int_t ntpc=0;
    Int_t nsa=0;
    for(Int_t i=0; i<nEntries; i++)
    {
      nt->GetEvent(i);
      Int_t iEvent=(Int_t)(event+0.1);
      if(iEvent!=iEventOld)
      {
	      Int_t theBin=TMath::BinarySearch(nCentBins+1,centLimits,centrold);
	      if(theBin>=0 && theBin<nCentBins){
          printf("Call Do Match; Event=%d Central=%f\n",iEvent,centrold);
	        DoMatch(nsa,ptsa,etasa,phisa,usedsa,ntpc,pttpc,etatpc,phitpc,hpttpc,hptpuresa);
	      }
	      centrold=centr;
	      iEventOld=iEvent;
	      nsa=0;
	      ntpc=0;
      }
      if(ITSrefit<0.1) continue;
      if(nITSclu<minITSclu) continue;
      if(TMath::Abs(eta)>0.8) continue;
      Double_t xySigma = xyP[0] + xyP[1]/TMath::Power(TMath::Abs(pt),xyP[2]);
      Double_t xyMax = 7*xySigma; //in micron
      if(cutOnDCA && TMath::Abs(d0xy*10000)>xyMax) continue;
      if(ITSpureSA>0.5)
      {
        if(chi2/nITSclu>chi2cutits) continue;
	      ptsa[nsa]=pt;
	      etasa[nsa]=eta;
	      phisa[nsa]=phi;
	      usedsa[nsa]=kFALSE;
	      nsa++;
      }
      else 
      {
       if(TPCin>0.1)
       {
	       if(TPCrefit<0.1) continue;
	       if(TPCchi2/nTPCclu>chi2cuttpc) continue;
 	       if(nTPCclu<minTPCclu) continue;
       }
       else
       {
         if(chi2/nITSclu>chi2cutits) continue;
       }
         pttpc[ntpc]=pt;
	       etatpc[ntpc]=eta;
	       phitpc[ntpc]=phi;
	       ntpc++;
      }
    }
    delete nt;
    df->Close();
    fil->Close();
    delete fil;
  }
  
  hpttpc->Sumw2();
  hptpuresa->Sumw2();

  TH1F* hRatio=(TH1F*)hptpuresa->Clone("hRatio");
  hRatio->Divide(hptpuresa, hpttpc,1.,1.,"B");
  
  hRatio->Fit("pol0","","",0.2,0.8);

  gStyle->SetOptStat(0);
  TH2F* hempty=new TH2F("hempty","",30,0.,3.,10,0.,1.5);
  TCanvas* crat=new TCanvas("crat","",800,800);
  hempty->Draw();
  hempty->GetXaxis()->SetTitle("pt (GeV/c)");
  hempty->GetYaxis()->SetTitle("Fraction of matched");
  hempty->GetYaxis()->SetTitleOffset(1.2);
  TLegend* leg4=new TLegend(0.2,0.2,0.4,0.4);
  leg4->SetFillColor(0);
  hRatio->SetLineColor(1);
  hRatio->Draw("same");

  TFile* outfil=new TFile(Form("%s/MatchedTracks_%s.root",direc[icase].Data(),flPatts[index].Data()),"recreate");
  hpttpc->Write();
  hptpuresa->Write();
  hRatio->Write(); 
  outfil->Close();
}  

void DoMatch(Int_t nsa,
	     Float_t* ptsa,
	     Float_t* etasa,
	     Float_t* phisa,
	     Bool_t* usedsa,
	     Int_t ntpc,
	     Float_t* pttpc,
	     Float_t* etatpc,
	     Float_t* phitpc,
	     TH1F* hpttpc,
	     TH1F* hptsa){

  printf("---- nSA=%d --- nTPC=%d-------\n",nsa, ntpc);
  for(Int_t it=0;it<ntpc;it++){
    hpttpc->Fill(pttpc[it]);
    for(Int_t is=0;is<nsa;is++){
      if(usedsa[is]) continue;
      Double_t deltapt=TMath::Abs(pttpc[it]-ptsa[is]);
      Double_t deltaphi=TMath::Abs(phitpc[it]-phisa[is]);
      if(deltaphi>TMath::Pi()) deltaphi-=2*TMath::Pi();
      if(deltaphi<-TMath::Pi()) deltaphi+=2*TMath::Pi();
      Double_t deltaeta=TMath::Abs(etatpc[it]-etasa[is]);
      if(deltapt<0.1*pttpc[it] && deltaphi<deltaphicut && deltaeta<deltaetacut){
	usedsa[is]=kTRUE;
	hptsa->Fill(ptsa[is]);
	break;
      }
    }
  }
}
