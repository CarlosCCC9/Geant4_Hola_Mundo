#include "construction.hh"

geometry_construct::geometry_construct(){

    DefineMaterials();
}

geometry_construct::~geometry_construct(){
}


void geometry_construct::DefineMaterials(){
    G4NistManager *nist = G4NistManager::Instance();

    air = nist->FindOrBuildMaterial("G4_AIR");
    water = nist->FindOrBuildMaterial("G4_Water");
    pyrex= nist->FindOrBuildMaterial("G4_Pyrex_Glass");
    polypropylene = nist->FindOrBuildMaterial("G4_POLYPROPYLENE");

    //Water porperties
    std::ifstream datafile;
  
    G4int Nentries=23;
    G4double water_rind_energy[Nentries]={};
    G4double water_rindex[Nentries]={};
  
    datafile.open("water_rind.dat");
    G4int n=0;
    while(1){
      G4double nrg,rind;
      datafile >> nrg >> rind;
      if(datafile.eof())
        break;
      water_rind_energy[n]=nrg*eV;
      water_rindex[n]=rind;
      n++;
    }
    datafile.close();
  
    G4double water_abs_nrg[29]={1.46*eV, 1.48*eV, 1.49*eV, 1.50*eV, 1.51*eV, 1.53*eV, 1.55*eV, 1.60*eV, 1.65*eV, 1.71*eV, 1.77*eV, 1.84*eV, 1.91*eV, 1.98*eV, 2.07*eV, 2.16*eV, 2.25*eV, 2.36*eV, 2.48*eV, 2.61*eV, 2.76*eV, 2.92*eV, 3.10*eV, 3.31*eV, 3.54*eV, 3.82*eV, 4.13*eV, 4.51*eV, 4.96*eV};
    G4double water_abs_lngt[29]={0.233*m, 0.288*m, 0.344*m, 0.357*m, 0.418*m, 0.504*m, 0.500*m, 0.417*m, 0.385*m, 0.629*m, 1.667*m, 2.410*m, 3.125*m, 3.571*m, 4.348*m, 12.658*m, 22.222*m, 31.250*m, 40.000*m, 40.486*m, 35.714*m, 26.316*m, 17.241*m, 8.547*m, 4.292*m, 2.392*m, 1.493*m, 0.935*m, 0.595*m};
    
    G4MaterialPropertiesTable *mptWater = new G4MaterialPropertiesTable();
    mptWater->AddProperty("RINDEX", water_rind_energy, water_rindex, Nentries);
    mptWater->AddProperty("ABSLENGTH", water_abs_nrg, water_abs_lngt, 29);
    water->SetMaterialPropertiesTable(mptWater);

    //Pyrex
    //Pyrex properties
      //https://www.pmoptics.com/corning_pyrex.html 
    G4double pyrex_nrg[5]= {1239.8*eV/643.8, 1239.8*eV/587.6, 1239.8*eV/546.1, 1239.8*eV/514.5, 1239.8*eV/486.1};
    G4double pyrex_rindex[5]={1.472, 1.474, 1.476, 1.477, 1.479};
    G4MaterialPropertiesTable *mptPyrex = new G4MaterialPropertiesTable();
    mptPyrex->AddProperty("RINDEX", pyrex_nrg, pyrex_rindex, 5);
    pyrex->SetMaterialPropertiesTable(mptPyrex);

    //Propiedades del aire
    G4double air_nrg[2]={1.239841939*eV/0.9, 1.239841939*eV/0.2};
    G4double air_rindex[2]={1.0, 1.0};
    
    G4MaterialPropertiesTable *mptAir = new G4MaterialPropertiesTable();
    mptAir->AddProperty("RINDEX", air_nrg, air_rindex, 2);
    air->SetMaterialPropertiesTable(mptAir);

}

void geometry_construct::Tank(){
    //Valores Fijos
    G4double Tank_diam = 80.*cm;
    G4double Tankh = 100.*cm;
    G4double Tank_wall_width = 2.9*cm;
    G4double pmt_diam = 20.*cm;
    G4double pmt_thick = 0.3*cm;
    G4double waterh = 95*cm;

    //Estructura del PMT
    G4double pmt_innerRad = 0;
    G4double phiStart = 0.0*deg;
    G4double spanningPhi = 360.0*deg;

    //elipsoide superior
    G4double zsemi_2 = 7.*cm;
    G4double semiAxis=0.5*pmt_diam;

    G4double bot_z = -6*cm;
    G4double str_h = 13.0*cm;

    solidDetector = new G4Ellipsoid("solidPMT", semiAxis,semiAxis, zsemi_2, 0*cm, zsemi_2);

    //Tanque cobertura
    G4double Tank_innerRad = 0.*cm;
    G4double Tank_startAngle = 0.*deg;
    G4double Tank_spanningAngle = 360.*deg;
  
    solidTank = new G4Tubs("solidTank", Tank_innerRad, 0.5*Tank_diam,0.5*Tankh,Tank_startAngle,Tank_spanningAngle);
  
    //Tanque reduccion
    G4double outerRad=Tank_diam-Tank_wall_width;
    G4double redh=Tankh-Tank_wall_width;
  
    solidTank_red = new G4Tubs("solidTank", Tank_innerRad, 0.5*outerRad,0.5*redh,Tank_startAngle,Tank_spanningAngle);
  
    //Agua
    solidWater = new G4Tubs("solidWater", Tank_innerRad, 0.5*outerRad,0.5*waterh,Tank_startAngle,Tank_spanningAngle);
  
    //Remanente aire
    G4double diff_h = redh-waterh;

    solidAir = new G4Tubs("solidAir", Tank_innerRad, 0.5*outerRad,0.5*diff_h,Tank_startAngle,Tank_spanningAngle);

    //Subtractions

    G4ThreeVector zTrans0(0.,0.,0.5*Tank_wall_width);
    G4SubtractionSolid *solidTank1 = new G4SubtractionSolid("solidTank1", solidTank, solidTank_red,0,zTrans0);

    //Logicos  
    logicTank = new G4LogicalVolume(solidTank1, polypropylene, "logicTank");
    logicWater = new G4LogicalVolume(solidWater, water, "logicWater");
    logicAir = new G4LogicalVolume(solidAir, air, "logicAir");
    logicDetector = new G4LogicalVolume(solidDetector,pyrex,"logicPMT_struct");

    //Fisicos
    physTank = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicTank, "physTank", logicWorld, false, 0, true);
    physWater = new G4PVPlacement(0, G4ThreeVector(0,0,-0.5*Tankh+Tank_wall_width+0.5*waterh), logicWater, "physWater", logicWorld, false,0,true);
    physAir = new G4PVPlacement(0, G4ThreeVector(0,0,-0.5*Tankh+Tank_wall_width+waterh+0.5*diff_h), logicAir, "physAir", logicWorld, false,0,true);
    //new rotation matrix in the z-axis about 180 degrees
    G4RotationMatrix* rotm = new G4RotationMatrix();
    rotm->rotateZ(180.*deg);
    physDetector = new G4PVPlacement(rotm, G4ThreeVector(0,0,0.5*Tankh+Tank_wall_width+str_h-bot_z),logicDetector,"physPMT",logicWorld,false,0,true);
    
    
    //physDetector = new G4PVPlacement(0, G4ThreeVector(0,0,-0.5*waterh+str_h-bot_z),logicDetector,"physPMT",logicWater,false,0,true);

    //Superficie Optica
    G4OpticalSurface *tyvek = new G4OpticalSurface("tyvek");
    tyvek->SetType(dielectric_dielectric);
    tyvek->SetModel(unified);
    tyvek->SetFinish(groundfrontpainted);


    G4double tyvek_nrg[248]={1.55*eV,1.55138*eV,1.55276*eV,1.55414*eV,1.55553*eV,1.55831*eV,1.5611*eV,1.56953*eV,1.58667*eV,1.58811*eV,1.58956*eV,1.59101*eV,1.59977*eV,1.60271*eV,1.63732*eV,1.63886*eV,1.64504*eV,1.64659*eV,1.64815*eV,1.64971*eV,1.6544*eV,1.65597*eV,1.65913*eV,1.66071*eV,1.66229*eV,1.66387*eV,1.66546*eV,1.66706*eV,1.68477*eV,1.6864*eV,1.68803*eV,1.69131*eV,1.70453*eV,1.71122*eV,1.71797*eV,1.72306*eV,1.73333*eV,1.74025*eV,1.75957*eV,1.76491*eV,1.7775*eV,1.77932*eV,1.79396*eV,1.79581*eV,1.79766*eV,1.79951*eV,1.83937*eV,1.86096*eV,1.87497*eV,1.88104*eV,1.8851*eV,1.92251*eV,1.95923*eV,1.96364*eV,1.96808*eV,1.97476*eV,1.97924*eV,1.98827*eV,2.02287*eV,2.03943*eV,2.04661*eV,2.05384*eV,2.05626*eV,2.05869*eV,2.06112*eV,2.07831*eV,2.08577*eV,2.0958*eV,2.15538*eV,2.1634*eV,2.18508*eV,2.19609*eV,2.2241*eV,2.25283*eV,2.29433*eV,2.29735*eV,2.30038*eV,2.30646*eV,2.33113*eV,2.33425*eV,2.44212*eV,2.44555*eV,2.45588*eV,2.45934*eV,2.46282*eV,2.4663*eV,2.46979*eV,2.47329*eV,2.47681*eV,2.48033*eV,2.48386*eV,2.48741*eV,2.49096*eV,2.49452*eV,2.4981*eV,2.50168*eV,2.50527*eV,2.50888*eV,2.51249*eV,2.51612*eV,2.53072*eV,2.5344*eV,2.5455*eV,2.54922*eV,2.56421*eV,2.58321*eV,2.58704*eV,2.59088*eV,2.59474*eV,2.5986*eV,2.60248*eV,2.60637*eV,2.61027*eV,2.63393*eV,2.63791*eV,2.69498*eV,2.69915*eV,2.70334*eV,2.70754*eV,2.74159*eV,2.74591*eV,2.75024*eV,2.75458*eV,2.75894*eV,2.76331*eV,2.7677*eV,2.7721*eV,2.77651*eV,2.78094*eV,2.81233*eV,2.81687*eV,2.82143*eV,2.826*eV,2.83059*eV,2.84444*eV,2.85843*eV,2.86312*eV,2.86783*eV,2.87255*eV,2.87729*eV,2.88205*eV,2.88682*eV,2.89161*eV,2.90606*eV,2.91091*eV,2.91578*eV,2.92066*eV,2.92556*eV,2.93048*eV,2.96033*eV,2.96536*eV,2.97041*eV,2.97548*eV,3.00626*eV,3.01145*eV,3.04298*eV,3.07517*eV,3.0806*eV,3.08606*eV,3.10806*eV,3.11361*eV,3.11917*eV,3.14732*eV,3.19929*eV,3.22294*eV,3.28982*eV,3.32748*eV,3.34023*eV,3.34664*eV,3.35308*eV,3.36602*eV,3.37253*eV,3.41212*eV,3.41881*eV,3.44583*eV,3.4595*eV,3.49416*eV,3.50118*eV,3.51529*eV,3.53668*eV,3.56561*eV,3.57291*eV,3.58025*eV,3.60243*eV,3.60989*eV,3.61738*eV,3.6249*eV,3.63245*eV,3.64765*eV,3.66297*eV,3.67842*eV,3.6862*eV,3.69401*eV,3.71763*eV,3.72557*eV,3.74156*eV,3.7496*eV,3.75768*eV,3.7658*eV,3.77395*eV,3.78213*eV,3.79861*eV,3.8069*eV,3.81523*eV,3.832*eV,3.84044*eV,3.84891*eV,3.86598*eV,3.8832*eV,3.89186*eV,3.90057*eV,3.90931*eV,3.93578*eV,3.94468*eV,3.95363*eV,3.9807*eV,3.99896*eV,4.03598*eV,4.04534*eV,4.05475*eV,4.0642*eV,4.08323*eV,4.09281*eV,4.1316*eV,4.15127*eV,4.17113*eV,4.19118*eV,4.22161*eV,4.23186*eV,4.24215*eV,4.2525*eV,4.26289*eV,4.28384*eV,4.30499*eV,4.31564*eV,4.32635*eV,4.33711*eV,4.35879*eV,4.38069*eV,4.41395*eV,4.42515*eV,4.43641*eV,4.44772*eV,4.47053*eV,4.48202*eV,4.49357*eV,4.50518*eV,4.51684*eV};
    G4double tyvek_rindex[248]={0.985106,0.985106,0.982979,0.982979,0.982979,0.985106,0.985106,0.985106,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.985106,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.982979,0.980851,0.980851,0.980851,0.980851,0.980851,0.980851,0.980851,0.980851,0.980851,0.980851,0.980851,0.980851,0.980851,0.980851,0.980851,0.978723,0.978723,0.978723,0.978723,0.976596,0.976596,0.976596,0.976596,0.976596,0.976596,0.976596,0.976596,0.976596,0.976596,0.974468,0.974468,0.974468,0.974468,0.974468,0.974468,0.97234,0.97234,0.97234,0.97234,0.97234,0.97234,0.97234,0.97234,0.970213,0.970213,0.970213,0.970213,0.970213,0.970213,0.968085,0.968085,0.968085,0.968085,0.965957,0.965957,0.96383,0.961702,0.961702,0.961702,0.959574,0.959574,0.959574,0.957447,0.955319,0.953191,0.951064,0.948936,0.946809,0.946809,0.946809,0.946809,0.944681,0.942553,0.942553,0.940426,0.938298,0.93617,0.93617,0.934043,0.931915,0.929787,0.929787,0.92766,0.925532,0.923404,0.923404,0.923404,0.923404,0.921277,0.919149,0.917021,0.917021,0.914894,0.912766,0.910638,0.908511,0.908511,0.908511,0.906383,0.906383,0.906383,0.902128,0.902128,0.9,0.897872,0.897872,0.897872,0.895745,0.893617,0.893617,0.893617,0.891489,0.889362,0.887234,0.887234,0.885106,0.885106,0.882979,0.882979,0.882979,0.880851,0.878723,0.878723,0.876596,0.874468,0.87234,0.87234,0.870213,0.870213,0.868085,0.868085,0.86383,0.861702,0.855319,0.853191,0.851064,0.848936,0.846809,0.844681,0.842553,0.842553,0.842553,0.842553,0.844681,0.851064,0.859574,0.865957,0.870213};
    
    G4MaterialPropertiesTable *mptTyvek = new G4MaterialPropertiesTable();
    mptTyvek->AddProperty("REFLECTIVITY", tyvek_nrg, tyvek_rindex, 248);
    tyvek->SetMaterialPropertiesTable(mptTyvek);
    
    G4LogicalBorderSurface *water_tank_surface = new G4LogicalBorderSurface("water_tank_surface", physWater, physTank, tyvek);

}


G4VPhysicalVolume *geometry_construct::Construct(){

    //Mundo
    G4double xWorld = 5.*m;
    G4double yWorld = 5.*m;
    G4double zWorld = 5.*m;

    solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);
    logicWorld = new G4LogicalVolume(solidWorld, air, "logicWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0,0,0), logicWorld, "physWorld", 0, false, 0, true);

    Tank();

    return physWorld;

}

void geometry_construct::ConstructSDandField(){
  //check if the detector is already defined
  G4SDManager *SDman = G4SDManager::GetSDMpointer();
  G4String SDname;
  G4VSensitiveDetector *sensDet, *waterSens;
  
  if(SDman->FindSensitiveDetector("SensitiveDetector", false)){
    sensDet = SDman->FindSensitiveDetector("SensitiveDetector", false);
  }
  else{
    sensDet = new sens_det("SensitiveDetector");
    SDman->AddNewDetector(sensDet);
  }
  logicDetector->SetSensitiveDetector(sensDet);

  if(SDman->FindSensitiveDetector("WaterSensitiveDetector", false)){
      waterSens = SDman->FindSensitiveDetector("WaterSensitiveDetector", false);
  }
  else{
    waterSens = new water_sensitive("WaterSensitiveDetector");
    SDman->AddNewDetector(waterSens);
  }
  logicWater->SetSensitiveDetector(waterSens);


}
