/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#pragma once

#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;
class G4Event;

class GePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    GePrimaryGeneratorAction();
    virtual ~GePrimaryGeneratorAction();
    virtual void GeneratePrimaries(G4Event*);

    const G4ParticleGun* GetParticleGun() const { return fParticleGun;}
    

  private:
    G4ParticleGun* fParticleGun;

};