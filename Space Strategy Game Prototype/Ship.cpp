//***************************************************************************************************************************************************
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
//***************************************************************************************************************************************************

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
#include "OverallProjectConstants.h"

//************************************************************************************************************************************************
// Start Public Method Definitions
//************************************************************************************************************************************************

//************************************************************************************************************************************************
//
// Method Name: Ship
//
// Description:
//  Constructs the ship object by setting the member vairables to default values.
//
//************************************************************************************************************************************************
Ship::Ship(Graphics& theGraphics, bool theIsManuverable, int theMovementDistance, int theNumberOfSmallWeapons, int theNumberOfMediumWeapons,
           int theNumberOfLargeWeapons, ALLEGRO_DISPLAY* theDisplay, int theWeaponPortX, int theWeaponPortY)
{
   // Set if the ship is manuverable with the passed in value.
   mIsManuverable = theIsManuverable;

   // Set the maximum movement distance with the passed in value.
   mMovementDistance = theMovementDistance;

   // Set the crew assigned to the ship to initially be null (no crew assigned).
   mCrew = nullptr;

   // Test Code - Update later.
   mpShipImage = new Sprite(theGraphics,
                            "Images/Spaceship_1.png",
                            0,
                            0,
                            64,
                            64);

   mpShipOnlyImage = al_load_bitmap("Images/Spaceship_1.png");

   // Set the array size.
   //mSmallWeapons = new SmallWeapons[theNumberOfSmallWeapons];
   //mMediumWeapons = new MediumWeapons[theNumberOfMediumWeapons];
   //mLargeWeapons = new LargeWeapons[theNumberOfLargeWeapons];

   // Temp Code Below
   mShipTileColumn = 4 * 64;
   mShipTileRow = 4 * 64;

   mActionSpeed = 5;
   mActionLevel = 0;

   mMinimumAttackDistance = 1;
   mMaximumAttackDistance = 7;

   mpWeapon = nullptr;

   mCurrentHealth = 30;

   mCurrentDirection = DIRECTION::UP;

   mpDisplay = theDisplay;

   mWeaponPortX = theWeaponPortX;
   mWeaponPortY = theWeaponPortY;
}

//************************************************************************************************************************************************
//
// Method Name: ~Ship
//
// Description:
//  TODO: Add method description.
//
//************************************************************************************************************************************************
Ship::~Ship()
{
   delete mpShipImage;
}

//************************************************************************************************************************************************
//
// Method Name: SetManuverable
//
// Description:
//  Set any change in the ships manuverability.
//
//************************************************************************************************************************************************
void Ship::SetManuverable(bool theIsManuverable)
{
   mIsManuverable = theIsManuverable;
}

//************************************************************************************************************************************************
//
// Method Name: SetCrew
//
// Description:
//  Set any change in the ships manuverability.
//
//************************************************************************************************************************************************
void Ship::SetCrew(Crew* theCrew)
{
   mCrew = theCrew;
}

//************************************************************************************************************************************************
//
// Method Name: SetTileColumn
//
// Description:
//  TODO: Add method description.
//
//************************************************************************************************************************************************
void Ship::SetTileColumn(int theTileColumn)
{
   mShipTileColumn = theTileColumn;
}

//************************************************************************************************************************************************
//
// Method Name: SetTileRow
//
// Description:
//  TODO: Add method description.
//
//************************************************************************************************************************************************
void Ship::SetTileRow(int theTileRow)
{
   mShipTileRow = theTileRow;
}

//************************************************************************************************************************************************
//
// Method Name: AddWeapon
//
// Description:
//  TODO: Add method description.
//
//************************************************************************************************************************************************
void Ship::AddWeapon(Weapon* thepWeapon)
{
   mpWeapon = thepWeapon;
}

//************************************************************************************************************************************************
//
// Method Name: MoveShip
//
// Description:
//  TODO: Add method description.
//
//************************************************************************************************************************************************
void Ship::MoveShip()
{
}

//************************************************************************************************************************************************
//
// Method Name: ResetActionLevel
//
// Description:
//  TODO: Add method description.
//
//************************************************************************************************************************************************
void Ship::ResetActionLevel()
{
   mActionLevel = 0;
}

//************************************************************************************************************************************************
//
// Method Name: IncrementActionLevel
//
// Description:
//  TODO: Add method description.
//
//************************************************************************************************************************************************
void Ship::IncrementActionLevel()
{
   mActionLevel += mActionSpeed;
}

//************************************************************************************************************************************************
//
// Method Name: GetActionLevel
//
// Description:
//  TODO: Add method description.
//
//************************************************************************************************************************************************
int Ship::GetActionLevel()
{
   return mActionLevel;
}

//************************************************************************************************************************************************
//
// Method Name: GetMovementDistance
//
// Description:
//  TODO: Add method description.
//
//************************************************************************************************************************************************
int Ship::GetMovementDistance()
{
   return mMovementDistance;
}

//************************************************************************************************************************************************
//
// Method Name: GetTileColumn
//
// Description:
//  TODO: Add method description.
//
//************************************************************************************************************************************************
int Ship::GetTileColumn()
{
   return mShipTileColumn;
}

//************************************************************************************************************************************************
//
// Method Name: GetTileRow
//
// Description:
//  TODO: Add method description.
//
//************************************************************************************************************************************************
int Ship::GetTileRow()
{
   return mShipTileRow;
}

int Ship::GetWeaponMinimumRange()
{
   return mpWeapon->GetMinimumRange();
}

int Ship::GetWeaponMaximumRange()
{
   return mpWeapon->GetMaximumRange();
}

int Ship::GetWeaponDamage()
{
   return mpWeapon->GetDamage();
}

//************************************************************************************************************************************************
//
// Method Name: GetActionLevel
//
// Description:
//  TODO: Add method description.
//
//************************************************************************************************************************************************
void Ship::Draw(Graphics& theGraphics)
{
   // Temporary to build ship and weapon attachments
   ALLEGRO_BITMAP* ShipBuilder = nullptr;
   ShipBuilder = al_create_bitmap(64, 64);

   // Set to draw on temporary canvas
   al_set_target_bitmap(ShipBuilder);
   
   // Clear canvas to be all black
   al_clear_to_color(al_map_rgb(0,0,0));

   // Draw the ship first using the image of only the ship.
   al_draw_bitmap_region(mpShipOnlyImage,
                         0,
                         0,
                         64,
                         64,
                         0,
                         0,
                         0);

   // Mask the weapon pink color.
   al_convert_mask_to_alpha(mpWeapon->GetBitmap(), al_map_rgb(255, 0, 255));

   // Draw weapon ontop of the ship.
   al_draw_rotated_bitmap(mpWeapon->GetBitmap(),
                          mpWeapon->GetPivotPointX(),
                          mpWeapon->GetPivotPointY(),
                          mWeaponPortX,
                          mWeaponPortY,
                          mpWeapon->GetAngle(),
                          0);

   // Target to draw on the ship canvas
   al_set_target_bitmap(mpShipImage->GetBitmap());

   // Set the canvas to be black
   al_clear_to_color(al_map_rgb(0,0,0));
   
   // draw the temporary built ship image as the final image for the bitmap.
   al_draw_bitmap_region(ShipBuilder,
                         0,
                         0,
                         64,
                         64,
                         0,
                         0,
                         0);

   // retarget the main display.
   al_set_target_bitmap(al_get_backbuffer(mpDisplay));

   // Draw the entire ship to the display.
   mpShipImage->Draw(theGraphics,
                     mShipTileColumn,
                     mShipTileRow);
   //mpWeapon->Draw(theGraphics,
   //               mShipTileColumn,
   //               mShipTileRow);

   al_destroy_bitmap(ShipBuilder);
}

int Ship::GetCurrentHealth()
{
   return mCurrentHealth;
}

void Ship::TakeDamage(int theDamage)
{
   mCurrentHealth -= theDamage;
}

//************************************************************************************************************************************************
// End Public Method Definitions
//************************************************************************************************************************************************

//************************************************************************************************************************************************
// Start Protected Method Definitions
//************************************************************************************************************************************************



//************************************************************************************************************************************************
// End Protected Method Definitions
//************************************************************************************************************************************************

//************************************************************************************************************************************************
// Start Private Method Definitions
//************************************************************************************************************************************************



//************************************************************************************************************************************************
// End Private Method Definitions
//************************************************************************************************************************************************