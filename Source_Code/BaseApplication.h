
#ifndef __BaseApplication_h_
#define __BaseApplication_h_

#include "NetworkGameManager.h"
#include "animationmanager.h"
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include "SoundManager.h"
#include "characterSounds.h"

#include "ogreObjLoader.h"
#include "Particles.h"

#include "bullet-2.82-r2704\src\btBulletCollisionCommon.h"
#include "bullet-2.82-r2704\src\BulletCollision\CollisionShapes\btHeightfieldTerrainShape.h"
#include "bullet-2.82-r2704\src\BulletCollision\CollisionDispatch\btGhostObject.h"

#include "bullet-2.82-r2704\src\BulletDynamics/Character/btKinematicCharacterController.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#  include <OIS/OISEvents.h>
#  include <OIS/OISInputManager.h>
#  include <OIS/OISKeyboard.h>
#  include <OIS/OISMouse.h>

#  include <OGRE/SdkTrays.h>
#  include <OGRE/SdkCameraMan.h>
#else
#  include <OISEvents.h>
#  include <OISInputManager.h>
#  include <OISKeyboard.h>
#  include <OISMouse.h>

#  include <SdkTrays.h>
#  include <SdkCameraMan.h>
#endif

#ifdef OGRE_STATIC_LIB
#  define OGRE_STATIC_GL
#  if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#    define OGRE_STATIC_Direct3D9
// D3D10 will only work on vista, so be careful about statically linking
#    if OGRE_USE_D3D10
#      define OGRE_STATIC_Direct3D10
#    endif
#  endif
#  define OGRE_STATIC_BSPSceneManager
#  define OGRE_STATIC_ParticleFX
#  define OGRE_STATIC_CgProgramManager
#  ifdef OGRE_USE_PCZ
#    define OGRE_STATIC_PCZSceneManager
#    define OGRE_STATIC_OctreeZone
#  else
#    define OGRE_STATIC_OctreeSceneManager
#  endif
#  include "OgreStaticPluginLoader.h"
#endif

//---------------------------------------------------------------------------

//Game States
namespace GameStates{
	enum{
		MAIN_MENU,
		CREDITS_MENU,
		IN_GAME,
		LOBBY,
		SEARCH
	};
}

namespace AnimationStates{
	enum{
		IDLE,
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT,
		ATTACKING,
		DEFENDING,
		JUMPING,
		DEATH
	};
}

class GameStatistics{
public:
	GameStatistics(){
		Kills = 0;
		Deaths = 0;
		KD = 0.0f;
	}

	int Kills;
	int Deaths;
	float KD; //kill death ratio 
};

class BaseApplication : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener
{
public:
    BaseApplication(void);
    virtual ~BaseApplication(void);

    virtual void go(void);

protected:
    virtual bool setup();
    virtual bool configure(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
    virtual void createFrameListener(void);
    virtual void createScene(void) = 0; // Override me!
    virtual void destroyScene(void);
    virtual void createViewports(void);
    virtual void setupResources(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	//virtual void initializeSounds();

	virtual void initPhysics();
	virtual void updatePhysics();

    virtual bool keyPressed(const OIS::KeyEvent &arg);
    virtual bool keyReleased(const OIS::KeyEvent &arg);
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

    // Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw);
    // Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw);
	//Handles button widget events.
	virtual void buttonHit(OgreBites::Button *b);

	virtual void syncEvents();

    Ogre::Root*                 mRoot;
    Ogre::Camera*               mCamera;
    Ogre::SceneManager*         mSceneMgr;
    Ogre::RenderWindow*         mWindow;
    Ogre::String                mResourcesCfg;
    Ogre::String                mPluginsCfg;

	//ANIMATIONS
	animationmanager*			mAnimMgr;
	Ogre::Real					mAnimationDirection; // direction/speed of the animation
	// movement boolians
	bool						mMoveForward;
	bool						mMoveBackward;
	bool						mMoveLeft;
	bool						mMoveRight;
	bool						mRotate; 
	bool						mIsJump;
	bool						mOnGround;


    Ogre::OverlaySystem*        mOverlaySystem;

    // OgreBites
    OgreBites::InputContext     mInputContext;
    OgreBites::SdkTrayManager*	mTrayMgr;
    OgreBites::SdkCameraMan*    mCameraMan;     	// Basic camera controller
    OgreBites::ParamsPanel*     mDetailsPanel;   	// Sample details panel
    bool                        mCursorWasVisible;	// Was cursor visible before dialog appeared?
    bool                        mShutDown;

    //OIS Input devices
    OIS::InputManager*          mInputManager;
    OIS::Mouse*                 mMouse;
    OIS::Keyboard*              mKeyboard;

    // Added for Mac compatibility
    Ogre::String                m_ResourcePath;

	//Menus
	Ogre::OverlayContainer*		m_MainMenuPanel;
	Ogre::OverlayContainer*		m_CreditsMenuPanel;
	Ogre::OverlayContainer*		m_LobbyPanel;
	Ogre::OverlayContainer*		m_SearchPanel;

	Ogre::OverlayContainer*		m_GameStatsPanel;

	//HUD
	Ogre::OverlayContainer*		m_ReticleHUDPanel;
	Ogre::OverlayContainer*		m_WeaponsHUDPanel;
	Ogre::OverlayContainer*		m_bloodPanel1;
	Ogre::OverlayContainer*		m_bloodPanel3;
	Ogre::OverlayContainer*		m_bloodPanel4;

	Ogre::OverlayContainer*		m_player1Panel;
	Ogre::OverlayContainer*		m_player2Panel;
	Ogre::OverlayContainer*		m_greenboxPanel;

	Ogre::OverlayContainer*		m_TextPanel;

	GameStatistics				m_LocalPlayerStatistics;
	GameStatistics				m_RemotePlayerStatistics; 

	TextAreaOverlayElement* LocalKillTextArea;
	TextAreaOverlayElement* LocalDeathTextArea;
	TextAreaOverlayElement* LocalKDTextArea;
	TextAreaOverlayElement* RemoteKillTextArea;
	TextAreaOverlayElement* RemoteDeathTextArea;
	TextAreaOverlayElement* RemoteKDTextArea;
	

	int      ff06SoundIndex;
	int      ff06SoundChannel;
	Entity * ent;
	SoundManager*	soundMgr	;
	SceneNode *    ff06Node;
	int            gunSoundIndex;
	int            gunSoundChannel;

	//keep track of current game state
	int							m_CurrentGameState;

	//Keep track of current animation states
	int							m_CurrentLocalAnimationState;
	int							m_CurrentRemoteAnimationState; 

	int							m_PlayerHealth;

	Ogre::Timer					m_Timer;
	float						m_ElapsedTime; //time between frames
	float						m_DealthTimer; 
	float						m_HitTimer; 
	float						m_FallTimer; 

	//For network game
	NetworkGameManager			mNetworkGameManager; 
	char						mToSend[BUFLEN]; //data to send to other host

	//sun
	SceneNode*					mSunNode;

	//fps camera
	Ogre::Camera*				mCameraFP;

	//if local host player is player 1
	bool						mIsPlayer1; 

	characterSounds				characterSound1;

	//remote host 
	Ogre::SceneNode				*m_RemoteHostNode; 
	Ogre::Entity				*m_RemoteSwordEnt;
	Ogre::Entity				*m_RemoteHelmetEnt;

	//player
	Ogre::SceneNode *fullCharacterNode;
	int playerSpeed;

	//particles
	Particles* particleCreator;

	//bullet variables
	/*btKinematicCharacterController* m_character;
	class	btPairCachingGhostObject* m_ghostObject;
	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

	class btBroadphaseInterface*	m_overlappingPairCache;

	class btCollisionDispatcher*	m_dispatcher;

	class btConstraintSolver*	m_constraintSolver;

	class btDefaultCollisionConfiguration* m_collisionConfiguration;

	class btTriangleIndexVertexArray*	m_indexVertexArrays;

	btDynamicsWorld*		m_dynamicsWorld;*/

	btCollisionWorld* collisionWorld;
public:
	float jumpVelocity;
	Ogre::Timer* jumpClock;
	btPairCachingGhostObject* player, *player1, *player2;
	btCollisionObject* bulletMap;
	bool isCollision, isCollision1, isCollision2;

#ifdef OGRE_STATIC_LIB
    Ogre::StaticPluginLoader m_StaticPluginLoader;
#endif
};

//---------------------------------------------------------------------------

#endif // #ifndef __BaseApplication_h_

//---------------------------------------------------------------------------