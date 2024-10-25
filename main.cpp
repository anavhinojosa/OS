#include <iostream>
#include <iomanip>
#include "userInputFunctions.h"
#include <iostream>
#include "booting.h"
#include "auth_page.h"
// #include "process.h"
#include "processManager.h"
#include "consoleCommands.h"
#include "CPUinstructions.h"
using namespace std;

<<<<<<< Updated upstream


int main() {
    int schedulingType;
    cout << "Enter 1 for FIFO, 2 for SJF: ";
    cin >> schedulingType;

    return 0;
}


=======
int main()
{
    std::cout << std::unitbuf;
    clearConsole();
    bootSystem();
    initializeQueues(); 
//initializeQueues() starts me a ready queue with 10 processes in incresing order cycles
            // std::queue<Process> readyQueue;
            // std::queue<Process> waitingQueue;
>>>>>>> Stashed changes


    CPU cpu;
    cpu.schedulePolicy = 2; // for Round Robin
    cpu.executeProcess();

<<<<<<< Updated upstream
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
=======
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

// Process* processesArrayPtr;

// bootSystem();
// startProcess();

// return 0;
>>>>>>> Stashed changes
