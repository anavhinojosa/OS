#include <iostream>

enum State { New, Ready, Running, Waiting, Terminated};

<<<<<<< Updated upstream
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
=======
const int max_process = 10000;
int count_process = 0;
int current_pid = 1000;

struct Process
{
    int pid;
    bool active;
    int cycle;
    Process()
    {
        pid = -1;       // pid to -1 = no active process
        active = false; // active is false = process is inactive
    }
};

Process processesArray[max_process];

void startProcess()
{
    int i = 0;
    srand(time(0));
    int randomProcess = 5; //lets make 10 processesArray for now
    cout << "Started process" << endl;

    for (i = 0; i < randomProcess; ++i)
    {
        if (count_process < max_process)
        {
            processesArray[count_process].pid = i; // random PId
            processesArray[count_process].active = true;
            processesArray[count_process].cycle = 5 + (rand() % 20); // goes from 5 to 24 i thinik

            cout << "Process Id: " << processesArray[count_process].pid << ", Cycles: " << processesArray[count_process].cycle << endl;

            count_process++;
        }
        else
        {
            cout << "Cannot start more processesArray. Maximum limit reached." << endl;
            break;
        }
    }
    cout << i << " processesArray were created." << endl;
}

void terminateProcess(int pid)
{
    bool found = false;

    for (int i = 0; i < count_process; i++)
    {
        if (processesArray[i].pid == pid && processesArray[i].active)
        {
            processesArray[i].active = false;
            cout << "Process with PID " << pid << " terminated successfully." << endl;
            found = true;
            count_process--; // forgot to add the decrement
            break;
        }
    }

    if (!found)
    {
        cout << "Process with PID " << pid << " not found." << endl;
>>>>>>> Stashed changes
    }

<<<<<<< Updated upstream
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
=======
void listProcesses()
{
    if (count_process == 0)
    {
        cout << "No running processesArray." << endl;
    }
    else
    {
        cout << "Currently running processesArray:" << endl;
        for (int i = 0; i < count_process; i++)
        {
            if (processesArray[i].active)
            {
                cout << "PID: " << processesArray[i].pid << endl;
            }
        }
    }
}

>>>>>>> Stashed changes
