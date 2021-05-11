/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "GeDetectorConstruction.hh"
#include "GeActionInitialization.hh"
#include "GePhysicsList.hh"
#include "GePrimaryGeneratorAction.hh"

int main(int argc, char** argv)
{

	G4int nThreads = 5;

  	G4long myseed = 345354;


	G4UIExecutive* ui = nullptr;
	if ( argc == 1 ) {
		ui = new G4UIExecutive(argc, argv);
	}

	auto runManager = G4RunManagerFactory::CreateRunManager();

	#ifdef G4MULTITHREADED
	if(nThreads > 0) runManager->SetNumberOfThreads(nThreads);
	#endif

	// Seed the random number generator manually
	G4Random::setTheSeed(myseed);

    runManager->SetUserInitialization(new GeDetectorConstruction);
    runManager->SetUserInitialization(new GePhysicsList);
	runManager->SetUserInitialization(new GeActionInitialization());
    // runManager->SetUserAction(new GePrimaryGeneratorAction);
	runManager->Initialize();

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