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
    vector<TokenStruct> tokenLine;
    string fileInput;
    fstream infile;
    infile.open("Text.txt", ios::in);   

    if (infile.is_open()) {    

        while (getline(infile, fileInput)) {

            tokenLine = Lexer(fileInput);
            if (Parser(tokenLine)) {
                cout << endl << "Successful run!";
            }
            else if (Parser(tokenLine) == false) {
                cout << endl << "Failed. See Errors";
            }
            //tokens.insert(tokens.end(), tokenLine.begin(), tokenLine.end());
 
        }
    }
    for (int i = 0; i < tokens.size(); i++) {
        cout << tokens[i].tokenName << endl;
    }
  /*  if (Parser(tokens)) {
        cout << endl << "Successful run!";
    }
    else if (Parser(tokens) == false) {
        cout << endl << "Failed. See Errors";
    } */
    return 0;
}