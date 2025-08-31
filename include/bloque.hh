#ifndef BLOQUE_HH
#define BLOQUE_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalPhoton.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4ParticleDefinition.hh"

class bloque_sensible : public G4VSensitiveDetector{

public:
    bloque_sensible(G4String);
    ~bloque_sensible();

private:
    G4double fEnergydep_w;

    virtual void Initialize(G4HCofThisEvent *) override;
    virtual void EndOfEvent(G4HCofThisEvent *) override;
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};



#endif
