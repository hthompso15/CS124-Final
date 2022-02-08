#include "HashTable.h"
#include "Fisherman.h"
#include "LinearProbing.h"
#include "SeparateChaining.h"
#include <iostream>
using namespace std;

// Hash function
unsigned long hornerHash(string key,int tableSize) {
    unsigned long hashVal = 0;
    for (char &letter : key) {
        hashVal = hashVal * 37 + letter;
    }
    return hashVal % tableSize;
}

// Method to get the Key
string getFishermanId(Fisherman fisherman) {
    return to_string(fisherman.getIdNum());
}

// Second get key method
string getFishermanRev(Fisherman fisherman) {
    return to_string(fisherman.getYear2019Rev());
}

// Method to calculate the average
double average(vector<int> vec) {
    double total = 0;
    for(int i = 0; i < vec.size(); i++) {
        total += vec[i];
    }
    long double x = total/vec.size();
    return x;
}

int main() {

    // Varying hash table sizes
    const unsigned long TABLE_SIZE = 1000;
    const unsigned long TABLE_2_SIZE = 1500;
    const unsigned long TABLE_3_SIZE = 2000;
    const unsigned long TABLE_4_SIZE = 2500;
    const unsigned long TABLE_5_SIZE = 5000;

    // Vector of 1000 objects
    vector<Fisherman> fisherman;
    getDataFromFile("CS124_datafile.csv", fisherman);


    //       SEPARATE CHAINING       //
    cout << "Separate Chaining data:" << endl;
    // Table size of 1000
    SeparateChaining<Fisherman> fishChain(TABLE_SIZE,getFishermanId);
    vector<int>numReads;
    for (Fisherman &fish : fisherman) {
        fishChain.insert(fish,numReads);
    }
    cout<< "Average number of reads of a table size of 1000 is " << average(numReads) << endl;
    int max = *max_element(numReads.begin(),numReads.end());
    cout<< "Max number of reads is " << max << endl;
    cout << endl;

    // Table size of 1500
    SeparateChaining<Fisherman> fishChain2(TABLE_2_SIZE,getFishermanId);
    vector<int>numReads2;
    for (int i = 0; i < 1501; i++) {
        fishChain.insert(fisherman[i],numReads2);
    }
    cout<< "Average number of reads of a table size of 1500 is " << average(numReads2) << endl;
    int max2 = *max_element(numReads2.begin(),numReads2.end());
    cout<< "Max number of reads is " << max2 << endl;
    cout << endl;

    // Table size of 2000
    SeparateChaining<Fisherman> fishChain3(TABLE_3_SIZE,getFishermanId);
    vector<int> numReads3;
    for (int i = 0; i < 2001; i++) {
        fishChain.insert(fisherman[i],numReads3);
    }
    cout<< "Average number of reads of a table size of 2000 is " << average(numReads3) << endl;
    int max3 = *max_element(numReads3.begin(),numReads3.end());
    cout<< "Max number of reads is " << max3 << endl;
    cout << endl;

    // Table size of 2500
    SeparateChaining<Fisherman> fishChain4(TABLE_4_SIZE,getFishermanId);
    vector<int> numReads4;
    for (int i = 0; i <2501; i++) {
        fishChain.insert(fisherman[i],numReads4);
    }
    cout<< "Average number of reads of a table size of 2500 is " << average(numReads4) << endl;
    int max4 = *max_element(numReads4.begin(),numReads4.end());
    cout<< "Max number of reads is " << max4 << endl;
    cout << endl;

    // Table size of 5000
    SeparateChaining<Fisherman> fishChain5(TABLE_5_SIZE,getFishermanId);
    vector<int> numReads5;
    for (int i = 0; i <5001; i++) {
        fishChain.insert(fisherman[i],numReads5);
    }
    cout<< "Average number of reads of a table size of 5000 is " << average(numReads5) << endl;
    int max5 = *max_element(numReads5.begin(),numReads5.end());
    cout<< "Max number of reads is " << max5 << endl;
    cout << endl;

    // Table with different hash function
    SeparateChaining<Fisherman> fishChain6(TABLE_SIZE,getFishermanId);
    vector<int> numReads6;
    for (Fisherman &fish : fisherman) {
        fishChain.insert2(fish,numReads6);
    }
    cout<< "Average number of reads of a table size of 1000 with a different hash is " << average(numReads6) << endl;
    int max6 = *max_element(numReads6.begin(),numReads6.end());
    cout<< "Max number of reads is " << max6 << endl;
    cout << endl;

    // Table with a different get key function
    SeparateChaining<Fisherman> fishChain7(TABLE_SIZE,getFishermanRev);
    vector<int> numReads7;
    for (Fisherman &fish : fisherman) {
        fishChain.insert(fish,numReads7);
    }
    cout<< "Average number of reads of a table size of 1000 with a different key is " << average(numReads7) << endl;
    int max7 = *max_element(numReads7.begin(),numReads7.end());
    cout<< "Max number of reads is " << max7 << endl;
    cout << endl;

    // Table with a different hash and get key function
    SeparateChaining<Fisherman> fishChain8(TABLE_SIZE,getFishermanRev);
    vector<int> numReads8;
    for (int i = 0; i < 1001; i++) {
        fishChain.insert(fisherman[i],numReads8);
    }
    cout<< "Average number of reads of a table size of 1000 with a different hash and key is " << average(numReads8) << endl;
    int max8 = *max_element(numReads8.begin(),numReads8.end());
    cout<< "Max number of reads is " << max8 << endl;
    cout << endl;


    //      Quadratic PROBING      //

    cout << "Quadratic Probing data:" << endl;

    // Table size of 1000
    LinearProbing<Fisherman> fishLin(TABLE_SIZE, getFishermanId);
    vector<int> linReads;
    for (int i = 0; i < 1001;i++) {
        fishLin.insert(fisherman[i],linReads);
    }
    cout<< "Average number of reads of a table size of 1000 is " << average(linReads) << endl;
    int linMax = *max_element(linReads.begin(),linReads.end());
    cout<< "Max number of reads is " << linMax << endl;
    cout << endl;

    // Table size of 1500
    LinearProbing<Fisherman> fishLin2(TABLE_2_SIZE, getFishermanId);
    vector<int> linReads2;
    for (int i = 0; i < 1501;i++) {
        fishLin2.insert(fisherman[i],linReads2);
    }
    cout<< "Average number of reads of a table size of 1500 is " << average(linReads2) << endl;
    int linMax2 = *max_element(linReads2.begin(),linReads2.end());
    cout<< "Max number of reads is " << linMax2 << endl;
    cout << endl;

    // Table size of 2000
    LinearProbing<Fisherman> fishLin3(TABLE_3_SIZE, getFishermanId);
    vector<int> linReads3;
    for (int i = 0; i < 2001;i++) {
        fishLin3.insert(fisherman[i],linReads3);
    }
    cout<< "Average number of reads of a table size of 2000 is " << average(linReads3) << endl;
    int linMax3 = *max_element(linReads3.begin(),linReads3.end());
    cout<< "Max number of reads is " << linMax3 << endl;
    cout << endl;

    // Table size of 2500
    LinearProbing<Fisherman> fishLin4(TABLE_4_SIZE, getFishermanId);
    vector<int> linReads4;
    for (int i = 0; i < 2501;i++) {
        fishLin4.insert(fisherman[i],linReads4);
    }
    cout<< "Average number of reads of a table size of 2500 is " << average(linReads4) << endl;
    int linMax4 = *max_element(linReads4.begin(),linReads4.end());
    cout<< "Max number of reads is " << linMax4 << endl;
    cout << endl;

    // Table size of 5000
    LinearProbing<Fisherman> fishLin5(TABLE_5_SIZE, getFishermanId);
    vector<int> linReads5;
    for (int i = 0; i < 5001;i++) {
        fishLin.insert(fisherman[i],linReads5);
    }
    cout<< "Average number of reads of a table size of 5000 is " << average(linReads5) << endl;
    int linMax5 = *max_element(linReads5.begin(),linReads5.end());
    cout<< "Max number of reads is " << linMax5 << endl;
    cout << endl;


    // Table size of 1500 is the most effecient
    // Table size of 1500 With new hash function
    LinearProbing<Fisherman> fishLin6(TABLE_2_SIZE, getFishermanId);
    vector<int> linReads6;
    for (int i = 0; i < 1501;i++) {
        fishLin2.insert2(fisherman[i],linReads6);
    }
    cout<< "Average number of reads of a table size of 1500 with new hash function is " << average(linReads6) << endl;
    int linMax6 = *max_element(linReads6.begin(),linReads6.end());
    cout<< "Max number of reads is " << linMax6 << endl;
    cout << endl;

    // Table size of 1500 With new hash function
    LinearProbing<Fisherman> fishLin7(TABLE_2_SIZE, getFishermanRev);
    vector<int> linReads7;
    for (int i = 0; i < 1501;i++) {
        fishLin2.insert(fisherman[i],linReads7);
    }
    cout<< "Average number of reads of a table size of 1500 with new getKey "
           "function is " << average(linReads7) << endl;
    int linMax7 = *max_element(linReads7.begin(),linReads7.end());
    cout<< "Max number of reads is " << linMax7 << endl;
    cout << endl;

    // Table size of 1500 With new hash function and new getKey function
    LinearProbing<Fisherman> fishLin8(TABLE_2_SIZE, getFishermanRev);
    vector<int> linReads8;
    for (int i = 0; i < 1501;i++) {
        fishLin2.insert2(fisherman[i],linReads8);
    }
    cout<< "Average number of reads of a table size of 1500 with new hash function and new getKet "
           "function is " << average(linReads8) << endl;
    int linMax8 = *max_element(linReads8.begin(),linReads8.end());
    cout<< "Max number of reads is " << linMax8 << endl;
    cout << endl;

    return 0;
}
