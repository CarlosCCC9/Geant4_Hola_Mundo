#include "bloque.hh"

bloque_sensible::bloque_sensible(G4String name):G4VSensitiveDetector(name){

  fEnergydep_w = 0.;

}

bloque_sensible::~bloque_sensible(){
}

void bloque_sensible::Initialize(G4HCofThisEvent *){
    fEnergydep_w = 0;
}

void bloque_sensible::EndOfEvent(G4HCofThisEvent *){

}

G4bool bloque_sensible::ProcessHits(G4Step *aStep, G4TouchableHistory *){

    G4bool isFirstStep = aStep->IsFirstStepInVolume();

    if(isFirstStep){
        G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
        G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

        G4ThreeVector posParticle = preStepPoint->GetPosition();
        G4ThreeVector momParticle = preStepPoint->GetMomentum();

        const G4VTouchable *touchable =aStep->GetPreStepPoint()->GetTouchable();
        G4int copyNo = touchable->GetCopyNumber();

        G4VPhysicalVolume *physVol = touchable->GetVolume();
        G4ThreeVector posDetector = physVol->GetTranslation();

        G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

        G4double time = preStepPoint->GetGlobalTime();
        G4double nrg = preStepPoint->GetTotalEnergy();

        G4AnalysisManager *man = G4AnalysisManager::Instance();

        man->FillNtupleIColumn(1, 0, evt);
        man->FillNtupleDColumn(1, 1, posParticle[0]);
        man->FillNtupleDColumn(1, 2, posParticle[1]);
        man->FillNtupleDColumn(1, 3, posParticle[2]);
        man->FillNtupleDColumn(1, 4, momParticle[0]);
        man->FillNtupleDColumn(1, 5, momParticle[1]);
        man->FillNtupleDColumn(1, 6, momParticle[2]);
        man->FillNtupleDColumn(1, 7, time);
        man->FillNtupleDColumn(1, 8, nrg);
        man->FillNtupleIColumn(1, 9, copyNo);
        man->FillNtupleDColumn(1, 10, posDetector[0]);
        man->FillNtupleDColumn(1, 11, posDetector[1]);
        man->FillNtupleDColumn(1, 12, posDetector[2]);        
        man->AddNtupleRow(1);
    }
    return true;

}
