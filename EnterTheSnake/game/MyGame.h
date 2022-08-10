#pragma once

class CMyGame : public CGame
{
	// Define sprites and other instance variables here
	CSprite startScreen;
	CSprite shead;	
	CSprite sapple;
	CSprite apple;
	CSprite portal;
	CSprite boss;
	CSprite transformation;

	CSoundPlayer eatSound;
	CSoundPlayer deadSound;
	CSoundPlayer gamewonSound;
	CSoundPlayer maintrackSound;
	CSoundPlayer teleportSound;
	CSoundPlayer portalSound1;
	CSoundPlayer portalSound2;

	
	CSoundPlayer transformationSound;

	CSprite background;

	CSpriteList tail;
	CSpriteList obstacles;

	
	int score, x, y, position , tposition, tspeed, tdirection, level;

	bool body,bossdirection, gamewon;

	float  bosX, newX, newY;


public:
	CMyGame(void);
	~CMyGame(void);

	void SetupLevel1();
	void SetupLevel2();
	void SetupLevel3();

	// Per-Frame Callback Funtions (must be implemented!)
	virtual void OnUpdate();
	virtual void OnDraw(CGraphics* g);

	// Game Life Cycle
	virtual void OnInitialize();
	virtual void OnDisplayMenu();
	virtual void OnStartGame();
	virtual void OnStartLevel(Sint16 nLevel);
	virtual void OnGameOver();
	virtual void OnTerminate();

	// Keyboard Event Handlers
	virtual void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	virtual void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	// Mouse Events Handlers
	virtual void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);
	virtual void OnLButtonDown(Uint16 x,Uint16 y);
	virtual void OnLButtonUp(Uint16 x,Uint16 y);
	virtual void OnRButtonDown(Uint16 x,Uint16 y);
	virtual void OnRButtonUp(Uint16 x,Uint16 y);
	virtual void OnMButtonDown(Uint16 x,Uint16 y);
	virtual void OnMButtonUp(Uint16 x,Uint16 y);
};
