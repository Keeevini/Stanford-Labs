// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include "console.h"
#include "simpio.h"
#include "filelib.h"
#include "strlib.h"
using namespace std;

string introduction();
string fillIn(string);
string requestWord(string);

int main() {
    // TODO: Finish the program!

    string inputFile = introduction();
    cout << endl;
    string output = fillIn(inputFile);
    cout << endl;
    cout << output;
    return 0;
}

string introduction() {
    cout << "Welcome to CS 106X Mad Libs!" << endl;
    cout << "I will ask you to provide various words" << endl;
    cout << "and phrases to fill in a story." << endl;
    cout <<"At the end, I will display your story to you." << endl <<endl;

    ifstream input;
    return promptUserForFile(input, "Mad Lib input file? ","Unable to open that file.  Try again.");
}

string fillIn(string inputFile) {
    ostringstream output;
    ifstream input; string line;
    input.open(inputFile);

    output << "Your Mad Lib story: " << endl;

    while (getline(input, line)) {
        istringstream input2(line); string word;
        string storage; bool toStore = false;

        while(input2 >> word){
            // cout << word << endl;
            if(stringContains(word, '<') && stringContains(word, '>')) {
                word = requestWord(word);
            }
            else {
                if(stringContains(word, '<')) {
                    toStore = true;
                    storage = word;
                } else {
                    if(toStore)
                        storage = storage + " " + word;
                }
                if(stringContains(word, '>')) {
                    word = requestWord(storage);
                    toStore = false;
                    storage = "";
                }
            }
            if(!toStore) {
                output << word << " ";
            }
        }
        // cout << line << endl;
        output << endl;
    }
    input.close();

       return output.str();
}

string requestWord(string input) {
    int openC = stringIndexOf(input, "<");
    int closeC = stringLastIndexOf(input, ">");
    string tag = input.substr(openC+1, closeC-1-openC);

    if(tag.at(0) == 'a' || tag.at(0) == 'e' || tag.at(0) == 'i' || tag.at(0) == 'o' || tag.at(0) == 'u') {
        return input.substr(0, stringIndexOf(input, tag.at(0))-1) + getLine("Please type an " + tag + ": ") + input.substr(closeC+1);
    }
        return input.substr(0, stringIndexOf(input, tag.at(0))-1) + getLine("Please type a " + tag + ": ") + input.substr(closeC+1);
}
