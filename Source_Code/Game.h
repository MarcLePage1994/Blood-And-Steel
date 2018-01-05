
#ifndef __GAME_H_
#define __GAME_H_

#include "BaseApplication.h"

//---------------------------------------------------------------------------

class Game : public BaseApplication, public Ogre::RenderTargetListener
{
public:
    Game(void);
    virtual ~Game(void);
	virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);		//update function before the main render function is called (i.e the scene)
    virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);	//update function after the main render function is called (i.e the scene)

	virtual void initPhysics();
	virtual void updatePhysics();

protected:
    virtual void createScene(void);
	virtual void initializeSounds();
	Ogre::Rectangle2D* mFullScreenQuad;
	Ogre::Entity* gladEntity;
			Ogre::Entity* gladSpearEntity;
			Ogre::Entity* rigTestEnt;
			Ogre::Entity* runAnimEnt;
			Ogre::Entity* walkAnimEnt;
			Ogre::Entity* shieldBlockEnt;
			Ogre::Entity* dodgeRollEnt;
			Ogre::Entity* fullCharacter;
};

//---------------------------------------------------------------------------

#endif // #ifndef __GAME_H_

//---------------------------------------------------------------------------
