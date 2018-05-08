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
	// ���� Ű(filePath) ���� �ش��ϴ� �ؽ��� �˻�
	std::map<std::string, SDL_Texture*>::iterator it = _textureMap.find(filePath);
	if (it != _textureMap.end())
	{
		// ������, �ִ� �ؽ��ĸ� ��ȯ
		return it->second;
	}
	
	// ������, �����ؼ� ��ȯ
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
	/*	todo : waveList ���� �� ���ηε� ���ϰ�
	*/
	// wavListMap[�ѹ�] = ����(���ϸ�.wav)
	// first -> �ѹ� , second -> ���ϸ�
	std::map<std::string, std::string> wavListMap = GameSystem::GetInstance()->GetWavListMap();

	Mix_Chunk* effectSound;

	std::map<std::string, std::string>::iterator it;
	for (it = wavListMap.begin(); it != wavListMap.end(); it++)
	{
		std::string filePath = "../Resources/" + _musicName + "/" + it->second;
		// �ӽ�
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