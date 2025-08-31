#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4GeneralParticleSource.hh"
#include "G4GenericMessenger.hh"
#include "G4PhysicsOrderedFreeVector.hh"
#include "G4RunManager.hh"
#include "G4Geantino.hh"

class generator : public G4VUserPrimaryGeneratorAction{

public:
  generator();
  ~generator();
  
  virtual void GeneratePrimaries(G4Event*);

private:
    G4GeneralParticleSource *gps;
    G4ParticleGun *m_particleGun;
    G4GenericMessenger *fMessenger;
    G4bool gun;


};


#endif
