#include "GSMenu.h"
//#include"GSSetting.cpp"
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg2");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("start");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 1.96, screenHeight/3.7);
	button->SetSize(screenWidth/4, screenHeight/7);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);
	
	//seting button
	auto texture1 = ResourceManagers::GetInstance()->GetTexture("setting");
	button = std::make_shared<GameButton>(model, shader, texture1);
	button->Set2DPosition(screenWidth / 1.96, 1.5*screenHeight/3.7);
	button->SetSize(screenWidth / 4, screenHeight / 7);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Setting);
	});
	m_listButton.push_back(button);

	//credit button
	auto texture2 = ResourceManagers::GetInstance()->GetTexture("credit");
	button = std::make_shared<GameButton>(model, shader, texture2);
	button->Set2DPosition(screenWidth / 1.96, 2*screenHeight/3.7);
	button->SetSize(screenWidth / 4, screenHeight / 7);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Credit);
	});
	m_listButton.push_back(button);

	//exit button
	auto texture3 = ResourceManagers::GetInstance()->GetTexture("quit");
	button = std::make_shared<GameButton>(model, shader, texture3);
	button->Set2DPosition(screenWidth / 1.96, 2.5*screenHeight/3.7);
	button->SetSize(screenWidth / 4, screenHeight / 7);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName = std::make_shared< Text>(shader, font, "MENU", TEXT_COLOR::RED, 1.0);
//	m_Text_gameName->Set2DPosition(Vector2(4*screenWidth/9, screenHeight/6));

	//if (sound == true)
	//{
	//	ResourceManagers::GetInstance()->PlaySound("sound_menu");
	//}
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{
}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Text_gameName->Draw();
}
