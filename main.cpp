#include <iostream>
#include<iomanip>
#include "userInputFunctions.h"
#include <iostream>
#include "booting.h"
#include "auth_page.h"
#include "process.h"

using namespace std;



int main() {
    int schedulingType;
    cout << "Enter 1 for FIFO, 2 for SJF: ";
    cin >> schedulingType;

    startProcess();  // Start processes based on scheduling type
    runScheduler(schedulingType);  // Run the selected scheduling algorithm

    return 0;
}



    /*
     * int choice;

    do {
        cout << "\nOS Simulator" << endl;
        cout << "1. Process Management" << endl;
        cout << "2. Next (authentication)" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int processChoice;
                do {
                    cout << "\nProcess Menu" << endl;
                    cout << "1. Start Process" << endl;
                    cout << "2. List Processes" << endl;
                    cout << "3. Terminate Process" << endl;
                    cout << "4. Back to Main Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> processChoice;

                    switch (processChoice) {
                        case 1:
                            startProcess();
                            break;
                        case 2:
                            listProcesses();
                            break;
                        case 3: {
                            int pid;
                            cout << "Enter PID to terminate: ";
                            cin >> pid;
                            terminateProcess(pid);
                            break;
                        }
                        case 4:
                            cout << "Returning to Main Menu" << endl;
                            break;
                        default:
                            cout << "Invalid choice, please try again." << endl;
                    }
                } while (processChoice != 4);
                break;
            }
            case 2: {
                if (authenticate()) {
                    cout << "Authentication successful!" << endl;
                    cout << "Hello! Welcome";
                    break;
                } else {
                    cout << "Failed. Try again." << endl;
                }
                break;
            }
            case 3:
                cout << "Exiting OS Simulator" << endl;
                break;

            default:
                cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 3);
     */
