#include "Font.h"
#include "Sprite.h"
#include "GameSystem.h"
#include "LoadingScene.h"
#include "SceneManager.h"
#include "ResourceManager.h"

#include "BMSParser.h"

LoadingScene::LoadingScene() 
{
	_waitTick = 2000;
	_updateTick = 0;
}
LoadingScene::~LoadingScene() 
{

}

void LoadingScene::Init() 
{
	BMSParser* bms = new BMSParser("carnation", "carnation_right");


	_backgroundSprite = new Sprite("loadingbackgroundspr", true);
	_backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2,
		GameSystem::GetInstance()->GetWindowHeight() / 2);

	ResourceManager::GetInstance()->LoadWav();

	//_loadingText = new Font("arialbd.ttf", 30);
}

void LoadingScene::Update(int deltaTime) 
{
	_backgroundSprite->Update(deltaTime);

	if (_waitTick < _updateTick) {
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_GAME);
	}
	_updateTick += deltaTime;
}

void LoadingScene::Render() 
{
	_backgroundSprite->Render();

	//_loadingText->Render();
}

void LoadingScene::Deinit() 
{
	delete _backgroundSprite;
}

void LoadingScene::KeyDown(unsigned int keyCode) 
{

}
void LoadingScene::KeyUp(unsigned int keyCode) 
{

}