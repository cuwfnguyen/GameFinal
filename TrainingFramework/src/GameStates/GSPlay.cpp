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
int score;
int best =0;
GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	score = 0;
	int deltaPos = 200;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("map1");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(3*screenWidth, 0.5*screenHeight);
	m_BackGround->SetSize(m_MapWidth, m_MapHeight);
//	m_listBackGround.push_back(m_BackGround);

	texture = ResourceManagers::GetInstance()->GetTexture("game_over");
	m_BackGround1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround1->Set2DPosition(1.3*screenWidth, 0.5*screenHeight);
	m_BackGround1->SetSize(screenWidth, screenHeight);


	std::shared_ptr<GameButton> button;
	texture = ResourceManagers::GetInstance()->GetTexture("back_play");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(0.05*screenWidth, screenHeight / 20);
	button->SetSize(screenWidth / 18, screenHeight / 14);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		ResourceManagers::GetInstance()->StopSound("bg_play");
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
	m_best = std::make_shared< Text>(shader, font, "Best: " + std::to_string(best), TEXT_COLOR::RED, 0.95);
	m_best->Set2DPosition(0.4*screenWidth, screenHeight / 15);

	//sinh coin
	for (int i = 0; i < 10; i++) 
	{
		shader = ResourceManagers::GetInstance()->GetShader("Animation");
		texture = ResourceManagers::GetInstance()->GetTexture("coin1");
		coin = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.05f);
		coin->SetSize(25, 25);
		m_listCoin.push_back(coin);
	}
	
	m_Player = std::make_shared<Player>(model, shader, texture);

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//diem end game
	texture = ResourceManagers::GetInstance()->GetTexture("obs4");
	std::shared_ptr<Obstacles> m_obs = std::make_shared<Obstacles>(model, shader, texture);
	m_obs->Set2DPosition(6500, 350);
	m_obs->SetSize(39,27);
	m_listObs.push_back(m_obs);

	//diem tang level
	texture = ResourceManagers::GetInstance()->GetTexture("obs1.19");
	m_obs = std::make_shared<Obstacles>(model, shader, texture);
	m_obs->Set2DPosition(2100, 350);
	m_obs->SetSize(195, 112);
	m_listObs.push_back(m_obs);

	for (int i = 0; i < 4; i++)
	{

		texture = ResourceManagers::GetInstance()->GetTexture("obs1.1");
		m_obs = std::make_shared<Obstacles>(model, shader, texture);
		m_obs->Set2DPosition(900+i*deltaPos*8, 163);
		m_obs->SetSize(50, 193);
		m_listObs.push_back(m_obs);

		texture = ResourceManagers::GetInstance()->GetTexture("obs1.0");
		m_obs = std::make_shared<Obstacles>(model, shader, texture);
		m_obs->Set2DPosition(900 + i*deltaPos * 8, 447);
		m_obs->SetSize(50, 165);
		m_listObs.push_back(m_obs);

		texture = ResourceManagers::GetInstance()->GetTexture("obs1.15");
		m_obs = std::make_shared<Obstacles>(model, shader, texture);
		m_obs->Set2DPosition(300 + 4 * deltaPos*i, 350);
		m_obs->SetSize(93, 30);
		m_listObs.push_back(m_obs);

		texture = ResourceManagers::GetInstance()->GetTexture("obs1.15");
		m_obs = std::make_shared<Obstacles>(model, shader, texture);
		m_obs->Set2DPosition(3500 + 4 * deltaPos*i,200);
		m_obs->SetSize(93, 30);
		m_listObs.push_back(m_obs);

		texture = ResourceManagers::GetInstance()->GetTexture("obs1.11");
		m_obs = std::make_shared<Obstacles>(model, shader, texture);
		m_obs->Set2DPosition(100 + 5.5 * deltaPos*i, 120);
		m_obs->SetSize(238,28);
		m_listObs.push_back(m_obs);

		texture = ResourceManagers::GetInstance()->GetTexture("obs2.4");
		m_obs = std::make_shared<Obstacles>(model, shader, texture);
		m_obs->Set2DPosition(1400 + i*deltaPos * 8, 434);
		m_obs->SetSize(50, 193);
		m_listObs.push_back(m_obs);

		texture = ResourceManagers::GetInstance()->GetTexture("obs2.3");
		m_obs = std::make_shared<Obstacles>(model, shader, texture);
		m_obs->Set2DPosition(1400 + i*deltaPos * 8, 149);
		m_obs->SetSize(50, 165);
		m_listObs.push_back(m_obs);
	}

	texture = ResourceManagers::GetInstance()->GetTexture("obs1.13");
	m_obs = std::make_shared<Obstacles>(model, shader, texture);
	m_obs->Set2DPosition(500,515);
	m_obs->SetSize(550, 31);
	m_listObs.push_back(m_obs);

	for (int i = 0; i < 15; i++) {
		texture = ResourceManagers::GetInstance()->GetTexture("obs2.2");
		m_obs = std::make_shared<Obstacles>(model, shader, texture);
		m_obs->Set2DPosition(950 + deltaPos*i, 515);
		m_obs->SetSize(34,31);
		m_listObs.push_back(m_obs);

		texture = ResourceManagers::GetInstance()->GetTexture("obs2.2");
		m_obs = std::make_shared<Obstacles>(model, shader, texture);
		m_obs->Set2DPosition(4545 + 0.5*deltaPos*i, 515);
		m_obs->SetSize(34, 31);
		m_listObs.push_back(m_obs);
	}

	m_listCoin[0]->Set2DPosition(452, 353);
	m_listCoin[1]->Set2DPosition(70,450);
	m_listCoin[2]->Set2DPosition(980, 513);
	m_listCoin[3]->Set2DPosition(1180, 513);
	//m_listCoin[4]->Set2DPosition(1380, 513);
	//m_listCoin[5]->Set2DPosition(1580, 513);
	m_listCoin[6]->Set2DPosition(3500,230);
	m_listCoin[7]->Set2DPosition(3600, 230);
	m_listCoin[8]->Set2DPosition(2180, 513);
	m_listCoin[9]->Set2DPosition(3000, 150);
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
		m_score->setText("Score: " + std::to_string(score));
		m_best->setText("Best: " + std::to_string(best));
		Vector2 posObj = m_Player->GetObj()->Get2DPosition();

		//check coin
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
					if(score>best)
					{
						best = score;
					}
				}
			}	
		}
		
		if(m_Player->GetObj()->m_isActive)
		{
			m_Player->GetObj()->Update(deltaTime);
			m_Player->Update(deltaTime);
		}
		Vector2 curPos = m_BackGround->Get2DPosition();
		for (auto coin : m_listCoin)
		{
			Vector2 posCoin = coin->Get2DPosition();
			if (coin->m_isActive)
			{
				if (m_listObs[1]->Get2DPosition().x >100)
				{
					posCoin.x -= 100*deltaTime;
					coin->Set2DPosition(posCoin);
				}
				else if (m_listObs[1]->Get2DPosition().x <= 100)
				{
					posCoin.x -= 200*deltaTime;
					coin->Set2DPosition(posCoin);
				}
			}
				
			coin->Update(deltaTime);
		}

		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}
	
		//check vat can
		for (auto obs : m_listObs)
		{
			m_Player->CheckObs(obs);
			if (m_Player->GetObj()->m_isOver)
			{
				//ResourceManagers::GetInstance()->PlaySound("over", false);
				//printf("Game Over");
				ResourceManagers::GetInstance()->StopSound("bg_play");
				GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Over);
				
			}
		}
		//vat can di chuyen theo chieu nguoc
		for(auto obs: m_listObs)
		{
			Vector2 pos = obs->Get2DPosition();
			if (m_listObs[1]->Get2DPosition().x >100)
			{
				pos.x -= 100 * deltaTime;
				obs->Set2DPosition(pos);
				obs->Update(deltaTime);
			}
			else if (m_listObs[1]->Get2DPosition().x <=100)
			{
				pos.x -= 200 * deltaTime;
				obs->Set2DPosition(pos);
				obs->Update(deltaTime);
			}
			
			
		}
		//het man choi, check obs o vi tri cuoi cung cua backgroud
		if(m_listObs[0]->Get2DPosition().x<=800)
		{
			ResourceManagers::GetInstance()->StopSound("bg_play");
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Over);
		}
		m_score->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
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
	if (m_Player->GetObj()->m_isActive)
	{
		m_Player->GetObj()->Draw();
	}
	m_score->Draw();
	m_best->Draw();

}

void GSPlay::SetNewPostionForBullet()
{

}