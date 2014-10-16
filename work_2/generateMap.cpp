#include "WFreqCounter.h"
#include "WordMap.h"

int main(int argc, char **argv)
{
	/* cout << "\nargc: " << argc << "\n"
		<< "argv[0]: " << argv[0] << endl;
	*/
	if (argc == 0 || argv == NULL)
	{
		cout << "no file for this process!" << endl;
		return -1;
	}

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
	
	return 0;
}
