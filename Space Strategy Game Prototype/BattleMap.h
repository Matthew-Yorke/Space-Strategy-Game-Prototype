//************************************************************************************************************************************************
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
//************************************************************************************************************************************************

#ifndef BattleMap_h
#define BattleMap_h

#include <string>
#include <vector>
#include "Ship.h"
#include "OverallProjectConstants.h"

class BattleMap
{
   struct VectorTwoDimensional
   {
      int Column;
      int Row;
   };

   //************************************************************************************************************************************************
   //                                   Start Method Declarations
   //************************************************************************************************************************************************

public:

   //************************************************************************************************************************************************
   //
   // Method Name: BattleMap
   //
   // Description:
   //  Constructor that sets member variables to default values.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   BattleMap();

   //************************************************************************************************************************************************
   //
   // Method Name: ~BattleMap
   //
   // Description:
   //  Destructor that cleans up any allocated memory.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   ~BattleMap();

   //************************************************************************************************************************************************
   //
   // Method Name: LoadMap
   //
   // Description:
   //  Load the battle map data by readin the file that is passed in.
   //
   // Arguments:
   //  theBattleMapFileName - The file location to open the battle map information.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void LoadMap(std::string theBattleMapFileName);

   //************************************************************************************************************************************************
   //
   // Method Name: AddPlayerShip
   //
   // Description:
   //  Add a ship to the players ship list for the battle.
   //
   // Arguments:
   //  thepPlayerShip - A pointer to the ship that is being added to the players ship list.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void AddPlayerShip(Ship* thepPlayerShip);

   //************************************************************************************************************************************************
   //
   // Method Name: RemovePlayerShip
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  thepPlayerShip - A pointer to the ship that is being removed to the players ship list.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void RemovePlayerShip(Ship* thepPlayerShip);

   //************************************************************************************************************************************************
   //
   // Method Name: MoveTileSelector
   //
   // Description:
   //  TODO: Add method description.
   //
   // Arguments:
   //  theDirection - The direction the tile selector is moving towards.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void MoveTileSelector(OverallProjectConstants::Direction theDirection);

   //************************************************************************************************************************************************
   //
   // Method Name: CalculateShipsMoveableArea
   //
   // Description:
   //  Calculates the tiles the current ship that is taking its action turn can move to.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void CalculateShipsMoveableArea();

   //************************************************************************************************************************************************
   //
   // Method Name: MoveShipToSelectedTile
   //
   // Description:
   //  Move the ship that is taking its action turn to the valid tile that the tile selector is
   //  selected at.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void MoveShipToSelectedTile();

   //************************************************************************************************************************************************
   //
   // Method Name: Draw
   //
   // Description:
   //  Draw the battle map images based on the state of the battle.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void Draw();

   //************************************************************************************************************************************************
   //
   // Method Name: DrawBattleMapTiles
   //
   // Description:
   //  Draw the tiles for the battle map onto the back buffer.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void DrawBattleMapTiles();

   //************************************************************************************************************************************************
   //
   // Method Name: DrawShipsMoveableArea
   //
   // Description:
   //  Draw the moveable tile indicators for the ship that is taking its action turn onto the back buffer.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void DrawShipsMoveableArea();

   //************************************************************************************************************************************************
   //
   // Method Name: DrawShips
   //
   // Description:
   //  Draw the ships for the battle map onto the back buffer.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void DrawShips();

   //************************************************************************************************************************************************
   //
   // Method Name: DrawTileSelector
   //
   // Description:
   //  Draw the tile selector for the battle map onto the back buffer.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void DrawTileSelector();

protected:

   // THere are currently no protected methods for this class.

private:

   // There are currently no private methods for this class.

   //************************************************************************************************************************************************
   //                                    End Method Declarations
   //************************************************************************************************************************************************

   //************************************************************************************************************************************************
   //                                Start Member Vairable Declarations
   //************************************************************************************************************************************************

public:

   // There are currently no public member variables for this class.

protected:

   // There are currently no protected member variables for this class.

private:

   // A dynamic 2-Dimensional array the holds tile information for each tile in the battle map. This is created upon a read of a battle map file and
   // deleted upon class destruction or before reading a new battle map file.
   //
   // Note: This is prototype of the map array, will need to use a structure to hold other information about a tile of the map such as if the tile
   //       is already occuppied.
   int** mpBattleMapArray;

   // The number of columns of tiles for the battle map.
   int mNumberOfTileColumns;

   // The number of rows of tiles for the battle map.
   int mNumberOfTileRows;
   
   // The column the tile selector is located at.
   int mTileSelectorColumn;

   // The row the tile selector is located at.
   int mTileSelectorRow;

   // Vector the holds the column x row for tile information.
   std::vector<std::pair<int, int>> mMoveableTiles;

   // Vector of pointers to ships that represents the players selected ships for the battle.
   std::vector<Ship*> mpPlayerShips;

   // Vector of pointers to ships that represents the oppositions ships for the battle.
   std::vector<Ship*> mpEnemyShips;

   // Pointer to the ship that is taking its action turn.
   Ship* mpCurrentShipsActionTurn;

   //************************************************************************************************************************************************
   //                                 End Member Vairable Declarations
   //************************************************************************************************************************************************
};

#endif