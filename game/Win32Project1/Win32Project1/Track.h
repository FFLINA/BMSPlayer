#pragma once

#include "string"
#include "Array.h"
#include "NoteData.h"

class Sprite;
class Note;
class Bar;

class Track
{
private:
	Array<Bar*>* _barArray;
	
	Sprite* _backgroundSprite;
	Sprite* _judgeLineSprite;

	Bar* _bar;

	int _score;
	int _combo;

public:
	Track();
	~Track();

	void Init(int x, Array<NoteData*>* seperatedData);
	void Update(int deltaTime);
	void Render();
	void Deinit();

	int GetScore() { return _score; }
	int GetCombo() { return _combo; }

	Sprite* _explosionSprite;
	Sprite* GetExplositionSprite() { return _explosionSprite; }

	// Input
private:
	bool _isKeyDown;

public:
	void KeyDown();
	void KeyUp();

	// NoteData
public:
	//void AddNoteDataList(float barNum, Array<std::string>* beatList);

private:
	//Array<NoteData*>* _noteDataList;
	//float _barNum;
	//int _count;
	//Array<std::string>* _beatList;
};