#include <cstdlib>
#include <cctype>
#include <string>

using namespace std;

enum TokenName
{
    tkERR = 0,tkINT,tkDELI,tkOPRT,tkIDENT,tkUNKN,tkWSP, tkEOF, tkKEY
};

//struct to hold token information
struct TokenType
{
	string token;
	int lexeme;
	string lexemeName;
};
