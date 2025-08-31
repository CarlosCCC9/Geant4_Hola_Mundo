#include "physics.hh"


physics_list::physics_list(){
    RegisterPhysics (new G4EmStandardPhysics());
    RegisterPhysics (new G4OpticalPhysics());
    RegisterPhysics (new G4DecayPhysics());
    RegisterPhysics (new G4RadioactiveDecayPhysics());

}

physics_list::~physics_list(){
}


/*
physics_list::physics_list() : G4VModularPhysicsList(), fEmPhys(0), fOpPhys(0), fDecayPhys(0), fVerbose(1), fMaxNumPhotonStep(20){
  G4LossTableManager::Instance();
  SetDefaultCutValue(1*mm);
  
  SetVerboseLevel(1);
  
  fEmName = G4String("emstandard");
  fEmPhys = new G4EmStandardPhysics();
  fOpPhys = new G4OpticalPhysics();
  fDecayPhys = new G4DecayPhysics();
}

physics_list::~physics_list(){
  delete fDecayPhys;
  delete fEmPhys;
  delete fOpPhys;
}

void physics_list::ConstructParticle(){
  fDecayPhys->ConstructParticle();
}

void physics_list::ConstructProcess(){
  AddTransportation();
  if (fEmPhys)
    fEmPhys->ConstructProcess();
    
  if (fOpPhys)
    fOpPhys->ConstructProcess();
  
  if (fDecayPhys)
    fDecayPhys->ConstructProcess();
}

void physics_list::SetCuts(){
  if (verboseLevel > 1){
    G4cout << "Tank sim physics list::SetCuts:";
  }
  SetCutsWithDefault();
}
*/
