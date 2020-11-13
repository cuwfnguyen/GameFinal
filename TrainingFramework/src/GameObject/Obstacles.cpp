#include "Obstacles.h"

Obstacles::~Obstacles()
{
}

void Obstacles::SetSize(GLint width, GLint height)
{
	m_isInScreen = false;
	Sprite2D::SetSize(width, height);
	m_Size.x = width;
	m_Size.y = height;
}

void Obstacles::CheckInScreen()
{
	Vector2 pos = Get2DPosition();
	Vector2 size = GetSize();

	if (pos.x + size.x * 0.5 < 0 || pos.x - size.x * 0.5 > screenWidth)
	{
		m_isInScreen = false;
	}
	else {
		m_isInScreen = true;
	}
}
void Obstacles::Update(GLfloat deltatime)
{
	Sprite2D::Update(deltatime);
}
