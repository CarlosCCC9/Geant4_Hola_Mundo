#include "action.hh"

action::action(){
}

action::~action(){
}

void action::BuildForMaster() const{
  /*
  run_act *runAction = new run_act();
  SetUserAction(runAction);
*/
}

void action::Build() const{
  generator *gen = new generator();
  SetUserAction(gen);
  

  run_act *runAction = new run_act();
  SetUserAction(runAction);
 /*
  event_act *eventAction = new event_act(runAction);
  SetUserAction(eventAction);

  step_act *steppingAction = new step_act(eventAction);
  SetUserAction(steppingAction);
*/

}
