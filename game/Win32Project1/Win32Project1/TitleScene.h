#pragma once

#include "Scene.h"
class Sprite;

class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();

	void Init();
	void Update(int deltaTime);
	void Render();
	void Deinit();

	void KeyDown(unsigned int keyCode);
	void KeyUp(unsigned int keyCode);

private:
	//Sprite* _backgroundSprite;
};