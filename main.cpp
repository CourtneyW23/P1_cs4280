#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <cctype>
#include <sstream>
#include "scanner.h"

using namespace std;

//Driver function
int main(int argc,  char* argv[])
{
	string fileName;
	ifstream file;
	
	fileName = argv[1];
	file.open(fileName.c_str(), ios::in);
	
	if(file.fail())
    	{
        	cout<<"\n** ERROR - the file \""<<fileName<<"\" cannot be found!\n\n";
        	exit(1);
    	}
	printScanner(file);

	file.close();	
return 0;
}

