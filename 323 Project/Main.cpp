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
    ofstream out2("outputLex.txt");
    out2 << "";
    out2.close();
    ofstream out("outputLex.txt", ios::app);

    if (infile.is_open()) {    

        bool checker = false;

        while (getline(infile, fileInput)) {

            tokenLine = Lexer(fileInput);
            bool check = Parser(tokenLine);

            if (check) {
                checker = true;
            }
            else {
                checker = false;
            }
        }

        if (checker) {

            out << "Successful run!" << endl;
        }
        else {

            out <<  "Failed. See Errors" << endl;
            
        }

        infile.close();
    }

    return 0;
}