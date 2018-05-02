#pragma once

#include <string>
#include <map>

#include "Array.h"
#include "NoteData.h"

class BMSParser
{
public:
	BMSParser(const char* musicName, const char* fileName);
	~BMSParser();

	void Parse(const char* musicName, const char* fileName);

private:
	void Process(char* line);

	int _dataCount;
	int _trackMaxNum;
	Array<NoteData*>* _noteDataList;
};