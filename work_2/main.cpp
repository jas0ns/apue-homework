#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <time.h>
using namespace std;

#include "WFreqCounter.h"

#define MAXFILESIZEPERPROC 1024*1024 // max file size per process : 1MB
#define DIRPATH "./prog"
#define MAXLOFFP 4096 //max length of file path

void traversalDir(string);
void createWriteProc();
class TypeForTran {
public:
	TypeForTran()
	{
		memset(str, 0, sizeof(char[56]));
	}
	
	TypeForTran(long time, const char *str)
	{
		this->time = time;
		strcpy(this->str, str);
	}
	long time;
	char str[56];
};


int fd[2];
char *filesPathes[10];
unsigned long filesTotalSize;
int fpi = 0;

int main(int argc, char **argv)
{
	time_t start,end;
	start = time(NULL);

	WordMap *totalWordMap = 0;
	for (int i=0; i<10; i++)
	{
		filesPathes[i] = new char[MAXLOFFP];
	}

	if (pipe(fd) == -1)
		err("create pipe error");
	
	pid_t pid;
	if ((pid = fork()) < 0)
		err("create read process error");
	
	if (pid == 0)  // child
	{
		if (close(fd[1]) == -1) err("read process close pipe write port error");
		WordMap totalWordMap;
		while(1)
		{
			TypeForTran tft;
			int n;
			if ((n = read(fd[0], &tft, sizeof(TypeForTran))) == -1)
			{
				err("read pipe error");
			}
			else if (n == sizeof(TypeForTran))
			{
				totalWordMap.RecordWord(tft.str, tft.time);
			}
			else if (n == 0)
			{	
				end = time(NULL);
				cout << endl << "total time is "
					 << difftime(end, start) << "s" << endl;
				
				map<string, long> tmap = totalWordMap.GetMap();
				map<string, long>::const_iterator map_it = tmap.begin();
				while (map_it != tmap.end())
				{
					cout << map_it->first << "  " << map_it->second << endl;
					map_it ++;
				}

				break;
			}
		}
		if (close(fd[0]) == -1) err("read process close pipe read port error");
	}
	else // parent
	{
		if (close(fd[0]) == -1) err("write process close pipe read port error");
		traversalDir(DIRPATH);
		if (fpi > 0) // handle the last few files in filesPathes[]
			createWriteProc();
		if (close(fd[1]) == -1) err("parent precess close pipe write port error");
	}
	return 0;
}

void traversalDir(string dirPath)
{
	DIR *dir;
 	struct dirent *ent;

	if ((dir = opendir(dirPath.c_str())) == NULL)
		err("opendir error");

	while ((ent = readdir(dir)) != NULL)
	{
		if (ent->d_type & DT_DIR)
		{
			if (string(".") == string(ent->d_name) 
					|| string("..") == string(ent->d_name))
				continue;
			else
			{
				traversalDir(dirPath + "/" + ent->d_name);
			}
		}
		else if (ent->d_type & DT_REG)
		{
			struct stat buff;
			string filePath(dirPath + "/" + ent->d_name);
			if (stat(filePath.c_str(), &buff) == -1)
				err("get file stat error");
			
			char curPath[MAXLOFFP];
			strcpy(curPath, filePath.c_str());
			if (filesTotalSize < MAXFILESIZEPERPROC)
			{
				strcpy(filesPathes[fpi++], curPath);
				filesTotalSize += buff.st_size;
			}
			else
			{
				createWriteProc();
				fpi = 1;
				strcpy(filesPathes[0], curPath);
				filesTotalSize = buff.st_size;
			}
		}
	}

	if (closedir(dir) == -1)
		err("closedir error");
}

void createWriteProc()
{
	pid_t pid;
	if ((pid = fork()) < 0)
		err("create write process error");
			
	if (pid == 0)  // child
	{
		WordMap curWordMap;
	 	WordMap totalWordMap;
		for (int i=0; i<fpi; i++)
		{
   			curWordMap = GenerateWordMapByFileName(filesPathes[i]);
			totalWordMap.MergeWordMaps(curWordMap);
		}
	
		map<string, long> tmap = totalWordMap.GetMap();
		map<string, long>::const_iterator map_it = tmap.begin();
		while (map_it != tmap.end())
		{
			TypeForTran *tft = new TypeForTran(map_it->second, map_it->first.c_str());
			if (write(fd[1], tft, sizeof(TypeForTran)) == -1)
				err("write to pipe error");
			map_it ++;
			delete tft;
		}

		if (close(fd[1]) == -1) err("write process close pipe write port error");
	
		exit(0);
	}
}
