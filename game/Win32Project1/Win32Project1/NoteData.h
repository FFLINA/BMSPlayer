#pragma once

#include <string>

#include "Array.h"

class NoteData
{
public:
	NoteData(float barNum, Array<std::string>* data);
	NoteData(float bar, std::string channel, std::string data);
	~NoteData();

private:
	void ChannelSeparate(std::string channel);
	void DataSeparate(std::string data);

	float _barNumber;
	int _channelType;
	int _channelNum;
	Array<std::string>* _beatList;

public:
	float GetBarNum() { return _barNumber; }
	int GetChannelType() { return _channelType; }
	int GetChannelNum() { return _channelNum; }
	Array<std::string>* GetBeatList() { return _beatList; }
};
