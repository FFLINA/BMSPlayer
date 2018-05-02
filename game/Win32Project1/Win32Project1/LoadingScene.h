#pragma once

#include "Scene.h"
class Sprite;
class Font;

class LoadingScene : public Scene
{
public:
	LoadingScene();
	~LoadingScene();

	void Init();
	void Update(int deltaTime);
	void Render();
	void Deinit();

	void KeyDown(unsigned int keyCode);
	void KeyUp(unsigned int keyCode);

private:
	//char _text[256];

	std::string _loadedWav;

	//Font* _loadingText;
	int _waitTick;
	int _updateTick;
	Sprite* _backgroundSprite;
};