#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <queue>
#include <algorithm>

class Process
{
public:
    int processId;
    int state; // 0-New, 2-waiting, 3-ready, 4-running, 5-terminated
    int numCycles;
    int waitingTime;

    Process()
    {
        processId = -1;
        state = 0; //new
        waitingTime = 0;
    }
};

const int numberProcesses = 10;
int arraySorted[numberProcesses];
Process processArray[numberProcesses];

int n = sizeof(arraySorted) / sizeof(arraySorted[0]);

std::queue<Process> readyQueue;
std::queue<Process> waitingQueue;

Process createProcess(int id)
{
    Process newProcess;
    newProcess.processId = 1000 + (rand() % 9000);
    newProcess.state = 0;
    newProcess.numCycles = 5 + (rand() % 10);

    return newProcess;
}

void fillUpArray()
{
    for (int i = 0; i < numberProcesses; i++)
    {
        Process tempProcess = createProcess(i);
        arraySorted[i] = tempProcess.numCycles;
        processArray[i] = tempProcess;
    }
    std::sort(arraySorted, arraySorted + n);

    for (int i = 0; i < numberProcesses; i++)
    {
        cout << arraySorted[i] << endl;
    }

    for (int i = 0; i < numberProcesses; i++)
    {

        for (int j = 0; j < numberProcesses; j++)
        {
            if (arraySorted[i] == processArray[j].numCycles)
            {
                waitingQueue.push(processArray[j]);
            }
        }
    }
}

void displayProcesses()
{
 //   cout << "PID\tCycles" << endl;
    for (int i = 0; i < numberProcesses; i++)
    {
        Process tempProcess = waitingQueue.front();
  //      cout << tempProcess.processId << "\t" << tempProcess.numCycles << endl;
        //cout << "PID" << tempProcess.processId << ", cycles:: " << tempProcess.numCycles << endl;
        readyQueue.push(tempProcess);
        waitingQueue.pop();
    }
}

void initializeQueues()
{
    while (!readyQueue.empty()) {
        readyQueue.pop(); //clear the readyQueue
    }
    fillUpArray();
    displayProcesses();
    // at this point we should have ready queue with the processes filled up.
}

void initializePriorityQueue()
{
}

#endif