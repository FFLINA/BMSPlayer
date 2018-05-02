#include <stdio.h>
#include <stdlib.h>

#include "EffectManager.h"
#include "GameSystem.h"
#include "Note.h"
#include "Sprite.h"
#include "Bar.h"

#include "Track.h"

#define GREAT 250
#define GOOD 100

Track::Track()
{
	_backgroundSprite = NULL;
	_judgeLineSprite = NULL;
	_isKeyDown = false;
}

Track::~Track()
{
	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}

	if (NULL != _judgeLineSprite)
	{
		delete _judgeLineSprite;
		_judgeLineSprite = NULL;
	}

	if (NULL != _explosionSprite)
	{
		delete _explosionSprite;
		_explosionSprite = NULL;
	}
}

void Track::Init(int x, Array<NoteData*>* seperatedData)
{
	// 판정선 위치조정
	GameSystem::GetInstance()->SetJudgeLineOffset(100);
	int judgeLineOffset = GameSystem::GetInstance()->GetJudgeLineOffset();

	// 이펙트
	_explosionSprite = new Sprite("successeffectspr", false);
	_explosionSprite->SetPosition(x,
		GameSystem::GetInstance()->GetWindowHeight() - judgeLineOffset);
	
	// 트랙
	_backgroundSprite = new Sprite("trackspr", true);
	_backgroundSprite->SetPosition(x ,
		GameSystem::GetInstance()->GetWindowHeight() / 2);

	// 판정선
	_judgeLineSprite = new Sprite("judgelinespr", true);
	_judgeLineSprite->SetPosition(x ,
		GameSystem::GetInstance()->GetWindowHeight() - judgeLineOffset);

	_bar = new Bar(seperatedData);
	_bar->Init(x);


	_score = 0;
	_combo = 0;

	EffectManager::GetInstance()->Init(x);

}

void Track::Update(int deltaTime)
{
	_backgroundSprite->Update(deltaTime);
	_judgeLineSprite->Update(deltaTime);

	_explosionSprite->Update(deltaTime);

	GameSystem::GetInstance()->SetIsMissJudge(false);

	_bar->Update(deltaTime);

	if (GameSystem::GetInstance()->GetIsMissJudge())
	{
		//EffectManager::GetInstance()->PlayEffect("miss");
		//GameSystem::GetInstance()->ResetCombo();

		// Auto 임시 테스트
		_explosionSprite->Play();
		EffectManager::GetInstance()->PlayEffect("great");
		GameSystem::GetInstance()->AddCombo();
		GameSystem::GetInstance()->AddScore(GREAT);
	}

	EffectManager::GetInstance()->Update(deltaTime);

}

void Track::Render()
{
	_backgroundSprite->Render();
	_judgeLineSprite->Render();

	_explosionSprite->Render();

	_bar->Render();

	EffectManager::GetInstance()->Render();
}

void Track::Deinit()
{
	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}

	if (NULL != _judgeLineSprite)
	{
		delete _judgeLineSprite;
		_judgeLineSprite = NULL;
	}

	if (NULL != _explosionSprite)
	{
		delete _explosionSprite;
		_explosionSprite = NULL;
	}

	
	_bar->Deinit();

	EffectManager::GetInstance()->Deinit();
	
}

void Track::KeyDown()
{
	if (true ==_isKeyDown)
		return;
	_isKeyDown = true;

	GameSystem::GetInstance()->SetIsGreatJudge(false);
	GameSystem::GetInstance()->SetIsGoodJudge(false);

	_bar->KeyDown();

	if (GameSystem::GetInstance()->GetIsGreatJudge())
	{
		printf("Great Effect\n");
		_explosionSprite->Play();
		EffectManager::GetInstance()->PlayEffect("great");
		GameSystem::GetInstance()->AddCombo();
		GameSystem::GetInstance()->AddScore(GREAT);
	}
	else if (GameSystem::GetInstance()->GetIsGoodJudge())
	{
		printf("Good Effect\n");
		_explosionSprite->Play();
		EffectManager::GetInstance()->PlayEffect("good");
		GameSystem::GetInstance()->AddCombo();
		GameSystem::GetInstance()->AddScore(GOOD);
	}
}

void Track::KeyUp()
{
	_isKeyDown = false;

	_bar->KeyUp();
}