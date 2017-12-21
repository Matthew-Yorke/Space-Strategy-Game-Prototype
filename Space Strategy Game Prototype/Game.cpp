//*************************************************************************************************
//
// File Name: Game.cpp
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
#include "allegro5/allegro.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Game.h"
#include "BattleMap.h"
#include "BattleMenu.h"

//*************************************************************************************************
//                                  Start Public Method Definitions
//*************************************************************************************************

//*******************************************************************************************
//
// Method Name: Game
//
// Description:
//  TODO: Add method description.
//
//*******************************************************************************************
Game::Game()
{
   // Initialize member variables.
   mpDisplay = nullptr;
   mpTimer = nullptr;
   mpEventQueue = nullptr;
   mIsGameDone = false;
}

//*******************************************************************************************
//
// Method Name: Initialize
//
// Description:
//  TODO: Add method description.
//
//*******************************************************************************************
bool Game::Initialize()
{
   // Intialize allegro and catch if a failure occurrs.
   if (!al_init()) {
      al_show_native_message_box(mpDisplay, "Error", "Error: al_init", "Failed to initialize allegro!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return false;
   }

   // Initialize the allegro image addon and catch if a failure occurrs.
   if (!al_init_image_addon()) {
      al_show_native_message_box(mpDisplay, "Error", "Error: al_init_image_addon", "Failed to initialize al_init_image_addon!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return false;
   }

   // Initialize the allegro primitives addon and catch if a failure occurrs.
   if (!al_init_primitives_addon()) {
      al_show_native_message_box(mpDisplay, "Error", "Error: al_init_primitives_addon", "Failed to initialize al_init_primitives_addon!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return false;
   }

   // Initialize the allegro display and catch if a failure occurrs.
   mpDisplay = al_create_display(mScreenWidth, mScreenHeight);
   if (!mpDisplay) {
      al_show_native_message_box(mpDisplay, "Error", "Error: display", "Failed to initialize display!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      return false;
   }

   // Initialize the allegro audio and catch if a failure occurrs.
   if (!al_install_audio()) {
      al_show_native_message_box(mpDisplay, "Error", "Error: audio", "Failed to initialize the audio addon!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(mpDisplay);
      return false;
   }

   // Initialize the allegro acodec and catch if a failure occurrs.
   if (!al_init_acodec_addon()) {
      al_show_native_message_box(mpDisplay, "Error", "Error: acodec", "Failed to initialize the acodec addon!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(mpDisplay);
      return false;
   }

   // Reserve samples for the allegro audio mixer and catch if a failure occurrs.
   if (!al_reserve_samples(5)) {
      al_show_native_message_box(mpDisplay, "Error", "Error: reserve samples", "Failed to reserve samples!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(mpDisplay);
      return false;
   }

   // Install the keyboard for allegro and catch if a failure occurrs.
   if (!al_install_keyboard())
   {
      al_show_native_message_box(mpDisplay, "Error", "Error: install keyboard", "Failed to install the keyboard component!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(mpDisplay);
      return false;
   }

   //Install the font addon for allegro
   al_init_font_addon();
   // Install the keyboard for allegro and catch if a failure occurrs.
   if (!al_init_font_addon())
   {
      al_show_native_message_box(mpDisplay, "Error", "Error: initialize font addon", "Failed to initialize the font addon!",
         NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(mpDisplay);
      return false;
   }

   //Install the ttf(True Type Font) for allegro
   al_init_ttf_addon();
   // Install the keyboard for allegro and catch if a failure occurrs.
   if (!al_init_ttf_addon())
   {
      al_show_native_message_box(mpDisplay, "Error", "Error: initialize ttf addon", "Failed to initialize the ttf addon!",
         NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(mpDisplay);
      return false;
   }

   // Setup the event_queue and catch if a failure occurs.
   mpEventQueue = al_create_event_queue();
   if (!mpEventQueue) {
      al_show_native_message_box(mpDisplay, "Error", "Error: al_create_event_queue", "Failed to initialize al_create_event_queue!",
                                 NULL, ALLEGRO_MESSAGEBOX_ERROR);
      al_destroy_display(mpDisplay);
      al_destroy_timer(mpTimer);
      return false;
   }

   // Set FPS to 60.
   mpTimer = al_create_timer(1.0 / 60.0);

   // Register types of events the event_queue will handle.
   // Note: Something went wrong here and caused the program to crash, will need to investigate and compare
   //       to the asteroids game.
   al_register_event_source(mpEventQueue, al_get_display_event_source(mpDisplay));
   al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
   al_register_event_source(mpEventQueue, al_get_timer_event_source(mpTimer));

   // Start the timer event.
   al_start_timer(mpTimer);

   // No failures occurred during initialization.
   return true;
}

//*******************************************************************************************
//
// Method Name: GameLoop
//
// Description:
//  TODO: Add method description.
//
//*******************************************************************************************
void Game::GameLoop()
{
   // Tracks what the next event will be from the event queue.
   ALLEGRO_EVENT nextEvent;

   // Set up the graphics used in this game.
   Graphics graphics(mpDisplay);

   // Note: This is purely to test the map file for loading and drawing the map that is currently loaded.
   BattleMap* bm = new BattleMap(graphics);
   bm->LoadMap("BattleMaps/PrototypeBattleMap.txt");
   Weapon* weapon = new Weapon(graphics, "Images/Weapon1.png", 2, 5, 5);
   Ship* StarterShip = new Ship(graphics, false, 3, 2, 1, 1);
   StarterShip->AddWeapon(weapon);
   bm->AddPlayerShip(StarterShip);
   Weapon* weapon2 = new Weapon(graphics, "Images/Weapon2.png", 0, 3, 5);
   Ship* SecondShip = new Ship(graphics, false, 2, 2, 1, 1);
   SecondShip->AddWeapon(weapon2);
   SecondShip->SetTileRow(5);
   SecondShip->SetTileColumn(5);
   bm->AddPlayerShip(SecondShip);
   bool redraw = false;
   float lastUpdateTime = static_cast<float>(al_current_time());

   // Continously loop until the game is exited.
   while (mIsGameDone == false)
   {
      //Obtain event actions before updating
      do
      {
         // Wait an obtain the next event in the event queue.
         al_wait_for_event(mpEventQueue, &nextEvent);

         // The event was the user clicking the exit button on the display.
         if (nextEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
         {
            // Indicate the the game is being exited.
            mIsGameDone = true;
         }
         // The event was the user pressing a key down.
         else if (nextEvent.type == ALLEGRO_EVENT_KEY_DOWN)
         {
            if (nextEvent.keyboard.keycode == ALLEGRO_KEY_W)
            {
               bm->UpKeyPressed();
            }
            if (nextEvent.keyboard.keycode == ALLEGRO_KEY_A)
            {
               //bm.MoveTileSelector(OverallProjectConstants::Direction::LEFT);
               bm->LeftKeyPressed();
            }
            if (nextEvent.keyboard.keycode == ALLEGRO_KEY_S)
            {
               bm->DownKeyPressed();
            }
            if (nextEvent.keyboard.keycode == ALLEGRO_KEY_D)
            {
               //bm.MoveTileSelector(OverallProjectConstants::Direction::RIGHT);
               bm->RightKeyPressed();
            }
            if (nextEvent.keyboard.keycode == ALLEGRO_KEY_Z)
            {
               bm->ActionKeyPressed();
            }
            if (nextEvent.keyboard.keycode == ALLEGRO_KEY_X)
            {
               bm->CancelKeyPressed();
            }
            if (nextEvent.keyboard.keycode == ALLEGRO_KEY_SPACE)
            {
               //bm.MoveShipToSelectedTile();
            }
            if (nextEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            {
            }
         }
         // The event was the user releasing a downed key.
         else if (nextEvent.type == ALLEGRO_EVENT_KEY_UP)
         {
            if (nextEvent.keyboard.keycode == ALLEGRO_KEY_W)
            {
            }
            if (nextEvent.keyboard.keycode == ALLEGRO_KEY_A)
            {
            }
            if (nextEvent.keyboard.keycode == ALLEGRO_KEY_S)
            {
            }
            if (nextEvent.keyboard.keycode == ALLEGRO_KEY_D)
            {
            }
         }
         // The event was a timer event.
         else if (nextEvent.type == ALLEGRO_EVENT_TIMER)
         {
            // The timer event was from the FPS timer.
            // Note: This will occurr ever 1/60th a second.
            if (nextEvent.timer.source == mpTimer)
            { 
               bm->DetermineNextActionTurn();
               //bm->CalculateShipsMoveableArea();

               const float currentTime = static_cast<float>(al_current_time());
               bm->Update(currentTime - lastUpdateTime);
               lastUpdateTime = currentTime;
               redraw = true;
            }
         }
      }
      while (!al_is_event_queue_empty(mpEventQueue));

      // Redraw 
      if (redraw == true)
      {
         redraw = false;

         bm->Draw(graphics);
         al_flip_display();
      }
   }
}

//*******************************************************************************************
//
// Method Name: Terminate
//
// Description:
//  TODO: Add method description.
//
//*******************************************************************************************
void Game::Terminate()
{
   al_destroy_display(mpDisplay);
   al_destroy_timer(mpTimer);
   al_destroy_event_queue(mpEventQueue);
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