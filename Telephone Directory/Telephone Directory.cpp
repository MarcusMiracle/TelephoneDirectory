/**
* File Name: Telephone Directory.cpp
* Name: Miracle Marcus
* Program Title: Telephone Directory
* Program Goal: Create a telephone directory using linked lists
* Date: 12th May, 2024
*/

#include <iostream>
#include <string>
#include "Telephone.h"

using namespace std;

int main() {
    string filename = "teldir.txt";  // File to save and load data

    TelephoneDirectory<string> users(filename);  // Create a directory object with the given filename
    users.loadFromFile();

    while (true) {
        // Display the menu options
        cout << "---Telephone Directory Menu---" << endl;
        cout << "\n1. Add a new subscriber" << endl;
        cout << "2. Remove a phone number from a subscriber" << endl;
        cout << "3. Add a phone number to a subscriber" << endl;
        cout << "4. Display a subscriber's phone numbers" << endl;
        cout << "5. Delete a subscriber" << endl;
        cout << "6. Display all subscribers" << endl;
        cout << "7. Exit" << endl;

        int choice, number;
        string surname, name;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {  // Add a new subscriber
            
            cout << "Enter surname: ";
            cin >> surname;
            cout << "Enter name: ";
            cin >> name;
            do {
                cout << "Enter phone number: ";
                cin >> number;

                if (number <= 0) {
                    cerr << "Invalid phone number!" << endl;
                }

            } while (number <= 0);

            string phoneNumber = to_string(number);
            users.addUser(surname, name, phoneNumber);  // Add the new subscriber
            cout << "Subscriber added successfully." << endl;
        }
        else if (choice == 2) {  // Remove a phone number from a subscriber
            
            cout << "Enter surname: ";
            cin >> surname;
            cout << "Enter name: ";
            cin >> name;
            do {
                cout << "Enter phone number to remove: ";
                cin >> number;

                if (number <= 0) {
                    cerr << "Invalid phone number!" << endl;
                }

            } while (number <= 0);

            string phoneNumber = to_string(number);

            if (users.removePhoneNumber(surname, name, phoneNumber)) {
                cout << "Phone number removed successfully." << endl;
            }
        }
        else if (choice == 3) {  // Add a phone number to a subscriber
            
            int number;
            cout << "Enter surname: ";
            cin >> surname;
            cout << "Enter name: ";
            cin >> name;
            do {
                cout << "Enter phone number to add: ";
                cin >> number;

                if (number <= 0) {
                    cerr << "Invalid phone number!" << endl;
                }

            } while (number <= 0);

            string phoneNumber = to_string(number);

            if (users.addPhoneNumber(surname, name, phoneNumber)) {
                cout << "Phone number added successfully." << endl;
            }
            else {
                cout << "Subscriber not found." << endl;
            }
        }
        else if (choice == 4) {  // Display a subscriber's phone numbers
            string surname, name;
            cout << "Enter surname: ";
            cin >> surname;
            cout << "Enter name: ";
            cin >> name;

            if (!users.displayPhoneNumbers(surname, name)) {
                cout << "Subscriber not found." << endl;
            }
        }
        else if (choice == 5) {  // Delete a subscriber
            string surname, name;
            cout << "Enter surname: ";
            cin >> surname;
            cout << "Enter name: ";
            cin >> name;

            if (users.deleteUser(surname, name)) {
                cout << "Subscriber deleted successfully." << endl;
            }
            else {
                cout << "Subscriber not found." << endl;
            }
        }
        else if (choice == 6) {  // Display all subscribers
            users.displayAll();  // Display the entire directory
        }
        else if (choice == 7) {  // Exit the program
            cout << "Exiting program..." << endl;
            users.saveToFile();
            break;  // Exit the loop to end the program
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0; 
}