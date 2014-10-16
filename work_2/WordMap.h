#ifndef WORDMAP_H
#define WORDMAP_H

#include <string>
#include <map>
using namespace std;

class WordMap {

public:
	WordMap();
	void RecordWord(string, int time = 1);
	void MergeWordMaps(WordMap subMap);
	map<string, long> GetMap();

private:
	map<string, long> wordMap;

};

#endif
