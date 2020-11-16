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
	m_Nor = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 0.07f);
	m_Nor->Set2DPosition(m_Position.x, m_Position.y);
	m_Nor->SetSize(60, 60);
	m_listSpriteAnimations.push_back(m_Nor);

	texture = ResourceManagers::GetInstance()->GetTexture("test1");
	m_Jump = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 3);
	m_Jump->Set2DPosition(m_Position.x, m_Position.y);
	m_Jump->SetSize(60,60);
	m_listSpriteAnimations.push_back(m_Jump);

	obj = m_Nor;

}

    
Player::~Player()
{
	obj = NULL;
}


void Player::HandleKeyEvents(GLbyte key, bool bIsPressed)
{
	if (bIsPressed)
	{
		if (key == VK_SPACE)
		{
			obj = m_listSpriteAnimations[0];
			if (!m_isInAir)
			{
				MOVE = VK_SPACE;
				m_isInAir = true;
				
			}
		}
	}
	else
	{
		m_isInAir = false;
		MOVE = 0;
	}
}

void Player::SetSize(GLint width, GLint height)
{
	Sprite2D::SetSize(width, height);
	m_Size.x = width;
	m_Size.y = height;
}
void Player::CheckObs(std::shared_ptr<Obstacles> obs) {

	Vector2 posObj = GetObj()->Get2DPosition();
	Vector2 posObs = obs->Get2DPosition();
	Vector2 sizeObs = obs->GetSize();
	//size 60. 60 

	/*if (((posObj.x-posObs.x)<=(60+sizeObs.x)/2)&& ((posObj.y - posObs.y) <= (60 + sizeObs.y) / 2))
	{
		m_isInAir = false;
		printf("Xu ly va cham");
	}
	else m_isInAir = true;*/
}

void Player::Move(GLfloat deltaTime) {
	if (m_isAlive)
	{
		if (MOVE)
		{
			if (MOVE == VK_SPACE)
			{
				if (m_Position.y > 10)
				{
					m_Position.y -= 300 * deltaTime;
					obj = m_Jump;
					obj->Set2DPosition(m_Position);
				}
			}
		}
		else
		{
			if(m_Position.y < 520)
			{
				m_Position.y += 150 * deltaTime;
				obj->Set2DPosition(m_Position);
			}	
		}
	}
}
void Player::Update(GLfloat deltaTime)
{
	Move(deltaTime);
}
