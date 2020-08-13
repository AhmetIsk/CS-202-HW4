/**
* Author : Ahmet Isik
* ID: 21702226
* Section : 2
* Assignment : 4
*/
#include "HashTable.h"
#include <iostream>
using namespace std;
// initializes the hashTable
HashTable::HashTable( const int tableSize, const CollisionStrategy option )
{
    hashArr = new HashNode[tableSize];
    for (int i = 0; i < tableSize; i++) {
        hashArr[i].current = EMPTY;
    }
    numOfElements = 0;
    size = tableSize;
    this->option = option;
}
// deletes the object of hashArr
HashTable::~HashTable()
{
    delete hashArr;
}
bool HashTable::insert( const int item ) {
    // if array is full, we cannot insert a new item
    if ( numOfElements >= size)
            return false;
    else if ( option == LINEAR ) {
        int key;
        int i = 0;
        do{
            // key function
            key = ( item + i ) % size;
            // if the item is already exist in the hash, we cannot insert same number again, uniqueness
            if ( hashArr[key].number == item ) {
                cout << item  << " not inserted because it already exists" << endl;
                return false;
            }
            // for insertion, deleted or empty location can be used
            if ( hashArr[key].current == EMPTY || hashArr[key].current == DELETED ) {
            hashArr[key].number = item;
            // assign it occupied after insertion
            hashArr[key].current = OCCUPIED;
            // increase number of elements
            numOfElements++;
            cout << item  << " inserted" << endl;
            return true;
            }
            else
                i++;
        }while((hashArr[key].current == OCCUPIED) && (i < size)); // until stopping condition or not occupied location
        cout << item  << " not inserted" << endl;
        return false;
    }
    else if ( option == QUADRATIC ) {
        int key;
        int i = 0;
        do{
            key = ( item + (i*i) ) % size;
            // if the item is already exist in the hash, we cannot insert same number again, uniqueness
            if ( hashArr[key].number == item ) {
                cout << item  << " not inserted because it already exists" << endl;
                return false;
            }
            if ( hashArr[key].current == EMPTY || hashArr[key].current == DELETED ) {
            hashArr[key].number = item;
            hashArr[key].current = OCCUPIED;
            numOfElements++;
            cout << item  << " inserted" << endl;
            return true;
            }
            else
                i++;
        }while((hashArr[key].current == OCCUPIED) && (i < size)); // until stopping condition or not occupied location
        cout << item  << " not inserted" << endl;
        return false;
    }
    else if ( option == DOUBLE ) {
        int key;
        int i = 0;
        int temp = item;
        int remain;
        int reverse_item = 0;
        // operations for finding the reverse on an item
        while (temp != 0) {
            remain = temp % 10;
            reverse_item = reverse_item*10 + remain;
            temp /= 10;
        }
        // use reversed item in key
        do{
            key = ( item + (i*reverse_item) ) % size;
            // if the item is already exist in the hash, we cannot insert same number again, uniqueness
            if ( hashArr[key].number == item ) {
                cout << item  << " not inserted because it already exists" << endl;
                return false;
            }
            if ( hashArr[key].current == EMPTY || hashArr[key].current == DELETED ) {
            hashArr[key].number = item;
            hashArr[key].current = OCCUPIED;
            numOfElements++;
            cout << item  << " inserted" << endl;
            return true;
            }
            else {
                i++;
                i %= size;
            }
        }while((hashArr[key].current == OCCUPIED) && (i < size)); // until stopping condition or not occupied location
        cout << item  << " not inserted" << endl;
        return false;
    }
    return false;
}

bool HashTable::remove( const int item ) {
    if ( numOfElements == 0) // if there is no element in hash array
            return false;
    else if ( option == LINEAR ) {
        int key;
        int i = 0;
        do{
            // key function
            key = ( item + i ) % size;
            if ( (hashArr[key].number == item) && (hashArr[key].current == OCCUPIED) ) {
            hashArr[key].number = -1;
            hashArr[key].current = DELETED; // assign it deleted
            numOfElements--; // decrease number of elements
            cout << item  << " removed" << endl;
            return true;
            }
            else
                i++;
        }while((hashArr[key].current != EMPTY) && (i < size)); // until stopping condition or finding an empty location
        cout << item  << " not removed" << endl;
        return false;
    }
    else if ( option == QUADRATIC ) {
        int key;
        int i = 0;
        do{
            key = ( item + (i*i) ) % size;
            if ( (hashArr[key].number == item) && (hashArr[key].current == OCCUPIED) ) {
            hashArr[key].number = -1;
            hashArr[key].current = DELETED;
            numOfElements--;
            cout << item  << " removed" << endl;
            return true;
            }
            else
                i++;
        }while((hashArr[key].current != EMPTY) && (i < size));// until stopping condition or finding an empty location
        cout << item  << " not removed" << endl;
        return false;
    }
    else if ( option == DOUBLE ) {
        int key;
        int i = 0;
        int temp = item;
        int remain;
        int reverse_item = 0;
        // operations for finding the reverse on an item
        while (temp != 0) {
            remain = temp % 10;
            reverse_item = reverse_item*10 + remain;
            temp /= 10;
        }
        // use reversed item in key
        do{
            key = ( item + (i*reverse_item) ) % size;
            if ( (hashArr[key].number == item) && (hashArr[key].current == OCCUPIED) ) {
            hashArr[key].number = -1;
            hashArr[key].current = DELETED;
            numOfElements--;
            cout << item  << " removed" << endl;
            return true;
            }
            else
                i++;
        }while((hashArr[key].current != EMPTY) && (i < size));// until stopping condition or finding an empty location
        cout << item  << " not removed" << endl;
        return false;
    }
    return false;
}

bool HashTable::search( const int item, int& numProbes ) {
    numProbes = 0;
    if ( numOfElements == 0) // if the array is empty
            return false;
    else if ( option == LINEAR ) {
        int key;
        int i = 0;
        do{
            key = ( item + i ) % size;
            if ( (hashArr[key].number == item) && (hashArr[key].current == OCCUPIED) ) { // if the item is found increase numProbes
            numProbes++;
            cout << item  << " found after " << numProbes << " probes" << endl;
            return true;
            }
            else {
                numProbes++; // increase numProbes if not found
                i++;
            }
        }while((hashArr[key].current != EMPTY) && (i < size)); // until stopping condition or finding an empty location
        cout << item  << " not found after " << numProbes << " probes" << endl;
        return false;
    }
    else if ( option == QUADRATIC ) {
        int key;
        int i = 0;
        do{
            key = ( item + (i*i) ) % size;
            if ( (hashArr[key].number == item) && (hashArr[key].current == OCCUPIED) ) { // if the item is found increase numProbes
            numProbes++;
            cout << item  << " found after " << numProbes << " probes" << endl;
            return true;
            }
            else {
                numProbes++; // increase numProbes if not found
                i++;
            }
        }while((hashArr[key].current != EMPTY) && (i <= size)); // until stopping condition or finding an empty location
        cout << item  << " not found after " << numProbes << " probes" << endl;
        return false;
    }
    else if ( option == DOUBLE ) {
        int key;
        int i = 0;
        int temp = item;
        int remain;
        int reverse_item = 0;
        // operations for finding the reverse on an item
        while (temp != 0) {
            remain = temp % 10;
            reverse_item = reverse_item*10 + remain;
            temp /= 10;
        }
        // use reversed item in key
        do{
            key = ( item + (i*reverse_item) ) % size;
            if ( (hashArr[key].number == item) && (hashArr[key].current == OCCUPIED) ) { // if the item is found increase numProbes
            numProbes++;
            cout << item  << " found after " << numProbes << " probes" << endl;
            return true;
            }
            else {
                numProbes++; // increase numProbes if not found
                i++;
            }
        }while((hashArr[key].current != EMPTY) && (i < size)); // until stopping condition or finding an empty location
        cout << item  << " not found after " << numProbes << " probes" << endl;
        return false;
    }
    return false;
}

void HashTable::display() {
    cout << "----- Display Part -----" << endl;
    // this loop prints out the item value with its index if the node is occupied, else prints out just index number
    for (int i = 0; i < size; i++) {
        if (hashArr[i].current == OCCUPIED)
            cout << i << ": " << hashArr[i].number <<endl;
        else
            cout << i << ": " << endl;
    }
}
// this function makes unsuccessful search for each index
// it stops if the stopping condition is reached or an empty or deleted location is occupied because we are not looking for an exact item
// counts the number of probes
// it is just for linear and quadratic strategies
void HashTable::unsuccSearch(int index, int& probes ) {
    probes = 0;
    if ( option == LINEAR ) {
        for ( int i = 0; i < size; i++ ) {
            int key = ( index + i ) % size;
            if ( hashArr[key].current != OCCUPIED ) { // increases probes and returns
                probes++;
                return;
            }
            else {
                probes++; // increases probes
            }
        }
    }
    else if ( option == QUADRATIC ) {
        for ( int i = 0; i < size; i++ ) {
            int key = ( index + (i*i)) % size;
            if ( hashArr[key].current != OCCUPIED ) { // increases probes and returns
                probes++;
                return;
            }
            else {
                probes++; // increases probes
            }
        }
    }
}
void HashTable::analyze( int& numSuccProbes, int& numUnsuccProbes ) {
    int probes;
    numSuccProbes = 0;
    numUnsuccProbes = 0;
    cout << "----- Analyze Part -----" << endl;
    // searches the existed values in array and counts the number of successful search probes
    for ( int i = 0; i < size; i++ ) {
        if ( hashArr[i].current == OCCUPIED ) {
            this->search(hashArr[i].number, probes);
            numSuccProbes += probes;
        }
    }
    // as mentioned in the report
    if ( option == DOUBLE ) {
        numUnsuccProbes = -1;
    }
    else {
        // calls unsuccSearch method for each array location as mentioned in the report and calculates number of unsuccessful search probes
        for ( int i = 0; i < size; i++ ) {
            unsuccSearch(i, probes);
            numUnsuccProbes += probes;
        }
    }
    cout << "Number of successful probes = " << numSuccProbes << endl;
    cout << "Number of unsuccessful probes = " << numUnsuccProbes << endl;
}
