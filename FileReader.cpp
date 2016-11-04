/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileReader.cpp
 * Author: zain
 * 
 * Created on October 16, 2016, 7:02 PM
 */

#include "FileReader.h"

FileReader::FileReader()
{
}

FileReader::FileReader(const string& fileName)
{
    this->fileName=fileName;
}

// process on file and convert all binary pattern in decimal numbers
void FileReader::processFile()
{
    numList.clear();
    
    ifstream inputFile;
    inputFile.open(fileName.c_str(),ios::in);
    
    char c;
    string oneByte="";
    int count=0;
    
    while(inputFile.get(c))
    {
        oneByte=oneByte+c;
        count++;
        
        // get 1 byte binary pattern 
        if(count==8)
        {
            // convert into number and push into vector list
            numList.push_back(binToDec(oneByte));
            count=0;
            oneByte="";
        }
    }
    inputFile.close();
}

string FileReader::getFileName() const
{
    return fileName;
}

vector<int> FileReader::getNumList() const
{
    return numList;
}

// convert binary pattern into decimal number
int FileReader::binToDec(const string binPattern)
{
    int size=binPattern.size()-1;
    int num=0;
    decimalNum=0;
    for(int i=binPattern.size()-1;i>=0;i--)
    {
        if(binPattern.at(i)=='1')
        {
            if(i==size)
                num=1;
            else
                num=pow(2,size-i);                                                 
        }
        // if bit is zero
        else
        {
            num=0;
        }             
        decimalNum=decimalNum+num;      
    }
    return decimalNum;
}

FileReader::~FileReader()
{
}

