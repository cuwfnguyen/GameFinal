#include "GSOver.h"

extern int screenWidth; 
extern int screenHeight; 
extern bool m_music;
GSOver::GSOver()
{

}


GSOver::~GSOver()
{
}



void GSOver::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("game_over");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//replay button
	texture = ResourceManagers::GetInstance()->GetTexture("yes");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 3, screenHeight / 1.5);
	button->SetSize(80, 60);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		ResourceManagers::GetInstance()->PauseSound("game_over");
	});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("no");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 1.6, screenHeight / 1.5);
	button->SetSize(60, 60);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		ResourceManagers::GetInstance()->PauseSound("game_over");
	});
	m_listButton.push_back(button);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("game");
	m_Text_gameName = std::make_shared< Text>(shader, font, "MENU", TEXT_COLOR::RED, 1.0);

	if(m_music)
	{
		ResourceManagers::GetInstance()->PlaySound("game_over");
	}
	

}

void GSOver::Exit()
{
}


void GSOver::HandleEvents()
{

}

void GSOver::Pause()
{

}

void GSOver::Resume()
{

}

void GSOver::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSOver::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSOver::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSOver::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
}
