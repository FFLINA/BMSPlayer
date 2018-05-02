#include "Sprite.h"
#include "GameSystem.h"
#include "TitleScene.h"
#include "SceneManager.h"

#include "BMSParser.h"

TitleScene::TitleScene() 
{
	//printf("TitleScene »ý¼ºÀÚ");
}
TitleScene::~TitleScene() 
{

}

void TitleScene::Init() 
{
	BMSParser* bms = new BMSParser("carnation","carnation_right");

	_backgroundSprite = new Sprite("titlebackgroundspr", true);
	_backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2,
		GameSystem::GetInstance()->GetWindowHeight() / 2);
}
void TitleScene::Update(int deltaTime) 
{
	_backgroundSprite->Update(deltaTime);
}
void TitleScene::Render() 
{
	_backgroundSprite->Render();
}
void TitleScene::Deinit() 
{
	delete _backgroundSprite;
}

void TitleScene::KeyDown(unsigned int keyCode) 
{

}
void TitleScene::KeyUp(unsigned int keyCode) 
{
	switch (keyCode) {
	case SDLK_SPACE:
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_LOADING);
		break;
	}
}