/*
 * File:   Resisotr.cpp
 * Author: Crivils
 *
 * Created on 2015年10月8日, 下午7:37
 */
#include <stdio.h>
#include "Resistor.h"

Resistor::Resistor(int rIndex_, string name_, double resistance_, int node1_, int node2_) : rIndex(rIndex), name(name_), resistance(resistance_), node1(node1_), node2(node2_) {
    //cout << "constructor" << endl;
    rIndex = rIndex_;
    name = name_;
    resistance = resistance_;
    node1 = node1_;
    node2 = node2_;
    next = NULL;
}

string Resistor::getName() const {
    return name;
}

double Resistor::getResistance() const {
    return resistance;
}

void Resistor::setResistance(double resistance_) {
    resistance = resistance_;
}

int Resistor::getNode1() {
    return node1;
}

int Resistor::getNode2() {
    return node2;
}

void Resistor::print() {
}

Resistor::Resistor() {
    rIndex = EOF;
    name = "";
    resistance = 0;
    node1 = EOF;
    node2 = EOF;
    next = NULL;
   
}

Resistor::~Resistor() {
    delete next;
}

