#include "event.hh"

event_act::event_act(run_act*){
  fEdep=0;
  fEdep_2=0;
}

event_act::~event_act(){
}

void event_act::BeginOfEventAction(const G4Event*){
  fEdep=0;
  fEdep_2=0;
}

void event_act::EndOfEventAction(const G4Event*){

  //Get event
}