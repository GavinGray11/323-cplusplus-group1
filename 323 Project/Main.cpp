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
    vector<Symbol> Symbols;
    string fileInput;
    fstream infile;
    infile.open("Text.txt", ios::in);   
    ofstream out2("outputLex.txt");
    out2 << "";
    out2.close();
    ofstream out("outputLex.txt", ios::app);

    if (infile.is_open()) {    

        bool checker = false;

        while (getline(infile, fileInput)) {

            tokenLine = Lexer(fileInput);
            bool check = Parser(tokenLine, Symbols);

            if (check) {
                checker = true;
            }
            else {
                checker = false;
                break;
            }
        }

        if (checker) {

            out << "Successful run!" << endl << endl;

            out << "Identifier         MemoryLocation       Type" << endl;
            for (int i = 0; i < Symbols.size(); i++) {
                out << Symbols[i].identifier << "                      " << Symbols[i].memoryLoc << "              " 
                    << Symbols[i].type << endl;
            }

        }
        else {

            out <<  "Failed. See Errors" << endl;
        }

        infile.close();
    }

    return 0;
}