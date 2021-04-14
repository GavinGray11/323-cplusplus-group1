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
 
        }
        infile.close();
        out.close();
    }
  
    if (Parser(tokens)) {
        cout << endl << "Successful run!";
    }
    else if (Parser(tokens) == false) {
        cout << endl << "Failed. See Errors";
    }
    return 0;
}