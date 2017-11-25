//*************************************************************************************************
//
// File Name: BattleMap.cpp
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
#include "BattleMap.h"
#include <iostream>
#include <fstream>
#include <sstream>

//*************************************************************************************************
//                                  Start Public Method Definitions
//*************************************************************************************************

//*******************************************************************************************
//
// Method Name: BattleMap
//
// Description:
//  TODO: Add method description.
//
//*******************************************************************************************
BattleMap::BattleMap()
{
   mNumberOfTileRows = 0;
   mNumberOfTileColumns = 0;
}

//*******************************************************************************************
//
// Method Name: Initialize
//
// Description:
//  TODO: Add method description.
//
//*******************************************************************************************
bool BattleMap::Initialize()
{
   // No failures occurred during initialization.
   return true;
}

//*******************************************************************************************
//
// Method Name: Terminate
//
// Description:
//  TODO: Add method description.
//
//*******************************************************************************************
void BattleMap::Terminate()
{
   // Delete any previously allocated array.
   // Note: is this needed here or possibly just in the destructor of this class?
   for (int i = 0; i < mNumberOfTileRows; i++)
   {
      delete[] mpBattleMapArray[i];
   }
   delete[] mpBattleMapArray;
}

//*******************************************************************************************
//
// Method Name: LoadMap
//
// Description:
//  TODO: Add method description.
//
//*******************************************************************************************
void BattleMap::LoadMap(std::string battleMapFileName)
{
   // Delete any previously allocated array.
   for (int i = 0; i < mNumberOfTileRows; i++)
   {
      delete[] mpBattleMapArray[i];
   }
   delete[] mpBattleMapArray;

   std::string currentFileLineString("");
   int LineNumber = 0;

   std::ifstream battleMapFile;
   battleMapFile.open(battleMapFileName);

   // Make sure the file properly opened.
   if (battleMapFile.is_open() == true)
   {
      // Exit once the "end of file" is reached.
      while (battleMapFile.eof() == false)
      {
         std::getline(battleMapFile, currentFileLineString);

         if(LineNumber == 0)
         {
            std::istringstream stringStream(currentFileLineString);
            std::string ParsedString;

            // Get first number of columns
            std::getline(stringStream, ParsedString, ',');
            mNumberOfTileColumns = stoi(ParsedString);

            // Get second number in the firs line for the number or row
            std::getline(stringStream, ParsedString, ',');
            mNumberOfTileRows = stoi(ParsedString);

            mpBattleMapArray = new int* [mNumberOfTileRows];

            for (int i = 0; i < mNumberOfTileRows; i++)
               mpBattleMapArray[i] = new int [mNumberOfTileColumns];
         }
         else if ((LineNumber-1) < mNumberOfTileRows)
         {
            std::istringstream stringStream(currentFileLineString);
            std::string ParsedString;
         
            for(int i = 0; i < mNumberOfTileColumns; i++)
            {
               std::getline(stringStream, ParsedString, ',');
               mpBattleMapArray[LineNumber-1][i] = stoi(ParsedString);
            }
         }

         LineNumber++;
      }
   }

   battleMapFile.close();
}

//*******************************************************************************************
//
// Method Name: DrawBattleMap
//
// Description:
//  TODO: Add method description.
//
//*******************************************************************************************
void BattleMap::DrawBattleMap(ALLEGRO_DISPLAY* display)
{
   // Note: This is just prototyping drawing. Will need to know which tile sheet to load (could be within the map text file) and other
   //       metadata such as what does 0 mean in the map array. Also a point in the map array could be {x,y} where x determines the row
   //       and y could determine the coumn to use for the tile sheet. Will also need to protect from the case where a map isn't laoded.

   ALLEGRO_BITMAP* tileImage;
   tileImage = al_load_bitmap("C:/Users/matt/Documents/Visual Studio 2017/Projects/Space Strategy Game Prototype/Space Strategy Game Prototype/Images/SpaceTile.png");

   for(int i = 0; i < mNumberOfTileRows; i++)
   {
      for(int j = 0; j < mNumberOfTileColumns; j++)
      {
         al_draw_bitmap(tileImage, i*64, j*64, 0);
      }
   }
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