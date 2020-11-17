#pragma once 
#include "Sprite2D.h"
#include "ResourceManagers.h"
#include "SpriteAnimation.h";
#include "Obstacles.h"

class Obstacles;
extern int g;
class Player : public Sprite2D
{

public:
	Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);

	~Player();

	void	HandleKeyEvents(GLbyte key, bool bIsPressed);

	std::shared_ptr<SpriteAnimation> GetObj() 
	{
		return obj;
	}
	void Move(GLfloat deltatime);
	void Update(GLfloat deltatime);
	void CheckObs(std::shared_ptr<Obstacles> obs);

	bool GetInAir()
	{
		return m_isInAir;
	}
	void	SetSize(GLint width, GLint height);
	Vector2	GetSize() {
		return m_Size;
	}
private:

	void(*m_pKeyPreesed)();

	bool m_isKeyPressed;

	bool m_isInAir;
	bool m_isActive = true;
	int m_ySpeed;
	int MOVE = 0;
	Vector2 m_Position;
	std::vector < std::shared_ptr<SpriteAnimation>> m_listSpriteAnimations;
	std::shared_ptr<SpriteAnimation> m_JumpUp;
	std::shared_ptr<SpriteAnimation> m_JumpDown;
	std::shared_ptr<SpriteAnimation> m_Nor;
	std::shared_ptr<SpriteAnimation> obj;
	std::shared_ptr<SpriteAnimation> m_Over;
	Vector2 m_Size;
};


