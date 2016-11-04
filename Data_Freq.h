/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Data_Freq.h
 * Author: zain
 *
 * Created on October 16, 2016, 10:34 PM
 */
#include <string>
using namespace std;
#ifndef DATA_FREQ_H
#define DATA_FREQ_H

class Data_Freq {
public:
    Data_Freq();
    Data_Freq(int data,int freq);
    int getData() const;
    void setData(int data);
    int getFreq() const;
    void setFreq(int freq);
    string getCode();
    void setCode(string code);
    virtual ~Data_Freq();
private:
    int data;
    int freq;
    string huffmanCode;
};

#endif /* DATA_FREQ_H */

