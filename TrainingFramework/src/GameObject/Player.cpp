#include "Player.h"; 
extern int screenWidth;
extern int screenHeight;

Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_isInAir = false;

	m_Position.x = 50;
	m_Position.y = 500;
	// Animation
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("test2");
	m_Nor = std::make_shared<SpriteAnimation>(model, shader, texture, 10, 0.07f);
	m_Nor->Set2DPosition(m_Position.x, m_Position.y);
	m_Nor->SetSize(50, 50);
	m_listSpriteAnimations.push_back(m_Nor);

	texture = ResourceManagers::GetInstance()->GetTexture("test1");
	m_JumpUp = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 3);
	m_JumpUp->Set2DPosition(m_Position.x, m_Position.y);
	m_JumpUp->SetSize(50, 50);
	m_listSpriteAnimations.push_back(m_JumpUp);

	texture = ResourceManagers::GetInstance()->GetTexture("test3");
	m_JumpDown = std::make_shared<SpriteAnimation>(model, shader, texture, 1, 3);
	m_JumpDown->Set2DPosition(m_Position.x, m_Position.y);
	m_JumpDown->SetSize(50, 50);;
	m_listSpriteAnimations.push_back(m_JumpDown);

	texture = ResourceManagers::GetInstance()->GetTexture("over");
	m_Over = std::make_shared<SpriteAnimation>(model, shader, texture, 5, 0.05f);
	m_Over->Set2DPosition(m_Position.x, m_Position.y);
	m_Over->SetSize(50, 50);;
	m_listSpriteAnimations.push_back(m_Over);

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
		if (key == VK_SPACE||key==VK_UP)
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

	Vector2 posObj =obj->Get2DPosition();
	Vector2 posObs = obs->Get2DPosition();
	Vector2 sizeObs = obs->GetSize();
	//size obj 50.50
	float distX = posObj.x - posObs.x;
	if (distX < 0)
		distX = -distX;
	float distY = posObj.y - posObs.y;
	if (distY < 0)
		distY = -distY;
	float distW = (50 + sizeObs.x) / 2;
	float distH = (50 + sizeObs.y) / 2; 
	if (distX +8<= distW && distY +8<= distH)//+8 de nhin truc quan hon
		{	
		if(!obj->m_isOver)
		{
			//obj = m_Over;
			obj->m_isOver = true;
			//ResourceManagers::GetInstance()->PlaySound("over", false);
			printf("game over");
		}
	}
}

void Player::Move(GLfloat deltaTime) {
	if (m_isActive)
	{
		if (MOVE)
		{
			if (MOVE == VK_SPACE)
			{
				if (m_Position.y > 95)
				{
					m_Position.y -= 200* deltaTime;
					obj = m_JumpUp;
					obj->Set2DPosition(m_Position);
				}  
				else if (m_Position.y <= 95) 
				{
					obj = m_JumpUp;
					obj->Set2DPosition(m_Position);
				}
			}
		}
		else
		{	
			if(m_Position.y < 500)
			{
				obj = m_JumpDown;
				
				m_Position.y += 220 * deltaTime;

				obj->Set2DPosition(m_Position);
			}	
			else if (m_Position.y>=500)
			{
				obj = m_Nor;
				obj->Set2DPosition(m_Position);
			}
		}
	}
}
void Player::Update(GLfloat deltaTime)
{
	Move(deltaTime);
}
