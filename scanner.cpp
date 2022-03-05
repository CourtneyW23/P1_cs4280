#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <unistd.h>
#include "scanner.h"

int stateTable[][8] = {{0, tkINT,  tkDELI,  tkOPRT,  tkIDENT, tkUNKN, tkWSP, tkEOF},
/* STATE 1 */   {tkINT,  tkINT, tkIDENT, tkDELI, tkUNKN, tkUNKN, tkERR, tkERR},
/* STATE 2 */   {tkDELI, tkDELI, tkUNKN, tkERR, tkERR, tkERR, tkERR, tkERR},
/* STATE 3 */   {tkOPRT,  tkOPRT, tkOPRT, tkOPRT, tkOPRT, tkOPRT, tkERR, tkERR},
/* STATE 4 */   {tkIDENT, tkIDENT, tkIDENT, tkERR, tkIDENT, tkIDENT, tkERR,  tkERR},
/* STATE 5 */   {tkUNKN,  tkUNKN, tkUNKN, tkUNKN,  tkUNKN, tkUNKN, tkERR, tkERR},
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
             (currentChar == '%') )
    {
        return tkOPRT;
    }

    else if(currentChar == EOF)
    {
        return tkEOF;
    }

    return tkUNKN;

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
        case tkUNKN:
            return "SCANNER ERROR: Unknown char:";
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

    bool comm = false;

    for (unsigned i = 0; i < expression.length(); i++)
    {

        if  (comm == true && expression[i] == '$' && expression[i+1] == '$')
            comm = false,  i++;

        else if ( comm)
            continue;

        else if (expression[i] == '$' && expression[i+1] == '$')
            comm = true,  i++;

        else  currentToken += expression[i];
    }
    return currentToken;
}

TokenType keywords[11] = {
        {"end", tkKEY, "Keyword:"},
        {"begin", tkKEY, "Keyword:"},
        {"void", tkKEY, "Keyword:"},
        {"getter", tkKEY, "Keyword:"},
        {"outter", tkKEY, "Keyword:"},
        {"main", tkKEY, "Keyword:"},
        {"if", tkKEY, "Keyword:"},
        {"then", tkKEY, "Keyword:"},
        {"assign", tkKEY, "Keyword:"},
        {"data", tkKEY, "Keyword:"},
        {"proc", tkKEY, "Keyword:"}
};

void printScanner(ifstream& file) {
	
    //ifstream file;	
    string expression = "";
    string fileName = "";
    vector<TokenType> tokens;
    int lineCount = 0;
    string line;

    //file.open(fileName.c_str());

    if(file.fail())
    {
        cout<<"\n** ERROR - the file \""<<fileName<<"\" cannot be found!\n\n";
        exit(1);
    }

    while (getline(file, expression)) {
        lineCount++;
	// use the "Scanner" function to isolate tokens
	tokens = Scanner(removeComments(expression));
        for (unsigned x = 0; x < tokens.size(); ++x) {
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
                tokens[x].token.find(keywords[10].token, 0) != string::npos) {
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

    file.close();

}
