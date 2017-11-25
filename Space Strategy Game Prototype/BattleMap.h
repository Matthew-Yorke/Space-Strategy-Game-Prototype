//*************************************************************************************************
//
// File Name: BattleMap.h
//
// Description:
//  TODO: Add file description.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     MM/DD/YYYY     TODO: Add history update
//
//*************************************************************************************************

#ifndef BattleMap_h
#define BattleMap_h

#include <string>

class BattleMap
{
   //**********************************************************************************************
   //                                   Start Method Declarations
   //**********************************************************************************************

public:

   //*******************************************************************************************
   //
   // Method Name: BattleMap
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
   BattleMap();

   //*******************************************************************************************
   //
   // Method Name: Initialize
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  True  - Intialization is successful.
   //  False - Initialization unsuccessful.
   //
   //*******************************************************************************************
   bool Initialize();

   //*******************************************************************************************
   //
   // Method Name: Terminate
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
   void Terminate();

   //*******************************************************************************************
   //
   // Method Name: LoadMap
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  battleMapFileName - TODO: Add description of the argument.
   //
   // Return:
   //  N/A
   //
   //*******************************************************************************************
   void LoadMap(std::string battleMapFileName);

   //*******************************************************************************************
   //
   // Method Name: DrawBattleMap
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  display - TODO: Add description of the argument.
   //
   // Return:
   //  N/A
   //
   //*******************************************************************************************
   void DrawBattleMap(ALLEGRO_DISPLAY* display);

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

   // Note: This is prototype of the map array, will need to use a structure to hold other information about a tile
   //       of the map such as if the tile is already occuppied.
   int** mpBattleMapArray;

   int mNumberOfTileColumns;

   int mNumberOfTileRows;

   //**********************************************************************************************
   //                                 End Member Vairable Declarations
   //**********************************************************************************************
};

#endif