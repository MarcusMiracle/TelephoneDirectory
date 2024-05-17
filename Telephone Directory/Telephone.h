/**
* File Name: Telephone.h
* Programmer: Miracle Marcus
* Program Title: Telephone Directory
* Program Goal: Create a telephone directory using linked lists
* Date: 12th May, 2024
*/
#ifndef TELEPHONE_H
#define TELEPHONE_H

#include <iostream>
#include <string>
#include <list>
#include <fstream>

using namespace std;

template <class T>
struct Node {
    T entry;
    Node<T>* next;
    Node() {
        entry = T();
        next = nullptr;
    }
    Node(const T& val) {
        entry = val;
        next = nullptr;
    }
};

enum errorCode { failure, success };

template <class info>
class User {
public:
    string surname;
    string name;
    list <string> phoneNumbers;

    User();
    User(const string& surname, const string& name);

    bool empty() const;
    int size() const;
    void addPhoneNumber(const string& phoneNumber);
};

template <class directory>
class TelephoneDirectory {
public:
    TelephoneDirectory(const string&);

    errorCode addUser(const string& surname, const string& name, const string& phoneNumber);
    errorCode deleteUser(const string& surname, const string& name);
    errorCode addPhoneNumber(const string& surname, const string& name, const string& phoneNumber);
    errorCode removePhoneNumber(const string& surname, const string& name, const string& phoneNumber);
    errorCode displayPhoneNumbers(const string& surname, const string& name);
    void displayAll();
    void loadFromFile();
    void saveToFile();

private:
    struct UserNode {
        User<directory> entry;
        UserNode* next;

        UserNode(const User<directory>& item) {
            entry = item;
            next = nullptr;
        }
    };

    UserNode* head;
    string filename;
};

// Template Class Member Function Definitions
template <class info>
User<info>::User() {}

template <class info>
User<info>::User(const string& userSurname, const string& userName) {
    surname = userSurname;
    name = userName;
}

template <class info>
bool User<info>::empty() const {
    return phoneNumbers.empty();
}

template <class info>
int User<info>::size() const {
    return phoneNumbers.size();
}

template <class info>
void User<info>::addPhoneNumber(const string& phoneNumber) {
    phoneNumbers.push_back(phoneNumber);
}

template<class directory>
TelephoneDirectory<directory>::TelephoneDirectory(const string& nameOfFile) {
    head = nullptr;
    filename = nameOfFile;
}

template<class directory>
errorCode TelephoneDirectory<directory>::addUser(const string& surname, const string& name, const string& phoneNumber) {
    string fullName = surname + " " + name;
    User<directory> newUser(surname, name);
    newUser.addPhoneNumber(phoneNumber); // Add the first phone number

    UserNode* temp = new UserNode(newUser);

    // Check if the list is empty
    if (head == nullptr) {
        head = temp;
        return success;
    }

    // Iterate until the next node is larger alphabetically
    UserNode* current = head;
    while (current->next != nullptr && current->next->entry.surname + " " + current->next->entry.name < fullName) {
        current = current->next;
    }

    // Check if the new user should be placed before the head
    if (fullName < current->entry.surname + " " + current->entry.name) {
        temp->next = head;
        head = temp;
    }
    else {
        // Insert after the current node
        temp->next = current->next;
        current->next = temp;
    }

    saveToFile();
    return success;
}


template<class directory>
errorCode TelephoneDirectory<directory>::deleteUser(const string& surname, const string& name) {
    UserNode* current = head;
    UserNode* previous = nullptr;

    if (current == nullptr) {
        cerr << "Telephone directory is empty." << endl;
        return failure;
    }

    // Iterate over the list to find the user to delete
    while (current != nullptr) {
        if (current->entry.surname == surname && current->entry.name == name) {
            // If the user to delete is the first node (head)
            if (current == head) {
                head = current->next;
            }
            else {
                previous->next = current->next;
            }
            delete current;
            saveToFile();
            return success;
        }
        else {
            previous = current;
            current = current->next;
        }
    }

    // If user does not exist
    return failure;
}


template<class directory>
errorCode TelephoneDirectory<directory>::addPhoneNumber(const string& surname, const string& name, const string& phoneNumber) {
    UserNode* current = head;

    // Iterate over the list to find user
    while (current != nullptr) {
        if (current->entry.surname == surname && current->entry.name == name) {
            current->entry.addPhoneNumber(phoneNumber);
            saveToFile(); // Save changes to file
            return success;
        }
        current = current->next;
    }
    return failure;
}

template<class directory>
errorCode TelephoneDirectory<directory>::removePhoneNumber(const string& surname, const string& name, const string& phoneNumber) {
    UserNode* currentUser = head;

    // Iterate over the list to check if it exists
    while (currentUser != nullptr) {
        // Check if the current user matches the specified surname and name
        if (currentUser->entry.surname == surname && currentUser->entry.name == name) {
            auto& phoneNumbers = currentUser->entry.phoneNumbers;
            auto it = find(phoneNumbers.begin(), phoneNumbers.end(), phoneNumber);
            if (it != phoneNumbers.end()) {
                phoneNumbers.erase(it);
                return success;
            }
            else {
                cerr << "Phone number not found for the user" << endl;
                return failure;
            }
        }
        currentUser = currentUser->next;
    }

    // If the user with the specified surname and name is not found
    cerr << "User not found" << endl;
    return failure;
}

template<class directory>
errorCode TelephoneDirectory<directory>::displayPhoneNumbers(const string& surname, const string& name) {
    UserNode* current = head;

    // Iterate over the list to check if it exists
    while (current != nullptr) {
        if (current->entry.surname == surname && current->entry.name == name) {
            auto& phoneNumbers = current->entry.phoneNumbers;
            if (phoneNumbers.empty()) {
                cout << "No phone numbers found for " << name << " " << surname << endl;
            }
            else {
                cout << "Phone numbers for " << name << " " << surname << ":" << endl;
                for (const auto& phoneNumber : phoneNumbers) {
                    cout << "- " << phoneNumber << endl;
                }
                cout << "\n";
            }
            return success;
        }
        else {
            current = current->next;
        }
    }
    // If user does not exist
    cerr << "User not found" << endl;
    return failure;
}

template<class directory>
void TelephoneDirectory<directory>::displayAll() {
    UserNode* currentUser = head;
    int i = 1;
    if (currentUser == nullptr) {
        cerr << "No user found!" << endl;
    }
    else {

        cout << "\n----Telephone Directory----" << endl;
        cout << "List sorted by Surname." << endl;
        while (currentUser != nullptr) {
            cout << i << ". " << currentUser->entry.surname << " " << currentUser->entry.name << endl;
            for (const auto& phoneNumber : currentUser->entry.phoneNumbers) {
                cout << "- " << phoneNumber << endl;
            }
            cout << endl;
            currentUser = currentUser->next;
            i++;
        }
    }
}



template<class directory>
void TelephoneDirectory<directory>::loadFromFile() {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        return;
    }

    string surname, name, phoneNumber;

    while (inFile >> surname >> name) {
        User<directory> newUser(surname, name);

        // Read all phone numbers for this user
        while (inFile.peek() != '\n' && inFile >> phoneNumber) {
            newUser.addPhoneNumber(phoneNumber);
        }

        addUser(surname, name, newUser.phoneNumbers.front());

        for (auto it = ++newUser.phoneNumbers.begin(); it != newUser.phoneNumbers.end(); ++it) {
            addPhoneNumber(surname, name, *it);
        }
    }

    inFile.close();
}


template<class directory>
void TelephoneDirectory<directory>::saveToFile() {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    UserNode* current = head;
    while (current != nullptr) {
        outFile << current->entry.surname << " " << current->entry.name;
        for (const auto& phone : current->entry.phoneNumbers) {
            outFile << " " << phone;
        }
        outFile << endl;
        current = current->next;
    }

    outFile.close();
}

#endif // TELEPHONE_H
