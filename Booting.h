#include <iostream>
#include "Delays.h"

using namespace std;

void bootSystem() {
    cout << "[System Booting...]" << endl;
    delay(2);
    cout << "[OK] Powering on hardware." << endl;
    delay(2);
    cout << "[OK] Loading kernel modules." << endl;
    delay(2);
    cout << "[OK] Initializing memory management unit (MMU)." << endl;
    delay(2);
    cout << "[OK] Configuring interrupt handling." << endl;
    delay(2);
    cout << "[OK] Boot sequence complete." << endl;
    delay(2);
    cout << "Welcome to the OS Simulator!" << endl;
    delay(2);
    cout << "\n";
}
