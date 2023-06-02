#pragma once

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <list>
#include <iterator>
#include <functional> // Добавлен заголовочный файл для хэш-функции

using namespace std;

template <typename KeyType, typename ValueType>
class HashNode {
public:
    KeyType key;
    ValueType value;

    HashNode(const KeyType& k, const ValueType& v) : key(k), value(v) {}
};

template <typename KeyType, typename ValueType>
class HashTable {
private:
    size_t size;
    list<HashNode<KeyType, ValueType>>* table;

public:
    HashTable(size_t tableSize);

    ~HashTable();

    bool isEmpty() const;

    size_t getSize() const;

    void insert(const KeyType& key, const ValueType& value);

    void remove(const KeyType& key);

    class Iterator {
    private:
        size_t index;
        typename list<HashNode<KeyType, ValueType>>::iterator nodeIterator;
        const HashTable<KeyType, ValueType>& hashTable;

    public:
        Iterator(const HashTable<KeyType, ValueType>& ht);

        bool isEnd() const;

        void moveToNext();

        HashNode<KeyType, ValueType>& operator*() const;

        HashNode<KeyType, ValueType>* operator->() const;

    private:
        void moveToNextIndex();
    };

    Iterator begin() const;

    Iterator end() const;

private:
    size_t hashFunction(const KeyType& key) const;
};

template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::HashTable(size_t tableSize) : size(tableSize) {
    table = new list<HashNode<KeyType, ValueType>>[size];
}

template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::~HashTable() {
    delete[] table;
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::isEmpty() const {
    for (size_t i = 0; i < size; ++i) {
        if (!table[i].empty())
            return false;
    }
    return true;
}

template <typename KeyType, typename ValueType>
size_t HashTable<KeyType, ValueType>::getSize() const {
    return size;
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value) {
    size_t index = hashFunction(key);
    table[index].push_back(HashNode<KeyType, ValueType>(key, value));
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::remove(const KeyType& key) {
    size_t index = hashFunction(key);
    typename list<HashNode<KeyType, ValueType>>::iterator it;
    for (it = table[index].begin(); it != table[index].end(); ++it) {
        if (it->key == key) {
            table[index].erase(it);
            break;
        }
    }
}

template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType>::Iterator::Iterator(const HashTable<KeyType, ValueType>& ht) : index(0), hashTable(ht) {
    if (!hashTable.table[index].empty())
        nodeIterator = hashTable.table[index].begin();
    else
        moveToNextIndex();
}

template <typename KeyType, typename ValueType>
bool HashTable<KeyType, ValueType>::Iterator::isEnd() const {
    return index >= hashTable.size;
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::Iterator::moveToNext() {
    ++nodeIterator;
    if (nodeIterator == hashTable.table[index].end())
        moveToNextIndex();
}

template <typename KeyType, typename ValueType>
HashNode<KeyType, ValueType>& HashTable<KeyType, ValueType>::Iterator::operator*() const {
    return *nodeIterator;
}

template <typename KeyType, typename ValueType>
HashNode<KeyType, ValueType>* HashTable<KeyType, ValueType>::Iterator::operator->() const {
    return &(*nodeIterator);
}

template <typename KeyType, typename ValueType>
void HashTable<KeyType, ValueType>::Iterator::moveToNextIndex() {
    ++index;
    while (index < hashTable.size && hashTable.table[index].empty())
        ++index;
    if (index < hashTable.size)
        nodeIterator = hashTable.table[index].begin();
}

template <typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator HashTable<KeyType, ValueType>::begin() const {
    return Iterator(*this);
}

template <typename KeyType, typename ValueType>
typename HashTable<KeyType, ValueType>::Iterator HashTable<KeyType, ValueType>::end() const {
    return Iterator(*this);
}

template <typename KeyType, typename ValueType>
size_t HashTable<KeyType, ValueType>::hashFunction(const KeyType& key) const {
    return hash<KeyType>{}(key) % size;
}

template <typename KeyType, typename ValueType>
HashTable<KeyType, ValueType> createHashTable(size_t size) {
    return HashTable<KeyType, ValueType>(size);
}

template <typename KeyType, typename ValueType>
void insertItem(HashTable<KeyType, ValueType>& hashTable) {
    KeyType key;
    ValueType value;
    cout << "Enter key: ";
    cin >> key;
    cout << "Enter value: ";
    cin >> value;
    hashTable.insert(key, value);
    cout << "Item inserted successfully!" << endl;
}

template <typename KeyType, typename ValueType>
void deleteItem(HashTable<KeyType, ValueType>& hashTable) {
    KeyType key;
    cout << "Enter key to delete: ";
    cin >> key;
    hashTable.remove(key);
    cout << "Item deleted successfully!" << endl;
}

template <typename KeyType, typename ValueType>
void displayHashTable(const HashTable<KeyType, ValueType>& hashTable) {
    typename HashTable<KeyType, ValueType>::Iterator it = hashTable.begin();
    while (!it.isEnd()) {
        cout << "Key: " << it->key << ", Value: " << it->value << endl;
        it.moveToNext();
    }
}

template <typename KeyType, typename ValueType>
void displayMenu(HashTable<KeyType, ValueType>& hashTable) {
    int choice;
    while (true) {
        cout << "======================" << endl;
        cout << "1. Insert item" << endl;
        cout << "2. Delete item" << endl;
        cout << "3. Display table" << endl;
        cout << "4. Check if table is empty" << endl;
        cout << "5. Exit" << endl;
        cout << "======================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            insertItem(hashTable);
            break;
        case 2:
            deleteItem(hashTable);
            break;
        case 3:
            displayHashTable(hashTable);
            break;
        case 4:
            if (hashTable.isEmpty()) {
                cout << "Table is empty." << endl;
            }
            else {
                cout << "Table is not empty." << endl;
            }
            break;
        case 5:
            cout << "Exiting..." << endl;
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}

#endif // HASHTABLE_H
