#include "WordMap.h"
#include <iostream>

WordMap::WordMap(){}

map<string, long> WordMap::GetMap()
{
	return this -> wordMap;
}

void WordMap::RecordWord(string word, int time)
{
	if (this -> wordMap.count(word))
	{
		this -> wordMap[word] += time;
	}
	else
	{
		this -> wordMap.insert(pair<string, int>(word, 1));
	}

	//cout << "record " << word << ", total number of times is " << wordMap[word] << endl;
}

void WordMap::MergeWordMaps(WordMap subMap)
{
	map<string, long>::const_iterator map_it = subMap.GetMap().begin();
	while (map_it != subMap.GetMap().end())
	{
		this -> RecordWord(map_it -> first, map_it -> second);
	}
}


