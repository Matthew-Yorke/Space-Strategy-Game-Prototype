//*************************************************************************************************
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
//*************************************************************************************************

#ifndef Ship_h
#define Ship_h

#include <string>
#include "Crew.h"

class Ship
{
   //**********************************************************************************************
   //                                   Start Method Declarations
   //**********************************************************************************************

public:

   //*******************************************************************************************
   //
   // Method Name: Ship
   //
   // Description:
   //  Ship constructor that sets member variables to default values.
   //
   // Arguments:
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
   //*******************************************************************************************
   Ship(bool theIsManuverable, int theMovementDistance, int theNumberOfSmallWeapons, int theNumberOfMediumWeapons,
        int theNumberOfLargeWeapons);

   //*******************************************************************************************
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
   //*******************************************************************************************
   void SetManuverable(bool theIsManuverable);

   //*******************************************************************************************
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
   //*******************************************************************************************
   void SetCrew(Crew* theCrew);

   //*******************************************************************************************
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
   //*******************************************************************************************
   void MoveShip();

protected:

private:

   //**********************************************************************************************
   //                                    End Method Declarations
   //**********************************************************************************************

   //**********************************************************************************************
   //                                Start Member Vairable Declarations
   //**********************************************************************************************

public:
   // A pointer that holds the image of the ship.
   ALLEGRO_BITMAP* mShipImage;

   // The maximum number of movement a ship can perform.
   int mMovementDistance;

   int mShipTileColumn;

   int mShipTileRow;

protected:

private:

   // Determines if movement used to turn the ship (False) or not (True).
   bool mIsManuverable;

   

   // An array that is the size of the number of small weapon types the ship can be equipped with.
   // This array size is declared upon creation of this class.
   // SmallWeapons* mSmallWeapons;

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

   //**********************************************************************************************
   //                                 End Member Vairable Declarations
   //**********************************************************************************************
};

#endif