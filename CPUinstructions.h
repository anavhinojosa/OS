#ifndef CPUINSTRUCTIONS_H
#define CPUINSTRUCTIONS_H
#include <iostream>
#include <queue>
#include <vector>
#include <iostream>

class CPU
{
public:
    Process currentProcess;
    int schedulePolicy; // 0-FCFS, 1-SJF, 2- Round Robi
    int timeQuantum;

    void executeProcess()
    {

        switch (schedulePolicy)
        {

        case 0:
            break; // FCFS code for later ANA

        case 1:
            break;

        case 2:
        {
            SJF(readyQueue, waitingQueue);
            break;
            // me fernando will work on this case, the RoundRobin policy
        }
        }
    };

    // ANA make function for FCFS

    void SJF(std::queue<Process> &readyQueue, std::queue<Process> &waitingQueue) // send priority queue with dequeue or wont work
    {
      //  clearConsole();

        bool sendOuterMessage = true;
        int totalCycles = 0;
        std::vector<Process> terminatedProcesses;
        this->timeQuantum = 5;

        currentProcess = readyQueue.front();
        readyQueue.pop();
        cout << "\nContext Switch to Process: " << currentProcess.processId << endl;
        sendOuterMessage = true;
        while ((!readyQueue.empty()) && (currentProcess.numCycles != 0))
        {
            delay(2);
            sendOuterMessage = true;
            for (int i = 0; i < timeQuantum; i++)
            {
                if (currentProcess.numCycles > 0)
                {
                    delay(1);

                    totalCycles++;
                    cout << "Process " << currentProcess.processId << ", cycles left: " << currentProcess.numCycles << endl;
                    currentProcess.numCycles--;
                }
                else
                {
                    delay(1);

                    cout << "Process " << currentProcess.processId << " terminated." << endl;
                    terminatedProcesses.push_back(currentProcess);
                    currentProcess = readyQueue.front();
                    readyQueue.pop();
                    cout << "\nContext Switch to Process: " << currentProcess.processId << endl;
                    sendOuterMessage = false;
                    break;
                }
            }

            delay(1);
            if (sendOuterMessage)
            {
                readyQueue.push(currentProcess);
                currentProcess = readyQueue.front();
                readyQueue.pop();

                cout << "\n\nContext Switch to Process: " << currentProcess.processId << endl;
            }
        }

        cout << "\tExecution Complete, Total Cycles: " << totalCycles << endl;
        for (int i = 0; i < numberProcesses; i++)
        {
            cout << terminatedProcesses[i].processId << endl;
        }
    }
};

#endif
