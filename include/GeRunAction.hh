/*########################################################*\ 
|* author: vlad orlov        May 2021                     *|
\*########################################################*/

#pragma once

#include "globals.hh"
#include "G4UserRunAction.hh"

class G4Timer;
class G4Run;

class GeRunAction : public G4UserRunAction
{
    public:
        GeRunAction();
        virtual ~GeRunAction();

    public:
        virtual void BeginOfRunAction(const G4Run* aRun);
        virtual void EndOfRunAction(const G4Run* aRun);

    private:
        G4Timer* fTimer;
};