#include <iostream>
#include <iomanip>
#include "userInputFunctions.h"
#include "booting.h"
#include "auth_page.h"
#include "processManager.h"
//#include "consoleCommands.h"
#include "CPUinstructions.h"
#include "processManager2.h"
#include "translation.h"

using namespace std;

int main()
{
    srand(time(0));
    std::cout << std::unitbuf;
    //clearConsole();
    bootSystem();
    initializePageTable();
    printPageTable();
    initializeQueues();
    // initializeQueues() starts me a ready queue with 10 processes in incresing order cycles
    //  std::queue<Process> readyQueue;
    //  std::queue<Process> waitingQueue;

    CPU cpu;
    cpu.schedulePolicy = 0; // for Round Robin
    if (cpu.schedulePolicy == 0)
    {
        cout << "FIFO" << endl;
    }
    else if (cpu.schedulePolicy == 1)
    {
        cout << "SJF" << endl;
    }
    else if (cpu.schedulePolicy == 2)
    {
        cout << "Round Robin" << endl;
    }
    else
    {
        cout << "Unknown Policy" << endl;
    }

    cpu.executeProcess();

    ///// try the other policy after this

    delay(6);
    cout << "\n\n\nChanging Policy to Shortest Job First..." << endl;
    delay(6);
    cout << "\nCreating 20 Processes..." << endl;
    cpu.schedulePolicy = 1;

    fillUpLinkedList(); // will give me a doubly with 20 processes, and an array with sorted cycle order

    cpu.executeProcess();

    /*for (int policy = 0; policy <=2; policy++) {
        CPU cpu;
        cpu.schedulePolicy = policy;
        if (cpu.schedulePolicy == 0) {
            cout << "FIFO" << endl;
        } else if (cpu.schedulePolicy == 1) {
            cout << "SJF" << endl;
        } else if (cpu.schedulePolicy == 2) {
            cout << "Round Robin" << endl;
        } else {
            cout << "Unknown Policy" << endl;
        }
        cpu.executeProcess();
        cout << "\n\n\n\n\n";*/
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
