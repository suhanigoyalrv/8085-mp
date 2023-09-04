#include<bits/stdc++.h>
#include<fstream>
#include"Execution.h"
#include"Validation.h"
#include"Memory_Allocation.h"
#include"Debugger.h"
#include"DataTransfer.h"
using namespace std;
void utility(bool* flag,string* registers,map<string,string>& memory)
{
	int n;
	cout<<"Enter  Number of MemoryAddresses needed:: "; 
	cin>>n;
	while(n--)
	{		
		string str1,str2;
		cout<<"Write the memory location and the the data corresponding to that memory location";
		cin>>str1>>str2;
		SET(str1,str2,memory);	//to set the data	
	}
}
	void PrintCode(vector<string>& sequence,map<string,string>& memory,string pc,bool* flag,string* registers)
	{
	    string start=" ";
	    string end="HLT";
	    cout<<"Starting Memory Address :: ";
	    cin>>start;
	    pc=start;
		string s;
	    /*if(memoryValidation(start))
	    {
			cout<<endl<<"INVALID/MEMORY ADDRESS OR RESERVED ADDRESS"<<endl;
	    }*/
	    ifstream infile("sample.txt");
	    getline(infile,s);    
	    while(s.compare(end)) //read file and print the code
	    {
			if(inputValidation(s)) 
				{
					cout<<pc;               //to allocate memory to print
					sequence.push_back(pc);	
					memory[pc]=s;
					string delimiter = " ";
					string token = s.substr(0, s.find(delimiter)); 
					pc=allocate_memory(token,pc);
					cout<<"::"<<s<<endl;
					getline(infile,s);
				}		
			else
				{
					cout<<"INVALID INPUT"<<endl;
			    }
	    }
	    pc=start;
	    int count=0;	
	    int last=sequence.size()-1;
	    //cout<<sequence[last];
	    while(pc.compare(sequence[last])) //for execution of each statement
	    {					
		    //cout<<memory[pc]<<endl;		
		    pc=execute_statement(memory[pc],flag,registers,memory,pc);
	    }
	    pc=execute_statement(memory[pc],flag,registers,memory,pc);
    }
    void PrintResult(bool* flag,string* registers,map<string,string>& memory)
    {
		int n;
	    cout<<"***"<<endl<<endl; //printing registers and flags
	    cout<<"REGISTERS"<<endl;
	    for(int i=0;i<7;i++)	
		    cout<<registers[i]<<" ";
	    cout<<endl;	
	    cout<<"***"<<endl;	
	    cout<<endl;
	    cout<<"flag"<<endl;
	    for(int i=0;i<7;i++)	
		    cout<<flag[i]<<" ";
	    cout<<endl;
	    cout<<"Enter the Number of Result Addresses needed:: ";
	    cin>>n;
	    string result[n];
	    for(int i=0;i<n;i++)
		    cin>>result[i];
	    cout<<"******"<<endl;
	    cout<<"Accumulator Result ::"<<registers[0]<<endl;	
	    cout<<"*******"<<endl;
	    cout<<"Memory Result"<<endl;
	    cout<<"*******"<<endl;
	    for(int i=0;i<n;i++)
		    cout<<result[i]<<" :: "<<memory[result[i]]<<endl;
    }
int main()
{
     map<string,string> memory;
	vector<string> sequence;
	string input;
	//ifstream infile("sample.txt");
	string pc=" ";
	string s;
	string registers[7];
	bool flag[8];
	for(int i=0;i<7;i++)
		registers[i]="00";
	for(int i=0;i<8;i++)
		flag[i]=false;	
    cout<<"Enter\n1-Programming mode\n2-Debugger mode\n";
    int ch,ch1;
    cin>>ch;
    if(ch==1)
    {
       cout<<"Welcome to 8085 Programming Mode\n";
       cout<<"____________\n";
       cout<<"enter\n1-to read from file\n2-to enter the code\n";
       cin>>ch1;
       if(ch1==1)
       {
           ifstream infile("sample.txt");
           utility(flag,registers,memory);
           PrintCode(sequence,memory,pc,flag,registers);
           PrintResult(flag,registers,memory);
       }
       else if(ch1==2)
       {
        ofstream fout;
        string line;
        fout.open("sample.txt");
		cin.ignore();
        while (fout) 
            {
				
                getline(cin, line);
				
                if (line == "HLT")
				{
                    fout << line << endl;
				    break;
				}
				fout << line << endl;
            }
        fout.close();
        utility(flag,registers,memory);
        PrintCode(sequence,memory,pc,flag,registers);
        PrintResult(flag,registers,memory);
       }
       
    }
    else if(ch==2)
    {
        cout<<"Welcome to Debugger mode\n";
        cout<<"enter\n1-to read from file\n2-to enter the code\n";
       cin>>ch1;
       if(ch1==1)
       {
           ifstream infile("sample.txt");
            string start=" ";
	        cout<<"Starting Memory Address :: ";
	        cin>>start;
	        pc=start;
	        /*if(memoryValidation(start))
	        {
			    cout<<endl<<"INVALID/MEMORY ADDRESS OR RESERVED ADDRESS"<<endl;
	        }*/
	       utility(flag,registers,memory);
           Run(memory[pc],flag,registers,memory,pc);
           
       }
       else if(ch1==2)
       {
        ofstream fout;
        string line;
        fout.open("sample.txt");
		cin.ignore();
        while (fout) 
            {
				
                getline(cin, line);
				
                if (line == "HLT")
				{
                    fout << line << endl;
				    break;
				}
				fout << line << endl;
            }
            string start=" ";
	        cout<<"Starting Memory Address :: ";
	        cin>>start;
	        pc=start;
	        /*if(memoryValidation(start))
	        {
			    cout<<endl<<"INVALID/MEMORY ADDRESS OR RESERVED ADDRESS"<<endl;
	        }*/
	        fout.close();
	    utility(flag,registers,memory);
        Run(memory[pc],flag,registers,memory,pc);
       }
    else
    {
        cout<<"Invalid input";
        exit(1);
    }
    
    return 0;
}
}