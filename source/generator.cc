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
    m_particleGun->SetParticleEnergy(0.2*GeV);
    m_particleGun->SetParticlePosition(G4ThreeVector(30*cm,0,1.1*m));
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
        //Randomly sample energies from a uniform distribution
        G4double minEnergy = 0.03*GeV;
        G4double maxEnergy = 1*GeV;
        G4double energy = G4UniformRand() * (maxEnergy - minEnergy) + minEnergy;
        m_particleGun->SetParticleEnergy(energy);

        //Position
        G4double rad = 1.*m;
        G4double rad_real = 0.4*m;
        G4double x,y;
        G4double theta=0.0;
        G4double phi=0.0;
        G4double sintheta, sinphi,costheta,cosphi, Phi, MaxPhi, MinPhi, MaxTheta, MinTheta,px,py,pz;
        G4double ax,bx,cx,t1,t2,disc;
        x=0.1*m; y=0.1*m;
        MaxPhi = 2.*M_PI;
        MinPhi = 0.;
        MaxTheta = M_PI/2.;
        MinTheta = 0.;
        px=py=pz=t1=t2=0;
        G4bool check=false;
        x=rad+100.;    y=rad+100.;
  
        while(std::sqrt((x*x)+(y*y)) > rad){
            x = G4UniformRand();
            y = G4UniformRand();

            x=(x*2.*rad)-rad;
            y=(y*2.*rad)-rad;
        }
        m_particleGun->SetParticlePosition(G4ThreeVector(x,y,1.1*m));


        while(check == false){
            theta = G4UniformRand();
            phi = G4UniformRand();
    
            sintheta = std::sqrt( theta * (std::sin(MaxTheta)*std::sin(MaxTheta) - std::sin(MinTheta)*std::sin(MinTheta) ) + std::sin(MinTheta)*std::sin(MinTheta) );
            costheta = std::sqrt(1.-sintheta*sintheta);
    
            Phi = MinPhi + (MaxPhi - MinPhi) * phi; 
            sinphi = std::sin(Phi);
            cosphi = std::cos(Phi);
    
            px = -sintheta * cosphi;
            py = -sintheta * sinphi;
            pz = -costheta;
    
            if(px==0 && py==0){
                if(std::sqrt(x*x + y*y)>=rad_real){
                    check = false;
                }
                else{
                    check=true;
                }
            }
    
            else{
                ax=px*px + py*py;
                bx=2.*(px*x + py*y);
                cx= x*x + y*y - rad_real*rad_real;
                disc= bx*bx - 4*ax*cx;
      
                if (  disc >= 0){
                    t1 = (-bx + std::sqrt(disc))/(2.*ax);
                    t2 = (-bx - std::sqrt(disc))/(2.*ax);
        
                    if ( (((1.7*m + pz*t1) < 1.65*m) && ((1.7*m + pz*t1) > -1.65*m)) || (((1.7*m + pz*t2) < 1.65*m) && ((1.7*m + pz*t2) > -1.65*m)) ){
                        check = true;
                    }
                    else{
                        check = false;
                    }
                }
    
                else{
                    check=false;
                }
            }
        }
    
        m_particleGun->SetParticleMomentumDirection(G4ThreeVector(px,py,pz));
        m_particleGun->GeneratePrimaryVertex(anEvent);
    }

    else{
        gps->GeneratePrimaryVertex(anEvent);    
    }
}
