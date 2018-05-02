#pragma once

#include <map>
#include <string>

#include "DLinkedList.h"
#include "Array.h"

class Sprite;
class Note;

class Bar
{
public:
	Bar(Array<NoteData*>* noteDataList);
	~Bar();

private:
	float _barCount;

	Array<NoteData*>* _noteDataList;
	DLinkedList<Note*> _noteList;

	Sprite* _barLineSprite;
	DLinkedList<Sprite*> _barLineList;
	
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


	// Input
	void KeyDown();
	void KeyUp();

	// test
	void EffectSoundPlay(Note* note);

	// update test
public:
	void UpdatePosition(float deltaTime);

private:
	int _updateDuration;
	int _barXposition;
	int _barYposition;
};
