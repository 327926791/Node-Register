#include <iostream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include "ResistorList.h"
#include "Resistor.h"
#include "NodeList.h"
#include "Rparser.h"
#include "easygl.h"

extern NodeList *g_NodeListPtr;
extern easygl window;

ResistorList::ResistorList() {
    totalRes = 0;
    head = NULL;
}

ResistorList::~ResistorList() {
    //delete head;
}


void ResistorList::sortResistor ( ) {
    Resistor *r, *new_head, *new_p ;
    Resistor *p = head; 
    Resistor *prev = NULL;

    int i, done ;
    
    //cout << totalRes << endl ;
    for (i=0; i<totalRes; i++) {
        r =  new Resistor(i, p->name, p->resistance, p->node1, p->node2);
        //cout << *r << endl ;
        
        if (i == 0) {
             head = r ;
             new_p = head ;
             prev = new_p ;
        }
        else {
            new_p = head ;
            done = 0 ;
            while (new_p != NULL) {
                if ((new_p->node1 > r->node1 && new_p->node2 > r->node1) || (new_p->node1 > r->node2 && new_p->node2 > r->node2)) { //insert the Res before
                    if (new_p == head) { // insert to the First
                        head = r;
                        r->next = new_p;
                        done = 1 ;
                        break ;
                    } else {
                        prev->next = r;
                        r->next = new_p;     
                        done = 1 ;
                        break ;
                    }
                }
                else {
                    prev = new_p ;
                    new_p = new_p->next ;
                }
            }
            if (done == 0)
                prev->next = r ;
        }
        p = p->next ;
    }
}


bool ResistorList::insertResistor(int rindex, string name, double resistance, int node1, int node2) {
    Resistor *r = new Resistor(rindex, name, resistance, node1, node2);
    Resistor *p = head;
    Resistor *prev = NULL;
    if (p == NULL) {
        //cout << "Inserted: "<< *r <<endl ;
        head = r;
        
    } else {
        while (p != NULL) {
            if (p->name == name) {
                cout << "Error: resistor " << name << " already exists" << endl;
                return false;            
            } else {
                prev = p;
                p = p->next;
            }
        }
        prev->next = r;
    }
    cout << "Inserted: resistor " << *r << endl;
    totalRes ++ ;
    return true;
}

void ResistorList::modifyResistor(string name, double resistance) {
    Resistor *p = head;

    while (p != NULL) {
        if (p->name == name) {
            cout << "Modified: resistor " << name << " from " << p->resistance << " Ohms to " << resistance << " Ohm" << endl;
            p->resistance = resistance;
            return;
        } else
            p = p->next;
    }
    cout << "Error: resistor " << name << " not found" << endl;
}


void ResistorList::deleteResistor() { //delete all resistor
    Resistor *r = head;

    while (r != NULL) {
        //cout<<"delete..."<<r->name <<endl ;
        head = r->next;
        r->next = NULL;
        delete r;
        totalRes--;
        r = head;
    }

    head = NULL;
}

void ResistorList::deleteResistor(string name) {
    Resistor *p = head;
    Resistor *prev = p;

    if (head != NULL && head->name == name) { // match the first Node 
        head = head->next;
        p->next = NULL;
        delete p;
        totalRes--;
        cout << "Deleted: resistor " << name << endl;
        return;
    }

    while (p != NULL) {
        if (p->name == name) {
            prev->next = p->next;
            p->next = NULL;
            cout << "Deleted: resistor " << name << endl;
            delete p;
            totalRes--;
            return;
        } else {
            prev = p;
            p = p->next;
        }
    }
    cout << "Error: resistor " << name << " not found" << endl;

}

void ResistorList::printR(string name) {
    Resistor * p = head;
    while (p != NULL) {
        if (p->name == name) {
            cout << "Print:" << endl;
            cout << *p << endl;
            return;
        } else
            p = p->next;
    }
    cout << "Error: resistor " << name << " not found" << endl;

}

Resistor * ResistorList::gethead() const {
    return head;
}

Resistor * ResistorList::findResistor(string name) {
    Resistor *p = head;

    while (p != NULL) {
        if (p->name == name) {
            return p;
        } else
            p = p->next;
    }
    return NULL;
}

void ResistorList::draw() {
    Resistor *res_p;
    Node *node_p;
    int node_index, totalNode;
    float x1, x2, y, x_intv, y_intv=0, res_index;
    char ss[30];
    string pname;

    if (totalRes == 0) //no Resistor, return directly
        return ;
    
    res_p = head;
    node_p = g_NodeListPtr->findNode(totalNode);
    //cout << totalNode <<endl ;
    
    // calculate the interval between two nodes and two resistors
    x_intv = max_width / totalNode;
    y_intv = (max_heigth - 150) / totalRes;

    // draw resitor one by one
    res_index = 0;
    while (res_p != NULL) {
        // draw connection point
        node_p = g_NodeListPtr->findNode(res_p->node1, node_index);
        
        x1 = x_intv * node_index + 120;
        y = y_intv * res_index + 200;
        // draw the first point on node1
        window.gl_setcolor(BLACK) ;
        window.gl_fillarc(x1, y, 15, 0, 360);
        // draw another point on node2
        node_p = g_NodeListPtr->findNode(res_p->node2, node_index);
        x2 = x_intv * node_index + 120;
        window.gl_fillarc(x2, y, 15, 0, 360);

        // draw resistor
        window.gl_fillresistor(x1, x2, y);

        // draw text
        window.gl_setcolor(BLACK) ;
        sprintf(ss, "(%4.2f Ohm)", res_p->resistance);
        pname = res_p->name;
        if (x1 > x2) {
            window.gl_drawtext(x2 + (x1 - x2 - 200) / 2 + 100, y - 30, pname.append(ss), 400);
        } else {
            window.gl_drawtext(x1 + (x2 - x1 - 200) / 2 + 100, y - 30, pname.append(ss), 400);
        }

        res_p = res_p->next;
        res_index++;
    }
}

