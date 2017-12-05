//***************************************************************************************************************************************************
//
// File Name: OverallProjectConstants.h
//
// Description:
//  Constants that are used throughout the project.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     12/04/2017     Initail defintion of constants used throughout the project.                                            
//
//***************************************************************************************************************************************************

#include "allegro5\allegro.h"
#include <string>

namespace OverallProjectConstants
{
   // The width in pixels that a tile is.
   const int TILE_WIDTH = 64;

   // The height in pixels that a tile is.
   const int TILE_HEIGHT = 64;

   // The magenta color based on the red, green, blue color combination.
   const ALLEGRO_COLOR MAGENTA_COLOR = al_map_rgb(255, 0, 255);

   // A string with no characters in the string.
   const std::string EMPTY_STRING = "";

   // Enumeration that describes four way direction.
   enum Direction { UP, DOWN, LEFT, RIGHT };
}