#pragma once

#include <map>
#include <string>
#include "SDL.h"


enum eScene
{
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_LOGO,
	SCENE_LOADING,
};

class Scene;

class SceneManager {
private:
	Scene* _scene;

public:
	SceneManager();
	~SceneManager();

	void Update(int deltaTime);
	void Render();
	void Deinit();

	void KeyDown(unsigned int keyCode);
	void KeyUp(unsigned int keyCode);

	void ChangeScene(eScene sceneType);


private:
	static SceneManager* _instance;

public:
	static SceneManager* GetInstance();

};