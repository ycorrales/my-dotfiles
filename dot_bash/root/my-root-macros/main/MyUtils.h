//
//  MyUtils.h
//  ALICE
//
//  Created by Yasser Corrales Morales on 5/19/15.
//  Copyright (c) 2015 Yasser Corrales Morales. All rights reserved.
//

#ifndef __My_Utils__
#define __My_Utils__

#include <cstddef>
#include <iostream>

#ifndef ROOT_TEnv
#include <TEnv.h>
#endif

#ifndef ROOT_TNamed
#include <TNamed.h>
#endif

#ifndef ROOT_TGrid
#include <TGrid.h>
#endif

#ifndef ROOT_TClonesArray
#include <TClonesArray.h>
#endif

#ifndef ROOT_TSystem
#include <TSystem.h>
#endif

#ifndef ROOT_TGaxis
#include <TGaxis.h>
#endif

//--Root--
class TCanvas;
class TLegend;
class TH1;
class TH1D;
class TPaveStats;
class TGrid;
class TVirtualPad;

//--MyClasses--
#ifndef __BASE_UTILS__
#include "BaseUtils.h"
#endif

using namespace BaseUtils;

//
//MyUtils
//
class MyUtils : public TNamed{

 public:
  MyUtils();
  ~MyUtils() { /*if (fMacroToCompileName) delete fMacroToCompileName;*/ };

  bool GetIsMyBJetLiLoaded()    { return !fLoad_myBJetsLib; }
  bool GetIsMyITSsaLibLoaded()  { return !fLoad_myITSsaLib; }
  bool GetIsRun2LibLoaded()     { return !fLoad_myRun2Lib;  }

  void SetToMyStyle();
  void CompileMacro(const char* name);

  TPaveStats* GetStatBox(TH1* hist);
  void ColourizeStatBox(TH1* hist);

  void MergeFromFile(bool isLocal = kTRUE,
                     const char* fl    = "dataset.dat",
                     const char* patt  = "",
                     int start = 1, int pack = -1);
  void MergeFromFind(const char* flPath,
                     const char* flName = "AnalysisResults.root",
                     int start = 1, int pack = -1);
  void ShowFileKeys(const char* _flname);

  static TH1* GetHistFromCanvas(TVirtualPad*& pad, int __pos);
  static void SetHistStyle(TH1* hist, int color, int mrk = -1,
                    float siz = 1., int stl = 1, int width = 1);
  static void ResetOutOfRange(TH1* hist, Double_t lw, Double_t up);
  static TCanvas* RatioPlot(TH1* h1 = NULL, TH1* h2 = NULL, TH1* rat = NULL, const char* ratTitle="", Bool_t setratYrange = false, double minY = 0, double maxY = 0);
  static TCanvas* ShowRatioPlot(TH1* h1 = NULL, TH1* h2 = NULL, TH1* rat = NULL);
  static void AddOneOver2PiPt(TH1D*& hist);
  static void RemoveOneOver2PiPt(TH1D*& hist);
  static void TestRatioPlot();

 protected:
  void Rootlogon();
  void ParseOption(int& nArg, char**& cArg);
  void LoadBjetLib();
  void LoadITSsaLib();
  void LoadRun2Lib();
  void GridConnect();
  void Merge(TClonesArray* flList, int start, int pack);
  TClonesArray* GetFileListToMerge(bool bIsLocal, int start, const char* fl,  TString& patStr);
  TClonesArray* GetFileListToMerge(TGridResult* gr);

 private:
  bool fUseMyStyle;
  bool fShowOptStat;
  bool fLoad_myBJetsLib;
  bool fLoad_myITSsaLib;
  bool fLoad_myRun2Lib;
  int  fLogLevel;
  string cpp_opt;

  TClonesArray* fMacroToCompileName;

  ClassDef(MyUtils, 0);
}; //end MyUtils

R__EXTERN MyUtils* gMyUtils;

namespace Utils {

  MyUtils* GetMyUtils();
};

#endif /* defined(__MyUtils__) */
