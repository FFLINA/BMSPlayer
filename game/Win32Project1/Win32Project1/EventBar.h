#pragma once

#include <map>
#include <string>

#include "DLinkedList.h"
#include "Array.h"

class Sprite;
class Note;

class EventBar
{
public:
	EventBar(Array<NoteData*>* noteDataList);
	~EventBar();

private:
	float _barCount;

	Array<NoteData*>* _noteDataList;
	DLinkedList<Note*> _noteList;

	std::map<std::string, std::string> _wavList;
	std::map<std::string, std::string> _bmpList;


	int judgeTick;

	int _judgeGoodStartTick;
	int _judgeGreatStartTick;
	int _judgeGreatEndTick;
	int _judgeGoodEndTick;

public:
	void Init(int x);
	void Update(int deltaTime);
	void Render();
	void Deinit();

	// test
	void EffectSoundPlay(Note* note);

private:
	int _updateDuration;
	int _barXposition;
	int _barYposition;
};
