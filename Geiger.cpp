#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"

int main(int argc, char** argv)
{

	G4UIExecutive* ui = 0;
	if ( argc == 1 ) {
	ui = new G4UIExecutive(argc, argv);
	}

    auto* runManager = new G4RunManager;
    // G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

    runManager->SetUserInitialization(new DetectorConstruction);
    runManager->SetUserInitialization(new PhysicsList);
    runManager->SetUserAction(new PrimaryGeneratorAction);


    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();


    G4UImanager* UImanager = G4UImanager::GetUIpointer();

	if ( ! ui ) { 
		// batch mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
	else { 
		// interactive mode
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}


    delete visManager; 
    delete runManager;

    return 0;
}