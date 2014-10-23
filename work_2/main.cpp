#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <string>
using namespace std;

#include "WFreqCounter.h"

#define MAXFILESIZEPERPROC 1024*1024 // max file size per process : 1MB
#define DIRPATH "./prog"
#define MAXLOFFP 4096 //max length of file path

void traversalDir(string);
void createWriteProc();

int fd[2];
char *filesPathes[10];
unsigned long filesTotalSize;
int fpi = 0;

int main(int argc, char **argv)
{
	//WordMap wordMap = GenerateWordMapByFileName("./test.txt");
	WordMap *totalWordMap = 0;

	if (pipe(fd) == -1)
		err("create pipe error");
	
	pid_t pid;
	if ((pid = fork()) < 0)
		err("create read process error");
	
	if (pid == 0)  // child
	{
		if (close(fd[1] == -1)) err("read process close pipe write port error");
		while(1)
		{
			WordMap *curWordMap = 0;
			int n;
			if ((n = read(fd[0], &curWordMap, sizeof(WordMap *))) == -1)
			{
				cout << "read end" << endl;
				cout << n << endl;
				err("read pipe error");
			}
			else if (n == sizeof(WordMap *))
			{
				cout << "curWordMap address is: " << curWordMap << endl;
				
				if (totalWordMap == 0)
					totalWordMap = curWordMap;
				else
				{
					(*totalWordMap).MergeWordMaps(*curWordMap);
				}
			}
		}
	}
	else // parent
	{
		if (close(fd[0]) == -1) err("write process close pipe read port error");
		traversalDir(DIRPATH);
		if (fpi > 0) // handle the last few files in filesPathes[]
			createWriteProc();
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
			//	cout << "dir name is " << ent->d_name << endl;
				traversalDir(dirPath + "/" + ent->d_name);
			}
		}
		else if (ent->d_type & DT_REG)
		{
		//	cout << "file name is " << ent->d_name << endl;	
			struct stat buff;
			string filePath(dirPath + "/" + ent->d_name);
			if (stat(filePath.c_str(), &buff) == -1)
				err("get file stat error");
			
			char curPath[MAXLOFFP];
			strcpy(curPath, filePath.c_str());
			if (filesTotalSize < MAXFILESIZEPERPROC)
			{
				filesPathes[fpi++] = curPath;
				filesTotalSize += buff.st_size;
			}
			else
			{
				createWriteProc();
				fpi = 1;
				filesPathes[0] = curPath;
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
//		if (close(fd[0]) == -1) err("child close pipe read port error");
		WordMap *curWordMap = 0;
	 	WordMap *totalWordMap = 0;
		for (int i=0; i<fpi; i++)
		{
   			*curWordMap = GenerateWordMapByFileName(filesPathes[i]);
			if (totalWordMap == 0)
	    		totalWordMap = curWordMap;
			else
				(*totalWordMap).MergeWordMaps(*curWordMap);
		}
					
		cout << "&totalWordMap is: "  << &totalWordMap << endl;
		cout << "write begin" << endl;
		ssize_t n;
		if ((n = write(fd[1], &totalWordMap, sizeof(WordMap *))) == -1)
			err("write WordMap* to the pipe error");
		
		if (close(fd[1] == -1)) err("child close pipe write port error");
	
		exit(0);
	}
}
