#include "WFreqCounter.h"

void err(const char *errMsg)
{
	cerr << errMsg << ": " 
		<< strerror(errno) << endl;
	exit(1);
}

WordMap GenerateWordMapByFileName(const char *fileName)
{
	int fd;
	char buff[BUFFSIZE];
	WordMap wordMap;
	cout << fileName << endl;
	if ((fd = open(fileName, O_RDONLY)) == -1)
		err("open file error");
	
	int readSize;
	int wiWhenCutWord = 0;
	char curWord[LONGESTLENGTHOFWORD];
	while ((readSize = read(fd, buff, BUFFSIZE)) > 0)
	{

		int wi = wiWhenCutWord != 0 ? wiWhenCutWord : 0;
		for (int i=0; i<readSize; i++)
		{
			char curc = buff[i];
			if (isAlphabet(curc))
			{
				curWord[wi] = curc <= 'Z' ? curc-'A'+'a' : curc;
				wi ++;
				
				if (i == readSize-1)
				{
					wiWhenCutWord = wi;
				}
			}
			else
			{
				if (wi != 0)
				{
					curWord[wi] = '\0'; 
					wi = 0;
					wordMap.RecordWord(curWord);		
				}
			}
		}
	}

	if (readSize == -1)
		err("read file error");

	if (close(fd) == -1)
		err("close file error");

	return wordMap;
}

bool isAlphabet(char c)
{
	if (c >= 'a' && c <= 'z' 
		|| c >= 'A' && c <= 'Z')
		return true;
	else 
		return false;
}

