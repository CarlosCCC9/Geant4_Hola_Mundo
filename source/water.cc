#include "water.hh"

water_sensitive::water_sensitive(G4String name):G4VSensitiveDetector(name){
    fEnergydep_w = 0;
}

water_sensitive::~water_sensitive(){
}

void water_sensitive::Initialize(G4HCofThisEvent *){
    fEnergydep_w = 0;
}

void water_sensitive::EndOfEvent(G4HCofThisEvent *){

}

G4bool water_sensitive::ProcessHits(G4Step *aStep, G4TouchableHistory *){

    /*
    //Gammas primarios
    
    G4bool isFirstStep = aStep->IsFirstStepInVolume();
    G4int step_num = aStep->GetTrack()->GetCurrentStepNumber();
    G4ParticleDefinition *particle = aStep->GetTrack()->GetDefinition();
    const G4VProcess *proc = aStep->GetTrack()->GetCreatorProcess();
    const G4String& creator= proc ? proc->GetProcessName() : " ";

    if(isFirstStep){
        if (particle == G4Gamma::GammaDefinition()){
            if(creator==" "){

                G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
                G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

                G4ThreeVector prePos = preStepPoint->GetPosition();
                G4ThreeVector postPos = postStepPoint->GetPosition();

                const G4VProcess *preProc = preStepPoint->GetProcessDefinedStep();
                const G4String& preProcName = preProc ? preProc->GetProcessName() : " ";

                const G4VProcess *postProc = postStepPoint->GetProcessDefinedStep();
                const G4String& postProcName = postProc ? postProc->GetProcessName() : " ";

                G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
                G4double nrg = preStepPoint->GetTotalEnergy();
                G4double nrg_dep = aStep->GetTotalEnergyDeposit();

                if(postProcName == "conv"){
                    G4AnalysisManager *man = G4AnalysisManager::Instance();

                    man->FillNtupleIColumn(2, 0, evt);
                    man->FillNtupleDColumn(2, 1, prePos[0]);
                    man->FillNtupleDColumn(2, 2, prePos[1]);
                    man->FillNtupleDColumn(2, 3, prePos[2]);                    
                    man->FillNtupleDColumn(2, 4, aStep->GetDeltaPosition().mag());
                    man->FillNtupleDColumn(2, 5, nrg);
                    man->FillNtupleIColumn(2, 6, step_num);
                    man->AddNtupleRow(2);
                }
    */
                /*
                G4cout<<"///////////////////"<<G4endl;
                G4cout<<"Length "<<aStep->GetDeltaPosition().mag()<<" Creator: "<<creator<<" Proc: "<<preProcName<<" "<<postProcName<<G4endl;
                G4cout<<"\n"<<G4endl;
                */
     //       }
    //    }

            
   // }
    

    G4bool isFirstStep = aStep->IsFirstStepInVolume();
    G4int step_num = aStep->GetTrack()->GetCurrentStepNumber();

    if(isFirstStep){
        G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
        G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

        G4ThreeVector posPhoton = preStepPoint->GetPosition();
        G4ThreeVector momPhoton = preStepPoint->GetMomentum();

        G4double wlen = (1.239841939*eV/momPhoton.mag())*1E+03;

        G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

        G4double time = preStepPoint->GetGlobalTime();

        G4ParticleDefinition *particle = aStep->GetTrack()->GetDefinition();
        //G4cout<<particle->GetParticleName()<<G4endl;

        G4double nrg = preStepPoint->GetTotalEnergy();
        G4double nrg_dep = aStep->GetTotalEnergyDeposit();
        //G4double nrg_kin = preStepPoint->GetKineticEnergy();

        G4int type=0;

        if(particle == G4OpticalPhoton::OpticalPhotonDefinition()){
            type=1;
        }
        else if(particle == G4Gamma::GammaDefinition()){
            type=2;
        }
        else if(particle == G4Electron::ElectronDefinition()){
            type=3;
            if(step_num>1){return false;}
        }
        else if(particle == G4Positron::PositronDefinition()){
            type=4;
            if(step_num>1){return false;}
        }

        const G4VProcess *proc = aStep->GetTrack()->GetCreatorProcess();
        const G4String& creator= proc ? proc->GetProcessName() : " ";


        G4int type_proc=0;

        if(creator=="conv"){
            type_proc=1;
        }
        else if(creator=="Cerenkov"){
            type_proc=2;
        }
        else if(creator=="phot"){
            type_proc=3;
        }
        else if(creator=="eBrem"){
            type_proc=4;
        }
        else if(creator=="compt"){
            type_proc=5;
        }
        else if(creator=="eIoni"){
            type_proc=6;
        }
        else if(creator=="annihil"){
            type_proc=7;
        }
        else{
            type_proc=0;
            //G4cout<<"creator: "<<creator<<G4endl;
        }

        //Get parent ID
        G4int parentID = aStep->GetTrack()->GetParentID();

        //Get particle Id
        //G4int particleID = aStep->GetTrack()->GetTrackID();
        /*
        if(particle != G4OpticalPhoton::Definition()){
            G4cout<<"name"<<"\tcreator"<<"\tparentID"<<"\tstep_num"<<"\tparticleID"<<"\ttime"<<"\tnrg"<<"\tnrg_dep"<<G4endl;
            G4cout<<particle->GetParticleName()<<"\t"<<creator<<"\t"<<parentID<<"\t"<<step_num<<"\t"<<particleID<<"\t"<<time<<"\t"<<nrg<<"\t"<<nrg_dep<<"\n";
            G4cout<<G4endl;
        }
        */
 
        G4AnalysisManager *man = G4AnalysisManager::Instance();

        man->FillNtupleIColumn(1, 0, evt);
        man->FillNtupleDColumn(1, 1, posPhoton[0]);
        man->FillNtupleDColumn(1, 2, posPhoton[1]);
        man->FillNtupleDColumn(1, 3, posPhoton[2]);
        man->FillNtupleDColumn(1, 4, wlen);
        man->FillNtupleDColumn(1, 5, nrg);
        man->FillNtupleDColumn(1, 6, nrg_dep);
        man->FillNtupleDColumn(1, 7, time);
        man->FillNtupleIColumn(1, 8, type_proc);
        man->FillNtupleIColumn(1, 9, parentID);
        man->AddNtupleRow(1);
    }

    return true;
}