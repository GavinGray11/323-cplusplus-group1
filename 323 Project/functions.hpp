#pragma once
#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <stack>

using namespace std;

struct TokenStruct {
    string token;
    int tokenType;
    string tokenName;
};

struct Symbol {
    string identifier;
    int memoryLoc;
    string type;
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


//determines if syntax is correct
bool Parser(vector<TokenStruct> vec, vector<Symbol>& v2);

//checks table for existing symbol, -1 if exists or index if it does not exist
int checkTable(vector<Symbol> &v2, string id);
//scans for memory location and adds a symbol at the first available memory location
void addSymbol(vector<Symbol>& v2, string id, string type);



