#include "generator.hh"

generator::generator(){

    //Modificar el proyecto luego de compilado
    fMessenger = new G4GenericMessenger(this, "/generator/", "Primary generator control");
  fMessenger->DeclareProperty("deg", deg, "Incidence of primary");

    deg=1;

    //Gun
    m_particleGun = new G4ParticleGun(1);

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("mu-");
  
    m_particleGun->SetParticleDefinition(particle);
    m_particleGun->SetParticleEnergy(0.2*GeV);
    m_particleGun->SetParticlePosition(G4ThreeVector(30*cm,0,1.1*m));
    m_particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,-1));

    //Initialize the energy array to zero
    for(G4int i=0; i<4173; i++){
        nrg[i] = 0;
    }

    //Read energy sampling file
    std::ifstream datafile;
    datafile.open("filtered_energies.dat");
    G4int i = 0;
    while(1){
        G4double energy;
        datafile >> energy;
        if(datafile.eof())
            break;
        nrg[i] = energy;
        i++;
    }
    datafile.close();

}

generator::~generator(){ 
    delete m_particleGun;    
}

void generator::GeneratePrimaries(G4Event *anEvent){

        //Randomly sample an energy from the array
        G4int index = G4UniformRand() * 4174;
        if(index >= 4174) index = 4173;
        G4double energy = nrg[index];
        //Set the particle energy
        m_particleGun->SetParticleEnergy(energy*GeV);

        //Nrg random between 0.03 and 1 GeV
        /*
        G4double minEnergy = 0.03*GeV;
        G4double maxEnergy = 1*GeV;
        G4double energy = G4UniformRand() * (maxEnergy - minEnergy) + minEnergy;
        m_particleGun->SetParticleEnergy(energy);
        */

        //Position
        G4double rad = 1.*m;
        G4double rad_real = 0.5*77*cm;
        G4double x,y;
        G4double theta=0.0;
        G4double phi=0.0;
        G4double sintheta, sinphi,costheta,cosphi, Phi, MaxPhi, MinPhi, MaxTheta, MinTheta,px,py,pz;
        G4double ax,bx,cx,t1,t2,disc;
        G4double z_ini=0.6*m;
        G4double tankh_half=0.5*m;

        x=0.1*m; y=0.1*m;
        MaxPhi = 2.*M_PI;
        MinPhi = 0.;
        MaxTheta = M_PI/2.;
        MinTheta = 0.;
        px=py=pz=t1=t2=0;
        G4bool check=false;
        
        switch(deg){

            case 0:

                x=rad_real+100.;
                y=rad_real+100.;
    
                while(std::sqrt((x*x)+(y*y)) > rad_real){
                    x = G4UniformRand();
                    y = G4UniformRand();
  
                    x=(x*2.*rad_real)-rad_real;
                    y=(y*2.*rad_real)-rad_real;
                }
  
                m_particleGun->SetParticlePosition(G4ThreeVector(x,y,z_ini));
                m_particleGun->SetParticleMomentumDirection(G4ThreeVector(0,0,-1));
  
                break;

            case 1:
                x=rad+100.;    y=rad+100.;
                while(std::sqrt((x*x)+(y*y)) > rad){
                    x = G4UniformRand();
                    y = G4UniformRand();

                    x=(x*2.*rad)-rad;
                    y=(y*2.*rad)-rad;
                }
                G4cout<<"x: "<<x<<" y: "<<y<<" nrg: "<<energy<<G4endl;
                m_particleGun->SetParticlePosition(G4ThreeVector(x,y,z_ini));

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

                            if ( (((z_ini + pz*t1) < tankh_half) && ((z_ini + pz*t1) > -tankh_half)) || (((z_ini + pz*t2) < tankh_half) && ((z_ini + pz*t2) > -tankh_half)) ){
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
                break;
        default:
            G4cerr<<"Invalid angle option"<<G4endl;
        
        }

    m_particleGun->GeneratePrimaryVertex(anEvent);

}
