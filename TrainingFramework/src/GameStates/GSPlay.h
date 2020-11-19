#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include"Player.h"
#include"Obstacles.h"
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
	
private:
	const int m_MapWidth =4800;
	const int m_MapHeight = 600;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_BackGround1;
	std::shared_ptr<Text>  m_score;
	std::shared_ptr<Text>  m_best;
	std::shared_ptr<SpriteAnimation> coin;
	std::vector < std::shared_ptr<Sprite2D>> m_listSprite2D;
	std::vector < std::shared_ptr<SpriteAnimation>> m_listCoin;
	std::vector < std::shared_ptr<Sprite2D>>m_listBackGround;
	std::shared_ptr<Player> m_Player;
	std::vector <std::shared_ptr<GameButton>>	m_listButton;
	std::vector<std::shared_ptr<Obstacles>> m_listObs;

};

