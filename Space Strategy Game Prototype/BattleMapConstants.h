//***************************************************************************************************************************************************
//
// File Name: BattleMapConstants.h
//
// Description:
//  Constants that are used in the BattleMap class.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     12/04/2017     Initail defintion of constants used exclusively in the battle map class.                                            
//
//***************************************************************************************************************************************************

#include "allegro5\allegro.h"

namespace BattleMapConstants
{
   // The delimeter used when parsing information from the battle map file.
   const char FILE_DELIMITER = ',';

   // The value to move one direction space from a current location tile column or row.
   const int ONE_TILE_DIFFERENCE = 1;

   // The flag for the allegro draw call to indicate no special changes to be made on drawing.
   const int DRAW_BITMAP_NO_FLAG = 0;
}