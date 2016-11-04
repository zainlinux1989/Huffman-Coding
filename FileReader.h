/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileReader.h
 * Author: zain
 *
 * Created on October 16, 2016, 7:02 PM
 */
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#ifndef FILEREADER_H
#define FILEREADER_H

class FileReader {
public:
    FileReader();
    FileReader(const string &fileName);
    void processFile();
    int binToDec(const string binPattern);
    vector<int> getNumList() const;
    string getFileName() const;
    virtual ~FileReader();
private:
    string fileName;
    int decimalNum;
    vector<int> numList;
};

#endif /* FILEREADER_H */

