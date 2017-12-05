//*************************************************************************************************
//
// File Name: PlayerInventories.h
//
// Description:
//  TODO: Add file description.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     MM/DD/YYYY     TODO: Add history update
//
//*************************************************************************************************

#ifndef PlayerInventories_h
#define PlayerInventories_h

#include <vector>
#include "Ship.h"
#include "Crew.h"

class PlayerInventories
{
   //**********************************************************************************************
   //                                   Start Method Declarations
   //**********************************************************************************************

public:

   //*******************************************************************************************
   //
   // Method Name: PlayerInventories
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //*******************************************************************************************
   PlayerInventories();

   //*******************************************************************************************
   //
   // Method Name: AddShip
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //*******************************************************************************************
   void AddShip();

   //*******************************************************************************************
   //
   // Method Name: RemoveShip
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //*******************************************************************************************
   void RemoveShip();

   //*******************************************************************************************
   //
   // Method Name: AddCrew
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //*******************************************************************************************
   void AddCrew();

   //*******************************************************************************************
   //
   // Method Name: RemoveCrew
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //*******************************************************************************************
   void RemoveCrew();

protected:

private:

   //**********************************************************************************************
   //                                    End Method Declarations
   //**********************************************************************************************

   //**********************************************************************************************
   //                                Start Member Vairable Declarations
   //**********************************************************************************************

public:

protected:

private:

   // The ships the player currently owns.
   std::vector<Ship*> mPlayerShip;

   // The crews the player currently commands.
   std::vector<Crew*> mPlayerCrews;

   //**********************************************************************************************
   //                                 End Member Vairable Declarations
   //**********************************************************************************************
};

#endif