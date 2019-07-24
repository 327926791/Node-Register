/*
 * File:   Node.cpp
 * Author: Crivils
 *
 * Created on 2015年10月8日, 下午7:37
 */
#include <iostream>
#include "Node.h"
using namespace std;

void Node::addResistor( ) {
    numRes++;
    return;

}

void Node::deleteResistor(){
    numRes--;
    return;
}

void Node::print(int nodeIndex) {
    cout << "Connections at node " << nodeIndex << ": " << numRes << " resistor(s)" << endl;

}

int Node::getnumRes() {
    return numRes;
}

 void Node::setVoltage(double vol, bool ifFix) {
     voltage = vol ;
     ifFixV = ifFix;
 }

Node::Node(int nodeid) {
    id = nodeid;
    numRes =0;
    next = NULL;
    voltage = 0;    
    ifFixV = false ;
}

Node::~Node() {  
}