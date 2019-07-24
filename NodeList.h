#pragma once
#ifndef NODELIST_H
#define NODELIST_H
#include <iostream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include "Node.h"
#include "ResistorList.h"

using namespace std;

class NodeList {
private:
    Node* head;
    int totalNode ;
    
public:
    NodeList();
    ~NodeList();
    
    Node * insertNode(int id);
    void deleteNode();
    Node * findNode(int nodeid, int &nodeIndex) ;
    Node * findNode(int &total) ;
    
    Node * findOrInsert();
    void printNode(const ResistorList &rl);
    void printNode(int nodeid, const ResistorList &rl);
    void deleteResistor();
    
    void draw() ;
    bool solve(const ResistorList &reslist) ;
    void printVoltage() ;
    bool setV(int nodeid, double vol,bool boolean);

};


#endif