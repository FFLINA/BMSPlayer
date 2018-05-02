#pragma once

#include "string"
#include "Array.h"
#include "NoteData.h"

class Sprite;
class Note;
class EventBar;

class EventTrack
{
public:
	EventTrack();
	~EventTrack();

	void Init(int x, Array<NoteData*>* seperatedData);
	void Update(int deltaTime);
	void Render();
	void Deinit();

private:

	Array<EventBar*>* _barArray;

	Sprite* _backgroundSprite;

	EventBar* _bar;

};
