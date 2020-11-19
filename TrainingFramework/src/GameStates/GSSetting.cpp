#include"GSSetting.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic 
bool m_sound;
bool m_music;
GSSetting::GSSetting()
{

}


GSSetting::~GSSetting()
{
}



void GSSetting::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_setting");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//back

	std::shared_ptr<GameButton> button;
	texture = ResourceManagers::GetInstance()->GetTexture("back_play");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(0.05*screenWidth, screenHeight / 20);
	button->SetSize(screenWidth / 18, screenHeight / 14);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);

	//sound
	texture = ResourceManagers::GetInstance()->GetTexture("sound_on");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(515,286);
	button->SetSize(55, 55);
	button->SetOnClick([]() 
	{
		m_sound = false;
	});
	
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("sound_off");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(515,286);
	button->SetSize(60,60);
	button->m_isActive = false;
	button->SetOnClick([]()
	{
		m_sound = true;
	});
	m_listButton.push_back(button);
	
	//music
	texture = ResourceManagers::GetInstance()->GetTexture("sound_on");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(515, 368);
	button->SetSize(55, 55);
	button->SetOnClick([]()
	{
		m_music = false;
	});
	
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("sound_off");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(515, 368);
	button->SetSize(60,60);
	button->m_isActive = false;
	button->SetOnClick([]()
	{
		m_music = true;
	});
	m_listButton.push_back(button);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName = std::make_shared< Text>(shader, font, "SETTING", TEXT_COLOR::RED, 0.7);
//	m_Text_gameName->Set2DPosition(Vector2(2.7*screenWidth / 6, screenHeight / 8));


}

void GSSetting::Exit()
{
}


void GSSetting::Pause()
{

}

void GSSetting::Resume()
{
}


void GSSetting::HandleEvents()
{
	if (!m_music)
	{
		m_listButton[3]->m_isActive = false;
		m_listButton[4]->m_isActive = true;
	}
	if (m_music)
	{
		m_listButton[3]->m_isActive = true;
		m_listButton[4]->m_isActive = false;
	}
	if (!m_sound)
	{
		m_listButton[1]->m_isActive = false;
		m_listButton[2]->m_isActive = true;
	}
	if (m_sound)
	{
		m_listButton[1]->m_isActive = true;
		m_listButton[2]->m_isActive = false;
	}
}

void GSSetting::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSSetting::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		if(it->m_isActive)
		{
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle()) break;
		}
		
	}
}

void GSSetting::Update(float deltaTime)
{
	HandleEvents();
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		if (it->m_isActive)
		{
			it->Update(deltaTime);
		}
			
	}
}

void GSSetting::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		if (it->m_isActive)
		{
			it->Draw();
		}
		
	}
	m_Text_gameName->Draw();
}
