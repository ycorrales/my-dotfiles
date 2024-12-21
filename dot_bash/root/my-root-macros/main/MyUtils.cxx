//--Root--
#include <TApplication.h>
#include <TCanvas.h>
#include <TClonesArray.h>
#include <TColor.h>
#include <TError.h>
#include <TFile.h>
#include <TFileMerger.h>
#include <TGridResult.h>
#include <TH1.h>
#include <TLegend.h>
#include <TMath.h>
#include <TObjArray.h>
#include <TObjString.h>
#include <TPaveStats.h>
#include <TROOT.h>
#include <TString.h>
#include <TStyle.h>
#include <TSystem.h>
#include <TVirtualPad.h>
#include <TKey.h>
#include <TClass.h>

#include <stdlib.h>
#include <string.h>

//--MyClasses--
#include "MyUtils.h"

#include "sPhenixStyle.h"
#include "sPhenixStyle.C"


//
//
//__________________________________________________________________________________
ClassImp(MyUtils);

//
//
//__________________________________________________________________________________
namespace Utils
{
  MyUtils* GetMyUtils()
  {
    static MyUtils utils;
    return &utils;
  }
}

//
//
//__________________________________________________________________________________
MyUtils* gMyUtils = Utils::GetMyUtils();

//
//
//__________________________________________________________________________________
MyUtils::MyUtils() : TNamed("MyUtils", "My utility class"),
fUseMyStyle(true),
fShowOptStat(true),
fLoad_myBJetsLib(false),
fLoad_myITSsaLib(false),
fLoad_myRun2Lib(false),
fLogLevel(kInfo),
cpp_opt("")
{
//  fMacroToCompileName = new TClonesArray("TObjString");

  Rootlogon();

//  if (fLoad_myBJetsLib) LoadBjetLib();
//  if (fLoad_myITSsaLib) LoadITSsaLib();
//  if (fLoad_myRun2Lib)  LoadRun2Lib();
//
//  for (int i = 0; i < fMacroToCompileName->GetEntries(); ++i) {
//    TObjString* objStr = (TObjString*)fMacroToCompileName->At(i);
//    TString& str = objStr->String();
//    str += cpp_opt;
//    if (! str.IsNull()) CompileMacro(str.Data());
//  }
//  gErrorIgnoreLevel = fLogLevel;
//  fMacroToCompileName->Clear();
}

//
//
//__________________________________________________________________________________
void MyUtils::Rootlogon()
{
  PrintMsg("This is rootlogon - Y. Corrales Morales");
  PrintMsg("Starting ROOT version %s.", gROOT->GetVersion());

  int    nArg = gApplication->Argc();
  char** cArg = gApplication->Argv();

//  ParseOption(nArg, cArg);

//  gApplication->GetOptions(&nArg, cArg);

  if (fUseMyStyle) SetToMyStyle();

  return;
}

//
//
//__________________________________________________________________________________
void MyUtils::ParseOption(int& nArg, char**& cArg)
{
  static char null[1] = {""};
  if (! nArg) return;

  Int_t i, j;
  TString aux;
  for (i = 0; i < nArg; ++i) {
    // Printf("%s", cArg[i]);
    if (! strncmp(cArg[i], "-h", 2)) {
      cArg[i] = null;
      Print();
    } else if (! strncmp(cArg[i], "-nstyle", 7)) {
      cArg[i] = null;
      fUseMyStyle = false;
    } else if(!strncmp(cArg[i], "-nstat", 6)){
      cArg[i] = null;
      fShowOptStat = false;
    } else if (! strncmp(cArg[i], "-itssa", 6)) {
      cArg[i] = null;
      fLoad_myITSsaLib = true;
    } else if (! strncmp(cArg[i], "-bjet", 5)) {
      cArg[i] = null;
      fLoad_myBJetsLib = true;
    } else if (! strncmp(cArg[i], "-run2", 5)) {
      cArg[i]=null;
      fLoad_myRun2Lib = true;
    } else if (! strncmp(cArg[i], "-c", 2)) {
      cArg[i] = null;
      ++i;
      TClonesArray& arr = *fMacroToCompileName;
      if (i < nArg) {
        int c = 0;
        bool last_arg = false;
        while (i < nArg && !last_arg) {
          aux = cArg[i];
          if (! aux.CompareTo('+') || ! aux.CompareTo("++")) {
            last_arg = true;
            cpp_opt=aux.Data();
            cArg[i] = null;
            ++i;
            continue;
          }
          new(arr[c]) TObjString(aux);
          ++c;
          cArg[i] = null;
          ++i;
        }
      } else {
        ErrorMsg(__FUNCTION__, "-c option must be followed by the macro name");
      }
    }
  }
  //remove handle arguments from argument array
  j = 0;
  for(i = 0; i < nArg; i++) {
    if(strcmp(cArg[i], null)) {
      cArg[j] = cArg[i];
      ++j;
    }
  }
  nArg = j;
  return;
}

//
//
//__________________________________________________________________________________
void MyUtils::SetToMyStyle(){
  const int font = 42;
  // default canvas options
  //  gStyle->SetCanvasDefW(750);
  //  gStyle->SetCanvasDefH(750);
  //  gStyle->SetPadBottomMargin(0.08); //margins...
  //  gStyle->SetPadTopMargin(0.08);
  //  gStyle->SetPadLeftMargin(0.06);
  //  gStyle->SetPadRightMargin(0.08);
//  gStyle->SetPadGridX(0); // grids, tickmarks
//  gStyle->SetPadGridY(0);
//  gStyle->SetPadTickX(1);
//  gStyle->SetPadTickY(1);
//  gStyle->SetPaperSize(20, 24); // US letter size
//
//  // Set plotting style
//  gStyle->SetName("Yasser's Root Styles");
//  if(!fShowOptStat)gStyle->SetOptStat(0);
//  gStyle->SetOptDate(0);
////  gStyle->SetPalette(1, 0); // avoid horrible default color schem
//  gStyle->SetStatColor(0);
//  gStyle->SetLabelSize(0.035, "xyz");  // size of axis value font
//  gStyle->SetLabelFont(font, "xyz");
//  gStyle->SetTitleSize(0.035, "xyz");
//  gStyle->SetTitleFont(font, "xyz");
//  gStyle->SetTitleOffset(1.2, "xy");
//  gStyle->SetTitleBorderSize(0);
//  gStyle->SetTitleFillColor(0);
//  gStyle->SetTextFont(font);
//
//  // improved palette
//  const Int_t NRGBs = 5;
//  const Int_t NCont = 255;
//
//  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
//  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
//  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
//  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };

//  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);

//  gStyle->SetNumberContours(NCont);

  SetsPhenixStyle();
}

//
//
//__________________________________________________________________________________
void MyUtils::LoadBjetLib(){

  std::string kBaseBjetDir(gSystem->ExpandPathName("$HOME/Alice/PWGHF_HFCJ/Bjets/macros/"));
  gSystem->AddIncludePath(Form("-I%s ",  kBaseBjetDir.data()));
  gROOT->ProcessLine(Form(".include %s", kBaseBjetDir.data()));
  CompileMacro(Form("%s/BjetUtils.cxx+", kBaseBjetDir.data()));
  return;
}

//
//
//__________________________________________________________________________________
void MyUtils::LoadITSsaLib(){

  std::string kBaseITSsaDir(gSystem->ExpandPathName("$HOME/Alice/PWGLF_SPECTRA/macros/pikp_ITSsaAn/"));
  gSystem->AddIncludePath(Form("-I%s ",   kBaseITSsaDir.data()));
  gROOT->ProcessLine(Form(".include %s",  kBaseITSsaDir.data()));
  CompileMacro(Form("%s/ITSsaUtils.cxx+", kBaseITSsaDir.data()));
  CompileMacro(Form("%s/FitDCAdistAllSpecies.C+", kBaseITSsaDir.data()));
  return;
}

//
//
//__________________________________________________________________________________
void MyUtils::LoadRun2Lib(){

  std::string kBaseDir(gSystem->ExpandPathName("$HOME/Alice/PWGLF_SPECTRA/SpectraAnalysisRun2/pp-PbPb_5-02TeV_kINT7-Mult/git-reps"));
  gSystem->AddIncludePath(Form("-I/utilities/%s ",   kBaseDir.data()));
  gROOT->ProcessLine(Form(".include %s/utilities",  kBaseDir.data()));
  std::string lib_name[4] = { "histoutils.cxx", "SpectraCommonParams.cxx", "SpectraCommon.cxx", "AnalysisCommon.cxx" };
  std::string ana_name[5] = { "writeHMPID.C", "writeITSsa.C", "writeKinks.C", "writeTOF.C", "writeTPConly.C"         };
  std::string add_name[1] = { "combinedev.C"                                                                         };

  unsigned int i = 0;
  for(i = 0; i < 4; ++i){
    CompileMacro(Form("%s/utilities/%s+g", kBaseDir.data(), lib_name[i].data()));
  }
  for(i = 0; i < 5; ++i){
    CompileMacro(Form("%s/utilities/AnalysisWriters/%s+g", kBaseDir.data(), ana_name[i].data()));
  }
  for(i = 0; i < 1; ++i){
    CompileMacro(Form("%s/utilities/%s+g", kBaseDir.data(), add_name[i].data()));
  }

  return;
}

//
//
//__________________________________________________________________________________
void MyUtils::CompileMacro(const char* name){

  InfoMsg("MyUtils::CompileMacro", "Compiling... %s", name);
  gROOT->LoadMacro(name);
}

//
//
//__________________________________________________________________________________
TPaveStats* MyUtils::GetStatBox(TH1* hist){

  if(!hist){
    ErrorMsg(__FUNCTION__, "No hist found");
    return NULL;
  }
  TList* lof = (TList*)hist->GetListOfFunctions();
  TPaveStats* statbox = (TPaveStats*)lof->FindObject("stats");
  if(!statbox){
    ErrorMsg(__FUNCTION__,
        "getstatbox failed, remember that a histogram only gets a stat box \
        once it is drawn.");
    return NULL;
  }

  return statbox;
}

//
//
//__________________________________________________________________________________
void MyUtils::ColourizeStatBox(TH1* hist){

  if(!hist){
    ErrorMsg(__FUNCTION__, "No hist found");
    return;
  }
  TPaveStats* statbox = GetStatBox(hist);
  if(!statbox) {
    ErrorMsg(__FUNCTION__,
        "getstatbox failed, remember that a histogram only gets a stat box \
        once it is drawn.");
    return;
  }
  Int_t colour = hist->GetMarkerColor();
  statbox->SetTextColor(colour);

  return;
}

//
//
//__________________________________________________________________________________
void MyUtils::GridConnect(){
  //Printf(TxtColor("Setting strict fast timeouts\n", color_txt::c_green));

  gEnv->SetValue("XNet.ConnectTimeout", 20);
  gEnv->SetValue("XNet.RequestTimeout", 40);
  gEnv->SetValue("XNet.MaxRedirectCount",  2);
  gEnv->SetValue("XNet.ReconnectWait",  2);
  gEnv->SetValue("XNet.FirstConnectMaxCnt",  3);
  gEnv->SetValue("XNet.TransactionTimeout", 300);

  gSystem->Load("libNetx.so") ;
  gSystem->Load("libRAliEn.so");

  TGrid::Connect("alien:", 0, 0, "t");
}

//
//
//__________________________________________________________________________________
TClonesArray* MyUtils::GetFileListToMerge(bool bIsLocal, int offset,
    const char* fl, TString& strPattern){

  int iFiles = 0;
  int iMerge = 0;
  //
  if(gSystem->AccessPathName(fl)) {
    ErrorMsg(__FUNCTION__, Form("File %s not found...", fl));
    return NULL;
  }
  //
  FILE* lFiles = fopen(fl, "r");
  char fName[200];
  //
  TClonesArray* strArray = new TClonesArray("TObjString", 100);
  strArray->SetOwner();

  while(!feof(lFiles)) {
    int res = fscanf(lFiles, "%s\n", fName);

    TString sFileName = fName;
    if(sFileName[0] == '#') continue;
    if(!strPattern.IsNull() && !sFileName.Contains(strPattern)) continue;

    iFiles++;
    if(iFiles < offset) continue;
    if(!bIsLocal) sFileName.Prepend("alien://");

    new((* strArray)[iMerge++]) TObjString(sFileName);
  }

  PrintMsg( color_txt::c_yellow, "Files info: %d files found with pattern %s\n",
                       strArray->GetEntries(),
                       ( strPattern.IsNull() ? "NULL" : strPattern.Data() ) );

  fclose(lFiles);
  return strArray;
}

//
//
//__________________________________________________________________________________
TClonesArray* MyUtils::GetFileListToMerge(TGridResult* gr){

  TClonesArray* strArray = new TClonesArray("TObjString", 100);
  strArray->SetOwner();

  Int_t numFiles = gr->GetEntries();

  for(Int_t iFl = 0; iFl < numFiles; ++iFl) {

    TString sFileName = Form("%s", gr->GetKey(iFl, "turl"));
    new((* strArray)[iFl]) TObjString(sFileName);
  }

  PrintMsg( color_txt::c_yellow, "Files info: %d files found", gr->GetEntries() );
  return strArray;
}

//
//
//__________________________________________________________________________________
void MyUtils::Merge(TClonesArray* flList, int _start, int _pack){

  int nFls  = flList->GetEntries();
  int flPack = (_pack < 0) ? nFls : _pack;

  int iMerge = 0;
  int iPacks = _start / flPack + 1;

  TFileMerger* mg = new TFileMerger();
  TString floutName("");
  TString str;
  for(int iFl = 0; iFl < nFls; ++iFl) {
    if(iMerge % flPack == 0) {
      if(iMerge) {
        InfoMsg(__FUNCTION__, "Merging up to: %s\n", str.Data() );
        mg->Merge();
        mg->Reset();
      }
      floutName = (_pack < 0) ? "AnalysisResults.root" : Form("OutputMerged_tmp-%03d.root", iPacks++);
      mg->OutputFile(floutName.Data());
    }
    str = ((TObjString*)flList->At(iFl))->GetString();

    PrintMsg( color_txt::c_yellow, "%d -> %s ", iFl + 1, str.Data() );
    mg->AddFile(str.Data());
    iMerge++;
  }
  if(mg->GetMergeList()->GetEntries()) {

    InfoMsg(__FUNCTION__,
        "Merging last %d files", mg->GetMergeList()->GetEntries());
    InfoMsg(__FUNCTION__,
        "Merging up to: %s\n", str.Data());
    mg->Merge();
    mg->Reset();
  }

  flList->Clear("C");

  delete mg;
  return;
}

//
//
//__________________________________________________________________________________
void MyUtils::MergeFromFile(bool isLocal,const char* fl,const char* patt,
    int start, int pack){

  if(!isLocal) GridConnect();
  TString tmpStrPatt(patt);
  TClonesArray* flList = GetFileListToMerge(isLocal, start, fl, tmpStrPatt);
  if(!flList) return;

  Merge(flList, start, pack);
  delete flList;
}

//
//
//__________________________________________________________________________________
void MyUtils::MergeFromFind(const char* flPath,const char* flName,
    int start, int pack){

  GridConnect();
  TGridResult* gr = NULL;
  if(gGrid) {
    gr = gGrid->Query(flPath, flName);
  }
  if(!gr) return;

  TClonesArray* flList = GetFileListToMerge(gr);
  if(!flList)
    return;

  Merge(flList, start, pack);
  delete flList;
}
//
//
//__________________________________________________________________________________
void MyUtils::ShowFileKeys(const char* _flname){

  const TString flname(_flname);
  if (flname.IsNull()) {
    ErrorMsg(__FUNCTION__, "Empty file path ...");
    return;
  }
  TFile *fl = new TFile(flname);
  if (!fl || fl->IsZombie()){
    ErrorMsg(__FUNCTION__, Form("file %s not found", flname.Data()));
    return;
  }
  fl->ls();
  TIter next(fl->GetListOfKeys());
  TKey* key;
  while ((key = (TKey*)next())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if (!cl->InheritsFrom("TCollection")) continue;
    TCollection* coll = (TCollection*)key->ReadObj();
    coll->Print();
  }
  return;
}
//__________________________________________________________________________________
TH1* MyUtils::GetHistFromCanvas(TVirtualPad*& pad, int __pos){

  Requires(pad, std::string("Canvas not found " + std::string(pad->GetName())));
  TList* lstOfObj=pad->GetListOfPrimitives();
  Requires(lstOfObj, "List of files not found");
  //
  TIterator* iter=lstOfObj->MakeIterator();
  TObject* obj;
  while((obj=iter->Next())) {
    if(obj->InheritsFrom("TH1")) {
      __pos--;
      if(!__pos) return (TH1*)obj;
    }
  }
  return nullptr;
}

//
//
//__________________________________________________________________________________
void MyUtils::SetHistStyle(TH1* hist, int color,
    int mrk, float siz, int stl, int width){

  if(mrk > 0) hist->SetMarkerStyle(mrk);
  hist->SetMarkerColor(color);
  hist->SetLineColor(color);
  hist->SetMarkerSize(siz);
  hist->SetLineStyle(stl);
  hist->SetLineWidth(width);
  hist->GetXaxis()->SetTitleOffset(1.2);
  hist->GetYaxis()->SetTitleOffset(1.2);
}

//
//
//__________________________________________________________________________________
void MyUtils::ResetOutOfRange(TH1* hist, Double_t lw, Double_t up){

  for(Int_t ibin = 0; ibin <= hist->GetNbinsX(); ibin++) {
    Float_t bin_center = hist->GetBinCenter(ibin);
    if(bin_center < lw || bin_center > up)
      hist->SetBinContent(ibin, -1);
  }
  return;
}

//
//
//__________________________________________________________________________________
TCanvas* MyUtils::RatioPlot(TH1* num, TH1* den, TH1* rat, const char* ratYaxisTitle,
                            bool setratYrange, double minY, double maxY){

  if(!num || !den) {
    num=GetHistFromCanvas(gPad, 1);
    den=GetHistFromCanvas(gPad, 2);
    if(!num || !den) {
      ErrorMsg(__FUNCTION__, "Not hists in the global pad were found.");
      return nullptr;
    }
  }
  num->Sumw2(kTRUE);
  den->Sumw2(kTRUE);

  //num->SetBit(TH1::kNoTitle);
  num->SetName("num");
  SetHistStyle(num, kRed, 20, .8);

  den->SetBit(TH1::kNoTitle);
  den->SetName("den");
  SetHistStyle(den, kBlue, 22, .8);

  if(!rat){
    rat = dynamic_cast<TH1*>(num->Clone("ratio"));
    if(!rat->Divide(num, den, 1, 1, "B")) {
      WarnMsg(__FUNCTION__,"Try same number of bins");
    }
  }
  SetHistStyle(rat, kBlack);
  rat->SetBit(TH1::kNoTitle);
  TString strRatYaxisTitle(ratYaxisTitle);
  if(strRatYaxisTitle.IsNull()) strRatYaxisTitle="Ratio";
  rat->GetYaxis()->SetTitle(strRatYaxisTitle);
  rat->SetMinimum( setratYrange ? minY : 0.80); // Define Y ..
  rat->SetMaximum( setratYrange ? maxY : 1.35); // .. range
  rat->SetStats(0);      // No statistics on lower plot

  return ShowRatioPlot(num, den, rat);
}

//
//
//__________________________________________________________________________________
TCanvas* MyUtils::ShowRatioPlot(TH1* num, TH1* den, TH1* rat){
  TCanvas* cv = new TCanvas("RatioPlots","RatioPlots",800,800);

  // Upper plot will be in pad1
   TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
   pad1->SetBottomMargin(0);  // Upper and lower plot are joined
   //pad1->SetRightMargin(.01); // Right margin
   pad1->SetGridx();         // Vertical grid
   pad1->Draw();             // Draw the upper pad: pad1
   pad1->cd();               // pad1 becomes the current pad
   num->SetStats(0);          // No statistics on upper plot
   num->Draw();               // Draw h1
   if (den) den->Draw("same");         // Draw h2 on top of h1

  // Do not draw the Y axis label on the upper plot and redraw a small
   // axis instead, in order to avoid the first label (0) to be clipped.
   //num->GetYaxis()->SetLabelSize(0.);

  // lower plot will be in pad
   cv->cd();          // Go back to the main canvas before defining pad2
   TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
   pad2->SetTopMargin(0);
   //pad1->SetRightMargin(.01); // Right margin
   pad2->SetBottomMargin(0.2);
   pad2->SetGridx(); // vertical grid
   pad2->Draw();
   pad2->cd();       // pad2 becomes the current pad


   rat->Draw("ep");       // Draw the ratio plot

   // Y axis num plot settings
   num->GetYaxis()->SetTitleSize(20);
   num->GetYaxis()->SetTitleFont(43);
   num->GetYaxis()->SetTitleOffset(1.55);

   // Ratio plot (h3) settings
   rat->SetTitle(""); // Remove the ratio title

   // Y axis ratio plot settings
   rat->GetYaxis()->CenterTitle(true);
   rat->GetYaxis()->SetNdivisions(505);
   rat->GetYaxis()->SetTitleSize(20);
   rat->GetYaxis()->SetTitleFont(43);
   rat->GetYaxis()->SetTitleOffset(1.55);
   rat->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   rat->GetYaxis()->SetLabelSize(15);

   // X axis ratio plot settings
   rat->GetXaxis()->SetTitleSize(20);
   rat->GetXaxis()->SetTitleFont(43);
   rat->GetXaxis()->SetTitleOffset(4.);
   rat->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   rat->GetXaxis()->SetLabelSize(15);

  return cv;
}

//
//
//__________________________________________________________________________________
void MyUtils::RemoveOneOver2PiPt(TH1D*& hist){

	if (!hist)
		hist = (TH1D*)GetHistFromCanvas(gPad, 1);

  for(int ibin(1); ibin <= hist->GetNbinsX(); ++ibin){

    double pt = hist->GetBinCenter(ibin);
    double yield = 0;
    double e_yield = 0;

    yield   = hist->GetBinContent(ibin);
    e_yield = hist->GetBinError(ibin);

    yield   *= (2 * TMath::Pi() * pt);
    e_yield *= (2 * TMath::Pi() * pt);

    hist->SetBinContent(ibin, yield);
    hist->SetBinError(ibin, e_yield);
  }
}

//
//
//__________________________________________________________________________________
void MyUtils::AddOneOver2PiPt(TH1D*& hist){

	if (!hist)
		hist = (TH1D*)GetHistFromCanvas(gPad, 1);

  for(int ibin(1); ibin <= hist->GetNbinsX(); ++ibin){

    double pt = hist->GetBinCenter(ibin);
    double yield = 0;
    double e_yield = 0;

    yield   = hist->GetBinContent(ibin);
    e_yield = hist->GetBinError(ibin);

    yield   /= (2 * TMath::Pi() * pt);
    e_yield /= (2 * TMath::Pi() * pt);

    hist->SetBinContent(ibin, yield);
    hist->SetBinError(ibin, e_yield);
  }
}

void MyUtils::TestRatioPlot() {

   // Define two gaussian histograms. Note the X and Y title are defined
   // at booking time using the convention "Hist_title ; X_title ; Y_title"
   TH1F *h1 = new TH1F("h1", "Two gaussian plots and their ratio;x title; h1 and h2 gaussian histograms", 100, -5, 5);
   TH1F *h2 = new TH1F("h2", "h2", 100, -5, 5);
   h1->FillRandom("gaus");
   h2->FillRandom("gaus");

   // Define the Canvas
   TCanvas *c = gMyUtils->RatioPlot(h1,h2);
   TPad* pad1 = (TPad*)c->GetPrimitive("pad1");
   pad1->cd();
   h1->GetYaxis()->SetLabelSize(0.);
   TGaxis *axis = new TGaxis(-5,20,-5,220,20,220,510,"");
   axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   axis->SetLabelSize(15);
   axis->Draw();
 }
