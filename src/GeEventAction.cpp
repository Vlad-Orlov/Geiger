/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#include "GeEventAction.hh"

#include "G4RunManager.hh"

#include "g4root.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include <vector>
using namespace std;

GeEventAction::GeEventAction() : G4UserEventAction(){}


void GeEventAction::BeginOfEventAction( const G4Event*)
{ 
    G4cout << "\n---> Begin of Event: " << G4RunManager::GetRunManager()->
    GetCurrentEvent()->GetEventID() << G4endl;
}


void GeEventAction::EndOfEventAction( const G4Event*)
{                          
  
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    G4int eventNumber = G4RunManager::GetRunManager()->
                                              GetCurrentEvent()->GetEventID();
}

GeEventAction::~GeEventAction(){}




