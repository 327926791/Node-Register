/*
 * File:   main.cpp
 * Author: Crivils
 *
 * Created on 2015年10月8日, 下午7:58
 */

#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

#include "Node.h"
#include "Resistor.h"
#include "Rparser.h"
#include "ResistorList.h"
#include "NodeList.h"
#include "easygl.h"
#include "graphics.h"
#include "easygl_constants.h"

using namespace std;

NodeList *g_NodeListPtr ;
ResistorList *g_ResListPtr ;

int main(int argc, char** argv) {
    string line,command ;
    int cur_resistor = 0 ;
   
    ResistorList rl,rld;
    NodeList rn;

    g_NodeListPtr = &rn ;
    g_ResListPtr = &rld ;
    
    
    while (1) {
        cout << "> ";
        getline(cin, line,'#');

        if (cin.eof()) {
            break;
        }

        stringstream ss(line);
        ss >> command ;
    
        if (command == "quit") {
           break ;
        }
        
        rld = rl ;
        parser(line, rl ,rn, cur_resistor);
    }
    
    // free all Node & Resistors before quit
    rl.deleteResistor() ;
    rn.deleteNode() ;
    
    return 0;
}
