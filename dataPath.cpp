/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dataPath.cpp
 * Author: zain
 * 
 * Created on October 30, 2016, 8:18 PM
 */

#include "dataPath.h"

dataPath::dataPath()
{
}

dataPath::dataPath(string data,string path)
{
    this->data=data;
    this->path=path;
}

string dataPath::getData() 
{
    return data;
}

string dataPath::getPath()
{
    return path;
}

void dataPath::setData(const string& data)
{
    this->data=data;
}

void dataPath::setPath(const string& path)
{
    this->path=path;
}

dataPath::~dataPath()
{
}

