#include <iostream>

using namespace std;

void delay(int seconds) {
  for (int i = 0; i < seconds * 100000000; ++i) {
    //simulate the delay.
  }
}

void bootSystem() {
  cout << "Booting OS Simulator" << endl;
  delay(4);

  cout << "Loading..." << endl;
  cout << "Please do not quit." << endl;
  delay(4);

  cout << "System booted" << endl;
}
