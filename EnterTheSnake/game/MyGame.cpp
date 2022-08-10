#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void) :

	startScreen(400, 300, "menu.bmp", 0),
	apple(400, 400, 40, 40, "apple.bmp", CColor::Black(), 0),
	portal(-200,200,80,80,"portal.bmp", CColor::White(), 0)
	
{
	

}

CMyGame::~CMyGame(void)
{
}


void CMyGame::OnUpdate()
{
	// do not run game logic when in menu mode
	if (IsMenuMode())

		return;


	Uint32 t = GetTime();



	
	CVector lastpos;
	lastpos = shead.GetPosition();
	shead.Update(t);
	apple.Update(t);

	if(level ==3 )
	sapple.Update(t);

	portal.Update(t);
	boss.Update(t);
	/*transformation.Update(t);*/

	for (CSprite* newtail : tail)
	{
		newtail->Update(t);

	}

	for (CSprite* cactus : obstacles)
	{
		cactus->Update(t);

	}

	if (tail.size() > 0)
	{
		body = 1;
	}

	// ============ Game Logic ===================

	if (level == 1 && (shead.GetBottom() < 0 || shead.GetTop() > 800 || shead.GetLeft() < 20 || shead.GetRight() > 780))
		GameOver();

	if (level == 2 && (shead.GetBottom() < 0 || shead.GetTop() > 800 || shead.GetLeft() < 820 || shead.GetRight() > 1580))
		GameOver();

	if (level == 3 && (shead.GetBottom() < 0 || shead.GetTop() > 800 || shead.GetLeft() < 1620 || shead.GetRight() > 2380))
		GameOver();

	if (bossdirection == 0)
	{
		if (boss.GetLeft() < 1620)
		{
			boss.SetAnimation("moveright", 24);
			boss.Update(GetTime());
			boss.SetDirection(180);
			boss.Proceed(60);
			boss.SetDirection(90);

		}

		if (boss.GetRight() > 2380)
		{
			boss.SetAnimation("moveleft", 24);
			boss.Update(GetTime());
			boss.SetDirection(180);
			boss.Proceed(60);
			boss.SetDirection(270);
		}

	}

	if (bossdirection == 1)
	{
		if (boss.GetLeft() < 1620)
		{
			boss.SetAnimation("moveright", 24);
			boss.Update(GetTime());
			boss.SetDirection(0);
			boss.Proceed(60);
			boss.SetDirection(90);

		}

		if (boss.GetRight() > 2380)
		{
			boss.SetAnimation("moveleft", 24);
			boss.Update(GetTime());
			boss.SetDirection(0);
			boss.Proceed(60);
			boss.SetDirection(270);
		}

	}

	if (boss.GetBottom() < 0)
	{
		bossdirection = 1;
	}

	if (boss.GetTop() > 800)
	{
		bossdirection = 0;
	}
	
	if (boss.HitTest(&shead)) GameOver();
	
	if (shead.HitTest(&apple))
	{
		if (level == 1)
		{
			x = ((rand() % 39) + 1) * 20;
			y = ((rand() % 39) + 1) * 20;
			apple.SetPosition(x, y);
		}

		if (level == 2)
		{
			x = ((rand() % 39) + 41) * 20;
			y = ((rand() % 39) + 1) * 20;
			apple.SetPosition(x, y);
			
					for (CSprite* cactus : obstacles)
						while (cactus->HitTest(&apple) == 1)
						{
							x = ((rand() % 39) + 41) * 20;
							y = ((rand() % 39) + 1) * 20;
							apple.SetPosition(x, y);
						}
			
			
		}

		if ( level == 3)
		{
			x = ((rand() % 39) + 81) * 20;
			y = ((rand() % 39) + 1) * 20;
			apple.SetPosition(x, y);
		}

		score++;

		if(body==0)
		{

			newX = shead.GetX();
			newY = shead.GetY();
			tdirection = shead.GetDirection();

				if (position == 0)
				{
					CSprite* tail1 = new CSprite(newX - 40, newY, 40, 40, "stail.bmp", CColor::White(), GetTime());
					tail1->SetDirection(tdirection);
					tail1->SetRotation(tdirection);

					tail.push_back(tail1);
					
				}

				if (position == 1)
				{
					CSprite* tail1 = new CSprite(newX, newY + 40, 40, 40, "stail.bmp", CColor::White(), GetTime());
					tail1->SetDirection(tdirection);
					tail1->SetRotation(tdirection);
					tail.push_back(tail1);

				}

				if (position == 2)
				{
					CSprite* tail1 = new CSprite(newX + 40, newY, 40, 40, "stail.bmp", CColor::White(), GetTime());
					tail1->SetDirection(tdirection);
					tail1->SetRotation(tdirection);
					tail.push_back(tail1);

				}

				if (position == 3)
				{
					CSprite* tail1 = new CSprite(newX, newY - 40, 40, 40, "stail.bmp", CColor::White(), GetTime());
					tail1->SetDirection(tdirection);
					tail1->SetRotation(tdirection);
					tail.push_back(tail1);

				}
				 
		}

		else if (body == 1)
		{

			newX = tail.back()->GetX();
			newY = tail.back()->GetY();
			tdirection = tail.back()->GetDirection();

			

			if (tdirection == 90)
			{
				CSprite* tail1 = new CSprite(newX - 40, newY, 40, 40, "stail.bmp", CColor::White(), GetTime());
				tail1->SetDirection(tdirection);
				tail1->SetRotation(tdirection);
				tail1->Update(GetTime());
				tail.push_back(tail1);

			}

			

			else if (tdirection == -90)
			{
				CSprite* tail1 = new CSprite(newX + 40, newY, 40, 40, "stail.bmp", CColor::White(), GetTime());
				tail1->SetDirection(tdirection);
				tail1->SetRotation(tdirection);
				tail1->Update(GetTime());
				tail.push_back(tail1);

			}

			else if (tdirection == 0)
			{
				CSprite* tail1 = new CSprite(newX, newY - 40, 40, 40, "stail.bmp", CColor::White(), GetTime());
				tail1->SetDirection(tdirection);
				tail1->SetRotation(tdirection);
				tail1->Update(GetTime());
				tail.push_back(tail1);

			}
			
			else 
			{
				CSprite* tail1 = new CSprite(newX, newY + 40, 40, 40, "stail.bmp", CColor::White(), GetTime());
				tail1->SetDirection(tdirection);
				tail1->SetRotation(tdirection);
				tail1->Update(GetTime());
				tail.push_back(tail1);

			}

		}

		eatSound.Play("eat.wav");

		


	}

	if (shead.HitTest(&sapple))
	{

		maintrackSound.Stop();
		gamewonSound.Play("gamewon.wav");
		gamewonSound.PlayOnce();

		score++;
		tail.delete_all();
		body = 0;
		shead.SetSpeed(0);
		boss.SetSpeed(0);
		
		/*transformation.SetPosition(sapple.GetPosition());*/
		shead.SetPosition(sapple.GetPosition());
		sapple.SetPosition(3000, 500);
		/*transformation.Die(500);*/
		
		shead.LoadImage("fform.bmp", "2", CColor::Black());
		shead.SetRotation(0);
		shead.SetImage("2");
		shead.Update(GetTime());

		gamewon = 1;



	}

	

	if (body == 1)
	{
		for (CSprite* newtail : tail)
		{
			
			newtail->SetSpeed(300);
			


		}

		if (shead.GetY() - tail.front()->GetY() >= 40)
		{
			
			tail.front()->SetDirection(shead.GetDirection());
			tail.front()->SetRotation(tail.front()->GetDirection());
			tail.front()->SetPosition(shead.GetPosition() - CVector(0, 40));
			tail.front()->Update(GetTime());

			


			

		}
		else if (shead.GetY() - tail.front()->GetY() <= -40)
		{
			tail.front()->SetDirection(shead.GetDirection());
			tail.front()->SetRotation(tail.front()->GetDirection());
			tail.front()->SetPosition(shead.GetPosition() + CVector(0, 40));
			tail.front()->Update(GetTime());

		}
		else if (shead.GetX() - tail.front()->GetX() >= 40)
		{
			tail.front()->SetDirection(shead.GetDirection());
			tail.front()->SetRotation(tail.front()->GetDirection());
			tail.front()->SetPosition(shead.GetPosition() - CVector(40, 0));
			tail.front()->Update(GetTime());

		}
		else if (shead.GetX() - tail.front()->GetX() <= -40)
		{
			tail.front()->SetDirection(shead.GetDirection());
			tail.front()->SetRotation(tail.front()->GetDirection());
			tail.front()->SetPosition(shead.GetPosition() + CVector(40, 0));
			tail.front()->Update(GetTime());

		}

		CSpriteList::iterator it;
		CSpriteList::iterator yt;


		{
			for (it = tail.begin(); it != tail.end(); it++) 
			
			{
				if (it == tail.begin())
				{
					yt = it;
				}

				else 
				{
					if ((*yt)->GetY() - (*it)->GetY() >= 40)
					{
						(*it)->SetDirection((*yt)->GetDirection());
						(*it)->SetRotation((*yt)->GetDirection());
						(*it)->SetPosition((*yt)->GetPosition() - CVector(0, 40));
						(*it)->Update(GetTime());
						(*yt)->Update(GetTime());


					}
					else if ((*yt)->GetY() - (*it)->GetY() <= -40)
					{
						(*it)->SetDirection((*yt)->GetDirection());
						(*it)->SetRotation((*yt)->GetDirection());
						(*it)->SetPosition((*yt)->GetPosition() + CVector(0, 40));
						(*it)->Update(GetTime());
						(*yt)->Update(GetTime());

					}
					else if ((*yt)->GetX() - (*it)->GetX() >= 40)
					{
						(*it)->SetDirection((*yt)->GetDirection());
						(*it)->SetRotation((*yt)->GetDirection());
						(*it)->SetPosition((*yt)->GetPosition() - CVector(40, 0));
						(*it)->Update(GetTime());
						(*yt)->Update(GetTime());

					}
					else if ((*yt)->GetX() - (*it)->GetX() <= -40)
					{
						(*it)->SetDirection((*yt)->GetDirection());
						(*it)->SetRotation((*yt)->GetDirection());
						(*it)->SetPosition((*yt)->GetPosition() + CVector(40, 0));
						(*it)->Update(GetTime());
						(*yt)->Update(GetTime());

					}

					yt = it;
				}


				


				
			}

		}

	}

	if (score == 5 && level==1)
	{
		portal.SetPosition(760, 760);
		portalSound1.Play("popening.wav");
		portalSound1.PlayOnce();

	


	}
		

	if (score == 7 && level ==2)
	{
		portal.SetPosition(1560, 760);
		portalSound2.Play("popening.wav");
		portalSound2.PlayOnce();
		
	}
		

	if (score ==6 && level == 3)
	{
		apple.SetPosition(3000, 0);
		sapple.SetPosition(2000,400);
	}
		






	if (shead.HitTest(portal.GetPosition()) && level == 1)
	{
			teleportSound.Play("teleport.wav");
			level = 2;
			SetupLevel2();
	}

	if (shead.HitTest(portal.GetPosition()) && level == 2 )
	{
		teleportSound.Play("teleport.wav");
		level = 3;
		SetupLevel3();
	}
		

	

	/*for (CSprite* newtail : tail)
	{
		if (newtail->HitTest(&shead))GameOver();

	}*/
	
	/*if (IsGameOver())
		maintrackSound.Stop();*/

	for (CSprite* cactus : obstacles)
	{
		if (cactus->HitTest(&shead))GameOver();

	}

	if (shead.GetX() - 80 >= 40) cout << t <<endl;

}

void CMyGame::OnDraw(CGraphics* g)
{
	int leftScreenLimit = 300;
	int rightScreenLimit = 1910;

	// draw menu when in menu mode
	if (IsMenuMode())
	{
		startScreen.Draw(g);

		*g << font(50) << color(CColor::LightGreen()) << xy(450, 145) << level;
		return;
	}

	if (level == 1 ) g->SetScrollPos(0, 0);
	if (level == 2) g->SetScrollPos(-800, 0);
	if (level == 3) g->SetScrollPos(-1610, 0);

	background.Draw(g);

	portal.Draw(g);
	apple.Draw(g);
	/*transformation.Draw(g);*/



	for (CSprite* cactus : obstacles)
		cactus->Draw(g);

	
	for (CSprite* newtail : tail)
		newtail->Draw(g);

		boss.Draw(g);

		shead.Draw(g);

		sapple.Draw(g);


	
	// print score at position xy(50,570)
	if (level ==1 )
	*g << font(28) << color(CColor::Red()) << xy(10, 570) <<score;//score;

	if (level == 2)
		*g << font(28) << color(CColor::Red()) << xy(810, 570) << score;//score;

	if (level == 3)
		*g << font(28) << color(CColor::Red()) << xy(1610, 570) << score;//score;
		sapple.Draw(g);

	// print game over at the centre of the screen
	if (IsGameOverMode())
	{
		if(level==1)
			* g << font(46) << color(CColor::Green()) << xy(250, 400) << " GAME OVER ";
		if (level == 2)
			*g << font(46) << color(CColor::Green()) << xy(1050, 400) << " GAME OVER ";
		if (level == 3)
			*g << font(46) << color(CColor::Green()) << xy(1850, 400) << " GAME OVER ";

	}

	if (gamewon == 1)
	{
		*g << font(46) << color(CColor::DarkBlue()) << xy(1850, 600) << " YOU WON !!!! ";
	}
}




/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
	background.LoadImage("background.bmp", "map", CColor::Black());
	background.SetImage("map"); background.SetPosition(1200, 400);

	shead.LoadImage("shead.bmp", "h", CColor::Black());
	shead.SetImage("h");
	
}

// called when a new game is requested (e.g. when F2 pressed)
// use this function to prepare a menu or a welcome screen
void CMyGame::OnDisplayMenu()
{   
	maintrackSound.Play("maintrack.wav");
	// default level
	level = 1;
}

// called when a new game is started
// as a second phase after a menu or a welcome screen
void CMyGame::OnStartGame()
{
	gamewon = 0;
	score = 0;
	newX = 0;
	newY = 0;
	x = 0;
	y = 0;
	body = 0;
	position = 0;
	tposition = 0;

	tail.delete_all();

	if (level == 1) SetupLevel1();
	if (level == 2) SetupLevel2();
	if (level == 3) SetupLevel3();
	

	


}

// called at the beginning of level 1
void CMyGame::SetupLevel1()
{
	portal.SetPosition(-200, 200);

	x = ((rand() % 39) + 1) * 20;
	y = ((rand() % 39) + 1) * 20;
	apple.SetPosition(x, y);

	score = 0;
	tail.delete_all();
	shead.SetPosition(80, 720);
	shead.SetDirection(90);
	shead.SetSpeed(300);
	shead.SetRotation(90);
}

// called at the beginning of level 2
void CMyGame::SetupLevel2()
{
	portal.SetPosition(-200, 200);

	x = ((rand() % 39) + 41) * 20;
	y = ((rand() % 39) + 1) * 20;
	apple.SetPosition(x, y);

	for (CSprite* cactus : obstacles)
		while (cactus->HitTest(&apple) == 1)
		{
			x = ((rand() % 39) + 41) * 20;
			y = ((rand() % 39) + 1) * 20;
			apple.SetPosition(x, y);
		}

	score = 0;
	body = 0;

	tail.delete_all();
	shead.SetPosition(880, 720);
	shead.SetDirection(90);
	shead.SetSpeed(300);
	shead.SetRotation(90);
	apple.SetPosition(1280, 400);

	CSprite* cactus1 = new CSprite(960,640,80,80, "obstacle1.bmp", CColor::Black(), GetTime()); obstacles.push_back(cactus1);

	CSprite* cactus2 = new CSprite(960,400, 80, 80, "obstacle1.bmp", CColor::Black(), GetTime()); obstacles.push_back(cactus2);

	CSprite* cactus3 = new CSprite(960,160, 80, 80, "obstacle1.bmp", CColor::Black(), GetTime()); obstacles.push_back(cactus3);

	CSprite* cactus4 = new CSprite(1200, 640, 80, 80, "obstacle1.bmp", CColor::Black(), GetTime()); obstacles.push_back(cactus4);

	CSprite* cactus5 = new CSprite(1200, 400, 80, 80, "obstacle1.bmp", CColor::Black(), GetTime()); obstacles.push_back(cactus5);

	CSprite* cactus6 = new CSprite(1200, 160, 80, 80, "obstacle1.bmp", CColor::Black(), GetTime()); obstacles.push_back(cactus6);

	CSprite* cactus7 = new CSprite(1440, 640, 80, 80, "obstacle1.bmp", CColor::Black(), GetTime()); obstacles.push_back(cactus7);

	CSprite* cactus8 = new CSprite(1440, 400, 80, 80, "obstacle1.bmp", CColor::Black(), GetTime()); obstacles.push_back(cactus8);

	CSprite* cactus9 = new CSprite(1440, 160, 80, 80, "obstacle1.bmp", CColor::Black(), GetTime()); obstacles.push_back(cactus9);

	
}

void CMyGame::SetupLevel3()
{
	x = ((rand() % 39) + 81) * 20;
	y = ((rand() % 39) + 1) * 20;
	apple.SetPosition(x, y);

	score = 0;
	body = 0;  
	bossdirection = 0;

	tail.delete_all();
	shead.SetPosition(1680, 720);
	shead.SetDirection(90);
	shead.SetSpeed(300);
	shead.SetRotation(90);
	apple.SetPosition(2000, 400);

	boss.SetPosition(2240,400);
	boss.LoadAnimation("boss.bmp", "moveleft", CSprite::Sheet(59, 1).Row(0).From(0).To(58), CColor::Black());
	boss.LoadAnimation("bossright.bmp", "moveright", CSprite::Sheet(59, 1).Row(0).From(0).To(58), CColor::Black());

	boss.SetAnimation("moveleft", 24);
	boss.SetDirection(270);
	boss.SetSpeed(280);

	sapple.LoadImage("sapple.bmp", "1", CColor::Black());
	sapple.SetImage("1");


	/*transformation.LoadAnimation("transformation.bmp", "1", CSprite::Sheet(61, 1).Row(0).From(0).To(60), CColor::Black());
	transformation.SetAnimation("1", 24);*/

}

// called when a new level started - first call for nLevel = 1
void CMyGame::OnStartLevel(Sint16 nLevel)
{	
	
}

// called when the game is over
void CMyGame::OnGameOver()
{
	deadSound.Play("dead.wav");
	deadSound.PlayOnce();
	maintrackSound.Stop();
	
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();

	if (IsMenuMode() && sym == SDLK_SPACE) StartGame();


	if (IsMenuMode())
	{
		if (sym == SDLK_F1)
		{
			level = 1;
		}

		if (sym == SDLK_F2)
		{
			level = 2;
		}

		if (sym == SDLK_F3)
		{
			level = 3;
		}


	}

	if (sym == SDLK_LCTRL && IsMenuMode())
	{
		startScreen.LoadImage("menu2.bmp", "2");
		startScreen.SetImage("2");
		startScreen.Update(GetTime());


	}

	if (sym == SDLK_F4)
		NewGame();

	if( position !=2 && position != 0)
	{ 
		if (sym == SDLK_RIGHT)
		{
			shead.SetDirection(90);
			shead.SetRotation(shead.GetDirection());
			position = 0;
		}
	}

	if (position != 3 && position != 1)
	{

		if (sym == SDLK_DOWN)
		{
			shead.SetDirection(180);
			shead.SetRotation(shead.GetDirection());
			position = 1;
		}

	}

	if (position != 0 && position != 2)
	{
		if (sym == SDLK_LEFT)
		{
			shead.SetDirection(270);
			shead.SetRotation(shead.GetDirection());
			position = 2;
		}

	}

	if (position != 1 && position != 3)
	{

		if (sym == SDLK_UP)
		{
			shead.SetDirection(0);
			shead.SetRotation(shead.GetDirection());
			position = 3;
			
		}

	}


}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_LCTRL && IsMenuMode())
	{
		
			startScreen.LoadImage("menu.bmp", "1");
			startScreen.SetImage("1");
			startScreen.Update(GetTime());
	}
}




void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
	
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	shead.SetDirection(shead.GetDirection() - 90);
	shead.SetRotation(shead.GetDirection());
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
	shead.SetDirection(shead.GetDirection() + 90);
	shead.SetRotation(shead.GetDirection());
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
