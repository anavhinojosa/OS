#ifndef CPUINSTRUCTIONS_H
#define CPUINSTRUCTIONS_H

#include <iostream>
#include <queue>
#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include "translation.h"

using namespace std;

extern int cyclesArray[]; //number of cycles for processes
extern std::list<Process> listProcesses;//list of processes

const int INSTRUCTION_LD = 0;//load
const int INSTRUCTION_ST = 1;//store
const int INSTRUCTION_ARITHMETIC = 2;//arithmetic
const int INSTRUCTION_LOGIC = 3;//logic

class CPU {
public:
    Process currentProcess;
    int schedulePolicy; // 0-FCFS, 1-SJF, 2- Round Robi
    int timeQuantum;

    void executeProcess(){
        switch (schedulePolicy) {
            case 0:
                FIFO(readyQueue);
            break;
            case 1:
                SJF(cyclesArray, listProcesses);
            break;
            case 2:
                RR(readyQueue, waitingQueue);
            break;
            default:
                cout << "Invalid. Try again (0-2)" << endl;
            break;
        }
    };

    // fifo
    void FIFO(queue<Process> &readyQueue)
    {
        cout << "Starting FIFO Scheduling..." << endl;
        int totalCycles = 0;                 // keep track of the total cycles executed
        vector<Process> terminatedProcesses; // stores the completed process
        // this is for the process taht are on the ready queue
        while (!readyQueue.empty())
        {
            currentProcess = readyQueue.front(); // get the next process (without removing it)
            readyQueue.pop();
            currentProcess.state = 4;//mark it as running
            // remove it from the queue
            // to show the next content switch to the other process
            cout << "\nContext Switch to Process: " << currentProcess.processId << endl;

            while (currentProcess.numCycles > 0)
            {
                delay(1);
                totalCycles++;              // incremenet the total cycles
                currentProcess.numCycles--; // decrement the cycles left for the process
                executeInstruction(currentProcess);//excutes an instruction
                // display the remaining cycles
                cout << "Process " << currentProcess.processId << " ,cycles left: " << currentProcess.numCycles << endl;
            }
            // show that a certain process has been terminated
            cout << "Process " << currentProcess.processId << " terminated" << endl;
            terminatedProcesses.push_back(currentProcess);
        }
        // show all of the total cycles that have been executed
        cout << "Execution compete, total cycles: " << totalCycles << endl;
    }

    // rr
    void RR(std::queue<Process> &readyQueue, std::queue<Process> &waitingQueue) {
        cout << "Starting Round Robin Scheduling..." << endl;
        int totalCycles = 0;//total cycles executed
        vector<Process> terminatedProcesses;//completed process
        timeQuantum = 5;// time quantum for rr
        while (!readyQueue.empty())
        {
            delay(1);
            currentProcess = readyQueue.front();
            readyQueue.pop();
            currentProcess.state = 4;//running
            cout << "\nContext Switch to Process: " << currentProcess.processId << endl;
            for (int i = 0; i < timeQuantum && currentProcess.numCycles > 0; i++) {
                if (currentProcess.numCycles > 0){
                    delay(1);
                    totalCycles++;
                    currentProcess.numCycles--;//decrease remaining cycles
                    executeInstruction(currentProcess);
                    cout << "Process " << currentProcess.processId << ",cycles left: " << currentProcess.numCycles << endl;

                }
            }
            if (currentProcess.numCycles > 0) {
                readyQueue.push(currentProcess);//if not finish push it back to the queue
            }
            else {
                //do if process if finish
                cout << "Process " << currentProcess.processId << " terminated" << endl;
                terminatedProcesses.push_back(currentProcess);
            }
        }
        cout << "Execution compete, total cycles: " << totalCycles << endl;
    }

    //shortest job first scheduling
    void SJF(int cyclesArray[], std::list<Process> &processList){
        cout << "Starting Shortest Job First Scheduling..." << endl;
        for (int i = 0; i < 20; i++)
        {
            int smallestNumCycles = cyclesArray[i]; // this will give me the shortest num per iteration
     //       cout << smallestNumCycles << endl;

            std::list<Process>::iterator currentProcess2 = std::find_if(processList.begin(), processList.end(),
                                                                        [smallestNumCycles](const Process &p)
                                                                        {
                                                                            return p.numCycles == smallestNumCycles;
                                                                        });

            Process toExecute = *currentProcess2;

            // cout << "Process: " << toExecute.processId << ", num Cycles: " << toExecute.numCycles << endl;
            processList.erase(currentProcess2);
            delay(3);
            cout << "\nContext switch to Process: " << toExecute.processId << ", with Cycles: " << toExecute.numCycles << endl;

            while (toExecute.numCycles > 0)
            {
                delay(1);
                cout << "Cycles left: " << toExecute.numCycles << endl;
                toExecute.numCycles--;
                //executeInstruction(toExecute);???
            }
            cout << "Process: " << toExecute.processId << " terminated!" << endl;
        }
    }
private:
    //this will executeInstruction - LD, ST, Arithmetic, Logic
    void executeInstruction(Process &process) {
        int instructionType = rand() % 4;//random
        switch (instructionType) {
            case INSTRUCTION_LD: {
                cout << "Process " << process.processId << " executed an LOAD instruction." << endl;
                break;
            }
            case INSTRUCTION_ST: {
                cout << "Process " << process.processId << " executed an ST instruction." << endl;
                break;
            }
            case INSTRUCTION_ARITHMETIC: {
                cout << "Process " << process.processId << " executed an ARITHMETIC instruction." << endl;
                break;
            }
            case INSTRUCTION_LOGIC: {
                cout << "Process " << process.processId << " executed an LOGIC instruction." << endl;
                break;
            }
            default:
                cout << "Unknown instruction type." << endl;
        }
    }
};

#endif
