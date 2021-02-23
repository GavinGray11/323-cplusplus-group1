#pragma once
#include <iostream>
#include <fstream>
#include <string> 
#include <vector>

using namespace std;

struct TokenStruct {
    string token;
    int tokenType;
    string tokenName;
};

enum FSM
{
    KILLSTATE   = 0,
    KEYWORD     = 1,
    IDENTIFIER  = 2,
    SEPERATOR   = 3,
    OPERATOR    = 4,
    INTEGER     = 5,
    REAL        = 6,
    SPACE       = 7,
    UNKNOWN     = 8,
    IGNORE      = 9
};


// function defs
vector<TokenStruct> Lexer(string expression);
int Get_FSM_Col(char currentChar);
string GetLexemeName(int tokenType);
bool findOperator(char opper);
bool findSeperator(char seperator);
bool findKeywords(string keyword);
bool findIdentifier(char ident);
bool findInteger(char integer);





