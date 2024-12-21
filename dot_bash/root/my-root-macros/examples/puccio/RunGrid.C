/// \file RunGrid.C
/// \brief Macro to lunch a task on the GRID
///
/// \author Maximiliano Puccio <maximiliano.puccio@cern.ch>, University and INFN Torino
/// \date Feb 21th, 2015

#if !defined(__CINT__) || defined(__MAKECINT__)
#include <Rtypes.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TChain.h>
#include <TArrayI.h>
#include "AliAnalysisGrid.h"
#include "AliAnalysisManager.h"
#include "AliAnalysisAlien.h"
#include "AliAnalysisDataContainer.h"
#include "AliMCEventHandler.h"
#include "AliLog.h"
#include "AliAnalysisTaskPIDResponse.h"
#include "AliAODInputHandler.h"
#include "AddTaskNucleiYield.C"
#include "AliAnalysisTaskNucleiYield.h"
#endif

void GetRunList(Int_t &start, Int_t &nRuns,TString who) {
  if (who.Contains("maximiliano",TString::kIgnoreCase)) {
    start = 0;
    nRuns = 80;
  }
  else if (who.Contains("stefania",TString::kIgnoreCase)) {
    start = 36;
    nRuns = 36;
  }
  else if (who.Contains("massimo",TString::kIgnoreCase)) {
    start = 72;
    nRuns = 36;
  }
  else {
    start = 0;
    nRuns = 107;
  }
  return;
}

void SetAlienHandler(AliAnalysisAlien* plugin,TString &who,const char *taskname, Bool_t isMC) {
  // Set versions of used packages
  plugin->SetAPIVersion("V1.1x");
  plugin->SetROOTVersion("v5-34-08-7");
  plugin->SetAliROOTVersion("v5-06-00");
  plugin->SetAliPhysicsVersion("vAN-20150120");
  plugin->SetExecutableCommand("aliroot -b -q");
  
  // Declare input data to be processed.
  
  // Method 1: Create automatically XML collections using alien 'find' command.
  // Define production directory LFN
  
  TArrayI rlist;
  // MC
  if (isMC) {
//    plugin->SetGridDataDir("/alice/sim/2014/LHC14a6/"); //sim v
    plugin->SetGridDataDir("/alice/sim/2012/LHC12a17a_fix/"); //sim 0-10% v test1
//    plugin->SetGridDataDir("/alice/sim/2012/LHC12a17d_fix/"); //sim 0-10% x test3
//    plugin->SetGridDataDir("/alice/sim/2012/LHC12a17b_fix/"); //sim 10-50% v test2
//    plugin->SetGridDataDir("/alice/sim/2012/LHC12a17e_fix/"); //sim 10-50% v test4
    plugin->SetDataPattern("*/AliAOD.root"); // sim
    plugin->SetRunPrefix("");   // mc
    
    Int_t runlist[107] = {
      167915, 167920, 167985, 167987, 168069, 168076, 168105, 168107, 168108, 168115,
      168310, 168311, 168322, 168325, 168341, 168342, 168361, 168362, 168458, 168460,
      168464, 168467, 168511, 168512, 168514, 168777, 168826, 168988, 168992, 169035,
      169040, 169044, 169045, 169091, 169094, 169099, 169138, 169144, 169145, 169148,
      169156, 169160, 169167, 169238, 169411, 169415, 169417, 169418, 169419, 169420,
      169475, 169498, 169504, 169506, 169512, 169515, 169550, 169553, 169554, 169555,
      169557, 169586, 169587, 169588, 169590, 169591, 169835, 169837, 169838, 169846,
      169855, 169858, 169859, 169923, 169965, 170027, 170040, 170081, 170083, 170084,
      170085, 170088, 170089, 170091, 170155, 170159, 170163, 170193, 170203, 170204,
      170207, 170228, 170230, 170268, 170269, 170270, 170306, 170308, 170309, 170311,
      170312, 170313, 170315, 170387, 170388, 170572, 170593
    };
    rlist.Set(107, runlist);
  } else {
    // DATA
    plugin->SetGridDataDir("/alice/data/2011/LHC11h_2/"); //sim
    plugin->SetDataPattern("*/pass2/AOD145/*AliAOD.root"); // sim
    plugin->SetRunPrefix("000");   // real data
    
    Int_t runlist[120] = {                                                                 // Counter
      170309, 170308, 170306, 170270, 170269, 170268, 170230, 170228, 170204, 170203,
      170193, 170163, 170159, 170155, 170081, 170027, 169859, 169858, 169855, 169846,
      169838, 169837, 169835, 169417, 169415, 169411, 169238, 169167, 169160, 169156,
      169148, 169145, 169144, 169138, 169094, 169091, 169035, 168992, 168988, 168826,
      168777, 168514, 168512, 168511, 168467, 168464, 168460, 168458, 168362, 168361,
      168342, 168341, 168325, 168322, 168311, 168310, 167988, 167987,                      // from CF
      167902, 167903, 167909, 167986, 168066, 168068, 168103, 168104, 168212, 168461,
      168984, 169040, 169044, 169045, 169099, 169143, 169418, 169419, 169420, 169475,
      169498, 169504, 169506, 169512, 169515, 169550, 169553, 169554, 169555, 169557,
      169584, 169586, 169587, 169588, 169590, 169591, 169922, 169956, 169975, 169981,
      170036, 170038, 170040, 170083, 170084, 170085, 170088, 170089, 170091, 170152,
      170195, 170207, 170208, 170311, 170312, 170313, 170315, 170387, 170388, 170556,
      170572, 170593
    };
    rlist.Set(120, runlist);

  }

  
  Int_t start = 0, nrun = 0;
  GetRunList(start,nrun,who);
  
  for(Int_t i = start; i < start + nrun; i++) {
    plugin->AddRunNumber(rlist[i]);
  }
  
  plugin->SetNrunsPerMaster(54);
  plugin->SetOutputToRunNo();
  
  
  // Method 2: Declare existing data files (raw collections, xml collections, root file)
  //   plugin->AddDataFile("/alice/data/2008/LHC08c/000057657/raw/Run57657.Merged.RAW.tag.root");
  
  // Define alien work directory where all files will be copied. Relative to alien $HOME.
  plugin->SetGridWorkingDir("NucleiYieldMCfix");
  
  // Declare alien output directory. Relative to working directory.
  plugin->SetGridOutputDir("output1"); // In this case will be $HOME/taskname/out
  
  // Declare the analysis source files names separated by blancs. To be compiled runtime
  // using ACLiC on the worker nodes.
  plugin->SetAnalysisSource("AliAnalysisTaskNucleiYield.cxx");
  
  //questo
  plugin->SetAdditionalLibs("libSTEERBase.so libESD.so AliAnalysisTaskNucleiYield.h AliAnalysisTaskNucleiYield.cxx libPWGflowBase.so libPWGflowTasks.so libPWGHFbase.so libPWGHFvertexingHF.so libOADB.so");
  plugin->AddIncludePath("-I. -I$ROOTSYS/include -I$ALICE_PHYSICS/include -g");
  
  // Declare the output file names separated by blancs.
  // (can be like: file.root or file.root@ALICE::Niham::File)
  // To only save certain files, use SetDefaultOutputs(kFALSE), and then
  // SetOutputFiles("list.root other.filename") to choose which files to save
  plugin->SetDefaultOutputs();
  //plugin->SetOutputFiles("list.root");
  
  // Optionally set a name for the generated analysis macro (default MyAnalysis.C)
  plugin->SetAnalysisMacro(Form("%s.C",taskname));
  
  // Optionally set maximum number of input files/subjob (default 100, put 0 to ignore)
  plugin->SetSplitMaxInputFileNumber(90);
  
  // Optionally modify the executable name (default analysis.sh)
  plugin->SetExecutable(Form("%s.sh",taskname));
  
  // set number of test files to use in "test" mode
  plugin->SetNtestFiles(1);
  
  // file containing a list of chuncks to be used for testin
  plugin->SetFileForTestMode("testdata");
  
  // Optionally resubmit threshold.
  plugin->SetMasterResubmitThreshold(90);
  
  // Optionally set time to live (default 30000 sec)
  plugin->SetTTL(30000);
  
  // Optionally set input format (default xml-single)
  plugin->SetInputFormat("xml-single");
  
  // Optionally modify the name of the generated JDL (default analysis.jdl)
  plugin->SetJDLName(Form("%s.jdl",taskname));
  
  // Optionally modify job price (default 1)
  plugin->SetPrice(1);
  
  // Optionally modify split mode (default 'se')
  plugin->SetSplitMode("se");
  
  // file should contain path name to a local directory containg *ESDs.root etc
  plugin->SetFileForTestMode("files.txt");
}

/// This is the main function that launches the task
///
/// \param runtype Running mode, can be local or grid
/// \param gridmode Grid parameter, can be "full", "test", "offline", "submit" or "terminate"
/// \param isMC True if the analysed dataset is MC
/// \param nentries Number of event to be analysed (it works only in local mode)
/// \param firstentry First event to be analysed (it works only in local mode)
/// \param taskname Name of the task
/// \return void
///
void RunGrid(TString runtype = "grid", TString gridmode = "test", Bool_t isMC = kFALSE,
             const Long64_t nentries = 400, const Long64_t firstentry = 0,
             const char *taskname = "NucleiYield") {
  // check run type
  TString who = runtype;
  if (
      who.Contains("stefano",TString::kIgnoreCase) ||
      who.Contains("simone",TString::kIgnoreCase) ||
      who.Contains("maximiliano",TString::kIgnoreCase) ||
      who.Contains("stefania",TString::kIgnoreCase) ||
      who.Contains("elena",TString::kIgnoreCase) ||
      who.Contains("massimo",TString::kIgnoreCase) ||
      who.Contains("all",TString::kIgnoreCase)
      ) {
    runtype = "grid";
    gridmode = "full";
  }
  
  if(runtype != "local" && runtype != "grid"){
    Printf("\n\tIncorrect run option, check first argument of run macro");
    Printf("\tint runtype = local or grid\n");
    return;
  }
  Printf("%s analysis chosen",runtype.Data());
  gROOT->ProcessLine(".include $ALICE_ROOT/include");
  
  gSystem->AddIncludePath("-I$ALICE_ROOT/include");
  gSystem->AddIncludePath("-I$ALICE_PHYSICS/include");
  
  // Load analysis specific libraries
  //=====================================================================
  
  gSystem->Load("libTree.so");
  gSystem->Load("libGeom.so");
  gSystem->Load("libPhysics.so");
  gSystem->Load("libVMC.so");
  gSystem->Load("libMinuit.so");
  gSystem->Load("libSTEERBase.so");
  gSystem->Load("libESD.so");
  gSystem->Load("libAOD.so");
  gSystem->Load("libANALYSIS.so");
  gSystem->Load("libOADB.so");
  gSystem->Load("libANALYSISalice.so");
  gSystem->Load("libCORRFW.so");
  gSystem->Load("libPWGHFbase.so");
  gSystem->Load("libPWGflowBase.so");
  gSystem->Load("libPWGflowTasks.so");
  gSystem->Load("libPWGHFvertexingHF.so");
  
  // Load analysis specific libraries
  //------ Create AlienPlugin ---------------------
  AliAnalysisAlien *plugin = 0x0;
  TChain *chain = 0x0;
  if (runtype != "local") {
    plugin = new AliAnalysisAlien();
    plugin->SetRunMode(gridmode);
    SetAlienHandler(plugin, who, taskname, isMC);
    if(!plugin) return;
  } else {
    gROOT->LoadMacro("$ALICE_PHYSICS/PWG/EMCAL/macros/CreateAODChain.C");
    chain = CreateAODChain("AODs.txt");
  }
  
  //---- Create the analysis manager
  AliAnalysisManager* mgr = new AliAnalysisManager(taskname);
  if(plugin) mgr->SetGridHandler(plugin);
  
  //  Input
  AliMCEventHandler*  mcHandler = new AliMCEventHandler();
  if (plugin && isMC) mgr->SetMCtruthEventHandler(mcHandler);
  
  AliAODInputHandler* iH = new AliAODInputHandler("handler","handler for my analisys");
  mgr->SetInputEventHandler(iH);
  
  
  //--------------------------------------------------------------
  // Other tasks
  
  // PID response
  gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDResponse.C");
  AliAnalysisTaskPIDResponse *pidTask = AddTaskPIDResponse(isMC); // useMC
  // PID QA
//    gROOT->LoadMacro("$ALICE_ROOT/ANALYSIS/macros/AddTaskPIDqa.C");
//    AliAnalysisTaskPIDqa *pidQATask = AddTaskPIDqa();
  
  gROOT->LoadMacro("./AliAnalysisTaskNucleiYield.cxx+");
  gROOT->LoadMacro("./AddTaskNucleiYield.C");
  AliAnalysisTaskNucleiYield* task = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020);
  AliAnalysisTaskNucleiYield* taskchi0 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"3cent_chisquare0");
  taskchi0->SetRequireMaxChi2(3.5);
  AliAnalysisTaskNucleiYield* taskchi1 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"3cent_chisquare1");
  taskchi1->SetRequireMaxChi2(4.5);
  AliAnalysisTaskNucleiYield* taskchi2 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"3cent_chisquare2");
  taskchi2->SetRequireMaxChi2(5.0);
  AliAnalysisTaskNucleiYield* taskchi3 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"3cent_chisquare3");
  taskchi3->SetRequireMaxChi2(5.5);
  AliAnalysisTaskNucleiYield* taskchi4 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"3cent_chisquare4");
  taskchi4->SetRequireMaxChi2(6.0);
  AliAnalysisTaskNucleiYield* taskdcaz0 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"3cent_dcaz0");
  taskdcaz0->SetRequireMaxDCAz(0.50);
  AliAnalysisTaskNucleiYield* taskdcaz1 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"3cent_dcaz1");
  taskdcaz1->SetRequireMaxDCAz(0.75);
  AliAnalysisTaskNucleiYield* taskdcaz2 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"3cent_dcaz2");
  taskdcaz2->SetRequireMaxDCAz(1.50);
  AliAnalysisTaskNucleiYield* taskdcaz3 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"3cent_dcaz3");
  taskdcaz3->SetRequireMaxDCAz(2.00);
  AliAnalysisTaskNucleiYield* tasktpc0 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"3cent_tpc0");
  tasktpc0->SetRequireTPCsignal(60);
  AliAnalysisTaskNucleiYield* tasktpc1 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"3cent_tpc1");
  tasktpc1->SetRequireTPCsignal(65);
  AliAnalysisTaskNucleiYield* tasktpc2 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"3cent_tpc2");
  tasktpc2->SetRequireTPCsignal(75);
  AliAnalysisTaskNucleiYield* tasktpc3 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"3cent_tpc3");
  tasktpc3->SetRequireTPCsignal(80);
  AliAnalysisTaskNucleiYield* taskcent4 = AddTaskNucleiYield(isMC,AliPID::kDeuteron,1000010020,"4cent");
  Float_t fourCentBins[5] = {0.,10.,20.,40.,60.};
  taskcent4->SetCentBins(4, fourCentBins);
  
  
  //__________________________________________________________________________
  // Disable debug printouts
  mgr->SetDebugLevel(3);
  AliLog::SetGlobalLogLevel(AliLog::kFatal);
  AliLog::SetGlobalDebugLevel(0);
  
  //__________________________________________________________________________
  if (!mgr->InitAnalysis()) return;
  mgr->PrintStatus();
  // Start analysis in grid.
  if (runtype == "local")
    mgr->StartAnalysis(runtype,chain,nentries,firstentry);
  else
    mgr->StartAnalysis(runtype,nentries,firstentry);
}
