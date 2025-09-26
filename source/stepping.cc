#include "stepping.hh"

step_act::step_act(event_act *eventAction){
    fEventAction = eventAction;
    //geom = geometry_construct;
}
  
step_act::~step_act(){
}

void step_act::UserSteppingAction(const G4Step *step){

    G4Track *aTrack = step->GetTrack();
    if (aTrack->GetDefinition()->GetParticleName() == "mu+" || 
            aTrack->GetDefinition()->GetParticleName() == "mu-"){
        if (aTrack->GetTrackStatus() == fStopAndKill && 
                step->GetPostStepPoint()->GetProcessDefinedStep() &&
                step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "Decay"){
            const geometry_construct *geom = static_cast<const geometry_construct*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
            G4LogicalVolume* currentVolume = step->GetPostStepPoint()->GetPhysicalVolume()->GetLogicalVolume();
            G4LogicalVolume *fScoringVolume = geom->GetScoringVolume();
            if(currentVolume == fScoringVolume){
                G4SDManager *sdManager = G4SDManager::GetSDMpointer();
                sens_det *sens = dynamic_cast<sens_det*>(sdManager->FindSensitiveDetector("SensitiveDetector"));
                if(sens) sens->decayed_muon=true;
                G4AnalysisManager *man= G4AnalysisManager::Instance();
                man->FillNtupleDColumn(3, 0, aTrack->GetGlobalTime()/ns);
                man->AddNtupleRow(3);
            }
        }
   }

}
