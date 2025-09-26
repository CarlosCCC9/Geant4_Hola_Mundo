#include "run.hh"

run_act::run_act(){

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->CreateNtuple("Detector", "Detector");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fX");
  man->CreateNtupleDColumn("fY");
  man->CreateNtupleDColumn("fZ");
  man->CreateNtupleDColumn("fPx");
  man->CreateNtupleDColumn("fPy");
  man->CreateNtupleDColumn("fPz");
  man->CreateNtupleDColumn("fTime");
  man->CreateNtupleDColumn("fNrg");
  man->FinishNtuple(0);

  man->CreateNtuple("Water", "Water");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fX");
  man->CreateNtupleDColumn("fY");
  man->CreateNtupleDColumn("fZ");
  man->CreateNtupleDColumn("fNrg");
  man->CreateNtupleDColumn("fNrg_Dep");
  man->CreateNtupleDColumn("fTime");
  man->CreateNtupleIColumn("fType");
  man->CreateNtupleIColumn("fProc_Type");
  man->FinishNtuple(1);

}

run_act::~run_act(){
}

void run_act::BeginOfRunAction(const G4Run* run){

  G4AnalysisManager *man = G4AnalysisManager::Instance();
  
  G4int runID = run->GetRunID(); 
  std::stringstream strRunID;
  strRunID<<runID;

  man->OpenFile("../analysis/output"+strRunID.str()+".root");
  }

void run_act::EndOfRunAction(const G4Run*){

  G4AnalysisManager *man = G4AnalysisManager::Instance();
  
  man->Write();
  man->CloseFile();
}
