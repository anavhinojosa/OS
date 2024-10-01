#ifndef USERINPUTFUNCTIONS_H
#define USERINPUTFUNCTIONS_H
#include<iostream>
#include<iomanip>
using namespace std;


// these functions are for safe user Input, they prevent the program from crashing

// pass parameters min and max during function call, and the message has to match the logic of these
// function enforces user to enter a number into the console

int getNumberInput(int min, int max, string message){

    cout << message;
    string userInputString;


    bool isAcceptable = true;

while(isAcceptable){
     try
    {
        cin >> userInputString;
        int userInputNum = stoi(userInputString);

    while(userInputNum < min || userInputNum > max){
        cout << "Please Enter a number between " << min << " and " << max << ": ";
        cin >> userInputString;
        userInputNum = stoi(userInputString);
    };

    cout << userInputNum << endl;
    return userInputNum;
    }
    catch (const invalid_argument &error)
    {
        cout << "Invalid input, please enter a valid integer: " << endl;
        isAcceptable = false;
    };
}

return 99;
};


#endif