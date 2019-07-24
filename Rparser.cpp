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
#include "easygl_constants.h"
#include "graphics.h"

using namespace std;
extern ResistorList *g_ResListPtr ;


easygl window("My Window", WHITE);

int countwords(string line) { //function used for counting words 
    string words;
    stringstream ss(line);

    int num = 0;
    while (1) {
        ss >> words;
        if (ss.fail())
            break;
        else
            num++;
    }
    return num;
}

void parser(string line, ResistorList & rl, NodeList & rn, int & currentR) {
    Node *node_p ;
    int node_index;
    string command;
    stringstream ss(line);
    int numofwords = countwords(line);

    ss >> command;

    if (command == "insertR") {
        // parse an insertR command

        string name;
        ss >> name;

        if (numofwords < 5) {
            cout << "Error: too few arguments" << endl;
            return;
        }
        if (numofwords > 5) {
            cout << "Error: too many arguments" << endl;
            return;
        }

        if (name == "all") {
            cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
            return;
        }

        double resist;
        ss >> resist;

        if (ss.fail()) {
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (resist < 0) {
            cout << "Error: negative resistance" << endl;
            return;
        }

        int node1;
        ss >> node1;

        if (ss.fail()) {
            cout << "Error: invalid argument" << endl;
            return;
        }

        if (ss.peek() != ' ' && ss.peek() != '\n' && ss.peek() != '\r' && ss.peek() != (-1)) { // check if it is an int
            //
            cout << "Error: invalid argument" << endl;
            return;
        }

        int node2;
        ss >> node2;

        if (ss.fail()) {
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (ss.peek() != ' ' && ss.peek() != '\n' && ss.peek() != '\r' && ss.peek() != -1) {
            cout << "Error: invalid argument" << endl;
            return;
        }

        if (node1 == node2) {
            cout << "Error: both terminals of resistor connect to node " << node1 << endl;
            return;
        }

        if (rl.insertResistor(currentR, name, resist, node1, node2)) {
            // insert successfully            
            currentR = currentR + 1;
            node_p = rn.insertNode(node1);
            node_p->addResistor() ;
            node_p = rn.insertNode(node2);
            node_p->addResistor() ;
            
        };

        //==============================================================================================================================================
        //==============================================================================================================================================
    } else if (command == "modifyR") {
        //Parse a modifyR command

        string mName;
        ss >> mName;

        if (numofwords < 3) {
            cout << "Error: too few arguments" << endl;
            return;
        }
        if (numofwords > 3) {
            cout << "Error: too many arguments" << endl;
            return;
        }

        if (mName == "all") {
            cout << "Error: resistor name cannot be the keyword \"all\"" << endl;
            return;
        }

        double mResist;
        ss >> mResist;

        if (ss.fail()) {
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (mResist < 0) {
            cout << "Error: negative resistance" << endl;
            return;
        }
        rl.modifyResistor(mName, mResist);
        
        //=============================================================================================================================================
        //==============================================================================================================================================
        
    } else if (command == "printR") {
        //Parse a printR command
        string pName;
        ss >> pName;

        if (numofwords < 2) {
            cout << "Error: too few arguments" << endl;
            return;
        }
        if (numofwords > 2) {
            cout << "Error: too many arguments" << endl;
            return;
        }

        rl.printR(pName);
    } else if (command == "printNode") {

        int pNode;
        string pNodeAll, meiyong;
        ss >> pNode;
        if (numofwords < 2) {
            cout << "Error: too few arguments" << endl;
            return;
        }
        if (numofwords > 2) {
            cout << "Error: too many arguments" << endl;
            return;
        }
        if (ss.fail()) {
            stringstream ss2(line);
            ss2 >> meiyong;
            ss2 >> pNodeAll;
            if (pNodeAll == "all") {
                //cout << "Print:" << endl;
                rn.printNode(rl);
            } else {
                cout << "Error: invalid argument" << endl;
                return;
            }
        } else {
            if (ss.peek() != ' ' && ss.peek() != '\n' && ss.peek() != '\r' && ss.peek() != (-1)) {
                cout << "Error: invalid argument" << endl;
                return;
            }
            rn.printNode(pNode, rl);
        }
        //=============================================================================================================================================
        //==============================================================================================================================================
        
    } else if (command == "deleteR") {
        //Parse an deleteR command
        Resistor *p;
        Node *np;

        string dName;
        ss >> dName;

        if (numofwords < 2) {
            cout << "Error: too few arguments" << endl;
            return;
        }

        if (numofwords > 2) {
            cout << "Error: too many arguments" << endl;
            return;
        }

        if (dName == "all") {
            //cout << "Deleted: all resistors" << endl;
            //rn.deleteAllResistor();
            rl.deleteResistor();
            rn.deleteResistor();
            cout << "Deleted: all resistors" << endl;
            return;
        } else {
            p = rl.findResistor(dName); //find which nodes the Resistor connected
            if (p != NULL) {
                np = rn.findNode(p->getNode1(), node_index);
                np->deleteResistor(); // resNum --
                np = rn.findNode(p->getNode2(), node_index);
                np->deleteResistor();
                rl.deleteResistor(dName); // delete the Resistor and free memory
            } else
                cout << "Error: Resistor " << dName << " not found" << endl;
        }
        
        //=============================================================================================================================================
        //==============================================================================================================================================
        
    } else if (command == "setV") {
        int nodeid;
        double vol;
        //Node *np;

        if (numofwords < 3) {
            cout << "Error: too few arguments" << endl;
            return;
        }
        if (numofwords > 3) {
            cout << "Error: too many arguments" << endl;
            return;
        }

        ss >> nodeid;
        if (ss.fail()) {
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (ss.peek() != ' ' && ss.peek() != '\n' && ss.peek() != '\r' && ss.peek() != -1) {
            cout << "Error: invalid argument" << endl;
            return;
        }
        ss >> vol;
        if (ss.fail()) {
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (ss.peek() != ' ' && ss.peek() != '\n' && ss.peek() != '\r' && ss.peek() != -1) {
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (!rn.setV(nodeid,vol,true))  { 
            // if return false meanning no node exist, creata a new one
            node_p = rn.insertNode(nodeid) ;
            node_p->setVoltage(vol, true) ;
        }
        cout << "Set: node " << nodeid << " to " << vol << " Volts" << endl;
        
        /*np = rn.findNode(nodeid, &node_index);
        if (np != NULL) {
            np->setVoltage(vol, true);
            cout << "Set: node " << nodeid << " to " << vol << " Volts" << endl;
        } else
            cout << "Error: Node " << nodeid << " not found" << endl;*/
        //=============================================================================================================================================
        //==============================================================================================================================================
        
    } else if (command == "unsetV") {
        int nodeid;
        //Node *np;

        if (numofwords < 2) {
            cout << "Error: too few arguments" << endl;
            return;
        }
        if (numofwords > 2) {
            cout << "Error: too many arguments" << endl;
            return;
        }

        ss >> nodeid;
        if (ss.fail()) {
            cout << "Error: invalid argument" << endl;
            return;
        }
        if (ss.peek() != ' ' && ss.peek() != '\n' && ss.peek() != '\r' && ss.peek() != -1) {
            cout << "Error: invalid argument" << endl;
            return;
        }
        rn.setV(nodeid,0,false);
        cout << "Unset: the solver will determine the voltage of node " << nodeid << endl;
        
        /*np = rn.findNode(nodeid, &node_index);
        if (np != NULL) {
            np->setVoltage(0, false);
            cout << "Unset: the solver will determine the voltage of node " << nodeid << endl;
        } else
            cout << "Error: Node " << nodeid << " not found" << endl;*/
        //=============================================================================================================================================
        //==============================================================================================================================================
        
    } else if (command == "solve") {
        if (rn.solve(rl)) {  // if successfully, print out the volatage
            rn.printVoltage() ;
        }
        else  // otherwise, print out Error message
            cout << "Error: no nodes have their voltage set" << endl;
        //=============================================================================================================================================
        //==============================================================================================================================================
        
    } else if (command == "draw") {
        //create a copy of resitors and sort the copied ResitorList for draw
        rn.solve(rl);
        g_ResListPtr->sortResistor() ;
        cout << "Draw: control passed to graphics window" << endl;
        window.set_world_coordinates(0, 0, max_width, max_heigth);
        window.gl_event_loop();
        cout << "Draw: complete; responding to commands again" << endl;
        
        // delete the copy of resistors
        g_ResListPtr->deleteResistor() ;
    } else {
        cout << "Error: invalid command" << endl;
    }
}