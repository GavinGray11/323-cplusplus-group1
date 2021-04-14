#include "functions.hpp"


/*Collumns*/
/*               rows        Keyword,    identifier,  seperator,  operator,   integer,    real,      space,     unknown      IGNORE*/
int stateTable[][10] = { {0, KEYWORD,    IDENTIFIER,  SEPERATOR,  OPERATOR,   INTEGER,    REAL,      SPACE,     UNKNOWN,     IGNORE},
/* STATE 1 */   {KEYWORD,    KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  IDENTIFIER, KILLSTATE, KILLSTATE, IDENTIFIER,  IGNORE},
/* STATE 2 */   {IDENTIFIER, KILLSTATE,  IDENTIFIER,  KILLSTATE,  KILLSTATE,  IDENTIFIER, KILLSTATE, KILLSTATE, IDENTIFIER,  IGNORE},
/* STATE 3 */   {SEPERATOR,  KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  KILLSTATE,  REAL,      KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 4 */   {OPERATOR,   KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  KILLSTATE,  KILLSTATE, KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 5 */   {INTEGER,    KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  INTEGER,    REAL,      KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 6 */   {REAL,       KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  REAL,       KILLSTATE, KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 7 */   {SPACE,      KILLSTATE,  KILLSTATE,   KILLSTATE,  KILLSTATE,  KILLSTATE,  KILLSTATE, KILLSTATE, KILLSTATE,   IGNORE},
/* STATE 8 */   {UNKNOWN,    KILLSTATE,  IDENTIFIER,  KILLSTATE,  KILLSTATE,  KILLSTATE,  KILLSTATE, KILLSTATE, UNKNOWN,     IGNORE},
/* STATE 9 */   {IGNORE,     IGNORE,     IGNORE,      IGNORE,     IGNORE,     IGNORE,     IGNORE,    IGNORE,    IGNORE,      IGNORE} };

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
        if (currentChar == '.') {
            return REAL;
        }
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

bool Parser(vector<TokenStruct> vec) {
    vector<TokenStruct> v;
    v = vec;
    TokenStruct dollarSign;
    dollarSign.token = "$";
    dollarSign.tokenName = "$"; //compare this
    dollarSign.tokenType = 1;
    v.push_back(dollarSign);
    stack <string> order;
    cout << endl;
    order.push("$");
    order.push("S");
    int i = 0;

    ofstream out("outputLex.txt");
    out << v[i].tokenName << " \t" << "=" << " \t"
        << v[i].token << endl;

    while (true) {
        if (v[i].tokenName == order.top()) {
            return true;
        }
        else if (order.top() == v[i].token) {
            i++;
            order.pop();
            out << v[i].tokenName << " \t" << "=" << " \t"
                << v[i].token << endl;
        }
        else if (order.top() == ")") {
            out << "Error: missing end parenthesis" << endl;
            return false;
        }
        else if (order.top() == "$") {
            out << "Error: missing first parenthesis" << endl;
            return false;
        }

        else if (order.top() == "S") {
            if (v[i].tokenType == 1) {
                order.pop();
                order.push("D");
                out << "<Statement> -> <Declerative>\n";
            }
            else if (v[i].tokenType == 2) {
                order.pop();
                if (v[i + 1].token == "=") {
                    order.push("A");
                    out << "<Statement> -> <Assign>\n";
                    //v[i].rules.push_back("<Statement> -> <Assign>");
                }

                else
                {
                    order.push("E");
                    out << "<Statement> -> <Expression>\n";
                }

            }
            else {
                return false;
            }
        }
        else if (order.top() == "A") {
            if (v[i].tokenType == 2) {
                order.pop();
                order.push("E");
                order.push("=");
                out << "<Assign> -> <ID> = <Expression>\n";
                i++;
                out << v[i].tokenName << " \t" << "=" << " \t"
                    << v[i].token << endl;
                //v[i].rules.push_back("<Assign> -> <ID> = <Expression>");
            }
            else {
                return false;
            }
        }
        else if (order.top() == "D") {
            if (v[i].tokenType == 1) {
                if (v[i + 1].tokenType == 2) {
                    order.pop();
                    //order.push(v[i + 1]);
                    //order.push(v[i]);
                    out << "<Declarative> -> <Type> <ID>\n";
                }
                else {
                    return false;
                }
            }

        }

        else if (order.top() == "E") {
            if (v[i].tokenType == 2 || v[i].token == "(" || v[i].tokenType == 5 || v[i].tokenType == 6) {
                order.pop();
                order.push("E'");
                order.push("T");
                out << "<Expression> -> <Term> <Expression>'\n";
            }
            else {
                cout << "error";
                return false;
            }
        }
        else if (order.top() == "T") {
            if (v[i].tokenType == 2 || v[i].token == "(" || v[i].tokenType == 5 || v[i].tokenType == 6) {
                order.pop();
                order.push("T'");
                order.push("F");
                out << " < Term > -> <factor> < Term>'\n";
            }
            else {
                cout << "Error: expecting identifier or expression" << endl;
                return false;
            }
        }
        else if (order.top() == "E'") {
            if (v[i].token == "+") {
                order.pop();
                order.push("E'");
                order.push("T");
                order.push("+");
                out << "<Expression> -> <Expression> + <Term>" << endl;
            }
            else if (v[i].token == "-") {
                order.pop();
                order.push("E'");
                order.push("T");
                order.push("-");
                out << "<Expression> -> <Expression> - <Term>" << endl;
            }
            else if (v[i].tokenName == "$" || v[i].token == ")") {
                order.pop();
                out << "<Expression>' -> <Term>" << endl;
            }
            else {
                out << "Error: no operator after ID";
                return false;
            }

        }
        else if (order.top() == "F") {
            if (v[i].tokenType == 2) {
                order.pop();
                i++;
                out << "<Factor> -> <ID>" << endl;
                out << v[i].tokenName << " \t" << "=" << " \t"
                    << v[i].token << endl;
            }
            else if (v[i].tokenType == 5 || v[i].tokenType == 6) {
                order.pop();
                i++;
                out << "<Factor> -> <Num>" << endl;
            }
            else if (v[i].token == "(") {
                order.pop();
                order.push(")");
                order.push("E");
                order.push("(");
                out << "<Factor> -> ( <Expression> )" << endl;
            }
            else {
                out << "Error: no indentifier or expression following operator" << endl;
                return false;
            }
        }
        else if (order.top() == "T'") {
            if (v[i].token == "*") {
                order.pop();
                order.push("T'");
                order.push("F");
                order.push("*");
                out << "<Term> -> <Term> * <Factor>" << endl;
            }
            else if (v[i].token == "/") {
                order.pop();
                order.push("T'");
                order.push("F");
                order.push("/");
                out << "<Term> -> <Term> / <Factor>" << endl;
            }
            else if (v[i].token == "+" || v[i].token == "-" || v[i].token == ")" || v[i].token == "$") {
                order.pop();
                out << "<Term> -> <Epsilon>" << endl;
            }
            else {
                out << "Error: expecting operator or end of expression" << endl;
                return false;
            }
        }
    }
}