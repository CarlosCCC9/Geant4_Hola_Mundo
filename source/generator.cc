#include "generator.hh"

generator::generator(){

    //Modificar el proyecto luego de compilado
    fMessenger = new G4GenericMessenger(this, "/generator/", "Primary generator control");
  fMessenger->DeclareProperty("gun", gun, "Type of primary");

    gun=false;


    //Gun
    m_particleGun = new G4ParticleGun(1);

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
  
    m_particleGun->SetParticleDefinition(particle);
    m_particleGun->SetParticleEnergy(0.*GeV);
    m_particleGun->SetParticlePosition(G4ThreeVector(0,0,0.25*m));
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
        G4ParticleDefinition *particle = m_particleGun->GetParticleDefinition();

        if (particle == G4Geantino::Geantino()){
            G4int Z = 9;
            G4int A = 18;

            G4double charge = 0.*eplus;
            G4double energy = 0.*keV;

            G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z,A,energy);
            m_particleGun->SetParticleDefinition(ion);
            m_particleGun->SetParticleCharge(charge);   
        }

        m_particleGun->GeneratePrimaryVertex(anEvent);
    }

    else{
        gps->GeneratePrimaryVertex(anEvent);    
    }
}
