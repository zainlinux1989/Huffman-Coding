/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   compress.h
 * Author: zain
 *
 * Created on October 16, 2016, 7:01 PM
 */
#include <string>
#include <queue>
#include <map>
#include "FileReader.h"
#include "Data_Freq.h"
#include "HuffmanNode.h"
#include "dataPath.h"
#include <vector>
#include <cmath>
#include <cstdlib>
#include <sstream>
using namespace std;
#ifndef COMPRESS_H
#define COMPRESS_H

struct Node
{
    Node* next;
    HuffmanNode dataFreq_node;
};

struct Compare
{
  bool operator()(const HuffmanNode* L, const HuffmanNode* R) const
  {
      // compare condition for order 
    return L->item.getFreq() > R->item.getFreq();
  }
};

class Huffman {
public:
    Huffman();

    void compressFile(const string& fileName);
    void decompressFile(const string& fileName);
    
    virtual ~Huffman();
private:
    
    string getBinary(int num);
    void decimalToBinary(int number,stringstream &s);
    void createCompressFile(const string& fileName);
    void printMaxHeap(HuffmanNode *root);
    void deleteMaxHeap(HuffmanNode *&root);
    void generateHuffmanCode(HuffmanNode * temproot, string s);
  
    string binaryNumber;
    FileReader *file;
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> minPriorityQ;

    // number and number code
    map<int,string> num_Key;
//    vector<Data_Freq> dataFreqList;
    
};

#endif /* COMPRESS_H */

