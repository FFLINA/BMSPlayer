#include <iostream>

#include "GameSystem.h"

GameSystem* GameSystem::_instance = 0;

GameSystem::GameSystem()
{
	_currentScore = 0;
	_currentCombo = 0;
	//_barMaxCount = 1;
}

GameSystem::~GameSystem()
{

}

GameSystem* GameSystem::GetInstance()
{
	if (0 == _instance)
	{
		_instance = new GameSystem();
	}
	return _instance;
}

int GameSystem::GetWindowWidth()
{
	return 1024;
}

int GameSystem::GetWindowHeight()
{
	return 800;
}

void GameSystem::Quit()
{
	SDL_Event newEvent;
	newEvent.type = SDL_QUIT;
	SDL_PushEvent(&newEvent);
}


// BMS
void GameSystem::AddWavListMap(std::string number, std::string context)
{
	_wavListMap.insert(std::map<std::string, std::string>::value_type(number, context));

	// ¸Ê Å½»ö¹æ¹ý
	/*map<std::string, char*>::iterator it;
	for (it = wavListMap.begin(); it != wavListMap.end(); it++)
	{
	cout << it->second << endl;
	}
	cout << test_dict[number] << endl;
	*/
}

void GameSystem::AddBmpListMap(std::string number, std::string context)
{
	_bmpListMap.insert(std::map<std::string, std::string>::value_type(number, context));
}

void GameSystem::SetBPM(float bpm)
{
	_BPM = bpm;
}


// combo, score
void GameSystem::ResetCombo()
{
	_currentCombo = 0;
}

void GameSystem::ResetScore()
{
	_currentScore = 0;
}

void GameSystem::AddCombo()
{
	_currentCombo++;
}

void GameSystem::AddScore(int score)
{
	_currentScore += score;
}

int GameSystem::GetCurrentScore()
{
	return _currentScore;
}

int GameSystem::GetCurrentCombo()
{
	return _currentCombo;
}

// System

void GameSystem::SetBarPerSec(float barPerSec)
{
	_barPerSec = barPerSec;
}
float GameSystem::GetBarPerSec()
{
	return _barPerSec;
}

float GameSystem::GetTotalPlayingTime()
{
	// tick
	return _totalTime;
}

void GameSystem::SetTotalPlayingTime(float time)
{
	// ÃÊ * 1000tick
	_totalTime = time * 1000;
}
void GameSystem::SetBarHeight(float barHeight)
{
	_barHeight = barHeight;
}

float GameSystem::GetBarHeight()
{
	return _barHeight;
}

void GameSystem::SetRenderer(SDL_Renderer* sdlRenderer)
{
	_sdlRenderer = sdlRenderer;
}

SDL_Renderer* GameSystem::GetRenderer()
{
	return _sdlRenderer;
}
