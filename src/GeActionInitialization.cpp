/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#include "GeActionInitialization.hh"

#include "GeEventAction.hh"
#include "GePrimaryGeneratorAction.hh"
#include "GeRunAction.hh"
#include "GeSteppingAction.hh"


GeActionInitialization::GeActionInitialization() : G4VUserActionInitialization(){}

GeActionInitialization::~GeActionInitialization(){}


void GeActionInitialization::BuildForMaster() const
{
  SetUserAction(new GeRunAction());
}


void GeActionInitialization::Build() const
{
    SetUserAction(new GePrimaryGeneratorAction());
    SetUserAction(new GeRunAction());
      	GeEventAction* eventAction = new GeEventAction;
        SetUserAction(eventAction);
        SetUserAction(new GeSteppingAction(eventAction));
}