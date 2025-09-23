#include "generator.hh"

generator::generator(){

    //Modificar el proyecto luego de compilado
    fMessenger = new G4GenericMessenger(this, "/generator/", "Primary generator control");
  fMessenger->DeclareProperty("gun", gun, "Type of primary");

    gun=true;


    //Gun
    m_particleGun = new G4ParticleGun(1);

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("mu-");
  
    m_particleGun->SetParticleDefinition(particle);
    m_particleGun->SetParticleEnergy(0.*GeV);
    m_particleGun->SetParticlePosition(G4ThreeVector(0,0,1.1*m));
    m_particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,-1));


    //General Source
    gps = new G4GeneralParticleSource();

}

generator::~generator(){ 
    delete m_particleGun;    
    delete gps;
}

void generator::GeneratePrimaries(G4Event *anEvent){

    if(gun){
        m_particleGun->GeneratePrimaryVertex(anEvent);
    }

    else{
        gps->GeneratePrimaryVertex(anEvent);    
    }
}
