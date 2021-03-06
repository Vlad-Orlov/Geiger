/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#pragma once

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

// These two classes are called within the construct function
class G4VPhysicalVolume;
class G4LogicalVolume;

class GeDetectorConstruction : public G4VUserDetectorConstruction
{
   public:
      GeDetectorConstruction();
      virtual ~GeDetectorConstruction();
      virtual G4VPhysicalVolume* Construct();

   private:
      void DefineMaterials();
};