#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"

#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ParticleTable.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4LossTableManager.hh"

class physics_list : public G4VModularPhysicsList{

    public:
      physics_list();
      ~physics_list();
    /*  
    protected:
      void ConstructParticle();
      void ConstructProcess();
      void SetCuts();
      
    private:
      G4VPhysicsConstructor *fEmPhys;
      G4VPhysicsConstructor *fOpPhys;
      G4VPhysicsConstructor *fDecayPhys;
      
      G4String fEmName;
      G4int fVerbose;
      G4int fMaxNumPhotonStep;
      
      G4bool fHelIsRegistered;
      G4bool fBicIsRegistered;
      G4bool fGnucIsRegistered;
      G4bool fStopIsRegistered;
    */
};

#endif
