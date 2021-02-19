#include "functions.hpp"

using namespace std;

int main() {


   
    vector<TokenStruct> tokens;
    string fileInput;
    fstream infile;
    infile.open("Text.txt", ios::in);                      
    if (infile.is_open()) {                                   
        while (getline(infile, fileInput)) {                      
            
            tokens = Lexer(fileInput);

            // display the tokens to the screen
            //ofstream outFile;
            //outFile.open("outputLEX.txt");
            for (unsigned i = 0; i < tokens.size(); i++)
            {
               cout << tokens[i].lexemeName << "  \t"
                    << tokens[i].token << endl;  
            }
        }
        infile.close();                                       
    }
    return 0;
}