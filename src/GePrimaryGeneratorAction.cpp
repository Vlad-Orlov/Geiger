/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#include "GePrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"


GePrimaryGeneratorAction::GePrimaryGeneratorAction()
{
  G4int n_particle = 1;
  fParticleGun = new G4GeneralParticleSource();

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "gamma";
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,5.*cm,0.));
}


GePrimaryGeneratorAction::~GePrimaryGeneratorAction()
{
   delete fParticleGun;
}

// Primary event
void GePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{ 
   fParticleGun->GeneratePrimaryVertex(anEvent);
}