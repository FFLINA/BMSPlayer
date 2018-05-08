#include "GameSystem.h"

#include "Sprite.h"
#include "Note.h"

// 시작하고나서 몇초 후에 판정선에 들어오는지(startSec) , 왼쪽에서 얼마만큼 (x) 떨어져있는지
//// 판정선 위치조정 (judgeLineOffset)


Note::Note(float judgeSec, std::string noteNum, int x)
//Note::Note(float startSec, int judgeLineOffset, int x)
{
	_sprite = new Sprite("notespr", true);
	
	//_x = 노트의 x축 위치 -> 해당 트랙의 위치
	_x = x;
	_noteNumber = noteNum;
	_judgeLineOffset = GameSystem::GetInstance()->GetJudgeLineOffset();

	_isLive = true;

	_totalBarHeight = GameSystem::GetInstance()->GetBarHeight();
	int noteTick = judgeSec * 1000;
	// 전체 시간(틱) - 판정까지의 시간(틱) 
	int startTick = GameSystem::GetInstance()->GetTotalPlayingTime() - noteTick;

	_updateDuration = startTick;
	UpdatePosition(0);

	_isPassed = false;
}

Note::~Note()
{
	delete _sprite;
}

void Note::Update(int deltaTime)
{
	if (false == _isLive) return;
	UpdatePosition(deltaTime);
	_sprite->Update(deltaTime);
}

void Note::Render()
{
	if (false == _isLive) return;
	_sprite->Render();
}

void Note::UpdatePosition(int deltaTime)
{ 
	// deltaTime = 1프레임당 움직인 틱

	_updateDuration += deltaTime;

	// 가장 먼저 도착하는 노트는 , updateDuration(업데이트 된 시간) 이 가장 높다고 생각
	// 전체 시간에서 업데이트 된 시간을 나눔 -> 전체 구간에서 업테이드 된 비율이 나옴 (0.00 >= 가장늦는 노트 , 가장빠른 노트 <= 1.0)
	float timePositionRate = (float)_updateDuration / (float)GameSystem::GetInstance()->GetTotalPlayingTime();
	// 이 비율을 전체 길이에 곱함 -> 진행된만큼의 포지션을 알 수 있음
	float positionByTick = (float)_totalBarHeight * timePositionRate;


	_y = positionByTick - (_totalBarHeight - GameSystem::GetInstance()->GetWindowHeight()) - _judgeLineOffset;

	_sprite->SetPosition(_x, _y);

	if (GameSystem::GetInstance()->GetTotalPlayingTime()+500 < _updateDuration)
	{
		_isLive = false;
	}
}

bool Note::IsLive()
{
	return _isLive;
}

void Note::Passed()
{
	_isPassed = true;
}

bool Note::IsPassed()
{
	return _isPassed;
}

int Note::GetCurrentTime()
{
	return _updateDuration;
}
