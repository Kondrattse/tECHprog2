#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Train {
private:
    string destination;
    string trainNumber;
    string departureTime;

public:
    Train() : destination(""), trainNumber(""), departureTime("") {}

    Train(const string& dest, const string& num, const string& time) {
        destination = dest;
        trainNumber = num;
        departureTime = time;
    }

    Train(const Train& other) {
        destination = other.destination;
        trainNumber = other.trainNumber;
        departureTime = other.departureTime;
    }

    ~Train() {}

    string getDestination() const { return destination; }
    string getTrainNumber() const { return trainNumber; }
    string getDepartureTime() const { return departureTime; }

    void setDestination(const string& dest) { destination = dest; }
    void setTrainNumber(const string& num) { trainNumber = num; }
    void setDepartureTime(const string& time) { departureTime = time; }

    bool operator<(const Train& other) const {
        return trainNumber < other.trainNumber;
    }

    Train& operator=(const Train& other) {
        if (this != &other) {
            destination = other.destination;
            trainNumber = other.trainNumber;
            departureTime = other.departureTime;
        }
        return *this;
    }

    bool operator==(const string& number) const {
        return trainNumber == number;
    }
};

#endif
