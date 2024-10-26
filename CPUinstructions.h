#ifndef CPUINSTRUCTIONS_H
#define CPUINSTRUCTIONS_H
#include <iostream>
#include <queue>
#include <vector>
#include <iostream>

using namespace std;

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
            FIFO(readyQueue);
            break;

        case 1:
            //sjf code
            break;

        case 2:
        {
            SJF(readyQueue, waitingQueue);
            break;
            // me fernando will work on this case, the RoundRobin policy
        }
        }
    };

    //fifo
    void FIFO(queue<Process> &readyQueue) {
        int totalCycles = 0;//keep track of the total cycles executed
        vector<Process> terminatedProcesses;//stores the completed process
        //this is for the process taht are on the ready queue
        while (!readyQueue.empty()) {
            currentProcess = readyQueue.front();//get the next process (without removing it)
            readyQueue.pop();//remove it from the queue
            //to show the next content switch to the other process
            cout << "\nContext Switch to Process: " << currentProcess.processId << endl;

            while(currentProcess.numCycles > 0) {
                delay(1);
                totalCycles++;//incremenet the total cycles
                currentProcess.numCycles--;//decrement the cycles left for the process
                //display the remaining cycles
                cout << "Process " << currentProcess.processId << " ,cycles left: " << currentProcess.numCycles << endl;
            }
            //show that a certain process has been terminated
            cout << "Process " << currentProcess.processId << " terminated" << endl;
            terminatedProcesses.push_back(currentProcess);
        }
        //show all of the total cycles that have been executed
        cout << "Execution compete, total cycles: " << totalCycles << endl;
    }

    //sjf
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
                    cout << "Process " << currentProcess.processId << ",cycles left: " << currentProcess.numCycles << endl;
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
