//*************************************************************************************************
//
// File Name: Game.h
//
// Description:
//  TODO: Add file description.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     MM/DD/YYYY     TODO: Add history update
//
//*************************************************************************************************

#ifndef Game_h
#define Game_h

class Game
{
   //**********************************************************************************************
   //                                   Start Method Declarations
   //**********************************************************************************************
   
   public:

      //*******************************************************************************************
      //
      // Method Name: Game
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
      Game();

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
      // Method Name: GameLoop
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
      void GameLoop();

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
      
      // TODO: Add member variable descrition.
      ALLEGRO_DISPLAY* mpDisplay;

      // TODO: Add member variable descrition.
      ALLEGRO_TIMER* mpTimer;

      // TODO: Add member variable descrition.
      ALLEGRO_EVENT_QUEUE* mpEventQueue;

      // TODO: Add member variable descrition.
      bool mIsGameDone;

      // TODO: Add member variable description.
      // TODO: Move to somehwere more appropriate.
      const int mScreenWidth = 1280;

      // TODO: Add member variable description.
      // TODO: Move to somehwere more appropriate.
      const int mScreenHeight = 720;


   //**********************************************************************************************
   //                                 End Member Vairable Declarations
   //**********************************************************************************************
};

#endif