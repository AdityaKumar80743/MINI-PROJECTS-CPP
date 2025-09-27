#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
#include <utility> // for pair
#include <functional> // for hash

using namespace std;

string fileName = "login_register_system.txt";

// Hash a password
string hashPassword(const string& password) {
    hash<string> hasher;
    return to_string(hasher(password));
}

// append info to file
void addInfo(string name, string pass) {
    ofstream file(fileName, ios::app);
    if (!file) {
        cerr << "Error: Could not open file for writing." << endl;
        return;
    }
    file << name << " " << hashPassword(pass) << endl;
}

// checks if name exists or not
pair<string,string> nameExist(string name) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error: Could not open file for reading." << endl;
        return make_pair("false", "false");
    }

    string info;
    while (getline(file, info)) { // read entire line
        istringstream ss(info);
        string firstInfo, secondInfo; 
        ss >> firstInfo >> secondInfo; //get name and password

        if (firstInfo == name) {
            file.close();
            return make_pair(firstInfo, secondInfo);
        }
    }
    file.close();
    return make_pair("false", "false");
}

// registration menu
void registerr() {
    string name, pass, cpass;
    cout << "Enter Name: ";
    cin >> name;

    // if name not taken 
    if (nameExist(name).first == "false") {
        cout << "Enter Password: ";
        cin >> pass;

        cout << "Confirm Password: ";
        cin >> cpass;

        if (pass == cpass) {
            addInfo(name, pass);
            cout << "Registration successful!" << endl;
        } else {
            cout << "Passwords do not match." << endl;
        }
    } else {
        cout << "Name not available." << endl;
    }
}

// login menu
void login() {
    string name, pass;
    cout << "Enter name: ";
    cin >> name;

    pair<string, string> info = nameExist(name);
    // name exists
    if (info.first != "false") {
        cout << "Enter password: ";
        cin >> pass;

        if (hashPassword(pass) == info.second) {
            cout << "---- Welcome " << name << " ----" << endl;
        } else {
            cout << "Incorrect password." << endl;
        }
    } else {
        cout << "Name does not exist." << endl;
    }
}

int main() {
    while (true) {
        cout << "--------- LOGIN & REGISTRATION SYSTEM ----------" << endl;
        cout << "1. Login \n2. Register \n3. Exit" << endl;

        int action;
        cout << "Enter Action: ";
        cin >> action;

        if (action == 1) login();
        else if (action == 2) registerr();
        else if (action == 3) break;
        else cout << "Invalid action." << endl;
    }
    return 0;
}
