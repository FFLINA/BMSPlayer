#include <iostream>

#include "SDL_Image.h"

#include "GameSystem.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::_instance = 0;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

ResourceManager* ResourceManager::GetInstance()
{
	if (0 == _instance)
	{
		_instance = new ResourceManager();
	}
	return _instance;
}

SDL_Texture* ResourceManager::FindTexture(const char* filePath)
{
	// 현재 키(filePath) 값에 해당하는 텍스쳐 검색
	std::map<std::string, SDL_Texture*>::iterator it = _textureMap.find(filePath);
	if (it != _textureMap.end())
	{
		// 있으면, 있는 텍스쳐를 반환
		return it->second;
	}
	
	// 없으면, 생성해서 반환
	SDL_Texture* texture = IMG_LoadTexture(GameSystem::GetInstance()->GetRenderer(), filePath);
	_textureMap[filePath] = texture;
	return texture;
}

Mix_Chunk * ResourceManager::GetWav(std::string noteWav)
{
	return _wavMap[noteWav];
}

void ResourceManager::LoadWav()
{
	/*	todo : waveList 같을 시 새로로딩 안하게
	*/
	// wavListMap[넘버] = 내용(파일명.wav)
	// first -> 넘버 , second -> 파일명
	std::map<std::string, std::string> wavListMap = GameSystem::GetInstance()->GetWavListMap();

	Mix_Chunk* effectSound;

	std::map<std::string, std::string>::iterator it;
	for (it = wavListMap.begin(); it != wavListMap.end(); it++)
	{
		std::string filePath = "../Resources/" + _musicName + "/" + it->second;
		// 임시
		filePath.pop_back();
		filePath.pop_back();
		filePath.pop_back();
		filePath.pop_back();
		filePath.append(".ogg");
		effectSound = Mix_LoadWAV(filePath.c_str());
		_wavMap[it->first] = effectSound;

		std::cout << it->first << "  :  " << filePath << std::endl;
	}

}