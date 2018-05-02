#include <iostream>

#include "sdl_mixer.h"
#include "sdl_ttf.h"

#include "Sprite.h"
#include "GameSystem.h"
#include "Track.h"
#include "Bar.h"
#include "Note.h"

#include "ResourceManager.h"

#define BarHeight 150

Bar::Bar(Array<NoteData*>* noteDataList)
{
	_noteDataList = noteDataList;
	_wavList = GameSystem::GetInstance()->GetWavListMap();
	_bmpList = GameSystem::GetInstance()->GetBmpListMap();
	//_barLineSprite = NULL;
}

Bar::~Bar()
{
	/*if (NULL != _barLineSprite)
	{
		delete _barLineSprite;
		_barLineSprite = NULL;
	}*/
}

void Bar::Init(int x)
{
	_barXposition = x;
	float totalPlayingSec = GameSystem::GetInstance()->GetTotalPlayingTime() / 1000.0f;
	float barCount = GameSystem::GetInstance()->GetBarCount();
	int oneBarHeight = GameSystem::GetInstance()->GetWindowHeight();
	float barPerSec = GameSystem::GetInstance()->GetBarPerSec();

	// 바 갯수만큼 반복  // 각 bar 높이는 전체 높이에서 갯수만큼 나눔
	for (int i = 0; i < barCount; i++)
	{
		/*_barLineSprite = new Sprite("barlinespr", true);
		_barLineSprite->SetPosition(_barXposition, (i * oneBarHeight));
		_barLineList.Append(_barLineSprite);
		
		_updateDuration = GameSystem::GetInstance()->GetTotalPlayingTime() - ((i * barPerSec) * 1000);
		
		UpdatePosition(0);
		*/

		float barNum = _noteDataList->Get(i)->GetBarNum();				
		int beatSize = _noteDataList->Get(i)->GetBeatList()->Size();
		float judgeSec = 0.0f;

		if (i == (int)barNum)
		{
			for (int x = 0; x < beatSize; x++)
			{
				std::string noteNum = _noteDataList->Get(i)->GetBeatList()->Get(x);
				if (0 != noteNum.compare("00") && 0 != noteNum.compare(""))
				{ // 읽은 노트의 번호가 00이 아닐 떄
					judgeSec = (((float)x / (float)beatSize) * barPerSec) + ((float)i * barPerSec);

					// #00119:00TX0000 -> barNum:1.000f, beatSize:4, noteNum:TX
					// judgeSec -> (1 / 4) * oneBarHeight
					// 해당 Bar에서의 판정시간을 구함
					// 해당 BarNum 보다 앞에있는 Bar의 전체길이도 같이 더해줘야함

					Note* note = new Note(judgeSec, noteNum, _barXposition);
					_noteList.Append(note);
				}
			}
		}
		
	}

	judgeTick = GameSystem::GetInstance()->GetTotalPlayingTime();
	//int judgeTick = GameSystem::GetInstance()->GetTotalPlayingTime();
	_judgeGoodStartTick = judgeTick - 100;
	_judgeGreatStartTick = judgeTick - 30;
	_judgeGreatEndTick = judgeTick + 30;
	_judgeGoodEndTick = judgeTick + 100;
}

void Bar::Update(int deltaTime)
{
	/*
	{	// Bar Line
		UpdatePosition(deltaTime);

		DLinkedListIterator<Sprite*> itr = _barLineList.GetIterator();
		for (itr.begin(); itr.valid(); itr.forth())
		{
			Sprite* line = itr.item();
			line->Update(deltaTime);
		}
	}*/
	
	
	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		Note* note = itr.item();
		if (note->IsLive())
		{
			note->Update(deltaTime);


			//// Auto 임시 테스트
			/*if (_judgeGoodEndTick < note->GetCurrentTime() && false == note->IsPassed())
			{
				note->Passed();
				printf("Miss Effect\n");
				GameSystem::GetInstance()->SetIsMissJudge(true);
			}*/

			//// Auto 임시 테스트
			if (judgeTick < note->GetCurrentTime() && false == note->IsPassed())
			{
				note->Passed(); 
				GameSystem::GetInstance()->SetIsMissJudge(true);
				EffectSoundPlay(note);
				note->SetLive(false);
			}

		}
	}
}

//void Bar::UpdatePosition(float deltaTime)
//{
//	_updateDuration += deltaTime;
//
//	float timePositionRate = (float)_updateDuration / (float)GameSystem::GetInstance()->GetTotalPlayingTime();
//	float positionByTick = GameSystem::GetInstance()->GetBarHeight() * timePositionRate;
//
//	_barYposition = positionByTick - (GameSystem::GetInstance()->GetBarHeight() - GameSystem::GetInstance()->GetWindowHeight()) - GameSystem::GetInstance()->GetJudgeLineOffset();
//
//	_barLineSprite->SetPosition(_barXposition, _barYposition);
//
//	DLinkedListIterator<Sprite*> itr = _barLineList.GetIterator();
//	for (itr.begin(); itr.valid(); itr.forth())
//	{
//		Sprite* line = itr.item();
//		line->SetPosition(_barXposition, _barYposition);
//	}
//
//}

void Bar::Render()
{
	//_barLineSprite->Render();

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
	itr.item()->Render();
	}
	
}

void Bar::Deinit()
{
	/*if (NULL != _barLineSprite)
	{
		delete _barLineSprite;
		_barLineSprite = NULL;
	}*/

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		delete itr.item();
		_noteList.Remove(itr);
	}
}

void Bar::KeyDown()
{
	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.begin(); itr.valid(); itr.forth())
	{
		Note* note = itr.item();

		if (false == note->IsLive())
		{
			continue;
		}

		if (note->IsPassed())
		{
			continue;
		}

		if (note->GetCurrentTime() < _judgeGoodStartTick)
		{
			break;
		}

		if (_judgeGoodStartTick <= note->GetCurrentTime() && note->GetCurrentTime() <= _judgeGoodEndTick)
		{
			if (_judgeGreatStartTick <= note->GetCurrentTime() && note->GetCurrentTime() <= _judgeGreatEndTick) {
				GameSystem::GetInstance()->SetIsGreatJudge(true);
				EffectSoundPlay(note);
				itr.item()->SetLive(false);
				break;
			}
			else {
				GameSystem::GetInstance()->SetIsGoodJudge(true);
				itr.item()->SetLive(false);
				EffectSoundPlay(note);
				break;
			}

		}
	}
}

void Bar::KeyUp()
{
}

void Bar::EffectSoundPlay(Note* note)
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