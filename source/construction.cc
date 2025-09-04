#include "construction.hh"

geometry_construct::geometry_construct(){

    nblocks=100;

    DefineMaterials();
}

geometry_construct::~geometry_construct(){
}


void geometry_construct::DefineMaterials(){
    G4NistManager *nist = G4NistManager::Instance();

    air = nist->FindOrBuildMaterial("G4_AIR");
    water = nist->FindOrBuildMaterial("G4_Water");
    gold = nist->FindOrBuildMaterial("G4_Au");
    lead = nist->FindOrBuildMaterial("G4_Pb");

    F18 = new G4Isotope("F18", 9, 18, 18.000938 *g/mole);
    elF18 = new G4Element("Fluor18", "F18",1);
    elF18->AddIsotope(F18, 100.0*perCent);

    matF18 = new G4Material("F18Src", 1.51*g/cm3, 1);
    matF18->AddElement(elF18, 100.0*perCent);
}


G4VPhysicalVolume *geometry_construct::Construct(){

    //Mundo
    G4double xWorld = 1.*m;
    G4double yWorld = 1.*m;
    G4double zWorld = 1.*m;

    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
    logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "physWorld", 0, false, 0, true);

    //Fuente
    G4double srcRad = 1.*mm;
    solidFluor = new G4Sphere("solidFluor", 0.0, srcRad, 0.0, 360.*deg, 0.0, 180.*deg);
    logicFluor = new G4LogicalVolume(solidFluor, matF18, "logicFluor");
    physFluor = new G4PVPlacement(0, G4ThreeVector(0,0,0.2*m), logicFluor, "physFluor", logicWorld, false, 0,true);

    G4VisAttributes *srcVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 1.0, 0.5));
    srcVisAtt->SetForceSolid(true);
    logicFluor->SetVisAttributes(srcVisAtt);


    //Placa
    G4double xPlaca = 25*cm;
    G4double yPlaca = 10*cm;
    G4double zPlaca = 10*cm;

    solidPlaca = new G4Box("solidPlaca", xPlaca, yPlaca, zPlaca/nblocks);
    logicPlaca = new G4LogicalVolume(solidPlaca, gold, "logicPlaca");

    //Divide zPlaca in nblocks parts and place them one after another
    for(G4int i=0; i<nblocks; i++){
        G4double zpos = -zPlaca + (i*2*zPlaca/nblocks) + (zPlaca/nblocks);
        physPlaca = new G4PVPlacement(0, G4ThreeVector(0,0,zpos), logicPlaca, "physPlaca", logicWorld, false, i, true);
    }

/*
    G4int zpos=0*cm;

    for(G4int i=0;i<nblocks;i++){
        physPlaca = new G4PVPlacement(0, G4ThreeVector(0,0,zpos),logicPlaca, "physPlaca", logicWorld, false, i, true);
        zpos=zpos+2*i*cm;
        //G4cout<<zpos<<G4endl;
    }
  */

   
    //Detector
    solidDetector= new G4Box("solidDetector", xPlaca, yPlaca, 1.*cm);
    logicDetector= new G4LogicalVolume(solidDetector, air, "logicDetector");
    physDetector = new G4PVPlacement(0, G4ThreeVector(0,0,-22.*cm), logicDetector, "physDetector", logicWorld, false,0,true);
   



    return physWorld;

}

void geometry_construct::ConstructSDandField(){
  //check if the detector is already defined
  G4SDManager *SDman = G4SDManager::GetSDMpointer();
  G4String SDname;
  G4VSensitiveDetector *sensDet, *sensBlock;
  
  if(SDman->FindSensitiveDetector("SensitiveDetector", false)){
    sensDet = SDman->FindSensitiveDetector("SensitiveDetector", false);
  }
  else{
    sensDet = new sens_det("SensitiveDetector");
    SDman->AddNewDetector(sensDet);
  }
  logicDetector->SetSensitiveDetector(sensDet);

   if(SDman->FindSensitiveDetector("BlockSensitiveDetector", false)){
      sensBlock = SDman->FindSensitiveDetector("BlockSensitiveDetector", false);
   }
   else{
      sensBlock = new bloque_sensible("BlockSensitiveDetector");
      SDman->AddNewDetector(sensBlock);
   }

    logicPlaca->SetSensitiveDetector(sensBlock);

}
