//***************************************************************************************************************************************************
//
// File Name: AnimatedSprite.h
//
// Description:
//  TODO: Add file description.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     MM/DD/YYYY     TODO: Add Description.
//
//***************************************************************************************************************************************************

#ifndef AnimatedSprite_H
#define AnimatedSprite_H

#include "Sprite.h"
#include "Graphics.h"

class AnimatedSprite : public Sprite
{
   //************************************************************************************************************************************************
   // Start Method Declarations
   //************************************************************************************************************************************************

public:
   
   //************************************************************************************************************************************************
   //
   // Method Name: AnimatedSprite
   //
   // Description:
   //  TODO: Add description.
   //
   // Arguments:
   //  theGraphics - TODO: Add description.
   //  theFilePath - TODO: Add description.
   //  theSourceX - TODO: Add description.
   //  theSourceY - TODO: Add description.
   //  theWidth - TODO: Add description.
   //  theHeight - TODO: Add description.
   //  theFps - TODO: Add description.
   //  theNumberFrames - TODO: Add description.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   AnimatedSprite(Graphics& theGraphics, const std::string theFilePath, int theSourceX, int theSourceY, int theWidth, int theHeight, float theFps,
                  int theNumberFrames);

   //************************************************************************************************************************************************
   //
   // Method Name: ~AnimatedSprite
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
   ~AnimatedSprite();

   //************************************************************************************************************************************************
   //
   // Method Name: Update
   //
   // Description:
   //  TODO: Add description.
   //
   // Arguments:
   //  theElapsedTime - TODO: Add description.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   void Update(float theElapsedTime);

protected:

   // There are currently no proected methods for this class.

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

   const float mFrameTime;

   const int mNumberFrames;

   int mCurrentFrame;

   float mElapsedTime;

   //************************************************************************************************************************************************
   // End Member Vairable Declarations
   //************************************************************************************************************************************************
};

#endif