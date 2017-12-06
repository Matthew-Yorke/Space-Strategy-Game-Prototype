//*************************************************************************************************
//
// File Name: Ship.cpp
//
// Description:
//  TODO: Add file description.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     MM/DD/YYYY     TODO: Add history update
//
//*************************************************************************************************

#include "stdio.h"
#include "allegro5\allegro.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Ship.h"

//*************************************************************************************************
//                                  Start Public Method Definitions
//*************************************************************************************************

//*******************************************************************************************
//
// Method Name: Ship
//
// Description:
//  Constructs the ship object by setting the member vairables to default values.
//
//*******************************************************************************************
Ship::Ship(bool theIsManuverable, int theMovementDistance, int theNumberOfSmallWeapons, int theNumberOfMediumWeapons,
           int theNumberOfLargeWeapons)
{
   // Set if the ship is manuverable with the passed in value.
   mIsManuverable = theIsManuverable;

   // Set the maximum movement distance with the passed in value.
   mMovementDistance = theMovementDistance;

   // Set the crew assigned to the ship to initially be null (no crew assigned).
   mCrew = nullptr;

   // Test Code - Update later.
   mShipImage = al_load_bitmap("C:/Users/matt/Documents/Visual Studio 2017/Projects/Space Strategy Game Prototype/Space Strategy Game Prototype/Images/Spaceship_1.png");
   al_convert_mask_to_alpha(mShipImage, al_map_rgb(255, 0, 255));

   // Set the array size.
   //mSmallWeapons = new SmallWeapons[theNumberOfSmallWeapons];
   //mMediumWeapons = new MediumWeapons[theNumberOfMediumWeapons];
   //mLargeWeapons = new LargeWeapons[theNumberOfLargeWeapons];

   // Temp Code Below
   mShipTileColumn = 4;
   mShipTileRow = 4;

   mActionSpeed = 5;
   mActionLevel = 0;
}

//*******************************************************************************************
//
// Method Name: SetManuverable
//
// Description:
//  Set any change in the ships manuverability.
//
//*******************************************************************************************
void Ship::SetManuverable(bool theIsManuverable)
{
   mIsManuverable = theIsManuverable;
}

//*******************************************************************************************
//
// Method Name: SetCrew
//
// Description:
//  Set any change in the ships manuverability.
//
//*******************************************************************************************
void Ship::SetCrew(Crew* theCrew)
{
   mCrew = theCrew;
}

//*******************************************************************************************
//
// Method Name: MoveShip
//
// Description:
//  TODO: Add method description.
//
//*******************************************************************************************
void Ship::MoveShip()
{
}

void Ship::ResetActionLevel()
{
   mActionLevel = 0;
}

void Ship::IncrementActionLevel()
{
   mActionLevel += mActionSpeed;
}

int Ship::GetActionLevel()
{
   return mActionLevel;
}

//*************************************************************************************************
//                                   End Public Method Definitions
//*************************************************************************************************

//*************************************************************************************************
//                                 Start Protected Method Definitions
//*************************************************************************************************



//*************************************************************************************************
//                                  End Protected Method Definitions
//*************************************************************************************************

//*************************************************************************************************
//                                  Start Private Method Definitions
//*************************************************************************************************



//*************************************************************************************************
//                                   End Private Method Definitions
//*************************************************************************************************