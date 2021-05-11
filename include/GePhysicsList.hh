/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#pragma once

#include "G4VModularPhysicsList.hh"

class GePhysicsList : public G4VModularPhysicsList
{
  public:
    GePhysicsList();
    ~GePhysicsList();
    
    virtual void SetCuts();

};
