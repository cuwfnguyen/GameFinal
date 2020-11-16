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

void Obstacles::Update(GLfloat deltatime)
{
	Sprite2D::Update(deltatime);
}
