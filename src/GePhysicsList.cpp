/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#include "GePhysicsList.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"

GePhysicsList::GePhysicsList()
  : G4VModularPhysicsList()
{
  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());
  RegisterPhysics(new G4EmStandardPhysics());
}


GePhysicsList::~GePhysicsList(){}


void GePhysicsList::SetCuts()
{
  G4VUserPhysicsList::SetCuts();
}