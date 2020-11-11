#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	
	void SetNewPostionForBullet();
	
	inline std::shared_ptr<SpriteAnimation> CurrentState()const
	{
		return obj;
	}
private:
	const int m_MapWidth =2036;
	const int m_MapHeight = 550;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
	std::shared_ptr<SpriteAnimation> coin;
	std::shared_ptr<SpriteAnimation> state1;
	std::vector < std::shared_ptr<Sprite2D>> m_listSprite2D;
	std::vector < std::shared_ptr<SpriteAnimation>> m_listSpriteAnimations;
	std::vector < std::shared_ptr<Sprite2D>>m_listBackGround;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<SpriteAnimation> state2;
	std::shared_ptr<SpriteAnimation> obj;
};

