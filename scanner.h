#include <cstdlib>
#include <cctype>
#include <string>
#include <vector>
#include "token.h"
using namespace std;

int getChar(char);
string getName(int);
vector<TokenType> Scanner(string);
string removeComments(string);
void printScanner(ifstream&);
