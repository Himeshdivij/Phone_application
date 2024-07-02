#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Contact {
public:
    string name;
    string phoneNumber;
};

class Phone {
private:
    vector<Contact> contacts;

public:
    void loadContactsFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Unable to open file " << filename << ". Starting with empty contacts list." << endl;
            return;
        }

        contacts.clear(); 

        Contact contact;
        while (inFile >> contact.name >> contact.phoneNumber) {
            contacts.push_back(contact);
        }

        inFile.close();
        cout << "Contacts loaded successfully!" << endl;
    }

    void saveContactsToFile(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Unable to create file " << filename << ". Contacts data cannot be saved." << endl;
            return;
        }

        for (const auto& contact : contacts) {
            outFile << contact.name << " " << contact.phoneNumber << endl;
        }

        outFile.close();
        cout << "Contacts saved successfully!" << endl;
    }

    void addContact(const string& name, const string& phoneNumber) {
        Contact contact;
        contact.name = name;
        contact.phoneNumber = phoneNumber;
        contacts.push_back(contact);
        cout << "Contact added successfully!" << endl;
    }

    void listContacts() {
        cout << "\nContacts List:" << endl;
        for (const auto& contact : contacts) {
            cout << contact.name << " : " << contact.phoneNumber << endl;
        }
    }

    void dialNumber(const string& phoneNumber) {
        cout << "Dialing " << phoneNumber << "..." << endl;
    }

    void sendMessage(const string& phoneNumber, const string& message) {
        cout << "Sending message to " << phoneNumber << ": " << message << endl;
    }

    void deleteContact(const string& name) {
        for (auto it = contacts.begin(); it != contacts.end(); ++it) {
            if (it->name == name) {
                contacts.erase(it);
                cout << "Contact deleted successfully!" << endl;
                return;
            }
        }
        cout << "Contact not found!" << endl;
    }
};

int main() {
    Phone myPhone;
    int choice;
    string name, phoneNumber, message;

    myPhone.loadContactsFromFile("contacts.txt");

    do {
        cout << "\nPhone Application Menu:\n";
        cout << "1. Add Contact\n";
        cout << "2. List Contacts\n";
        cout << "3. Dial Number\n";
        cout << "4. Send Message\n";
        cout << "5. Delete\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter contact name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter phone number: ";
                getline(cin, phoneNumber);
                myPhone.addContact(name, phoneNumber);
                break;

            case 2:
                myPhone.listContacts();
                break;

            case 3:
                cout << "Enter phone number to dial: ";
                cin >> phoneNumber;
                myPhone.dialNumber(phoneNumber);
                break;

            case 4:
                cout << "Enter phone number to send message: ";
                cin >> phoneNumber;
                cout << "Enter message: ";
                cin.ignore();
                getline(cin, message);
                myPhone.sendMessage(phoneNumber, message);
                break;

            case 5:
                cout << "Enter contact name to delete: ";
                cin.ignore();
                getline(cin, name);
                myPhone.deleteContact(name);
                break;

            case 6:
                cout << "Exiting Phone Application. Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;

        }
    } while (choice != 6);

    myPhone.saveContactsToFile("contacts.txt");

    return 0;
}
