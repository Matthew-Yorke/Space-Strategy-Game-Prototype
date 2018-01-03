//***************************************************************************************************************************************************
//
// File Name: BattleMap.cpp
//
// Description:
//  TODO: Add file description.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     12/04/2017     Initial implementation for the battle map class. Added in loading battle map information, drawing a
//                                      portion of the graphics, and movement inital movement selection of a ship.
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
#include "BattleMap.h"
#include "BattleMapConstants.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <math.h>

//***************************************************************************************************************************************************
// Start Public Method Definitions
//***************************************************************************************************************************************************

//***************************************************************************************************************************************************
//
// Method Name: BattleMap
//
// Description:
//  Set the member variables for this class to default values.
//
//***************************************************************************************************************************************************
BattleMap::BattleMap(Graphics& theGraphics, ALLEGRO_DISPLAY* theDisplay)
{
   // Set the default number of tile columns and rows in the map.
   mNumberOfTileColumns = 0;
   mNumberOfTileRows = 0;

   // Set the default column and row the tile selector is located at.
   mTileSelectorRow = 0;
   mTileSelectorColumn = 0;

   // Set the default current ship that is in its action turn.
   mpCurrentShipsActionTurn = nullptr;

   // Create a new battle menu object to use for this battle.
   mpBattleMenu = new BattleMenu(theGraphics);
   
   // Set the default state to start determining which ship will go first.
   mCurrentBattleState = BattleState::DETERMINING;

   mpTileSelectorImage = new AnimatedSprite(theGraphics,
                                            "Images/TileSelector.png",
                                            0,
                                            0,
                                            64,
                                            64,
                                            2,
                                            2);

   mMoveTime = 1.0f / 60.0f;
   mElapsedTime = 0.0f;
   mTurningCount = 0;
   mWeaponAngle = 0.0F;
   mpGraphics = &theGraphics;
   mAttackedTileX = 0;
   mAttackedTileY = 0;
   mpDisplay = theDisplay;
}

//***************************************************************************************************************************************************
//
// Method Name: ~BattleMap
//
// Description:
//  Clean up any allocated memory.
//
//***************************************************************************************************************************************************
BattleMap::~BattleMap()
{
   // Clean up any allocated memory in the Battle Map container.
   //for (int currentTileRow = 0;
   //   currentTileRow < mNumberOfTileRows;
   //   currentTileRow++)
   //{
   //   delete[] mpBattleMapArray[currentTileRow];
   //   mpBattleMapArray[currentTileRow] = nullptr;
   //}
   //delete[] mpBattleMapArray;
   //mpBattleMapArray = nullptr;

   // Clean up any allocated memory in the Player Ship container.
   while (mpPlayerShips.empty() == false)
   {
      delete mpPlayerShips.back();
      mpPlayerShips.pop_back();
   }

   // Clean up any allocated memory in the Enemy Ship container.
   while (mpEnemyShips.empty() == false)
   {
      delete mpEnemyShips.back();
      mpEnemyShips.pop_back();
   }

   // Clean up allocated memory used for the battle menu.
   delete mpBattleMenu;

   delete mpTileSelectorImage;
}

//***************************************************************************************************************************************************
//
// Method Name: UpKeyPressed
//
// Description:
//  Perform an action dependant on the battle state when the up key is pressed:
//     MENU_MAIN - Move the the cursor up one selection.
//     MOVE - Move the tile selector up one tile.
//
//***************************************************************************************************************************************************
void BattleMap::UpKeyPressed()
{
   // Determine which battle state is currently occurring.
   switch (mCurrentBattleState)
   {
      // The battle state is in the ship action menu (main) selector state.
      case BattleState::MENU_MAIN:
      {
         // Move the battle menu cursor up on selection.
         mpBattleMenu->MoveCursorUp();
         break;
      }
      // The battle state is in the ship movement selector state.
      case BattleState::MOVE:
      {
         // Move the tile selector one tile up.
         MoveTileSelector(OverallProjectConstants::Direction::UP);
         break;
      }
      case BattleState::ATTACK:
      {
         // Move the tile selector one tile up.
         MoveTileSelector(OverallProjectConstants::Direction::UP);
         break;
      }
      // All other states not defined here or an error state occured.
      default:
      {
         // If the Default case occurs, then do nothing as nothing should happened when the up button is pressed that is not defined above.
      }
   }
}

//***************************************************************************************************************************************************
//
// Method Name: LeftKeyPressed
//
// Description:
//  Perform an action dependant on the battle state when the up key is pressed:
//     MOVE - Move the tile selector left one tile.
//
//***************************************************************************************************************************************************
void BattleMap::LeftKeyPressed()
{
   // Determine which battle state is currently occurring.
   switch (mCurrentBattleState)
   {
      // The battle state is in the ship movement selector state.
      case BattleState::MOVE:
      {
         // Move the tile selector one tile left.
         MoveTileSelector(OverallProjectConstants::Direction::LEFT);
         break;
      }
      case BattleState::ATTACK:
      {
         // Move the tile selector one tile left.
         MoveTileSelector(OverallProjectConstants::Direction::LEFT);
         break;
      }
      // All other states not defined here or an error state occured.
      default:
      {
         // If the Default case occurs, then do nothing as nothing should happened when the left button is pressed that is not defined above.
      }
   }
}

//***************************************************************************************************************************************************
//
// Method Name: DownKeyPressed
//
// Description:
//  Perform an action dependant on the battle state when the up key is pressed:
//     MENU_MAIN - Move the the cursor down one selection.
//     MOVE - Move the tile selector down one tile.
//
//***************************************************************************************************************************************************
void BattleMap::DownKeyPressed()
{
   // Determine which battle state is currently occurring.
   switch (mCurrentBattleState)
   {
      // The battle state is in the ship action menu (main) selector state.
      case BattleState::MENU_MAIN:
      {
         // Move the battle menu cursor down on selection.
         mpBattleMenu->MoveCursorDown();
         break;
      }
      // The battle state is in the ship movement selector state.
      case BattleState::MOVE:
      {
         // Move the tile selector one tile down.
         MoveTileSelector(OverallProjectConstants::Direction::DOWN);
         break;
      }
      case BattleState::ATTACK:
      {
         // Move the tile selector one tile down.
         MoveTileSelector(OverallProjectConstants::Direction::DOWN);
         break;
      }
      // All other states not defined here or an error state occured.
      default:
      {
         // If the Default case occurs, then do nothing as nothing should happened when the down button is pressed that is not defined above.
      }
   }
}

//***************************************************************************************************************************************************
//
// Method Name: RightKeyPressed
//
// Description:
//  Perform an action dependant on the battle state when the up key is pressed:
//     MOVE - Move the tile selector right one tile.
//
//***************************************************************************************************************************************************
void BattleMap::RightKeyPressed()
{
   // Determine which battle state is currently occurring.
   switch (mCurrentBattleState)
   {
      // The battle state is in the ship movement selector state.
      case BattleState::MOVE:
      {
         // Move the tile selector on tile to the right.
         MoveTileSelector(OverallProjectConstants::Direction::RIGHT);
         break;
      }
      // The battle state is in the ship movement selector state.
      case BattleState::ATTACK:
      {
         // Move the tile selector on tile to the right.
         MoveTileSelector(OverallProjectConstants::Direction::RIGHT);
         break;
      }
      // All other states not defined here or an error state occured.
      default:
      {
         // If the Default case occurs, then do nothing as nothing should happened when the right button is pressed that is not defined above.
      }
   }
}

//***************************************************************************************************************************************************
//
// Method Name: ActionKeyPressed
//
// Description:
//  Perform an action dependant on the battle state when the action key is pressed:
//     MENU_MAIN - Center the tile selector and determine which battle state to change to based on the menu item selected.
//     MOVE - Move the current ship taking its action turn to the selected tile (if within the movement bounds) and set the battle state to return
//            to the main battle menu.
//
//***************************************************************************************************************************************************
void BattleMap::ActionKeyPressed()
{
   // Determine which battle state is currently occurring.
   switch (mCurrentBattleState)
   {
      // The battle state is in the ship action menu (main) selector state.
      case BattleState::MENU_MAIN:
      {
         // Center the tile selector to where the ship that is currently taking its action turn and then determine which state to change to next
         // based on the selection in the main battle menu.
         CenterTileSelector();
         DetermineStateFromMenu();
         break;
      }
      // The battle state is in the ship movement selector state.
      case BattleState::MOVE:
      {
         // Move the ship to the selected tile and then revert back to the main battle menu state.
         bool validMove = MoveShipToSelectedTile();

         if(validMove == true)
         {
            mCurrentBattleState = BattleState::MOVE_ANIMATION;
         }

         break;
      }
      case BattleState::ATTACK:
      {
         // Move the ship to the selected tile and then revert back to the main battle menu state.
         bool validMove = AttackSelectedTile();

         if(validMove == true)
         {
            mCurrentBattleState = BattleState::ATTACK_SETUP;
         }

         break;
      }
      // All other states not defined here or an error state occured.
      default:
      {
         // If the Default case occurs, then do nothing as nothing should happened when the action button is pressed that is not defined above.
      }
   }
}

//***************************************************************************************************************************************************
//
// Method Name: CancelKeyPressed
//
// Description:
//  Perform an action dependant on the battle state when the cancel key is pressed:
//     MOVE - Set the battle state to return to the main battle menu.
//
//***************************************************************************************************************************************************
void BattleMap::CancelKeyPressed()
{
   // Determine which battle state is currently occurring.
   switch (mCurrentBattleState)
   {
      // The battle state is in the ship movement selector state.
      case BattleState::MOVE:
      {
         // Change the current battle state to revert back to the main battle menu state.
         mCurrentBattleState = BattleState::MENU_MAIN;
         break;
      }
      case BattleState::ATTACK:
      {
         // Change the current battle state to revert back to the main battle menu state.
         mCurrentBattleState = BattleState::MENU_MAIN;
         break;
      }
      // All other states not defined here or an error state occured.
      default:
      {
         // If the Default case occurs, then do nothing as nothing should happened when the cancel button is pressed that is not defined above.
      }
   }
}

//***************************************************************************************************************************************************
//
// Method Name: LoadMap
//
// Description:
//  Read the file at the location indicated by the passed in string and retrieve information by line:
//     Line 0: The number of columns and rows in the battle map.
//     Lines 1 - EOF: The battle map array that includes tile information and location.
//
//***************************************************************************************************************************************************
void BattleMap::LoadMap(std::string theBattleMapFileName)
{
   // Delete any previously allocated memory in the battle map array.
   //for (int currentTileRow = 0;
   //     currentTileRow < mNumberOfTileRows;
   //     currentTileRow++)
   //{
   //   delete[] mpBattleMapArray[currentTileRow];
   //}
   //delete[] mpBattleMapArray;
 
   // Holds the string line that is currently be read in the file.
   std::string currentFileLineString(OverallProjectConstants::EMPTY_STRING);

   // The line number that is currently being read.
   int currentLineNumber = 0;

   // Open the file by the string that is passed in this function.
   std::ifstream battleMapFile;
   battleMapFile.open(theBattleMapFileName);

   // Make sure the file properly opened.
   if (battleMapFile.is_open() == true)
   {
      // Exit once the "end of file" is reached.
      while (battleMapFile.eof() == false)
      {
         // Read the next line the file.
         std::getline(battleMapFile,
                      currentFileLineString);
         // Change the string to be an input stream so it can be parsed.
         std::istringstream stringStream(currentFileLineString);
         // the string that is parsed by a delimeter.
         std::string parsedString("");

         // Get the metadata about the number of columns and rows in the map.
         if(currentLineNumber == 0)
         {
            // The first parsed string is an integer that represents the number of columns.
            std::getline(stringStream,
                         parsedString,
                         BattleMapConstants::FILE_DELIMITER);
            mNumberOfTileColumns = stoi(parsedString);

            // The second parsed string is an integer that represents the number of rows.
            std::getline(stringStream,
                         parsedString,
                         BattleMapConstants::FILE_DELIMITER);
            mNumberOfTileRows = stoi(parsedString);

            // Create a new array with the column and row sizes for the 2D sizes.
            //mpBattleMapArray = new int* [mNumberOfTileRows];
            //for (int currentTileRow = 0;
            //     currentTileRow < mNumberOfTileRows;
            //     currentTileRow++)
            //{
            //   mpBattleMapArray[currentTileRow] = new int [mNumberOfTileColumns];
            //}
         }
         // Retrieve the map tile information including column and row location and add the data to the battle map container.
         // The current line being read in the file minues the offset is the current row of the battle map.
         else if ((currentLineNumber - currentLineNumber) < mNumberOfTileRows)
         {
            // For the row iterate through each column in the battle map and transfer the information from the file to the battle map container.
            for(int currentTileColumn = 0;
                currentTileColumn < mNumberOfTileColumns;
                currentTileColumn++)
            {
               std::getline(stringStream,
                            parsedString,
                            BattleMapConstants::FILE_DELIMITER);
               TileNode* newNode = new TileNode();
               newNode->Column = currentTileColumn;
               newNode->Row = currentLineNumber - currentLineNumber;
               newNode->DistanceFromCurrentShip = -1;
               mBattleMapVector.push_back(newNode);
               //mpBattleMapArray[currentLineNumber - currentLineNumber][currentTileColumn] = stoi(parsedString);
            }
         }
         
         // Indicate that the line is being incremented as the next line is about to be read.
         currentLineNumber++;
      }
   }

   // Close the battle map file now that reading from it is done.
   battleMapFile.close();
}

//***************************************************************************************************************************************************
//
// Method Name: AddPlayerShip
//
// Description:
//  Add the indicated ship from the players list of ships they are controlling in the battle.
//
//***************************************************************************************************************************************************
void BattleMap::AddPlayerShip(Ship* thepPlayerShip)
{
   // Add the passed in ship to the ships that the player is controlling in this battle.
   mpPlayerShips.push_back(thepPlayerShip);
}

//***************************************************************************************************************************************************
//
// Method Name: RemovePlayerShip
//
// Description:
//  Remove the indicated ship from the players list of ships they controlling in the battle.
//
//***************************************************************************************************************************************************
void BattleMap::RemovePlayerShip(Ship* thepPlayerShip)
{
   // Try to find the player ship indicated to be removed by searching the ships the player is controlling this battle. If found, remove the ship
   // from the players list of ships they controlling this battle.
   auto shipIterator = std::find(mpPlayerShips.begin(),
                                 mpPlayerShips.end(),
                                 thepPlayerShip);
   if (shipIterator != mpPlayerShips.end())
   {
      mpPlayerShips.erase(shipIterator);
   }
}

//***************************************************************************************************************************************************
//
// Method Name: MoveTileSelector
//
// Description:
//  Move where the tile selector will be located and drawn by one tile based on the passed in direction.
//
//***************************************************************************************************************************************************
void BattleMap::MoveTileSelector(OverallProjectConstants::Direction theDirection)
{
   // Determine which direction is occurring to process.
   switch (theDirection)
   {
      case OverallProjectConstants::Direction::UP:
      {
         // Decrement the tile selector row to check one tile above the current tile selector location.
         mTileSelectorRow--;

         // Make sure the tile selector does not go out of bounds of the top of the map.
         if (mTileSelectorRow < 0)
         {
            mTileSelectorRow = 0;
         }

         // Break at the end end of the case as not to fall through the next case.
         break;
      }
      case OverallProjectConstants::Direction::DOWN:
      {
         // Increment the tile selector row to check one tile below the current tile selector location.
         mTileSelectorRow++;

         // Make sure the tile selector does not go out of bounds of the bottom of the map.
         if (mTileSelectorRow > mNumberOfTileRows)
         {
            mTileSelectorRow = mNumberOfTileRows;
         }
   
         // Break at the end end of the case as not to fall through the next case.
         break;
      }
      case OverallProjectConstants::Direction::LEFT:
      {
         // Decrement the tile selector column to check one tile left of the current tile selector location.
         mTileSelectorColumn--;

         // Make sure the tile selector does not go out of bounds of the left of the map.
         if (mTileSelectorColumn < 0)
         {
            mTileSelectorColumn = 0;
         }

         // Break at the end end of the case as not to fall through the next case.
         break;
      }
      case OverallProjectConstants::Direction::RIGHT:
      {
         // Increment the tile selector column to check one tile right of the current tile selector location.
         mTileSelectorColumn++;

         // Make sure the tile selector does not go out of bounds of the right of the map.
         if (mTileSelectorColumn > mNumberOfTileColumns)
         {
            mTileSelectorColumn = mNumberOfTileColumns;
         }

         // Break at the end end of the case as not to fall through the next case.
         break;
      }
      default:
      {
         // If the Default case occurs, then do nothing as this case should not occur.
      }
   }
}

//***************************************************************************************************************************************************
//
// Method Name: CenterTileSelector
//
// Description:
//  Center the tile selector to the tile the ship that is taking its action turn.
//
//***************************************************************************************************************************************************
void BattleMap::CenterTileSelector()
{
   // Set the tile selector column and row to be the same as the ship that is currently taking its action turn.
   mTileSelectorColumn = mpCurrentShipsActionTurn->GetTileColumn() / 64;
   mTileSelectorRow = mpCurrentShipsActionTurn->GetTileRow() / 64;
}

//***************************************************************************************************************************************************
//
// Method Name: CalculateShipsMoveableArea
//
// Description:
//  Calculate the tiles that the current ship that is taking its action turn can move to.
//
//***************************************************************************************************************************************************
void BattleMap::CalculateShipsMoveableArea()
{
   int currentColumn = 0;
   int currentRow = 0;

   // Stop any unecessary processing in finding which tiles are needed by knowing that there are areas already found in the Already Found areas
   // container. THe reasoning is becuase the Already Found container will be cleared once the ship moves, allowing processing for the next set of
   // areas to be found at the new ship location.
   if ((mpCurrentShipsActionTurn != nullptr) &&
       (mMoveableTiles.empty() == true))
   {
      // Holds the list of tile locations to investigate from for more moveable spaces.
      std::vector<TileNode*>/*std::pair<int, int>>*/ investigateAreas;
      // List of new areas found from the investigate areas container.
      std::vector<TileNode*>/*std::pair<int, int>>*/ newInvestigateAreas;

      // Add the ships location as the starting investigate area.
      TileNode* startingNode = new TileNode();
      startingNode->Column = mpCurrentShipsActionTurn->GetTileColumn() / 64;
      startingNode->Row = mpCurrentShipsActionTurn->GetTileRow() / 64;
      startingNode->DistanceFromCurrentShip = 0;
      investigateAreas.push_back(startingNode);//std::make_pair(mpCurrentShipsActionTurn->GetTileColumn(),
                                                //mpCurrentShipsActionTurn->GetTileRow()));

      // Add the ships location as a tile where it can move to.
      
      mMoveableTiles.push_back(startingNode);//std::make_pair(mpCurrentShipsActionTurn->GetTileColumn(),
                                            //  mpCurrentShipsActionTurn->GetTileRow()));

      // For as many movement spaces that are left, check which tiles are needed in the moveable tile container for the tiles the ship can traverse
      // to.
      for (int currentMovementDistance = 0;
           currentMovementDistance < mpCurrentShipsActionTurn->GetMovementDistance();
           currentMovementDistance++)
      {
         // For each tile that is to be investigated this iteration, search for each adjacent tile to check if it's already added to the moveable
         // tiles container. If they aren't found in the moveable tiles container, then add them to the moveable tiles and new areas to investigate
         // containers so the next iteration will know what tiles are already found and which tiles to check next respectfully.
         for (auto currentInvestigateArea = investigateAreas.begin();
              currentInvestigateArea < investigateAreas.end();
              currentInvestigateArea++)
         {
            // Check the tile above of the investigate tile.
            currentColumn = (*currentInvestigateArea)->Column;
            currentRow = (*currentInvestigateArea)->Row - BattleMapConstants::ONE_TILE_DIFFERENCE;
            auto foundMoveableTileIterator = std::find_if(mMoveableTiles.begin(),
                                                          mMoveableTiles.end(),
                                                          [currentColumn, currentRow](const TileNode* d){return d->Column == currentColumn && d->Row == currentRow;});
            if (foundMoveableTileIterator == mMoveableTiles.end() &&
                IsTileOccupied((*currentInvestigateArea)->Column, (*currentInvestigateArea)->Row - BattleMapConstants::ONE_TILE_DIFFERENCE) == false)
            {
               TileNode* ValidNode = new TileNode();
               ValidNode->Column = currentColumn;
               ValidNode->Row = currentRow;
               ValidNode->DistanceFromCurrentShip = currentMovementDistance + 1;
               mMoveableTiles.push_back(ValidNode);
               newInvestigateAreas.push_back(ValidNode);
               //mMoveableTiles.push_back(std::make_pair((currentInvestigateArea)->first - BattleMapConstants::ONE_TILE_DIFFERENCE,
               //                                        (currentInvestigateArea)->second));
               //newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first - BattleMapConstants::ONE_TILE_DIFFERENCE,
               //                                             (currentInvestigateArea)->second));
            }

            
            // Check the tile below of the investigate tile.
            currentColumn = (*currentInvestigateArea)->Column;
            currentRow = (*currentInvestigateArea)->Row + BattleMapConstants::ONE_TILE_DIFFERENCE;
            foundMoveableTileIterator = std::find_if(mMoveableTiles.begin(),
                                                     mMoveableTiles.end(),
                                                     [currentColumn, currentRow](const TileNode* d){return d->Column == currentColumn && d->Row == currentRow;});
            if (foundMoveableTileIterator == mMoveableTiles.end() &&
                IsTileOccupied((*currentInvestigateArea)->Column, (*currentInvestigateArea)->Row + BattleMapConstants::ONE_TILE_DIFFERENCE) == false)
            {
               TileNode* ValidNode = new TileNode();
               ValidNode->Column = currentColumn;
               ValidNode->Row = currentRow;
               ValidNode->DistanceFromCurrentShip = currentMovementDistance + 1;
               mMoveableTiles.push_back(ValidNode);
               newInvestigateAreas.push_back(ValidNode);
               //mMoveableTiles.push_back(std::make_pair((currentInvestigateArea)->first + BattleMapConstants::ONE_TILE_DIFFERENCE,
               //                                        (currentInvestigateArea)->second));
               //newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first + BattleMapConstants::ONE_TILE_DIFFERENCE,
               //                                             (currentInvestigateArea)->second));
            }

            // Check the tile to the left of the investigate tile.
            currentColumn = (*currentInvestigateArea)->Column - BattleMapConstants::ONE_TILE_DIFFERENCE;
            currentRow = (*currentInvestigateArea)->Row;
            foundMoveableTileIterator = std::find_if(mMoveableTiles.begin(),
                                                     mMoveableTiles.end(),
                                                     [currentColumn, currentRow](const TileNode* d){return d->Column == currentColumn && d->Row == currentRow;});
            if (foundMoveableTileIterator == mMoveableTiles.end() &&
                IsTileOccupied((*currentInvestigateArea)->Column - BattleMapConstants::ONE_TILE_DIFFERENCE, (*currentInvestigateArea)->Row) == false)
            {
               TileNode* ValidNode = new TileNode();
               ValidNode->Column = currentColumn;
               ValidNode->Row = currentRow;
               ValidNode->DistanceFromCurrentShip = currentMovementDistance + 1;
               mMoveableTiles.push_back(ValidNode);
               newInvestigateAreas.push_back(ValidNode);
               //mMoveableTiles.push_back(std::make_pair((currentInvestigateArea)->first,
               //                                        (currentInvestigateArea)->second - BattleMapConstants::ONE_TILE_DIFFERENCE));
               //newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first,
               //                                             (currentInvestigateArea)->second - BattleMapConstants::ONE_TILE_DIFFERENCE));
            }

            // Check the tile to the right of the investigate tile.
            currentColumn = (*currentInvestigateArea)->Column + BattleMapConstants::ONE_TILE_DIFFERENCE;
            currentRow = (*currentInvestigateArea)->Row;
            foundMoveableTileIterator = std::find_if(mMoveableTiles.begin(),
                                                     mMoveableTiles.end(),
                                                     [currentColumn, currentRow](const TileNode* d){return d->Column == currentColumn && d->Row == currentRow;});
            if (foundMoveableTileIterator == mMoveableTiles.end() &&
                IsTileOccupied((*currentInvestigateArea)->Column + BattleMapConstants::ONE_TILE_DIFFERENCE, (*currentInvestigateArea)->Row) == false)
            {
               TileNode* ValidNode = new TileNode();
               ValidNode->Column = currentColumn;
               ValidNode->Row = currentRow;
               ValidNode->DistanceFromCurrentShip = currentMovementDistance + 1;
               mMoveableTiles.push_back(ValidNode);
               newInvestigateAreas.push_back(ValidNode);
               //mMoveableTiles.push_back(std::make_pair((currentInvestigateArea)->first,
               //                                        (currentInvestigateArea)->second + BattleMapConstants::ONE_TILE_DIFFERENCE));
               //newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first,
               //                                             (currentInvestigateArea)->second + BattleMapConstants::ONE_TILE_DIFFERENCE));
            }
         }

         // Transfer the data from the new investigate areas container to the investigate areas container for the next iteratio to know which tiles
         // to search from.
         investigateAreas.clear();
         investigateAreas = newInvestigateAreas;
         newInvestigateAreas.clear();
      }

      // Clear the investigate area container.
      investigateAreas.clear();
   }
}

//***************************************************************************************************************************************************
//
// Method Name: CalculateShipsAttackableArea
//
// Description:
//  TODO: Add description.
//
//***************************************************************************************************************************************************
void BattleMap::CalculateShipsAttackableArea()
{
   // Stop any unecessary processing in finding which tiles are needed by knowing that there are areas already found in the Already Found areas
   // container. THe reasoning is becuase the Already Found container will be cleared once the ship moves, allowing processing for the next set of
   // areas to be found at the new ship location.
   if ((mpCurrentShipsActionTurn != nullptr) && (mAttackableTiles.empty() == true))
   {
      // Holds the list of tile locations to investigate from for more moveable spaces.
      std::vector<std::pair<int, int>> investigateAreas;
      // List of new areas found from the investigate areas container.
      std::vector<std::pair<int, int>> newInvestigateAreas;
      std::vector<std::pair<int, int>> invalidAreas;

      // Add the ships location as the starting investigate area.
      investigateAreas.push_back(std::make_pair(mpCurrentShipsActionTurn->GetTileColumn() / 64,
                                                mpCurrentShipsActionTurn->GetTileRow() / 64));

      // Add the ships location as a tile where it can move to.
      invalidAreas.push_back(std::make_pair(mpCurrentShipsActionTurn->GetTileColumn() / 64,
                                            mpCurrentShipsActionTurn->GetTileRow() / 64));

      // For as many movement spaces that are left, check which tiles are needed in the moveable tile container for the tiles the ship can traverse
      // to.
      for (int currentInvalidAttackableDistance = 0;
           currentInvalidAttackableDistance < mpCurrentShipsActionTurn->GetWeaponMinimumRange();
           currentInvalidAttackableDistance++)
      {
         // For each tile that is to be investigated this iteration, search for each adjacent tile to check if it's already added to the moveable
         // tiles container. If they aren't found in the moveable tiles container, then add them to the moveable tiles and new areas to investigate
         // containers so the next iteration will know what tiles are already found and which tiles to check next respectfully.
         for (auto currentInvestigateArea = investigateAreas.begin();
              currentInvestigateArea < investigateAreas.end();
              currentInvestigateArea++)
         {
            // Check the tile above of the investigate tile.
            auto foundInvalidAttackableTileIterator = std::find(invalidAreas.begin(),
                                                                invalidAreas.end(),
                                                                std::make_pair((currentInvestigateArea)->first - BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                                (currentInvestigateArea)->second));
            if (foundInvalidAttackableTileIterator == invalidAreas.end())
            {
               invalidAreas.push_back(std::make_pair((currentInvestigateArea)->first - BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                       (currentInvestigateArea)->second));
               newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first - BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                            (currentInvestigateArea)->second));
            }

            // Check the tile below of the investigate tile.
            foundInvalidAttackableTileIterator = std::find(invalidAreas.begin(),
                                                           invalidAreas.end(),
                                                           std::make_pair((currentInvestigateArea)->first + BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                           (currentInvestigateArea)->second));
            if (foundInvalidAttackableTileIterator == invalidAreas.end())
            {
               invalidAreas.push_back(std::make_pair((currentInvestigateArea)->first + BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                     (currentInvestigateArea)->second));
               newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first + BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                            (currentInvestigateArea)->second));
            }

            // Check the tile to the left of the investigate tile.
            foundInvalidAttackableTileIterator = std::find(invalidAreas.begin(),
                                                           invalidAreas.end(),
                                                           std::make_pair((currentInvestigateArea)->first,
                                                           (currentInvestigateArea)->second - BattleMapConstants::ONE_TILE_DIFFERENCE));
            if (foundInvalidAttackableTileIterator == invalidAreas.end())
            {
               invalidAreas.push_back(std::make_pair((currentInvestigateArea)->first,
                                                     (currentInvestigateArea)->second - BattleMapConstants::ONE_TILE_DIFFERENCE));
               newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first,
                                                            (currentInvestigateArea)->second - BattleMapConstants::ONE_TILE_DIFFERENCE));
            }

            // Check the tile to the right of the investigate tile.
            foundInvalidAttackableTileIterator = std::find(invalidAreas.begin(),
                                                           invalidAreas.end(),
                                                           std::make_pair((currentInvestigateArea)->first,
                                                           (currentInvestigateArea)->second + BattleMapConstants::ONE_TILE_DIFFERENCE));
            if (foundInvalidAttackableTileIterator == invalidAreas.end())
            {
               invalidAreas.push_back(std::make_pair((currentInvestigateArea)->first,
                                                     (currentInvestigateArea)->second + BattleMapConstants::ONE_TILE_DIFFERENCE));
               newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first,
                                                            (currentInvestigateArea)->second + BattleMapConstants::ONE_TILE_DIFFERENCE));
            }
         }

         // Transfer the data from the new investigate areas container to the investigate areas container for the next iteratio to know which tiles
         // to search from.
         investigateAreas.clear();
         investigateAreas = newInvestigateAreas;
         newInvestigateAreas.clear();
      }

      // Clear the investigate area container.
      investigateAreas.clear();

      //*********************************************************************************************************************************************

      // Add the ships location as the starting investigate area.
      investigateAreas.push_back(std::make_pair(mpCurrentShipsActionTurn->GetTileColumn() / 64,
                                                mpCurrentShipsActionTurn->GetTileRow() / 64));

      // For as many movement spaces that are left, check which tiles are needed in the moveable tile container for the tiles the ship can traverse
      // to.
      for (int currentAttackableDistance = 0;
           currentAttackableDistance < mpCurrentShipsActionTurn->GetWeaponMaximumRange();
           currentAttackableDistance++)
      {
         // For each tile that is to be investigated this iteration, search for each adjacent tile to check if it's already added to the moveable
         // tiles container. If they aren't found in the moveable tiles container, then add them to the moveable tiles and new areas to investigate
         // containers so the next iteration will know what tiles are already found and which tiles to check next respectfully.
         for (auto currentInvestigateArea = investigateAreas.begin();
              currentInvestigateArea < investigateAreas.end();
              currentInvestigateArea++)
         {
            // Check the tile above of the investigate tile.
            auto foundInvalidAttackableTileIterator = std::find(invalidAreas.begin(),
                                                                invalidAreas.end(),
                                                                std::make_pair((currentInvestigateArea)->first - BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                                               (currentInvestigateArea)->second));
            auto foundValidAttackableTileIterator = std::find(mAttackableTiles.begin(),
                                                              mAttackableTiles.end(),
                                                              std::make_pair((currentInvestigateArea)->first - BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                                             (currentInvestigateArea)->second));
            if ((foundInvalidAttackableTileIterator == invalidAreas.end()) &&
                (foundValidAttackableTileIterator == mAttackableTiles.end()))
            {
               mAttackableTiles.push_back(std::make_pair((currentInvestigateArea)->first - BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                         (currentInvestigateArea)->second));
               newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first - BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                            (currentInvestigateArea)->second));
            }
            else if ((foundInvalidAttackableTileIterator != invalidAreas.end()) &&
                     (foundValidAttackableTileIterator == mAttackableTiles.end()))
            {
               newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first - BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                            (currentInvestigateArea)->second));
            }

            // Check the tile below of the investigate tile.
            foundInvalidAttackableTileIterator = std::find(invalidAreas.begin(),
                                                           invalidAreas.end(),
                                                           std::make_pair((currentInvestigateArea)->first + BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                           (currentInvestigateArea)->second));
            foundValidAttackableTileIterator = std::find(mAttackableTiles.begin(),
                                                         mAttackableTiles.end(),
                                                         std::make_pair((currentInvestigateArea)->first + BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                         (currentInvestigateArea)->second));
            if ((foundInvalidAttackableTileIterator == invalidAreas.end()) &&
                (foundValidAttackableTileIterator == mAttackableTiles.end()))
            {
               mAttackableTiles.push_back(std::make_pair((currentInvestigateArea)->first + BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                         (currentInvestigateArea)->second));
               newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first + BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                            (currentInvestigateArea)->second));
            }
            else if ((foundInvalidAttackableTileIterator != invalidAreas.end()) &&
                     (foundValidAttackableTileIterator == mAttackableTiles.end()))
            {
               newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first + BattleMapConstants::ONE_TILE_DIFFERENCE,
                                                            (currentInvestigateArea)->second));
            }

            // Check the tile to the left of the investigate tile.
            foundInvalidAttackableTileIterator = std::find(invalidAreas.begin(),
                                                           invalidAreas.end(),
                                                           std::make_pair((currentInvestigateArea)->first,
                                                                          (currentInvestigateArea)->second - BattleMapConstants::ONE_TILE_DIFFERENCE));
            foundValidAttackableTileIterator = std::find(mAttackableTiles.begin(),
                                                         mAttackableTiles.end(),
                                                         std::make_pair((currentInvestigateArea)->first,
                                                                        (currentInvestigateArea)->second - BattleMapConstants::ONE_TILE_DIFFERENCE));
            if ((foundInvalidAttackableTileIterator == invalidAreas.end()) &&
                (foundValidAttackableTileIterator == mAttackableTiles.end()))
            {
               mAttackableTiles.push_back(std::make_pair((currentInvestigateArea)->first,
                                                         (currentInvestigateArea)->second - BattleMapConstants::ONE_TILE_DIFFERENCE));
               newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first,
                                                            (currentInvestigateArea)->second - BattleMapConstants::ONE_TILE_DIFFERENCE));
            }
            else if ((foundInvalidAttackableTileIterator != invalidAreas.end()) &&
                     (foundValidAttackableTileIterator == mAttackableTiles.end()))
            {
               newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first,
                                                            (currentInvestigateArea)->second - BattleMapConstants::ONE_TILE_DIFFERENCE));
            }

            // Check the tile to the right of the investigate tile.
            foundInvalidAttackableTileIterator = std::find(invalidAreas.begin(),
                                                           invalidAreas.end(),
                                                           std::make_pair((currentInvestigateArea)->first,
                                                                          (currentInvestigateArea)->second + BattleMapConstants::ONE_TILE_DIFFERENCE));
            foundValidAttackableTileIterator = std::find(mAttackableTiles.begin(),
                                                         mAttackableTiles.end(),
                                                         std::make_pair((currentInvestigateArea)->first,
                                                                        (currentInvestigateArea)->second + BattleMapConstants::ONE_TILE_DIFFERENCE));
            if ((foundInvalidAttackableTileIterator == invalidAreas.end()) &&
                (foundValidAttackableTileIterator == mAttackableTiles.end()))
            {
               mAttackableTiles.push_back(std::make_pair((currentInvestigateArea)->first,
                                                         (currentInvestigateArea)->second + BattleMapConstants::ONE_TILE_DIFFERENCE));
               newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first,
                                                            (currentInvestigateArea)->second + BattleMapConstants::ONE_TILE_DIFFERENCE));
            }
            else if ((foundInvalidAttackableTileIterator != invalidAreas.end()) &&
                     (foundValidAttackableTileIterator == mAttackableTiles.end()))
            {
               newInvestigateAreas.push_back(std::make_pair((currentInvestigateArea)->first,
                                                            (currentInvestigateArea)->second + BattleMapConstants::ONE_TILE_DIFFERENCE));
            }
         }

         // Transfer the data from the new investigate areas container to the investigate areas container for the next iteratio to know which tiles
         // to search from.
         investigateAreas.clear();
         investigateAreas = newInvestigateAreas;
         newInvestigateAreas.clear();
      }

      // Clear the investigate area container.
      investigateAreas.clear();
   }
}

void BattleMap::CalculateMovementPath(TileNode* theEndTile)
{
   TileNode* lookedAtTile = theEndTile;
   mMovementPath.insert(mMovementPath.begin(), lookedAtTile);

   for(int Count = theEndTile->DistanceFromCurrentShip; Count > 0; Count--)
   {
      // Check tile above.
      int column = lookedAtTile->Column;
      int row = lookedAtTile->Row - 1;
      auto foundValidTile = std::find_if(mMoveableTiles.begin(),
                                         mMoveableTiles.end(),
                                         [column, row](const TileNode* d){return d->Row == row && d->Column == column;});
      if(foundValidTile != mMoveableTiles.end() &&
         (*foundValidTile)->DistanceFromCurrentShip == (lookedAtTile->DistanceFromCurrentShip - 1))
      {
         lookedAtTile = *foundValidTile;
         mMovementPath.insert(mMovementPath.begin(), *foundValidTile);
         continue;
      }

      // Check tile left.
      column = lookedAtTile->Column - 1;
      row = lookedAtTile->Row;
      foundValidTile = std::find_if(mMoveableTiles.begin(),
                                    mMoveableTiles.end(),
                                    [column, row](const TileNode* d){return d->Row == row && d->Column == column;});
      if(foundValidTile != mMoveableTiles.end() &&
         (*foundValidTile)->DistanceFromCurrentShip == (lookedAtTile->DistanceFromCurrentShip - 1))
      {
         lookedAtTile = *foundValidTile;
         mMovementPath.insert(mMovementPath.begin(), *foundValidTile);
         continue;
      }

      // Check tile below.
      column = lookedAtTile->Column;
      row = lookedAtTile->Row + 1;
      foundValidTile = std::find_if(mMoveableTiles.begin(),
                                    mMoveableTiles.end(),
                                    [column, row](const TileNode* d){return d->Row == row && d->Column == column;});
      if(foundValidTile != mMoveableTiles.end() &&
         (*foundValidTile)->DistanceFromCurrentShip == (lookedAtTile->DistanceFromCurrentShip - 1))
      {
         lookedAtTile = *foundValidTile;
         mMovementPath.insert(mMovementPath.begin(), *foundValidTile);
         continue;
      }

      // Check tile right.
      column = lookedAtTile->Column + 1;
      row = lookedAtTile->Row;
      foundValidTile = std::find_if(mMoveableTiles.begin(),
                                    mMoveableTiles.end(),
                                    [column, row](const TileNode* d){return d->Row == row && d->Column == column;});
      if(foundValidTile != mMoveableTiles.end() &&
         (*foundValidTile)->DistanceFromCurrentShip == (lookedAtTile->DistanceFromCurrentShip - 1))
      {
         lookedAtTile = *foundValidTile;
         mMovementPath.insert(mMovementPath.begin(), *foundValidTile);
         continue;
      }
   }
}

//***************************************************************************************************************************************************
//
// Method Name: MoveShipToSelectedTile
//
// Description:
//  Move the current ship that is taking its action turn to a new tile that is within the bounds of its movement distance.
//
//***************************************************************************************************************************************************
bool BattleMap::MoveShipToSelectedTile()
{
   bool successfulMove = false;

   int column = mTileSelectorColumn;
   int row = mTileSelectorRow;

   // Check if the selected are the tile selector is at is within the bounds of moveable tiles.
   auto foundMoveableTileIterator = std::find_if(mMoveableTiles.begin(),
                                                 mMoveableTiles.end(),
                                                 [column, row](const TileNode* d){return d->Column == column && d->Row == row;});
   if(foundMoveableTileIterator != mMoveableTiles.end())
   {
      CalculateMovementPath(*foundMoveableTileIterator);

      // The tile selector selected a valid moveable tile so the ship is moved to where the tile selector is.
      //mpCurrentShipsActionTurn->SetTileColumn(mTileSelectorColumn);
      //mpCurrentShipsActionTurn->SetTileRow(mTileSelectorRow);

      // Clear the moveable tiles container as this will need to be updated as new movement needs to be calculated.
      //mMoveableTiles.clear();

      // TODO: Remove when necessary post testing.
      //mAttackableTiles.clear();

      //mpBattleMenu->SetMenuLocation(mpCurrentShipsActionTurn->GetTileColumn() * 64, mpCurrentShipsActionTurn->GetTileRow() * 64);

      // Indicate that the move was successful.
      successfulMove = true;
   }

   return successfulMove;
}

//***************************************************************************************************************************************************
//
// Method Name: AttackSelectedTile
//
// Description:
//  Move the current ship that is taking its action turn to a new tile that is within the bounds of its movement distance.
//
//***************************************************************************************************************************************************
bool BattleMap::AttackSelectedTile()
{
   bool successfulMove = false;
   float angle = 0.0;

   // Check if the selected are the tile selector is at is within the bounds of moveable tiles.
   auto foundAttackableTileIterator = std::find(mAttackableTiles.begin(),
                                                mAttackableTiles.end(),
                                                std::make_pair(mTileSelectorColumn,
                                                               mTileSelectorRow));
   if(foundAttackableTileIterator != mAttackableTiles.end())
   {
         mAttackedTileX = (*foundAttackableTileIterator).first * 64;
         mAttackedTileY = (*foundAttackableTileIterator).second * 64;

         switch (mpCurrentShipsActionTurn->GetDirection())
         {
            case DIRECTION::UP:
            {
               angle = atan2((((*foundAttackableTileIterator).second * 64) + 32) - (mpCurrentShipsActionTurn->GetTileRow() + 46),
                             (((*foundAttackableTileIterator).first * 64) + 32) - (mpCurrentShipsActionTurn->GetTileColumn() + 32));
               break;
            }
            case DIRECTION::DOWN:
            {
               angle = atan2((((*foundAttackableTileIterator).second * 64) + 32) - (mpCurrentShipsActionTurn->GetTileRow() + 18),
                             (((*foundAttackableTileIterator).first * 64) + 32) - (mpCurrentShipsActionTurn->GetTileColumn() + 32));
               break;
            }
            case DIRECTION::LEFT:
            {
               angle = atan2((((*foundAttackableTileIterator).second * 64) + 32) - (mpCurrentShipsActionTurn->GetTileRow() + 32),
                             (((*foundAttackableTileIterator).first * 64) + 32) - (mpCurrentShipsActionTurn->GetTileColumn() + 46));
               break;
            }
            case DIRECTION::RIGHT:
            {
               angle = atan2((((*foundAttackableTileIterator).second * 64) + 32) - (mpCurrentShipsActionTurn->GetTileRow() + 32),
                             (((*foundAttackableTileIterator).first * 64) + 32) - (mpCurrentShipsActionTurn->GetTileColumn() + 18));
               break;
            }
         }

         angle = (angle/3.14F*180) + (angle > 0 ? 0 : 360);

         mWeaponAngle = angle + 90 % 360;

         //mpCurrentShipsActionTurn->SetWeaponAngle((angle * (3.14F/180.0F)) - mpCurrentShipsActionTurn->GetShipAngle());

      //// Iterate through the list of player ships and damage the on at the tile selected.
      //for (auto ShipIterator = mpPlayerShips.begin(); ShipIterator != mpPlayerShips.end();)
      //{
      //   if ((*ShipIterator)->GetTileColumn() / 64 == foundAttackableTileIterator->first &&
      //       (*ShipIterator)->GetTileRow() / 64 == foundAttackableTileIterator->second)
      //   {
      //      (*ShipIterator)->TakeDamage(mpCurrentShipsActionTurn->GetWeaponDamage());
      //
      //      if ((*ShipIterator)->GetCurrentHealth() <= 0)
      //      {
      //         delete *ShipIterator;
      //         ShipIterator = mpPlayerShips.erase(ShipIterator);
      //      }
      //      else
      //      {
      //         ShipIterator++;
      //      }
      //   }
      //   else
      //   {
      //      ShipIterator++;
      //   }
      //}
      //
      //// Iterate through the list of enemy ships and draw them at the tile location the ship is indicated to be at.
      //for (auto ShipIterator = mpEnemyShips.begin(); ShipIterator != mpEnemyShips.end();)
      //{
      //   if ((*ShipIterator)->GetTileColumn() / 64 == foundAttackableTileIterator->first &&
      //       (*ShipIterator)->GetTileRow() / 64 == foundAttackableTileIterator->second)
      //   {
      //      (*ShipIterator)->TakeDamage(mpCurrentShipsActionTurn->GetWeaponDamage());
      //
      //      if ((*ShipIterator)->GetCurrentHealth() <= 0)
      //      {
      //         delete *ShipIterator;
      //         ShipIterator = mpEnemyShips.erase(ShipIterator);
      //      }
      //      else
      //      {
      //         ShipIterator++;
      //      }
      //   }
      //   else
      //   {
      //      ShipIterator++;
      //   }
      //}


      // Clear the moveable tiles container as this will need to be updated as new movement needs to be calculated.
      mMoveableTiles.clear();

      // TODO: Remove when necessary post testing.
      mAttackableTiles.clear();

      mpBattleMenu->SetMenuLocation(mpCurrentShipsActionTurn->GetTileColumn(), mpCurrentShipsActionTurn->GetTileRow());

      // Indicate that the move was successful.
      successfulMove = true;
   }

   return successfulMove;
}

//***************************************************************************************************************************************************
//
// Method Name: DetermineStateFromMenu
//
// Description:
//  Retrieve the selection index from the battle menu and determine which battle state to change to.
//     Index 0 - Switch to the ship movement selector state.
//     Index 1 - Switch to the attack selector state.
//     Index 2 - Switch to the determining state to decide which state is next to take its action turn.
//
//***************************************************************************************************************************************************
void BattleMap::DetermineStateFromMenu()
{
   // Retrieve the selection index from the battle menu.
   int selection = mpBattleMenu->GetSelectionIndex();
   
   // The selection index is to switch to the movement selector state.
   if (selection == 0)
   {
      mCurrentBattleState = BattleState::MOVE;
   }
   // The selection index is to switch to the attack selector state.
   else if (selection == 1)
   {
      mCurrentBattleState = BattleState::ATTACK;
   }
   // The selection index is to switch to the determining state. The ship that is finishing its action turn has its action level reset.
   else
   {
      mCurrentBattleState = BattleState::DETERMINING;
      mpCurrentShipsActionTurn->ResetActionLevel();
      mpBattleMenu->ResetCursor();
   }   
}

//***************************************************************************************************************************************************
//
// Method Name: DetermineNextActionTurn
//
// Description:
//  Determines which ship is next to take its action turn. If no ship is taking its action turn then increment all ships action level by their
//  speeds.
//
//***************************************************************************************************************************************************
void BattleMap::DetermineNextActionTurn()
{
   // Only occurs while in the determining state.
   if (mCurrentBattleState == BattleState::DETERMINING)
   {
      // Iterate through all the player ships.
      for (auto ShipIterator = mpPlayerShips.begin(); ShipIterator != mpPlayerShips.end(); ShipIterator++)
      {
         // Check if the next ship has reached the action level where it can take its action turn.
         if ((*ShipIterator)->GetActionLevel() >= 100)
         {
            // Set that this ship is now going to take its action turn.
            mpCurrentShipsActionTurn = (*ShipIterator);
            // Set the battle menu to display to the right of the ship.
            mpBattleMenu->SetMenuLocation(mpCurrentShipsActionTurn->GetTileColumn(), mpCurrentShipsActionTurn->GetTileRow());
            // Now calculate the moveable area for this ship.
            CalculateShipsMoveableArea();
            //
            CalculateShipsAttackableArea();
            // Change the battle state to be the main battle menu for this ship to start taking its action turn.
            mCurrentBattleState = BattleState::MENU_MAIN;
            // Break from the for loop.
            break;
         }
         // The ship being checked has not reached the action level where it can take its action turn.
         else
         {
            // Increment this ships action level by its speed.
            (*ShipIterator)->IncrementActionLevel();
         }
      }
   }
}

bool BattleMap::AreSame(double a, double b)
{
    return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
}

//***************************************************************************************************************************************************
//
// Method Name: Update
//
// Description:
//  TODO: Add description.
//
//***************************************************************************************************************************************************
void BattleMap::Update(float theElapsedTime)
{
   float weaponAngle = 0.0F;

   mpBattleMenu->Update(theElapsedTime);
   mpTileSelectorImage->Update(theElapsedTime);

   if(mCurrentBattleState == BattleState::MOVE_ANIMATION)
   {
      mElapsedTime += theElapsedTime;

      if (mElapsedTime > mMoveTime)
      {
         if(mpCurrentShipsActionTurn->GetTileColumn() < (mMovementPath.front()->Column * 64))
         {
            if (mpCurrentShipsActionTurn->GetDirection() != DIRECTION::RIGHT)
            {
               switch(mpCurrentShipsActionTurn->GetDirection())
               {
                  case DIRECTION::LEFT:
                  {
                     mpCurrentShipsActionTurn->SetShipAngle(mpCurrentShipsActionTurn->GetShipAngle() - (5.0f * (3.14f/180.0f)));
                     mTurningCount++;

                     if(mTurningCount == 36)
                     {
                        mTurningCount = 0;
                        mpCurrentShipsActionTurn->SetDirection(DIRECTION::RIGHT);
                     }
                     break;
                  }
                  case DIRECTION::UP:
                  {
                     mpCurrentShipsActionTurn->SetShipAngle(mpCurrentShipsActionTurn->GetShipAngle() + (5.0f * (3.14f/180.0f)));
                     mTurningCount++;

                     if(mTurningCount == 18)
                     {
                        mTurningCount = 0;
                        mpCurrentShipsActionTurn->SetDirection(DIRECTION::RIGHT);
                     }
                     break;
                  }
                  case DIRECTION::DOWN:
                  {
                     mpCurrentShipsActionTurn->SetShipAngle(mpCurrentShipsActionTurn->GetShipAngle() - (5.0f * (3.14f/180.0f)));
                     mTurningCount++;

                     if(mTurningCount == 18)
                     {
                        mTurningCount = 0;
                        mpCurrentShipsActionTurn->SetDirection(DIRECTION::RIGHT);
                     }
                     break;
                  }
                  default:
                  {
                  }
               }
            }
            else
            {
            mpCurrentShipsActionTurn->SetTileColumn(mpCurrentShipsActionTurn->GetTileColumn() + 2);
            }
         }
         else if(mpCurrentShipsActionTurn->GetTileColumn() > (mMovementPath.front()->Column * 64))
         {
            if (mpCurrentShipsActionTurn->GetDirection() != DIRECTION::LEFT)
            {
               switch(mpCurrentShipsActionTurn->GetDirection())
               {
                  case DIRECTION::RIGHT:
                  {
                     mpCurrentShipsActionTurn->SetShipAngle(mpCurrentShipsActionTurn->GetShipAngle() + (5.0f * (3.14f/180.0f)));
                     mTurningCount++;

                     if(mTurningCount == 36)
                     {
                        mTurningCount = 0;
                        mpCurrentShipsActionTurn->SetDirection(DIRECTION::LEFT);
                     }
                     break;
                  }
                  case DIRECTION::UP:
                  {
                     mpCurrentShipsActionTurn->SetShipAngle(mpCurrentShipsActionTurn->GetShipAngle() - (5.0f * (3.14f/180.0f)));
                     mTurningCount++;

                     if(mTurningCount == 18)
                     {
                        mTurningCount = 0;
                        mpCurrentShipsActionTurn->SetDirection(DIRECTION::LEFT);
                     }
                     break;
                  }
                  case DIRECTION::DOWN:
                  {
                     mpCurrentShipsActionTurn->SetShipAngle(mpCurrentShipsActionTurn->GetShipAngle() + (5.0f * (3.14f/180.0f)));
                     mTurningCount++;

                     if(mTurningCount == 18)
                     {
                        mTurningCount = 0;
                        mpCurrentShipsActionTurn->SetDirection(DIRECTION::LEFT);
                     }
                     break;
                  }
                  default:
                  {
                  }
               }
            }
            else
            {
               mpCurrentShipsActionTurn->SetTileColumn(mpCurrentShipsActionTurn->GetTileColumn() - 2);
            }
         }
         else if(mpCurrentShipsActionTurn->GetTileRow() < (mMovementPath.front()->Row * 64))
         {
            if (mpCurrentShipsActionTurn->GetDirection() != DIRECTION::DOWN)
            {
               switch(mpCurrentShipsActionTurn->GetDirection())
               {
                  case DIRECTION::UP:
                  {
                     mpCurrentShipsActionTurn->SetShipAngle(mpCurrentShipsActionTurn->GetShipAngle() - (5.0f * (3.14f/180.0f)));
                     mTurningCount++;

                     if(mTurningCount == 36)
                     {
                        mTurningCount = 0;
                        mpCurrentShipsActionTurn->SetDirection(DIRECTION::DOWN);
                     }
                     break;
                  }
                  case DIRECTION::LEFT:
                  {
                     mpCurrentShipsActionTurn->SetShipAngle(mpCurrentShipsActionTurn->GetShipAngle() - (5.0f * (3.14f/180.0f)));
                     mTurningCount++;

                     if(mTurningCount == 18)
                     {
                        mTurningCount = 0;
                        mpCurrentShipsActionTurn->SetDirection(DIRECTION::DOWN);
                     }
                     break;
                  }
                  case DIRECTION::RIGHT:
                  {
                     mpCurrentShipsActionTurn->SetShipAngle(mpCurrentShipsActionTurn->GetShipAngle() + (5.0f * (3.14f/180.0f)));
                     mTurningCount++;

                     if(mTurningCount == 18)
                     {
                        mTurningCount = 0;
                        mpCurrentShipsActionTurn->SetDirection(DIRECTION::DOWN);
                     }
                     break;
                  }
                  default:
                  {
                  }
               }
            }
            else
            {
               mpCurrentShipsActionTurn->SetTileRow(mpCurrentShipsActionTurn->GetTileRow() + 2);
            }
         }
         else if(mpCurrentShipsActionTurn->GetTileRow() > (mMovementPath.front()->Row * 64))
         {
            if (mpCurrentShipsActionTurn->GetDirection() != DIRECTION::UP)
            {
               switch(mpCurrentShipsActionTurn->GetDirection())
               {
                  case DIRECTION::DOWN:
                  {
                     mpCurrentShipsActionTurn->SetShipAngle(mpCurrentShipsActionTurn->GetShipAngle() - (5.0f * (3.14f/180.0f)));
                     mTurningCount++;

                     if(mTurningCount == 36)
                     {
                        mTurningCount = 0;
                        mpCurrentShipsActionTurn->SetDirection(DIRECTION::UP);
                     }
                     break;
                  }
                  case DIRECTION::LEFT:
                  {
                     mpCurrentShipsActionTurn->SetShipAngle(mpCurrentShipsActionTurn->GetShipAngle() + (5.0f * (3.14f/180.0f)));
                     mTurningCount++;

                     if(mTurningCount == 18)
                     {
                        mTurningCount = 0;
                        mpCurrentShipsActionTurn->SetDirection(DIRECTION::UP);
                     }
                     break;
                  }
                  case DIRECTION::RIGHT:
                  {
                     mpCurrentShipsActionTurn->SetShipAngle(mpCurrentShipsActionTurn->GetShipAngle() - (5.0f * (3.14f/180.0f)));
                     mTurningCount++;

                     if(mTurningCount == 18)
                     {
                        mTurningCount = 0;
                        mpCurrentShipsActionTurn->SetDirection(DIRECTION::UP);
                     }
                     break;
                  }
                  default:
                  {
                  }
               }
            }
            else
            {
               mpCurrentShipsActionTurn->SetTileRow(mpCurrentShipsActionTurn->GetTileRow() - 2);
            }
         }

         if(mMovementPath.empty() == false &&
            mpCurrentShipsActionTurn->GetTileColumn() == (mMovementPath.front()->Column * 64) &&
            mpCurrentShipsActionTurn->GetTileRow() == (mMovementPath.front()->Row * 64))
         {
            mMovementPath.erase(mMovementPath.begin());
         }

         if (mMovementPath.empty() == true)
         {
            // Free memory used.
            for(auto Iterator = mMoveableTiles.begin();
                Iterator != mMoveableTiles.end();
                Iterator++)
            {
               delete *Iterator;
            }
            mMoveableTiles.clear();
            mAttackableTiles.clear();

            mpBattleMenu->SetMenuLocation(mpCurrentShipsActionTurn->GetTileColumn(), mpCurrentShipsActionTurn->GetTileRow());

            mCurrentBattleState = BattleState::MENU_MAIN;
         }

         mElapsedTime = 0.0f;
      }
   }
   else if(mCurrentBattleState == BattleState::ATTACK_SETUP)
   {
      if(mpCurrentShipsActionTurn->GetRotateOnAttack() == true)
      {
         float curentWeaponAngle = mpCurrentShipsActionTurn->GetWeaponAngle() * (180.0F/3.14F);
         if ((curentWeaponAngle >= (fmod((mWeaponAngle - 1.0F) - mpCurrentShipsActionTurn->GetShipAngle() * (180.0F/3.14F), 360.0F))) &&
             (curentWeaponAngle <= (fmod((mWeaponAngle + 1.0F) - mpCurrentShipsActionTurn->GetShipAngle() * (180.0F/3.14F), 360.0F))))
         {
            switch (mpCurrentShipsActionTurn->GetDirection())
            {
               case DIRECTION::UP:
               {
                  mpProjectiles.push_back(new Projectile(*mpGraphics,
                                                         mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileFilePath(),
                                                         mpCurrentShipsActionTurn->GetTileColumn() + 32,
                                                         mpCurrentShipsActionTurn->GetTileRow() + 46,
                                                         mpCurrentShipsActionTurn->GetWeaponAngle() + mpCurrentShipsActionTurn->GetShipAngle(),
                                                         mpDisplay,
                                                         mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileWidth(),
                                                         mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileHeight()));
                  break;
               }
               case DIRECTION::DOWN:
               {
                  mpProjectiles.push_back(new Projectile(*mpGraphics,
                                                         mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileFilePath(),
                                                         mpCurrentShipsActionTurn->GetTileColumn() + 32,
                                                         mpCurrentShipsActionTurn->GetTileRow() + 18,
                                                         mpCurrentShipsActionTurn->GetWeaponAngle() + mpCurrentShipsActionTurn->GetShipAngle(),
                                                         mpDisplay,
                                                         mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileWidth(),
                                                         mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileHeight()));
                  break;
               }
               case DIRECTION::LEFT:
               {
                  mpProjectiles.push_back(new Projectile(*mpGraphics,
                                                         mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileFilePath(),
                                                         mpCurrentShipsActionTurn->GetTileColumn() + 46,
                                                         mpCurrentShipsActionTurn->GetTileRow() + 32,
                                                         mpCurrentShipsActionTurn->GetWeaponAngle() + mpCurrentShipsActionTurn->GetShipAngle(),
                                                         mpDisplay,
                                                         mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileWidth(),
                                                         mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileHeight()));
                  break;
               }
               case DIRECTION::RIGHT:
               {
                  mpProjectiles.push_back(new Projectile(*mpGraphics,
                                                         mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileFilePath(),
                                                         mpCurrentShipsActionTurn->GetTileColumn() + 18,
                                                         mpCurrentShipsActionTurn->GetTileRow() + 32,
                                                         mpCurrentShipsActionTurn->GetWeaponAngle() + mpCurrentShipsActionTurn->GetShipAngle(),
                                                         mpDisplay,
                                                         mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileWidth(),
                                                         mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileHeight()));
                  break;
               }
            }

            mCurrentBattleState = BattleState::ATTACK_ANIMATION;
         }
         else
         {
            curentWeaponAngle += 1.0F;
            curentWeaponAngle = fmod(curentWeaponAngle, 360.0F);
            
            mpCurrentShipsActionTurn->SetWeaponAngle(curentWeaponAngle * (3.14F/180.0F));
         }
      }
      else
      {
         switch (mpCurrentShipsActionTurn->GetDirection())
         {
            case DIRECTION::UP:
            {
               mpProjectiles.push_back(new Projectile(*mpGraphics,
                                                      mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileFilePath(),
                                                      mpCurrentShipsActionTurn->GetTileColumn() + 32,
                                                      mpCurrentShipsActionTurn->GetTileRow() + 46,
                                                      mWeaponAngle * (3.14F/180.0F),
                                                      mpDisplay,
                                                      mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileWidth(),
                                                      mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileHeight()));
               break;
            }
            case DIRECTION::DOWN:
            {
               mpProjectiles.push_back(new Projectile(*mpGraphics,
                                                      mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileFilePath(),
                                                      mpCurrentShipsActionTurn->GetTileColumn() + 32,
                                                      mpCurrentShipsActionTurn->GetTileRow() + 18,
                                                      mWeaponAngle * (3.14F/180.0F),
                                                      mpDisplay,
                                                      mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileWidth(),
                                                      mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileHeight()));
               break;
            }
            case DIRECTION::LEFT:
            {
               mpProjectiles.push_back(new Projectile(*mpGraphics,
                                                      mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileFilePath(),
                                                      mpCurrentShipsActionTurn->GetTileColumn() + 46,
                                                      mpCurrentShipsActionTurn->GetTileRow() + 32,
                                                      mWeaponAngle * (3.14F/180.0F),
                                                      mpDisplay,
                                                      mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileWidth(),
                                                      mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileHeight()));
               break;
            }
            case DIRECTION::RIGHT:
            {
               mpProjectiles.push_back(new Projectile(*mpGraphics,
                                                      mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileFilePath(),
                                                      mpCurrentShipsActionTurn->GetTileColumn() + 18,
                                                      mpCurrentShipsActionTurn->GetTileRow() + 32,
                                                      mWeaponAngle * (3.14F/180.0F),
                                                      mpDisplay,
                                                      mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileWidth(),
                                                      mpCurrentShipsActionTurn->GetWeaponData()->GetProjectileHeight()));
               break;
            }
         }

         mCurrentBattleState = BattleState::ATTACK_ANIMATION;
      }
   }
   else if(mCurrentBattleState == BattleState::ATTACK_ANIMATION)
   {
      for (auto ProjectileIterator = mpProjectiles.begin(); ProjectileIterator != mpProjectiles.end();)
      {
         (*ProjectileIterator)->Update();

         if(((*ProjectileIterator)->GetCoordinateX() >= (mAttackedTileX + 16)) &&
            ((*ProjectileIterator)->GetCoordinateX() <= (mAttackedTileX + 64 - 16)) &&
            ((*ProjectileIterator)->GetCoordinateY() >= (mAttackedTileY + 16)) &&
            ((*ProjectileIterator)->GetCoordinateY() <= (mAttackedTileY + 64 - 16)))
         {
            delete *ProjectileIterator;
            ProjectileIterator = mpProjectiles.erase(ProjectileIterator);
         }
         else
         {
            ProjectileIterator++;
         }
      }

      if (mpProjectiles.empty() == true)
      {
         mCurrentBattleState = BattleState::MENU_MAIN;
      }
   }
}

bool BattleMap::IsTileOccupied(int theColumn, int theRow)
{
   bool isOccupied = false;

   // Iterate through the list of player ships and draw them at the tile location the ship is indicated to be at.
   for (auto ShipIterator = mpPlayerShips.begin(); ShipIterator != mpPlayerShips.end(); ShipIterator++)
   {
      if (theColumn == (*ShipIterator)->GetTileColumn() / 64 &&
          theRow == (*ShipIterator)->GetTileRow() / 64)
      {
         isOccupied = true;
      }
   }

   // Iterate through the list of enemy ships and draw them at the tile location the ship is indicated to be at.
   for (auto ShipIterator = mpEnemyShips.begin(); ShipIterator != mpEnemyShips.end(); ShipIterator++)
   {
      if (theColumn == (*ShipIterator)->GetTileColumn() / 64 &&
          theRow == (*ShipIterator)->GetTileRow() / 64)
      {
         isOccupied = true;
      }
   }

   return isOccupied;
}

//***************************************************************************************************************************************************
//
// Method Name: Draw
//
// Description:
//  Draw everything on the battle map that needs to drawn based on the current state of the battle map.
//
//***************************************************************************************************************************************************
void BattleMap::Draw(Graphics& theGraphics)
{
   // Determine which battle state is occurring.
   switch (mCurrentBattleState)
   {
      // The battle state to determine which ship will be next to take its action turn next.
      case BattleState::DETERMINING:
      {
         // Draw the tile for the map and the ships on the map.
         DrawBattleMapTiles();
         DrawShips(theGraphics);
         break;
      }
      case BattleState::MENU_MAIN:
      {
         // Draw the tile for the map, the ships on the map, and the battle menu.
         DrawBattleMapTiles();
         DrawShips(theGraphics);
         mpBattleMenu->DrawMenu();
         mpBattleMenu->DrawCursor(theGraphics);
         break;
      }
      case BattleState::MOVE:
      {
         // Draw the tile for the map, the moveable area that the ship can traverse to, the ships on the map, and the tile selector.
         DrawBattleMapTiles();
         DrawShipsMoveableArea();
         DrawShips(theGraphics);
         DrawTileSelector(theGraphics);
         break;
      }
      case BattleState::ATTACK:
      {
         DrawBattleMapTiles();
         DrawShipsAttackableArea();
         DrawShips(theGraphics);
         DrawTileSelector(theGraphics);
         break;
      }
      case BattleState::ATTACK_ANIMATION:
      {
         DrawBattleMapTiles();
         DrawShips(theGraphics);
         DrawProjectiles(theGraphics);
         break;
      }
      default:
      {
         // Draw the tile for the map and the ships on the map.
         DrawBattleMapTiles();
         DrawShips(theGraphics);
      }
   }
}

//***************************************************************************************************************************************************
//
// Method Name: DrawBattleMapTiles
//
// Description:
//  Draw the tiles of the battle map by iterating through the 2D battle map array and drawing the indicate tile at each location.
//
//***************************************************************************************************************************************************
void BattleMap::DrawBattleMapTiles()
{
   // Load the image used for the tiles.
   ALLEGRO_BITMAP* pTileImage;
   pTileImage = al_load_bitmap("Images/SpaceTile.png");
  
   // Create a color mask for the magenta color which will amke any magenta color in the image to be completely transparent.
   al_convert_mask_to_alpha(pTileImage,
                            OverallProjectConstants::MAGENTA_COLOR);

   // Note: This is prototype code and will be updated. Will need to know which tile in the tile sheet to use and how to draw just that tile.
   // Iterate through all the columns and rows of the battle and draw the tile.
   for (int currentRow = 0;
        currentRow < mNumberOfTileRows;
        currentRow++)
   {
      for (int currentColumn = 0;
           currentColumn < mNumberOfTileColumns;
           currentColumn++)
      {
         al_draw_bitmap(pTileImage,
                        currentRow * OverallProjectConstants::TILE_HEIGHT,
                        currentColumn * OverallProjectConstants::TILE_WIDTH,
                        BattleMapConstants::DRAW_BITMAP_NO_FLAG);
      }
   }

   // Clean up memory by destroying the bitmap.
   al_destroy_bitmap(pTileImage);
}

//***************************************************************************************************************************************************
//
// Method Name: DrawShipsMoveableArea
//
// Description:
//  Draw the moveable areas the ship can move to by iterating the moveable tile container and drawing an indication at each tile location in the
//  container.
//
//***************************************************************************************************************************************************
void BattleMap::DrawShipsMoveableArea()
{
   // Load the image used for the moveable tile location.
   ALLEGRO_BITMAP* pMoveableTile;
   pMoveableTile = al_load_bitmap("Images/MoveableAreaTile.png");
   
   // Create a color mask for the magenta color which will amke any magenta color in the image to be completely transparent.
   al_convert_mask_to_alpha(pMoveableTile,
                            OverallProjectConstants::MAGENTA_COLOR);

   // Iterate through the list of moveable tiles and draw indication of where the player can select.
   for (auto currentMoveableTileIterator = mMoveableTiles.begin();
        currentMoveableTileIterator < mMoveableTiles.end();
        currentMoveableTileIterator++)
   {
      al_draw_bitmap(pMoveableTile,
                     (*currentMoveableTileIterator)->Column * OverallProjectConstants::TILE_WIDTH,
                     (*currentMoveableTileIterator)->Row * OverallProjectConstants::TILE_HEIGHT,
                     BattleMapConstants::DRAW_BITMAP_NO_FLAG);
   }

   // Clean up memory by destroying the bitmap.
   al_destroy_bitmap(pMoveableTile);
}

//***************************************************************************************************************************************************
//
// Method Name: DrawShipsAttackableArea
//
// Description:
//  TODO: Add description.
//
//***************************************************************************************************************************************************
void BattleMap::DrawShipsAttackableArea()
{
   // Load the image used for the moveable tile location.
   ALLEGRO_BITMAP* pAttackableTile;
   pAttackableTile = al_load_bitmap("Images/AttackableAreaTile.png");

   // Create a color mask for the magenta color which will amke any magenta color in the image to be completely transparent.
   al_convert_mask_to_alpha(pAttackableTile,
                            OverallProjectConstants::MAGENTA_COLOR);

   // Iterate through the list of moveable tiles and draw indication of where the player can select.
   for (auto currentAttackableTileIterator = mAttackableTiles.begin();
        currentAttackableTileIterator < mAttackableTiles.end();
        currentAttackableTileIterator++)
   {
      al_draw_bitmap(pAttackableTile,
                     currentAttackableTileIterator->first * OverallProjectConstants::TILE_WIDTH,
                     currentAttackableTileIterator->second * OverallProjectConstants::TILE_HEIGHT,
                     BattleMapConstants::DRAW_BITMAP_NO_FLAG);
   }

   // Clean up memory by destroying the bitmap.
   al_destroy_bitmap(pAttackableTile);
}

//***************************************************************************************************************************************************
//
// Method Name: DrawShips
//
// Description:
//  Draw all the ships on the display for the next frame by iterating through the each players/AIs ship list for the battle and drawing at the
//  locations the ships indicate they are at.
//
//***************************************************************************************************************************************************
void BattleMap::DrawShips(Graphics& theGraphics)
{
   // Iterate through the list of player ships and draw them at the tile location the ship is indicated to be at.
   for (auto ShipIterator = mpPlayerShips.begin(); ShipIterator != mpPlayerShips.end(); ShipIterator++)
   {
      (*ShipIterator)->Draw(theGraphics);
   }

   // Iterate through the list of enemy ships and draw them at the tile location the ship is indicated to be at.
   for (auto ShipIterator = mpEnemyShips.begin(); ShipIterator != mpEnemyShips.end(); ShipIterator++)
   {
      (*ShipIterator)->Draw(theGraphics);
   }
}

//***************************************************************************************************************************************************
//
// Method Name: DrawTileSelector
//
// Description:
//  Draw the tile selector by drawing the tile selector where it indicates it's currently located at.
//
//***************************************************************************************************************************************************
void BattleMap::DrawTileSelector(Graphics& theGraphics)
{
   // Load the image used for the tile selector.
   mpTileSelectorImage->Draw(theGraphics,
                             mTileSelectorColumn * OverallProjectConstants::TILE_WIDTH,
                             mTileSelectorRow * OverallProjectConstants::TILE_HEIGHT);
}

void BattleMap::DrawProjectiles(Graphics& theGraphics)
{
   for (auto ProjectileIterator = mpProjectiles.begin(); ProjectileIterator != mpProjectiles.end(); ProjectileIterator++)
   {
      (*ProjectileIterator)->Draw(theGraphics);
   }
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