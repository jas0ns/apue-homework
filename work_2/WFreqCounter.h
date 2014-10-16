#ifndef WFREQCOUNTER_H
#define WFREQCOUNTER_H

#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


#include "WordMap.h"

#define BUFFSIZE 4096
#define LONGESTLENGTHOFWORD 45

void err(const char *errMsg);
WordMap GenerateWordMapByFileName(const char *fileName);
bool isAlphabet(char c);

#endif


