#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool signIn() {
    string username, password, storedUsername, storedPassword;

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream infile("userdata.txt");
    if (infile.is_open()) {
        bool found = false;
        while (infile >> storedUsername >> storedPassword) {
            if (username == storedUsername && password == storedPassword) {
                cout << "Sign-in successful!" << endl;
                found = true;
                break;
            }
        }
        infile.close();
        if (!found) {
            cout << "User not found or incorrect password!" << endl;
            return false;
        }
        return true;
    } else {
        cout << "No user data found. Please sign up first." << endl;
        return false;
    }
}

// sign-up
void signUp() {
    string username, password;

    cout << "Enter a new Username: ";
    cin >> username;
    cout << "Enter a new Password: ";
    cin >> password;

    ofstream outfile("userdata.txt", ios::app); //apend to the file
    if (outfile.is_open()) {
        outfile << username << " " << password << endl;
        outfile.close();
        cout << "Sign-up successful!" << endl;
    } else {
        cout << "Unable to write to file. Please check permissions." << endl;
    }
}

// authentication menu
bool authenticate() {
    int choice;

    cout << "Welcome to OS" << endl;
    cout << "1. Sign in\n2. Sign up\n3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            return signIn();
        case 2:
            signUp();
        return authenticate();
        case 3:
            cout << "Exit" << endl;
        return false;
        default:
            cout << "Invalid choice, please try again." << endl;
        return authenticate();
    }
}
