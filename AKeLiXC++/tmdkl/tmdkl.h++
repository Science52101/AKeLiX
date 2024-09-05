#ifndef TMDKL_H
#define TMDKL_H

#include <iostream>
#include <windows.h>

// The MDK ( Micro Dynamic Kalculator ) Library

// The MDK ( Micro Dynamic Kalculator ) Library - Console Line Drawer

// MDK CalculateGraphics f(x)
void MDK_CalculateGraphics(HANDLE console, int clmns, int rws, char coordchar, double (*fx)(int), bool vl)
{
    short rws2 = rws;

    Sleep(300);

    for (short i = 0; i < clmns; i++)
    {
        COORD pos = { 0, 0 };
        if (rws >= fx(i))
        {
            pos = { i,  static_cast<SHORT>(rws2 - fx(i)) };
        }
        else
        {
            pos = { i,  0 };
        }
        SetConsoleCursorPosition(console, pos);
        std::cout << coordchar;
        if (vl) { std::cout << fx(i); }

        Sleep(1);
    }
}

// The MDK ( Micro Dynamic Kalculator ) Library - MDK Interface Tools

// Clean Terminal
void MDK_CleanTerminal(HANDLE console)
{
    SetConsoleCursorPosition(console, { 0, 0 });
    for (int i = 0; i <= 20000; i++)
    {
        printf(" ");
        if ((rand() % 1000) == 0)
        {
            Sleep(1);
        }
    }
}

// The MDK ( Micro Dynamic Kalculator ) Library - Automatic MDK

// MDK Draw f(x)
void MDK_Draw(double (*fx)(int), char coordchar = '#', bool cleanTerminal = true, bool withValues = false)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int clmns = csbi.srWindow.Right - csbi.srWindow.Left, rws = csbi.srWindow.Bottom - csbi.srWindow.Top;
    if (cleanTerminal) { MDK_CleanTerminal(console); }
    MDK_CalculateGraphics(console, clmns, rws, coordchar, fx, withValues);
}

#endif
