
#include "Game.h"

bool isCollideTemp = 0;

//---------------------------------------------------------------------------
Game::Game(void)
{
}
//---------------------------------------------------------------------------
Game::~Game(void)
{
}

//---------------------------------------------------------------------------
void Game::createScene(void)
{
	m_CurrentGameState = GameStates::MAIN_MENU;

	m_CurrentLocalAnimationState = AnimationStates::IDLE;
	m_CurrentRemoteAnimationState = AnimationStates::IDLE; 

//////////////////////////////////////////////////////////////////////////////////
	//MENUS And HUD
//////////////////////////////////////////////////////////////////////////////////

	//load textures
	Ogre::TextureManager::getSingleton().load("main_menu.jpg", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,0,1,false,Ogre::PixelFormat::PF_FLOAT32_RGB);
	Ogre::TextureManager::getSingleton().load("credits_menu.jpg", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,0,1,false,Ogre::PixelFormat::PF_FLOAT32_RGB);
	Ogre::TextureManager::getSingleton().load("game_lobby.jpg", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,0,1,false,Ogre::PixelFormat::PF_FLOAT32_RGB);
	Ogre::TextureManager::getSingleton().load("search.jpg", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,0,1,false,Ogre::PixelFormat::PF_FLOAT32_RGB);
	
	
	Ogre::TextureManager::getSingleton().load("reticule.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,0,1,false,Ogre::PixelFormat::PF_FLOAT32_RGBA);
	Ogre::TextureManager::getSingleton().load("weapons.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,0,1,false,Ogre::PixelFormat::PF_FLOAT32_RGBA);
	Ogre::TextureManager::getSingleton().load("blood1.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,0,1,false,Ogre::PixelFormat::PF_FLOAT32_RGBA);
	Ogre::TextureManager::getSingleton().load("blood3.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,0,1,false,Ogre::PixelFormat::PF_FLOAT32_RGBA);
	Ogre::TextureManager::getSingleton().load("blood4.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,0,1,false,Ogre::PixelFormat::PF_FLOAT32_RGBA);

	Ogre::TextureManager::getSingleton().load("final_stats.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,0,1,false,Ogre::PixelFormat::PF_FLOAT32_RGBA);

	Ogre::TextureManager::getSingleton().load("greenbox.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,0,1,false,Ogre::PixelFormat::PF_FLOAT32_RGBA);
	Ogre::TextureManager::getSingleton().load("player1.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,0,1,false,Ogre::PixelFormat::PF_FLOAT32_RGBA);
	Ogre::TextureManager::getSingleton().load("player2.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D,0,1,false,Ogre::PixelFormat::PF_FLOAT32_RGBA);

	// Create a material using the texture
    Ogre::MaterialPtr MainMenuMaterial = Ogre::MaterialManager::getSingleton().create( "MainMenuMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
    MainMenuMaterial->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "main_menu.jpg" );

	// Create a material using the texture
    Ogre::MaterialPtr CreditsMenuMaterial = Ogre::MaterialManager::getSingleton().create( "CreditsMenuMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
    CreditsMenuMaterial->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "credits_menu.jpg" );

	// Create a material using the texture
    Ogre::MaterialPtr LobbyMaterial = Ogre::MaterialManager::getSingleton().create( "LobbyMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
    LobbyMaterial->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "game_lobby.jpg" );

	// Create a material using the texture
    Ogre::MaterialPtr SearchMaterial = Ogre::MaterialManager::getSingleton().create( "SearchMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
    SearchMaterial->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "search.jpg" );

	// Create a material using the texture
    Ogre::MaterialPtr ReticleMaterial = Ogre::MaterialManager::getSingleton().create( "ReticleMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
    ReticleMaterial->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "reticule.png" );
	ReticleMaterial->getTechnique( 0 )->getPass( 0 )->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	ReticleMaterial->getTechnique( 0 )->getPass( 0 )->setDepthWriteEnabled(false);

	// Create a material using the texture
    Ogre::MaterialPtr WeaponsMaterial = Ogre::MaterialManager::getSingleton().create( "WeaponsMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
    WeaponsMaterial->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "weapons.png" );
	WeaponsMaterial->getTechnique( 0 )->getPass( 0 )->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	WeaponsMaterial->getTechnique( 0 )->getPass( 0 )->setDepthWriteEnabled(false);

	// Create a material using the texture
    Ogre::MaterialPtr bloodMaterial1 = Ogre::MaterialManager::getSingleton().create( "BloodMaterial1", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
    bloodMaterial1->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "blood1.png" );
	bloodMaterial1->getTechnique( 0 )->getPass( 0 )->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	bloodMaterial1->getTechnique( 0 )->getPass( 0 )->setDepthWriteEnabled(false);

	// Create a material using the texture
    Ogre::MaterialPtr bloodMaterial3 = Ogre::MaterialManager::getSingleton().create( "BloodMaterial3", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
    bloodMaterial3->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "blood3.png" );
	bloodMaterial3->getTechnique( 0 )->getPass( 0 )->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	bloodMaterial3->getTechnique( 0 )->getPass( 0 )->setDepthWriteEnabled(false);

	// Create a material using the texture
    Ogre::MaterialPtr bloodMaterial4 = Ogre::MaterialManager::getSingleton().create( "BloodMaterial4", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
    bloodMaterial4->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "blood4.png" );
	bloodMaterial4->getTechnique( 0 )->getPass( 0 )->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	bloodMaterial4->getTechnique( 0 )->getPass( 0 )->setDepthWriteEnabled(false);

	// Create a material using the texture
    Ogre::MaterialPtr GameStatsMaterial = Ogre::MaterialManager::getSingleton().create( "GameStatsMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
    GameStatsMaterial->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "final_stats.png" );
	GameStatsMaterial->getTechnique( 0 )->getPass( 0 )->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	GameStatsMaterial->getTechnique( 0 )->getPass( 0 )->setDepthWriteEnabled(false);

	// Create a material using the texture
    Ogre::MaterialPtr player1TextMaterial = Ogre::MaterialManager::getSingleton().create( "Player1TextMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
    player1TextMaterial->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "player1.png" );
	player1TextMaterial->getTechnique( 0 )->getPass( 0 )->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	player1TextMaterial->getTechnique( 0 )->getPass( 0 )->setDepthWriteEnabled(false);

	// Create a material using the texture
    Ogre::MaterialPtr player2TextMaterial = Ogre::MaterialManager::getSingleton().create( "Player2TextMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
    player2TextMaterial->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "player2.png" );
	player2TextMaterial->getTechnique( 0 )->getPass( 0 )->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	player2TextMaterial->getTechnique( 0 )->getPass( 0 )->setDepthWriteEnabled(false);

	// Create a material using the texture
    Ogre::MaterialPtr greenBoxMaterial = Ogre::MaterialManager::getSingleton().create( "GreenBoxMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
    greenBoxMaterial->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "greenbox.png" );
	greenBoxMaterial->getTechnique( 0 )->getPass( 0 )->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	greenBoxMaterial->getTechnique( 0 )->getPass( 0 )->setDepthWriteEnabled(false);
  

///////////////////////////////////////////////////////////////////////////////////
//for menus/hud
	Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
    // Create an overlay
    Ogre::Overlay* overlay = overlayManager.create( "GUIOverlay" );
 
    // Create a panel
    m_MainMenuPanel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "MainMenuPanel" ) );
    m_MainMenuPanel->setPosition( 0.0, 0.0 );
    m_MainMenuPanel->setDimensions(1.0, 1.0);
	m_MainMenuPanel->setMaterialName( "MainMenuMaterial" );

	m_CreditsMenuPanel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "CreditsMenuPanel" ) );
    m_CreditsMenuPanel->setPosition( 0.0, 0.0 );
    m_CreditsMenuPanel->setDimensions(1.0, 1.0);
	m_CreditsMenuPanel->setMaterialName("CreditsMenuMaterial");

	m_LobbyPanel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "LobbyPanel" ) );
    m_LobbyPanel->setPosition( 0.0, 0.0 );
    m_LobbyPanel->setDimensions(1.0, 1.0);
	m_LobbyPanel->setMaterialName("LobbyMaterial");

	m_SearchPanel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "SearchPanel" ) );
    m_SearchPanel->setPosition( 0.0, 0.0 );
    m_SearchPanel->setDimensions(1.0, 1.0);
	m_SearchPanel->setMaterialName("SearchMaterial");

	m_ReticleHUDPanel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "ReticlePanel" ) );
    m_ReticleHUDPanel->setPosition( 0.47f, 0.47f);
    m_ReticleHUDPanel->setDimensions(0.05f, 0.08f);
	m_ReticleHUDPanel->setMaterialName("ReticleMaterial");

	m_WeaponsHUDPanel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "WeaponsPanel" ) );
    m_WeaponsHUDPanel->setPosition( 0.9f, 0.0f);
    m_WeaponsHUDPanel->setDimensions(0.07f, 0.1f);
	m_WeaponsHUDPanel->setMaterialName("WeaponsMaterial");

	m_bloodPanel1 = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "blood1Panel" ) );
	m_bloodPanel1->setPosition( 0.0f, 0.0f );
	m_bloodPanel1->setDimensions(1.0f, 1.0f);
	m_bloodPanel1->setMaterialName( "BloodMaterial1" );

	m_bloodPanel3 = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "blood3Panel" ) );
	m_bloodPanel3->setPosition( 0.0f, 0.0f );
    m_bloodPanel3->setDimensions(1.0f, 1.0f);
	m_bloodPanel3->setMaterialName( "BloodMaterial3" );

	m_bloodPanel4 = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "blood4Panel" ) );
    m_bloodPanel4->setPosition( 0.0f, 0.0f );
    m_bloodPanel4->setDimensions(1.0f, 1.0f);
	m_bloodPanel4->setMaterialName( "BloodMaterial4" );

	m_GameStatsPanel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "GameStatsPanel" ) );
    m_GameStatsPanel->setPosition( 0.0f, 0.0f );
    m_GameStatsPanel->setDimensions(1.0f, 1.0f);
	m_GameStatsPanel->setMaterialName( "GameStatsMaterial" );

	m_player1Panel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "Player1Panel" ) );
    m_player1Panel->setPosition( 0.30f, 0.15f);
    m_player1Panel->setDimensions(0.25f, 0.25f);
	m_player1Panel->setMaterialName("Player1TextMaterial");

	m_player2Panel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "Player2Panel" ) );
    m_player2Panel->setPosition( 0.255f, 0.25f);
    m_player2Panel->setDimensions(0.25f, 0.25f);
	m_player2Panel->setMaterialName("Player2TextMaterial");

	m_greenboxPanel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "GreenBoxPanel" ) );
   // m_greenboxPanel->setPosition( 0.0, 0.0);
    m_greenboxPanel->setDimensions(0.025f, 0.05f);
	m_greenboxPanel->setMaterialName("GreenBoxMaterial");

///////////////////////////////////////////////////////////////////////////////////
	////TEXT
////////////////////////////////////////////////////////////////////
	 // create a font resource
	 ResourcePtr font = FontManager::getSingleton().create("MyFont","General");
	 // set as truetype
	 font->setParameter("type","truetype");
	 // set the .ttf file name
	 font->setParameter("source","ctrl_freak.ttf");
	 // set the size
	 font->setParameter("size","32");
	 // set the dpi
	 font->setParameter("resolution","128");
	 // load the ttf
	 font->load();

	 //---------------------------
	// Create text panel
	m_TextPanel = static_cast<OverlayContainer*>(OverlayManager::getSingleton().createOverlayElement("Panel", "PanelName"));
	m_TextPanel->setMetricsMode(Ogre::GMM_PIXELS);
	m_TextPanel->setPosition(950, 400);
	m_TextPanel->setDimensions(300, 120);

	//-------------------------------------
	// Create a text areas

//////LOCAL PLAYER
	LocalKillTextArea = static_cast<TextAreaOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("TextArea", "LocalKillTextArea"));
	LocalKillTextArea->setMetricsMode(Ogre::GMM_PIXELS);
	LocalKillTextArea->setPosition(0, 0);
	LocalKillTextArea->setDimensions(300, 120);
	LocalKillTextArea->setCharHeight(26);
	// set the font name to the font resource that you just created.
	LocalKillTextArea->setFontName("MyFont");
	// say something
	LocalKillTextArea->setCaption("0");

	LocalDeathTextArea = static_cast<TextAreaOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("TextArea", "LocalDeathTextArea"));
	LocalDeathTextArea->setMetricsMode(Ogre::GMM_PIXELS);
	LocalDeathTextArea->setPosition(200, 0);
	LocalDeathTextArea->setDimensions(300, 120);
	LocalDeathTextArea->setCharHeight(26);
	// set the font name to the font resource that you just created.
	LocalDeathTextArea->setFontName("MyFont");
	// say something
	LocalDeathTextArea->setCaption("0");

	LocalKDTextArea = static_cast<TextAreaOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("TextArea", "LocalKDTextArea"));
	LocalKDTextArea->setMetricsMode(Ogre::GMM_PIXELS);
	LocalKDTextArea->setPosition(400, 0);
	LocalKDTextArea->setDimensions(300, 120);
	LocalKDTextArea->setCharHeight(26);
	// set the font name to the font resource that you just created.
	LocalKDTextArea->setFontName("MyFont");
	// say something
	LocalKDTextArea->setCaption("0.0");

//////REMOTE PLAYER
	RemoteKillTextArea = static_cast<TextAreaOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("TextArea", "RemoteKillTextArea"));
	RemoteKillTextArea->setMetricsMode(Ogre::GMM_PIXELS);
	RemoteKillTextArea->setPosition(0, 100);
	RemoteKillTextArea->setDimensions(300, 120);
	RemoteKillTextArea->setCharHeight(26);
	// set the font name to the font resource that you just created.
	RemoteKillTextArea->setFontName("MyFont");
	// say something
	RemoteKillTextArea->setCaption("0");

	RemoteDeathTextArea = static_cast<TextAreaOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("TextArea", "RemoteDeathTextArea"));
	RemoteDeathTextArea->setMetricsMode(Ogre::GMM_PIXELS);
	RemoteDeathTextArea->setPosition(200, 100);
	RemoteDeathTextArea->setDimensions(300, 120);
	RemoteDeathTextArea->setCharHeight(26);
	// set the font name to the font resource that you just created.
	RemoteDeathTextArea->setFontName("MyFont");
	// say something
	RemoteDeathTextArea->setCaption("0");

	RemoteKDTextArea = static_cast<TextAreaOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("TextArea", "RemoteKDTextArea"));
	RemoteKDTextArea->setMetricsMode(Ogre::GMM_PIXELS);
	RemoteKDTextArea->setPosition(400, 100);
	RemoteKDTextArea->setDimensions(300, 120);
	RemoteKDTextArea->setCharHeight(26);
	// set the font name to the font resource that you just created.
	RemoteKDTextArea->setFontName("MyFont");
	// say something
	RemoteKDTextArea->setCaption("0.0");

//////////////////////////////////////////////////////////////////

    // Add the panel to the overlay
    overlay->add2D(m_MainMenuPanel);
	overlay->add2D(m_LobbyPanel);
	overlay->add2D(m_SearchPanel);
	overlay->add2D(m_CreditsMenuPanel);
	overlay->add2D(m_ReticleHUDPanel);
	overlay->add2D(m_WeaponsHUDPanel);
	overlay->add2D(m_bloodPanel1);
	overlay->add2D(m_bloodPanel3);
	overlay->add2D(m_bloodPanel4);
	overlay->add2D(m_GameStatsPanel);
	overlay->add2D(m_player1Panel);
	overlay->add2D(m_player2Panel);
	overlay->add2D(m_greenboxPanel);
	overlay->add2D(m_TextPanel);

	// Add the text area to the panel, done after adding to overlay to avoid ogre error
	m_TextPanel->addChild(LocalKillTextArea);
	m_TextPanel->addChild(LocalDeathTextArea);
	m_TextPanel->addChild(LocalKDTextArea);
	m_TextPanel->addChild(RemoteKillTextArea);
	m_TextPanel->addChild(RemoteDeathTextArea);
	m_TextPanel->addChild(RemoteKDTextArea);

    // Show the overlay
    overlay->show();
	m_CreditsMenuPanel->hide();
	m_ReticleHUDPanel->hide();
	m_WeaponsHUDPanel->hide();
	m_SearchPanel->hide();
	m_LobbyPanel->hide();
	m_bloodPanel1->hide();
	m_bloodPanel3->hide();
	m_bloodPanel4->hide();
	m_player1Panel->hide();
	m_player2Panel->hide();
	m_greenboxPanel->hide();
	m_GameStatsPanel->hide();
	m_TextPanel->hide();
	
//////////////////////////////////////////////////////////////////////////////////
	//LEVEL
//////////////////////////////////////////////////////////////////////////////////

	// Set the scene's ambient light and shadows
    mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	//mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
	mSceneMgr->setShadowCasterRenderBackFaces(true);
	//mSceneMgr->setShadowDirectionalLightExtrusionDistance(10.0f);
	//mSceneMgr->setShadowFarDistance(10.0f);
	mSceneMgr->setShadowColour(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
 
    // Create an Entity
    Ogre::Entity* arena = mSceneMgr->createEntity("Arena_vs", "Arena_V11.mesh");
	arena->setCastShadows(true);
 
    // Create a SceneNode and attach the Entity to it
    Ogre::SceneNode* arenaNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ArenaNode");
    arenaNode->attachObject(arena);

	Ogre::Vector3 lightPos = Ogre::Vector3(208.861f, 4295.51f, -15.004f); 
	Ogre::Vector3 lightDir = (Ogre::Vector3)(Ogre::Vector3(10.7127f, 106.347f , -11.2268f) - lightPos).normalise(); 
 
    // Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("directionalLight");
	light->setPosition(lightPos);
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(Ogre::Vector3(-lightDir.x, -lightDir.y, -lightDir.z));
	light->setPowerScale(100.0f);
	light->setCastShadows(true);

	//sky dome
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 15);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//REMOTE HOST

	//Ogre::Entity* RemoteHostEntity = mSceneMgr->createEntity("RemoteHost", "SwordChop.mesh");
	Ogre::Entity* RemoteHostEntity = mSceneMgr->createEntity("RemoteHost", "CrixusAllAnims.mesh");
	m_RemoteHostNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("RemoteHostNode");
	m_RemoteHostNode->attachObject(RemoteHostEntity);
	m_RemoteHostNode->scale(1, 1, 1);
	m_RemoteHostNode->setVisible(false);

	Ogre::Skeleton* RemoteSkel = RemoteHostEntity->getSkeleton();
	animationmanager::EntityAnimationState *RemoteAnimation =  new animationmanager::EntityAnimationState(RemoteHostEntity, RemoteHostEntity->getAnimationState("RunAnim"),true,true); // create the animation state
	mAnimMgr->loadEntityAnimationState(*RemoteAnimation); // push the animationstate back.

//-----------(NEW)--END FULL CHARACTER ANIMATIONS--------------

	m_RemoteSwordEnt = mSceneMgr->createEntity("RemoteSword", "SwordModel.mesh");
	m_RemoteHelmetEnt = mSceneMgr->createEntity("RemoteHelmet", "CrixusHelm.mesh");
	RemoteHostEntity->attachObjectToBone("CrixusBaseNoRig:R_Hand", m_RemoteSwordEnt, Ogre::Quaternion::IDENTITY, Ogre::Vector3::ZERO);
	RemoteHostEntity->attachObjectToBone("CrixusBaseNoRig:Head", m_RemoteHelmetEnt, Ogre::Quaternion::IDENTITY, Ogre::Vector3::ZERO);
	m_RemoteSwordEnt->setVisible(false);
	m_RemoteHelmetEnt->setVisible(false);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////Animations
///////////////////////////////////////////////////////////////////////////////

//-----------(NEW)--FULL CHARACTER ANIMATIONS-------------------
	fullCharacter = mSceneMgr->createEntity("characterAnim", "CrixusAllAnims.mesh");
	fullCharacterNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("fullCharacterNode");
	fullCharacterNode->attachObject(fullCharacter);
	fullCharacterNode->scale(1, 1, 1);
	fullCharacterNode->setPosition(600.0, 0.0, 800.0);


	//this one isnt working properly atm. fullCharacterNode might not be what i think it is
	//characterSound1 = characterSounds(soundMgr, fullCharacterNode);


	Ogre::Skeleton* fullCharacterSkel = fullCharacter->getSkeleton();
	//fullCharacterSkel->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);

	fullCharacter->attachObjectToBone("CrixusBaseNoRig:Head",mCameraFP); // attaches object to the bone, need a new camera just for FP view. Because the 3rd person camera has a fly option. 
	animationmanager::EntityAnimationState *gladiatorAnimation =  new animationmanager::EntityAnimationState(fullCharacter,fullCharacter->getAnimationState("IdleAnim"),true,true); // create the animation state
	mAnimMgr->loadEntityAnimationState(*gladiatorAnimation); // push the animationstate back.

//-----------(NEW)--END FULL CHARACTER ANIMATIONS--------------

	Ogre::Entity* swordEnt = mSceneMgr->createEntity("Sword", "SwordModel.mesh");
	fullCharacter->attachObjectToBone("CrixusBaseNoRig:R_Hand", swordEnt, Ogre::Quaternion::IDENTITY, Ogre::Vector3::ZERO);
	Ogre::Entity* helmetEnt = mSceneMgr->createEntity("Helmet", "CrixusHelm.mesh");
	fullCharacter->attachObjectToBone("CrixusBaseNoRig:Head", helmetEnt, Ogre::Quaternion::IDENTITY, Ogre::Vector3::ZERO);


//======================================================================================
//SOUNDS
//======================================================================================
	//initiate local character Sounds
	initializeSounds();

	//ff06 is just the global node for now. eventually attach to proper character
	characterSound1 = characterSounds(soundMgr, ff06Node);

//======================================================================================
//Particle Systems
//======================================================================================
	
	////Sun Particle
	//particleCreator->newParticleSystem(mSceneMgr, "Sun", "Space/Sun", Ogre::Vector3(12000.0f,10000.0f,-35.0f));
	////Tunnel Torch Particles
	//particleCreator->newParticleSystem(mSceneMgr, "torch1", "Examples/JetEngine1", Ogre::Vector3(150.0, 195.0, 2700.0));
	//particleCreator->newParticleSystem(mSceneMgr, "torch2", "Examples/JetEngine1", Ogre::Vector3(150.0, 195.0, 3036.0));
	//particleCreator->newParticleSystem(mSceneMgr, "torch3", "Examples/JetEngine1", Ogre::Vector3(-150.0, 195.0, 3036.0));
	//particleCreator->newParticleSystem(mSceneMgr, "torch4", "Examples/JetEngine1", Ogre::Vector3(-150.0, 195.0, 2700.0));
	//particleCreator->newParticleSystem(mSceneMgr, "torch5", "Examples/JetEngine1", Ogre::Vector3(-150.0, 195.0, -2750.0));
	//particleCreator->newParticleSystem(mSceneMgr, "torch6", "Examples/JetEngine1", Ogre::Vector3(-150.0, 195.0, -3088.0));
	//particleCreator->newParticleSystem(mSceneMgr, "torch7", "Examples/JetEngine1", Ogre::Vector3(150.0, 195.0, -3110.0));
	//particleCreator->newParticleSystem(mSceneMgr, "torch8", "Examples/JetEngine1", Ogre::Vector3(150.0, 195.0, -2750.0));
	////Platform Torch Particles
	//particleCreator->newParticleSystem(mSceneMgr, "platTorch1", "Examples/pitFireEffect", Ogre::Vector3(2360.0, 383.0, -185.0));
	//particleCreator->newParticleSystem(mSceneMgr, "platTorch2", "Examples/pitFireEffect", Ogre::Vector3(2360.0, 383.0, 195.0));
	////Pit Fire Particles
	//particleCreator->newParticleSystem(mSceneMgr, "FirePit", "Examples/PitFire", Ogre::Vector3(0.0, -600.0, 0.0));
	////Dust Cloud Run Particles
	//particleCreator->newParticleSystem(mSceneMgr, "DustCloudRun", "Examples/DustCloudRun", Ogre::Vector3(400.0, 0.0, 800.0));
	////Dust Cloud Walk Particles
	//particleCreator->newParticleSystem(mSceneMgr, "DustCloudWalk", "Examples/DustCloudWalk", Ogre::Vector3(600.0, 0.0, 800.0));

	particleCreator = new Particles(); 

	//Sun Particle
	particleCreator->newParticleSystem(mSceneMgr, "Sun", "Space/Sun", Ogre::Vector3(12000.0f,10000.0f,-35.0f));
	//Tunnel Torch Particles
	particleCreator->newParticleSystem(mSceneMgr, "torch1", "Examples/JetEngine1", Ogre::Vector3(150.0, 195.0, 2700.0));
	particleCreator->newParticleSystem(mSceneMgr, "torch2", "Examples/JetEngine1", Ogre::Vector3(150.0, 195.0, 3036.0));
	particleCreator->newParticleSystem(mSceneMgr, "torch3", "Examples/JetEngine1", Ogre::Vector3(-150.0, 195.0, 3036.0));
	particleCreator->newParticleSystem(mSceneMgr, "torch4", "Examples/JetEngine1", Ogre::Vector3(-150.0, 195.0, 2700.0));
	particleCreator->newParticleSystem(mSceneMgr, "torch5", "Examples/JetEngine1", Ogre::Vector3(-150.0, 195.0, -2750.0));
	particleCreator->newParticleSystem(mSceneMgr, "torch6", "Examples/JetEngine1", Ogre::Vector3(-150.0, 195.0, -3088.0));
	particleCreator->newParticleSystem(mSceneMgr, "torch7", "Examples/JetEngine1", Ogre::Vector3(150.0, 195.0, -3110.0));
	particleCreator->newParticleSystem(mSceneMgr, "torch8", "Examples/JetEngine1", Ogre::Vector3(150.0, 195.0, -2750.0));
	//Platform Torch Particles
	particleCreator->newParticleSystem(mSceneMgr, "platTorch1", "Examples/pitFireEffect", Ogre::Vector3(2360.0, 383.0, -185.0));
	particleCreator->newParticleSystem(mSceneMgr, "platTorch2", "Examples/pitFireEffect", Ogre::Vector3(2360.0, 383.0, 195.0));
	//Pit Fire Particles
	particleCreator->newParticleSystem(mSceneMgr, "FirePit", "Examples/PitFire", Ogre::Vector3(0.0, -600.0, 0.0));
	////Dust Cloud Run Particles
	//particleCreator->newParticleSystem(mSceneMgr, "DustCloudRun", "Examples/DustCloudRun", Ogre::Vector3(400.0, 0.0, 800.0));
	//Dust Cloud Walk Particles
	particleCreator->newParticleSystemAttachedToEnt(mSceneMgr, "DustCloudWalk", "Examples/DustCloudWalk", Ogre::Vector3(600.0, 0.0, 800.0), "fullCharacterNode");
	//Remote Dust Cloud Walk Particles
	particleCreator->newParticleSystemAttachedToEnt(mSceneMgr, "RemoteDustCloudWalk", "Examples/DustCloudWalk", Ogre::Vector3(600.0, 0.0, 800.0), "RemoteHostNode");
	//Atmospheric Dust Particles
	particleCreator->newParticleSystem(mSceneMgr, "DustParticles", "Examples/AtmosphericParticles", Ogre::Vector3(0.0, 0.0, 0.0));

	//only have remote dust cloud show up if there is a remote player and they are walking around
	particleCreator->getParticleSystemNode("RemoteDustCloudWalk")->setVisible(false);
//////////////////////////////////////////////////////////////////////////////
	//Render To Texture
/////////////////////////////////////////////////////////////////////////////

	
	/*CompositorManager::getSingleton().addCompositor(mCamera->getViewport(), "HDR");
	CompositorManager::getSingleton().setCompositorEnabled(mCamera->getViewport(), "HDR", true); 
	CompositorManager::getSingleton().registerCompositorLogic("HDR", );*/

	////create the texture
	//Ogre::TexturePtr rtt_texture = Ogre::TextureManager::getSingleton().createManual("RttTex", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::TEX_TYPE_2D, mWindow->getWidth(), mWindow->getHeight(), 0, Ogre::PF_FLOAT32_RGB, Ogre::TU_RENDERTARGET);

	////get render target of the texture in order to set some parameters and later also add a RenderTargetListener
	//Ogre::RenderTexture *renderTexture = rtt_texture->getBuffer()->getRenderTarget();
	//
	//renderTexture->addViewport(mCamera);
	//renderTexture->getViewport(0)->setClearEveryFrame(true);
	//renderTexture->getViewport(0)->setBackgroundColour(Ogre::ColourValue::Black);
	//renderTexture->getViewport(0)->setOverlaysEnabled(false);
	//renderTexture->addListener(this);

	////set up fullscreen quad 
	//mFullScreenQuad = new Ogre::Rectangle2D(true);
	////mFullScreenQuad->setCorners(0.5f, -0.5f, 1.0f, -1.0f);
	//mFullScreenQuad->setCorners(-1.0f, 1.0f, 1.0f, -1.0f);
	//mFullScreenQuad->setCastShadows(false);
	//mFullScreenQuad->setBoundingBox(Ogre::AxisAlignedBox::BOX_INFINITE);

	//Ogre::SceneNode* FullScreenQuadNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("FullScreenQuadNode");
	//FullScreenQuadNode->attachObject(mFullScreenQuad);

	////Ogre::HighLevelGpuProgramPtr vp = Ogre::HighLevelGpuProgramManager::getSingleton().createProgram("StdQuad_vp", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, "glsl", GPT_VERTEX_PROGRAM);
	////vp->setSourceFile("StdQuad_vp.glsl");

	////Ogre::HighLevelGpuProgramPtr fp = Ogre::HighLevelGpuProgramManager::getSingleton().createProgram("example_f", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, "glsl", GPT_FRAGMENT_PROGRAM);
	////fp->setSource("example_f.glsl");

	////// Create a material for fullscreen qaud
 ////   Ogre::MaterialPtr FullScreenMaterial = Ogre::MaterialManager::getSingleton().create( "FullScreenMaterial", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
 ////   //FullScreenMaterial->getTechnique( 0 )->getPass( 0 )->createTextureUnitState( "RttTex" );
	////FullScreenMaterial->getTechnique( 0 )->getPass( 0 )->setLightingEnabled(false);
	////FullScreenMaterial->getTechnique(0)->getPass(0)->setVertexProgram("StdQuad_vp");
	//////FullScreenMaterial->getTechnique(0)->getPass(0)->getVertexProgramParameters()->setNamedAutoConstant("worldViewProj", GpuProgramParameters::ACT_WORLDVIEWPROJ_MATRIX);
	////FullScreenMaterial->getTechnique(0)->getPass(0)->setFragmentProgram("example_f");

	//mFullScreenQuad->setMaterial("MyHDR");

//======================================================================================
//PHYSICS
//======================================================================================

	initPhysics();
	
}

void Game::initializeSounds()
{

	
   soundMgr = new SoundManager();
   soundMgr->Initialize();

   // Create a 3D, looped sound for the plane's engine noise
   ff06SoundIndex = soundMgr->CreateLoopedSound(Ogre::String("menu.ogg"));
   // or you can use the generic CreateSound, specifying the sound type directly:
//   ff06SoundIndex = soundMgr->CreateSound(Ogre::String("Sound050.ogg"), SOUND_TYPE_3D_SOUND_LOOPED);
   ff06SoundChannel = INVALID_SOUND_CHANNEL;

   // Create a 3D, single-shot sound for the plane's gunfire noise
   gunSoundIndex = soundMgr->CreateSound(Ogre::String("Sound035.ogg"));
   gunSoundChannel = INVALID_SOUND_CHANNEL;

  // ent = mSceneMgr->createEntity("FF06", "FF06.mesh");
   ff06Node = mSceneMgr->getRootSceneNode()->createChildSceneNode("FF06Node", Vector3(0.0f, 0.0f, 0.0f));
   //ff06Node->attachObject(ent);
   ff06Node->setScale(1.0f, 1.0f, 1.0f);

}

void Game::initPhysics(){

	jumpClock = new Ogre::Timer();
	jumpVelocity = 0;
	mOnGround = true;

	isCollision = false;
	isCollision1 = false;
	isCollision2 = false;

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);
	btVector3 worldAabbMin(-1000,-1000,-1000);
	btVector3 worldAabbMax(1000,1000,1000);

	btAxisSweep3* broadphase = new btAxisSweep3(worldAabbMin,worldAabbMax);

	collisionWorld = new btCollisionWorld(dispatcher,broadphase,collisionConfiguration);


	btMatrix3x3 basisA;
	basisA.setIdentity();

	btMatrix3x3 basisB;
	basisB.setIdentity();

	player = new btPairCachingGhostObject();
	player1 = new btPairCachingGhostObject();
	bulletMap = new btCollisionObject();
	player->getWorldTransform().setBasis(basisA);
	player1->getWorldTransform().setBasis(basisA);
	bulletMap->getWorldTransform().setBasis(basisB);
	btQuaternion temp;
	btTransform playerTransform = btTransform(temp.getIdentity(), btVector3(0,0,0));
	bulletMap->setWorldTransform(playerTransform);
	player->setWorldTransform(playerTransform);
	player1->setWorldTransform(playerTransform);

	btBoxShape* boxA = new btBoxShape(btVector3(5,5,5));
	boxA->setMargin(0.f);

	btCapsuleShape* capA = new btCapsuleShape(2.0f, 1.0f);
	capA->setMargin(0.0f);

	btBoxShape* boxB = new btBoxShape(btVector3(2,2,2));
	boxB->setMargin(0.f);


	player->setCollisionShape(boxA);//&hullA;
	//player1->setCollisionShape(capA);
	//bulletMap->setCollisionShape(boxB);//&hullB;

	//player
	objLoader objFile1;
	objFile1.LoadOBJ("characterCollisionMesh.obj", 50000);
	btTriangleMesh* trimesh = new btTriangleMesh();
	for (int i=0;i<objFile1.numTriangles;i++)
	{
		btVector3 vertex1(objFile1.vertices[objFile1.faces[i][0]][0]
		,objFile1.vertices[objFile1.faces[i][0]][1]
		,objFile1.vertices[objFile1.faces[i][0]][2]);
		btVector3 vertex2(objFile1.vertices[objFile1.faces[i][1]][0]
		,objFile1.vertices[objFile1.faces[i][1]][1]
		,objFile1.vertices[objFile1.faces[i][1]][2]);
		btVector3 vertex3(objFile1.vertices[objFile1.faces[i][2]][0]
		,objFile1.vertices[objFile1.faces[i][2]][1]
		,objFile1.vertices[objFile1.faces[i][2]][2]);
		trimesh->addTriangle(vertex1, vertex2, vertex3);
	}
	btCollisionShape* shape = 0;
	{
		//static, non-moving world environment geometry
		shape = new btConvexTriangleMeshShape(trimesh);
	}
	shape->setMargin(0.0f);

	player1->setCollisionShape(shape);



	//arena.
	objLoader objFile;
	objFile.LoadOBJ("Arena.obj", 50000);
	btTriangleMesh* trimesh1 = new btTriangleMesh();
	for (int i=0;i<objFile.numTriangles;i++)
	{
		btVector3 vertex1(objFile.vertices[objFile.faces[i][0]][0]
		,objFile.vertices[objFile.faces[i][0]][1]
		,objFile.vertices[objFile.faces[i][0]][2]);
		btVector3 vertex2(objFile.vertices[objFile.faces[i][1]][0]
		,objFile.vertices[objFile.faces[i][1]][1]
		,objFile.vertices[objFile.faces[i][1]][2]);
		btVector3 vertex3(objFile.vertices[objFile.faces[i][2]][0]
		,objFile.vertices[objFile.faces[i][2]][1]
		,objFile.vertices[objFile.faces[i][2]][2]);
		trimesh1->addTriangle(vertex1, vertex2, vertex3);
	}
	shape = 0;
	{
		//static, non-moving world environment geometry
		bool useQuantization = true;
		shape  = new btBvhTriangleMeshShape(trimesh1,useQuantization);
	}
	shape->setMargin(0.0f);

	bulletMap->setCollisionShape(shape);

	int myGroup = 1;
	int myMask = 1;

	collisionWorld->addCollisionObject(player1, myGroup, myMask);
	collisionWorld->addCollisionObject(player,myGroup,myMask);
	collisionWorld->addCollisionObject(bulletMap,myGroup,myMask);

	//Ogre::ManualObject* myManualObject =  mSceneMgr->createManualObject("manual1"); 
	//Ogre::SceneNode* myManualObjectNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("manual1_node"); 

	//// NOTE: The second parameter to the create method is the resource group the material will be added to.
	//// If the group you name does not exist (in your resources.cfg file) the library will assert() and your program will crash
	//Ogre::MaterialPtr myManualObjectMaterial = Ogre::MaterialManager::getSingleton().create("manual1Material","General"); 
	//myManualObjectMaterial->setReceiveShadows(false); 
	//myManualObjectMaterial->getTechnique(0)->setLightingEnabled(true); 
	//myManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0,0,1,0); 
	//myManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0,0,1); 
	//myManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,1); 

	//myManualObject->begin("manual1Material", Ogre::RenderOperation::OT_LINE_LIST); 
	//for(int i =0; i<objFile.numTriangles; i++)
	//{
	//	Ogre::Vector3 vertex1(objFile.vertices[objFile.faces[i][0]][0],objFile.vertices[objFile.faces[i][0]][1],objFile.vertices[objFile.faces[i][0]][2]);
	//	Ogre::Vector3 vertex2(objFile.vertices[objFile.faces[i][1]][0],objFile.vertices[objFile.faces[i][1]][1],objFile.vertices[objFile.faces[i][1]][2]);
	//	Ogre::Vector3 vertex3(objFile.vertices[objFile.faces[i][2]][0],objFile.vertices[objFile.faces[i][2]][1],objFile.vertices[objFile.faces[i][2]][2]);
	//	myManualObject->position(vertex1); 
	//	myManualObject->position(vertex2); 
	//	myManualObject->position(vertex3); 
	//	myManualObject->position(vertex1); 
	//}
	//// etc 
	//myManualObject->end(); 

	//myManualObjectNode->attachObject(myManualObject);
}

struct contactCallback : public btCollisionWorld::ContactResultCallback
	{
		virtual	btScalar	addSingleResult(btManifoldPoint& cp,	const btCollisionObjectWrapper* colObj0Wrap,int partId0,int index0,const btCollisionObjectWrapper* colObj1Wrap,int partId1,int index1)
		{
			isCollideTemp = 1;
			//isCollision = true;
			//mCameraMan->isCollision = true;
			return 1;
		}
	};

void Game::updatePhysics(){
	if(!mCameraMan->isCollision)
	{ 
		isCollideTemp = 0;
		isCollision = false;
	}
	Ogre::Vector3 ogrePos = mCamera->getPosition();
	btVector3 position = btVector3(ogrePos.x, ogrePos.y , ogrePos.z) ;
	//position += btVector3(0,mCamera->getDirection().y * -1,mCamera->getDirection().z*2.0f);
	btQuaternion temp;
	btTransform playerTransform = btTransform(temp.getIdentity(), position);
	//bulletMap->setWorldTransform(playerTransform);
	player->setWorldTransform(playerTransform);

	Ogre::Vector3 ogrePos1 = fullCharacterNode->getPosition();
	position = btVector3(ogrePos1.x, ogrePos1.y + 4 , ogrePos1.z) ;
	//position += btVector3(0,mCamera->getDirection().y * -1,mCamera->getDirection().z*2.0f);
	playerTransform = btTransform(temp.getIdentity(), position);
	player1->setWorldTransform(playerTransform);

	contactCallback callback;
	collisionWorld->performDiscreteCollisionDetection();
	collisionWorld->contactPairTest(player, bulletMap, callback);
	if(isCollideTemp == 1)
	{
		mCameraMan->isCollision = true;
		isCollision = true;
		isCollideTemp = 0;
	}
	collisionWorld->contactPairTest(player1, bulletMap, callback);
	if(isCollideTemp == 1)
	{
		isCollision1 = true;
		isCollideTemp = 0;
	}

	


}

//---------------------------------------------------------------------------
void Game::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	//mFullScreenQuad->setVisible(false);
}
//---------------------------------------------------------------------------
void Game::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	//mFullScreenQuad->setVisible(true);
}

//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        Game app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
