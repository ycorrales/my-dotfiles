////////////////////////////////////////////////
// Class to fit (Convolution Landau+Gaussian) //
//                                            //
// E. Biolcati - 26/06/2009                   //
// Y. Corrales - 03/02/2009                   //
////////////////////////////////////////////////

#include <Riostream.h>
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TGraphErrors.h>
#include <TLatex.h>
#include <TCanvas.h>

#include "MyLanGauFit.h"

//___________________________________________________________________
MyLanGauFit::MyLanGauFit(Double_t xl, Double_t xu, Int_t npar):
fNpars(npar),
fXlower(xl),
fXupper(xu) {
  lgFun = new TF1("MyLanGauFitFunc", this, &MyLanGauFit::EvaluteLanGau,
                  fXlower, fXupper, fNpars, "MyLanGauFit", "EvaluteLanGau");
}

//___________________________________________________________________
MyLanGauFit::~MyLanGauFit() {
  
  if (lgFun)
    delete lgFun;
}

//___________________________________________________________________
Double_t MyLanGauFit::InitParams(TH1D *h, AliPID::EParticleType pType) {
  
  //Par 2 is fix to histograms integral;
  Int_t    bMax= h->GetMaximumBin();
  
  Stat_t   RMS=h->GetRMS();
  Stat_t   Integral=h->Integral("width"); 
  
  Double_t mp=h->GetXaxis()->GetBinCenter(bMax);
  Double_t startvalues[4];  
  
  if (!RMS || !Integral)
    return -1;
 
  //Electron 11
  if (pType == AliPID::kElectron) {
    
    startvalues[0] = RMS / 6;
    startvalues[1] = mp;
    startvalues[2] = Integral;
    startvalues[3] = RMS / 6;
    
    lgFun->SetParameters(startvalues);
  }
  
  //Pion 211
  if (pType == AliPID::kPion) {
    
    startvalues[0] = RMS / 6;
    startvalues[1] = mp;
    startvalues[2] = Integral;
    startvalues[3] = RMS / 6;
    
    lgFun->SetParameters(startvalues);
  }
  
  //Kaon 321
  if ( pType == AliPID::kKaon) {
    
    startvalues[0] = RMS / 6;
    startvalues[1] = mp;
    startvalues[2] = Integral;
    startvalues[3] = RMS / 6;
    
    lgFun->SetParameters(startvalues);
  }
  
  //Proton 2212 
  if (pType == AliPID::kProton) {
    
    startvalues[0] = RMS / 6;
    startvalues[1] = mp;
    startvalues[2] = Integral;
    startvalues[3] = RMS / 6;
    
    lgFun->SetParameters(startvalues);
  }
  
  Double_t lEdge = mp - 1.5 * RMS;
  Double_t hEdge = mp + 3.5 * RMS;
  
  lgFun->SetRange(lEdge, hEdge);
  lgFun->SetNpx(200);
  
  return 0;
}

//___________________________________________________________________
Double_t MyLanGauFit::EvaluteLanGau(Double_t *x, Double_t *par) {
  
  //Fit parameters:
  //par[0]=Width (scale) parameter of Landau density
  //par[1]=Most Probable (MP, location) parameter of Landau density
  //par[2]=Total area (integral -inf to inf, normalization constant)
  //par[3]=Width (sigma) of convoluted Gaussian function
  //
  //In the Landau distribution (represented by the CERNLIB approximation), 
  //the maximum is located at x=-0.22278298 with the location parameter=0.
  //This shift is corrected within this function, so that the actual
  //maximum is identical to the MP parameter.
  // Numeric constants
  
  Double_t invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
  Double_t mpshift  = -0.22278298;       // Landau maximum location

  // Control constants
  Double_t np = 100.0;      // number of convolution steps
  Double_t sc =   5.0;      // convolution extends to +-sc Gaussian sigmas
  
  // Variables
  Double_t xx;
  Double_t mpc;
  Double_t fland;
  Double_t sum = 0.0;
  Double_t xlow,xupp;
  Double_t step;
  Double_t i;
  

  // MP shift correction
  mpc = par[1] - mpshift * par[0]; 
  
  // Range of convolution integral
  xlow = x[0] - sc * par[3];
  xupp = x[0] + sc * par[3];

  step = (xupp-xlow) / np;

  // Convolution integral of Landau and Gaussian by sum
  for(i=1.0; i<=np/2; i++) {
    xx = xlow + (i-.5) * step;
    fland = TMath::Landau(xx,mpc,par[0]) / par[0];
    sum += fland * TMath::Gaus(x[0],xx,par[3]);
    
    xx = xupp - (i-.5) * step;
    fland = TMath::Landau(xx,mpc,par[0]) / par[0];
    sum += fland * TMath::Gaus(x[0],xx,par[3]);
  }
  return (par[2] * step * sum * invsq2pi / par[3]);
}
