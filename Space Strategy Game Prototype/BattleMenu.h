//************************************************************************************************************************************************
//
// File Name: BattleMenu.h
//
// Description:
//  TODO: Add file description.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     12/DD/2017     TODO: Add change description.
//
//************************************************************************************************************************************************

#ifndef BattleMenu_h
#define BattleMenu_h

//***************************************************************************************************************************************************
//
// Struct Name: Cursor
//
// Description:
//  Cursor structure that holds the image to be used and the x and y coordinate the cursor is to be drawn at.
//
//***************************************************************************************************************************************************
struct Cursor
{
   ALLEGRO_BITMAP* pCursorImage;
   int XCoordinate;
   int YCoordinate;
};

class BattleMenu
{
   //************************************************************************************************************************************************
   // Start Method Declarations
   //************************************************************************************************************************************************

public:

   //************************************************************************************************************************************************
   //
   // Method Name: BattleMenu
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
   BattleMenu();
   
   //************************************************************************************************************************************************
   //
   // Method Name: ~BattleMenu
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
   ~BattleMenu();

   //************************************************************************************************************************************************
   //
   // Method Name: MoveCursorUp
   //
   // Description:
   //  Move the cursor up on item menu in the battle menu.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void MoveCursorUp();

   //************************************************************************************************************************************************
   //
   // Method Name: MoveCursorDown
   //
   // Description:
   //  Move the cursor down on item menu in the battle menu.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void MoveCursorDown();

   //************************************************************************************************************************************************
   //
   // Method Name: DrawMenu
   //
   // Description:
   //  Draw the menu including the text of the items for the battle menu.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void DrawMenu();

   //************************************************************************************************************************************************
   //
   // Method Name: DrawCursor
   //
   // Description:
   //  Draw the cursor to the item it currently is pointing at on the battle menu.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void DrawCursor();

   //************************************************************************************************************************************************
   //
   // Method Name: GetSelectionIndex
   //
   // Description:
   //  Return the index of the item that is currently being pointed to in the battle menu.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  Returns the index value (starting at 0) for the item being pointed at in the battle menu.
   //
   //************************************************************************************************************************************************
   int GetSelectionIndex();

   //************************************************************************************************************************************************
   //
   // Method Name: SetMenuLocation
   //
   // Description:
   //  Set the X and Y coordinates for where to draw the battle menu.
   //
   // Arguments:
   //  X - The x coordinate the battle menu will be drawn at.
   //  Y - The y coordinate the battle menu will be drawn at.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void SetMenuLocation(int X, int Y);

   //************************************************************************************************************************************************
   //
   // Method Name: ResetCursor
   //
   // Description:
   //  TODO: Add description.
   //
   // Arguments:
   //  N/A
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void ResetCursor();

protected:

   // There are currently no protected methods for this class.

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

   // Pointer for the font to be used on the battle menu.
   ALLEGRO_FONT* mpMenuFont;

   // The cursor to be displayed on the battle menu.
   Cursor mMenuCursor;

   // The selection index for the item currently being pointed at by the cursor.
   int mMenuSelectionIndex;

   // The ship x coordinate to determine where to draw the battle menu at on the x axis.
   int mCurrentShipLocationX;
   
   // The ship y coordinate to determine where to draw the battle menu at on the y axis.
   int mCurrentShipLocationY;

   //************************************************************************************************************************************************
   // End Member Vairable Declarations
   //************************************************************************************************************************************************
};

#endif