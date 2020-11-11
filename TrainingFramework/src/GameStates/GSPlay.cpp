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

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
bool m_isPause;
int MOVE = 0;
int m_posX = screenWidth/5;
int m_posY = 22*screenHeight/37;
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
	texture = ResourceManagers::GetInstance()->GetTexture("back1.1");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(55 * screenWidth / 60, 15 * screenHeight / 16);
	button->SetSize(screenWidth / 6, screenHeight / 14.5);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("pause");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(45 * screenWidth / 60, 15 * screenHeight / 16);
	button->SetSize(screenWidth / 6, screenHeight / 4.5);
	button->SetOnClick([]() {
		m_isPause = true;
	});
	m_listButton.push_back(button);
	texture = ResourceManagers::GetInstance()->GetTexture("play1");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(45 * screenWidth / 60, 15 * screenHeight / 16);
	button->SetSize(screenWidth / 6, screenHeight / 4.5);
	button->SetOnClick([]() {
		m_isPause = false;
	});
	m_listButton.push_back(button);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "Score: 0", TEXT_COLOR::PURPLE, 1.0);
	m_score->Set2DPosition(Vector2(100, 25));

	// Animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("animation1");
	state1 = std::make_shared<SpriteAnimation>(model, shader, texture, 4, 0.07f);
	state1->Set2DPosition(m_posX, m_posY);
	state1->SetSize(50, 50);
	m_listSpriteAnimations.push_back(state1);

	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("player1");
	state2 = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 3);
	state2->Set2DPosition(m_posX, m_posY);
	state2->SetSize(40, 40);
	m_listSpriteAnimations.push_back(state2);
	obj = m_listSpriteAnimations[1];

	
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("coin1");
	coin = std::make_shared<SpriteAnimation>(model, shader, texture, 6, 0.05f);
	coin->Set2DPosition(200,400);
	coin->SetSize(50, 50);

	ResourceManagers::GetInstance()->PlaySound("bg_sound");
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{
	m_isPause = true;
}

void GSPlay::Resume()
{
	m_isPause = false;
}

void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed) {
		if (key == VK_UP) {
			MOVE = VK_UP;
		}
		//if (key == VK_DOWN) {
		//	obj = m_listSpriteAnimations[0];
		//	if (curAPos.y + 10 < m_MapHeight) {
		//		curAPos.y = curAPos.y + 10;
		//		obj->Set2DPosition(curAPos.x, curAPos.y);
		//		m_listSpriteAnimations[1]->Set2DPosition(curAPos.x, curAPos.y);
		//	}
		//}
		//if (key == VK_LEFT) {
		//	obj = m_listSpriteAnimations[0]; //khong cho di nguoc lai
		//	curPos.x = curPos.x + 10;
		//	m_BackGround->Set2DPosition(curPos.x, curPos.y);
		//}
		//if (key == VK_RIGHT) {
		//	obj = m_listSpriteAnimations[0];
		//	if (curPos.x >-m_MapWidth/2) {
		//		curPos.x = curPos.x - 10;
		//		m_BackGround->Set2DPosition(curPos.x, curPos.y);
		//	}
			//else {
			//	if(curAPos.x>0)//chua xu ly duoc
			//	curAPos.x = curAPos.x + 10;
			//	obj->Set2DPosition(curAPos.x, curAPos.y);
			//	m_listSpriteAnimations[1]->Set2DPosition(curAPos.x, curAPos.y);
			//}
		
	}
	else
	{
		MOVE = 0;
		obj = m_listSpriteAnimations[1];
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
	
}

void GSPlay::Update(float deltaTime)
{
	Vector2 curPos = m_BackGround->Get2DPosition();
	Vector2 curAPos = obj->Get2DPosition();
	coin->Update(deltaTime);
	if (MOVE) {
		if (MOVE == VK_UP)
		{
			obj = m_listSpriteAnimations[0];
			if (curAPos.y > 10) {
				curAPos.y = curAPos.y - 500*deltaTime;
				obj->Set2DPosition(curAPos.x, curAPos.y);
				//m_listSpriteAnimations[0]->Set2DPosition(curAPos.x, curAPos.y);
			}
			
		}
		//obj->Update(deltaTime);
	}
		if (!m_isPause){
		obj->Update(deltaTime);
		
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

	}
}

void GSPlay::Draw()
{
	for (auto bg : m_listBackGround) {
		bg->Draw();
	}
	coin->Draw();
	obj->Draw();
	for (auto list : m_listSprite2D) {
		list->Draw();
	}
	for (auto it : m_listButton)
	{
	
	}

	//for (auto obj : m_listSpriteAnimations)
	//{
		//obj->Draw();
	//}

	m_score->Draw();

}

void GSPlay::SetNewPostionForBullet()
{

}