#include <bits/stdc++.h>

using namespace std;
int LAST_ID = 1;

// helper functions
bool icontains(const string &str1, const string &str2) {
    auto it = search(str1.begin(), str1.end(), str2.begin(), str2.end(),
                     [](char ch1, char ch2) { return tolower(ch1) == tolower(ch2); });
    return (it != str1.end());
}

bool stringCompare(string str1, string str2) {
    if (str1.length() != str2.length())
        return false;
    for (int i = 0; i < str1.length(); i++) {
        if (tolower(str1[i]) != tolower(str2[i]))
            return false;
    }
    return true;
}

//TRASH
string string_strip(std::string s) {
    if (s.empty()) {
        return s;
    }
    int first = s.find_first_not_of(' ');
    int last = s.find_last_not_of(' ');
    return s.substr(first, (last - first + 1));
}

vector<string> splitString(string str, string delimiter) {
    vector<string> result;
    if (stringCompare(str, delimiter)) {
        result.push_back("");
        result.push_back("");
        return result;
    }
    string first_part = str.substr(0, str.find(delimiter));
    string last_part = str.substr(str.find(delimiter) + delimiter.length(), str.size());
    result.push_back(first_part);
    result.push_back(last_part);

    return result;
}


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
            cout << "\033[1;31mNo contact found!\033[0m" << endl;
            return;
        }
        for (int i = 0; i < contacts.size(); i++) {
            cout << "Contact " << i + 1 << endl;
            contacts[i].print();
            cout << endl;
        }
    }

    void displayAsDatabase(bool all = true, vector<int> ids = vector<int>(), string field = "",
                           string value = "", string row_name = "", string row_value = "") {
        if (contacts.empty()) {
            cout << "\033[1;31mNo contact found!\033[0m" << endl;
            return;
        }
        if (row_name == "id") {
            string id = "ID" + row_value;
            cout << left << setw(5) << id << "|";
        } else {
            cout << left << setw(5) << "ID" << "|";
        }
        if (row_name == "name") {
            string name = "Name" + row_value;
            cout << left << setw(22) << name << "|";
        } else {
            cout << left << setw(20) << "Name" << "|";
        }
        cout << left << setw(30) << "Address" << "|";
        cout << left << setw(30) << "Email" << "|";
        cout << left << setw(15) << "Phone" << endl;

        cout << setfill('-') << setw(5) << "" << "";
        cout << setfill('-') << setw(20) << "|" << "-";
        cout << setfill('-') << setw(30) << "|" << "-";
        cout << setfill('-') << setw(30) << "|" << "-";
        cout << setfill('-') << setw(15) << "|" << endl;

        cout << setfill(' ');
        if (all) {
            for (int i = 0; i < contacts.size(); i++) {
                cout << left << setw(5) << contacts[i].getId() << "|";
                cout << left << setw(20) << contacts[i].getName() << "|";
                cout << left << setw(30) << contacts[i].getAddress() << "|";
                cout << left << setw(30) << contacts[i].getEmail() << "|";
                cout << left << setw(15) << contacts[i].getPhone() << endl;
            }
        } else {
            for (int i = 0; i < ids.size(); i++) {
                for (int j = 0; j < contacts.size(); j++) {
                    if (contacts[j].getId() == ids[i]) {
                        cout << left << setw(5) << contacts[j].getId() << "|";
                        if (field == "name") {
                            vector<string> slice = splitString(contacts[j].getName(), value);
                            string res = slice[0] + "\033[1;33m" + value + "\033[0m" + slice[1];
                            cout << left << setw(20) << res << "|";
                        } else {
                            cout << left << setw(20) << contacts[j].getName() << "|";
                        }
                        cout << left << setw(30) << contacts[j].getAddress() << "|";
                        cout << left << setw(30) << contacts[j].getEmail() << "|";
                        cout << left << setw(15) << contacts[j].getPhone() << endl;
                    }
                }
            }
        }
    }

    void deleteContact(int id) {
        for (int i = 0; i < contacts.size(); i++) {
            if (contacts[i].getId() == id) {
                contacts.erase(contacts.begin() + i);
                cout << "Contact deleted!" << endl;
                return;
            }
        }

        cout << "Contact not found!" << endl;
    }

    // updates database.dat file with current contacts
    void updateDatabase() {
        ofstream wf("database.dat", ios::binary);
        for (int i = 0; i < contacts.size(); i++) {
            wf.write(to_string(contacts[i].getId()).c_str(), to_string(contacts[i].getId()).size());
            wf.write("|", 1);
            wf.write(contacts[i].getName().c_str(), contacts[i].getName().size());
            wf.write("|", 1);
            wf.write(contacts[i].getAddress().c_str(), contacts[i].getAddress().size());
            wf.write("|", 1);
            wf.write(contacts[i].getEmail().c_str(), contacts[i].getEmail().size());
            wf.write("|", 1);
            wf.write(contacts[i].getPhone().c_str(), contacts[i].getPhone().size());
            wf.write("\n", 1);
        }
        wf.close();
    }

    // this function searches for a contact by name and displays it
    void searchByName(string name) {
        vector<int> ids;
        bool found = false;
        for (Contact contact: contacts) {
            if (icontains(contact.getName(), name)) {
                ids.push_back(contact.getId());
                found = true;
            }
        }
        if (!found) {
            cout << "\033[1;31mNo contact found!\033[0m" << endl;
            return;
        } else {

//            displayAsDatabase(false, ids, "name", name);
            displayAsDatabase(false, ids);
        }
    }

    void searchByAddress(string address) {
        vector<int> ids;
        bool found = false;
        for (Contact contact: contacts) {
            if (icontains(contact.getAddress(), address)) {
                ids.push_back(contact.getId());
                found = true;
            }
        }
        if (!found) {
            cout << "\033[1;31mNo contact found!\033[0m" << endl;
            return;
        } else {
            displayAsDatabase(false, ids);
        }
    }

    void searchByEmail(string email) {
        vector<int> ids;
        bool found = false;
        for (Contact contact: contacts) {
            if (icontains(contact.getEmail(), email)) {
                ids.push_back(contact.getId());
                found = true;
            }
        }
        if (!found) {
            cout << "\033[1;31mNo contact found!\033[0m" << endl;
            return;
        } else {
            displayAsDatabase(false, ids);
        }
    }

    void searchByPhone(string phone) {
        vector<int> ids;
        bool found = false;
        for (Contact contact: contacts) {
            if (contact.getPhone() == phone) {
                ids.push_back(contact.getId());
                found = true;
            }
        }
        if (!found) {
            cout << "\033[1;31mNo contact found!\033[0m" << endl;
            return;
        } else {
            displayAsDatabase(false, ids);
        }

    }

    void searchById(int id) {
        vector<int> ids;
        bool found = false;
        for (Contact contact: contacts) {
            if (contact.getId() == id) {
                ids.push_back(contact.getId());
                found = true;
            }
        }
        if (!found) {
            cout << "\033[1;31mNo contact found!\033[0m" << endl;
            return;
        } else {
            displayAsDatabase(false, ids);
        }
    }

    void sortByName(bool asc) {
        vector<Contact> temp_contacts;
        temp_contacts = contacts;

        if (asc) {
            sort(temp_contacts.begin(), temp_contacts.end(), [](Contact a, Contact b) {
                return a.getName() < b.getName();
            });
        } else {
            sort(temp_contacts.begin(), temp_contacts.end(), [](Contact a, Contact b) {
                return a.getName() > b.getName();
            });
        }
        vector<int> ids;
        for (Contact contact: temp_contacts) {
            ids.push_back(contact.getId());
        }
        string char_asc_or_desc = asc ? "⌄  " : "⌃  ";
        displayAsDatabase(false, ids, "", "", "name", char_asc_or_desc);

    }

    void sortById(bool asc) {
        vector<Contact> temp_contacts;
        temp_contacts = contacts;

        if (asc) {
            sort(temp_contacts.begin(), temp_contacts.end(), [](Contact a, Contact b) {
                return a.getId() < b.getId();
            });
        } else {
            sort(temp_contacts.begin(), temp_contacts.end(), [](Contact a, Contact b) {
                return a.getId() > b.getId();
            });
        }
        vector<int> ids;
        for (Contact contact: temp_contacts) {
            ids.push_back(contact.getId());
        }
        string char_asc_or_desc = asc ? "⌄  " : "⌃  ";
        displayAsDatabase(false, ids, "", "", "id", char_asc_or_desc);

    }

    vector<Contact> getContacts() {
        return contacts;
    }

};


int main() {

    cout << "************************************************************" << endl;
    cout << "                CONTACT MANAGEMENT SYSTEM                   " << endl;
    cout << "************************************************************" << endl;
    cout << endl;
    cout << "::::::::::::::::::::::::MENU PROGRAM::::::::::::::::::::::::" << endl;
    cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    Phonebook phonebook;

    // load all data from database
    ifstream rf("database.dat", ios::binary);
    string line;
    while (getline(rf, line)) {
        stringstream ss(line);
//        cout << ss.str() << endl;
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
        cout << "+---------------------------------+" << endl;
        cout << "|           CONTACT MENU          |" << endl;
        cout << "+---------------------------------+" << endl;
        cout << "| 1. Add a contact                |" << endl;
        cout << "| 2. Display all contacts         |" << endl;
        cout << "| 3. Delete a contact             |" << endl;
        cout << "| 4. Search contact               |" << endl;
        cout << "| 5. Exit                         |" << endl;
        cout << "+---------------------------------+" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout << endl;
        if (choice == 1) {
            string name, address, email, phone;
            name:
            cout << "Enter name: ";
            cin.ignore();
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
            while (true) {
                cout << endl;
                cout << endl;
                cout << "\t1. Sort by name ascending" << endl;
                cout << "\t2. Sort by name descending" << endl;
                cout << "\t3. Sort by id ascending" << endl;
                cout << "\t4. Sort by id descending" << endl;
                cout << "\t5. Back to main menu" << endl;
                cout << endl;
                cout << "\tEnter your choice: ";
                int choice2;
                cin >> choice2;
                cout << endl;
                if (choice2 == 1) {
                    phonebook.sortByName(true);
                } else if (choice2 == 2) {
                    phonebook.sortByName(false);
                } else if (choice2 == 3) {
                    phonebook.sortById(true);
                } else if (choice2 == 4) {
                    phonebook.sortById(false);
                } else if (choice2 == 5) {
                    break;
                } else {
                    cout << "Invalid choice!" << endl;
                }


            }
        } else if (choice == 3) {
            cout << "Enter contact id: ";
            int id;
            cin >> id;
            phonebook.deleteContact(id);
            phonebook.updateDatabase();
        } else if (choice == 4) {
            cout << "\t1. Search by name" << endl;
            cout << "\t2. Search by address" << endl;
            cout << "\t3. Search by email" << endl;
            cout << "\t4. Search by phone" << endl;
            cout << "\t5. Search by id" << endl;
            cout << "\t6. Back to main menu" << endl;
            cout << endl;
            cout << "\tEnter your choice: ";
            int choice4;
            cin >> choice4;
            cout << endl;
            if (choice4 == 1) {
                string name;
                cout << "\tEnter name: ";
                cin.ignore();
                getline(cin, name);
                phonebook.searchByName(name);
            } else if (choice4 == 2) {
                string address;
                cout << "\tEnter address: ";
                cin.ignore();
                getline(cin, address);
                phonebook.searchByAddress(address);
            } else if (choice4 == 3) {
                string email;
                cout << "\tEnter email: ";
                cin.ignore();
                getline(cin, email);
                phonebook.searchByEmail(email);
            } else if (choice4 == 4) {
                string phone;
                cout << "\tEnter phone: ";
                cin.ignore();
                getline(cin, phone);
                phonebook.searchByPhone(phone);
            } else if (choice4 == 5) {
                int id;
                cout << "\tEnter id: ";
                cin >> id;
                phonebook.searchById(id);
            } else if (choice4 == 6) {
                continue;
            } else {
                cout << "\tInvalid choice!" << endl;
            }
        } else if (choice == 5) {
            cout << "Thank you for using our program!" << endl;
            break;
        } else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
