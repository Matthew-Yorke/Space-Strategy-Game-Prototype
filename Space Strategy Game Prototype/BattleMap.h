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
#include "BattleMenu.h"

class BattleMap
{
   //************************************************************************************************************************************************
   // Start Method Declarations
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
   // Method Name: UpKeyPressed
   //
   // Description:
   //  Process the action for when the up key is pressed based on the current battle state.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void UpKeyPressed();

   //************************************************************************************************************************************************
   //
   // Method Name: LeftKeyPressed
   //
   // Description:
   //  Process the action for when the left key is pressed based on the current battle state.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void LeftKeyPressed();

   //************************************************************************************************************************************************
   //
   // Method Name: DownKeyPressed
   //
   // Description:
   //  Process the action for when the down key is pressed based on the current battle state.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void DownKeyPressed();

   //************************************************************************************************************************************************
   //
   // Method Name: RightKeyPressed
   //
   // Description:
   //  Process the action for when the right key is pressed based on the current battle state.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void RightKeyPressed();

   //************************************************************************************************************************************************
   //
   // Method Name: ActionKeyPressed
   //
   // Description:
   //  Process the action for when the action key is pressed based on the current battle state.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void ActionKeyPressed();

   //************************************************************************************************************************************************
   //
   // Method Name: CancelKeyPressed
   //
   // Description:
   //  Process the action for when the cancel key is pressed based on the current battle state.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void CancelKeyPressed();
   
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
   //  Remove a ship from the players ship list.
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
   //  Move the tile selector one tile based on the direction passed in.
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
   // Method Name: CenterTileSelector
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
   void CenterTileSelector();

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
   // Method Name: DetermineStateFromMenu
   //
   // Description:
   //  Determine which battle state to switch to based on the selection from the main battle menu.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void DetermineStateFromMenu();

   //************************************************************************************************************************************************
   //
   // Method Name: DetermineNextActionTurn
   //
   // Description:
   //  Determine which ship takes its action turn next.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void DetermineNextActionTurn();

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
   // End Method Declarations
   //************************************************************************************************************************************************

   //************************************************************************************************************************************************
   // Start Member Vairable Declarations
   //************************************************************************************************************************************************

public:

   // There are currently no public member variables for this class.

protected:

   // There are currently no protected member variables for this class.

private:

   // The states that the battle can be.
   // DETERMINING - Used to calculate which ship will take it's next action turn.
   // MENU_MAIN - Used to determine the player is currently selecting from the menu's main window.
   // MOVE - Used to determine where the player can move a ship.
   // ATTACK - Used to determine the player is selecting an attack area.
   enum BattleState { DETERMINING, MENU_MAIN, MOVE, ATTACK};

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

   // Pointer to the battle menu that is used for the player to select an action for a ship to perform.
   BattleMenu* mpBattleMenu;

   // Tracks the current battle state to determine what action to perform when processing is occurring.
   BattleState mCurrentBattleState;

   //************************************************************************************************************************************************
   // End Member Vairable Declarations
   //************************************************************************************************************************************************
};

#endif