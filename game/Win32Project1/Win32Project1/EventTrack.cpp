#include "GameSystem.h"
#include "Sprite.h"

#include "EventTrack.h"
#include "EventBar.h"

EventTrack::EventTrack()
{
	_backgroundSprite = NULL;
}

EventTrack::~EventTrack()
{
	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}
}

void EventTrack::Init(int x, Array<NoteData*>* seperatedData)
{
	// Æ®·¢
	_backgroundSprite = new Sprite("trackspr", true);
	_backgroundSprite->SetPosition(x,
		GameSystem::GetInstance()->GetWindowHeight() / 2);

	_bar = new EventBar(seperatedData);
	_bar->Init(x);
}

void EventTrack::Update(int deltaTime)
{
	_backgroundSprite->Update(deltaTime);

	_bar->Update(deltaTime);

}

void EventTrack::Render()
{
	_backgroundSprite->Render();

	_bar->Render();
}

void EventTrack::Deinit()
{
	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;

	}
	_bar->Deinit();
}