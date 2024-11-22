#ifndef CPUINSTRUCTIONS_H
#define CPUINSTRUCTIONS_H

#include <iostream>
#include <queue>
#include <vector>
#include <list>
#include <algorithm>
#include "Translation.h"
#include "Delays.h"

using namespace std;

// external variables
extern int cyclesArray[];           // # of cycles for processes
extern list<Process> listProcesses; // list of processes
extern int instructionsExecuted;    // instruction execution counter

// instruction types
const int INSTRUCTION_LD = 0;         // load
const int INSTRUCTION_ST = 1;         // store
const int INSTRUCTION_ARITHMETIC = 2; // arithmetic
const int INSTRUCTION_LOGIC = 3;      // logic

class CPU
{
public:
    Process currentProcess;
    int schedulePolicy; // 0 - FCFS, 1 - SJF, 2 - Round Robin
    int timeQuantum;    // time quantum for RR

    void executeProcess(queue<Process> &readyQueue, queue<Process> &terminatedProcesses)
    {
        if (readyQueue.empty())
        {
            cout << "[Error] No processes in ready queue." << endl;
        }
        switch (schedulePolicy)
        {
        case 0:
        {
            FCFS(readyQueue, terminatedProcesses);
            break;
        }
        case 1:
        {
            Process processArray[listProcesses.size()];
            int index = 0;
            for (Process &p : listProcesses)
            {
                processArray[index++] = p;
            }
            SJF(processArray, listProcesses.size());
            break;
        }
        case 2:
        {
            RR(readyQueue, terminatedProcesses);
            break;
        }
        default:
        {
            cout << "Invalid scheduling policy. Use 0-FCFS, 1-SJF, or 2-RR." << endl;
            break;
        }
        }
    }

    // first Come, First Served (FCFS) Scheduling
    void FCFS(queue<Process> &readyQueue, queue<Process> &terminatedProcesses)
    {
        cout << "[First Come, First Served Scheduling...]" << endl;
        // continue until the ready queue is empty
        while (!readyQueue.empty())
        {
            // select the first process
            currentProcess = readyQueue.front();
            readyQueue.pop();         // remove the process from the ready queue
            currentProcess.state = 4; // update the state to running
            // context switch
            cout << "[Context Switch: PID " << currentProcess.processId << "]" << endl;
            // continue until there are no more cycles
            while (currentProcess.numCycles > 0)
            {
                executeCycle(currentProcess);
            }
            // since there are no more cycles, then update the state
            currentProcess.state = 5; // terminated
            // add it to the terminated process to a queue
            terminatedProcesses.push(currentProcess); // terminatedProcesses queue
            cout << "Process " << currentProcess.processId << " terminated.\n"
                 << endl;
        }
        cout << "[Processes Completed in First Come, First Served Scheduling]\n"
             << endl;
    }

    // Shortest Job First (SJF) Scheduling
    void SJF(Process processes[], int processCount)
    {
        cout << "\n[Switching to Shortest Job First Scheduling...]" << endl;
        vector<Process> processVector(processes, processes + processCount);
        sort(processVector.begin(), processVector.end(),
             [](const Process &a, const Process &b)
             { return a.numCycles < b.numCycles; });
        for (const Process &p : processVector)
        {
            currentProcess = p;
            cout << "\n[Context Switch: PID " << currentProcess.processId << "]" << endl;
            while (currentProcess.numCycles > 0)
            {
                executeCycle(currentProcess);
            }
            currentProcess.state = 5; // terminated
            cout << "Process " << currentProcess.processId << " terminated." << endl;
        }
        cout << "\n[Processes Completed in Shortest Job First Scheduling]" << endl;
    }

    // Round Robin (RR) Scheduling
    void RR(queue<Process> &readyQueue, queue<Process> &terminatedProcesses)
    {
        while (!readyQueue.empty())
        {
            Process currentProcess = readyQueue.front();
            readyQueue.pop();
            cout << "[Context Switch: PID " << currentProcess.processId << "]" << endl;
            int cyclesToExecute = min(currentProcess.numCycles, timeQuantum);
            for (int i = 0; i < cyclesToExecute; i++)
            {
                executeCycle(currentProcess);
            }
            if (currentProcess.numCycles > 0)
            {
                readyQueue.push(currentProcess);
            }
            else
            {
                currentProcess.state = 5; // terminated
                terminatedProcesses.push(currentProcess);
                cout << "Process " << currentProcess.processId << " terminated." << endl;
            }
        }
    }

    void printSummary(queue<Process> &terminatedProcesses)
    {
        cout << "[Final Summary]" << endl;
        cout << "Processes Completed:" << endl;
        int processCount = 0;
        while (!terminatedProcesses.empty())
        {
            Process p = terminatedProcesses.front();
            terminatedProcesses.pop();
            cout << ++processCount << ". PID " << p.processId << endl;
        }
        cout << "\nScheduling Algorithms Simulated:" << endl;
        cout << "1. First Come First Serve" << endl;
        cout << "2. Shortest Job First" << endl;
        cout << "3. Round Robin" << endl;
        cout << "\nStatistics:" << endl;
        cout << "\nTotal TLB Hits: " << std::dec << tlbHits << endl;
        cout << "Total TLB Misses: " << std::dec << tlbMisses << endl;
        cout << "Page Faults Handled: " << std::dec << pageFaults << endl;
        cout << "Instructions Executed: " << std::dec << instructionsExecuted << endl;
    }

private:
    void executeCycle(Process &process)
    {
        if (process.numCycles > 0)
        {
            cout << "[Executing Instructions for PID " << process.processId << "]" << endl;
            process.numCycles--; // decrement the cycles
            cout << "[Cycle Update] PID " << process.processId
                 << ", Cycles Left: " << process.numCycles
                 << ", State: Running" << endl;
        }
        else
        {
            process.state = 5; // process as Terminated
        }
    }

    // execute a random instruction for a process
    void executeInstruction(Process &process)
    {
        cout << "[Executing Instructions for PID " << std::dec << process.processId << "]" << endl;
        static int instructionCount = 1;
        int maxInstructions = 1; // 1 instructions per cycle
        int executed = 0;        // instructions executed in this cycle
        cout << "[Executing Instructions for PID " << process.processId << "]" << endl;
        while (executed < maxInstructions)
        {
            int instructionType = rand() % 4;
            instructionsExecuted++; // increment global instruction counter
            switch (instructionType)
            {
            case INSTRUCTION_LD:
            {
                int virtualAddress = rand() % (NUM_VIRTUAL_PAGES * PAGE_SIZE); // random virtual address
                cout << "Instruction " << instructionCount++ << ": LOAD R1, [0x" << hex << virtualAddress << "]" << endl;
                translateAddress(virtualAddress);
                cout << "[LOAD Completed for Virtual Address 0x" << hex << virtualAddress << "]" << endl;
                break;
            }
            case INSTRUCTION_ST:
            {
                int virtualAddress = rand() % (NUM_VIRTUAL_PAGES * PAGE_SIZE);
                cout << "Instruction " << instructionCount++ << ": STORE R2, [0x" << hex << virtualAddress << "]" << endl;
                translateAddress(virtualAddress);
                cout << "[STORE Completed for Virtual Address 0x" << hex << virtualAddress << "]" << endl;
                break;
            }
            case INSTRUCTION_ARITHMETIC:
                cout << "Instruction " << instructionCount++ << ": ADD R1, R2, R3" << endl;
                cout << "  - [OK] Arithmetic Operation Performed." << endl;
                break;
            case INSTRUCTION_LOGIC:
                cout << "Instruction " << instructionCount++ << ": AND R4, R5, R6" << endl;
                cout << "  - [OK] Logical Operation Performed." << endl;
                break;
            }
            executed++;
        }
    }
};

#endif
