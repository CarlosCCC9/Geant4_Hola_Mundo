#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Ellipsoid.hh"
#include "G4Cons.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4LogicalVolume.hh"
#include "G4GenericMessenger.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4SDManager.hh"

#include "detector.hh"
#include "bloque.hh"
#include "water.hh"




class geometry_construct : public G4VUserDetectorConstruction{

    public:
        geometry_construct();
        ~geometry_construct();
        G4LogicalVolume *GetScoringVolume() const {return fScoringVolume;}

        virtual G4VPhysicalVolume *Construct();
        void Tank();

    private:
        
        virtual void ConstructSDandField();

        G4Material *air, *water, *pyrex, *polypropylene, *stainless_steel;

        G4Box *solidWorld;
        G4Ellipsoid *solidDetector, *solidPMT_struct, *solidPMT;
        G4Tubs *solidTank, *solidTank_red, *solidWater, *solidAir, *solidStruct;

        G4LogicalVolume *logicWorld, *logicTank, *logicWater, *logicAir, *logicCone, *logicPMT, *logicStruct;
        G4VPhysicalVolume *physWorld, *physTank, *physWater, *physAir, *physCone, *physPMT, *physStruct;
        void DefineMaterials();

        G4LogicalVolume *fScoringVolume;

};


#endif
