#include "functions.hpp"


                             /*Collumns*/
/*               rows        Keyword,    identifier,  seperator,  operator,   integer,    real,      space,     unknown      IGNORE*/
int stateTable[][10] = { {0, KEYWORD,    IDENTIFIER,  SEPERATOR,  OPERATOR,   INTEGER,    REAL,      SPACE,     UNKNOWN,     IGNORE},
/* STATE 1 */   {KEYWORD,    KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  IDENTIFIER, KILLSTATE, KILLSTATE, IDENTIFIER,  IGNORE},
/* STATE 2 */   {IDENTIFIER, KILLSTATE,  IDENTIFIER,  KILLSTATE,  KILLSTATE,  IDENTIFIER, KILLSTATE, KILLSTATE, IDENTIFIER,  IGNORE},
/* STATE 3 */   {SEPERATOR,  KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  KILLSTATE,  REAL,      KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 4 */   {OPERATOR,   KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  KILLSTATE,  KILLSTATE, KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 5 */   {INTEGER,    KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  INTEGER,    KILLSTATE, KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 6 */   {REAL,       KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  REAL,       KILLSTATE, KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 7 */   {SPACE,      KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  KILLSTATE,  KILLSTATE, KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 8 */   {UNKNOWN,    KILLSTATE,  IDENTIFIER,  KILLSTATE,  KILLSTATE,  KILLSTATE,  KILLSTATE, KILLSTATE, UNKNOWN,     IGNORE},
/* STATE 9 */   {IGNORE,     IGNORE,     IGNORE,      IGNORE,     IGNORE,     IGNORE,     IGNORE,    IGNORE,    IGNORE,      IGNORE}};

vector<TokenStruct> Lexer(string file)
{
    TokenStruct tokenObjectFound;
    vector<TokenStruct> tokens;
    char currentChar;
    int columnState = KILLSTATE;    // columns
    int currentState = KILLSTATE;   // rows
    int prevState = KILLSTATE;
    string currentToken;

   
    for (unsigned i = 0; i < file.length();)
    {
        currentChar = file[i];
        columnState = Get_FSM_Col(currentChar);
        currentState = stateTable[currentState][columnState];

       // Stays at a UNKNOWN state until it hits a KILLSTATE meaning a token was found
        if (currentState == KILLSTATE) {
            if (prevState != SPACE) {
                
                tokenObjectFound.token = currentToken;
                if (findKeywords(tokenObjectFound.token)) {
                    tokenObjectFound.tokenType = KEYWORD;
                }
                else {
                    tokenObjectFound.tokenType = prevState;
                }
                
                tokenObjectFound.tokenName = GetLexemeName(tokenObjectFound.tokenType);
                tokens.push_back(tokenObjectFound);
            }
            currentToken = "";
        } 
        else {
            currentToken += currentChar;
            i++;
        }
        prevState = currentState;

    }
    // stores the last token of the for loop that reads in the string
    if (currentState != SPACE && currentToken != "") {
        tokenObjectFound.token = currentToken;
        if (findKeywords(tokenObjectFound.token)) {
            tokenObjectFound.tokenType = KEYWORD;
        }
        else {
            tokenObjectFound.tokenType = currentState;
        }

        tokenObjectFound.tokenName = GetLexemeName(tokenObjectFound.tokenType);
        tokens.push_back(tokenObjectFound);
    }

    vector<int> toDelete;
  for (int i = 2; i < tokens.size(); i++) {
      bool check = false;
        if (tokens[i].tokenType == INTEGER && i > 1) {
            for (int j = i-1; j >= 0; j--) {
                if (tokens[j].token == "." || tokens[j].tokenType == INTEGER) {
                    tokens[i].token = tokens[j].token + tokens[i].token;
                    check = true;
                    toDelete.push_back(j);
                }
            }
        }
        if (check == true) {
            tokens[i].tokenName = "REAL";
            tokens[i].tokenType = REAL;
        }
    }
  for (int i = 0; i < toDelete.size(); i++) {
      tokens.erase(tokens.begin() + toDelete[i]);
  }

    return tokens;
}
int Get_FSM_Col(char currentChar) {
    
    if (isspace(currentChar)) {
        return SPACE;
    }
    else if (findOperator(currentChar)) {
        return OPERATOR;
    }
    else if (findSeperator(currentChar)) {
        return SEPERATOR;
    }
    else if (findIdentifier(currentChar)) {
        return IDENTIFIER;
    }
    else if (findInteger(currentChar)) {
        return INTEGER;
    } 
    else if (currentChar == '!') {
        return IGNORE;
    }

    return UNKNOWN;
}
string GetLexemeName(int lexeme) {
    switch (lexeme) {
    case KEYWORD:
        return "KEYWORD";
        break;
    case IDENTIFIER:
        return "IDENTIFIER";
        break;
    case SEPERATOR:
        return "SEPERATOR";
        break;
    case OPERATOR:
        return "OPERATOR";
        break;
    case INTEGER:
        return "INTEGER";
        break;
    case REAL:
        return "REAL  ";
        break;
    case SPACE:
        return "SPACE";
        break;
    case UNKNOWN:
        return "UNKNOWN";
        break;
    case IGNORE:
        return "IGNORE";
        break;
    default:
        return "ERROR";
        break;
    }
}

bool findOperator(char opper) {
    switch (opper) {
    case '*':
        return true;
        break;
    case '+':
        return true;
        break;
    case '-':
        return true;
        break;
    case '=':
        return true;
        break;
    case '/':
        return true;
        break;
    case '>':
        return true;
        break;
    case '<':
        return true;
        break;
    case '%':
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool findSeperator(char seperator) {
    switch (seperator) {
    case '(':
        return true;
        break;
    case ')':
        return true;
        break;
    case '{':
        return true;
        break;
    case '}':
        return true;
        break;
    case '[':
        return true;
        break;
    case ']':
        return true;
        break;
    case ',':
        return true;
        break;
    case '.':
        return true;
        break;
    case ':':
        return true;
        break;
    case ';':
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool findKeywords(string keyword) {
    
    string keywords[] = { 
        "int", "float", "bool", "True", "False", "if", "else", 
        "then", "endif", "endelse", "while", "whileend", "do", 
        "enddo", "for", "endfor", "STDinput", "STDoutput", "and", 
        "or" , "not" };
    for (int i = 0; i < 19; i++)
    if (keyword == keywords[i]) {
        return true;
    }
    return false;
}
bool findIdentifier(char ident) {
    string alphabetLower = "abcdefghijklmnopqrstuvwxyz";
    string alphabetHigher = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < alphabetHigher.length(); i++) {
        if (ident == alphabetLower[i] || ident == alphabetHigher[i]) {
            return true;
        }
    }
    return false;
}

bool findInteger(char integer) {
    switch (integer) {
    case '0':
        return true;
        break;
    case '1':
        return true;
        break;
    case '2':
        return true;
        break;
    case '3':
        return true;
        break;
    case '4':
        return true;
        break;
    case '5':
        return true;
        break;
    case '6':
        return true;
        break;
    case '7':
        return true;
        break;
    case '8':
        return true;
        break;
    case '9':
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool Parser(vector<TokenStruct> v) {
    TokenStruct dollarSign;
   // dollarSign.token = "$";
  //  dollarSign.tokenName = "$"; //compare this
  //  dollarSign.tokenType = 1;


    stack <string> order;
    cout << endl;
   // v.push_back(dollarSign);
    order.push("$");
    order.push("E");
    int i = 0;
    while (true) {
        if (v[i].tokenName == order.top()) {
            return true;
        }
        else if (order.top() == "E") {
            order.pop();
            order.push("E'");
            order.push("T");

        }
        else if (order.top() == "T") {
            if (v[i].tokenType == 2 || v[i].tokenType == 5 || v[i].tokenType == 6) {
                order.pop();
                i++;
            }
            else {
                return false;
            }
        }
        else if (order.top() == "E'"){
            if (v[i].tokenType == 4) {
                i++;
                order.push("E'");
                order.push("T");
            }
            else if (v[i].tokenName == "$") {
                order.pop();
            }
            else {
                cout << "no operator after ID";
                return false;
            }

        }
    }
    
}

