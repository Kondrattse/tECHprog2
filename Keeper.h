#ifndef KEEPER_H
#define KEEPER_H

#include "Train.h"
#include <fstream>
#include <algorithm>

using namespace std;

class Keeper {
private:
    struct Node {
        Train data;
        Node* next;

        Node(const Train& t) : data(t), next(NULL) {}
    };

    Node* head;
    int count;

public:
    Keeper() : head(NULL), count(0) {}

    ~Keeper() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addTrain(const Train& train) {
        Node* newNode = new Node(train);

        if (!head || newNode->data.getTrainNumber() < head->data.getTrainNumber()) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next &&
                   current->next->data.getTrainNumber() < newNode->data.getTrainNumber()) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        count++;
        cout << "Train added successfully!" << endl;
    }

    void addTrainFromInput() {
        string dest, num, time;
        cout << "Enter destination: ";
        cin.ignore();
        getline(cin, dest);

        cout << "Enter train number: ";
        getline(cin, num);

        cout << "Enter departure time (HH:MM): ";
        getline(cin, time);

        Train newTrain(dest, num, time);
        addTrain(newTrain);
    }

    bool removeTrain(const string& trainNumber) {
        if (!head) return false;

        if (head->data.getTrainNumber() == trainNumber) {
            Node* temp = head;
            head = head->next;
            delete temp;
            count--;
            return true;
        }

        Node* current = head;
        while (current->next) {
            if (current->next->data.getTrainNumber() == trainNumber) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                count--;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    Train* findTrain(const string& trainNumber) {
        Node* current = head;
        while (current) {
            if (current->data.getTrainNumber() == trainNumber) {
                return &(current->data);
            }
            current = current->next;
        }
        return NULL;
    }

    void printTrainByNumber(const string& trainNumber) {
        Train* train = findTrain(trainNumber);
        if (train) {
            cout << "\n=== Train Information ===" << endl;
            cout << "Destination: " << train->getDestination() << endl;
            cout << "Train Number: " << train->getTrainNumber() << endl;
            cout << "Departure Time: " << train->getDepartureTime() << endl;
        } else {
            cout << "Train with number " << trainNumber << " not found!" << endl;
        }
    }

    void printAll() const {
        if (!head) {
            cout << "No trains in the system!" << endl;
            return;
        }

        cout << "\n=== All Trains (Sorted by Number) ===" << endl;
        cout << "Destination\t\tTrain Number\tDeparture" << endl;
        cout << "----------------------------------------" << endl;

        Node* current = head;
        while (current) {
            cout << current->data.getDestination() << "\t\t"
                 << current->data.getTrainNumber() << "\t\t"
                 << current->data.getDepartureTime() << endl;
            current = current->next;
        }
    }

    bool editTrain(const string& trainNumber) {
        Train* train = findTrain(trainNumber);
        if (!train) return false;

        cout << "\nEditing train " << trainNumber << endl;
        cout << "Current information:" << endl;
        cout << "Destination: " << train->getDestination() << endl;
        cout << "Departure Time: " << train->getDepartureTime() << endl;

        cout << "\nEnter new information (press Enter to keep current):" << endl;

        string input;
        cout << "Destination [" << train->getDestination() << "]: ";
        cin.ignore();
        getline(cin, input);
        if (!input.empty()) train->setDestination(input);

        cout << "Train number [" << train->getTrainNumber() << "]: ";
        getline(cin, input);
        if (!input.empty()) train->setTrainNumber(input);

        cout << "Departure time [" << train->getDepartureTime() << "]: ";
        getline(cin, input);
        if (!input.empty()) train->setDepartureTime(input);

        return true;
    }

    void saveToFile(const string& filename) const {
        ofstream out;
        out.open(filename.c_str());

        if (!out.is_open()) {
            cout << "Error opening file for writing!" << endl;
            return;
        }

        out << count << endl;
        Node* current = head;
        while (current) {
            out << current->data.getDestination() << endl;
            out << current->data.getTrainNumber() << endl;
            out << current->data.getDepartureTime() << endl;
            current = current->next;
        }

        out.close();
        cout << "Data saved to file " << filename << endl;
    }

    void loadFromFile(const string& filename) {
        ifstream in;
        in.open(filename.c_str());

        if (!in.is_open()) {
            cout << "Error opening file for reading!" << endl;
            return;
        }

        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = NULL;
        count = 0;

        int fileCount;
        in >> fileCount;
        in.ignore();

        for (int i = 0; i < fileCount; i++) {
            string dest, num, time;
            getline(in, dest);
            getline(in, num);
            getline(in, time);

            Train train(dest, num, time);
            addTrain(train);
        }

        in.close();
        cout << "Data loaded from file " << filename << endl;
    }

    int getCount() const { return count; }
    bool isEmpty() const { return count == 0; }
};

#endif
