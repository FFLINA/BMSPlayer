#pragma once

#include "Scene.h"
class Sprite;
class Font;

class ResultScene : public Scene
{
public:
	ResultScene();
	~ResultScene();

	void Init();
	void Update(int deltaTime);
	void Render();
	void Deinit();

	void KeyDown(unsigned int keyCode);
	void KeyUp(unsigned int keyCode);

private:
	Font* _text;
	//Sprite* _backgroundSprite;
};