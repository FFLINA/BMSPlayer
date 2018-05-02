#pragma once

#include "SDL.h"
#include "sdl_mixer.h"
#include "sdl_ttf.h"

#include <map>
#include <string>

class ResourceManager
{
private:
	ResourceManager();
	~ResourceManager();

private:
	static ResourceManager* _instance;

public:
	static ResourceManager* GetInstance();

private:
	std::map<std::string, SDL_Texture*> _textureMap;

	std::string _musicName;
	std::map<std::string, Mix_Chunk*> _wavMap;

public:
	SDL_Texture* FindTexture(const char* filePath);

	void ResourceManager::SetMusic(const char* musicName) { _musicName = musicName; }

	Mix_Chunk* GetWav(std::string noteWav);
	void ResourceManager::LoadWav();
};
