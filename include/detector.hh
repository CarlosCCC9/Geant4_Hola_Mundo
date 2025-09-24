#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalPhoton.hh"
#include "G4Electron.hh"
#include "G4MuonMinus.hh"
#include "G4ParticleDefinition.hh"


class sens_det : public G4VSensitiveDetector{

  public:
    sens_det(G4String);
    ~sens_det();
      
  private:
    virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
    
      
    virtual void Initialize(G4HCofThisEvent *) override;
    virtual void EndOfEvent(G4HCofThisEvent *) override;

};
    
#endif
