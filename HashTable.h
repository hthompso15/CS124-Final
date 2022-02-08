//
// Created by Harrison Thompson on 11/29/20.
//

#ifndef PROJECT5_2_HASHTABLE_H
#define PROJECT5_2_HASHTABLE_H

// If this produces errors, go into CMakeLists.txt and change
// the CMAKE_CXX_STANDARD from 14 to 17.
#if __cplusplus < 17
#include <experimental/optional>
using std::experimental::optional;
using std::experimental::nullopt;
using std::experimental::make_optional;
#else
#include <optional>
using std::optional;
using std::nullopt;
using std::make_optional;
#endif

#include <functional>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::function;
using std::string;
using std::vector;

template<typename Hashable>
class HashTable {
private:
    vector<optional<Hashable>> table;
    unsigned long tableSize;

    // The function to get the key from the object
    function<string(Hashable)> getKey;

    // Hash function
    unsigned long hornerHash(string key) {
        unsigned long hashVal = 0;
        for (char &letter : key) {
            hashVal = hashVal * 37 + letter;
        }
        return hashVal % tableSize;
    }

public:
    // Constructor
    HashTable(unsigned long tableSize, function<string(Hashable)> getKey) {
        this->tableSize = tableSize;
        this->getKey = getKey;
        // Make sure the vector has room for tableSize number of elements
        table.resize(tableSize);
    }

    // insert
    void insert(Hashable item) {
        // Get the key from the item
        string key = getKey(item);
        // Hash the key to get an index
        unsigned long index = hornerHash(key);
        // Put the item at that index in the table
        table[index] = item;
    }

    // find
    // Return type is optional<Hashable> because if we find the item,
    // we return it; otherwise we return nullopt.
    optional<Hashable> find(string key) {
        unsigned long index = hornerHash(key);
        // Check that there is an object at this index
        if (table[index]) {
            // Check that the object is the one we're looking for
            if (key == getKey(*table[index])) {
                // We found the object
                return *table[index];
            }
        }
        // We did not find the object
        return nullopt;
    }

    // delete
    optional<Hashable> remove(string key) {
        unsigned long index = hornerHash(key);
        // Check that there is an object at this index
        if (table[index]) {
            // Check that the object is the one we're looking for
            if (key == getKey(*table[index])) {
                // We found the object. Delete it.
                Hashable returnObject = *table[index];
                table[index] = nullopt;
                return returnObject;
            }
        }
        // We did not find the object
        return nullopt;
    }

    // printTable
    void printTable() const {
        for (unsigned long i = 0; i < table.size(); ++i) {
            cout << i << ": ";
            // If there is a value at this index in the table
            if (table[i]) {
                // Use an * to access the value and print it
                cout << *table[i];
            }
            cout << endl;
        }
    }
};



#endif //PROJECT5_2_HASHTABLE_H
