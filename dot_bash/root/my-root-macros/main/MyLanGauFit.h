#ifndef MYLANGAUFIT_H
#define MYLANGAUFIT_H

#include "AliPID.h"

class TH1F;
class TF1;

////////////////////////////////////////////////////////////////////////////
// Class to fit  (Convolution Landau+Gaussian)                            //
// Landau Width  GetLanGauFun()->GetParameter(0);                         //
// MPV           GetLanGauFun()->GetParameter(1);                         //
// Integral      GetLanGauFun()->GetParameter(2);                         //
// Gaus Width    GetLanGauFun()->GetParameter(3);                         //
//                                                                        //
// E. Biolcati - 26/06/2009                                               //
// Y. Corrales - 03/02/2010                                               //
////////////////////////////////////////////////////////////////////////////

class MyLanGauFit {
  
public:
  MyLanGauFit(Double_t xl=0, Double_t xu=1500, Int_t npar=4);
  ~MyLanGauFit();
  
  Double_t InitParams(TH1D *h, AliPID::EParticleType pType);
  
  void SetNparams(Int_t prs)  { fNpars = prs;   }
  void SetLowerX(Double_t xl) { fXlower= xl;    }
  void SetUpperX(Double_t xu) { fXupper= xu;    }

  Int_t    GetNparams() { return fNpars;  }
  Double_t GetLowerX()  { return fXlower; }
  Double_t GetUpperX()  { return fXupper; }

  TF1*         GetLanGauFun() { return lgFun;   }
  
private:
  Double_t EvaluteLanGau(Double_t *, Double_t *);
  
  TF1     *lgFun;

  Int_t    fNpars;
  Double_t fXlower;
  Double_t fXupper;
};
#endif
