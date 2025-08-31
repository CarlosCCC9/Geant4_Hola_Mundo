#include "detector.hh"

sens_det::sens_det(G4String name):G4VSensitiveDetector(name){

  fEnergydep = 0.;

}

sens_det::~sens_det(){
}

void sens_det::Initialize(G4HCofThisEvent *){
  fEnergydep = 0;
}

void sens_det::EndOfEvent(G4HCofThisEvent *){

}

G4bool sens_det::ProcessHits(G4Step *aStep, G4TouchableHistory *){

  G4Track *track = aStep->GetTrack();
  
  track->SetTrackStatus(fStopAndKill);

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posParticle = preStepPoint->GetPosition();
    G4ThreeVector momParticle = preStepPoint->GetMomentum();

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

    G4double time = preStepPoint->GetGlobalTime();
    G4double nrg = preStepPoint->GetTotalEnergy();

    G4AnalysisManager *man = G4AnalysisManager::Instance();

      man->FillNtupleIColumn(0, 0, evt);
      man->FillNtupleDColumn(0, 1, posParticle[0]);
      man->FillNtupleDColumn(0, 2, posParticle[1]);
      man->FillNtupleDColumn(0, 3, posParticle[2]);
      man->FillNtupleDColumn(0, 4, momParticle[0]);
      man->FillNtupleDColumn(0, 5, momParticle[1]);
      man->FillNtupleDColumn(0, 6, momParticle[2]);
      man->FillNtupleDColumn(0, 7, time);
      man->FillNtupleDColumn(0, 8, nrg);
      man->AddNtupleRow(0);

    return true;
  
}
