#include <bits/stdc++.h>

using namespace std;
int LAST_ID = 1;

class Contact {
private:
    string name, address, email, phone;
    int id;
public:
    Contact(string name, string address, string email, string phone, int id) {
        if (id == 0) {
            this->id = LAST_ID++;
        } else {
            this->id = id;
        }
        this->name = name;
        this->address = address;
        this->email = email;
        this->phone = phone;

    }

    string getName() {
        return name;
    }

    string getAddress() {
        return address;
    }

    string getEmail() {
        return email;
    }

    string getPhone() {
        return phone;
    }

    int getId() {
        return id;
    }

    void setName(string name) {
        this->name = name;
    }

    void setAddress(string address) {
        this->address = address;
    }

    void setEmail(string email) {
        this->email = email;
    }

    void setPhone(string phone) {
        this->phone = phone;
    }

    void setId(int id) {
        this->id = id;
    }

    void print() {
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
    }
};


void addToDatabase(Contact contact) {
    ofstream wf("database.dat", ios::binary | ios::app);
    wf.write(to_string(contact.getId()).c_str(), to_string(contact.getId()).size());
    wf.write("|", 1);
    wf.write(contact.getName().c_str(), contact.getName().size());
    wf.write("|", 1);
    wf.write(contact.getAddress().c_str(), contact.getAddress().size());
    wf.write("|", 1);
    wf.write(contact.getEmail().c_str(), contact.getEmail().size());
    wf.write("|", 1);
    wf.write(contact.getPhone().c_str(), contact.getPhone().size());
    wf.write("\n", 1);
    wf.close();
}


class Phonebook {
private:
    vector<Contact> contacts;
public:
    void addContact(Contact contact) {
        contacts.push_back(contact);

    }

    void displayAllContacts() {
        if (contacts.empty()) {
            cout << "No contact found!" << endl;
            return;
        }
        for (int i = 0; i < contacts.size(); i++) {
            cout << "Contact " << i + 1 << endl;
            contacts[i].print();
            cout << endl;
        }
    }

    void displayAsDatabase() {
        if (contacts.empty()) {
            cout << "No contact found!" << endl;
            return;
        }

        cout << left << setw(5) << "ID" << "|";
        cout << left << setw(20) << "Name" << "|";
        cout << left << setw(30) << "Address" << "|";
        cout << left << setw(30) << "Email" << "|";
        cout << left << setw(15) << "Phone" << endl;

        cout << setfill('-') << setw(5) << "" << "";
        cout << setfill('-') << setw(20) << "|" << "-";
        cout << setfill('-') << setw(30) << "|" << "-";
        cout << setfill('-') << setw(30) << "|" << "-";
        cout << setfill('-') << setw(15) << "|" << endl;

        cout << setfill(' ');

        for (int i = 0; i < contacts.size(); i++) {
            cout << left << setw(5) << contacts[i].getId() << "|";
            cout << left << setw(20) << contacts[i].getName() << "|";
            cout << left << setw(30) << contacts[i].getAddress() << "|";
            cout << left << setw(30) << contacts[i].getEmail() << "|";
            cout << left << setw(15) << contacts[i].getPhone() << endl;
        }
    }

    vector<Contact> getContacts() {
        return contacts;
    }

};


int main() {
    cout << "************************************************************" << endl;
    cout << "                  CONTACT MANAGEMENT SYSTEM                 " << endl;
    cout << "************************************************************" << endl;
    cout << endl;
    cout << "::::::::::::::::::::::::MENU PROGRAM::::::::::::::::::::::::" << endl;
    Phonebook phonebook;

    // load all data from database
    ifstream rf("database.dat", ios::binary);
    string line;
    while (getline(rf, line)) {
        stringstream ss(line);
        cout << ss.str() << endl;
        string id, name, address, email, phone;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, address, '|');
        getline(ss, email, '|');
        getline(ss, phone, '|');
        Contact contact(name, address, email, phone, stoi(id));
        phonebook.addContact(contact);
    }
    LAST_ID = phonebook.getContacts().back().getId() + 1;


    while (true) {
        cout << "1. Add a contact" << endl;
        cout << "2. Display all contacts" << endl;
        cout << "3. Delete a contact" << endl;
        cout << "4. Search contact" << endl;
        cout << "5. Exit" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout << endl;
        if (choice == 1) {
            string name, address, email, phone;
            name:
            cout << "Enter name: ";
            getline(cin, name);
            if (name.empty()) {
                cout << "Name cannot be empty!" << endl;
                goto name;
            }
            address:
            cout << "Enter address: ";
            getline(cin, address);
            if (address.empty()) {
                cout << "Address cannot be empty!" << endl;
                goto address;
            }
            email:
            cout << "Enter email: ";
            getline(cin, email);
            if (email.empty()) {
                cout << "Email cannot be empty!" << endl;
                goto email;
            }
            phone:
            cout << "Enter phone: ";
            getline(cin, phone);
            if (phone.empty()) {
                cout << "Phone cannot be empty!" << endl;
                goto phone;
            }
            Contact contact(name, address, email, phone, 0);
            phonebook.addContact(contact);
            addToDatabase(contact);
            cout << "Contact added successfully!" << endl;
        } else if (choice == 2) {
            phonebook.displayAsDatabase();
        } else if (choice == 5) {
            cout << "Thank you for using our program!" << endl;
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
