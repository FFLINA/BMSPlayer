#include "GameSystem.h"

#include "Sprite.h"
#include "Note.h"

// �����ϰ��� ���� �Ŀ� �������� ��������(startSec) , ���ʿ��� �󸶸�ŭ (x) �������ִ���
//// ������ ��ġ���� (judgeLineOffset)


Note::Note(float judgeSec, std::string noteNum, int x)
//Note::Note(float startSec, int judgeLineOffset, int x)
{
	_sprite = new Sprite("notespr", true);
	
	//_x = ��Ʈ�� x�� ��ġ -> �ش� Ʈ���� ��ġ
	_x = x;
	_noteNumber = noteNum;
	_judgeLineOffset = GameSystem::GetInstance()->GetJudgeLineOffset();

	_isLive = true;

	_totalBarHeight = GameSystem::GetInstance()->GetBarHeight();
	int noteTick = judgeSec * 1000;
	// ��ü �ð�(ƽ) - ���������� �ð�(ƽ) 
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
	// deltaTime = 1�����Ӵ� ������ ƽ

	_updateDuration += deltaTime;

	// ���� ���� �����ϴ� ��Ʈ�� , updateDuration(������Ʈ �� �ð�) �� ���� ���ٰ� ����
	// ��ü �ð����� ������Ʈ �� �ð��� ���� -> ��ü �������� �����̵� �� ������ ���� (0.00 >= ����ʴ� ��Ʈ , ������� ��Ʈ <= 1.0)
	float timePositionRate = (float)_updateDuration / (float)GameSystem::GetInstance()->GetTotalPlayingTime();
	// �� ������ ��ü ���̿� ���� -> ����ȸ�ŭ�� �������� �� �� ����
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
