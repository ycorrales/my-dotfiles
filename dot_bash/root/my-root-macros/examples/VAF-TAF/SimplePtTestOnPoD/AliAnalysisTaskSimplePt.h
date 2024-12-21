#ifndef AliAnalysisTaskSimplePt_H
#define AliAnalysisTaskSimplePt_H
#include "AliAnalysisTaskSE.h"

class TObjArray;
class AliVParticle;
class AliAODEvent;
class TLorentzVector;
class AliMuonTrackCuts;

class AliAnalysisTaskSimplePt : public AliAnalysisTaskSE {

  public:

    AliAnalysisTaskSimplePt();
    AliAnalysisTaskSimplePt(const char *name);
    virtual ~AliAnalysisTaskSimplePt();

    virtual void NotifyRun();
    void UserCreateOutputObjects();
    void UserExec(Option_t *option);
    void Terminate(Option_t *);
    
  private:

    AliAnalysisTaskSimplePt(const AliAnalysisTaskSimplePt&);
    AliAnalysisTaskSimplePt& operator=(const AliAnalysisTaskSimplePt&);

    AliAODEvent* fAODEvent;       // AOD event
    TH1D *fHistThePt;             //!
    TList *fOutput;               //< List of histograms for data

  ClassDef(AliAnalysisTaskSimplePt, 1);

};

#endif
