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

    	int opt;
	string fileName;
	ifstream file;
	
	fileName = argv[1];
	file.open(fileName.c_str(), ios::in);

	printScanner(file);
	return 0;
}

