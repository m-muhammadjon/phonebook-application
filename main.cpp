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

bool isValidEmail(string email) {
    const regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    return regex_match(email, pattern);
}

bool isValidPhoneNumber(const string &phoneNumber) {
    const regex pattern(R"(^\+\d{12}$)");
    return regex_match(phoneNumber, pattern);
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

    void updateContact(int id) {
        for (int i = 0; i < contacts.size(); i++) {
            if (contacts[i].getId() == id) {
                cout << "Enter new name or press enter to skip: ";
                string name;
                cin.ignore();
                getline(cin, name);
                if (name != "") {
                    contacts[i].setName(name);
                }
                cout << "Enter new address or press enter to skip: ";
                string address;
                getline(cin, address);
                if (address != "") {
                    contacts[i].setAddress(address);
                }
                email_update_section:
                cout << "Enter new email or press enter to skip: ";
                string email;
                getline(cin, email);
                if (email != "") {
                    if (!isValidEmail(email)) {
                        cout << "\033[31mInvalid email!\033[0m" << endl;
                        goto email_update_section;
                    }
                    if (checkEmailExists(email)) {
                        cout << "\033[31mEmail already exists!\033[0m" << endl;
                        goto email_update_section;
                    }
                    contacts[i].setEmail(email);
                }
                phone_update_section:
                cout << "Enter new phone or press enter to skip: ";
                string phone;
                getline(cin, phone);
                if (phone != "") {
                    if (!isValidPhoneNumber(phone)) {
                        cout << "\033[31mInvalid phone!\033[0m" << endl;
                        goto phone_update_section;
                    }
                    if (checkPhoneExists(phone)) {
                        cout << "\033[31mPhone already exists!\033[0m" << endl;
                        goto phone_update_section;
                    }
                    contacts[i].setPhone(phone);
                }
                cout << "\033[32mContact updated!\033[0m" << endl;
                return;
            }
        }
        cout << "\033[31mContact not found!\033[0m" << endl;
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
            cout << "\033[1;33m";
            cout << ids.size() << " contacts found with name \"" << name << "\"" << endl;
            cout << "\033[0m";
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
            cout << "\033[1;33m";
            cout << ids.size() << " contacts found with address \"" << address << "\"" << endl;
            cout << "\033[0m";
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
            cout << "\033[1;33m";
            cout << ids.size() << " contacts found with email \"" << email << "\"" << endl;
            cout << "\033[0m";
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
            cout << "\033[1;33m";
            cout << ids.size() << " contacts found with phone \"" << phone << "\"" << endl;
            cout << "\033[0m";
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


    bool checkEmailExists(string email) {
        for (Contact contact: contacts) {
            if (contact.getEmail() == email) {
                return true;
            }
        }
        return false;
    }

    bool checkPhoneExists(string phone) {
        for (Contact contact: contacts) {
            if (contact.getPhone() == phone) {
                return true;
            }
        }
        return false;
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
        cout << "| 5. Update contact               |" << endl;
        cout << "| 6. Exit                         |" << endl;
        cout << "+---------------------------------+" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout << endl;
        if (choice == 1) {
            string name, address, email, phone;
            cin.ignore();
            name:
            cout << "Enter name: ";
            getline(cin, name);
            if (name.empty()) {
                cout << "\033[31mName cannot be empty!\033[0m" << endl;
                goto name;
            }
            address:
            cout << "Enter address: ";
            getline(cin, address);
            if (address.empty()) {
                cout << "\033[31mAddress cannot be empty!\033[0m" << endl;
                goto address;
            }
            email:
            cout << "Enter email: ";
            getline(cin, email);
            if (email.empty()) {
                cout << "\033[31mEmail cannot be empty!\033[0m" << endl;
                goto email;
            }
            bool email_exists = false;
            for (Contact contact: phonebook.getContacts()) {
                if (contact.getEmail() == email) {
                    email_exists = true;
                    break;
                }
            }
            if (email_exists) {
                cout << "\033[31mEmail already exists!\033[0m" << endl;
                goto email;
            }
            if (isValidEmail(email) == false) {
                cout << "\033[31mInvalid email!\033[0m" << endl;
                goto email;
            }

            phone:
            cout << "Enter phone: ";
            getline(cin, phone);
            if (phone.empty()) {
                cout << "\033[31mPhone cannot be empty!\033[0m" << endl;
                goto phone;
            }
            bool phone_exists = false;
            for (Contact contact: phonebook.getContacts()) {
                if (contact.getPhone() == phone) {
                    phone_exists = true;
                    break;
                }
            }
            if (phone_exists) {
                cout << "\033[31mPhone number already exists!\033[0m" << endl;
                goto phone;
            }
            if (isValidPhoneNumber(phone) == false) {
                cout << "\033[31mInvalid phone number!\033[0m" << endl;
                goto phone;
            }

            Contact contact(name, address, email, phone, 0);
            phonebook.addContact(contact);
            addToDatabase(contact);
            cout << "\033[32mContact added successfully!\033[0m" << endl;
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
            delete_contact:
            cout << "Enter contact id to delete or type 0 to cancel, type -1 to move search section: ";
            int id;
            cin >> id;
            if (id == 0) {
                continue;
            } else if (id == -1) {
                goto search_section;
            }
            phonebook.deleteContact(id);
            phonebook.updateDatabase();
        } else if (choice == 4) {
            search_section:
            while (true) {
                cout << "\t1. Search by name" << endl;
                cout << "\t2. Search by address" << endl;
                cout << "\t3. Search by email" << endl;
                cout << "\t4. Search by phone" << endl;
                cout << "\t5. Search by id" << endl;
                cout << "\t6. Delete contact" << endl;
                cout << "\t7. Update contact" << endl;
                cout << "\t8. Back to main menu" << endl;
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
                    goto delete_contact;
                } else if (choice4 == 7) {
                    goto update_contact;
                } else if (choice4 == 8) {
                    break;
                } else {
                    cout << "\tInvalid choice!" << endl;
                }
            }
        } else if (choice == 5) {
            update_contact:
            cout << "Enter contact id to update or type 0 to cancel, type -1 to move search section: ";
            int id;
            cin >> id;
            if (id == 0) {
                continue;
            } else if (id == -1) {
                goto search_section;
            }
            phonebook.updateContact(id);
            phonebook.updateDatabase();

        } else if (choice == 6) {
            cout << "\033[34mThank you for using our program!\033[0m" << endl;
            break;
        } else {
            cout << "\033[31mInvalid choice!\033[0m" << endl;
        }
    }

    return 0;
}
