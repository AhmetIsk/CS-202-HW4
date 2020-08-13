/**
* Author : Ahmet Isik
* ID: 21702226
* Section : 2
* Assignment : 4
*/
#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
// function to convert string inputs to integer to make operations in text file
int stringToInt(string s) {

    stringstream si(s);
    int a = 0;
    si >> a;
    return a;
}

int main(int argc, char *argv[]) {
    // receives table size as third parameter
    int tableSize = stringToInt(argv[3]);
    int numProbs, numSuccProbes, numUnsuccProbes;
    // if user enters more than 3 parameter
    if( argc > 4 ) {
       cout << "Too many arguments supplied.\n" << endl;
    }
    // if user enters less than 3 parameter
    else if( argc < 4 ) {
       cout << "Three arguments expected.\n" << endl;
    }

    ifstream inFile;
    // opens the file entered as first parameter by user
    inFile.open(argv[1]);
    if (!inFile) { // if file is not opened
        cout << "Unable to open file";
    }

    int in; // for item
    string op; // for operation type

    // according to second parameter, hash table type is determined and a new hashTable object is created
    // with given size and type and finally current items of array is displayed and table is analyzed
    // for successful and unsuccessful search
    if (string(argv[2]) == "LINEAR") {
        HashTable hash1(tableSize , LINEAR);
        while ( inFile >> op >> in ) { // reads type of operation and item value and makes operation according to these values
            if ( op == "I" )
                hash1.insert(in);
            else if ( op == "R" )
                hash1.remove(in);
            else if ( op == "S" )
                hash1.search(in, numProbs);
        }
        hash1.display();
        hash1.analyze(numSuccProbes, numUnsuccProbes);
    }

    if (string(argv[2]) == "QUADRATIC") {
        HashTable hash1(tableSize , QUADRATIC);
        while ( inFile >> op >> in ) { // reads type of operation and item value and makes operation according to these values
            if ( op == "I" )
                hash1.insert(in);
            else if ( op == "R" )
                hash1.remove(in);
            else if ( op == "S" )
                hash1.search(in, numProbs);
        }
        hash1.display();
        hash1.analyze(numSuccProbes, numUnsuccProbes);
    }

    if (string(argv[2]) == "DOUBLE") {
        HashTable hash1(tableSize , DOUBLE);
        while ( inFile >> op >> in ) { // reads type of operation and item value and makes operation according to these values
            if ( op == "I" )
                hash1.insert(in);
            else if ( op == "R" )
                hash1.remove(in);
            else if ( op == "S" )
                hash1.search(in, numProbs);
        }
        hash1.display();
        hash1.analyze(numSuccProbes, numUnsuccProbes);
    }

    inFile.close();

    return 0;
}
