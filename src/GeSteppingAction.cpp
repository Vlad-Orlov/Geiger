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
    

    // Only info about electrons gets recorded
    if( ParticleName != "e-") return;


    // Electrons that are born in cathode and go into the gas volume
    if(prephysvolname == "geigerTube" && postphysvolname == "gas")
    {   
        G4double x, y, z, rho, phi, u, E;
        x = aStep->GetPostStepPoint()->GetPosition().getX();
        y = aStep->GetPostStepPoint()->GetPosition().getY();
        z = aStep->GetPostStepPoint()->GetPosition().getZ();
        rho = sqrt(x*x + y*y);
        phi = aStep->GetPostStepPoint()->GetPosition().getPhi();
        u = 11.*phi*mm;
        E = track->GetKineticEnergy();

        analysisManager->FillNtupleDColumn(0,0, x/mm);
        analysisManager->FillNtupleDColumn(0,1, y/mm);
        analysisManager->FillNtupleDColumn(0,2, z/mm);
        analysisManager->FillNtupleDColumn(0,3, rho/mm);
        analysisManager->FillNtupleDColumn(0,4, phi/deg);
        analysisManager->FillNtupleDColumn(0,5, u/mm);
        analysisManager->FillNtupleDColumn(0,6, E/keV);

        analysisManager->AddNtupleRow(0);
        track->SetTrackStatus(fStopAndKill);
    }

    // Electrons that are born in anode wire and go to the gas volume
    if(prephysvolname == "anodeTube" && postphysvolname == "gas")
    {   
        G4double x, y, z, rho, phi, u, E;
        x = aStep->GetPostStepPoint()->GetPosition().getX();
        y = aStep->GetPostStepPoint()->GetPosition().getY();
        z = aStep->GetPostStepPoint()->GetPosition().getZ();
        rho = sqrt(x*x + y*y);
        phi = aStep->GetPostStepPoint()->GetPosition().getPhi();
        u = 1.*phi*mm;
        E = track->GetKineticEnergy();

        analysisManager->FillNtupleDColumn(1,0, x/mm);
        analysisManager->FillNtupleDColumn(1,1, y/mm);
        analysisManager->FillNtupleDColumn(1,2, z/mm);
        analysisManager->FillNtupleDColumn(1,3, rho/mm);
        analysisManager->FillNtupleDColumn(1,4, phi/deg);
        analysisManager->FillNtupleDColumn(1,5, u/mm);
        analysisManager->FillNtupleDColumn(1,6, E/keV);

        analysisManager->AddNtupleRow(1);
        track->SetTrackStatus(fStopAndKill);
    }

    // Electrons that are born in gas volume itself
    if(prephysvolname == "gas" && postphysvolname == "gas")
    {   
        G4double x, y, z, rho, phi, u, E;
        x = aStep->GetPostStepPoint()->GetPosition().getX();
        y = aStep->GetPostStepPoint()->GetPosition().getY();
        z = aStep->GetPostStepPoint()->GetPosition().getZ();
        rho = sqrt(x*x + y*y);
        phi = aStep->GetPostStepPoint()->GetPosition().getPhi();
        u = 11.*phi*mm;
        E = track->GetKineticEnergy();

        analysisManager->FillNtupleDColumn(2,0, x/mm);
        analysisManager->FillNtupleDColumn(2,1, y/mm);
        analysisManager->FillNtupleDColumn(2,2, z/mm);
        analysisManager->FillNtupleDColumn(2,3, rho/mm);
        analysisManager->FillNtupleDColumn(2,4, phi/deg);
        analysisManager->FillNtupleDColumn(2,5, u/mm);
        analysisManager->FillNtupleDColumn(2,6, E/keV);

        analysisManager->AddNtupleRow(2);
        track->SetTrackStatus(fStopAndKill);
    }




}



