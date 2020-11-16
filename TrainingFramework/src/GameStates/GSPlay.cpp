#include "GSPlay.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "SpriteAnimation.h"
#include <WinUser.h>
#include"Player.h"
int score = 0;
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
bool m_isPause = false;
int m_bgX = screenHeight/2;
GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("map1");
	//auto texture1 = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(1.3*screenWidth, 0.5*screenHeight);
	m_BackGround->SetSize(m_MapWidth, m_MapHeight);
	m_listBackGround.push_back(m_BackGround);

	texture = ResourceManagers::GetInstance()->GetTexture("map3");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(1.3*screenWidth+m_MapWidth, 0.5*screenHeight);
	m_BackGround->SetSize(m_MapWidth, m_MapHeight);
	m_listBackGround.push_back(m_BackGround);

	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(29889*screenWidth/7330, 0.5*screenHeight);
	m_BackGround->SetSize(m_MapWidth, m_MapHeight);;
	m_listBackGround.push_back(m_BackGround);

	std::shared_ptr<GameButton> button;
	texture = ResourceManagers::GetInstance()->GetTexture("back_play");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(0.05*screenWidth, screenHeight / 20);
	button->SetSize(screenWidth / 18, screenHeight / 14);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		ResourceManagers::GetInstance()->PauseSound("bg_play");
	});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("pause");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(0.13*screenWidth,  screenHeight / 20);
	button->SetSize(screenWidth / 18, screenHeight / 14);
	button->m_isActive = true;
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->CurrentState()->Pause();
	});
	m_listButton.push_back(button);
	texture = ResourceManagers::GetInstance()->GetTexture("play1");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(0.13*screenWidth, screenHeight / 20);
	button->SetSize(screenWidth / 18, screenHeight / 14);
	button->m_isActive = false;
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->CurrentState()->Resume();
	});
	m_listButton.push_back(button);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font,"Score: "+std::to_string (score), TEXT_COLOR::RED, 0.95);
	m_score->Set2DPosition(0.17*screenWidth,screenHeight/15);
	
	//coin->Set2DPosition(200, 400);//sinh coin
	for (int i = 0; i < 10; i++) 
	{
		shader = ResourceManagers::GetInstance()->GetShader("Animation");
		texture = ResourceManagers::GetInstance()->GetTexture("coin1");
		coin = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.05f);
		coin->SetSize(25, 25);
		m_listCoin.push_back(coin);
	}
	

		m_listCoin[1]->Set2DPosition(350, 403);
		m_listCoin[2]->Set2DPosition(450, 350);
	m_Player = std::make_shared<Player>(model, shader, texture);

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.2");
	std::shared_ptr<Obstacles> m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(170,373);
	m_obs1->SetSize(160,34);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70,250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.3");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(238,148);
	m_obs1->SetSize(90,212);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.4");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(265,270);
	m_obs1->SetSize(40,39);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.5");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(250, 459);
	m_obs1->SetSize(120, 78);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.6");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(360, 472);
	m_obs1->SetSize(91, 30);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.7");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(440,459);
	m_obs1->SetSize(71,81);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.8");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(490,472);
	m_obs1->SetSize(38,32);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.9");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(541,373);
	m_obs1->SetSize(69,36);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.10");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(642,304);
	m_obs1->SetSize(59,39);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.11");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(911,270);
	m_obs1->SetSize(317,37);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.11.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(1050,234);
	m_obs1->SetSize(38,34);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.12");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(858,444);
	m_obs1->SetSize(352,108);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.13");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(1013,470);
	m_obs1->SetSize(550,31);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.14");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(1167,408);
	m_obs1->SetSize(151,39);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.15");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(1214, 271);
	m_obs1->SetSize(124,40);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.16");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(1388,439);
	m_obs1->SetSize(201,42);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.17");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(1588,459);
	m_obs1->SetSize(83,79);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.18");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(1740,270);
	m_obs1->SetSize(197,38);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.19");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(1740,441);
	m_obs1->SetSize(195,112);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.20");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(1920, 372);
	m_obs1->SetSize(100,40);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.21");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(1920, 475);
	m_obs1->SetSize(103,44);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.22");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(1858,470);
	m_obs1->SetSize(30,35);
	m_listObs.push_back(m_obs1);


	//if(sound=true)
	//{
		ResourceManagers::GetInstance()->PlaySound("bg_play",true);
	//}
	
		
}
void GSPlay::CheckCoin()
{
	
}
void GSPlay::Exit()
{
}

void GSPlay::Pause()
{
	m_listButton[1]->m_isActive = false;
	m_listButton[2]->m_isActive = true;
	m_isPause = true;
	ResourceManagers::GetInstance()->PauseSound("bg_play");

}

void GSPlay::Resume()
{
	m_listButton[1]->m_isActive = true;
	m_listButton[2]->m_isActive = false;
	m_isPause = false;
	ResourceManagers::GetInstance()->ResumeSound("bg_play");
}

void GSPlay::HandleEvents()
{
	for (auto obs: m_listObs)
	{
		Vector2 pos = obs->Get2DPosition();
		m_Player->CheckObs(obs);
		if (!m_Player->GetInAir())
		{
			break;
		}
	}
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	//handle event space or up
	m_Player->HandleKeyEvents(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		if (it->m_isActive) 
		{
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle()) break;   
		}
	}
	
}

void GSPlay::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		if (it->m_isActive)
		{
			it->Update(deltaTime);
		}
	}
	
	if (!m_isPause)
	{
		m_score->setText("Score " + std::to_string(score));
		Vector2 posObj = m_Player->GetObj()->Get2DPosition();

		for (auto coin : m_listCoin)
		{
			Vector2 posCoin = coin->Get2DPosition();
			float px = posObj.x-posCoin.x;
			float py = posObj.y-posCoin.y;

			if ((px < 20 && (px > -20) && (py > -10) && (py < 10)))
			{
				if (coin->m_isActive)
				{
					coin->m_isActive = false;
					printf("Ghi diem");
					score += 1;
					ResourceManagers::GetInstance()->PlaySound("coinsound", false);
				}
			}
			
		}

		m_Player->Update(deltaTime);
		m_Player->GetObj()->Update(deltaTime); 

		Vector2 curPos = m_BackGround->Get2DPosition();

		for (auto coin : m_listCoin)
		{
			if (coin->m_isActive)
				coin->Set2DPosition(coin->Get2DPosition().x - 100 * deltaTime, 0.5*screenHeight);
			coin->Update(deltaTime);
		}

		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}
		for (auto bg : m_listBackGround)
		{
			bg->Update(deltaTime);
			bg->Set2DPosition(bg->Get2DPosition().x - 100 * deltaTime,0.5*screenHeight);
			/*
			if (bg->Get2DPosition().x >= 29889 * screenWidth / 7330)
			{
				bg->Set2DPosition( bg->Get2DPosition().x - 2*m_MapWidth, 0.5*screenHeight);
				
			}*/
		}
		for(auto obs: m_listObs)
		{
			Vector2 pos = obs->Get2DPosition();
			pos.x -= 100 * deltaTime;
			obs->Set2DPosition(pos);
			obs->Update(deltaTime);

		}
		m_score->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	for (auto bg : m_listBackGround) 
	{
		bg->Draw();
	}
	
	for (auto obs : m_listObs) 
	{
		obs->Draw();
	}

	for (auto coin : m_listCoin)
	{
		if(coin->m_isActive)
		coin->Draw();
	}

	for (auto list : m_listSprite2D) 
	{
		list->Draw();
	}
	for (auto it : m_listButton)
	{
		if (it->m_isActive) 
		{
			it->Draw();
		}
	}
	m_Player->GetObj()->Draw();  
	m_score->Draw();

}

void GSPlay::SetNewPostionForBullet()
{

}