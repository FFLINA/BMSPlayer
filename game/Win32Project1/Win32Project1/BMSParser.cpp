#include <iostream>
#include <fstream>

#include "BMSParser.h"
#include "GameSystem.h"
#include "ResourceManager.h"
#include "Note.h"

using namespace std;

BMSParser::BMSParser(const char* musicName, const char* fileName)
{
	_dataCount = 0;
	_trackMaxNum = 0;
	ResourceManager::GetInstance()->SetMusic(musicName);
	Parse(musicName,fileName);
}

BMSParser::~BMSParser()
{
}

void BMSParser::Parse(const char* musicName, const char* fileName)
{
	std::ifstream ifile;

	char line[200]; // �� �پ� �о �ӽ÷� ������ ����

	char filePath[256];
	sprintf(filePath, "../Resources/%s/%s.bms",musicName, fileName);
	ifile.open(filePath);  // ���� ����

	if (ifile.is_open())
	{
		printf("���� ���� ����\n");

		_noteDataList = new Array<NoteData*>(2048);

		while (ifile.getline(line, sizeof(line))) // �� �پ� �о� ó���� �����Ѵ�.
		{
			Process(line);
		}

		// ������ ������ŭ ��������
		_noteDataList->Resize(_dataCount);

		int trackSize;
		if (9 == _trackMaxNum)
			trackSize = 7;
		else
			trackSize = _trackMaxNum;

		GameSystem::GetInstance()->SetTrackSize(trackSize);
		GameSystem::GetInstance()->SetNoteData(_noteDataList);
	}

	ifile.close(); // ���� �ݱ�
	_dataCount = 0;
}

void BMSParser::Process(char* line)
{

	// line�� ���������
	if (strcmp(line, "") == 0)
		return;

	// ���� ����
	char* contents = NULL;


	if (!strncmp(line, "#", 1))
	{
		std::string token = strtok_s(line, " :", &contents);
		const char* c_token = token.c_str();
		float barMaxCount = 0.0f;

		if (!strcmp(c_token, "#PLAYER"))
		{
			int Player = atoi(contents);
		}
		else if (!strcmp(c_token, "#GENRE"))
		{
		}
		else if (!strcmp(c_token, "#TITLE"))
		{
		}
		else if (!strcmp(c_token, "#ARTIST"))
		{
		}
		else if (!strcmp(c_token, "#BPM"))
		{
			GameSystem::GetInstance()->SetBPM(atof(contents));
		}
		else if (!strcmp(c_token, "#PLAYLEVEL"))
		{
		}
		else if (!strcmp(c_token, "#DIFFICULTY"))
		{
		}
		else if (!strcmp(c_token, "#RANK"))
		{
		}
		else if (!strcmp(c_token, "#TOTAL"))
		{
		}
		else if (!strcmp(c_token, "#VOLWAV"))
		{
		}
		else if (!strcmp(c_token, "#STAGEFILE"))
		{
		}
		else if (!strcmp(c_token, "#MIDIFILE"))
		{
		}
		else if (!strcmp(c_token, "#VIDEOFILE"))
		{
		}
		else if (!strncmp(c_token, "#WAV", 4))
		{
			std::string number = token.substr(4, 2);
			std::string s_contents(contents);
			GameSystem::GetInstance()->AddWavListMap(number, s_contents);

		}
		else if (!strncmp(c_token, "#BMP", 4))
		{
			std::string number = token.substr(4, 2);
			std::string s_contents(contents);
			GameSystem::GetInstance()->AddBmpListMap(number, s_contents);
		}
		else // ������ ����
		{
			if (0 != strcmp(contents, "00"))
			{
				float barNumber = std::stof(token.substr(1, 3));
				std::string channelNum = token.substr(4, 2);
				std::string noteContents = contents;

				std::string trackType = channelNum.substr(0, 1);
				std::string trackNum = channelNum.substr(1, 1);
				
				// "1" �̸� 0�� return
				if (0 == trackType.compare("1"))
				{
					if (_trackMaxNum < stoi(trackNum))
						_trackMaxNum = stoi(trackNum);
				}

				//��Ʈ�� ���� �������� ����Ʈ�� ��� ����
				
 				NoteData* noteData = new NoteData(barNumber, channelNum, noteContents);

				_noteDataList->Set(_dataCount, noteData);
				
				if (barMaxCount < barNumber)
				{
					barMaxCount = barNumber;
					GameSystem::GetInstance()->SetBarCount(barMaxCount + 3);
				}
				_dataCount++;
			}
		}
	}
	else
	{
		return;
	}
}
