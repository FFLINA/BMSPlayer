#include "NoteData.h"

NoteData::NoteData(float barNum, Array<std::string>* data)
{
	_barNumber = barNum;
	_channelNum = NULL;
	_channelType = NULL;
	_beatList = data;
}

NoteData::NoteData(float barNum, std::string channel, std::string data)
{
	_barNumber = barNum;
	ChannelSeparate(channel);
	DataSeparate(data);
}

NoteData::~NoteData()
{
}

void NoteData::ChannelSeparate(std::string channel)
{
	_channelType = std::stoi(channel.substr(0, 1));
	_channelNum = std::stoi(channel.substr(1, 1));
}

void NoteData::DataSeparate(std::string data)
{
	int beatSize = data.length() / 2;
	_beatList = new Array<std::string>(beatSize);
	int x = 0;
	for (int i = 0; i < beatSize; i++)
	{
		_beatList->Set(i, data.substr(x, 2));
		x += 2;
	}
}
