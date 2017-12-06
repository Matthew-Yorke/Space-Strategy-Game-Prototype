//***************************************************************************************************************************************************
//
// File Name: BattleMenu.cpp
//
// Description:
//  TODO: Add file description.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     12/DD/2017     TODO: Add change description.
//
//***************************************************************************************************************************************************

#include "stdio.h"
#include "allegro5/allegro.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "BattleMenu.h"
#include "OverallProjectConstants.h"

//***************************************************************************************************************************************************
// Start Public Method Definitions
//***************************************************************************************************************************************************

//***************************************************************************************************************************************************
//
// Method Name: BattleMenu
//
// Description:
//  Set the member variables for this class to default values.
//
//***************************************************************************************************************************************************
BattleMenu::BattleMenu()
{
   // Load the battle menu font.
   mpMenuFont = al_load_ttf_font("C:/Users/matt/Documents/Visual Studio 2017/Projects/Space Strategy Game Prototype/Space Strategy Game Prototype/Fonts/CamingoCode-Regular.ttf",
                                 16,
                                 0);

   // Load the image for the cursor for the battle menu and set the default values for the x and y coordinate to draw it at.
   mMenuCursor.pCursorImage = al_load_bitmap("C:/Users/matt/Documents/Visual Studio 2017/Projects/Space Strategy Game Prototype/Space Strategy Game Prototype/Images/MenuCursor.png");
   mMenuCursor.XCoordinate = 0;
   mMenuCursor.YCoordinate = 16;

   // Create a color mask for the magenta color which will amke any magenta color in the image to be completely transparent.
   al_convert_mask_to_alpha(mMenuCursor.pCursorImage, OverallProjectConstants::MAGENTA_COLOR);

   // Set the menu selection index to the first item in the menu.
   mMenuSelectionIndex = 0;

   // Set the default values for the x and y location values for the ship that is taking its action turn.
   mCurrentShipLocationX = 0;
   mCurrentShipLocationY = 0;
}

//***************************************************************************************************************************************************
//
// Method Name: ~BattleMenu
//
// Description:
//  Clean up any allocated memory.
//
//***************************************************************************************************************************************************
BattleMenu::~BattleMenu()
{
   // Clean up memory allocated for the font used.
   al_destroy_font(mpMenuFont);

   // Clean up memory allocated for the cursor.
   al_destroy_bitmap(mMenuCursor.pCursorImage);
}

//************************************************************************************************************************************************
//
// Method Name: MoveCursorUp
//
// Description:
//  Move the cursor of the battle menu up one item. If there isn't an item below the cursor starts at the bottom of the menu on the last item.
//
//************************************************************************************************************************************************
void BattleMenu::MoveCursorUp()
{
   // Check if there isn't a selection above the current selection.
   if(mMenuCursor.YCoordinate == mCurrentShipLocationY)
   {
      // Set the cursor to be the bottom item in the menu.
      mMenuCursor.YCoordinate = mCurrentShipLocationY + 32;
      mMenuSelectionIndex = 2;
   }
   // There is a selection above the current selection.
   else
   {
      // Set the cursor to be the next item in the menu above where it currently is.
      mMenuCursor.YCoordinate -= 16;
      mMenuSelectionIndex--;
   }
}

//************************************************************************************************************************************************
//
// Method Name: MoveCursorDown
//
// Description:
//  Move the cursor of the battle menu down one item. If there isn't an item below the cursor starts at the top of the menu on the first item.
//
//************************************************************************************************************************************************
void BattleMenu::MoveCursorDown()
{
   // Check if there isn't a selection below the current selection.
   if (mMenuCursor.YCoordinate == mCurrentShipLocationY + 32)
   {
      // Set the cursor to be the top item in the menu.
      mMenuCursor.YCoordinate = mCurrentShipLocationY;
      mMenuSelectionIndex = 0;
   }
   // There is a selection below the current selection.
   else
   {
      // Set the cursor to be the next item in the menu below where it currently is.
      mMenuCursor.YCoordinate += 16;
      mMenuSelectionIndex++;
   }
}

//***************************************************************************************************************************************************
//
// Method Name: DrawMenu
//
// Description:
//  Draw the battle menu including the text.
//
//***************************************************************************************************************************************************
void BattleMenu::DrawMenu()
{
   // Draw a box for the battle menu to contain all the other elements of the battle menu.
   al_draw_filled_rectangle(mCurrentShipLocationX, mCurrentShipLocationY, mCurrentShipLocationX + 122, mCurrentShipLocationY + 68, al_map_rgb(255, 255, 255));

   // Draw the text for the selections on the battle menu.
   al_draw_text(mpMenuFont, al_map_rgb(0, 0, 0), mCurrentShipLocationX + 21, mCurrentShipLocationY + 5, ALLEGRO_ALIGN_LEFT, "Move");
   al_draw_text(mpMenuFont, al_map_rgb(0, 0, 0), mCurrentShipLocationX + 21, mCurrentShipLocationY + 21, ALLEGRO_ALIGN_LEFT, "Attack");
   al_draw_text(mpMenuFont, al_map_rgb(0, 0, 0), mCurrentShipLocationX + 21, mCurrentShipLocationY + 37, ALLEGRO_ALIGN_LEFT, "Wait");
}

//***************************************************************************************************************************************************
//
// Method Name: DrawCursor
//
// Description:
//  Draw the cursor to be displayed on the battle menu.
//
//***************************************************************************************************************************************************
void BattleMenu::DrawCursor()
{
   // Draw the cursor on the battle menu to be left and centered height of the currently item it points at in the battle menu.
   al_draw_bitmap(mMenuCursor.pCursorImage, mMenuCursor.XCoordinate, mMenuCursor.YCoordinate+8, 0);
}

//***************************************************************************************************************************************************
//
// Method Name: GetSelectionIndex
//
// Description:
//  Return the currently selected (the one the cursor is pointing at) item index of the battle menu.
//
//***************************************************************************************************************************************************
int BattleMenu::GetSelectionIndex()
{
   return mMenuSelectionIndex;
}

//***************************************************************************************************************************************************
//
// Method Name: SetMenuLocation
//
// Description:
//  Retrieve the the ship x and y location to know where to draw the battle to the right of the ship that is taking its action turn.
//
//***************************************************************************************************************************************************
 void BattleMenu::SetMenuLocation(int X, int Y)
{
    mCurrentShipLocationX = X + 64;
    mCurrentShipLocationY = Y;

    mMenuCursor.XCoordinate = X + 64;
    mMenuCursor.YCoordinate = Y;
}

 //***************************************************************************************************************************************************
 //
 // Method Name: ResetCursor
 //
 // Description:
 //  Reset the cursor to be the top item of the battle menu.
 //
 //***************************************************************************************************************************************************
 void BattleMenu::ResetCursor()
{
    mMenuCursor.XCoordinate = mCurrentShipLocationX;
    mMenuCursor.YCoordinate = mCurrentShipLocationY;

    mMenuSelectionIndex = 0;
}

//***************************************************************************************************************************************************
// End Public Method Definitions
//***************************************************************************************************************************************************

//***************************************************************************************************************************************************
// Start Protected Method Definitions
//***************************************************************************************************************************************************

// Note: There are no protected methods in this class.

//***************************************************************************************************************************************************
// End Protected Method Definitions
//***************************************************************************************************************************************************

//***************************************************************************************************************************************************
// Start Private Method Definitions
//***************************************************************************************************************************************************

// Note: There are no provate methods in this class.

//***************************************************************************************************************************************************
// End Private Method Definitions
//***************************************************************************************************************************************************