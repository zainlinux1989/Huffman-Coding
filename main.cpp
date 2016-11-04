/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: zain
 *
 * Created on October 16, 2016, 7:00 PM
 */

#include <cstdlib>
#include "FileReader.h"
#include "Huffman.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
    string command;
    string fileName;
    
    cout<<">> ";
    getline(cin,command);
    
    Huffman hm;
    
    while (command.length() >= 8 && ((command.substr(command.length() - 3, 3) == ".8b")||(command.substr(command.length() - 4, 4) == ".zif")))
    {

        // if command start with "compress" and end with .8b
        if (command.substr(0, 8) == "compress")
        {
            if (command.substr(command.length() - 3, 3) == ".8b")
            {
                fileName = command.substr(9, command.length());
                hm.compressFile(fileName.c_str());
            }

            else
            {
                cout<<"Invalid parameters command not end with .8b"<<endl;
            }
            
            cout << ">> ";
            getline(cin, command);
        }

            // if command start with "decompress" and end with .zif
        else if (command.substr(0, 10) == "decompress")
        {
            if (command.substr(command.length() - 4, 4) == ".zif")
            {
                fileName = command.substr(11, command.length());
                hm.decompressFile(fileName.c_str());
            }

            else
            {
                cout<<"Invalid parameters command not end with .zif"<<endl;
            }   
            
            cout << ">> ";
            getline(cin, command);
        }
   }

    if(command=="quit")
        cout<<"Have a nice day"<<endl;
    
    else
        cout << "Invalid command" << endl;
    
    return 0;
}

