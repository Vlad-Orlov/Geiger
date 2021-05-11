/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#pragma once

#include "G4UserSteppingAction.hh"
#include "globals.hh"

/// Stepping action class
class GeDetectorConstruction;
class GeEventAction;
class GeSteppingAction : public G4UserSteppingAction
{
  public:
    GeSteppingAction(GeEventAction*);
    virtual ~GeSteppingAction();

    virtual void UserSteppingAction(const G4Step*);

  private:

    G4int fEventNumber;

  private:
    GeEventAction* fEventAction;
     GeDetectorConstruction* Detector;

};
