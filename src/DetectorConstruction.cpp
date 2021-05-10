/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#include "DetectorConstruction.hh"
#include "G4NistManager.hh"         
#include "G4Box.hh"
#include "G4Tubs.hh"                
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"        
#include "G4RotationMatrix.hh"      
#include "G4Transform3D.hh"         
#include "G4PhysicalConstants.hh"   
#include "G4SystemOfUnits.hh"

DetectorConstruction::DetectorConstruction() : G4VUserDetectorConstruction() 
{
   DefineMaterials(); 
}

DetectorConstruction::~DetectorConstruction(){} 


void DetectorConstruction::DefineMaterials()
{
   G4NistManager* man = G4NistManager::Instance(); 
   G4bool isotopes = false;

   G4Element* H = man->FindOrBuildElement("H", isotopes);
   G4Element* O = man->FindOrBuildElement("O", isotopes);
   
   G4Material* H2O = new G4Material("Water" ,1.000 * g/cm3, 2);            
 
   H2O->AddElement(H, 2);  
   H2O->AddElement(O, 1);
   
   G4Element* N = man->FindOrBuildElement("N", isotopes);
   G4double density = 1.290 * mg/cm3;
   G4Material* Air = new G4Material("Air", density, 2);
   Air->AddElement(N, 70*perCent);
   Air->AddElement(O, 30*perCent);
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
  
   G4NistManager* nist = G4NistManager::Instance();

   G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
   G4Material* tube_mat = nist->FindOrBuildMaterial("G4_STEEL");


   G4double worldSize = 1 * m;

   G4Box* worldSol = new G4Box("World", worldSize, worldSize, worldSize);
   G4LogicalVolume* worldLog = new G4LogicalVolume(worldSol, world_mat, "World");
   G4VPhysicalVolume* worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLog, "World", 0, false, 0);


   G4double detLength = 197.*mm;

   G4Tubs* detTubeSol = new G4Tubs("geigerTube", 10*mm, 12*mm, detLength/2., 0, 360*deg);
   G4LogicalVolume* detTubeLog = new G4LogicalVolume(detTubeSol, tube_mat, "geigerTube");
   G4VPhysicalVolume* detTubePhys = new G4PVPlacement(0,                 
                                                      G4ThreeVector(), 
                                                      detTubeLog,      
                                                      "geigerTube",      
                                                      worldLog,         
                                                      false,             
                                                      0);


   G4Tubs* anodeTubeSol = new G4Tubs("anodeTube", 0*mm, 1*mm, detLength/2., 0, 360*deg);
   G4LogicalVolume* anodeTubeLog = new G4LogicalVolume(anodeTubeSol, tube_mat, "anodeTube");
   G4VPhysicalVolume* anodeTubePhys = new G4PVPlacement(0,                 
                                                      G4ThreeVector(), 
                                                      anodeTubeLog,      
                                                      "anodeTube",      
                                                      worldLog,         
                                                      false,             
                                                      0);                
   
   return worldPhys;
}