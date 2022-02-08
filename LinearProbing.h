//
// Created by Harrison Thompson on 11/29/20.
//

#ifndef PROJECT5_2_LINEARPROBING_H
#define PROJECT5_2_LINEARPROBING_H

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
class LinearProbing {
private:
    enum state {empty, filled, removed};
    struct hashItem {
        Hashable item;
        state status;
    };
    vector<hashItem> table; // This allows table[i].item and table[i].status
    unsigned long tableSize;
    unsigned long numItems;

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

    // Different hash function
    unsigned long hornerHash2(string key) {
        unsigned long hashVal = 0;
        for (char &letter : key) {
            hashVal = hashVal * 2 + letter;
        }
        return hashVal / tableSize;
    }

        // Find the next prime number
    int nextPrime(int n) {
        if (n % 2 == 0) {
            ++n;
        }
        bool prime = false;
        while (!prime) {
            prime = true;
            for (int i = 3; i * i <= n; i += 2) {
                if (n % i == 0) {
                    prime = false;
                }
            }
            n += 2;
        }
        return (n-2);
    }

    // Helper method to rehash
    void rehash(vector<int> &numReads) {
        // Save a copy of the hash table
        vector<hashItem> oldTable = table;
        // Double the size of the table and go to the next prime
        tableSize = nextPrime(tableSize * 2);
        table.clear();
        table.resize(tableSize);
        // Reinsert all of the items
        numItems = 0;
        for (unsigned long i = 0; i < oldTable.size(); ++i) {
            if (oldTable[i].status == filled) {
                insert(oldTable[i].item,numReads);
            }
        }
    }

public:
    // Constructor
    LinearProbing(unsigned long tableSize, function<string(Hashable)> getKey) {
        this->tableSize = nextPrime(tableSize);
        this->getKey = getKey;
        numItems = 0;
        // Make sure the vector has room for tableSize number of elements
        // This should default all the statuses to empty
        table.resize(this->tableSize);
    }

    // insert
    void insert(Hashable item, vector<int> &numReads) {
        int reads = 0;
        // Get the key from the item
        string key = getKey(item);
        if (!find(key,reads)) {
            // Hash the key to get an index
            unsigned long index = hornerHash(key);
            // Probe until we find a spot to insert
            int x = 1;
            while (table[index].status == filled) {
                index = (index + (x*x)) % tableSize;
                x++;
            }
            // Save a copy of the state
            state temp = table[index].status;
            // Insert the item
            table[index].item = item;
            table[index].status = filled;
            if (temp == empty) {
                // Update numItems
                ++numItems;
                // Check if we need to rehash
                if (numItems > (tableSize / 2)) {
                    // Less than half of the table is empty. Rehash.
                    rehash(numReads);
                }
            }
        }
        numReads.push_back(reads);
    }

    // Insert2 method with new hash
    // insert
    void insert2(Hashable item, vector<int> &numReads) {
        int reads = 0;
        // Get the key from the item
        string key = getKey(item);
        if (!find(key,reads)) {
            // Hash the key to get an index
            unsigned long index = hornerHash2(key);
            // Probe until we find a spot to insert
            int x = 1;
            while (table[index].status == filled) {
                index = (index + (x*x)) % tableSize;
                x++;
            }
            // Save a copy of the state
            state temp = table[index].status;
            // Insert the item
            table[index].item = item;
            table[index].status = filled;
            if (temp == empty) {
                // Update numItems
                ++numItems;
                // Check if we need to rehash
                if (numItems > (tableSize / 2)) {
                    // Less than half of the table is empty. Rehash.
                    rehash(numReads);
                }
            }
        }
        numReads.push_back(reads);
    }

    // TODO: make sure we do not infinitely probe
    // find
    // Return type is optional<Hashable> because if we find the item,
    // we return it; otherwise we return nullopt.
    optional<Hashable> find(string key,int &reads) {
        unsigned long index = hornerHash(key);
        // Probe
        reads++;
        while (table[index].status != empty) {
            reads++;
            reads++;
            // Check if there's an item and if that item is the one we're looking for
            if (table[index].status == filled && key == getKey(table[index].item)) {
                // We found the object
                reads++;
                return table[index].item;
            }
            index = (index + 1) % tableSize;
        }
        // We did not find the object
        return nullopt;
    }

    // delete
    optional<Hashable> remove(string key) {
        unsigned long index = hornerHash(key);
        // Probe
        while (table[index].status != empty) {
            // Check if there's an item and if that item is the one we're looking for
            if (table[index].status == filled && key == getKey(table[index].item)) {
                // We found the object. Remove it.
                table[index].status = removed;
                return table[index].item;
            }
            index = (index + 1) % tableSize;
        }
        // We did not find the object
        return nullopt;
    }

    // printTable
    void printTable() const {
        for (unsigned long i = 0; i < table.size(); ++i) {
            cout << i << ": ";
            // If there is a value at this index in the table
            if (table[i].status == filled) {
                cout << table[i].item;
            } else if (table[i].status == removed) {
                cout << "X";
            }
            cout << endl;
        }
    }
};


#endif //PROJECT5_2_LINEARPROBING_H
