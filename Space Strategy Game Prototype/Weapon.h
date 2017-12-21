//***************************************************************************************************************************************************
//
// File Name: BattleMap.h
//
// Description:
//  TODO: Add file description.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     12/04/2017     Initial implementation for the battle map class. Added in loading battle map information, drawing a
//                                      portion of the graphics, and movement inital movement selection of a ship.
//
//***************************************************************************************************************************************************

#ifndef Weapon_H
#define Weapon_H

#include "Graphics.h"
#include "Sprite.h"

class Weapon
{
   //************************************************************************************************************************************************
   // Start Method Declarations
   //************************************************************************************************************************************************

public:

   //************************************************************************************************************************************************
   //
   // Method Name: Weapon
   //
   // Description:
   //  Constructor that sets member variables to default values.
   //
   // Arguments:
   //  theGraphics - TODO: Add description.
   //  theImageFileName - TODO: Add description.
   //  theMinimumRange - TODO: Add description.
   //  theMaximumRange - TODO: Add description.
   //  theDamage - TODO: Add description.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   Weapon(Graphics& theGraphics, std::string theImageFileName, int theMinimumRange, int theMaximumRange, int theDamage);

   //************************************************************************************************************************************************
   //
   // Method Name: GetMinimumRange
   //
   // Description:
   //  TODO: Add description
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   int GetMinimumRange();

   //************************************************************************************************************************************************
   //
   // Method Name: GetMaximumRange
   //
   // Description:
   //  TODO: Add description
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   int GetMaximumRange();

   //************************************************************************************************************************************************
   //
   // Method Name: GetDamage
   //
   // Description:
   //  TODO: Add description
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   int GetDamage();

   void Draw(Graphics& theGraphics, int theColumn, int theRow);

protected:

   // There are currently no protected methods for this class.

private:

   // There are currently no private methods for this class.

   //************************************************************************************************************************************************
   // End Method Declarations
   //************************************************************************************************************************************************

   //************************************************************************************************************************************************
   // Start Member Vairable Declarations
   //************************************************************************************************************************************************

public:

   // There are currently no public member variables for this class.

protected:

   // There are currently no protected member variables for this class.

private:

   int mMinimumRange;

   int mMaximumRange;

   int mDamage;

   Sprite* mpImage;

   //************************************************************************************************************************************************
   // End Member Vairable Declarations
   //************************************************************************************************************************************************
};

#endif