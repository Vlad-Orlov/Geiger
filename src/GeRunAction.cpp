/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#include "G4Timer.hh"

#include "GeRunAction.hh"
#include "GeDetectorConstruction.hh"
#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"
#include "Randomize.hh"
#include "G4HCofThisEvent.hh"

#include "GeEventAction.hh"

GeRunAction::GeRunAction() : G4UserRunAction(), fTimer(0)
{
  fTimer = new G4Timer;
  // automatic (time-based) random seeds for each run
     G4cout << "*******************" << G4endl;
     G4cout << "*** AUTOSEED ON ***" << G4endl;
     G4cout << "*******************" << G4endl;
     long seeds[1];
     time_t systime = time(NULL);
     //seeds[0] = (long) systime;
     G4Random::showEngineStatus();

     // Create analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetNtupleMerging(true);
    analysisManager->SetFileName("Geiger");
        
    analysisManager->CreateNtuple("Cathode","Cathode");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("rho");
    analysisManager->CreateNtupleDColumn("phi"); 
    analysisManager->CreateNtupleDColumn("u"); 
    analysisManager->CreateNtupleDColumn("E");
    analysisManager->FinishNtuple(0);

    analysisManager->CreateNtuple("Anode","Anode");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("rho");
    analysisManager->CreateNtupleDColumn("phi");
    analysisManager->CreateNtupleDColumn("u");  
    analysisManager->CreateNtupleDColumn("E");
    analysisManager->FinishNtuple(1);

    analysisManager->CreateNtuple("Gas","Gas");
    analysisManager->CreateNtupleDColumn("x");
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("rho");
    analysisManager->CreateNtupleDColumn("phi"); 
    analysisManager->CreateNtupleDColumn("u"); 
    analysisManager->CreateNtupleDColumn("E");
    analysisManager->FinishNtuple(2);
}


GeRunAction::~GeRunAction()
{
  delete fTimer;
}


void GeRunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
    fTimer->Start();

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile();
}


void GeRunAction::EndOfRunAction(const G4Run* aRun)
{
    fTimer->Stop();
    G4cout << "number of event = " << aRun->GetNumberOfEvent()
           << " " << *fTimer << G4endl;

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}

