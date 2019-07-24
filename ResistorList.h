#pragma once
#ifndef RESISTORLIST_H
#define RESISTORLIST_H

#include "Resistor.h"

class ResistorList {
private:
Resistor* head;
int totalRes ;      //total number of the Resistors in the list

public:
ResistorList() ;
~ResistorList();
bool insertResistor(int rindex, string name, double resistance, int node1, int node2);
//int insertResistorForDraw(int rindex, string name, double resistance, int node1, int node2);
void modifyResistor(string name, double resistance);
void deleteResistor(string name);    // delete resistor by name
void deleteResistor();               //delete all resistors
void printR(string name);
void draw() ;                          // draw resistor
void sortResistor( ) ;
Resistor * gethead() const;          
Resistor * findResistor(string name) ;
};


#endif