#include <iostream>
#include <fstream>  // For file handling
#include <string>
using namespace std;

int main() {
    int choice;
    string username, password, storedUsername, storedPassword;

    cout << "Welcome to OS" << endl;
    cout << "1. Sign in\n2. Sign up\n3. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            //sign in
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            //open file and read stored username and password
            {
                ifstream infile("userdata.txt");
                if (infile.is_open()) {
                    infile >> storedUsername >> storedPassword;
                    infile.close();

                    if (username == storedUsername && password == storedPassword) {
                        cout << "Sign-in successful!" << endl;
                    } else {
                        cout << "User not found or incorrect password!" << endl;
                    }
                } else {
                    cout << "No user data found. Please sign up first." << endl;
                }
            }
            break;

        case 2:
            //sign up
            cout << "Enter a new Username: ";
            cin >> username;
            cout << "Enter a new Password: ";
            cin >> password;

            //save the new username and password to a file
            {
                ofstream outfile("userdata.txt");
                outfile << username << " " << password;
                outfile.close();
                cout << "Sign-up successful!" << endl;
            }
            break;

        case 3:
            cout << "Exit" << endl;
            return 0;

        default:
            cout << "Invalid choice, please try again. Example 1, 2 or 3" << endl;
    }

    return 0;
}
