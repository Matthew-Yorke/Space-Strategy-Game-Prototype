#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include "Game.h"

//*******************************************************************************************
//
// Method Name: main
//
// Description:
//  TODO: Add method description.
//
//*******************************************************************************************
int main()
{
   bool succesfulInitalization = false;

   Game game = Game();
   succesfulInitalization = game.Initialize();

   if (succesfulInitalization == true)
   {
      game.GameLoop();
   }

   game.Terminate();

   return 0;
}