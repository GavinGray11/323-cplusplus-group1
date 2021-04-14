/*
323 Project 1 Working Iteration
Group 1 C++
----------------
Gavin Gray
Jacob Hajjar
Efrain Trujillo
Matheo Maco
Brian Landaverde
----------------
*/
#include "functions.hpp"

using namespace std;

int main() {

    vector<TokenStruct> tokens;
    string fileInput;
    fstream infile;
    infile.open("Text.txt", ios::in);   

    if (infile.is_open()) {    

        ofstream out("outputLex.txt");

        while (getline(infile, fileInput)) {                      
            
            tokens = Lexer(fileInput);

            for (unsigned i = 0; i < tokens.size(); i++)
            {
               out << tokens[i].tokenName << " \t" << "=" << " \t"
                   << tokens[i].token << endl;  
            }
        }
        infile.close();  
        out.close();
    }
    TokenStruct dollarSign;
    dollarSign.token = "$";
    dollarSign.tokenName = "$"; //compare this
    dollarSign.tokenType = 1;
    tokens.push_back(dollarSign);
    if (Parser(tokens)) {
        cout << endl << "Successful run!";
    } else if (Parser(tokens) == false) {
        cout << endl << "Failed. See Errors";
    }
    return 0;
}