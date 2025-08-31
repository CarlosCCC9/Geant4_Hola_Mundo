#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4MTRunManager.hh"
//#include "FTFP_BERT.hh"
//#include "G4OpticalPhysics.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv){

  #ifdef G4MULTITHREADED
    G4MTRunManager *runManager = new G4MTRunManager();
  #else
    G4RunManager *runManager = new G4RunManager();
  #endif
  
  runManager->SetUserInitialization(new geometry_construct());

  /*
  //physics list
  G4VModularPhysicsList* physicsList = new FTFP_BERT;
  auto opticalPhysics = new G4OpticalPhysics();
  physicsList->RegisterPhysics(opticalPhysics);
  runManager->SetUserInitialization(physicsList);
  */

  runManager->SetUserInitialization(new physics_list());
  runManager->SetUserInitialization(new action());
  
  //runManager->Initialize();
  
  G4UIExecutive *ui = 0;
  
  if(argc == 1){
    ui = new G4UIExecutive(argc,argv);
  }
  
  G4VisManager *visManager = new G4VisExecutive();
  visManager->Initialize();
  
  G4UImanager *UImanager = G4UImanager::GetUIpointer();
  
  if(ui){
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    }
  else{
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);

    }
    
    delete ui;
    delete visManager;
    delete runManager;
    
  return 0;
}
