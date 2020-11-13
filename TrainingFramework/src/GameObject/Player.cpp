#include "Player.h"; 
extern int screenWidth;
extern int screenHeight;

Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_isInAir = false;
	m_isAlive = true;
	m_Position.x = screenWidth / 5;
	m_Position.y = 22 * screenHeight / 37;
	// Animation

	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("test2");
	m_Jump = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 0.07f);
	m_Jump->Set2DPosition(m_Position.x, m_Position.y);
	m_Jump->SetSize(60, 60);
	m_listSpriteAnimations.push_back(m_Jump);

	texture = ResourceManagers::GetInstance()->GetTexture("player1");
	m_Nor = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 3);
	m_Nor->Set2DPosition(m_Position.x, m_Position.y);
	m_Nor->SetSize(40, 40);
	m_listSpriteAnimations.push_back(m_Nor);

	obj = m_Jump;

}

    
Player::~Player()
{
	obj = NULL;
}


void Player::HandleKeyEvents(GLbyte key, bool bIsPressed)
{
	if (bIsPressed)
	{
		if (key == VK_UP)
		{
			obj = m_listSpriteAnimations[0];
			if (!m_isInAir)
			{
				MOVE = VK_UP;
				m_isInAir = true;
				
			}
		}
	}
	else
	{
		m_isInAir = false;
		MOVE = 0;
		//obj = m_listSpriteAnimations[1];
	}
}

void Player::CheckObs(std::shared_ptr<Obstacles> obs) {

	Vector2 pos = GetObj()->Get2DPosition();
	Vector2 fPos = obs->Get2DPosition();
	Vector2 fSize = obs->GetSize();

	if ((pos.y + 26 <= fPos.y - fSize.y * 0.5 + 11) && (pos.y + 26 >= fPos.y - fSize.y * 0.5) && (pos.x + 10 >= fPos.x - fSize.x * 0.5 && pos.x - 10 <= fPos.x + fSize.x * 0.5))
	{
		m_Position.y = fPos.y - 0.5*fSize.y - 26;
		m_isInAir = false;
	}
	else m_isInAir = true;
}
void Player::Move(GLfloat deltaTime) {
	if (m_isAlive)
	{
		if (MOVE)
		{
			if (MOVE == VK_UP)
			{
				if (m_Position.y > 10)
				{
					m_Position.y -= 200 * deltaTime;
					obj->Set2DPosition(m_Position);
				}
			}
		}
		else
		{
			m_Position.y += 100 * deltaTime;
			obj->Set2DPosition(m_Position);
		}
	}
}
void Player::Update(GLfloat deltaTime)
{
	Move(deltaTime);
}
