/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   huffman.cpp
 * Author: zain
 * 
 * Created on October 16, 2016, 7:01 PM
 */

#include <stddef.h>
#include <stdio.h>

#include "Huffman.h"
#include "HuffmanNode.h"

Huffman::Huffman()
{
    
}

// compress file 
void Huffman::compressFile(const string& fileName)
{
    vector<int> numList;
    file=new FileReader(fileName);
    file->processFile();
    numList=file->getNumList();
    
    ifstream inputFile(fileName.c_str(),ios::in);
    
    // incorrect file open checking  
    if(!inputFile)
    {
        cout<<"Invalid file or file not exist"<<endl;
        return;
    }
    inputFile.close();
    
    // remove .8b from last and add .out for output file 
    string outputFileName=fileName.substr(0,fileName.size()-3)+".zif";
    ofstream outputFile;        // output file adding header
    outputFile.open(outputFileName.c_str(),ios::out);
    
    int freqTab[256];
    
    // zero all index of frequency table
    for(int i=0;i<256;i++)
        freqTab[i]=0;
    
    // modify frequency table
    for(int i=0;i<numList.size();i++)
    {
        freqTab[numList.at(i)]++;
    }
    
    Data_Freq df;
    HuffmanNode *huffmanNode;
    
    int checkFlag=0;
    
    // variable if only one pattern present in file
    int onlyOneItemData=0;
    int onlyOneItemFreq=0;
    
    // add non zero frequency items in dataFreq list
    for(int i=0;i<256;i++)
    {
        // create nodes and push in queue
        if(freqTab[i]>0)
        {
            df.setData(i);
            df.setFreq(freqTab[i]);
            
            // create huffman node 
            huffmanNode=new HuffmanNode;
            huffmanNode->item=df;
           
            huffmanNode->left=NULL;
            huffmanNode->right=NULL;
            
            // open compress file add data.frequency at first as header
            if(checkFlag==0)
            {
                outputFile<<df.getData()<<"."<<df.getFreq()<<" ";
                onlyOneItemData=df.getData();
                onlyOneItemFreq=df.getFreq();
                checkFlag++;
            }
            else if(checkFlag==1)
            {
                outputFile<<df.getData()<<"."<<df.getFreq();
                checkFlag++;
            }
            else if(checkFlag>1)
            {
                outputFile<<" "<<df.getData()<<"."<<df.getFreq();
            }

            // and push in priority queue
            minPriorityQ.push(huffmanNode);
        }
    }
    
    outputFile<<endl;
    // close file after adding header
    outputFile.close();
    
    // if only one pattern present in file
    if(checkFlag==1)
    {
        outputFile.open(outputFileName.c_str());
        outputFile<<onlyOneItemData<<"."<<onlyOneItemFreq;
        outputFile<<endl;
        outputFile.close();
    }
    
    // zero all index of frequency table
    for(int i=0;i<256;i++)
        freqTab[i]=0;
    
    // run while loop until queue number of items in queue becomes 1 
    while(minPriorityQ.size()!=1)
    {
        // create internal heap node
        HuffmanNode *heapInternalNode=new HuffmanNode;
        
//        heapInternalNode->leftBranch='0';     // set node left branch tag = 0        
        heapInternalNode->left=minPriorityQ.top();    // attach node left with min queue item       
        heapInternalNode->item.setData(-1);       // set node data = -1
        heapInternalNode->item.setFreq(minPriorityQ.top()->item.getFreq());   // get frequency of first min queue item, set to node frequency  
        minPriorityQ.pop();     // pop item
        
        
//        heapInternalNode->rightBranch='1';    // set node left branch tag = 0
        heapInternalNode->right=minPriorityQ.top();   // attach node right with next min queue item  
        heapInternalNode->item.setFreq(heapInternalNode->item.getFreq()+minPriorityQ.top()->item.getFreq());    // get frequency of second min queue item and add with current node frequency, and set
        minPriorityQ.pop();
        
        minPriorityQ.push(heapInternalNode);  // push node to queue again
    }
    
    HuffmanNode *heapRootNode=minPriorityQ.top();     // get last item of queue and it is a root node of MaxHeap 
    minPriorityQ.pop();

    // print Max Heap
//    printMaxHeap(heapRootNode);
    
    string code;
    
    // only one data pattern present in file
    if(heapRootNode->left==NULL&&heapRootNode->right==NULL)
    {
        heapRootNode->item.setCode("0");
        
        num_Key[heapRootNode->item.getData()]=heapRootNode->item.getCode();
    }
    else
        generateHuffmanCode(heapRootNode,code);
    
    // create compress file
    createCompressFile(outputFileName);
    
    // delete all heap nodes after compress file creation
//    deleteMaxHeap(heapRootNode);
    
    // delete node also
//    delete huffmanNode;
    
    
}

// function compressFile function
void Huffman::createCompressFile(const string& fileName)
{
    ifstream inputFile;
    ofstream outputFile;
    
    inputFile.open(file->getFileName().c_str(),ios::in);
    if(!inputFile)
    {
        cout<<"Invalid file or file not exist"<<endl;
        return;
    }
    
    outputFile.open(fileName.c_str(),ios::app);     // append data after data.frequency header
    
     
    FileReader *f=new FileReader;
    
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
            // convert binary number of input file convert into decimal, find number(key) from map and print its corresponding binary(value) in output file.
            outputFile<<num_Key[f->binToDec(oneByte)];
            count=0;
            oneByte="";
        }
    }
    outputFile.close();
    inputFile.close();
}

// generate huffman code from huffman tree
void Huffman::generateHuffmanCode(HuffmanNode * tempRoot, string s)
{
    HuffmanNode * dummyRoot = new HuffmanNode;
    dummyRoot = tempRoot;

    dummyRoot->item.setCode(s);
    if (dummyRoot == NULL)
    {
//        return;
    }
    else if (dummyRoot->left == NULL && dummyRoot->right== NULL)
    {
        // get huffman code of digit.
        num_Key[dummyRoot->item.getData()]=dummyRoot->item.getCode();
    }
    else
    {

        dummyRoot->left->item.setCode(s.append("0"));
        s.erase(s.end() - 1);
        dummyRoot->right->item.setCode(s.append("1"));
        s.erase(s.end() - 1);

        generateHuffmanCode(dummyRoot->left, s.append("0"));
        s.erase(s.end() - 1);
        generateHuffmanCode(dummyRoot->right, s.append("1"));
        s.erase(s.end() - 1);
    }
}

// print MAX Heap in infix order, edit to print branch pattern for each external node
void Huffman::printMaxHeap(HuffmanNode* root)
{
    if(root!=NULL)
    {
        printMaxHeap(root->left);
        if(root->item.getData()!=-1)
        {
            cout << endl;
            cout << "Data : " << root->item.getData() << endl;
            cout << "Frequency : " << root->item.getFreq() << endl;
            cout << "Code : " << root->item.getCode() << endl;
        }
        printMaxHeap(root->right);
    }
}

// delete heap tree after creating compress file 
void Huffman::deleteMaxHeap(HuffmanNode* &root)
{
    if(root==NULL)
    {
        return;
    }
    
    deleteMaxHeap(root->left);
    
    deleteMaxHeap(root->right);
    
    delete root;
    root=NULL;
}

// decompress compressed file
void Huffman::decompressFile(const string& fileName)
{
    vector<Data_Freq> DF;
    DF.clear();   
    
    ifstream inputFile;
    inputFile.open(fileName.c_str(),ios::in);
    
    if(!inputFile)
    {
        cout<<"Invalid file or file not exist"<<endl;
        return;
    }
    
    // decompress file 
    string outputFileName=fileName.substr(0,fileName.length()-3)+"_N.8b";
    ofstream outputFile;
    outputFile.open(outputFileName.c_str(),ios::out);
    
    char ch='0';
 
    string dataStr="";
    string freqStr="";
    int data=0;
    int freq=0;

   
    // read header tree from file
    while(ch!='\n')
    {  
        // read data.frequency from file

          // read data
          while(inputFile.get(ch)&&ch!='.')
          {
              dataStr=dataStr+ch;
          }
          
          // read frequency
          while(inputFile.get(ch)&&ch!=' ')
          {
            if(ch==' '||ch=='\n')
            {
                break;
            }
            freqStr=freqStr+ch;
          }      
          
          data=atoi(dataStr.c_str());
          freq=atoi(freqStr.c_str());
          DF.push_back(Data_Freq(data, freq));
        
       
       
        if(ch=='\n')
        {
            break;
        }
         
        freq=0;
        data=0;   
        freqStr="";
        dataStr="";
    }
    
    // create huffman node 
    HuffmanNode *huffmanNode;
    
    
    // create nodes which contain Data and Frequency and push in queue
    for (int i = 0; i < DF.size(); i++)
    {
        // create huffman node 
        huffmanNode = new HuffmanNode;
        huffmanNode->item = DF[i];

        huffmanNode->left = NULL;
        huffmanNode->right = NULL;

        // and push in priority queue
        minPriorityQ.push(huffmanNode);
    }
      
    // if than one nodes present in huffman tree
    if (DF.size() > 1)
    {
        // run while loop until queue number of items in queue becomes 1 
        while (minPriorityQ.size() != 1)
        {
            // create internal heap node
            HuffmanNode *heapInternalNode = new HuffmanNode;
     
            heapInternalNode->left = minPriorityQ.top(); // attach node left with min queue item       
            heapInternalNode->item.setData(-1); // set node data = -1
            heapInternalNode->item.setFreq(minPriorityQ.top()->item.getFreq()); // get frequency of first min queue item, set to node frequency  
            minPriorityQ.pop(); // pop item


            heapInternalNode->right = minPriorityQ.top(); // attach node right with next min queue item  
            heapInternalNode->item.setFreq(heapInternalNode->item.getFreq() + minPriorityQ.top()->item.getFreq()); // get frequency of second min queue item and add with current node frequency, and set
            minPriorityQ.pop();

            minPriorityQ.push(heapInternalNode); // push node to queue again
        }

    }
    
    HuffmanNode *heapRootNode=minPriorityQ.top();     // get last item of queue and it is a root node of MaxHeap 
    minPriorityQ.pop();
    
    // print Max Heap
//    printMaxHeap(heapRootNode);
    
    // read compressed file, traverse in tree and get original code from leaf node 
    
    // if than one nodes present in huffman tree
    if (DF.size() > 1)
    {
        HuffmanNode *current;
        current=heapRootNode;
    
        inputFile.get(ch);
        while (!inputFile.eof())
        {
            if (ch == '0')
            {
                current = current->left;
            }
            else if (ch == '1')
            {
                current = current->right;
            }

            // if current point out leaf node
            if (current->left == NULL && current->right == NULL)
            {
                outputFile << getBinary(current->item.getData()); // print 8-bit binary in file 
                current = heapRootNode; // reset current pointer to root
            }
            inputFile.get(ch);
        }
    }
    
    // if only one nodes present in huffman tree
    else if(DF.size()==1)
    {
        inputFile.get(ch);
        while(!inputFile.eof())
        {
            outputFile<<getBinary(huffmanNode->item.getData());
            inputFile.get(ch);
        }
    }
    
    inputFile.close();
    outputFile.close();
}


// get binary from decimalToBinary function and convert into 8-bit length
string Huffman::getBinary(int num)
{
    stringstream binStr;
    string binaryStr;
    
    decimalToBinary(num,binStr);
    
    // convert string stream into string
    binaryStr=binStr.str();
    
    // find difference convert binary into 8-bit binary by add zero at beginning  
    int strDiff=8-binaryStr.length();
    for(int i=0;i<strDiff;i++)
    {
        binaryStr="0"+binaryStr;
    }
    return binaryStr;
}

// convert decimal number into binary number
 void Huffman::decimalToBinary(int number, stringstream& numStr) 
 {
	int remainder;

	if(number <= 1) {
		numStr << number;
		return;
	}

	remainder = number%2;
	decimalToBinary(number >> 1,numStr);    
	numStr << remainder;
}  
// for decompression write huffman code table in output file than write compress string get pattern and match with table
Huffman::~Huffman()
{
}

