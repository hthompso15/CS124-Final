//
// Created by Harrison Thompson on 11/29/20.
//

#ifndef PROJECT5_2_FISHERMAN_H
#define PROJECT5_2_FISHERMAN_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

class Fisherman {
private:
    int id_num;
    int age;
    std::string state;
    int num_traps;
    int year_2018_rev;
    int year_2019_rev;
public:
    // Constructors
    Fisherman() {
        id_num = 0;
        age = 18;
        state = "ME";
        num_traps = 0;
        year_2018_rev = 0;
        year_2019_rev = 0;
    }

    Fisherman(int pn,
              int age,
              std::string st,
              int nt,
              int srr,
              int drr) {
        this->id_num = pn;
        this-> age = age;
        this->state = st;
        this->num_traps = nt;
        this->year_2018_rev = srr;
        this->year_2019_rev = drr;
    }

    // Setters
    void setIdNum(int num) {
        this->id_num = num;
    }

    void setAge(int age) {
        this->age = age;
    }

    void setHomePort(std:: string st) {
        this->state = st;
    }

    void setNumTraps(int num) {
        this->num_traps = num;
    }

    void setYear2018Rev(int rev) {
        this->year_2018_rev = rev;
    }

    void setYear2019Rev(int rev) {
        this->year_2019_rev = rev;
    }

    // Getters

    int getIdNum() {
        return id_num;
    }

    int getAge() {
        return age;
    }

    std::string getState() {
        return state;
    }

    int getNumTraps() {
        return num_traps;
    }

    int getYear2018Rev() {
        return year_2018_rev;
    }

    int getYear2019Rev() {
        return year_2019_rev;
    }

    // Overloaded method for vector output
    friend ostream& operator << (ostream& outs, const Fisherman &fish) {
        outs << left << setw(5) << fish.id_num;
        outs << right << setw(5) << fish.age;
        outs << right << setw(5) << fish.state;
        outs << right << setw(6) << fish.num_traps;
        outs << right << setw(8) << fish.year_2018_rev;
        outs << left << "  " << fish.year_2019_rev;
        return outs;
    }

    friend bool operator == (const Fisherman &lhs, const Fisherman &rhs) {
        return (lhs.id_num == rhs.id_num);
    }

    friend bool operator <= (const Fisherman &lhs, const Fisherman &rhs) {
        return (lhs.id_num <= rhs.id_num);
    }

    friend bool operator < (const Fisherman &lhs, const Fisherman &rhs) {
        return (lhs.id_num < rhs.id_num);
    }

    friend bool operator >= (const Fisherman &lhs, const Fisherman &rhs) {
        return (lhs.id_num >= rhs.id_num);
    }

    friend bool operator > (const Fisherman &lhs, const Fisherman &rhs) {
        return (lhs.id_num > rhs.id_num);
    }


};
int averageRevDiff(vector<Fisherman> &vector) {

    int counter = 0;
    for (int j = 0; j < vector.size(); ++j) {
        int revenue_diff = vector[j].getYear2018Rev() - vector[j].getYear2019Rev();
        if (revenue_diff < 0) {
            revenue_diff = revenue_diff * (-1);
        }
        counter += revenue_diff;
    }

    int average = counter / vector.size();
    return average;
}

// Method to read the data in from the file and add it do a vector
void getDataFromFile (string filename,vector<Fisherman> &fisherman) {

    ifstream fIn;
    fIn.open("../"+ filename);

    string header = "";
    if(fIn) {
        getline(fIn,header);
        //cout << header << endl;
    }

    int id_num, age, num_traps, year_2018_rev, year_2019_rev;
    string state = "";

    char comma = ',';

    while (fIn && fIn.peek() != EOF) {
        // Read id
        fIn >> id_num >> comma;

        // Read age
        fIn >> age;

        // Check to see if the stream is broken
        if (!fIn) {
            // There was no age
            age = 0;
            // Clear the stream so we can continue reading
            fIn.clear();
        }
        fIn >> comma;

        // Read state
        getline(fIn, state, ',');
        if (state == "1") {
            state = "ME";
        } else if (state == "2") {
            state = "NH";
        } else
            state = "MA";

        // Read num traps
        fIn >> num_traps;
        // Check to see if the stream is broken
        if (!fIn) {
            // There was no num_traps
            num_traps = 0;
            // Clear the stream so we can continue reading
            fIn.clear();
        }
        fIn >> comma;

        // read 2018 revenue
        fIn >> year_2018_rev;
        // Check to see if the stream is broken
        if (!fIn) {
            // There was no 2018 rev
            year_2018_rev = 0;
            // Clear the stream so we can continue reading
            fIn.clear();
        }
        fIn >> comma;

        // read year 2019 revenue
        fIn >> year_2019_rev;

        // Check to see if the stream is broken
        if (!fIn) {
            //There was no 2019 rev
            year_2019_rev = 0;
            // Clear the stream so we can continue reading
            fIn.clear();
        }

        // Create a fisherman object and add it to the vector
        fisherman.push_back(Fisherman(id_num, age, state, num_traps, year_2018_rev, year_2019_rev));
    }
    fIn.close();

}


#endif //PROJECT5_2_FISHERMAN_H
