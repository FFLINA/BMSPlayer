#pragma once
#include <map>

#include "Scene.h"
#include "Array.h"
#include "sdl_image.h"

class Sprite;
class NoteData;
class Track;
class EventTrack;
class Font;

class GameScene : public Scene
{
private:
	Array<Track*>* _trackArray;
	Array<EventTrack*>* _eventTrackArray;

	std::map<int , Array<NoteData*>*> _seperatedTrackDataMap;
	std::map<int, Array<NoteData*>*> _seperatedEventDataMap;
	int _eventTrackMaxCount;
	int _trackSize;

	int _barNumCheck;
	int _barDuplicationCount;

	int _gameDuration;

	int _curScore;
	int _curCombo;

	Font* _text;

	void NoteDataSeperate();
	Array<NoteData*>* NullDataSetting();
public:
	GameScene();
	~GameScene();

	void Init();
	void Update(int deltaTime);
	void Render();
	void Deinit();

	// Input
public:
	void KeyDown(unsigned int keyCode);
	void KeyUp(unsigned int keyCode);
};
