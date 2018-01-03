//***************************************************************************************************************************************************
//
// File Name: Weapon.h
//
// Description:
//  TODO: Add file description.
//
// Change History:
//  Author               Date           Description
//  Matthew D. Yorke     MM/DD/2018     TODO: Add description.
//
//***************************************************************************************************************************************************

#ifndef Projectile_H
#define Projectile_H

#include "Graphics.h"
#include "Sprite.h"

class Projectile
{
   //************************************************************************************************************************************************
   // Start Method Declarations
   //************************************************************************************************************************************************

public:

   //************************************************************************************************************************************************
   //
   // Method Name: Weapon
   //
   // Description:
   //  Constructor that sets member variables to default values.
   //
   // Arguments:
   //  theGraphics - TODO: Add description.
   //  theImageFileName - TODO: Add description.
   //  theMinimumRange - TODO: Add description.
   //  theMaximumRange - TODO: Add description.
   //  theDamage - TODO: Add description.
   //
   // Return:
   //  N/A
   //
   //************************************************************************************************************************************************
   Projectile(Graphics& theGraphics, std::string theImageFileName, int theCoordinateX, int theCoordinateY, float theAngle, ALLEGRO_DISPLAY* theDisplay, int theWidth, int theHeight);

   void Update();

   void Draw(Graphics& theGraphics);

   inline int GetCoordinateX() {return mCoordinateX;};

   inline int GetCoordinateY() {return mCoordinateY;};

   inline void SetCoordinates(int theCoordinateX, int theCoordinateY) {mCoordinateX = theCoordinateX; mCoordinateY = theCoordinateY;};

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

   Sprite* mpImage;

   float mCoordinateX;

   float mCoordinateY;

   float mAngle;

   ALLEGRO_DISPLAY* mpDisplay;

   //************************************************************************************************************************************************
   // End Member Vairable Declarations
   //************************************************************************************************************************************************
};

#endif
