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
std::shared_ptr<Sprite2D> m_BackGround1;
bool m_isPause;

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
	m_BackGround->Set2DPosition(13 * screenWidth / 12, screenHeight / 2);
	m_BackGround->SetSize(m_MapWidth, m_MapHeight);
	//m_listBackGround.push_back(m_BackGround);

	/*m_BackGround1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround1->Set2DPosition(m_bgX+screenWidth, screenHeight/2);
	m_BackGround1->SetSize(screenWidth, screenHeight);*/
	//m_listBackGround.push_back(m_BackGround1);

	std::shared_ptr<GameButton> button;
	texture = ResourceManagers::GetInstance()->GetTexture("back1.1");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(55 * screenWidth / 60, 15 * screenHeight / 16);
	button->SetSize(screenWidth / 6, screenHeight / 14.5);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("pause1.1");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(35 * screenWidth / 60, 15 * screenHeight / 16);
	button->SetSize(screenWidth / 6, screenHeight / 14.5);
	button->SetOnClick([]() {
		m_isPause = true;
	});
	m_listButton.push_back(button);
	texture = ResourceManagers::GetInstance()->GetTexture("resume1.1");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(45 * screenWidth / 60, 15 * screenHeight / 16);
	button->SetSize(screenWidth / 6, screenHeight / 14.5);
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
		Vector2 curPos = m_BackGround->Get2DPosition();
		Vector2 curAPos = obj->Get2DPosition();
		if (key == VK_UP) {
			obj = m_listSpriteAnimations[0];
			if (curAPos.y > 10) {
				 curAPos.y = curAPos.y - 10;
				obj->Set2DPosition(curAPos.x, curAPos.y);
				m_listSpriteAnimations[1]->Set2DPosition(curAPos.x, curAPos.y);
			}
		}
		if (key == VK_DOWN) {
			obj = m_listSpriteAnimations[0];
			if (curAPos.y + 10 < m_MapHeight) {
				curAPos.y = curAPos.y + 10;
				obj->Set2DPosition(curAPos.x, curAPos.y);
				m_listSpriteAnimations[1]->Set2DPosition(curAPos.x, curAPos.y);
			}
		}
		if (key == VK_LEFT) {
			obj = m_listSpriteAnimations[0]; //khong cho di nguoc lai
			curPos.x = curPos.x + 10;
			m_BackGround->Set2DPosition(curPos.x, curPos.y);
		}
		if (key == VK_RIGHT) {
			obj = m_listSpriteAnimations[0];
			if (curPos.x > 0) {
				curPos.x = curPos.x - 10;
				m_BackGround->Set2DPosition(curPos.x, curPos.y);
			}
			else {
				if(curAPos.x>0)//chua xu ly duoc
				curAPos.x = curAPos.x + 10;
				obj->Set2DPosition(curAPos.x, curAPos.y);
				m_listSpriteAnimations[1]->Set2DPosition(curAPos.x, curAPos.y);
			}
		}
	}
	else
	{
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
	
		if (!m_isPause){
		obj->Update(deltaTime);
		
		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}


	}
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	obj->Draw();
	for (auto list : m_listSprite2D) {
		list->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	for (auto obj : m_listSpriteAnimations)
	{
		//obj->Draw();
	}

	m_score->Draw();

}

void GSPlay::SetNewPostionForBullet()
{
}