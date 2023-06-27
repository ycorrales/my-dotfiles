/* $Id: $ */

///////////////////////////////////////////////////////////////////
//                                                               //
// rootlogon.C macro                                             //
//                                                               //
// Origin: Y. Corrales Morales, Torino, corrales@to.infn.it      //
//                                                               //
// Last change: Feb 9, 2017                                      //
//                                                               //
///////////////////////////////////////////////////////////////////

#if ! defined(__CINT__) || defined(__MAKECINT__) || defined(__CLING__)

#include <TROOT.h>
#include <TString.h>
#include <TSystem.h>

#endif

//__________________________________________________________________________________
void rootlogon()
{
  const string pwd = gSystem->WorkingDirectory();
  const string inc = pwd;
  //
  const string kBaseDir    = gSystem->Getenv("ROOTSYS")       ?
                             gSystem->ExpandPathName("$DOTFILES/root/my-root-macros/main") : "";
  const string fastjet     = gSystem->Getenv("FASTJET")       ?
                             gSystem->ExpandPathName("$FASTJET/include")                    : "";
  const string aliroot     = gSystem->Getenv("ALICE_ROOT")    ?
                             gSystem->ExpandPathName("$ALICE_ROOT/include")                 : "";
  const string aliphysics  = gSystem->Getenv("ALICE_PHYSICS") ?
                             gSystem->ExpandPathName("$ALICE_PHYSICS/include")              : "";
  const string fairmq_base = gSystem->Getenv("FAIRMQ_ROOT")   ?
                             gSystem->ExpandPathName("$FAIRMQ_ROOT/include")                : "";
  const string fairmq_full = gSystem->Getenv("FAIRMQ_ROOT")   ?
                             gSystem->ExpandPathName("$FAIRMQ_ROOT/include/fairmq")         : "";
  const string o2_develo   = gSystem->Getenv("O2_ROOT")       ?
                             gSystem->ExpandPathName("$O2_ROOT")                            : "";
  const string macros_path = gSystem->Getenv("MACROS_PATH")   ?
                             gSystem->ExpandPathName("$MACROS_PATH")                         : "";
  // Include paths
  // =============
  // There are 2 separate paths: one for ACLiC, and one for CINT or CLING.
  // 1. ACLiC include path
  gSystem->AddIncludePath(Form("-I%s ", inc.data()));
  //if(kBaseDir    != "") gSystem->AddIncludePath(Form("-I%s/", kBaseDir.data()));
  //if(fastjet     != "") gSystem->AddIncludePath(Form("-I%s ", fastjet.data()));
  //if(aliroot     != "") gSystem->AddIncludePath(Form("-I%s ", aliroot.data()));
  //if(aliphysics  != "") gSystem->AddIncludePath(Form("-I%s ", aliphysics.data()));
  //if(fairmq_base != "") gSystem->AddIncludePath(Form("-I%s ", fairmq_base.data()));
  //if(fairmq_full != "") gSystem->AddIncludePath(Form("-I%s ", fairmq_full.data()));

  // 2. Interpreter include path
  // Type .include (ROOT 5) or .I (ROOT 6) at the ROOT REPL to see a listing
  string kCmdInclude(".I");
  string kBuildDir("ROOT6");
#if defined(__CINT__)
  kCmdInclude = ".include";
  kBuildDir = "ROOT5";
#endif

  gROOT->ProcessLine(Form("%s %s",   kCmdInclude.data(), inc.data()));
  if(kBaseDir    != "")
    gROOT->ProcessLine(Form("%s %s", kCmdInclude.data(), kBaseDir.data()));
  if(fastjet     != "")
    gROOT->ProcessLine(Form("%s %s", kCmdInclude.data(), fastjet.data()));
  if(aliroot     != "")
    gROOT->ProcessLine(Form("%s %s", kCmdInclude.data(), aliroot.data()));
  if(aliphysics  != "")
    gROOT->ProcessLine(Form("%s %s", kCmdInclude.data(), aliphysics.data()));
  if(fairmq_base != "")
    gROOT->ProcessLine(Form("%s %s", kCmdInclude.data(), fairmq_base.data()));
  if(fairmq_full != "")
    gROOT->ProcessLine(Form("%s %s", kCmdInclude.data(), fairmq_full.data()));

  // Macros path
  // ===========
   if(macros_path != "") {
    string new_macros_path = gROOT->GetMacroPath();
    new_macros_path += string(":") + macros_path;
    gROOT->SetMacroPath(new_macros_path.c_str());
  }

#if defined(__CLING__)
#endif
  if(gSystem->Getenv("TMPDIR"))
    gSystem->SetBuildDir(gSystem->Getenv("TMPDIR"));
  bool load_myutils = (kBaseDir != "") ?
    !gSystem->AccessPathName(Form("%s/MyUtils.cxx", kBaseDir.data())) : false;
  if (load_myutils)
  {
    string tmp_build_dir = gSystem->GetBuildDir();
    gSystem->SetBuildDir(string(kBaseDir + "/../build").data());
    gROOT->ProcessLine(Form(".L %s/MyUtils.cxx+", kBaseDir.data()));
    gSystem->SetBuildDir(tmp_build_dir.data());
  }
  return;
}
