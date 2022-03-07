#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>
#include "scanner.h"

int stateTable[][8] = {{0, tkINT,  tkDELI,  tkOPRT,  tkIDENT, tkCERR, tkWSP, tkEOF},
/* STATE 1 */   {tkINT,  tkINT, tkIDENT, tkDELI, tkCERR, tkCERR, tkERR, tkERR},
/* STATE 2 */   {tkDELI, tkDELI, tkCERR, tkERR, tkERR, tkERR, tkERR, tkERR},
/* STATE 3 */   {tkOPRT,  tkOPRT, tkOPRT, tkOPRT, tkERR, tkERR, tkERR, tkERR},
/* STATE 4 */   {tkIDENT, tkIDENT, tkIDENT, tkERR, tkIDENT, tkIDENT, tkERR,  tkERR},
/* STATE 5 */   {tkCERR,  tkCERR, tkCERR, tkCERR,  tkCERR, tkCERR, tkERR, tkERR},
/* STATE 6 */   {tkWSP, tkERR, tkERR, tkERR, tkERR,  tkERR,  tkERR, tkERR}};


int getChar(char currentChar)
{
    if(isspace(currentChar))
    {
        return tkWSP;
    }
    else if(isdigit(currentChar))
    {
        return tkINT;
    }
    if ( islower(currentChar) || (currentChar == '_' ) ) {
        return tkIDENT;
    }
    else if ((currentChar == ',') || (currentChar == ';') ||
             (currentChar == '(') || (currentChar == ')') ||
             (currentChar == '[') || (currentChar == ']') ||
             (currentChar == '{') || (currentChar == '}') ||
             (currentChar == '.'))
    {

        return tkDELI;
    }
    else if ((currentChar == '+') || (currentChar == '-') ||
             (currentChar == '*') || (currentChar == '/') ||
             (currentChar == '=') || (currentChar == ':') ||
             (currentChar == '>') || (currentChar == '<') ||
             (currentChar == '%') || (currentChar == '!'))
    {
        return tkOPRT;
    }

    else if(currentChar == EOF)
    {
        return tkEOF;
    }

    return tkCERR;

}

string getName(int lexeme) {
    switch (lexeme) {
        case tkINT:
            return "Integer:";
            break;
        case tkDELI:
            return "Delimiter:";
            break;
        case tkOPRT:
            return "Operator:";
            break;
        case tkIDENT:
            return "Identifier:";
            break;
        case tkCERR:
            return "SCANNER ERROR: char:";
            break;
        case tkWSP:
            return "WhiteSpace:";
            break;
        default:
            return "SCANNER ERROR";
            break;
    }
}


vector<TokenType> Scanner(string expression)
{
    TokenType access;
    vector<TokenType> tokens;
    char currentChar = ' ';
    int col = tkERR;
    int currentState = tkERR;
    int prevState = tkERR;
    string currentToken = " ";

    for(unsigned x = 0; x < expression.length();)
    {
        currentChar = expression[x];
        col = getChar(currentChar);
        currentState = stateTable[currentState][col];

        if(currentState == tkERR)
        {
            if(prevState != tkWSP)
            {
                access.token = currentToken;
                access.lexeme = prevState;
                access.lexemeName = getName(access.lexeme);
                tokens.push_back(access);
            }
            currentToken = "";
        }
        else
        {
            currentToken += currentChar;
            ++x;
        }
        prevState = currentState;

    }

    if(currentState != tkWSP && currentToken != " ")
    {
        access.token = currentToken;
        access.lexeme = currentState;
        access.lexemeName = getName(access.lexeme);
        tokens.push_back(access);
    }
    return tokens;
}

string removeComments(string expression)
{
    string currentToken;

    bool singleComm = false;
    bool multiComm = false;

    for (unsigned i = 0; i < expression.length(); i++)
    {
	if  (singleComm == true && expression[i] == '\n')
            singleComm = false;
        
	if  (multiComm == true && expression[i] == '#' && expression[i+1] == '#')
            multiComm = false,  i++;

        else if ( singleComm || multiComm)
            continue;

        else if (expression[i] == '#' && expression[i+1] == '#')
            singleComm = true,  i++;
	
	else if (expression[i] == '#' && expression[i+1] == '#')
            multiComm = true,  i++;

        else  currentToken += expression[i];
    }
    return currentToken;
}


void printScanner(ifstream& file) {

	
    string expression;
    TokenType keywords[17] =  {
        {"start", tkKEY, "Keyword:"},
        {"stop", tkKEY, "Keyword:"},
        {"repeat", tkKEY, "Keyword:"},
        {"until", tkKEY, "Keyword:"},
        {"whole", tkKEY, "Keyword:"},
        {"label", tkKEY, "Keyword:"},
        {"quit", tkKEY, "Keyword:"},
        {"listen", tkKEY, "Keyword:"},
        {"yell", tkKEY, "Keyword:"},
        {"main", tkKEY, "Keyword:"},
        {"portal", tkKEY, "Keyword:"},
        {"if", tkKEY, "Keyword:"},
        {"then", tkKEY, "Keyword:"},
        {"pick", tkKEY, "Keyword:"},
        {"declare", tkKEY, "Keyword:"},
        {"assign", tkKEY, "Keyword:"},
        {"proc", tkKEY, "Keyword:"}
};
    string fileName;
    vector<TokenType> tokens;
    int lineCount = 0;
    string line;


    while (getline(file, expression)) {
        lineCount++;
	// use the "Scanner" function to isolate tokens
	tokens = Scanner(removeComments(expression));
	for (unsigned x = 0; x < tokens.size(); ++x) {
            //check if position is -1 or not
 		if (tokens[x].token.find(keywords[0].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[1].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[2].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[3].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[4].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[5].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[6].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[7].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[8].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[9].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[10].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[11].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[12].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[13].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[14].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[15].token, 0) != string::npos ||
                	tokens[x].token.find(keywords[16].token, 0) != string::npos )  {
                tokens[x].lexemeName = keywords[x].lexemeName;
                cout << tokens[x].lexemeName << "\t"
                     << tokens[x].token  << "\t"
                     << "line: " << lineCount << endl;
            }
            else if (tokens[x].token.size() > 8) {
                cout << "SCANNER ERROR: IDENTIFIER char size > 8: " << "\t"
                     << tokens[x].token << "\t"
                     << "line: " << lineCount << endl;
            }
            else
                cout << tokens[x].lexemeName << "\t"
                     << tokens[x].token << "\t"
                     << "line: " << lineCount << endl;
        }
    }
}
