#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "detector.hh"
#include "bloque.hh"




class geometry_construct : public G4VUserDetectorConstruction{

    public:
        geometry_construct();
        ~geometry_construct();

        virtual G4VPhysicalVolume *Construct();

    private:
        
        G4int nblocks;

        virtual void ConstructSDandField();

        G4Material *air, *water, *gold, *lead, *matF18;
        G4Element *elF18;
        G4Isotope *F18;        

        G4Box *solidWorld, *solidPlaca, *solidDetector;
        G4Sphere *solidFluor;

        G4LogicalVolume *logicWorld, *logicPlaca, *logicDetector, *logicFluor;
        G4VPhysicalVolume *physWorld, *physPlaca, *physDetector, *physFluor;

        void DefineMaterials();

};




#endif
