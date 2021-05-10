#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"

int main(int argc, char** argv)
{
 
  G4RunManager* runManager = new G4RunManager;

  G4VisManager* visManager = VisManager;
  visManager -> initialize();

  runManager -> SetUserInitialization(new DetectorConstruction);
  runManager -> SetUserInitialization(new PhysicsList);

  runManager -> SetUserAction(new PrimaryGeneratorAction);

  runManager -> Initialize();

  G4UImanager* UI = G4UImanager::GetUIpointer();
  UI -> ApplyCommand("/run/verbose 1");
  UI -> ApplyCommand("/event/verbose 1");
  UI -> ApplyCommand("/tracking/verbose 1");

  int numberOfEvents = 3;
  runManager -> BeamOn(numberOfEvents);

  delete runManager;
  delete visManager; 

  return 0;
}