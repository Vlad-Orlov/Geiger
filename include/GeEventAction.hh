/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#pragma once

#include "G4UserEventAction.hh"
#include "globals.hh"

class GeDetectorConstruction;

class GeEventAction : public G4UserEventAction
{
  public:
    GeEventAction();
   ~GeEventAction();
  public:
    virtual void BeginOfEventAction(const G4Event*);
    virtual void   EndOfEventAction(const G4Event*);

  private:

};
    
