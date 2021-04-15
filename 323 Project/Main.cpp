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
    ofstream out("outputLex.txt");
   // out << "";
    if (infile.is_open()) {    

        while (getline(infile, fileInput)) {

            tokenLine = Lexer(fileInput);
            bool check = Parser(tokenLine);
            if (check) {
                cout << endl << "Successful run!";
            }
            else {
                cout << endl << "Failed. See Errors";
                break;
            }
            //tokens.insert(tokens.end(), tokenLine.begin(), tokenLine.end());
 
        }
    }
 //   for (int i = 0; i < tokenLine.size(); i++) {
  //      cout << tokenLine[i].tokenName << endl;
   // }

    return 0;
}