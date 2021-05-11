/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#include "GeSteppingAction.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include <cmath>
#include "g4root.hh"
#include "G4Step.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "GeDetectorConstruction.hh"
#include "G4VSolid.hh"
#include <vector>
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "GeEventAction.hh"

GeSteppingAction::GeSteppingAction(GeEventAction* EvAct):G4UserSteppingAction(),fEventAction(EvAct)
{
  fEventNumber = -1;
}


GeSteppingAction::~GeSteppingAction()
{ ; }


void GeSteppingAction::UserSteppingAction(const G4Step* aStep)
{
    G4int eventNumber = G4RunManager::GetRunManager()->
                                              GetCurrentEvent()->GetEventID();

    if (eventNumber != fEventNumber)
    {
        fEventNumber = eventNumber;
    }
  

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    G4String ParticleName = aStep->GetTrack()->GetDynamicParticle()->
                                  GetParticleDefinition()->GetParticleName();
      


    G4Track* track = aStep->GetTrack();

    G4int stepnum=track->GetCurrentStepNumber();
    G4int parentid=track -> GetParentID();


    G4int trackid = track -> GetTrackID();


    G4VPhysicalVolume* postvolumephys = NULL;
    postvolumephys = aStep->GetPostStepPoint()->GetPhysicalVolume();
    if(!postvolumephys) return;
    G4String postphysvolname = postvolumephys->GetName();

    G4int post_copynum = postvolumephys->GetCopyNo();


    G4VPhysicalVolume* prevolumephys = NULL;
    prevolumephys = aStep->GetPreStepPoint()->GetPhysicalVolume();
    G4String prephysvolname = prevolumephys->GetName();
    

    if(postphysvolname == "gas")
    {
        analysisManager->FillNtupleDColumn(0,0, 
                                    aStep->GetPostStepPoint()->GetPosition().getX());
        analysisManager->FillNtupleDColumn(0,1, 
                                    aStep->GetPostStepPoint()->GetPosition().getY());
        analysisManager->FillNtupleDColumn(0,2, 
                                    aStep->GetPostStepPoint()->GetPosition().getZ());


        analysisManager->AddNtupleRow(0);
        track->SetTrackStatus(fStopAndKill);
    }



    // }

}



