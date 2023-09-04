#include <iostream>
#include<cstring>
#include<fstream>
#include<bits/stdc++.h>
#include<sstream>
#include"Execution.h"
#include"Memory_Allocation.h"
#include<map>
#include"Debugger.h"
using namespace std;

void RunTillBreakpoint(string input,bool* flag,string* registers,map<string,string> &memory,string pc)
{
    int breakpoint;
    //vector<string> sequence;
    cout<<"Enter breakpoint: ";
    cin>>breakpoint;
    string s,temp=pc;
    ifstream infile("sample.txt");
    while(breakpoint)
    {	
        //ifstream infile("sample.txt");
        getline(infile,s);
        cout<<pc;               //to allocate memory to print
		//sequence.push_back(pc);	
		memory[pc]=s;
		string delimiter = " ";
		string token = s.substr(0, s.find(delimiter)); 
		pc=allocate_memory(token,pc);
		cout<<"::"<<s<<endl;
        exe(temp,flag,registers,memory);
        temp=pc;
        breakpoint--;
    }
    PrintArchitecture(registers,flag,memory,pc);
}
 void exe(string pc,bool* flag,string* registers,map<string,string> &memory)
 {						
		    pc=execute_statement(memory[pc],flag,registers,memory,pc);
	    //pc=execute_statement(memory[pc],flag,registers,memory,pc);
        //PrintArchitecture(registers,flag,memory,pc);
}

void printhelp(string input,bool* flag,string* registers,map<string,string>& memory,string pc)
{
    Run(input,flag,registers,memory,pc);
}
void PrintArchitecture(string* registers,bool* flag,map<string,string>& memory,string pc)
{
    cout<<"*****Microprocessor Architecture*****\n";
    cout<<"__________________\n";
    cout<<"Registers           "<<"Value                    "<<endl;
    cout<<"___________________\n";
    cout<<"Accumulator         "<<setw(13)<<registers[0]<<endl;
    cout<<"-------------------------------------------------------\n";
    cout<<"B                   "<<setw(13)<<registers[1]<<endl;
    cout<<"-------------------------------------------------------\n";
    cout<<"C                   "<<setw(13)<<registers[2]<<endl;
    cout<<"-------------------------------------------------------\n";
    cout<<"D                   "<<setw(13)<<registers[3]<<endl;
    cout<<"-------------------------------------------------------\n";
    cout<<"E                   "<<setw(13)<<registers[4]<<endl;
    cout<<"-------------------------------------------------------\n";
    cout<<"H                   "<<setw(13)<<registers[5]<<endl;
    cout<<"-------------------------------------------------------\n";
    cout<<"L                   "<<setw(13)<<registers[6]<<endl;
    cout<<"___________________\n";
    cout<<endl;
    cout<<"___________________\n";
    cout<<"Flags  "<<"  CY  "<<"  Z  "<<"  AC  "<<"  P  "<<"  S  "<<endl;
    cout<<"-------------------------------------------------------\n";
    cout<<"Value  "<<  flag[0]  <<  flag[6]  <<  flag[4]  <<  flag[2]  <<  flag[7]  <<endl;
    cout<<"___________________\n";
    Run(memory[pc],flag,registers,memory,pc);
}
void PrintMemoryAddress(map<string,string> &memory,bool*flag,string* registers)
{
    string command;
    cout<<"Enter the command for printing:"<<endl;
    cin.ignore();
    getline(cin,command);
    
    
    if(command[0]=='p' && command[1]==' ')
    {
        if(command.length()==3 && (command[2]=='A'||command[2]=='B'||command[2]=='C'||command[2]=='D'||command[2]=='E'||command[2]=='H'||command[2]=='L'))
        {
            cout<<"Value at "<<command[2]<<" is "<<registers[command[2]-'A']<<endl;
        }
        else if(command.length()==6) //doubt in hexadecimal
        {
        string addr=command.substr(2,5);
        cout<<addr<<endl;
        cout<<"Value stored at "<<addr<<" is "<<memory[addr];
        }
    }
}
void Run(string input,bool* flag,string* registers,map<string,string>& memory,string pc)
{
    cout<<"Commands:\n";
    cout<<"run(r)->Run till breakpoint or end of program\n";
    cout<<"step(s)->Execute one instruction at a time\n";
    cout<<"print(p)->Print value of register or memory location\n";
    cout<<"print architecture(pa)->printing the 8085 architecture\n";
    cout<<"quit(q)->quit the debugger mode\n";
    cout<<"help(h)->Help message\n";
    while(true)
    {
        string choice;
        cout<<"\n";
        cin>>choice;
        if(choice=="run"||choice=="r")
        {
            RunTillBreakpoint(input,flag,registers,memory,pc);
        }
        else if(choice=="quit"||choice=="q")
        {
            cout<<"Debugger terminated";
            break;
        }
        else if(choice=="help"||choice=="h")
        {
            printhelp(input,flag,registers,memory,pc);
        }
        else if(choice=="print"||choice=="p")
        {
            PrintMemoryAddress(memory,flag,registers);
        }
        else if(choice=="print architecture"||choice=="pa")
        {
            PrintArchitecture(registers,flag,memory,pc);
        }
        else
        {
            cout<<"INVALID COMMAND\ntype 'help' for list of commands\n";
        }
    }
}