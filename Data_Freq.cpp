/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Data_Freq.cpp
 * Author: zain
 * 
 * Created on October 16, 2016, 10:34 PM
 */

#include "Data_Freq.h"

Data_Freq::Data_Freq()
{
}

Data_Freq::Data_Freq(int data, int freq)
{
    setData(data);
    setFreq(freq);
}

int Data_Freq::getData() const
{
    return data;
}

void Data_Freq::setData(int data)
{
    this->data=data;
}

int Data_Freq::getFreq() const
{
    return freq;
}

void Data_Freq::setFreq(int freq)
{
    this->freq=freq;
}

string Data_Freq::getCode()
{
    return huffmanCode;
}

void Data_Freq::setCode(string code)
{
    this->huffmanCode=code;
}

Data_Freq::~Data_Freq()
{
}

