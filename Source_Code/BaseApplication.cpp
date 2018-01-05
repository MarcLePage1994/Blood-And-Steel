
#include "BaseApplication.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <macUtils.h>
#endif

Ogre::Vector3 play1StartingPos = Ogre::Vector3(2.47939f, 5.0f, 3000.0f); 
Ogre::Vector3 play2StartingPos = Ogre::Vector3(-2.4085f, 5.0f, -3000.0f); 

//---------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
    : mRoot(0),
    mCamera(0),
	mCameraFP(0),
    mSceneMgr(0),
    mWindow(0),
	mAnimMgr(0),
	mAnimationDirection(1),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mTrayMgr(0),
    mCameraMan(0),
    mDetailsPanel(0),
    mCursorWasVisible(false),
    mShutDown(false),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0),
    mOverlaySystem(0),
	mMoveForward(false),
	mMoveBackward(false),
	mMoveRight(false),
	mMoveLeft(false),
	mRotate(false),
	m_PlayerHealth(100),
	m_DealthTimer(0.0f),
	m_ElapsedTime(0.0f), 
	//m_HitTimer(1000.0f), 
	m_HitTimer(0.0f), 
	m_FallTimer(0.0f),
	playerSpeed(5)
{
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    m_ResourcePath = Ogre::macBundlePath() + "/Contents/Resources/";
#else
    m_ResourcePath = "";
#endif
}

//---------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
    if (mTrayMgr) delete mTrayMgr;
    if (mCameraMan) delete mCameraMan;
    if (mOverlaySystem) delete mOverlaySystem;

    // Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
}

//---------------------------------------------------------------------------
bool BaseApplication::configure(void)
{
    // Show the configuration dialog and initialise the system.
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg.
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise.
        // Here we choose to let the system create a default rendering window by passing 'true'.
        mWindow = mRoot->initialise(true, "Blood And Steel: Gladiators");

        return true;
    }
    else
    {
        return false;
    }
}
//---------------------------------------------------------------------------
void BaseApplication::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);

	mAnimMgr = new animationmanager();

    // Initialize the OverlaySystem (changed for Ogre 1.9)
    mOverlaySystem = new Ogre::OverlaySystem();
    mSceneMgr->addRenderQueueListener(mOverlaySystem);

	mCameraFP = mSceneMgr->createCamera("FP_Camera"); //First person camera

	//setup FirstPerson Camera
	mCameraFP->lookAt(Ogre::Vector3(0,0,0));
	mCameraFP->setNearClipDistance(5);
}
//---------------------------------------------------------------------------
void BaseApplication::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
   // mCamera->setPosition(Ogre::Vector3(0,0,80)); 
	//mCamera->setPosition(2.47939, 159.389, 3122.53);

    // Look back along -Z
    //mCamera->lookAt(Ogre::Vector3(0,0,-300));
    mCamera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // Create a default camera controller
}
//---------------------------------------------------------------------------
void BaseApplication::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem(pl);

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    // Set initial mouse clipping size
    windowResized(mWindow);

    // Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    mInputContext.mKeyboard = mKeyboard;
    mInputContext.mMouse = mMouse;
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mInputContext, this);
    //mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //mTrayMgr->hideCursor();

	//create menu
	mTrayMgr->createButton(OgreBites::TL_LEFT,"_Create","Create Match",180.0f);
	mTrayMgr->createButton(OgreBites::TL_LEFT,"_Join","Join Match",180.0f);
	mTrayMgr->createButton(OgreBites::TL_LEFT,"_Credits","Credits",180.0f);
	mTrayMgr->createButton(OgreBites::TL_LEFT,"_Quit","Quit",180.0f);

	windowResized(mWindow);

    // Create a params panel for displaying sample details
    Ogre::StringVector items;
    items.push_back("cam.pX");
    items.push_back("cam.pY");
    items.push_back("cam.pZ");
    items.push_back("");
    items.push_back("cam.oW");
    items.push_back("cam.oX");
    items.push_back("cam.oY");
    items.push_back("cam.oZ");
    items.push_back("");
    items.push_back("Filtering");
    items.push_back("Poly Mode");

    mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(9, "Bilinear");
    mDetailsPanel->setParamValue(10, "Solid");
    mDetailsPanel->hide();

    mRoot->addFrameListener(this);
}
//---------------------------------------------------------------------------
void BaseApplication::destroyScene(void)
{
	if(jumpClock)
	{
		delete jumpClock;
	}
}
//---------------------------------------------------------------------------
void BaseApplication::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCameraFP);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

	mCameraMan->setStyle(OgreBites::CS_MANUAL); // turn off cameraMan

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	mCameraFP->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}
//---------------------------------------------------------------------------
void BaseApplication::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
            // OS X does not set the working directory relative to the app.
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location.
            if (!Ogre::StringUtil::startsWith(archName, "/", false)) // only adjust relative directories
                archName = Ogre::String(Ogre::macBundlePath() + "/" + archName);
#endif

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//---------------------------------------------------------------------------
void BaseApplication::createResourceListener(void)
{
}
//---------------------------------------------------------------------------
void BaseApplication::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//---------------------------------------------------------------------------
void BaseApplication::go(void)
{
#ifdef _DEBUG
#ifndef OGRE_STATIC_LIB
    mResourcesCfg = m_ResourcePath + "resources_d.cfg";
    mPluginsCfg = m_ResourcePath + "plugins_d.cfg";
#else
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#endif
#else
#ifndef OGRE_STATIC_LIB
    mResourcesCfg = m_ResourcePath + "resources.cfg";
    mPluginsCfg = m_ResourcePath + "plugins.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif
#endif

    if (!setup())
        return;


	// Start playing the plane's engine noise
   //soundMgr->PlaySound(ff06SoundIndex, ff06Node, &ff06SoundChannel);
   soundMgr->PlaySoundA(ff06SoundIndex, ff06Node, &ff06SoundChannel);

   // Allow the plane's engine to be heard farther away than normal sounds.
   //soundMgr->Set3DMinMaxDistance(ff06SoundChannel, 0.0, 500.0);

    mRoot->startRendering();

    // Clean up
    destroyScene();
}
//---------------------------------------------------------------------------
bool BaseApplication::setup(void)
{
    mRoot = new Ogre::Root(mPluginsCfg);

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    loadResources();

    // Create the scene
    createScene();

    createFrameListener();

	//initializeSounds();

	mNetworkGameManager.init();
	memset(mToSend, '\0', BUFLEN);

    return true;
};
//---------------------------------------------------------------------------



bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

	//////////////////////////////////////////////////////////////////
	//update time
	m_ElapsedTime = m_Timer.getMilliseconds();
	m_Timer.reset();

	//////////////////////////////////////////////////////////////////

    // Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

	//////////////////////////////////////////////////FOR NETWORK GAME
	if(m_CurrentGameState == GameStates::LOBBY && mIsPlayer1 && mNetworkGameManager.lobbySize == 1){
		if(mNetworkGameManager.lobbyListen()){
			m_player2Panel->setPosition( 0.255f, 0.25f);
			m_player2Panel->show();
		}
	}

	if(m_CurrentGameState == GameStates::LOBBY && !mIsPlayer1 && mNetworkGameManager.lobbySize > 1){
		std::vector<float> serverOutput = mNetworkGameManager.server.recieveMessage();  

		if(serverOutput.size() == 1)
		{
			if(serverOutput[0] == 1.0f)
			{
				m_CurrentGameState = GameStates::IN_GAME;
				mTrayMgr->destroyWidget("_JoinLobbyBack");
				m_LobbyPanel->hide();
				m_player1Panel->hide();
				m_player2Panel->hide();
				m_greenboxPanel->hide();

				mTrayMgr->hideCursor();

				m_ReticleHUDPanel->show();
				m_WeaponsHUDPanel->show();

				//set remote host node
				m_RemoteHostNode->setPosition(play1StartingPos);
				m_RemoteHostNode->setVisible(true);
				m_RemoteSwordEnt->setVisible(true);
				m_RemoteHelmetEnt->setVisible(true);
			}
		}
	}

	//only send position data if camera moves and in game
	if(m_CurrentGameState == GameStates::IN_GAME && mNetworkGameManager.lobbySize > 1){
		//if(mMoveForward == true || mMoveBackward == true || mMoveRight == true || mMoveLeft == true)
		if(m_CurrentLocalAnimationState != AnimationStates::IDLE || mRotate || mIsJump)
		{
			sprintf(mToSend, "%f@%f@%f@%f@%f@%f@%f@%f@", fullCharacterNode->getPosition().x, fullCharacterNode->getPosition().y ,fullCharacterNode->getPosition().z
												 , fullCharacterNode->getOrientation().w, fullCharacterNode->getOrientation().x, fullCharacterNode->getOrientation().y, fullCharacterNode->getOrientation().z
												 , (float)m_CurrentLocalAnimationState);
			mNetworkGameManager.client.sendMessage(mToSend, false); 

			//Move sun so sun stays still
			//mSunNode->translate(mCameraMan->getCamera()->getPosition() - play1StartingPos);
			//play1StartingPos = mCameraMan->getCamera()->getPosition(); 
		}
		std::vector<float> serverOutput = mNetworkGameManager.server.recieveMessage();  

		if(serverOutput.size() == 8){
			m_RemoteHostNode->setPosition(serverOutput[0], serverOutput[1], serverOutput[2]);
			m_RemoteHostNode->setOrientation(serverOutput[3],serverOutput[4],serverOutput[5],serverOutput[6]);

			int previousAnimationState = m_CurrentRemoteAnimationState;
			m_CurrentRemoteAnimationState = (int)serverOutput[7];

			//REMOTE PLAYER ANIMATIONS
			if(m_CurrentRemoteAnimationState == AnimationStates::FORWARD && previousAnimationState != m_CurrentRemoteAnimationState)
			{
				mAnimMgr->changeAnimationState("RemoteHost", "WalkAnim");
				particleCreator->getParticleSystemNode("RemoteDustCloudWalk")->setVisible(true);
			}
			else if(m_CurrentRemoteAnimationState == AnimationStates::BACKWARD && previousAnimationState != m_CurrentRemoteAnimationState)
			{
				mAnimMgr->changeAnimationState("RemoteHost", "WalkAnim");
				particleCreator->getParticleSystemNode("RemoteDustCloudWalk")->setVisible(true);
			}
			else if(m_CurrentRemoteAnimationState == AnimationStates::RIGHT && previousAnimationState != m_CurrentRemoteAnimationState)
			{
				mAnimMgr->changeAnimationState("RemoteHost", "StrafeAnim");
				particleCreator->getParticleSystemNode("RemoteDustCloudWalk")->setVisible(true);
			}
			else if(m_CurrentRemoteAnimationState == AnimationStates::LEFT && previousAnimationState != m_CurrentRemoteAnimationState)
			{
				mAnimMgr->changeAnimationState("RemoteHost", "StrafeAnim");
				particleCreator->getParticleSystemNode("RemoteDustCloudWalk")->setVisible(true);
			}
			else if(m_CurrentRemoteAnimationState == AnimationStates::ATTACKING && previousAnimationState != m_CurrentRemoteAnimationState)
			{
				mAnimMgr->changeAnimationState("RemoteHost","SwordChop");
				particleCreator->getParticleSystemNode("RemoteDustCloudWalk")->setVisible(true);
			}
			else if(m_CurrentRemoteAnimationState == AnimationStates::DEFENDING && previousAnimationState != m_CurrentRemoteAnimationState)
			{
				mAnimMgr->changeAnimationState("RemoteHost","ShieldBlock");
				particleCreator->getParticleSystemNode("RemoteDustCloudWalk")->setVisible(false);
			}
			/*else if(m_CurrentRemoteAnimationState == AnimationStates::IDLE && previousAnimationState != m_CurrentRemoteAnimationState)
			{
				mAnimMgr->changeAnimationState("RemoteHost", "IdleAnim");
				particleCreator->getParticleSystemNode("RemoteDustCloudWalk")->setVisible(false);
			}*/
			else if(m_CurrentRemoteAnimationState == AnimationStates::DEATH && previousAnimationState != m_CurrentRemoteAnimationState)
			{
				mAnimMgr->changeAnimationState("RemoteHost","DeathAnim", false);
				particleCreator->getParticleSystemNode("RemoteDustCloudWalk")->setVisible(false);

				//update score
				char buffer[32];
				//local
				m_LocalPlayerStatistics.Kills++; 
				itoa(m_LocalPlayerStatistics.Kills, buffer, 10);
				m_TextPanel->getChild("LocalKillTextArea")->setCaption(buffer);

				if(m_LocalPlayerStatistics.Deaths != 0){
					m_LocalPlayerStatistics.KD = (float)m_LocalPlayerStatistics.Kills / (float)m_LocalPlayerStatistics.Deaths; 
					std::ostringstream ss;
					ss << m_LocalPlayerStatistics.KD;
					std::string s(ss.str());
					m_TextPanel->getChild("LocalKDTextArea")->setCaption(s);
				}
				else{
					std::ostringstream ss;
					ss << m_LocalPlayerStatistics.Kills;
					std::string s(ss.str());
					m_TextPanel->getChild("LocalKDTextArea")->setCaption(s);
				}

				//remote
				m_RemotePlayerStatistics.Deaths++; 
				itoa(m_RemotePlayerStatistics.Deaths, buffer, 10);
				m_TextPanel->getChild("RemoteDeathTextArea")->setCaption(buffer);

				m_RemotePlayerStatistics.KD = (float)m_RemotePlayerStatistics.Kills / (float)m_RemotePlayerStatistics.Deaths; 
				std::ostringstream ss;
				ss << m_RemotePlayerStatistics.KD;
				std::string s(ss.str());
				m_TextPanel->getChild("RemoteKDTextArea")->setCaption(s);
			}
		}
		else if(serverOutput.size() == 1){
			//if remote host player left the game
			if(serverOutput[0] == -1.0f){
				mNetworkGameManager.client.cleanUp();
				mNetworkGameManager.lobbySize = 1; 
				m_RemoteHostNode->setVisible(false);
				m_RemoteSwordEnt->setVisible(false);
				m_RemoteHelmetEnt->setVisible(false);
			}
		}
		else{
			int previousAnimationState = m_CurrentRemoteAnimationState;
			m_CurrentRemoteAnimationState = AnimationStates::IDLE; 

			if(previousAnimationState != m_CurrentRemoteAnimationState)
			{
				mAnimMgr->changeAnimationState("RemoteHost", "IdleAnim");
				particleCreator->getParticleSystemNode("RemoteDustCloudWalk")->setVisible(false);
			}
		}

		//for player damage
		float distance = fullCharacterNode->getPosition().distance(m_RemoteHostNode->getPosition());
		if(distance <= 200.0f && m_CurrentRemoteAnimationState == AnimationStates::ATTACKING && m_CurrentLocalAnimationState != AnimationStates::DEFENDING && m_PlayerHealth != 0){

			m_HitTimer += m_ElapsedTime;

			//so the player does not take damage every frame
			if(m_HitTimer >= 1000.0f)
			{
				m_PlayerHealth -= 25; 
				m_HitTimer = 0.0f;
			}
		}
		else if(m_CurrentRemoteAnimationState != AnimationStates::ATTACKING){
			//reset hit timer
			//m_HitTimer = 1000.0f;
			m_HitTimer = 0.0f;
		}
	}

	//if player falls in the pit
	if(fullCharacterNode->getPosition().y <= -15.0f){
		m_FallTimer += m_ElapsedTime;

		//so the player does not take damage every frame
		if(m_FallTimer >= 1000.0f)
		{
			m_PlayerHealth -= 25; 
			m_FallTimer = 0.0f;
		}
	}
	else{
		m_FallTimer = 0.0f;
	}
	/////////////////////////////////////////////////////////////////

    mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRenderingQueued(evt);   // If dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible())          // If details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCamera->getDerivedPosition().x));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCamera->getDerivedPosition().y));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCamera->getDerivedPosition().z));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
            mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
            mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
            mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }
    }

	mAnimMgr->frameAnimationUpdate(evt.timeSinceLastFrame * mAnimationDirection);

	//-----------------------------------CHARACTER MOVEMENT-----------------------------------------------------
	Ogre::Vector3 trans = Ogre::Vector3(0.0f, 0.0f, 0.0f);

	if(mMoveForward == true && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mAnimationDirection = 1;
		trans += mSceneMgr->getSceneNode("fullCharacterNode")->getOrientation().zAxis() * playerSpeed;
	}
	else
	{
		mMoveForward = false;
	}

	if(mMoveBackward == true && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mAnimationDirection = -1;
		trans += mSceneMgr->getSceneNode("fullCharacterNode")->getOrientation().zAxis() * -playerSpeed;
	}
	else
	{
		mMoveBackward = false;
	}

	if(mMoveLeft == true && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mAnimationDirection = 1;
		trans += mSceneMgr->getSceneNode("fullCharacterNode")->getOrientation().xAxis() * playerSpeed;
	}
	else
	{
		mMoveLeft = false;
	}

	if(mMoveRight == true && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mAnimationDirection = -1;
		trans += mSceneMgr->getSceneNode("fullCharacterNode")->getOrientation().xAxis() * -playerSpeed;
	}
	else
	{
		mMoveRight = false;
	}

	//hide and show dust particles, depending if player is moving or not, and only translate player if vector is not full of zeros 
	if(trans == Ogre::Vector3(0.0f, 0.0f, 0.0f)){
		particleCreator->getParticleSystemNode("DustCloudWalk")->setVisible(false);
	}
	else{
		particleCreator->getParticleSystemNode("DustCloudWalk")->setVisible(true);
	}


	mSceneMgr->getSceneNode("fullCharacterNode")->translate(trans);

	//for jumping
	if(m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH)//!mOnGround)
	{
		float gravity = -9.8f * 16.0f; 
		float time = jumpClock->getMilliseconds() * 0.0001f;
		jumpVelocity = jumpVelocity + gravity *time;
		if(time>4)
		{
			jumpClock->reset();
		} 
		if(jumpVelocity < 4.0f && jumpVelocity > -4.0f && time < 0.2f)
		{
			jumpVelocity = 0;
		}
		if(mIsJump == true)
		{
			mSceneMgr->getSceneNode("fullCharacterNode")->translate(0,jumpVelocity * time ,0);

			isCollision1 = false;
			updatePhysics(); //for wals
			if(isCollision1 == true)
			{
				mSceneMgr->getSceneNode("fullCharacterNode")->translate(0,jumpVelocity * time * -1  ,0);
				jumpClock->reset();
				mIsJump = false;
			}
		}
	}

	mSceneMgr->getSceneNode("fullCharacterNode")->translate(0, -2  ,0);
	updatePhysics();
	if(isCollision1 != true)
	{
		mIsJump = true;
	}
	else
	{
		jumpClock->reset();
	}
	mSceneMgr->getSceneNode("fullCharacterNode")->translate(0, 2  ,0);
	isCollision1 = false;

	if(m_CurrentGameState == GameStates::IN_GAME)
		updatePhysics(); //first check, for floor

	if(isCollision1 == true && m_CurrentGameState == GameStates::IN_GAME)
	{
		//mSceneMgr->getSceneNode("fullCharacterNode")->translate(Ogre::Vector3(0,1,0));
		isCollision1 = false;
		{
			//mSceneMgr->getSceneNode("fullCharacterNode")->translate(Og*-re::Vector3(0,-1,0));
			mSceneMgr->getSceneNode("fullCharacterNode")->translate(-1*trans);
			//updatePhysics(); //second floor check
		}
	}


	//FOR PLAYER DAMAGE
	//show blood on screen
	if (m_PlayerHealth == 75)
	{
		m_bloodPanel1->show();
	}
	else if (m_PlayerHealth == 50)
	{
		m_bloodPanel3->show();
	}
	else if (m_PlayerHealth == 25)
	{
		m_bloodPanel4->show();
	}
	else if (m_PlayerHealth == 0)
	{
		if(m_CurrentLocalAnimationState != AnimationStates::DEATH){

			m_CurrentLocalAnimationState = AnimationStates::DEATH;
			//play death animation 

			fullCharacterNode->translate(0.0f, 10.0f, 0.0f);

			mAnimMgr->changeAnimationState("characterAnim", "DeathAnim", false);

			//update score
			char buffer[32];
			//local
			m_LocalPlayerStatistics.Deaths++; 
			itoa(m_LocalPlayerStatistics.Deaths, buffer, 10);
			m_TextPanel->getChild("LocalDeathTextArea")->setCaption(buffer);

			m_LocalPlayerStatistics.KD = (float)m_LocalPlayerStatistics.Kills / (float)m_LocalPlayerStatistics.Deaths; 
			std::ostringstream ss;
			ss << m_LocalPlayerStatistics.KD;
			std::string s(ss.str());
			m_TextPanel->getChild("LocalKDTextArea")->setCaption(s);

			//remote
			m_RemotePlayerStatistics.Kills++; 
			itoa(m_RemotePlayerStatistics.Kills, buffer, 10);
			m_TextPanel->getChild("RemoteKillTextArea")->setCaption(buffer);

			if(m_RemotePlayerStatistics.Deaths != 0){
				m_RemotePlayerStatistics.KD = (float)m_RemotePlayerStatistics.Kills / (float)m_RemotePlayerStatistics.Deaths; 
				std::ostringstream ss;
				ss << m_RemotePlayerStatistics.KD;
				std::string s(ss.str());
				m_TextPanel->getChild("RemoteKDTextArea")->setCaption(s);
			}
			else{
				std::ostringstream ss;
				ss << m_RemotePlayerStatistics.Kills;
				std::string s(ss.str());
				m_TextPanel->getChild("RemoteKDTextArea")->setCaption(s);
			}
		}
	}

	if(m_CurrentLocalAnimationState == AnimationStates::DEATH){
		m_DealthTimer += m_ElapsedTime;

		//respond player
		if(m_DealthTimer >= 5000){
			m_CurrentLocalAnimationState = AnimationStates::IDLE;
			mAnimMgr->changeAnimationState("characterAnim", "IdleAnim");

			m_bloodPanel1->hide();
			m_bloodPanel3->hide();
			m_bloodPanel4->hide();

			m_PlayerHealth = 100;

			if(mIsPlayer1){
				fullCharacterNode->setPosition(play1StartingPos);
				jumpClock->reset();
			}
			else{
				fullCharacterNode->setPosition(play2StartingPos);
			}

			m_DealthTimer = 0.0f;
		}
	}
	

	//mCameraFP->setOrientation(mSceneMgr->getEntity("Gladiator")->getSkeleton()->getBone("CrixusBaseNoRig:Head")->getOrientation()); // set the bone orientation to the camera
	mCameraFP->setOrientation(mSceneMgr->getEntity("characterAnim")->getSkeleton()->getBone("CrixusBaseNoRig:Head")->convertLocalToWorldOrientation(Ogre::Quaternion(0.0, 0.0, 1.0, 0.0))); // set the bone orientation to the camera
	
	//updatePhysics();
	mCameraMan->reverseCollision(evt);

	mRotate = false;

	syncEvents();

    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
{
    if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
    {
        mTrayMgr->toggleAdvancedFrameStats();
    }
    //else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
    //{
    //    if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
    //    {
    //        mTrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
    //        mDetailsPanel->show();
    //    }
    //    else
    //    {
    //        mTrayMgr->removeWidgetFromTray(mDetailsPanel);
    //        mDetailsPanel->hide();
    //    }
    //}
    //else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
    //{
    //    Ogre::String newVal;
    //    Ogre::TextureFilterOptions tfo;
    //    unsigned int aniso;

    //    switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
    //    {
    //    case 'B':
    //        newVal = "Trilinear";
    //        tfo = Ogre::TFO_TRILINEAR;
    //        aniso = 1;
    //        break;
    //    case 'T':
    //        newVal = "Anisotropic";
    //        tfo = Ogre::TFO_ANISOTROPIC;
    //        aniso = 8;
    //        break;
    //    case 'A':
    //        newVal = "None";
    //        tfo = Ogre::TFO_NONE;
    //        aniso = 1;
    //        break;
    //    default:
    //        newVal = "Bilinear";
    //        tfo = Ogre::TFO_BILINEAR;
    //        aniso = 1;
    //    }

    //    Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
    //    Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
    //    mDetailsPanel->setParamValue(9, newVal);
    //}
    //else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
    //{
    //    Ogre::String newVal;
    //    Ogre::PolygonMode pm;

    //    switch (mCamera->getPolygonMode())
    //    {
    //    case Ogre::PM_SOLID:
    //        newVal = "Wireframe";
    //        pm = Ogre::PM_WIREFRAME;
    //        break;
    //    case Ogre::PM_WIREFRAME:
    //        newVal = "Points";
    //        pm = Ogre::PM_POINTS;
    //        break;
    //    default:
    //        newVal = "Solid";
    //        pm = Ogre::PM_SOLID;
    //    }

    //    mCamera->setPolygonMode(pm);
    //    mDetailsPanel->setParamValue(10, newVal);
    //}
    //else if(arg.key == OIS::KC_F5)   // refresh all textures
    //{
    //    Ogre::TextureManager::getSingleton().reloadAll();
    //}
    //else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    //{
    //    mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    //}
    else if (arg.key == OIS::KC_ESCAPE)	
    {
       // mShutDown = true;
		if(m_CurrentGameState == GameStates::IN_GAME)	//go back to main menu
		{
			m_CurrentGameState = GameStates::MAIN_MENU;

			mTrayMgr->createButton(OgreBites::TL_LEFT,"_Create","Create Match",180.0f);
			mTrayMgr->createButton(OgreBites::TL_LEFT,"_Join","Join Match",180.0f);
			mTrayMgr->createButton(OgreBites::TL_LEFT,"_Credits","Credits",180.0f);
			mTrayMgr->createButton(OgreBites::TL_LEFT,"_Quit","Quit",180.0f);

			m_MainMenuPanel->show();
			mTrayMgr->showCursor();

			m_ReticleHUDPanel->hide();
			m_WeaponsHUDPanel->hide();
			m_bloodPanel1->hide();
			m_bloodPanel3->hide();
			m_bloodPanel4->hide();

			//handle leaving multiplayer game
			if(mNetworkGameManager.lobbySize > 1)
			{
				mNetworkGameManager.client.sendMessage("-1@", false);
			}

			mNetworkGameManager.client.cleanUp();
			mNetworkGameManager.lobbySize = 1;

			m_RemoteHostNode->setVisible(false);
			m_RemoteSwordEnt->setVisible(false);
			m_RemoteHelmetEnt->setVisible(false);

			m_bloodPanel1->hide();
			m_bloodPanel3->hide();
			m_bloodPanel4->hide();

			m_PlayerHealth = 100;

			//reset score
			m_TextPanel->getChild("LocalKillTextArea")->setCaption("0");
			m_TextPanel->getChild("LocalDeathTextArea")->setCaption("0");
			m_TextPanel->getChild("LocalKDTextArea")->setCaption("0.0");
			m_TextPanel->getChild("RemoteKillTextArea")->setCaption("0");
			m_TextPanel->getChild("RemoteDeathTextArea")->setCaption("0");
			m_TextPanel->getChild("RemoteKDTextArea")->setCaption("0.0");

			m_LocalPlayerStatistics = GameStatistics();
			m_RemotePlayerStatistics = GameStatistics();
		}
    }
	//else if (arg.key == OIS::KC_C)
	//{
	//	Ogre::Viewport*vp = mWindow->getViewport(0); // get a pointer to the viewport

	//	if(vp->getCamera() == mCamera){ // if 3rd person camera is active set FP cam active
	//		vp->setCamera(mCameraFP);
	//		mCameraMan->setStyle(OgreBites::CS_MANUAL); // turn off cameraMan
	//		//fpCameraMan->setStyle(OgreBites::CS_FREELOOK); // fp camera man on
	//	}
	//	else if(vp->getCamera() == mCameraFP) // if FP cam active set 3rd person cam active
	//	{
	//		vp->setCamera(mCamera);
	//		mCameraMan->setStyle(OgreBites::CS_FREELOOK); // turn on cameraMan
	//		//fpCameraMan->setStyle(OgreBites::CS_MANUAL); //fp cameraman off.
	//	}
	//}
	//show game stats
	else if(arg.key == OIS::KC_TAB && m_CurrentGameState == GameStates::IN_GAME){
		m_GameStatsPanel->show();
		m_TextPanel->show();

		m_player1Panel->setPosition( 0.15f, 0.30f);
		m_player1Panel->show();
		m_player2Panel->setPosition( 0.105f, 0.40f);
		m_player2Panel->show();
		if(mIsPlayer1){
			m_greenboxPanel->setPosition(0.375f, 0.395f);
		}
		else{
			m_greenboxPanel->setPosition(0.30f, 0.495f);
		}
		m_greenboxPanel->show();
	}
	/*else if (arg.key == OIS::KC_1)
	{
		if(m_CurrentGameState == GameStates::IN_GAME && m_PlayerHealth != 0)	
		{
			m_PlayerHealth -= 25; 
		}
	}
*/
	//else if (arg.key == OIS::KC_1)
	//{
	//	if(m_CurrentGameState == GameStates::IN_GAME)	
	//	{
	//		m_bloodPanel1->show();
	//		//m_bloodPanel2->hide();
	//		//m_bloodPanel3->hide();
	//		//m_bloodPanel4->hide();

	//		characterSound1.playShieldImpact();
	//	}
	//}
	//else if (arg.key == OIS::KC_2)
	//{
	//	if(m_CurrentGameState == GameStates::IN_GAME)	
	//	{
	//		//m_bloodPanel1->hide();
	//		m_bloodPanel2->show();
	//		//m_bloodPanel3->hide();
	//		//m_bloodPanel4->hide();
	//	}
	//}
	//else if (arg.key == OIS::KC_3)
	//{
	//	if(m_CurrentGameState == GameStates::IN_GAME)	
	//	{
	//		//m_bloodPanel1->hide();
	//		//m_bloodPanel2->hide();
	//		m_bloodPanel3->show();
	//		//m_bloodPanel4->hide();
	//	}
	//}
	//else if (arg.key == OIS::KC_4)
	//{
	//	if(m_CurrentGameState == GameStates::IN_GAME)	
	//	{
	//		//m_bloodPanel1->hide();
	//		//m_bloodPanel2->hide();
	//		//m_bloodPanel3->hide();
	//		m_bloodPanel4->show();
	//	}
	//}
	/*else if (arg.key == OIS::KC_5)
	{
		if(m_CurrentGameState == GameStates::IN_GAME)	
		{
			m_bloodPanel1->hide();
			m_bloodPanel2->hide();
			m_bloodPanel3->hide();
			m_bloodPanel4->hide();
		}
	}*/
	//ANIMATIONS
	else if(arg.key == OIS::KC_W && m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mMoveForward = true;
		if(mMoveBackward == false){
			mAnimMgr->changeAnimationState("characterAnim", "WalkAnim");
			m_CurrentLocalAnimationState = AnimationStates::FORWARD;
		}
	}
	else if(arg.key == OIS::KC_S && m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mMoveBackward = true;
		if(mMoveForward == false)
		{
			mAnimMgr->changeAnimationState("characterAnim", "WalkAnim");
			m_CurrentLocalAnimationState = AnimationStates::BACKWARD;
		}
	}
	else if(arg.key == OIS::KC_D && m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mMoveRight = true;
		if(mMoveLeft == false)
		{
			mAnimMgr->changeAnimationState("characterAnim", "StrafeAnim");
			m_CurrentLocalAnimationState = AnimationStates::RIGHT;
		}
	}
	else if(arg.key == OIS::KC_A && m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mMoveLeft = true;
		if(mMoveRight == false)
		{
			mAnimMgr->changeAnimationState("characterAnim", "StrafeAnim");
			m_CurrentLocalAnimationState = AnimationStates::LEFT;
		}
	}

	//Player speed
	else if(arg.key == OIS::KC_LSHIFT && m_CurrentGameState == GameStates::IN_GAME)
	{
		playerSpeed = 10;
	}
	else if(arg.key == OIS::KC_SPACE && m_CurrentGameState == GameStates::IN_GAME)
	{
		if(mIsJump != true)
		{
			mIsJump = true;
			mOnGround = false;
			jumpClock->reset();
			jumpVelocity = 200.0f;
		}
	}

	//only move the camera if the game is running
	if(m_CurrentGameState == GameStates::IN_GAME)
	{
		Ogre::Viewport*vp = mWindow->getViewport(0); // get a pointer to the viewport
		if(vp->getCamera() == mCamera){
			mCameraMan->injectKeyDown(arg); // only want to send move commands if the right camera is selected.
		}
	}
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::keyReleased(const OIS::KeyEvent &arg)
{
	//only move the camera if the game is running
	if(m_CurrentGameState == GameStates::IN_GAME)
	{
		Ogre::Viewport*vp = mWindow->getViewport(0); // get a pointer to the viewport
		if(vp->getCamera() == mCamera){
			mCameraMan->injectKeyUp(arg); // only want to send move commands if the right camera is selected.
		}
	}

	//ANIMATIONS
	if(arg.key == OIS::KC_W && m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mMoveForward = false;
		mAnimationDirection = 1;

		//only go back to idle if all animations are not playing
		if(mMoveBackward == false && mMoveLeft == false && mMoveRight == false){
			mAnimMgr->changeAnimationState("characterAnim", "IdleAnim");
			m_CurrentLocalAnimationState = AnimationStates::IDLE;
		}
	}
	else if(arg.key == OIS::KC_S && m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mMoveBackward = false;
		mAnimationDirection = 1;

		//only go back to idle if all animations are not playing
		if(mMoveForward == false && mMoveLeft == false && mMoveRight == false){
			mAnimMgr->changeAnimationState("characterAnim", "IdleAnim");
			m_CurrentLocalAnimationState = AnimationStates::IDLE;
		}
	}
	else if(arg.key == OIS::KC_D && m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mMoveRight = false;
		mAnimationDirection = 1;

		//only go back to idle if all animations are not playing
		if(mMoveLeft == false && mMoveBackward == false && mMoveForward == false){
			mAnimMgr->changeAnimationState("characterAnim", "IdleAnim");
			m_CurrentLocalAnimationState = AnimationStates::IDLE;
		}
	}
	else if(arg.key == OIS::KC_A && m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mMoveLeft = false;
		mAnimationDirection = 1;

		//only go back to idle if all animations are not playing
		if(mMoveRight == false && mMoveBackward == false && mMoveForward == false){
			mAnimMgr->changeAnimationState("characterAnim", "IdleAnim");
			m_CurrentLocalAnimationState = AnimationStates::IDLE;
		}
	}
	//Player speed
	else if(arg.key == OIS::KC_LSHIFT && m_CurrentGameState == GameStates::IN_GAME)
	{
		playerSpeed = 5;
	}
	//hide game stats
	else if(arg.key == OIS::KC_TAB && m_CurrentGameState == GameStates::IN_GAME){
		m_GameStatsPanel->hide();
		m_TextPanel->hide();

		m_player1Panel->hide();
		m_player2Panel->hide();
		m_greenboxPanel->hide();
	}

    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mouseMoved(const OIS::MouseEvent &arg)
{
    if (mTrayMgr->injectMouseMove(arg)) return true;
   
	//only move the camera if the game is running
	if(m_CurrentGameState == GameStates::IN_GAME)
	{
		mCameraMan->injectMouseMove(arg);

		Ogre::Viewport*vp = mWindow->getViewport(0); // get a pointer to the viewport
		if(vp->getCamera() == mCameraFP && m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH){
		//	mCameraFP->yaw(Ogre::Degree(-arg.state.X.rel * 0.15f));

			mSceneMgr->getSceneNode("fullCharacterNode")->rotate(Ogre::Vector3(0,1,0),Ogre::Degree(-arg.state.X.rel * 0.15f),Ogre::Node::TS_LOCAL);
			mRotate = true;
		}
	}
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	//Animations
	if(id == OIS::MB_Left && m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mAnimMgr->changeAnimationState("characterAnim","SwordChop");
		m_CurrentLocalAnimationState = AnimationStates::ATTACKING;
	}
	else if(id == OIS::MB_Right && m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		mAnimMgr->changeAnimationState("characterAnim","ShieldBlock");
		m_CurrentLocalAnimationState = AnimationStates::DEFENDING;
	}

    if (mTrayMgr->injectMouseDown(arg, id)) return true;
    
	//only move the camera if the game is running
	if(m_CurrentGameState == GameStates::IN_GAME)
	{
		mCameraMan->injectMouseDown(arg, id);
	}
    return true;
}
//---------------------------------------------------------------------------
bool BaseApplication::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	//Animations
	if(id == OIS::MB_Left && m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		if(mMoveLeft == false && mMoveRight == false && mMoveBackward == false && mMoveForward == false){
			mAnimMgr->changeAnimationState("characterAnim","IdleAnim");
			m_CurrentLocalAnimationState = AnimationStates::IDLE;
		}
		else if(mMoveForward == true)
		{
			if(mMoveBackward == false){
				mAnimMgr->changeAnimationState("characterAnim", "WalkAnim");
				m_CurrentLocalAnimationState = AnimationStates::FORWARD;
			}
		}
		else if(mMoveBackward == true)
		{
			if(mMoveForward == false)
			{
				mAnimMgr->changeAnimationState("characterAnim", "WalkAnim");
				m_CurrentLocalAnimationState = AnimationStates::BACKWARD;
			}
		}
		else if(mMoveRight == true)
		{
			if(mMoveLeft == false)
			{
				mAnimMgr->changeAnimationState("characterAnim", "StrafeAnim");
				m_CurrentLocalAnimationState = AnimationStates::RIGHT;
			}
		}
		else if(mMoveLeft == true)
		{
			if(mMoveRight == false)
			{
				mAnimMgr->changeAnimationState("characterAnim", "StrafeAnim");
				m_CurrentLocalAnimationState = AnimationStates::LEFT;
			}
		}

	}
	else if(id == OIS::MB_Right && m_CurrentGameState == GameStates::IN_GAME && m_CurrentLocalAnimationState != AnimationStates::DEATH)
	{
		if(mMoveLeft == false && mMoveRight == false && mMoveBackward == false && mMoveForward == false){
			mAnimMgr->changeAnimationState("characterAnim","IdleAnim");
			m_CurrentLocalAnimationState = AnimationStates::IDLE;
		}
		else if(mMoveForward == true)
		{
			if(mMoveBackward == false){
				mAnimMgr->changeAnimationState("characterAnim", "WalkAnim");
				m_CurrentLocalAnimationState = AnimationStates::FORWARD;
			}
		}
		else if(mMoveBackward == true)
		{
			if(mMoveForward == false)
			{
				mAnimMgr->changeAnimationState("characterAnim", "WalkAnim");
				m_CurrentLocalAnimationState = AnimationStates::BACKWARD;
			}
		}
		else if(mMoveRight == true)
		{
			if(mMoveLeft == false)
			{
				mAnimMgr->changeAnimationState("characterAnim", "StrafeAnim");
				m_CurrentLocalAnimationState = AnimationStates::RIGHT;
			}
		}
		else if(mMoveLeft == true)
		{
			if(mMoveRight == false)
			{
				mAnimMgr->changeAnimationState("characterAnim", "StrafeAnim");
				m_CurrentLocalAnimationState = AnimationStates::LEFT;
			}
		}
	}

    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    
	//only move the camera if the game is running
	if(m_CurrentGameState == GameStates::IN_GAME)
	{
		mCameraMan->injectMouseUp(arg, id);
	}
    return true;
}
//---------------------------------------------------------------------------
// Adjust mouse clipping area
void BaseApplication::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}
//---------------------------------------------------------------------------
// Unattach OIS before window shutdown (very important under Linux)
void BaseApplication::windowClosed(Ogre::RenderWindow* rw)
{
    // Only close for window that created OIS (the main window in these demos)
    if(rw == mWindow)
    {
        if(mInputManager)
        {
            mInputManager->destroyInputObject(mMouse);
            mInputManager->destroyInputObject(mKeyboard);

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}
//---------------------------------------------------------------------------
void BaseApplication::buttonHit(OgreBites::Button* b) 
{
	if(b->getCaption() == "Create Match")
	{
		m_CurrentGameState = GameStates::LOBBY;

		mTrayMgr->destroyWidget("_Create");
		mTrayMgr->destroyWidget("_Join");
		mTrayMgr->destroyWidget("_Credits");
		mTrayMgr->destroyWidget("_Quit");

		mTrayMgr->createButton(OgreBites::TL_BOTTOM,"_Start","Start",180.0f);
		mTrayMgr->createButton(OgreBites::TL_BOTTOMRIGHT,"_LobbyBack","Back",180.0f);

		m_MainMenuPanel->hide();
		m_LobbyPanel->show();

		mIsPlayer1 = true;

	//////LOCAL PLAYER
		LocalKillTextArea->setPosition(0, 0);
		LocalDeathTextArea->setPosition(200, 0);
		LocalKDTextArea->setPosition(400, 0);

	//////REMOTE PLAYER
		RemoteKillTextArea->setPosition(0, 100);
		RemoteDeathTextArea->setPosition(200, 100);
		RemoteKDTextArea->setPosition(400, 100);

		jumpVelocity = 0.0f;
		jumpClock->reset();

		//set Proper camera
		mCamera->setPosition(play1StartingPos + Ogre::Vector3(0, 159.389 - play1StartingPos.y, 0));
		// Look back along -Z
		mCamera->lookAt(Ogre::Vector3(0,0,-300));

		//set Proper cameraFP
		fullCharacterNode->setPosition(play1StartingPos);
		// Look back along -Z
		fullCharacterNode->setOrientation(0.0f, 0.0f, 90.0f, 0.0f);

		m_player1Panel->setPosition( 0.30f, 0.15f);
		m_player1Panel->show();
		m_greenboxPanel->setPosition(0.525f, 0.245f);
		m_greenboxPanel->show();
	}
	else if(b->getCaption() == "Join Match")
	{
		m_CurrentGameState = GameStates::SEARCH;

		mTrayMgr->destroyWidget("_Create");
		mTrayMgr->destroyWidget("_Join");
		mTrayMgr->destroyWidget("_Credits");
		mTrayMgr->destroyWidget("_Quit");

		mTrayMgr->createButton(OgreBites::TL_BOTTOMRIGHT,"_SearchBack","Back",180.0f);

		m_MainMenuPanel->hide();
		m_SearchPanel->show();

		mIsPlayer1 = false;

		jumpVelocity = 0.0f;
		jumpClock->reset();

		//////LOCAL PLAYER
		LocalKillTextArea->setPosition(0, 100);
		LocalDeathTextArea->setPosition(200, 100);
		LocalKDTextArea->setPosition(400, 100);

	//////REMOTE PLAYER
		RemoteKillTextArea->setPosition(0, 0);
		RemoteDeathTextArea->setPosition(200, 0);
		RemoteKDTextArea->setPosition(400, 0);

		//set Proper camera
		mCamera->setPosition(play2StartingPos);
		// Look back along Z
		mCamera->lookAt(Ogre::Vector3(0,0, 300));

		//set Proper cameraFP
		fullCharacterNode->setPosition(play2StartingPos);
		// Look back along -Z
		fullCharacterNode->setOrientation(0.0f, 0.0f, -90.0f, 0.0f);

		//if able to find match go to lobby
		if(mNetworkGameManager.joinMatchInit()){
			m_CurrentGameState = GameStates::LOBBY;

			mTrayMgr->destroyWidget("_SearchBack");

			//mTrayMgr->createButton(OgreBites::TL_BOTTOM,"_Start","Start",180.0f);
			mTrayMgr->createButton(OgreBites::TL_BOTTOMRIGHT,"_JoinLobbyBack","Back",180.0f);

			m_SearchPanel->hide();
			m_LobbyPanel->show();

			m_player1Panel->setPosition( 0.30f, 0.15f);
			m_player1Panel->show();
			m_player2Panel->setPosition( 0.255f, 0.25f);
			m_player2Panel->show();
			m_greenboxPanel->setPosition(0.45f, 0.345f);
			m_greenboxPanel->show();
		}
	}
	else if(b->getCaption() == "Start")
	{
		m_CurrentGameState = GameStates::IN_GAME;

		mTrayMgr->destroyWidget("_Start");
		mTrayMgr->destroyWidget("_LobbyBack");

		m_MainMenuPanel->hide();
		m_LobbyPanel->hide();
		mTrayMgr->hideCursor();

		m_player1Panel->hide();
		m_player2Panel->hide();
		m_greenboxPanel->hide();

		m_ReticleHUDPanel->show();
		m_WeaponsHUDPanel->show();

		//send message to remote hosts that game is starting
		if(mNetworkGameManager.lobbySize > 1)
		{
			mNetworkGameManager.client.sendMessage("1@", false);

			//set remote host node
			m_RemoteHostNode->setPosition(play2StartingPos);
			m_RemoteHostNode->setVisible(true);
			m_RemoteSwordEnt->setVisible(true);
			m_RemoteHelmetEnt->setVisible(true);
		}
	}
	else if(b->getCaption() == "Credits")
	{
		m_CurrentGameState = GameStates::CREDITS_MENU;

		mTrayMgr->destroyWidget("_Create");
		mTrayMgr->destroyWidget("_Join");
		mTrayMgr->destroyWidget("_Credits");
		mTrayMgr->destroyWidget("_Quit");

		mTrayMgr->createButton(OgreBites::TL_BOTTOMLEFT,"_Back","Back",180.0f);

		m_CreditsMenuPanel->show();
		m_MainMenuPanel->hide();
	}
	else if(b->getCaption() == "Quit")
	{
		mShutDown = true;
		mNetworkGameManager.cleanUp();
	}
	else if(b->getName() == "_Back")
	{
		m_CurrentGameState = GameStates::MAIN_MENU;

		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Create","Create Match",180.0f);
		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Join","Join Match",180.0f);
		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Credits","Credits",180.0f);
		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Quit","Quit",180.0f);

		mTrayMgr->destroyWidget("_Back");

		m_CreditsMenuPanel->hide();
		m_MainMenuPanel->show();
	}
	else if(b->getName() == "_LobbyBack")
	{
		m_CurrentGameState = GameStates::MAIN_MENU;

		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Create","Create Match",180.0f);
		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Join","Join Match",180.0f);
		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Credits","Credits",180.0f);
		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Quit","Quit",180.0f);

		mTrayMgr->destroyWidget("_Start");
		mTrayMgr->destroyWidget("_LobbyBack");

		m_LobbyPanel->hide();
		m_MainMenuPanel->show();

		m_player1Panel->hide();
		m_player2Panel->hide();
		m_greenboxPanel->hide();

		mNetworkGameManager.client.cleanUp();
		mNetworkGameManager.lobbySize = 1;
	}
	else if(b->getName() == "_JoinLobbyBack")
	{
		m_CurrentGameState = GameStates::MAIN_MENU;

		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Create","Create Match",180.0f);
		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Join","Join Match",180.0f);
		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Credits","Credits",180.0f);
		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Quit","Quit",180.0f);

		mTrayMgr->destroyWidget("_JoinLobbyBack");

		m_LobbyPanel->hide();
		m_MainMenuPanel->show();
		
		m_player1Panel->hide();
		m_player2Panel->hide();
		m_greenboxPanel->hide();

		mNetworkGameManager.client.cleanUp();
		mNetworkGameManager.lobbySize = 1;
	}
	else if(b->getName() == "_SearchBack")
	{
		m_CurrentGameState = GameStates::MAIN_MENU;

		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Create","Create Match",180.0f);
		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Join","Join Match",180.0f);
		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Credits","Credits",180.0f);
		mTrayMgr->createButton(OgreBites::TL_LEFT,"_Quit","Quit",180.0f);

		mTrayMgr->destroyWidget("_SearchBack");

		m_SearchPanel->hide();
		m_MainMenuPanel->show();

		mNetworkGameManager.client.cleanUp();
		mNetworkGameManager.lobbySize = 1;
	}

}
//---------------------------------------------------------------------------


void BaseApplication::syncEvents()
{
	//check state of character
	String currentState;
	Ogre::Real testNumber = 0.03;

	currentState = mAnimMgr->getCurrentAnimationState("characterAnim");
	//changeAnimationState("characterAnim","SwordChop");
	if(mAnimMgr->getCurrentAnimationTime() < testNumber)
	{
		if(currentState == "SwordChop")
		{
			characterSound1.playSwordSwing();
		}
		
		if(currentState == "ShieldBlock")
		{
			//characterSound1.playShieldImpact();
			characterSound1.playShieldLift();
		}
		
		if(currentState == "WalkAnim" || currentState == "StrafeAnim")
		{
			characterSound1.playFootstepsWalk();
		}
		else
		{
			characterSound1.stopFootstepWalk();
		}
	}
}

//---------------------------------------------------------------------------
void BaseApplication::initPhysics(){}
void BaseApplication::updatePhysics(){}
