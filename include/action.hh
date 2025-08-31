#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "run.hh"
//#include "event.hh"
//#include "stepping.hh"

class action : public G4VUserActionInitialization{

    public:
      action();
      ~action();
      
      virtual void Build() const;
      virtual void BuildForMaster() const;
    
};

#endif
