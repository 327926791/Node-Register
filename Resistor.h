#pragma once
/*
* File: Resistor.h
*/
#ifndef RESISTOR_H
#define RESISTOR_H
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Resistor {
private:
int rIndex;
double resistance; // resistance (in Ohms)
string name; // C++ string holding the label
int node1;
int node2; // IDs of nodes it attaches to
Resistor* next;

public:
friend class ResistorList;
friend class NodeList ;
Resistor(int rIndex, string name_, double resistance_, int node1_, int node2_);
Resistor();
// rIndex_ is the index of this resistor in the resistor array
// endpoints_ holds the node indices to which this resistor connects
~Resistor();
string getName() const; // returns the name
double getResistance() const; // returns the resistance
void setResistance(double resistance_);
// you *may* create either of the below to print your resistor
void print();
int getNode1();
int getNode2();

friend ostream & operator<<(ostream&out, const Resistor&r) {

//out << setw(20) << left << r.name << " " << setw(8) << setprecision(2) << setiosflags(ios::fixed) << right << r.resistance << " Ohms " << r.node1 << " -> " << r.node2;
out << r.name << " "  << setprecision(2) << setiosflags(ios::fixed) << r.resistance << " Ohms " << r.node1 << " -> " << r.node2;
return out;
};

};

#endif