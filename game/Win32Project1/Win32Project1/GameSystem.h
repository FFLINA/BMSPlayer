#pragma once

#include <map>
#include <string>

#include "SDL.h"
#include "DLinkedList.h"
#include "Note.h"
#include "NoteData.h"

class GameSystem
{
	// singleton
private:
	GameSystem();
	~GameSystem();

private:
	static GameSystem* _instance;

public:
	static GameSystem* GetInstance();

	int GetWindowWidth();
	int GetWindowHeight();

	void Quit();

	// BMS
private:
	std::map<std::string, std::string> _wavListMap;
	std::map<std::string, std::string> _bmpListMap;
	float _BPM;
	float _barMaxCount;

	int _trackSize;
	Array<NoteData*>* _noteDataList;

public:
	void AddWavListMap(std::string number, std::string context);
	std::map<std::string, std::string> GetWavListMap() { return _wavListMap; }
	void AddBmpListMap(std::string number, std::string context);
	std::map<std::string, std::string> GetBmpListMap() { return _bmpListMap; }

	void SetBPM(float bpm);
	float GetBPM() { return _BPM; }
	void SetBarCount(float barMaxCount) { _barMaxCount = barMaxCount; }
	float GetBarCount() { return _barMaxCount; }

	void SetTrackSize(int trackSize) { _trackSize = trackSize; }
	int GetTrackSize() { return _trackSize; }
	void SetNoteData(Array<NoteData*>* noteDataList) { _noteDataList = noteDataList; }
	Array<NoteData*>* GetNoteData() { return _noteDataList; }

	// combo, score
private:
	int _currentCombo;
	int _currentScore;

public:
	void ResetCombo();
	void ResetScore();
	void AddCombo();
	void AddScore(int score);
	int GetCurrentScore();
	int GetCurrentCombo();


	// track
private:
	float _barHeight;
	int _offset;
	float _totalTime;
	float _barPerSec;

public:
	float GetTotalPlayingTime();
	void SetTotalPlayingTime(float time);
	void GameSystem::SetBarPerSec(float barPerSec);
	float GameSystem::GetBarPerSec();
	void SetBarHeight(float barHeight);
	float GetBarHeight();

	void SetJudgeLineOffset(int offset) { _offset = offset; }
	int GetJudgeLineOffset() { return _offset; }

	// Judge
private:
	bool _isGreatJudge;
	bool _isGoodJudge;
	bool _isMissJudge;

public:
	void SetIsGreatJudge(bool judge) { _isGreatJudge = judge; }
	void SetIsGoodJudge(bool judge) { _isGoodJudge = judge; }
	void SetIsMissJudge(bool judge) { _isMissJudge = judge; }
	bool GetIsGreatJudge() { return _isGreatJudge; }
	bool GetIsGoodJudge() { return _isGoodJudge; }
	bool GetIsMissJudge() { return _isMissJudge; }

	// Render
private:
	SDL_Renderer* _sdlRenderer;

public:
	void SetRenderer(SDL_Renderer* sdlRenderer);
	SDL_Renderer* GetRenderer();
};
