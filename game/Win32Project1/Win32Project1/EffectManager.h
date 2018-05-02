#pragma once

#include <map>
#include <string>

class Sprite;

class EffectManager
{
private:
	EffectManager();
	~EffectManager();

	//Sprite* _explosionSprite;
	Sprite* _missEffectSprite;
	Sprite* _goodEffectSprite;
	Sprite* _greatEffectSprite;

	std::map<std::string, Sprite*> _spriteMap;

private:
	static EffectManager* _instance;

public:
	static EffectManager* GetInstance();

public:
	void Init(int x);
	void Update(int deltaTime);
	void Render();
	void Deinit();

	void PlayEffect(std::string judgeEffect);
	void StopEffect();
};