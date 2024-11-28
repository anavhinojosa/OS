#include <iostream>
#include "ProcessManager.h"
#include "CPUInstructions.h"
#include "Translation.h"
#include "Booting.h"
#include "MMU.h"
#include "SystemMemory.h"
#include "SystemStorage.h"

using namespace std;

// Define global variables
list<Process> listProcesses;           // List of processes for scheduling
queue<Process> readyQueue;             // Ready queue for processes
queue<Process> waitingQueue;           // Waiting queue for processes
Process processArray[numberProcesses]; // Array of processes

int arraySorted[numberProcesses];       // Array of sorted cycles
int cyclesArray[numberProcesses] = {0}; // Array to store process cycles
int tlbHits = 0;
int tlbMisses = 0;
int pageFaults = 0;
int instructionsExecuted = 0;

int main()
{
    srand(time(0)); // Seed random

    // Boot sequence
    bootSystem();

    // page table
    initializePageTable();

    // initialize Queues
    queue<Process> terminatedProcesses; // queue for terminated processes
    initializeProcesses(readyQueue);

    // display Ready Queue
    displayProcesses(readyQueue, "Ready Queue");

    // components
    CPU scheduler;

    // First Come, First Served Scheduling
    cout << "\n\nAbout to execute in First Come First served\n\n\n\n" << endl;
    delay(5);

    scheduler.schedulePolicy = 0;
    scheduler.executeProcess(readyQueue, terminatedProcesses);

    initializeProcesses(readyQueue);

    // Shortest Job First Scheduling
    cout << "[Debug] Starting SJF scheduling." << std::endl;
    scheduler.schedulePolicy = 1;

    cout << "\n\nAbout to execute in Shortest Job first\n\n\n\n" << endl;
    delay(5);
    scheduler.executeProcess(readyQueue, terminatedProcesses);
    cout << "[Debug] SJF scheduling completed." << std::endl;

    initializeProcesses(readyQueue);
    cout << "[Debug] Ready queue reinitialized for RR." << std::endl;

    // Round Robin Scheduling
    cout << "[Debug] Starting Round Robin scheduling." << std::endl;
    scheduler.schedulePolicy = 2;
    scheduler.timeQuantum = 4;

    cout << "\n\nAbout to execute Round Robin\n\n\n\n" << endl;
    delay(5);
    scheduler.executeProcess(readyQueue, terminatedProcesses);
    cout << "[Debug] Round Robin scheduling completed." << std::endl;

    // Print Final Summary
    scheduler.printSummary(terminatedProcesses);
    cout << "[Debug] Program execution completed successfully." << std::endl;

    return 0;
}
