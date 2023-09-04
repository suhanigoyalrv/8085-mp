#include<bits/stdc++.h>
using namespace std;
#ifndef DEBUGGER_H
#define DEBUGGER_H
void RunTillBreakpoint(string input,bool* flag,string* registers,map<string,string> &memory,string pc);
void printhelp();
void PrintArchitecture(string* registers,bool* flag,map<string,string>& memory,string pc);
void PrintMemoryAddress(map<string,string> &memory,bool*flag,string* registers);
void exe(string pc,bool* flag,string* registers,map<string,string> &memory);
void Run(string input,bool* flag,string* registers,map<string,string> &memory,string pc);
#endif