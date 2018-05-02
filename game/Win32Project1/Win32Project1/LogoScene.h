#pragma once

#include "Scene.h"
class Sprite;

class LogoScene : public Scene
{
public:
	LogoScene();
	~LogoScene();

	void Init();
	void Update(int deltaTime);
	void Render();
	void Deinit();

	void KeyDown(unsigned int keyCode);
	void KeyUp(unsigned int keyCode);

private:
	int _waitTick;
	int _updateTick;
	//Sprite* _backgroundSprite;
};