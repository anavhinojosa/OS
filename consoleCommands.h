
#ifndef CONSOLECOMMANDS_H
#define CONSOLECOMMANDS_H

#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#endif

void clearConsole()
{
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux/macOS
#endif
}

#endif