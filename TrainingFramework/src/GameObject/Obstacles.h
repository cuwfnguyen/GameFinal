#pragma once
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "Player.h"

class Player;
extern int xSpeed;
extern int screenWidth;

class Obstacles:
	public Sprite2D
{
public:
	Obstacles(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
		:Sprite2D(model, shader, texture) {};
	Obstacles() = default;

	~Obstacles();

	void	SetSize(GLint width, GLint height);

	Vector2	GetSize() {
		return m_Size;
	}

	void	Update(GLfloat deltatime);

private:

	Vector2 m_Size;
	bool	m_isInScreen;
};

