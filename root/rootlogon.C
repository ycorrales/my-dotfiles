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
                             "$HOME/Work/git_myROOTmacros/main"   : "";
  const string fastjet     = gSystem->Getenv("FASTJET")       ?                               \
                              "$FASTJET/include"              : "";
  const string aliroot     = gSystem->Getenv("ALICE_ROOT")    ?
                              "$ALICE_ROOT/include"           : "";
  const string aliphysics  = gSystem->Getenv("ALICE_PHYSICS") ?
                              "$ALICE_PHYSICS/include"        : "";
  const string fairmq_base = gSystem->Getenv("FAIRMQ_ROOT")   ?
                              "$FAIRMQ_ROOT/include"          : "";
  const string fairmq_full = gSystem->Getenv("FAIRMQ_ROOT")   ?
                              "$FAIRMQ_ROOT/include/fairmq"   : "";
  const string o2_develo   = gSystem->Getenv("O2_ROOT")       ?
                              "$O2_ROOT"                      : "";
  const string sPHENIX     = gSystem->Getenv("OPT_SPHENIX")   ?
                              "$OPT_SPHENIX"                  : "";
  // Include paths
  // =============
  // There are 2 separate paths: one for ACLiC, and one for CINT or CLING.
  // 1. ACLiC include path
  gSystem->AddIncludePath(Form("-I%s ", inc.data()));
  if(kBaseDir    != "") gSystem->AddIncludePath(Form("-I%s/", kBaseDir.data()));
  if(fastjet     != "") gSystem->AddIncludePath(Form("-I%s ", fastjet.data()));
  if(aliroot     != "") gSystem->AddIncludePath(Form("-I%s ", aliroot.data()));
  if(aliphysics  != "") gSystem->AddIncludePath(Form("-I%s ", aliphysics.data()));
  if(fairmq_base != "") gSystem->AddIncludePath(Form("-I%s ", fairmq_base.data()));
  if(fairmq_full != "") gSystem->AddIncludePath(Form("-I%s ", fairmq_full.data()));

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
   if(sPHENIX != "") {
    string macro_path = gROOT->GetMacroPath();
    macro_path += string(":") + gSystem->ExpandPathName("$HOME/sPHENIX_SW/macros/macros/g4simulations/");
    gROOT->SetMacroPath(macro_path.c_str());
  }

#if defined(__CLING__)
#endif
  if(gSystem->Getenv("TMPDIR"))
    gSystem->SetBuildDir(gSystem->Getenv("TMPDIR"));
  if(kBaseDir != "") gROOT->ProcessLine(Form(".L %s/MyUtils.cxx+", kBaseDir.data()));

  return;
}