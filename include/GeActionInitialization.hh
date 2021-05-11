/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#pragma once

#include "G4VUserActionInitialization.hh"


class GeActionInitialization : public G4VUserActionInitialization
{
  public:
    GeActionInitialization();
    virtual ~GeActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

