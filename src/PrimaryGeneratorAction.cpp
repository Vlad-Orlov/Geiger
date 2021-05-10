/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#include "PrimaryGeneratorAction.hh"

// Now to create some events in our world
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ThreeVector.hh"
#include "G4Geantino.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

/* We'll use the Geantino (non-interacting particle) for the gun, can be changed. 
 * This particle is generally used for testing. Think of it as similar to a neutrino. 
 *
 * In our gun design all particles will fire from a stationary spot
 * */
PrimaryGeneratorAction::PrimaryGeneratorAction()
{
   G4int n_particle = 1;   // Number of particles fired per beamOn run
   particleGun = new G4ParticleGun(n_particle);  // creation of particle gun

   particleGun -> SetParticleDefinition(G4Geantino::GeantinoDefinition()); // Use Geantino as firing particle
   // 1GeV energy of gun, this can be changed from the command line
   particleGun -> SetParticleEnergy(1.0 * GeV);  
   particleGun -> SetParticlePosition(G4ThreeVector(-1.*m, 0.*m, 0.*m));   // Set gun to be at furthest x in world (far left to standard orientation)
}

// Create destructor
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
   delete particleGun;
}

// Primary event
void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
   particleGun -> SetParticleMomentumDirection(G4ThreeVector(1.0,0.,0.));  // Pure x momentum
 
   particleGun -> GeneratePrimaryVertex(anEvent);  // creates the initial momentum
}