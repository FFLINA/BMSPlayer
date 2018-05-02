#include <stdio.h>
#include "Font.h"
#include "Sprite.h"
#include "GameSystem.h"
#include "ResultScene.h"
#include "SceneManager.h"

ResultScene::ResultScene() {

}
ResultScene::~ResultScene() {

}


void ResultScene::Init() {
	_backgroundSprite = new Sprite("resultbackgroundspr", true);
	_backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2,
		GameSystem::GetInstance()->GetWindowHeight() / 2);
	
	int finalScore = GameSystem::GetInstance()->GetCurrentScore();
	int finalCombo = GameSystem::GetInstance()->GetCurrentCombo();

	_text = new Font("arialbd.ttf", 50);
	char text[256];
	sprintf(text, "Final Score : %d\n Final Combo : %d", finalScore, finalCombo);
	_text->SetText(text);



}
void ResultScene::Update(int deltaTime) {
	_backgroundSprite->Update(deltaTime);
}
void ResultScene::Render() {
	_backgroundSprite->Render();
	_text->SetPosition(400, 450);
	_text->Render();
}
void ResultScene::Deinit() {
	delete _backgroundSprite;
}

void ResultScene::KeyDown(unsigned int keyCode) {

}
void ResultScene::KeyUp(unsigned int keyCode) {
	switch (keyCode) {
	case SDLK_SPACE:
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_TITLE);
		break;
	}
}