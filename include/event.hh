#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

#include "run.hh"

class event_act : public G4UserEventAction{

    public:

     event_act(run_act*);
     ~event_act();
     
     virtual void BeginOfEventAction(const G4Event*);
     virtual void EndOfEventAction(const G4Event*);
     
     void AddEdep(G4double edep){fEdep += edep;}
     void AddEdep_2(G4double edep){fEdep_2 += edep;}
     
    private:

      G4double fEdep, fEdep_2;
    
};

#endif