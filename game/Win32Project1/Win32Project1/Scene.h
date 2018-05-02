#pragma once

class Sprite;

class Scene {
protected:
	Sprite* _backgroundSprite;

public:
	Scene();
	~Scene();

	virtual void Init();
	virtual void Update(int deltaTime);
	virtual void Render();
	virtual void Deinit();

	virtual void KeyDown(unsigned int keyCode);
	virtual void KeyUp(unsigned int keyCode);
};