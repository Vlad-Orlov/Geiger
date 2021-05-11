/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "gamma";
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,5.*cm,0.));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(661.2*keV);
}


PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
   delete fParticleGun;
}

// Primary event
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
   fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,-1.0,0.));
 
   fParticleGun->GeneratePrimaryVertex(anEvent);
}