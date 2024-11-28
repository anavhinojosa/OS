#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <iostream>
#include <cstdlib>
#include <queue>
#include <list>
#include <algorithm>
#include "SystemMemory.h" // to declare the page table

class PageTable;

using namespace std;
class Process
{
public:
    int processId;
    int state;     // 0-New, 2-Waiting, 3-Ready, 4-Running, 5-Terminated
    int numCycles; // # of cycles left (decimal only, 1-10)
    int waitingTime;
    int cpuBurst;
    int ioBurst;
    int pagesNeeded;
    PageTable *PT = new PageTable(); // tiene de los dos, pero no se como declarar ubicacion

    Process()
    {
        processId = 0;
        state = 0; // new state
        waitingTime = 0;
        cpuBurst = 0;
        ioBurst = 0;
        numCycles = 0;
    }
};

const int numberProcesses = 10;

// extern declarations
extern list<Process> listProcesses;
extern queue<Process> readyQueue;
extern queue<Process> waitingQueue;
extern Process processArray[numberProcesses];
extern int arraySorted[numberProcesses];

void initializeProcesses(queue<Process> &readyQueue)
{
    listProcesses.clear();
    while (!readyQueue.empty())
    {
        readyQueue.pop();
    }

    int initializedCount = 0;

    for (int i = 0; i < numberProcesses; i++)
    {
        Process process;
        process.processId = 10000 + (rand() % 90000);
        process.numCycles = 1 + (rand() % 10);
        process.cpuBurst = 2 + (rand() % 5);
        process.ioBurst = 1 + (rand() % 5);
        process.pagesNeeded = 10 + (rand() % 20);
        process.state = 1;                // ready state
        readyQueue.push(process);         // add it to the ready queue
        listProcesses.push_back(process); // add it to the list

        cout << "[OK] Process Created: PID " << process.processId << endl;
        cout << "CPU Burst Time: " << process.cpuBurst << "ms" << endl;
        cout << "IO Burst Time: " << process.ioBurst << "ms" << endl;
        cout << "Total Cycles: " << process.numCycles << endl;
        initializedCount++;
    }

    cout << "\n"
         << initializedCount << " processes were initialized." << endl;
}

// display processes in a queue
void displayProcesses(queue<Process> &inputQueue, const string &queueName)
{
    cout << "[" << queueName << "]: ";
    queue<Process> tempQueue = inputQueue; // temporary queue to iterate without modifying
    while (!tempQueue.empty())
    {
        Process p = tempQueue.front();
        cout << "PID " << p.processId << " ";
        tempQueue.pop();
    }
    cout << endl;
}

Process createProcess()
{
    Process newProcess;
    newProcess.processId = 10000 + (rand() % 90000);
    newProcess.state = 0;
    newProcess.numCycles = 1 + (rand() % 10);
    newProcess.cpuBurst = 1 + (rand() % 5);
    newProcess.ioBurst = 1 + (rand() % 5);
    return newProcess;
}

// initialize and sort processes
void fillUpArray()
{
    for (int i = 0; i < numberProcesses; i++)
    {
        Process tempProcess = createProcess();
        processArray[i] = tempProcess;          // process to array
        arraySorted[i] = tempProcess.numCycles; // numCycles for sorting
    }

    // sort arraySorted for short
    sort(arraySorted, arraySorted + numberProcesses);

    // push processes to the waiting queue
    for (int i = 0; i < numberProcesses; i++)
    {
        for (int j = 0; j < numberProcesses; j++)
        {
            if (arraySorted[i] == processArray[j].numCycles)
            {
                waitingQueue.push(processArray[j]);
                break;
            }
        }
    }
}

// from the waiting queue to the ready queue
void initializeReadyQueue()
{
    while (!readyQueue.empty())
    {
        readyQueue.pop();
    }

    while (!waitingQueue.empty())
    {
        Process tempProcess = waitingQueue.front();
        waitingQueue.pop();
        tempProcess.state = 3; // Ready
        readyQueue.push(tempProcess);
    }
}

// queue
void initializeQueues()
{
    fillUpArray();          // Fill waiting queue with sorted processes
    initializeReadyQueue(); // from waiting to ready queue

    cout << "[Process Creation...]" << endl;
    queue<Process> tempQueue = readyQueue;
    while (!tempQueue.empty())
    {
        Process tempProcess = tempQueue.front();
        tempQueue.pop();
        cout << "[OK] Process Created: PID " << tempProcess.processId << endl;
        cout << "State: New → Ready" << endl;
        cout << "CPU Burst Time: " << tempProcess.cpuBurst << "ms" << endl;
        cout << "IO Burst Time: " << tempProcess.ioBurst << "ms" << endl;
        cout << "Total Cycles: " << tempProcess.numCycles << endl;
        cout << "Added to Ready Queue.\n"
             << endl;
    }
}

#endif
