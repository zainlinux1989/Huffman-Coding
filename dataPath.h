/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dataPath.h
 * Author: zain
 *
 * Created on October 30, 2016, 8:18 PM
 */
#include <string>
using namespace std;
#ifndef DATAPATH_H
#define DATAPATH_H

class dataPath {
public:
    dataPath();
    dataPath(string data,string path);
    void setData(const string& data);
    string getData();
    void setPath(const string& path);
    string getPath();
    virtual ~dataPath();
private:
    string data;
    string path;
};

#endif /* DATAPATH_H */

