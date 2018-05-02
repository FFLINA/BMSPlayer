
#include "GameSystem.h"
#include "EffectManager.h"

#include "Sprite.h"

EffectManager* EffectManager::_instance = 0;

EffectManager::EffectManager()
{

}

EffectManager::~EffectManager()
{
	
	if (NULL != _missEffectSprite)
	{
		delete _missEffectSprite;
		_missEffectSprite = NULL;
	}

	if (NULL != _goodEffectSprite)
	{
		delete _goodEffectSprite;
		_goodEffectSprite = NULL;
	}

	if (NULL != _greatEffectSprite)
	{
		delete _greatEffectSprite;
		_greatEffectSprite = NULL;
	}
}

EffectManager* EffectManager::GetInstance()
{
	if (0 == _instance)
	{
		_instance = new EffectManager();
	}
	return _instance;
}

void EffectManager::Update(int deltaTime)
{
	_missEffectSprite->Update(deltaTime);
	_goodEffectSprite->Update(deltaTime);
	_greatEffectSprite->Update(deltaTime);
}

void EffectManager::Render()
{
	_missEffectSprite->Render();
	_goodEffectSprite->Render();
	_greatEffectSprite->Render();
}

void EffectManager::Deinit()
{
	if (NULL != _missEffectSprite)
	{
		delete _missEffectSprite;
		_missEffectSprite = NULL;
	}

	if (NULL != _goodEffectSprite)
	{
		delete _goodEffectSprite;
		_goodEffectSprite = NULL;
	}

	if (NULL != _greatEffectSprite)
	{
		delete _greatEffectSprite;
		_greatEffectSprite = NULL;
	}
}

void EffectManager::Init(int x)
{
	int judgeLineOffset = 100;

	
	// 판정
	_missEffectSprite = new Sprite("misseffectspr", false);
	_missEffectSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2,
		GameSystem::GetInstance()->GetWindowHeight() / 2);
	_goodEffectSprite = new Sprite("goodeffectspr", false);
	_goodEffectSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2,
		GameSystem::GetInstance()->GetWindowHeight() / 2);
	_greatEffectSprite = new Sprite("greateffectspr", false);
	_greatEffectSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2,
		GameSystem::GetInstance()->GetWindowHeight() / 2);

	_spriteMap["miss"] = _missEffectSprite;
	_spriteMap["good"] = _goodEffectSprite;
	_spriteMap["great"] = _greatEffectSprite;

}

void EffectManager::PlayEffect(std::string judgeEffect)
{
	// 현재 키(filePath) 값에 해당하는 텍스쳐 검색
	StopEffect();
	std::map<std::string, Sprite*>::iterator it = _spriteMap.find(judgeEffect);
	if (it != _spriteMap.end())
	{
		it->second->SetFrameInterval(2500);
		it->second->Play();
	}
}

void EffectManager::StopEffect()
{
	_missEffectSprite->Stop();
	_goodEffectSprite->Stop();
	_greatEffectSprite->Stop();
}

