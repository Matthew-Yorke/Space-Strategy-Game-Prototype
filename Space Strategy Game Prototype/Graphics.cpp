//***************************************************************************************************************************************************
//
// File Name: Graphics.cpp
//
// Description:
//  TODO: Add file description.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     MM/DD/YYYY     TODO: Add Description.
//
//***************************************************************************************************************************************************

#include "Graphics.h"
#include "OverallProjectConstants.h"

//***************************************************************************************************************************************************
// Start Public Method Definitions
//***************************************************************************************************************************************************

//***************************************************************************************************************************************************
//
// Method Name: Graphics
//
// Description:
//  TODO: Add description.
//
//***************************************************************************************************************************************************
Graphics::Graphics(ALLEGRO_DISPLAY* theDisplay)
{
   mpDisplay = theDisplay;
}

//***************************************************************************************************************************************************
//
// Method Name: ~Graphics
//
// Description:
//  TODO: Add description.
//
//***************************************************************************************************************************************************
Graphics::~Graphics()
{
   for (auto spriteSheetIterator = mpSpriteSheets.begin();
        spriteSheetIterator != mpSpriteSheets.end();
        spriteSheetIterator++)
   {
      al_destroy_bitmap(spriteSheetIterator->second);
   }
}

//***************************************************************************************************************************************************
//
// Method Name: Draw
//
// Description:
//  TODO: Add description.
//
//***************************************************************************************************************************************************
void Graphics::Draw(ALLEGRO_BITMAP* thepSource, int theStartPositionX, int theStartPositionY, int theWidth, int theHeight, int theDestinationX,
                    int theDestinationY, float theAngle)
{
   ALLEGRO_BITMAP* rotated = NULL;
   rotated = al_create_bitmap(theWidth, theHeight);
   al_set_target_bitmap(rotated);
   al_clear_to_color(al_map_rgb(0,0,0));

   al_convert_mask_to_alpha(thepSource, al_map_rgb(255, 0, 255));

   //al_draw_bitmap_region(thepSource,
   //                      theStartPositionX,
   //                      theStartPositionY,
   //                      theWidth,
   //                      theHeight,
   //                      theDestinationX,
   //                      theDestinationY,
   //                      0);

   al_draw_bitmap_region(thepSource,
                         theStartPositionX,
                         theStartPositionY,
                         theWidth,
                         theHeight,
                         0,
                         0,
                         0);

    al_convert_mask_to_alpha(rotated, al_map_rgb(0,0,0));
    al_set_target_bitmap(al_get_backbuffer(mpDisplay));
    al_draw_rotated_bitmap(rotated,
                   al_get_bitmap_width(rotated)/2,
                   al_get_bitmap_height(rotated)/2,
                   theDestinationX + al_get_bitmap_width(rotated)/2,
                   theDestinationY + al_get_bitmap_height(rotated)/2,
                   theAngle,
                   0);
    al_destroy_bitmap(rotated);
}

//***************************************************************************************************************************************************
//
// Method Name: LoadImage
//
// Description:
//  TODO: Add description.
//
//***************************************************************************************************************************************************
ALLEGRO_BITMAP* Graphics::LoadImage(const std::string& theFilePath)
{
   if (mpSpriteSheets.count(theFilePath) == 0)
   {
      mpSpriteSheets[theFilePath] = al_load_bitmap(theFilePath.c_str());
   }

   return mpSpriteSheets[theFilePath];
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

// Note: There are no private methods in this class.

//***************************************************************************************************************************************************
// End Private Method Definitions
//***************************************************************************************************************************************************