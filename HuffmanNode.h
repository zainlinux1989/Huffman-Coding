/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: zain
 *
 * Created on October 16, 2016, 11:12 PM
 */

#ifndef NODE_H
#define NODE_H

#include "Data_Freq.h"


struct HuffmanNode
{
    Data_Freq item;
//    char leftBranch;
//    char rightBranch;
    
    HuffmanNode* left;
    HuffmanNode* right;
};

struct TNode
{
    int data;
    string str;
    TNode* left;
    TNode* right;
};

#endif /* NODE_H */

