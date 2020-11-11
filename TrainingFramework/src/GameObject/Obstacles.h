#pragma once
#include "Sprite2D.h"
#include"SpriteAnimation.h"
class Obstacles : public SpriteAnimation
{
public:
	Obstacles(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLint numFrames, GLfloat frameTime) :SpriteAnimation(model, shader, texture, numFrames, frameTime) {};

	~Obstacles();

};

