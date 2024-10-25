#include <iostream>

enum State { New, Ready, Running, Waiting, Terminated};

class Process {
public:
    int pid;
    int cycles;
    State state;
    Process (int id, int cyc) {
        pid = id;
        cycles = cyc;
        state = New;
    }

    void display() {
        cout << "Process ID: " << pid << " , Cycles" << cycles << << " , State: " << getStateName() << endl;
    }

    string getStateName() {
        switch (state) {
            case New:
                return "New";
            case Ready:
                return "Ready";
            case Running:
                return "Running";
            case Waiting:
                return "Waiting";
            case Terminated:
                return "Terminated";
            default:
                return "Not found :(";

    }
}