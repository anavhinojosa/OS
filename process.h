#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int max_process = 10000;
int count_process = 0;
int current_pid = 1000;

struct Process {
    int pid;
    bool active;
    Process() {
        pid = -1; //pid to -1 = no active process
        active = false; //active is false = process is inactive
    }
};

Process processes[max_process];

void startProcess() {
    if (count_process < max_process) {
        processes[count_process].pid = current_pid++;
        processes[count_process].active = true;
        cout << "Process started with PID: " << processes[count_process].pid << endl;
        count_process++;
    } else {
        cout << "Cannot start more processes. Maximum limit reached." << endl;
    }
}

void terminateProcess(int pid) {
    bool found = false;

    for (int i = 0; i < count_process; i++) {
        if (processes[i].pid == pid && processes[i].active) {
            processes[i].active = false;
            cout << "Process with PID " << pid << " terminated successfully." << endl;
            found = true;
            count_process--;//forgot to add the decrement
            break;
        }
    }

    if (!found) {
        cout << "Process with PID " << pid << " not found." << endl;
    }
}

void listProcesses() {
    if (count_process == 0) {
        cout << "No running processes." << endl;
    } else {
        cout << "Currently running processes:" << endl;
        for (int i = 0; i < count_process; i++) {
            if (processes[i].active) {
                cout << "PID: " << processes[i].pid << endl;
            }
        }
    }
}
