#include <cstdlib>
#include <cctype>
#include <string>

using namespace std;

enum TokenName
{
    tkERR,tkINT,tkDELI,tkOPRT,tkIDENT,tkCERR,tkWSP, tkEOF, tkKEY
};

//struct to hold token information
struct TokenType
{
	string token;
	int lexeme;
	string lexemeName;
};
