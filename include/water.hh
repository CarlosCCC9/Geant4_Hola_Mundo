#ifndef WATER_HH
#define WATER_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalPhoton.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4MuonMinus.hh"
#include "G4ParticleDefinition.hh"

class water_sensitive : public G4VSensitiveDetector{

public:
    water_sensitive(G4String);
    ~water_sensitive();

private:
    virtual void Initialize(G4HCofThisEvent *) override;
    virtual void EndOfEvent(G4HCofThisEvent *) override;
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};


#endif