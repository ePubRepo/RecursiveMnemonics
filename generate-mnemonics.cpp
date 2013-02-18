/**
 * File: generate-mnemonics.cpp
 * ----------------------------
 * This is an application that compiles phone numbers (or, more generally,
 * numbers) to mnemonics, where the digit-to-letter mappins are consistent
 * with those listed on a traditional telephone keypad.
 */

#include <string>    // for string
#include <iostream>  // for cout, endl
#include <sstream>
using namespace std;

#include "console.h"
#include "simpio.h"  // for getLine
#include "vector.h"  // for the Vector class template
#include "map.h"     // for the Map class template

static void buildMappings(Map<char, string>& mappings) {
    const string options[] = {
        "ABC", "DEF", "GHI", "JKL",
        "MNO", "PQRS", "TUV", "WXYZ"
    };
    
    for (int i = 0; i < sizeof(options)/sizeof(options[0]); i++) {
        mappings['2' + i] = options[i];
    }
}

static bool isAllPositiveDigits(const string& response) {
    for (int i = 0; i < response.size(); i++) {
        if (response[i] < '2' || response[i] > '9') {
            return false;
        }
    }
    
    return true;
}

static string getPhoneNumber() {
    while (true) {
        string response = getLine("Enter a string of digits [or hit <enter> if you're done]: ");
        if (isAllPositiveDigits(response)) return response;
        cout << "Whatever you enter, make sure it includes only digit characters in ['2', '9'].  ";
        cout << "Please try again." << endl;
    }
}

/*
static void generateMnemonics(const string& number, Map<char, string>& mappings, Vector<string>& mnemonics) {
    if (number.length() == 1) {
        char myDigit = number.at(0);
        string possibleChars = mappings.get(myDigit);
    } else {
        
    }
}
*/

/*
static void generateMnemonics(const string& number, Map<char, string>& mappings, Vector<string>& mnemonics) {
    if (number.length() == 1) {
        char myDigit = number.at(0);
        string possibleChars = mappings.get(myDigit);
        for (int i = 0; i < possibleChars.length(); i++) {
            char charToAdd = mappings.get(myDigit).at(i);
            stringstream ss;
            string toAdd;
            ss << charToAdd;
            ss >> toAdd;
            mnemonics.add(toAdd);
        }
    } else {
        
    }
}
*/

/*
static void generateMnemonics(const string& number, Map<char, string>& mappings, Vector<string>& mnemonics) {
    if (number.length() == 1) {
        char myDigit = number.at(0);
        string possibleChars = mappings.get(myDigit);
        for (int i = 0; i < possibleChars.length(); i++) {
            char charToAdd = mappings.get(myDigit).at(i);
            stringstream ss;
            string toAdd;
            ss << charToAdd;
            ss >> toAdd;
            mnemonics.add(toAdd);
        }
    } else {
        for (int i = 0; i < number.length(); i++) {
            char ch = number[i];
            string rest = number.substr(0, i) + number.substr(i + 1);
            generateMnemonics(rest, mappings, mnemonics);
            for (int n = 0; n < mnemonics.size(); n++) {
                string s = mnemonics.get(n);
                mnemonics.add(ch + s);
            }
        }
    }
}
 */


static void generateMnemonics(const string& number, Map<char, string>& mappings, Vector<string>& mnemonics) {
    char myDigit = number.at(0);
    
    if (number.length() == 1) {
        string possibleChars = mappings.get(myDigit);
        for (int i = 0; i < possibleChars.length(); i++) {
            char charToAdd = mappings.get(myDigit).at(i);
            stringstream ss;
            string toAdd;
            ss << charToAdd;
            ss >> toAdd;
            mnemonics.add(toAdd);
        }
    } else {
        string newNumber = number.substr(1, number.length() - 1);
        generateMnemonics(newNumber, mappings, mnemonics);
        string myLetters = mappings.get(myDigit);
        int initialSize = mnemonics.size();
        for (int j = 0; j < initialSize; j++) {
            string s = mnemonics.get(0);
            mnemonics.remove(0);
            for (int k = 0; k < myLetters.size(); k++) {
                mnemonics.add(myLetters.at(k) + s);
            }
        }
    }
}

int main() {
    Map<char, string> mappings;
    buildMappings(mappings);
    while (true) {
        string number = getPhoneNumber();
        if (number.empty()) break;
        Vector<string> mnemonics;
        generateMnemonics(number, mappings, mnemonics);
        cout << "These are the possible mnemonics: " << endl << endl;
        int count = 0;
        foreach (string mnemonic in mnemonics) {
            cout << "  " << mnemonic;
            count = (count + 1) % 9;
            if (count % 9 == 0) cout << endl;
        }
        cout << endl;
    }
    
    return 0;
}
