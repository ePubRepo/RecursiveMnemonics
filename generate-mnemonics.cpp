/**
 * File: generate-mnemonics.cpp
 * ----------------------------
 * This is an application that compiles phone numbers (or, more generally,
 * numbers) to mnemonics, where the digit-to-letter mappins are consistent
 * with those listed on a traditional telephone keypad.
 */

#include <string>    // for string
#include <iostream>  // for cout, endl
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

static void generateMnemonics(const string& number, Map<char, string>& mappings, Vector<string>& mnemonics) {
    if (number.length() < 1) {
        // Base Case: no string left
        cout << "hi";
    } else {
        // Resursive Case: generate more mnemonics
        char nextNumber = number.at(1);
        cout << "Length: " << mappings.get(nextNumber).length() << endl;
        cout << "Values: " << mappings.get(nextNumber) << endl;
        for (int i = 0; i < mappings.get(nextNumber).length(); i++) {
            char letter = mappings.get(nextNumber).at(i);
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
