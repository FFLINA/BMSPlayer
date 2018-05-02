#include <stdio.h>
#include <iostream>

#include "sdl_mixer.h"
#include "sdl_ttf.h"

#include "GameSystem.h"
#include "Font.h"

#include "NoteData.h"
#include "Sprite.h"
#include "Track.h"
#include "EventTrack.h"
#include "GameScene.h"
#include "SceneManager.h"

#include "BMSParser.h"

using namespace std;

GameScene::GameScene()
{
	GameSystem::GetInstance()->ResetCombo();
	GameSystem::GetInstance()->ResetScore();
}

GameScene::~GameScene()
{
	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}
}

void GameScene::Init()
{
	_backgroundSprite = new Sprite("backgroundspr", true);
	_backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWindowWidth() / 2,
		GameSystem::GetInstance()->GetWindowHeight() / 2);

	float barCount = GameSystem::GetInstance()->GetBarCount();
	float BPM = GameSystem::GetInstance()->GetBPM();					// 160	

	float barPerSec = (4 * 60) / BPM;									// 1.5  //����� 1.5�ʰ� �ɷ�����
	GameSystem::GetInstance()->SetBarPerSec(barPerSec);
	float totalPlayingSec = barPerSec * barCount;						// 1.5 * 105 = 157.5 = 2��37�� ��Ȯ
	GameSystem::GetInstance()->SetTotalPlayingTime(totalPlayingSec);	// 157.5
	
	float gameSpeed = 1.0f;

	//bar ���� = ������ ȭ�����
	int barHeight = GameSystem::GetInstance()->GetWindowHeight();		// 800


	//���� ��ü ����
	float totalbarHeight = (float)barHeight * (float)totalPlayingSec * gameSpeed;		// 800 * 154.5 = 123,600
	GameSystem::GetInstance()->SetBarHeight(totalbarHeight);


	_trackSize = GameSystem::GetInstance()->GetTrackSize();

	//�Ľ��� �����͵� �и��۾�
	NoteDataSeperate();

	_trackArray = new Array<Track*>(_trackSize);

	int eventTrackSize = _seperatedEventDataMap.size();
	_eventTrackArray = new Array<EventTrack*>(eventTrackSize);

	int startX = 70;
	for (int i = 0; i < _trackSize; i++) {
		
		int x = startX + (i * 60) + 2;
		Track* track = new Track();
		track->Init(x, _seperatedTrackDataMap[i]);
		_trackArray->Set(i, track);
	}

	int eventTrackStartX = startX + (_trackSize * 62) + 200;
	for (int i = 0; i < eventTrackSize; i++)
	{
		int x = eventTrackStartX + (i * 60) + 2;
		EventTrack* eventT = new EventTrack();
		eventT->Init(x, _seperatedEventDataMap[i]);
		_eventTrackArray->Set(i, eventT);
	}
	_gameDuration = 0;
	_curScore = 0;
	_curCombo = 0;

	_text = new Font("arialbd.ttf", 24);

}

void GameScene::Update(int deltaTime)
{
	_backgroundSprite->Update(deltaTime);
	int sumScore = 0;
	int sumCombo = 0;

	if (_gameDuration <= GameSystem::GetInstance()->GetTotalPlayingTime() + 500)
	{
		_gameDuration += deltaTime;
		
		for (int i = 0; i < _trackArray->Size(); i++) {
			Track* track = _trackArray->Get(i);

			track->Update(deltaTime);

			sumScore = GameSystem::GetInstance()->GetCurrentScore();
			sumCombo = GameSystem::GetInstance()->GetCurrentCombo();
		}

		for (int i = 0; i < _eventTrackArray->Size(); i++)
		{
			EventTrack* eventT = _eventTrackArray->Get(i);
			eventT->Update(deltaTime);
		}

		if (_curCombo != sumCombo)
		{
			_curScore = sumScore;
			_curCombo = sumCombo;
			char text[256];
			sprintf(text, 
				"Score : %04d \r\n"
				"Combo : %04d", _curScore, _curCombo);

			_text->SetText(text);
		}
	}
	else
	{
		//Mix_PauseMusic();
		SceneManager::GetInstance()->ChangeScene(eScene::SCENE_RESULT);
	}
}

void GameScene::Render()
{
	_backgroundSprite->Render();
	for (int i = 0; i < _trackArray->Size(); i++) {
		Track* track = _trackArray->Get(i);
		track->Render();
	}
	for (int i = 0; i < _eventTrackArray->Size(); i++) {
		EventTrack* eventT = _eventTrackArray->Get(i);
		eventT->Render();
	}
	_text->Render();
}

void GameScene::Deinit()
{
	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}

	for (int i = 0; i < _trackArray->Size(); i++) {
		Track* track = _trackArray->Get(i);
		track->Deinit();
		delete track;
	}
	for (int i = 0; i < _eventTrackArray->Size(); i++) {
		EventTrack* eventT = _eventTrackArray->Get(i);
		eventT->Deinit();
		delete eventT;
	}

}

void GameScene::KeyDown(unsigned int keyCode)
{
	switch (keyCode)
	{
	case SDLK_s:
		_trackArray->Get(0)->KeyDown();
		break;
	case SDLK_d:
		_trackArray->Get(1)->KeyDown();
		break;
	case SDLK_f:
		_trackArray->Get(2)->KeyDown();
		break;
	case SDLK_SPACE:
		_trackArray->Get(3)->KeyDown();
		break;
	case SDLK_j:
		_trackArray->Get(4)->KeyDown();
		break;
	case SDLK_k:
		_trackArray->Get(5)->KeyDown();
		break;
	case SDLK_l:
		_trackArray->Get(6)->KeyDown();
		break;
	}
}

void GameScene::KeyUp(unsigned int keyCode)
{
	switch (keyCode)
	{
	case SDLK_s:
		_trackArray->Get(0)->KeyUp();
		break;
	case SDLK_d:
		_trackArray->Get(1)->KeyUp();
		break;
	case SDLK_f:
		_trackArray->Get(2)->KeyUp();
		break;
	case SDLK_SPACE:
		_trackArray->Get(3)->KeyUp();
		break;
	case SDLK_j:
		_trackArray->Get(4)->KeyUp();
		break;
	case SDLK_k:
		_trackArray->Get(5)->KeyUp();
		break;
	case SDLK_l:
		_trackArray->Get(6)->KeyUp();
		break;
	}
}

void GameScene::NoteDataSeperate()
{
	
	_barNumCheck = 0;
	_barDuplicationCount = 0;

	Array<NoteData*>* row_data = GameSystem::GetInstance()->GetNoteData();
	

	for (int i = 0; i < _trackSize; i++)
	{	// null�� ���ִ� null_data Array �� trackMap�ʱ�ȭ
		Array<NoteData*>* null_data = NullDataSetting();
		_seperatedTrackDataMap.insert(std::map<int, Array<NoteData*>*>::value_type(i, null_data));
	}

	Array<NoteData*>* null_data = NullDataSetting();
	_seperatedEventDataMap.insert(std::map<int, Array<NoteData*>*>::value_type(0, null_data));

	int trackNum;

	for (int i = 0; i < row_data->Size(); i++)	// i = BMSParser::_dataCount
	{
		int barNum = row_data->Get(i)->GetBarNum();
		int channelType = row_data->Get(i)->GetChannelType();
		int channelNum = row_data->Get(i)->GetChannelNum();

		NoteData* newNoteData = row_data->Get(i);

		switch (channelNum)
		{
		case 1:	trackNum = 0; break;
		case 2:	trackNum = 1; break;
		case 3:	trackNum = 2; break;
		case 4:	trackNum = 3; break;
		case 5:	trackNum = 4; break;
		case 8:	trackNum = 5; break;
		case 9:	trackNum = 6; break;
		}

		if (1 == channelType)	// ������Ʈ ä���� ��
		{
			_seperatedTrackDataMap[trackNum]->Set(barNum, newNoteData); 
			// �ʱ�ȭ�Ҷ� null_data �� �����ͷ� �Ѱܼ� �̻��� ? < ���� / �ذ�
		}
		else  //�̺�Ʈ ä���϶�
		{
			if (1 == channelNum) // ȿ���� ä�� // �켱 1 �� �ִٰ� ����
			{
				if (_barNumCheck == barNum)
				{
					_barDuplicationCount++;
					// �ߺ� barNum�� ���涧���� 1�� �÷��� Null �ʱ�ȭ �� Set

					Array<NoteData*>* null_data = NullDataSetting();
					_seperatedEventDataMap.insert(std::map<int, Array<NoteData*>*>::value_type(_barDuplicationCount, null_data));
					_seperatedEventDataMap[_barDuplicationCount]->Set(barNum, newNoteData);
				}
				else
				{
					_seperatedEventDataMap[0]->Set(barNum, newNoteData);
					_barDuplicationCount = 0;
				}
				
				_barNumCheck = barNum;
			}
		} // if
	}
}

Array<NoteData*>* GameScene::NullDataSetting()
{
	Array<NoteData*>* null_data = new Array<NoteData*>(GameSystem::GetInstance()->GetBarCount());
	for (int i = 0; i < null_data->Size(); i++)
	{
		Array<std::string>* nullstring = new Array<std::string>(0); // GXGYGZH0 ���� ������ (string) �迭
		NoteData* nulldata = new NoteData(i, nullstring);
		null_data->Set(i, nulldata);
	}

	return null_data;
}