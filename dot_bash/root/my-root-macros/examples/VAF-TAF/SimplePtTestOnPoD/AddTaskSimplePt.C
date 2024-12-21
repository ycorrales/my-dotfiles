AliAnalysisTaskSimplePt *AddTaskSimplePt(Bool_t usePhysicsSelection) {

  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    ::Error("AddTaskpAJPsi", "No analysis manager to connect to.");
    return NULL;
  }

  AliAnalysisDataContainer *coutput1 = mgr->CreateContainer("clist", TList::Class(), AliAnalysisManager::kOutputContainer, mgr->GetCommonFileName());
  AliAnalysisTaskSimplePt *simplePtTask = new AliAnalysisTaskSimplePt("AliAnalysisTaskSimplePt");
  mgr->AddTask(simplePtTask);

  mgr->ConnectInput(simplePtTask, 0, mgr->GetCommonInputContainer());
  mgr->ConnectOutput(simplePtTask, 1, coutput1);

  return simplePtTask;
}
