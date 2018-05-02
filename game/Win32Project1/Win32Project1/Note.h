#pragma once


#include "string"

class Sprite;

class Note
{
private:
	Sprite* _sprite;

	int _updateDuration;
	int _x;
	int _y;
	std::string _noteNumber;

	int _totalBarHeight;
	int _judgeLineOffset;

	bool _isLive;
	bool _isPassed;

public:
	Note(float judgeSec, std::string noteNum, int x);
	//Note(float startSec, int judgeLineOffset, int x);
	~Note();

	void Update(int deltaTime);
	void Render();

	void UpdatePosition(int deltaTime);

	bool IsLive();
	void SetLive(bool isLive) { _isLive = isLive; }

	void Passed();
	bool IsPassed();

	int GetCurrentTime();
	std::string GetNoteNum() { return _noteNumber; }
};
