enum hout_bins_meaning {
  kYield = 1,
  kYieldStat,
  kYieldSysHi,
  kYieldSysLo,
  kMean,
  kMeanStat,
  kMeanSysHi,
  kMeanSysLo
};

enum func_type {
  kLevyTsallis,
  kBlastWave,
  kBoltz,
  kMTexpo,
  kPTexpo,
  kFermiDirac,
  kBoseEinstein,
  kBylinkin,
  kHagedorn,
  kBoltPWL,
  numfunctypes
};

char c_shape[numfunctypes][20] = {
  "LevyTsallis",
  "BlastWave",
  "Boltzmann",
  "MTexponent",
  "PTexponent",
  "FermiDirac",
  "BoseEinstein",
  "  Bylinkin",
  "  Hagedorn",
  "BoltPWL"
};

char c_multbins_xi[11][10] = {
  "0-100%",
  "0-1%",
  "1-5%",
  "5-10%",
  "10-15%",
  "15-20%",
  "20-30%",
  "30-40%",
  "40-50%",
  "50-70%",
  "70-100%"
};

char c_multbins_om[6][10] = {
  "0-100%",
  "0-5%",
  "5-15%",
  "15-30%",
  "30-50%",
  "50-100%"
};

bool isxiforLevy = kTRUE;
bool isomforLevy = kFALSE;

const int multbins_xi = 10;
const int multbins_om = 5;

double rangestobefit_xi[multbins_xi+1][numfunctypes][2];
double rangestobefit_om[multbins_om+1][numfunctypes][2];

void EstimateSystematic(bool skip_xi=kFALSE, bool skip_om=kFALSE, int reference=kLevyTsallis){
  
  gErrorIgnoreLevel = kError;
  
  gStyle->SetOptStat(0);
  gROOT->LoadMacro("./YieldMean.C+");
  
  TFile *fin = new TFile("./FinalSpectraWithSysts.root","read");  
  
  DefineRangesToBeFit();
  TH1* h_out = 0x0;
  
  // xi case
  //---------------------------------------------------------------------------------------------------------------
    
    if(!skip_xi){
    
      isxiforLevy = kTRUE;
      isomforLevy = kFALSE;
   
    //get spectra and scale (just for visualization)
      
      float scalefactor_xi[multbins_xi+1] = {1./200,512,256,128,64,32,16,8,4,2,1}; // 0 is MB, 1-10 is multdiff
      TH1D *spectrum_xi_stat[multbins_xi+1]; // 0 is MB, 1-10 is multdiff
      TH1D *spectrum_xi_syst[multbins_xi+1];
      for(int n3=0; n3<multbins_xi+1; n3++){
        if(n3==0){
          spectrum_xi_stat[n3] = (TH1D*) fin->Get("fSpectrumStat_int_xi");
          spectrum_xi_syst[n3] = (TH1D*) fin->Get("fSpectrumTotSyst_int_xi");
        }
        else{
          spectrum_xi_stat[n3] = (TH1D*) fin->Get(Form("fSpectrumStat_xi[%d]",n3-1));
          spectrum_xi_syst[n3] = (TH1D*) fin->Get(Form("fSpectrumTotSyst_xi[%d]",n3-1));
        }
        spectrum_xi_stat[n3]->SetName(Form("spectrum_xi_stat[%d]",n3));
        spectrum_xi_stat[n3]->Scale(scalefactor_xi[n3]);
        spectrum_xi_syst[n3]->SetName(Form("spectrum_xi_syst[%d]",n3));
        spectrum_xi_syst[n3]->Scale(scalefactor_xi[n3]);
      }
    
    
    //fit spectra and extract yields and means
      
      double yield_xi[multbins_xi+1][numfunctypes];
      double estat_yield_xi[multbins_xi+1][numfunctypes];
      double esyst_yield_xi[multbins_xi+1][numfunctypes];
      double mean_xi[multbins_xi+1][numfunctypes];
      double estat_mean_xi[multbins_xi+1][numfunctypes];
      double esyst_mean_xi[multbins_xi+1][numfunctypes];
      
      TF1 *func_xi[multbins_xi+1][numfunctypes];
      
      TCanvas *can_xi = new TCanvas("can_xi","can_xi",900,900); 
      TH1D *frame_spectra_xi = new TH1D("frame_spectra_xi","",1,0,7);
      PrepareCanvasAndFrame(can_xi,frame_spectra_xi,kFALSE);
      
      for(int n3=0; n3<multbins_xi+1; n3++){
        for(int n1=0; n1<numfunctypes-2; n1++){
          if(n1==kPTexpo) continue;
//           if(n1!=kBylinkin && n1!=kLevyTsallis) continue;
          func_xi[n3][n1] = ChooseFunction(n3,n1,kFALSE,rangestobefit_xi[n3][n1][1]);
          func_xi[n3][n1]->SetLineColor(n1+1); if(n1==(numfunctypes-1)) func_xi[n3][n1]->SetLineColor(1);
          h_out = YieldMean(spectrum_xi_stat[n3],spectrum_xi_syst[n3],func_xi[n3][n1],0,10,rangestobefit_xi[n3][n1][0],rangestobefit_xi[n3][n1][1],0.01,0.5,"0qI");
          //if(n1==kBylinkin) printf("Mult%d	%s	chi2/ndf = %f\n",n3,c_shape[n1],func_xi[n3][n1]->GetChisquare()/func_xi[n3][n1]->GetNDF());
	  //if(n1==kBylinkin) printf("%f   %f    %f    %f     %f     %f\n",func_xi[n3][n1]->GetParameter(0),func_xi[n3][n1]->GetParameter(1),func_xi[n3][n1]->GetParameter(2),func_xi[n3][n1]->GetParameter(3),func_xi[n3][n1]->GetParameter(4),func_xi[n3][n1]->GetParameter(5));
	  yield_xi[n3][n1] = h_out->GetBinContent(kYield);
          estat_yield_xi[n3][n1] = h_out->GetBinContent(kYieldStat);
          esyst_yield_xi[n3][n1] = TMath::Max(h_out->GetBinContent(kYieldSysHi),h_out->GetBinContent(kYieldSysLo));
          mean_xi[n3][n1] = h_out->GetBinContent(kMean);
          estat_mean_xi[n3][n1] = h_out->GetBinContent(kMeanStat);
          esyst_mean_xi[n3][n1] = TMath::Max(h_out->GetBinContent(kMeanSysHi),h_out->GetBinContent(kMeanSysLo));
          h_out->Reset();
          can_xi->cd();
          spectrum_xi_syst[n3]->Draw("same");
          func_xi[n3][n1]->Draw("same");
          can_xi->Update();
        }
      }
    
    
    //calculate extrapfrac, systematics and R factors
      
      double syst_yield_xi[multbins_xi+1];
      double syst_mean_xi[multbins_xi+1];
      double R_yield_xi[multbins_xi+1][numfunctypes]; //R factor (uncorrelated part)
      double R_mean_xi[multbins_xi+1][numfunctypes];
      double Rmax_yield_xi[multbins_xi+1]; //maximum among R factors from different functions. One for each multiplicity bin
      double Rmax_mean_xi[multbins_xi+1];
      double extrap_xi[multbins_xi+1][numfunctypes];
      double extrapfrac_xi[multbins_xi+1][numfunctypes];
      
      for(int n3=0; n3<multbins_xi+1; n3++){
        syst_yield_xi[n3]= 0;
        syst_mean_xi[n3] = 0;
	Rmax_yield_xi[n3]= 0;
	Rmax_mean_xi[n3]= 0;
        for(int n1=0; n1<numfunctypes-2; n1++){
          R_yield_xi[n3][n1]= 0;
          R_mean_xi[n3][n1] = 0;
          extrapfrac_xi[n3][n1] = 0;
          //if(n3==0) R_yield_xi_perfuntion[n1]=0;
          if(n1==kPTexpo) continue;
//           if(n1!=kBylinkin && n1!=kLevyTsallis) continue;
          extrap_xi[n3][n1] = func_xi[n3][n1]->Integral(0,0.6);
          extrapfrac_xi[n3][n1] = extrap_xi[n3][n1]/yield_xi[n3][n1]*100;
	  if(n1==reference) printf("mult %d  -  Extrap frac = %.1f\n",n3,extrapfrac_xi[n3][n1]);
          if(n1==reference) continue;
          syst_yield_xi[n3] = TMath::Max(syst_yield_xi[n3],TMath::Abs(yield_xi[n3][n1]-yield_xi[n3][reference])/yield_xi[n3][reference]);
          syst_mean_xi[n3] = TMath::Max(syst_mean_xi[n3],TMath::Abs(mean_xi[n3][n1]-mean_xi[n3][reference])/mean_xi[n3][reference]);
          if(n3>0){
            R_yield_xi[n3][n1] = TMath::Abs((yield_xi[n3][n1]/yield_xi[n3][reference]) / (yield_xi[0][n1]/yield_xi[0][reference])-1);
            R_mean_xi[n3][n1] = TMath::Abs((mean_xi[n3][n1]/mean_xi[n3][reference]) / (mean_xi[0][n1]/mean_xi[0][reference])-1);
	    if(R_yield_xi[n3][n1]>Rmax_yield_xi[n3]) Rmax_yield_xi[n3] = R_yield_xi[n3][n1];
	    if(R_mean_xi[n3][n1]>Rmax_mean_xi[n3]) Rmax_mean_xi[n3] = R_mean_xi[n3][n1];
          }
        } 
      }
    
    
    //histos 
      
      TH1D *h_syst_yield_xi = new TH1D("h_syst_yield_xi","",multbins_xi+1,0,multbins_xi+1);
      TH1D *h_systfrac_yield_xi = new TH1D("h_systfrac_yield_xi","",multbins_xi+1,0,multbins_xi+1);
      TH1D *h_systWITHconstsystfrac_yield_xi = new TH1D("h_systWITHconstsystfrac_yield_xi","",multbins_xi+1,0,multbins_xi+1);
      TH1D *h_systuncWITHconstsystfrac_yield_xi = new TH1D("h_systuncWITHconstsystfrac_yield_xi","",multbins_xi+1,0,multbins_xi+1);
      TH1D *h_systcorWITHconstsystfrac_yield_xi = new TH1D("h_systcorWITHconstsystfrac_yield_xi","",multbins_xi+1,0,multbins_xi+1);
      for(int n3=0; n3<multbins_xi+1; n3++) {
        h_syst_yield_xi->SetBinContent(n3+1,syst_yield_xi[n3]*100);
        h_syst_yield_xi->SetBinError(n3+1,1e-08);
        h_systfrac_yield_xi->SetBinContent(n3+1,syst_yield_xi[n3]*yield_xi[n3][reference]/extrap_xi[n3][reference]*100);
        h_systfrac_yield_xi->SetBinError(n3+1,1e-08);
        h_systWITHconstsystfrac_yield_xi->SetBinContent(n3+1,extrap_xi[n3][reference]*29.27/yield_xi[n3][reference]);
        h_systWITHconstsystfrac_yield_xi->SetBinError(n3+1,1e-08);
      }
      for(int n3=0; n3<multbins_xi+1; n3++) {
	double uncpart_xi = TMath::Sqrt(h_systWITHconstsystfrac_yield_xi->GetBinContent(n3+1)*h_systWITHconstsystfrac_yield_xi->GetBinContent(n3+1)-h_syst_yield_xi->GetBinContent(2)*h_syst_yield_xi->GetBinContent(2));
	double corpart_xi = TMath::Sqrt(h_systWITHconstsystfrac_yield_xi->GetBinContent(n3+1)*h_systWITHconstsystfrac_yield_xi->GetBinContent(n3+1)-uncpart_xi*uncpart_xi);
        h_systuncWITHconstsystfrac_yield_xi->SetBinContent(n3+1,uncpart_xi);
        h_systuncWITHconstsystfrac_yield_xi->SetBinError(n3+1,1e-08);
        h_systcorWITHconstsystfrac_yield_xi->SetBinContent(n3+1,corpart_xi);
        h_systcorWITHconstsystfrac_yield_xi->SetBinError(n3+1,1e-08);
      }    
    
    //canvasing
      
      TCanvas *cansys_xi = new TCanvas("cansys_xi","cansys_xi",700*1.5,500*1.5);
      double maxleftscale = 1.4*h_syst_yield_xi->GetMaximum();
      double maxrightscale = 1.1*h_systfrac_yield_xi->GetMaximum();
      TH1D *frame_R_xi = new TH1D("frame_R_xi","frame_R_xi",multbins_xi+1,0,multbins_xi+1);
      frame_R_xi->GetYaxis()->SetRangeUser(0,maxleftscale);
      frame_R_xi->SetTitle("Systematic on Yield due to Extrapolation: #Xi");
      frame_R_xi->GetYaxis()->SetTitle("Systematic on Yield (%)");
      frame_R_xi->GetXaxis()->SetTitle("mult. bin");
      frame_R_xi->GetXaxis()->SetTitleSize(0.045);
      frame_R_xi->GetXaxis()->SetLabelSize(0.045);
      for(int j = 0; j<multbins_xi+1; j++) frame_R_xi->GetXaxis()->SetBinLabel(j+1,c_multbins_xi[j]);
      frame_R_xi->Draw();
//       h_syst_yield_xi->SetFillStyle(3001);
      h_syst_yield_xi->SetFillStyle(0);
      h_syst_yield_xi->SetLineColor(kBlack);
      h_syst_yield_xi->SetLineWidth(2);
      h_syst_yield_xi->SetFillColor(kGray+1);
      h_syst_yield_xi->Draw("HISTsame");
      h_systWITHconstsystfrac_yield_xi->SetFillStyle(0);
      h_systWITHconstsystfrac_yield_xi->SetLineColor(kBlack);
      h_systWITHconstsystfrac_yield_xi->SetLineWidth(2);
      h_systWITHconstsystfrac_yield_xi->SetLineStyle(3);
      h_systWITHconstsystfrac_yield_xi->Draw("HISTsame");
      h_systuncWITHconstsystfrac_yield_xi->SetFillStyle(0);
      h_systuncWITHconstsystfrac_yield_xi->SetLineColor(kBlue);
      h_systuncWITHconstsystfrac_yield_xi->SetLineWidth(2);
      h_systuncWITHconstsystfrac_yield_xi->SetLineStyle(3);
      h_systuncWITHconstsystfrac_yield_xi->Draw("HISTsame");
      h_systcorWITHconstsystfrac_yield_xi->SetFillStyle(0);
      h_systcorWITHconstsystfrac_yield_xi->SetLineColor(kGreen);
      h_systcorWITHconstsystfrac_yield_xi->SetLineWidth(2);
      h_systcorWITHconstsystfrac_yield_xi->SetLineStyle(3);
      h_systcorWITHconstsystfrac_yield_xi->Draw("HISTsame");
      h_systfrac_yield_xi->Scale(maxleftscale/maxrightscale);
      h_systfrac_yield_xi->SetFillStyle(0);
      h_systfrac_yield_xi->SetLineStyle(1);
      h_systfrac_yield_xi->SetFillColor(kRed);
      h_systfrac_yield_xi->SetLineColor(kRed);
      h_systfrac_yield_xi->SetLineWidth(2);
      h_systfrac_yield_xi->Draw("HISTsame");
      // draw an axis on the right side
      //TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),gPad->GetUxmax(),gPad->GetUymax(),0,1.1*h_syst_yield_xi->GetMaximum(),510,"+L");
      TGaxis *axis = new TGaxis(11,0,11,maxleftscale,0,maxrightscale,510,"+L");
      axis->SetTitle("Systematic on Extrapolation (%)");
      axis->SetLabelFont(42);
      axis->SetLabelSize(frame_R_xi->GetYaxis()->GetLabelSize());
      axis->SetTitleFont(42);
      axis->SetTitleSize(frame_R_xi->GetYaxis()->GetTitleSize());
      axis->SetTitleColor(kRed);
      axis->SetLineColor(kRed);
      axis->SetTextColor(kRed);
      axis->SetLabelColor(kRed);
      axis->Draw();
      TLine *lineRat_xi = new TLine(0,h_systfrac_yield_xi->GetMaximum(),11,h_systfrac_yield_xi->GetMaximum());
      lineRat_xi->SetLineColor(kRed);
      lineRat_xi->SetLineStyle(3);
      lineRat_xi->SetLineWidth(2);
      lineRat_xi->Draw();
    }
 
  
  // om case
  //---------------------------------------------------------------------------------------------------------------
    
    if(!skip_om){
    
      isomforLevy = kFALSE;
      isomforLevy = kTRUE;
   
    //get spectra and scale (just for visualization)
      
      float scalefactor_om[multbins_om+1] = {1./150,16,8,4,2,1};
      TH1D *spectrum_om_stat[multbins_om+1]; // 0 is MB, 1-10 is multdiff
      TH1D *spectrum_om_syst[multbins_om+1];
      for(int n3=0; n3<multbins_om+1; n3++){
        if(n3==0){
          spectrum_om_stat[n3] = (TH1D*) fin->Get("fSpectrumStat_int_om");
          spectrum_om_syst[n3] = (TH1D*) fin->Get("fSpectrumTotSyst_int_om");
        }
        else{
          spectrum_om_stat[n3] = (TH1D*) fin->Get(Form("fSpectrumStat_om[%d]",n3-1));
          spectrum_om_syst[n3] = (TH1D*) fin->Get(Form("fSpectrumTotSyst_om[%d]",n3-1));
        }
        spectrum_om_stat[n3]->SetName(Form("spectrum_om_stat[%d]",n3));
        spectrum_om_stat[n3]->Scale(scalefactor_om[n3]);
        spectrum_om_syst[n3]->SetName(Form("spectrum_om_syst[%d]",n3));
        spectrum_om_syst[n3]->Scale(scalefactor_om[n3]);
      }
    
    
    //fit spectra and extract yields and means
      
      double yield_om[multbins_om+1][numfunctypes];
      double estat_yield_om[multbins_om+1][numfunctypes];
      double esyst_yield_om[multbins_om+1][numfunctypes];
      double mean_om[multbins_om+1][numfunctypes];
      double estat_mean_om[multbins_om+1][numfunctypes];
      double esyst_mean_om[multbins_om+1][numfunctypes];
      
      TF1 *func_om[multbins_om+1][numfunctypes];
      
      TCanvas *can_om = new TCanvas("can_om","can_om",900,900); 
      TH1D *frame_spectra_om = new TH1D("frame_spectra_om","",1,0,6);
      PrepareCanvasAndFrame(can_om,frame_spectra_om,kTRUE);
      
      for(int n3=0; n3<multbins_om+1; n3++){
        for(int n1=0; n1<numfunctypes-2; n1++){
          if(n1==kPTexpo) continue;
//           if(n1!=kBylinkin && n1!=kLevyTsallis) continue;
          func_om[n3][n1] = ChooseFunction(n3,n1,kTRUE,rangestobefit_om[n3][n1][1]);
          func_om[n3][n1]->SetLineColor(n1+1); if(n1==(numfunctypes-1)) func_om[n3][n1]->SetLineColor(1);
          h_out = YieldMean(spectrum_om_stat[n3],spectrum_om_syst[n3],func_om[n3][n1],0,10,rangestobefit_om[n3][n1][0],rangestobefit_om[n3][n1][1],0.01,0.5,"0qI");
          //if(n1==kBylinkin) printf("Mult%d	%s	chi2/ndf = %f	\n",n3,c_shape[n1],func_om[n3][n1]->GetChisquare()/func_om[n3][n1]->GetNDF());
	  //if(n1==kBylinkin) printf("%f   %f    %f    %f     %f     %f\n",func_om[n3][n1]->GetParameter(0),func_om[n3][n1]->GetParameter(1),func_om[n3][n1]->GetParameter(2),func_om[n3][n1]->GetParameter(3),func_om[n3][n1]->GetParameter(4),func_om[n3][n1]->GetParameter(5));
	  yield_om[n3][n1] = h_out->GetBinContent(kYield);
          estat_yield_om[n3][n1] = h_out->GetBinContent(kYieldStat);
          esyst_yield_om[n3][n1] = TMath::Max(h_out->GetBinContent(kYieldSysHi),h_out->GetBinContent(kYieldSysLo));
          mean_om[n3][n1] = h_out->GetBinContent(kMean);
          estat_mean_om[n3][n1] = h_out->GetBinContent(kMeanStat);
          esyst_mean_om[n3][n1] = TMath::Max(h_out->GetBinContent(kMeanSysHi),h_out->GetBinContent(kMeanSysLo));
          h_out->Reset();
          can_om->cd();
          spectrum_om_syst[n3]->Draw("same");
          func_om[n3][n1]->Draw("same");
          can_om->Update();
        }
      }
    
    
    //calculate extrapfrac, systematics and R factors
      
      double syst_yield_om[multbins_om+1];
      double syst_mean_om[multbins_om+1];
      double R_yield_om[multbins_om+1][numfunctypes]; //R factor (uncorrelated part)
      double R_mean_om[multbins_om+1][numfunctypes];
      double Rmax_yield_om[multbins_om+1]; //maommum among R factors from different functions. One for each multiplicity bin
      double Rmax_mean_om[multbins_om+1];
      double extrap_om[multbins_om+1][numfunctypes];
      double extrapfrac_om[multbins_om+1][numfunctypes];
      
      for(int n3=0; n3<multbins_om+1; n3++){
        syst_yield_om[n3]= 0;
        syst_mean_om[n3] = 0;
	Rmax_yield_om[n3]= 0;
	Rmax_mean_om[n3]= 0;
        for(int n1=0; n1<numfunctypes-2; n1++){
          R_yield_om[n3][n1]= 0;
          R_mean_om[n3][n1] = 0;
          extrapfrac_om[n3][n1] = 0;
          //if(n3==0) R_yield_om_perfuntion[n1]=0;
          if(n1==kPTexpo) continue;
//           if(n1!=kBylinkin && n1!=kLevyTsallis) continue;
          extrap_om[n3][n1] = func_om[n3][n1]->Integral(0,0.9);
          extrapfrac_om[n3][n1] = extrap_om[n3][n1]/yield_om[n3][n1]*100;
	  if(n1==reference) printf("mult %d  -  Extrap frac = %.1f\n",n3,extrapfrac_om[n3][n1]);
          if(n1==reference) continue;
          syst_yield_om[n3] = TMath::Max(syst_yield_om[n3],TMath::Abs(yield_om[n3][n1]-yield_om[n3][reference])/yield_om[n3][reference]);
          syst_mean_om[n3] = TMath::Max(syst_mean_om[n3],TMath::Abs(mean_om[n3][n1]-mean_om[n3][reference])/mean_om[n3][reference]);
          if(n3>0){
            R_yield_om[n3][n1] = TMath::Abs((yield_om[n3][n1]/yield_om[n3][reference]) / (yield_om[0][n1]/yield_om[0][reference])-1);
            R_mean_om[n3][n1] = TMath::Abs((mean_om[n3][n1]/mean_om[n3][reference]) / (mean_om[0][n1]/mean_om[0][reference])-1);
	    if(R_yield_om[n3][n1]>Rmax_yield_om[n3]) Rmax_yield_om[n3] = R_yield_om[n3][n1];
	    if(R_mean_om[n3][n1]>Rmax_mean_om[n3]) Rmax_mean_om[n3] = R_mean_om[n3][n1];
          }
        } 
      }
    
    
    //histos 
      
      TH1D *h_syst_yield_om = new TH1D("h_syst_yield_om","",multbins_om+1,0,multbins_om+1);
      TH1D *h_systfrac_yield_om = new TH1D("h_systfrac_yield_om","",multbins_om+1,0,multbins_om+1);
      TH1D *h_systWITHconstsystfrac_yield_om = new TH1D("h_systWITHconstsystfrac_yield_om","",multbins_om+1,0,multbins_om+1);
      TH1D *h_systuncWITHconstsystfrac_yield_om = new TH1D("h_systuncWITHconstsystfrac_yield_om","",multbins_om+1,0,multbins_om+1);
      TH1D *h_systcorWITHconstsystfrac_yield_om = new TH1D("h_systcorWITHconstsystfrac_yield_om","",multbins_om+1,0,multbins_om+1);
      for(int n3=0; n3<multbins_om+1; n3++) {
        h_syst_yield_om->SetBinContent(n3+1,syst_yield_om[n3]*100);
        h_syst_yield_om->SetBinError(n3+1,1e-08);
        h_systfrac_yield_om->SetBinContent(n3+1,syst_yield_om[n3]*yield_om[n3][reference]/extrap_om[n3][reference]*100);
        h_systfrac_yield_om->SetBinError(n3+1,1e-08);
	//printf("%f\n",h_systfrac_yield_om->GetBinContent(n3+1));
        h_systWITHconstsystfrac_yield_om->SetBinContent(n3+1,extrap_om[n3][reference]*27.568574/yield_om[n3][reference]);
        h_systWITHconstsystfrac_yield_om->SetBinError(n3+1,1e-08);
      }
      for(int n3=0; n3<multbins_om+1; n3++) {
	double uncpart_om = TMath::Sqrt(h_systWITHconstsystfrac_yield_om->GetBinContent(n3+1)*h_systWITHconstsystfrac_yield_om->GetBinContent(n3+1)-h_syst_yield_om->GetBinContent(2)*h_syst_yield_om->GetBinContent(2));
	double corpart_om = TMath::Sqrt(h_systWITHconstsystfrac_yield_om->GetBinContent(n3+1)*h_systWITHconstsystfrac_yield_om->GetBinContent(n3+1)-uncpart_om*uncpart_om);
        h_systuncWITHconstsystfrac_yield_om->SetBinContent(n3+1,uncpart_om);
        h_systuncWITHconstsystfrac_yield_om->SetBinError(n3+1,1e-08);
        h_systcorWITHconstsystfrac_yield_om->SetBinContent(n3+1,corpart_om);
        h_systcorWITHconstsystfrac_yield_om->SetBinError(n3+1,1e-08);
      }    
    
    
    //canvasing
      
      TCanvas *cansys_om = new TCanvas("cansys_om","cansys_om",700*1.5,500*1.5);
      double maxleftscale = 1.4*h_syst_yield_om->GetMaximum();
      double maxrightscale = 1.1*h_systfrac_yield_om->GetMaximum();
      TH1D *frame_R_om = new TH1D("frame_R_om","frame_R_om",multbins_om+1,0,multbins_om+1);
      frame_R_om->GetYaxis()->SetRangeUser(0,maxleftscale);
      frame_R_om->SetTitle("Systematic on Yield due to Extrapolation: #Omega");
      frame_R_om->GetYaxis()->SetTitle("Systematic on Yield (%)");
      frame_R_om->GetXaxis()->SetTitle("mult. bin");
      frame_R_om->GetXaxis()->SetTitleSize(0.045);
      frame_R_om->GetXaxis()->SetLabelSize(0.045);
      for(int j = 0; j<multbins_om+1; j++) frame_R_om->GetXaxis()->SetBinLabel(j+1,c_multbins_om[j]);
      frame_R_om->Draw();
//       h_syst_yield_om->SetFillStyle(3001);
      h_syst_yield_om->SetFillStyle(0);
      h_syst_yield_om->SetLineColor(kBlack);
      h_syst_yield_om->SetLineWidth(2);
      h_syst_yield_om->SetFillColor(kGray+1);
      h_syst_yield_om->Draw("HISTsame");
      h_systWITHconstsystfrac_yield_om->SetFillStyle(0);
      h_systWITHconstsystfrac_yield_om->SetLineColor(kBlack);
      h_systWITHconstsystfrac_yield_om->SetLineStyle(3);
      h_systWITHconstsystfrac_yield_om->SetLineWidth(2);
      h_systWITHconstsystfrac_yield_om->Draw("HISTsame");
      h_systuncWITHconstsystfrac_yield_om->SetFillStyle(0);
      h_systuncWITHconstsystfrac_yield_om->SetLineColor(kBlue);
      h_systuncWITHconstsystfrac_yield_om->SetLineStyle(3);
      h_systuncWITHconstsystfrac_yield_om->SetLineWidth(2);
      h_systuncWITHconstsystfrac_yield_om->Draw("HISTsame");
      h_systcorWITHconstsystfrac_yield_om->SetFillStyle(0);
      h_systcorWITHconstsystfrac_yield_om->SetLineColor(kGreen);
      h_systcorWITHconstsystfrac_yield_om->SetLineStyle(3);
      h_systcorWITHconstsystfrac_yield_om->SetLineWidth(2);
      h_systcorWITHconstsystfrac_yield_om->Draw("HISTsame");
      h_systfrac_yield_om->Scale(maxleftscale/maxrightscale);
      h_systfrac_yield_om->SetFillStyle(0);
      h_systfrac_yield_om->SetLineStyle(1);
      h_systfrac_yield_om->SetFillColor(kRed);
      h_systfrac_yield_om->SetLineColor(kRed);
      h_systfrac_yield_om->SetLineWidth(2);
      h_systfrac_yield_om->Draw("HISTsame");
      // draw an axis on the right side
      TGaxis *axis = new TGaxis(6,0,6,maxleftscale,0,maxrightscale,510,"+L");
      axis->SetTitle("Systematic on Extrapolation (%)");
      axis->SetLabelFont(42);
      axis->SetLabelSize(frame_R_om->GetYaxis()->GetLabelSize());
      axis->SetTitleFont(42);
      axis->SetTitleSize(frame_R_om->GetYaxis()->GetTitleSize());
      axis->SetTitleColor(kRed);
      axis->SetLineColor(kRed);
      axis->SetTextColor(kRed);
      axis->SetLabelColor(kRed);
      axis->Draw();
      TLine *lineRat_om = new TLine(0,h_systfrac_yield_om->GetMaximum(),6,h_systfrac_yield_om->GetMaximum());
      lineRat_om->SetLineColor(kRed);
      lineRat_om->SetLineStyle(3);
      lineRat_om->SetLineWidth(2);
      lineRat_om->Draw();
     }
 
 
  // writing in file
    if(!skip_xi && !skip_om){
      TFile *fout = new TFile("SystLowPtExtr_cfr.root","recreate");
      fout->cd();
      h_systWITHconstsystfrac_yield_xi->Write("h_syst_yield_xi");
      h_systWITHconstsystfrac_yield_om->Write("h_syst_yield_om");
      h_systuncWITHconstsystfrac_yield_xi->Write("h_systunc_yield_xi");
      h_systuncWITHconstsystfrac_yield_om->Write("h_systunc_yield_om");
      h_systcorWITHconstsystfrac_yield_xi->Write("h_systcor_yield_xi");
      h_systcorWITHconstsystfrac_yield_om->Write("h_systcor_yield_om");
    }
  
}

void DefineRangesToBeFit(){
  
  for(int i=0; i<multbins_xi+1; i++){
    for(int j=0; j<numfunctypes; j++){
      rangestobefit_xi[i][j][0] = 0.6;
      rangestobefit_xi[i][j][1] = 6.5;
      if(j==kMTexpo){
	if(i==0) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==1) 			rangestobefit_xi[i][j][1] = 6.5;
	if(i==2) 			rangestobefit_xi[i][j][1] = 4;
	if(i==3) 			rangestobefit_xi[i][j][1] = 4;
	if(i==4) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==5) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==6) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==7) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==8) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==9) 			rangestobefit_xi[i][j][1] = 2.5;
	if(i==10) 			rangestobefit_xi[i][j][1] = 2.2;
// 	if(i==0) 			rangestobefit_xi[i][j][1] = 2.9;
// 	if(i==1) 			rangestobefit_xi[i][j][1] = 5;
// 	if(i==2) 			rangestobefit_xi[i][j][1] = 4;
// 	if(i==3) 			rangestobefit_xi[i][j][1] = 3.4;
// 	if(i==4) 			rangestobefit_xi[i][j][1] = 3.4;
// 	if(i==5) 			rangestobefit_xi[i][j][1] = 3.4;
// 	if(i==6) 			rangestobefit_xi[i][j][1] = 2.9;
// 	if(i==7) 			rangestobefit_xi[i][j][1] = 2.9;
// 	if(i==8) 			rangestobefit_xi[i][j][1] = 2.9;
// 	if(i==9) 			rangestobefit_xi[i][j][1] = 2.5;
// 	if(i==10) 			rangestobefit_xi[i][j][1] = 2.2;
      }
      if(j==kPTexpo){
	if(i==0) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==1) 			rangestobefit_xi[i][j][1] = 5;
	if(i==2) 			rangestobefit_xi[i][j][1] = 4;
	if(i==3) 			rangestobefit_xi[i][j][1] = 3.4;
	if(i==4||i==5) 			rangestobefit_xi[i][j][1] = 3.4;
	if(i==6||i==7) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==8) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==9) 			rangestobefit_xi[i][j][1] = 2.5;
	if(i==10) 			rangestobefit_xi[i][j][1] = 2.2;
      }
      if(j==kFermiDirac){
	if(i==0) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==1) 			rangestobefit_xi[i][j][1] = 5;
	if(i==2) 			rangestobefit_xi[i][j][1] = 4;
	if(i==3) 			rangestobefit_xi[i][j][1] = 3.4;
	if(i==4) 			rangestobefit_xi[i][j][1] = 3.4;
	if(i==5) 			rangestobefit_xi[i][j][1] = 3.4;
	if(i==6) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==7) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==8) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==9) 			rangestobefit_xi[i][j][1] = 2.5;
	if(i==10) 			rangestobefit_xi[i][j][1] = 2.2;
      }
      if(j==kBoseEinstein){
	if(i==0) 			rangestobefit_xi[i][j][1] = 3.4;
	if(i==1) 			rangestobefit_xi[i][j][1] = 6.5;
	if(i==2) 			rangestobefit_xi[i][j][1] = 5;
	if(i==3) 			rangestobefit_xi[i][j][1] = 4;
	if(i==4) 			rangestobefit_xi[i][j][1] = 4;
	if(i==5) 			rangestobefit_xi[i][j][1] = 4;
	if(i==6) 			rangestobefit_xi[i][j][1] = 3.4;
	if(i==7) 			rangestobefit_xi[i][j][1] = 3.4;
	if(i==8) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==9) 			rangestobefit_xi[i][j][1] = 2.5;
	if(i==10) 			rangestobefit_xi[i][j][1] = 2.2;
      }
      if(j==kBoltz){
	if(i==0) 			rangestobefit_xi[i][j][1] = 2.5;
	if(i==1) 			rangestobefit_xi[i][j][1] = 4;
	if(i==2) 			rangestobefit_xi[i][j][1] = 3.4;
	if(i==3) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==4) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==5) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==6) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==7) 			rangestobefit_xi[i][j][1] = 2.9;
	if(i==8) 			rangestobefit_xi[i][j][1] = 2.5;
	if(i==9) 			rangestobefit_xi[i][j][1] = 2.2;
	if(i==10) 			rangestobefit_xi[i][j][1] = 2.0;
      }
    }
  }
  
  for(int i=0; i<multbins_om+1; i++){
    for(int j=0; j<numfunctypes; j++){
      rangestobefit_om[i][j][0] = 0.9;
      rangestobefit_om[i][j][1] = 5.5;
      if(j==kBoltz){
// 	if(i==0||i==1) 		rangestobefit_om[i][j][1] = 3.0;
// 	if(i==2||i==3||i==4) 	rangestobefit_om[i][j][1] = 2.6;
// 	if(i==5) 		rangestobefit_om[i][j][1] = 2.6;
	if(i==0) 	rangestobefit_om[i][j][1] = 3.0;
	else if(i==1) 	rangestobefit_om[i][j][1] = 3.0;
	else if(i==2) 	rangestobefit_om[i][j][1] = 3.0;
	else if(i==3) 	rangestobefit_om[i][j][1] = 3.8;
	else if(i==4) 	rangestobefit_om[i][j][1] = 3.0;
	else if(i==5) 	rangestobefit_om[i][j][1] = 2.6;
      }
      if(j==kMTexpo){
	if(i==0) 	rangestobefit_om[i][j][1] = 3.8;
	else if(i==1) 	rangestobefit_om[i][j][1] = 5.5;
	else if(i==2) 	rangestobefit_om[i][j][1] = 5.5;
	else if(i==3) 	rangestobefit_om[i][j][1] = 3.8;
	else if(i==4) 	rangestobefit_om[i][j][1] = 3.0;
	else if(i==5) 	rangestobefit_om[i][j][1] = 2.6;
      }
      if(j==kPTexpo){
	if(i==0) 	rangestobefit_om[i][j][1] = 5.5;
	else if(i==1) 	rangestobefit_om[i][j][1] = 5.5;
	else if(i==2) 	rangestobefit_om[i][j][1] = 5.5;
	else if(i==3) 	rangestobefit_om[i][j][1] = 3.8;
	else if(i==4) 	rangestobefit_om[i][j][1] = 3.0;
	else if(i==5) 	rangestobefit_om[i][j][1] = 2.6;
      }
      if(j==kFermiDirac){
	if(i==0) 	rangestobefit_om[i][j][1] = 3.8;
	else if(i==1) 	rangestobefit_om[i][j][1] = 5.5;
	else if(i==2) 	rangestobefit_om[i][j][1] = 5.5;
	else if(i==3) 	rangestobefit_om[i][j][1] = 3.8;
	else if(i==4) 	rangestobefit_om[i][j][1] = 3.0;
	else if(i==5) 	rangestobefit_om[i][j][1] = 2.6;
      }
      if(j==kBoseEinstein){
	if(i==0) 	rangestobefit_om[i][j][1] = 3.8;
	else if(i==1) 	rangestobefit_om[i][j][1] = 5.5;
	else if(i==2) 	rangestobefit_om[i][j][1] = 5.5;
	else if(i==3) 	rangestobefit_om[i][j][1] = 3.8;
	else if(i==4) 	rangestobefit_om[i][j][1] = 3.0;
	else if(i==5) 	rangestobefit_om[i][j][1] = 2.6;
      }
    }
  }
    
}

void PrepareCanvasAndFrame(TCanvas *can, TH1D *frame, bool isomega){
  if(!isomega){  
    can->SetLogy();
    can->SetMargin(0.15,0.02,0.15,0.02);
    frame->SetName("frame_spectra_xi");
    frame->GetYaxis()->SetRangeUser(0.6e-7,70/*1e-1*/);
    frame->GetYaxis()->SetTitle("1/#it{N}_{ev} d^{2}#it{N}/(d#it{p}_{T}d#it{y})  (GeV/#it{c})^{-1}");
    frame->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
    frame->GetYaxis()->SetTitleSize(0.04);
    frame->GetXaxis()->SetTitleSize(0.04);
    frame->GetYaxis()->SetLabelSize(0.04);
    frame->GetXaxis()->SetLabelSize(0.04);
    frame->GetYaxis()->SetTitleOffset(1.5);
    frame->GetXaxis()->SetTitleOffset(1.3);
    can->cd();
    frame->Draw();
  }
  else{
    can->SetLogy();
    can->SetMargin(0.15,0.02,0.15,0.02);
    frame->SetName("frame_spectra_om");
    frame->GetYaxis()->SetRangeUser(1e-8,2e-1);
    frame->GetYaxis()->SetTitle("1/#it{N}_{ev} d^{2}#it{N}/(d#it{p}_{T}d#it{y})  (GeV/#it{c})^{-1}");
    frame->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
    frame->GetYaxis()->SetTitleSize(0.04);
    frame->GetXaxis()->SetTitleSize(0.04);
    frame->GetYaxis()->SetLabelSize(0.04);
    frame->GetXaxis()->SetLabelSize(0.04);
    frame->GetYaxis()->SetTitleOffset(1.5);
    frame->GetXaxis()->SetTitleOffset(1.3);
    can->cd();
    frame->Draw();
    
  }
}

TF1 *ChooseFunction(int n3, int n1, bool isom = kFALSE, double maxfunc = 10){

  double cascmass = 1.32171;
  if(isom) cascmass = 1.67245;
  char cascname[5];
  if(!isom) sprintf(cascname,"xi");
  else sprintf(cascname,"om");
    
    double blasstart_xi[multbins_xi+1][4]= {{0.6406 , 0.4254 , 5.7506 ,   10.0308},
					    {0.6406 , 0.4254 , 5.7506 , 2436.0308},
					    {0.6941 , 0.3847 , 6.4504 , 1523.4006},
					    {0.6948 , 0.3312 , 4.8429 , 1422.7860},
					    {0.7050 , 0.3399 , 6.5239 ,  503.2534},
					    {0.7341 , 0.3454 , 9.3197 ,  189.5922},
					    {0.7359 , 0.2949 , 6.5086 ,  206.1323},
					    {0.7355 , 0.2881 , 7.4523 ,   88.3888},
					    {0.7832 , 0.3236 , 18.3388 ,  15.1583},
					    {0.7706 , 0.2962 , 14.3628 ,  13.9437},
					    {0.7599 , 0.2250 , 11.8931 ,  11.6706} };

    double blasstart_om[multbins_om+1][4] = {{0.7767 , 0.2000 , 1.7796 ,   10.3769},
					     {0.7767 , 0.2000 , 1.7796 , 3632.3769},
					     {0.7595 , 0.2115 , 2.1847 ,  663.3541},
					     {0.7262 , 0.2000 , 1.9681 ,  337.9667},
					     {0.7235 , 0.2391 , 4.5031 ,   19.7332},
					     {0.7468 , 0.2396 , 8.7570 ,    2.8114} };

  TF1 *f;
  
  char namefunc[50];
  sprintf(namefunc,"func_%s[%d][%d]",cascname,n3,n1);
  
  if(n1==kLevyTsallis){
    f = LevyTsallis(namefunc, maxfunc);
  }
  else if(n1==kBlastWave){
    if(!isom) f = BGBlastWave(namefunc,cascmass,blasstart_xi[n3][0],blasstart_xi[n3][1],blasstart_xi[n3][2],blasstart_xi[n3][3],maxfunc,kFALSE);
    else  f = BGBlastWave(namefunc,cascmass,blasstart_om[n3][0],blasstart_om[n3][1],blasstart_om[n3][2],blasstart_om[n3][3],maxfunc,kFALSE);
  }
  else if(n1==kBoltz){
    f = Boltzmann(namefunc, cascmass, 0.1, 1.,maxfunc);
  }
  else if(n1==kMTexpo){
    f = GetMTExpdNdptTimesPt(cascmass, 0.1, 1.,namefunc,maxfunc);
  }
  else if(n1==kPTexpo){
    f = GetPTExpdNdptTimesPt(0.1, 1.,namefunc,maxfunc);
  }
  else if(n1==kFermiDirac){
    f = GetFermiDiracdNdptTimesPt(cascmass, 0.1, 1.,namefunc,maxfunc);
  }
  else if(n1==kBoseEinstein){
    f = GetBoseEinsteindNdptTimesPt(cascmass, 0.1, 1.,namefunc,maxfunc);
  }
  
  else if(n1==kBylinkin){
    f = Bylinkin(namefunc,cascmass,maxfunc);
  }
  
  else if(n1==kHagedorn){
    f = Hagedorn(namefunc,cascmass,maxfunc);
  }
  
  else if(n1==kBoltPWL){
    f = BoltPWL(namefunc, cascmass, 0.3, 1.,1,1,1,maxfunc);
  }
  
  return f;
  
}

/*****************************************************************/
/* BYLINKIN FUNCTION */
/*****************************************************************/

Double_t Bylinkin_Func(const double * x, const double* p) 
{
	 Double_t mass   = p[0];
 	 Double_t a1 = p[1];
 	 Double_t a2 = p[2];
 	 Double_t t1  = p[3];
 	 Double_t t2  = p[4];
 	 Double_t n   = p[5];

	Double_t pt=x[0];
	Double_t mt=TMath::Sqrt(pt*pt+mass*mass);
	
	Double_t f1=TMath::Exp(-1.0*(mt-mass)/t1);
	Double_t f2=1.0+(pt*pt)/(t2*t2*n);
	f2=TMath::Power(f2,-1.0*n);
	return pt*a1*(f1+a2*f2);
}

TF1 * Bylinkin(const Char_t *name, Double_t mass, double maxfunc=10)
{
	TF1 *fun = new TF1(name,Bylinkin_Func , 0, maxfunc, 6);
	fun->SetParNames("mass","Norm_{global}","Norm_{n}","T_{exp}","T_{n}","n");
	fun->FixParameter(0,mass);    
        if(mass<1.5){
	  fun->SetParameter(1,0.015739); fun->SetParLimits(1,0,100);
	  fun->SetParameter(2,1.180543); fun->SetParLimits(2,0,100);
	  fun->SetParameter(3,0.225147); fun->SetParLimits(3,0.1,1);
	  fun->SetParameter(4,1.156606); fun->SetParLimits(4,0,100);
	  fun->SetParameter(5,4.225767); fun->SetParLimits(5,0,20);
	}
	if(mass>1.5){
	  fun->SetParameter(1,0.015739); fun->SetParLimits(1,0,10);
	  fun->SetParameter(2,0.180543); fun->SetParLimits(2,0,10);
	  fun->SetParameter(3,0.225147); fun->SetParLimits(3,0.1,1);
	  fun->SetParameter(4,1.156606); fun->SetParLimits(4,0,2);
	  fun->SetParameter(5,20); fun->SetParLimits(5,12,1000);
	}
	return fun;

}

/*****************************************************************/
/* HAGEDORN FUNCTION */
/*****************************************************************/

Double_t Hagedorn_Func(Double_t *x, Double_t *par)
{
      Float_t pt =x[0];
      Double_t mt=TMath::Sqrt(pt*pt+par[5]*par[5]);
      Double_t f=-1.0*par[0]*mt-par[1]*mt*mt;
      f=TMath::Exp(f)+mt/par[2];
      f=TMath::Power(f,par[3]);
      f=pt*par[4]/f;
      return f;
}


TF1 * Hagedorn (const Char_t *name, Double_t mass, double maxfunc=10)
{

	TF1 *fun = new TF1(name, Hagedorn_Func, 0, maxfunc, 6);
	fun->SetParNames("a","b","m0","n","Scale","mass");
	if(mass<1.6){
	  fun->SetParameter(0,-5); fun->SetParLimits(0,-100,0);
	  fun->SetParameter(1,0.3); fun->SetParLimits(1,0.1,10);
	  fun->SetParameter(2,10); fun->SetParLimits(2,0,1000000);
	  fun->SetParameter(3,0.5); fun->SetParLimits(3,0,1);
	  fun->SetParameter(4,1); fun->SetParLimits(4,0,10000000);
	} else{
	  fun->SetParameter(0,-5); fun->SetParLimits(0,-100,0);
	  fun->SetParameter(1,0.3); fun->SetParLimits(1,0.05,1);
	  fun->SetParameter(2,10); fun->SetParLimits(2,0.01,10000);
	  fun->SetParameter(3,0.3); fun->SetParLimits(3,0,0.5);
	  fun->SetParameter(4,1); fun->SetParLimits(4,0,10000);
	}
	fun->FixParameter(5,mass);

	return fun;
  
}

/*****************************************************************/
/* BOSE-EINSTEIN FUNCTION */
/*****************************************************************/

TF1 * GetBoseEinsteindNdptTimesPt(Double_t mass, Double_t temp, Double_t norm, const char * name, double maxfunc=10){

  // Bose einstein distribution as a function of dNdpt
  char formula[500];
  snprintf(formula,500,"[0]*x*1./(exp(sqrt(x**2+%f**2)/[1])-1)", mass);
  TF1 *fLastFunc=new TF1(name,formula,0,maxfunc);
  fLastFunc->SetParameters(norm, temp);
  fLastFunc->SetParLimits(1, 0.01, 10);
  fLastFunc->SetParNames("norm", "T");
  return fLastFunc;

}

/*****************************************************************/
/* FERMI-DIRAC FUNCTION */
/*****************************************************************/

TF1 *GetFermiDiracdNdptTimesPt(Double_t mass, Double_t temp, Double_t norm, const char * name, double maxfunc=10){

  // Bose einstein distribution as a function of dNdpt
  char formula[500];
  snprintf(formula,500,"[0]*x*1./(exp(sqrt(x**2+%f**2)/[1])+1)", mass);
  TF1 *fLastFunc=new TF1(name,formula,0,maxfunc);
  fLastFunc->SetParameters(norm, temp);
  //fLastFunc->SetParLimits(1, 0.01, 10);
  fLastFunc->SetParNames("norm", "T");
  return fLastFunc;

}

/*****************************************************************/
/* MT-EXPONENTIAL FUNCTION */
/*****************************************************************/

TF1 * GetMTExpdNdptTimesPt(Double_t mass, Double_t temp, Double_t norm, const char * name, double maxfunc=10){

  // Simple exponential in 1/mt*MT, as a function of dNdpt
  char formula[500];
  snprintf(formula,500,"[0]*x*exp(-sqrt(x**2+%f**2)/[1])", mass);
  TF1 *fLastFunc = new TF1(name,formula,0,maxfunc);
  //fLastFunc->SetNpx(20000);
  fLastFunc->SetParameters(norm, temp);
  fLastFunc->SetParLimits(1, 0.01, 1);
  fLastFunc->SetParNames("norm", "T");
  return fLastFunc;

}

/*****************************************************************/
/* PT-EXPONENTIAL FUNCTION */
/*****************************************************************/

TF1 * GetPTExpdNdptTimesPt(Double_t temp, Double_t norm, const char * name, double maxfunc=10){

  // Simple exponential in 1/pt*dNdpT, as a function of dNdpt
  char formula[500];
  snprintf(formula,500,"[0]*x*exp(-x/[1])");
  TF1* fLastFunc=new TF1(name,formula,0,maxfunc);
  fLastFunc->SetParameters(norm, temp);
  fLastFunc->SetParLimits(1, 0.01, 10);
  fLastFunc->SetParNames("norm", "T");
  return fLastFunc;

}

/*****************************************************************/
/* BOLTZMANN+POWLAW FUNCTION */
/*****************************************************************/

Double_t BoltzmannPowerLaw_Func(const Double_t *x, const Double_t *p)
{
  /* dN/dpt */
 
  Double_t pt = x[0];
  Double_t mass = p[0];
  Double_t mt = TMath::Sqrt(pt * pt + mass * mass);
  Double_t T = p[1];
  Double_t norm = p[2];
 
  return pt * (norm * mt * TMath::Exp(-mt / T)) + p[3]/TMath::Power(1+(pt*pt/(p[4]*p[4]*p[5])),p[5]);
  
}
 
TF1 *BoltPWL(const Char_t *name, Double_t mass, Double_t T = 0.3, Double_t norm = 1., double pl1 = 1, double pl2 = 1, double pl3 = 1, double maxfunc=10)
{
  if (mass == 1.32171)  TF1 *fBoltzmannPWL = new TF1(name, BoltzmannPowerLaw_Func, 0.0, maxfunc, 6);
  if (mass == 1.67245)  TF1 *fBoltzmannPWL = new TF1(name, BoltzmannPowerLaw_Func, 0.0, maxfunc, 6);
  fBoltzmannPWL->SetParameters(mass, T, norm,pl1,pl2,pl3);
  fBoltzmannPWL->SetParNames("mass", "T", "norm");
  fBoltzmannPWL->FixParameter(0, mass);
  fBoltzmannPWL->SetParLimits(1, 0.2, 0.5);
  fBoltzmannPWL->SetParLimits(2, 0., 1000);
  fBoltzmannPWL->SetParLimits(3, 0., 100);
//   fBoltzmannPWL->SetParLimits(4, 0., 10);
  fBoltzmannPWL->SetParLimits(5, 0., 10);
  return fBoltzmannPWL;
}


/*****************************************************************/
/* BOLTZMANN FUNCTION */
/*****************************************************************/

Double_t Boltzmann_Func(const Double_t *x, const Double_t *p)
{
  /* dN/dpt */
 
  Double_t pt = x[0];
  Double_t mass = p[0];
  Double_t mt = TMath::Sqrt(pt * pt + mass * mass);
  Double_t T = p[1];
  Double_t norm = p[2];
 
  return pt * norm * mt * TMath::Exp(-mt / T);
  
}
 
TF1 *Boltzmann(const Char_t *name, Double_t mass, Double_t T = 0.1, Double_t norm = 1., double maxfunc=10)
{
  if (mass == 1.32171)  TF1 *fBoltzmann = new TF1(name, Boltzmann_Func, 0.0, maxfunc, 3);
  if (mass == 1.67245)  TF1 *fBoltzmann = new TF1(name, Boltzmann_Func, 0.0, maxfunc, 3);
  fBoltzmann->SetParameters(mass, T, norm);
  fBoltzmann->SetParNames("mass", "T", "norm");
  fBoltzmann->FixParameter(0, mass);
//   fBoltzmann->SetParLimits(1, 0.01, 1e3);
//   fBoltzmann->SetParLimits(2, 1.e-3, 1);
  return fBoltzmann;
}

/*****************************************************************/
/* LEVY-TSALLIS FUNCTION */
/*****************************************************************/

double MyLevyTsallisPt(const Double_t *pt, const Double_t *par){
  //Levy Fit Function
  if(isxiforLevy)      lMass  = 1.32171; //Xi Mass
  else if(isomforLevy) lMass  = 1.67245; //Omega Mass
  Double_t ldNdy  = par[0];
  Double_t lTemp = par[1];
  Double_t lPower = par[2];

  Double_t lBigCoef = ((lPower-1)*(lPower-2)) / (lPower*lTemp*(lPower*lTemp+lMass*(lPower-2)));
  Double_t lInPower = 1 + (TMath::Sqrt(pt[0]*pt[0]+lMass*lMass)-lMass) / (lPower*lTemp);

  return ldNdy * pt[0] * lBigCoef * TMath::Power(lInPower,(-1)*lPower);
  //return ldNdy * lBigCoef * TMath::Power(lInPower,(-1)*lPower);
}

TF1 *LevyTsallis(const Char_t *name, double maxfunc=10){
  
  TF1* fLevy = new TF1(name,MyLevyTsallisPt,0,maxfunc,3);
  fLevy->SetParameters(0.15,0.2,7);
  //f->SetParLimits(0,0,2);
  fLevy->SetParLimits(1,0.05,0.8);
  fLevy->SetParLimits(2,2,100);

  return fLevy;
}

/*****************************************************************/
/* BOLTZMANN-GIBBS BLAST-WAVE */
/*****************************************************************/
 
static TF1 *fBGBlastWave_Integrand = NULL;

Double_t
BGBlastWave_Integrand(const Double_t *x, const Double_t *p)
{
 
  /*
     x[0] -> r (radius)
     p[0] -> mT (transverse mass)
     p[1] -> pT (transverse momentum)
     p[2] -> beta_max (surface velocity)
     p[3] -> T (freezout temperature)
     p[4] -> n (velocity profile)
  */
 
  Double_t r = x[0];
  Double_t mt = p[0];
  Double_t pt = p[1];
  Double_t beta_max = p[2];
  Double_t temp_1 = 1. / p[3];
  Double_t n = p[4];
 
  Double_t beta = beta_max * TMath::Power(r, n);
  if (beta > 0.9999999999999999) beta = 0.9999999999999999;
  Double_t rho = TMath::ATanH(beta);
  Double_t argI0 = pt * TMath::SinH(rho) * temp_1;
  if (argI0 > 700.) argI0 = 700.;
  Double_t argK1 = mt * TMath::CosH(rho) * temp_1;
  //  if (argI0 > 100 || argI0 < -100)
  //    printf("r=%f, pt=%f, beta_max=%f, temp=%f, n=%f, mt=%f, beta=%f, rho=%f, argI0=%f, argK1=%f\n", r, pt, beta_max, 1. / temp_1, n, mt, beta, rho, argI0, argK1);
  return r * mt * TMath::BesselI0(argI0) * TMath::BesselK1(argK1);
 
}
 
Double_t
BGBlastWave_Func(const Double_t *x, const Double_t *p)
{
  /* dN/dpt */
 
  Double_t pt = x[0];
  Double_t mass = p[0];
  Double_t mt = TMath::Sqrt(pt * pt + mass * mass);
  Double_t beta_max = p[1];
  Double_t temp = p[2];
  Double_t n = p[3];
  Double_t norm = p[4];
 
  if (!fBGBlastWave_Integrand)
  fBGBlastWave_Integrand = new TF1("fBGBlastWave_Integrand", BGBlastWave_Integrand, 0., 1., 5);
  fBGBlastWave_Integrand->SetParameters(mt, pt, beta_max, temp, n);
  Double_t integral = fBGBlastWave_Integrand->Integral(0., 1., (Double_t *)0, 1.e-6);
  return norm * pt * integral;
}

TF1 *
BGBlastWave(const Char_t *name, Double_t mass, Double_t beta_max = 0.9, Double_t temp = 0.1, Double_t n = 1., Double_t norm = 1.e8, double maxfunc=10, bool isint = kFALSE)
{
 
  TF1 *fBGBlastWave = new TF1(name, BGBlastWave_Func, 0., maxfunc, 5);
  fBGBlastWave->SetParameters(mass, beta_max, temp, n, norm);
  fBGBlastWave->SetParNames("mass", "beta_max", "T", "n", "norm");
  fBGBlastWave->FixParameter(0, mass);  
  
  fBGBlastWave->SetParLimits(1, 0.62, 0.85);
  fBGBlastWave->SetParLimits(2, 0.2, 0.5);
  fBGBlastWave->SetParLimits(3, 1, 20);
  fBGBlastWave->SetParLimits(4, 0, 16000);
 
  return fBGBlastWave;
}

