#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include <string>
using namespace std;

#include "WFreqCounter.h"

#define DIRPATH "./prog"
#define MAXLOFFP 4096 //max length of file path

void traversalDir(string);
int main(int argc, char **argv)
{
	//WordMap wordMap = GenerateWordMapByFileName("./test.txt");
	traversalDir(DIRPATH);
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
	//			cout << "dir name is " << ent->d_name << endl;
				traversalDir(dirPath + "/" + ent->d_name);
			}
		}
		else if (ent->d_type & DT_REG)
		{
	//		cout << "file name is " << ent->d_name << endl;	
			
			struct stat buff;
			string filePath(dirPath + "/" + ent->d_name);
			if (stat(filePath.c_str(), &buff) == -1)
				err("get file stat error");
	//		cout << "file size is: " << buff.st_size << endl;
			
			char *filesPathes[10];
			memset(filesPathes, 0, sizeof(char *)*10);
			char curPath[MAXLOFFP];
			strcpy(curPath, filePath.c_str());
			filesPathes[0] = curPath;

			int fd[2];
			if (pipe(fd) == -1)
				err("create pipe error");
			filesPathes[1] = sprintf();
			

			pid_t pid;	
			if ((pid = fork()) < 0)
			{
				err("create sub process error");
			}
			else if (pid == 0)  //child
			{
				if (close(fd[0]) == -1) err("child close pipe read port error");
				WordMap *curWordMap = 0;
			    WordMap *totalWordMap = 0;
			   	for (int i=0; i<argc; i++)
				{
		    		*curWordMap = GenerateWordMapByFileName(argv[i]);
					if (totalWordMap == 0)
				    	*totalWordMap = *curWordMap;
				    else
				   		(*totalWordMap).MergeWordMaps(*curWordMap);
				}
				
			//	if (execv("./generateMap", filesPathes) == -1)
		   	//		err("generateMap error");
			}
			else
			{
				if (close(fd[1] == -1)) err("parent close pipe write port error");

			}


		//	long totalSize = buff.st_size;
		//	char *filePathes[10]; 
		//	while (totalSize >= 1024*1024)
		//	{
		//		fork();
		//		if ()
		//	}
			
		}
	}

	if (closedir(dir) == -1)
		err("closedir error");
}




