#include <iostream>
#include <list>
#include <iterator>
#include"hashtable.h"

using namespace std;

int main() {
    cout << "Welcome to the Hash Table program!" << endl;

    size_t tableSize;
    cout << "Enter the size of the hash table: ";
    cin >> tableSize;

    HashTable<string, int> hashTable = createHashTable<string, int>(tableSize);

    displayMenu(hashTable);

    return 0;
}
