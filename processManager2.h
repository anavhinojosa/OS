#ifndef PROCESSMANAGER2_H
#define PROCESSMANAGER2_H
#include <algorithm>
#include <list>

// class Process
// {
// public:
//     int processId;
//     int state; // 0-New, 2-waiting, 3-ready, 4-running, 5-terminated
//     int numCycles;
//     int waitingTime;

//     Process()
//     {
//         processId = -1;
//         state = 0; // new
//         waitingTime = 0;
//     }
// };

const int numberProcesses2 = 20;

int cyclesArray[numberProcesses2];

std::list<Process> listProcesses;

Process createProcess2(int id)
{
    Process newProcess;
    newProcess.processId = id;
    newProcess.state = 0;
    newProcess.numCycles = 5 + (rand() % 10);
    return newProcess;
};

void fillUpLinkedList()
{
    for (int i = 0; i < numberProcesses2; i++)
    {
        Process newProcess = createProcess2(i);
        cyclesArray[i] = newProcess.numCycles;
        listProcesses.push_front(newProcess);
    }

    int size = sizeof(cyclesArray) / sizeof(cyclesArray[0]);
    std::sort(cyclesArray, cyclesArray + size);

    for (int i = 0; i < numberProcesses2; i++)
    {
   //     cout << "Cycles: " << cyclesArray[i] << endl;
    }
}

#endif