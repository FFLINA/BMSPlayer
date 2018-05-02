#include "Sprite.h"
#include "GameSystem.h"
#include "LogoScene.h"
#include "SceneManager.h"

LogoScene::LogoScene() {
	_waitTick = 2000;
	_updateTick = 0;
}
LogoScene::~LogoScene() {

}


void LogoScene::Init() {
	_backgroundSprite = new Sprite("logobackgroundspr", true);
	_backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2,
		GameSystem::GetInstance()->GetWindowHeight() / 2);
}
void LogoScene::Update(int deltaTime) {
	_backgroundSprite->Update(deltaTime);

	if (_waitTick < _updateTick) {
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_TITLE);
	}
	_updateTick += deltaTime;
}
void LogoScene::Render() {
	_backgroundSprite->Render();
}
void LogoScene::Deinit() {
	delete _backgroundSprite;
}

void LogoScene::KeyDown(unsigned int keyCode) {

}
void LogoScene::KeyUp(unsigned int keyCode) {
	switch (keyCode) {
	case SDLK_SPACE:
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_TITLE);
		break;
	}
}