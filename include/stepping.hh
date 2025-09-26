#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4LogicalVolume.hh"

#include "construction.hh"
#include "detector.hh"
#include "event.hh"

class step_act : public G4UserSteppingAction{

public:
  step_act(event_act* eventAction);
  ~step_act();
  
  virtual void UserSteppingAction(const G4Step*);
  
  
private:
  event_act *fEventAction;
};


#endif
