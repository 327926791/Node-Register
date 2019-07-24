#ifndef RPARSER_H
#define RPARSER_H
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include "ResistorList.h"
#include "NodeList.h"

#define max_width 1500
#define max_heigth 1000
#define MIN_INTERATION_CHANGE 0.0001

int countwords(string line);
void parser(string line, ResistorList &resistor_p,NodeList &node_, int &index);

#endif /* RPARSER_H */