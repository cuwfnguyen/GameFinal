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
	m_score = std::make_shared< Text>(shader, font, "Score: 0", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(0.2*screenWidth,screenHeight/15);

	

	
	//coin->Set2DPosition(200, 400);//sinh coin
	for (int i = 0; i < 10; i++) 
	{
		shader = ResourceManagers::GetInstance()->GetShader("Animation");
		texture = ResourceManagers::GetInstance()->GetTexture("coin1");
		coin = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.05f);
		coin->SetSize(50, 50);
		m_listCoin.push_back(coin);
	}

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

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.6");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(360,472);
	m_obs1->SetSize(91,30);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);
	
	texture = ResourceManagers::GetInstance()->GetTexture("obs1.5");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(250,459);
	m_obs1->SetSize(120,78);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
	m_obs1 = std::make_shared<Obstacles>(model, shader, texture);
	m_obs1->Set2DPosition(70, 250);
	m_obs1->SetSize(103, 421);
	m_listObs.push_back(m_obs1);


//	if(sound=true)
	//{
	//	ResourceManagers::GetInstance()->PlaySound("bg_sound");
	//}
	
		
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{
	m_listButton[1]->m_isActive = false;
	m_listButton[2]->m_isActive = true;
	m_isPause = true;
	//ResourceManagers::GetInstance()->PauseSound("bg_sound");

}

void GSPlay::Resume()
{
	m_listButton[1]->m_isActive = true;
	m_listButton[2]->m_isActive = false;
	m_isPause = false;
	//ResourceManagers::GetInstance()->PlaySound("bg_sound");
}

void GSPlay::HandleEvents()
{
	for (auto gr : m_listObs)
	{
		Vector2 pos = gr->Get2DPosition();
		if (gr->GetIsInScreen())
		{
			m_Player->CheckObs(gr);

			if (!m_Player->GetInAir())
			{
				break;
			}
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
		m_Player->Update(deltaTime);
		m_Player->GetObj()->Update(deltaTime);
		Vector2 curPos = m_BackGround->Get2DPosition();
	
		for (auto gr : m_listObs) {
			Vector2 pos = gr->Get2DPosition();
			gr->Set2DPosition(pos);
			gr->CheckInScreen();
			gr->Update(deltaTime);

		}
		coin->Update(deltaTime);

		

		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}
		for (auto bg : m_listBackGround)
		{
			bg->Update(deltaTime);
			bg->Set2DPosition(bg->Get2DPosition().x - 100 * deltaTime,0.5*screenHeight);
			coin->Set2DPosition(coin->Get2DPosition().x-50*deltaTime,0.5*screenHeight);
			
			if (bg->Get2DPosition().x >= 29889 * screenWidth / 7330)
			{
				bg->Set2DPosition( bg->Get2DPosition().x - 2*m_MapWidth, 0.5*screenHeight);
				
			}
		}
		for(auto obs: m_listObs)
		{
			Vector2 pos = obs->Get2DPosition();
			pos.x -= 100 * deltaTime;
			obs->Set2DPosition(pos);
			obs->CheckInScreen();
			obs->Update(deltaTime);

		}
	}
}

void GSPlay::Draw()
{
	for (auto bg : m_listBackGround) 
	{
		bg->Draw();
	}
	coin->Draw();
	for (auto obs : m_listObs) {
		obs->Draw();
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