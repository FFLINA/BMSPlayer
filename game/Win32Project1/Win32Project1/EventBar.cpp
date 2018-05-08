#include <iostream>

#include "sdl_mixer.h"
#include "sdl_ttf.h"

#include "Sprite.h"
#include "GameSystem.h"
#include "Track.h"
#include "EventBar.h"
#include "Note.h"
#include "ResourceManager.h"

#define BarHeight 150

using namespace std;

EventBar::EventBar(Array<NoteData*>* noteDataList)
{
	_noteDataList = noteDataList;
	_wavList = GameSystem::GetInstance()->GetWavListMap();
	_bmpList = GameSystem::GetInstance()->GetBmpListMap();
}

EventBar::~EventBar()
{
}

void EventBar::Init(int x)
{
	_barXposition = x;
	float totalPlayingSec = GameSystem::GetInstance()->GetTotalPlayingTime() / 1000.0f;
	float barCount = GameSystem::GetInstance()->GetBarCount();
	int oneBarHeight = GameSystem::GetInstance()->GetWindowHeight();
	float barPerSec = GameSystem::GetInstance()->GetBarPerSec();

	// 바 갯수만큼 반복  // 각 bar 높이는 전체 높이에서 갯수만큼 나눔
	for (int i = 0; i < barCount; i++)
	{
		_updateDuration = GameSystem::GetInstance()->GetTotalPlayingTime() - ((i * barPerSec) * 1000);

		float barNum = _noteDataList->Get(i)->GetBarNum();
		int beatSize = _noteDataList->Get(i)->GetBeatList()->Size();
		float judgeSec = 0.0f;

		if (i == (int)barNum)
		{
			for (int x = 0; x < beatSize; x++)
			{
				std::string noteNum = _noteDataList->Get(i)->GetBeatList()->Get(x);
				if (0 != noteNum.compare("00") && 0 != noteNum.compare(""))
				{
					judgeSec = (((float)x / (float)beatSize) * barPerSec) + ((float)i * barPerSec);

					Note* note = new Note(judgeSec, noteNum, _barXposition);
					_noteList.Append(note);
				}
			}
		}
	}

	judgeTick = GameSystem::GetInstance()->GetTotalPlayingTime();
}

void EventBar::Update(int deltaTime)
{
	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		Note* note = itr.item();
		if (note->IsLive())
		{
			note->Update(deltaTime);

			if (judgeTick < note->GetCurrentTime() && false == note->IsPassed())
			{
				note->Passed();
				EffectSoundPlay(note);
				note->SetLive(false);
			}
		}
	}
}

void EventBar::Render()
{
	/*DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		itr.item()->Render();
	}*/
}

void EventBar::Deinit()
{
	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		delete itr.item();
		_noteList.Remove(itr);
	}
}

void EventBar::EffectSoundPlay(Note* note)
{
	Mix_Chunk* effectSound = ResourceManager::GetInstance()->GetWav(note->GetNoteNum());

	if (NULL != effectSound)
	{
		Mix_PlayChannel(-1, effectSound, 0);
	}
	else
	{
		printf("Error Load Effect Wav\n");
	}
}