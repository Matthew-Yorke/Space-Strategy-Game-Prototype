//***************************************************************************************************************************************************
//
// File Name: Ship.h
//
// Description:
//  TODO: Add file description.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     MM/DD/YYYY     TODO: Add history update
//
//***************************************************************************************************************************************************

#ifndef Ship_h
#define Ship_h

#include <string>
#include "Crew.h"
#include "Sprite.h"
#include "Weapon.h"

class Ship
{
   //************************************************************************************************************************************************
   // Start Method Declarations
   //************************************************************************************************************************************************

public:

   //************************************************************************************************************************************************
   //
   // Method Name: Ship
   //
   // Description:
   //  Ship constructor that sets member variables to default values.
   //
   // Arguments:
   //  theGraphics - TODO: Add description.
   //  theIsManuverable - Determines if the ship is classified manuverable and turning does not
   //                     require movement (True) or the ship is not manuverable and will cost
   //                     movement to turn the ship (False).
   //  theMovementDistance - The number of movement points the ship has.
   //  theNumberOfSmallWeapons  - The number of small weapon types this ship can equip.
   //  theNumberOfMediumWeapons - The number of medium weapon types this ship can equip.
   //  theNumberOfLargeWeapons - The number of large weapon types this ship can equip.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   Ship(Graphics& theGraphics, bool theIsManuverable, int theMovementDistance, int theNumberOfSmallWeapons, int theNumberOfMediumWeapons,
        int theNumberOfLargeWeapons);

   //************************************************************************************************************************************************
   //
   // Method Name: ~Ship
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
   //************************************************************************************************************************************************
   ~Ship();

   //************************************************************************************************************************************************
   //
   // Method Name: SetManuverable
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
   //************************************************************************************************************************************************
   void SetManuverable(bool theIsManuverable);

   //************************************************************************************************************************************************
   //
   // Method Name: SetCrew
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  theCrew - TODO: Add description of the argument.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void SetCrew(Crew* theCrew);

   //************************************************************************************************************************************************
   //
   // Method Name: SetTileColumn
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  theTileColumn - TODO: Add description.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void SetTileColumn(int theTileColumn);

   //************************************************************************************************************************************************
   //
   // Method Name: SetTileRow
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  theTileRow - TODO: Add description.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void SetTileRow(int theTileRow);

   //************************************************************************************************************************************************
   //
   // Method Name: AddWeapon
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  thepWeapon - TODO: Add description.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void AddWeapon(Weapon* thepWeapon);

   //************************************************************************************************************************************************
   //
   // Method Name: MoveShip
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
   //************************************************************************************************************************************************
   void MoveShip();

   //************************************************************************************************************************************************
   //
   // Method Name: ResetActionLevel
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
   //************************************************************************************************************************************************
   void ResetActionLevel();

   //************************************************************************************************************************************************
   //
   // Method Name: IncrementActionLevel
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
   //************************************************************************************************************************************************
   void IncrementActionLevel();
   
   //************************************************************************************************************************************************
   //
   // Method Name: GetActionLevel
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  TODO: Add method description.
   //
   //************************************************************************************************************************************************
   int GetActionLevel();

   //************************************************************************************************************************************************
   //
   // Method Name: GetMovementDistance
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   // TODO: Add method description.
   //
   //************************************************************************************************************************************************
   int GetMovementDistance();

   //************************************************************************************************************************************************
   //
   // Method Name: GetTileColumn
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  TODO: Add method description.
   //
   //************************************************************************************************************************************************
   int GetTileColumn();

   //************************************************************************************************************************************************
   //
   // Method Name: GetTileRow
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  TODO: Add method description.
   //
   //************************************************************************************************************************************************
   int GetTileRow();

   int GetWeaponMinimumRange();

   int GetWeaponMaximumRange();

   int GetWeaponDamage();

   //************************************************************************************************************************************************
   //
   // Method Name: Draw
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  theGraphics - TODO: Add description.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void Draw(Graphics& theGraphics);

   int GetCurrentHealth();

   void TakeDamage(int theDamage);

protected:

private:

   //************************************************************************************************************************************************
   // End Method Declarations
   //************************************************************************************************************************************************

   //************************************************************************************************************************************************
   // Start Member Vairable Declarations
   //************************************************************************************************************************************************

public:

   // TODO: These will need to be moved to the weapons classes and retrieved.
   int mMinimumAttackDistance;
   int mMaximumAttackDistance;

protected:

private:

   // The maximum number of movement a ship can perform.
   int mMovementDistance;

   // A pointer that holds the image of the ship.
   Sprite* mpShipImage;

   // Determines if movement used to turn the ship (False) or not (True).
   bool mIsManuverable;

   // An array that is the size of the number of small weapon types the ship can be equipped with.
   // This array size is declared upon creation of this class.
   // SmallWeapons* mSmallWeapons;
   Weapon* mpWeapon;

   // An array that is the size of the number of medium weapon types the ship can be equipped with.
   // This array size is declared upon creation of this class.
   // MediumWeapons* mMediumWeapons;

   // An array that is the size of the number of large weapon types the ship can be equipped with.
   // This array size is declared upon creation of this class.
   // LargeWeapons* mLargeWeapons;

   // Holds the armor assigned to this ship.
   // Armor mShipArmor;

   // Pointer to the crew that is assigned to this ship.
   Crew* mCrew;

   // Holds a string describing the ship type.
   std::string mShipType;

   // Holds a string of the ships name.
   std::string mShipName;

   // The minimum number of crew members needed to be assigned to this ship.
   int mMinimumCrewSize;

   // The maximum number of crew members that can be assigned to the ship positions.
   int mMaximumCrewSize;

   // Holds the number of crew members assigned to be pilots.
   int mNumberOfPilots;

   // Hold the number of crew members assigned to be gunners, this effects weapon capabilities.
   int mNumberOfGunners;

   // Holds the number of crew members assigned to be engineers, this effects ship defenses and manuverability.
   int mNumberOfEngineers;

   int mActionSpeed;
   int mActionLevel;

   int mShipTileColumn;

   int mShipTileRow;

   int mCurrentHealth;

   //************************************************************************************************************************************************
   // End Member Vairable Declarations
   //************************************************************************************************************************************************
};

#endif